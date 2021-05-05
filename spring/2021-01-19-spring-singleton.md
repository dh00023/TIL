# Spring Singleton

Spring에서의 singleton pattern을 알아보기 이전에 

- [Singleton 디자인패턴](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/singleton_pattern.md)
- [Item3 - Singleton](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-01-14-singleton.md)

를 선행하면 더 이해하는데 좋다.

## Singleton Container

**스프링은 기본적으로 별다른 설정을 하지 않으면 내부에서 생성하는 빈 오브젝트를 모두 싱글톤**으로 만든다.

스프링은 서버 환경에서 싱글톤이 만들어져 서비스 오브젝트 방식으로 사용되는 것은 적극 지지한다. 하지만 자바의 기본적인 싱글톤 패턴의 구현 방식은 여러가지 단점이 있기때문에 **스프링은 직접 싱글톤 형태의 오브젝트를 만들고 관리하는 기능을 제공**한다.

스프링 컨테이너는 싱글톤 컨테이너 역할을 하며, 이렇게 싱글톤 객체를 생성하고 관리하는 기능을 Singleton Registry라고 한다.

**Singleton Registry**의 장점은 평범한 자바 클래스이더라도 IoC방식의 컨테이너를 사용해 생성과 관계설정, 사용 등에 대한 제어권을 손쉽게 싱글톤 방식으로 만들어져 관리되게 할 수 있다. 그렇기 때문에 테스트 환경에서도 자유롭게 오브젝트를 만들 수 있고, 테스트를 위한 목적으로 오브젝트를 대체하는 것도 간단하다.

즉, 싱글턴 패턴의 단점을 해결하면서 객체를 싱글톤 방식으로 유지 할 수 있다. 

( 1. 싱글톤 패턴을 위한 지저분한 코드가 추가되지 않음. 2. DIP, OCP, 테스트, private 생성자로 부터 자유롭게 싱글톤 사용 가능)

싱글톤이 멀티스레드 환경에서 서비스 형태의 오브젝트로 사용되는 경우에는 stateless 방식으로 만들어져야한다. 이때는 읽기전용 값이라면 초기화 시점에 인스턴스 변수에 저장해두고 공유하는 것은 문제 없다. 만약 각 요청에 대한 정보나, DB 서버의 리소스로 부터 생성한 정보는 파라미터와 로컬 변수, 리턴 값을 이용하면 된다. 메소드 파라미터나, 메소드 안에서 생성되는 로컬 변수는 매번 새로운 값을 저장할 독립적인 공간이 만들어지기 때문에 싱글톤이라고 해도 문제없다.

## Spring에서의 Singleton Pattern

spring의 bean들은 Bean Factory에 의해서 관리되고 있으며, 기본적으로 이러한 bean의 생명주기의 scope는 singleton을 따르고 있다.
Spring Boot에서는 별도의 설정이 없다면, `DefaultListableBeanFactory`를 기본으로 사용하며, `resolveBean` 메소드를 보면 알 수 있다.

```java
    @Nullable
    private <T> T resolveBean(ResolvableType requiredType, @Nullable Object[] args, boolean nonUniqueAsNull) {
        // 1. 등록되어있는 bean들의 이름을 검색
        NamedBeanHolder<T> namedBean = resolveNamedBean(requiredType, args, nonUniqueAsNull);

        // 2. 등록되어있다면 해당 bean을 리턴(인스턴스)
        if (namedBean != null) {
            return namedBean.getBeanInstance();
        }

        // 3. 다른 beanfactory에서 요청한 bean 찾기    
        BeanFactory parent = getParentBeanFactory();
        if (parent instanceof DefaultListableBeanFactory) {
            return ((DefaultListableBeanFactory) parent).resolveBean(requiredType, args, nonUniqueAsNull);
        }
        else if (parent != null) {
            ObjectProvider<T> parentProvider = parent.getBeanProvider(requiredType);
            if (args != null) {
                return parentProvider.getObject(args);
            }
            else {
                return (nonUniqueAsNull ? parentProvider.getIfUnique() : parentProvider.getIfAvailable());
            }
        }
        // 4. 찾지 못했을 시 null 반환
        return null;
    }
```

