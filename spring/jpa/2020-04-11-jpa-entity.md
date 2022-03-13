# JPA Entity 매핑


## 객체와 테이블 매핑

| annotation | 설명                                                         |
| ---------- | ------------------------------------------------------------ |
| @Entity    | 클래스를 테이블과 매핑한다고 JPA에 알려줌<br />JPA Entity임을 알린다. |
| @Table     | Entity Class에 매핑할 테이블 정보를 알려준다.<br />이 어노테이션 생략시 클래스 이름을 테이블 이름으로 매핑 |

### @Entity

- 기본 생성자는 필수
- `final` 클래스, `enum`, `interface`, `inner` 클래스에는 사용 불가
- 저장할 필드에 `final` 사용하면 안됨

### @Table

| 속성                         | 기능                                                         | 기본값             |
| ---------------------------- | ------------------------------------------------------------ | ------------------ |
| name                         | 매핑할 테이블 명                                             | 엔티티 이름을 사용 |
| catalog                      | catalog 기능이 있는 데이터베이스에서 catalog 매핑            |                    |
| schema                       | schema 기능이 있는 데이터베이스에서 schema 매핑              |                    |
| uniqueConstraints<br />(DDL) | DDL 생성 시 유니크 제약조건을 만듦<br />2개 이상의 복합 유니크 제약조건도 만들 수 있으며, 이 기능은 스키마 자동 생성 기능을 사용해 DDL을 만들때만 사용 |                    |

## 데이터베이스 초기화 전략

```yaml
# application.yml
spring.jpa.hibernate.ddl-auto=[none|create-drop|create|update|validate]
```

- `none`: 아무것도 실행하지 않음(default)
- `create-drop`: SessionFactory가 시작될 때 drop 후 create를 실행하고, SessionFactory가 종료될 때 drop을 실행(in-memory DB의 경우 기본값)
- `create`: SessionFactory가 시작될 때 데이터베이스 drop을 실행하고 create 실행
- `update`: 변경된 스키마를 적용
- `validate`: 변경된 스키마가 있다면 변경사항을 출력하고 애플리케이션을 종료

## 제약 조건

### 두개 이상 컬럼 묶어 Unique 설정

`@Table`의 `uniqueConstraints` 속성을 사용해 지정할 수 있다.

```kotlin
@Table(uniqueConstraints = {
  @UniqueConstraint(name = "NAME_AGE_UNIQUE",
                   columnNames = {"name", "age"})
})
```

```sql
ALTER TABLE MEMBER
	ADD CONSTRAINT NAME_AGE_UNIQUE UNIQUE (NAME, AGE)
```

## 필드와 컬럼 매핑

### @Column

DDL과 관련된 속성들은 DDL을 자동으로 생성하는 경우에만 사용되며, JPA 실제 로직에는 영향을 주지 않는다.

| 속성                                 | 설명                                                         | 기본값                                                |
| ------------------------------------ | ------------------------------------------------------------ | ----------------------------------------------------- |
| name                                 | 매핑할 컬럼의 이름을 지정.                                   | 객체 Field 이름                                       |
| insertable<br />(거의 사용하지 않음) | Entity 저장 시 해당 Field도 저장, false로 읽기 전용 설정 가능. | true                                                  |
| updatable<br />(거의 사용하지 않음)  | Entity 수정 시 해당 Field도 수정, false로 읽기 전용 설정 가능. | true                                                  |
| table<br />(거의 사용하지 않음)      | 하나의 Entity설정에서 두 개이상 Table에 매핑할 때 사용       | 현재 Class가 매핑된 Table                             |
| nullable(DDL)                        | true/false로 null 허용 여부 설정                             | true                                                  |
| unique(DDL)                          | true/false로 Unique 제약 조건 설정<br />`@Table.uniqueConstraints`와 동일하지만 한 컬럼에만 제약조건을 걸 때 사용 |                                                       |
| length(DDL)                          | Column 속성 길이 설정                                        | 255                                                   |
| columnDefinition(DDL)                | DB Column 정보를 직접 설정                                   | Java Type과 설정 DB 방언으로, 적절한 Column Type 생성 |
| precision, scale(DDL)                | BigDecimal, BigInteger Type에서 사용<br />- precision: 소수점 포함 전체 자릿수<br />- scale: 소수 자릿수, <br />double, float Type에는 적용되지 않음. 아주 큰 숫자나 정밀한 소수를 다룰때 사용. | precision=19, scale=2                                 |

