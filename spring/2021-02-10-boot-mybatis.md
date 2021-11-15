# Spring Boot Mybatis 연동하기

실무를 하다보면, Mybatis로 DB를 사용하는 경우가 많다. 스프링 부트 프로젝트에서 mybatis 연동하는 법에 대해서 정리할 것이다.

## dependency 설정

### maven pom.xml

```xml
        <dependency>
            <groupId>org.mybatis.spring.boot</groupId>
            <artifactId>mybatis-spring-boot-starter</artifactId>
            <version>2.1.4</version>
        </dependency>
```

pom.xml에 mybatis관련 dependency를 추가해준다.

그리고 추가적으로 xml 파일을 target class에 생성되도록 하려면  추가로 설정해줘야한다. 빌드시 해당 resource는 포함하겠다는 의미이다.

```xml
    <build>
        <resources>
            <resource>
                <directory>src/main/java</directory>
                <includes>
                    <include>**/*.xml</include>
                </includes>
            </resource>
        </resources>
    </build>
```


## application.yml

```yaml
mybatis:
  mapper-locations: classpath*:**/mapper/*.xml
```

application.yml에 mybatis mapper 파일이 생성되는 위치를 지정한다.

## config

### mybatis-config.xml

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN" "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <settings>
        <setting name="defaultStatementTimeout" value="25"/>
    </settings>
</configuration>
```

mybatis 관련 설정을 해준다. 기본적인 설정만 했으며, [mybatis 공식문서](https://mybatis.org/mybatis-3/ko/configuration.html)에서 추가적인 설정을 확인할 수 있다.

### MysqlMybatisConfig.java

```java
package spring.batch.practice.config;

import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.session.SqlSessionFactory;
import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.SqlSessionTemplate;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.ConfigurationPropertiesScan;
import org.springframework.boot.jdbc.DataSourceBuilder;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.io.Resource;
import org.springframework.core.io.support.PathMatchingResourcePatternResolver;

import javax.sql.DataSource;

@Slf4j
@Configuration
public class MysqlMybatisConfig {

    @Value("${mybatis.mapper-locations}")
    private String mapperLocations;

    @Bean(name = "mybatisDataSource")
    @ConfigurationProperties(prefix = "spring.datasource.hikari")
    public DataSource dataSource(){
        return DataSourceBuilder.create().build();
    }

    @Bean(name = "mybatisSqlSessionFactory")
    public SqlSessionFactory sqlSessionFactory(@Qualifier("mybatisDataSource") DataSource dataSource, ApplicationContext applicationContext) throws Exception{
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        sqlSessionFactoryBean.setDataSource(dataSource);
        sqlSessionFactoryBean.setConfigLocation(applicationContext.getResource("classpath:mybatis/mybatis-config.xml"));
        sqlSessionFactoryBean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources(mapperLocations));

        return sqlSessionFactoryBean.getObject();

    }

    @Bean
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("mybatisSqlSessionFactory") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```

mapperLocation은 application.yml에서 설정한 mapper-locations값을 `@Value`를 통해 지정한다. 이전에 dataSource에는 해당 Database 관련 정보를 설정한 값을 prefix로 지정해준다.

```yaml
spring:
  config:
    activate:
      on-profile: mysql
  datasource:
    hikari:
      jdbc-url: jdbc:mysql://127.0.0.1:3306/spring_batch?serverTimezone=UTC
      username: test
      password: test
      driver-class-name: com.mysql.cj.jdbc.Driver
```

`SqlSessionFactory`를 `SqlSessionFactoryBean`에 mybatis-config.xml 위치와 mapper파일들을 설정해주면 된다.



## 참고

- [一以貫之 [intellij] 빌드 시 xml 파일 복사가 안될 때](https://graykim.tistory.com/232)
- [mybatis.org](https://mybatis.org/mybatis-3/ko/configuration.html)

