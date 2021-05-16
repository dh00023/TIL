# ITEM 5: PREFER DEPENDENCY INJECTION TO HARDWIRING RESOURCES



많은 클래스가 하나 이상의 자원에 의존한다. 이때 **사용하는 자원에 따라 동작이 달라지는 클래스(하나 이상의 자원에 의존)에는 정적 유틸리티 클래스나 싱글턴 방식이 적합하지 않다**.

**인스턴스를 생성할 때 생성자에 필요한 자원을 넘겨주는 방식**을 사용하면, 클래스가 여러 자원 인스턴스를 지원하고, 클라이언트가 원하는 자원을 사용할 수 있다. 이 방법은 [의존 객체 주입](https://github.com/dh00023/TIL/blob/master/spring/2020-03-21-IoC.md#dependency-injection)의 한 형태로 **유연성과 재사용성, 테스트 용이성**을 높여준다.

```java
public class SpellChecker {
    private final Lexicon dictionayr;

    public SpellChecker(Lexicon dictionary){
        // null이면 NPE 아닌경우 objects 반환
        this.dictionary = Objects.requireNonNull(dictionary);
    }

    public boolean isValid(String word){}
}
```

위의 예시에서는 단순히 한개의 자원만 사용하지만, 자원이 몇 개든 의존 관계가 어떻게 되든 잘 작동한다. **[불변]()을 보장**하여 여러 클라이언트가 의존 객체를 안심하고 사용할 수 있다. 의존 객체 주입은 생성자, [정적 팩터리](./2021-01-12-static-factory-methods.md), [Builder](./2021-01-13-builder-pattern.md) 모두에 똑같이 적용 할 수 있다.

Factory란 호출할 때마다 특정 타입의 인스턴스를 반복해서 만들어 주는 객체를 말하는데, [Factory Method Pattern](../design_pattern/2020-03-20-factory_method_pattern.md)은 의존 객체 주입 패턴을 응용해서 구현한 것이다.

```java
@FunctionalInterface
public interface Supplier<T> {

    /**
     * Gets a result.
     *
     * @return a result
     */
    T get();
}
```

`Supplier<T>` 인터페이스는 팩터리를 표현한 완벽한 예시이다. 이 방식을 사용해 클라이언트는 자신이 명시한 타입의 하위 타입이라면 무엇이든 생성할 수 있는 팩터리를 만들 수 있다.

```java
Mosaic create(Supplier<? extends Tile> tileFactory) { ... }
```

의존 객체 주입이 유연성과 테스트 용이성을 개선해주지만, 의존성이 너무 많은 프로젝트에서는 코드를 어지럽게 하며, 스프링 같은 의존 객체 주입 프레임워크를 사용해 코드의 어지러움을 해소할 수 있다.