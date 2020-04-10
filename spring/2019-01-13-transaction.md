# Spring Trasaction

흔히 java에서 트랜잭션 사용시 `try catch` 문 사이에 commit과 Rollback을 이용하여 처리한다.

```java
Connection conn = null;
try {
    conn = DriverManager.getConnection(jdbcUrl, user, pw);
    conn.setAutoCommit(false);
    /*
        ...쿼리 실행..
     */
    conn.commit();
} catch (SQLException e) {
    if(conn!=null) {
        try {
            conn.rollback();
        } catch (SQLException e1) {
 
        }
    }
} finally {
    if(conn!=null) {
        try {
            conn.close();
        } catch (SQLException e) {
 
        }
    }
}
```

reSpring에서는 이러한 반복적인 작업을 두 가지 방법으로 한번에 해결할 수 있다.

1. 선언에 의한 트랜잭션
2. 프로그램에 의한 트랜잭션

### 선언에 의한 트랜잭션

선언에 의한 트랜잭션에는 두가지(1. AOP 2. annotation) 방법이 있다.

#### @Transactional Annotation

우선 annotation 사용을 위한 bean 설정을 해준다.

```xml
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:tx="http://www.springframework.org/schema/tx"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
            http://www.springframework.org/schema/beans/spring-beans.xsd
            http://www.springframework.org/schema/tx
            http://www.springframework.org/schema/tx/spring-tx.xsd">
     
    <bean id="dataSource" class="com.mchange.v2.c3p0.ComboPooledDataSource"
          destroy-method="close">
        <property name="driverClass" value="com.mysql.jdbc.Driver"/>
        <property name="jdbcUrl" value=""/>
        <property name="user" value="user"/>
        <property name="password" value="pwd"/>
    </bean>
 
    <bean id="transactionManager"
          class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
        <property name="dataSource" ref="dataSource"/>
        <tx:annotation-driven transaction-manager="transactionManager"/>
    </bean>
</beans>
```

다음과 같이 설정 후 원하는 메소드 위에 `@Transactional` 을 붙여 간편하게 트랜잭션을 구현할 수 있다.

메소드 전체를 하나의 트랜잭션으로 묶을 수 있다는 것은` @Transactional`의 내부 동작이 **Proxy**로 이루어진다는 것을 의미한다.

```java
@Transactional
public void something (int a) {
    ...
}
```

`@Transactional` 이 적용된 경우 트랜잭션 기능이 적용된 프록시 객체가 생성된다.

 이 프록시 객체는 `@Transactional`이 포함된 메소드가 호출되면, **PlatformTransactionManager**를 사용하여 트랜잭션을 시작하고, 결과의 정상 여부에 따라 Commit 또는 Rollback 한다.

`@Transactional` 어노테이션에 여러가지  속성을 지정할 수 있다.

```java
@Transactional(isolation = Isolation.READ_COMMITTED, propagation = Propagation.REQUIRED, rollbackFor = Exception.class)
public int method(int i) throws Exception {
	return sqlMapClient.delete("");
}
```



#### isolation

격리수준(트랜잭션에서 일관성이 없는 데이터를 허용하도록 하는 수준)을 말하는데 옵션은 다음과 같다.

