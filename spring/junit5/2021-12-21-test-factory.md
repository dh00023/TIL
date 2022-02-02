
# 동적 테스트

## @TestFactory

`@TestFactory` 가 붙은 팩토리 메소드에 의해 런타임시 만들어지는 동적 테스트를 구현할 수 있다.

- `@TestFactory` 메소드는 그 자체로 테스트는 아니며, 팩토리 메소드가 테스트 케이스이다.
- `@TestFactory` 메소드는 반드시 하나의 `DynamicNode`, `Stream`, `Collection`, `Interable`, `Interator`, `DynamicNode` 인스턴스의 배열을 반환해야한다.
- `@TestFactory`가 리턴하는 Stream은 `stream.close()`을 호출해서 닫아줘야 리소스를 안전하게 사용할 수 있다.

즉, 런타임시 만들어지는 테스트 케이스를 말하며, 람다 표현식이나 메서드 추론 방식으로 제공될 수 있는 함수형 인터페이스의 조합이다.

동적 테스트는 콜백 라이플 사이클이 존재하지 않는다.
`@BeforeEach` 와 `@AfterEach` 메소드는 `@TestFactory` 메소드에서는 실행하지만, 각각의 Dynamic 테스트에 대해서는 실행하지 않는다.
즉, Dynamic 테스트 관한 람다 표현식안의 테스트 인스턴스의 필드에 접근하기위해서 해당 필드는 초기화 되지 않는다.

## 참고

- [민동현 - JUnit5 완벽가이드](https://donghyeon.dev/junit/2021/04/11/JUnit5-%EC%99%84%EB%B2%BD-%EA%B0%80%EC%9D%B4%EB%93%9C/)
- [노력남자 - JUnit 5 (3) - 태깅, 필터링 테스트 (@Tag)](https://effortguy.tistory.com/115?category=841326)
- [https://awayday.github.io/2017-11-12/junit5-05/](https://awayday.github.io/2017-11-12/junit5-05/)
