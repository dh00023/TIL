# JPA Entity

JPA Entity를 구현하려면 다음 규칙을 지켜져야한다.

1. **모든 Entity 클래스는 @Id 설정이 필요**하다.
   - 이때 **@Id로 설정된 값에는 null값이 올 수 없다**.
2. 기본키가 복합키인 경우에는 @EmbeddedId 혹은 @IdClass를 사용한다.
3. 테이블에 Primary Key가 없는 경우가 있을 수 있다. 이 경우에는 **Unique한 컬럼을 기준으로 @Id annotation을 붙이면된다**.

## 단일키

```java
@Entity
@Table(name="member")
public class Member implements Serializable {
	
	private static final long serialVersionUID = 1L;

	@Id
	private String mbrId;
	
	private String name;
	
	//Getter, Setter
}

```

- @Entity : JPA Entity임을 알린다.
- @Table : 'member' 테이블과 매핑됨을 명시한다.
- @Id : Primary Key임을 명시한다.

## 복합키(EmbeddedId, @IdClass)

두 어노테이션은 물리적 모델 관점에서 차이점은 없다.

- @EmbeddedId는 결합 된 PK가 의미있는 엔티티 자체이거나 코드에서 재사용 될 때 의미가 있다.
  - 객체 지향에 더 가까운 방법
- @IdClass는 필드의 일부 조합이 고유하지만 특별한 의미가 없을 경우에 유용하다.
  - DB에 더 가까운 방법

### @IdClass

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

### @EmbeddedId

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