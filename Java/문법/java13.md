## 13. Generic

Generic 타입을 이용함으로써 잘못된 타입이 사용될 수 있는 문제를 컴파일 과정에서 제거할 수 있게되었다. 제네릭은 클래스와 인터페이스, 메소드를 정의할 때 타입(type)을 파라미터(parameter)로 사용할 수 있도록한다. 타입 파라미터는 코드 작성 시 구체적인 타입으로 대체되어 다양한 코드를 생성하도록 해준다.

#### 장점

1. 컴파일 시 강한 타입 체크를 할 수 있다.

2. 타입 변환(casting)을 제거한다.
   ```java
   // generic이 아닌경우
   List list = new ArrayList();
   list.add("hello");
   String str = (String)list.get(0); // 타입 변환이 필요
   
   // generic
   List<String> list = new ArrayList<String>();
   list.add("hello");
   String str = list.get(0); // 타입 변환을 하지 않음
   ```



### Generic Type

Generic Type은 **타입을 파라미터로 가지는 클래스(`class<T>`)와 인터페이스(`interface<T>`)**를 말한다.

```java
public class 클래스명<T> {...}
public interface 인터페이스명<T> {...}
```

 타입 파라미터는 변수명과 동일한 규칙으로 작성될 수 있지만, **일반적으로 대문자 한글자**로 표현한다. Generic Type을 실제 코드에서 사용하려면 타입 파라미터에 구체적인 타입을 지정해야한다.

```java
public class Box{
    private Object obj;
    public void set(Object object){this.obj = object;}
    public Object get(){ return obj; }
}
```

위의 코드에서  클래스 필드 타입을 Object로 선언한 이유는 필드에 모든 종류의 객체를 저장하고 싶어서이다. **Object는 모든 자바 클래스의 최상위 조상(부모) 클래스이다.** 자식 객체는 부모타입에 대입할 수 있기 때문에 모든 자바 객체는 Object타입으로 자동 타입변환되어 저장된다.

```java
Box box = new Box();
box.set("안녕");						// String 타입을 Object타입으로 자동타입 변환
String str = (String) box.get();	// Object 타입을 String타입으로 강제 타입 변환
```

다음과 같이 get으로 가져오기위해서는 강제 타입 변환이 필요하다.



Object 타입을 사용하면 모든 종류의 자바 객체를 저장할 수 있다는 장점은 있지만, 저장할 때와 읽어올 때 타입 변환이 발생하며, 잦은 타입 변환은 전체 프로그램 성능에 좋지 못한 결과를 가져올 수 있다.



**Generic을 통해서 타입변환이 발생하지 않도록 할 수 있다.**

```java
public class Box<T>{
    private T t;
    public void set(T t){this.t = t;}
    public T get(){ return t; }
}
```

```java
Box<String> box = new Box<String>();
```

여기서 T는 클래스로 **객체를 생성할 때 구체적인  타입으로 변경**된다. 그렇기 때문에 저장할 때와 읽어올 때 타입 변환이 발생하지 않는다. 이와 같이 generic은 클래스 설계시 구체적은 타입을 명시하지 않고, 타입 파라미터로 대체했다가 실제 클래스가 사용될 때 구체적인 타입을 지정함으로써 타입 변환을 최소화시킨다.



### 멀티 타입 파라미터

Generic Type은 **두 개 이상**의 멀티 파라미터를 사용할 수 있다. 

```java
public class Product<T, M>{
    private T kind;
    private M model;
    
    public T getKind(){ return this.kind; }
	public M getModel(){ return this.model; }
    
    public void setKind(T kind){ this.kind = kind; }
    public void setMode(M model){ this.model = model; }
}
```

```java
public class ProductEx{
    public static void main(String[] args){
        Product<TV, String> prd1 = new Product<TV,String>();
        prd1.setKind(new TV());
        prd1.setModel("삼성TV");
        TV tv = prd1.getKind();
        String tvModel = prd1.getModel();
    }
}
```

제네릭 타입 변수 선언과 객체 생성을 동시에 할 때 타입 파라미터에 구체적인 타입을 지정하는 코드가 중복될 수 있다. 그렇기 때문에 자바7에서 부터는 `<>` (다이아몬드연산자)를 제공한다. 자바 컴파일러는 타입 파라미터 부분에 `<>`연산자를 사용하면 타입 파라미터를 유추해서 자동으로 설정해준다.

```java
// java7이후
Product<TV, String> product = new Porduct<>();
```

### Generic Method

**Generic Method는 매개타입과 리턴 타입으로 타입 파라미터**를 갖는 메소드이다.