### @Enumerated

`enum class` 를 사용하려면 `@Enumerated` 어노테이션으로 매핑이 필요하다.

- `EnumType.ORDINAL` : enum 순서를 데이터베이스에 저장 (default)
  - 장점 : 데이터베이스에 저장되는 데이터 크기가 작음
  - 단점 : 이미 저장된 enum 순서 변경 불가
- `EnumType.STRING` : enum 명을 데이터베이스에 저장(권장)
  - 장점 : 저장된 enum의 순서가 바뀌거나 추가되어도 안전
  - 단점 : 데이터베이스에 저장되는 데이터 크기가 ORDINAL에 비교해 큼

### @Temporal

날짜 타입(`java.util.Date`, `java.util.Calendar`)을 매핑할 때 사용하며, 아래 `TemporalType`은 필수로 지정해야한다.

- `TemporalType.DATE`
- `TemporalType.TIME`
- `TemporalType.TIMESTAMP`
  - datetime : MySQL
  - timestamp : H2, Oracle, PostgreSQL


### @CreationTimestamp / @UpdateTimestamp

엔티티 객체에 대해 `INSERT`, `UPDATE` 등의 쿼리가 발생할 때, 현재 시간을 자동으로 저장해주는 `@CreationTimestamp`와 `@UpdateTimestamp` 어노테이션을 제공.

### @Lob

`CLOB`, `BLOB` 타입 매핑시 `@Lob`을 사용하면 된다.

- CLOB : `String`, `char []`, `java.sql.CLOB`
- BLOB : `byte[]`, `java.sql.BLOB`

> mysql text 타입인 경우에는 `@Column(columnDefinition = "TEXT")` 사용
>
> longtext의 경우 `@Lob` 사용

### @Transient

해당 필드는 매핑하지 않으므로, 데이터베이스에 저장/조회하지 않는다. 
즉, 객체에 임시로 어떤 값을 보관하고 싶은 경우에 사용한다.

```kotlin
@Transient
val temp: String
```

### @Access

JPA가 Entity에 접근하는 방식 지정

- `AccessType.FIELD` : 필드에 직접 접근.
- `AccessType.PROPERTY` : 접근자(getter)를 사용해 접근

지정하지 않는 경우 `@Id`를 지정한 기준으로 설정된다.

## 기본 키 매핑

JPA Entity를 구현하려면 다음 규칙을 지켜져야한다.

1. **모든 Entity 클래스는 `@Id` 설정이 필요**하다.
   - 이때 **`@Id`로 설정된 값에는 `null`값이 올 수 없다**.
2. 기본키가 복합키인 경우에는 `@EmbeddedId` 혹은 `@IdClass`를 사용한다.
3. 테이블에 Primary Key가 없는 경우가 있을 수 있다. 이 경우에는 **Unique한 컬럼을 기준으로 `@Id` annotation을 붙이면된다**.

### 자동 할당(단일키)

기본 키를 애플리케이션에서 직접 할당하는 방법

| 속성 | 설명                                    |
| ---- | --------------------------------------- |
| @Id  | Primary Key임을 명시<br />(식별자 필드) |

`entityManager.persist()` 호출 전 애플리케이션에서 직접 식별자 값을 할당해야하며, 식별자 값 없이 저장하면 예외가 발생한다.

### 자동 생성(단일키)

