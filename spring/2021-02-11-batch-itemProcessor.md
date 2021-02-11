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

## 구현체

Spring Batch 에서는 자주 사용하는 용도의 Processor를 미리 클래스로 만들어서 제공해주고 있다.

- ItemProcessorAdapter
- ValidatingItemProcessor
- CompositeItemProcessor

하지만 최근에는 대부분 processor를 직접 구현하는 경우가 많고, 람다식으로 빠르게 구현할때도 많다. 그래서 `ItemProcessorAdapter`와 `ValidatingItemProcessor`는 거의 사용하지 않는다.

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

