# ITEM 10: OBEY THE GENERAL CONTRACT WHEN OVERRIDING EQUALS

`equals`   메서드를 재정의는 여러가지 함정이 있다. 그러므로 **다음과 같은 상황에서는 재정의 하지 않는 것이 좋다**.

- 각 인스턴스가 본질적으로 고유한 경우( 동작하는 개체를 표현하는 클래스 ex-`Thread` )
- 인스턴스의 logical equality(논리적 동치성)를 검사할 일이 없는 경우
- 상위 클래스에서 재정의한 `equals`가 하위 클래스에도 적합한 경우(`AbstractSet`, `AbstractList`)
- 클래스가 private or package-private이고 `equals` 메서드를 호출할 일이 없는 경우



그렇다면 `equals` 를 재정의해야할 때는 언제일까?

**객체 식별성(두 객체가 물리적으로 같은지)이 아니라 논리적 동치성(logical equality)을 확인해야하지만, 상위 클래스의 `equals`가 재정의되지 않은 경우이다.** 주로, 값 클래스(`Integer`, `String`)가 해당된다. 

값 클래스이더라도 [정적 팩터리 메소드](./2021-01-12-static-factory-methods.md)라면 `equals`를 재정의하지 않아도 된다. (`Enum` 포함)

## equals 메서드 규약

`equals` 메서드는 동치관계(equivalence relation)를 구현하며, 다음을 만족한다.

| 규약                 | 설명                                                         |
| -------------------- | ------------------------------------------------------------ |
| 반사성(reflexivity)  | null이 아닌 모든 참조 값 x에 대해, `x.equals(x)`는 true이다. |
| 대치성(symmetry)     | null이 아닌 모든 참조 값 x,y에 대해, `x.equals(y)`가 true이면, `y.equals(x)`도 true이다. |
| 추이성(transitivity) | null이 아닌 모든 참조 값 x, y, z에 대해 `x.equals(y)`가 true이고 `y.equals(z)`가 true이면, `x.eqauls(z)`도 true이다. |
| 일관성(consistency)  | null이 아닌 모든 참조 값 x,y에 대해 `x.equals(y)`를 반복해서 호출하면 항상 true or flase를 반환한다. |
| null 아님            | null이 아닌 모든 참조 값 x에 대해, `x.equals`는 flase이다.   |

**`equals` 규약을 어기면 그 객체를 사용하는  다른 객체들이 어떻게 반응할지 알 수 없다.**

### 반사성

단순히 말하면 객체는 자기 자신과 같아야 한다는 뜻이다. 

### 대칭성

두 객체는 서로에 대한 동치여부에 대해 똑같은 결과가 나와야한다.

```java
public final class CaseInsensitiveString {

    private final String s;

    public CaseInsensitiveString(String s){
        this.s = Objects.requireNonNull(s);
    }

  	// 대칭성 위반
    @Override
    public boolean equals(Object o){
        if(o instanceof CaseInsensitiveString)
            return s.equalsIgnoreCase(((CaseInsensitiveString) o).s);
        if(o instanceof String)
            return s.equalsIgnoreCase((String) o);
        return false;
    }
}
```

```java
CaseInsensitiveString cis = new CaseInsensitiveString("Test");
String s = "test";

System.out.println(s.equals(cis)); // false
System.out.println(cis.equals(s)); // true
```

여기서 문제는 String의 equals는 `CaseInsensitiveString`의 존재를 모르기때문에 false를 반환하며, 이는 대칭성을 위반한다.

**equals 규약을 어기면, 그 객체를 사용하는 다른 객체들이 어떻게 반응할지 알 수 없다. ** 이러한 문제를 해결하려면 아래와 같이 String과의 연동을 하겠다는 목표를 버려야한다.

```java
@Override
public boolean equals(Object o){
		return o instanceof CaseInsensitiveString && ((CaseInsensitiveString) o).s.equalsIgnoreCase(s);
}
```

```java
CaseInsensitiveString cis = new CaseInsensitiveString("Test");
String s = "test";

System.out.println(s.equals(cis)); // false
System.out.println(cis.equals(s)); // false 
```

### 추이성

첫 번째 객체와 두 번째 객체가 같고, 두 번째 객체와 세 번째 객체가 같다면, 첫번째 객체와 세번째 객체도 같아야한다는 의미이다.

```java
public class Point {

    private final int x;
    private final int y;

    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o){
        if(!(o instanceof Point))
            return false;
        Point p = (Point)o;
        return p.x == x && p.y == y;
    }
}
```

