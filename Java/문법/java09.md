# 09. 중첩 클래스와 중첩 인터페이스

## 중첩 클래스와 중첩 인터페이스란?

객체 지향 프로그램에서 클래스들은 서로 긴밀한 관계를 맺고 상호작용을 한다. 

클래스가 여러 클래스와 관계를 맺는 경우에는 독립적으로 선언하는 것이 좋으나, 특정 클래스와 관계를 맺을 경우에는 관계 클래스를 클래스 내부에 선언하는 것이 좋다.

**중첩 클래스**란 클래스 내부에 선언한 클래스를 말한다.

- 중첩 클래스를 사용하면 두 클래스의 멤버들을 서로 쉽게 접근할 수 있다.
- 외부에는 불 필요한 관계 클래스를 감춤으로서 코드의 복잡성을 줄일 수 있다.

```java
class ClassName{
    class NestedClassName{
    }
}
```

**중첩 인터페이스**는 클래스 내부에 선언한 인터페이스이다.

```java
class ClassName{
    interface NestedInterfaceName{
        
    }
}
```

중첩 인터페이스는 주로 UI 프로그래밍에서 이벤트를 처리할 목적으로 많이 활용된다.



### - 중첩 클래스

중첩 클래스는 클래스 내부에 선언되는 위치에 따라서 두 가지로 분류된다.

1. 멤버 클래스 : 클래스의 멤버로서 선언

   -  클래스나 객체가 사용 중이라면 언제든지 재사용 가능
   - 인스턴스 멤버 클래스 : A 객체를 생성해야만 사용할 수 있는 B 중첩 클래스

   ```java
   class A{
       class B{...}
   }
   ```

   - 정적 멤버 클래스 : A클래스로 바로 접근할 수 있는 B 중첩 클래스

   ```java
   class A{
       static class B{...}
   }
   ```

2. 로컬 클래스 : 메소드 내부에서 선언

   - 메소드 실행 시에만 사용되고, 메소드 실행이 종료되면 없어진다.

   ```java
   class A{
       void method(){
           class B{...}
       }
   }
   ```



멤버 클래스와 로컬 클래스도 하나의 클래스 이기 때문에 컴파일하면 바이트 코드 파일(`.class`)이 별도로 생성된다.

```
# 멤버 클래스
A&B.class

# 로컬 클래스
A$1B.class
```

#### 인스턴스 멤버 클래스

인스턴스 멤버 클래스는 **인스턴스 필드와 메소드만 선언이 가능**하고 **정적 필드와 메소드는 선언할 수 없다.**

```java
class A{
	/* 인스턴스 멤버 클래스 */
    class B{
        B(){}			// 생성자
        int field1;		// 인스턴스 필드
        void method1(){}// 인스턴스 메소드
        
        //static int field2;	정적 필드(X)
        //static void method(){}정적 메소드(X)
    }
}
```

A클래스 외부에서 인스턴스 멤버 클래스인 B를 생성하려면 먼저 A를 생성한 후 B를 생성해야한다.

```java
A a = new A();
A.B b = a.new B();
b.field1 = 3;
b.method1();
```

#### 정적 멤버 클래스

**static**키워드로 선언된 클래스를 말한다. 정적 멤버 클래스는 모든 종류의 필드와 메소드를 선언할 수 있다.

```java
class A{
    /* 정적 멤버 클래스 */
    static class C{
        C(){}					//생성자
        int field1;				//인스턴스 필드
        static int field2;		//정적 필드
        void method1(){}		//인스턴스 메소드
        static void method2(){}	//정적 메소드
    }
}
```

A클래스 외부에서 정적 멤버 클래스 C를 생성하기 위해서는 A를 생성할 필요가 없다.

```java
A.C c = new A.C();
c.field1 = 3;
c.method1();
A.C.field2 = 3;
A.C.method2();
```

#### 로컬 클래스

메소드 내에 선언된 클래스를 로컬(local) 클래스라고 한다. 로컬 클래스는 **접근 제한자(public, private) 및 static을 붙일 수 없다**. 로컬 클래스는 메소드 내부에서만 사용되므로 접근을 제한할 필요가 없기 때문이다.

로컬 클래스 내부에는 인스턴스 필드와 메소드만 선언이 가능하고 정적 필드와 메소드는 선언할 수 없다.