대리 키 사용 방식으로 `@GeneratedValue` 추가 후 원하는 키 생성 전략을 선택하면된다.

| strategy | 설명                                                         |
| -------- | ------------------------------------------------------------ |
| IDENTITY | 기본 키 생성을 데이터베이스에 위임<br />(데이터베이스에 의존<br />MySQL은 기본 키 값을 자동으로 채워주는 AUTO_INCREMENT 기능 제공) |
| SEQUENCE | 데이터베이스 시퀀스를 사용해 기본키 할당<br />(데이터베이스에 의존 : 오라클은 제공, MySQL은 제공하지 않음) |
| TABLE    | 키 생성용 테이블을 하나 만들어두고 시퀀스처럼 사용하는 방법  |

#### IDENTITY

```kotlin
@GeneratedValue(strategy = GenerationType.IDENTITY)
```

여기서 `IDENTITY` 전략은 데이터베이스에 insert한 후에 기본 키 값을 조회할 수 있다.(데이터베이스에 Entity를 저장해서 식별자 값을 획득한 후 영속성 컨텍스트에 저장) 하이버네이트의 경우는 JDBC3에서 제공하는 API의 `Statement.getGeneratedKeys()` 메서드를 사용하여 데이터를 저장함과 동시에 생성된 키값을 얻어온다. **이 경우에는 트랜잭션 쓰기 지연은 동작하지 않는다.**

#### SEQUENCE

```sql
CREATE SEQUENCE [sequenceName] START WITH [initialValue] INCREMENT BY [allocationSize];
```

```kotlin
@Entity
data class Board(
	@Id
  @GeneratedValue(strategy = GenerationType.SEQUENCE,
                 generator = "BOARD_SEQ_GENERATOR")
  @SequenceGenerator(
    name = "BOARD_SEQ_GENERATOR",
    sequenceName = "BOARD_SEQ", // 매핑할 데이터베이스 시퀀스명
    initialValue = 1,
    allocationSize = 1
  )
  val id: Long
)
```

여기서 `@SequenceGenerator`를 사용해 시퀀스 생성기를 등록했으며, 등록한 시퀀스 생성기를 ` @GeneratedValue` 의 generator로 생성한 시퀀스를 지정했다.

- @SequenceGenerator

  | 속성            | 기능                                                         | default            |
  | --------------- | ------------------------------------------------------------ | ------------------ |
  | name            | 식별자 생성기 이름                                           | 필수값             |
  | sequenceName    | 데이터베이스에 등록되어있는 시퀀스 이름                      | hibernate_sequence |
  | initialValue    | DDL 생성시에만 사용<br />시퀀스 DDL 생성시 처음 시작하는 수 지정 | 1                  |
  | allocationSize  | 시퀀스 한 번 호출에 증가하는 수                              | 50                 |
  | catalog, schema | 데이터베이스 catalog, schema 이름                            |                    |

여기서 매핑할 데이터베이스 시퀀스 명을 지정하지 않으면 `hibernate_sequence`를 전역에서 사용한다.

SEQUENCE 전략은 데이터베이스 1. <u>시퀀스를 사용해 식별자를 조회</u>한 후 2. <u>조회한 식별자를 Entity에 할당하고, 영속성 컨텍스트에 저장</u>한다.

즉, 데이터베이스와 2번 통신한다.

JPA는 시퀀스에 접근하는 횟수를 줄이기 위해 `allocationSize`를 사용한다. allocationSize만큼 한 번에 시퀀스 값을 증가시키고, allocationSize만큼 메모리에 시퀀스 값을 할당한다.
이 최적화 방법은 시퀀스 값을 선점하므로, 여러 JVM이 동시에 동작해도 기본 키 값이 충돌하지 않는다. 단 allocationSize만큼 시퀀스 값이 증가하는 것은 유의해야한다.

