# ITEM32: 제네릭과 가변인수를 함께 쓸 때는 신중해라

- [Generic#heap pollution](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/java-generic.md#heap-pollut)

- 관련 용어

  | 한글                     | 영문                    | 예                                 |
  | ------------------------ | ----------------------- | ---------------------------------- |
  | 매개변수화 타입          | parameterized type      | `List<String>`                     |
  | 실제 타입 매개변수       | actual type parameter   | `String`                           |
  | 제네릭 타입              | generic type            | `List<E>`                          |
  | 정규 타입 매개변수       | formal type parameter   | `E`                                |
  | 비한정적 와일드카드 타입 | unbounded wildcard type | `List<?>`                          |
  | 로 타입                  | raw type                | `List`                             |
  | 한정적 타입 매개변수     | bounded type parameter  | `<E extends Number>`               |
  | 재귀 타입 한정           | recursive type bound    | `<T extends Comparable<T>>`        |
  | 한정적 와일드카드 타입   | bounded wildcard type   | `List<? extends Number>`           |
  | 제네릭 메서드            | generic method          | `static <E> List<E> asList(E[] a)` |
  | 타입 토큰                | type token              | `String.class`                     |

시작전, 위 개념에 대한 이해가 있어야 이해하기 쉬우며, 일부 겹치는 내용도 있다.

------

가변인수는 메서드에 넘기는 인수의 갯수를 클라이언트가 조절할 수 있게 해주는데, 구현 방식에서 헛점이 한 개 있다.
[가변인수 메서드-item53]()를 호출하면 가변인수를 담기 위한 배열이 자동으로 하나 만들어지는데, 이 배열이 외부 클라이언트에 노출되는 경우 문제가 생기는 것이다.

```java
public class VarargsTest {

    @Test
    void varargsErrTest() {
        List<String> strings = new ArrayList<>();
        strings.add("test");
        dangerous(strings);
    }

    static void dangerous(List<String>... stringLists) {
        List<Integer> ints = List.of(42);
        Object[] objs = stringLists;
        objs[0] = ints;                                     // (1) 힙오염
        String s = stringLists[0].get(0); // (2) runtime error - ClassCastException

    }
}
```

**(1)** 부분에서 힙오염이 발생하지만, 결과적으로 **(2)**부분에서 런타임시에 `ClassCastException` 오류가 발생하는 것을 확인할 수 있다. 이 예제 처럼 타입 안정성이 깨지므로, 제네릭 가변인수 매개변수에 값을 저장하는 것은 안전하지 않다.

다음은 varargs 매개변수 배열에 아무것도 저장하지 않아도 타입 안전성이 깨질 수 있는 예이다.

```java
static <T> T[] toArray(T... args) {
    return args;
}
```

이 메서드는 가변인수로 넘어온 매개변수들을 배열에 담아 반환하는 제네릭 메서드이다. 메서드가 반환하는 배열의 타입은 메서드에 인수를 넘기는 컴파일 타임에 결정되는데, 그 시점에는 컴파일러에게 충분한 정보가 주어지지 않아서 타입을 잘못 판단할 수 있다. 즉, 자신의 가변인수 매개변수 배열을 그대로 반환하면 힙 오염을 메서드를 호출한 곳까지 전이하는 결과를 낳을 수도 있다.

```java
public class VarargsTest {

    @Test
    void heapPollutionTest() {
        String[] attrs = pickTwo("좋은", "빠른", "저렴한");
        System.out.println("attrs = " + Arrays.toString(attrs));
    }

    static <T> T[] toArray(T... args) { // warning : Possible heap pollution from parameterized vararg type 
        return args;
    }

    static <T> T[] pickTwo(T a, T b, T c) {
        switch (ThreadLocalRandom.current().nextInt(3)) {
            case 0: return toArray(a, b); // warning : Unchecked generics array creation for varargs parameter  
            case 1: return toArray(a, c); // warning : Unchecked generics array creation for varargs parameter 
            case 2: return toArray(b, c); // warning : Unchecked generics array creation for varargs parameter 
        }
        throw new AssertionError();
    }
}

```

컴파일러는 `pickTwo()`메서드의  `T...`를 `T[]`로 변환하고, 타입 소거(type erasure)에 의해 최종적으로 `Object[]`로 변환시키게 된다. `pickTwo()`의 반환값을 `String[]` 에 저장하려고 하니 형변환이 실패해서 `ClassCastException` 오류가 나는 것이다.

자신의 제네릭 매개변수 배열의 참조를 노출하여, 힙오염이 발생한 것이며 즉, 제네릭 가변인수 매개변수 배열에 다른 메서드가 접근하도록 허용하는 것은 안전하지 않다는 것을 알 수 있다.

단, 아래 두 경우는 예외이다.

1. @SafeVarargs로 선언된 타입 안전성이 보장된 또 다른 varargs 메서드에 넘기는 것은 안전하다.
2. 배열 내용의 일부 함수를 호출만 하는 (varargs를 받지않는) 일반 메서드에 넘기는 것도 안전하다.

실제로 프로그래머가 제네릭 배열을 직접 생성하는 것은 허용하지 않으면서, 가변인수 매개변수를 받는 메서드를 허용한 것은 실무에서 매우 유용하게 사용되기 때문이다. 실제로 자바 라이브러리에서도 이러한 메서드(타입 안전한)를 제공하고 있다.

 ````java
Arrays.asList(T... a);
Collections.addAll(Collection<? super T> c, T... elements);
EnumSet.of(E first, E... rest);
 ````

제네릭 가변인수 메서드의 타입 안전이 보장될 때는 Java 7부터 `@SafeVarargs` 어노테이션으로 경고문구를 숨길 수 있다. 이때, 메서드가 안전한 게 확실하지 않다면 절대로 어노테이션을 달아서는 안된다.

그렇다면 해당 메서드가 안전한 경우는 언제일까? 메서드가 배열에 아무것도 저장하지 않고, 그 배열의 참조가 밖으로 노출되지 않는다면 타입이 안전하다고 판단할 수 있다. 즉, varargs 매개변수 배열이 호출자로부터 순수하게 인수들을 전달하는 일만 한다면 그 메서드는 안전한 것이다.

1. varargs 매개변수 배열에 아무것도 저장하지 않는다.
2. 배열 혹은 복제본을 신뢰할 수 없는 코드에 노출하지 않는다.

만약 이 두가지 규칙을 하나라도 어긴 경우에는 `@SafeVarargs` 어노테이션을 붙여서는 안된다. 또한, `@SafeVarargs` 어노테이션은 재정의할 수 없는 메서드에만 달아야한다. ( Java 8에서 정적 메서드, final 인스턴스 메서드에만 가능, Java 9부터는 private 인스턴스 메서드도 허용 )

```java
@SafeVarargs
static <T> List<T> flatten(List<? extends T>... lists) {
  List<T> result = new ArrayList<>();
  for (List<? extends T> list : lists) {
    result.addAll(list);
  }
  return result;
}
```

위 예제는 varargs 매개변수를 안전하게 사용하는 전형적인 예이다. varargs 배열을 직접 노출 시키지 않고, `T`타입의 와일드 카드타입을 사용하였기 때문에`ClassCastException` 또한 발생할 일이 없다.

`@SafeVarargs` 어노테이션을 붙이는게 유일한 답은 아니며, 제네릭 varargs 매개변수를 List로 대체하는 방법도 있다.

```java
static <T> List<T> flatten(List<List<? extends T>> lists) {
  List<T> result = new ArrayList<>();
  for (List<? extends T> list : lists) {
    result.addAll(list);
  }
  return result;
}
```

```java
audience = flatten(List.of(friends, romans, countrymen));
```

정적 팩터리 메서드인 `List.of`를 활용해 메서드에 임의의 인수를 넘길 수 있다. (`List.of` 에 `@SafeVarargs`가 있기때문에 가능)

```java
public class VarargsTest {

    @Test
    void heapPollutionTest() {
        List<String> attrs = pickTwo("좋은", "빠른", "저렴한");
        System.out.println("attrs = " + Arrays.toString(attrs));
    }

    static <T> List<T> pickTwo(T a, T b, T c) {
        switch (ThreadLocalRandom.current().nextInt(3)) {
            case 0: return List.of(a, b);
            case 1: return List.of(a, c);
            case 2: return List.of(b, c);
        }
        throw new AssertionError();
    }
}
```

이 방법의 장점은 컴파일러가 메서드 타입 안정성을 검증할 수 있는데 있다. 또한, 프로그래머가 `@SafeVarargs` 어노테이션을 달지 않아도 되며, 실수로 안전하다고 판단할 걱정도 없다.
단점은 클라이언트 코드가 살짝 지저분해지고, 속도가 약간 느려질 수 있다는 점이다.