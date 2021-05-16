# ITEM 13: OVERRIDE CLONE JUDICIOUSLY

```java
public interface Cloneable {
}
```

메서드 하나 없는 **`Cloneable` 인터페이스는 Object의 protected 메서드인 `clone`의 동작방식을 결정**한다. `Cloneable`을 구현한 클래스의 인스턴스에서 `clone`을 호출하면 그 객체의 필드들을 하나하나 복사한 객체를 반환하며, 구현하지 않은 클래스의 인스턴스에서 호출하면 `CloneNotSupportException`을 던진다.

인터페이스를 구현한다는 것은 일반적으로 해당 클래스가 그 인터페이스에서 정의한 기능을 제공한다고 선언하는 행위인데, `Cloneable`의 경우에는 상위 클래스에 정의된 동작 방식을 변경한 것이므로 따라하는 것은 좋지 않다.

불변 클래스는 굳이 `clone`을 제공하지 않는 것이 좋다.

```java
public final class PhoneNumber implements Cloneable{
    private final short areaCode, prefix, lineNum;
    private int hashCode;
    
    @Override
    public PhoneNumber clone(){
        try{
            // 형변환
            return (PhoneNumber) super.clone();
        }catch (CloneNotSupportedException e){
            throw new AssertionError();
        }
    }
}
```

```java
public class Object {

    @HotSpotIntrinsicCandidate
    protected native Object clone() throws CloneNotSupportedException;
```

try-catch로 구현한 이유는 Object의 `clone()`이 `CloneNotSupportedException`을 던져주고 있기 때문이며, `Cloneable`을 구현하면 `CloneNotSupportedException`이 발생하지 않을 것을 안다.

Object 메서드는 `CloneNotSupportedException`을 던진다고 선언했지만, 재정의한 메소드에서는 `throws`절을 없애는 것이 좋다. 검사 예외를 던지지 않아야 그 메서드를 사용하기 편하기 때문이다.([비검사 예외-item71]())

**`clone()`은 원본 객체에 아무런 해를 끼치지 않는 동시에 복제된 객체의 불변식을 보장해야한다.** 

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

위 stack 클래스는 가변객체를 참조하고 있다.

```java
    @Override
    public Stack clone() {
        try{
            Stack result = (Stack) super.clone();
            result.elements = elements.clone();
            return result;
        }catch (CloneNotSupportedException e){
            throw new AssertionError();
        }
    }
```

원본 객체를 유지하면서 복제된 객체의 불변을 유지하는 가장 쉬운 방법은 **elements 배열의 `clone`을 재귀적으로 호출**해주는 것이다 .이때, 배열의 clone은 런타임 타입과 컴파일타임 타입 모두가 원본 배열과 똑같은 배열을 반환하므로 별도로 형변환을 해줄 필요는 없다. 따라서 **배열을 복제할 때는 배열의 clone 메서드를 사용하는 것을 권장**한다.

한편 위 Stack 클래스의 elements 필드가 final이었다면 final 필드는 새로운 값을 할당할 수 없기때문에 위 clone() 메서드 방식은 작동하지 않는다.

**Cloneable 아키텍처는 가변 객체를 참조하는 필드는 final로 선언하라는 일반 용법과 충돌한다.** 원본과 복제된 객체가 가변 객체를 공유해도 된다면 상관없지만, 복제할 수 있는 클래스를 만들기 위해 일부 필드에서 `final` 한정자를 제거해야할 수도 있다.

