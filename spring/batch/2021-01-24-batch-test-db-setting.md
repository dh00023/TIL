# 테스트 시에만 H2 데이터베이스 사용하도록 설정하기


## pom.xml 설정

사용할 DB에 대한 런타임의존성을 설정해준다.

```xml
<dependency>
	<groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <scope>runtime</scope>
</dependency>
<dependency>
	<groupId>mysql</groupId>
	<artifactId>mysql-connector-java</artifactId>
	<scope>runtime</scope>
</dependency>
```

## application.yml 설정

```yml
spring:
  datasource:
    url: jdbc:mysql://127.0.0.1:3306/{db명}
    username: {username}
    password: {password}
    driver-class-name: com.mysql.jdbc.Driver

  jpa:
    show-sql: true
    hibernate:
      ddl-auto: create # 테스트용 DB 생성(실제 운영시 동일하게 사용하면, 애플리케이션 재기동시마다 삭제됨)
```

## Test 파일 설정

```java
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)
public class InactvieUserJobTest {
	}
```

`@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)` 설정시, 테스트용 클래스에서 사용할 데이터베이스를 적용되게 하는 Annotation이다.


## 참고

- [처음 배우는 스프링 부트2](https://www.hanbit.co.kr/store/books/look.php?p_code=B4458049183)
