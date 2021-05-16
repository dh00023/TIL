# ITEM 18: 상속보다는 컴포지션을 사용해라

상속은 코드를 재사용하는 강력한 수단이지만, 잘못 사용하면 **상속이 캡슐화를 깨뜨려** 객체의 유연성을 해치는 설계를 하게될 수 있다. 상위 클래스가 어떻게 구현되느냐에 따라 하위 클래스의 동작에 이상이 생길 수 있다. 그러므로 상위 클래스 설계자가 확장을 충분히 고려하고 문서화를 해두지 않으면 하위 클래스는 상위 클래스의 변화에 맞춰 수정해야 한다.

## 상속을 잘못 사용한 경우

```java
public class InstrumentedHashSet<E> extends HashSet<E> {

    // 추가된 원소
    private int addCount = 0;

    public InstrumentedHashSet(){
    }

    public InstrumentedHashSet(int initCap, float loadFactor){
        super(initCap, loadFactor);
    }

    @Override public boolean add(E e){
        addCount++;
        return super.add(e);
    }

    @Override public boolean addAll(Collection<? extends E> c){
        addCount += c.size();
        return super.addAll(c);
    }

    public int getAddCount(){
        return addCount;
    }
}
```

위 클래스는 잘 구현된 것처럼 보이지만 제대로 작동하지 않는다. `addAll()`을 호출하는 경우 addCount가 잘 못 반영된다.

```java
    public boolean addAll(Collection<? extends E> c) {
        boolean modified = false;
        for (E e : c)
            if (add(e))
                modified = true;
        return modified;
    }
```

상속받은 `HashSet`의 `addAll()`에서 `add()`함수를 호출하고 있기때문이다. 이는 내부 구현 방식으로 `HashSet`문서에는 쓰여있지 않다. 이 경우 하위 클래스에서 `addAll()` 메서드를 재정의하지 않으면 당장은 제대로 동작할지 모르나 `HashSet`이 `addAll`이 `add` 메서드를 이용해 구현했음을 가정한 해법이라는 한계에 지나치지 않는다.

이처럼 자신의 다른 부분을 사용하는 self-use(자기 사용)여부는 해당 클래스의 내부 구현 방식에 해당하며, 자바 플랫폼의 전반적인 정책인지 다음 릴리즈에서도 유지될지 알 수 없다.

`addAll()` 메서드를 주어진 컬렉션을 순회하면서 원소 하나당 `add()` 메서드를 한번만 호출하는 방식으로 재정의할 수도 있다. 하지만 이 방식은 상위 클래스의 메서드 동작을 다시 구현하는 것이며, 오류가 발생하거나 성능이 떨어질 수도 있다. 또한 하위 클래스에서 접근할 수 없는 private 필드를 써야하는 경우 이 방식으로 구현 자체가 불가능하다.

이 외에도 다음 릴리즈에서 상위 클래스에 새로운 메서드가 추가되는 경우에도 문제가 생길 수 있다. 이는 메서드 재정의보다 훨씬 안전한 것은 맞지만 위험성이 전혀 없는 것은 아니다. 다음 릴리즈에서 상위 클래스에 새로운 메서드가 추가됐는데, 그게 새로 추가한 메서드와 시그니처가 같고 반환 타입은 달라 컴파일 오류가 발생하거나, 반환 타입 마저 같다면 상위 클래스의 새 메서드를 재정의한 것과 같아져 앞선 메서드 재정의 문제와 똑같은 상황이 생긴다. 또한, 새로 추가한 메서드가 상위 클래스의 메서드가 요구하는 규약을 만족하지 못할 가능성이 크다.

## Composition 사용

**Composition(컴포지션)이란** 기존 클래스를 확장하는 대신, **새로운 클래스를 만들고 private 필드로 기존 클래스의 인스턴스를 참조하는 방법**을 통해 기능을 확장시키는 것이다. 새로운 클래스의 인스턴스 메서드들은 **private 필드로 참조하는 기존 클래스의 대응하는 메서드(forwarding method)를 호출해 그 결과를 반환**하며, 이를 **forwarding(전달)**이라 한다. 이렇게 구현하면 새로운 클래스는 기존 클래스의 내부 구현 방식의 영향에서 벗어날 수 있으며, 기존 클래스에 새로운 메서드가 추가되더라도 전혀 영향을 받지 않는다.

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Set;

