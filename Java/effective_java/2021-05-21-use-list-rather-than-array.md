# ITEM28: 배열보다는 리스트를 사용해라

## **배열과 리스트 차이**

### 배열은 공변(함께 변한다), 제네릭은 불공변(서로 다르다)

#### 공변이란?

자기 자신과 자식 객체로 타입 변환을 허용해주는 것이다.

```java
Object[] objects = new Long[1];
```

그러므로 위와같은 문법을 허용해준다.

#### 불공변이란?

`List<String>` 과 `List<Object>` 가 있을 때 **두 개의 타입은 전혀 관련이 없다**는 의미이다.

```java
public class Test {
    public static void test(List<Object> list) {

    }
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("Gyunny");
        test(list);   // 컴파일 에러
    } 
}
```

제네릭이 공변이라면, 위 코드는 오류가 발생하지 않을 것이다. 하지만 자기와 타입이 같은 것만 같다고 인식하는 특징 때문에 컴파일 오류가 발생한다. 즉, 이러한 특성 때문에 제네릭은 컴파일 타임에 타입 안정성을 가질 수 있다.



- Array(공변)는 타입이 다른 경우 런타임 `ArrayStoreException` 오류 발생

```java
Object[] objects = new Long[1];
objects[0] = "ArrayStoreException : 타입이다름";
```

```
Exception in thread "main" java.lang.ArrayStoreException: java.lang.String
	at ch5.dahye.item28.ArrListTest.main(ArrListTest.java:7)
```

- List(불공변)는 컴파일 오류 발생

```java
List<Object> ol = new ArrayList<Long>();
ol.add("타입이 다름");
```

```java
java: incompatible types: java.util.ArrayList<java.lang.Long> cannot be converted to java.util.List<java.lang.Object>
```

```java
Object[] objects = new Long[1];
Assertions.assertThrows(ArrayStoreException.class, () -> objects[0] = "ArrayStoreException : 타입이다름");
```

Array와 List 두개 모두 Long 타입에 String 값을 넣을 수 없다. **여기서 큰 차이는 배열은 런타임시 해당 오류를 알며, 리스트는 컴파일시 바로 알 수 있다.**

2. 배열은 런타임에도 자신이 담기로 한 원소 타입을 인지하고 확인하며, 반면 리스트(제네릭)는 타입 정보가 런타임에는 소거 되며, 원소 타입은 컴파일시에만 검사한다. 즉, 런타임시에는 타입을 알 수 없다. 이렇게 소거하는 이유는 제네릭을 지원하기 전 레거시 코드와 제네릭 타입을 함께 사용할 수 있도록 하기 위해서 이다.([item26](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-19-generic-dont-use-raw-type.md))



위 두 차이로 인해 배열과 제네릭은 함께 어우러지지 못한다. 배열은 제네릭 타입, 매개변수화 타입, 타입 매개변수로 사용할 수 없으며, 아래와 같이 사용하려고 하면 제네릭 배열 생성 오류를 발생시킨다.

```java
List<String>[] stringList = new List<String>[1];
```

```
java: generic array creation
```

타입 안정성때문에 위와 같이 제네릭 배열을 생성하지 못하도록 했다. 제네릭 배열 생성을 허용한다면 컴파일러가 자동 생성한 형변환 코드에서 런타임시 `ClassCastException` 이 발생할 수 있으며, 이는 런타임시 `ClassCastException` 이 발생하지 않도록 막겠다는 제네릭의 취지에 어긋난다.

### 타입

배열은 구체화(reify)가 되고, 제네릭은 비구체화(non-reify)가 된다.

#### 구체화 타입 (reifiable type)

자신의 타입 정보를 런타임에도 알고 있는 것이다.

#### 비 구체화 타입 (non-reifiable type)

**비 구체화 타입은 런타임 시에 소거(erasure)되기 때문에 런타임에는 컴파일타임보다 타입 정보를 적게 가지는 타입**이다. 
`E`, `List<E>`, `List<String>` 과 같은 타입을 실체화 불가 타입 혹은 비 구체화 타입이라고 한다. 



여기서 말하는 타입 소거란 무엇일까?

#### Generic Type Erasure

제네릭은 타입의 안정성을 보장하며, 실행시간에 오버헤드가 발생하지 않도록 하기위해 추가됐다. 컴파일러는 컴파일 시점에 제네릭에 대해 원소 타입 소거(type erasure)를 한다. 즉, **컴파일 타임에만 타입 제약 조건을 정의하고, 런타임에는 타입을 제거**한다는 뜻이다.

- **unbounded Type(`<?>`, `<T>`)은 `Object`로 변환**
- **bound type(`<E extends Comparable>`)의 경우는 Object가 아닌 `Comprarable`로 변환**
- 제네릭 타입을 사용할 수 있는 일반 클래스, 인터페이스, 메소드에만 소거 규칙을 적용
- 타입 안정성 보존을 위해 필요시 type  casting
- **확장된 제네릭 타입에서 다형성을 보존하기위해 bridge method 생성**

하나씩 예제를 보면서 알아볼 것이다.