```java
void method(){
    /* 로컬 클래스 */
    class D{
        D(){}				//생성자
        int field1;			//인스턴스 필드
        void method1(){}	//인스턴스 메소드
    }
    D d = new D();
    d.field1 = 3;
    d.method1();
}
```

로컬 클래스는 메소드가 실행될 때 메소드 내에서 객체를 생성하고 사용해야한다. 주로 비동기 처리를 위해 스레드 객체를 만들 때 사용한다.



### - 중첩 클래스의 접근 제한

#### 바깥 필드와 메소드에서 사용 제한

멤버 클래스가 선언됨에 따라 바깥 클래스의 필드와 메소드에 사용 제한이 생긴다.

```java
public class A{
    // 인스턴스 필드
    B field1 = new B();			//=>(O)
    C field2 = new C();			//=>(O)
    
    // 인스턴스 메소드
    void method1(){
        B var1 = new B();		//=>(O)
        C var2 = new C();		//=>(O)
    }
    
    // 정적 필드 초기화
    static B field3 = new B();	//=>(X)
    static C field4 = new C();	//=>(O)
    
    // 정적 메소드
    static void method2(){
        B var1 = new B();		//=>(X)
        C var2 = new C();		//=>(O)
    }
    
    // 인스턴스 멤버 클래스
    class B{}
    // 정적 멤버 클래스
    static class C{}
}
```

인스턴스 멤버 클래스(B)는 바 깥 클래스의 인스턴스 필드의 초기값이나 인스턴스 메소드에서 객체를 생성할 수 있으나 정적 필드의 초기값이나 정적 메소드에서는 객체를 생성할 수 없다.

정적 멤버 클래스(C)는 모든 필드의 초기값이나 모든 메소드에서 객체를 생성할 수 있다.

#### 멤버 클래스에서 사용 제한

멤버 클래스 내부에서 바깥 클래스의 필드와 메소드를 접근할 때에도 제한이 따른다.

```java
class A{
    int field1;
    void method1(){...}
    
    static int field2;
    static void method2(){...}
    
    class B{
        void method(){
            field1 = 10; 	//=>(O)
            method1();		//=>(O)
            field2 = 10;	//=>(O)
            method2();		//=>(O)
        }
    }
}
```

인스턴스 멤버 클래스(B)안에서 바깥 클래스의 모든 필드와 메소드에 접근할 수 있다.

```java
class A{
    int field1;
    void method1(){...}
    
    static int field2;
    static void method2(){...}
    
    class C{
        void method(){
            field1 = 10; 	//=>(X)
            method1();		//=>(X)
            field2 = 10;	//=>(O)
            method2();		//=>(O)
        }
    }
}
```

정적 멤버 클래스(C)안에서는 바깥 클래스의 정적 필드와 메소드에만 접근할 수 있고, 인스턴스 필드와 메소드는 접근 할 수 없다.

#### 로컬 클래스에서 사용 제한

로컬 클래스 내부에서는 바깥 클래스의 필드나 메소드를 제한 없이 사용할 수 있다. 문제는 메소드의 매개 변수나 로컬 변수를 로컬 클래스에서 사용하는 경우이다. 로컬 클래스 객체는 메소드 실행이 끝나도 힙 메모리에 존재해서 계속 사용될 수 있다. 매개 변수나 로컬 변수는 메소드 실행이 끝나면 스택 메모리에서 사라지기 때문에 문제가 발생한다.

이 문제를 해결하기 위해 자바는 컴파일 시 로컬 클래스에서 사용하는 매개 변수나 로컬 변수의 값을 로컬 클래스 내부에 복사해 두고 사용한다. 값이 변경되면 로컬 클래스에 복사해 둔 값과 달라지는 문제를 해결하기 위해 매개 변수나 로컬 변수를 **final**로 선언해서 수정을 막는다.

즉, 로컬 클래스에서 사용 가능한 것은 **final**로 선언된 매개 변수와 로컬 변수이다. final 키워드가 있다면 로컬 클래스의 메소드 내부에 지역변수로 복사되지만, final 키워드가 없다면 로컬 클래스의 필드로 복사된다.

```java
void outMethod(final int arg1, int arg2){
    final int var1 = 1;
    int var2 = 2;
    class LocalClass{
        void method(){
            int result = arg1 + arg2 + var1 + var2;
        }
    }
}
```

```java
class LocalClass{
	// 필드로 복사
    int arg2 = 매개값;
    int var2 = 2;
    void method(){
        //로컬 변수로 복사
        int arg1 = 매개값;
        int var2 = 1;
        int result = arg1 + arg2 + var1 + var2;
    }
}
```

