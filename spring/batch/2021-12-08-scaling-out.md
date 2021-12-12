# Spring Batch Scalling 기능

처리해야할 데이터가 증가하여 일정 규모 이상이 되는 경우 배치도 Scalling이 필요하다.
Spring Batch에서 제공하는 Scalling기능은 다음과 같다.

|기능|프로세스||설명|
|:-----|:-----|:-----|:-----|
|Multi-threaded Step|Single process|Local|단일 Step 수행시, 해당 Step내의 각 Chunk를 별도의 여러 쓰레드에서 실행하는 방법|
|Parallel Steps|Single process|Local|여러개의 Step을 병렬로 실행하는 방법으로, 단일 Step내의 성능 향상은 없다.|
|Remote Chunking|Multi process|Remote|Step처리가 여러 프로세스로 분할되어 외부의 다른 서버로 전송하여 처리하는 방식<br> 어느 서버에서 어떤 데이터를 처리하고 있는지 관리하지 않기 때문에 메세지 유실이 안되는 것이 100% 보장 되어야한다.(AWS SQS, Kafka 등 MQ사용 권장)|
|Partitioning|Single/Multi process|Local/Remote|매니저(마스터)를 이용해 데이터를 더 작은 파티션으로 나누고, 파티션에서 슬레이브가 독립적으로 작동하는 방식|
|`AsyncItemProcessor`와 `AsyncItemWriter`||Local|별개의 쓰레드를 통해 ItemProcessor와 ItemWriter를 처리<br>`spring-batch-integration`의존성에서 지원|

이 중 일부를 구현해볼 것이다.

## Multi-threaded Step


스프링 배치의 멀티 쓰레드 Step은 `TaskExecutor`를 이용해 각 쓰레드가 Chunk단위로 실행되게 하는 방식이다.

- `SimpleAsyncTaskExecutor` : chunk 단위별로 쓰레드 생성
- `ThreadPoolTaskExecutor` : 쓰레드풀 내에서 지정된 갯수의 쓰레드만을 재사용하면서 실행(운영에서 사용할 때는 쓰레드풀로 사용하는 것을 권장)

멀티쓰레드 환경 구성시 사용하고자 하는 Reader와 Writer가 멀티쓰레드를 지원하는지 파악이 필요하다.

