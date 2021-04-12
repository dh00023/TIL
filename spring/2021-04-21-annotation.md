# Spring Bean

Spring Bean을 등록하는데 있어서 2가지 방법이 있다.

1. 컴포넌트 스캔과 자동 의존관계 설정
2. 자바 코드로 직접 스트링 빈 등록하기

## 컴포넌트 스캔과 자동 의존관계 설정

| Annotation | 설명 |
|:------|:------|
|@Component| `@Component` 어노테이션이 있으면, 스프링 빈으로 자동 등록된다.|
|@Controller| 컨트롤러 |
|@Service| 서비스 |
|@Repository|  |
|@Autowired| 객체 생성 시점에 스프링 컨테이너에서 해당 스프링 빈을 찾아서 주입한다. <br>스프링이 관리하는 객체에서만 동작<br>(서비스 간의 연결 선 역할이라고 생각하면 이해하기 쉽다.) |

위에서 보이는 `@Controller`, `@Repository`, `@Service` 모두 내부에 `@Component` 어노테이션이 포함되어 있는 것을 볼 수 있다.

- `@Controller`

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Component
public @interface Controller {

	/**
	 * The value may indicate a suggestion for a logical component name,
	 * to be turned into a Spring bean in case of an autodetected component.
	 * @return the suggested component name, if any (or empty String otherwise)
	 */
	@AliasFor(annotation = Component.class)
	String value() default "";

}
```

- `@Repository`

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Component
public @interface Repository {

	/**
	 * The value may indicate a suggestion for a logical component name,
	 * to be turned into a Spring bean in case of an autodetected component.
	 * @return the suggested component name, if any (or empty String otherwise)
	 */
	@AliasFor(annotation = Component.class)
	String value() default "";

}
```

이렇게 `@Component` 어노테이션을 보고 스프링 빈으로 등록되는 것을 컴포넌트 스캔이라고 한다.

### 예제 코드

- Controller

```java
package dh0023.springmvc.member.controller;

import dh0023.springmvc.member.service.MemberService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;

@Controller
public class MemberController {


    private final MemberService memberService;

    @Autowired
    public MemberController(MemberService memberService){
        this.memberService = memberService;
    }

}

```

- Service

```java
package dh0023.springmvc.member.service;

import dh0023.springmvc.member.domain.Member;
import dh0023.springmvc.member.repository.MemberRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class MemberService {


    private final MemberRepository memberRepository;

    @Autowired
    public MemberService(MemberRepository memberRepository){
        this.memberRepository = memberRepository;
    }
    ...
}

```

- Repository

```java
@Repository
public class MemoryMemberRepository implements MemberRepository{

    // 실무에서는 ConcurrentHashMap을 사용해야한다.
    private static Map<Long, Member> store = new HashMap<>();
    private static long sequence = 0L;

		...
}

```



## 자바 코드로 직접 스트링 빈 등록하기

`@Service`, `@Repository` 어노테이션으로 빈을 등록하지 않고 직접 `@Bean` 어노테이션으로 빈을 등록 할 수 있다.

- Controller

```java
@Controller
public class MemberController {


    private final MemberService memberService;

    @Autowired
    public MemberController(MemberService memberService){
        this.memberService = memberService;
    }

}
```

- Service

```java
public class MemberService {


    private final MemberRepository memberRepository;

    public MemberService(MemberRepository memberRepository){
        this.memberRepository = memberRepository;
    }
  // ...
}
```

- Repository

```java
public class MemoryMemberRepository implements MemberRepository{
	...
}
```

- Configuration 설정

```java
@Configuration
public class SpringConfig {

    @Bean
    public MemberService memberService(){
        return new MemberService(memberRepository());
    }

    @Bean
    public MemberRepository memberRepository(){
        return new MemoryMemberRepository();
    }
}
```



## 언제 사용해야할까?

정형화된 Controller, Servcie, Repository는 컴포넌트 스캔을 사용한다.

하지만, 정형화 되지 않거나, 상황에 따라 구현 클래스를 변경해야 하면 설정을 통해 스프링 빈으로 등록한다.