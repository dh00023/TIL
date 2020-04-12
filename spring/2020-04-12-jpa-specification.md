# Spring Data Specification

**Specification는 검색조건을 추상화한 객체**다. 검색 조건에 대해 Specification에 생성하고, 이를 통해 다양한 조건의 검색을 할 수 있다는 뜻이다. 

Spring JPA Specificatoin은 동적 쿼리(Dynamic Query)를 작성할 때 도움이 된다. 예를 들어, 필터링(해당 값이 있는 경우에만 조건을 걸 때)을 할때 사용하면 좋다. 

Specification 다음과 같은 방식으로 조건 검색을 한다. 

1. Specification을 입력 받도록 Repository 인터페이스 정의하기
2. 검색 조건을 모아 놓은 클래스 만들기 (Specifications 객체)
3. 검색 조건을 조합한 Specification 인스턴스를 이용해서 검색하기

```java
public interface PaymentRepository extends JpaRepository<Payment, String>, JpaSpecificationExecutor<Payment>{
}

```

상속받지 않고 필요한 메소드만 직접 정의해서 구현해도 된다. JpaSpecificationExecutor를 살펴보면 다음과 같이 구현되어 있는 것을 볼 수 있다.

```java
/**
 * Interface to allow execution of {@link Specification}s based on the JPA criteria API.
 *
 * @author Oliver Gierke
 * @author Christoph Strobl
 */
public interface JpaSpecificationExecutor<T> {

	/**
	 * Returns a single entity matching the given {@link Specification} or {@link Optional#empty()} if none found.
	 *
	 * @param spec can be {@literal null}.
	 * @return never {@literal null}.
	 * @throws org.springframework.dao.IncorrectResultSizeDataAccessException if more than one entity found.
	 */
	Optional<T> findOne(@Nullable Specification<T> spec);

	/**
	 * Returns all entities matching the given {@link Specification}.
	 *
	 * @param spec can be {@literal null}.
	 * @return never {@literal null}.
	 */
	List<T> findAll(@Nullable Specification<T> spec);

	/**
	 * Returns a {@link Page} of entities matching the given {@link Specification}.
	 *
	 * @param spec can be {@literal null}.
	 * @param pageable must not be {@literal null}.
	 * @return never {@literal null}.
	 */
	Page<T> findAll(@Nullable Specification<T> spec, Pageable pageable);

	/**
	 * Returns all entities matching the given {@link Specification} and {@link Sort}.
	 *
	 * @param spec can be {@literal null}.
	 * @param sort must not be {@literal null}.
	 * @return never {@literal null}.
	 */
	List<T> findAll(@Nullable Specification<T> spec, Sort sort);

	/**
	 * Returns the number of instances that the given {@link Specification} will return.
	 *
	 * @param spec the {@link Specification} to count instances for. Can be {@literal null}.
	 * @return the number of instances.
	 */
	long count(@Nullable Specification<T> spec);
}
```

### JPA Criteria

JPA Criteria는 동적 쿼리를 사용하기 위한 JPA 라이브러리이다. 기본적으로 JPQL(JPA Query Language)과 같이 엔티티 조회를 기본으로 하며, 컴파일 시점에 에러를 확인할 수 있는 장점이 있다.

### 예제

여기서 필요한 메소드를 정의해서 구현하면된다. 그 중에서 아래의 경우를 구현해볼 것이다. 

```java
Page<T> findAll(@Nullable Specification<T> spec, Pageable pageable);
```

```java
	@Override
	@Transactional(readOnly = true)
	public List<Payment> getPaymentRecentList(String mbrId, String succYn, Integer size) {
		// DynamicQuery로 succYn이 null이 아닌 경우에만 where 조건에 추가
		// Paging을 통해서 size(default 15)만큼만 최근(DESC) 데이터를 가져온다.
		Page<Payment> page= paymentRepository.findAll(new Specification<Payment>() {

			private static final long serialVersionUID = 1L;

			@Override
			public Predicate toPredicate(Root<Payment> root, CriteriaQuery<?> query,
					CriteriaBuilder criteriaBuilder) {
				// TODO Auto-generated method stub
				List<Predicate> predicates = new ArrayList<>();
				
				// where mbrId = ?
				predicates.add(criteriaBuilder.and(criteriaBuilder.equal(root.get( "mbrId"), mbrId)));
				
				// 만약 성공여부(succYn)이 있는 경우에 조건 추가. null인 경   우 전체(Y/N) 조회 
				// where succYn = ?
				if(!StringUtils.isEmpty(succYn)) {
					predicates.add(criteriaBuilder.and(criteriaBuilder.equal(root.get( "succYn"), succYn)));
				}
				
				return criteriaBuilder.and(predicates.toArray(new Predicate[predicates.size()]));
			}
		
			// Jpa PageRequest를 사용해 size만큼 데이터 가져오기
			// 이때 pmtId(primary key)를 기준으로 내림차순(최근)데이터를 가져온다. 
		}, PageRequest.of(0, size, Sort.by(Sort.Direction.DESC, "pmtId"))); 
		
		
		return page.getContent();
	}

```

- CriteriaBuilder 클래스를 통하여 조건문을 정의할 수 있고 정의된 스펙들은 조합하여 쓸 수 있다.

## 참조

- [https://yellowh.tistory.com/114](https://yellowh.tistory.com/114)

- [https://velog.io/@hellozin/JPA-Specification%EC%9C%BC%EB%A1%9C-%EC%BF%BC%EB%A6%AC-%EC%A1%B0%EA%B1%B4-%EC%B2%98%EB%A6%AC%ED%95%98%EA%B8%B0](https://velog.io/@hellozin/JPA-Specification으로-쿼리-조건-처리하기)
- [https://kohen.tistory.com/4](https://kohen.tistory.com/4)

