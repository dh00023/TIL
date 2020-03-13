# 상속(Inheritance)

## 상속이란

부모 클래스(상위 클래스)는 자식 클래스(하위 클래스 or 파생 클래스)에게 자신의 멤버를 물려줄 수 있다.

![상속 이미지](http://cfile7.uf.tistory.com/image/99C59C3359A4ACE613577F)

상속은 이미 잘 개발된 클래스를 재사용해서 새로운 클래스를 만들기 때문에 **코드의 중복**을 줄여준다.

상속을 해도 부모 클래스의 모든 필드와 메소드들을 물려받는 것은 아니다. 부모 클래스에서 `private` 접근 제한을 갖는 필드와 메소드는 상속 대상에서 제외된다. 또한 부모 클래스와 자식 클래스가 다른 패키지에 존재한다면 `default` 접근 제한을 갖는 필드와 메소드도 상속 대상에서 제외된다.

상속을 이용하면 클래스의 수정을 최소화시킬 수도 있다. 부모 클래스의 수정으로 모든 자식 클래스들의 수정 효과를 가져오기 때문에 **유지 보수 시간**을 최소화 시켜준다.



## 클래스 상속(extends)

```java
class 자식클래스 extends 부모클래스{
    //필드
    //생성자
    //메소드
}
```

다른 언어와 달리 자바는 **다중 상속을 허용하지 않는다.**



## 부모 생성자 호출(Super)

자바에서 객체를 생성하면, 부모 객체가 먼저 생성되고 자식 객체가 그 다음에 생성된다.

모든 객체는 클래스의 생성자를 호출해야만 생성된다. 부모 객체도 예외는 아니다. 부모 생성자는 자식 생성자의 맨 첫 줄에서 호출된다.

```java
public DmbCellphone(){
    super(); // 부모의 기본 생성자 호출
}
```

예를 들어 부모 생성자가 명시적으로 선언되지 않았다면 컴파일러는 위와 같은 기본 생성자를 생성해낸다.

만약에 매개변수가 있는 생성자가 있다면 반드시 부모 생성자 호출을 위해 

```java
super(매개값, ...);
```

을 명시해줘야한다. 또한 반드시 자식 생성자 첫 줄에 위치해야한다.



## 메소드 재정의

부모 클래스의 모든 메소드가 자식 클래스가 사용하기에 적합하지 않을 수도 있다. 이때 상속된 일부 메소드는 자식 클래스에서 수정해서 사용해야한다. 자바는 **메소드 오버라이딩(Overriding)**을 제공한다.



### - `@Override`

메소드 오버라이딩은 상속된 메소드의 내용이 자식 클래스에 맞지 않을 경우, 자식 클래스에서 동일한 메소드를 재정의하는 것을 말한다. 메소드가 오버라이딩되었다면 자식 객체에서 메소드를 호출하면 오버라이딩된 자식 메소드가 호출된다.

1. 부모의 메소드와 동일한 시그너처(리턴 타입, 메소드 이름, 매개 변수 리스트)를 가져야한다.
2. 접근 제한을 더 강하게 오버라이딩 할 수 없다.
3. 새로운 예외를 throws할 수 없다.

### - `super`

자식 클래스 내부에서 오버라이딩된 부모 클래스의 메소드를 호출해야 하는 상황이 발생한다면 명시적으로 **super**키워드를 붙여서 부모 메소드를 호출할 수 있다.

```java
super.부모메소드();
```

##  final 클래스와 final 메소드

**final** 키워드는 클래스, 필드, 메소드 선언 시에 사용할 수 있다. **final 키워드는 해당 선언이 최종 상태이고, 결코 수정될 수 없음을 뜻한다.** 

필드 선언 시에 final이 지정되면 초기값 설정 후, 더 이상 값을 변경할 수 없다는 것이다.


### - 상속할 수 없는 final 클래스

final 클래스는 부모 클래스가 될 수 없어 자식 클래스를 만들 수 없다.

```java
public final class 클래스 {...}
```

대표적인 예는 자바 표준 API에서 제공하는 String 클래스이다.

### - 오버라이딩 할 수 없는 final 메소드

메소드 선언 시 final 키워드를 붙이게 되면 이 메소드는 최종적인 메소드이므로 오버라이딩(Overriding)할 수 없는 메소드가 된다.

```java
public final 리턴타입 메소드([매개변수,...]){...}
```


## protected 접근 제한자

| 접근 제한 | 적용할 내용          | 접근할 수 없는 클래스                          |
| --------- | -------------------- | ---------------------------------------------- |
| protected | 필드, 생성자, 메소드 | 자식 클래스가 아닌 다른 패키지에 소속된 클래스 |

protected는 public과 default 접근 제한의 중간쯤에 해당된다. default와 같이 같은 패키지에서는 접근 제한이 없지만 다른 패키지에서는 자식 클래스만 접근을 허용한다.

```java
package package1;

public class A{
    protected String field; //필드
    
    protected A(); // 생성자
    
    protected void method(){} //메소드
}
```

```java
package package1;

public class B{
    protected void method(){
        A a = new A(); 		// OK
        a.field = "value"; 	// OK
        a.method();			// OK
    } 
}
```

```java
package package2;
import package1.A;

public class C{
    protected void method(){
        A a = new A(); 		// NO
        a.field = "value"; 	// NO
        a.method();			// NO
    } 
}
```

```java
package package2;
import package1.A;

public class D extends A{
    protected void method(){
        A a = new A(); 		// OK
        a.field = "value"; 	// OK
        a.method();			// OK
    } 
}
```

## 타입 변환과 다형성

**다형성**은 같은 타입이지만 실행 결과가 다양한 객체를 이용할 수 있는 성질을 말한다. 다형성은 하나의 타입에 여러 객체를 대입함으로써 다양한 기능을 이용할 수 있도록 해준다. 다형성을 위해 부모 타입에 모든 자식 객체가 대입될 수 있다.

타입 변환이란 데이터 타입을 다른 데이터 타입으로 변환하는 행위를 말한다. 클래스 타입에서도 타입 변환이 있는데 이때 상속 관계에 있는 클래스 사이에서 발생한다.



### Promotion(자동 타입 변환)

프로그램 실행 도중에 자동적으로 타입 변환이 일어나는 것을 말한다.

```
부모 클래스 변수 = 자식클래스 타입;
```

자식클래스타입이 부모 클래스 타입으로 자동 타입 변환된다.

```java
class Animal{   
}
```

```java
class Cat extends Animal{
}
```

```java
Cat cat = new Cat();
Animal animal = cat;
```

여기서 cat과 animal은 변수 타입만 다를 뿐, 동일한 Cat객체를 참조한다.

```java
cat == animal // true
```

바로 위의 부모가 아니더라도 상속 계층에서 상위 타입이라면 자동 타입 변환이 일어날 수 있다.

```java
class A{}

class B extends A{}
class C extends A{}

class D extends B{}
class E extends C{}

public class PromotionExample{
    public static void main(String[] args){
        B b = new B();
        C c = new C();
        D d = new D();
        E e = new E();
        
        A a1 = b; // OK
        A a2 = c; // OK
        A a3 = d; // OK
        A a4 = e; // OK
        
        B b1 = d; // OK
        C c1 = e; // OK
        
        B b2 = e; // NO
        C c2 = d; // NO        
    }
}
```

부모 타입으로 자동 타입 변환된 이후에는 부모 클래스에 선언된 필드와 메소드만 접근이 가능하다. 비록 **변수는 자식 객체를 참조하지만 변수로 접근 가능한 멤버는 부모 클래스 멤버로만 한정**된다.

예외) **메소드가 자식 클래스에서 오버라이딩 되었다면 자식 클래스의 메소드가 호출**된다.

