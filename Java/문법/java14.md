# 14. 람다식

**함수형 프로그래밍**은 병렬처리와 이벤트 지향 프로그래밍에 적합하기 때문에 부각되고있다. 자바는 함수적 프로그래밍을 위해 **람다식**을 도입했다.

**람다식은 익명 함수를 생성하기 위한 식으로 객체 지향 언어보다는 함수 지향 언어**에 가깝다. 

1. 자바 코드가 매우 간결 해짐
2. 컬렉션의 요소를 필터링하거나 매핑해 원하는 결과를 쉽게 집계할 수 있음

```
람다식 -> 매개변수를 가진 코드 블록 -> 익명구현객체
```

람다식의 형태는 매개 변수를 가진 코드 블록이지만, 런타임 시에 익명 구현 객체를 생성한다.

```java
Runnable runnable = new Runnable(){ //익명구현객체
    public void run(){...}
};
```

```java
Runnable runnable = () -> {...}; //람다식
```

람다식은 `(매개변수)->{실행코드}` 의 형태로 작성된다.



### 람다식 기본 문법

```java
(타입 매개변수, ...)->{실행문; ...}
```

- `(타입 매개변수, ...)` : 오른쪽 중괄호 {}를 실행하기 위해 필요한 값을 제공하는 역할, 매개변수 이름은 개발자가 자유롭게 줄 수 있다.
- `->` : 매개 변수를 이용해서 중괄호`{}` 를 실행

```java
(int a)->{System.out.println(a);}
```

매개 변수 타입은 런타임시에 대입되는 값에 따라 자동으로 인식될 수 있기 때문에 람다식에서는 매개 변수의 타입을 일반적으로 언급하지 않는다.

```java
(a)->{System.out.println(a);}
```

하나의 매개변수만 있다면 `()` 를 생략할 수 있고, 하나의 실행문만 있다면 `{}` 도 생략할 수 있다.

```java
a -> System.out.println(a);
```

만약 매개변수가 없다면 빈괄호`()` 를 반드시 사용해야한다.

```java
(x,y) -> { return x+y; }
```

실행문을 실행하고 결과값을 리턴해야한다면 위와 같이 return문으로 결과값을 지정할 수 있다.

```java
(x,y) -> x+y
```

만약 `{}` 에 return문만 있는 경우에는 위와 같이 return문을 사용하지 않고 작성할 수 있다.



### 타겟 타입과 함수적 인터페이스

```java
인터페이스 변수 = 람다식;
```

람다식은 인터페이스 변수에 대입된다. 즉, **람다식은 인터페이스의 익명 구현 객체를 생성**한다는 뜻이다. 인터페이스는 직접 객체화할 수 없기 때문에 **익명 구현 클래스를 생성하고 객체화**한다. 람다식은 대입될 인터페이스의 종류에 따라 작성법이 달라지기 때문에 **람다식이 대입될 인터페이스를 람다식의 타겟타입(target type)**이라 한다.

#### @FunctionallInterface 함수적 인터페이스

람다식이 하나의 메소드를 정의하기 때문에 두 개 이상의 추상 메소드가 선언된 인터페이스는 람다식을 이용해서 구현객체를 생성할 수 없다. 즉, **하나의 추상 메소드가 선언된 인터페이스만이 람다식의 타겟 타입**이 될 수 있으며, 이를 **함수적 인터페이스**라 한다. 인터페이스 선언시 `@FunctionallInterface` 어노테이션을 붙이면 컴파일러가 두 개 이상의 추상 메소드가 선언되지 않도록 체킹해준다. 

```java
@FunctionalInterface
public interface MyFunctionalInterface{
    public void methodA();
    public void methodB(); // 컴파일 오류
}
```

#### 매개 변수와 리턴값이 없는 람다식

```java
@FunctionalInterface
public interface MyFunctionalInterface{
    public void method();
}
```

```java
MyFunctionalInterface fi = ()->{...}
```

method()가 매개변수 값을 가지지 않기 때문에 람다식에서 매개변수가 없다.

```java
fi.method();
```

람다식이 대입된 인터페이스의 참조 변수는 위와 같이 method()를 호출할 수 있으며, 호출은 람다식의 `{...}` 를 실행시킨다.

#### 매개 변수가 있는 람다식

```java
@FunctionalInterface
public interface MyFunctionalInterface{
    public void method(int x);
}
```

```java
MyFunctionalInterface fi = (x)->{...}
MyFunctionalInterface fi = x -> {...}
```

```java
fi.method(5);
```



#### 리턴값이 있는 람다식

```java
@FunctionalInterface
public interface MyFunctionalInterface{
    public int method(int x, int y);
}
```

```java
MyFunctionalInterface fi = (x, y)->{ ... ; return 값; }
```

```java
MyFunctionalInterface fi = (x, y)->{ 
    return x + y;
}
MyFunctionalInterface fi = (x, y) -> x + y;
```

```java
int result = fi.method(2,5);
```



### 클래스 멤버와 로컬 변수 사용

람다식의 실행 블록에는 클래스의 멤버(필드, 메소드) 및 로컬 변수를 사용할 수 있다. 

#### 클래스 멤버 사용

클래스의 멤버인 필드와 메소드는 제약없이 사용할 수 있다. 하지만 **this** 키워드를 사용할 때는 주의가 필요하다.

일반적으로 익명 객체 내부에서 this는 익명 객체의 참조이지만, **람다식에서 this는 내부적으로 생성되는 람다식을 실행한 객체의 참조**이다.

```java
public interface MyFunctionalInterface{
    public void method();
}
```

```java
public class UsingThis{
	public int outterField = 10;
    
    class Inner{
        int innerField = 20;
        
        void method(){
            //람다식
            MyFunctionalInterface fi = ()->{
                // 바깥 객체의 참조를 얻기 위해서는 클래스명.this사용
				System.out.println("outterField : "+ UsingThis.this.outterField);
				// 람다식 내부에서 this는 Inner 객체를 잠조
                System.out.println("innerField : "+ this.innerField);
            };
            fi.method();
        }
    }
}
```

```java
public class UsingThisEx {
    public static void main(String... args){
        UsingThis usingThis = new UsingThis();
        UsignThis.Inner inner = usingThis.new Inner();
        inner.method();
    }
}
```



#### 로컬 변수 사용

람다식은 메소드 내부에서 주로 작성되므로 로컬 익명 구현 객체를 생성시킨다고 봐야한다. 람다식에서 바깥 클래스의 필드나 메소드는 제한 없이 사용할 수 있으나, **메소드의 매개변수 또는 로컬 변수를 사용하면 이 두 변수는 final 특성을 가져야한다.**

[[09. 중첩 클래스와 중첩 인터페이스 - 익명객체의 로컬 변수 사용](https://dh00023.gitbooks.io/java/%EB%AC%B8%EB%B2%95/java09.html) 를 참조]

매개 변수 또는 로컬 변수를 람다식에서 읽는 것은 허용되지만, 람다식 내부 또는 외부에서 변경할 수 없다.

```java
public interface MyFunctionalInterface{
    public void method();
}
```

```java
public class UsingLocalVariable{
	// arg는 final 특성
    void method(int arg){
        int localVar = 40; // localVal final 특성
        
        // final특성때문에 변경 불가
        // arg = 31;
        // localVal = 20;
        
        // 람다식
        MyFunctionalInterface fi = () -> {
            System.out.println("arg: " + arg);
            System.out.println("localVal: " + localVal);
        };
        fi.method();
    }
}
```



<!-- 14.5 표준 API의 함수적 인터페이스 이후로는 시간적 여유가 될때 공부 -->

