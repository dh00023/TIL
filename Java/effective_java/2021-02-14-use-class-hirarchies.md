# ITEM 23 : 태그 달린 클래스보다 클래스 계층구조를 활용해라

## 태그 달린 클래스 문제점

```java
class Figure {
    enum Shape { RECTANGLE, CIRCLE };
  
    // 태그 필드 
    final Shape shape;
  
    // shape가 RECTANGLE일때만 사용
    double length;
    double width;
  
    // shape이 CIRCLE 일때만 사용
    double radius;
  
    // 원용 생성자
    Figure(double radius){
        shape = Shape.CIRCLE;
        this.radius = radius;
    }
    
    // 사각형용 생성자
    Figure(double length, double width){
        shape = Shape.RECTANGLE;
        this.length = length;
        this.width = width;
    }
  
    double area() {
        switch(shape){
          case RECTANGLE:
              return length * width;
          case CIRCLE:
              return Math.PI * (radius * radius);
          default:
              throw new AssertionError(shape);
        }
    }
}
```

위 코드는 현재 모양을 나타내는 태그(shape)가 있는 클래스이다. 위와 같은 태그 달린 클레스는 단점이 많다.

1. 열거 타입 선언, 태그 필드, switch문 등 쓸데없는 코드가 많음
2. 여러 구현이 한 클래스에 혼합되어 있어 가독성이 나쁨
3. 다른 의미를 위한 코드도 있어, 메모리를 많이 사용
4. `final`로 필드를 선언하려면, 해당 의미에서 사용하지 않는 필드까지 생성자에서 초기화해야한다.
5. 다른 의미를 추가하려면 코드 수정이 필요
6. 인스턴스 타입만으로 현재 나태내는 의미를 알 길이 없다.

즉, **태그 달린 클래스는 장황하며, 오류를 내기 쉽고 비효율적**이다.

## 클래스 계층구조

1. 계층 구조의 루트가 될 추상 클래스 정의하고, 태그 값에 따라 동작이 달라지는 메서드들은 추상 메서드로 선언
2. 태그 값에 상관없이 동작이 일정한 메서드들은 일반 메서드로 추가
3. 모든 하위 클래스에서 공통으로 사용하는 데이터 필드도 루트 클래스에 추가
4. 루트 클래스를 확장한 구체 클래스를 의미별로 정의, 각 하위 클래스에 각자 의미에 해당하는 데이터 필드 추가
5. 루트 클래스가 정의한 추상 메서드를 하위 클래스에서 각자 의미에 맞게 구현

```java
abstract class Figure {
    abstract double area();
}
```

```java
class Circle extends Figure {
    final double radius;
    
    Circle(double radius){
        this.radius = radius;
    }
  
    @Override double area(){
        return Math.PI * (radius * radius);
    }
}
```

```java
class Ractangle extends Figure {
    final double length;
    final double width;
    
    Ractangle(double length, double width){
        this.length = length;
        this.width = width;
    }
  
    @Override double area(){
        return length * width;
    }
}
```

이렇게 클래스 계층구조를 활용해 구현하면, 태그 달린 클래스의 단점을 모두 해소할 수 있다. 또한, 타입 사이의 자연스러운 계층 관계를 반영하여 유연성은 물론 컴파일타임에 타입 검사 능력을 높여준다.