```java
public class HashTable implements Cloneable{
    private Entry[] buckets = new Entry[10];

    private static class Entry {
        final Object key;
        Object value;
        Entry next;

        Entry(Object key, Object value, Entry next){
            this.key = key;
            this.value = value;
            this.next = next;
        }


        Entry deepCopy(){
            // 해당 엔트리가 가리키는 연결 리스트를 재귀적으로 복사
            // 재귀 호출이기 때문에, 리스트의 원소 수 만큼 스택 프레임을 소비해 리스트가 길면 스택 오버플로우 발생 위험 있음.
            // return new Entry(key, value, next == null ? null : next.deepCopy());

            // 스택오버플로우 문제를 피하기 위해 반복자를 사용
            Entry result = new Entry(key,value, next);
            for(Entry p = result; p.next != null; p = p.next)
                p.next = new Entry(p.next.key, p.next.value, p.next.next);
            return result;
        }
    }

    /**
     * 잘못된 Clone
     * 원본과 같은 연결 리스트를 참조 해 원본과 복제본 모두 예기치 않게 동작할 가능성 생김
     * @return
     * @Override
     *     public  HashTable clone(){
     *         try{
     *             HashTable result = (HashTable) super.clone();
     *             result.buckets = buckets.clone();
     *             return result;
     *         }catch (CloneNotSupportedException e){
     *             throw new AssertionError();
     *         }
     *     }
     */


    /**
     *
     * @return
     */
    @Override
    public  HashTable clone(){
        try{
            HashTable result = (HashTable) super.clone();
            result.buckets = new Entry[buckets.length];
            for(int i =0 ; i < buckets.length; i++){
                if(buckets[i] != null){
                    result.buckets[i] = buckets[i].deepCopy();
                }
            }
            return result;
        }catch (CloneNotSupportedException e){
            throw new AssertionError();
        }
    }
}
```

`HashTable` 클래스를 보면, `Stack`과 동일한 방법으로 `clone()`을 구현하면 원본과 같은 연결 리스트를 참조 해 원본과 복제본 모두 예기치 않게 동작할 가능성 생길 수 있기때문에, `deepCopy()`를 별도로 구현하여 해당 엔트리가 가리키는 연결 리스트를 재귀적으로 복사해주었다.

`clone()` 메서드는 재정의될 수 있는 메서드를 호출해서는 안된다. 만약 `clone()`이 하위 클래스에서 재정의한 메서드를 호출하면, 하위 클래스는 복제 과정에서 자신의 상태를 교정할 수 있는 기회를 일게되어 원본과 상태가 달라질 가능성이 커지게된다.

요약하자면, `Cloneable`을 구현하는 모든 클래스는 `clone()`을 재정의해야 한다. 이때 접근 제한자는 public으로, 반환 타입은 클래스 자신으로 변경한다. 가장 먼저 `super.clone` 을 호출한 후 필요한 필드를 전부 적절히 수정해줘야 한다. 일반적으로 '깊은 구조'에 숨어 있는 모든 가변 객체를 복사하고, 복제본이 가진 객체 참조 모두가 복사된 객체들을 가리키게 해야한다. 기본 타입 필드와 불변 객체 참조만을 갖는 클래스라면 아무 필드도 수정할 필요는 없다.



`Cloneable`을 구현하지 않은 클래스라면 **복사 생성자와 복사 팩터리라는 더 나은 객체 복사 방식을 제공할 수 있다.**

```java
// 복사생성자
public Item(Item item){...};
```

```java
// 복사 팩터리
public static Item newInstance(Item item){...};
```

복사 생성자란 단순히 자신과 같은 클래스의 인스턴스를 인수로 받는 생성자를 말한다.

복사 생성자/팩터리는

- 생성자를 쓰지 않는 방식의 객체 생성 메커니즘을 사용하지 않는다.
- 엉성하게 문서화된 규약에 기대지 않고, 정상적인 final 필드 용법과도 충돌하지 않는다.
- 불필요한 검사 예외를 던지지 않고, 형변환도 필요치 않는다.
- **해당 클래스가 구현한 인터페이스 타입의 인스턴스를 인수로 받을 수 있다.**

모든 범용 컬렉션 구현체는 `Collection` 이나 `Map` 타입을 받는 생성자를 제공한다. 이를 이용하면 클라이언트는 원본의 구현 타입에 얽매이지 않고 복제본의 타입을 직접 선택할 수 있다. (`HashSet`을 `TreeSet` 타입으로 복제 가능)

```java
new TreeSet<>(s);
```

