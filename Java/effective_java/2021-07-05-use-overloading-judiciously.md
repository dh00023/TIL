# ITEM 52: 다중정의는 신중히 사용해라

```java
public class CollectionClassifier {

    public static String classify(Set<?> s) {
        return "집합";
    }

    public static String classify(List<?> lst) {
        return "리스트";
    }

    public static String classify(Collection<?> c) {
        return "그 외";
    }
}
```

```java
public class OverloadingTest {
    @Test
    void overloadingTest() {
        Collection<?>[] collections = {
                new HashSet<String>(),
                new ArrayList<BigInteger>(),
                new HashMap<String, String>().values()
        };

        Assertions.assertEquals(CollectionClassifier.classify(collections[0]), "집합");
        Assertions.assertEquals(CollectionClassifier.classify(collections[1]), "리스트");
        Assertions.assertEquals(CollectionClassifier.classify(collections[2]), "그 외");

    }
}
```

```java
org.opentest4j.AssertionFailedError: 
Expected :그 외
Actual   :집합
org.opentest4j.AssertionFailedError: 
Expected :그 외
Actual   :리스트
```

다음을 수행 시킨 경우, 실제로 수행해보면 "그 외"만 출력되는 것을 확인할 수 있다.
다중정의(overloading)는 **어느 메서드를 호출할지가 컴파일타임에 정해지기 때문**이다.
컴파일 타임에는 항상 `Collection<?>` 타입이므로, 세번째 메서드인 `classify(Collection<?>)`가 호출된 것 이다.

**재정의한 메서드(Overriding)는 동적(런타임)으로 선택되며, 다중정의(overloading)한 메서드는 정적(컴파일 타임)으로 선택된다.**

## Overriding

```java
public class Wine {
    String name() { return "포도주"; }
}
```

```java
public class SparlklingWine extends Wine{
    @Override
    String name() { return "발포성 포도주"; }
}
```

```java
public class Champane extends SparlklingWine{
    @Override
    String name() { return "샴페인"; }
}
```

```java
public class OverridingTest {

    @Test
    void overridingTest() {
        List<Wine> wineList = List.of(new Wine(), new SparlklingWine(), new Champane());

        Assertions.assertEquals(wineList.get(0).name(), "포도주");
        Assertions.assertEquals(wineList.get(1).name(), "발포성 포도주");
        Assertions.assertEquals(wineList.get(2).name(), "샴페인");
    }
}
```

`name()`  메서드는 하위클래스에서 각각 재정의하고 있다.
테스트 코드 수행시, 예상한 대로 "포도주", "발포성 포도주", "샴페인"이 출력되는 것을 확인할 수 있다.
메서드 재정의는 컴파일 타임에 그 인스턴스의 타입이 무엇인지는 상관 없으며, 가장 하위에서 재정의한 메서드가 실행되는 것이다.

## Overloading

다시 다중정의로 돌아가, 원하는 대로 값을 얻기 위해서는 다음과 같이 수정해줘야한다.

```java
public class CollectionClassifier {

    public static String classify(Collection<?> c) {
        return c instanceof Set ? "집합" :
                c instanceof List ? "리스트" : "그 외";
    }
}
```

`instanceof`로 명시적 검사로 변경하면, 이전에 실패한 테스트도 통과하는 것을 볼 수 있다.

- 다중정의가 혼란을 주는 상황은 피해야한다.
-  안전하고, 보수적으로 가려면 매개변수 수가 같은 다중정의는 만들지 말아야한다.
-  가변인수를 사용하는 메서드는 다중정의를 아예 하지 말아야한다.

### 다중정의 대안

1. 다중정의하는 대신 메서드 이름을 다르게 지어주는 방법

    ```java
        public void writeBoolean(boolean val) throws IOException {
            bout.writeBoolean(val);
        }
    
        public void writeByte(int val) throws IOException  {
            bout.writeByte(val);
        }
    
        public void writeShort(int val)  throws IOException {
            bout.writeShort(val);
        }
    
        public void writeChar(int val)  throws IOException {
            bout.writeChar(val);
        }
    ```

    `ObjectOutputStream` 클래스에서 모든 메서드에 위와 같이 다른 이름을 지어주고 있다.

2. [정적 팩터리](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-01-12-static-factory-methods.md)
    생성자의 경우 두번째 생성자부터는 무조건 다중정의가 된다. 하지만 정적 팩터리 메서드를 사용해 이름을 구분할 수 있다.

### 그 외

- 메서드 다중정의 시, 서로 다른 함수형 인터페이스라도 같은 위치의 인수로 받으면 안된다.
    - 서로 다른 함수형 인터페이스일지라도, 서로 근본적으로 다르지 않다.
- 다중정의의 메서드가 모두 같은 기능을 한다면, 신경쓰지 않아도 된다.

