# 빈 생명주기

스프링 빈은 **객체생성 -> 의존관계주입**의 라이프사이클을 가진다. (생성자 주입의 경우 예외)

스프링 빈은 객체를 생성하고, 의존관계 주입이 다 끝난 후에 필요한 데이터를 사용할 수 있는 준비가 완료된다. 따라서 의존관계 주입이 모두 완료되고 난 후에 초기화가 호출되야한다.

- 스프링은 의존관계 주입이 완료되면 스프링 빈에 콜백 메서드를 통해서 초기화 시점을 알려주는 다양한 기능을 제공한다.
- 스프링 컨테이너가 종료되기 직전에 소멸 콜백을 준다.

#### 스프링 빈 이벤트 라이프사이클

![https://media.geeksforgeeks.org/wp-content/uploads/20200428011831/Bean-Life-Cycle-Process-flow3.png](./assets/Bean-Life-Cycle-Process-flow3.png)

1. 스프링 컨테이너 생성
2. 스프링 빈 생성
3. 의존관계 주입
4. 초기화 콜백 : 빈이 생성되고, 빈의 의존관계 주입이 완료된 후 
5. 사용
6. 소멸전 콜백 : 빈이 소멸되기 직전에 호출
7. 스프링 종료

> 생성자는 필수 정보를 받고, 메모리를 할당해서 객체를 생성하는 책임을 가진다.
>
> 초기화는 이렇게 생성된 값을 활용해서 외부 커넥션을 연결하는 등 무거운 동작을 수행한다.
>
> 즉, **생성자 안에서 초기화 작업을 함께 하는 것 보다는 객체를 생성하는 부분과 초기화 하는 부분은 명확하게 나누는 것이 유지보수 관점에 좋다.**

## 콜백 방법

### 인터페이스 방법

`InitializingBean`, `DisposableBean` 을 구현하여, 초기화 메서드와 소멸 메서드를 설정할 수 있다.

- InitializingBean

  ```java
  public interface InitializingBean {
  
  	/**
  	 * Invoked by the containing {@code BeanFactory} after it has set all bean properties
  	 * and satisfied {@link BeanFactoryAware}, {@code ApplicationContextAware} etc.
  	 * <p>This method allows the bean instance to perform validation of its overall
  	 * configuration and final initialization when all bean properties have been set.
  	 * @throws Exception in the event of misconfiguration (such as failure to set an
  	 * essential property) or if initialization fails for any other reason
  	 */
  	void afterPropertiesSet() throws Exception;
  
  }
  ```

- DisposableBean

  ```java
  public interface DisposableBean {
  
  	/**
  	 * Invoked by the containing {@code BeanFactory} on destruction of a bean.
  	 * @throws Exception in case of shutdown errors. Exceptions will get logged
  	 * but not rethrown to allow other beans to release their resources as well.
  	 */
  	void destroy() throws Exception;
  
  }
  ```

- 예제 클래스

  ```java
  package dh0023.springcore.lifecycle;
  
  import org.springframework.beans.factory.DisposableBean;
  import org.springframework.beans.factory.InitializingBean;
  
  /**
   * 테스트를 위한 가짜 NetworkClient
   */
  public class NetworkClient implements InitializingBean, DisposableBean {
  
      private String url;
  
      public NetworkClient() {
          System.out.println("생성자 호출, url = " + url);
      }
  
      public void setUrl(String url) {
          this.url = url;
      }
  
      // start service
      public void connect() {
          System.out.println("connect: " + url);
      }
  
      public void call(String message) {
          System.out.println("call: " + url + " message = " + message);
      }
  
      public void disconnect() {
          System.out.println("close: " + url);
      }
  
      /**
       * 의존관계 주입 후 호출
       * @throws Exception
       */
      @Override
      public void afterPropertiesSet() throws Exception {
          System.out.println("NetworkClient.afterPropertiesSet");
          connect();
          call("초기화 연결 메세지");
      }
  
      /**
       * 소멸직후 콜백
       * @throws Exception
       */
      @Override
      public void destroy() throws Exception {
          System.out.println("NetworkClient.destroy");
          disconnect();
      }
  }
  
  ```

- Test Code

  ```java
  package dh0023.springcore.lifecycle;
  
  import org.junit.jupiter.api.Test;
  import org.springframework.context.ConfigurableApplicationContext;
  import org.springframework.context.annotation.AnnotationConfigApplicationContext;
  import org.springframework.context.annotation.Bean;
  import org.springframework.context.annotation.Configuration;
  import org.springframework.context.annotation.Description;
  
  public class BeanLifeCycleTest {
  
      @Test
      @Description("인터페이스 적용 테스트")
      void lifeCycleInterfaceTest() {
          ConfigurableApplicationContext ac = new AnnotationConfigApplicationContext(LifeCycleConfig.class);
          NetworkClient client = ac.getBean(NetworkClient.class);
          ac.close();
      }
  
  
      @Configuration
      static class LifeCycleConfig {
          @Bean
          public NetworkClient networkClient() {
              NetworkClient networkClient = new NetworkClient();
              networkClient.setUrl("http://spring-core.dev");
              return networkClient;
          }
      }
  }
  
  ```

- 결과

  ```
  23:23:39.553 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'networkClient'
  생성자 호출, url = null
  NetworkClient.afterPropertiesSet
  connect: http://spring-core.dev
  call: http://spring-core.dev message = 초기화 연결 메세지
  23:23:39.645 [main] DEBUG org.springframework.context.annotation.AnnotationConfigApplicationContext - Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@932bc4a, started on Sun May 16 23:23:38 KST 2021
  NetworkClient.destroy
  close: http://spring-core.dev
  
  Process finished with exit code 0
  ```

  1. Creating shared instance of singleton bean 'networkClient'
  2. 생성자 호출
  3. NetworkClient.afterPropertiesSet
  4. Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@932bc4a
  5. NetworkClient.destroy
  6. 스프링 종료

  다음과 같은 순서로 사이클이 수행되는 것을 확인할 수 있다.

#### 단점

- 스프링 전용 인터페이스이다. 해당 코드가 스프링 전용 인터페이스에 의존하게 된다.
- 초기화, 소멸 메서드의 이름을 변경할 수 없다.
- 외부 라이브러리에 적용할 수 없다.

이 방법은 초창기 나온 방법으로, 현재는 거의 사용하지 않는다.



### 설정 정보 사용(메서드 등록)

`@Bean` 어노테이션에 등록 초기화, 소멸 메서드를 설정하는 방법이다.

- 예제 클래스

  ```java
  /**
   * 테스트를 위한 가짜 NetworkClient
   */
  public class NetworkClientMethod {
  
      private String url;
  
      public NetworkClientMethod() {
          System.out.println("생성자 호출, url = " + url);
  
      }
  
      public void setUrl(String url) {
          this.url = url;
      }
  
      // start service
      public void connect() {
          System.out.println("connect: " + url);
      }
  
      public void call(String message) {
          System.out.println("call: " + url + " message = " + message);
      }
  
      public void disconnect() {
          System.out.println("close: " + url);
      }
  
      public void init() {
          System.out.println("NetworkClientMethod.init");
          connect();
          call("초기화 연결 메세지");
  
      }
  
      public void close() {
          System.out.println("NetworkClientMethod.close");
          disconnect();
      }
  
  }
  ```

- 테스트 코드

  ```java
  package dh0023.springcore.lifecycle;
  
  import org.junit.jupiter.api.Test;
  import org.springframework.context.ConfigurableApplicationContext;
  import org.springframework.context.annotation.AnnotationConfigApplicationContext;
  import org.springframework.context.annotation.Bean;
  import org.springframework.context.annotation.Configuration;
  import org.springframework.context.annotation.Description;
  
  public class BeanLifeCycleTest {
  
      @Test
      @Description("메서드 적용 테스트")
      void lifeCycleMethodTest() {
          ConfigurableApplicationContext ac = new AnnotationConfigApplicationContext(LifeCycleConfig.class);
          NetworkClientMethod client = ac.getBean(NetworkClientMethod.class);
          ac.close();
      }
  
  
      @Configuration
      static class LifeCycleConfig {
  
          @Bean(initMethod = "init", destroyMethod = "close")
          public NetworkClientMethod networkClientMethod() {
              NetworkClientMethod networkClientMethod = new NetworkClientMethod();
              networkClientMethod.setUrl("http://spring-core.dev");
              return networkClientMethod;
          }
      }
  }
  
  ```

- 결과

  ```java
  23:35:00.964 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'networkClientMethod'
  생성자 호출, url = null
  NetworkClientMethod.init
  connect: http://spring-core.dev
  call: http://spring-core.dev message = 초기화 연결 메세지
  23:35:01.128 [main] DEBUG org.springframework.context.annotation.AnnotationConfigApplicationContext - Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@932bc4a, started on Sun May 16 23:35:00 KST 2021
  NetworkClientMethod.close
  close: http://spring-core.dev
  
  Process finished with exit code 0
  ```

  1. Creating shared instance of singleton bean 'networkClientMethod'
  2. 생성자 호출
  3. 초기화 콜백 : NetworkClientMethod.init 
  4. Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@932bc4a
  5. 소멸직후 콜백 : NetworkClientMethod.close
  6. 스프링 종료

#### 특징

- 메서드 이름을 자유롭게 줄 수 있다.
- 스프링 빈이 스프링 코드에 의존하지 않는다.
- 설정 정보를 사용하기 때문에 코드를 고칠 수 없는 외부 라이브러리에도 초기화, 종료 메서드를 적용할 수 있다.

#### @Bean destroyMethod

라이브러리 대부분 `close`, `shutdown` 과 같은 이름의 종료 메서드를 사용한다.

```java
	String destroyMethod() default AbstractBeanDefinition.INFER_METHOD;
```

```java
public static final String INFER_METHOD = "(inferred)";
```

`destoryMethod()` 의 default값은 `(inferred)` 로 등록되어 있다. 이 추론 기능은 `close`, `shutdown` 과 같은 이름의 메서드를 자동으로 호출해준다. 이름 그대로 종료 메서드를 추론해서 호출해주는 것이다.

따라서 직접 스프링 빈으로 등록하면 종료 메서드는 따로 적어주지 않아도 된다. 만약 추론기능을 사용하기 싫은 경우에는 `destroyMethod=""` 로 설정해주면 된다.

### 어노테이션 방법

- `@PostConstruct`

  ```java
  package javax.annotation;
  
  import java.lang.annotation.*;
  import static java.lang.annotation.ElementType.*;
  import static java.lang.annotation.RetentionPolicy.*;
  
  /**
   * The <code>PostConstruct</code> annotation is used on a method that 
   * needs to be executed after dependency injection is done to perform 
   * any initialization. This  method must be invoked before the class 
   * is put into service. This annotation must be supported on all classes 
   * that support dependency injection. The method annotated with 
   * <code>PostConstruct</code> must be invoked even if the class does 
   * not request any resources to be injected. Only one 
   * method in a given class can be annotated with this annotation. 
   * The method on which the <code>PostConstruct</code> annotation is 
   * applied must fulfill all of the following criteria:
   * <ul>
   * <li>The method must not have any parameters except in the case of 
   * interceptors in which case it takes an <code>InvocationContext</code>
   * object as defined by the Interceptors specification.</li>
   * <li>The method defined on an interceptor class or superclass of an
   * interceptor class must have one of the following signatures:
   * <p>
   * void &#060;METHOD&#062;(InvocationContext)
   * <p>
   * Object &#060;METHOD&#062;(InvocationContext) throws Exception
   * <p>
   * <i>Note: A PostConstruct interceptor method must not throw application 
   * exceptions, but it may be declared to throw checked exceptions including 
   * the java.lang.Exception if the same interceptor method interposes on 
   * business or timeout methods in addition to lifecycle events. If a 
   * PostConstruct interceptor method returns a value, it is ignored by 
   * the container.</i>
   * </li>
   * <li>The method defined on a non-interceptor class must have the 
   * following signature:
   * <p>
   * void &#060;METHOD&#062;()
   * </li>
   * <li>The method on which the <code>PostConstruct</code> annotation
   * is applied may be public, protected, package private or private.</li>
   * <li>The method must not be static except for the application client.</li>
   * <li>The method should not be final.</li>
   * <li>If the method throws an unchecked exception the class must not be put into   
   * service except in the case where the exception is handled by an
   * interceptor.</li></ul>
   *
   * @see javax.annotation.PreDestroy
   * @see javax.annotation.Resource
   * @since 1.6, Common Annotations 1.0
   */
  @Documented
  @Retention (RUNTIME)
  @Target(METHOD)
  public @interface PostConstruct {
  }
  
  ```

- `@PreDestroy` 

  ```java
  package javax.annotation;
  
  import java.lang.annotation.*;
  import static java.lang.annotation.ElementType.*;
  import static java.lang.annotation.RetentionPolicy.*;
  
  /**
   * The <code>PreDestroy</code> annotation is used on a method as a
   * callback notification to signal that the instance is in the
   * process of being removed by the container. The method annotated
   * with <code>PreDestroy</code> is typically used to
   * release resources that it has been holding. This annotation must be
   * supported by all container-managed objects that support the use of
   * the <code>PostConstruct</code> annotation except the Jakarta EE application 
   * client. The method on which the <code>PreDestroy</code> annotation
   * is applied must fulfill all of the following criteria:
   * <ul>
   * <li>The method must not have any parameters except in the case of
   * interceptors in which case it takes an <code>InvocationContext</code>
   * object as defined by the Interceptors specification.</li>
   * <li>The method defined on an interceptor class or superclass of an
   * interceptor class must have one of the following signatures:
   * <p>
   * void &#060;METHOD&#062;(InvocationContext)
   * <p>
   * Object &#060;METHOD&#062;(InvocationContext) throws Exception
   * <p>
   * <i>Note: A PreDestroy interceptor method must not throw application
   * exceptions, but it may be declared to throw checked exceptions including
   * the java.lang.Exception if the same interceptor method interposes on
   * business or timeout methods in addition to lifecycle events. If a
   * PreDestroy interceptor method returns a value, it is ignored by
   * the container.</i>
   * </li>
   * <li>The method defined on a non-interceptor class must have the
   * following signature:
   * <p>
   * void &#060;METHOD&#062;()
   * </li>
   * <li>The method on which PreDestroy is applied may be public, protected,
   * package private or private.</li>
   * <li>The method must not be static.</li>
   * <li>The method should not be final.</li>
   * <li>If the method throws an unchecked exception it is ignored by
   * the container.</li>
   * </ul>
   *
   * @see javax.annotation.PostConstruct
   * @see javax.annotation.Resource
   * @since 1.6, Common Annotations 1.0
   */
  
  @Documented
  @Retention (RUNTIME)
  @Target(METHOD)
  public @interface PreDestroy {
  }
  
  ```

- 테스트 클래스

  ```java
  package dh0023.springcore.lifecycle;
  
  import org.springframework.beans.factory.DisposableBean;
  import org.springframework.beans.factory.InitializingBean;
  
  import javax.annotation.PostConstruct;
  import javax.annotation.PreDestroy;
  
  /**
   * 테스트를 위한 가짜 NetworkClient
   */
  public class NetworkClient {
  
      private String url;
  
      public NetworkClient() {
          System.out.println("생성자 호출, url = " + url);
      }
  
      public void setUrl(String url) {
          this.url = url;
      }
  
      // start service
      public void connect() {
          System.out.println("connect: " + url);
      }
  
      public void call(String message) {
          System.out.println("call: " + url + " message = " + message);
      }
  
      public void disconnect() {
          System.out.println("close: " + url);
      }
  
      /**
       * 의존관계 주입 후 호출
       * @throws Exception
       */
      @PostConstruct
      public void init() throws Exception {
          System.out.println("NetworkClient.init");
          connect();
          call("초기화 연결 메세지");
      }
  
      /**
       * 소멸직전 콜백
       * @throws Exception
       */
      @PreDestroy
      public void close() throws Exception {
          System.out.println("NetworkClient.close");
          disconnect();
      }
  }
  ```

- 테스트 코드

  ```java
  package dh0023.springcore.lifecycle;
  
  import org.junit.jupiter.api.Test;
  import org.springframework.context.ConfigurableApplicationContext;
  import org.springframework.context.annotation.AnnotationConfigApplicationContext;
  import org.springframework.context.annotation.Bean;
  import org.springframework.context.annotation.Configuration;
  import org.springframework.context.annotation.Description;
  
  public class BeanLifeCycleTest {
      @Test
      @Description("어노테이션 방 적용 테스트")
      void lifeCycleTest() {
          ConfigurableApplicationContext ac = new AnnotationConfigApplicationContext(LifeCycleConfig.class);
          NetworkClient client = ac.getBean(NetworkClient.class);
          ac.close();
      }
  
  
      @Configuration
      static class LifeCycleConfig {
          @Bean
          public NetworkClient networkClient() {
              NetworkClient networkClient = new NetworkClient();
              networkClient.setUrl("http://spring-core.dev");
              return networkClient;
          }
      }
  }
  
  ```

- 결과

  ```java
  23:50:43.425 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'networkClient'
  생성자 호출, url = null
  NetworkClient.init
  connect: http://spring-core.dev
  call: http://spring-core.dev message = 초기화 연결 메세지
  23:50:43.557 [main] DEBUG org.springframework.context.annotation.AnnotationConfigApplicationContext - Closing org.springframework.context.annotation.AnnotationConfigApplicationContext@932bc4a, started on Sun May 16 23:50:42 KST 2021
  NetworkClient.destroy
  close: http://spring-core.dev
  ```

#### 특징

- **최신 스프링에서 가장 권장하는 방법**
- 애노테이션만 붙이면 되므로 매우 편리
- `javax.annotation` 패키지는 스프링 종속적인 기술이 아니라 자바 표준이다. 따라서, 스프링이 아닌 다른 컨테이너에서도 동작한다.

#### 단점

- 외부 라이브러리에 적용하지 못한다. 외부 라이브러리를 초기화/종료 해야하면 `@Bean` 의 기능을 사용해야한다.

## 참고

- [김영한 스프링 핵심 원리 - 기본편](https://inf.run/deVM)

