# ITEM 54: null이 아닌, 빈 컬렉션이나 배열을 반환해라

- ~~컬렉션이 비었으면 null 반환(안좋은 예)~~ 

    ```java
    private final List<Cheese> cheesesInStock = ...;
    
    /**
     * @return 매장 안의 모든 치즈 목록 반환
     * 단, 재고가 없다면 null반환
     */
    public List<Cheese> getCheeses() {
      return cheesesInStock.isEmpty() ? null : new ArrayList<>(cheesesInStock);
    }
    ```

위 예처럼 `null`을 반환하면 클라이언트는 `null` 상황을 처리하는 코드를 추가로 작성해줘야한다.

```java
List<Cheese> cheeses = shop.getCheeses();
if (cheeses != null && cheeses.contains(Cheese.STILTON)){ ... } // null 예외 처리
```

다음과 같이 컨테이너(컬렉션이나 배열)가 빈 경우 `null`을 반환하는 메서드 사용시 항상 위와 같이 방어 코드를 넣어줘야한다. 실제로 객체가 0개일 가능성이 거의 없는 경우에서는 한참뒤에 오류가 발생할 수 있다. 또한, `null`을 반환하는 곳에서도 `null` 에 대한 처리를 별도로 해줘야해 코드가 더 복잡해진다.

빈컨테이너를 `null` 대신 반환해야하는 이유는 다음과 같다.

1. 성능 분석 결과 할당이 성능 저하의 주범이라고 확인되지 않는 한, 이 정도의 성능 차이는 신경 쓸 정고가 아니다.

2. 빈 컬렉션과 배열은 굳이 새로 할당하지 않고도 반환할 수 있다.

    ```java
    public List<Cheese> getCheeses() {
      return new ArrayList<>(cheesesInStock);
    }
    ```

대부분의 경우 위와 같이 대응하면 되지만, 사용 패턴에 따라서 빈 컬렉션 할당이 성능을 눈에 띄게 떨어뜨리는 경우가 있다. 이 경우에는 매번 똑같은 **불변 컬렉션을 반환**하면 된다.

- `Collections.emptyList`
- `Collections.emptySet`
- `Collections.emtpyMap`

불변 컬렉션을 사용하는 것은 최적화에 해당하므로, 꼭 필요한 경우에만 사용해야하며, 수정 전후로 성능을 측정해 개선이 됐는지 확인이 필요하다.

배열의 경우도 컬렉션과 동일하다. 배열의 경우에도 `null`을 반환하지 말고, 길이가 0인 배열을 반환하면 된다. 보통의 경우 정확한 길이의 배열을 반환하면 된다.

```java
public Cheese[] getCheeses() {
  return cheesesInStock.toArray(new Cheese[0]);
}
```

만약 성능을 떨어뜨릴 것 같다면, 길이가 0인 불변 배열을 선언해두고, 매번 그 배열을 반환하면 된다.

```java
private static final Cheese[] EMPTY_CHEESE_ARRAY = new Cheese[0];
public Cheese[] getCheeses() {
  return cheesesInStock.toArray(EMPTY_CHEESE_ARRAY);
}
```

단순히 성능을 개선하는 목적으로는 배열을 미리 할당하는 건 추천하지 않으며, 오히려 성능이 떨어진다는 보고도 있다.
