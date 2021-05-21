# ITEM29: Generic 타입으로 만들어라

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

기존에 앞선 7장에서 생성한 `Stack` 클래스를 Generic 타입으로 변경해볼 것이다.

- 기존 Stack

  ```java
  public class Stack {
      private Object[] elements;
      private int size = 0;
      private static final int DEFAULT_CAPACITY = 16;
  
      public Stack() {
          elements = new Object[DEFAULT_CAPACITY];
      }
  
      public void push(Object e) {
          ensureCapacity();
          elements[size++] = 0;
      }
  
      public Object pop() {
          if (size == 0) {
              throw new EmptyStackException();
          }
          return elements[--size];
      }
  
      // 원소를 위한 공간을 적어도 하나 이상 여유를 두며, 늘려야하는 경우 두배 이상 늘린다.
      private void ensureCapacity() {
          if (elements.length == size) {
              elements = Arrays.copyOf(elements, 2 * size + 1);
          }
      }
  }
  ```

- Generic으로 생성 -> 제네릭 배열 생성 오류 발생

  ```java
  public class Stack<E> {
      // private으로 저장
      private E[] elements;
      private int size = 0;
      private static final int DEFAULT_INITIAL_CAPACITY = 15;
  
      public Stack() {
          elements = new Object[DEFAULT_INITIAL_CAPACITY];
      }
  
      public void push(E e) {
          ensureCapacity();
          elements[size++] = e;
      }
  
      public E pop() {
          if (isEmpty()) {
              throw new EmptyStackException();
          }
  
          E result = elements[size--];
          elements[size] = null;
          return result;
      }
  
      public boolean isEmpty() {
          return size == 0;
      }
  
      private void ensureCapacity() {
          if (elements.length == size) {
              elements = Arrays.copyOf(elements, 2 * size + 1);
          }
      }
  }
  
  ```

  ```java
  elements = new Object[DEFAULT_INITIAL_CAPACITY];
  ```

  ```java
  warning: [unchecked] unchecked cast
  ```

  위 배열 생성 부분에서 다음과 같이 타입이 안전하지 않다는 오류가 발생하며, `(E[]) new Object[DEFAULT_INITIAL_CAPACITY];`로 해결 할 수 있다.



### 방법1. 제네릭 배열 생성 금지 제약 우회

```java
public class Stack<E> {
    // private으로 저장
    private E[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 15;

    public Stack() {
        elements = (E[]) new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(E e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public E pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }

        E result = elements[size--];
        elements[size] = null;
        return result;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    private void ensureCapacity() {
        if (elements.length == size) {
            elements = Arrays.copyOf(elements, 2 * size + 1);
        }
    }
}

```

```
Unchecked cast: 'java.lang.Object[]' to 'E[]' 
```

비검사 형변환 경고문구가 뜨는데, 이 클래스가 타입 안전성을 해치지 않는 것을 확인해봐야한다. `elements` 배열은 private 필드에 저장되며, `push()` 메서드로 추가되는 원소의 타입은 항상 `E` 이다. 그러므로, 확실히 안전한 것은 우리는 파악할 수 있다.

```java
		// elements 배열은 push(E)로 넘어온 E인스턴스만 담는다.
    // 타입 안정성을 보장하지만, 런타임 타입은 E[]가 아닌 Object[]이다.
    @SuppressWarnings("unchecked")
    public Stack() {
        elements = (E[]) new Object[DEFAULT_INITIAL_CAPACITY];
    }
```

`@SuppressWarnings("unchecked")` 어노테이션을 추가하여, 경고 문구가 발생하지 않도록 하면, 깔끔히 컴파일되며, 명시적으로 형변환을 하지 않고도 `ClassCastException` 을 걱정없이 사용할 수 있다. ([item27](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-20-remove-unchecked-warning.md)) 

위 방법은 가독성이 방법2보다 더 좋다. 배열의 타입을 `E[]`로 선언하여 오직 `E` 타입 인스턴스만 받는 것을 명확히 표현하며, 코드도 더 짧다. 또한, 형변환을 배열 생성시 단 한번만 해주고 있다.

하지만, 이 방법은 런타임 타입이 컴파일타임 타입과 달라 [힙 오염-item 32]()을 발생시킨다.

### 방법2. Object[]로 타입 변경

두번째 방법은 `elements` 의 타입을 `Object[]`로 변경하는 방법이다.

```java
public class Stack<E> {
    // private으로 저장
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 15;

    public Stack() {
        elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(E e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public E pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }

        E result = elements[size--]; 
        elements[size] = null;
        return result;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    private void ensureCapacity() {
        if (elements.length == size) {
            elements = Arrays.copyOf(elements, 2 * size + 1);
        }
    }
}


```

다음과 같이 변경시 `E result = elements[size--]` 부분에서 형변환 컴파일 오류가 발생한다.

```
java: incompatible types: java.lang.Object cannot be converted to E
```

```java
E result = (E) elements[size--];
```

`(E)` 로 캐스팅해주면, 컴파일 오류는 발생하지 않으나 다음과 같은 오류문구가 뜬다.

```
Unchecked cast: 'java.lang.Object' to 'E' 
```

`E` 는 실체화가 불가능한 타입이므로 컴파일러는 런타임에 이루어지는 형변환이 안전한지 증명할 수 없으며, 방법1과 마찬가지로 어노테이션을 사용하여 경고를 숨길 것이다.

```java
// push에서 E타입만 허용하므로 안전
@SuppressWarnings("unchecked")E result = (E) elements[size--];
```

`@SuppressWarnings("unchecked")` 는 가능한 좁은 범위에 설정하는 것이 좋으므로, 변수 선언 부분에 붙여주었다.

방법2는 배열에서 원소를 읽을 때마다 형변환을 해주고 있으며, 가독성도 방법1보다 좋지 않다. 하지만, 힙 오염을 일으키지 않는다.



------

이번장의 예시는 [item28 - 배열보다 리스트를 사용해라](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-21-use-list-rather-than-array.md) 의 내용과 모순되어 보인다.

**제네릭 타입 안에서 리스트를 사용하는 것이 항상 가능한 것도, 좋은 것도 아니다.**  자바가 리스트를 기본타입으로 제공하지 않아, `ArrayList` 와 같은 제네릭 타입도 결국은 기본 타입인 배열을 사용해 구현해야하며, `HashMap` 의 경우 성능을 높일 목적으로 배열을 사용하기도 한다.

```java
Stack<String> stack = new Stack<>();
```

대부분 **제네릭 타입은 타입 매개변수에 아무런 제약을 두지 않으며**, `Stack<Object>`, `Stack<int[]>`, `Stack<List<String>>`, `Stack` 등 어떤 참조 타입으로도 생성할 수 있다. 단, **기본타입은 사용할 수 없다.** `Stack<int>` 같이 기본타입으로 만들려고 하면 컴파일 오류가 발생한다. 해당 오류는 자바 제네릭 타입 시스템의 근본적인 문제이며, [item61-박싱된 기본타입]()을 사용해 우회할 수 있다.

추가적으로, 한정적 타입 매개변수(bounded type parameter)를 사용해 매개변수에 제약을 둘 수도 있다.

```java
public class DelayQueue<E extends Delayed> extends AbstractQueue<E>
    implements BlockingQueue<E> {
```

`<E extends Delayed>`는 `Delayed` 하위 타입만 받는다는 뜻이며, `DelayQueue` 의 원소에서 형변환 없이 바로 `Delayed` 메서드를 사용할 수 있다. 또한, `ClassCastException` 오류도 걱정할 필요가 없다.