# Today I Learned

매일 공부한 내용을 기록하는 Repository 입니다.

## [Java](Java)

* [Basic](Java/문법/README.md)
  * [변수와 타입](Java/문법/java-variable.md)
  * [연산자](Java/문법/java-operator.md)
  * [조건문과 반복문](Java/문법/java-conditionAndLoop.md)
  * [참조 타입](Java/문법/java-referenceType.md.md)
  * [클래스](Java/문법/java-class.md)
  * [상속(Inheritance)](Java/문법/java-inheritance.md.md)
  * [인터페이스(Interface)](Java/문법/java-interface.md)
  * [중첩 클래스와 중첩 인터페이스](Java/문법/java-nested.md)
  * [예외 처리](Java/문법/java-exception.md)
  * [API - Object, System, Class, Math, Wrapper](Java/문법/java-api.md)
  * [API - String, StringBuffer, StringBuilder](Java/문법/java-string.md)
  * [Thread](Java/문법/java-thread.md)
  * [Generic](Java/문법/java-generic.md)
  * [Lambda](Java/문법/java-lambda.md)
  * [Collection - List, Set](Java/문법/java-collection.md)
  * [Collection - Map](Java/문법/2020-03-13-map.md)
  * [Collection - Tree](Java/문법/2020-03-24-tree.md)
  * [Collection - Stack, Queue](Java/문법/2020-03-24-stackAndQueue.md)
  * [Stream](Java/문법/2020-03-25-stream.md)
  * [Reflection](Java/문법/2019-01-21-reflection.md)
  * [정규표현식](Java/문법/regexp.md)
  * [GUI](Java/문법/GUI.md)
  * [UML](Java/문법/UML.md)
  * [Serializable](Java/문법/2021-01-18-Serializable.md)
* Advanced
  * [OutOfMemoryError](Java/심화/2021-01-23-outOfMemoryError.md)
  * [AutoValue](Java/심화/2020-02-02-autoValue.md)
