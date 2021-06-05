# ITEM 34:  int 상수 대신 열거 타입을 사용해라

## 상수

일반적으로 불변의 값을 **상수**라고 부른다.(ex) 원주율, 지구의 무게, 둘레 등등
상수는 객체마다 저장할 필요가 없는 공용성을 띠고 있으며, 여러 가지 값으로 초기화될 수 없다.

```java
static final 타입 상수 [=초기값];
```
```java
static final 타입 상수;
static {
    상수 = 초기값;
}
```

이렇게 변하지 않는 값을 공통적으로 선언하고, 한군데서 관리하기 위해 사용한다.

## 정수 열거 패턴(int enum pattern)

자바에서 열거타입을 지원하기 이전(Java 1.5 이전)에는 정수 상수를 다음과 같이 한묶음에 선언해서 사용하고 했다.

```java
public static final int MONDAY      = 1;
public static final int TUESDAY   = 2;
public static final int WEDNSDAY  = 3;
```

정수 열거 패턴에는 수많은 단점이 있다. 

```java
public static final int APPLE_FUJI = 0;
public static final int APPLE_PIPPIN = 1;
public static final int APPLE_GRANNY_SMITH = 2;

public static final int ORANGE_NAVEL = 0;
public static final int ORANGE_TEMPLE = 1;
public static final int ORANGE_BLOOD = 2;
```

이때, 정수 열거 패턴을 위한 별도의 namespace를 지원하지 않기 때문에 어쩔수 없이 접두어를 사용해서 이름 충돌을 방지한다.

```java
APPLE_FUJI == ORANGE_NAVEL;
```

정수 열거 패턴은 위의 결과가 `true` 가 되기 때문에 **타입 안전성이 지켜지지 않으며, 표현력도 좋지 않다.**

또한, 평범한 상수를 나열한 것이기 때문에 컴파일시 그 값이 클라이언트 파일에 그대로 들어간다. 즉, 상수의 값이 바뀌면 클라이언트도 반드시 다시 컴파일 해줘야하는 단점이 있다. 

마지막으로, 정수 상수는 문자열로 출력하기가 어렵다. 그 값을 출력하거나 디버거로 살펴볼 때도, 의미가 아닌 숫자로만 보이며, 같은 정수 열거 그룹에 속한 상수가 몇개인지도 알 수 없다.

## 문자열 열거 패턴(string enum pattern)

```java
public static final String APPLE_FUJI                   = "apple fuji";
public static final String APPLE_PIPPIN                 = "apple pippin";
public static final String APPLE_GRANNY_SMITH   = "apple granny smith";
```

상수의 의미를 출력할 수 있다는 점은 좋지만, 오히려 더 나쁜 변형이다.
이렇게 하드코딩한 문자열에 오타가 있어도 컴파일러는 확인할 길이 없으며, 또한 문자열 비교에 따른 성능저하도 생긴다.

## 열거 타입(enumeration type)

자바는 열거 패턴의 단점을 없애고, 클래스의 장점을 가져오는 열거타입(enum type)을 제시했다.

```java
public enum 열거타입이름 {...}
```

```java
public enum Week {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, ...};
```

( *열거 타입은 일정 개수의 상수 값을 정의한 다음, 그 이외의 값은 허용하지 않는 타입* )

- 열거 타입 자체는 클래스이며, 상수 하나당 자신의 인스턴스를 하나씩 만들어 `public static final` 필드로 공개한다. 
- 열거 타입은 밖에서 접근할 수 있는 생성자를 제공하지 않으므로, 사실상 `final` 이다. 
- 즉, 클라이언트가 인스턴스를 직접 생성하거나 확장할 수 없으므로, 열거 타입 선언으로 만들어진 인스턴스들은 딱 한개씩만 존재한다.
    싱글턴은 원소가 하나뿐인 열거 타입이라 할 수 있고, 반대로 열거타입은 싱글턴을 일반화한 형태라고 볼 수 있다.
- 열거 타입은 컴파일타임에서의 타입 안전성을 제공한다.
    위의 예제에서 `Week` 열거 타입을 매개변수로 선언했다면, 건너받은 참조는 `null` 혹은 `Week` 의 값 중 한개임이 확실하다.
    이때, 다른 타입의 값을 넘기려고 하면 컴파일 오류가 발생한다.
- 각자의 이름공간이 있으며, 열거 타입에 새로운 상수를 추가하거나 순서를 바꾸더라도, 다시 컴파일하지 않아도 된다.
- 열거타입의 `toString`은 출력하기에 적합한 문자열을 제공한다.
- 열거타입에는 임의의 메서드나 필드를 추가할 수 있고, 임의의 인터페이스를 구현하게 할 수도 있다.

### 열거타입 예시

