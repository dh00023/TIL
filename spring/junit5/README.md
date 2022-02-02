# JUnit5

Junit은 Java의 단위 테스팅 도구이다.

- 단위 테스트 Framework중 하나
- 단정문으로 Test Case 수행결과를 판별
- Annotation으로 간결하게 사용 가능

## JUnit5

Junit5는 이전 버전과 다르게 3개의 서브 프로젝트 모듈로 이루어져있다.

- **JUnit Platform** : TestEngine API, Console Launcher, JUnit 4 based Runner 등 포함
- **JUnit Jupiter** : TestEngine API 구현체로 JUnit 5 구현
- **JUnit Vintage** : TestEngine API 구현체로 JUnit 3, 4 구현
  - Junit5에서 JUnit Vintage 모듈을 포함하고 있어 JUnit 3,4도 사용할 수 있지만, 완벽하게 지원해주는 것은 아니다.

## Dependencies

spring boot 2.2.0 이후 버전에서는 Junit5가 기본으로 변경되었다. Junit5는 Java8 부터 지원하며, 이전 버전으로 작성된 테스트 코드여도 컴파일이 지원된다.

### SpringBoot 2.2.0 이전 버전에서 junit5 설정

#### maven

```xml
<!-- spring boot test junit5 사용 exclusion을 통해 junit4에서 코드 실행시 사용하는 vintage-engine 예외처리-->
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-test</artifactId>
  <scope>test</scope>
  <exclusions>
    <exclusion>
      <groupId>org.junit.vintage</groupId>
      <artifactId>junit-vintage-engine</artifactId>
    </exclusion>
  </exclusions>
</dependency>

<!-- 테스트 코드 작성에 필요한 junit-jupiter-api 모듈과 테스트 실행을 위한 junit-jupiter-engine 모듈 포함 -->
<dependency>
  <groupId>org.junit.jupiter</groupId>
  <artifactId>junit-jupiter-api</artifactId>
</dependency>
```

#### gradle

```
testImplementation ('org.springframework.boot:spring-boot-starter-test') {
	exclude module: 'junit'
}
testImplementation 'org.junit.jupiter:junit-jupiter-api'
testRuntimeOnly'org.junit.jupiter:junit-jupiter-engine'
```

테스트를 구성하고, 프레임워크를 상속하기 위한 어노테이션을 지원한다.
대부분 어노테이션은 `junit-jupiter-api`모듈의 `org.junit.jupiter.api` 패키지안에 존재한다.

## 용어

#### 테스트 클래스

최상위 클래스, 스태틱 멤버 클래스,  `@Nested` 클래스에 적어도 한개의 `@Test` 어노테이션이 달린 테스트 메소드가 포함되어있는 클래스를 말한다.
테스트 클래스는 `abstract`이면 안되고, 하나의 생성자가 존재해야한다.

#### 테스트 메소드

아래 메타 어노테이션이 붙여진 메소드를 말하며, 테스트 메소드는 테스트 할 클래스, 상속한 부모 클래스, 인터페이스에 선언된다.
`abstract`를 선언해서는 안되며, 어떠한 값도 반환되면 안된다.

- `@Test`
- `@RepetedTest`
- `@ParameterizedTest`
- `@TestFactory`
- `@TestTemplate`

#### 라이플 사이클 메소드

아래 메타 어노테이션이 붙여진 메소드를 말하며, 테스트 메소드는 테스트 할 클래스, 상속한 부모 클래스, 인터페이스에 선언된다.
`abstract`를 선언해서는 안되며, 어떠한 값도 반환되면 안된다.

- `@BeforeAll`
- `@AfterAll`
- `@BeforeEach`
- `@AfterEach`

## Dependency Injection

Junit Jupiter의 주된 변화로 테스트 클래스의 생성와 메서드가 파라미터를 가질 수 있게 되었다.
이는 코드의 유연함이 증가할 뿐만 아니라, 의존성 주입 또한 가능하게 되었다.

`ParameterResolver`는 실행 시간 동안에 동적으로 파라미터를 해석할 수 있는 API를 정의하고 있다.
현재 자동으로 등록되는 3개의 Resolver가 있다.

| ParmeterResolver                | 설명                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| TestInfoParameterResolver       | `TestInfo` Resolver이다.<br />`TestInfo` 객체는 테스트 클래스, 메서드명, 디스플레이명과 같은 현재 테스트에 대한 정보를 가지고 있다. |
| RepetitionInfoParameterResolver | 반복 실행 가능한 메서드(`@RepeatedTest` ,`@BeforeEach` ,`@AfterEach`)와 같은 메서드 정보를 가지는 `RepetionInfo` 객체에 대한 Resolver이다. |
| TestReporterParameterResolver   | 현재 실행하는 테스트에 대한 추가 정보를 표시할 수 있는 `TestReporter` 객체에 대한 Resolver이다. |

### TestInfo

| 메소드명         | **타입**             | **설명**                                   |
| ---------------- | -------------------- | ------------------------------------------ |
| getDisplayName() | `String`             | @DisplayName 값이랑 동일                   |
| getTags()        | `Set<String>`        | @Tag 배열 값                               |
| getTestClass()   | `Optional<Class<?>>` | 패키지 + 테스트 클래스명                   |
| getTestMethod()  | `Optional<Method>`   | 패키지명 + 테스트 클래스명 + 테스트 메소드 |

### RepetitionInfo

| **메소드명 / 변수명**          | **타입** | **설명**                                                     |
| ------------------------------ | -------- | ------------------------------------------------------------ |
| getCurrentRepetition()         | int      | 현재 반복 횟수                                               |
| getTotalRepetitions()          | int      | 총 반복 횟수                                                 |
| DISPLAY_NAME_PLACEHOLDER       | String   | @DisplayName 값                                              |
| SHORT_DISPLAY_NAME             | String   | 반복할 때 나타나는 테스트명  **기본값 : "repetition " + 현재 반복 횟수 + " of " + 총 반복 횟수** |
| LONG_DISPLAY_NAME              | String   | DISPLAY_NAME_PLACEHOLDER + " :: " + SHORT_DISPLAY_NAME       |
| TOTAL_REPETITIONS_PLACEHOLDER  | String   | 현재 반복 횟수                                               |
| CURRENT_REPETITION_PLACEHOLDER | String   | 총 반복 횟수                                                 |

### TestInfoParameterResolver

```java
@DisplayName("TestInfo 테스트")
public class TestInfoTest {

    TestInfoTest(TestInfo testInfo) {
        assertThat("TestInfo 테스트").isEqualTo(testInfo.getDisplayName());
    }

    @BeforeEach
    void setUp(TestInfo testInfo) {
        String displayName = testInfo.getDisplayName();
        assertThat("demo test").isEqualTo(testInfo.getDisplayName());
    }

    @Test
    @Tag("demo1")
    @DisplayName("demo test")
    void test(TestInfo testInfo) {
        assertThat(testInfo.getTags().contains("demo1")).isTrue();
    }
}
```
