# ITEM 47: 반환 타입으로는 스트림보다 컬렉션이 낫다.

`Collection` 인터페이스는 `Iterable`의 하위 타입이고, `stream` 메서드도 제공하여 즉, 반복과 스트림을 동시에 지원한다.
그러므로 원소 시퀀스를 반환하는 공개 API의 반환 타입에는 **`Collection` 이나 그 하위 타입을 쓰는 것이 좋다.**
하지만, 단지 컬렉션을 반환한다는 이유로 덩치가 큰 시퀀스를 메모리에 올려서는 안된다.

## 스트림 반복분

`Stream` 인터페이스는 `Iterable` 인터페이스가 정의한 추상 메서드를 전부 포함할 뿐만 아니라 ,`Iterable` 인터페이스가 정의한 방식대로 동작한다.
하지만, `Iterable`을 확장하고 있지 않기 때문에 for-each로 스트림을 반복할 수 없다.

만약 `Stream`을 반복문으로, `Iterable`을 `Stream`으로 사용하고 싶은 경우에는 각각 중개해주는 어댑터를 사용하면 된다.
하지만, 어댑터를 사용하는 방법은 난잡하고, 직관성이 떨어지므로 쓰지 않는 것을 권장한다.

### Stream -> Iterable 어댑터

```java
public static <E> Iterable<E> iterableOf(Stream<E> stream){
  return stream::iterator;
}
```

`Stream<E>`를 `Iterable<E>`로 중개해주는 어댑터를 사용하면 어떠한 스트림도 for-each 반복문을 사용할 수 있다.

```java
for(ProcessHandle p : iterableOf(ProcessHandle.allProcesses())){
  // 프로세스 처리 로직
}
```

### Iterable -> Stream 어댑터

```java
public static <E> Stream<E> streamOf(Iterable<E> iterable){
  return StreamSupport.stream(iterable.spliterator(), false);
}
```

 다음은 `Iterable<E>`를 `Stream<E>`로 중개해주는 어댑터이다. 

## 전용 컬렉션 구현

**반환할 시퀀스가 크지만 표현을 간결하게 할 수 있다면 전용 컬렉션을 구현하는 방안을 검토**하는 것이 좋다.
멱집합을 반환하는 경우, 원소 개수가 n개이면 멱집합의 원소 개수는 2^n개로 표준 컬렉션 구현체에 저장하는 것은 옳지 않다. 하지만 `AbstractList`를 이용해 전용 컬렉션을 쉽게 구현할 수 있다.

```java
public class PowerSet {
  public static final <E> Collection<Set<E>> of(Set<E> s) {
    List<E> src = new ArrayList<>(s);
    if(src.size() > 30) {
      // int size이므로 최대길이 제한이 있음.(컬렉션 반환 타입 단점)
      throw new IllegalArgumentException("집합에 원소가 너무 많습니다.(원소 최대 30개) : " + s);
    }
    
    return new AbastractList<Set<E>>() {
      @Override public int size() {
        return 1 << src.size();
      }
      
      @Override public boolean contains(Object o){
        return o instanceof Set && src.containsAll((Set)o);
      }
      
      @Override public Set<E> get(int index){
        Set<E> result = new HashSet<>();
        for(int i = 0; index !=0; i++, index >>= 1){
          if((index & 1) == 1){
            result.add(src.get(i));
          }
        }
        return result;
      }
    }
  }
}
```

`AbstractCollection`을 활용해 `Collection` 구현체를 작성할때는 아래 3개 메서드는 반드시 구현해야한다.

-  `Iterable`용 메서드
-  `contains`
-  `size`

만약, `contains`와 `size`를 구현하는게 불가능한 경우 `Stream` 이나 `Iterable`로 구현하는 것이 낫다.
이렇게 전용 컬렉션을 구현하는 것이 스트림보다 약 1.4배 정도 더 빨랐으며, 어댑터 형식은 스트림보다 약 2.3배 더 느리다고 한다.(이펙티브 자바 저자의 컴퓨터 기준)

