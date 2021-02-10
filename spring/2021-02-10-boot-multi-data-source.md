# Spring Boot 다중 DataSource 설정

프로젝트에 따라 Datasource를 여러개 설정해야하는 경우가 있다. 이때 여러개의 DB를 설정하는 방법에 대해 알아볼 것이다.

## application.yml

설정할 Database정보를 `application.yml` 에 추가해준다.

```yaml
databases:
  mysql:
  	first:
      jdbc-url: jdbc:mysql://127.0.0.1:3306/spring_batch?serverTimezone=UTC
      username: test
      password: test
      driver-class-name: com.mysql.cj.jdbc.Driver
 		second:
      jdbc-url: jdbc:mysql://127.0.0.1:3306/test?serverTimezone=UTC
      username: test
      password: test
      driver-class-name: com.mysql.cj.jdbc.Driver
  h2:
    jdbc-url: jdbc:h2:mem:testdb;DB_CLOSE_DELAY=-1;DB_CLOSE_ON_EXIT=FALSE
    username: sa
    password:
    driver-class-name: org.h2.Driver
```



## config 설정

### MysqlMybatisConfig

```java
@Slf4j
@Configuration
public class MysqlMybatisConfig {

    @Value("${mybatis.mapper-locations}")
    private String mapperLocations;

    @Bean(name = "mybatisDataSource")
    @ConfigurationProperties(prefix = "databases.mysql.first")
    @Primary
    public DataSource dataSource(){
        return DataSourceBuilder.create().build();
    }

    @Bean(name = "mybatisSqlSessionFactory")
    @Primary
    public SqlSessionFactory sqlSessionFactory(@Qualifier("mybatisDataSource") DataSource dataSource, ApplicationContext applicationContext) throws Exception{
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        sqlSessionFactoryBean.setDataSource(dataSource);
        sqlSessionFactoryBean.setConfigLocation(applicationContext.getResource("classpath:mybatis/mybatis-config.xml"));
        sqlSessionFactoryBean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources(mapperLocations));

        return sqlSessionFactoryBean.getObject();

    }

    @Bean
    @Primary
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("mybatisSqlSessionFactory") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }

}
```

### MysqlSecondMybatisConfig

```java
@Slf4j
@Configuration
public class MysqlSecondMybatisConfig {

    @Value("${mybatis.mapper-locations}")
    private String mapperLocations;

 		@Bean(name = "mybatisSecondDataSource")
    @ConfigurationProperties(prefix = "databases.mysql.second")
    public DataSource dataSource(){
        return DataSourceBuilder.create().build();
    }
  
  	@Bean(name = "mybatisSecondSqlSessionFactory")
    public SqlSessionFactory sqlSessionFactory(@Qualifier("mybatisSecondDataSource") DataSource dataSource, ApplicationContext applicationContext) throws Exception{
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        sqlSessionFactoryBean.setDataSource(dataSource);
        sqlSessionFactoryBean.setConfigLocation(applicationContext.getResource("classpath:mybatis/mybatis-config.xml"));
        sqlSessionFactoryBean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources(mapperLocations));

        return sqlSessionFactoryBean.getObject();
    }

  	
  	@Bean(name="mybatisSecondSqlSessionTemplate")
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("mybatisSecondSqlSessionFactory") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```



다음과 같이 설정해주면 된다. 

- `@Primary` 처음 스프링 구동 시 기본으로 사용할 Bean을 설정하는 것이다. 

```java
    @Autowired
    private SqlSessionFactory sqlSessionFactory;
```

다음과 같이 별도 Bean 설정없이 `@Autowired`로 연결한 경우, `@Primary`로 설정한 mybatisSqlSessionFactory가 연결되며,

```java
    @Autowired
		@Qualifier("mybatisSecondSqlSessionFactory")
    private SqlSessionFactory sqlSessionFactory;
```

`@Qualifier("mybatisSecondSqlSessionFactory")`로 기본값이 빈을 연결할 수 있다.

## 참고

- [Spring Batch 로 다중 Data Source 접근하기(매우 간단 주의)](https://medium.com/official-podo/spring-batch-%EB%A1%9C-%EB%8B%A4%EC%A4%91-data-source-%EC%A0%91%EA%B7%BC%ED%95%98%EA%B8%B0-%EB%A7%A4%EC%9A%B0-%EA%B0%84%EB%8B%A8-%EC%A3%BC%EC%9D%98-7332f2a5f7f8)

