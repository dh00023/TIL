# ITEM28: 배열보다는 리스트를 사용해라

## **배열과 리스트 차이**

1. 배열은 공변(함께 변한다), 제네릭은 불공변(서로 다르다)

   - Array는 타입이 다른 경우 런타임 `ArrayStoreException` 오류 발생

   ```java
   Object[] objects = new Long[1];
   objects[0] = "ArrayStoreException : 타입이다름";
   ```

   ```
   Exception in thread "main" java.lang.ArrayStoreException: java.lang.String
   	at ch5.dahye.item28.ArrListTest.main(ArrListTest.java:7)
   ```

   - List는 컴파일 오류 발생

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



## 타입

`E`, `List<E>`, `List<String>` 과 같은 타입을 실체화 불가 타입(non-reifiable type)이라고 한다. **실체화 불가 타입은 실체화가 되지 않아서 런타임에는 컴파일타임보다 타입 정보를 적게 가지는 타입**이다. 

매개변수화 타입 가운데 실체화 될 수 있는 타입은 `List<?>`, `Map<?,?>` 과 같이 [비한정적 와일드카드 타입](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-19-generic-dont-use-raw-type.md#%EB%B9%84%ED%95%9C%EC%A0%95%EC%A0%81-%EC%99%80%EC%9D%BC%EB%93%9C%EC%B9%B4%EB%93%9C-%ED%83%80%EC%9E%85unbounded-wildcard-type)뿐이다. 배열은 비한정적 와일드카드 타입으로 만들 수는 있지만 유용하게 사용하는 케이스는 거의 없다.

배열을 제네릭으로 생성할 수 없어 귀찮아 지는 경우도 있다.

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





