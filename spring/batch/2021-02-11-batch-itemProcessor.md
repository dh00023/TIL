# ItemProcessor

`ItemPorcessor`는 데이터를 가공하거나 필터링하는 역할을 하며, 필수가 아니다. 이 역할은 `ItemWriter`에서도 구현이 가능하지만, 분리함으로써 비즈니스 코드가 섞이는 것을 방지할 수 있다.

```java
public interface ItemProcessor<I, O> {
    @Nullable
    O process(@NonNull I var1) throws Exception;
}
```

`I`는 ItemReader에서 받을 데이터 타입이며, `O`는 ItemWriter에 보낼 데이터 타입이다. 즉, Reader에서 읽은 데이터가 ItemProcessor의 `process()`를 통과한 후 Writer에 전달된다. 구현해야할 메소드는 process하나이며, **Java 8부터는 인터페이스의 추상 메서드가 1개인 경우 람다식을 사용**할 수 있다.

```java
@Bean(BEAN_PREFIX + "processor")
@StepScope
public ItemProcessor<ReadType, WriteType> processor() {
    return item -> {
        item.convert();
        return item;
    };
}
```

- 불필요한 코드가 없어 구현 코드 양이 적다. (빠르게 구현 가능)
- 고정된 형태가 없어 원하는 형태의 어떤 처리도 가능하다.
- Batch Config 클래스 안에 포함되어 있어야만 하며, Batch Config 코드 양이 많아질 수 있다.
  - 코드 양이 많아지만 별도 클래스로 Processor를 분리해서 사용하기도 한다.

크게 ItemProcessor는 다음 역할을 한다.

- 변환 : Reader에서 읽은 데이터를 원하는 타입으로 변환하여, Writer에 넘겨줄 수 있다.

  ```java
  		// Pay -> String 타입 변환
  		@Bean
      public ItemProcessor<Pay, String> processor(){
          return pay -> {
              return pay.getTxName();
          };
      }
  ```

- 필터 : Reader에서 넘겨준 데이터를 Writer로 넘겨줄 것인지 결정할 수 있으며, `null`을 반환하면 Writer에 전달되지 않는다.

  ```java
  		// amount가 10000이상인 값만 Writer에 넘어가도록 필터
  		@Bean
      public ItemProcessor<Pay, Pay> nullProcessor(){
          return pay -> {
              if(pay.getAmount() < 10000){
                  log.info("Pay amount :{}", pay.getAmount());
                  return null;
              }
              return pay;
          };
      }
  ```

ItemProcessor가 `null`을 반환하면 해당 Item의 모든 이후 처리가 중지된다. 이때 null을 반환하더라도 다른 Item 처리가 계속 이루어진다.

## 구현체

Spring Batch 에서는 자주 사용하는 용도의 Processor를 미리 클래스로 만들어서 제공해주고 있다.

- ItemProcessorAdapter
- ValidatingItemProcessor
- CompositeItemProcessor

하지만 최근에는 대부분 processor를 직접 구현하는 경우가 많고, 람다식으로 빠르게 구현할때도 많다. 그래서 `ItemProcessorAdapter`와 `ValidatingItemProcessor`는 거의 사용하지 않는다.

### ValidatingItemProcessor

입력 데이터 유효성 검증에 사용하는 ItemProcessor 구현체이다. 입력 아이템의 유효성 검증을 수행하는 스프링배치 `Validator`를 사용할 수 있으며, 유효성 검증이 실패하면, `ValidationException`이 발생한다.

- `org.springframework.batch.item.validator.ValidatingItemProcessor`

#### BeanValidatingItemProcessor

JSR 303은 빈 유효성 검증을 위한 것으로, 스프링 배치는 미리 정의된 유효성 검증 기능을 어노테이션으로 제공해준다.
해당 어노테이션을 사용하려면, 다음 의존성을 추가해줘야한다.

```groovy
implementation 'org.springframework.boot:spring-boot-starter-validation'
```

