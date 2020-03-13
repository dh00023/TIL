# 인터페이스(interface)

## 인터페이스의 역할

자바에서 인터페이스는 **객체의 사용 방법을 정의**한 타입이다. 인터페이스는 **객체의 교환성을 높여주기 때문**에 다형성을 구현하는 매우 중요한 역할을 한다.

![인터페이스](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS16zVuL6TgZiFe-5Wh9cKUXbdE9Ptx7GODD28ddvuOPBQzfov5)

위의 사진과 같이 인터페이스는 개발코드와 객체가 서로 통신하는 접점 역할을 한다. 개발 코드가 인터페이스의 메소드를 호출하면 인터페이스는 객체의 메소드를 호출시킨다. 그렇기 때문에 개발 코드는 객체의 내부 구조를 알 필요가 없이 인터페이스의 메소드만 알고 있으면 된다.

인터페이스를 중간에 두는 이유는 **개발 코드를 수정하지 않고, 사용하는 객체를 변경할 수 있도록 하기 위해서**이다. 인터페이스는 하나의 객체가 아니라 여러 객체들과 사용이 가능하므로 어떤 객체를 사용하느냐에 따라서 실행 내용과 리턴 값이 다를 수 있다. 즉, **코드 변경 없이 실행 내용과 리턴값을 다양화**할 수 있는 장점이 있다.



## 인터페이스 선언

```java
[public] interface 인터페이스명{...}
```

인터페이스명을 작성하는 규칙은 클레스명을 작성하는 규칙과 같다.

`public` 접근 제한은 다른 패키지에서도 인터페이스를 사용할 수 있도록 해준다.

인터페이스는 **상수**와 **메소드**만을 수엄 멤버로 가진다. 인터페이스는 객체를 생성할 수 없기 때문에 생성자를 가질 수 없다.

```java
interface 인터페이스명{
    // 상수
    타입 상수명 = 값;
    // 추상 메소드
    타입 메소드명(매개변수,...);
    // 디폴트 메소드
    default 타입 메소드명(매개변수,..){}
    // 정적 메소드
    static 타입 메소드명(매개변수){...}
}
```

### Constant Field(상수 필드)

인터페이스는 객체 사용 설명서 이므로 런타임 시 데이터를 저장할 수 있는 필드를 선언할 수 없다. 그러나 상수 필드는 선언 가능하다. **상수를 선언할 때 반드시 초기값을 대입**해야한다.

```java
[public static final] 타입 상수명 = 값;
```

상수명은 대문자로 작성하되, 서로 다른 단어는 `_`로 연결하는 것이 관례이다. 

### Abstract Method(추상 메소드)

객체가 가지고 있는 메소드를 설명한 것으로 호출할 때 어떤 매개값이 필요하고, 리턴 타입이 무엇인지만 알려준다. 실제 실행부는 객체가 가지고 있다.

인터페이스에서 선언된 모든 추상 메소드는 **public abstract** 특성을 갖는다.

### Default Method(디폴트 메소드)

디폴트 메소드는 인터페이스에 선언되지만 사실 **객체가 가지고 있는 인스턴스 메소드라고 생각**해야한다. 자바8부터 사용가능.

```java
[public] default 리턴타입 메소드명(매개변수,...){...}
```

### Static Method(정적 메소드)

객체가 없어도 **인터페이스만으로도 호출 가능**하다. 자바8부터 사용 가능.

```java
[public] static 리턴타입 메소드명(매개변수,...){...}
```



## 인터페이스 구현

### 구현 클래스

객체는 인터페이스에서 정의된 추상 메소드와 동일한 메소드 이름, 매개 타입, 리턴 타입을 가진 실체 메소드를 가지고 있어야한다.

이러한 객체를 인터페이스 구현(implement) 객체라고 하며, 구현 객체를 생성하는 클래스를 구현 클래스라고 한다.

```java
public class 구현클래스명 implements 인터페이스명{
    //인터페이스에 선언된 추상 메소드의 실체 메소드 선언
}
```

