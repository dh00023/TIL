# ITEM1 - STATIC FACTORY METHODS INSTEAD OF CONSTRUCTORS

## Static Factory Method(정적 메소드)

public 생성자를 사용해 객체를 생성하는 방법 외 다음과 같이 **public static factory method** 를 사용해 해당 클래스의 인스턴스를 만드는 방법이 있다.

```java
// boolean의 기본 타입의 값을 받아 Boolean 객체 참조로 변환
public static Boolean valueOf(boolean b){
    return b ? Boolean.TRUE : Boolean.FALSE;
}
```

이처럼 생성자 대신 정적 팩토리 메소드를 사용하는 것에 대한 장단점은 다음과 같다.

### 장점

1. **이름을 가질 수 있다.**

   ```java
   public class Book {
       private String title;
       private String author;
       
       // 생성자1
       public Book(String title, String author){
           this.title = title;
           this.author = author;
       }
   
       /**
        * 생성자는 하나의 시그니처만 사용하므로, 다음과 같이 생성자 생성이 불가능하다.
        * 
        */
       public Book(String title){
           this.title = title;
       }
       
       public Book(String author){
           this.author = author;
       }
   }
   
   ```

   생성자는 똑같은 타입의 파라미터로 받는 생성자를 여러개 생성할 수 없으므로, 한 클래스에 시그니처가 같은 생성자가 여러 개 필요한 경우에도 사용할 수 있으며, 파라미터가 반환하는 객체를 잘 설명하지 못하는 경우에, 이름을 잘 지은 static factory method를 사용할 수 있다.

   ```java
   public class Book {
     String title;
     String author;
     
     public Book(String title, String author){
       this.title = title;
       this.autor = author;
     }
     
     public Book(){}
     
     /*
     * withName, withTitle과 같이 이름을 명시적으로 선언할 수 있으며,
     * 한 클래스에 시그니처가 같은(String) 생성자가 여러개 필요한 경우에도 다음과 같이 생성할 수 있다.
     */
     
     public static Book withAuthor(String author){
       Book book = new Book();
       book.author = author;
       return book;
     }
     
     public static Book withTitle(String title){
       Book book = new Book();
       book.title = title;
       return book;
     }
   }
   ```

2. **호출될 때마다 인스턴스를 새로 생성하지 않아도 된다.**

   ```java
   public final class Boolean implements java.io.Serializable,
                                         Comparable<Boolean>
   {
       /**
        * The {@code Boolean} object corresponding to the primitive
        * value {@code true}.
        */
       public static final Boolean TRUE = new Boolean(true);
   
       /**
        * The {@code Boolean} object corresponding to the primitive
        * value {@code false}.
        */
       public static final Boolean FALSE = new Boolean(false);
    		// ...
   }
   ```

   ```java
   // boolean의 기본 타입의 값을 받아 Boolean 객체 참조로 변환
   public static Boolean valueOf(boolean b){
       return b ? Boolean.TRUE : Boolean.FALSE;
   }
   ```

   - 불변클래스 : 미리 만들어둔 인스턴스를 재활용하여(캐싱) 불필요한 객체 생성을 피할 수 있다.
   - `Boolean.TRUE`는 이에 대한 대표적인 예로, 객체를 생성하지 않는다.
   - [Flyweight pattern]() : 데이터를 공유해 메모리를 절약하는 패턴으로 공통으로 사용되는 객체는 한번만 사용되고, pool에 의해서 관리, 사용된다.
   - [Instance-Controlled Class]() : 정적 펙토리 방식의 클래스는 언제 어느 인스턴스를 살아 있게 할지 통제할 수 있다.
     - [Singleton]() / [noninstattiable]() 로 만들 수 있다.

3. **리턴 타입의 하위 타입 객체를 반환할 수 있다.**

   - 반환할 객체의 클래스를 자유롭게 선택할 수 있다. (유연성)
   - **인터페이스 기반 프레임워크**  : 인터페이스를 정적 펙토리 메서드의 반환 타입으로 사용
     - 인터페이스를 구현한 모든 클래스를 공개하는 것이 아닌 인터페이스 만을 공개할 수 있다.

   ```java
   // java7 Collections.emptyList()
   public Collections(){
     	///...
     
       public static final List EMPTY_LIST = new EmptyList<>();
   
       public static final <T> List<T> emptyList() {
           return (List<T>) EMPTY_LIST;
       }
     
   	  //...
   }
   ```

   ```java
   // java9 List of()
   static <E> List<E> of() {
       return (List<E>) ImmutableCollections.ListN.EMPTY_LIST;
   }
   ```

