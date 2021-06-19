# ITEM 44: 표준 함수형 인터페이스를 사용해라

자바가 람다를 지원하면서 [템플릿 메서드 패턴](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/2020-03-20-template_method_pattern.md)의 매력은 크게 줄었다. 
요즘은 **함수 객체를 받는 정적 팩터리나 생성자를 제공하는 방법**으로 템플릿 메서드 패턴을 대체하여 구현하고 있다. 즉, 함수 객체를 매개변수로 받는 생성자와 메서드를 더 많이 만들어야한다.( 이때,  함수형 매개변수 타입을 올바르게 선택해야한다.)

```java
protected boolean removeEldestEntry(Map.Entry<K,V> eldest) {
  return false;
}
```

`Map`의 새로운 키를 추가하는 `put` 메서드에서 `removeEldestEntry` 메서드를 호출해 `true`가 반환되면 맵에서 가장 오래된 원소를 제거한다.
 `LinkedHashMap` 에서 `removeEldestEntry`를 다음과 같이 재정의해서 캐시로 사용할 수 있다. 

```java
@Override
protected boolean removeEldestEntry(Map.Entry<K,V> eldest) {
  return size() > 100; // 최근 원소 100개 유지
}
```

위 메서드를 람다를 이용해 다시 구현한다면, 함수 객체를 받는 정적 팩터리나 생성자를 제공했을 것이다.
재정의한 `removeEldestEntry`는 `size()` 메서드를 호출하는데, 이는 `size()`가 인스턴스 메서드이기 떄문에 가능한 것이다.

```java
public final int size(){ return size; }
```

람다로 다시 구현할때, 정적 팩터리나 생성자를 호출할 때는 `Map`의 인스턴스가 존재하지 않기 때문에, 다음과 같이 `Map` 자신도 함수 객체에 넘겨줘야한다. 이를 반영한 함수형 인터페이스는 다음과 같다.

```java
@FunctionInterface interface EldestEntryRemovalFunction<K, V> {
    boolean remove(Map<K,V> map, Map.Entry<K, V> eldest);
}
```

## 표준 함수형 인터페이스

위 `EldestEntryRemovalFunction`도 잘 동작하지만, 자바 표준 라이브러리에서 이미 제공해주므로 굳이 사용할 필요가 없다.

- `BiPredicate`로 대체 가능

  ```java
  // EldestEntryRemovalFunction 대체
  BiPredicate<Map<K,V>, Map.Entry<K,V> eldest>
  ```

**필요한 용도에 맞는게 있다면, 직접 구현하는 것보다 표준 함수형 인터페이스를 활용**하는 것이 좋다. 관리할 대상이 줄어들며, 유용한 디폴트 메서드를 많이 제공해줘 다른 코드와 상호 운용성도 좋아질 것이다.

`java.util.function` 패키지에 총 43개 인터페이스가 있지만 기본 인터페이스 6개만 안다면, 나머지 인터페이스는 유추해서 사용할 수 있을 것이다.

| 인터페이스          | 함수 시그니처         | 설명                                          | 예                    |
| ------------------- | --------------------- | --------------------------------------------- | --------------------- |
| `UnaryOperator<T>`  | `T apply(T t)`        | 반환값과 인수의 타입이 같은 함수, 인수 1개    | `String::toLowerCase` |
| `BinaryOperator<T>` | `T apply(T t1, T t2)` | 반환값과 인수의 타입이 같은 함수, 인수 2개    | `BigInteger::add`     |
| `Predicate<T>`      | `boolean test(T t)`   | 한 개의 인수를 받아서 boolean을 반환하는 함수 | `Collection::isEmpty` |
| `Function<T,R>`     | `R apply(T t)`        | 인수와 반환 타입이 다른 함수                  | `Arrays::asList`      |
| `Supplier<T>`       | `T get()`             | 인수를 받지 않고 값을 반환, 제공하는 함수     | `Instant::now`        |
| `Consumer<T>`       | `void accept(T t)`    | 한 개의 인수를 받고 반환값이 없는 함수        | `System.out::println` |

