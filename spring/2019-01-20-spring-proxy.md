# JDK Proxy

![https://www.baeldung.com/wp-content/uploads/2017/10/springaop-process.png](./assets/springaop-process.png)



스프링에서는 **JDK 동적 프록시**와 **CGLib 프록시**를 사용하고 있다.

#### 다이나믹 프록시란 무엇일까?

- 런타임 시에 동적으로 만들어지는 오브젝트
-  java의 reflection을 이용해서 proxy 객체 생성(`java.lang.reflect`)
- 타겟 인터페이스와 동일한 형태로 생성
  - 프록시 대상의 객체가 최소 하나 이상의 인터페이스를 구현했다면 JDK 동적 프록시를 이용하면된다.
- FactoryBean(팩토리빈)을 통해 생성



> 스프링의 빈은 기본적으로 클래스 이름과 Property로 정의한다.
>
> 스프링은 지정된 클래스 이름을 가지고 reflection을 이용해 해당 클래스의 객체(object)를 생성한다.

> FactoryBean은 스프링은 대신해서 Object 생성 로직을 담당하도록 만들어진 빈이다.



#### 구현과정

1. Proxy.newProxyInstance() 를 통한 프록시 생성
2. Proxy.newProxyInstance() 호출할 때 전달하는 InvocationHandler 인터페이스의 단일 메소드인 invoke()에 부가기능을 단 한번만 구현함으로써 코드 중복을 해결할 수 있다.

다이나믹 프록시 객체는 클래스 파일 자체가 존재하지 않으며, 빈 객체로 등록이 불가하다.



```java
public interface ServiceTest {
  void print();
}

@Service
public class ServiceTestImpl implements ServiceTest {
  @Async
  public void print() {
  }
}

@RestController
public class HelloController {
  private final ServiceTest service;
  public HelloController(ServiceTest service) {
    this.service = service;
    System.out.println(service.getClass());
  }
}
```

```zsh
class com.sun.proxy.$Proxy60
```

위의 코드를 살펴보면 인터페이스(ServiceTest)를 구현한 객체(ServiceTestImpl)이 있다. print문의 결과를 보면 JDK 동적 프록시가 들어간 것을 확인할 수 있다.

스프링 AOP를 이용하여 프록시 객체를 생성해볼 것이다. 스프링 내부에서 제공하는 FactoryBean 클래스를 사용하여 생성할 것이다.

```java
ProxyFactory proxyFactory = new ProxyFactory();
proxyFactory.setInterfaces(ServiceTest.class);
proxyFactory.setTarget(new ServiceTestImpl());
proxyFactory.addAdvice(new ServiceAdvice());
final ServiceTest proxy = (ServiceTest) proxyFactory.getProxy();
System.out.println(proxy.getClass());
```

```java
class com.sun.proxy.$Proxy60
```

인터페이스가 있어서 JDK 동적 프록시가 생성된 것을 볼 수 있다.

### CGLib Proxy

바이트 코드를 조작해서 프록시 객체를 생성한다. 

대상 객체의 인터페이스를 구현하지 않는 경우에는 CGLib 프록시를 이용하여 객체를 생성한다.

```java
@Service
public class ServiceTestImpl {
  @Async
  public void print() {
  }
}

@RestController
public class HelloController {
  private final ServiceTest service;
  public HelloController(ServiceTest service) {
    this.service = service;
    System.out.println(service.getClass());
  }
}
```

```java
class me.wonwoo.ServiceTestImpl$$EnhancerBySpringCGLIB$$bababcc1
```

인터페이스 없이 생성한 경우에는 CGLib 프록시로 생성된 것을 확인할 수 있다.

스프링 AOP를 이용하여 프록시 객체를 생성해볼 것이다. 스프링 내부에서 제공하는 FactoryBean 클래스를 사용하여 생성할 것이다.

```java
ProxyFactory proxyFactory = new ProxyFactory();
proxyFactory.setTarget(new ServiceTestImpl());
proxyFactory.addAdvice(new ServiceAdvice());
final ServiceTest proxy = (ServiceTest) proxyFactory.getProxy();
System.out.println(proxy.getClass());
```

```java
class me.wonwoo.ServiceTestImpl$$EnhancerBySpringCGLIB$$bababcc1
```

인터페이스 없이 생성한 경우에는 CGLib 프록시 객체가 생성된 것을 볼 수 있다.

하지만 CGLib Proxy는 제약 사항이 있다.

- `final` 메소드와 클래스의 경우에는 Advice를 할 수 없다.

```java
@Bean
public final SomeObject someObject(){
  return new SomeObject();
}

@Service
public final class ServiceTestImpl {
   //....
}
```

위와 같은 **final** 클래스와 메서드는 오류가 발생한다.(JDK 동적 프록시는 final 클래스나 메소드여도 상관없다. )

프록시 객체에 CGLib을 강제화 하고 싶다면 다음과 같이 설정할 수 있다. 강제화를 하게되면 인터페이스가 있는 경우에도 CGLib 프록시 객체가 삽입된다.

```java
@EnableAsync(proxyTargetClass = true)
@EnableCaching(proxyTargetClass = true)
```

#### JDK Dynamic Proxy vs CGLIB

두 방식의 차이는 **인터페이스의 유무** 로서, AOP의 타깃이 되는 클래스가 인터페이스를 구현하였다면 JDK Dynamic Proxy 사용, 구현하지 않았다면 CGLIB 방식을 사용한다.

사용자가 어떻게 설정하느냐에 따라서 인터페이스를 구현했다 하더라도 CGLIB 방식을 강제하거나 AspectJ를 사용할 수 있다.

- CGLIB(스프링의 XML 설정 파일에 빈을 등록하는 방법)

```xml
<!--proxy-targetclass="true"을 추가하여 CGLIB을 사용하도록 한다.-->
<aop:config proxy-target-class="true"> 
    <!-- other beans defined here... -->
    <aop:pointcut id="fooServiceMethods" expression="execution(* x.y.service.*.*(..))"/>
    <aop:advisor advice-ref="txAdvice" pointcut-ref="fooServiceMethods"/>
</aop:config>
```

- AspectJ : 어노테이션 기반의 스타일 선호

```xml
<aop:aspectj-autoproxy proxy-target-class="true"> 
```



### AspectJ

타겟 오브젝트를 직접 조작하는 방법이다.

#### 참조 페이지

- [http://ooz.co.kr/205?category=818548](http://ooz.co.kr/205?category=818548)
- [http://wonwoo.ml/index.php/post/1576](http://wonwoo.ml/index.php/post/1576)