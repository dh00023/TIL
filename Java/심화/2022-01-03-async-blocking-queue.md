# BlockingQueue(Java5)

- Thread-safe
  - Queue 메소드들은 내부적으로 `locks`혹은 동시성 제어를 사용해 원자성을 보장한다.
  - Bulk Collection Operations(`addAll()`, `containsAll()`, `retainAll()`, `remainAll()`)은 원자성을 보장하지 않으며, 원자성을 보장하기 위해서는 직접 구현해야한다.
- `null`을 허용하지 않는다.
  - `null` 값을 `add()`, `put()`, `offer()` 하면 `NullPointerException` 발생하므로 주의
  - `null`은 `pool` 이 실패한 경우 반환된다.
- 용량(capacity)에 제한을 둘 수 있다.
  - default : `Integer.MAX_VALUE`
- Collection 인터페이스를 제공한다.
  - `BlockingQueue`는 Producer-Consumer 패턴의 대기열 목적으로 디자인 되었다.
  - Collection 인터페이스를 지원하기 때문에 `remove()`와 같은 Collection 메소드를 사용할 수 있지만 매우 비효율 적이다.
- 데이터가 추가되지 않는 것을 나타내기 위한 `close()`, `shutdown()` 을 제공하지 않는다.
  - 일반적으로 producer가 특수한 end-of-stream 또는 poison 객체를 삽입하고 , consumer가 판단하는 패턴으로 목적에 맞춰서 구현해야한다.

```java
public interface BlockingQueue<E> extends Queue<E> {
    boolean add(E e);

    boolean offer(E e);

    void put(E e) throws InterruptedException;

    boolean offer(E e, long timeout, TimeUnit unit)
        throws InterruptedException;

    E take() throws InterruptedException;

    E poll(long timeout, TimeUnit unit)
        throws InterruptedException;

    int remainingCapacity();

    boolean remove(Object o);

    boolean contains(Object o);

    int drainTo(Collection<? super E> c, int maxElements);
}
```

![](./assets/61859757-b486b300-af03-11e9-9ad7-57f00107d003.png)

- Throw exception : 해당 메소드를 즉시 사용할 수 없으면,  Exception 발생
- Special value : `null`이나 `boolean` 값을 반환
- Blocks : 해당 작업을 수행할 때까지 현재의 Thread가 무한 대기
- Times out : 주어진 시간만큼만 block

## 구현체

### ArrayBlockingQueue

- `ArrayBlockingQueue`는 Array로 구현된 BlockingQueue이다. 
- Queue를 생성할 때 크기를 설정하며, 내부적으로 배열을 사용해 아이템 저장
  - 생성 후에는 크기 변경이 불가하다.
- 동시성에 안전하여, 멀티 쓰레드에서 synchronized없이 사용 가능
- 아이템을 꺼낼 때 비어있으면 추가될 때까지 기다리며, 아이템 추가시 Queue가 가득차 있으면 Exception이 발생하거나 일정 시간 기다릴 수 있다.
  - 꽉 찬경우 추가 block, 빈 경우 추출 block
- 선택적으로 공평성 정책을 두어 block 된 thread들을 순차적 대기열을 생성한다.
  - 대기열 처리에 대한 정확한 순서를 보장하지 않는다.

```java
       int capacity = 3;

        ArrayBlockingQueue<Integer> queue = new ArrayBlockingQueue<>(capacity);

        queue.add(1);

        System.out.println(queue);

        queue.add(2);
        queue.add(3);

        System.out.println(queue);

        // queue가 가득찬 경우에 IllegalStateException 발생
        try {
            queue.add(4);
        } catch (IllegalStateException e) {
            System.out.println(e.getMessage());
        }

        // queue가 가득찬 경우 여유 공간 0
        if (queue.remainingCapacity() == 0) {
            System.out.println("Queue is full");
        }

        // 아이템 가져오기
        Integer first = queue.take();
        System.out.println("take : " + first);


        boolean isSuccess = queue.offer(4);
        System.out.println("Success : " + isSuccess);
        // offer는 예외가 발생하지 않고 false return
        isSuccess = queue.offer(5);
        System.out.println("Success : " + isSuccess);

        // put : 공간이 생길때 까지 무한히 대기
//        queue.put(5);

        // poll : 아이템 가져올 때 일정 시간 대기
        // timeout 발생하면 null 반환
        Integer second = queue.poll(0, TimeUnit.MILLISECONDS);
        System.out.println(second);

```

