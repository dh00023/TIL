# 스프링 부트

스프링 부트는 필요한 환경 설정을 최소화하고 개발자가 비즈니스 로직에 집중할 수 있도록 도와줘 생산생을 향상시켰다.

## 특징

- 임베디드 톰캣, 제티, 언더토우를 사용해 독립 실행이 가능한 스프링 애플리케이션 개발
- 통합 스타터를 제공하여 maven/gradle 구성 간소화
- 스타터를 통한 자동화된 스프링 설정 제공
- 번거로운 XML 설정 요구하지 않음
- JAR을 사용해 자바 옵션만으로도 배포 가능
- 애플리케이션의 모니터링과 관리를 위한 Spring Actuator 제공


- [Spring Boot Reference Guide](https://docs.spring.io/spring-boot/docs/current/reference/htmlsingle/)를 참고해 스타터 내부의 의존성을 확인할 수 있다.

## 라이브러리

- spring-boot-starter-web
    - spring-boot-starter-tomcat: 톰캣(웹서버)
    - spring-webmvc: 스프링 웹 MVC
- spring-boot-starter-thymeleaf: 타임리프 템플릿 엔진(View)
- spring-boot-starter: 스프링 부트 + 스프링 코어 + 로깅
    - spring-boot
        - spring-core
    - spring-boot-starter-logging
        - logback, slf4j
- spring-boot-starter-test: 스프링부트 테스트

## 장단점

### 장점

- 각각의 의존성 버전을 올리는 것이 조금 더 수월하다.
- 특정 라이브러리에 버그가 있더라도 스프링팀의 버그 픽스한 버전을 받기 편리하다.
- 간단한 어노테이션 설정이나 프로퍼티 설정으로 세부적인 설정 없이 원하는 기능을 빠르게 적용할 수 있다.
- 별도의 외장 톰캣을 설치할 필요가 없다.

### 단점

- 설정을 개인화하면 버전을 올릴 때 기존 스프링 프레임워크를 사용하는 것과 동일한 불편함을 겪을 수 있다.
- 특정 설정을 개인화 혹은 설정 자체를 변경하고 싶다면, 내부의 설정 코드를 살펴봐야하는 불편함이 있다.



## 자동 환경 설정

스프링 부트 자동 환경설정은 Web, H2, JDBC를 비롯해 약 100여 개의 자동 설정을 제공한다. 그리고 새로 추가되는 라이브러리는 스프링 부트 자동-설정 의존성에 따라 설정이 자동 적용된다. 자동 설정은 `@EnableAutoConfiguration` (`@Configuration`과 반드시 같이 사용) 또는 `@SpringBootApplication` 중 하나를 사용하면 된다.

스프링 프레임워크에서는 의존성을 일일이 빈으로 설정했으나, 스프링 부트는 관련 의존성을 스타터라는 묶음으로 제공해 수동 설정을 지양한다.

### @SpringBootApplication

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@SpringBootConfiguration
@EnableAutoConfiguration
@ComponentScan(
    excludeFilters = {@Filter(
    type = FilterType.CUSTOM,
    classes = {TypeExcludeFilter.class}
), @Filter(
    type = FilterType.CUSTOM,
    classes = {AutoConfigurationExcludeFilter.class}
)}
)
public @interface SpringBootApplication {
  ...
}
```

- `@SpringBootConfiguration` : 스프링 부트의 설정을 나타내는 어노테이션
  - Spring의 `@Configuration` 대체
  - 스프링부트 전용
- `@EnableAutoConfiguration` :  **자동 설정의 핵심 어노테이션** 
  - 클래스 경로에 지정된 내용을 기반으로 자동 설정
  - 특별한 설정값을 추가하지 않으면 default값 설정
- `@ComponentScan` : 특정 패키지 경로를 기반으로 `@configuration`에서 사용할 `@Component`  설정 클래스를 찾는다.
  - basePackages 프로퍼티 값에 별도로 값을 설정하지 않으면, `@ComponentScan`이 위치한 패키지가 루트 경로로 설정



### @EnableAutoConfiguration

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@AutoConfigurationPackage
@Import({AutoConfigurationImportSelector.class})
public @interface EnableAutoConfiguration {
    String ENABLED_OVERRIDE_PROPERTY = "spring.boot.enableautoconfiguration";

    Class<?>[] exclude() default {};

    String[] excludeName() default {};
}
```

여기서 자동 설정을 지원해주는 어노테이션은 `@Import({AutoConfigurationImportSelector.class})`이다. 

```java
public class AutoConfigurationImportSelector implements DeferredImportSelector, BeanClassLoaderAware, ResourceLoaderAware, BeanFactoryAware, EnvironmentAware, Ordered {
    private static final AutoConfigurationImportSelector.AutoConfigurationEntry EMPTY_ENTRY = new AutoConfigurationImportSelector.AutoConfigurationEntry();
    private static final String[] NO_IMPORTS = new String[0];
    private static final Log logger = LogFactory.getLog(AutoConfigurationImportSelector.class);
    private static final String PROPERTY_NAME_AUTOCONFIGURE_EXCLUDE = "spring.autoconfigure.exclude";
    private ConfigurableListableBeanFactory beanFactory;
    private Environment environment;
    private ClassLoader beanClassLoader;
    private ResourceLoader resourceLoader;
    private AutoConfigurationImportSelector.ConfigurationClassFilter configurationClassFilter;

    public AutoConfigurationImportSelector() {
    }

    public String[] selectImports(AnnotationMetadata annotationMetadata) {
        if (!this.isEnabled(annotationMetadata)) {
            return NO_IMPORTS;
        } else {
            AutoConfigurationImportSelector.AutoConfigurationEntry autoConfigurationEntry = this.getAutoConfigurationEntry(annotationMetadata);
            return StringUtils.toStringArray(autoConfigurationEntry.getConfigurations());
        }
    }
  ...
}
```

`AutoConfigurationImportSelector` 내부의 `selectImports()`에는 자동 설정 방식에 대해 조금 더 상세히 살펴볼 수 있다.

```java
    protected AutoConfigurationImportSelector.AutoConfigurationEntry getAutoConfigurationEntry(AnnotationMetadata annotationMetadata) {
        if (!this.isEnabled(annotationMetadata)) {
            return EMPTY_ENTRY;
        } else {
            AnnotationAttributes attributes = this.getAttributes(annotationMetadata);
            List<String> configurations = this.getCandidateConfigurations(annotationMetadata, attributes);
            configurations = this.removeDuplicates(configurations);
            Set<String> exclusions = this.getExclusions(annotationMetadata, attributes);
            this.checkExcludedClasses(configurations, exclusions);
            configurations.removeAll(exclusions);
            configurations = this.getConfigurationClassFilter().filter(configurations);
            this.fireAutoConfigurationImportEvents(configurations, exclusions);
            return new AutoConfigurationImportSelector.AutoConfigurationEntry(configurations, exclusions);
        }
    }
```

`getAutoConfigurationEntry()` 메서드를 보면 `removeDuplicates()` 종복된 설정과 `getExclusions()`으로 제외할 설정을 제외시켜주고 있다. 그리고 나서 이중에 프로젝트에서 사용하는 빈만 임포트할 자동 대상으로 선택하고 있다.

- `META-INF/spring.factories` : 자동 설정 타깃 클래스 목록. 이곳에 선언되어 있는 클래스들이 `@EnableAutoConfiguration` 의 타겟
- `META-INF/spring-configuration-metadata.json`  : 자동 설정에 사용할 프로퍼티 정의 파일.
  - 미리 구현되어 있는 자동 설정에 프로퍼티만 주입 시키면 된다.(별도 환경설정 불필요)
- `org/springframework/boot/autoconfigure` : 미리 구현해놓은 자동 설정 리스트
  - `{특정설정이름}AutoConfiguration` 형식으로 이름이 지정되어 있음

위 파일은 모두 `spring-boot-autoconfiguration`에 미리 정의되어 있고, 지정된 프로퍼티 값을 사용해 설정 클래스 내부 값을 바꿀 수 있다.

[Spring Boot Reference Guide - Common Application properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#common-application-properties)에서 프로퍼티 값을 쉽게 확인할 수 있다.

### 자동 설정 어노테이션

#### 자동 설정 조건 어노테이션

| 어노테이션                        | 적용 조건                                                    |
| --------------------------------- | ------------------------------------------------------------ |
| `@ConditionalOnBean`              | 해당하는 빈 클래스나 이름이 미리 빈 팩토리에 포함되어 있는 경우 |
| `@ConditionalOnClass`             | 해당하는 클래스가 클래스 경로에 있는 경우                    |
| `@ConditionalOnCloudPlatform`     | 해당하는 클라우드 플랫폼이 활용 상태인 경우                  |
| `@ConditionalOnExpression`        | SpEL에 의존하는 조건인 경우                                  |
| `@ConditionalOnJava`              | JVM 버전이 일치하는 경우                                     |
| `@ConditionalOnJndi`              | JNDI가 사용가능하고 특정 위치에 있는 경우                    |
| `@ConditionalOnMissingBean`       | 해당하는 빈 클래스나 이름이 미리 빈 팩토리에 포함되어 있지 않은 경우 |
| `@ConditionalOnMissingClass`      | 해당하는 클래스가 클래스 경로에 없을 경우                    |
| `@ConditionalOnNotWebApplication` | 웹 어플리케이션이 아닌경우                                   |
| `@ConditionalOnProperty`          | 특정한 피로퍼티가 지정한 값을 갖는 경우                      |
| `@ConditionalOnResource`          | 특정 리소스가 클래스 경로에 있는 경우                        |
| `@ConditionalOnSingleCandidate`   | 지정한 빈 클래스가 이미 빈 팩토리에 포함되어 있고 단일 후보자로 지정 가능한 경우 |
| `@ConditionalOnWebApplication`    | 웹 어플리케이션인 경우                                       |

#### 

#### 자동 설정 순서 어노테이션

| 어노테이션             | 설명                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `@AutoConfigureAfter`  | 지정한 특정 자동 설정 클래스들이 적용된 이후에 해당 자동 설정 적용 |
| `@AutoConfigureBefore` | 지정한 특정 자동 설정 클래스들이 적용된 이전에 해당 자동 설정 적용 |
| `@AutoConfigureOrder`  | 자동 설정 순서 지정을 위한 스프링 프레임워크의 `@Order` 어노테이션 변형으로 기존 설정 클래스에는 영향을 주지 않고 자동 설정 클래스들 간의 순서만 지정한다. |

#### 예시

```java
@Configuration
@ConditionalOnWebApplication(type = ConditionalOnWebApplication.Type.SERVLET) // 웹 어플리케이션일 떄
@ConditionalOnClass(WebServlet.class) // WebServlet.class가 경로에 있을때
@ConditionalOnProperty(prefix = "spring.h2.console" , name = "enabled", havingValue = "true", matchIfMissing = false) // spring.h2.console.enabled 값이 true일때
@EnableConfigurationProperties(H2ConsoleProperties.class)
public class H2ConsoleAutoConfiguration {
  ...
}
```





