# ITEM 55: Optional 반환은 신중하게 해라

### 자바8 이전 값을 반환할 수 없는 경우

#### 예외

예외는 진짜 예외적인 상황에서만 사용해야하며, 예외를 생성할 때 스택 추적 전체를 캡처하는 비용도 만만치 않다.

```java
public static <E extends Comparable<E>> E max(Collection<E> c){
  if (c.isEmpty())
    throw new IllegalArgumentException("빈 컬렉션");

  E result = null;
  for (E e : c){
    if (result == null || e.compareTo(result) > 0){
      result = Objects.requireNonNull(e);
    }
  }
  return result;
}
```

#### null

`null`을 반환하면, 예외를 던지는 경우와 같은 문제는 발생하지 않지만, `null` 을 반환할 수 있는 메서드 호출시 별도의 `null` 처리 코드를 추가해줘야한다.
그렇지 않으면, 근본적인 원인과 상관 없는 코드에서  `NullPointerException`이 발생할 수 있다.

### 자바8 이후 : Optional

`Optional<T>`는 `null`이 아닌 `T` 타입 참조를 하나 담거나, 아무것도 담지 않을 수 있다.
보통 `T`를 반환해야 하지만 특정 조건에서 아무것도 반환하지 않아야 할 때 `T` 대신 `Optional<T>`를 반환하도록 선언하면 된다.

- 유요한 값이 없는 경우 빈 결과를 반환
- 예외를 던지는 메서드보다 유연하고, 사용하기 쉬움
- `null`을 반환하는 메서드보다 오류 가능성이 적음

```java
public static <E extends Comparable<E>> Optional<E> max(Collection<E> c){
  if (c.isEmpty())
    return Optional.empty(); // 빈 옵셔널

  E result = null;
  for (E e : c){
    if (result == null || e.compareTo(result) > 0){
      result = Objects.requireNonNull(e);
    }
  }
  return Optional.of(result); // 값이든 옵셔널
}
```

- `Optional.empty()` : 빈 옵셔널
- `Optional.of(v)` : 값이 있는 옵셔널(`null` 허용안함)
- `Optional.ofNullable(v)`  : `null` 값 허용하는 값이있는 옵셔널

**`Optional`을 반환하는 메서드에서는 절대 `null`을 반환해서는 안된다.**
`null`을 반환하는 것은 `Optional`을 도입한 취지를 무시하는 것이다.



#### stream 종단 연산

스트림 종단 연산 중 옵셔널을 반환하는 연산이 많다.

```java
public static <E extends Comparable<E>> Optional<E> max(Collection<E> c){
  return c.stream().max(Comparator.naturalOrder());
}
```

스트림 `max` 종단 연산으로 `Optional`을 반환하도록 쉽게 구현할 수 있다.

#### Optional을 사용하는 기준

- 반환 값이 없을 수도 있음을 API 사용자에게 명확하게 알려준다.
- `Optional` 반환시 클라이언트는 값을 받지 못한 경우 취할 행동을 설정해야한다.
- 반환 값을 `Optional`을 사용하는 것이 무조건 좋은건 아니다.
    -  컬렉션, 스트림, 배열, 옵셔널 같은 컨테이너 타입은 `Optional`로 감싸면 안된다.
    -  `Optional<List<T>>`  보다 빈 `List<T>>`가 더 좋다.([ITEM 54]())
    -  빈 컨테이너를 반환하면, 옵셔널 처리 코드를 추가하지 않아도 된다.
- 즉, 결과가 없을 수도 있으며, 클라이언트가 해당 상황을 별도로 처리해야하는 경우 `Optional<T>`를 반환
    - `Optional` 도 초기화, 할당과 값을 꺼내는데 메서드를 호출하는 비용이 든다.
    - 성능이 중요한 상황에서는 `Optional`이 맞지 않을 수 있다.
- 박싱된 기본 타입을 담은 `Optional`을 반환하지 말자
    - `OptionalInt`, `OptionalDouble`, `OptionalLong` : `int`, `double`, `long` 기본 타입 전용 옵셔널 클래스 사용
    - `Boolean`, `Byte`, `Character`, `Short`, `Float` 는 상대적으로 덜 중요한 기본 타입으로 예외
- `Optional`을 컬렉션의 키, 값, 원소, 배열의 원소로 사용하지 말자.
    - `Map` 안에 키가 없는 사실을 나타내는 경우가 2가지(키 자체가 없는 경우, 키는 있지만 빈 옵셔널인 경우)로 나뉘게 된다.
    - 복잡성을 오히려 높여 오류 가능성을 높일 수 있다.

#### Optional 메서드

- `orElse` : 기본 값 설정

    ```java
    String lastWordInLexicon = max(words).orElse("단어 없음");
    ```

- `orElseThrow` : 원하는 예외 설정 - 실제 예외가 아닌 예외 팩터리를 생성해, 실제로 예외가 발생하지 않는 한 예외 생성 비용은 들지 않는다.

    ```java
    Toy myToy = max(toys).orElseThrow(TemperTantrumExcpetion::new);
    ```

- `get` : 항상 값이 채워져 있다고 가정하고, 바로 값을 꺼내서 사용

    ```java
    Element lastNobleGas = max(Elements.NOBLE_GASES).get(); // 만약 잘못 판단한 경우 NoSuchElementException 발생
    ```

- `orElseGet` : 기본값을 설정하는 비용이 부담스러울 때 `Supplier<T>`를 인수로 받는 메서드 사용
    값이 처음 필요할 때 `Supplier<T>`를 사용해 생성하므로 초기 설정 비용을 낮출 수 있다.

- `isPresent` : 옵셔널이 채워져 있으면 true, 빈 값이면 false 반환
    `isPresent`는 다른 메서드들로 대체할 수 있으며, 대체해 사용한 경우 더 짧고 명확하고 용법에 맞는 코드가 되므로 신중히 사용

    - `isPresent` 사용

      ```java
      Optional<ProcessHandle> parentProcess = ph.parent();
      System.out.println("부모 PID: " + (parentProcess.isPresent() ? 
                                       String.valueOf(parentProcess.get().pid()) : "N/A"));
      ```
      
    - `map` 사용

        ```java
        System.out.println("부모 PID: " + ph.parent().map(h -> String.valueOf(h.pid()).orElse("N/A"));
        ```

- 스트림을 사용하는 경우 `Stream<Optional<T>>`로 받아 값이 있는 옵셔널에서 값을 뽑아 `Stream<T>`에 전달

    ```java
    streamOfOptionals.filter(Optional::isPresent).map(Optional::get)
    ```

- `Optional.stream()` : `Optional`을 `Stream`으로 변환

    ```java
    streamOfOptionals.flatMap(Optional::stream)
    ```




