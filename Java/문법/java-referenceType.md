# 참조 타입(Reference Type)

## 데이터 타입 분류

- 기본타입(primitive type) : 정수, 실수, 문자, 논리 리터럴
- 참조타입(reference type) : 객체(Object)의 번지를 참조하는 타입으로 배열, 열거, 클래스, 인터페이스


## 메모리 사용 영역

![](http://bestforjava.com/images/jvm_architecture.jpg)

### 메소드(Method) 영역

코드에서 사용되는 클래스 들을 클래스 로더로 읽어 클래스별로 runtime constant pool, field data, method data, method code, constructor code를 분류해서 저장된다.
메소드 영역은 JVM이 시작할 때 생성되고 모든 스레드가 공유하는 영역이다.

### 힙(Heap)영역

힙 영역은 객체와 배열이 생성되는 영역이다. 힙 영역에 생성된 객체와 배열은 JVM 스택 영역의 변수나 다른 객체의 필드에서 참조한다.
참조하는 변수나 필드가 없다면 의미 없는 객체가 되기 때문에 이를 쓰레기로 취급하고 Garbage Collector를 실행시켜 자동으로 힙 영역에서 제거한다.

### JVM 스택(Stack) 영역

JVM 스택 영역은 각 스레드마다 존재하며, 스레드가 시작될 때 할당된다.JVM 스택은 메소드를 호출할 때마다 Frame을 추가(push)하고, 메소드가 종료되면 해당 프레임을 제거(pop)하는 동작을 수행한다.

## 참조 방식

### 강한 참조(Strong Reference)

가장 일반적인 참조 유형이다.

```java
Integer prime = 1;
```
primte 변수는 값이 1인 `Integer` 객체에 대한 강한 참조를 가진다. 강한 참조가 있는 객체는 GC 대상이 되지 않는다.

### 부드러운 참조(Soft Reference)

```java
Integer prime = 1;
SoftReference<Integer> sr = new SoftReference<Integer>(prime);
```
`SoftReference` 클래스를 이용하여 생성할 수 있다. 만약 prime객체의 상태가 `null`이 되어 더이상 Strong Reference는 없고 대상을 참조하는 객체가 `SoftReference`만 존재할 경우 GC대상이 된다. 
`SoftReference`는 메모리가 부족하지 않으면 GC 대상으로 잡히지 않는다. 때문에 조금은 엄격하지 않은 Cache Library들에서 널리 사용되는 것으로 알려져있다.

### 약한 참조(Weak Reference)

```java
Integer prime = 2;
WeakReference<Integer> wr = new WeakReference<Integer>(prime);
```

약한 참조는 `WeakReference` 클래스를 이용해 생성이 가능하다. `SoftReference`와 동일하게 prime 객체의 상태가 `null`이 되어 해당 객체를 참조하는 객체가 `WeakReference` 뿐이라면 GC 대상이 된다.

`WeakReference`가 `SoftReference`와 다른점은 `WeakReference`는 메모리가 부족하지 않더라도 GC대상이 되며, 다음 GC가 발생하는 시점에 무조건 없어진다.

## 참조 변수의 `==`,`!=`연산

참조 변수에서 `==`,`!=` 연산은 동일한 객체를 참조하는지, 다른 객체를 참조하는지 알아볼 때 사용된다.
참조 타입 변수의 값은 힙 영역의 객체 주소이므로 결국 주소 값을 비교하는 것이 된다.

## `null`과 `NullPionterException`

참조 타입 변수는 힙 영역의 객체를 참조하지 않는 뜻으로 `null`값을 가질 수 있다. null값도 초기값으로 사용할 수 있기 때문에 null로 초기화된 참조 변수는 스택 영역에 생성된다.

자바에서 프로그램 실행 도중 발생하는 오류를 Exception이라 한다. 참조 변수를 사용하면서 가장 많이 발생하는 오류로 **NullpointerExceptoin**이 있다. 이 예외는 참조 타입 변수를 잘못 사용하면 발생한다. 참조 변수가 null을 가지고 있으면 참조 타입 변수는 사용할 수 없다.

## String 타입

자바는 문자열을 String변수에 저장한다.

```java
String 변수;
변수 = "문자열";

String 변수2 = "문자열";
```

자바는 문자열 리터럴이 동일하다면 String 객체를 공유하도록 되어있다.

```java
String name1 = "Faker";
String name2 = "Faker";
```
name1과 name2는 동일한 문자열인 "Faker"를 참조하므로 동일한 String 객체를 공유하고 있다.

`new`를 이용하면 서로 다른 객체를 생성할 수 있다.
```java
String name1 = new String("Faker");
String name2 = new String("Faker");
```

이 경우에 name1과 name2는 다른 String 객체를 참조한다.
동일한 객체인지 비교할 때는 `==`와 `!=`로 비교하고, 문자열만을 비교할 때에는 String객체의 `equals()`메소드를 사용해야한다.

```java
boolean result = str1.equals(str2);
```

## 배열 타입

배열은 같은 타입의 데이터를 연속된 공간에 나열시키고, 각 데이터에 인덱스를 부여해 놓은 자료구조이다.

```java
타입[] 변수;
타입 변수[];
```

```java
데이터타입[] 변수 = {값0, 값1, ...};
```

여기서 주의할 점은 이미 배열 변수를 선언한 후에 다른 실행문에서 중괄호를 사용한 배열 생성은 허용되지 않는다.
```java
타입[] 변수;
변수 = {값0, 값1,...};// 컴파일에러
변수 = new 타입[] {값0, 값1,...};
```

값의 목록을 가지고 있지 않지만, 향후 값들을 저장할 배열을 미리 만들고 싶다면 new연산자로 생성시킬 수 있다.
```java
타입[] 변수 = new 타입[길이];
```
new연산자로 생성할 경우 자동적으로 기본값으로 초기화한다.

배열의 길이는 `배열변수.length()`로 구할 수 있다.

#### 다차원 배열

```java
int[][] scores = new int[2][3];
```

## 열거 타입(enumeration type)

```java
public enum 열거타입이름 {...}
```
```java
public enum Week {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, ...};
```
열거 상수는 열거 타입의 값으로 사용되는데, 관례적으로 열거 상수는 모두 대문자로 작성한다.

```java
Week today = Week.SUNDAY;
Week reservationDay = null;
```

## 참고

- [http://blog.breakingthat.com/2018/08/26/java-collection-map-weakhashmap/](http://blog.breakingthat.com/2018/08/26/java-collection-map-weakhashmap/)