# ITEM 49: 매개변수가 유효한지 검사해라

메서드와 생성자 대부분이 입력 매개변수의 값이 특정 조건을 만족하기를 바란다.
이러한 제약은 메서드 로직이 실행되기 전, 즉, 메서드 도입 부분에서 매개변수를 확인해 잘못된 값이 넘어온 경우 바로 깔끔하게 예외처리를 할 수 있다.

**"오류는 가능한 한 빨리 발견하는 것이 좋다."**

매개변수 검사를 제대로 하지 않았을 경우 다음 문제들이 발생할 수 있다.

1. 메서드가 수행되는 중간에 모호한 예외를 던지며 실패하는 경우
2. 메서드가 잘 수행됐지만 잘못된 결과를 반환하는 경우
3. 메서드는 문제없이 수행됐지만, 어떤 객체를 이상한 상태로 만들어놓아, 미래의 알 수 없는 시점에 메서드와 관련 없는 오류를 발생하는 경우

## public / protectd method

`public` 과 `protected` 메서드는 매개변수 값이 잘못됐을 때 던지는 예외를 문서화 해야한다.
(`@throws` 자바독 태그 이용)

```java
    /**
     * (현재 값 mod m) 값을 반환
     * 항상 음이 아닌 BigInteger를 반환한다는 점에서 remainder와 다름
     *
     * @param m 계수(양수)
     * @return 현재 값 mod m
     * @throws ArithmeticException m이 0 이하이면 발생
     */
    public BigInteger mod(BigInteger m) {
        if (m.signum() <= 0) {
            throw new ArithmeticException("계수(m)는 양수여야 합니다. " + m);
        }
        return m;
    }
```

이렇게 발생하는 예외도 같이 문서화 해두면, 간단한 방법으로 API 사용자가 제약을 지킬 가능성이 높아진다.
위 예제에서 `NullPointException` 에 대한 문서화를 하지 않은 이유는 `BigInteger` 클래스 수준에서 기술되어 있기 때문이다. 클래스 수준 주석은 해당 클래스의 모든 public 메서드에 적용되므로, 각 메서드에 일일이 기술하지 않아도 된다.

### Objects.requireNonNull

- java7에 추가
- `java.util.Objects.requireNonNull`

```java
    /**
     * Checks that the specified object reference is not {@code null}. This
     * method is designed primarily for doing parameter validation in methods
     * and constructors, as demonstrated below:
     * <blockquote><pre>
     * public Foo(Bar bar) {
     *     this.bar = Objects.requireNonNull(bar);
     * }
     * </pre></blockquote>
     *
     * @param obj the object reference to check for nullity
     * @param <T> the type of the reference
     * @return {@code obj} if not {@code null}
     * @throws NullPointerException if {@code obj} is {@code null}
     */
    public static <T> T requireNonNull(T obj) {
        if (obj == null)
            throw new NullPointerException();
        return obj;
    }

    /**
     * Checks that the specified object reference is not {@code null} and
     * throws a customized {@link NullPointerException} if it is. This method
     * is designed primarily for doing parameter validation in methods and
     * constructors with multiple parameters, as demonstrated below:
     * <blockquote><pre>
     * public Foo(Bar bar, Baz baz) {
     *     this.bar = Objects.requireNonNull(bar, "bar must not be null");
     *     this.baz = Objects.requireNonNull(baz, "baz must not be null");
     * }
     * </pre></blockquote>
     *
     * @param obj     the object reference to check for nullity
     * @param message detail message to be used in the event that a {@code
     *                NullPointerException} is thrown
     * @param <T> the type of the reference
     * @return {@code obj} if not {@code null}
     * @throws NullPointerException if {@code obj} is {@code null}
     */
    public static <T> T requireNonNull(T obj, String message) {
        if (obj == null)
            throw new NullPointerException(message);
        return obj;
    }
```

- `null` 검사를 수동으로 하지 않아도 된다.
- 원하는 예외 메세지도 지정할 수 있다.
- 입력 값을 그대로 반환해, 값을 사용하는 동시에 검사도 가능

```java
this.strategy = Objects.requireNonNull(strategy, "전략 값이 없습니다.");
```

### Java9 Objects 범위검사

Java9에서는 범위 검사 기능도 추가됐다.

- `checkFromIndexSize`
- `checkFromToIndex`
- `checkIndex`

위 메서드들은 `null` 검사 메서드만큼 유연하지는 않다.

- 예외 메세지 지정불가능
- 리스트와 배열 전용으로 설계
- 닫힌 범위는 다루지 못함

## private method

`private` 메서드의 경우 `assert` (단언문)을 사용해 매개변수 유효성을 검증할 수 있다.

```java
    private static void sort(long a[], int offset, int length) {
        assert a != null;
        assert offset >= 0 && offset <= a.length;
        assert length >= 0 && length <= a.length - offset;
    }
```

- 실패시 `AssertionError` 예외를 던진다.

    ```java
    java.lang.AssertionError
        at ch8.dahye.item49.MethodTest.sort(MethodTest.java:39)
      ...
    ```

- 런타임에 아무런 효과와 성능 저하도 없다.

- `-ea` or `--enableassertions` 플래그를 설정하면, 런타임시 영향을 준다.

