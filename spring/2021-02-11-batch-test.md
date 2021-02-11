# Spring Batch Test

## 통합 테스트

- pom.xml

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
```

스프링 부트 배치 테스트 사용시 의존성에 반드시 `spring-boot-starter-test`가 포함되어 있어야한다.



```java
@RunWith(SpringRunner.class)
@SpringBatchTest 
@SpringBootTest(classes={BatchJpaTestConfiguration.class, TestBatchConfig.class})
public class BatchIntegrationTestJobConfigurationTest {
    @Autowired
    private JobLauncherTestUtils jobLauncherTestUtils; // (2)

    @Autowired
    private SalesRepository salesRepository;

    @Autowired
    private SalesSumRepository salesSumRepository;

    @After
    public void tearDown() throws Exception {
        salesRepository.deleteAllInBatch();
        salesSumRepository.deleteAllInBatch();
    }

    @Test
    public void 기간내_Sales가_집계되어_SalesSum이된다() throws Exception {
        //given
        LocalDate orderDate = LocalDate.of(2019,10,6);
        int amount1 = 1000;
        int amount2 = 500;
        int amount3 = 100;

        salesRepository.save(new Sales(orderDate, amount1, "1"));
        salesRepository.save(new Sales(orderDate, amount2, "2"));
        salesRepository.save(new Sales(orderDate, amount3, "3"));

        JobParameters jobParameters = new JobParametersBuilder() 
                .addString("orderDate", orderDate.format(FORMATTER))
                .toJobParameters();

        //when
        JobExecution jobExecution = jobLauncherTestUtils.launchJob(jobParameters); // (3)


        //then
        assertThat(jobExecution.getStatus()).isEqualTo(BatchStatus.COMPLETED);
        List<SalesSum> salesSumList = salesSumRepository.findAll();
        assertThat(salesSumList.size()).isEqualTo(1);
        assertThat(salesSumList.get(0).getOrderDate()).isEqualTo(orderDate);
        assertThat(salesSumList.get(0).getAmountSum()).isEqualTo(amount1+amount2+amount3);
    }
}
```

- `@SpringBatchTest` :  자동으로 ApplicatonContext에 테스트에 필요한 여러 유틸 Bean을 등록해준다.

  | Util                           | 설명                                                         | 테스트 단위 |
  | ------------------------------ | ------------------------------------------------------------ | ----------- |
  | JobLauncherTestUtils           | 스프링 배치 테스트에 필요한 전반적인 유틸 기능들 지원        | 통합 테스트 |
  | JobRepositoryTestUtils         | DB에 생성된 JobExecution을 쉽게 생성/삭제 가능하도록 지원    | 통합 테스트 |
  | StepScopeTestExecutionListener | 배치 단위 테스트시 `@StepScope` 컨텍스트를 생성<br>해당 컨텍스트를 통해 JobParameter등을 단위 테스트에서 DI 받을 수 있다. | 단위 테스트 |
  | JobScopeTestExecutionListener  | 배치 단위 테스트시 `@JobScope` 컨텍스트를 생성<br/>해당 컨텍스트를 통해 JobParameter등을 단위 테스트에서 DI 받을 수 있다. | 단위 테스트 |

- `@SpringBootTest` : 통합 테스트 실행시 사용할 Java설정들을 선택
  -  `BatchJpaTestConfiguration`은 테스트할 Batch Job
  - `TestBatchConfig` : 배치 테스트 환경
- `jobLauncherTestUtils.launchJob(jobParameters)` : `JobParameters`와 함께 Job을 실행한다.
  - 해당 Job의 결과는 `JobExecution`에 담겨 반환된다.
  - `jobExecution.getStatus()`로 성공적으로 수행되었는지 검증한다.

```java
@Configuration
@EnableAutoConfiguration
@EnableBatchProcessing // 배치 환경을 자동 설정
public class TestBatchConfig {
}
```

- `@EnableBatchProcessing` : 스프링부트 배치 스타터에 미리 정의된 설정들을 실행시키는 어노테이션으로 JobBuilder, StepBuilder 등 다양한 설정 주입



## 참고

- [기억보단 기록을 - 10. Spring Batch 가이드 - Spring Batch 테스트 코드](https://jojoldu.tistory.com/455?category=902551)