```java
public class Parent{
    public void method1(){
        System.out.println("Parent method1");
    }
    public void method2(){
        System.out.println("Parent method2");
    }
}
```

```java
public class Child extends Parent{
	@Override
    public void method2(){
        System.out.println("Child method2");
    }
	public void method3(){
        System.out.println("Child method3");
    }
}
```

```java
public class ChildExample{
    public static void main(String[] args){
        Child child =  new Child();
        
        Parent parent = child;  //자동 타입 변환
        parent.method1();
        parent.method2(); 		// 재정의된 메소드 호출
        parent.method3();		// 호출 불가능!
    }
}
```

```
// output
Parnet method1
Child method2
```


### 필드의 다형성

**다형성이란 동일한 타입을 사용하지만 다양한 결과가 나오는 성질**을 말한다.

필드의 값을 다양화함으로써 실행 결과가 다르게 나오도록 구현하는데, 필드의 타입은 변함이 없지만, 실행 도중에 어떤 객체를 필드로 저장하느냐에 따라 실행 결과가 달라질 수 있다. 이것이 필드의 다형성이다.

예를 들어 자동차 클래스에 포함된 타이어 클래스를 생각해보자. 자동차 클래스를 처음 설계할 때 사용한 타이어 객체는 언제든지 성능이 좋은 다른 타이어 객체로 교환할 수 있어야하며, 사용방법은 동일하지만 실행 결과는 더 우수하게 나와야한다. 이것을 프로그램으로 구현하기 위해서는 **상속, 오버라이딩, 타입 변환**을 이용한다.

