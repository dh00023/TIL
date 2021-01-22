# ITEM 7: ELIMINATE OBSOLETE OBJECT REFERENCES

자바는 가비지 컬렉터가 다 쓴 객체를 알아서 회수해간다고 메모리 관리에 더 이상 신경 쓰지 않아도 되는 것은 아니다.

```java
public class Stack {
  	private Object[] elements;
  	private int size = 0;
  	private static final int DEFAULT_CAPACITY = 16;
  
  	public Stack() {
      	elements = new Object[DEFAULT_CAPACITY];
    }
  
  	public void push(Object e){
      	ensureCapacity();
      	elements[size++] = 0;
    }
  	
  	public Object pop(){
      	if(size == 0){
          	throw new EmptyStackException();
        }
      	return elements[--size];
    }
  
  	// 원소를 위한 공간을 적어도 하나 이상 여유를 두며, 늘려야하는 경우 두배 이상 늘린다.
  	private void ensureCapacity(){
      	if(elements.length == size){
          	elements = Arrays.copyOf(elements, 2*size+1);
        }
    }
}
```

위 스택 코드에는 **메모리 누수** 문제점이 있다.  위의 스택을 사용하는 프로그램을 오래 실행하면, 점차 GC 활동과 메모리 사용량이 늘어나 결국 성능이 저하될 것이다. 상대적으로 드문 경우이지만 심할 때는 디스크 페이징이나 **`OutOfMemoryError`**를 일으켜 예기치 않게 종료되기도 한다.

위 스택은 스택이 늘었다가 주는 경우에 스택에서 꺼내진 객체들을 가비지 컬렉터가 회수 하지 않는다. 이 스택이 그 객체들의 다 쓴 참조(obsolete reference: 앞으로 다시 쓰지 않을 참조)를 여전히 가지고 있기 때문이다.

객체 참조 하나를 살려두면 GC는 그 객체뿐만 아니라 그 객체가 참조하는 모든 객체를 회수해가지 못한다. 그래서 단 몇 개의 객체가 매우 많은 객체를 회수되지 못하게 할 수 있고, 잠재적으로 성능에 악영향을 줄 수 있다.

```java
		public Object pop(){
      	if(size == 0){
          	throw new EmptyStackException();
        }
      	Object result = elements[--size];
      	elements[size] = null;
      	return result;
    }
```

이는 다음과 같이  **null 처리** 를 통해 해당 참조 해제 처리를 하여 해결할 수 있다. 다 쓴 참조를 `null` 처리하여 실수로 해당 참조를 사용하려고 하면 시스템은 즉시 `NullPointException` 을 던지며 종료되며, 프로그램 오류는 가능한 초반에 발견하는 것이 좋다.

하지만 모든 객체를 다 쓰자마자 `null` 처리를 할 필요는 없고, 이는 필요 이상으로 프로그램을 지저분하게 만들 수 있다. **객체 참조를 null 처리하는 일은 예외적인 경우여야 한다.** 다쓴 참조를 해제하는 가장 좋은 방법은 **그 참조를 담은 변수를 유효 범위(scope) 밖으로 밀어내는 것**이다. 

위 Stack class는 자기 메모리를 직접 관리하기 때문에 메모리 누수에 취약하다. 객체 참조를 담는 elements 배열로 저장소 풀을 만들어 원소를 관리하는데, GC는 해당 배열에서 비활성화 영역에 참조하는 객체를 똑같이 유요한 객체로 보기 때문에 문제가 발생한다. **비활성 영역이 되는 순간 null 처리를 통해 해당 객체를 더 이상 사용하지 않는것을 GC에 알려야한다**. 이는 단순히 위 stack class만을 말하는 것이 아니며, `Collection` 클래스는 모두 주의해야한다.

**캐시 또한 메모리 누수를 일으키는 요소이다.** 객체  참조를 캐시에 넣어두고, 이 사실을 잊은 채 그 객체를 계속해서 놔두는 경우를 흔히 볼 수 있다. 이를 해결하는 방법은 여러 가지이다.

1. `WeakHashMap` : 캐시 외부에서 키를 참조하는 동안만 엔트리가 살아 있는 캐시가 필요한 상황

2. 백그라운드 스레드(`ScheduledThreadPoolExecutor`)를 활용하거나, 캐시에 새 엔트리 추가시 부수 작업으로 쓰지 않는 엔트리를 청소하는 방법

   ```java
   // LinkedHashMap은 뒤의 방법으로 사용하지 않는 엔트리를 처리
   	void afterNodeInsertion(boolean evict) { // possibly remove eldest
           LinkedHashMap.Entry<K,V> first;
           if (evict && (first = head) != null && removeEldestEntry(first)) {
               K key = first.key;
               removeNode(hash(key), key, null, false, true);
           }
       }
   ```

**리스너 혹은 콜백** 또한 메모리 누수의 요소이다. 클라이언트가 콜백만 등록하고 명확히 해지하지 않는 경우 콜백은 계속 쌓여만 갈 것이다. 이럴 때 콜백을 약한 참조로 저장하면, GC가 즉시 수거해간다.(ex) `WeakHashMap` 의 키로 저장하는 방법

## WeakHashMap

