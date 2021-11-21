# Step

`Step`은 **실질적인 배치 처리를 정의하고 제어하는 데 필요한 모든 정보**가 들어있는 도메인 객체로, `Job`을 처리하는 실질적인 단위로 쓰인다.(**Job:Step = 1:M**)

- Step은 Job을 구성하는 **독립된** 작업 단위
- 순차적으로 배치 처리 수행
- Step은 모든 단위 작업의 조각으로 자체적으로 입력, 처리기, 출력을 다룬다.
- 트랜잭션은 Step 내부에서 이루어짐
- `org.springframework.batch.core.Step`

## StepExecution

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

## `Tasklet` 기반

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

### Adapter

#### `CallableTaskletAdapter`

- `org.springframework.batch.core.step.tasklet.CallableTaskletAdapter`
- `Callable<V>` 인터페이스의 구현체를 구성할 수 있게 해주는 Adapter
    - 리턴값이 존재하기 때문에 공유 객체를 사용하지 않는다.
    - 체크 예외를 외부로 던질 수 있다.
- Step의 특정 로직을 해당 Step이 실행되는 스레드가 아닌 다른 스레드에서 실행하고 싶을 때 사용

```java
@EnableBatchProcessing
@SpringBootApplication
public class CallableTaskletConfiguration {

    @Autowired
    private JobBuilderFactory jobBuilderFactory;

    @Autowired
    private StepBuilderFactory stepBuilderFactory;

    @Bean
    public Job callableJob() {
        return this.jobBuilderFactory.get("callableJob")
                .start(callableStep())
                .build();
    }

    @Bean
    public Step callableStep() {
        return this.stepBuilderFactory.get("callableStep")
                .tasklet(callableTasklet())
                .build();
    }

    @Bean
    public Callable<RepeatStatus> callableObject() {
        return () -> {
            System.out.println("This was executed in another thread");
            return RepeatStatus.FINISHED;
        };
    }

    @Bean
    public CallableTaskletAdapter callableTasklet() {

        // CallableTaskletAdapter는 Step이 실행되는 스레드와 별개의 스레드에서 실행되지만
        // Step과 병렬로 실행되는 것은 아니다.
        CallableTaskletAdapter callableTaskletAdapter = new CallableTaskletAdapter();

        callableTaskletAdapter.setCallable(callableObject());

        return callableTaskletAdapter;
    }

}

```

### `MethodInvokingTaskletAdapter`

- `org.springframework.batch.core.step.tasklet.MethodInvokingTaskletAdapter`1
- 다른 클래스 내의 메서드를 Tasklet처럼 실행 가능

```java
@EnableBatchProcessing
@Configuration
public class MethodInvokingTaskletConfiguration {
    @Autowired
    private JobBuilderFactory jobBuilderFactory;

    @Autowired
    private StepBuilderFactory stepBuilderFactory;

    @Bean
    public Job methodInvokingJob() {
        return this.jobBuilderFactory.get("methodInvokingJob")
                .start(methodInvokingStep())
                .build();
    }

    @Bean
    public Step methodInvokingStep() {
        return this.stepBuilderFactory.get("methodInvokingStep")
                .tasklet(methodInvokingTasklet())
                .build();
    }

  	@StepScope
    @Bean
    public MethodInvokingTaskletAdapter methodInvokingTasklet(
            @Value("#{jobParameters['message']}") String message) {
        // 다른 클래스 내의 메서드를 Tasklet처럼 실행 가능
        MethodInvokingTaskletAdapter methodInvokingTaskletAdapter = new MethodInvokingTaskletAdapter();

        methodInvokingTaskletAdapter.setTargetObject(customerService()); // 호출할 메서드가 있는 객체
        methodInvokingTaskletAdapter.setTargetMethod("serviceMethod"); // 호출할 메서드명
        methodInvokingTaskletAdapter.setArguments(new String[] {message});

        return methodInvokingTaskletAdapter;
    }

    @Bean
    public CustomerService customerService() {
        return new CustomerService();
    }

}

```

TargetMethod는 `ExitStatus.COMPLETED` default이며, `ExitStatus`를 반환하면 메서드가 반환한 값이 Tasklet에서 반환된다.

