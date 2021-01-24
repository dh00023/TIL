# ITEM 8: AVOID FINALIZERS AND CLEANERS

자바는 `finalizer`, `cleaner`두 가지 객체 소멸자를 제공한다. `finalizer`와 `cleaner`는 GC가 더 이상 사용하지 않는 자원에 대한 정리작업을 진행하기 위해 사용된다.

**finalizer**

- 예측이 불가능하며, 상황에 따라 위험할 수 있어 일반적으로 불필요
- 오동작, 낮은 성능, 이식성 문제의 원인

`finalizer` 나름의 쓰임새가 있지만 기본적으로 사용을 지양해야한다. (Java 9에서 deprecated)

**cleaner**

`cleaner`는 `finalizer`의 대안으로 소개되었다. `cleaner`는 `finalizer`보다는 덜 위험하지만 여전히 아래 단점을 가지고 있다.

- 예측 불가능
- 느림
- 일반적으로 불필요

## 사용을 지양해야하는 이유

### 1. `finalizer`와 `cleaner`로는 제때 실행되어야 하는 작업은 절대 알 수 없다.

`finalizer`와 `cleaner`는 즉시 수행된다는 보장이 없으며, 객체에 접근할 수 없게 된 후 `finalizer`와 `cleaner`가 실행될 때까지 어느정도 걸리는지 알 수 없다. 예를 들어, 파일 닫기를 `finalizer`/ `cleaner`에 맡기게 된다면 시스템이 동시에 열 수 있는 파일 개수에 한계가 있기에 오류가 발생할 수 있다.

클래스에 `finalizer`를 달아두면 인스턴스의 자원 회수가 제멋대로 지연될 수 있다. 실제로 원인을 알 수 없는 [OutOfMemoryError](https://github.com/dh00023/TIL/blob/master/Java/%EC%8B%AC%ED%99%94/2021-01-23-outOfMemoryError.md)가 발생해 분석해보았을 때, 애플리케이션이 죽는 시점에 객체 수천개가 `finalizer` 스레드는 다른 애플리케이션 스레드 보다 우선순위가 낮아 대기열에서 회수되기만을 기다리고 있었다. 

`cleaner`는 자신이 수행할 스레드를 제어할 수 있다는 점에서 낫지만, 여전히 백그라운드에서 수행되며 가비지 컬렉터의 통제하에 있어 즉각 수행된다는 보장이 없다.

또한, 자바는 `finalizer`와 `cleaner`의 수행 시점 뿐만 아니라 수행 여부 조차 보장하지 않는다. 이것은 접근할 수 없는 일부 객체에 종료 작업을 전혀 수행하지 못한 채 프로그램이 중단 될 수도 있다는 것이다.

**즉, 상태를 영구적으로 수정하는 작업에서 절대 `finalizer`와 `cleaner`에 의존하면 안된다. **

`System.gc`, `System.runFinalization` 은 `finalizer`와 `cleaner`가 실행될 가능성은 높여줄 수 있으나, 보장해주지 않으며, `System.runFinalizersOnExit`과 `Runtime.runFinalizersOnExit`은 실행을 보장해준다고 되어있지만 ThreadStop 의 심각한 결함 문제가 있다.

또한, `finalizer`는 동작 중 발생한 예외는 무시되며, 처리할 작업이 남아 있더라도 그 순간 종료된다. 잡지 못한 예외 때문에 해당 객체는 마무리가 덜 된 상태로 남아 있을 수 있으며, 다른 스레드가 훼손된 객체를 사용하려 한다면, 어떻게 동작할지 예측할 수 없다. (`cleaner`는 자신의 스레드를 통제하므로 이러한 문제 발생안함)

### 2. `finalizer`와  `cleaner`는 심각한 성능 문제도 동반될 수 있다.

 `AutoCloseable` 객체를 생성해 GC가 수거하기 까지 12ns가 걸린 것이, `finalizer`를 사용하니 550ns가 걸렸다. `finalizer`가 GC의 효율을 떨어뜨리기 때문이다. 

`cleaner`도 클래스의 모든 인스턴스를 수거하는 형태로 사용하면 `finalizer`와 성능은 유사하며, 안정망 방식을 사용하면 약 66ns가 걸리나, 안전망을 설치하면 성능이 약 5배 정도 느려진다.



### 3. `finalizer`를 사용한 클래스는 `finalizer` 공격에 노출되어 심각한 보안 문제를 일으킬 수 있다.

생성자나 직렬화 과정에서 예외가 발생하면, 생성되다 만 객체에서 악의적으로 하위 클래스의 `finalizer`가 수행될 수 있다.  이 `finalizer`는 정적 필드에 자신의 참조를 할당해 GC가 수집하지 못하게 막을 수 있다.

객체 생성을 막기위해 생성자에서 예외를 던질 수 있지만, `finalizer`가 있다면 이도 불가능하다.

**final이 아닌 클래스를 `finalizer` 공격으로 방어하려면 아무 로직이 없는 `finalize` 메서드를 만든 후 final로 선언하면 된다.** 



## 사용하는 곳

1. 자원의 소유자가 `close` 메서드를 호출하지 않는 것에 대비한 안정망 역할로 사용 (언제 회수 될지 모르지만 늦게라도 해주는 것이 좋음 ) - `FileInputStream`, `FileOutputStream`, `ThreadPoolExecutor`에서 안전망 역할의 `finalizer` 제공
2. \**Native Peer*는 자바 객체가 아니므로 GC가 그 존재를 알지 못한다. 즉, 네이티브 피어와 연결된 객체에서의 자원 회수용으로 사용한다. 단, 성능 저하를 감당할 수 있고 네이티브 피어가 심각한 자원을 가지고 있지 않을 때만 해당한다. 성능저하를 감당할 수 없거나 자원을 즉시 회수해야한다면 `close` 메서드를 사용해야한다.

`cleaner`는 안전망 역할이나 중요하지 않은 네이티브 자원 회수 용으로만 사용하며, 이 경우에도 불확실성과 성능저하에 유의해야한다.

*\* Native Peer : 일반 자바 객체가 네이티브 메서드를 통해 기능을 위임한 네이티브 객체*

## 대안

파일이나 스레드 등 종료해야 할 자원을 담고 있는 객체의 클래스에서 `finalizer`와 `cleaner`를 대신해주려면 `AutoCloseable`을 구현해주고, `close` 메서들르 호출하면된다.([try-with-resources(item 9)](./2021-01-25-try-with-resources.md))

각 인스턴스는 `close` 메서드에서 더 이상 유효하지 않음을 기록하고, 다른 메서드는 해당 필드를 검사해 객체가 닫힌 후에 호출했다면 `IllegalStateException` 오류를 발생시키는 것이다.



## 참고

- [yundeleyundle.log - [Item8] finalizer와 cleaner사용을 피하라](https://velog.io/@yundleyundle/Item8-finalizer%EC%99%80-cleaner%EC%82%AC%EC%9A%A9%EC%9D%84-%ED%94%BC%ED%95%98%EB%9D%BC)

