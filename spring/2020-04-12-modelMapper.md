# Model Mapping

모델 매핑은 어느 Layer 단에서 구현해야할까?

- Servie : 여러 서비스에서 사용시 중복코드가 발생하며, 모델간 매핑 로직은 비즈니스 로직이 아니므로, 목적에 부합하지 않는다.
- Model Object 
  - 서비스가 커지고, 모델간 다양한 매핑이 있을 경우 점점 객체안에 메서드가 많아지게 된다.
  - 모델 객체에 모델간 매핑 로직은 모델 객체의 목적에 부합하지 않는다.
#### Mapper
**모델간 매핑에 대한 책임**을 진다.
이때, 라이브러리를 이용해서 모델간 매핑을 자동화할것인지 직접 Mapper를 이용해서 처리할지 정해야한다.

- **ModelMapper**
  - 내부적으로 Refelction을 사용하므로 사용하지 않는 것이 좋다.
  - Reflection으로 인한 성능 이슈와 예상치 못한 결과가 발생할 수 있다.
- **MapStruct**
  - Reflection을 사용하지 않는다.
  - 컴파일시 생성한다.
  - 국내는 적지만 미국에서 점점 사용도가 높아지고 있다.

## Model Mapper

Entity와 DTO간 객체 변환을 할 때 ModelMapper를 활용하면, 쉽게 변환할 수 있다.

- pom.xml

```xml
	<!-- model mapper - entity-DTO conversion -->
<dependency>
  <groupId>org.modelmapper</groupId>
  <artifactId>modelmapper</artifactId>
  <version>2.3.0</version>
</dependency>
```

사용 방법은 간단하다. 

```java
private PaymentDto convertToDto(Payment payment) {
		
		// Entity를 DTO로 변환하기위해 modelmapper사용 
		ModelMapper modelMapper = new ModelMapper();
		
		PaymentDto paymentDto = modelMapper.map(payment, PaymentDto.class);
	    
		return paymentDto;
}
```

처음에는 이렇게 convertToDto 메소드로 Entity에서 DTO로 변환하는 작업을 했으나, 이것은 비즈니스 로직이 아니기 때문에 따로 Mapper클래스를 생성하는 것이 좋다.

## MapStruct

- pom.xml

```xml
<!-- mapStruct - Entity to Dto-->
<dependency>
  <groupId>org.mapstruct</groupId>
  <artifactId>mapstruct</artifactId>
  <version>1.3.1.Final</version> 
</dependency>
```

```xml
<plugin>
  <groupId>org.apache.maven.plugins</groupId>
  <artifactId>maven-compiler-plugin</artifactId>
  <configuration>
    <annotationProcessorPaths>
      <path>
        <groupId>org.mapstruct</groupId>
        <artifactId>mapstruct-processor</artifactId>
        <version>1.3.1.Final</version>
      </path>
      <!-- other annotation processors -->
    </annotationProcessorPaths>
  </configuration>
</plugin>
```

- EntityMapper

```java
import java.util.List;

public interface EntityMapper <D, E>{

	E toEntity(D dto);
	D toDto(E entity);
	List<D> toDtoList(List<E> entity);
}
```

-  PaymentMapper

```java
@Mapper(componentModel = "spring")
public interface PaymentMapper extends EntityMapper<PaymentDto, Payment> {


}
```

- Service

```java
@Autowired
private PaymentMapper paymentMapper;
	@Override
	@Transactional
	public PaymentDto cancelRequest(String mbrId, String pmtId, long pmtAmt, Boolean isParticleCancle) {
		
	// ...
		Payment result = paymentRepository.save(newPayment); 
		PaymentDto paymentDto = paymentMapper.toDto(result);
		
		return paymentDto;
  }
```

이렇게 사용하면된다. 만약에 변수명이 다르다면, @Mapping annotation으로 쉽게 바꿀 수 있다.



## 참조

- [https://mapstruct.org/](https://mapstruct.org/)
- [https://atin.tistory.com/672](https://atin.tistory.com/672)

