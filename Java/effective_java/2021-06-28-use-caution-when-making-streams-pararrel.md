# ITEM 48: 스트림 병렬화는 주의해서 사용해라

## Java 동시성 프로그래밍

1. Java5 : `java.util.concurrent`, `Executor`
2. Java7 : 고성능 병렬 분해(parallel decom-position) 프레임워크 `fork-join`
3. Java 8 : Stream의 `paralle` 메서드



## 안정성과 응답가능 상태 유지

동시성 프로그래밍을 할 때는 안정성(safety)과 응답 가능(liveness) 상태를 유지하기 위해 노력해야하는데, 병렬 스트림 파이프라인 프로그래밍에서도 동일하다.

다음 예는 스트림을 사용해 20개의 메르센 소수를 생성하는 프로그램이다.

```java
public static void main(String[] args) {
  primes().map(p -> TWO.pow(p.intValueExact()).subtract(ONE))
        .filter(mersenne -> mersenne.isProbablePrime(50))
        .limit(20)
        .forEach(System.out::println);
}

static Stream<BigInteger> primes() {
  return Stream.iterate(TWO, BigInteger::nextProbablePrime);
}
```

프로그램 수행시 약 12.5초 정도 걸리는데, 속도를 높이고 싶어 `paralle()` 을 호출하면, 아무것도 출력하지 못하면서 CPU는 90%나 차지하는 상태가 되어, 강제 종료시까지 응답없는 상태가 될 수 있다.
이러한 현상은 스트림 라이브러리가 파이프라인을 병렬화하는 방법을 찾아내지 못했기 때문에 발생한 것이다.
데이터 소스가 `Stream.iterate()` 이거나 중간 연산으로 `limit()`을 사용하면 파이프라인 병렬화로는 성능 개선을 할 수 없다.
즉, **스트림 파이프라인을 마구잡이로 병렬화하면 안되며, 오히려 성능이 나빠질 수 있다.**

### 병렬화 하기 좋은 경우

#### 참조 지역성이 뛰어난 경우

- `ArrayList` 
- `HashMap`
- `HashSet`
- `ConcurrentHashMap`
- 배열
- int 범위
- long 범위

위 자료구조들은 **모두 데이터를 원하는 크기로 정확하고 쉽게 나눌 수 있어, 일을 다수의 스레드에 분배하기 좋다**.
또한, 원소들을 순차적으로 실행할 때 **참조 지역성이 뛰어나다**.
(*참조지역성 : 이웃한 원소의 참조들이 메모리에 연속해서 저장되어 있음.*)
참조 지역성이 낮으면 스레드는 데이터가 주 메모리에서 캐시 메모리로 전송되어 오기를 기다리며 대부분 시간을 낭비하며 보내게 되며, 참조 지역성은 대량의 데이터를 처리하는  벌크 연산을 병렬화 할 때 아주 중요한 요소로 작용한다.
기본 타입의 배열은 데이터 자체가 메모리에 연속해서 저장되기 때문에 참조 지역성이 가장 뛰어나 병렬화 효과가 가장 좋다.

#### 종단 연산 - 축소(reduction)

종단 연산에서 수행하는 작업량이 파이프라인 전체 작업에서 상당 비중으로 차지하며, 순차적인 연산이라면 파이프라인 병렬 수행의 효과는 제한될 수 밖에 없다.

축소(reduction)는 파이프라인에서 만들어진 모든 원소를 하나로 합치는 작업이다.

- reduce 메서드
- min, max, count, sum 완성된 형태로 제공되는 메서드
-  `anyMatch`, `allMatch`, `noneMatch` 와 같이 조건에 맞으면 바로 반환하는 메서드

위 메서드는 병렬화에 적합하지만, 가변 축소를 수행하는 Stream의 `collect` 메서드는 컬렉션들을 합치는 부담이 크기때문에 병렬화에 적합하지 않다.

#### `spliterator` 메서드 재정의

직접 구현한 `Stream`, `Iterable`, `Collection`이 병렬화 이점을 제대로 누리게 하려면 `spliterator` 메서드를 반드시 재정의하고 결과 스트림의 병렬화 성능을 강도 높게 테스트하는 것이 좋다.

하지만, `spliterator` 메서드를 재정의 하는 것은 난이도가 있으며, 지금은 다루지 않고, 나중에 기회가 된다면 더 공부해볼 것이다!

## 마무리

- **스트림을 잘못 병렬화하면 성능이 나빠질 뿐만 아니라 결과 자체가 잘못되거나 예상 못한 동작(safety failure)이 발생할 수 있다.**
    - `Stream` 명세대로 동작하지 않을 때, 발생할 수 있음
    - 예를들어, Stream reduce 연산의 `accumulator`와 `combiner` 함수는 반드시 결합 법칙을 만족하고, 간섭받지 않고, 상태를 갖지 않아야한다.
- 위 조건을 다 만족하더라도, 병렬화에 드는 추가 비용을 상쇄하지 못한다면, 성능 향상이 미미할 수 있음.
    - 스트림 안의 원소 수와 원소당 수행되는 코드 줄 수를 곱해 수십만이 되어야 성능향상을 느낄 수 있다.
- 스트림 병렬화는 오직 성능 최적화 수단이다.
    - 변경 전후로 테스트해 병렬화 사용에 가치가 있는지 확인해야한다.
- 계산이 정확하고, 확실히 성능이 좋아졌을 경우에만 병렬화를 실 운영에 적용해야한다.
- 조건이 잘 갖춰지면, parallel 메서드 호출 하나로 프로세서 코어 수에 비례하는 성능 향상을 만끽할 수 있다.
