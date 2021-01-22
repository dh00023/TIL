# ITEM 6: AVOID CREATING UNNECESSARY OBJECT

똑같은 기능의 객체를 매번 생성하는 것보다 객체 하나를 생성하여 **재사용**하는 편이 좋을 때가 많다. 특히 [불변 객체(item 17)]()는 언제든지 재사용할 수 있다.

```java
// 안좋은 예 - 호출될 때마다 인스턴스 새로 생성
String s = new String("bad example");
```

위의 문장은 실행될 때마다 String 인스턴스를 새로 만들며, 이 문장이 반복문이나 빈번히 호출되는 메서드 안에 있다면, String 인스턴스가 수없이 많이 만들어 질 수 있다.

```java
// 하나의 String 인스턴스 사용
String s = "good example";
```

위의 경우 새로운 인스턴스를 매번 만드는 대신 **하나의 인스턴스**를 사용하며, **같은 가상 머신 안에서 똑같은 문자열 릴터럴을 사용하는 경우 모든 코드가 같은 객체를 재사용함이 보장**된다.

[정적 팩터리 메서드(item 1)](./2021-01-12-static-factory-methods.md)를 제공하는 불변 클래스에서는 불필요한 객체 생성을 피할 수 있다.

```java
	  // 생성자 - Java9에서 deprecated
    public Boolean(String s) {
        this(parseBoolean(s));
    }

  	// 팩터리 메서드
  	public static Boolean valueOf(String s) {
        return parseBoolean(s) ? TRUE : FALSE;
    }
```

생성자는 매번 새로운 객체를 생성하지만, 팩터리 메서드는 그렇지 않으므로, `Boolean(String)` 생성자 대신 `Boolean.valuesOf(String)` 팩터리 메서드를 사용하는 것이 좋다. 

```java
static boolean isRomanNumeral(String s){
  	return s.matcheds("^(?=.)M*(C[MD]|D?C{0,3})" + "(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$");
}
```

정규 표현식을 활용해 유효한 로마 숫자인지 확인하는 메서드이다. 하지만 이 방식은 `String.matches` 메서드를 사용한다는 문제점이 있다.

```java
/**
     * Tells whether or not this string matches the given <a
     * href="../util/regex/Pattern.html#sum">regular expression</a>.
     *
     * <p> An invocation of this method of the form
     * <i>str</i>{@code .matches(}<i>regex</i>{@code )} yields exactly the
     * same result as the expression
     *
     * <blockquote>
     * {@link java.util.regex.Pattern}.{@link java.util.regex.Pattern#matches(String,CharSequence)
     * matches(<i>regex</i>, <i>str</i>)}
     * </blockquote>
     *
     * @param   regex
     *          the regular expression to which this string is to be matched
     *
     * @return  {@code true} if, and only if, this string matches the
     *          given regular expression
     *
     * @throws  PatternSyntaxException
     *          if the regular expression's syntax is invalid
     *
     * @see java.util.regex.Pattern
     *
     * @since 1.4
     * @spec JSR-51
     */
    public boolean matches(String regex) {
        return Pattern.matches(regex, this);
    }

```

`String.matches` 메서드 내부에서 만드는 정규표현식용 `Pattern` 인스턴스는 한 번 쓰고 버려져 곧 바로 가비지 컬렉션 대상이 된다. `Pattern` 은 입력받은 정규표현식에 해당하는 유한 상태 머신(finite state machine)을 만들어 인스턴스 생성 비용이 높다.

