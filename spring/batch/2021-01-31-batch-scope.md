# Batch Scope & Job Parameter

Spring Batch의 경우 **외부, 내부에서 파라미터를 받아 여러 Batch 컴포넌트에서 사용할 수 있게 지원하고 있는데 이를 Job Parameter**라 한다. 

Job Parameter를 사용하기 위해서는 항상 Spring Batch 전용 Scope를 선언해야하는데 종류는 크게 `@StepScope`와 `@JobScope`가 있다.

```java
@Value("#{jobParameters[파라미터명]}")
```

Job Parameter는 `Double`, `Long`, `Date`, `String` 타입을 사용할 수 있으며, `LocalDate`와 `LocalDateTime`은 제공하지 않아, 타입을 변환해서 사용해야한다.

Job Parameter 사용시 많이 오해하는 부분이 있다. Job Parameter는 **Scope Bean을 생성할때만 사용 가능하다.** 즉, **`@StepScope`, `@JobScope`** **Bean을 생성할때만  Job Parameters가 생성된다.**

## Bean Scope

Spring Bean의 **기본 Scope는 singleton**이지만, `@JobScope`, `@StepScope`를 사용하게되면 Spring Batch가 **지정된 Job/Step의 실행 시점에 해당 컴포넌트를 Spring Bean으로 생성**한다. 즉, **Bean의 생성 시점을 지정된 Scope가 실행되는 시점**으로 지연시킬 수 있다.

> JobScope, StepScope는 Job/Step이 실행되고 끝날때 각각 생성/삭제가 이루어진다고 보면된다.

이렇게 Bean 생성시점을 지연시키면 얻는 장점은 크게 2개가 있다.

**1. JobParameter의 Late Binding**

꼭 application이 실행되는 시점이 아니더라도, Controller, Service와 같은 비즈니스 로직 처리단계에서 Job Parameter를 할당시킬 수 있다.

**2. 동일한 컴포넌트를 병렬 혹은 동시에 사용할때 유용**

예를 들어, Step내부에 Tasklet이 있고, 이 Tasklet은 멤버 변수를 변경하는 로직이 있다고 가정해보자.

이 경우 `@StepScope` 없이 Step을 병렬로 실행하게되면 서로 다른 Step에서 하나의 Tasklet을 두고 마구잡이로 상태를 변경하려고 할것이다. 하지만, `@StepScope`로 Scope를 변경하면 각각의 Step에서 별도의 Tasklet을 생성하고 관리하기 때문에 서로의 상태를 침범할 일이 없다.

## 사용 예제

### @JobScope

`@JobScope`는 **Step** 선언문에서 사용가능

```java
@Bean
public Job scopeJob() {
  	return jobBuilderFactory.get("scopeJob")
      			.start(scopeStep())
      			.build();
}

@Bean
@JobScope
public Step scopeStep(@Value("#{jobParameters[requestDate]}") String requestDate){
  
  	return stepBuilderFactory.get("scopeStep")
      				.tasklet((stepContribution, chunkContext) -> {
                    log.info(">>> Start step : {}", requestDate);
                    return RepeatStatus.FINISHED;
                }).build();
}
```

### @StepScope

`@StepScope`는 **Tasklet, ItemReader, ItemWriter, ItemProcessor** 등에서 사용 가능

```java
@Bean
public Step scopeStep2(){  
  	return stepBuilderFactory.get("scopeStep2")
      				.tasklet(scopeStepTasklet())
      				.build();
}


@Bean
@StepScope
public Tasklte scopeStepTasklet(@Value("#{jobParameters[requestDate]}") String requestDate){  
  	return (stepContribution, chunkContext) -> {
               log.info(">>> Start scopeStepTasklet : {}", requestDate);
               return RepeatStatus.FINISHED;
            };
}
```

### Class 멤버 변수로 할당받기

```java
@Bean
public Job simpleJob() {
  	return jobBuilderFactory.get("simpleJob")
      			.start(simpleStep())
      			.build();
}

// 생성자
private final SimpleJobTasklet tasklet;

public Step simpleStep(){
  	log.info("Start simpleStep");
  
  	return stepBuilderFactory.get("simpleStep")
      				.tasklet(tasklet1).build();
}
```

```java
/**
	* StepScope로 생성했기때문에 JobParameters를 받아올 수 있다.
	*/

@Component
@StepScope
public class SimpleJobTasklet implements Tasklet{
  
  	// 클래스 멤버 변수로 할당
  	@Value("#{jobParameters[requestDate]}")
  	private String requestDate;
  
  	public SimpleJobTasklet(){ log.info("SimpleJobTasklet 생성");}
  
  	@Override
  	public RepeatStatus execute(StepContribution contribution, ChunkContext chunkContext) throws Exception{
      	log.info("SimpleJobTasklet execute");
      	log.info("requestDate : {}", requestDate);
      
      	return RepeatStatus.FINISHED;
    }
}
```



