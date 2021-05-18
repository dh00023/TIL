# ITEM 20 : 추상 클래스보다 인터페이스를 우선하라

자바가 제공하는 다중 구현 메커니즘은 **인터페이스와 추상 클래스** 두가지이다. Java8부터 인터페이스도 디폴트 메서드를 제공할 수 있게되어, 두 메커니즘 모두 인스턴스 메서드를 구현 형태로 제공할 수 있다.  인터페이스와 추상 클래스의 가장 큰 차이점은 추상 클래스가 정의한 타입을 구현하는 클래스는 반드시 추상 클래스의 하위 클래스가 되어야한다는 점이다. 반면 인터페이스는 선언한 메서드를 모두 정의하고 그 일반 규약을 잘 지킨 클래스라면 다른 어떤 클래스를 상속했든 같은 타입으로 취급 된다. 

**기존 클래스에도 손쉽게 새로운 인터페이스를 구현할 수 있다.** 클래스 선언에 `implements` 구문만 추가하면 된다. 반면 새로운 추상 클래스를 기존 클래스에 추가하는 것은 어렵다.  두 클래스가 같은 추상 클래스를 확장하기 원하는 경우, 그 추상 클래스는 계층 구조상 두 클래스의 공통 조상이어야하며, 새로 추가된 추상 클래스의 모든 자손이 이를 상속하게 되는 것이다.

**인터페이스는 mixin(믹스인) 정의에 안성맞춤**이다. mixin은 클래스가 구현할 수 있는 타입으로, 믹스인을 구현한 클래스는 원래의 주된 타입 외에도 특정 선택적 행위를 제공한다고 선언하는 효과를 준다. `Comparable`은 mixin 인터페이스로, 자신을 구현한 클래스의 인스턴스들끼리는 순서를 정할 수 있다. 이처럼 **대상 타입의 주된 기능에 선택적 기능을 혼합(mixed in)한다고해서 믹스인**이라 부르며, 추상클래스는 기존 클래스에 덧씌울 수 없기 때문에 믹스인을 정의할 수 없다.

**인터페이스로는 계층구조가 없는 타입 프레임워크를 만들 수 있다.**  타입을 계층적으로 정의하면 수많은 개념을 구조적으로 잘 표현할 수 있지만, 현실에서는 계층을 엄격히 구분하기 어려운 개념도 있다.

```java
public interface Singer{
    AudioClip sing(Song s);
}
```

```java
public interface SongWriter{
    Song compose(int chartPosition);
}
```

```java
public interface SingerSongWriter extends Singer, SongWriter{
    AudioClip strum();
    void actSensitive();
}
```

위 코드처럼 타입을 인터페이스로 정의하면 가수 클래스가 `Singer`와 `SongWriter` 클래스를 모두 구현해도 전혀 문제되지 않으며,  `Singer`, `SongWriter` 인터페이스를 모두 확장하고 새로운 메서드까지 추가해 제 3의 인터페이스도 정의할 수 있다. 이 정도의 유연성이 항상 필요하지는 않지만, 같은 구조를 클래스로 만들려면 가능한 조합 전부를 각각의 클래스로 정의한 거대한 계층구조가 만들어 질 것이다. 이러한 거대한 클래스 계층구조에는 공통 기능을 정의해 놓은 타입이 없으니, 매개변수 타입만 다른 메서드들을 수없이 많이 가진 클래스를 낳을 수 있다.

**[Wrapper Class](./2021-02-12-use-composition.md)와 함께 사용하면 인터페이스는 기능을 향상시키는 안전하고 강력한 수단이 된다.** 추상클래스는 새로운 기능을 추가하는 방법은 상속 뿐이며, 상속해서 만든 클래스는 래퍼 클래스보다 활용도가 떨어지고 깨지기 쉬운 경우가 더 많다.

```java

    /**
     * Removes all of the elements of this collection that satisfy the given
     * predicate.  Errors or runtime exceptions thrown during iteration or by
     * the predicate are relayed to the caller.
     *
     * @implSpec
     * The default implementation traverses all elements of the collection using
     * its {@link #iterator}.  Each matching element is removed using
     * {@link Iterator#remove()}.  If the collection's iterator does not
     * support removal then an {@code UnsupportedOperationException} will be
     * thrown on the first matching element.
     *
     * @param filter a predicate which returns {@code true} for elements to be
     *        removed
     * @return {@code true} if any elements were removed
     * @throws NullPointerException if the specified filter is null
     * @throws UnsupportedOperationException if elements cannot be removed
     *         from this collection.  Implementations may throw this exception if a
     *         matching element cannot be removed or if, in general, removal is not
     *         supported.
     * @since 1.8
     */
    default boolean removeIf(Predicate<? super E> filter) {
        Objects.requireNonNull(filter);
        boolean removed = false;
        final Iterator<E> each = iterator();
        while (each.hasNext()) {
            if (filter.test(each.next())) {
                each.remove();
                removed = true;
            }
        }
        return removed;
    }
```

