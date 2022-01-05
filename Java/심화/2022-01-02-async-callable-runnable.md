# Callable/Runnable

Thread는 Runnable과 Callable의 구현된 함수를 수행한다.

## Runnable

쓰레드 구현시 Runnable 인터페이스를 이용해서 생성할 수 있다.

- 어떤 객체도 반환하지 않음
- Exception을 발생시키지 않음

```java
@FunctionalInterface
public interface Runnable {
    public abstract void run();
}
```

인터페이스를 살펴보면 인자를 받지 않으며, 반환값도 없는 것을 확인할 수 있다.

```java
public class RunnableEx {

    
    static class TestRunnable implements Runnable {

        @Override
        public void run() {
            String result = "Called at " + LocalDate.now();
            System.out.println(result);
        }
    }

    public static void main(String[] args) {
        
        // Runnable 구현한 클래스로 구현
        TestRunnable runnable = new TestRunnable();
        Thread thread = new Thread(runnable);
        thread.start();

        // lambda로 구현
        Thread thread2 = new Thread( () -> {
            System.out.println("Runnable at " + LocalDate.now());
        });
        thread2.start();
    }
}
```

## Callable

```java
@FunctionalInterface
public interface Callable<V> {
    /**
     * Computes a result, or throws an exception if unable to do so.
     *
     * @return computed result
     * @throws Exception if unable to compute a result
     */
    V call() throws Exception;
}
```

Callable은 인자를 받지 않으며, 특정 타입(`V`) 객체를 반환한다. 또한 `Exception`을 발생시킬 수 있다.

```java
public class CallableEx {

    static class TestCallable implements Callable<String> {
        @Override
        public String call() throws Exception {
            String result = "Called at " + LocalDate.now();
            return result;
        }
    }

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        TestCallable callable = new TestCallable();
        FutureTask futureTask = new FutureTask(callable);

        Thread thread = new Thread(futureTask);
        thread.start();

        System.out.println("result : " + futureTask.get());
    }
}

```