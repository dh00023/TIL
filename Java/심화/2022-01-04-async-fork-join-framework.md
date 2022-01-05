# ForkJoin Framework

병렬 스트림은 요소들을 병렬 처리하기 위해 ForkJoin Framework를 사용한다.

![https://3.bp.blogspot.com/-Q8AvlvJINSM/WDOuW6lqXLI/AAAAAAAAAvw/URAPQ-s1P4owTkk1Bp4KrMxxtBYA9K_pgCLcB/s1600/%25EC%25BA%25A1%25EC%25B2%2598.JPG](./assets/forkjoin.JPG)

- Fork 단계 : 전체 데이터를 서브 데이터로 분리
- 서브 데이터를 멀티 코어에서 병렬로 처리
- Join 단계 : 서브 데이터 결과를 결합해 최종 결과

![https://t1.daumcdn.net/cfile/tistory/250ED44B58D7697A25](./assets/250ED44B58D7697A25.jpeg)

ForkJoin 프레임워크는 `ExecutorService`의 구현 객체인 `ForkJoinPool`을 사용해서 작업 스레드를 관리한다.

## RecursiveTask

스레드 풀을 이용하려면 `RecursiveTask`의 서브클래스를 만들어야한다.

```java
public abstract class RecursiveTask<V> extends ForkJoinTask<V> {
```
-  ForkJoinTask

```java
public abstract class ForkJoinTask<V> implements Future<V>, Serializable {
```

`RecursiveTask`는 `ForkJoinTask`를 상속하고 있으며, `fork()`, `join()` 메소드를 호출할 수 있으며, Task 분할 로직과 더 이상 분할 불가능한 경우 sub task의 결과를 생성할 로직을 추상메서드인 `compute()` 에 구현해야한다.

그러므로 대부분의 compute 메서드는 다음과 같은 의사코드 형식을 유지한다.

```java
// https://java-8-tips.readthedocs.io/en/stable/forkjoin.html
if(Task is small) { // Task가 충분히 작거나 더 이상 분할할 수 없으면
    Execute the task  // task 수행
} else {
    //Split the task into smaller chunks
    // task를 두 sub task로 분할
    ForkJoinTask first = getFirstHalfTask();
    first.fork(); // task 분할
    ForkJoinTask second = getSecondHalfTask();
    second.compute(); // 태스크가 다시 서브태스크로 분할되도록 재귀 호출
    first.join(); // task 합산
}
```

```java

public class CalculatorTask extends RecursiveTask<Long> {

    private final long[] numbers;
    private final int start;
    private final int end;
    public static final long THRESHOLD = 4; // 이 값 이하의 서브태스크는 더 이상 분할 할 수 없음

    public CalculatorTask(long[] numbers) {
        this(numbers, 0, numbers.length);
    }

    /**
     * 메인 task의 subTask를 재귀적으로 만들 떄 사용할 비공개 생성자
     * @param numbers
     * @param start
     * @param end
     */
    private CalculatorTask(long[] numbers, int start, int end) {
        this.numbers = numbers;
        this.start = start;
        this.end = end;
    }

    @Override
    protected Long compute() {
        int length = end - start; // task에서 더할 배열의 길이

        if(length <= THRESHOLD) {
            return computeSequentially(); // 기준 값과 같거나 작으면 순차적으로 결과를 계산
        }

        // 작업을 반으로 분할
        CalculatorTask leftTask = new CalculatorTask(numbers, start, start + length / 2);
        leftTask.fork();  //분할된 작업을 다른 스레드로 비동기 실행

        CalculatorTask rightTask = new CalculatorTask(numbers, start + length / 2, end);

        long rightResult = rightTask.compute(); // 현재 스레드에서 compute 재귀호출
        long leftResult = leftTask.join();  // 분할된 작업결과를 조인
        return rightResult + leftResult;  // 분할된 두 결과 값의 합
    }

    // 분할된 배열을 계산
    private long computeSequentially() {
        long sum = 0;
        for (int i = start; i < end; i++) {
            sum += numbers[i];
        }
        return sum;
    }
}

```

```java
long[] numbers = LongStream.rangeClosed(1, n).toArray();
ForkJoinTask<Long> task = new CalculatorTask(numbers);
long result = ForkJoinPool.invoke(task);
```

## Fork/Join 프레임워크 제대로 사용하기

- `join()` 메서드를 task에 호출하면 task의 결과값이 나올 때까지 호출자를 블록시킨다. 그러므로 두 개의 sub task가 모두 시작된 다음에 `join()`을 호출해야한다.
- `RecursiveTask` 내에서는 `ForkJoinPool.invoke()` 메서드를 사용하면 안된다. 순차 코드에서 병렬 계산을 시작할 때만 `invoke()`를 사용해야한다.
- 두 개의 task모두에 `fork()` 메서드를 호출하는 것보다 한 쪽은 `fork()`, 다른 한 쪽은 `compute()`를 호출하는 것이 효율적이다.
  - 두 sub task중 한 개는 같은 스레드를 재사용할 수 있더 불필요한 Task를 할당하는 오버헤드를 줄일 수 있음
- Fork/Join 프레임워크에서 병렬 계산은 디버깅하기 어렵다.
- 멀티코어에서 Fork/Join 프레임워크을 사용하는 것이 순차 처리보다 항상 빠르지 않다. 병렬 처리로 성능을 개선하려면 독립적인 서브 태스크로 분할 할 수 있어야한다.

## Work Stealing

Work Stealing 기법에서 `ForkJoinPool`의 모든 스레드를 거의 공정하게 분할한다.

```java
WorkQueue[] queues; 
final ForkJoinPool.WorkQueue workQueue; // work-stealing mechanics
```

`ForkJoinPool`에는 `WorkQueue`가 있으며, `WorkQueue`는 모든 스레드가 공유한다. 스레드는 자신의 작업수행 `WorkQueue`와 전체가 공유하는 `WorkQueue[]`를 가지고 작업을 수행하며, `fork()` 발생시 push한다.

각 스레드는 자신의 WorkQueue에서 pop하여 작업을 실행하고, 자신에게 할당된 작업이 없으면,`poll()` 메서드를 통해  다른 스레드 큐의 꼬리에서 작업을 훔쳐와 수행한다.모든 task가 작업이 완료될때까지 이 과정을 반복한다.

## Spliterator(Java8)

`Spliterator`는 분할할 수 있는 반복자로 병렬 작업에 특화되어있다.
Java8은 컬렉션 프레임워크에 포함된 모든 자료구조에 사용할 수 있는 default Spliterator 구현체를 제공한다.

```java
public interface Spliterator<T> {
    
    // 요소를 순차적으로 소비하면서 탐색해야 할 요소가 있으면 true 반환(Iterator 동작과 동일)
    boolean tryAdvance(Consumer<? super T> action);
    
    // 자신이 반환한 요소를 분할해 두번째 Spliterator 생성
    Spliterator<T> trySplit();

    // 탐색해야할 요소 수 정보
    long estimateSize();

    // Spliterator특성 정의
    int characteristics();
}
```

![https://user-images.githubusercontent.com/61372486/128547827-033a007a-9a64-421f-9785-1cda9062a0d6.png](./assets/128547827-033a007a-9a64-421f-9785-1cda9062a0d6.png)

위 이미지 처럼 스트림을 여러 스트림으로 분할하는 과정은 재귀적으로 일어난다. Step3과 같이 `trySplit()` 이 null을 반환했다는 것은 더 이상 분할할 수 없음을 나타내며 모든 `trySplit()`이 null을 반환하면 종료된다. 여기서 분할 과정은 `characteristics()`에 정의한 특성에 영향을 받는다.

### Spliterator 특성


| 특성       | 의미                                                         |
| ---------- | ------------------------------------------------------------ |
| ORDERED    | 리스트와 같이 요소에 정해진 순서가 있으므로 요소를 탐색하고 분할할 때 이 순서에 유의해야한다. |
| DISTINCT   | x, y 두 요소를 방문했을 때 `x.equals(y)`는 항상 false를 반환한다. |
| SORTED     | 탐색된 요소는 미리 정의된 정렬 순서를 따른다.                |
| SIZED      | 크기가 알려진 소스(ex. Set)로 Spliterator를 생성했으므로 `estimatedSize()`는 정확한 값을 반환한다. |
| NON-NULL   | 탐색하는 모든 요소는 null이 아니다.                          |
| IMMUTABLE  | 이 Spliterator는 불변이다.<br />요소를 탐색하는 동안 요소를 추가, 삭제, 수정할 수 없다. |
| CONCURRENT | 동기화 없이 Spliterator의 소스를 여러 스레드에서 동시에 수정할 수 있다. |
| SUBSIZED   | 이 Spliterator, 분할되는 모든 Spliterator는 SIZED특성을 갖는다. |

## 병렬 스트림

병렬 처리를 위해 코드에서 포크조인 프레임워크를 직접 사용할 수 있지만, 병렬 스트림을 이용할 경우 백그라운드에서 사용되기때문에 쉽게 병렬 처리를 할 수 있다.

**병렬 스트림이란 각각의 스레드에서 처리할 수 있도록 스트림 요소를 여러 청크로 분할한 스트림**이다. 병렬 스트림을 이용하면 모든 멀티코어 프로세서가 각각의 청크를 처리하도록 할당 할 수 있다.

```java
public static long parallelSum(long n) {
        return Stream.iterate(1L, i -> i + 1)
                .limit(n)
                .parallel()  // 순차 스트림을 병렬 스트림으로 변환
                .reduce(0L, Long::sum); // 스트림의 모든 숫자를 더함
    }
```

| 메소드           | 인터페이스                                                   | 리턴타입                                             |
| ---------------- | ------------------------------------------------------------ | ---------------------------------------------------- |
| parallelStream() | java.util.Collection                                         | Stream                                               |
| parallel()       | java.util.Stream.Stream<br/>java.util.Stream.IntStream<br/>java.util.Stream.LongStream<br/>java.util.Stream.DoubleStream | Stream<br/>IntStream<br/>LongStream<br/>DoubleStream |

병렬 스트림은 내부적으로 `ForkJoinPool`을 사용하며, 기본적으로 `ForkJoinPool`은 `Runtime.getRuntime().availableProcessors()`의 만큼의 스레드를 가진다. 

```java
System.setProperty("java.util.concureent.ForkJoinPool.common.parallelism", "15");
```

위와 같이 해당 값을 변경할 수는 있지만 전역 설정 코드이기 때문에 모든 병렬 스트림 연산에 영향을 주므로 기본값을 사용하는 것을 권장한다.

병렬화를 이용하면 순차나 반복 형식에 비해 성능이 좋아질 것이라 추측할 수 있다. 하지만 스트림 병렬 처리가 스트림 순차 처리보다 항상 실행 성능이 좋다고 판단해서는 안된다.

다음은 [JMH 라이브러리](https://github.com/melix/jmh-gradle-plugin)를 이용해 벤치마크를 수행보았다.

```java
@BenchmarkMode(Mode.AverageTime) // 벤치마크 대상 메서드를 실행하는데 걸린 평균 시간
@OutputTimeUnit(TimeUnit.MILLISECONDS) // 벤치마크 결과를 밀리초 단위로 출력
@Fork(value = 2, jvmArgs = {"-Xms4G", "-Xmx4G"}) // 4Gb의 힙공간을 제공한 환경에서 두 번 벤치마크 수행해 결과 신뢰성 확보
public class ParallelStreamBenchMark {

    private static final long N = 10_000_000L;

    @Benchmark // 벤치마크 대상 메서드
    public long sequentialSum() {
        return Stream.iterate(1L, i -> i + 1)
                .limit(N)
                .reduce(0L, Long::sum);
    }

    @Benchmark // 벤치마크 대상 메서드
    public long iterativeSum() {
        long result = 0;
        for (long i = 1L; i <= N; i++) {
            result += i;
        }
        return result;
    }
    @Benchmark
    public long parallelSum() {
        return Stream.iterate(1L, i -> i + 1)
                .limit(N)
                .parallel()  // 순차 스트림을 병렬 스트림으로 변환
                .reduce(0L, Long::sum);
    }

}
```

```
Benchmark                              Mode  Cnt   Score   Error  Units
ParallelStreamBenchMark.sequentialSum  avgt   10  56.014 ± 0.232  ms/op
ParallelStreamBenchMark.iterativeSum  avgt   10  3.351 ± 0.018  ms/op
ParallelStreamBenchMark.parallelSum    avgt   10  58.053 ± 0.899  ms/op
```

전통적인 for루프를 사용하면 저수준으로 동작할 뿐만아니라 기본값을 박싱하거나 언박싱할 필요도 없으므로 더 빠른 것을 볼 수 있다.

여기서 병렬 버전은 순차 버전에 비해 느린 결과가 나온 것을 확인 할 수 있다. 
위 코드에서는  

1. **반복 결과로 박싱된 객체가 만들어지므로 숫자를 더하기 위해 언박싱을 해야한다.** 
2. **반복 잡업은 병렬로 수행할 수 있는 독립 단위로 나누기가 어렵다.**
   - iterate연산은 본질적으로 순차적이므로 청크로 분할하기 어렵다.
   - 리듀싱 과정을 시작하는 시점에 전체 숫자 리스트가 준비되지 않아 스트림을 병렬로 처리할 수 있도록 청크를 분할할 수 없으므로, 스레드를 할당하는 오버헤드만 발생했다.

멀티코어 프로세서를 활용해서 효과적으로 연산을 병렬로 실행하기 위해서 `LongStream.rangeClosed`메서드로 구현해봤다.

```java
    @Benchmark
    public long rangedSum() {
        return LongStream.rangeClosed(1, N)
                .reduce(0L, Long::sum);
    }

    @Benchmark
    public long parallelRangedSum() {
        return LongStream.rangeClosed(1, N)
                .parallel()
                .reduce(0L, Long::sum);
    }
```

- `LongStream.rangeClosed`는 기본형 long을 직접 사용하여 박싱/언박싱 오버헤드가 사라진다.
- `LongStream.rangeClosed`는 쉽게 청크로 분할할 수 있는 숫자 범위를 생산한다.

```
Benchmark                                  Mode  Cnt  Score   Error  Units
ParallelStreamBenchMark.parallelRangedSum  avgt   10  0.486 ± 0.001  ms/op
ParallelStreamBenchMark.rangedSum          avgt   10  3.339 ± 0.006  ms/op
```

오버헤드를 줄여주고, 청크로 쉽게 분할이 되니 기존보다 훨씬 빨라진 것을 보여준다. 올바른 자료구조를 선택해야 병렬 실행도 최적의 성능을 발휘할 수 있다.

### 병렬 스트림 효과적으로 사용하기

- 확신이 서지 않으면 적절한 벤치마크로 성능을 직접 측정하는 것이 좋다.
- 박싱/언박싱은 성능을 크게 저하시킬 수 있는 요소다.
  - `IntStream`, `LongStream`, `DoubleStream` 등 박싱 동작을 피할 수 있는 기본형 특화 스트림을 제공해주고 있다.
- `limit` , `findFirst` 처럼 요소의 순서에 의존하는 연산을 병렬 스트림에서 수행하면 순차 스트림에서보다 성능이 좋지않다.
- 스트림의 특성과 파이프라인의 중간 연산이 스트림의 특성을 어떻게 바꾸는지에 따라 분해 과정의 성능이 달라질 수 있다.
- 요소의 수와 요소당 처리 시간 : 병렬 처리는 스레드풀 생성, 스레드 생성이라는 추가비용이 발생하기 때문에 Collection에 요소수가 적고 요소당 처리 시간이 짧으면 순차 처리가 오히려 병렬 처리보다 빠를 수 있다.
- 스트림 소스의 종류 : 배열(`ArrayList`)은 인덱스로 요소를 관리하기 때문에 Fork 단계에서 요소를 쉽게 분리할 수 있어 병렬 처리 시간이 절약된다. 반면에 LinkedList는 요소 분리가 쉽지 않아 상대적으로 병렬 처리가 늦다. ( `HashSet`, `TreeSet` 은 나쁘지 않음)
  - 커스텀 `Spliterator`를 구현해 분해 과정을 제어할 수 있다.
- 코어(Core) 수 : 싱글 코어 CPU일 경우에는 순차 처리가 더 빠르다. 병렬 스트림을 사용할 경우 스레드 수만 증가하고 동시성 작업으로 처리되기 때문에 좋지 못한 결과를 준다. 코어의 수가 많을수록 병렬 작업 처리속도는 빨라진다.