예를 들어 [JpaPagingItemReader](https://docs.spring.io/spring-batch/docs/current/api/org/springframework/batch/item/database/JpaPagingItemReader.html)의 경우는 아래와 같이 thread-safe를 제공해주고 있는것을 볼 수 있으며,

```
public class JpaPagingItemReader<T>
extends AbstractPagingItemReader<T>
ItemReader for reading database records built on top of JPA.

It executes the JPQL setQueryString(String) to retrieve requested data. The query is executed using paged requests of a size specified in AbstractPagingItemReader.setPageSize(int). Additional pages are requested when needed as AbstractItemCountingItemStreamItemReader.read() method is called, returning an object corresponding to current position.

The performance of the paging depends on the JPA implementation and its use of database specific features to limit the number of returned rows.

Setting a fairly large page size and using a commit interval that matches the page size should provide better performance.

In order to reduce the memory usage for large results the persistence context is flushed and cleared after each page is read. This causes any entities read to be detached. If you make changes to the entities and want the changes persisted then you must explicitly merge the entities.

The reader must be configured with an EntityManagerFactory. All entity access is performed within a new transaction, independent of any existing Spring managed transactions.

The implementation is thread-safe in between calls to AbstractItemCountingItemStreamItemReader.open(ExecutionContext), but remember to use saveState=false if used in a multi-threaded client (no restart available).
```

[JpaCursorItemReader](https://docs.spring.io/spring-batch/docs/current/api/org/springframework/batch/item/database/JpaCursorItemReader.html)는 thread-safe하지 않은 것을 볼 수 있다.

```
public class JpaCursorItemReader<T>
extends AbstractItemCountingItemStreamItemReader<T>
implements org.springframework.beans.factory.InitializingBean
ItemStreamReader implementation based on JPA Query.getResultStream(). It executes the JPQL query when initialized and iterates over the result set as AbstractItemCountingItemStreamItemReader.read() method is called, returning an object corresponding to the current row. The query can be set directly using setQueryString(String), or using a query provider via setQueryProvider(JpaQueryProvider). The implementation is not thread-safe.
```

여기서 또 한가지 알아둬야할 점이 있다. 멀티쓰레드로 각 chunk들이 개별로 진행되는 경우 실패 지점에서 재시작하는 것이 불가능하다. 왜냐하면, 멀티쓰레드의 경우 1~n개의 chunk가 동시에 실행되며, 5번째 chunk가 실패했다고 해서 1~4 chunk가 모두 성공했다는 보장이 없다.

그래서 멀티쓰레드 적용시 일반적으로 ItemReader의 `saveState` 옵션을 false로 설정한다.

> saveState : `ItemStream#update(ExecutionContext)` 메소드로 `ExectuionContext`에  reader의 상태값을 저장할지 결정한다.
> (Defualt : true)

### Thread-safe

#### PagingItemReader

- [Multithread Job구현시 이슈사항 정리](./2021-12-09-multithread-error.md) 

위에서 봤듯이 PagingItemReader는 thread-safe한 것을 알 수 있다.
멀티쓰레드로 수행하는 배치가 있다면, DB접근시 PagingItemReader를 사용하는 것을 권장한다.

- application.yml

    ```yaml
    spring:
      datasource:
        hikari:
          driver-class-name: com.mysql.cj.jdbc.Driver
          jdbc-url: jdbc:mysql://localhost:3306/spring_batch
          username: spring
          password: Springtest2021!
          maximum-pool-size: 10 # pool에 유지할 최대 connection 수
          auto-commit: false # 자동 commit 여부
    ```
    
- main() 메서드 설정

    ```java
    @SpringBootApplication(exclude = DataSourceAutoConfiguration.class)
    public class SpringBatchRealApplication {
    
        public static void main(String[] args) {
            // main thread가 종료되면 jvm 강제 종료
            // main thread가 종료됐다는 것은 자식 thread도 모두 종료됐다는 것을 보장
            System.exit(SpringApplication.exit(SpringApplication.run(SpringBatchRealApplication.class, args)));
        }
    }
    ```

- Job 구현

    ```java
        @Bean(JOB_NAME)
        public Job job() {
            return this.jobBuilderFactory.get(JOB_NAME)
                    .incrementer(new RunIdIncrementer())
                    .start(step())
                    .build();
    
        }
    
        @Bean(JOB_NAME + "Step")
        public Step step() {
            return this.stepBuilderFactory.get(JOB_NAME + "Step")
                    .<Ncustomer, Ncustomer> chunk(chunkSize)
                    .reader(reader(null))
                    .writer(writer())
                    .taskExecutor(executor())
                    .throttleLimit(poolSize) // default : 4, 생성된 쓰레드 중 몇개를 실제 작업에 사용할지 결정
                    .build();
        }
    
        @Bean(JOB_NAME + "TaskPool")
        public TaskExecutor executor() {
            // 쓰레드 풀을 이용한 쓰레드 관리 방식
            ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
            executor.setCorePoolSize(poolSize); // 풀의 기본 사이즈
            executor.setMaxPoolSize(poolSize); // 풀의 최대 사이즈
            executor.setThreadGroupName("multi-thread-");
            executor.setWaitForTasksToCompleteOnShutdown(Boolean.TRUE);
    
            // allowCoreThreadTimeOut을 true로 설정해
            // core thread 가 일정시간 태스크를 받지 않을 경우 pool 에서 정리하고,
            // 모든 자식 스레드가 정리되면 jvm 도 종료 되게 설정한다.
            executor.setKeepAliveSeconds(30);
            executor.setAllowCoreThreadTimeOut(true);
    
            executor.initialize();
            return executor;
        }
    
        @Bean(JOB_NAME + "Reader")
        public JdbcPagingItemReader<Ncustomer> reader(PagingQueryProvider pagingQueryProvider) {
    
            return new JdbcPagingItemReaderBuilder<Ncustomer>()
                    .name("customerJdbcPagingItemReader")   // Reader의 이름, ExecutionContext에 저장되어질 이름
                    .dataSource(dataSource)                 // DB에 접근하기 위해 사용할 DataSource객체
                    .queryProvider(pagingQueryProvider)     // PagingQueryProvider
                    .pageSize(10)                           // 각 페이지 크기
                    .rowMapper(new BeanPropertyRowMapper<>(Ncustomer.class)) // 쿼리 결과를 인스턴스로 매핑하기 위한 매퍼
                    .saveState(false)                       // Reader가 실패한 지점을 저장하지 않도록 설정
                    .build();
        }
    ```

    여기서 핵심은 `TaskExecutor`을 구현하는 부분과 Step실행시 `.saveState(false)`로 설정하여, Reader가 실패한 지점을 저장하지 않고, 실패시 다시 처음부터 실행하도록 하는 것이다. (다른 thread들의 성공을 보장하지 않으므로!)

    `TaskExecutor` 구현시에는 allowCoreThreadTimeOut을 설정해 특정시간(KeepAliveSeconds)이후에 사용하지 않으면 종료되도록 설정한다.

    다음 Job을 수행하면 각 thread별로 병렬로 수행되는 것을 확인할 수 있다.

### Not Thread Safety

#### CursorItemReader

cursorItemReader의 경우에는 thread safety를 보장하지 않는다. Reader 영역을 `SynchronizedItemStreamReader`로 wrapping하여 thread safety하게 구현할 수 있다.

```java
@Bean(JOB_NAME + "Reader")
    public SynchronizedItemStreamReader<Ncustomer> reader() {

        String sql = "SELECT N.CUSTOMER_ID" +
                ", CONCAT(N.LAST_NAME, \" \", N.FIRST_NAME) AS FULL_NAME\n" +
                " , N.ADDRESS1 AS ADDRESS\n" +
                ", N.POSTAL_CODE\n" +
                "FROM NCUSTOMER N\n" +
                "LIMIT 55";

        JdbcCursorItemReader itemReader =  new JdbcCursorItemReaderBuilder<Ncustomer>()
                .name(JOB_NAME + "Reader")   // Reader의 이름, ExecutionContext에 저장되어질 이름
                .dataSource(dataSource)                 // DB에 접근하기 위해 사용할 DataSource객체
                .rowMapper(new BeanPropertyRowMapper<>(Ncustomer.class)) // 쿼리 결과를 인스턴스로 매핑하기 위한 매퍼
                .sql(sql)
                .saveState(false)                       // Reader가 실패한 지점을 저장하지 않도록 설정
                .build();

        return new SynchronizedItemStreamReaderBuilder<Ncustomer>()
                .delegate(itemReader)
                .build();
    }
```

`SynchronizedItemStreamReader`의 `delegate`에 수행하고 싶은 `CursorItemReader`를 등록해주면 된다.

```java
public class SynchronizedItemStreamReader<T> implements ItemStreamReader<T>, InitializingBean {

	private ItemStreamReader<T> delegate;

	public void setDelegate(ItemStreamReader<T> delegate) {
		this.delegate = delegate;
	}

	/**
	 * This delegates to the read method of the <code>delegate</code>
	 */
	@Nullable
	public synchronized T read() throws Exception, UnexpectedInputException, ParseException, NonTransientResourceException {
		return this.delegate.read();
	}
```

`SynchronizedItemStreamReader`의 `read()` 메서드를 보면 **`synchronized`** 메서드로 감싸 동기화된 읽기가 가능하다.

```
2021-12-12 23:02:25.062  INFO 31421 --- [ multi-thread-5] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=1
2021-12-12 23:02:25.062  INFO 31421 --- [ multi-thread-2] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=2
2021-12-12 23:02:25.062  INFO 31421 --- [ multi-thread-4] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=3
2021-12-12 23:02:25.062  INFO 31421 --- [ multi-thread-1] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=4
2021-12-12 23:02:25.062  INFO 31421 --- [ multi-thread-3] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=5
2021-12-12 23:02:25.063  INFO 31421 --- [ multi-thread-4] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=6
2021-12-12 23:02:25.063  INFO 31421 --- [ multi-thread-3] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=7
2021-12-12 23:02:25.063  INFO 31421 --- [ multi-thread-5] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=8
2021-12-12 23:02:25.063  INFO 31421 --- [ multi-thread-2] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=9
2021-12-12 23:02:25.063  INFO 31421 --- [ multi-thread-1] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=10
2021-12-12 23:02:25.064  INFO 31421 --- [ multi-thread-2] d.e.s.j.m.l.CursorItemReaderListener     : Reading customer id=11
```

수행 결과를 보면, 각 thread가 순차적으로 읽어와 개별로 처리하는 것을 확인할 수 있다.

이미 네트워크/DISK IO/CPU/Memory 등 서버 자원이 이미 **단일 쓰레드에서도 리소스 사용량이 한계치에 달했다면** 멀티쓰레드로 진행한다고 해서 성능 향상을 기대할 수 없으며, 실제 운영 환경 적용 이전에 충분히 테스트를 진행해보고 해야한다.
