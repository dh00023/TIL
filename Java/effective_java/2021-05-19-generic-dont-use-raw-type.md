# ITEM 26 : 로 타입은 사용하지 마라

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

제네릭은 클래스와 인터페이스, 메소드를 정의할 때 타입을 파라미터로 사용할 수 있도록한다. Generic 타입을 이용함으로써 잘못된 타입이 사용될 수 있는 문제를 컴파일 과정에서 제거할 수 있게되었다.

Generic type은 **타입을 파라미터로 가지는 클래스(`class<T>`)와 인터페이스(`interface<T>`)**를 말한다.

이때, Raw type은 타입 파라미터가 없는 제네릭 타입을 의미한다. 

- raw type Box class

  ```java
  public class Box<T> {
      public void set(T t) { /* ... */ }
  }
  ```

  ```java
  // Box는 Generic type이지만 타입 파라미터 없이 생성
  Box rawBox = new Box();
  ```

- Collection Raw type

  ```java
  private final Collection stamps = new ArrayList<>();
  ```

Raw type은 타입 선언에서 제네릭 타입 정보가 전부 지워진 것처럼 동작하는데, 이건 Generic에 도래하기 전 코드와 호환하도록 하기 위해서이다.

>The superclasses (respectively, superinterfaces) of a raw type are the erasures of the superclasses (superinterfaces) of any of the parameterizations of the generic type.
>The type of a constructor, instance method, or non-static field of a raw type C that is not inherited from its superclasses or superinterfaces is the raw type that corresponds to the erasure of its type in the generic declaration corresponding to C.
>
>Raw Type의 슈퍼 클래스는 Raw Type이다.
>상속 받지 않은 Raw Type의 생성자, 인스턴스 메서드, 인스턴스 필드는 Raw Type이다.

- Raw type : runtime 오류

  ```java
  public class RawTypeTest {

      static class Coin {
          public void cancle(){
              System.out.println("Coin.cancle");
          }
      }

      static class Stamp {

          public void cancle(){
              System.out.println("Stamp.cancle");
          }
      }

      public static void main(String[] args) {
          // stamps는 Stamp 인스턴스만 취급
          Collection stamps = new ArrayList();

          // Stamp만 받고 싶지만, Coin이 들어가도 아무 오류 없이 컴파일되고 실행됨.
          stamps.add(new Stamp());
          stamps.add(new Coin());

          // 조회시 ClassCastException 발생
          for (Iterator i = stamps.iterator(); i.hasNext();) {
              Stamp stamp = (Stamp) i.next();
              stamp.cancle();
          }
      }
  }
  ```

  ```
  Exception in thread "main" java.lang.ClassCastException: ...
  ```
또 다른 예를 하나 더 살펴보자.

- Raw type List : runtime 오류

  ```java
  public class ListRawTypeTest {
  
      public static void main(String[] args) {
          List<String> strings = new ArrayList<>();
  
          unsafeAdd(strings, Integer.valueOf(100));
          String s = strings.get(0); // ClassCastException 오류 발생
      }
  
      private static void unsafeAdd(List list, Object o) {
          list.add(o);
      }
  }
  ```
  
  ```
  Exception in thread "main" java.lang.ClassCastException: class java.lang.Integer cannot be cast to class java.lang.String (java.lang.Integer and java.lang.String are in module java.base of loader 'bootstrap')
  	at ch5.dahye.item26.ListRawTypeTest.main(ListRawTypeTest.java:12)
  ```

오류는 가장 빨리 발견하는 것이 좋으며, 즉 가능한 발생 즉시(컴파일) 발견하는 것이 좋다. 위의 예제에서는 오류가 발생하고 한참뒤인 런타임에서야 오류를 발견할 수 있다. 런타임시 `ClassCastException` 오류가 발생하게 되면, 해당 오류가 발생한 부분을 찾기 위해 전체 코드를 훑어봐야할 수도 있다.

- Generic parameter type : compile 오류

  ```java
  public class RawTypeTest {
  
      static class Coin {
          public void cancle(){
              System.out.println("Coin.cancle");
          }
      }
  
      static class Stamp {
  
          public void cancle(){
              System.out.println("Stamp.cancle");
          }
      }
  
      public static void main(String[] args) {
          // stamps는 Stamp 인스턴스만 취급
          Collection<Stamp> stamps = new ArrayList();
  
          // 컴파일시 오류발생
          stamps.add(new Stamp());
          stamps.add(new Coin());
  
          // 조회시 ClassCastException 발생
          for (Iterator i = stamps.iterator(); i.hasNext();) {
              Stamp stamp = (Stamp) i.next();
              stamp.cancle();
          }
      }
  }
  ```

  ```
  java: incompatible types: ch5.dahye.item26.RawTypeTest.Coin cannot be converted to ch5.dahye.item26.RawTypeTest.Stamp
  ```
  
  ```java
  public class ListRawTypeTest {
  
      public static void main(String[] args) {
          List<String> strings = new ArrayList<>();
  
          unsafeAdd(strings, Integer.valueOf(100));
          String s = strings.get(0);
      }
  
      private static void unsafeAdd(List<Object> list, Object o) {
          list.add(o);
      }
  }
  ```
  
  ```
  /Users/dh0023/Develop/study-cow/java/src/ch5/dahye/item26/ListRawTypeTest.java:11:19
  java: incompatible types: java.util.List<java.lang.String> cannot be converted to java.util.List<java.lang.Object>
  ```

