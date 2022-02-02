# Multithread Job구현시 이슈사항 정리

## Caused by: java.lang.RuntimeException: Driver com.mysql.cj.jdbc.Driver claims to not accept jdbcUrl,

- as-is

  ```yaml
  spring:
    datasource:
      driver-class-name: com.mysql.cj.jdbc.Driver
      url: jdbc:mysql://localhost:3306/spring_batch
      username: spring
      password: Springtest2021!
  ```

hikari설정을 하지 않은채 datasource설정을 하고 있었다. 그래서 다음과 같이 변경해 주었다.

- to-be

  ```yaml
  spring:
    datasource:
      hikari:
        driver-class-name: com.mysql.cj.jdbc.Driver
        jdbc-url: jdbc:mysql://localhost:3306/spring_batch
        username: spring
        password: Springtest2021!
  ```

여기서 추가로 주의해줘야할 부분이 있다.

`spring.datasource.hikari.jdbc-url`인데 `spring.datasource.hikari.url`로 설정하게 되면 다음과 같은 오류가 발생하면서 실패한다.

```
Caused by: java.lang.RuntimeException: Driver com.mysql.cj.jdbc.Driver claims to not accept jdbcUrl, jdbc:h2:mem:bc4ba7e6-c5cd-4c61-8406-7eb55dc03018;DB_CLOSE_DELAY=-1;DB_CLOSE_ON_EXIT=FALSE
	at com.zaxxer.hikari.util.DriverDataSource.<init>(DriverDataSource.java:110) ~[HikariCP-4.0.3.jar:na]
	at com.zaxxer.hikari.pool.PoolBase.initializeDataSource(PoolBase.java:331) ~[HikariCP-4.0.3.jar:na]
	at com.zaxxer.hikari.pool.PoolBase.<init>(PoolBase.java:114) ~[HikariCP-4.0.3.jar:na]
	at com.zaxxer.hikari.pool.HikariPool.<init>(HikariPool.java:108) ~[HikariCP-4.0.3.jar:na]
```

