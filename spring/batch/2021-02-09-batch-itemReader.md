# ItemReader

![chunk](https://t1.daumcdn.net/cfile/tistory/992DD04D5CEB519E20)

Spring Batch의 Reader에서 읽어올 수 있는 데이터 유형은 다음과 같다.

- 입력 데이터에서 읽어오기
- 파일에서 읽어오기
- DB에서 읽어오기
- Java Message Service 등 다른 소스에서 읽어오기
- 커스텀한 Reader로 읽어오기

가장 대표적인 구현체인 `JdbcPagingItemReader`의 클래스 계층 구조를 보면 다음과 같다.

![image-20210209153930033](./assets/image-20210209153930033.png)

여기서 `ItemReader`와 `ItemStream` 인터페이스도 같이 구현하고 있는 것을 볼 수 있다. 

```java
public interface ItemStream {
    void open(ExecutionContext var1) throws ItemStreamException;

    // Batch의 처리 상태 업데이트
    void update(ExecutionContext var1) throws ItemStreamException;

    void close() throws ItemStreamException;
}
```

`ItemStream`은 주기적으로 상태를 저장하고, 오류가 발생하면 해당 상태에서 복원하기 위한 마커인터페이스이다. 즉, **`ItemRader` 의 상태를 저장하고 실패한 곳에서 다시 실행할 수 있게 해주는 역할**을 한다. `ItemReader`와 `ItemStream` 인터페이스를 직접 구현하여 원하는 형태의 ItemReader를 만들 수 있다.

- [공식문서](https://docs.spring.io/spring-batch/docs/4.0.x/reference/html/readersAndWriters.html#readersAndWriters)

## Database Reader

![cursorvspaging](https://t1.daumcdn.net/cfile/tistory/99A202395CEB519E1D)

- Cursor 방식은 DB와 커넥션을 맺은 후, Cursor를 한칸씩 옮기면서 지속적으로 데이터를 가져온다.
  - JdbcCursorItemReader
  - HibernateCursorItemReader
  - StoredProcedureItemReader
- Paging 방식은 한번에 지정한 PageSize만큼 데이터를 가져온다.
  - JdbcPagingItemReader
  - HibernatePagingItemReader
  - JpaPagingItemReader
  - [MybatisItemReader](http://mybatis.org/spring/ko/batch.html)

### CursorItemReader

CursorItemReader는 streaming으로 데이터를 처리한다. 대표적인 CursorItemReader중 하나인 `JdbcCursorItemReader`와 Spring Batch v4.3.0  이후에 도입된 `JpaCursorItemReader`를 살펴볼 것이다.

#### JdbcCursorItemReader

```java

@Slf4j
@RequiredArgsConstructor
@Configuration
public class JdbcCursorItemReaderJobConfiguration {
    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final DataSource dataSource;


    private static final int CHUNK_SIZE = 10;

    @Bean
    public Job jdbcCursorItemReaderJob(){
        return jobBuilderFactory.get("jdbcCursorItemReaderJob")
                .start(jdbcCursorItemReaderStep())
                .build();
    }
    @Bean
    public Step jdbcCursorItemReaderStep(){
        return stepBuilderFactory.get("jdbcCursorItemReaderStep")
                .<Pay, Pay>chunk(CHUNK_SIZE)
                .reader(jdbcCursorItemReader())
                .writer(jdbcCursorItemWriter())
                .build();
    }
    @Bean
    public JdbcCursorItemReader<Pay> jdbcCursorItemReader(){
        return new JdbcCursorItemReaderBuilder<Pay>()
                .fetchSize(CHUNK_SIZE)
                .dataSource(dataSource)
                .rowMapper(new BeanPropertyRowMapper<>(Pay.class))
                .sql("SELECT id, amount, tx_name, tx_date_time FROM pay")
                .name("jdbcCursorItemReader")
                .build();
    }
    @Bean
    public ItemWriter<Pay> jdbcCursorItemWriter(){
        return list -> {
            for(Pay pay : list){
                log.info("Current Pay={}", pay);
            }
        };
    }
}
```

- `<T, T> chunk(int chunkSize)` : 첫번째 T는 Reader에서 반환할 타입, 두번째 T는 Writer에 파라미터로 넘어올 타입이다.
- fetchSize : DB에서 한번에 가져올 데이터 양을 나타낸다. Paging은 실제 쿼리를 limit, offset으로 분할 처리하는 반면, Cursor는 분할 처리없이 실행되나 내부적으로 가져온는 데이터는 FetchSize만큼 가져와 `read()`를 통해서 하나씩 가져온다.
- dataSource : DB에 접근하기 위해 사용할 DataSource객체
- rowMapper : 쿼리 결과를 인스턴스로 매핑하기 위한 매퍼
- sql : Reader에서 사용할 쿼리문
- name : Reader의 이름, ExecutionContext에 저장되어질 이름

```java
@Slf4j
@Configuration
@RequiredArgsConstructor
public class JpaCursorItemReaderJobConfiguration {

    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;

    private static final int CHUNK_SIZE = 10;


    @Bean
    public Job jpaCursorItemReaderJob() throws Exception {
        return jobBuilderFactory.get("jpaCursorItemReaderJob")
                .start(jpaCursorItemReaderStep())
                .build();
    }

    @Bean
    public Step jpaCursorItemReaderStep() throws Exception {
        return stepBuilderFactory.get("jpaCursorItemReaderStep")
                .<Pay, Pay>chunk(CHUNK_SIZE)
                .reader(jpaCursorItemReader())
                .writer(jpaCursorItemWriter())
                .build();
    }

    @Bean
    public JpaCursorItemReader<Pay> jpaCursorItemReader() throws Exception{
        return new JpaCursorItemReaderBuilder<Pay>()
                .name("jpaCursorItemReader")
                .entityManagerFactory(entityManagerFactory)
                .queryString("SELECT p FROM Pay p")
                .build();
    }

    private ItemWriter<Pay> jpaCursorItemWriter() {
        return list -> {
            for (Pay pay: list) {
                log.info("Current Pay={}", pay);
            }
        };
    }

}
```



Cursor는 하나의 Connection으로 Batch가 끝날때가지 사용되기 때문에 Batch가 끝나기전에 DB와 어플리케이션 Connection이 끊어질 수 있으므로, DB와  SocketTimeout을 충분히 큰 값으로 설정해야한다.

**Batch 수행시간이 오래 걸리는 경우에는 `PagingItemReader`를 사용**하는 것이 좋다. **Paging의 경우 한 페이지를 읽을때마다 Connection을 맺고 끊기 때문에 아무리 많은 데이터라도 타임아웃과 부하 없이 수행**될 수 있다.



### PagingItemReader

SpringBatch에서 offset과 limit을 PageSize에 맞게 자동으로 생성해준다. 다만 각 쿼리는 개별적으로 실행되므로, 페이징시 결과를 정렬(order by)하는 것이 중요하다.

#### JdbcPagingItemReader

```java
package spring.batch.practice.jobs;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.batch.core.Job;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.configuration.annotation.JobBuilderFactory;
import org.springframework.batch.core.configuration.annotation.StepBuilderFactory;
import org.springframework.batch.item.ItemWriter;
import org.springframework.batch.item.database.JdbcPagingItemReader;
import org.springframework.batch.item.database.Order;
import org.springframework.batch.item.database.PagingQueryProvider;
import org.springframework.batch.item.database.builder.JdbcPagingItemReaderBuilder;
import org.springframework.batch.item.database.support.SqlPagingQueryProviderFactoryBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import spring.batch.practice.domain.Pay;

import javax.sql.DataSource;
import java.util.HashMap;
import java.util.Map;

@Slf4j
@RequiredArgsConstructor
@Configuration
public class JdbcPagingItemReaderJobConfiguration {
    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final DataSource dataSource;


    private static final int CHUNK_SIZE = 10;

    @Bean
    public Job jdbcPagingItemReaderJob() throws Exception {
        return jobBuilderFactory.get("jdbcPagingItemReaderJob")
                .start(jdbcPagingItemReaderStep())
                .build();
    }
    @Bean
    public Step jdbcPagingItemReaderStep() throws Exception {
        return stepBuilderFactory.get("jdbcPagingItemReaderStep")
                .<Pay, Pay>chunk(CHUNK_SIZE)
                .reader(jdbcPagingItemReader())
                .writer(jdbcPagingItemWriter())
                .build();
    }
    @Bean
    public JdbcPagingItemReader<Pay> jdbcPagingItemReader() throws Exception {
        Map<String, Object> params = new HashMap<>();
        params.put("amount", 2000);

        return new JdbcPagingItemReaderBuilder<Pay>()
                .fetchSize(CHUNK_SIZE)
                .dataSource(dataSource)
                .rowMapper(new BeanPropertyRowMapper<>(Pay.class))
                .queryProvider(createQueryProvider())
                .parameterValues(params)
                .name("jdbcPagingItemReader")
                .build();
    }
    @Bean
    public ItemWriter<Pay> jdbcPagingItemWriter(){
        return list -> {
            for(Pay pay : list){
                log.info("Current Pay={}", pay);
            }
        };
    }

    @Bean
    public PagingQueryProvider createQueryProvider() throws Exception {
        SqlPagingQueryProviderFactoryBean queryProvider = new SqlPagingQueryProviderFactoryBean();
        queryProvider.setDataSource(dataSource);
        queryProvider.setSelectClause("id, amount, tx_name, tx_date_time");
        queryProvider.setFromClause("from pay");
        queryProvider.setWhereClause("where amount >= :amount");

        Map<String, Order> sortKeys = new HashMap<>();
        sortKeys.put("id", Order.ASCENDING);

        queryProvider.setSortKeys(sortKeys);

        return queryProvider.getObject();
    }
}

```

`PagingItemReader`는 `PagingQueryProvider`를 통해 쿼리를 생성한다. 이렇게 생성하는 이유는 각 DB에는 Paging을 지원하는 자체적인 전략이 있으며, Spring은 각 DB의 Paging 전략에 맞춰 구현되어야만 한다.

```java
public SqlPagingQueryProviderFactoryBean() {
        this.providers.put(DatabaseType.DB2, new Db2PagingQueryProvider());
        this.providers.put(DatabaseType.DB2VSE, new Db2PagingQueryProvider());
        this.providers.put(DatabaseType.DB2ZOS, new Db2PagingQueryProvider());
        this.providers.put(DatabaseType.DB2AS400, new Db2PagingQueryProvider());
        this.providers.put(DatabaseType.DERBY, new DerbyPagingQueryProvider());
        this.providers.put(DatabaseType.HSQL, new HsqlPagingQueryProvider());
        this.providers.put(DatabaseType.H2, new H2PagingQueryProvider());
        this.providers.put(DatabaseType.MYSQL, new MySqlPagingQueryProvider());
        this.providers.put(DatabaseType.ORACLE, new OraclePagingQueryProvider());
        this.providers.put(DatabaseType.POSTGRES, new PostgresPagingQueryProvider());
        this.providers.put(DatabaseType.SQLITE, new SqlitePagingQueryProvider());
        this.providers.put(DatabaseType.SQLSERVER, new SqlServerPagingQueryProvider());
        this.providers.put(DatabaseType.SYBASE, new SybasePagingQueryProvider());
    }
```

Spring Batch에서는 `SqlPagingQueryProviderFactoryBean`을 통해 DataSource 설정 값을 보고, 위 Provider중 하나를 자동 선택하도록 한다.

```sql
SELECT id, amount, tx_name, tx_date_time FROM pay WHERE amount >= :amount ORDER BY id ASC LIMIT 10
```

실행된 쿼리 로그를 보면 LIMIT 10이 들어간 것을 볼 수 있다.

#### JpaPagingItemReader

Jpa에서는 Cursor 기반 DB 접근을 지원하지 않는다.

```java

@Slf4j
@RequiredArgsConstructor
@Configuration
public class JpaPagingItemReaderJobConfiguration {
    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;
    private final EntityManagerFactory entityManagerFactory;


    private static final int CHUNK_SIZE = 10;

    @Bean
    public Job jpaPagingItemReaderJob() {
        return jobBuilderFactory.get("jpaPagingItemReaderJob")
                .start(jpaPagingItemReaderStep())
                .build();
    }
    @Bean
    public Step jpaPagingItemReaderStep() {
        return stepBuilderFactory.get("jpaPagingItemReaderStep")
                .<Pay, Pay>chunk(CHUNK_SIZE)
                .reader(jpaPagingItemReader())
                .writer(jpaPagingItemWriter())
                .build();
    }
    @Bean
    public JpaPagingItemReader<Pay> jpaPagingItemReader(){
        return new JpaPagingItemReaderBuilder<Pay>()
                .name("jpaPagingItemReader")
                .entityManagerFactory(entityManagerFactory)
                .pageSize(CHUNK_SIZE)
                .queryString("SELECT p FROM Pay p WHERE amount >= 2000")
                .build();
    }
    @Bean
    public ItemWriter<Pay> jpaPagingItemWriter(){
        return list -> {
            for(Pay pay : list){
                log.info("Current Pay={}", pay);
            }
        };
    }
}

```

`.entityManagerFactory`를 설정하는 것 이외에 Jdbc와 크게 다른 점은 없다.

### MyBatisPagingItemReader

```xml
<!--mybatis-config.xml-->
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <settings>
        <setting name="defaultStatementTimeout" value="25"/>
    </settings>
</configuration>
```

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
        Resource[] resources = new PathMatchingResourcePatternResolver().getResources(mapperLocations);
        System.out.println(resources[0].getURL());
        sqlSessionFactoryBean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources(mapperLocations));

        return sqlSessionFactoryBean.getObject();

    }

    @Bean
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("mybatisSqlSessionFactory") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="spring.batch.practice.dao.PayMapper">

    <select id="selectPayList" parameterType="hashmap" resultType="spring.batch.practice.domain.Pay">
	<![CDATA[
        SELECT ID, AMOUNT, TX_NAME, TX_DATE_TIME
        FROM PAY
        WHERE AMOUNT <= #{amount}
        ]]>
	</select>

</mapper>
```

```java

@Slf4j
@RequiredArgsConstructor
@Configuration
public class MybatisPagingItemReaderJobConfiguration {
    private final JobBuilderFactory jobBuilderFactory;
    private final StepBuilderFactory stepBuilderFactory;

    @Autowired
    @Qualifier("mybatisSqlSessionFactory")
    private SqlSessionFactory sqlSessionFactory;


    private static final int CHUNK_SIZE = 10;

    @Bean
    public Job mybatisPagingItemReaderJob() throws Exception {
        return jobBuilderFactory.get("mybatisPagingItemReaderJob")
                .start(mybatisPagingItemReaderStep())
                .build();
    }
    @Bean
    public Step mybatisPagingItemReaderStep() throws Exception {
        return stepBuilderFactory.get("mybatisPagingItemReaderStep")
                .<Pay, Pay>chunk(CHUNK_SIZE)
                .reader(mybatisPagingItemReader())
                .writer(mybatisPagingItemWriter())
                .build();
    }
    @Bean
    public MyBatisPagingItemReader<Pay> mybatisPagingItemReader() throws Exception {
        Map<String, Object> params = new HashMap<>();
        params.put("amount", 2000);

        return new MyBatisPagingItemReaderBuilder<Pay>()
                .pageSize(CHUNK_SIZE)
                .sqlSessionFactory(sqlSessionFactory)
                .queryId("spring.batch.practice.dao.PayMapper.selectPayList")
                .parameterValues(params)
                .build();
    }
    @Bean
    public ItemWriter<Pay> mybatisPagingItemWriter() {
        return list -> {
            for (Pay pay : list) {
                log.info("Current Pay={}", pay);
            }
        };
    }
}
```



## 주의 사항

- `JpaRepository`를 `ListItemReader`, `QueueItemReader`에 사용하면 안된다.
  - 이렇게 구현하는 경우 Spring Batch의 장점인 Paging & Cursor 구현이 없어 대규모 데이터 처리가 불가능하다.
  - `JpaRepository`를 사용해야하는 경우 `RepositoryItemReader`를 사용하는 것을 권장한다.
- Hibernate, JPA등 영속성 컨텍스트가 필요한 Reader 사용시 fetch size와 chunk size는 동일한 값을 유지해야 한다.