- unbounded Type(`<?>`, `<T>`)은 `Object`로 변환

  ```java
  // 타입 소거 이전
  public class Node<T> {
  
      private T data;
      private Node<T> next;
  
      public Node(T data, Node<T> next) {
          this.data = data;
          this.next = next;
      }
  
      public T getData() { return data; }
      // ...
  }
  ```
  
  ```java
  // 런타임(타입 소거 후)
  public class Node {
  
      private Object data;
      private Node next;
  
      public Node(Object data, Node next) {
          this.data = data;
          this.next = next;
      }
  
      public Object getData() { return data; }
      // ...
  }
  ```
  
  type erasure가 적용되면서 특정 타입으로 제한되지 않은 `<T>`는 다음과 같이 `Object`로 대체된다.
  
  제네릭 메서드에서도 동일하다.
  
  ```java
  public static <T> int count(T[] anArray, T elem) {
      int cnt = 0;
      for (T e : anArray)
          if (e.equals(elem))
              ++cnt;
          return cnt;
  }
  ```
  
  ```java
  public static int count(Object[] anArray, Object elem) {
      int cnt = 0;
      for (Object e : anArray)
          if (e.equals(elem))
              ++cnt;
          return cnt;
  }
  ```
  
  `T` 는 비한정적 타입이므로, 컴파일러가 `Object` 로 변환한다.
  
- bound type(`<E extends Comparable>`)의 경우는 Object가 아닌 `Comprarable`로 변환

  ```java
  // 컴파일 할 때 (타입 변환 전) 
  public class Node<T extends Comparable<T>> {
  
      private T data;
      private Node<T> next;
  
      public Node(T data, Node<T> next) {
          this.data = data;
          this.next = next;
      }
  
      public T getData() { return data; }
      // ...
  }
  ```

  ```java
  // 런타임 시
  public class Node {
  
      private Comparable data;
      private Node next;
  
      public Node(Comparable data, Node next) {
          this.data = data;
          this.next = next;
      }
  
      public Comparable getData() { return data; }
      // ...
  }
  ```

  한정된 타입(bound type)에서는 컴파일 시점에 제한된 타입으로 변환된다. `Comparable` 로 변환된 것을 확인할  수 있다.

  ```java
  public static <T extends Shape> void draw(T shape) { /* ... */ }
  ```

  ```java
  public static void draw(Shape shape) { /* ... */ }
  ```

  여기서는 `Shape` 로 변환된 것을 확인할 수 있다.

- 확장된 제네릭 타입에서 다형성을 보존하기위해 bridge method 생성

  컴파일러가 컴파일 시점에 제네릭 타입 안정성을 위해 bridge method를 생성할 수 있다. 다음 예제를 살펴보자.

  ```java
  public class Node<T> {
  
      public T data;
  
      public Node(T data) { this.data = data; }
  
      public void setData(T data) {
          System.out.println("Node.setData");
          this.data = data;
      }
  }
  
  public class MyNode extends Node<Integer> {
      public MyNode(Integer data) { super(data); }
  
      public void setData(Integer data) {
          System.out.println("MyNode.setData");
          super.setData(data);
      }
  }
  ```

  위 두개의 클래스가 있다. 이때 다음과 코드를 실행해야한다고 예를 들어보자.

  ```java
  MyNode mn = new MyNode(5);
  Node n = mn;            // A raw type - compiler throws an unchecked warning
  n.setData("Hello");     // Causes a ClassCastException to be thrown.
  Integer x = mn.data;    
  
  ```

  타입이 소거된 후에는 다음과 같이 적용되며,런타임시  `ClassCastException` 를 발생시키게 된다.

  ```java
  MyNode mn = new MyNode(5);
  Node n = (MyNode)mn;         // A raw type - compiler throws an unchecked warning
  n.setData("Hello");          // Causes a ClassCastException to be thrown.
  Integer x = (String)mn.data; 
  ```

  타입 소거 후에 `Node`와 `MyNode`는 다음과 같이 변환되는 것을 볼 수 있으며, 소거 후에는 `Node` 시그니처 메서드가 `setData(T data)` 에서 `setData(Object data)`로 바꾸기 때문에 `MyNode` 의 `setData(Integer data)`를 overriding 할 수  없게 된다.

  ```java
  public class Node {
  
      public Object data;
  
      public Node(Object data) { this.data = data; }
  
      public void setData(Object data) {
          System.out.println("Node.setData");
          this.data = data;
      }
  }
  
  public class MyNode extends Node {
  
      public MyNode(Integer data) { super(data); }
  
      public void setData(Integer data) {
          System.out.println("MyNode.setData");
          super.setData(data);
      }
  }
  ```

  런타임 시에는 다음과 같이 타입이 소거된 상태로 변할 것이다. (`Object`로 변환) 그렇게 되면,  `Object` 로 변하게 되는 경우에 대한 불일치를 없애기 위해 컴파일러는 런타임에 해당 제네릭 타입의 타임 소거를 위한 bridge method를 생성해준다.

  ```java
  class MyNode extends Node {
  
      // Bridge method generated by the compiler
      //
      public void setData(Object data) {
          setData((Integer) data);
      }
  
      public void setData(Integer data) {
          System.out.println("MyNode.setData");
          super.setData(data);
      }
  
      // ...
  }
  ```

  그렇기때문에 `ClassCastException` 예외를 던지는 것을 알 수 있다.

