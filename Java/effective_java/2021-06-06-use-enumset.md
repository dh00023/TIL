# ITEM 36: 비트 필드 대신 EnumSet을 사용해라

열거한 값들이 집합으로 사용될 경우, 이전에는 비트 필드 열거 상수를 사용했다.

```java
/**
 * 정수 열거 패턴
 * 비트 필드 열거 상수 - 이전 기법
 */
public class Text {
    public static final int STYLE_BOLD          = 1 << 0;
    public static final int STYLE_ITALIC        = 1 << 1;
    public static final int STYLE_UNDERLINE     = 1 << 0;
    public static final int STYLE_STRIKETHROUGH = 1 << 0;

    // 매개변수 syltes는 0개 이상의 STYLE_ 상수를 비트별 OR한 값
    public void applyStyles(int styles) { ... }
    
}
```

비트별 `OR` 연산자를 이용해 여러 상수를 하나의 집합으로 모을 수 있으며, 이렇게 만들어진 집합을 비트 필드라고 한다.

```java
text.applyStyles(STYLE_BOLD | STYLE_UNDERLINE);
```

비트 필드를 사용하면, 비트별 연산을 사용해 합집합과 교집합 같은 집합 연산을 효율적으로 수행할 수 있다. 하지만 비트 필드는 정수 열거 상수의 단점을 그대로 갖고 있으며, 비트 필드 값이 그대로 출력되는 경우 단순 정수 열거 상수 출력시 보다 해석하기가 훨씬 어려워진다. 또한, 비트 필드 하나에 녹아있는 모든 원소를 순회하기도 까다로우며, 최대 몇 비트가 필요한지를 API 작성시 미리 예측하여 적절한 타입을 선택해야한다. 왜냐하면 API수정 없이는 비트수를 더 늘릴 수 없기 때문이다.
정수 상수보다 열거타입을 선호하는 경우에도 상수 집합을 주고 받아야하는 경우에 비트 필드를 사용하기도 한다.

이제는 `java.util.EnumSet` 클래스를 사용해 비트필드를 대체할 수 있다.

- `EnumSet` 클래스는 열거 타입 상수 값으로 구성된 집합을 효과적으로 표현
- `Set` 인터페이스를 완벽히 구현
- 타입 안전
- 다른 어떠한  `Set` 구현체와도 함꼐 사용 가능

`EnumSet`의 내부는 비트 벡터로 구현되어 있으며, 대부분의 경우에 `EnumSet` 전체를 `long` 변수 하나로 표현하여 비트 필드에 대등한 성능을 보여준다. 
`removeAll`과 `retainAll`과 같은 대량 작업은 비트를 효율적으로 처리할 수 있는 산술 연산을 써서 구현했으며, `EnumSet`이 모두 처리해주기 때문에 비트를 직접 다룰 때 흔히 겪는 오류에서 벗어날 수 있다.

```java
import java.util.Set;

public class NewText {
    public enum Style { BOLD, ITALIC, UNDERLINE, STRIKETHROUGH }

    public void applyStyles(Set<Style> styles) { ... }    
}
```

```java
text.applyStyles(EnumSet.of(Style.BOLD, Style.UNDERLINE));
```

다음과 같이 `EnumSet`을 이용해서 구현할 수 있으며, `EnumSet` 은 집합 생성 등 다양한 기능의 정적 팩터리를 제공하고 있다.
이때, `public void applyStyles(Set<Style> styles)`가 `Set`으로 받는 이유는 모든 클라이언트가 `EnumSet`을 건넬거라고 짐작되는 경우에도 **이왕이면 인터페이스로 받는게 더 좋은 습관**이다. 이렇게 인터페이스로 받으면 다른 `Set` 구현체를 넘기더라도 처리할 수 있기 때문이다.



`EnumSet`의 유일한 단점은 불변 `EnumSet`을 만들 수 없다는 것이며, 자바 11까지도 제공하지 않고 있다. 구글 구아바 라이브러리를 이용하면 불변 `EnumSet`을 만들 수는 있지만, 내부에서는 `EnumSet`을 사용해 구현하고 있으며, 성능면에서 좋지 않다. 혹은 `Collections.unmodifiableSet`으로 구현할 수 있지만 명확성과 성능면에서는 희생을 해야한다.