public class ForwardingSet<E> implements Set<E> {
    
    // private 필드로 기존 클래스의 인스턴스 참조
    private final Set<E> s;
    public ForwardingSet(Set<E> s){
        this.s = s;
    }

    @Override
    public int size() {
        return s.size();
    }

    @Override
    public boolean isEmpty() {
        return s.isEmpty();
    }

    @Override
    public boolean contains(Object o) {
        return s.contains(o);
    }

    @Override
    public Iterator<E> iterator() {
        return s.iterator();
    }

    @Override
    public Object[] toArray() {
        return s.toArray();
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return s.toArray(a);
    }

    @Override
    public boolean add(E e) {
        return s.add(e);
    }

    @Override
    public boolean remove(Object o) {
        return s.remove(o);
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return s.containsAll(c);
    }

    @Override
    public boolean addAll(Collection<? extends E> c) {
        return s.addAll(c);
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return s.retainAll(c);
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return s.removeAll(c);
    }

    @Override
    public void clear() {
        s.clear();
    }
}
```

```java
import java.util.Collection;
import java.util.Set;

public class InstrumentedSet<E> extends ForwardingSet<E> {

    // 추가된 원소
    private int addCount = 0;

    public InstrumentedSet(Set<E> s){
        super(s);
    }

    @Override public boolean add(E e){
        addCount++;
        return super.add(e);
    }

    @Override public boolean addAll(Collection<? extends E> c){
        addCount += c.size();
        return super.addAll(c);
    }

    public int getAddCount(){
        return addCount;
    }
}
```

`ForwardingSet`은 `Set` 인터페이스를 구현현했고, `Set`의 인스턴스를 인수로 받는 생성자를 생성했다. 임의의  `Set`에 기능을 덧 씌워 새로운 `Set`으로 만든 것이 이 클래스의 핵심이다.

 상속 방식은 구체 클래스 각각을 따로 확장해야 하며, 지원하고 싶은 상위 클래스의 생성자에 대응하는 생성자를 별도로 정의해줘야한다. 하지만, **컴포지션 방식은 한 번만 구현해두면 어떠한 `Set` 구현체라도 계측할 수 있으며, 기존 생성자들과도 함께 사용**할 수 있다.

```java
Set<Instant> times = new InstrumentedSet<>(new TreeSet<> cmp);
Set<E> s = new InstrumentedSet<>(new HashSet<>(INIT_CAPACITY));
```

다른 `Set`인스턴스를 감싸고 있다는 뜻에서 `InstrumentedSet`과 같은 클래스를 래퍼 클래스(wrapper class)라고 하며, 다른 `Set`에 기능을 덧 씌운다는 뜻에서 Decorator pattern(데코레이터 패턴)이라고 한다. 래퍼 객체가 내부 객체에 자기 자신의 참조를 넘기는 경우에 위임에 해당한다.

**래퍼 클래스는 단점이 거의 없으나 콜백 프레임워크와는 어울리지 않는다는 점은 주의**해야한다. 콜백 프레임워크에서는 자기 자신의 참조를 다른 객체에 넘겨서 다음 호출 때 사용하도록 한다. 내부 객체는 자신을 감싸고 있는 래퍼의 존재를 몰라 this(자신)의 참조를 넘기고, 콜백 때 래퍼가 아닌 내부 객체를 호출하게된다. 전달 메서드가 성능에 주는 영향이나 래퍼 객체가 메모리 사용량에 주는 영향은 실전에서 별다른 영향이 없다고 밝혀졌다.

## 상속은 언제 사용해야할까?

상속은 받드시 하위 클래스가 상위 클래스의 진짜 하위 타입인 상황에서만 사용해야 한다.( B is A 인 경우) 클래스 B가 클래스 A를 상속하려고 할 때 클래스 B가 클래스 A라고 확신할 수 없다면 상속해서는 안된다.

(`Stack`과  `Properties` 는 원칙을 위반한 클래스이다.)

컴포지션 대신 상속을 사용하기로 결정하기 전에 확장하려는 클래스의 API에 아무런 결함이 없는지 확인해보고, 그 결함이 하위 클래스에도 전파되도 괜찮은지 확인해 봐야한다.