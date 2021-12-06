# 스프링 배치 Job별 Bean등록하기

스프링배치에서 여러개의 Job을 생성하다보니, 동일한 Bean에 대한 충돌 오류가 계속해서 발생했다.

```java
@RequiredArgsConstructor
@Configuration
public class JpaCursorCustomerJob {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    @Bean
    public Job  job(){
        return jobBuilderFactory.get("jpaCursorItemReaderJob")
                .start(jpaCursorItemReaderStep())
                .build();
    }
```

```java
@RequiredArgsConstructor
@Configuration
public class HibernateCursorCustomerJob {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    @Bean
    public Job job() {
        return jobBuilderFactory.get("hibernateCursorItemReaderJob")
                .start(hibernateCursorItemReaderStep())
                .build();
    }
```

```
defined in class path resource [io/spring/batch/javagradle/book/basic/db/cursor/job/JpaCursorCustomerJob.class]] for bean 'job': There is already [Root bean: class [null]; scope=; abstract=false; lazyInit=null; autowireMode=3; dependencyCheck=0; autowireCandidate=true; primary=false; factoryBeanName=hibernateCursorCustomerJob; factoryMethodName=job; initMethodName=null; destroyMethodName=(inferred); defined in class path resource [io/spring/batch/javagradle/book/basic/db/cursor/job/HibernateCursorCustomerJob.class]] bound.
```

`application.yml`에 bean overriding을 허용하도록 할 수도 있지만, 

```yaml
spring:
	main:
		allow-bean-definition-overriding: true
```

해당 빈들이 모두 등록될 필요가 없기때문에 수행할 job.name을 가진 실제로 수행할 Job의 Bean만 등록하고 싶어 `@ConditionalOnProperty` 어노테이션을 사용할 것이다.

## @ConditionalOnProperty란?

`application.properties` or `application.yml`의 속성 값에 따라 조건부로 일부 빈을 생성 해야하는 경우에만 생성 가능하게 해준다.

```yaml
spring:
  batch:
    job:
      names: ${job.name:NONE} # argument로 전달하는 job 수행
```
스프링 배치에서 다음과 같이 수행할 Job이름을 받아올 때 Job 이름에 해당하는 Class의 빈만 등록하도록 하려고 할때,

```java
@RequiredArgsConstructor
@Configuration
@ConditionalOnProperty(name = "spring.batch.job.names", havingValue = "hibernateCursorItemReaderJob")
public class HibernateCursorCustomerJob {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    @Bean
    public Job job() {
        return jobBuilderFactory.get("hibernateCursorItemReaderJob")
                .start(hibernateCursorItemReaderStep())
                .build();
    }
```

```java
@RequiredArgsConstructor
@Configuration
@ConditionalOnProperty(name = "spring.batch.job.names", havingValue = "jpaCursorItemReaderJob")
public class JpaCursorCustomerJob {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    @Bean
    public Job  job(){
        return jobBuilderFactory.get("jpaCursorItemReaderJob")
                .start(jpaCursorItemReaderStep())
                .build();
    }
```

각각 Job 이름에 따라 등록하도록 설정 하였다.
여기서 `name`은 프로퍼티 key값이며, `havingValue`에 포함된 값인 경우에만 조건부로 빈을 등록하겠다는 것이다.

위와 같이 설정하여 `--job.name=hibernateCursorItemReaderJob city=Chicago`로 수행하면

```
   JpaCursorCustomerJob:
      Did not match:
         - @ConditionalOnProperty (spring.batch.job.names=jpaCursorItemReaderJob) found different value in property 'spring.batch.job.names' (OnPropertyCondition)


   HibernateCursorCustomerJob matched:
      - @ConditionalOnProperty (spring.batch.job.names=hibernateCursorItemReaderJob) matched (OnPropertyCondition)
```

`JpaCursorCustomerJob`는 job.name이 다르므로 빈 등록에서 제외되고, `HibernateCursorCustomerJob`는 일치하여 빈 등록이 된것을 확인할 수 있다.

하지만 여기서 문제가 발생했다.