### `SystemCommandTasklet`

- `org.springframework.batch.core.step.tasklet.SystemCommandTasklet`
- 시스템 명령을 실행할 때 사용하며, 지정한 시스템 명령을 비동기로 실행한다.

```java

@EnableBatchProcessing
@Configuration
public class SystemCommandConfiguration {
    @Autowired
    private JobBuilderFactory jobBuilderFactory;

    @Autowired
    private StepBuilderFactory stepBuilderFactory;

    @Bean
    public Job systemCommandJob() {
        return this.jobBuilderFactory.get("systemCommandJob")
                .start(systemCommandStep())
                .build();
    }

    @Bean
    public Step systemCommandStep() {
        return this.stepBuilderFactory.get("systemCommandStep")
                .tasklet(systemCommandTasklet())
                .build();
    }

    @Bean
    public SystemCommandTasklet systemCommandTasklet() {
        SystemCommandTasklet systemCommandTasklet = new SystemCommandTasklet();

        // 명령어
        systemCommandTasklet.setCommand("touch tmp.txt");
        systemCommandTasklet.setTimeout(5000);

        // Job이 비정상적으로 종료될 떄 시스템 프로세스와 관련된 스레드를 강제 종료할지 여부
        systemCommandTasklet.setInterruptOnCancel(true);

        // 작업 디렉토리 설정
        systemCommandTasklet.setWorkingDirectory("/Users/dh0023/Develop/gitbook/TIL");

        // 시스템 반환 코드를 스프링 배치 상태 값으로 매핑
        systemCommandTasklet.setSystemProcessExitCodeMapper(touchCodeMapper());

        // 비동기로 실행하는 시스템 명령을 주기적으로 완료 여부 확인, 완료 여부를 확인하는 주기(default=1초)
        systemCommandTasklet.setTerminationCheckInterval(5000);

        // 시스템 명령을 실행하는 TaskExecutor 구성 가능
        // 문제가 발생하면 락이 발생할 수 있으므로, 동기방식으로 구현하지 않는 것이 좋다.
        systemCommandTasklet.setTaskExecutor(new SimpleAsyncTaskExecutor());

        // 명령을 실행하기 전에 설정하는 환경 파라미터 목록
        systemCommandTasklet.setEnvironmentParams(
                new String[]{"BATCH_HOME=/Users/dh0023/Develop/spring/spring-practice/batch-practice"});

        return systemCommandTasklet;
    }

    @Bean
    public SimpleSystemProcessExitCodeMapper touchCodeMapper() {
        // 반환된 시스템 코드가 0이 ExitStatus.FINISHED
        // 0이 아니면 ExitStatus.FAILED
        return new SimpleSystemProcessExitCodeMapper();
    }

    @Bean
    public ConfigurableSystemProcessExitCodeMapper configurableSystemProcessExitCodeMapper() {
        // 일반적인 구성 방법으로 매핑 구성을 할 수 있음.
        ConfigurableSystemProcessExitCodeMapper mapper = new ConfigurableSystemProcessExitCodeMapper();

        Map<Object, ExitStatus> mappings = new HashMap<Object, ExitStatus>() {
            {
                put(0, ExitStatus.COMPLETED);
                put(1, ExitStatus.FAILED);
                put(2, ExitStatus.EXECUTING);
                put(3, ExitStatus.NOOP);
                put(4, ExitStatus.UNKNOWN);
                put(ConfigurableSystemProcessExitCodeMapper.ELSE_KEY, ExitStatus.UNKNOWN);
            }
        };

        mapper.setMappings(mappings);

        return mapper;
    }
}
```

- `SimpleSystemProcessExitCodeMapper`

    ```java
    public class SimpleSystemProcessExitCodeMapper implements SystemProcessExitCodeMapper {
    	@Override
    	public ExitStatus getExitStatus(int exitCode) {
    		if (exitCode == 0) {
    			return ExitStatus.COMPLETED;
    		} else {
    			return ExitStatus.FAILED;
    		}
    	}
    
    }
    ```

## `Chunk` 기반