[기억보단 기록을 - Spring Boot & HikariCP Datasource 연동하기](https://jojoldu.tistory.com/296)를 참고해보면 `datasource.url`과 `datasource.jdbc-url`의 차이에 대해 설명해주고 있다.

- 자동 설정

  - `spring.datasource.url`이 모든 Datasource의 url이 된다.

- 수동 설정 (Java Config)

  - `spring.datasource.jdbc-url` 로 해야 한다. 

  - 이때 수동 설정없이 jdbc-url로 설정하면, `hirari.url`로 설정하는 것과 동일한 오류 발생하므로 주의해야한다.

    ```
    Caused by: java.lang.RuntimeException: Driver com.mysql.cj.jdbc.Driver claims to not accept jdbcUrl, jdbc:h2:mem:5513bc19-062e-4178-89ff-164d5bde2112;DB_CLOSE_DELAY=-1;DB_CLOSE_ON_EXIT=FALSE
    	at com.zaxxer.hikari.util.DriverDataSource.<init>(DriverDataSource.java:110) ~[HikariCP-4.0.3.jar:na]
    	at com.zaxxer.hikari.pool.PoolBase.initializeDataSource(PoolBase.java:331) ~[HikariCP-4.0.3.jar:na]
    	at com.zaxxer.hikari.pool.PoolBase.<init>(PoolBase.java:114) ~[HikariCP-4.0.3.jar:na]
    ```

-  `spring.datasource.hikari` : 상황에 따라 계속해서 `application.yml`을 수정할 수 없으므로,  hikari 설정을 별도로 하면 된다.

즉, HikariCP를 사용할경우 `spring.datasource`로 값을 설정하기 보다는 `spring.datasource.hikari`로 하시면 수동/자동 구분없이, 오해없이 설정할 수 있다.

  

## Transaction already active

```
java.lang.IllegalStateException: Transaction already active
	at org.hibernate.engine.transaction.internal.TransactionImpl.begin(TransactionImpl.java:74) ~[hibernate-core-5.4.32.Final.jar:5.4.32.Final]
	at org.springframework.batch.item.database.JpaPagingItemReader.doReadPage(JpaPagingItemReader.java:193) ~[spring-batch-infrastructure-4.3.3.jar:4.3.3]
	at org.springframework.batch.item.database.AbstractPagingItemReader.doRead(AbstractPagingItemReader.java:110) ~[spring-batch-infrastructure-4.3.3.jar:4.3.3]
	at org.springframework.batch.item.support.AbstractItemCountingItemStreamItemReader.read(AbstractItemCountingItemStreamItemReader.java:93) ~[spring-batch-infrastructure-4.3.3.jar:4.3.3]
	at org.springframework.batch.core.step.item.SimpleChunkProvider.doRead(SimpleChunkProvider.java:99) ~[spring-batch-core-4.3.3.jar:4.3.3]
	at org.springframework.batch.core.step.item.SimpleChunkProvider.read(SimpleChunkProvider.java:180) ~[spring-batch-core-4.3.3.jar:4.3.3]
```

위 오류와 같이 Transaction 오류가 발생하는 경우가 있었다. 오류의 시작 지점으로 가보니

```
021-12-10 01:19:49.430 ERROR 18132 --- [agingTaskPool-1] o.h.hql.internal.ast.ErrorTracker        : line 1:87: unexpected token: limit
2021-12-10 01:19:49.431 ERROR 18132 --- [agingTaskPool-1] o.h.hql.internal.ast.ErrorTracker        : line 1:87: unexpected token: limit

antlr.NoViableAltException: unexpected token: limit
	at org.hibernate.hql.internal.antlr.HqlBaseParser.primaryExpression(HqlBaseParser.java:1113) ~[hibernate-core-5.4.32.Final.jar:5.4.32.Final]
	at org.hibernate.hql.internal.antlr.HqlBaseParser.atom(HqlBaseParser.java:3946) ~[hibernate-core-5.4.32.Final.jar:5.4.32.Final]

```

query에 오류가 있어 1번째 threadPool에서 실패를 하여 transaction rollback을 시작했는데 뒤이어서 thread 2~4가 transaction rollback을 하다 보니, 해당 오류가 발생하는 것이었다.

- transaction-4

```2021-12-10 01:27:51.558 DEBUG 18183 --- [agingTaskPool-4] o.s.batch.core.step.tasklet.TaskletStep  : Rollback for RuntimeException: java.lang.IllegalStateException: Transaction already active
2021-12-10 01:27:51.558 DEBUG 18183 --- [agingTaskPool-4] o.s.t.support.TransactionTemplate        : Initiating transaction rollback on application exception

java.lang.IllegalStateException: Transaction already active
	at org.hibernate.engine.transaction.internal.TransactionImpl.begin(TransactionImpl.java:74) ~[hibernate-core-5.4.32.Final.jar:5.4.32.Final]
```

- transaction-3

```
2021-12-10 01:27:51.559 DEBUG 18183 --- [agingTaskPool-3] o.s.batch.core.step.tasklet.TaskletStep  : Rollback for RuntimeException: java.lang.IllegalStateException: Transaction already active
2021-12-10 01:27:51.559 DEBUG 18183 --- [agingTaskPool-3] o.s.t.support.TransactionTemplate        : Initiating transaction rollback on application exception

java.lang.IllegalStateException: Transaction already active
	at org.hibernate.engine.transaction.internal.TransactionImpl.begin(TransactionImpl.java:74) ~[hibernate-core-5.4.32.Final.jar:5.4.32.Final]

```

ItemWriter와 ItemReader의 Datasource설정을 따로 하여, 읽어올떄는 setReadOnly로 설정하여 해결해보고 추가로 내용 정리할 예정이다.



## multi thread 수행 완료 후 batch job 종료되지 않는 문제

[https://multifrontgarden.tistory.com/281](https://multifrontgarden.tistory.com/281)에 정리가 잘되어있어 참고하여 해결하였다.

### JVM이 종료되지 않는 이유

`ThreadPoolTaskExecutor`는 `ThreadPoolExecutor`를 활용해 병렬수행이 가능하도록 제공한다. `ThreadPoolExecutor`는 작업이 완료되면 명시적으로 `shutdown()` 메서드를 호출해 스레드를 종료시켜주고 있다.

jvm은 자식 스레드들이 살아있으면 종료되지 않는데, spring batch에서 `shutdown()`이 호출되지 않고 있어 종료되지 않는 것이다.

### Step에서 TaskExecutor 사용하는 경우

TaskExecutor를 step에서 설정하여 청크 단위로 병렬 처리를 하는 경우, `TaskExecutor`에는 `shutdown()` 메서드가 없는 인터페이스를 호출하기 때문에, `shutdown()` 메서드를 호출할 수 없다. 

```java
@FunctionalInterface
public interface TaskExecutor extends Executor {
	@Override
	void execute(Runnable task);
}
```

다음과 같이 `main()` 메서드를 작성하여 job종료시 jvm을 종료시킬 수 있다.

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

main thread가 종료되면, jvm을 강제로 종료하게 되며, main thread가 종료됐다는 것은 자식 thread들이 모두 종료됐다는 것을 의미하므로 모든 task가 완료된것을 보장할 수 있다.

[https://spring.io/guides/gs/batch-processing/](https://spring.io/guides/gs/batch-processing/) 공식 가이드문서에서도 위 방법을 가이드해주고 있다.

해당 설정을 한 후 수행해보면 정상적으로 바로 종료되는 것을 확인할 수 있다.

### ThreadPoolTaskExecutor 설정하기

```java
 // 쓰레드 풀을 이용한 쓰레드 관리 방식
ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
executor.setCorePoolSize(poolSize); // 풀의 기본 사이즈
executor.setMaxPoolSize(poolSize); // 풀의 최대 사이즈
executor.setThreadGroupName("multi-thread-");        executor.setWaitForTasksToCompleteOnShutdown(Boolean.TRUE);

// allowCoreThreadTimeOut을 true로 설정해
// core thread 가 일정시간 태스크를 받지 않을 경우 pool 에서 정리하고,
// 모든 자식 스레드가 정리되면 jvm 도 종료 되게 설정한다.
executor.setKeepAliveSeconds(30);
executor.setAllowCoreThreadTimeOut(true);
```

`allowCoreThreadTimeOut`는 keppAliveSeconds로 설정한 시간이 지나면, core thread도 pool에서 정리되도록 설정하는 것이다. 특정시간이 지나 core pool에 남아있는 thread도 없게되면 종료된다.

위 설정대로 설정한 후 실행해보면 정확히 Job이 수행 완료된 후 30초 후에 종료되는 것을 볼 수 있다.

```
2021-12-12 22:26:19.651 DEBUG 30911 --- [           main] o.s.b.a.ApplicationAvailabilityBean      : Application availability state ReadinessState changed to ACCEPTING_TRAFFIC
2021-12-12 22:26:49.649 DEBUG 30911 --- [ionShutdownHook] s.c.a.AnnotationConfigApplicationContext : Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@bcef303, started on Sun Dec 12 22:26:18 KST 2021
2021-12-12 22:26:49.649 DEBUG 30911 --- [ionShutdownHook] ySourcesPropertyResolver$DefaultResolver : Found key 'spring.liveBeansView.mbeanDomain' in PropertySource 'systemProperties' with value of type String
2021-12-12 22:26:49.652 DEBUG 30911 --- [ionShutdownHook] o.s.j.e.a.AnnotationMBeanExporter        : Unregistering JMX-exposed beans on shutdown
2021-12-12 22:26:49.653 DEBUG 30911 --- [ionShutdownHook] o.s.j.e.a.AnnotationMBeanExporter        : Unregistering JMX-exposed beans
2021-12-12 22:26:49.653 DEBUG 30911 --- [ionShutdownHook] o.s.s.concurrent.ThreadPoolTaskExecutor  : Shutting down ExecutorService 'multithreadPagingJobTaskPool'
```