인터페이스의 추상메소드의 실체 메소드를 작성할 때 주의할 점은 인터페이스의 모든 메소드는 기본적으로 **public** 접근 제한을 갖기 때문에 public보다 낮은 접근 제한으로 작성할 수 없다.

만약 인터페이스에 선언된 추상 메소드에 대응하는 실체 메소드를 구현 클래스가 작성하지 않으면 구현 클래스는 자동적으로 추상 클래스가 된다.

```java
public abstract class Television implements RemoteControl{
  	// 실체 메소드 없을경우
}
```

실체 메소드에 붙는 `@Override`는 인터페이스의 추상 메소드에 대한 정확한 실체 메소드인지 컴파일러가 체크하도록 지시하는 어노테이션이다.

인터페이스로 구현 객체를 사용하려면 인터페이스 변수를 선언하고 구현 객체를 대입해야한다. 인터페이스 변수는 참조 타입이기 때문에 구현 객체가 대입될 경우 구현 객체의 번지를 저장한다.

```java
인터페이스 변수;
변수 = 구현객체;

인터페이스 변수 = 구현객체;
```

### 익명 구현 객체

일회성의 구현 객체를 만들기 위해 소스파일을 만들고 클래스를 선언하는 것은 비효율적이다. 자바는 **소스 파일을 만들지 않고도 구현 객체를 만들 수 있는 익명 구현 객체**를 제공한다.

UI 프로그래밍에서 이벤트 처리, 임시 작업 스레드를 만들기 위해서 익명 구현 객체를 많이 사용한다.

```java
인터페이스 변수 = new 인터페이스(){
    //인터페이스에 선언된 추상 메소드의 실체 메소드 선언
}; 
```

여기서 끝에 `;`이 반드시 붙어야한다. 익명 구현 객체도 클래스로부터 생성되는데 자바컴파일러에 의해서 자동으로 생성된다. 이때 이름뒤에 $와 생성 번호가 붙는다.

```
ex) RemoteControlExample$1
```

### 다중 인터페이스 구현 클래스

