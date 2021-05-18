# ITEM 16: IN PUBLIC CLASSES, USE ACCESSOR METHODS, NOT PUBLIC FIELDS 

```java
class Point {
    public double x;
    public double y;
}
```

위 클래스는 아래 문제점들을 가지고 있다.

- 캡슐화 이점 제공하지 못함(데이터 필드에 직접 접근 가능)
- 내부 표현 변경시 API 수정 필요
- 불변식 보장 불가능
- 외부에서 필드에 접근할 때 부수 작업 수행 불가능

이러한 문제점들이 싫어 보통 아래와 같이 private 필드를  public 접근자로 접근하는 방법을 구현한다.

## 접근자 방식

```java
class Point{
    private double x;
    private double y;
    
    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }
    
    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }
    public void setX(double x){
        return this.x = x;
    }
    public void setY(double y){
        return this.y = y;
    }
}
```

패키지 바깥에서 접근할 수 있는 클래스라면 접근자를 제공하여 클래스 내부 표현 방식을 언제든 바꿀 수 있는 유연성이 있다. 그러므로 public 클래스에서 이 방식은 확실히 맞다.

하지만, **`package-private`, `private` 중첩 클래스의 경우 데이터 필드를 노출한다고 해도 그 클래스가 표현하려는 추상 개념만 올바르게 표현한다면 문제가 없다**. **접근자 방식보다 훨씬 깔끔하며, 패키지 바깥 코드 신경쓰지 않고 데이터 표현 방식을 바꿀 수 있다**.

## 불변 필드

```java
public final class Time {
    private static final int HOURS_PER_DAY = 24;
    private static final int MINUTES_PER_DAY = 60;
    
    public final int hour;
    public final int minute;
    
    public Time(int hour, int minute){
        if(hour < 0 || hour >= HOURS_PER_DAY){
            throw new IllegalArgumentException("시간 : "+ hour);
        }
        if(minute < 0 || minute >= MINUTES_PER_DAY){
            throw new IllegalArgumentException("분 : "+ hour);
        }
        this.hour = hour;
        this.minute = minute;
    }
}
```

다음과 같이 public 클래스의 필드가 불변이라면 불변식은 보장할 수 있게되어 직접 노출할 때의 **단점은 줄지만, 여전히 단점이 존재**한다.

- 내부 표현 변경시 API 수정 필요
- 필드를 읽을 때 부수 작업을 수행할 수 없다.

