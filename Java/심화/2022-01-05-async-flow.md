# 리액티브 시스템

리액티브 시스템이란  런타임 환경이 변화에 대응하도록 전체 아키텍처가 설계된 프로그램이다.

## Reactive Manifesto

### 반응성(responsive)

리액티브 시스템이 큰 작업을 처리하느라 **간단한 질의의 응답을 지연하지 않고 실시간으로 입력에 반응**하는 것.

### 회복성(resilient)

**한 컴포넌트의 실패로 전체 시스템이 실패하지 않음을 의미**.
예를 들어 네트워크가 고장이 나도 이와 관계없는 질의에는 아무 영향이 없어야한다.

### 탄력성(elastic)

시스템이 자신의 **작업 부하에 맞게 적응하며 작업을 효율적으로 처리**.
예를 들어 각 큐가 원활하게 처리될 수 있도록 다양한 소프트웨어 서비스와 관련된 작업자 스레드를 적절하게 재배치할 수 있다.

### 메세지 주도(message-driven)

회복성과 탄력성을 지원하려면 약한 결합, 고립, 위치 투명성 등을 지원하도록 경계를 명확히 정의한다. 또한 **비동기 메시지를 전달해 컴포넌트 간 통신**이 이뤄진다.

여러가지 방법으로 위 속성을 구현할 수 있지만 `Flow` 관련 자바 인터페이스에서 제공하는 리액티브 프로그래밍 형식을 이용하는 것도 주요 방법 중 하나이다. 리액티브 프로그래밍은 메세지 주도 속성을 반영하고 있다.

## 리액티브 프로그래밍

> 프로그래밍은 데이터 스트림 및 변화의 전파와 관련된 선언적 프로그래밍 패러다임 - wiki

- 변화의 전파와 데이터 흐름 : 데이터가 변경될 떄마다 이벤트를 발생시켜 데이터를 지속적으로 전달
- 선언적 프로그래밍 : 실행할 동작을 구체적으로 명시하는 명령형 프로그램과 달리 선연형 프로그램은 단순히 목표를 선언

## Flow(Java9)

`Flow` 인터페이스에 발행(pub)-구독(sub) 모델을 적용해 리액티브 프로그래밍을 제공한다.

- **구독자**가 구독할 수 있는 **발행자**
- 여기서 연결을 **구독(subscription)**이라 한다.
- 구독을 이용해 메시지(이벤트)를 전송한다.

### Publisher

```java
	@FunctionalInterface
    public static interface Publisher<T> {
        public void subscribe(Subscriber<? super T> subscriber);
    }

```

### Subscriber

```java
    public static interface Subscriber<T> {

        public void onSubscribe(Subscription subscription);

        public void onNext(T item);

        public void onError(Throwable throwable);

        public void onComplete();
    }
```

스프레드 시트에서 C3는 `= C1 + C2` 공식을 포함하고 있으며, C1, C2의 값이 변경되면 C3도 변경되는 예로 구독자와 발행자를 구현해 볼 것이다.

```java
public class SimpleCell implements Publisher<Integer>, Subscriber<Integer> {
    private int value = 0;
    private String name;
    private List<Subscriber> subscribers = new ArrayList<>();

    public SimpleCell(String name) {
        this.name = name;
    }

    @Override
    public void subscribe(Subscriber<? super Integer> subscriber) {
        subscribers.add(subscriber);
    }

    public void subscribe(Consumer<? super Integer> onNext) {
        subscribers.add(new Subscriber<Integer>() {

            @Override
            public void onComplete() {
            }

            @Override
            public void onError(Throwable t) {
                t.printStackTrace();
            }

            @Override
            public void onNext(Integer val) {
                onNext.accept(val);
            }

            @Override
            public void onSubscribe(Subscription s) {
            }

        });
    }

    // 새로운 값이 있음을 모든 구독자에게 알리는 메서드
    private void notifyAllSubscribers() {
        subscribers.forEach(subscriber -> subscriber.onNext(this.value));
    }

    @Override
    public void onSubscribe(Subscription subscription) {
        System.out.println("onSubscribe");
    }

    @Override
    public void onNext(Integer newValue) {
        this.value = newValue;
        System.out.println(this.name + " : " + this.value);
        notifyAllSubscribers(); // 값이 갱신되었음을 모든 구독자에게 알림
    }


    @Override
    public void onError(Throwable throwable) {
        System.out.println("onError");
    }

    @Override
    public void onComplete() {
        System.out.println("onComplete");

    }
}
```