```java
public class ColorPoint extends Point{
    private final String color;
    
    public ColorPoint(int x, int y, String color){
        super(x,y);
        this.color = color;
    }
}
```

`ColorPoint` 클래스에서 equals 메서드를 구현하지 않는다면, `Point` equals가 상속되어 색상 정보는 무시된 채 비교를 수행하게된다. 이때, 규약은 어긴 것은 아니지만, 중요한 정보를 놓치게 되므로 받아들일 수 없다.

```java
@Override
public boolean equals(Object o){
		if(!(o instanceof ColorPoint))
    		return false;
		return super.equals(o) && ((ColorPoint) o).color == color;
}
```

다음과 같이 equals를 구현하면 Point와 ColorPoint를 비교한 결과와 그 둘을 바꿔서 비교한 결과가 다를 수 있다. ( 대칭성 위배 )

```java
Point p = new Point(1,2);
ColorPoint cp = new ColorPoint(1,2, Color.RED);

System.out.println(p.equals(cp)); // true
System.out.println(cp.equals(p)); // false
```

우선 `p.equals(cp)` 는 색상 정보에 대한 비교는 무시하고, `cp.equals(p)`는 매개변수의 클래스 종류가 다르다며 매번 false만 반환할 것이다.

```java
		@Override
    public boolean equals(Object o){
        if(!(o instanceof Point))
            return false;
        if(!(o instanceof ColorPoint))
            return o.equals(this);
        return super.equals(o) && ((ColorPoint) o).color == color;
    }
```

```java
Point p = new Point(1,2);
ColorPoint cp = new ColorPoint(1,2, Color.RED);
ColorPoint cp2 = new ColorPoint(1,2,Color.BLACK);

System.out.println(cp.equals(p)); // true
System.out.println(p.equals(cp2)); // true 
System.out.println(cp2.equals(cp)); // false
```

다음과 같이 변경하면, 대칭성은 맞지만 추이성은 여전히 위배되며, **이 방식은 무한 재귀에 빠질 위험**도 있다. **구체 클래스를 확장해 새로운 값을 추가하면서 equals 규약을 만족시킬 방법은 존재하지 않는다.** 

`equals` 안의 instance 검사를 `getClass` 검사로 바꾸면 규약도 지키면서 상속이 가능하다고 생각할 수 있지만, 이는 리스코프 치환 원칙에 위반된다. 리스코프 치환 원칙에 따르면, 어떤 타입에 있어 중요한 속성이라면, 그 하위 타입에서도 마찬가지로 중요하다. 따라서 그 타입의 모든 메서드가 하위 타입에서도 똑같이 잘 동작해야한다. 

구체 클래스의 하위 클래스에서 값을 추가할 방법은 없지만 우회할 수 있는 방법이 하나있다. [상속대신 컴포지션을 사용해라 - [Item 18]()]

```java
public class ColorPoint {
    private final Color color;
    private final Point point;

    public ColorPoint(int x, int y, Color color){
        this.point = new Point(x,y);
        this.color = Objects.requireNonNull(color);
    }

		public Point asPoint(){
        return point;
    }
  
    @Override
    public boolean equals(Object o){
        if(!(o instanceof ColorPoint))
            return false;
        ColorPoint cp = (ColorPoint) o;
        return cp.point.equals(point) && cp.color.equals(cp);
    }

}
```

```java
Point p = new Point(1,2);
ColorPoint cp = new ColorPoint(1,2, Color.RED);
ColorPoint cp2 = new ColorPoint(1,2,Color.BLACK);

System.out.println(cp.equals(p)); // false
System.out.println(p.equals(cp2)); // false 
System.out.println(cp2.equals(cp)); // false
```

`Point` 를 상속하는 대신 `Point`를 `ColorPoint`의 private 필드로 두고,  `ColorPoint`와 같은 위치의 일반 `Point`를 반환하는 뷰를 public으로 추가하는 방식이다. 자바 라이브러리에서도 구체 클래스를 확장해 값을 추가한 클래스가 있다.

```java
public class Timestamp extends java.util.Date {

    /**
     * @serial
     */
    private int nanos;
  
  ...
}
```

`Timestamp`는 `Date`를 상속받은 후 nanos 필드를 추가했다. 그 결과 `Timestamp`의 equals는 대칭성을 위배해, Date 객체와 한 컬렉션에 넣거나 서로 섞어 사용하면, 엉뚱하게 동작할 수 있다. `Timestamp`의 API 설명에 주의사항을 언급하고 있다.



