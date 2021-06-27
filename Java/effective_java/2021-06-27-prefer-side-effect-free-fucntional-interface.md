# ITEM 46: 스트림에서 부작용 없는 함수를 사용해라

시작전 `Lambda`, `Collection`, `Stream` 이 선행되어야 한다.

- [Lambda](https://github.com/dh00023/TIL/blob/master/Java/문법/java-lambda.md)
- [Collection - List, Set](https://github.com/dh00023/TIL/blob/master/Java/문법/java-collection.md)
- [Collection - Map](https://github.com/dh00023/TIL/blob/master/Java/문법/2020-03-13-map.md)
- [Collection - Tree](https://github.com/dh00023/TIL/blob/master/Java/문법/2020-03-24-tree.md)
- [Collection - Stack, Queue](https://github.com/dh00023/TIL/blob/master/Java/문법/2020-03-24-stackAndQueue.md)
- [Stream](https://github.com/dh00023/TIL/blob/master/Java/문법/2020-03-25-stream.md)

---

스트림은 함수형 프로그래밍에 기초한 패러다임으로, 스트림이 제공하는 표현력, 속도, 병렬성을 얻으려면 패러다임을 받아들여야한다.

## 스트림 패러다임

스트림 패러다임의 핵심은 **계산을 일련의 변환으로 재구성하는 부분**이다.
각 변환 단계는 가능한 이전 단계의 결과를 받아 처리하는 **순수 함수**여야한다.

* 순수함수 : 오직 입력만이 결과에 영향을 주는 함수
    * 다른 가변 상태를 참조하지 않음
    * 함수 스스로 다른 상태를 변경하지 않음

순수 함수이기 위해서는 스트림 연산에 건네는 함수 객체는 모두 부작용(side effect)이 없어야한다.
이제 예를 보면서, 올바른 스트림 패러다임에 대해서 알아볼 것이다.

### 스트림 패러다임은 이해하지 못한채 API만 사용한 예

```java
Map<String, Long> freq = new HashMap<>();
try(Stream<String> words = new Scanner(file).tokens()) {
  words.forEach(word -> {
    freq.merge(word.toLowerCase(), 1L, Long::sum);
  });
}
```

위 코드는 스트림 코드를 가장한 반복적 코드로, 스트림 API의 이점을 살리지 못하고 있다.

- `forEach` : **스트림이 수행한 연산 결과를 보여줄 때 사용하고, 계산할 때는 사용하지 말자**.
    (스트림 계산 결과를 기존 컬렉션에 추가하는 등 다른 용도로도 쓸 수 있다.)

`forEach` 내부에서 외부 상태(`freq`)를 수정하는 람다를 실행하고 있으므로 순수 함수가 아닌 것을 볼 수 있다.
또한, 같은 기능의 반복문보다 코드가 길고, 읽기 어려우며, 유지보수에도 좋지 않다.

다음 예는 위 예제 코드를 올바르게 작성한 것이다.

```java
Map<String, Long> freq;
try(Stream<String> words = new Scanner(file).tokens()) {
  freq = words.collect(groupingBy(String::toLowerCase, counting()));
}
```

스트림 API를 제대로 사용했으며, 코드도 짧고 명확하다.

### Collector

- `java.util.stream.Collectors`  : 자주 사용하는 API 제공
    - `Collectors` 의 멤버를 정적 임포트(static import)해 사용하면, 스트림 가독성이 좋아짐
- 스트림의 원소를 손쉽게 컬렉션으로 생성 가능
- 최종 처리(스트림 종료 작업)



#### toList()

```java
List<String> topTen = freq.keySet().stream()
  .sorted(comparing(freq::get).reversed()) // Comparator.comparing
  .limit(10)
  .collect(toList()); // List 형태로 반환
```



#### toMap()

- `toMap(keyMapper, valueMapper)` : 각 원소가 고유한 키에 매핑되어 있을 때 적합

    ```java
    private static final Map<String, Operation> stringToEnum = Stream.of(values()).collect(toMap(Object::toString, e -> e));
    ```

- 인수 3개 받는 `toMap` : 어떤 키와 그 키에 연관된 원소들 중 하나를 골라 연관 짓는 맵을 만들때 유용

    ```java
    Map<Artist, Album> topHits = albums.collect(
      toMap(Album::artist, a->a, maxBy(comparing(Album::sales)))); // 
    ```

    - 마지막에 쓴 값을 취하는 수집기

      ```java
      toMap(keyMapper, valueMapper, (oldVal, newVal) -> newVal);
      ```
      ```java
      Stream<String> s = Stream.of("apple", "banana", "apricot", "orange", "apple");
      Map<Character, String> m = s.collect(Collectors.toMap(s1 -> s1.charAt(0), s1 -> s1, (oldVal, newVal) -> oldVal + "|" + newVal)); 
      // {a=apple|apricot|apple, b=banana, o=orange} 
      ```

- 네번째 인수로 맵 팩터리(`EnumMap`, `TreeMap`, `HashMap`)를 받는 toMap

    ```java
    Stream<String> s = Stream.of("apple", "banana", "apricot", "orange", "apple");
    LinkedHashMap<Character, String> m = s.collect(
                   Collectors.toMap(s1 -> s1.charAt(0), s1 -> s1, (s1, s2) -> s1 + "|" + s2,
                                                    LinkedHashMap::new));
    ```

#### groupingBy()

- 입력으로 분류 함수(classifier)를 받고 출력으로 원소들을 카테고리별로 모아 놓은 맵을 담은 수집기 반환한다.

  ```java
  List<Product> productList = Arrays.asList(new Product(23, "potatoes"),
                  new Product(14, "orange"),
                  new Product(13, "lemon"),
                  new Product(23, "bread"),
                  new Product(13, "sugar"));
   
   
  Map<Integer, List<Product>> collectorMapOfLists = productList.stream()
    .collect(Collectors.groupingBy(Product::getAmount));
  ```
  
  ```java
  words.collect(groupingBy(word -> alphabetize(word)));
  ```
  
- `groupingBy`가 반환하는 수집기(`collector`)가 **리스트 외의 값**을 갖는 맵을 생성하게 할 때 사용

    - 다운스트림 수집기(해당 카테고리의 모든 원소를 담은 스트림으로부터 값을 생성)도 명시 필요

    - `toSet()` : 원소들의 리스트가 아닌 집합(Set)을 값으로 갖는 맵 생성

    - `toCollection(collectionFactory)` : 컬렉션을 값으로 갖는 맵 생성

    - `counting()` : 각 키를 해당 키에 속하는 원소의 개수와 매핑한 맵 생성

        ```java
        Map<String, Long> freq = words.collect(groupingBy(String::toLowerCase, counting()));
        ```

- 다운스트림 수집기에 더해 맵 팩터리도 지정 : 맵과 그 안에 담긴 컬렉션 타입 모두 지정 가능

    - ex)값이  `TreeSet`인 `TreeMap` 반환하는 수집기

- `groupingByConcurrent` : 위 3개 `groupingBy`에 각각 대응하는 메서드의 동시 수행 버전, `ConcurrentHashMap` 인스턴스 생성

#### partitionBy

분류 함수 자리에 `Predicate` 를 받고, 키가 `Boolean` 인 맵을 반환한다.

#### minBy, maxBy

인수로 받은 비교자를 이용해 스트림에서 값이 가장 작은/큰 원소를 찾아 반환한다.

#### joining

`CharSequence` 인스턴스의 스트림에만 적용 가능하다.

- 매개변수가 없는 `joining`은 단순히 원소들을 연결하는 수집기를 반환
- 1개 인자를 넣으면 구분자를 추가한 문자열 생성
- 인수 3개 : 접두문자(prefix) + 구분문자  + 접미문자(suffix)
    - ex) 접두 : `[` , 구분 `,`, 접미 : `]` -> [came, saw, conquered]로 출력