```yaml
# application.yml 다음 설정이 true로 설정해야 최적화 방법 적용됨
# true로 설정하지않으면 1 (1~50) 2(51~100)과 같이 할당됨
spring.jpa.hibernate.use-new-id-generator-mappings = [true|off|false|on]
```

#### TABLE

```kotlin
@Entity
@TableGenerator(
	name = "BOARD_SEQ_GENERATOR",
  table = "CUSTOM_SEQUENCES",
  pkColumnValue = "BOARD_SEQ",
  allocationSize = 1
)
data class Board(
  @GeneratorValue(strategy = GenerationType.TABLE,
                   generator = "BOARD_SEQ_GENERATOR")
  val id: Long
)

```

```sql
create table CUSTOM_SEQUENCES(
	sequence_name varchar(255) not null,
  next_val bigint,
  primary key (sequence_name)
)
```

`CUSTOM_SEQUENCES` 키 생성용 테이블을 하나 만들어두고 그 테이블을 지정한 후 `pkCloumnValue`로 시퀀스 값을 한개 생성하여 사용하는 것이다. 

| Sequence_name | Next_val |
| ------------- | -------- |
| BOARD_SEQ     | 2        |

다음과 같이 pkCloumnValue로 지정한 값이 추가된 것을 볼 수 있으며, 키 생성시마다 `next_val`이 증가하는 것을 볼 수 있다.

- `@TableGenerator`

  | 속성                   | 기능                                                         | 기본값             |
  | ---------------------- | ------------------------------------------------------------ | ------------------ |
  | name                   | 식별자 생성기 이름                                           | 필수값             |
  | table                  | 키 생성 테이블명                                             | hibernate_sequence |
  | pkColumnName           | 시퀀스 컬럼명                                                | sequence_name      |
  | valueColumnName        | 시퀀스 값 컬럼명                                             | next_val           |
  | pkColumnValue          | 키로 사용할 값 이름                                          | Entity 이름        |
  | initialValue           | DDL 생성시에만 사용<br />시퀀스 DDL 생성시 처음 시작하는 수 지정 | 0                  |
  | allocationSize         | 시퀀스 한 번 호출에 증가하는 수                              | 50                 |
  | catalog, schema        | 데이터베이스 catalog, schema 이름                            |                    |
  | uniqueConstraints(DDL) | 유니크 제약조건 지정                                         |                    |


이 전략은 데이터베이스 시퀀스 생성용 테이블에서 식별자 값을 획득한 후 영속성 컨텍스트에 저장한다.

### AUTO

`GenerationType.AUTO` 는 선택한 데이터베이스에 따라 위 3개 전략 중 하나를 자동으로 선택한다.

- Oracle : SEQUENCE
- MySQL : IDENTITY

### 권장하는 식별자 선택 전략

데이터베이스 기본 키는

1. null 값은 허용하지 않는다.
2. 유일해야한다.
3. 변해선 안 된다.

테이블의 기본 키를 선택하는 전략은 <u>1. 자연 키</u> , <u>2. 대리 키</u>가 있다. 

- 자연 키 : 비즈니스에 의미가 있는 키 (ex) 주민번호, 이메일, 전화번호
- 대리 키/대체 키 : 비즈니스와 관련 없는 임의로 만들어진 키 (ex) 시퀀스, auto_increment

비즈니스 환경은 언젠가 변하며, 자연 키보다는 대리 키 사용을 권장한다.

### 복합키(EmbeddedId, @IdClass)

두 어노테이션은 물리적 모델 관점에서 차이점은 없다.

- @EmbeddedId는 결합 된 PK가 의미있는 엔티티 자체이거나 코드에서 재사용 될 때 의미가 있다.
  - 객체 지향에 더 가까운 방법
- @IdClass는 필드의 일부 조합이 고유하지만 특별한 의미가 없을 경우에 유용하다.
  - DB에 더 가까운 방법

#### @IdClass

@IdClass에는 식별자 클래스를 생성해야한다. 예시에서는 PaymentMasterPk 클래스를 생성해주었다. 여기서 식별자 클래스에는 몇가지 규칙이 있다.

