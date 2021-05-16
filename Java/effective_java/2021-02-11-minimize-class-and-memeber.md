# ITEM 15: MINIMIZE THE ACCESSIBILITY OF CLASSES AND MEMBERS

잘 설계된 컴포넌트는 모든 내부 구현을 완벽히 숨겨, 구현과 API를 깔끔히 분리한다. 오직  API를 통해서만 다른 컴포넌트와 소통하며, 서로의 내부 동작 방식에는 전혀 개의치 않는다.( [캡슐화](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/java-class.md#%EC%BA%A1%EC%8A%90%ED%99%94encapsulation) )

## 캡슐화(정보 은닉)의 장점

- 여러 컴포넌트를 병렬로 개발할 수 있어 **시스템 개발 속도를 높인다**. 
- 각 컴포넌트를 더 빨리 파악해 디버깅할 수 있고, 다른 컴포넌트로 교체하는 부담도 적기 때문에 **시스템 관리 비용을 낮춘다**.
- **성능 최적화에 도움**을 준다.
  - 완성된 시스템을 프로파일링해 최적화할 컴포넌트를 정한 다음 다른 컴포넌트에 영향을 주지 않고 해당 컴포넌트만 최적화할 수 있다.([item 67]())
- **소프트웨어 재사용성**을 높인다.
  - 외부에 의존하지 않고 독자적으로 동작할 수 있는 컴포넌트라면, 낯선 환경에서도 유용하게 쓰일 가능성이 높다.
- 큰 시스템을 **제작하는 난이도를 낮춘다**.
  - 시스템 전체가 완성되지 않은 상태에서도 개별 컴포넌트의 동작을 검증할 수 있기 때문

정보 은닉은 [접근 제한자](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/java-class.md#%EC%A0%91%EA%B7%BC-%EC%A0%9C%ED%95%9C%EC%9E%90)(`private`, `protected`, `public`)을 제대로 활용하는 것이 핵심이다.

## 접근 제한자

**모든 클래스와 멤버의 접근성을 가능한 좁혀야 한다.**

톱레벨 클래스와 인터페이스를 `public`으로 선언하면, 공개 API가 되며, `package-private`로 선언하면 해당 패키지 안에서만 이용할 수 있다. 패키지 외부에서 쓸 이유가 없다면, `package-private` (`default`)로 선언하여, 클라이언트에 아무런 피해 없이 다음 릴리즈에서 수정, 교체, 제거할 수 있다. `public`으로 선언하면 API가 되므로 하위 호환을 위해 영원히 관리해줘야 한다.

### 멤버 접근 제한자

![java package-private 이미지 검색결과](https://www.programcreek.com/wp-content/uploads/2011/11/access-level.png?ezimgfmt=rs:632x192/rscb10/ng:webp/ngcb10)

- `private` : 멤버를 선언한 톱레벨 클래스에서만 접근 가능
- `package-private` : 멤버가 소속된 패키지 안의 모든 클래스에서 접근 가능. 접근 제한자를 명시하지 않았을 때 적용되는 패키지 접근 수준이며, 단, 인터페이스는 기본적으로 `public` 이 적용된다.
- `protected` : `package-private`의 접근 범위를 포함하며, 이 멤버를 선언한 클래스의 하위 클래스에서도 접근할 수 있다.
- `public` : 모든 곳에서 접근할 수 있다.



클래스의 공개 API외의 모든 멤버는 `private`로 만들고, 오직 같은 패키지의 다른 클래스가 접근해야하는 멤버에 한해 `package-private`로 풀어주는 것이 좋다. `private`와 `package-private` 멤버는 모두 해당 클래스의 구현에 해당하여, 공개 API에 영향을 주지 않으나, `Serializable`을 구현한 클래스에서는 그 필드들도 의도치 않게 공개 API가 될 수 있다.([item 86](), [item 87]())

<<<<<<< HEAD
`public` 클래스에서 멤버 접근 수준을 `package-private`에서 `protected`로 변경하는 순간 그 멤버에 접근할 수 있는 대상 범위가 엄청나게 넓어진다. `public` 클래스의 `protected` 멤버는 공개 API로 영원히 지원되어야 하며, 내부 동작 방식을 API 문서에 적어 사용자에게 공개해야 할 수 도 있다.([item 19]()) 그러므로 **`protected` 멤버는 적을 수록 좋다.**

**테스트만을 위해 클래스, 인터페이스, 멤버를 공개 API로 만들어서는 안된다.**

**`public` 클래스의 인스턴스 필드는 되도록 `public`이 아니어야한다**. ([item 16]())  필드가 가변 객체를 참조하거나, `final`이 아닌 인스턴스 필드를 `public`으로 선언하면, 그 필드에 담을 수 있는 값을 제한할 힘을 잃는다.(불변식을 보장할 수 없게 된다.) 또한, `public` 가변 필드를 갖는 클래스는 일반적으로 스레드 안정성이 없다.  
=======
`public` 클래스에서 멤버 접근 수준을 `package-private`에서 `protected`로 변경하는 순간 그 멤버에 접근할 수 있는 대상 범위가 엄청나게 넓어진다. `public` 클래스의 `protected` 멤버는 공개 API로 영원히 지원되어야 하며, 내부 동작 방식을 API 문서에 적어 사용자에게 공개해야 할 수 도 있다.([item 19](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-13-design-inheirtance.md)) 그러므로 **`protected` 멤버는 적을 수록 좋다.**

**테스트만을 위해 클래스, 인터페이스, 멤버를 공개 API로 만들어서는 안된다.**

**`public` 클래스의 인스턴스 필드는 되도록 `public`이 아니어야한다**. ([item 16](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-02-11-use-accessor-method.md))  필드가 가변 객체를 참조하거나, `final`이 아닌 인스턴스 필드를 `public`으로 선언하면, 그 필드에 담을 수 있는 값을 제한할 힘을 잃는다.(불변식을 보장할 수 없게 된다.) 또한, `public` 가변 필드를 갖는 클래스는 일반적으로 스레드 안정성이 없다.  
>>>>>>> java

정적 필드에서도 이러한 문제는 마찬가지이다. 하지만 ,해당 클래스가 표현하는 추상 개념을 완성하는 데 꼭 필요한 구성요소로써의 상수라면 `public static final` 필드로 공개해도 좋다. 이러한 필드는 반드시 기본 타입 값이나 불변 객체를 참조해야한다. 그렇지 않다면, 다른 객체를 참조하지 못하지만 참조된 객체 자체는 수정될 수 있는 결과를 초래할 수도 있다.

길이가 0이 아닌 배열은 모두 변경이 가능하다. **클래스에서  public static final 배열 필드를 두거나 이 필드를 반환하는 접근자 메서드를 제공하면 안된다.**

- public 불변 리스트

```java
private static final Thing[] PRIVATE_VALUES = {...};
public static final List<Thing> VALUES = Collections.unmodifiableList(Arrays.asList(PRIVATE_VALUES));
```

- 방어적 복사(private 배열 복사본)

```java
private static final Thing[] PRIVATE_VALUES = {...};
public static final Thing[] values(){
  	return PRIVATE_VALUES.clone();
}
```

다음 두 가지 방법으로 배열을 제공하는 것을 권장한다.

## 모듈

Java9 부터는 모듈 개념이 도입되었다. 패키지는 클래스들의 묶음이라면, **모듈은 패키지들의 묶음**이다.

- [java9 module system](https://grokonez.com/java/java-9-module-system)
- [java 9 - Module System tutorialpoint](https://www.tutorialspoint.com/java9/java9_module_system.htm)

모듈은 클래스를 외부에 공개하지 않으면서도 같은 모듈을 이루는 패키지 사이에서 자유롭게 공유할 수 있다. 모듈은 자신에 속하는 패키지 중 공개(export) 할 것들을 `module-info.java`에 선언하며, 해당 패키지를 공개하지 않았더라면 `protected`, `public` 멤버일지라도 모듈 외부에서는 접근할 수 없다.

이때 주의해야할 점은 모듈의 jar 파일을 자신의 모듈 경로가 아닌 애플리케이션 클래스 패스에 둔다면 그 모듈 안의 모든 패키지는 마치 모듈이 없는 것처럼 동작한다. 즉, 모듈이 공개(export)했는지 여부와 상관 없이 public 클래스가 선언한 모든 `public`, `protected` 멤버를 모듈 밖에서도 접근할 수 있게된다.

모듈의 모든 장점을 누리기 위해서는 패키지들을 모듈 단위로 묶고, 모듈 선언에 패키지들의 모든 의존성을 명시해야한다. 그런 다음 소스 트리를 재배치하고, 모듈 안에서 일반 패키지로의 모든 접근에 특별한 조치를 취해야 한다.  그러므로, 꼭 필요한 경우가 아니라면 당분간은 사용하지 않는 것이 좋다.

## 참고

- [쟈미의 devlog - [Effective Java] item 15. 클래스와 멤버의 접근 권한을 최소화하라](https://jyami.tistory.com/77)

