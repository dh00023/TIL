# ITEM 58: 전통적인 for 문보다는 for-each문을 사용해라

전통적인 for문과 비교시 for-each문 장점은 명료하고, 유연하고, 버그를 예방해준다. 그러면서 성능저하도 없다.

## 전통적인 for문

- 반복자와 인덱스 변수는 코드를 지저분하게 할 뿐이며, 실제로 필요한 것은 원소이다.
- 쓰이는 요소의 종류가 늘어나면 오류가 생길 가능성도 높아진다.
- 잘못된 변수를 사용했을 때 컴파일러가 잡아준다는 보장이 없다.
- 컬렉션, 배열 등 컨테이너 종류에 따라 코드 형태가 달라지므로 주의가 필요하다.

### collection 순회

```java
for (Iterator<Element> i = c.iterator(); i.hasNext();) {
  Element e = i.next();
}
```

### 배열 순회

```java
for (int i = 0; i< a.length; i++) {
}
```



위 문제는 **for-each** 문을 사용하면 해결된다. 

## for-each문

- for-each문은 반복자나 인덱스 변수를 사용하지 않아 코드가 깔끔해지고, 오류가 발생할 일도 없다.

    ```java
    for (Element e : elements) {
      
    }
    ```

- 하나의 관용구로 컬렉션과 배열 모두 처리할 수 있어, 어떤 컨테이너를 사용하는지 신경쓰지 않아도 된다.

- for-each문을 사용하는 것은 for문을 사용하는 것과 속도가 같다.

- 컬렉션을 중첩해 사용한다면, 실수를 예방할 수 있다.

    - 전통적 for문

        ```java
        enum Face { ONE, TWO, THREE, FOUR, FIVE, SIX }
        
        Collection<Face> faces = EnumSet.allOf(Face.class);
        
        for (Iterator<Face> i = faces.iterator(); i.hasNext(); )
          for (Iterator<Face> j = faces.iterator(); j.hasNext(); )
            System.out.println(i.next() + " " + j.next());
        ```

        `i.next()` 가 안쪽 for문에서 호출되었기때문에 36개 조합이 아닌, 6개 조합이 나온다. j보다 i의 수가 적다면, 예외가 발생할 수도 있다.

        ```java
        enum Suit { CLUB, DIAMOND, HEART, SPADE }
        enum Rank { ACE, DEUCE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING }
        
        static Collection<Suit> suits = Arrays.asList(Suit.values());
        static Collection<Rank> ranks = Arrays.asList(Rank.values());
        
        List<Card> deck = new ArrayList<>();
        for (Iterator<Suit> i = suits.iterator(); i.hasNext(); )
          for (Iterator<Rank> j = ranks.iterator(); j.hasNext(); )
            deck.add(new Card(i.next(), j.next())); // NoSuchElementException
        ```

        ```java
        for (Iterator<Suit> i = suits.iterator(); i.hasNext(); )
          Suit suit = i.next();
          for (Iterator<Rank> j = ranks.iterator(); j.hasNext(); )
            deck.add(new Card(suit, j.next()));
        ```
    
        다음과 같이 해결할 수 있지만, for-each문을 사용하면 더 간단하게 해결할 수 있다.
    
    - for-each문
    
        ```java
        for (Suit suit : suits)
          for (Rank rank : ranks)
            deck.add(new Card(suit, rank));
        ```

## for-each를 사용할 수 없는 경우

#### 파괴적인 필터링(destructive filtering)

컬렉션을 순회하면서 선택된 원소를 제거해야 하는경우, 반복자의 remove 메서드를 호출해야한다.

java8부터는 `Collection`의 `removeIf` 메서드를 사용해 컬렉션을 명시적으로 순회하는 것을 피할 수 있다.

#### 변형(transforming)

리스트나 배열을 순회하면서 그 원소의 값 일부 혹은 전체를 교체해야한다면 리스트의 반복자는 배열의 인덱스를 사용해야한다.

#### 병렬 반복(parallel iteration)

여러 컬렉션을 병렬로 순회해야한다면 각각의 반복자와 인텍스 변수를 사용해 엄격하고 명시적으로 제어해야한다.

## Iterable

for-each문은  `Iterable`을 구현한 객체라면 무엇이든지 순회할 수 있다.

```java
public interface Iterable<T> {
    /**
     * Returns an iterator over elements of type {@code T}.
     *
     * @return an Iterator.
     */
    Iterator<T> iterator();
}
```

원소들의 묶음을 표현하는 타입을 작성해야한다면, `Iterable`을 구현하는 것이 좋다. `Iterable`을 구현해둔다면 그 타입의 `for-each`문을 사용할 수 있기 때문이다.