4. **입력 매개변수에 따라 매번 다른 클래스의 객체를 반환할 수 있다**.

   - 하위 타입 클래스이기만 하면 어떠한 클래스의 객체를 반환할 수 있다.

   - 그 대표적인 예가 `EnumSet` 으로, public 생성자 없이 오직 정적 팩터리만으로 제공한다.

     ```java
     public abstract class EnumSet<E extends Enum<E>> extends AbstractSet<E>
         implements Cloneable, java.io.Serializable
     {
         //...
         /**
          * Creates an empty enum set with the specified element type.
          *
          * @param <E> The class of the elements in the set
          * @param elementType the class object of the element type for this enum
          *     set
          * @return An empty enum set of the specified type.
          * @throws NullPointerException if <tt>elementType</tt> is null
          */
         public static <E extends Enum<E>> EnumSet<E> noneOf(Class<E> elementType) {
             Enum<?>[] universe = getUniverse(elementType);
             if (universe == null)
                 throw new ClassCastException(elementType + " not an enum");
     
             if (universe.length <= 64)
                 return new RegularEnumSet<>(elementType, universe);
             else
                 return new JumboEnumSet<>(elementType, universe);
         }
       
       //...
     }
     ```

     EnumType의 원소의 개수에 따라 `RegularEnumSet`, `JumboEnumSet` 으로 결정되는데 클라이언트는 이 두 객체의 존재를 모르며, 추후에 새로운 타입을 만들거나 기존 타입을 없애는 경우에도 문제되지 않는다.

5. **정적 팩토리 메소드를 작성하는 시점에는 반환할 객체의 클래스가 존재하지 않아도 된다**.

   - 대표적인 Service Provider Framework(서비스 제공자 프레임워크)로는 JDBC 가 있다.
   - **서비스 인터페이스**(JDBC -  `Connection`) : 구현체의 동작 정의
   -  **제공자 등록 API**(JDBC - `DriverManager.registerDriver`) : provider가 구현체를 등록할 떄 사용
   - **서비스 접근 API**(JDBC - `DriverManager.getConnection`) : 클라이언트는 서비스 접근 API 사용시 원하는 구현체의 조건을 명시할 수 있음
   - 서비스 제공자 인터페이스(JDBC - `Driver`) : 서비스 인터페이스의 인스턴스를 생성하는 펙토리 객체를 설명해준다.
   - 클라이언트는 서비스 접근 API 사용시 원하는 구현체의 조건을 명시할 수 있는 점은  Service Provider Framework가 유연한 정적 팩토리라고 할 수 있는 실체이다.

   

### 단점

1.  `public` 혹은 `protected` 생성자가 없이 정적 펙터리 메서드만 제공하는 클래스는 하위 클래스를 생성할 수 없다.
   - 해당 제약은 상속보다는 [Composition]() 사용을 유도하고, [Immutable]() 타입으로 만드려면 해당 제약을 지켜야 한다는 점에서 장점이 될 수 있다.
2. 프로그래머가 해당 메서드를 찾기 쉽지 않다.
   - 생성자는 API Docs 상단에 모아두었기 때문에 찾기가 쉬우나, 정적 팩터리 메서드는 다른 메서드와 구분 없이 보여주므로 사용자가 인스턴스화할 방법을 알아서 찾아내야한다.

### 주로 사용하는 명명 방식

| 메서드                      | 설명                                                         | 예제                                                        |
| --------------------------- | ------------------------------------------------------------ | ----------------------------------------------------------- |
| `from`                      | 매개변수를 하나 받아 해당 타입의 인스턴스를 반환(형변환 method) | `Date d = Date.from(instant);`                              |
| `of`                        | 여러 매개변수를 받아 적합한 타입의 인스턴스를 반환하는 집계 메서드 | `Set<Rank> faceCards = EnumSet.of(JACK, QUEEN, KING);`      |
| `valueOf`                   | `from`과 `of`의 더 자세한 버전                               | `BigInteger.valueOf(Integer.MAX_VALUE);`                    |
| `instance`<br>`getInstance` | 매개변수를 받을 경우 매개변수로 명시한 인스턴스를 반환하지만 같은 인스턴스임을 보장하지는 않음 | `StackWalker luke = StackWalker.getInstance(options);`      |
| `create`<br>`newInstance`   | `instance` 혹은 `getInstance`와 같지만 매번 새로운 인스턴스르 ㄹ생성해 반환한다. | `Object newArr = Array.newInstance(classObj,arrayLen);`     |
| `getType`                   | `getInstance`와 같으나 생성할 클래스가 아닌 다른 클레스의 팩터리 메서드를 정의할 때 사용한다. | `FileStore fs = Files.getFileStore(path)`                   |
| `newType`                   | `newInstance`와 같으나 생성할 클래스가 아닌 다른 클레스의 팩터리 메서드를 정의할 때 사용한다. | `BufferedReader br = Files.newBufferedReader(path);`        |
| `type`                      | `getType`과 `newType`의 간결한 버전                          | `List<Complaint> litany = Collections.list(legachLitancy);` |



## 참고

- [https://parkgaebung.tistory.com/29](https://parkgaebung.tistory.com/29)
- [쟈미의 devlog](https://jyami.tistory.com/56)