이런 로컬 클래스의 내부 복사 위치에 신경 쓸 필요 없이 **로컬 클래스에서 사용된 매개 변수와 로컬 변수는 모두 final 특성** 을 갖는 다는 것만 알면된다.

#### 중첩 클래스에서 바깥 클래스 참조 얻기

클래스 내부에서 **this**는 객체 자신의 참조이다. 중첩 클래스에서 **this**키워드를 사용하면 바깥 클래스의 객체 참조가 아니라, 중첩 클래스의 객체 참조가된다.

즉, **중첩 클래스 내부에서 `this.field`, `this.method()`로 호출하면 중첩 클래스의 필드와 메소드가 사용된다.**

중첩 클래스 내부에서 바깥 클래스의 객체 참조를 얻으려면 `바깥클래스.this`를 사용하면된다.

```
바깥클래스.this.필드;
바깥클래스.this.메소드();
```

```java
public class Outter{
    String field = "Outter-field";
    void method(){
        System.out.println("Outter-method");
    }
    
    class Nested{
        String field = "Nested-field";
        void method(){
            System.out.println("Nested-method");
        }
        void print)_{
            System.out.println(this.field);	//=>Nested-field
            this.method();					//=>Nested-method
            System.out.println(Outter.this.field);//=>Outter-field
            Outter.this.method();			//=>Outter-method
        }
    }
}
```

### - 중첩 인터페이스

중첩 인터페이스는 클래스의 멤버로 선언된 인터페이스를 말한다. 인터페이스를 클래스 내부에 선언하는 이유는 해당 클래스와 긴말한 관계를 맺는 구현 클래스를 만들기 위해서이다.

```java
class A{
    interface I{
        void method();
    }
}
```

UI 프로그래밍에서 이벤트를 처리할 목적으로 많이 활용된다. 

```java
public class Button{
    // 인터페이스 타입 필드
    OnClickListener listener;
    
    // 매개 변수의 다형성
    void setOnClikcListener(OnClickListenr listener){
        this.listener = listener;
    }
    
    void touch(){
        // 구현 객체의 onClick()메소드 호출
        listener.onClick();
    }
    
    // 중첩 인터페이스
    interface OnClickLister{
        void onClick();
    }
}
```

아무 객체를 받으면 안되고, Button 내부에 선언된 중첩 인터페이스를 구현한 객체만 받아야하는 것을 코드로 구현해 보았다.

```java
public class CallListener implements Button.OnClickListener{
    @Override
    public void onClick(){
        System.out.println("전화를 겁니다.");
    }
}
```

```java
public class MessageListener implements Button.OnClickListener{
    @Override
    public void onClick(){
        System.out.println("메세지를 보냅니다.");
    }
}
```

## 익명 객체

익명(anonymous) 객체는 **이름이 없는 객체**를 말한다. 익명 객체는 단독으로 생성할 수 없고 **클래스를 상속**하거나 **인터페이스를 구현**해야만 생성할 수 있다. 익명 객체는 필드의 초기값이나 로컬 변수의 초기값, 매개 변수의 매개 값으로 주로 대입된다.

 UI 이벤트 처리 객체나 스레드 객체를 간편하게 생성할 목적으로 익명 객체가 많이 활용된다.

#### 익명 자식 객체 생성

부모 타입으로 필드나 변수를 선언하고, 자식 객체를 초기값으로 대입하는 경우를 보자.

```java
class Child extends Parents{}		//자식 클래스 선언

class A{
    Parent field = new Child();		//필드에 자식 객체 대입
    void method(){
        Parent localVar = new Child();//로컬 변수에 자식 객체를 대입
    }
}
```

부모 클래스를 상속해서 자식 클래스를 선언하고, new연산자를 이용해 성성한 후, 필드나 로컬 변수에 대입하는 것이 기본이다.

하지만 자식 클래스가 재사용되지 않고, 오로지 해당 필드와 변수의 초기값으로만 사용할 경우라면 익명 자식 객체를 생성해서 초기값으로 대입하는 것이 좋은 방법이다.

```java
부모클래스 [필드|변수] = new 부모클래스(매개값, ...){
    //필드
    //메소드
};
```

`부모클래스(매개값,...){}`은 부모 클래스를 상속해서 {}와 같이 자식 클래스를 선언하라는 뜻이다. 이때 매개값은 부모 생성자의 매개 변수에 맞게 입력하면된다. 일반 클래스와의 차이점은 생성자를 선언할 수 없다는 것이다.

