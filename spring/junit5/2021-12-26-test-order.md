# 테스트 순서

## @TestMethodOrder

일반적으로 단위테스트는 테스트 순서에 영향을 받지 않지만, 통합 테스트나 테스트의 순서가 중요한 함수형 테스트를 하는 경우에 테스트 실행 순서를 지정해야하는 경우가 있다.

| 파라미터명 | 타입                             | 설명                                                         |
| ---------- | -------------------------------- | ------------------------------------------------------------ |
| value      | `Class<? extends MethodOrderer>` | 정렬 타입<br />MethodName : 메소드명 <br />DisplayName : displayName 기반<br />OrderAnnotation : `@Order(n)` 명시된 순서대로 정렬 <br />Random : 랜덤 |

### OrderAnnotation

```java

@TestMethodOrder(value = MethodOrderer.OrderAnnotation.class)
public class TestMethodOrderTest {

    @Order(1)
    @Test
    void test1() {

    }

    @Order(2)
    @Test
    void test2() {

    }


    @Order(3)
    @Test
    void test3() {

    }
}
```

## 참고

- [민동현 - JUnit5 완벽가이드](https://donghyeon.dev/junit/2021/04/11/JUnit5-%EC%99%84%EB%B2%BD-%EA%B0%80%EC%9D%B4%EB%93%9C/)
- [노력남자 - JUnit 5 (6) - 테스트 순서 ](https://effortguy.tistory.com/120?category=841326)