* [Effective Java 3/E](Java/effective_java/README.md)
  * [ITEM 1: Static Factory Method(정적 메소드)](Java/effective_java/2021-01-12-static-factory-methods.md)
  * [ITEM 2: Builder Pattern](Java/effective_java/2021-01-13-builder-pattern.md)
  * [ITEM 3: Singleton](Java/effective_java/2021-01-14-singleton.md)
  * [ITEM 4: Private Constructor](Java/effective_java/2021-01-16-private-constructor.md)
  * [ITEM 5: Dependency Injection](Java/effective_java/2021-01-16-dependency-injection.md)
  * [ITEM 6: Avoid Unnecessary Object](Java/effective_java/2021-01-22-avoid-unnecessary-object.md)
  * [ITEM 7: Eliminate Object Reference](Java/effective_java/2021-01-22-eliminate-object-reference.md)
  * [ITEM 8: Avoid finalizer and cleaner](Java/effective_java/2021-01-25-avoid-finalizer-and-cleaner.md)
  * [ITEM 9: try-with-resources](Java/effective_java/2021-01-25-try-with-resources.md)
  * [ITEM 10: The gerneral contract when overriding equlas](Java/effective_java/2021-02-01-overriding-equals.md)
  * [ITEM 11: Overriding hashCode](Java/effective_java/2021-02-02-overriding-hashCode.md)
  * [ITEM 12: overriding toString](Java/effective_java/2021-02-03-overriding-toString.md)
  * [ITEM 13: overriding clone judiciously](Java/effective_java/2021-02-03-overriding-clone-judiciously.md)
  * [ITEM 14: Consider implementing comparable](Java/effective_java/2021-02-04-comparable.md)
  * [ITEM 15: 클래스와 멤버의 접근을 최소화해라](Java/effective_java/2021-02-11-minimize-class-and-memeber.md)
  * [ITEM 16: Use Accessor methods](Java/effective_java/2021-02-11-use-accessor-method.md)
  * [ITEM 17: 변경 가능성을 최소화해라(불변 클래스)](Java/effective_java/2021-02-11-minimize-mutability.md)
  * [ITEM 18: 상속보단 컴포지션을 사용해라](Java/effective_java/2021-02-12-use-composition.md)
  * [ITEM 19: 상속을 고려해 설계하고 문서화해라](Java/effective_java/2021-02-13-design-inheirtance.md)
  * [ITEM 20: 추상 클래스보다 인터페이스를 우선하라](Java/effective_java/2021-02-13-prefer-interface.md)
  * [ITEM 21: 인터페이스는 구현하는 쪽을 생각해 설계해라.](Java/effective_java/2021-02-13-design-interface-for-posterity.md)
  * [ITEM 22: 인터페이스는 타입을 정의하는 용도로만 사용해라](Java/effective_java/2021-02-13-use-interface-to-define-type.md)
  * [ITEM 23: 태그 달린 클래스보다 클래스 계층구조를 활용해라](Java/effective_java/2021-02-14-use-class-hirarchies.md)
  * [ITEM 24: 멤버 클래스는 되도록 static으로 구현해라](Java/effective_java/2021-02-14-favor-static-memeber.md)
  * [ITEM 25: 톱레벨 클래스는 한 파일에 하나만 생성해라.](Java/effective_java/2021-02-14-limit-single-top-level-class.md)
  * [ITEM 26: Raw type은 사용하지 마라](Java/effective_java/2021-05-19-generic-dont-use-raw-type.md)
  * [ITEM 27: 비검사 경고를 제거해라](Java/effective_java/2021-05-20-remove-unchecked-warning.md)
  * [ITEM 28: 배열보다는 리스트를 사용해라](Java/effective_java/2021-05-21-use-list-rather-than-array.md)
  * [ITEM 29: 이왕이면 제네릭 타입으로 만들어라](Java/effective_java/2021-05-22-make-generic-type.md)
  * [ITEM 30: 이왕이면 제네릭 메서드로 만들어라](Java/effective_java/2021-05-29-make-generic-method.md)
  * [ITEM 31 : 한정적 와일드카드를 사용해 API 유연성을 높여라](Java/effective_java/2021-05-30-use-bounded-wildcards.md)
  * [ITEM 32: 제네릭과 가변인수를 함께 쓸 때는 신중해라](Java/effective_java/2021-05-30-careful-when-using-generic-and-varargs.md)
  * [ITEM 33: 타입 안전 이종 컨테이너를 고려해라](Java/effective_java/2021-05-31-consider-type-safe-heterogeneous-container.md)
  * [ITEM 34: int 상수 대신 열거 타입을 사용해라](Java/effective_java/2021-06-05-use-enum-type.md)
  * [ITEM 35: ordinal 메서드 대신 인스턴스 필드를 사용해라](Java/effective_java/2021-06-06-use-instant-field.md)
  * [ITEM 36: 비트 필드 대신 EnumSet을 사용해라](Java/effective_java/2021-06-06-use-enumset.md)
  * [ITEM 37: ordinal 인덱싱 대신 EnumMap을 사용해라](Java/effective_java/2021-06-06-use-enummap.md)
  * [TEM 38 : 확장할 수 있는 열거타입이 필요하면 인터페이스를 사용해라](Java/effective_java/2021-06-06-enum-type-implements-interface.md)
* [객체지향 설계 원칙(SOLID)](Java/2020-03-21-SOLID.md)
* [Design Pattern](Java/design_pattern/README.md)
  * [Strategy Pattern](Java/design_pattern/2020-03-21-strategy_pattern.md)
  * [Template Method Pattern](Java/design_pattern/2020-03-20-template_method_pattern.md)
  * [Factory Method Pattern](Java/design_pattern/2020-03-20-factory_method_pattern.md)
  * [Singleton Pattern](Java/design_pattern/singleton_pattern.md)
  * [Delegation Pattern](Java/design_pattern/delegation_pattern.md)
  * [Proxy Pattern](Java/design_pattern/proxy_pattern.md)
  * [Adapter Pattern](Java/design_pattern/2021-02-14-adapter-pattern.md)
* [실습](Java/실습/README.md)
   * [인터페이스 실습 - Vehicle](Java/실습/vehicle.md)
   * [인터페이스 실습 - Remote](Java/실습/remote.md)
   * [GUI 실습 - Calculator](Java/실습/calculator.md)
   * [GUI 실습 - button](Java/실습/button.md)
   * [GUI 실습 - lotto](Java/실습/lotto.md)
   * [Thread 실습 - 좌석예약, 메세지보내기](Java/실습/lotto.md)
* [Jar vs War](Java/2021-05-23-jar-vs-war.md)