| level   | 옵션             | 설명                                                         |
| ------- | ---------------- | ------------------------------------------------------------ |
| level 0 | READ_UNCOMMITTED | 트랜잭션에 처리중인 or 아직 commit(확정)되지 않은 데이터를 다른 트랜잭션이 읽는 것을 허용한다.<br>ex) 한 사용자가 A라는 데이터를 B라는 데이터로 변경하는 동안 다른 사용자는 아직 완료되지않은(Uncommitted or Dirty) 데이터 B'를 읽을 수 있다. |
| level 1 | READ_COMMITTED   | Dirty Read를 방지한다. 즉, 트랜잭션이 commit되어 확정된 데이터만을 읽는 것을 허용한다.<br>ex) 한 사용자가 A라는 데이터를 B라는 데이터로 변경하는 동안 다른 사용자는 해당 데이터에 접근할 수 없다. |
| level 2 | REPEATABLE_READ  | 트랜잭션이 완료될 때까지 SELECT문이 사용하는 모든 데이터에 shared lock이 걸린다. 다른 사용자는 그 영역에 해당되는 데이터에 대한 수정이 불가능하다.<br>선행 트랜잭션이 읽은 데이터는 트랜잭션이 종료될 때까지 후행 트랜잭션이 갱신하거나 삭제하는 것을 불허함으로써 같은 데이터를 두 번 쿼리했을 때 일관성 있는 결과를 리턴함 |
| level 3 | SERIALIZABLE     | 완벽한 읽기 일관성 모드를 제공한다.<br>데이터의 일관성 및 동시성을 위해 MVCC를 사용하지 않는다.<br>트랜잭션이 완료될 때까지 SELECT 문장이 사용하는 모든 데이터에 shared lock이 걸리므로 다른 사용자는 그 영역에 해당되는 데이터에 대한 수정 및 입력이 불가능하다. |

> Dirty read 
>
> 위와 같이 다른 트랜잭션에서 처리하는 작업이 완료되지 않았는데도 다른 트랜잭션에서 볼 수 있는 현상을 dirty read 라고 하며, READ UNCOMMITTED 격리수준에서만 일어나는 현상

> MVVC(Multi Version Concurrency Control)
>
> MVCC는 다중 사용자 데이터베이스 성능을 위한 기술로 데이터 조회 시 LOCK을 사용하지 않고 데이터의 버전을 관리해 데이터의 일관성 및 동시성을 높이는 기술



#### propagation

트랜잭션 동작 도중에 다른 트랜잭션을 실행해야하는 상황이 자주 발생하게 되는데, 호출되는 트랜잭션의 입장에서는 호출한 트랜잭션을 그대로 사용할 수도 있고, 새로운 트랜잭션을 생성할 수도 있다.

- 호출한 트랜잭션을 그대로 사용한 경우 중간에 오류가 발생하면 모든 트랜잭션이 롤백이 된다.

- 새로운 트랜잭션을 생성한 경우  중간에 오류가 발생하면 오류가 발생한 트랜잭션이 롤백 될 것이다. 

이러한 트랜잭션 관련 설정은 @Transactional의 propagation 속성을 통해 지정할 수 있다.

```java
@Transactional(propagation = Propagation.REQUIRES_NEW)
public void something (int a) {
    …
}
```

| propagation 속성 | 설명                                                         |
| ---------------- | ------------------------------------------------------------ |
| **REQUIRED**     | 부모 트랜잭션 내에서 실행하며 부모 트랜잭션이 없을 경우 새로운 트랜잭션을 생성 |
| REQUIRES_NEW | 부모 트랜잭션을 무시하고 무조건 새로운 트랜잭션이 생성 |
|MANDATORY| 부모 트랜잭션 내에서 실행되며 부모 트랜잭션이 없을 경우 예외가 발생 |
|SUPPORTS| 부모 트랜잭션 내에서 실행하며 부모 트랜잭션이 없을 경우 nontransactionally로 실행 |
|NOT_SUPPORTED| nontransactionally로 실행하며 부모 트랜잭션 내에서 실행될 경우 일시 정지 |
|NEVER| nontransactionally로 실행되며 부모 트랜잭션이 존재한다면 예외가 발생 |
|NESTED| 해당 메서드가 부모 트랜잭션에서 진행될 경우 별개로 커밋되거나 롤백될 수 있다.<br> 둘러싼 트랜잭션이 없을 경우 REQUIRED와 동일하게 작동 |

#### rollback-for

특정 예외가 발생했을 경우에 롤백되도록 설정한다. 설정하지 않을 경우 오로지 RuntimeException을 상속받은 예외에만 롤백처리를 해준다.

#### no-rollback-for 

특정 예외가 발생하더라도 롤백되지 않도록 설정한다.



#### 참조

- [https://preamtree.tistory.com/97 ](https://preamtree.tistory.com/97 )
- [https://taetaetae.github.io/2016/10/08/20161008/](https://taetaetae.github.io/2016/10/08/20161008/)