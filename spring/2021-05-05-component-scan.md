# 컴포넌트 스캔

스프링 빈을 등록할 때는 자바 코드의 `@Bean`이나 XML의 `<bean>` 등을 통해서 설정 정보에 직접 등록할 스프링 빈을 나열하여 등록할 수 있다. 하지만 이렇게 등록해야 할 스프링 빈이 수십, 수백개가 되면 일일이 등록하기도 힘들며, 설정 정보도 커지고, 누락하는 문제도 발생한다.

```java
@Configuration
public class AppConfig {

    @Bean
    public MemberService memberService() {
        return new MemberServiceImpl(memberRepository());
    }

    @Bean
    public MemberRepository memberRepository() {
        return new MemoryMemberRepository();
    }
}
```

스프링은 설정 정보가 없어도 자동으로 스프링 빈을 등록하는 **컴포넌트 스캔**이라는 기능을 제공한다.

`@ComponentScan`  : `@Component` 어노테이션이 붙은 빈을 다 등록해준다.

- `excludeFilters` : 제외할 Component 설정
- `includeFilters` : 포함할 Component 설정
- `basePackages` : 탐색할 기본 패키지 경로(설정 안한 경우 해당 어노테이션 패키지 하위로 설정)
  - `basePackages = {"dh0023.springcore.order", "dh0023.springcore.member"}` : 여러 시작 위치 지정가능
- `basePackageClassses` : 지정한 클래스의 패키지를 탐색 시작 위치로 지정(default : `@ComponentScan` 이 붙은 설정 정보 클래스 패키지 하위로 설정)

```java
package dh0023.springcore.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;

/**
 * @ComponentScan은 @Component 어노테이션이 붙은 클래스를 빈으로 등록해준다.
 * 기본패키지를 설정해주지 않으면, 현재 패키지 하위로 설정된다.
 * 예외하고 싶은 클래스가 있는 경우 excludeFilters로 설정할 수 있다.
 */
@Configuration
@ComponentScan(
        basePackages = "dh0023.springcore",
        excludeFilters = @ComponentScan.Filter(type = FilterType.ANNOTATION, classes = Configuration.class)
)
public class AutoAppConfig {

}
```

그러면 의존관계는 어떻게 주입하는 걸까? `@Autowired` 로 의존관계를 자동으로 주입할 수 있다.

`@Bean` 으로 생성해 직접 의존관계를 설정하던 코드에서, `@Component` 와 `@Autowired` 만으로 의존관계와 빈으로 등록할 수 있다.

```java
package dh0023.springcore.member.service;

import dh0023.springcore.member.domain.Member;
import dh0023.springcore.member.repository.MemberRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class MemberServiceImpl implements MemberService{

    /**
     * 생성자 DI를 통해 구현클래스 의존성 제거 => 실행에만 집중 가능
     */
    private final MemberRepository memberRepository;

  	/**
  	 * Autowired로 자동 의존관계 주입 가능
     */
    @Autowired
    public MemberServiceImpl(MemberRepository memberRepository) {
        this.memberRepository = memberRepository;
    }
}
```

- 별도로 빈 이름을 설정하고 싶은 경우에는 `@Component("설정할 빈 이름")` 과 같이 설정할  수 있다.
- `@Autowired` 를 지정하면 스프링 컨테이너가 해당 스프링 빈을 찾아서 주입하는데 이때, 타입이 같은 빈을 찾아서 주입을 한다.

### FilterType 옵션

| type              | 설명                                                         | 예                                                           |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `ANNOTATION`      | default<br />어노테이션을 인식해서 동작                      | `type = FilterType.ANNOTATION, classes = Configuration.class` |
| `ASSIGNABLE_TYPE` | 지정한 타입과 자식 타입을 인식해서 동작<br />클래스 직접 지정 | `org.example.ExampleService`                                 |
| `ASPECTJ`         | AspectJ 패턴 사용                                            | `org.example..*Service+`                                     |
| `REGEX`           | 정규 표현식                                                  | `org.example.Default.*`                                      |
| `CUSTOM`          | TypeFilter 이라는 인터페이스를 구현해서 처리                 | `org.example.MyTypeFilter`                                   |

### `@ComponentScan` 권장 위치

### `@ComponentScan` 권장 위치

패키지 위치를 별도로 지정하지 않고, 설정 정보 클래스 위치를 프로젝트 최상단에 두는 것을 권장한다.(스프링 부트도 이 방법으로 시작)

프로젝트 메인 설정 정보는 프로젝트를 대표하는 정보이기 때문에 프로젝트 시작 루트 위치에 두는 것을 권장한다.

```java
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@SpringBootConfiguration
@EnableAutoConfiguration
@ComponentScan(excludeFilters = { @Filter(type = FilterType.CUSTOM, classes = TypeExcludeFilter.class),
		@Filter(type = FilterType.CUSTOM, classes = AutoConfigurationExcludeFilter.class) })
public @interface SpringBootApplication {

	/**
	 * Exclude specific auto-configuration classes such that they will never be applied.
	 * @return the classes to exclude
	 */
	@AliasFor(annotation = EnableAutoConfiguration.class)
	Class<?>[] exclude() default {};

	/**
	 * Exclude specific auto-configuration class names such that they will never be
	 * applied.
	 * @return the class names to exclude
	 * @since 1.3.0
	 */
	@AliasFor(annotation = EnableAutoConfiguration.class)
	String[] excludeName() default {};
  ...
}
```

스프링 부트를 사용하면 스프링 부트의 대표 시작 정보인 `@SpringBootApplication` 안에 `@ComponentScan` 이 포함되어있으며, 보통 최상단에 해당 클래스가 위치해있다.

### `@ComponentScan` 대상