```java
class Car{
    // field
    Tire frontLeftTire = new Tire();
	Tire frontRightTire = new Tire();
    Tire backLeftTire = new Tire();
    Tire backLeftTire = new Tire();
    
    // method
    void run(){}
}
```

```java
Car myCar = new Car();
myCar.frontRightTire = new HankookTire();	// 타이어 교체
myCar.backLeftTire = new KumhoTire();		// 타이어 교체
```

 여기서 frontRightTire와 backLeftTire는 원래 Tire 객체가 저장되어야하지만, Tire 자식 객체가 저장되어도 상관없다. 왜냐하면 자식 타입은 부모 타입으로 **자동 타입 변환**이 되기 때문이다. 또한 Tire 자식 객체가 저장되어도 Car객체는 Tire클래스에 선언된 필드와 메소드만 사용하므로 전혀 문제가 되지 않는다.

이와 같이 자동 타입 변환을 이용해서 Tire 필드값을 교체함으로써 다양한 실행 결과를 얻게 된다. 이것이 필드의 다형성이다.



### 하나의 배열로 객체 관리

```java
// field
Tire frontLeftTire = new Tire("앞왼쪽",6);
Tire frontRightTire = new Tire("앞오른쪽",2);
Tire backLeftTire = new Tire("뒤왼쪽",3);
Tire backRightTire = new Tire("뒤오른쪽",4);

// 배열
Tire[] tires = {
    new Tire("앞왼쪽",6),
	new Tire("앞오른쪽",2),
	new Tire("뒤왼쪽",3),
	new Tire("뒤오른쪽",4)
};
```

이렇게 배열로 관리했을 경우 인덱스로 표현되므로 제어문이나 대입에서 활용하기 쉽다.



### 매개 변수의 다형성

자동 타입 변환은 주로 메소드를 호출할 때 많이 발생한다. 메소드를 호출할 때에는 매개 변수의 타입과 동일한 매개값을 지정하는 것이 정석이지만, 매개값을 다양화하기 위해 매개 변수에 자식 타입 객체를 지정할 수도 있다.

```java
class Driver{
    void drive(Vehicld vehicle){
        vehicle.run();
    }
}
```

```java
Driver driver = new Driver();
Vehicle vehicle = new Vehicle();

Bus bus = new Bus(); //자식클래스
driver.drive(bus); // 자동타입변환 발생
```

```
Vehicle vehicle = bus;
```

자동으로 타입 변환이 발생한 것을 볼 수 있다.

**매개 변수의 타입이 클래스일 경우, 해당 클래스의 객체뿐만 아니라 자식 객체까지도 매개값으로 사용할 수 있다.** 매개값으로 어떤 자식 객체가 제공되느냐에 따라 메소드의 실행 결과는 다양해질 수 있다.(매개변수의 다형성) 자식 객체가 부모의 메소드를 재정의(오버라이딩)했다면 메소드 내부에서 오버라이딩된 메소드를 호출함으로써 메소드의 실행 결과는 다양해진다.



### Casting(강제 타입 변환)

casting은 부모 타입을 자식 타입으로 변환하는 것을 말한다. **자식 타입이 부모 타입으로 자동 변환한 후, 다시 자식 타입으로 변환할 때 강제 타입 변환을 사용할 수 있다**.

```java
자식클래스 변수 = (자식클래스) 부모클래스타입;
```

자식 타입이 부모 타입으로 자동 변환하면, **부모 타입에 선언된 필드와 메소드만 사용 가능하다는 제약 사항**이 따른다. 만약 자식 타입에 선언된 필드와 메소드를 꼭 사용해야 한다면 강제 타입 변환을 해서 다시 자식 타입으로 변환한 다음 자식 타입의 필드와 메소드를 사용하면된다.

```java
class Parent{
    String field1;
    void method1(){}
    void method2(){}
}
```

```java
class Child extends Parent{
    String field2;
    void method3(){}
}
```

```java
class ChildExample{
    public static void main(String[] args){
        Parent parent = new Child();
        parent.field1 = "xxx"; 	// OK
        parent.method1();		// OK
        parent.method2();		// OK

        parent.field2 = "xxx"; 	// NO
        parent.method3();		// NO
        
        Child child = (Child) parent;
        child.field2 = "yyy";	// OK
        child.method3();		// OK
    }
}
```



### instanceof(객체 타입 확인)

