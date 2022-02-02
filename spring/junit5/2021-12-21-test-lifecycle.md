# 테스트 LifeCycle

테스트 인스턴스 상태 변경가능성때문에 일어나는 사이드 이펙을 줄이고, 테스트 메서드를 독립된 환경에서 독립적으로 실행시키기 위해 Junit은 테스트 메소드를 실행시키기 전에 각각의 테스트 클래스의 새로운 인스턴스를 만든다.
**즉, 테스트 메소드마다 새로운 테스트 클래스의 인스턴스를 만들며, 디폴트 동작**이다.

## @TestInstance

테스트 인스턴스 생성 단위를 변경하기 위해 생성하는 어노테이션이다.

| **파라미터명** | **타입**  | **설명**                                                     | default    |
| -------------- | --------- | ------------------------------------------------------------ | ---------- |
| value          | LifeCycle | 테스트 인스턴스 생성 단위 설정  <br />PER_METHOD : 메소드 단위<br />PER_CLASS : 클래스 단위 | PER_METHOD |

같은 인스턴스 안에서 모든 테스트 메소드를 실행하고 싶다면 `@TestInstance(Lifecycle.PER_CLASS)` 어노테이션을 사용하면 된다.
이 어노테이션을 사용하면, 클래스 단위로 새로운 인스턴스가 생기며, 그 안에 있는 인스턴스 변수를 테스트 메소드들이 공유하므로, `@BeforeEach`와 `@AfterEach`를 사용해 내부 상태를 리셋해야한다.

`PER_CLASS` 는 `@BeforeAll`과 `@AfterAll`를 붙인 메서드를 static 메서드로 구현하지 않아도 되며, 인터페이스의 `default` 메서드에서도 사용하지 않아도 된다.

또한, `@Nested` 테스트 클래스에서도 `@BeforeAll`과 `@AfterAll` 메소드를 사용할 수 있게 해준다.

## @BeforeEach

각각의 테스트 메소드가 실행되기전에 실행되어야 하는 메서드임을 명시해준다.
`@Test`, `@RepetedTest`, `ParameterizedTest`, `@TestFactory`가 붙은 테스트 메서드가 실행되기 전에 실행된다.
(Junit4의 `@Before`와 동일)
테스트 수행전 필요한 목업 데이터를 설정해주기 위해 주로 사용한다.

```java
    @Mock
    private SqlSessionFactory sqlSessionFactory;

    @Mock
    private SqlSession sqlSession;

    @Mock
    private Cursor<Object> cursor;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.openMocks(this);
    }
```

## @AfterEach

각각의 테스트 메소드가 실행 완료되고 난 후 실행되어야 하는 메소드임을 명시해준다.
`@Test`, `@RepetedTest`, `ParameterizedTest`, `@TestFactory`가 붙은 테스트 메서드가 실행된 후에 실행된다.
(Junit4의 `@After`와 동일)
테스트 수행 완료 후 테스트 데이터 삭제, 자원해제 등에 주로 사용한다.

```java
    @AfterEach
    public void tearDown() {
        this.jdbcTemplate.update("delete from customer");
    }
```

## @BeforeAll

테스트가 시작되기 전 **딱 한 번만 실행되며, 테스트 메서드간 공유 되어야하므로 static 메서드**여야한다.

## @AfterAll

테스트가 완료된 후 **딱 한 번만 실행되며, 테스트 메서드간 공유 되어야하므로 static 메서드**여야한다.

```java

public class JunitJupiterTests {

    @BeforeAll
    public static void beforeAll() {
        System.out.println("Before All");
    }


    @BeforeEach
    void beforeEach() {
        System.out.println("Before Each");
    }

    @Test
    void test1() {
        System.out.println("test1");
    }


    @Test
    void test2() {
        System.out.println("test2");
        assertThat(StringUtils.hasText("")).isFalse();
    }

    @AfterAll
    public static void afterAll() {
        System.out.println("After All");
    }


    @AfterEach
    void afterEach() {
        System.out.println("After Each");
    }
}
```

```
Before All
Before Each
test1
After Each
Before Each
test2
After Each
After All
```



## 참고

- [민동현 - JUnit5 완벽가이드](https://donghyeon.dev/junit/2021/04/11/JUnit5-%EC%99%84%EB%B2%BD-%EA%B0%80%EC%9D%B4%EB%93%9C/)
- [노력남자 - JUnit (5) - 테스트 인스턴스 (@TestInstance)](https://effortguy.tistory.com/119?category=841326)