```java
public enum Planet {
    MERCURY(3.302e+23, 2.439e6),
    VENUS(4.869e+24, 6.052e6),
    EARTH(5.975e+24, 6.378e6);

    private final double mass;          // 질량
    private final double raduis;        // 반지름
    private final double surfaceGravity; // 표면중력

    private static final double G = 6.67300E-11;


    Planet(double mass, double raduis) {
        this.mass = mass;
        this.raduis = raduis;
        this.surfaceGravity = G * mass / (raduis * raduis);
    }

    public double mass() {
        return mass;
    }

    public double radius() {
        return raduis;
    }

    public double surfaceGravity() {
        return surfaceGravity;
    }

    public double surfaceWeight(double mass) {
        return mass * surfaceGravity; // F = ma
    }
}
```

열거 타입 상수 각각을 특정 데이터와 연결지으려면 생성자에 데이터를 받아 인스턴스 필드에 저장하면된다. 열거 타입은 근본적으로 불변이라 모든 필드는 `final` 이어야한다. 필드를 `public`으로 선언해도 되지만, `private`으로 두고 별도의 public 접근자 메서드를 두는 것이 낫다.

```java
public class WeightTable {
    public static void main(String[] args) {
        double earthWeight = Double.parseDouble("185");
        double mass = earthWeight / Planet.EARTH.surfaceGravity();
        for (Planet p : Planet.values()) {
            System.out.printf("%s에서의 무게는 %f이다.%n", p, p.surfaceWeight(mass) );
        }
    }
}
```

```
MERCURY에서의 무게는 69.912739이다.
VENUS에서의 무게는 167.434436이다.
EARTH에서의 무게는 185.000000이다.

Process finished with exit code 0
```

`toString` 메서드는 상수 이름을 문자열로 반환하는 것을 확인할 수 있다. 또한, 여기서 원래 상수에서 제거된 상수를 참조하는 곳에서는 컴파일 오류가 발생할 것이며, 이때 어떤 값에서 발생하는지 바로 알 수 있을 것이다.

열거타입에 선언한 클래스 혹은 그 패키지에서만 유용한 기능은 `private` 이나 `package-private` 메서드로 구현하면 된다.

### 상수별 메서드 구현

```java
public enum Operation {
    PLUS, MINUS, TIMES, DIVIDE;

    public double apply(double x, double y) {
        switch (this) {
            case PLUS:
                return x + y;
            case MINUS:
                return x - y;
            case TIMES:
                return x * y;
            case DIVIDE:
                return x / y;
        }
        throw new AssertionError("알 수 없는 연산: " + this);
    }
}
```

다음과 같이 사칙연산 계산기의 연산종류를 열거 타입으로 선언하고, 상수가 뜻하는 연산을 하는 `apply()` 메서드가 있다. 위 코드는 동작은 하지만, 좋은 방법은 아니다. 새로운 상수를 추가하면 해당 case 문도 추가해야하고, 혹시라도 깜빡한 경우, 컴파일은 되지만 `AssertionError` 오류가 발생된다.

```java
public enum Operation {
    PLUS    {public double apply(double x, double y){return x + y;}},
    MINUS   {public double apply(double x, double y){return x - y;}},
    TIMES   {public double apply(double x, double y){return x * y;}},
    DIVIDE  {public double apply(double x, double y){return x / y;}};

    public abstract double apply(double x, double y);
}
```

다음과 같이 `apply` 추상 메서드를 선언하고, 각 상수에 맞게 재정의 하는 방법이다.
이렇게 구현하면, 새로운 상수 추가시에도 `apply` 재정의 사시를 까먹기 어려울 것이며, 추상메서드를 재정의하지 않은 경우 컴파일 오류로 알려준다.

```java
public enum Operation {
    PLUS("+")    {public double apply(double x, double y){return x + y;}},
    MINUS("-")   {public double apply(double x, double y){return x - y;}},
    TIMES("*")   {public double apply(double x, double y){return x * y;}},
    DIVIDE("/")  {public double apply(double x, double y){return x / y;}};

    private final String symbol;

    Operation2(String symbol) {
        this.symbol = symbol;
    }
    @Override public String toString() {
        return symbol;
    }
    public abstract double apply(double x, double y);
}
```

상수별 메서드 구현을 상수별 데이터와 결합할 수도 있다. 

### valueOf

열거 타입에는 상수 이름을 입력받아 그 이름에 해당하는 상수를 반환해주는 `valueOf` 메서드가 자동으로 생성된다.

```java
Operation i = Operation.valueOf("PLUS");
System.out.println(i); // PLUS
```

### fromString

열거 타입의 `toString` 메서드를 재정의했다면, `toString` 이 반환하는 문자열을 해당 열거 타입 상수로 변환해주는 `fromString` 메서드도 함께 제공하는걸 고려해볼 수 있다.

