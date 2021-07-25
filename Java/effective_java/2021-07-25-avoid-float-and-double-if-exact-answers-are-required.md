# ITEM 60: 정확한 답이 필요하다면 float와 double은 피해라

`float`와 `double` 타입은 과학과 공학 계산용으로 설계되었으며, 이진 부동소수점 연산에 주로 쓰인다. 이때, 넓은 범위의 수를 빠르게 정밀한 **근사치**로 계산하도록 설계되어있기 때문에 정확한 결과가 필요한 경우에는 사용하면 않된다.
`float`와 `doulbe`은 특히 금융 관련 계산과는 맞지 않다.

```java
System.out.println(1.03 - 4.02);     // -2.9899999999999993
System.out.println(1.00 - 9 * 0.10); // 0.09999999999999998
```

다음과 같이 소수점 계산시 정확한 값이 나오지 않는 것을 볼 수 있다. 결과를 출력하기전에 반올림을하면 해결될거라 생각할 수 있지만, 반올림을해도 틀린값이 나올 수 있다.

이렇게 정확한 계산이 필요한 경우에는 `BigDecimal`, `int`, `long`을 사용해야한다.

```java
System.out.println(BigDecimal.valueOf("1.03").subtract(BigDecimal.valueOf("4.02"))); // -2.99
System.out.println(BigDecimal.valueOf("1.00").subtract(BigDecimal.valueOf("9").multiply(BigDecimal.valueOf("0.10")))); // 0.1
```

다음과 같이 정확한 값이 나오는 것을 확인할 수 있다.

`BigDecimal`은 기본타입보다 쓰기 불편하고, 느리다는 단점이 있다.

- 코딩 시의 불편함과 성능 저하를 신경 쓰지 않거나 큰 수를 계산하는 경우에는  `BigDecimal`을 사용
    - 8자리 10진수 이상인 경우
- 성능이 중요하고 소수점을 직접 추적할 수 있고 숫자가 너무 크지 않다면 `int`나 `long`을 사용해라.
    