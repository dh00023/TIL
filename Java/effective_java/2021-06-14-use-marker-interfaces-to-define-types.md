# ITEM 41: 정의하려는 것이 타입이라면 마커 인터페이스를 사용해라

마커 인터페이스(marker interface)란, 일반적인 인터페이스와  동일하지만, **아무 메서드도 선언하지 않은 인터페이스**이다. 자바의 대표적인 마커 인터페이스로는 `Serializable`, `Cloneable`, `EventListener`가 있다. 
대부분의 경우 마커 인터페이스를 **단순한 타입 체크**를 하기 위해 사용한다.

- `Serializable`

    ```java
    package java.io;
    
    public interface Serializable {
    }
    ```

`Serializable` 인터페이스를 구현한 클래스는 `ObjectOutputStream`을 통해 직렬화할 수 있다.

- Item : `Serializable`을 구현하지 않음.

```java
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

import java.math.BigDecimal;

@Getter
@Setter
@AllArgsConstructor
public class Item {
    private long id;
    private String name;
    private BigDecimal price;
}
```

```java
public class SerializableTest {

    @Test
    void serializableTest() throws IOException {

        File f= new File("test.txt");
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream(f));
        objectOutputStream.writeObject(new Item(1L, "item A", new BigDecimal(30000)));
    }
}
```

```
java.io.NotSerializableException: ch6.dahye.item41.Item

    at java.base/java.io.ObjectOutputStream.writeObject0(ObjectOutputStream.java:1185)
    at java.base/java.io.ObjectOutputStream.writeObject(ObjectOutputStream.java:349)
```

`Serializable` 을 구현하지 않은 객체를 직렬화하려고하면 다음과 같이 오류가 발생하는 것을 볼 수 있다. 오류가 발생한 `ObjectOutputStream.writeObject0`의 1185번째 라인을 보면 `Serializable`을 구현하지 않은 경우 `NotSerializableException` 예외를 발생하고 있다. 여기서 단순히 `Serializable`이 구현되었는지 타입 확인 정도만 하고 있다.

```java
       if (obj instanceof String) {
                writeString((String) obj, unshared);
            } else if (cl.isArray()) {
                writeArray(obj, desc, unshared);
            } else if (obj instanceof Enum) {
                writeEnum((Enum<?>) obj, desc, unshared);
            } else if (obj instanceof Serializable) {
                writeOrdinaryObject(obj, desc, unshared);
            } else {
                if (extendedDebugInfo) {
                    throw new NotSerializableException(
                        cl.getName() + "\n" + debugInfoStack.toString());
                } else {
                    throw new NotSerializableException(cl.getName());
                }
            }
```

이렇게 단순히 타입 체크 정도만하고 있어, 마커 인터페이스라 부르는 것이다.

## 마커 어노테이션 vs 마커 인터페이스

1. **마커 인터페이스를 구현한 클래스의 인스턴스를 구분하는 타입으로 쓸 수 있다.** 마커 어노테이션은 구분하는 타입으로 사용할 수 없으며, 마커 어노테이션의 경우 런타임시 발견할 오류를 **마커 인터페이스를 구현하면 컴파일타임에 발견**할 수 있다.
    - 위에서 살펴본 `ObjectOutputStream.writeObject`는 런타임시 문제를 확인하므로 이러한 마커 인터페이스의 장점을 살리지 못한 케이스이다.
2. **마커 인터페이스는 적용 대상을 더 정밀하게 지정할 수 있다.**
    - 마커 어노테이션은 `ElevmentType.Type` 으로 타겟을 지정하므로 모든 타입(클래스, 인터페이스, 열거 타입, 어노테이션)에 적용된다.
    - 마킹하고 싶은 특정 클래스에서만 마커 인터페이스를 구현하여 적용대상을 더 정밀하게 지정할 수 있다.
3. **마커 어노테이션은 거대한 어노테이션 시스템의 지원을 받을 수 있다.**
    - 어노테이션을 적극적으로 사용하는 프레임워크에서는 마커 어노테이션을 쓰는 것이 일관성을 지키는데 유리

### 사용

- 마커 어노테이션 사용

    - 클래스, 인터페이스 외 프로그램 요소(모듈, 패키지, 필드, 지역변수 등)에 마킹해야하는 경우
        *(클래스와 인터페이스만이 인터페이스를 구현하거나 확장이 가능)*
    - 어노테이션을 적극적으로 사용하는 프레임워크

- 마커 인터페이스 사용

    - 마킹된 객체를 매개변수로 받는 메서드를 작성해야할 때
        *(마커 인터페이스를 해당 메서드의 매개변수 타입으로 사용하면 컴파일타임에 오류 발생)*
    - 새로 추가하는 메서드 없이 단지 타입 정의가 목적인 경우

    