강제 타입 변환은 자식 타입이 부모 타입으로 변환되어 있는 상태에서만 가능하기 때문에 부모 타입의 변수가 부모 객체를 참조할 경우 자식 타입으로 변환할 수 없다.

```java
Parent parent = new Parent();
Child child = (Child) parent;	//불가능
```

어떤 객체가 어떤 클래스의 인스턴스인지 확인하려면 `instanceof` 연산자를 사용할 수 있다.

```java
boolean result = 좌항(객체) instanceof 우항(타입);
```

강제 타입 변환이 필요한 경우 반드시 매개값이 어떤 객체인지 확인하고 안전하게 강제타입 변환을 해야한다.

```java
public void method(Parent parent){
    if(parent instanceof Child){	// parent 매개변수가 참조하는 객체가 child인지 조사
        Child child = (Child) parent;
    }
}
```



## 7-8. 추상(abstract) 클래스

사전적 의미로 추상은 실체 간에 공통되는 특성을 추출한 것을 말한다.  예를 들어 새, 곤충, 물고기 등의 실체에서 공통되는 특성은 동물, 삼성, 현대,LG 등의 실체에서 공통되는 특성은 회사이다. 이때 동물과 회사는 추상적인 것이다.

클래스에서도 추상 클래스가 존재한다. **객체를 직접 생성할 수 있는 클래스를 실체 클래스**라고 한다면 **이 클래스들의 공통적인 특성을 추출해서 선언한 클래스를 추상 클래스**라고 한다. **추상 클래스(부모)와 실체 클래스(자식)는 상속의 관계를 갖는다.**

![](http://cfile29.uf.tistory.com/image/257B694D587582B62E50F1)



추상 클래스는 실체 클래스의 공통되는 필드와 메소드를 추출해서 만들었기 때문에 객체를 직접 생성해서 사용할 수 없다. 다시말해 추상 클래스는 new연산자를 사용해서 인스턴스를 생성하지 못한다.

```java
Animal animal = new Animal(); //불가능
```

```java
class Ant extends Animal{} 		//가능
```

- 용도
  - **실체 클래스들의 공통된 필드와 메소드의 이름을 통일할 목적**
  - **실체 클래스를 작성할 때 시간을 절약**



```java
public abstract class 클래스{
    //필드
    //생성자
    //메소드
}
```

추상 클래스를 선언할 때는 클래스 선언에 **abstract**키워드를 붙여야한다. 추상 클래스도 일반 클래스와 마찬가지로 필드, 생성자, 메소드를 선언할 수 있다. new연산자로 직접 생성자를 호출할 수는 없지만 자식 객체가 생성될 때 `super()`를 호출해서 추상 클래스 객체를 생성하므로 추상 클래스도 생성자가 반드시 있어야한다.

```java
public abstract class Phome{
    //필드
    public String owner;
    
    //생성자
    public Phone(String owner){
        this.owner = owner;
    }
    //메소드    
    public void turnOn(){
        System.out.println("폰 전원을 켭니다.");
    }
    public void turnOff(){
        System.out.println("폰 전원을 끕니다.");
    }
}
```

```java
public class SmartPhone extends Phone{
    public SmartPhone(String owner){
        super(owner);
    }
    public void internetSearch(){
        System.out.println("인터넷 검색을 합니다.");
    }
}
```

```java
public class PhoneExample{
    public static void main(String[] args){
        SmartPhone smartPhone = new SmartPhone("홍길동");
        
        smartPhone.turnOn();	//Phone의 메소드
    }
}
```



추상 클래스는 실체 클래스가 공통적으로 가져야 할 필드와 메소드들을 정의해 놓은 것이므로  실체 클래스의 멤버(필드, 메소드)를 통일화하는데 목적이 있다. 하지만 메소드의 선언만 통일화하고, 실행 내용은 실체 클래스마다 달라야하는 경우가 있다. 이런 경우를 위해서 추상 클래스는 **추상 메소드**를 선언할 수 있다. 추상 메소드는 추상 클래스에서만 선언할 수 있는데, 메소드의 선언부만 있고, 실행 내용인 `{}`가 없는 메소드를 말한다. 자식 클래스는 반드시 추상 메소드를 오버라이딩해서 실행 내용을 작성해야한다.

```java
[public | protected]abstract 리턴타입 메소드명(매개변수,...);
```

```java
public abstract class Animal{
    public String kind;
    public abstract void sound();
}
```

```java
public class Dog extends Animal{
    public Dog(){
        this.kind = "포유류";
    }
    
    @Override
    public void sound(){
        System.out.println("멍멍");
    }
}
```