인터페이스의 메서드 중 구현 방법이 명백한 것이 있다면, 디폴트 메서드로 제공해 프로그래머의 일을 덜어줄 수 있다. 디폴트 메서드는 `Composition` 인터페이스의 `removeIf()` 메서드를 참고하면되고, 디폴트 메서드 제공시 `@implSpec`으로  상속하려는 사람에게 설명을 해줘야한다. 디폴트 메서드에도 다음과 같은 제약이 있다. `equals`, `hashCode`는 디폴트 메서드로 제공해서는 안된다. 또한, 인터페이스는 인스턴스 필드를 가질 수 없고, public이 아닌 정적 멤버도 가질 수 없다.(private 정적 메서드는 예외) 마지막으로, 직접 구현하지 않은 인터페이스에는 디폴트 메서드를 추가할 수 없다.

인터페이스와 추상 골격 구현 클래스를 함께 제공하는 식으로 인터페이스와 추상 클래스의 장점을 모두 취하는 방법도 있다. 인터페이스로는 타입을 정의하고, 골격 구현 클래스는 나머지 메서드를 구현한다. 이렇게 구현하면 단순히 골격 구현을 확장하는 것만으로 이 인터페이스를 구현하는데 필요한 일이 대부분 완료되며, 이는 바로 [템플릿 메서드 패턴](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/2020-03-20-template_method_pattern.md)이다.

```java
static List<Integer> intArrayAsList(int[] a){

    Objects.requireNonNull(a);
  
    // Java9부터 다이아몬드 연산자를 아래와 같이 사용 가능. 더 낮은 버전에서는 AbstractList<Integer>로 변경
    return new AbstractList<>(){
      
        // AbstractList의 abstract 메서드로 반드시 구현해야함
        @Override public Integer get(int i){
            return a[i]; 
        }
      
        // 선택적으로 구현
        @Override public Integer set(int i,Integer val){
            int oldVal = a[i];
            a[i] = val;
            return oldVal;
        }
        
        // AbstractCollection의 abstract 메서드로 반드시 구현해야함
        @Override public int size(){
            return a.length; 
        }
    }
}
```


이 예시는 int 배열을 받아 Integer 인스턴스의 리스트 형태로 보여주는 [Adapter](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/2021-02-14-adapter-pattern.md)이기도 하다. 이 구현에서는 [익명 클래스 - item 24](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-14-favor-static-memeber.md)형태를 사용했다.

**골격 구현 클래스는 추상 클래스처럼 구현을 도와주는 동시에 추상 클래스로 타입을 정의할 때 따라오는 제약에서 자유롭다**. 반드시 이렇게 구현해야하는 것은 아니며, 구조상 골격 구현을 확장하지 못한다면 인터페이스를 직접 구현하면 된다. 이러한 경우에도 인터페이스가 직접 제공하는 디폴트 메서드를 여전히 누릴 수 있으며, 골격 구현 클래스를 우회적으로 이용할 수 있다. 인터페이스를 구현한 클래스에서 해당 골격 구현을 확장한 private 내부 클래스를 정의하고, 각 메서드 호출을 내부 클래스의 인스턴스에 전달하는 것이다. 이 방식을 simulated muliple inheritance라 하며, 다중 상속의 많은 장점을 제공하면서 동시에 단점은 피하게 해준다.

골격 구현 작성은 다음 순서를 따르면 된다.

1. 다른 메서드들의 구현에 기반 메서드 선정
2. 기반 메서드들을 사용해 직접 구현할 수 있는 메서드를 모두 디폴트 메서드로 제공
3.  단, equals(), hashCode()는 제공하면 안된다.
4. 기반 메서드나 디폴트 메서드로 만들지 못한 메서드가 남아 있다면, 인터페이스를 구현하는 골격 구현 클래스를 만들어 남은 메서드를 작성
5. 골격 구현은 기본적으로 상속이므로, 설계 및 문서화 지침을 따라야 한다.

