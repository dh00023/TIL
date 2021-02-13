# ITEM 21 : 인터페이스는 구현하는 쪽을 생각해 설계해라

Java8의 디폴트 메서드가 추가되기 전까지는 기존 구현체를 깨뜨리지 않고 인터페이스에 메서드를 추가할 방법이 없었다. 디폴트 메서드도 위험이 완전히 사라진 것은 아니다. 디폴트 메서드를 선언하면, 그 인터페이스를 구현한 후 디폴트 메서드를 재정의하지 않은 모든 클래스에서 디폴트 구현이 쓰이게 되므로, 모든 기존 구현체와 매끄럽게 연동되리라는 보장은 없다.  즉, **생각할 수 있는 모든 상황에서 불변식을 해치지 않는 디폴트 메서드를 작성하기는 어렵다**.

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

Java8에서 `Collection` 인터페이스에추가된 `removeIf()` 메서드이다. 현재 [Apache Commons Collection  4.4](https://commons.apache.org/proper/commons-collections/download_collections.cgi)에서는 `org.apache.commons.collections4.collection.SynchronizedCollection` 에서 `removeIf()`를 아래와 같이 재정의하고 있으나, 이전 버전에서는 정의하지 않고 있다.

```java
    public boolean removeIf(Predicate<? super E> filter) {
        synchronized(this.lock) {
            return this.decorated().removeIf(filter);
        }
    }
```

이전 버전(4.3이하)을 사용하는 경우 `removeIf`를 재정의하지 않아, 디폴트 구현을 물려받아 모든 메서드 호출을 알아서 동기화해주지 못한다. `removeIf`의 구현은 동기화에 대해 아무것도 모르므로, 락 객체를 사용할 수 없으며, `SynchronizedCollection`  인스턴스를 여러 스레드가 공유하는 환경에서 `removeIf`를 호출하면 `ConcurrentModificationException`이 발생하거나 다른 예상치 못한 결과로 이어질 수 있다.

**또한, 디폴트 메서드는 컴파일에 성공하더라도 기존 구현체에 런타임 오류를 일으킬 수 있다.** 

그러므로, 기존 인터페이스에 디폴트 메서드로 새 메서드를 추가하는 일은 꼭 필요한 경우가 아니면 피해야한다. 반면, 새로운 인터페이스를 만드는 경우라면 표준적인 메서드 구현을 제공하는데 아주 유용한 수단이며, 그 인터페이스를 더 쉽게 구현해 활용할 수 있게끔 해준다. 디폴트 메서드는 인터페이스로부터 메서드를 제거하거나 기존 메서드의 시그니처를 수정하는 용도가 아님을 명시해야한다.



**디폴트 메서드가 생겼더라도, 인터페이스 설계할 때는 여전히 주의를 기울여야한다. 인터페이스를 릴리즈한 후라도 결함을 수정하는 것이 가능할 수는 있지만, 절대 그 가능성에 기대서는 안된다.**