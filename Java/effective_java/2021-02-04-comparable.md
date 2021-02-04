# ITEM 14: CONSIDER IMPLEMENTING COMPARABLE

```java
public interface Comparable<T> {
  	/**
  	 * 이객체와 주어진 객체의 순서를 비교
  	 * 객체가 주어진 객체보다 작으면 음의 정수
  	 * 같으면 0
  	 * 크면 양의 정수를 반환
  	 * 비교할 수 없는 타입의 객체가 주어지면 ClassCastException
  	 */
    public int compareTo(T o);
}
```

`Comparable` 은 단순 동치성 비교와 순서 비교를 할 수 있는 Generic 인터페이스이다. `Comparable`을 구현한 클래스의 인스턴스에는 자연적인 순서가 있음을 뜻하며,  `Comparable`을 구현한 객체들의 배열은 다음과 같이 쉽게 정렬할 수 있다.

```java
Arrays.sort(a);
```

```java
// String은 Comparable을 구현함
public final class String
    implements java.io.Serializable, Comparable<String>, CharSequence {
  ...
}
```

사실상 자바 플랫폼 라이브러리의 모든 값 클래스와 열거타입이 `Comparable`을 구현했으며, 알파벳, 숫자, 연대 같이 순서가 명확한 값 클래스를 작성한다면 `Comparable` 인터페이스를 구현하는 것이 좋다.

**compareTo 메서드 일반 규약**

`sgn`은 signum function을 뜻하고, 표현식의 값이 음수, 0, 양수일 때 -1, 0, 1을 반환하도록 정의

1. `sgn(x.compareTo(y)) == -sgn(y.compareTo(x))` 
2. `x.compareTo(y) > 0 && y.compareTo(z) > 0`이면 `x.compareTo(z) > 0` 이다.
3. `x.compareTo(y) == 0` 이면 `sgn(x.compareTo(z)) == sgn(y.compareTo(z))` 이다.
4. `(x.compareTo(y) == 0 ) == (x.equals(y))` 여야한다. (이 권고는 필수는 아니지만 꼭 지키는게 좋으며, 만약 지키지 않았다면 이 클래스의 순서는 `equals` 메서드와 일관되지 않는 다는 것을 명시해야한다.)

`compareTo` 규약을 지키지 못하면 비교를 활용하는 클래스(`TreeSet`, `TreeMap`, `Collections`, `Arrays`)를 활용하지 못한다.

4번 규약을 지키지 않은 즉, `compareTo`와 `equals`의 결과가 일관되지 않은 경우에는 이 클래스의 객체를 정렬된 컬렉션에서 의도치 않은 동작을 할 수 있다.

```java
    public static void main(String[] args) {

        BigDecimal a = new BigDecimal("1.0");
        BigDecimal b = new BigDecimal("1.00");

        Set<BigDecimal> hs = new HashSet<>();
        hs.add(a);
        hs.add(b);

        System.out.println(hs.size()); // 2

        Set<BigDecimal> ts = new TreeSet<>();
        ts.add(a);
        ts.add(b);

        System.out.println(ts.size()); // 1

    }
```

`HashSet`은 `equals` 메소드로 비교를 하기때문에 `HashSet`의 원소는 2개이고, `TreeSet`은 `compareTo` 메서드로 비교하기 떄문에 원소의 개수는 1개이다.

`Comparable`은 타입을 인수로 받는 제네릭 인터페이스로, `compareTo` 메서드의 인수 타입은 컴파일타임에 정해진다. 인수 타입 자체가 잘못됐다면, 컴파일 자체가 되지 않으며, null을 인수로 넣어 호출한다면 `NullPointerExeption`이 발생할 것이다. `compareTo`는 각 필드가 동치인지 비교하는 것이 아닌 **순서를 비교**한다.

`compareTo` 메서드에서 관계 연산자 `<`와 `>` 를 사용하는 방식은 추천하지 않으며, 자바7부터 박싱된 기본 타입 클래스들에 새로 추가된 `compare`을 이용하면 된다.

클래스의 핵심 필드가 여러 개라면 가장 핵심적인 필드부터 비교해야한다. 비교 결과가 0이 아니라면(순서가 정해진다면) 반환하면 된다.

```java
	public int compareTo(PhoneNumber pn){
        int result = Short.compare(areaCode, pn.areaCode);
        if(result == 0){
            result = Short.compare(prefix, pn.prefix);
            if(result == 0){
                result = Short.compare(lineNum, pn.lineNum);
            }   
        }
        return result;
    }
```

자바 8에서는 `Comparator` 인터페이스를 활용해서 구현할 수 있다.

```java
private static final Comparator<PhoneNumber> COMPARATOR = Comparator.comparingInt((PhoneNumber pn) -> pn.areaCode).thenComparingInt(pn -> pn.lineNum).thenComparingInt(pn -> pn.prefix);
    
    public int compareTo(PhoneNumber pn){
        return COMPARATOR.compare(this, pn);
    }
```

이 방식은 간결하지만 ,약간의 성능저하가 뒤따른다. `Comparator`는 자바의 숫자용 기본 타입을 모두 커버할 수 있다.



**비교자 주의 사항**

```java
static Comparator<Object> hashCodeOrder = new Comparator<>() {
    public int compare(Object o1, Object o2) {
        return o1.hashCode() - o2.hashCode();
    }
};
```

다음 방식은 정수 오버플로우나, 부동소수점 계산 방식에 따른 오류를 낼 수 있으며, 성능 또한 월등히 빠르지 않기 때문에 사용하면 안된다. 아래 두 방식중 하나로 구현하는 것을 권장한다.

- 정적 compare 메서드 활용

```java
static Comparator<Object> hashCodeOrder = new Comparator<>() {
  	public int compare(Object o1, Object o2){
      	return Integer.compare(o1.hashCode(), o2.hashCode());
    }
}
```

- 비교자 생성 메서드 활용

```java
static Comparator<Object> hashCodeOrder = Comparator.comparingInt(o->o.hashCode);
```



정리하지면 다음과 같다.

1. 순서를 고려하는 값 클래스 작성시 `Comparable` 인터페이스를 구현해 해당 인스턴스를 쉽게 정렬, 검색, 비교할 수 있는 컬렉션과 어우러지도록 해야 한다.
2. `compareTo` 메서드에서 필드 값 비교시 `<`, `>` 연산자는 사용하지 말자
3. 박싱된 기본 타입 클래스가 제공하는 정적 `compare` 메서드나 `Compartor` 인터페이스가 제공하는 비교자 생성 메서드를 사용하자.