### 일관성

두 객체가 같다면 어느 하나 혹은 두 객체가 수정되지 않는 한 앞으로도 영원히 같아야 한다는 의미이다. 가변 객체는 비교 시점에 따라 서로 다를 수도 같을 수도 있는 반면, 불변 객체는 한번 다르면 끝까지 달라야한다. 즉, 불변 클래스를 만들기로 했다면 eqauls는 한번 같다고 한 객체와 영원히 같고, 한번 다른 객체와는 영원히 다르도록 만들어야한다.

- **클래스가 불변이든 가변이든 equals의 판단에 신뢰할 수 없는 자원이 끼어들게 해서는 안된다.**  (`java.net.URL` 의 equlas는 일관성을 어김)

### NULL-아님

모든 객체가 `null`과 같지 않아야한다. 실수로 `NullPointException`을 던지는 코드는 흔할 것이지만, 이 규약은 이러한 경우도 허용하지 않는다. 동치성 검사를 하려면 equals는 객체를 적절히 형변환한 후 필수 필드들의 값을 알아야하는데, 이때 형변환에 앞서 `instanceof` 연산자로 입력 매개변수가 올바른 타입인지 검사해야한다. `instanceof`의 첫번째 피연산자가 null이면 false를 반환하므로 묵시적인 null검사를 할 수 있다.

```java
		@Override
    public boolean equals(Object o){
        if(!(o instanseof MyType))
            return false;
        MyType mt = (Mytype) o;
```



## equals 구현 주의 사항

1. **`==` 연산자를 사용해 입력이 자기 자신의 참조인지 확인**
2. **`instanceof` 연산자로 입력이 올바른 타입인지 확인**
3. **입력을 올바른 타입으로 형변환 한다.**
4. **입력 객체와 자기 자신의 대응되는 '핵심' 필드들이 모두 일치하는지 하나씩 검사한다.**

이때, `float`, `double`을 제외한 기본 타입 필드는 `==`로 비교하고, 참조 타입 필드는 각각의 `equals` 메서드로,  `float`, `double`은 `Float.compare(float, float)`와 `Double.compare(double,double)`로 비교한다. `Float.equals`와 `Double.equals`는 오토박싱을 수반할 수 있어 성능상 좋지 않다.

때로는 null값도 정상 값으로 취급하는 참조 타입 필드도 있는데, 이때는 `Objects.equals(Object, Object)`로 비교해 `NullPointerException`을 예방해야한다.

또한, 어떤 필드를 먼저 비교하느냐가 equals의 성능을 좌우하기도 하는데, **최상의 성능을 위해서는 다를 가능성이 크거나 비교하는 비용이 싼 필드를 먼저 비교**하는 것이 좋다. 논리적 상태와 관련 없는 필드는 비교해서는 안되며, 핵심 필드로 계산할 수 있는 파생 필드도 굳이 비교할 필요는 없다. 하지만, 파생 필드가 객체 전체의 상태를 대표하는경우 파생필드를 비교하는 것이 더 빠를 수 있다.

-  **equals를 재정의할 때는 hashCode도 반드시 재정의 해야한다.([item 11]())**

- `Object` 외의 타입을 매겨변수로 받는 equals는 선언하지 말자.



<<<<<<< HEAD
[AutoValue 프레임워크](https://github.com/google/auto/tree/master/value)를 사용하면 `equals`와 `hashCode`를 작성해준다.
=======
[AutoValue 프레임워크](https://github.com/google/auto/tree/master/value)를 사용하면 `equals`와 `hashCode`를 작성해준다. ([AutoValue 예제 보기](../심화/2020-02-02-autoValue.md))
>>>>>>> java

### @AutoValue

```xml
<dependencies>
    <dependency>
        <groupId>com.google.auto.value</groupId>
        <artifactId>auto-value</artifactId>
        <version>1.3</version>
    </dependency>
</dependencies>
```

```java
import com.google.auto.value.AutoValue;
 
@AutoValue
public abstract class Product {
 
      public abstract String name();
      public abstract String price();
 
      @AutoValue.Builder
      public abstract static class Builder {
        public abstract Builder name(String name);
        public abstract Builder price(String price);
        public abstract Product build();
      }
 
      public static Product.Builder builder() {
        return new AutoValue_Product.Builder();
      }
}
```

