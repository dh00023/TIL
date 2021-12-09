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


