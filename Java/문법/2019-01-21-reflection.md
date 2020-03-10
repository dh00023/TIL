# Reflection

리플렉션은 구체적인 클래스 타입을 알지 못해도, 그 클래스의 메소드, 타입, 변수들을 접근할 수 있도록 해주는 자바API이다.

JVM에 로딩되어 있는 있는 클래스와 메소드 정보를 읽어 올 수 있다.

```java
public class Car{
    public void drive{
        // ....
    }
}
```

```java
public class Main{
    public static void main(String[] args){
        Object car = new Car();
        car.drive(); // 컴파일 에러
    }
}
```

Object 타입으로 Car클래스의 인스턴스를 생성할 수는 있지만 사용가능한 메소드는 Object의 변수들과 메소드들 뿐이기 때문에 컴파일 에러가 발생한다. 이러한 경우에 사용하는게 리플렉션이다.

자바 클래스 파일은 바이트 코드로 컴파일되어서 static 영역에 위치하게 된다. 그러므로 클래스 이름만 알고 있으면 언제든지 이 영역을 살펴 클래스 정보를 알 수 있다.

- ClassName
- Class Modifiers(public, private, synchronized)
- Package Info
- Superclass
- Implemented Interfaces
- Constructors
- MethodsFields
- Annotations

다음과 같은 정보들을 알 수 있다.

#### 참조페이지

-  <https://12bme.tistory.com/129> 
- https://brunch.co.kr/@kd4/8