매개변수화된 컬렉션 타입을 사용하면서, 컴파일 오류가 발생하였고, 바로 어디서 잘못된 타입이 들어간 것인지 파악할 수 있다.


**Raw type을 사용하는 것을 막아두진 않았지만 절대로 사용해서는 안된다.  Raw type은 제네릭이 주는 장점(안정성과 표현력)을 모두 잃게된다.**

Raw type은 Java가 제네릭을 도입하기전(JDK 5.0) 이전 기존 코드와의 호환성을 보장하기 위해서 제공하고 있는 것이다. 제네릭과 자바의 강점을 사용하기 위해서는 Raw type을 사용해서는 안된다.

### 비한정적 와일드카드 타입(Unbounded wildcard type) 

만약 제네릭 타입을 사용하고 싶지만, 실제 타입 매개변수가 무엇인지 신경 쓰고 싶지 않다면 `<?>` (비한정적 와일드카드 타입)을 사용하면 된다.

- `제네릭타입<?>` : 제한없음(타입 파라미터를 대치하는 구체적 타입으로 모든 클래스나 인터페이스 타입이 올 수 있다.)

```java
    static int numElemnetsInCommon(Set s1, Set s2) {
        int result = 0;
        for (Object o1 : s1) {
            if (s2.contains(o1)) {
                result++;
            }
        }
        return result;
    }
```

위 set은 Raw type을 사용해 모르는 타입의 원소도 받고 있지만, 안전하지 않다. 

```java
    static int numElemnetsInCommon(Set<?> s1, Set<?> s2) { ... }
```

다음과 같이 비한정적 와일드카드 타입을 사용해 Raw type의 불안전성을 막을 수 있다. Raw type의 불안정성의 예를 하나 살펴보자.

```java
Collection collection = new ArrayList<>();
collection.add("test");
collection.add(123);
```

Raw type 컬렉션에는 아무 원소나 넣을 수 있어 타입 불변식을 훼손하기 쉽다. 비한정적 와일드카드 타입을 사용하면 `Collection<?>` 에는 null을 제외한 어떠한 원소도 넣을 수 없다. 

```java
Collection<?> collection = new ArrayList<>();
collection.add(null); // 가능
collection.add("test"); // 컴파일 오류 
```

```
java: incompatible types: java.lang.String cannot be converted to capture#1 of ?
```

null을 제외한 어떠한 원소도 컬렉션에 추가할 수 없게 하였으며, 컬렉션에서 꺼낼 수 있는 타입 또한 전혀 알 수 없게 하여 컬렉션의 타입 불변식을 훼손하지 못하게 막을 수 있다.

마지막으로 비한정적 와일드카드 타입이 사용될 수 있는 시나리오는 다음과 같다.

1. Object 클래스에서 제공되는 기능을 사용하여 구현할 수 있는 메서드를 작성하는 경우

2. **타입 파라미터에 의존적이지 않은 일반 클래스의 메소드를 사용하는 경우**( ex) `List.clear`, `List.size`, `Class<?>`)

### 예외케이스

#### class 리터럴에는 Raw type을 사용해야한다.

자바 명세는 class 리터럴에 매개변수화 타입을 사용하지 못하게 했다.(배열과 기본 타입은 허용)

`List.class` , `String[].class`, `int.class` 는 허용하지만, `List<String>.class`, `List<?>.class` 는 허용하지 않는다.

#### instanceof 연산

런타임에는 제네릭 타입 정보가 지워지므로 `instanceof` 연산자는 비한정적 와일드카드 타입(Unbounded wildcard type) 이외의 매개변수화 타입에는 적용할 수 있다. 또한, Raw type과 비한정적 와일드카드 타입이 완전히 동일하게 동작한다. 그러므로 Raw type을 쓰는 편이 더 깔끔하다.

```java
if (o instanceof Set) {
  	Set<?> s = (Set<?>) o;
}
```



## 참고

- [http://happinessoncode.com/2018/02/08/java-generic-raw-type/](http://happinessoncode.com/2018/02/08/java-generic-raw-type/)
- [https://medium.com/@joongwon/java-java%EC%9D%98-generics-604b562530b3](https://medium.com/@joongwon/java-java%EC%9D%98-generics-604b562530b3)