- Executor & BlockingQueue 예제

```java
public class ParallelExcutorEx {

    private static class ParallelExcutorService {
        private final int maxCore = Runtime.getRuntime().availableProcessors();
        private final ExecutorService executor = Executors.newFixedThreadPool(maxCore);
        private final BlockingQueue<String> queue = new ArrayBlockingQueue<>(10);

        public ParallelExcutorService() {
        }

        public void submit(String job) {
            executor.submit(() -> {
                String threadName = Thread.currentThread().getName();
                System.out.println("finished " + job);
                String result = job + ", " + threadName;
                try {
                    queue.put(result);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
        }

        public String take() {
            try {
                return queue.take();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new IllegalStateException(e);
            }
        }

        public void close() {
            List<Runnable> unfinishedTasks = executor.shutdownNow();
            if (!unfinishedTasks.isEmpty()) {
                System.out.println("Not all tasks finished before calling close: " + unfinishedTasks.size());
            }
        }
    }

    public static void main(String args[]) {
        ParallelExcutorService service = new ParallelExcutorService();
        service.submit("job1");
        service.submit("job2");
        service.submit("job3");
        service.submit("job4");

        for (int i = 0; i < 4; i++) {
            String result = service.take();
            System.out.println(result);
        }

        System.out.println("end");
        service.close();

    }
}
```

### LinkedBlockingQueue

```java
public class LinkedBlockingQueue<E> extends AbstractQueue<E>
        implements BlockingQueue<E>, java.io.Serializable {
```

- LinkedList 로 구현한 Queue
- capacity default : `Integer.MAX_VALUE`
- 용량을 초과하지 않는 한에서 node는 동적으로 삽입시마다 생성되며, 초과시 block
- 배열 기반 큐보다 동시성에서 높은 처리율(throughput)을 가진다.

### PriorityBlockingQueue

```java
public class PriorityBlockingQueue<E> extends AbstractQueue<E>
    implements BlockingQueue<E>, java.io.Serializable {
```

- `PriorityQueue`와 같은 정렬 방식을 가지는 용량 제한이 없는 Queue
- 입력 무제한으로 기본 설계가 되었으며, 추가 작업 수행중 실패되면 자원이 더 이상 없는 것이다. ( `OutOfMemoryError`)
- `null`, non-comparable 객체를 수용하지 않는다.
  - 정렬 불가능한 요소의 추가를 허용하지 않음

### SynchronousQueue

- Queue 내부로의 insert 작업이 다른 스레드의 remove 작업과 반드시 동시에 발생해야한다.  (서로 대칭되는 작업이 없을경우 생길때까지 대기)
- null 값을 수용하지 않는다.
- `remove()` 될 떄만 새로운 element를 추가할 수 있다.
- `poll()` 수행시 Queue에 삽입 시도한 쓰레드가 없으면 `null`을 반환한다.

### DelayQueue

```java
public class DelayQueue<E extends Delayed> extends AbstractQueue<E>
    implements BlockingQueue<E> {
```

- `Delayed`의 sub 객체만 `DelayQueue`의 인스턴스를 생성할 수 있다.
- 내부 배열 크기를 알아서 늘어나게 unbounded하게 설계되어 별도로 capacity를 지정하지 않고 인스턴스를 생성할 수 있다.

```java
public interface Delayed extends Comparable<Delayed> {
    long getDelay(TimeUnit unit);
}
```

`Delayed`는 주어진 시간 이후에 동작해야하는 객체를 나타내기 위해 설계되었으며, `compareTo()`와 `getDelay()` 메서드를 구현하여 구현체를 생성할 수 있다.

`DelayedQueue`는 시간 지연처리에 적합하다.

## 참고

- [https://jjaesang.github.io/java/2019/07/25/java-blockingqueue.html](https://jjaesang.github.io/java/2019/07/25/java-blockingqueue.html)
- [[Java\] BlockingQueue 의 종류와 용법](http://oniondev.egloos.com/558949)
- [Java 자료구조 파헤치기 #7 DelayQueue, LinkedBlockingQueue, PriorityBlockingQueue](https://sup2is.github.io/2019/09/16/delay-queue-linked-blocking-queue-priority-blocking-queue.html)