즉, 제네릭 타입 소거(Generic Type Eraser) 과정에 의해서 매개변수화 타입 가운데 실체화 될 수 있는 타입은 `List<?>`, `Map<?,?>` 과 같이 [비한정적 와일드카드 타입](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-19-generic-dont-use-raw-type.md#%EB%B9%84%ED%95%9C%EC%A0%95%EC%A0%81-%EC%99%80%EC%9D%BC%EB%93%9C%EC%B9%B4%EB%93%9C-%ED%83%80%EC%9E%85unbounded-wildcard-type)뿐인 것이다. 



배열은 비한정적 와일드카드 타입으로 만들 수는 있지만 유용하게 사용하는 케이스는 거의 없다. 배열을 제네릭으로 생성할 수 없어 귀찮아 지는 경우도 있다.

- 제네릭 컬렉션에 자신의 원소 타입을 담은 배열을 반환하는 것은 보통 불가능([ITEM33]())
- 제네릭 타입과 [가변인수 메서드 - item53]() 를 함께 사용하는 경우([item32]() 로 해결 가능)

배열로 형 변환시 제네릭 배열 생성 오류나 비검사 형변환 경고가 뜨는 경우에는 대부분 `E[]` 대신 `List<E>` 를 사용하면 해결된다. 코드 가독성과 성능은 살짝 안좋아질 수 있지만, 타입 안정성과 상호운용성은 좋아진다.



## Array -> Generic

- Array

```java
public class ChooserArray {

    private final Object[] choiceArray;


    // 생성자에 어떤 컬렉션을 넘기느냐에 따라 주사위판, 매직8볼, 몬테카를로 시뮬레이션용으로 활용 가능
    public ChooserArray(Collection choices) {
        this.choiceArray = choices.toArray();
    }

    // 컬렉션안의 원소 중 하나를 무작위로 선택해 반환
    // 반환된 Object를 원하는 타입으로 형변환 필요 -> 타입이 다른게 들어가 있는 경우 런타임 오류 발생
    public Object choose() {
        Random rnd = ThreadLocalRandom.current();
        return choiceArray[rnd.nextInt(choiceArray.length)];
    }
}
```

위 클래스의 경우 choose 메서드를 호출할 때마다 반환된 Object를 원하는 타입으로 형변환 해야하며, 이때 다른 타입의 원소가 들어 있다면 런타임 오류가 발생할 것이다. 이러한 경우 런타임 오류가 발생하지 않도록 Generic으로 변경 해주는 것이 좋다.

- Generic

```java
package ch5.dahye.item28;

import java.util.Collection;

public class ChooserGeneric<T> {

    private final T[] choiceArray;


    public ChooserGeneric(Collection<T> choices) {
      	// incompatible types 오류 -> (T[])로 형변환 필요
        this.choiceArray = (T[]) choices.toArray();
    }
}

```

다음과 같이 형변환 하여 collection을 array로 변환하는 경우 아래와 같이 경고가 뜬다.

```
Unchecked cast: 'java.lang.Object[]' to 'T[]' 
```

T가 무슨타입인지 모르므로, 컴파일러는 이 형변환이 런타임에도 안전한지 보장할 수 없다는 것이다.(**제네릭은 원소의 타입 정보가 소거되어 런타임시 어떤 타입인지 알 수 없음**) 

위 코드는 동작하지만, 컴파일러가 안전을 보장하지 못한다. 만약 타입 안전성을 확신한다면 주석을 남기고 `@SuppressWarnings("unchecked")` 어노테이션을 추가할 수 있다. 하지만, [[item 27](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-20-remove-unchecked-warning.md)] 과 같이 비검사 경고를 제거하여 원인을 제거하는 것이 좋다.

- 비검사 형검사 경고 제거

```java
public class Chooser<T> {
    private final List<T> choiceList;

    public Chooser(Collection<T> choices) {
        this.choiceList = new ArrayList<>(choices);
    }
    
    public T choose() {
        Random rnd = ThreadLocalRandom.current();
        return choiceList.get(rnd.nextInt(choiceList.size()));
    }
}

```

**배열 대신 리스트를 사용하여, 형변환 경고를 제거**할 수 있다. 또한 런타임시에 `ClassCastException`이 발생할 일도 없다.





## 참고

- [https://stackoverflow.com/questions/18411440/why-we-call-unbounded-wild-card-parameterized-type-as-reifiable](https://stackoverflow.com/questions/18411440/why-we-call-unbounded-wild-card-parameterized-type-as-reifiable)
- [https://docs.oracle.com/javase/tutorial/java/generics/erasure.html](https://docs.oracle.com/javase/tutorial/java/generics/erasure.html)

- [[Java\] Generic Type erasure란 무엇일까?](https://devlog-wjdrbs96.tistory.com/263)
- [Java 제네릭 기본](https://sthwin.tistory.com/22)