하지만 여기에서는 private static 접근 제어자를 통한 singleton 패턴은 찾아볼 수 없다.

### 안티 패턴

안티 패턴이란, 습관적으로 많이 사용하는 패턴이지만 성능, 디버깅, 유지보수, 가독성 측면에서 부정적인 영향을 줄 수 있어 지양하는 패턴이다.

Singleton 패턴은 다음과 같은 단점이 있다.

1. private 생성자를 가지고 있어 상속을 할 수 없다.( 다형성 제공 불가능, 객체지향 설계 적용 불가)
2. 테스트가 어렵다.
3. 서버환경에서는 1개의 instance를 보장하지 못한다.
4. 전역 상태를 만들 수 있기 때문에 바람직하지 못하다.
	- singleton은 어디에서든지 누구나 접근해 사용할 수 있으므로, 객체지향에서 권장하지 되지 않는 프로그래밍 모델이다.

이러한 이유로 Spring에서 직접 싱글톤 패턴을 사용하지 않으며, **Singleton Registry** 방식을 사용한다.

### Singleton Registry / Singleton Pattern 주의점

객체 인스턴스를 하나만 생성해서 공유하는 싱글톤 방식은 여러 클라이언트가 하나의 같은 객체 인스턴스를 공유하기 때문에 싱글톤 객체는 상태를 유지 (stateful)하게 설계하면 안된다. **무상태(stateless)로 설계**해야 한다!

- 특정 클라이언트에 의존적인 필드가 있으면 안된다.
-  특정 클라이언트가 값을 변경할 수 있는 필드가 있으면 안된다!
-  가급적 읽기만 가능해야 한다.
-  필드 대신에 자바에서 공유되지 않는, 지역변수, 파라미터, ThreadLocal 등을 사용해야 한다.

스프링 빈의 필드에 공유 값을 설정하면 정말 큰 장애가 발생할 수 있다.



## @Configuration

```java
/**
 * 애플리케션의 실제 동작에 필요한 구현 객체 생성
 * 생성한 객체 인스턴스의 참조를 생성자를 통해 주입해준다.
 * @Configuration 어노테이션으로 @Bean이 싱글톤으로 관리될 수 있게 해준다.
 */
@Configuration
public class AppConfig {

    @Bean
    public MemberService memberService() {
        System.out.println("call AppConfig.memberService");
        return new MemberServiceImpl(memberRepository());
    }

    @Bean
    public MemberRepository memberRepository() {
        System.out.println("AppConfig.memberRepository");
        return new MemoryMemberRepository();
    }

    @Bean
    public OrderService orderService(){
        System.out.println("AppConfig.orderService");
        return new OrderServiceImpl(memberRepository(), getDiscountPolicy());
    }

    @Bean
    public DiscountPolicy getDiscountPolicy() {
        return new RateDiscountPolicy();
    }

}
```

```java
package dh0023.springcore.singleton;

import dh0023.springcore.config.AppConfig;
import dh0023.springcore.member.repository.MemberRepository;
import dh0023.springcore.member.service.MemberServiceImpl;
import dh0023.springcore.order.service.OrderServiceImpl;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ConfigurationSingletonTest {

    @Test
    void configurationTest() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(AppConfig.class);

        MemberServiceImpl memberService = ac.getBean("memberService", MemberServiceImpl.class);
        OrderServiceImpl orderService = ac.getBean("orderService", OrderServiceImpl.class);
        MemberRepository memberRepository = ac.getBean("memberRepository", MemberRepository.class);

        MemberRepository memberRepository1 = memberService.getMemberRepository();
        MemberRepository memberRepository2 = orderService.getMemberRepository();

        System.out.println("memberRepository = " + memberRepository);
        System.out.println("memberRepository1 = " + memberRepository1);
        System.out.println("memberRepository2 = " + memberRepository2);

        Assertions.assertThat(memberRepository).isSameAs(memberRepository1);
        Assertions.assertThat(memberRepository).isSameAs(memberRepository2);
    }


    @Test
    void configurationDeep() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(AppConfig.class);
        AppConfig bean = ac.getBean(AppConfig.class);

        System.out.println("bean = " + bean.getClass());
        // bean = class dh0023.springcore.config.AppConfig$$EnhancerBySpringCGLIB$$2a067523

    }
}

```

