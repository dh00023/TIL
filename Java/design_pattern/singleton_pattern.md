# Singleton Pattern

애플리케이션이 시작될 때 어떤 클래스가 **최초 한번만** 메모리를 할당하고(static) 그 메모리에 인스턴스를 만들어 사용하는 디자인 패턴이다. 생성자가 여러번 호출되더라도 실제로 생성되는 객체는 하나이며, 최초 생성 이후 호출된 생성자는 최초에 생성한 객체를 반환한다.

즉, **인스턴스를 하나만 만들어 사용하기위한 패턴**이다.

<img src="./assets/singleton-example.png" style="zoom:48%;" />

> 하나의 인스턴스만을 생성하는 책임이 있으며, `getInstance()` 메서드를 통해 모든 클라이언트에게 동일한 인스턴스를 반환하는 작업을 수행한다.

```java
public class Singleton {
    private static Singleton singletonObject;

    private Singleton() {}

    public static Singleton getInstance() {
        if (singletonObject == null) {
            singletonObject = new Singleton();
        }
        return singletonObject;
    }
}
```

하나의 인스턴스만을 유지하기 위해 인스턴스 생성에 특별한 제약을 걸어둬야 한다. new 를 실행할 수 없도록 **생성자에 private 접근 제어자를 지정**하고, 유일한 단일 객체를 반환할 수 있도록 **정적 메소드를 지원**해야 한다. 또한 유일한 단일 객체를 참조할 정적 참조변수가 필요하다.



#### 문제점

**멀티스레딩 환경에서 싱글턴 패턴을 적용하다보면 문제가 발생**할 수 있다. 동시에 접근하다가 하나만 생성되어야 하는 인스턴스가 두 개 생성될 수 있는 것이다.  이러한 문제는  1. 인스턴스를 만드는 메서드에 동기화하는 방법 (Thread-Safe Initialization) 2. 정적 변수에 인스턴스를 만들어 바로 초기화하는 방법 (Eager Initialization)으로 해결할 수 있다.

```java
public class Singleton {
    private static Singleton singletonObject;

    private Singleton() {}

    public static synchronized Singleton getInstance() {
        if (singletonObject == null) {
            singletonObject = new Singleton();
        }
        return singletonObject;
    }
}
```

단순히 synchronized 키워드를 사용하면 성능상 이슈가 있을 수 있다.

```java
public class Singleton {
    private static volatile Singleton singletonObject;

    private Singleton() {}

    public static Singleton getInstance() {
        if (singletonObject == null) {
            synchronized (Singleton.class) {
                if(singletonObject == null) {
                    singletonObject = new Singleton();
                }
            }
        }
        return singletonObject;
    }
}
```

다음과 같이 `DCL(Double Checking Locking)`을 써서 `getInstance()`에서 **동기화 되는 영역을 줄일 수 있다.** 초기에 객체를 생성하지 않으면서도 동기화하는 부분을 작게 만들었다. 그러나 이 코드는 **멀티코어 환경에서 동작할 때,** 하나의 CPU 를 제외하고는 다른 CPU 가 lock 이 걸리게 된다. 그렇기 때문에 다른 방법이 필요하다.

```java
public class Singleton {
    private static volatile Singleton singletonObject = new Singleton();

    private Singleton() {}

    public static Singleton getSingletonObject() {
        return singletonObject;
    }
}
```

**정적변수에 인스턴스를 만들어 바로 초기화 하는 방법**(Eager initialization)으로 해결할 수 있다.

#### 왜 싱글톤을 사용할까?

1. 고정된 메모리 영역을 사용하면서 메모리 낭비를 방지할 수 있다.
2. 전역 인스턴스이기 때문에 다른 클래스의 인스턴스들이 데이터를 공유하기 쉽다. (Connection Pool,  스레드 풀, 디바이스 설정 객체처럼 공통퇸 객체를 여러개 생성해 사용해야하는 상황에서 많이 사용)
3. 두 번째 이용시부터는 객체 로딩 시간이 줄어 성능이 좋아진다.


#### 참조 페이지

- [https://jeong-pro.tistory.com/86](https://jeong-pro.tistory.com/86)
- [https://asfirstalways.tistory.com/335](https://asfirstalways.tistory.com/335)
- [https://gmlwjd9405.github.io/2018/07/06/singleton-pattern.html](https://gmlwjd9405.github.io/2018/07/06/singleton-pattern.html)
- [https://github.com/JaeYeopHan/Interview_Question_for_Beginner/tree/master/DesignPattern](https://github.com/JaeYeopHan/Interview_Question_for_Beginner/tree/master/DesignPattern)