```java
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public enum Operation {
    PLUS("+")    {public double apply(double x, double y){return x + y;}},
    MINUS("-")   {public double apply(double x, double y){return x - y;}},
    TIMES("*")   {public double apply(double x, double y){return x * y;}},
    DIVIDE("/")  {public double apply(double x, double y){return x / y;}};

    private final String symbol;

    Operation(String symbol) {
        this.symbol = symbol;
    }
    @Override public String toString() {
        return symbol;
    }
    public abstract double apply(double x, double y);

    // 열거 타입 상수 생성 후 정적 필드가 초기화될 때 추가됨.
    private static final Map<String, Operation> stringToEnum = Stream.of(values()).collect(Collectors.toMap(Object::toString, e->e));

    public static Optional<Operation> fromString(String symbol) {
        return Optional.ofNullable(stringToEnum.get(symbol)); // 주어진 연산이 가리키는 상수가 존재하지 않을 수 있음
    }
}

```

열거타입의 정적필드 중 생성자에서 접근할 수 있는 것은 상수 변수 뿐이다. 열거 타입 생성자가 실행되는 시점에는 정적 필드들이 초기화되기 전이라 자기 자신을 추가하지 못하도록 제약이 꼭 필요하다.

### 전략 열거 타입 패턴

```java
enum PayrollDay {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY;

    private static final int MINS_PER_SHIFT = 8 * 60;

    int pay(int minutesWorked, int payRate) {
        int basePay = minutesWorked * payRate;

        int overtimePay;
        switch (this) {
            case SATURDAY:
            case SUNDAY:
                overtimePay = basePay / 2;
                break;
            default:
                overtimePay = minutesWorked <= MINS_PER_SHIFT ? 0 : (minutesWorked - MINS_PER_SHIFT) * payRate / 2;
        }
        
        return basePay + overtimePay;
    }
    
}
```

다음과 같이 시간당 기본 임금과 그날 일한 시간이 주어지면 일당을 계산해주는 메서드를 갖고 있는 열거타입이다. 위 코드는 간결해보이지만, 관리하는데에 있어서는 위험한 코드이다. 새로운 값을 열거타입에 추가하고, 그 값을 처리하는 case문에도 반드시 넣어줘야하는 것이다. 만약 까먹고 case문에 추가를 안한 경우 휴일 수당을 받아야하는데 평일 수당을 받게되는 경우가 발생할 수도 있다.

```java
import static ch5.dahye.item34.PayrollDay.PayType.*;

enum PayrollDay {
    MONDAY(WEEKDAY), TUESDAY(WEEKDAY), WEDNESDAY(WEEKDAY), THURSDAY(WEEKDAY), FRIDAY(WEEKDAY), SATURDAY(WEEKEND), SUNDAY(WEEKEND);

    private final PayType payType;

    PayrollDay(PayType payType) {
        this.payType = payType;
    }

    int pay(int minutesWorked, int payRate) {
        return payType.pay(minutesWorked, payRate);
    }

    enum PayType {
        WEEKDAY {
          int overtimePay(int minsWorked, int payRate){
              return minsWorked <= MINS_PER_SHIFT ? 0 : (minsWorked - MINS_PER_SHIFT) * payRate / 2;
          }
        },
        WEEKEND {
            int overtimePay(int minsWorked, int payRate){
                return minsWorked * payRate / 2;
            }
        };

        abstract int overtimePay(int minsWorked, int payRate);
        private static final int MINS_PER_SHIFT = 8 * 60;

        public int pay(int minsWorked, int payRate){
            int basePay = minsWorked * payRate;
            return basePay + overtimePay(minsWorked, payRate);
        }
    }

}
```

이 방식은 잔업수당 계산을 `PayType` 전략 열거 타입에 위임하여, `switch` 문이나 상수별 메서드 구현이 필요 없게 된다. 이 패턴은 switch문보다 복잡하지만 더 안전하고 유연하다.



### Switch문이 적합한 경우

기존 열거 타입에 상수별 동작을 혼합해서 넣는 경우에는 `switch`문이 더 좋은 선택이 될 수 있다.

```java
public static Operation inverse(Operation op) {
  switch (op) {
    case PLUS:      return Operation.MINUS;
    case MINUS:     return Operation.PLUS;
        case TIMES:     return Operation.DIVIDE;
    case DIVIDE:    return Operation.TIMES;
    default: throw new AssertionError("알 수 없는 연산: " + this);
  }
}
```



## 결론

열거 타입은 정수상수와 성능이 비슷하다. 열거 타입을 메모리에 올리는 공간과 초기화하는 시간이 들긴 하지만 체감될 정도는 아니다.

열거타입은

1. 필요한 원소를 컴파일타임에 알 수 있는 상수 집합이라면 항상 열거 타입을 사용하자
2. 열거 타입에 정의된 상수 개수가 영원히 고정 불변일 필요는 없다.

