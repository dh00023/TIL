# 배치 개발시 발생하는 오류

## EL1008E: Property or field 'jobParameters' cannot be found on object of type 

```
Caused by: org.springframework.beans.factory.BeanExpressionException: Expression parsing failed; nested exception is org.springframework.expression.spel.SpelEvaluationException: EL1008E: Property or field 'jobParameters' cannot be found on object of type 'org.springframework.beans.factory.config.BeanExpressionContext' - maybe not public or not valid?
	at org.springframework.context.expression.StandardBeanExpressionResolver.evaluate(StandardBeanExpressionResolver.java:170) ~[spring-context-5.3.12.jar:5.3.12]
	at org.springframework.beans.factory.support.AbstractBeanFactory.evaluateBeanDefinitionString(AbstractBeanFactory.java:1631) ~[spring-beans-5.3.12.jar:5.3.12]
	at org.springframework.beans.factory.support.DefaultListableBeanFactory.doResolveDependency(DefaultListableBeanFactory.java:1324) ~[spring-beans-5.3.12.jar:5.3.12]
	at org.springframework.beans.factory.support.DefaultListableBeanFactory.resolveDependency(DefaultListableBeanFactory.java:1300) ~[spring-beans-5.3.12.jar:5.3.12]
	at org.springframework.beans.factory.support.ConstructorResolver.resolveAutowiredArgument(ConstructorResolver.java:887) ~[spring-beans-5.3.12.jar:5.3.12]
	at org.springframework.beans.factory.support.ConstructorResolver.createArgumentArray(ConstructorResolver.java:791) ~[spring-beans-5.3.12.jar:5.3.12]
	... 66 common frames omitted
```

- jobParameters를 사용하는데 Scope를 설정해주지 않아서 발생하는 오류이다.

  ```java
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
  ```

- `StepScope` or `JobScope`를 붙여주면된다.

    ```java
    @Bean
    @StepScope
    public MethodInvokingTaskletAdapter methodInvokingTasklet(
      @Value("#{jobParameters['message']}") String message) {
    ```


- [Batch Scope & Job Parameters](./2021-01-31-batch-scope.md)



## The bean 'systemCommandJob', defined in class path resource [class], could not be registered.

스프링 5.1.0 은 컴포넌트 탐색과정에서 발생하는 오버헤드를 감소시키기 위한 여러가지 정책이 반영되었는데, 그 중에 하나가 생성한 빈을 덮어쓰는 상황을 강제적으로 제한한다.

그래서 동일한 이름을 가진 스프링 빈이 등록되려고 하면 BeanDefinitionOverrideException 이 발생한다.

```
Exception encountered during context initialization - cancelling refresh attempt: org.springframework.beans.factory.support.BeanDefinitionOverrideException: Invalid bean definition with name 'systemCommandJob' defined in class path resource [io/spring/batch/javagradle/tasklet/SystemCommandJob.class]: Cannot register bean definition [Root bean: class [null]; scope=; abstract=false; lazyInit=null; autowireMode=3; dependencyCheck=0; autowireCandidate=true; primary=false; factoryBeanName=systemCommandJob; factoryMethodName=systemCommandJob; initMethodName=null; destroyMethodName=(inferred); defined in class path resource [io/spring/batch/javagradle/tasklet/SystemCommandJob.class]] for bean 'systemCommandJob': There is already [Generic bean: class [io.spring.batch.javagradle.tasklet.SystemCommandJob]; scope=singleton; abstract=false; lazyInit=null; autowireMode=0; dependencyCheck=0; autowireCandidate=true; primary=false; factoryBeanName=null; factoryMethodName=null; initMethodName=null; destroyMethodName=null; defined in file [/Users/dh0023/Develop/spring/spring-practice/batch-practice/build/classes/java/main/io/spring/batch/javagradle/tasklet/SystemCommandJob.class]] bound.
```

동일한 이름의 Bean이 등록된 경우 발생하는 오류이다.

```java
@EnableBatchProcessing
@Configuration
public class SystemCommandJob {
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
```

이때는 `SystemCommandJob` 클래스와 `systemCommandJob` Bean의 이름이 동일해서 발생한 오류이다. 

```yaml
spring:
   main:
     allow-bean-definition-overriding: true
```

만약 빈 overriding을 가능하게 하고 싶으면 다음과 같이 설정하면 된다.

## 참고

- [https://oingdaddy.tistory.com/178](https://oingdaddy.tistory.com/178)

