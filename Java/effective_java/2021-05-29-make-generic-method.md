# ITEM30: 이왕이면 제네릭 메서드로 만들어라

- [기본 Generic 문법 알아보기](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/java-generic.md)
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

------

[제네릭 타입](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-22-make-generic-type.md)과 마찬가지로, 클라이언트에서 입력 매개변수와 반환값을 명시적으로 형변환해야하는 메서드보다, 제네릭 메서드가 더 안전하며 사용하기도 쉽다. 
형변환 없이 사용하기 위해서는 대부분 제네릭 메서드를 사용한다.

```java
public static Set union(Set s1, Set s2) {
  Set result = new HashSet(s1); // raw type
  result.addAll(s2);
  return result;
}
```

위 코드는 컴파일은 되지만 아래 두가지 경고가 발생한다.

```
Unchecked call to 'HashSet(Collection<? extends E>)' as a member of raw type 'java.util.HashSet' 
Unchecked call to 'addAll(Collection<? extends E>)' as a member of raw type 'java.util.Set'
```

경고를 없애기 위해서는 타입안정성을 지켜주면 된다.

```java
public static <E> Set<E> union(Set<E> s1, Set<E> s2) {
  Set<E> result = new HashSet<>(s1); // raw type
  result.addAll(s2);
  return result;
}
```

다음과 같이 제네릭 메서드로 바꿔주면 경고 문구가 뜨지 않으며, 타입 안전성도 지켜지는 것을 확인할 수 있다.



## 제네릭 싱글턴 팩터리

때때로 불변 객체를 여러 타입으로 활용할 수 있게 만들어야 하는 경우가 있다. **요청한 타입 매개변수에 맞게 매번 그 객체의 타입을 바꿔주는 정적 팩터리**(제네릭 싱글턴 팩터리)를 이용해 구현할 수 있다.

- `Collections.emptySet` 컬렉션용

  ```java
  // Collections.emptySet()
  @SuppressWarnings("unchecked")
  public static final <T> Set<T> emptySet() {
    return (Set<T>) EMPTY_SET;
  }
  ```

- `Collections.reverseOrder()` : 함수 객체

  ```java
  // Collections.reverseOrder()
  @SuppressWarnings("unchecked")
  public static <T> Comparator<T> reverseOrder() {
    return (Comparator<T>) ReverseComparator.REVERSE_ORDER;
  }
  
  private static class ReverseComparator implements Comparator<Comparable<Object>>, Serializable {
  
    private static final long serialVersionUID = 7207038068494060240L;
  
    static final ReverseComparator REVERSE_ORDER = new ReverseComparator();
  
    public int compare(Comparable<Object> c1, Comparable<Object> c2) {
      return c2.compareTo(c1);
    }
  
    private Object readResolve() { return Collections.reverseOrder(); }
  
    @Override
    public Comparator<Comparable<Object>> reversed() {
      return Comparator.naturalOrder();
    }
  }
  ```
  
  `reverseOrder()`는 `ReverseComparator`의 싱글턴 객체 `REVERSE_ORDER`를 `Comparator<T>` 타입으로 형변환을 해주는 역할을 한다.

### 함수 객체

제네릭 싱글턴 팩터리 패턴으로 항등함수를 담은 클래스를 직접 구현해볼 것이다.(`Functon.identity`)

```java
public class GenericMethodTest {

    private static UnaryOperator<Object> IDNTITY_FN = (t) -> t;

    @SuppressWarnings("unchecked")
    private static <T> UnaryOperator<T> identityFunction() {
        return (UnaryOperator<T>) IDNTITY_FN;
    }

    @Test
    void genericSingletonEx() {
        String[] strings = {"faker", "keria", "teddy"};
        UnaryOperator<String> sameString = identityFunction();
        for (String s : strings) {
            System.out.println(sameString.apply(s));
        }

        Number[] numbers = {1, 2.0, 3L};
        UnaryOperator<Number> sameNumber = identityFunction();
        for (Number n : numbers) {
            System.out.println(sameNumber.apply(n));
        }
    }
}
```

제네릭 싱글턴 팩터리 패턴으로 `IDNTITY_FN`를 `UnaryOperator<T>`로 형변환해주는 함수이다. 이때, `UnaryOperator<Object>`는 `UnaryOperator<T>`가 아니기 때문에 비검사 형변환 경고가 발생하지만, 항등함수는 입력 값을 수정없이 그대로 반환하는 특별한 함수이므로, `T`에 어떤 타입이 오든 타입이 안전하기 때문에 `@SupperessWarnings`로 해당 경고를 없애주었다.

### 재귀적 타입 한정

이 외에도 **자기 자신이 들어간 표현식을 사용하여, 타입 매개변수의 허용 범위를 한정하는 재귀적 타입 한정(recursive type bound)** 개념이 있다.
재귀적 타입 한정은 주로 타입의 자연적 순서를 정하는 `Comparable` 과 함께 사용한다.

```java
public interface Comparable<T> {
    public int compareTo(T o);
}
```

매개변수 `T`는 `Comparable<T>`를 구현한 타입이 비교할 수 있는 원소의 타입을 정의하며, 실제로 거의 모든 타입은 자신과 같은 타입의 원소와만 비교할 수 있다.
`Comparable`을 구현한 원소의 컬렉션을 입력받는 메서드들은 주로 그 원소들을 정렬, 검색, 비교하는 용도로 사용되며, 해당 용도로 사용하려면 컬렉션에 담긴 모든 원소가 상호 비교될 수 있어야한다.

```java
public static <E extends Comparable<E>> E max(Collection<E> c) {
  if (c.isEmpty()) {
    throw new IllegalArgumentException("collection is empty");
  }
  E result = null;
  
  for (E e : c) {
    if (result == null || e.compareTo(result) > 0) {
      result = Objects.requireNonNull(e);
    }
  }

  return result;
}
```

타입한정인 `<E extends Comparable<E>>`는 "모든 타입 E는 자신과 비교할 수 있다"라는 의미로 해석할 수 있으며, 상호 비교가 가능하다는 것을 의미한다.