```java
public class ArithmeticCell extends SimpleCell{

    private int left;
    private int right;

    public ArithmeticCell(String name) {
        super(name);
    }

    public void setLeft(int left) {
        this.left = left;
        onNext(left + this.right);
    }

    public void setRight(int right) {
        this.right = right;
        onNext(right + this.left);
    }
}

```

```java
class ArithmeticCellTest {

    @Test
    void test1() {
        ArithmeticCell c3 = new ArithmeticCell("C3");
        ArithmeticCell c5 = new ArithmeticCell("C5");

        SimpleCell c1 = new SimpleCell("C1");
        SimpleCell c4 = new SimpleCell("C4");
        SimpleCell c2 = new SimpleCell("C2");

        c1.subscribe(c3::setLeft);
        c2.subscribe(c3::setRight);

        c3.subscribe(c5::setLeft);
        c4.subscribe(c5::setRight);

        c1.onNext(10);
        c2.onNext(20);
        c1.onNext(15);
        c4.onNext(1);
        c4.onNext(3);
    }

}
```

```
C1 : 10
C3 : 10
C5 : 10
C2 : 20
C3 : 30
C5 : 30
C1 : 15
C3 : 35
C5 : 35
C4 : 1
C5 : 36
C4 : 3
C5 : 38
```

데이터가 발행자(생산자)에서 구독자(소비자)로 흐름에 착안해 이를 **upstream** or **downstream**이라 부른다.
위 예제에서 newValue는 업스트림 `onNext()` 메서드로 전달되고 `notifyAllSubstribers()` 호출을 통해 다운스트림 `onNext()`로 전달된다.

### Pressure

Pressure(압력)이란 뭘까?

예를 들어 모든 SMS 메시지를 폰으로 제공하는 발행자에 가입하는 상황이 있다. 처음에는 새 폰에서 가입이 잘 동작하지만 추 후에는 매 초마다 수천 개의 메세지가 `onNext()`로 전달되는 경우와 같은 상황을 압력이라 볼 수 있다.

### Backpressure

Publisher에서 Subscriber로 정보를 전달할 때 정보의 흐름 속도를 backpressure(흐름 제어)로 Subscriber에서 Publisher로 정보를 요청해야 할 필요가 있을 수 있다.

```java
	public static interface Subscriber<T> {
        public void onSubscribe(Subscription subscription);
    //...
    }
```

Publisher는 여러 구독자를 가지고 있으므로 backpressure가 한 연결에만 영향을 미춰야한다. Publisher와 Subscriber사이에 채널이 연결되면 첫 이벤트로 `onSubscribe()`메서드가 호출된다.

```java
	public static interface Subscription {
        public void request(long n);

        public void cancel();
    }
```

`Subscription`은 `Publisher`와 `Subscriber`와  통신할 수 있는 메서드를 포함하고 있다.
여기서 콜백을 통한 역방향 소통에 주목해야한다. `Publisher`는 `Subscription` 객체를 만들어 `Subscriber`로 전달하면 `Subscriber`는 이를 이용해 `Publisher`에 정보를 보낼 수 있다.

실제 역압력의 간단한 형태를 살펴보자. 한번에 한 개의 이벤트를 처리하도록 발행-구독 연결을 구성하려면 다음과 같이 구현해야한다.

- `Subscriber`가 `onSubscribe`로 전달된 `Subscription` 구현 객체를 subscription 같은 필드에 로컬로 저장
- `Subscriber`가 수많은 이벤트를 받지 않도록 `onSubscribe`, `onNext`, `onError`의 마지막 동작에 `channel.request(1)`을 추가해 오직 한 이벤트만 요청
- 요청을 보낸 채널에만 `onNext`, `onError` 이벤트를 보내도록 한다.



## 참고

- [모던 자바 인 액션]()

