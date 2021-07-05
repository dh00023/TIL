# ITEM 50: 적시에 방어적 복사본을 만들어라

클라이언트가 불변식을 깨뜨릴 수 있으므로, 방어적 프로그래밍을 해야한다.

## 가변 필드

클래스가 가변 필드를 가진 경우 외부에서 내부를 수정할 수 있으므로, 주의해야한다.

```java
public class Period {
    private final Date start;
    private final Date end;

    /**
     * @param start 시작 시각
     * @param end 종료 시각(시작 시각 보다 뒤여야한다.)
     *
     * @throws IllegalArgumentException 시작 시각이 종료 시각보다 늦으면 발생
     * @throws NullPointerException start나 end가 null이면 발생
     */
    public Period(Date start, Date end) {
        if (start.compareTo(end) > 0) {
            throw new IllegalArgumentException(start + "가 " + end + "보다 늦습니다");
        }
        this.start = start;
        this.end = end;
    }

    public Date start() {
        return start;
    }

    public Date end() {
        return end;
    }
}
```

### 생성자

`Date` 가 가변이므로 다음과 같이 외부에서 내부 데이터를 수정할 수 있다.
(java8이상에서는 `Date` 대신 `Instant`, `LocalDateTime`, `ZonedDateTime`을 사용하면 된다.)

```java
Date start = new Date();
Date end = new Date();
Period p = new Period(start, end);
end.setYear(78); // p의 내부 수정
```

#### defensive copy

생성자에서 받은 가변 매개변수를 방어적 복사를 통해 외부에서 값을 수정하는 것을 막을 수 있다.

```java
    /**
     * @param start 시작 시각
     * @param end 종료 시각(시작 시각 보다 뒤여야한다.)
     *
     * @throws IllegalArgumentException 시작 시각이 종료 시각보다 늦으면 발생
     * @throws NullPointerException start나 end가 null이면 발생
     */
    public Period(Date start, Date end) {
        this.start = new Date(start.getTime());
        this.end = new Date(end.getTime());
        
        if (start.compareTo(end) > 0) {
            throw new IllegalArgumentException(start + "가 " + end + "보다 늦습니다");
        }
    }
```

여기서 매개변수의 유효성 검사를 하기전에 방어적 복사본을 만들고, 복사본으로 유효성 검사를 하고 있다.
멀티 스레딩 환경에서 원본 객체의 유효성 검사 후 복사본을 만드는 순간에 다른 스레드가 원본 객체를 수정할 위험이 있기때문에 반드시 방어적 복사본을 만들고, 복사본으로 유효성 검사를 해야한다.

여기서 `clone()`을 사용하지 않은 이유는, `clone`이 `Date`가 정의한 게 아닐 수도 있다.
즉,  매개변수가 제 3자에 의해 확장될 수 있는 타입인 경우 방어적 복사를 만들 때, `clone()`을 사용해서는 안된다.

### 접근자 메서드

```java
Date start = new Date();
Date end = new Date();
Period p = new Period(start, end);
p.end().setYear(78); // p의 내부 수정
```

다음과 같이 접근 메서드( `end()`, `start()`)로 내부 값을 수정할 수 있다.
접근자 메서드도 가변 필드의 방어적 복사를 반환하여 외부 수정을 막을 수 있다.

#### defensive copy

```java
    public Date start() {
        return new Date(start.getTime());
    }

    public Date end() {
        return new Date(end.getTime());
    }
```

생성자와 달리 접근자 메서드에서는 방어적 복사에  `clone()`을 사용해도 된다. 왜냐하면, `Period`가 가지고 있는 `Date` 객체는 `java.util.Date` 임이 확실하기 때문이다.
그렇더라도, [ITEM 13 : clone 재정의는 주의해서 정의해라](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-03-overriding-clone-judiciously.md)에서 이야기 하듯이, 인스턴스 복사시에는 일반적으로 생성자나 정적 팩터리를 사용하는 것이 좋다.



참고로, 길이가 1이상인 배열은 무조건 가변이므로, 내부에서 사용하는 배열을 클라이언트에 반환할 때는 방어적 복사를 하거나 불변 뷰를 반환해야한다.

---

모든 경우에 방어적 복사를 해야하는 것은 아니다. 복사 비용이 너무 크거나 클라이언트가 그 요소를 잘못 수정할 일이 없다고 확신한다면, 방어적 복사를 수행하는 대신 해당 구성요소를 수정했을 때의 책임이 클라이언트에 있음을 문서에 명시하면 된다.