![다중인터페이스](http://mblogthumb2.phinf.naver.net/20160523_165/mals93_1463934197436hawyV_JPEG/dinterface.jpg?type=w800)

객체는 다음과 같이 다수의 인터페이스 타입으로 사용할 수 있다.

```java
public class 구현클래스명 implements 인터페이스A, 인터페이스B{
    //인터페이스A에 선언된 추상 메소드의 실체 메소드 선언
    //인터페이스B에 선언된 추상 메소드의 실체 메소드 선언
}
```

구현 클래스는 모든 인터페이스의 추상 메소드에 대해 실체 메소드를 작성해야한다. 만약 하나라도 없으면 추상 클래스로 선언해야한다.

## 인터페이스 사용

인터페이스로 구현 객체를 사용하려면 인터페이스 변수를 선언하고 구현 객체를 대입해야한다. 인터페이스 변수는 참조 타입이기 때문에 구현 객체가 대입될 경우 구현 객체의 번지를 저장한다.

```java
인터페이스 변수;
변수 = 구현객체;

인터페이스 변수 = 구현객체;
```

인터페이스는 클래스의 필드, 생성자 또는 메소드의 매개 변수, 생성자, 메소드의 로컬 변수로 선언될 수 있다.

```java
public class MyClass{
    // Field
    RemoteControl rc = new Television();
    
    // Constructor
    MyClass(RemoteControl rc){
        this.rc = rc;
    }
    //=> MyClass mc = new MyClass(new Television());
    
    //Method
    void methodA(){
        // local variable
        RemoteControl rc = new Audio();
    }
    
    void methodB(RemoteControl rc){...}
    //=> mc.methodB(new Audio());
}
```



## 타입 변환과 다형성

요즘은 상속보다는 인터페이스를 통해서 다형성을 구현하는 경우가 더 많다. **다형성은 하나의 타입에 대입되는 객체에 따라서 실행 결과가 다양한 형태로 나오는 성질**을 말한다. 인터페이스 타입에 어떤 구현 객체를 대입하느냐에 따라 실행 결과가 달라진다.

**상속은 같은 종류의 하위 클래스**를 만드는 기술이고, **인터페이스는 사용 방법이 동일한 클래스**를 만드는 만드는 기술이라는 개념적 차이는 있지만 둘 다 다형성을 구현하는 기술이다.

인터페이스를 사용해 메소드를 호출하도록 코딩을 했다면, 구현 객체를 교체하는 것은 매우 손쉽고 빠르게 할 수 있다. 프로그램 소스 코드는 변함이 없는데, 구현 객체를 교체함으로써 프로그램의 실행 결과가 다양해진다. 이것이 인터페이스의 다형성이다.

인터페이스 타입으로 매개 변수를 선언하면 메소드 호출 시 매개값으로 여러 가지 종류의 구현 객체를 줄 수 있기 때문에 메소드 실행 결과가 다양하게 나온다. 이것이 인터페이스 매개 변수의 다형성이다.

### 자동타입변환(Promotion)

구현 객체가 인터페이스 타입으로 변환되는 것은 자동 타입 변환에 해당한다.

```java
인터페이스 변수 = 구현객체;
```

인터페이스 구현 클래스를 상속해서 자식 클래스를 만들었다면 자식 객체 역시 인터페이스 타입으로 자동 타입 변환시킬 수 있다. 자동타입변환을 이용하면 필드의 다형성과 매개 변수의 다형성을 구현할 수 있다.

#### 필드의 다형성

```java
public interface Tire{
    public void roll();
}
```

```java
public class HankookTire implements Trie{
    @Override
    public void roll(){
        System.out.println("한국 타이어가 굴러갑니다.");
    }
}
```

```java
public class KumhoTire implements Trie{
    @Override
    public void roll(){
        System.out.println("금호 타이어가 굴러갑니다.");
    }
}
```

```java
public class Car{
    //인터페이스 타입 필드 선언과 초기 구현 객체 대입
    Tire frontLeftTire = new HankookTire();
    Tire frontRighttTire = new HankookTire();
    Tire backLeftTire = new HankookTire();
    Tire backRightTire = new HankookTire();
    
    //인터페이스에서 설명된 roll() 메소드 호출
    void run(){
		frontLeftTire.roll();
        frontRightTire.roll();
        backLeftTire.roll();
        backRightTire.roll();
    }
}
```

```java
public class CarExample{
    public static void main(String[] args){
        Car myCar = new Car();
        
        myCar.run();
        
        myCar.frontLeftTire = new KumhoTire();
        myCar.frontRightTire = new KumhoTire();
        
        myCar.run();
    }
}
```

#### 인터페이스 배열로 구현 객체 관리

```java
Tire[] tires = {
    new HankookTire(),
    new HankookTire(),
	new HankookTire(),
    new HankookTire()
};
```

```java
tires[1] = new KumhoTire();
```

tires 배열의 각 항목은 Tire 인터페이스 타입이므로 구현객체를 대입하면 자동타입 변환이 발생하기 때문에 아무런 문제가 없다.

```java
void run(){
    for(Tire tire : tires){
        tire.roll();
    }
}
```

위와 같이 for문으로 작성할 수 있다.

#### 매개 변수의 다형성

매개 변수를 인터페이스 타입으로 선언하고 호출할 때에는 구현 객체를 대입한다.

```java
public class Driver{
    public void drive(Vehicle vehicle){
        vehicle.run();
    }
}
```

```java
public interface Vehicle{
    public void run();
}
```

```java
public class Bus implements Vehicle{
    @Override
    public void run(){
        System.out.println("버스가 달립니다.");
    }
}
```

```java
public class Taxi implements Vehicle{
    @Override
    public void run(){
        System.out.println("택시가 달립니다.");
    }
}
```

```java
public class DriverExample{
    public static void main(String[] args){
        Driver driver = new Driver();
        
        Bus bus = new Bus();
        Taxi taxi = new Taxi();
        
        driver.drive(taxi); // 자동타입변환
        driver.drive(bus); 	// 자동타입변환
    }
}
```

### 강제타입변환(Casting)

강제 타입 변환을 해서 구현 클래스 타입으로 변환한 다음에 구현 클래스의 필드와 메소드를 사용할 수 있다.

```java
구현클래스 변수 = (구현클래스) 인터페이스변수;
```

```java
public interface Vehicle{
    public void run();
}
```

```java
public class Bus implements Vehicle{
    @Override
    public void run(){
        System.out.println("버스가 달립니다.");
    }
    
    public void checkFare(){
        System.out.println("승차요금을 확인합니다.");
    }
}
```

```java
public class VehicleExample{
    public static void main(String[] args){
        Vehicle vehicle = new Bus();
        
        vehicle.run(); 			//OK
        vehicle.checkFare();	//NO Vehicle 인터페이스에는 checkFare()가 없다.
        
        Bus bus = (Bus) vehicle; //강제타입변환
        bus.checkFare();		//OK
    }
}
```

### 객체 타입 확인(instanceof)

```java
if(vehicle instanceof Bus){
    Bus bus = (Bus) vehicle;
}
```

vehicle인터페이스 타입으로 변환된 객체가 Bus인지 확인한 것이다.

강제 타입 변환을 한다면 반드시 매개 값이 어떤 객체인지 instanceof 연산자로 확인하고 안전하게 강제 타입 변환을 해야한다.

## 인터페이스 상속

인터페이스도 다른 인터페이스를 상속할 수 있다. 이때 클래스와는 달리 **다중 상속**을 허용한다.

```java
public interface 하위인터페이스 extends 상위인터페이스1, 상위인터페이스2{...}
```

하위 인터페이스를 구현하는 클래슨느 하위 인터페이스의 메소드 뿐만아니라 상위 인터페이스의 모든 추상 메소드에 대한 실체 메소드를 가지고 있어야한다.

```java
하위인터페이스 변수 = new 구현클래스(...);
싱위인터페이스1 변수 = new 구현클래스(...);
상위인터페이스2 변수 = new 구현클래스(...);
```

하위인터페이스로 타입 변환이 되면 상,하위 인터페이스에 선언된 모든 메소드를 사용할 수 있으나, 상위 인터페이스로 타입 변환되면 상위 인터페이스에 선언된 메소드만 사용가능하다.



## 디폴트 메소드와 인터페이스 확장

인터페이스에서 디폴트 메소드를 허용한 이유는 기존 인터페이스를 확장해서 새로운 기능을 추가하기 위해서이다. 기존 인터페이스의 이름과 추상 메소드의 변경 없이 디폴트 메소드만 추가할 수 있기 때문에 이전에 개발한 구현 클래스를 그대로 사용할 수 있으면서 새롭게 개발하는 클래스는 디폴트 메소드를 활용할 수 있다.

```java
public interface MyInterface{
    public void method1();
}
```

```java
public class MyclassA implements MyInterface{
    @Override
    public void method1(){
        System.out.println("myclassA method1실행");
    }
}
```

```java
public interface MyInterface{
    public void method1();
    
    //디폴트메소드 추가
    public default void method2(){
        System.out.println("myinterface- method2실행");
    }
}
```

인터페이스를 수정해도 디폴트 메소드를 생성했기때문에 MyclassA에서 컴파일에러가 발생하지 않는다.

```java
public class MyclassB implements MyInterface{
    @Override
    public void method1(){
        System.out.println("myclassB method1실행");
    }
    //디폴트 메소드 재정의
    @Override
    public void method2(){
        System.out.println("myclassB method2실행");
    }
}
```

```java
public class DefaultExample{
    public static void main(String[] args){
        MyInterface mi1 = new MyclassA();
        mi1.method1();	//=>myclassA method1실행
        mi1.method2();	//=>myinterface- method2실행
        
        MyInterface mi2 = new MyclassB();
        mi2.method1();	//=>myclassB method1실행
        mi2.method2();	//=>myclassB- method2실행
    }
}
```

### 디폴트 메소드가 있는 인터페이스 상속

1. 디폴트 메소드를 단순히 상속만 받는다.
2. 디폴드 메소드를 재정의(override)해서 실행 내용을 변경한다.
3. 디폴트 메소드를 추상 메소드로 재선언한다.