순수한 클래스라면  `class dh0023.springcore.config.AppConfig`로 출력되어야한다. 하지만, `@Configuration` 이 CGLIB 바이트 코드 조작 라이브러리를 사용해 `AppConfig` 를 상속받은 임의의 클래스(`AppConfig@CGLIB`)를 스프링 빈으로 등록한다.

`@Bean`이 붙은 메서드마다 이미 스프링 빈이 존재한다면, 존재하는 빈을 반환하고, 존재하지 않는다면 새로 생성하는 로직이 포함되어 있을 것으로 예상된다.

만약 `@Configuration` 을 설정하지 않고 `@Bean` 빈을 등록하면 어떻게 될까?

```java
/**
 * 애플리케션의 실제 동작에 필요한 구현 객체 생성
 * 생성한 객체 인스턴스의 참조를 생성자를 통해 주입해준다.
 * @Configuration 어노테이션으로 @Bean이 싱글톤으로 관리될 수 있게 해준다.
 */
public class AppConfig {

    @Bean
    public MemberService memberService() {
        System.out.println("call AppConfig.memberService");
        return new MemberServiceImpl(memberRepository());
    }

    @Bean
    public MemberRepository memberRepository() {
        System.out.println("AppConfig.memberRepository");
        return new MemoryMemberRepository();
    }

    @Bean
    public OrderService orderService(){
        System.out.println("AppConfig.orderService");
        return new OrderServiceImpl(memberRepository(), getDiscountPolicy());
    }

    @Bean
    public DiscountPolicy getDiscountPolicy() {
        return new RateDiscountPolicy();
    }

}
```

```java
package dh0023.springcore.singleton;

import dh0023.springcore.config.AppConfig;
import dh0023.springcore.member.repository.MemberRepository;
import dh0023.springcore.member.service.MemberServiceImpl;
import dh0023.springcore.order.service.OrderServiceImpl;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ConfigurationSingletonTest {

    @Test
    void configurationTest() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(AppConfig.class);

        MemberServiceImpl memberService = ac.getBean("memberService", MemberServiceImpl.class);
        OrderServiceImpl orderService = ac.getBean("orderService", OrderServiceImpl.class);
        MemberRepository memberRepository = ac.getBean("memberRepository", MemberRepository.class);

        MemberRepository memberRepository1 = memberService.getMemberRepository();
        MemberRepository memberRepository2 = orderService.getMemberRepository();

        System.out.println("memberRepository = " + memberRepository);
        System.out.println("memberRepository1 = " + memberRepository1);
        System.out.println("memberRepository2 = " + memberRepository2);

        Assertions.assertThat(memberRepository).isSameAs(memberRepository1);
        Assertions.assertThat(memberRepository).isSameAs(memberRepository2);
    }


    @Test
    void configurationDeep() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(AppConfig.class);
        AppConfig bean = ac.getBean(AppConfig.class);

        System.out.println("bean = " + bean.getClass());
        // bean = class dh0023.springcore.config.AppConfig

    }
}


```

`@Configuration`을 등록하지 않아도, **`@Bean`으로 스프링 빈등록이 가능**하나, 바이트 조작을 하지 않는 Class가 생성된다. 또한, **싱글톤이 보장되지 않는다.**



## 참고

- [https://sabarada.tistory.com/25](https://sabarada.tistory.com/25)
- [김영한 스프링 핵심 원리 - 기본편](https://inf.run/deVM)