```
2021-12-06 23:30:57.326 DEBUG 64228 --- [           main] o.s.b.a.b.JobLauncherApplicationRunner   : No job found in registry for job name: hibernateCursorItemReaderJob
2021-12-06 23:30:57.327 DEBUG 64228 --- [           main] o.s.b.a.ApplicationAvailabilityBean      : Application availability state ReadinessState changed to ACCEPTING_TRAFFIC
2021-12-06 23:30:57.329 DEBUG 64228 --- [ionShutdownHook] s.c.a.AnnotationConfigApplicationContext : Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@58c34bb3, started on Mon Dec 06 23:30:50 KST 2021
```

`No job found in registry for job name: hibernateCursorItemReaderJob` 해당 job이름을 찾을 수 없다는 로그가 찍혔고 다음과 같이 조건부로 빈을 설정하면 `JobRegistry`에 등록이 안되는 것이다.


## 별도로 등록한 Bean JobRegistry에 등록하기


두가지 방법으로 해결할 수 있다.

### 1. Job을 Bean으로 등록하기전 JobRegistry에 등록
    
```java
    @Bean
    public Job job() throws DuplicateJobException {
        Job job = jobBuilderFactory.get("jpaCursorItemReaderJob")
                .start(jpaCursorItemReaderStep())
                .build();
        ReferenceJobFactory factory = new ReferenceJobFactory(job);
        jobRegistry.register(factory);
        return job;
    }
```

다음과 같이 jobRegistry에 등록해주면 되지만, Job Bean 선언마다 등록해줘야하는 단점이 있다.

### 2. `JobRegistryBeanPostProcessor` 활용하기

`BatchConfigurer`를 하나 생성하여 `JobRegistryBeanPostProcessor`를 등록해줄것이다.

```java
    @Bean
    public JobRegistryBeanPostProcessor jobRegistryBeanPostProcessor(JobRegistry jobRegistry) {
        JobRegistryBeanPostProcessor jobRegistryBeanPostProcessor = new JobRegistryBeanPostProcessor();
        jobRegistryBeanPostProcessor.setJobRegistry(jobRegistry);
        return jobRegistryBeanPostProcessor;
    }
```

`JobRegistryBeanPostProcessor`는 Job마다 등록할 필요 없이 Job이 빈으로 등록될 때 후처리를 통해 `JobRegistry`에 등록해준다.


매번 Job을 등록할때마다 선언을 해줘야하는 1번방법보다 기본 `BatchConfigurer`를 하나 생성해주고, 해당 `BatchConfigurer`를 `@Import`하는 방법으로 해결할 것이다.

```java
import org.springframework.batch.core.configuration.JobRegistry;
import org.springframework.batch.core.configuration.annotation.EnableBatchProcessing;
import org.springframework.batch.core.configuration.support.JobRegistryBeanPostProcessor;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Component;

@EnableBatchProcessing
@Component
public class BasicBatchConfigurer {

    @Bean
    public JobRegistryBeanPostProcessor jobRegistryBeanPostProcessor(JobRegistry jobRegistry) {
        JobRegistryBeanPostProcessor jobRegistryBeanPostProcessor = new JobRegistryBeanPostProcessor();
        jobRegistryBeanPostProcessor.setJobRegistry(jobRegistry);
        return jobRegistryBeanPostProcessor;
    }

}
```

```java
@RequiredArgsConstructor
@Configuration
@ConditionalOnProperty(name = "spring.batch.job.names", havingValue = "jpaCursorItemReaderJob")
@Import(BasicBatchConfigurer.class)
public class JpaCursorCustomerJob {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    @Bean
    public Job job() throws DuplicateJobException {

        return jobBuilderFactory.get("jpaCursorItemReaderJob")
                .start(jpaCursorItemReaderStep())
                .build();;
    }
```

해당 Job을 수행하면 정상적으로 수행되는 것을 확인할 수 있다.

```
2021-12-07 00:13:08.665  INFO 99799 --- [           main] o.s.b.c.l.support.SimpleJobLauncher      : Job: [SimpleJob: [name=jpaCursorItemReaderJob]] completed with the following parameters: [{city=Houston, ids=6}] and the following status: [COMPLETED] in 393ms
```

## 참고

- [http://www.java2s.com/example/java-api/org/springframework/batch/core/configuration/support/jobregistrybeanpostprocessor/jobregistrybeanpostprocessor-0-0.html](http://www.java2s.com/example/java-api/org/springframework/batch/core/configuration/support/jobregistrybeanpostprocessor/jobregistrybeanpostprocessor-0-0.html)
- [https://meteorkor.tistory.com/87](https://meteorkor.tistory.com/87)
