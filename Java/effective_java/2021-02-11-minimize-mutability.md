# ITEM 17: MINIMIZE MUTABILITY

불변 클래스란 그 인스턴스의 내부 값을 수정할 수 없는 클래스이다. 불변 인스턴스 정보는 고정되어 객체가 파괴되는 순간까지 절대 달라지지 않는다. 

- 자바 플랫폼 라이브러리 불변클래스 : `String`, 기본 타입의 박싱된 클래스들, `BigInteger`, `BigDecimal`

불변 클래스는 가변 클래스보다 설계, 구현, 사용이 쉬우며 오류가 생길 여지도 적고 훨씬 안전하다.

1. 객체의 상태를 변경하는 메서드(변경자)를 제공하지 않는다.
2. 클래스를 확장할 수 없도록 한다.
3. 모든 필드를 final로 선언한다.
4. 모든 필드를 private로 선언한다. 
5. 자신 외에는 내부 가변 컴포넌트에 접근할 수 없도록 한다.(방어적 복사)

```java

public final class Complex {
    private final double re;
    private final double im;

    public Complex(double re, double im){
        this.re = re;
        this.im = im;
    }

    public double realPart() {
        return re;
    }

    public double imaginaryPart(){
        return im;
    }

    public Complex plus(Complex c){
        return new Complex(re+c.re, im+c.im);
    }

    public Complex minus(Complex c){
        return new Complex(re-c.re, im-c.im);
    }

    public Complex times(Complex c){
        return new Complex(re*c.re - im*c.im, re*c.im + im*c.re);
    }

    public Complex divdedBy(Complex c){
        double tmp = c.re*c.re+c.im*c.im;
        return new Complex((re*c.re + im*c.im)/tmp,(im*c.re-re*c.im)/tmp);
    }

    @Override public boolean equals(Object o){
        if(o == this) return true;
        if(!(o instanceof Complex)) return false;
        Complex c = (Complex) o;

        return Double.compare(c.re, re) == 0 && Double.compare(c.im, im) == 0;
    }

    @Override
    public int hashCode(){
        return 31 * Double.hashCode(re) + Double.hashCode(im);
    }

    @Override
    public String toString(){
        return "("+re+" + "+im+"i)";
    }
}
```

여기서 사칙연산 메서드는 인스턴스 자신은 수정하지 않고 새로운 Complex 인스턴스를 만들어 반환하고 있다.  피연산자에 함수를 적용해 결과를 반환하지만, 피연산자 자체는 그대로인 프로그래밍 패턴을 함수형 프로그래밍이라한다. 또한 메서드 이름을 전치사로 사용하였으며, 이는 메서드가 객체값을 변경하지 않는다는 사실을 강조한 것이다. (단, `BigInteger`와 `BigDecimal`은 이 명명 규칙을 따르고 있지 않음)

- **불변 객체는 근본적으로 thread safe하므로 따로 동기화할 필요가 없다**. 불변 객체는 다른 스레드에 영향을 줄 수 없으므로, 안심하고 공유할 수 있다. 그러므로, 불변 클래스는 한번 만든 인스턴스를 최대한 재활용 하는 것을 권장한다. 

  ```java
  public static final Complex ZERO = new Complex(0,0);
  public static final Complex ONE = new Complex(1,0);
  public static final Complex I = new Complex(0,1);
  ```

  다음과 같이 자주 쓰이는 값들을 상수로 제공하면 쉽게 재활용할 수 있다.

  불변 클래스는 자주 사용되는 인스턴스를 캐싱하여 같은 인스턴스를 중복 생성하지 않도록 [정적 팩터리](./2021-01-12-static-factory-methods.md)를 제공할 수 있으며, 박싱된 기본 타입 클래스 전부와 `BigInteger`가 여기에 속한다. 정적 팩터리를 사용하면 여러 클라이언트가 인스턴스를 공유해 메모리 사용량과 가비지 컬렉션 비용이 줄어든다.

  불변 객체는 복사 자체가 의미 없어, [방어적 복사(item 50)]()도 필요 없으며,  `clone()`이나 [복사 생성자(item13)](./2021-02-03-overriding-clone-judiciously.md)를 제공하지 않는것이 좋다.

- **불변 객체는 자유롭게 공유할 수 있으며, 불변 객체끼리는 내부 데이터를 공유할 수 있다.**

- **객체 생성시 다른 불변 객체들을 구성요소로 사용하면 이점이 많다.** 예를 들면, Map의 Key와 Set의 원소로 쓰기에 좋다. 

- **불변 객체는 그 자체로 실패 원자성을 제공한다.([item 76]())**

  - 실패 원자성 : 메서드에서 예외가 발생한 후에도 그 객체는 메서드 호출전과 동일한 유효한 상태여야한다.

불변 클래스에도 단점이 있다. **값이 다르면 반드시 독립된 객체로 만들어야 한다는 것**이다. 값의 수가 많다면, 이들을 모두 만드는데 큰 비용이 든다. 이는 원하는 객체를 완성하기까지 단계가 많고, 그 중간 단계에서 만든 객체들이 모두 버려진다면 성능 문제는 더 커진다.

- 다단계 연산들을 예측해 기본 기능으로 제공
- `package-private`의 가변 동반 클래스로 제공
  - 대표적인 예로 `String`, `StringBuffer` 



클래스가 불변임을 보장하려면 자신을 상속하지 못하게 해야하는데 가장 쉬운 방법은 `final` 클래스이지만, 모든 생성자를 `private`, `package-private`로 구현하고 public 정적 팩터리를 제공하는 방법이다.

```java

public final class Complex {
    private final double re;
    private final double im;
    

    private Complex(double re, double im){
        this.re = re;
        this.im = im;
    }
    
    public static Complex valueOf(double re, double im){
        return new Complex(re, im);
    }
  ...
}
```

패키지 바깥의 클라이언트가 볼때 이 불변객체는 사실상 public,  protected 생성자가 없어 final 클래스와 같다. 정적 팩터리 방식은 다수의 구현 클래스를 활용한 유연성을 제공하고, 이에 더해 다음 릴리즈에서 객체 캐싱 기능을 추가해 성능을 끌어올릴 수도 있다.

신뢰할 수 없는 하위 클래스의 인스턴스인 경우에는 이 인수들은 가변이라 가정하고 방어적 복사를 사용해야한다.

```java
public static BigInteger safeInsatance(BigInteger val){
  	return val.getClass() == BigInteger.class ? val : new BigInteger(val.toByteArray());
}
```



## 요약

- **Getter가 있다고 해서 무조건 Setter를 구현하지 말자**
- **클래스는 꼭 필요한 경우가 아니라면 불변**이여야한다.
- **불변으로 만들 수 없는 클래스이더라도 변경할 수 있는 부분은 최대한 줄이자**.
  - 다른 합당한 이유가 없다면 모든 필드는 `private final` 이여야한다.
- **생성자는 불변식 설정이 모두 완료된, 객체를 생성해야한다.**
  - 확실한 이유가 없다면 생성자와 정적 팩터리 이외에는 그 어떤 초기화 메서드도 public으로 제공하면 안된다.

(`java.util.concurrent.CountDownLatch`는 다음 원칙을 잘 지키고 있다. )