```java
// 필드의 초기값으로 익명 자식 객체 생성 대입
class A{
    Parent field = new Parent(){
        int childField;
        void childMethod(){}
        @Override
        void parentMethod(){}
    };
}
```

```java
// 메소드 내에서 로컬 변수 선언시 초기값으로 익명 자식객체 생성
class A{
    void method(){
        Parent localVar = new Parent(){
            int childField;
			void childMethod(){}
            @Override
            void parentMethod(){}
        }
    }
}
```

메소드의 매개값으로 익명 자식 객체를 대입한 것이다.

```java
class A{
    void method1(Parent parent){}
    
    void method2(){
        method1(
            new Parent(){
                int childField;
                void childMethod(){}
                @Override
                void parentMethod(){}
            }
        )
    }
}
```

**익명 자식 객체에 새롭게 정의된 필드와 메소드는 익명 자식 객체 내부에서만 사용되고, 외부에서는 필드와 메소드에 접근할 수 없다.**

#### 익명 구현 객체 생성

인터페이스 타입으로 필드나 변수를 선언하고, 구현 객체를 초기값으로 대입하는 경우이다.

```java
class TV implements RemoteControl{}

class A{
    RemoteControl field = new TV();
    void method(){
        RemoteControl localVar = new TV();
    }
}
```

위와 같이 구현 클래스를 선언하고, new연산자를 이용해 생성한 후, 필드나 로컬 변수에 대입하는 것이 기본이다.



구현 클래스가 재사용되지 않고, 오로지 해당 필드와 변수의 초기값으로만 사용되는 경우라면 익명 구현 객체를 초기값으로 대입하는 것이 좋다.

```java
인터페이스 [필드|변수] = new 인터페이스{
	//인터페이스에 선언된 추상 메소드의 실체 메소드 선언
    //필드
    //메소드
};
```

인터페이스에 선언된 모든 추상 메소드들의 실체메소드를 작성하지 않으면 컴파일 에러가 난다. 추가적으로 필드와 메소드를 선언할 수 있지만, 실체 메소드에서만 사용이 가능하고 외부에서는 사용하지 못한다.

```java
class A{
    // 클래스 A의 필드 선언
    RemoteControl field = new RemoteControl(){
		// RemoteControl 인터페이스의 추상메소드에 대한 실체 메소드
        @Override
        void turnOn(){}
    };
}
```

```java
void method(){
    //로컬 변수 선언
    RemoteControl localVar = new RemoteControl(){
        @Override
        void turnOn(){}
    };
}
```

```java
class A{
    void method1(RemoteControl rc){}
    
    void method2(){
        method1(
            //매개값으로 익명 구현객체 대입
            new RemoteControl(){
                @Override
                void turnOn(){}
            }
        );
    }
}
```

#### 익명 객체의 로컬 변수 사용

익명 객체 내부에서는 바깥 클래스의 필드나 메소드는 제한 없이 사용할 수 있다. 문제는 메소드의 매개 변수나 로컬 변수를 익명 객체에서 사용할 때이다. 메소드 내에서 생성된 익명 객체는 메소드 실행이 끝나도 힙 메모리에 존재해서 계속 사용할 수 있다. 하지만 매개 변수나 로컬 변수는 메소드 실행이 끝나면 스택 메모리에서 사라지기 때문에 익명 객체에서 사용할 수 없게 되므로 문제가 발생한다.

=> 위의 로컬 클래스에서 사용제한과 해결 방법이 같다. 단지 차이점은 클래스 이름의 존재 여부만 다를 뿐이다.

```java
public interface Calculatable{
    public int sum();
}
```

```java
public class Anonymous{
    private int field;
    public void method(final int arg1, int arg2){
        final int var1 = 0;
        int var2 = 0;
        
        field = 10;
        //arg1 = 20; (X)
        //arg2 = 20; (X)
        
        //var1 = 30; (X)
        //var2 = 30; (X)
        
        Calculatable calc = new Calculatable(){
            @Override
            public int sum()
            {
        		int result = field + arg1 + arg2 + var1 + var2;
                return result;
            }
        };
        System.out.println(calc.sum());
    }
}
```

```java
public class AnonymousEx{
    public static void main(String[] args){
        Anonymous anony = new Anonymous();
        anony.method(0,0);			//=>10
    }
}
```