| 어노테이션                     | 속성                                                         | 설명                                                         |
| ------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| @NotNull<br />@Null            |                                                              | 값이 null인지 아닌지 검사                                    |
| @Size                          | int min : 최소 크기(default : 0)<br />int max : 최대크기     | 길이나 크기가 지정한 값 범위에 있는지 검사<br />null은 유효하다고 판단 |
| @Pattern                       | String regexp = 정규표현식                                   | 값이 정규 표현식에 일치하는지 검사<br />null은 유효하다고 판단 |
| @AssertTrue<br />@AssertFalse  |                                                              | 값이 true인지 false인지 검사<br />null은 유효하다 판단       |
| @DecmialMax<br />@DecimalMin   | String value: 최대값 또는 최솟값<br />boolean inclusive : 지정값 포함 여부(default : true) | 지정한 값보다 작거나 같은지 혹은 크거나 같은지 검사<br />null은 유효하다 판단 |
| @Max<br />@Min                 | long value                                                   | 지정한 값보다 작거나 같은지 혹은 크거나 같은지 검사<br />null은 유효하다 판단 |
| @Digits                        | int integer : 허용가능한 정수 자릿수<br />int fraction : 허용 가능한 소수점 이하 자릿수 | 자릿수가 지정한 크기를 넘지 않는지 검사<br />null은 유효하다 판단 |
| @NotEmpty                      |                                                              | 문자열, 배열 :  null이 아니고, 길이가 0이 아닌지 검사<br />Collection :  null이 아니고, 크기가 0이 아닌지 검사 |
| @NotBlank                      |                                                              | null이 아니고 최소한 한개 이상의 공백이 아닌 문자를 포함하는지 검사 |
| @Positive<br />@PositiveOrZero |                                                              | 양수인지 검사<br />OrZero는 양수 혹은 0인지 검사<br />null은 유효하다 판단 |
| @Negative<br />@NegativeOrZero |                                                              | 음수인지 검사<br />OrZero는 음수 혹은 0인지 검사<br />null은 유효하다 판단 |
| @Email                         |                                                              | 이메일 주소가 유효한지 검사<br />null은 유효하다 판단        |
| @Future<br />@FuterOrPresent   |                                                              | 해당 시간이 미래인지 검사<br />OrPresent는 현재 또는 미래시간인지 검사<br />null은 유효하다 판단 |
| @Past<br />@PastOrPresent      |                                                              | 해당 시간이 과거인지 검사<br />OrPresent는 현재 또는 과거시간인지 검사<br />null은 유효하다 판단 |

```java
public class Customer {

    @NotNull(message = "firstname은 필수값입니다.")
    @Pattern(regexp = "[a-zA-Z]+", message = "firstname은 영어여야합니다.")
    private String firstName;

    @NotNull(message = "city 필수값입니다.")
    @Pattern(regexp = "[a-zA-Z\\. ]+")
    private String city;

    @NotNull(message = "state 필수값입니다.")
    @Size(min=2, max=2)
    @Pattern(regexp = "[A-Z{2}]+")
    private String state;

  // ...
}
```

위 예제와 같이 고유한 메세지를 지정할 수 있으며, 필드 값의 길이가 잘못됐는지 형식이 잘못됐는지 식별할 수 있다.

```java
    @Bean
    public Step validationDelimitedFileStep() {
        return this.stepBuilderFactory.get("validationDelimitedFileStep")
                .<Customer, Customer>chunk(10)
                .reader(validationDelimitedCustomerItemReader(null))
                .processor(validationCustomerProcessor()) // processor
                .writer(validationDelimitedCustomerItemWriter())
                .build();
    }

    /**
     * BeanValidationItemProcessor 설정
     * @return
     */
    @Bean
    public BeanValidatingItemProcessor<Customer> validationCustomerProcessor() {
        return new BeanValidatingItemProcessor<>();
    }
```

```alidation failed for Customer(firstName=Athena, middleInitial=YS, lastName=Burt, addressNumber=4951, street=Mollis Rd., city=Newark, state=DE, zipCode=41034, address=null, transactions=null): 
Field error in object 'item' on field 'middleInitial': rejected value [YS]; codes [Size.item.middleInitial,Size.middleInitial,Size.java.lang.String,Size]; arguments [org.springframework.context.support.DefaultMessageSourceResolvable: codes [item.middleInitial,middleInitial]; arguments []; default message [middleInitial],1,1]; default message [크기가 1에서 1 사이여야 합니다]
Field error in object 'item' on field 'middleInitial': rejected value [YS]; codes [Pattern.item.middleInitial,Pattern.middleInitial,Pattern.java.lang.String,Pattern]; arguments [org.springframework.context.support.DefaultMessageSourceResolvable: codes [item.middleInitial,middleInitial]; arguments []; default message [middleInitial],[Ljavax.validation.constraints.Pattern$Flag;@5c7a06ec,[a-zA-Z]]; default message [middleInitial는 반드시 영어여야합니다.]
```