- [자바 참조 타입](../문법/java-referenceType.md#참조-방식)에 대해 선행이 필요하다.

`List`, `Map`, `Set` 같은 자바 `Collection` 클래스들을 사용할 때는 항상 주의가 필요하다. `Collection` 클래스 안에 담겨있는 인스턴스는 프로그램에서 사용여부와 관계 없이 모두 사용되는 것으로 판단되어 GC의 대상이 되지 않아 메모리 누수의 흔한 원인이 된다.

일반적인 `HashMap`의 경우 `Map`안에 Key/Value가 들어가게 되면 사용여부와 관계 없이 해당 참조는 지워지지 않는다. Key에 해당하는 객체가 더 이상 존재하지 않게되어 `null` 이 되었을 경우 `HashMap` 에서도 더 이상 꺼낼 일이 없는 경우를 예로 들어보자. `HashMap`의 경우 해당 객체가 사라지더라도 GC대상으로 잡지 못하여 컬렉션에 쌓여, 메모리 누수의 원인이 된다. 

이때 `WeakHashMap`은`WeakReference`를 이용하여 `HashMap`의 Key를 구현한 것이다.`WeakHashMap`에 있는 Key값이 더이상 사용되지 않는다고 판단되면 다음 GC때 해당 Key, Value 쌍을 제거한다. 임의로 제거되어도 상관없는 데이터들을 위해 주로 사용된다.

```java
 /**
     * The entries in this hash table extend WeakReference, using its main ref
     * field as the key.
     */
    private static class Entry<K,V> extends WeakReference<Object> implements Map.Entry<K,V> {
        V value;
        final int hash;
        Entry<K,V> next;

        /**
         * Creates new entry.
         */
        Entry(Object key, V value,
              ReferenceQueue<Object> queue,
              int hash, Entry<K,V> next) {
            super(key, queue);
            this.value = value;
            this.hash  = hash;
            this.next  = next;
        }

        @SuppressWarnings("unchecked")
        public K getKey() {
            return (K) WeakHashMap.unmaskNull(get());
        }

        public V getValue() {
            return value;
        }

        public V setValue(V newValue) {
            V oldValue = value;
            value = newValue;
            return oldValue;
        }
```

```java
public class ReferenceTest {

    public static void main(String[] args){

        HashMap<Integer, String> hashMap = new HashMap<>();

        Integer key1 = 1000;
        Integer key2 = 2000;
        Integer key3 = 3000;
        hashMap.put(key3, "test c");
        hashMap.put(key2, "test b");

        key3 = null;

        System.out.println("HashMap GC 수행 이전");
        hashMap.entrySet().stream().forEach(el -> System.out.println(el));

        System.gc();

        System.out.println("HashMap GC 수행 이후");
        hashMap.entrySet().stream().forEach(el -> System.out.println(el));

        WeakHashMap<Integer, String> map = new WeakHashMap<>();

        map.put(key1, "test a");
        map.put(key2, "test b");

        key1 = null;

        System.out.println("WeakHashMap GC 수행 이전");
        map.entrySet().stream().forEach(el -> System.out.println(el));

        System.gc();

        System.out.println("WeakHashMap GC 수행 이후");
        map.entrySet().stream().forEach(el -> System.out.println(el));

    }
}
```

```
HashMap GC 수행 이전
2000=test b
3000=test c
HashMap GC 수행 이후
2000=test b
3000=test c
WeakHashMap GC 수행 이전
1000=test a
2000=test b
WeakHashMap GC 수행 이후
2000=test b
```

`WeakHashMap`의 Value는 강한 참조에 의해 보관 유지된다. Value 객체가 직간접적으로 자신의 Key를 강한참조하지 않도록 주의해야한다. 이러한 경우에는 Key가 삭제되지 않기 때문이다. 만약 Key를 참조한느 Value를 사용해 `WeakHashMap` 또한 올바르게 동작하길 바란다면 `WeakReference`로 래핑해주는 방식을 사용하면 된다.

```java
weakHashMap.put(key, new WeakReference(value));
```



## GC 확인하기

만약 GC가 수행되고 있는 것을 확인하고 싶다면 아래 옵션을 추가해주면된다.

Intellj의 `Edit Configurations -> VM options`에 `-verbose:gc -XX:+PrintCommandLineFlags`를 추가해주면 현재 GC가 수행중인지 확인할 수 있다.

```java
public static void main(String[] args) throws InterruptedException {
        List<Integer> li = IntStream.range(1, 100).boxed().collect(Collectors.toList());
        for (int i=1; true; i++) {
            if (i % 100 == 0) {
                li = new ArrayList<>();
                Thread.sleep(100);
            }
            IntStream.range(0, 100).forEach(li::add);
        }
    }
```

```
[GC (Allocation Failure)  33246K->1292K(125952K), 0.0035248 secs]
[GC (Allocation Failure)  34572K->1284K(125952K), 0.0028950 secs]
[GC (Allocation Failure)  34564K->1200K(125952K), 0.0033107 secs]
[GC (Allocation Failure)  34480K->1268K(125952K), 0.0045468 secs]
...
```





## 참고

- [JVM\] WANR! Collections & Memory Leak](https://blog.naver.com/kbh3983/220999674350)
- [YABOONG 자바 메모리 관리 - 가비지 컬렉션](https://yaboong.github.io/java/2018/06/09/java-garbage-collection/)