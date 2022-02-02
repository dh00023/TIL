# ItemWriter

Reader와 Processor를 거쳐 처리된 Item을 Chunk 단위만큼 쌓은 후 이를 Writer에 전달하고, `ItemWriter`는 배치의 출력을 담당한다.

```java
public interface ItemWriter<T> {
    void write(List<? extends T> var1) throws Exception;
}
```

`ItemWriter`의 `write()`는 인자로 Item List를 받는 것을 볼 수 있다. Spring Batch에서는 다양한 Output 타입을 처리할 수 있도록 Writer를 제공하고 있다.

- [공식문서](https://docs.spring.io/spring-batch/docs/4.0.x/reference/html/readersAndWriters.html#itemWriter)

## Database Writer

- JdbcBatchItemWriter

- HibernateItemWriter
- JpaItemWriter

다음 3가지 Writer가 있으며, Database의 영속성과 관련해서는 항상 Flush를 해줘야한다.  Writer가 받은 모든 Item이 처리 된 후에 Spring Batch는 현재 트랜잭션을 커밋한다.

### JdbcBatchItemWriter

ORM을 사용하지 않는 경우에는 대부분 `JdbcBatchItemWriter`를 사용한다. 

![jdbcwrite-flow](https://t1.daumcdn.net/cfile/tistory/99CE9E385BAC174309)

`JdbcBatchItemWriter`는 `JdbcTemplate`을 사용하며, JDBC의 **Batch 기능을 사용해 한번에 DB로 전달하여 DB내부에서 쿼리가 실행**되도록 한다. 어플리케이션과 데이터베이스 간에 데이터를 주고 받는 회수를 최소화하여 성능향상을 할 수 있도록 하기 위해서다.

```java
    public void write(final List<? extends T> items) throws Exception {
        if (!items.isEmpty()) {
            if (logger.isDebugEnabled()) {
                logger.debug("Executing batch with " + items.size() + " items.");
            }

            int[] updateCounts;
            int value;
            if (!this.usingNamedParameters) {
                updateCounts = (int[])this.namedParameterJdbcTemplate.getJdbcOperations().execute(this.sql, new PreparedStatementCallback<int[]>() {
                    public int[] doInPreparedStatement(PreparedStatement ps) throws SQLException, DataAccessException {
                        Iterator var2 = items.iterator();

                        while(var2.hasNext()) {
                            T item = var2.next();
                            JdbcBatchItemWriter.this.itemPreparedStatementSetter.setValues(item, ps);
                            ps.addBatch();
                        }

                        return ps.executeBatch();
                    }
                });
            } else if (items.get(0) instanceof Map && this.itemSqlParameterSourceProvider == null) {
                updateCounts = this.namedParameterJdbcTemplate.batchUpdate(this.sql, (Map[])items.toArray(new Map[items.size()]));
            } else {
                SqlParameterSource[] batchArgs = new SqlParameterSource[items.size()];
                value = 0;

                Object item;
                for(Iterator var5 = items.iterator(); var5.hasNext(); batchArgs[value++] = this.itemSqlParameterSourceProvider.createSqlParameterSource(item)) {
                    item = var5.next();
                }

                updateCounts = this.namedParameterJdbcTemplate.batchUpdate(this.sql, batchArgs);
            }

            if (this.assertUpdates) {
                for(int i = 0; i < updateCounts.length; ++i) {
                    value = updateCounts[i];
                    if (value == 0) {
                        throw new EmptyResultDataAccessException("Item " + i + " of " + updateCounts.length + " did not update any rows: [" + items.get(i) + "]", 1);
                    }
                }
            }
        }

    }
```

이때 `write()`메서드를 보면 **SQL문을 한번씩 호출하는 것이 아닌 `batchUpdate`로 데이터를 청크 단위로 일괄처리**하는 것을 볼 수 있다. 이렇게 하면 실행 성능을 크게 향상 시킬 수 있으며, 데이터  변경 실행을 트랜잭션 내에서 할 수 있다.

| Property                       | Parameter Type                 | Default        | 설명                                                         |
| ------------------------------ | ------------------------------ | -------------- | ------------------------------------------------------------ |
| assertUpdates                  | boolean                        | true           | true이면 모든 아이템이 삽입이나 수정되었는지 검증한다.<br />즉, 적어도 하나의 항목이 행을 업데이트 하거나 삭제하지 않을 경우 예외(`EmptyResultDataAccessException`)를 throw할지 설정한다. |
| **dataSource**                 | **DataSource**                 | **null(필수)** | **필요한 데이터베이스에 대한 접근 제공**                     |
| **sql**                        | **String**                     | **null(필수)** | 각 아이템당 수행할 SQL                                       |
| itemPreparedStatementSetter    | ItemPreparedStatementSetter    | null           | 표준 PreparedState가 제공된다면(파라미터 위치에 ?사용), 이 클래스를 사용해 파라미터 값을 채움 |
| itemSqlParameterSourceProvider | ItemSqlParameterSourceProvider | null           | 제공된 SQL에 네임드 파라미터가 사용된다면, 이 클래스를 사용해 파라미터 값 채움 |
| simpleJdbcTemplate             | SimpleJdbcTemplate             | null           | SimpleJdbcOperations 인터페이스의 구현체를 주입 가능         |
| afterPropertiesSet             |                                |                | 각각 Writer들이 실행되기 위해 필요한 필수 값들이 제대로 세팅되어 있는지 확인 |

#### JdbcBatchItemWriterBuilder

JdbcBatchItemWriterBuilder는 다음 3가지 설정 값을 갖고 있다.

| Property      | Parameter Type | Default | 설명                                                         |
| ------------- | -------------- | ------- | ------------------------------------------------------------ |
| assertUpdates | boolean        | true    | true이면 모든 아이템이 삽입이나 수정되었는지 검증한다.<br />즉, 적어도 하나의 항목이 행을 업데이트 하거나 삭제하지 않을 경우 예외(`EmptyResultDataAccessException`)를 throw할지 설정한다. |
| columnMapped  |                |         | Key, Value 기반으로 Insert SQL의 Values를 매핑한다.          |
| beanMapped    |                |         | POJO 기반으로 Insert SQL의 Values를 매핑한다.                |

- columnMapped

  ```java
      @Bean // beanMapped시 필수
      public JdbcBatchItemWriter<Pay> jdbcBatchItemWriter(){
          return new JdbcBatchItemWriterBuilder<Map<String, Object>>() // Map 사용
                  .columnMapped()
                  .dataSource(this.dataSource)
                  .sql("insert into pay2(amount, tx_name, tx_date_time) values (:amount, :txName, :txDateTime)")
                  .build();
      }
  ```

- beanMapped

  ```java
      @Bean // beanMapped시 필수
      public JdbcBatchItemWriter<Pay> jdbcBatchItemWriter(){
          return new JdbcBatchItemWriterBuilder<Pay>()
                  .dataSource(dataSource)
                  .sql("insert into pay(amount, tx_name, tx_datetime) values (:amount, :txname, :txDateTime)")
                  .beanMapped()
                  .build();
      }
  ```

#### afterPropertiesSet

이 외에  `afterPropertiesSet()`메서드를 추가로 알고 있으면 좋다. 이 메서드는 `InitalizingBean` 인터페이스에서 갖고 있으며, ItemWriter 구현체들은 모두 `InitializingBean` 인터페이스를 구현하고 있다.

```java
    public void afterPropertiesSet() {
        Assert.notNull(this.namedParameterJdbcTemplate, "A DataSource or a NamedParameterJdbcTemplate is required.");
        Assert.notNull(this.sql, "An SQL statement is required.");
        List<String> namedParameters = new ArrayList();
        this.parameterCount = JdbcParameterUtils.countParameterPlaceholders(this.sql, namedParameters);
        if (namedParameters.size() > 0) {
            if (this.parameterCount != namedParameters.size()) {
                throw new InvalidDataAccessApiUsageException("You can't use both named parameters and classic \"?\" placeholders: " + this.sql);
            }

            this.usingNamedParameters = true;
        }

        if (!this.usingNamedParameters) {
            Assert.notNull(this.itemPreparedStatementSetter, "Using SQL statement with '?' placeholders requires an ItemPreparedStatementSetter");
        }

    }
```

이 메서드는 각각 Writer들이 실행되기 위해 필요한 필수 값들이 제대로 세팅되어 있는지 확인한다. Writer 생성 후 해당 메서드를 실행하면 어느 값이 누락되었는지 알 수 있어서 많이 사용하는 옵션이다.

```java
    @Bean
    public JdbcBatchItemWriter<Pay> jdbcBatchItemWriter(){
        JdbcBatchItemWriter<Pay> jdbcBatchItemWriter = new JdbcBatchItemWriterBuilder<Pay>()
                                                          .dataSource(dataSource)
                                                          .sql("insert into pay(amount, tx_name, tx_date_time) values (:amount+1000, :txName, :txDateTime)")
                                                          .beanMapped()
                                                          .build();
        jdbcBatchItemWriter.afterPropertiesSet();
        return jdbcBatchItemWriter;
    }
```

### HibernateItemWriter

- `org.springframework.batch.item.database.HibernateItemWriter`

```java
public class HibernateItemWriter<T> implements ItemWriter<T>, InitializingBean {
	@Override
	public void write(List<? extends T> items) {
		doWrite(sessionFactory, items);
		sessionFactory.getCurrentSession().flush();
		if(clearSession) {
			sessionFactory.getCurrentSession().clear();
		}
	}

	/**
	 * Do perform the actual write operation using Hibernate's API.
	 * This can be overridden in a subclass if necessary.
	 *
	 * @param sessionFactory Hibernate SessionFactory to be used
	 * @param items the list of items to use for the write
	 */
	protected void doWrite(SessionFactory sessionFactory, List<? extends T> items) {
		if (logger.isDebugEnabled()) {
			logger.debug("Writing to Hibernate with " + items.size()
					+ " items.");
		}

		Session currentSession = sessionFactory.getCurrentSession();

		if (!items.isEmpty()) {
			long saveOrUpdateCount = 0;
			for (T item : items) {
				if (!currentSession.contains(item)) {
					currentSession.saveOrUpdate(item);
					saveOrUpdateCount++;
				}
			}
			if (logger.isDebugEnabled()) {
				logger.debug(saveOrUpdateCount + " entities saved/updated.");
				logger.debug((items.size() - saveOrUpdateCount)
						+ " entities found in session.");
			}
		}
	}
```

`HibernateItemWriter`에서 각 아이템에 대해 `session.saveOrUpdate` 메서드를 호출하며, 모든 아이템이 저장되거나 수정되면 `flush` 메서드를 통해 모든 변경 사항을 한번에 실행한다.

#### 의존성 추가

```groovy
compileOnly 'org.springframework.boot:spring-boot-starter-data-jpa'
```

#### 프로퍼티 설정

```yaml
spring:
  jpa:
    properties:
      hibernate:
        current_session_context_class: org.springframework.orm.hibernate5.SpringSessionContext
```

#### JPA 어노테이션 추가

```java
@Entity // 매핑할 객체가 Entity임을 나타냄
@Table(name = "customer") // Entityrㅏ 매핑되는 테이블 지정
public class Customer {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id; // pk
    private String firstName;
    private String middleInitial;
    private String lastName;
    private String address;
    private String city;
    private String state;
    private String zipCode;
}
```

#### Configurer 생성

```java
@Component
public class HibernateBatchConfigurer extends DefaultBatchConfigurer {

    private DataSource dataSource;
    private SessionFactory sessionFactory;
    private PlatformTransactionManager transactionManager;

    /**
     * Datasource connection과 하이버네이트 세션 설정
     * @param dataSource
     * @param entityManagerFactory
     */
    public HibernateBatchConfigurer(DataSource dataSource,
                                    EntityManagerFactory entityManagerFactory) {
        super(dataSource);
        this.dataSource = dataSource;
        this.sessionFactory = entityManagerFactory.unwrap(SessionFactory.class);

        // 하이버네이트 트랜잭션 설정
        this.transactionManager = new HibernateTransactionManager(this.sessionFactory);
    }

    @Override
    public PlatformTransactionManager getTransactionManager() {
        return this.transactionManager;
    }
}
```

`HibernateTransactionManager`를 트랜잭션 으로 설정해준다.

```java
    @Bean
    public HibernateItemWriter<Customer> hibernateItemWriter() {

        return new HibernateItemWriterBuilder<Customer>()
                .sessionFactory(entityManagerFactory.unwrap(SessionFactory.class))
                .build();
    }
```

### JpaItemWriter

ORM을 사용할 때, Writer에 전달하는 데이터가 Entity 클래스인 경우 `JpaItemWriter`를 사용하면 된다. `JpaItemWriter`는 JPA를 사용하기 때문에 영속성 관리를 위해 `EntityManager`를 할당해줘야한다. 

일반적으로 `spring-boot-starter-data-jpa`를 의존성에 등록하면 `EntityManager`가 Bean으로 자동 생성되어 DI코드만 추가하면 된다.

```groovy
compileOnly 'org.springframework.boot:spring-boot-starter-data-jpa'
```

#### afterPropertiesSet

```java
    public void afterPropertiesSet() throws Exception {
        Assert.notNull(this.entityManagerFactory, "An EntityManagerFactory is required");
    }
```

`JpaItemWriter`의 `afterPropertiesSet()`에서는 `EntityManagerFactory` 만 필수 값으로 확인하고 있어 체크할 요소가 적다. 즉, `setEntityManger`만 해주면 모든 설정이 끝난다.

```java
		@Bean
    public JpaItemWriter<Pay> jpaCursorItemWriter() {

        JpaItemWriter<Pay> jpaItemWriter = new JpaItemWriter<>();
        jpaItemWriter.setEntityManagerFactory(entityManagerFactory);
        return jpaItemWriter;
    }
```

####  write()

```java
    public void write(List<? extends T> items) {
        EntityManager entityManager = EntityManagerFactoryUtils.getTransactionalEntityManager(this.entityManagerFactory);
        if (entityManager == null) {
            throw new DataAccessResourceFailureException("Unable to obtain a transactional EntityManager");
        } else {
            this.doWrite(entityManager, items);
            entityManager.flush();
        }
    }

    protected void doWrite(EntityManager entityManager, List<? extends T> items) {
        if (logger.isDebugEnabled()) {
            logger.debug("Writing to JPA with " + items.size() + " items.");
        }

        if (!items.isEmpty()) {
            long addedToContextCount = 0L;
            Iterator var5 = items.iterator();

            while(var5.hasNext()) {
                T item = var5.next();
                if (!entityManager.contains(item)) {
                    if (this.usePersist) {
                        entityManager.persist(item);
                    } else {
                        entityManager.merge(item);
                    }

                    ++addedToContextCount;
                }
            }

            if (logger.isDebugEnabled()) {
                logger.debug(addedToContextCount + " entities " + (this.usePersist ? " persisted." : "merged."));
                logger.debug((long)items.size() - addedToContextCount + " entities found in persistence context.");
            }
        }

    }
```

`JpaItemWriter`의 `doWrite()`를 보면 넘어온 item 그대로  `entityManager.merge(item)`를 수행하여 테이블에 바로 반영하기 때문에, `JpaItemWriter`는 **Entity 클래스를 제네릭 타입으로 받아야만 한다**.

### MyBatisBatchItemWriter

- [https://mybatis.org/spring/ko/batch.html](https://mybatis.org/spring/ko/batch.html)

Step에서 정의한 Chunk Size(FetchSize)만큼 처리해주려면 executorType을 **BATCH**로 설정해줘야한다.

```java
mybatis:
	config-location: classpath:mybatis/mybatis-config.xml
	mapper-locations: classpath*:mybatis/**/*.sql
	executorType: BATCH
```

그 다음 수행할 쿼리를 mapper에 작성해주고 수행하면 된다.

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="spring.batch.practice.dao.customerMapper">

    <select id="insertCustomer" parameterType="spring.batch.practice.domain.Customer">
		INSERT INTO CUSTOMER(FIRST_NAME, MIDDLE_INITIAL, LAST_NAME, ADDRESS, CITY, STATE, ZIP_CODE)
    VALUES (#{firstName}, #{middleInitial}, #{lastName}, #{address}, #{city}, #{state}, #{zipCode})
		</select>
</mapper>
```

```java
@Bean
public MyBatisBatchItemWriter<Customer> testWriter(SqlSessionFactory sqlSessionFactory) {
    return new MyBatisBatchItemWriterBuilder<Customer>()
    .sqlSessionFactory(sqlSessionFactory)
    .statementId("spring.batch.practice.dao.customerMapper.insertCustomer")
    .build();
}
```

### RepositoryItemWriter

쓰기 작업 수행시에는 페이징이나 정렬이 필요없으므로, `CrudRepository`를 사용한다.

```java
public interface CustomerRepository extends CrudRepository<Customer, Long> {
}
```

```java
    @Bean
    public RepositoryItemWriter<Customer> repositoryItemWriter() {

        return new RepositoryItemWriterBuilder<Customer>()
                .repository(customerRepository)
                .methodName("save")
                .build();
    }
```

위에서 구현한 repository를 설정해주고, 호출할 메서드명만 지정해주면된다.

## Custom ItemWriter

Reader와는 다르게 Writer의 경우 custom하게 구현해야하는 경우가 많다.

- Reader에서 읽어온 데이터를 RestTemplate으로 외부 API를 전달해야하는 경우
- 임시 저장을 하고 비교하기 위해 singleton 객체에 값을 넣어야하는 경우
- 여러 Entity를 동시에 저장해야하는 경우

다음과 같이 여러 상황이 있을 수 있다. 이러한 경우 `ItemWriter` 인터페이스를 직접 구현하면 된다.

- java7 이하

  ```java
    @Bean
      public ItemWriter<Pay> customItemWriter() {
          return new ItemWriter<Pay>() {
              @Override
              public void write(List<? extends Pay> items) throws Exception {
                  for (Pay item : items) {
                      System.out.println(item);
                  }
              }
          };
      }
  ```
  
- java8 이상(ItemWriter의 추상메서드가 `write()` 한개 이므로 람다식 사용 가능)

  ```java
   @Bean
     public ItemWriter<Pay> customItemWriter() {
         return items -> {
             for (Pay item : items) {
                 System.out.println(item);
             }
         };
     }
  ```



다음과 같이 `write()`함수를 `@Override`하면 구현체 생성은 끝난다. 



## 참고

- [기억보단 기록을 - 8. Spring Batch 가이드 - ItemWriter](https://jojoldu.tistory.com/347?category=902551)