![https://github.com/cheese10yun/TIL/raw/master/assets/chun-process.png](../assets/chun-process.png)

Chunk란 **아이템이 트랜잭션에 commit되는 수**를 말한다.

즉, **청크 지향 처리란 한 번에 하나씩 데이터를 읽어 Chunk라는 덩어리를 만든 뒤, Chunk 단위로 트랜잭션을 다루는 것을 의미**한다.

Chunk 지향 프로세싱은 1000개의 데이터에 대해 배치 로직을 실행한다고 가정하면, Chunk 단위로 나누지 않았을 경우에는 한개만 실패해도 성공한 999개의 데이터가 롤백된다. Chunk 단위를 10으로 한다면, 작업 중에 다른 Chunk는 영향을 받지 않는다. 

이때, Chunk는 커밋 간격(commit interval)에 의해 정의되고 수행하므로, 커밋 간격에 따라 성능이 달라질 수 있다. 최상의 성능을 얻기 위해서는 커밋 간격 설정이 중요하다.

`ItemReader`, `ItemProcessor`, `ItemWriter` 3단계로 비지니스 로직을 분리해 역할을 명확하게 분리할 수 있다.

- 비즈니스 로직 분리
- 읽어온 배치 데이터와 쓰여질 데이터 타입이 다른 경우에 대한 대응
- 각 Chunk는 자체 트랜잭션으로 실행되며, 처리에 실패하면 성공한 트랜잭션 이후부터 다시 시작 가능

 그러므로 읽어온 배치의 데이터와 저장할 데이터 타입이 다른 경우에 대응할 수 있다.

### ItemReader

- `Step`의 대상이 되는 **배치 데이터(File, Xml, DB 등)를 읽어오는 인터페이스** 
- `org.springframework.batch.item.ItemReader<T>`

```java
public interface ItemReader<T> {
    // read 메서드의 반환 타입을 T(제너릭)으로 구현하여 직접 타입을 지정할 수 있음
    @Nullable
    T read() throws Exception, UnexpectedInputException, ParseException, NonTransientResourceException;
}
```

### ItemProcessor

- `ItemReader`로 읽어 온 **배치 데이터를 변환하는 역할**을 수행
- `ItemProcessor`는 로직 처리만 수행하여 역할을 분리하고, 명확한 input/output을 `ItemProcessor`로 구현해놓으면 더 직관적인 코드가 될 것이다.

- `org.springframework.batch.item.ItemProcessor<T>`

  ```java
  public interface ItemProcessor<I, O> {
      @Nullable
      O process(@NonNull I var1) throws Exception;
  }
  ```

### ItemWriter

  - **배치 데이터(DB, File 등)를 저장**한다.
  - `org.springframework.batch.item.ItemWriter<T>`

  ```java
  public interface ItemWriter<T> {
      // T(제네릭)으로 지정한 타입을 List 매개변수로 받는다.
      void write(List<? extends T> var1) throws Exception;
  }
  ```

  리스트의 데이터 수는 설정한 \*청크(Chunk) 단위로 불러온다.

#### 청크 기반 Job 예시

```java
@EnableBatchProcessing
@Configuration
public class ChunkBasedConfiguration {

    @Autowired
    private JobBuilderFactory jobBuilderFactory;

    @Autowired
    private StepBuilderFactory stepBuilderFactory;

    /**
     * 실제 스프링 배치 Job 생성
     */
    @Bean
    public Job chunkBasedJob() {
        return this.jobBuilderFactory.get("chunkBasedJob")
                .start(chunkStep())
                .build();
    }

    @Bean
    public Step chunkStep() {
        return this.stepBuilderFactory.get("chunkStep")
                .<String, String> chunk(1000) // chunk 기반, 커밋간격 1000
                .reader(itemReader())
                .writer(itemWriter())
                .build();
    }

    @Bean
    public ListItemReader<String> itemReader(){

        List<String> items = new ArrayList<>(100000);

        for (int i = 0; i < 100000; i++) {
            items.add(UUID.randomUUID().toString());
        }

        return new ListItemReader<>(items);
    }

    @Bean
    public ItemWriter<String> itemWriter() {
        return items -> {
            for (String item : items) {
                System.out.println(">> current item = " + item);
            }
            System.out.println(">> end itemWriter chunk " + items.size());
        };
    }
}
```

일반적으로는 위와 같이 커밋간격을 하드 코딩해 크기를 정의하지만, 크기가 동일하지 않은 청크를 처리해야하는 경우도 있다.
스프링 배치는 `org.springframework.batch.repeat.CompletionPolicy` 인터페이스를 제공해 청크가 완료되는 시점을 정의할 수 있도록 제공해준다.

### CompletionPolicy

청크 완료 여부를 결정할 수 있는 결정로직을 구현할 수 있는 인터페이스로, `CompletionPolicy` 인터페이스의 구현체에 대해서 알아 볼 것이다.

```java
package org.springframework.batch.repeat;

public interface CompletionPolicy {

  // 청크 완료 여부의 상태를 기반으로 결정 로직 수행
	boolean isComplete(RepeatContext context, RepeatStatus result);

  // 내부 상태를 이용해 청크 완료 여부 판단
	boolean isComplete(RepeatContext context);

  // 청크의 시작을 알 수 있도록 정책을 초기화
	RepeatContext start(RepeatContext parent);

 	// 각 item이 처리가되면 update 메서드가 호출되면서 내부 상태 갱신
	void update(RepeatContext context);
}
```

#### 직접 구현하는 방법

`CompletionPolicy`를 구현하여 필수 메서드들을 각각 알맞게 로직을 구성하면된다.

```java
public class RandomChunkSizePolicy implements CompletionPolicy {

    private int chunksize;
    private int totalProcessed;
    private Random random = new Random();

  	// 청크 완료 여부의 상태를 기반으로 결정 로직 수행
    @Override
    public boolean isComplete(RepeatContext context, RepeatStatus result) {
        if (RepeatStatus.FINISHED == result) {
            return true;
        } else {
            return isComplete(context);
        }
    }

  	// 내부 상태를 이용해 청크 완료 여부 판단
    @Override
    public boolean isComplete(RepeatContext context) {
        return this.totalProcessed >= chunksize;
    }

  	// 청크의 시작을 알 수 있도록 정책을 초기화
    @Override
    public RepeatContext start(RepeatContext parent) {
        this.chunksize = random.nextInt(20);
        this.totalProcessed = 0;

        System.out.println("chunk size has been set to => " + this.chunksize);
        return parent;
    }

  	// 각 item이 처리가되면 update 메서드가 호출되면서 내부 상태 갱신
    @Override
    public void update(RepeatContext context) {
        this.totalProcessed++;
    }
}
```

```
chunk size has been set to => 5
>> current item = b784cda0-961f-4faf-9737-4334e774f0d1
>> current item = 9fc3ec22-5d54-4632-94e3-fcc28cc00260
>> current item = 53452739-0122-4f8b-a52a-667e37cbf908
>> current item = de9ad8ec-1bf7-40d4-b991-72b6699594f9
>> current item = 352104aa-ae63-4928-96e2-460b3b145d43
>> end itemWriter chunk 5
chunk size has been set to => 10
>> current item = 4116f3e9-cad3-4387-8f46-a871d825d7d9
>> current item = 3e1f58b7-a1fa-45bd-b336-2484d1d543f3
>> current item = a58e2401-37e8-402a-8ac3-daddaf2e91a0
>> current item = 01162200-fc7d-4580-8533-d6deab7f3c65
>> current item = 31280b14-49bf-4a03-b1d4-210585e4da40
>> current item = 91b7d269-8105-41dc-ae6a-1d682913c168
>> current item = abeead5f-751b-4862-aa37-4f32eb09439a
>> current item = b6bf1a92-56e8-433a-a0ea-935e101cad6f
>> current item = 84af0778-d6e1-4aef-bd8f-347b047bb276
>> current item = b86477f3-b997-4b04-a3ca-27f517c9170f
>> end itemWriter chunk 10
chunk size has been set to => 11
```

다음과 같이 Random으로 지정된 수만큼 chunk가 수행되는 것을 확인 할 수 있다.

#### SimpleCompletionPolicy

가장 기본적인 구현체로, 미리 구성해둔 임곗값에 도달하면 청크 완료로 표시한다.

```java
public class SimpleCompletionPolicy extends DefaultResultCompletionPolicy {

	public static final int DEFAULT_CHUNK_SIZE = 5;

	int chunkSize = 0;

	public SimpleCompletionPolicy() {
		this(DEFAULT_CHUNK_SIZE);
	}

	public SimpleCompletionPolicy(int chunkSize) {
		super();
		this.chunkSize = chunkSize;
	}
```

```java
@Bean
public Step chunkStep() {
  return this.stepBuilderFactory.get("chunkStep")
                .<String, String> chunk(completionPolicy()) // completePolicy 호출
                .reader(itemReader())
                .writer(itemWriter())
                .build();
}


@Bean
public CompletionPolicy completionPolicy() {
    // 처리된 ITEM 개수를 세어, 이 개수가 임계값에 도달하면 chunk 완료로 표시
    SimpleCompletionPolicy simpleCompletionPolicy = new SimpleCompletionPolicy(1000);

    return simpleCompletionPolicy;
}
```

#### TimeoutTerminationPolicy

타임아웃 값을 구성해, 청크 내에서 처리 시간이 지정한 시간이 넘으면 청크가 완료된 것으로 간주하고, 모든 트랜잭션 처리를 정상적으로 한다는 것이다.
`TimeoutTerminationPolicy` 만으로 청크 완료 시점을 결정하는 경우는 거의 존재하지 않으며, `CompositeCompletionPolicy`의 일부로 사용하는 경우가 많다.

```java
public class TimeoutTerminationPolicy extends CompletionPolicySupport {

	/**
	 * Default timeout value in milliseconds (the value equivalent to 30 seconds).
	 */
	public static final long DEFAULT_TIMEOUT = 30000L;

	private long timeout = DEFAULT_TIMEOUT;

	/**
	 * Default constructor.
	 */
	public TimeoutTerminationPolicy() {
		super();
	}

	/**
	 * Construct a {@link TimeoutTerminationPolicy} with the specified timeout
	 * value (in milliseconds).
	 * 
	 * @param timeout duration of the timeout.
	 */
	public TimeoutTerminationPolicy(long timeout) {
		super();
		this.timeout = timeout;
	}
```

```java
    @Bean
    public CompletionPolicy timeoutCompletionPolicy() {
        TimeoutTerminationPolicy timeoutTerminationPolicy = new TimeoutTerminationPolicy(3);
        return timeoutTerminationPolicy;
    }
```

`TimeoutTerminationPolicy`로 수행한 경우 각 chunk 단위를 확인해보면 다음과 같이 제각각인 것을 볼 수있다.

```
>> end itemWriter chunk 795
>> end itemWriter chunk 679
>> end itemWriter chunk 841
>> end itemWriter chunk 1153
>> end itemWriter chunk 1061
>> end itemWriter chunk 1916
>> end itemWriter chunk 1667
>> end itemWriter chunk 1719
>> end itemWriter chunk 931
>> end itemWriter chunk 1634
>> end itemWriter chunk 941
>> end itemWriter chunk 667
>> end itemWriter chunk 665
>> end itemWriter chunk 547
>> end itemWriter chunk 533
>> end itemWriter chunk 973
>> end itemWriter chunk 647
>> end itemWriter chunk 1632
>> end itemWriter chunk 676
```

#### CompositeCompletionPolicy

`CompositeCompletionPolicy`는 청크 완료 여부를 결정하는 여러 정책을 함께 구성할 수 있다.
포함하고 있는 여러 정책 중 하나라도 청크 완료라고 판단되면 해당 청크가 완료된 것으로 표시한다.

```java
		@Bean
    public CompletionPolicy compositeCompletionPolicy() {
        CompositeCompletionPolicy policy = new CompositeCompletionPolicy();

        // 여러 정책 설정
        policy.setPolicies(
                new CompletionPolicy[]{
                        new TimeoutTerminationPolicy(3),
                        new SimpleCompletionPolicy(1000)
                }
        );
      	return policy;
    }
```

다음과 같이 수행한 경우에는 chunk 단위가 1000개를 넘어선 경우가 없는 것을 확인할 수 있다.

```
>> end itemWriter chunk 731
>> end itemWriter chunk 1000
>> end itemWriter chunk 690
>> end itemWriter chunk 1000
>> end itemWriter chunk 798
>> end itemWriter chunk 1000
>> end itemWriter chunk 980
>> end itemWriter chunk 838
>> end itemWriter chunk 850
>> end itemWriter chunk 1000
>> end itemWriter chunk 263
>> end itemWriter chunk 556
>> end itemWriter chunk 629
>> end itemWriter chunk 962
>> end itemWriter chunk 960
>> end itemWriter chunk 1000
>> end itemWriter chunk 1000
>> end itemWriter chunk 1000
>> end itemWriter chunk 898
>> end itemWriter chunk 1000
>> end itemWriter chunk 900
>> end itemWriter chunk 798
>> end itemWriter chunk 215
```

## Step Listener

스탭과 청크의 시작과 끝에서 특정 로직을 처리할 수 있게 해준다.

(`StepListener`는 모든 스탭 리스너가 상속하는 마커 인터페이스이다.)

모든 수준에 리스너를 적용해 Job을 중단할 수 있으며, 일반적으로 전처리를 수행하거나 이후 결과를 평가하거나, 일부 오류처리에도 사용된다.

### `StepExecutionListener`

- `org.springframework.batch.core.StepExecutionListener`

```java
public interface StepExecutionListener extends StepListener {

	void beforeStep(StepExecution stepExecution);

  // Listener가 스텝이 반환한 ExitStatus를 Job에 전달하기 전에 수정할 수 있음.
	@Nullable
	ExitStatus afterStep(StepExecution stepExecution);
}
```

`@BeforeStep`, `@AfterStep` 애너테이션 제공

```java
public class LoggingStepStartStopListener {

    @BeforeStep
    public void beforeStep(StepExecution stepExecution) {
        System.out.println(stepExecution.getStepName() + " 시작");
    }


    @AfterStep
    public ExitStatus afterStep(StepExecution stepExecution) {
        System.out.println(stepExecution.getStepName() + " 종료");
        return stepExecution.getExitStatus();
    }
}
```

```java
    @Bean
    public Step chunkStep() {
        return this.stepBuilderFactory.get("chunkStep")
                .<String, String> chunk(randomChunkSizePolicy())
                .reader(itemReader())
                .writer(itemWriter())
                .listener(new LoggingStepStartStopListener()) // Listener 설정
                .build();
    }
```

### `ChunkListener`

```java
public interface ChunkListener extends StepListener {

	static final String ROLLBACK_EXCEPTION_KEY = "sb_rollback_exception";

	void beforeChunk(ChunkContext context);

	void afterChunk(ChunkContext context);

	void afterChunkError(ChunkContext context);
}
```

`@BeforeChunk`, `@AfterChunk` 애너테이션 제공

## Step Flow

### 조건 로직

스프링 배치의 Step은 `StepBuilder`의 `.next()` 메서드를 사용해 지정한 순서대로 실행된다.
전이(transition)를 구성해 결과에 따른 다른 순서로 실행하는 것도 가능하다.

```java
    @Bean
    public Job conditionalJob() {
        return this.jobBuilderFactory.get("conditionalJob")
                .start(firstStep())
                .on("FAILED").to(failureStep())
                .from(firstStep()).on("*").to(successStep())
                .end()
                .build();
    }
```

스프링 배치는 기준에 따라 두개의 와일드 카드를 허용한다.

- `*` : 0개 이상의 문자를 일치하는 것을 의미
    - `C*` : COMPLETE, CORRECT
- `?` :  1개의 문자를 일치 시키는 것을 의미
    - `?AT` : CAT, KAT과 일치하지만, THAT과는 불일치

#### JobExecutionDecider

Job 실행 정보(`jobExecution`)와 스탭 실행정보( `stepExecution`)를 인자로 받아 모든 정보를 이용해 다음에 무엇을 수행할지에 대해 결정할 수 있다.

```java
public interface JobExecutionDecider {

	/**
	 * Strategy for branching an execution based on the state of an ongoing
	 * {@link JobExecution}. The return value will be used as a status to
	 * determine the next step in the job.
	 * 
	 * @param jobExecution a job execution
	 * @param stepExecution the latest step execution (may be {@code null})
	 * @return the exit status code
	 */
	FlowExecutionStatus decide(JobExecution jobExecution, @Nullable StepExecution stepExecution);

}
```

 ```java
 public class RandomDecider implements JobExecutionDecider {
 
     private Random random = new Random();
 
     @Override
     public FlowExecutionStatus decide(JobExecution jobExecution, StepExecution stepExecution) {
         if (random.nextBoolean()) {
             return new FlowExecutionStatus(FlowExecutionStatus.COMPLETED.getName());
         } else {
             return new FlowExecutionStatus(FlowExecutionStatus.FAILED.getName());
         }
     }
 }
 ```

```java
    @Bean
    public Job conditionalJob() {
        return this.jobBuilderFactory.get("conditionalJob")
                .start(firstStep())
                .next(decider())
                .from(decider())
                .on("FAILED").to(failureStep())
                .from(decider()).on("*").to(successStep())
                .end()
                .build();
    }
```

### Job 종료하기

스프링 배치에서는 Job을 종료할 때 아래 3가지 상태로 종료할 수 있다.

| 상태            | 설명                                                         |
| --------------- | ------------------------------------------------------------ |
| Completed(완료) | 스프링 배치 처리가 성공적으로 종료됐음을 의미<br />`JobInstance`가 Completed로 종료되면 동일한 파라미터를 사용해 다시 실행할 수 없다. |
| Failed(실패)    | 잡이 성공적으로 완료되지 않았음을 의미<br />Failed 상태로 종료된 잡은 스프링 배치를 사용해 동일한 파라미터로 다시 실행할 수 있다. |
| Stopped(중지)   | Stopped 상태로 종료된 잡은 다시 수행 가능하다.<br />Job에 오류가 발생하지 않았어도, 중단된 위치에서 잡을 다시 시작할 수 있다.<br />사람의 개입이 필요하거나 다른 검사/처리가 필요한 상황에 유용하다. |

`BatchStatus`를 판별할 때, `ExitStatus`를 평가하면서 식별된다. 
`ExitStatus`는 스텝, 청크, 잡에서 반환될 수 있으며, `BatchStatus`는 `StepExecution` 이나 `JobExecution` 내에 보관되며, `JobRepository`에 저장된다.

#### Completed 상태로 종료하기

`.end()` 메서드 사용

```java
return this.jobBuilderFactory.get("conditionalJob")
                .start(firstStep())
                .on("FAILED").end()
                .from(firstStep()).on("*").to(successStep())
                .end()
                .build();
```

`BATCH_STEP_EXECUTION` 테이블에 스텝이 반환한 `ExitStatus`가 저장되며, 스텝이 반환한 상태가 무엇이든 상관없이 `BATCH_JOB_EXECUTION`에 `COMPLETED`가 저장된다.

#### Failed 상태로 종료하기

`fail()` 메서드 사용

```java
return this.jobBuilderFactory.get("conditionalJob")
                .start(firstStep())
                .on("FAILED").fail()
                .from(firstStep()).on("*").to(successStep())
                .end()
                .build();
```

여기서  `firstStep()` 이 FAILED로 끝나면, `JobRepository` 에 해당 Job이 실패한 것으로 저장되며, 동일한 파라미터를 사용해 다시 실행할 수 있다.

#### Stopped 상태로 종료하기

`.stopAndRestart()` 메서드로 잡을 다시 수행한다면, 미리 구성해둔 스텝부터 시작된다.
아래 예제에서는 재수행시 `successStep()`부터 수행되는것을 볼 수 있다.

```java
return this.jobBuilderFactory.get("conditionalJob")
                .start(firstStep())
                .on("FAILED").stopAndRestart(successStep())
                .from(firstStep()).on("*").to(successStep())
                .end()
                .build();
```