## Job Parameter vs 시스템 변수

### JobParameter

```java
@Bean
@StepScope
public FlatFileItemReader<Partner> reader(
        @Value("#{jobParameters[pathToFile]}") String pathToFile){
    FlatFileItemReader<Partner> itemReader = new FlatFileItemReader<Partner>();
    itemReader.setLineMapper(lineMapper());
    itemReader.setResource(new ClassPathResource(pathToFile));
    return itemReader;
}
```

### 시스템 변수

시스템 변수는 `application.properties`와 `-D` 옵션으로 실행하는 변수 포함

```java
@Bean
@ConfigurationProperties(prefix = "my.prefix")
protected class JobProperties {

    String pathToFile;

    ...getters/setters
}

@Autowired
private JobProperties jobProperties;

@Bean
public FlatFileItemReader<Partner> reader() {
    FlatFileItemReader<Partner> itemReader = new FlatFileItemReader<Partner>();
    itemReader.setLineMapper(lineMapper());
    String pathToFile = jobProperties.getPathToFile();
    itemReader.setResource(new ClassPathResource(pathToFile));
    return itemReader;
}
```



**1. 시스템 변수를 사용하게 되는 경우 Spring Batch의  Job Parameter 관련 기능을 사용하지 못한다.**

Spring Batch는 같은 JobParameter로 같은 Job을 두 번 수행하지 않는다. 하지만 시스템 변수를 사용하게 되는 경우에는 이 기능이 전혀 동작하지 않게 된다. 또한 Spring Batch에서 자동으로 관리해주는 Parameter 관련 메타 테이블에 전혀 관리가 되지 않게 된다.

즉, Job Parameter를 사용하지 못하는 것은 Late Binding을 못한다는 의미이다. 

**2. Command Line이 아닌 다른 방법으로 Job을 실행하기 어렵다.**

## 주의 사항

```java
@Scope(
    value = "step",
    proxyMode = ScopedProxyMode.TARGET_CLASS
)
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface StepScope {
}
```

`@StepScope` 내부 코드를 보면 `@Scope(value = "step", proxyMode = ScopedProxyMode.TARGET_CLASS)` 로 표시하는 것과 같다. 이때 `proxyMode`로 인한 문제가 발생할 수 있다. 

예를 들어 `@StepScope`를 사용하는데, 해당 Bean의 return type이 인터페이스인 경우에 문제가 발생할 수 있다.

```java
@Bean
@StepScope
public ItemReader<Person> reader(@Value("#{jobParameters[name]}") String name){
  	Map<String, Object> params = new HashMap<>();
  	params.put("name", name);
  
	  JpaPagingItemReader<Person> reader = new JpaPagingItemReader<>();
  	reader.setQueryString("select * from person where name = :name");
  	reader.setParameterValues(params);
  	reader.setEntityManagerFactory(entityManagerFactory);
  	reader.setPageSize(CHUNK_SIZE);
		return reader;
}
```

```
o.s.b.c.l.AbstractListenerFactoryBean    : org.springframework.batch.item.ItemReader is an interface.  The implementing class will not be queried for annotation based listener configurations.  If using @StepScope on a @Bean method, be sure to return the implementing class so listner annotations can be used.
```

관련 내용을 정리하면 다음과 같다.

**`@Bean` 메소드에서 `@StepScope`를 사용하는 경우 listner 어노테이션을 사용할 수 있도록 구현 클래스를 return**해야한다. 아래와 같이  구현 클래스를 return하여 해당 문제점을 해결할 수 있다.

```java
@Bean
@StepScope
public JpaPagingItemReader<Person> reader(@Value("#{jobParameters[name]}") String name){
  	Map<String, Object> params = new HashMap<>();
  	params.put("name", name);
  
	  JpaPagingItemReader<Person> reader = new JpaPagingItemReader<>();
  	reader.setQueryString("select * from person where name = :name");
  	reader.setParameterValues(params);
  	reader.setEntityManagerFactory(entityManagerFactory);
  	reader.setPageSize(CHUNK_SIZE);
		return reader;
}
```



## 참고

- [기억보단 기록을 - 5. Spring Batch 가이드 - Spring Batch Scope & Job Parameter](https://jojoldu.tistory.com/330?category=902551) 
- [기억보단 기록을 - Spring Batch에서 @StepScope 사용시 주의사항](https://jojoldu.tistory.com/132)