```java
// Map.Entry 인터페이스나 그 하위 인터페이스로는 이 골격 구현 제공 불가능
// equals, hashCode, toString 재정의 할 수 없기 때문
public abstract class AbstractMapEntry<K,V> implements Map.Entry<K,V>{

    // 변경 가능한 엔트리는 이 메서드를 반드시 재정의
    @Override public V setValue(V value){
        throw new UnsupportedOperationException();
    }

    // Map.Entry.equals의 일반 규약 구현
    @Override public boolean equals(Object o){
        if(o == this) return true;
        if(!(o instanceof Map.Entry)) return false;
        Map.Entry<?,?> e = (Map.Entry) o;
        return Objects.equals(e.getKey(), getKey())
                && Objects.equals(e.getValue(), getValue());
    }
    
    // Map.Entry.hashCode 일반 규약 구현
    @Override public int hashCode() {
        return Objects.hashCode(getKey()) ^ Objects.hashCode(getValue());
    }
    
    @Override public String toString(){
        return getKey() + "=" +getValue();
    }

}
```



**단순구현은 골격 구현의 작은 변종이다. 단순 구현도 골격 구현과 같이 상속을 위해 인터페이스를 구현한 것이지만, 추상 클래스가 아니란 점이 다르다.**

`AbstractMap.SimpleEntry`가 대표적인 예이다.

```java
    public static class SimpleEntry<K,V>
        implements Entry<K,V>, java.io.Serializable
    {
        private static final long serialVersionUID = -8499721149061103585L;

        private final K key;
        private V value;

        /**
         * Creates an entry representing a mapping from the specified
         * key to the specified value.
         *
         * @param key the key represented by this entry
         * @param value the value represented by this entry
         */
        public SimpleEntry(K key, V value) {
            this.key   = key;
            this.value = value;
        }

        /**
         * Creates an entry representing the same mapping as the
         * specified entry.
         *
         * @param entry the entry to copy
         */
        public SimpleEntry(Entry<? extends K, ? extends V> entry) {
            this.key   = entry.getKey();
            this.value = entry.getValue();
        }

        /**
         * Returns the key corresponding to this entry.
         *
         * @return the key corresponding to this entry
         */
        public K getKey() {
            return key;
        }

        /**
         * Returns the value corresponding to this entry.
         *
         * @return the value corresponding to this entry
         */
        public V getValue() {
            return value;
        }

        /**
         * Replaces the value corresponding to this entry with the specified
         * value.
         *
         * @param value new value to be stored in this entry
         * @return the old value corresponding to the entry
         */
        public V setValue(V value) {
            V oldValue = this.value;
            this.value = value;
            return oldValue;
        }

        /**
         * Compares the specified object with this entry for equality.
         * Returns {@code true} if the given object is also a map entry and
         * the two entries represent the same mapping.  More formally, two
         * entries {@code e1} and {@code e2} represent the same mapping
         * if<pre>
         *   (e1.getKey()==null ?
         *    e2.getKey()==null :
         *    e1.getKey().equals(e2.getKey()))
         *   &amp;&amp;
         *   (e1.getValue()==null ?
         *    e2.getValue()==null :
         *    e1.getValue().equals(e2.getValue()))</pre>
         * This ensures that the {@code equals} method works properly across
         * different implementations of the {@code Map.Entry} interface.
         *
         * @param o object to be compared for equality with this map entry
         * @return {@code true} if the specified object is equal to this map
         *         entry
         * @see    #hashCode
         */
        public boolean equals(Object o) {
            if (!(o instanceof Map.Entry))
                return false;
            Map.Entry<?,?> e = (Map.Entry<?,?>)o;
            return eq(key, e.getKey()) && eq(value, e.getValue());
        }

        /**
         * Returns the hash code value for this map entry.  The hash code
         * of a map entry {@code e} is defined to be: <pre>
         *   (e.getKey()==null   ? 0 : e.getKey().hashCode()) ^
         *   (e.getValue()==null ? 0 : e.getValue().hashCode())</pre>
         * This ensures that {@code e1.equals(e2)} implies that
         * {@code e1.hashCode()==e2.hashCode()} for any two Entries
         * {@code e1} and {@code e2}, as required by the general
         * contract of {@link Object#hashCode}.
         *
         * @return the hash code value for this map entry
         * @see    #equals
         */
        public int hashCode() {
            return (key   == null ? 0 :   key.hashCode()) ^
                   (value == null ? 0 : value.hashCode());
        }

        /**
         * Returns a String representation of this map entry.  This
         * implementation returns the string representation of this
         * entry's key followed by the equals character ("{@code =}")
         * followed by the string representation of this entry's value.
         *
         * @return a String representation of this map entry
         */
        public String toString() {
            return key + "=" + value;
        }

    }
```