`@Component` 뿐만 아니라 다른 어노테이션들도 추가로 대상에 포함된다. 

예를 들어 `@Configuration` 어노테이션을 살펴보자.

```java
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Component
public @interface Configuration {
	//...
}
```

해당 어노테이션 내부에 `@Component` 어노테이션을 포함하고 있는 것을 볼 수 있다. `@ComponentScan` 은 `@Component` 어노테이션이 붙어있는 클래스는 모두 빈으로 등록하므로, `@Controller`, `@Service`, `@Repository` 등등 어노테이션이 붙은 클래스도 빈으로 등록하는 것을 알 수 있다.

- 어노테이션에는 상속관계라는 것이 없으며, 특정 애노테이션을 들고 있는 것을 인식할 수 있는 것은 자바 언어가 지원하는 기능은 아니고, 스프링이 지원하는 기능이다.

### 중복 등록과 충돌

#### 자동빈등록 vs 자동 빈등록

컴포넌트 스캔에 의해 자동으로 스프링 빈이 등록되는데, 그 이름이 같은 경우 스프링은 `ConflictingBeanDefinitionException` 예외 발생시킨다.

이러한 경우는 거의 발생하지 않는다.

#### 수동 빈 등록 vs 자동 빈 등록

```java
@Component
public class MemoryMemberRepository implements MemberRepository {}
```

```java
@Configuration
@ComponentScan(
  	excludeFilters = @Filter(type = FilterType.ANNOTATION, classes = Configuration.class)
)
public class AutoAppConfig {
		
  	@Bean(name = "memoryMemberRepository")
    public MemberRepository memberRepository() {
    		return new MemoryMemberRepository();
    }
}
```

같은 이름으로 수동빈과 자동빈이 등록된 경우에는, 수동 빈등록이 우선권을 가진다.

```
Overriding bean definition for bean 'memoryMemberRepository' with a different
definition: replacing
```

수동빈이 자동 빈을 오버라이딩 한다.

최근 스프링 부트에서는 수동 빈 등록과 자동 빈 드옭이 충돌나면 오류가 발생하도록 기본 값을 바꾸었으며, 만약 오버라이딩을 가능하게 하고 싶으면 `spring.main.allow-bean-definition-overriding=true` 로 옵션을 설정하라고 가이드를 주고 있다.

```
Consider renaming one of the beans or enabling overriding by setting
spring.main.allow-bean-definition-overriding=true
```



## 테스트 코드로 확인

### 기본 `@ComponentScan` 빈등록 확인

```java
package dh0023.springcore.scan;

import dh0023.springcore.config.AutoAppConfig;
import dh0023.springcore.member.service.MemberService;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class AutoAppConfigTest {

    @Test
    void basicScan() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(AutoAppConfig.class);

        MemberService memberService = ac.getBean(MemberService.class);

        Assertions.assertThat(memberService).isInstanceOf(MemberService.class);
    }
}
```

```java
23:44:34.697 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'org.springframework.context.event.internalEventListenerProcessor'
23:44:34.701 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'org.springframework.context.event.internalEventListenerFactory'
23:44:34.713 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'org.springframework.context.annotation.internalAutowiredAnnotationProcessor'
23:44:34.716 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'org.springframework.context.annotation.internalCommonAnnotationProcessor'
23:44:34.739 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'autoAppConfig'
23:44:34.748 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'rateDiscountPolicy'
23:44:34.749 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'memoryMemberRepository'
23:44:34.750 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'memberServiceImpl'
23:44:34.858 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Autowiring by type from bean name 'memberServiceImpl' via constructor to bean named 'memoryMemberRepository'
23:44:34.860 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Creating shared instance of singleton bean 'orderServiceImpl'
23:44:34.865 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Autowiring by type from bean name 'orderServiceImpl' via constructor to bean named 'memoryMemberRepository'
23:44:34.866 [main] DEBUG org.springframework.beans.factory.support.DefaultListableBeanFactory - Autowiring by type from bean name 'orderServiceImpl' via constructor to bean named 'rateDiscountPolicy'
```

로그를 보면 singleton bean이 등록되는 것을 볼 수 있으며,  Autowired도 확인할 수 있다.



### 예외/포함 확인

- MyExcludeComponent

```java
package dh0023.springcore.scan.filter;

import java.lang.annotation.*;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface MyExcludeComponent {
}
```

- MyIncludeComponent

```java
package dh0023.springcore.scan.filter;

import java.lang.annotation.*;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface MyIncludeComponent {
}

```

- BeanA

```java
package dh0023.springcore.scan.filter;

@MyIncludeComponent
public class BeanA {
}
```

- BeanB

```java
package dh0023.springcore.scan.filter;

@MyExcludeComponent
public class BeanB {
}

```

- Test

```java
package dh0023.springcore.scan.filter;

import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.NoSuchBeanDefinitionException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;

import static org.assertj.core.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.*;

public class ComponentFilterAppConfigTest {

    @Test
    void filterScan() {
        ApplicationContext ac = new AnnotationConfigApplicationContext(ComponentFilterAppConfig.class);

        BeanA beanA = ac.getBean("beanA", BeanA.class);
        assertThat(beanA).isNotNull();

        assertThrows(
                NoSuchBeanDefinitionException.class, () -> ac.getBean("beanB", BeanB.class)
        );


    }

    @Configuration
    @ComponentScan(
            includeFilters = @ComponentScan.Filter(type = FilterType.ANNOTATION, classes = MyIncludeComponent.class),
            excludeFilters = @ComponentScan.Filter(type = FilterType.ANNOTATION, classes = MyExcludeComponent.class)
    )
    static class ComponentFilterAppConfig {
    }
}

```



## 참고

- [김영한 스프링 핵심 원리 - 기본편](https://inf.run/deVM)