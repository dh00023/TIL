# @Repeatable

`@Repeatable`은 Java 8버전 이후 메타 어노테이션으로, 어노테이션을 반복 적용할 수 있게 한다.
Java8 이전에는 반복 적용하고 싶은 어노테이션은 다음과 같이 적용했다.

```java
// case 1
@GreenColor
@BlueColor
@RedColor
public class RGBColor { ... }

// case 2
@Color(colors={"green", "blue", "red"}
public class RGBColor { ... }
```

`@GreenColor`, `@BlueColor`, `@RedColor` 이렇게 각각의 어노테이션을 생성하거나, 배열 매개변수를 받아 구현하였다.

Java 8이후 부터는 `@Repeatable` 어노테이션을 제공해주며, 사용방법은 다음과 같다.

1. Repeatable Annotation 타입을 선언(실 사용할 어노테이션)

    - `@Repeatable`에 Container annotation 전달

    ```java
    @Repeatable(value = Colors.class) // 
    @Retention(RetentionPolicy.RUNTIME)
    public @interface Color {
        String value(); // 
    }
    ```

2. 컨테이너 어노테이션 타입을 포함하여 선언(묶음 값을 관리하는 컨테이너 어노테이션)

    - 컨테이너 어노테이션은 내부 어노테이션을 반환하는 `value()` 메서드를 정의해야한다.

    ```java
    @Target(ElementType.TYPE)
    @Retention(RetentionPolicy.RUNTIME)
    @Documented
    public @interface Colors {
        Color[] value();  
    }
    ```

위와 같이 `@Repeatable` 어노테이션으로 구현하면 다음과 같이 어노테이션을 사용할 수 있다.

```java
@Color("green")
@Color("blue")
@Color("red")
public class RGBColor { ... }
```

이때, 한가지 주의할 점이 있다. 하위 어노테이션(`@Color`)가 한개만 정의된 경우 컨테이너 어노테이션(`@Colors`)로 묶이지 않으므로, 하위 어노테이션(`@Color`)에도   `@Retention(RetentionPolicy.RUNTIME)`를 선언해주어야한다.




## 참고

- [https://jistol.github.io/java/2018/08/31/annotation-repeatable/](https://jistol.github.io/java/2018/08/31/annotation-repeatable/)
- https://docs.oracle.com/javase/tutorial/java/annotations/repeating.html