기본 인터페이스는 기본 타입인 `int`, `long`, `double`용으로 각 3개씩 변형이 있다.

- `Predicate`
    - `IntPredicate`
    - `LongPredicate`
    - `DoublePredicate`

이 변형들 중 유일하게 `Function`의 변형만 반환 타입이 매개변수화 되었다.

- `LongFunction<int[]>` : `long` 인수를 받아 `int[]` 반환

`Function` 인터페이스는 기본 타입을 반환하는 변형이 총 9개가 더 있으며, 입력과 결과의 타입이 항상 다르다.

- 입력과 결과 타입이 모두 기본 타입인 경우 `SrcToResult`
    - ex) `long`을 받아 `int`를 반환하면 `LongToIntFunction`
- 입력이 객체 참조이고 결과가 `int`, `long`, `double`인 변형 `ToResult`
    - ex) `ToLongFunction<int[]>` : `int[]` 인수를 받아 `long`으로 반환

기본 함수형 인터페이스 중 인수를 2개씩 받는 변형이 있다.

- `BiPredicate<T,U>`
- `BiFunction<T,U,R>`
    - `ToIntBiFunction<T,U,R>`
    - `ToLongBiFunction<T,U,R>`
    - `ToDoubleBiFunction<T,U,R>`
- `BiConsumer<T,U>`

표준 함수형 인터페이스 사용시 주의할 점이 있다**. 표준 함수형 인터페이스는 대부분 기본 타입만 지원**한다. 그렇다고 박싱된 기본 타입을 넣어 사용하게 되면 동작은하지만 계산량이 많을 때 성능이 매우 느려질 수 있으므로, 사용해서는 안된다.

### 직접 구현

표준 함수형 인터페이스 중 필요한 용도에 맞는게 없다면 직접 구현해야한다.

- `Comparator` 인터페이스

  ```java
  @FunctionalInterface
  public interface Comparator<T> {
      int compare(T o1, T o2);
  }
  ```
  
- `BiFunction<T,U>`

    ```java
    @FunctionalInterface
    public interface ToIntBiFunction<T, U> {
        int applyAsInt(T t, U u);
    }
    ```

`Comparator` 인터페이스는 구조적으로 `ToIntBiFunction`와 동일하다. 인자 두개(Bi)를 받아서 정수형으로 반환(ToInt)하는 인수와 반환 타입이 다른 함수(Function)이다.

여기서 `Comparator`를 `ToIntBiFunction`로 사용하지 않고, 독자적 인터페이스로 남아야하는 이유 3가지가 있다.

1. 자주 쓰이며, 이름 자체가 용도를 명확히 설명
2. 반드시 지켜야할 규약이 있음.
3. 유용한 디폴트 메서드를 제공할 수 있음.

3가지 이유 중 하나 이상을 만족한다면 전용 함수형 인터페이스를 구현할지 고민해보는 것이 좋다.

### @FunctionInterface

`@FunctionInterface` 어노테이션은 프로그래머의 의도를 명시하는 것으로 3가지 목적이 있다.

1. 해당 인터페이스가 람다용으로 설계된 것임을 명시
2. 해당 인터페이스가 추상 메서드를 오직 한개만 가지고 있어야 컴파일 가능
3. 유지보수 과정에서 누군가 실수로 메서드를 추가하지 못하게 막아줌

즉, 직접 만든 함수형 인터페이스에는 항상 `@FunctionInterface` 어노테이션을 붙여줘야한다.

### 주의점

서로 다른 함수형 인터페이스를 같은 위치의 인수로 받는 메서드들을 다중정의해서는 안된다. 클라이언트에게 불필요한 모호함만 주며, 다음과 같이 모호함으로 인해 문제가 발생할 수 있다.

```java
public interface ExecutorService extends Executor {
    <T> Future<T> submit(Callback<T> task);
    Future<?> submit(Runnable task);
}
```

`ExecutorService` 인터페이스는 `Callable<T>`와 `Runnable`을 각각 인수로 하여 다중정의했다. 올바른 메서드를 알려주기 위해서는 `submit` 메서드를 사용할 때마다 형변환을 해줘야한다.
