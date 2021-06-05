# ITEM 38 : 확장할 수 있는 열거타입이 필요하면 인터페이스를 사용해라

타입 안전 열거 패턴은 열거한 값들을 그대로 가져온 다음 다른 값을 더 추가하여 다른 목적으로 사용(확장)할 수 있는 반면, **열거 타입은 확장이 불가능**하다. 대부분 상황에서 열거 타입을 확장하는 것은 좋지 않은 아이디어이다.

- 확장한 타입의 원소는 기반 타입의 원소로 취급하지만, 반대는 성립하지 않는다.
- 기반 타입과 확장된 타입들의 원소 모두를 순회할 방법이 마땅하지 않다.
- 확장성을 높이기 위해 고려해야할 부분이 많다.

하지만, 확장할 수 있는 열거 타입이 어울리는 쓰임이 한개 있는데, 바로 **연산 코드(operation code or opcode)**이다. 기본 아이디어는 열거 타입이 임의의 인터페이스를 구현할 수 있는 사실을 이용하는 것이다.

```java
public interface Operation {
    double apply(double x, double y);
}
```

```java
public enum BasicOperation implements Operation {
    PLUS("+") {
        public double apply(double x, double y) {
            return x + y;
        }
    },
    MINUS("-") {
        public double apply(double x, double y) {
            return x - y;
        }
    },
    TIMES("*") {
        public double apply(double x, double y) {
            return x * y;
        }
    },
    DIVIDE("/") {
        public double apply(double x, double y) {
            return x / y;
        }
    };

    private final String symbol;

    BasicOperation(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String toString() {
        return symbol;
    }

}
```

열거 타입인 `BasicOperation`은 확장할 수 없지만 인터페이스인 `Operation`은 확장할 수 있고, 이 인터페이스를 연산 타입으로 사용하면 된다. 이렇게 `Operation`을 구현한 또 다른 열거 타입을 정의해 기본 타입을 대체할 수 있다.

```java
public enum ExtendedOperation implements Operation {
    EXP("^") {
        public double apply(double x, double y) {
            return Math.pow(x, y);
        }
    },
    REMAINDER("%") {
        public double apply(double x, double y) {
            return x % y;
        }
    };

    private final String symbol;

    ExtendedOperation(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String toString() {
        return symbol;
    }
}
```

`ExtendedOperation`은 지수 연산과 나머지 연산을 추가 구현한 것이며, 이때 `Operation` 인터페이스를 구현하여 작성해주면 된다. 새로 작성한 연산은 기존 연산을 쓰던 곳 어디든 사용할 수 있다.

즉, 정리하면 다음과 같다.

- 클라이언트는 인터페이스를 구현해 자신만의 열거 타입을 만들 수 있다.
- 기본 열거 타입의 인스턴스가 쓰이는 모든 곳에서 새로 확장한 열거타입의 인스턴스로 대체해 사용할 수 있다.
- 열거 타입은 기본적으로 `Enum` 클래스를 상속받기 때문에 추상 클래스를 상속 받을수 없다.

```java
public class ImplementsEnumTest {

    @Test
    void extendedOperationTest() {
        double x = 4.0;
        double y = 2.0;

        test(ExtendedOperation.class, x, y);
    }

    private static <T extends Enum<T> & Operation> void test(Class<T> opEnumType, double x, double y) {
        for (Operation op : opEnumType.getEnumConstants()) {
            System.out.printf("%f %s %f = %f%n", x, op, y, op.apply(x, y));
        }
    }
  
    private static void test2(Collection<? extends Operation> opSet, double x, double y) {
        for (Operation op : opSet) {
            System.out.printf("%f %s %f = %f%n", x, op, y, op.apply(x, y));
        }
    }
}
```

`private static <T extends Enum<T> & Operation> void test(Class<T> opEnumType, double x, double y)` 는 `ExtendedOperation`의 `class`리터럴을 넘겨 확장된 연산들이 무엇인지 알려준다. 여기서 `class` 리터럴은 한정적 타입 토큰 역할을 한다.
`<T extends Enum<T> & Operation>` 는 `Class` 객체가 열거 타입인 동시에, `Operation`의 하위 타입이여야된다는 의미이다.
`private static void test2(Collection<? extends Operation> opSet, double x, double y)` 는 `Class` 객체 대신 **한정적 와일드카드 타입**을 넘기는 방법이다. `test2`는 여러 구현 타입의 연산을 조합해 호출할 수 있게 되었으나, 특정 연산에서는 `EnumSet`과 `EnumMap`을 사용하지 못한다.

### 단점

인터페이스를 이용해 확장 가능한 열거타입을 구현하는 방법에는 **"열거 타입끼리 구현을 상속할수 없다"** 는 문제점이 있다.
이때, 확장한 Enum 타입끼리 많은 로직을 공유해야 한다면, 다음 방법으로 코드 중복을 없앨 수 있다.

1. 별도의 helper class 작성
2. static helper method로 분리
3. [디폴트 구현](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-13-prefer-interface.md) : 아무 상태에도 의존하지 않는 경우