```java
public <타입파라미터, ...> 리턴타입 메소드명(매개변수, ...){...}
```

```java
public <T> Box<T> boxing(T t){...}
```

매개변수타입으로 T, 리턴타입으로 `Box<T>`를 사용했다.



Generic 메소드는 다음과 같이 호출될 수 있다.

```java
//명시적으로 구체적 타입을 지정
리턴타입 변수 = <구체적타입> 메소드명(매개값);
Box<Integer> box = <Integer>boxing(100);

//매개값을 보고 구체적 타입을 추정
리턴타입 변수 = 메소드명(매개값);
Box<Integer> box = boxing(100);
```



### 제한된 타입 파라미터(`<T extends 최상위타입>`)

타입 파라미터에 지정되는 구체적인 타입을 제한할 필요가 종종 있다. 숫자를 연산하는 제네릭 메소드의 매개값으로는 Number타입 또는 그 하위 클래스 타입의 인스턴스만 가져야한다. 이렇게 제한된 타입 파라미터가 필요한 경우가 있다.

```java
public <T extends 상위타입> 리턴타입 메소드(매개변수, ...){...}
```

 상위 타입은 클래스뿐만 인터페이스도 가능하다. 하지만 인터페이스라고 해서 implements를 사용하지 않는다.

- 타입 파라미터의 구체적 타입 : 상위타입, 상위타입의 하위 또는 구현클래스
- `{}` 안에서의 타입 파라미터 변수 : 상위 타입의 멤버(필드, 메소드로 제한

```java
public <T extends Number> int compare(T t1, T t2){
    double v1 = t1.doubleValue();
    double v2 = t2.doubleValue();
    return Double.compare(v1,v2);
}
```

```java
public class Util{
    public static <T extends Number> int compare(T t1, T t2){
        double v1 = t1.doubleValue();
	    double v2 = t2.doubleValue();
	    return Double.compare(v1,v2);
    }
}
```

```java
public class Example{
    public static void main(String[] args){
        //String str = Util.compare("a","b"); Number타입이 아니므로 오류
        int result = Util.compare(10,20);
        int result2 = Util.compare(10.5,20);
    }
}
```



### 와일드카드 타입(`<?>`, `<? extends ...>`, `<? super ...>`)

코드에서 **`?`를 일반적으로 와일드카드**라고 부른다.

- `제네릭타입<?>` : 제한없음(타입 파라미터를 대치하는 구체적 타입으로 모든 클래스나 인터페이스 타입이 올 수 있다.)
- `제네릭타입<? extends 상위타입>` :  상위 클래스 제한(타입 파라미터를 대치하는 구체적 타입으로 상위 타입이나 하위 타입만 올 수 있다.)
- `제네릭타입<? super 하위타입>` :  하위 클래스 제한(타입 파라미터를 대치하는 구체적 타입으로 하위 타입이나 상위타입이 올 수 있다.)

```java
public class Couse<T>{
    private String name;
    private T[] students;
    
    public Course(String name, int capacity){
        this.name = name;
        // 타입 파라미터로 배열을 생성하려면 new T[n]형태가 아닌 (T[])(new T[n])의 형태로 생성해야한다.
        students = (T[])(new Object[capacity]);
    }
    
    public String getName(){ return name; }
    public T[] getStudents(){ return students; }
    public void add(T t){
        for(int i=0;i<students.length;i++){
            if(students[i] == null){
                students[i]=t;
				break;
            }
        }
    }
}
```

수강생이 될 수 있는 타입이 아래와 같다.

- Person
  - Worker
  - Student
    - HighStudent



- `Course<?>` : 수강생은 모든 타입(Person, Worker, Student, HightStudent)
- `Course<? extends Students>` :  수강생는 Student와 HighStudent만 가능
- `Course<? super Worker>` :  Worker, Person만 가능



### Generic Type의 상속과 구현

제네릭 타입도 부모 클래스가 될 수 있다.

```java
public class ChildProduct<T,M> extends Product<T,M>{...}
```

자식 제네릭 타입은 추가적으로 타입 파라미터를 가질 수 있다.

```java
public class ChildProduct<T,M,C> extends Product<T,M>{...}
```

제네릭 인터페이스를 구현한 클래스도 제네릭 타입이된다.

```java
public interface Storage<T>{
    public void add(T item, int index);
    public T get(int index);
}
```

```java
public class StorageImpl<T> implements Storage<T>{
    private T[] array;
    
    public StorageImpl(int capacity){
        this.array = (T[])(new Object[capacity]);
    }

    @Override
    public void add(T item, int index){
        array[index] = item;
    }
    
    @Override
    public T get(int index){
        return array[index];
    }
}
```

