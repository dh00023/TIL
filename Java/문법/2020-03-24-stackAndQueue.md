# Collectoin - Stack, Queue

## Stack

Stack은 LIFO(Last In First Out) 자료구조이다. (*[Stack 자료구조 살펴보기](https://github.com/dh00023/TIL/blob/master/algorithm/2018-04-24-algorithm-stack.md)*)

스택을 응용한 대표적인 예가 JVM 스택 메모리이며, 스택 메모리에 저장된 변수는 나중에 저장된 것 부터 제거된다.

| 리턴타입 | 메소드       | 설명                                                         |
| -------- | ------------ | ------------------------------------------------------------ |
| E        | push(E item) | 주어진 객체를 스택에 넣는다.                                 |
| E        | peek()       | 스택의 맨 위 객체를 가져온다. 객체를 스택에서 제거하지 않는다. |
| E        | pop()        | 스택의 맨 위 객체를 가져오고, 스택에서 제거한다.             |

```java
Stack<E> stack = new Stack<E>();
```



## Queue

Queue는 FIFO(First In First Out) 자료구조이다. (*[Queue 자료구조 살펴보기](https://github.com/dh00023/TIL/blob/master/algorithm/2018-04-25-algorithm-queue.md)*)

Queue를 응용한 대표적인 예는 스레드풀(ExecutorService)의 작업 큐이다. 작업 큐는 먼저 들어온 작업부터 처리한다.

| 리턴타입 | 메소드     | 설명                                                         |
| -------- | ---------- | ------------------------------------------------------------ |
| boolean  | offer(E e) | 주어진 객체를 넣는다.                                        |
| E        | peek()     | 가장 먼저 추가한 객체를 가져오고, 객체를 큐에서 제거하지 않는다. |
| E        | poll()     | 가장 먼저 추가한 객체를 가져오고, 큐에서 제거한다.           |

Queue의 인터페이스를 구현한 대표적인 클래스는 LinkedList이다. LinkedList는 List 인터페이스로 구현했기때문에 List Collection이기도 하다.

```java
Queue<E> queue = new LinkedList<E>();
```

### ConcurrentLinkedQueue

동기화된 컬렌션은 멀티 스레드 환경에서 하나의 스레드가 요소를 안전하게 처리하도록 도와주지만, 전체 요소를 빠르게 처리하지는 못한다. 하나의 스레드가 요소를 처리할때 전체 잠금이 발생해 다른 스레드는 대기상태가된다.
자바는 멀티 스레드가 컬렉션의 요소를 병렬적으로 처리할 수 있도록 컬렉션을 제공하고 있다.

```java
Queue<E> queue = new ConcurrentLinkedQueue<E>();
```
ConcurrentLinkedQueue는 lock-free 알고리즘을 구현한 컬렉션이다. 여러 개의 스레드가 동시에 접근하는 경우, lock하지 않고, 최소한 하나으 ㅣ스레드가 안전하게 요소를 저장하거나 얻도록 해준다.