# Spring Boot Batch 시작

## Config 설정

### @EnableBatchProcessing

```java
import org.springframework.batch.core.configuration.annotation.EnableBatchProcessing;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@EnableBatchProcessing
public class PracticeApplication {

    public static void main(String[] args) {
        SpringApplication.run(PracticeApplication.class, args);
    }

}
```

```java
@EnableBatchProcessing // 스프링부트 배치 스타터에 미리 정의된 설정들을 실행시키는 어노테이션으로 JobBuilder, StepBuilder 등 다양한 설정 주입
@Configuration
public class TestJobConfig {

    // Job 실행에 필요한 JobLauncher를 필드값으로 갖는 JobLauncherTestUtils를 빈으로 등록
    @Bean
    public JobLauncherTestUtils jobLauncherTestUtils(){
        return new JobLauncherTestUtils();
    }
}
```

배치 작업에 필요한 빈을 미리 등록하여 사용할 수 있도록 해준다. 

| 기본 포함 bean               | bean name          |
| ---------------------------- | ------------------ |
| `JobRepository`              | jobRepository      |
| `JobLauncher`                | jobLauncher        |
| `JobRegistry`                | jobRegistry        |
| `PlatformTransactionManager` | transactionManager |
| `JobBuilderFactory`          | jobBuilders        |
| `StepBuilderFactory`         | stepBuilders       |

#### DefaultBatchConfiguerer

만약 커스텀이 필요한 경우 `DefaultBatchConfiguerer`을 상속받아 필요한 설정만 재정의 하여 사용할 수 있다. 예를 들어, 여러 개의 DB에 접근하고 싶어 `DataSource`를 여러개 설정해야하는 경우이다.

```java
@Configuration
public class DatabaseConfig {
    @Bean
    @Primary
    public DataSource dataSource()
    {
        return .........;
    }
}
```

```java
@Configuration
@EnableBatchProcessing
@ComponentScan(basePackageClasses = DefaultBatchConfigurer.class)
public class MyBatchConfig {
}
```

- 참고 : [https://stackoverflow.com/questions/25540502/use-of-multiple-datasources-in-spring-batch](https://stackoverflow.com/questions/25540502/use-of-multiple-datasources-in-spring-batch)

## MySQL 환경에서 Spring Batch  실행하기

Spring Batch에서는 메타 데이터 테이블이 필요하다. 

- 이전에 실행한 Job 정보
- 최근 실패한 Batch Parameter가 어떤 것들이 있고, 성공한 Job은 어떤 것들인지
- 다시 실행한다면 어디서 부터 시작할지
- 어떤 Job에 어떤 Step이 있고, Step들 중 성공한 Step과 실패한 Step들은 어떤 것들이 있는지

![Spring Batch Meta-Data ERD](https://docs.spring.io/spring-batch/docs/current/reference/html/images/meta-data-erd.png)

기본적으로 H2 DB를 사용할 경우에는 해당 테이블을 Boot가 실행될때 자동으로 생성해주지만, **MySQL, Oracle**과 같은 DB는 개발자가 직접 생성해주어야 한다. 해당 sql문을 차례대로 실행해주면 된다.



![image-20210124205536134](./assets/image-20210124205536134.png)



## MySql, H2 Database 연결하기

### pom.xml

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

### application.yml

```yaml
spring:
  profiles:
    active: local
---
spring:
  profiles: local
  datasource:
    hikari:
      jdbc-url: jdbc:h2:mem:testdb;DB_CLOSE_DELAY=-1;DB_CLOSE_ON_EXIT=FALSE
      username: sa
      password:
      driver-class-name: org.h2.Driver
---
spring:
  profiles: mysql
  datasource:
    hikari:
      jdbc-url: jdbc:mysql://127.0.0.1:3306/spring_batch?serverTimezone=UTC
      username: ${user_name}
      password: ${password}
      driver-class-name: com.mysql.jdbc.Driver
```

![image-20210124224911352](./assets/image-20210124224911352.png)

Active profiles에 설정한 값이 `spring-profiles` 값이다. 다음과 같이 설정 후 실행해주면 mysql이 기본 DB로 실행되는 것을 볼 수 있다.

## 지정한 Batch Job만 실행하기

```yaml
spring:
  profiles:
    active: local
    
spring.batch.job.names: ${job.name:NONE}
---

```

Spring Batch가 수행될 때, arguments로 `job.name`이 넘어오면 해당 값과 일치하는 Job만 수행시킬 수 있다.

`${job.name:NONE}` 의 의미는 `job.name`이 있으면 `job.name`을 할당하고, 없으면 `NONE`을 할당하겠다는 의미이다. 여기서 `NONE`이 `spring.batch.job.names` 에 할당되면 어떠한 배치도 실행하지 않겠다는 의미이며, 혹시라도 값이 없는 경우에 모든 배치가 수행되지 않도록 막는 역할을 한다.

![image-20210131194226674](./assets/image-20210131194226674.png)

```
--job.name=stepNextJob
```

위 program arguments를 추가하고 수행하면 해당 name의 Job만 실행 되는 것을 확인할 수 있다.

```
Job: [SimpleJob: [name=stepNextJob]] launched with the following parameters: [{version=2}]
2021-01-31 19:43:59.202  INFO 20321 --- [           main] o.s.batch.core.job.SimpleStepHandler     : Executing step: [step1]
2021-01-31 19:43:59.221  INFO 20321 --- [           main] s.b.p.jobs.StepNextJobConfiguration      : >>> this is step1
2021-01-31 19:43:59.237  INFO 20321 --- [           main] o.s.batch.core.step.AbstractStep         : Step: [step1] executed in 33ms
2021-01-31 19:43:59.303  INFO 20321 --- [           main] o.s.batch.core.job.SimpleStepHandler     : Executing step: [step2]
2021-01-31 19:43:59.315  INFO 20321 --- [           main] s.b.p.jobs.StepNextJobConfiguration      : >>> this is step2
2021-01-31 19:43:59.323  INFO 20321 --- [           main] o.s.batch.core.step.AbstractStep         : Step: [step2] executed in 19ms
2021-01-31 19:43:59.353  INFO 20321 --- [           main] o.s.batch.core.job.SimpleStepHandler     : Executing step: [step3]
2021-01-31 19:43:59.372  INFO 20321 --- [           main] s.b.p.jobs.StepNextJobConfiguration      : >>> this is step3
2021-01-31 19:43:59.385  INFO 20321 --- [           main] o.s.batch.core.step.AbstractStep         : Step: [step3] executed in 32ms
2021-01-31 19:43:59.402  INFO 20321 --- [           main] o.s.b.c.l.support.SimpleJobLauncher      : Job: [SimpleJob: [name=stepNextJob]] completed with the following parameters: [{version=2}] and the following status: [COMPLETED] in 258ms
```

```bash
$ java -jar batch-application.jar --job.name=simpleJob
```

실제 운영 환경에서는 위와 같이 수행하면된다.

## 참고

- [기억보단 기록을-2.Spring Batch 가이드 - Batch Job 실행해보기](https://jojoldu.tistory.com/325?category=902551)
- [기억보단 기록을 - 4. Spring Batch 가이드 - Spring Batch Job Flow](https://jojoldu.tistory.com/328?category=902551)
