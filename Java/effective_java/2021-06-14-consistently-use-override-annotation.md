# ITEM 40: @Override 어노테이션을 일관되게 사용해라

```java
package java.lang;

import java.lang.annotation.*;

/**
 * Indicates that a method declaration is intended to override a
 * method declaration in a supertype. If a method is annotated with
 * this annotation type compilers are required to generate an error
 * message unless at least one of the following conditions hold:
 *
 * <ul><li>
 * The method does override or implement a method declared in a
 * supertype.
 * </li><li>
 * The method has a signature that is override-equivalent to that of
 * any public method declared in {@linkplain Object}.
 * </li></ul>
 *
 * @author  Peter von der Ah&eacute;
 * @author  Joshua Bloch
 * @jls 8.4.8 Inheritance, Overriding, and Hiding
 * @jls 9.4.1 Inheritance and Overriding
 * @jls 9.6.4.4 @Override
 * @since 1.5
 */
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.SOURCE)
public @interface Override {
}
```

- `@Target(ElementType.METHOD)` : 메서드 선언에만 달 수 있음
- `@Retention(RetentionPolicy.SOURCE)` : 소스코드(`.java`)까지 유지

`@Override` 어노테이션은 상위 타입의 메서드를 재정의할때 사용한다. `@Override`를 일관되게 사용하면, 여러가지 버그를 예방할 수 있다.

다음은 `Object.equals`와 `Object.hashCode`를 재정의한 클래스 코드이다.

```java
public class Biagram {
    private final char first;
    private final char second;

    public Biagram(char first, char second) {
        this.first = first;
        this.second = second;
    }

    public boolean equals(Biagram b) {
        return b.first == first && b.second == second;
    }

    public int hashCode() {
        return 31 * first + second;
    }

    public static void main(String[] args) {
        Set<Biagram> s = new HashSet<>();
        for (int i = 0; i < 10; i++) {
            for (char ch = 'a'; ch <= 'z'; ch++) {
                s.add(new Biagram(ch, ch));
            }
        }
        System.out.println(s.size()); // 260
    }
}
```

여기서 Set은 중복을 허용하지 않으므로 `s.size`는 26이 출력될거라 예상하지만, 260이 출력된다.
그 이유는 `equals` 메서드를 재정의한 것이 아닌 다중정의(overloading)을 했기 때문이다. 이러한 오류를 컴파일러가 찾아내게 하려면 `@Override` 어노테이션을 추가해 `Object.equals` 를 재정의하려는 의도를 명확하게 나타내야한다.

```java
public class Biagram {
    private final char first;
    private final char second;

    public Biagram(char first, char second) {
        this.first = first;
        this.second = second;
    }

    @Override public boolean equals(Biagram b) {
        return b.first == first && b.second == second;
    }

    @Override public int hashCode() {
        return 31 * first + second;
    }

    public static void main(String[] args) {
        Set<Biagram> s = new HashSet<>();
        for (int i = 0; i < 10; i++) {
            for (char ch = 'a'; ch <= 'z'; ch++) {
                s.add(new Biagram(ch, ch));
            }
        }
        System.out.println(s.size());
    }
}
```

```
java: method does not override or implement a method from a supertype
```

`@Override`를 붙이게되면 컴파일러는 해당 메서드가 상위 메서드와 다르다는 것을 찾아 오류가 발생하며, 올바르게 수정할 수 있다.

즉, **상위 클래스의 메서드를 재정의하는 모든 메서드에 @Override 어노테이션을 다는것을 권장한다.**
단, 상위 클래스의 추성 메서드는 굳이 `@Override`를 달지 않아도 된다.

`@Override` 어노테이션을 정리하자면 다음과 같다.

- 클래스, 인터페이스의 메서드를 재정의할 때 사용
- 시그니처가 올바른지 재차 확인 가능
- 컴파일타임에 오류 발견 가능
- 추상 클래스나 인터페이스에서는 상위 클래스, 상위 인터페이스의 메서드를 재정의한 모든 메서드에 추가하는 것을 권장
- 추상 메서드는 굳이 어노테이션을 달지 않아도 된다.