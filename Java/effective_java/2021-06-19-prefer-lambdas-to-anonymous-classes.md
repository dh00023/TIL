# ITEM 42: 익명 클래스보다는 람다를 사용해라

## 익명 클래스를 이용한 함수 객체

```java
Collections.sort(words, new Comparator<String>() {
  	public int compare(String s1, String s2){
      	return Integer.compare(s1.length(), s2.length());
    }
});
```

위 예제는 문자열을 길이순으로 정렬하는데 있어서, 정렬을 위한 비교함수로 익명클래스를 사용한 예이다. 

- [전략 패턴](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/2020-03-21-strategy_pattern.md) 과 같이 함수 객체를 사용하는 객체 지향 디자인 패턴에는 익명 클래스면 충분
- 익명 클래스 방식은 코드가 너무 길기 때문에 함수형 프로그래밍에 적합하지 않음.

Java8 이후 추상 메서드가 1개인 인터페이스(함수형 인터페이스)들의 인스턴스를 람다를 사용해 만들 수 있게 되었다.

## Lambda expression

람다는 함수나 익명 클래스와 개념은 비슷하지만 **코드는 훨씬 간결**하다.

```java
Collections.sort(words, 
          (s1, s2) -> Integer.compare(s1.length(), s2.length()));
```

앞선 익명 클래스 예제를 람다로 변경해보니 훨씬 간결하며, 명확하게 표현되는 것을 볼 수 있다.
이때, 매개변수와 반환값 타입을 별도로 써주지 않아도, 컴파일러가 타입 추론을 통해서 타입을 결정할 수 있다. (상황에 따라 컴파일러가 타입 추론을 못하는 경우가 있는데, 그런 경우 직접 명시 필요)
**타입을 명시해야 코드가 더 명확한 경우를 제외하고는 람다의 모든 매개변수 타입은 생략하는 것이 좋다.** 

- 생성자 메서드

  ```java
  Collections.sort(words, comparingInt(String::length));
  ```
  
  람다 비교 자리에 생성 메서드를 사용하면 코드를 더 간결하게 만들 수 있다.
  
- `List` 인터페이스에 추가된 `sort` 메서드

    ```java
    words.sort(comparingInt(String::length));
    ```

[ITEM 34](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-06-05-use-enum-type.md#%EC%83%81%EC%88%98%EB%B3%84-%EB%A9%94%EC%84%9C%EB%93%9C-%EA%B5%AC%ED%98%84)에서 상수별 클래스 몸체를 구현하는 방식보다 열거 타입에 인스턴스 필드를 두는 편이 낫다면서 다음과 같이 `Operation` 열거타입을 구현했었다.

```java
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
}
```

여기서 람다를 이용하면 더 쉽게 구현할 수 있다.

```java
package ch7.dahye.item42;

import java.util.Map;
import java.util.Optional;
import java.util.function.DoubleBinaryOperator;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public enum Operation {
    PLUS("+", (x, y) -> x + y),
    MINUS("-", (x, y) -> x - y),
    TIMES("*", (x, y) -> x * y),
    DIVIDE("/", (x, y) -> x / y);

    private final String symbol;
    private final DoubleBinaryOperator op;
    Operation(String symbol, DoubleBinaryOperator op) {
        this.symbol = symbol;
        this.op = op;
    }

    @Override
    public String toString() {
        return symbol;
    }

    public double apply(double x, double y){
        return op.applyAsDouble(x, y);
    };
}
```

기존에 `apply` 추상메서드를 람다로 구현해 생성자에 넘기고, 생성자는 인스턴스 필드(op)로 람다를 저장해둔다. 그리고 나서 `apply` 메서드에서 필드에 저장된 람다를 호출하여 구현하면 더 깔끔하게 구현할 수 있다.

- `DoubleBinaryOperator`

    ```java
    @FunctionalInterface
    public interface DoubleBinaryOperator {
        /**
         * Applies this operator to the given operands.
         *
         * @param left the first operand
         * @param right the second operand
         * @return the operator result
         */
        double applyAsDouble(double left, double right);
    }
    ```

    `double` 타입 인수 2개를 받아 `double` 타입 결과를 돌려주는 인터페이스

람다로 기존 방식을 모두 대체해도 된다고 생각할 수 있다. 
하지만 **람다는 메서드,클래스와는 달리 이름이 없고 문서화도 못한다. 그러므로 코드 자체로 동작이 명확하게 설명되지 않거나 코드 줄 수 가 많아지면 람다를 쓰지 말아야한다.**

- 람다는 1~3줄 내로!
- 람다가 길거나 읽기 어렵다면 람다를 사용하지 않는 쪽으로 리팩터링

또한, 열거타입에서 생성자에 넘겨진 인수들의 타입은 컴파일 타임에 추론되기 때문에 열거 타입 생성자 안의 람다는 열거 타입 인스턴스 멤버에 접근할 수 없다. (인스턴스는 런타임에 만들어지기 때문)
**인스턴스 필드나 메서드를 사용해야만 하는 상황이면, 상수별 클래스 몸체를 사용**해야한다.



람다는 **함수형 인터페이스에서만 사용**된다.

- 추상 클래스의 인스턴스를 만드는 경우 익명 클래스 사용
- 추상 메서드가 여러개인 인터페이스의 인스턴스를 만드는 경우 익명 클래스 사용

마지막으로 **람다는 자기 자신을 참조할 수 없다.**

- 람다에서 `this`는 바깥 인스턴스
- 익명 클래스에서 `this`는 익명 클래스 인스턴스 자신

즉, 함수 객체가 자신을 참조해야 한다면 반드시 익명 클래스를 사용해야한다.



람다도 익명 클래스처럼 직렬화 형태가 구현별로 다를 수 있으므로, 람다를 직렬화 하는 것은 최대한 삼가해야한다.





