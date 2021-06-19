# ITEM 43: 람다보다는 메서드 참조를 사용해라

람다의 가장 큰 장점은 간결함이다. **함수객체를 람다 보다 더 간결하게 구현할 수 있는 메서드 참조**(method reference)에 대해 이번장에서 다뤄볼 것이다.


```java
    default V merge(K key, V value,
            BiFunction<? super V, ? super V, ? extends V> remappingFunction) {
        Objects.requireNonNull(remappingFunction);
        Objects.requireNonNull(value);
        V oldValue = get(key);
        V newValue = (oldValue == null) ? value :
                   remappingFunction.apply(oldValue, value);
        if (newValue == null) {
            remove(key);
        } else {
            put(key, newValue);
        }
        return newValue;
    }
```

Java 8때 `Map`에 추가된 `merge` 메서드는 키, 값, 함수를 인수로 받는다. 주어진 키가 맵에 없다면 주어진 키, 값을 그대로 저장하고, 반대로 키가 이미 있다면 {키, 함수의 결과} 쌍을 저장한다.

```java
// 키가 맵 안에 없으면 키와 숫자 1을 매핑하고, 이미 있다면 기존 매핑 값을 증가
map.merge(key, 1, (count, incr) -> count + incr);
```

 `merge` 메서드의 전형적인 쓰임을 잘 보여준다. 위 람다는 두 인수의 합을 단순히 반환할 뿐이지만, 매개변수인 `count` 와 `incr`은 크게 하는 일 없이 공간을 차지하는 것을 볼 수 있다.

Java8부터 `Integer` 클래스(모든 기본타입의 박싱 타입)는 위 람다와 기능이 같은 정적 메서드 `sum` 을 제공하기 시작했다.

```java
public final class Integer extends Number implements Comparable<Integer> {
  ...
  public static int sum(int a, int b) {
        return a + b;
  }
  ...
}
```

람다대신 메서드 참조를 전달하면 똑같은 결과도 더 간결하게 구현할 수 있다.

```java
map.merge(key, 1, Integer::sum);
```

하지만 매개변수의 이름 자체가 프로그래머에게 좋은 가이드가 되는 경우에는 람다를 사용하는 것이  유지보수에 더 좋을 수 있다.
그렇더라도 메서드 참조를 사용하는 편이 보통은 더 짧고 간결해, 람다로 작성할 코드를 새로운 메서드에 담은 다음, 람다 대신 그 메서드 참조를 사용하는 방식을 사용할 수 있다. 이때, 메서드 참조에 기능을 잘 드러내는 이름을 지어줄 수 있고, 주석으로 설명을 남길 수 있다.
메서드와 람다가 같은 클래스에 있을때는 람다가 메서드 참조보다 더 간결할 수 있다.

람다와 메서드가 모두 `GoshThisClassNameIsHumonous` 클래스에 있다면 람다로 구현한 것이 더 간결하고, 명확하다.

- 메서드 참조

  ```java
  service.execute(GoshThisClassNameIsHumonous::action);
  ```

- 람다

  ```java
  service.execute(() -> action());
  ```

### 메서드 참조 유형

| 유형               | 예                     | 람다                                                     |
| ------------------ | ---------------------- | -------------------------------------------------------- |
| 정적               | Integer::parseInt      | str -> Integer.parseInt(str)                             |
| 한정적(인스턴스)   | Instant.now()::isAfter | Instant then = instant.now();<br />t -> then.isAfter(t); |
| 비한정적(인스턴스) | String::toLowerCase    | str -> str.toLowerCase()                                 |
| 클래스 생성자      | TreeMap<K,V>::new      | () -> new TreeMap<K,V>()                                 |
| 배열 생성자        | int[]::new             | len -> new int[len]                                      |

- 수신 객체(참조 대상 인스턴스)를 특정하는 한정적 인스턴스 메서드 참조
    - 함수 객체가 받는 인수와 참조되는 메서드가 받는 인수가 동일
- 수신 객체(참조 대상 인스턴스)를 특정하지 않는 비한정적 인스턴스 메서드 참조
    - 함수 객체를 적용하는 시점에 수신 객체를 알 수 있음
    - 수신 객체 전달용 매개변수가 매개변수 목록의 첫번째로 추가되며, 그 뒤로는 참조되는 메서드 선언에 정의된 매개변수들이 뒤따른다.
    - 주로, 스트림 파이프라인에서 매핑과 필터 함수에 주로 쓰임([Item 45](https://github.com/dh00023/TIL/blob/master/Java/effective_java//2021-06-20-use-streams-judiciously.md))

정리하자면 다음과 같다.
**메서드 참조가 더 짧고 명확하다면 메서드 참조를, 그렇지 않다면 람다를 사용**하자.