다음과 같이 지정한 validation에 맞지 않으면 예외가 발생하는 것을 볼 수 있다.

#### ValidatingItemProcessor

데이터셋 내에서 한개의 필드의 값이 고유해야하는 경우가 있을 수 있다.
고유한 값의 필드를 `ItemStream` 인터페이스를 구현하여, 각 커밋과 필드 값을 `ExecutionContext`에 저장해 상태를 유지할 수 있다.

```java

/**
 * JobExecution 간의 상태를 저장하기 위해 ItemStreamSupport 상속
 */
public class UniqueLastNameValidator extends ItemStreamSupport implements Validator<Customer> {

    private Set<String> lastNames = new HashSet<>();

    @Override
    public void validate(Customer value) throws ValidationException {
        if (lastNames.contains(value.getLastName())) {
            throw new ValidationException(value.getLastName() + " lastName이 중복됩니다.");
        }
        this.lastNames.add(value.getLastName());
    }

    @Override
    public void open(ExecutionContext executionContext) {

        String lastNames = getExecutionContextKey("lastNames");

        // lastNames가 Execution에 저장되어있는지 확인 후 저장되어있다면, 스텝 처리 이전에 해당값으로 원복
        if (executionContext.containsKey(lastNames)) {
            this.lastNames = (Set<String>) executionContext.get(lastNames);
        }
    }

    /**
     * 청크 단위로 수행되는데, 오류가 발생할 경우 현재 상태를 ExecutionContext에 저장
     * @param executionContext
     */
    @Override
    public void update(ExecutionContext executionContext) {
        Iterator<String> itr = lastNames.iterator();
        Set<String> copiedLastNames = new HashSet<>();

        while (itr.hasNext()) {
            copiedLastNames.add(itr.next());
        }

        executionContext.put(getExecutionContextKey("lastNames"), copiedLastNames);
    }
}
```

Validator를 구현한 후 Step을 다음과 같이 구현하면 된다.

```java
@Bean
    public Step validationDelimitedFileStep() {
        return this.stepBuilderFactory.get("validationDelimitedFileStep")
                .<Customer, Customer>chunk(10)
                .reader(validationDelimitedCustomerItemReader(null))
                .processor(customerValidatingItemProcessor()) // 프로세서
                .writer(validationDelimitedCustomerItemWriter())
                .stream(uniqueLastNameValidator()) // stream 설정
                .build();
    }



    @Bean
    public ValidatingItemProcessor<Customer> customerValidatingItemProcessor() {
        return new ValidatingItemProcessor<>(uniqueLastNameValidator());
    }

    @Bean
    public UniqueLastNameValidator uniqueLastNameValidator() {
        UniqueLastNameValidator uniqueLastNameValidator = new UniqueLastNameValidator();

        uniqueLastNameValidator.setName("uniqueLastNameValidator");

        return uniqueLastNameValidator;
    }
```





`CompositeItemProcessor`는 **ItemProcessor간의 체이닝을 지원**하는 Processor이다.

```java
    @Bean
    public CompositeItemProcessor compositeItemProcessor(){
        List<ItemProcessor> delegates = new ArrayList<>(2);
        delegates.add(nullProcessor());
        delegates.add(processor());

        CompositeItemProcessor processor = new CompositeItemProcessor();
        processor.setDelegates(delegates);
        return processor;
    }

		@Bean
    public ItemProcessor<Pay, String> processor(){
        return pay -> {
            return pay.getTxName();
        };
    }


    @Bean
    public ItemProcessor<Pay, Pay> nullProcessor(){
        return pay -> {
            if(pay.getAmount() < 10000){
                log.info("Pay amount :{}", pay.getAmount());
                return null;
            }
            return pay;
        };
    }
```

다음과 같이 Processor가 여러개 필요한 경우 체이닝 작업을 할 수 있다.

하지만, 여기서 제네릭 타입은 사용하지 못하며, 만약 제네릭타입을 사용하게 되면 `delegates`에 포함된 `ItemProcessor`는 모두 같은 제네릭 타입을 가져야한다. 만약 같은 제네릭 타입을 사용할 수 있는 ItemProcessor간 체이닝이라면 제네릭을 선언하는 것이 더 안전한 코드가 될 수 있다.



## 참고

- [기억보단 기록을 - 9. Spring Batch 가이드 - ItemProcessor](https://jojoldu.tistory.com/347?category=902551)