1. Serializable 인터페이스 구현
2. 식별자 클래스의 필드명과 Entity에서 사용하는 식별자의 필드명이 동일해야한다.
3. `equals()` 와 `hashCode()` 를 구현해야한다.
4. 기본 생성자(args가 없는)를 구현해야한다.
5. 클래스의 접근 제한자는 public이어야한다.

```java
@Entity
@IdClass(PaymentMasterPK.class)
@Table(name="payment_mst")
public class PaymentMaster implements Serializable{
	
	private static final long serialVersionUID = 1L;

	@Id
	private String pmtCode;
	
	@Id
	private String pmtType;
	
	private String pmtName;
	
	private String partCnclYn;
	
  // Getter, Setter
}
```

```java
public class PaymentMasterPK implements Serializable{

	private static final long serialVersionUID = 1L;

	private String pmtCode;
	private String pmtType;

	public PaymentMasterPK(){

	}

	public PaymentMasterPK(String pmtCode, String pmtType){
		if(StringUtils.isEmpty(pmtType)) {
			pmtType = new String("");
		}
		this.pmtCode = pmtCode;
		this.pmtType = pmtType;
	}

  // Getter, Setter
	
	@Override
	public boolean equals(Object obj) {
		
		if(this == obj) {
			return true;
		}
		
		if(obj == null || this.getClass() != obj.getClass()) {
			return false;
		}
		
		PaymentMasterPK paymentMasterPK = (PaymentMasterPK)obj;
		
		if(this.pmtCode.equals(paymentMasterPK.pmtCode) && this.pmtType.equals(paymentMasterPK.pmtType) ) {
			return true;
		}
		
		return false;
		
	}
	@Override
	public int hashCode() {
		return Objects.hash(pmtCode, pmtType);		
	}
}
```

#### @EmbeddedId

1. 식별자 클래스에 @Embeddable을 사용해야한다.
2. Serializable 인터페이스를 구현해야한다.
3. `equals()`, `hashCode()` 를 구현해야한다.
4. 기본생성자를 선언해야한다.
5. 클래스의 접근 제한자는 public이어야한다.

```java
@Entity
@Table(name="payment_mst")
public class PaymentMaster implements Serializable{
	
	private static final long serialVersionUID = 1L;

	@EmbeddedId
	private PaymentMasterPk paymentMasterPK;
		
	private String pmtName;
	
	private String partCnclYn;
	
  // Getter, Setter
}
```

```java
@Embeddable
public class PaymentMasterPK implements Serializable{

	private static final long serialVersionUID = 1L;

	private String pmtCode;
	private String pmtType;

	public PaymentMasterPK(){

	}

	public PaymentMasterPK(String pmtCode, String pmtType){
		this.pmtCode = pmtCode;
		this.pmtType = pmtType;
	}

  // Getter, Setter
	
	@Override
	public boolean equals(Object obj) {
		
		if(this == obj) {
			return true;
		}
		
		if(obj == null || this.getClass() != obj.getClass()) {
			return false;
		}
		
		PaymentMasterPK paymentMasterPK = (PaymentMasterPK)obj;
		
		if(this.pmtCode.equals(paymentMasterPK.pmtCode) && this.pmtType.equals(paymentMasterPK.pmtType) ) {
			return true;
		}
		
		return false;
		
	}
	@Override
	public int hashCode() {
		return Objects.hash(pmtCode, pmtType);		
	}
}
```



## 참조

- [http://blog.breakingthat.com/2018/03/16/jpa-entity-%EB%B3%B5%ED%95%A9pk-%EB%A7%B5%ED%95%91-embeddedid-idclass/](http://blog.breakingthat.com/2018/03/16/jpa-entity-복합pk-맵핑-embeddedid-idclass/)
- [https://steady-hello.tistory.com/106](https://steady-hello.tistory.com/106)