> finite state machine 이란
>
> 상태를 기반으로 동작하는 개념의 방식으로, 상태를 기반으로 처리되기 때문에 **한 번에 한 개의 상태만 처리**된다. 상태에 기반한 조건에 의해 처리되므로, 상태 값이 변경되면 상태에 대한 종료 및 다른 상태로의 변환을 처리한다.
>
> [https://drehzr.tistory.com/70](https://drehzr.tistory.com/70)

이렇게 생성 비용이 많이 드는 객체가 반복해서 필요하다면, 캐싱하여 재사용하는 것을 권장한다.

```java
public class RomanNumerals{
  
  	private static final Pattern ROMAN = Pattern.compile("^(?=.)M*(C[MD]|D?C{0,3})" + "(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$");
  	
  	static boolean isRomanNumeral(String s){
      	return ROMAN.matcher(s).matches();
    }
}
```

불변인 Pattern 인스턴스를 클래스 초기화 과정에서 직접 생성해 캐싱해두고, 나중에 `isRomanNumeral` 메서드 호출을 통해 이 인스턴스를 재사용하여 성능을 개선할 수 있다.

하지만, 클래스가 초기화된 후 이 메서드를 한 번도 호출하지 않는다면, `ROMAN` 필드는 필요없이 초기화 된 것이다. [lazy initialization(item 83)]() 으로 `isRomanNumeral` 메서드가 처음으로 호출될 때 필드를 초기화하도록 하여 불필요한 초기화를 없앨 수 있지만, 지연 초기화는 코드를 복잡하게 만드는데, 성능은 크게 개선되지 않을 때가 많으므로 권하지 않는다.([item 67]())

`Map` 인터페이스의 `KeySet` 메서드는 `Map` 객체 안의 모든 키 값을 담은 `Set` 뷰를 반환한다. `KeySet` 호출시 새로운 `Set` 인스턴스가 만들어진다고 생각할 수 있지만, 사실은 매번 동일한 `Set` 인스턴스를 반환할 수도 있다. 반환된 `Set`  인스턴스가 일반적으로 가변이더라도 반환된 인스턴스들은 기능적으로 모두 동일하며, 반환된 객체 중 하나를 수정하면 모든 객체가 동일한 `Map` 을 대변하기 떄문에 모든 객체가 따라서 바뀐다. `KeySet` 뷰 객체를 여러 개 생성해도 되지만, 그럴 필요는 없다.

또 다른 예로 auto boxing을 들 수 있다. auto boxing은 기본 타입과 박싱된 기본 타입을 섞어 쓸 때 자동으로 상호 변환해주는 기술이다. 오통 박싱은 기본 타입과 그에 대응하는 박싱된 기본 타입의 구분을 흐려주지만, 완전히 없애주는 것은 아니다.

```java
private static long sum(){
  	Long sum = 0L;
  	for (long i = 0; i< Integer.MAX_VALUE; i++){
      	sum += i;
    }
  
  	return sum;
}
```

위 코드는 모든 정수의 총 합을 구하는 메서드로, int를 사용하지 않고 long을 사용하고 있다. 정확한 답을 낼 수는 있지만, 제대로 구현하였을 때보다 성능상으로 훨씬 느려진다. sum 변수를 `long`이 아닌 `Long` 으로 선언하여 불필요한 인스턴스가 `sum += i` 연산이 이루어질 때마다 생성되는 것이다. 단순히 sum의 타입을 `long`으로만 변경해주어도 성능이 개선된다. **즉, 박싱된 기본 타입보다는 기본 타입을 사용하고, 의도치 않은 오토박싱이 숨어들지 않도록 주의해야 한다.**

실제로 상품의 가격을 계산할 때 의도치 않은 auto boxing이 흔히 발생한다. 가격 필드에 대한 타입으로 `BigDecimal` 을 주로 사용하는데 `BigDecimal` 내부 메소드는 기본타입을 사용하고 있다.

```java
public BigDecimal(long val) {
    this.intCompact = val;
    this.intVal = (val == INFLATED) ? INFLATED_BIGINT : null;
    this.scale = 0;
}
public long longValue(){
    return (intCompact != INFLATED && scale == 0) ? intCompact : toBigInteger().longValue();
}
```

이때 `BigDecimal.longValue()`로 연산을 하고 싶다면, 기본 타입을 사용해야하며, 그렇지 않다면 불필요한 인스턴스가 생성될 것이다.



프로그램의 명확성, 간결성, 기능을 위해 객체를 추가로 생성하는 것이라면 일반적으로 좋은 일이다. 불필요한 객체를 생성하는 것을 피하고자 객체 풀(pool)을 생성하는 것은 권장하지 않는다. 자체 객체 풀은 코드를 헷갈리게 만들며, 메모리 사용량을 늘리고 성능을 떨어뜨린다. JVM의 가비지 컬렉터는 상당히 최적화가 잘되어있어 직접 만든 객체 풀보다 훨씬 빠른 경우가 많다. **방어적 복사가 필요한 상황에서 객체를 재사용했을 때의 피해가 필요 없는 객체를 반복 생성했을 때의 피해보다 훨씬 큰 것을 유의**해야한다.

