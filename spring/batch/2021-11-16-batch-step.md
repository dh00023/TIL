# Step

`Step`은 **실질적인 배치 처리를 정의하고 제어하는 데 필요한 모든 정보**가 들어있는 도메인 객체로, `Job`을 처리하는 실질적인 단위로 쓰인다.(**Job:Step = 1:M**)

- Step은 Job을 구성하는 독립된 작업 단위
- `org.springframework.batch.core.Step`

### StepExecution

`Step`의 실행 정보를 담는 객체로, 각각의 `Step`이 실행될 때마다 `StepExecution`이 생성된다.

```java
public class StepExecution extends Entity {
    private final JobExecution jobExecution; // 현재 JobExecution 정보
    private final String stepName; // Step 이름
    private volatile BatchStatus status; // Step의 실행 상태(COMPLETED, STARTING, STARTED ...)
    private volatile int readCount; // 성공적으로 읽은 레코드 수
    private volatile int writeCount; // 성공적으로 쓴 레코드 수
    private volatile int commitCount; // Step의 실행에 대해 커밋된 트랜잭션 수
    private volatile int rollbackCount; // Step의 실행에 대해 롤백된 트랜잭션 수
    private volatile int readSkipCount; // 읽기에 실패해 건너 띈 렉코드 수
    private volatile int processSkipCount; // 프로세스가 실패해 건너 띈 렉코드 수
    private volatile int writeSkipCount;// 쓰기에 실패해 건너 띈 렉코드 수
    private volatile Date startTime; // Step이 실행된 시간(null == 시작되지 않음)
    private volatile Date endTime; // Step의 실행 성공 여부와 관계 없이 끝난 시간
    private volatile Date lastUpdated; // 마지막으로 수정된 시간
    private volatile ExecutionContext executionContext; // Step 실행 사이에 유지해야하는 사용자 데이터
    private volatile ExitStatus exitStatus; // Step 실행 결과에 대한 상태 값(UNKOWN, EXECUTING, COMPLETE, ...)
    private volatile boolean terminateOnly; // Job 실행 중지 여부
    private volatile int filterCount; // 실행에서 필터링된 레코드 수
    private transient volatile List<Throwable> failureExceptions; // Step 실행중 발생한 예외 리스트
    ...
}
```

### `Tasklet` 기반

- `Tasklet`은 임의의 `Step`을 실행할 때 하나의 작업을 처리하는 방식
- 읽기, 처리, 쓰기로 나뉜 방식이 청크 지향 프로세싱이라면 이를 **단일 작업으로 만드는 개념**이 `Tasklet`
- 트랜잭션 내에서 로직이 실행될 수 있는 기능을 제공하는 전략 인터페이스
- `org.springframework.batch.core.step.tasklet.Tasklet`

```java
public interface Tasklet {
  	// 내부에 원하는 단일 작업을 구현하고 나면, RepeatStatus.FINISHED 반환후 작업이 계속되면 RepeatStatus.CONTINUABLE 반환
    @Nullable
    RepeatStatus execute(StepContribution var1, ChunkContext var2) throws Exception;
}
```

### `Chunk` 기반

`ItemReader`, `ItemProcessor`, `ItemWriter` 3단계로 비지니스 로직을 분리해 역할을 명확하게 분리할 수 있다.

- 비즈니스 로직 분리
- 읽어온 배치 데이터와 쓰여질 데이터 타입이 다른 경우에 대한 대응

 그러므로 읽어온 배치의 데이터와 저장할 데이터 타입이 다른 경우에 대응할 수 있다.

#### ItemReader

- `Step`의 대상이 되는 **배치 데이터(File, Xml, DB 등)를 읽어오는 인터페이스** 
- `org.springframework.batch.item.ItemReader<T>`

```java
public interface ItemReader<T> {
    // read 메서드의 반환 타입을 T(제너릭)으로 구현하여 직접 타입을 지정할 수 있음
    @Nullable
    T read() throws Exception, UnexpectedInputException, ParseException, NonTransientResourceException;
}
```

#### ItemProcessor

- `ItemReader`로 읽어 온 **배치 데이터를 변환하는 역할**을 수행
- `ItemProcessor`는 로직 처리만 수행하여 역할을 분리하고, 명확한 input/output을 `ItemProcessor`로 구현해놓으면 더 직관적인 코드가 될 것이다.

- `org.springframework.batch.item.ItemProcessor<T>`

  ```java
  public interface ItemProcessor<I, O> {
      @Nullable
      O process(@NonNull I var1) throws Exception;
  }
  ```

#### ItemWriter

  - **배치 데이터(DB, File 등)를 저장**한다.
  - `org.springframework.batch.item.ItemWriter<T>`

  ```java
  public interface ItemWriter<T> {
      // T(제네릭)으로 지정한 타입을 List 매개변수로 받는다.
      void write(List<? extends T> var1) throws Exception;
  }
  ```

  리스트의 데이터 수는 설정한 \*청크(Chunk) 단위로 불러온다.

### 청크 지향 프로세싱

![https://github.com/cheese10yun/TIL/raw/master/assets/chun-process.png](../assets/chun-process.png)

Chunk란 **아이템이 트랜잭션에 commit되는 수**를 말한다.

즉, **청크 지향 처리란 한 번에 하나씩 데이터를 읽어 Chunk라는 덩어리를 만든 뒤, Chunk 단위로 트랜잭션을 다루는 것을 의미**한다.

Chunk 지향 프로세싱은 1000개의 데이터에 대해 배치 로직을 실행한다고 가정하면, Chunk 단위로 나누지 않았을 경우에는 한개만 실패해도 성공한 999개의 데이터가 롤백된다. Chunk 단위를 10으로 한다면, 작업 중에 다른 Chunk는 영향을 받지 않는다. 