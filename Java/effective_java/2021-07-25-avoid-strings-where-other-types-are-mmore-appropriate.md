# ITEM 62: 다른 타입이 적절하다면 문자열 사용을 피해라

#### 문자열은 다른 값 타입을 대신하기에 적합하지 않다.

입력 받은 데이터가 진짜 문자열인 경우에만 문자열을 사용하는 것이 좋다.

#### 문자열은 열거 타입을 대신하기에 적합하지 않다.

- [ITEM 34:  int 상수 대신 열거 타입을 사용해라](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-06-05-use-enum-type.md)

#### 문자열은 혼합 타입을 대신하기에 적합하지 않다.

여러 요소가 혼합된 데이터를 하나의 문자열로 표현하는 것은 좋지 않으며, 차라리 전용 클래스를 새로 만드는 것이 좋다.

- [private static class](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-14-favor-static-memeber.md)

혼합된 데이터를 사용하면 다음과 같은 문제점이 있다.

1. 개별 요소 접근시 문자열 파싱 필요 : 느리고, 귀찮고, 오류 가능성 커짐
2. 적절한 `equals`, `compareTo`, `toString` 메서드 제공 불가능

#### 문자열은 권한을 표현하기에 적합하지 않다.

아래 코드는 스레드 지역변수 기능을 설계할 때, 클라이언트가 제공한 문자열 키로 스레드별 지역변수를 식별한 예이다.

```java
public class ThreadLocal {
  private ThreadLocal() { } // 객체 생성 불가
  
  // 현 스레드 값을 키로 구분해 저장
  public static void set(String key, Object value);
  
  // 현 스레드의 값을 반환
  public static Object get(String key);
}
```

이 방식은 스레드 구분용 문자열 키가 전역범위로 공유된다는 것이며, 만약 두 클라이언트가 동일한 고유 키를 사용한다면, 같은 변수를 공유하게 된다.
또한, 보안도 취약하다.
이는 문자열대신 위조할 수 없는 키를 사용하면 된다.

```java
public final class ThreadLocal<T> {
  public ThreadLocal();
  public void set(T value);
  public T get();
}
```

다음과 같이 해결할 수 있다.

