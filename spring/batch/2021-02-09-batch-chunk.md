# Chunk 지향 처리

![](https://docs.spring.io/spring-batch/docs/4.0.x/reference/html/images/chunk-oriented-processing.png)

Chunk란 **아이템이 트랜잭션에 commit되는 수**를 말한다.

즉, **청크 지향 처리란 한 번에 하나씩 데이터를 읽어 Chunk라는 덩어리를 만든 뒤, Chunk 단위로 트랜잭션을 다루는 것을 의미**한다. Chunk 단위로 트랜잭션을 수행하기 때문에, 수행이 실패한 경우 해당 Chunk 만큼만 롤백이 되고, 이전에 커밋된 트랜잭션 범위까지는 반영된다는 것을 의미한다.

Chunk 지향 프로세싱은 1000개의 데이터에 대해 배치 로직을 실행한다고 가정하면, Chunk 단위로 나누지 않았을 경우에는 한개만 실패해도 성공한 999개의 데이터가 롤백된다. Chunk 단위를 10으로 한다면, 작업 중에 다른 Chunk는 영향을 받지 않는다. 

- Reader에서 데이터 하나를 읽어 온다.(item 단위)
- 읽어온 데이터를 Processor에서 가공한다.(item 단위)
- 가공된 데이터들을 별도의 공간에 모은 뒤 Chunk 단위만큼 쌓이게 되면 Writer에 전달하고 Writer는 일괄 저장한다. (Chunk = items)

여기선 **Reader, Processor에서는 1건씩 다뤄지고, Writer에서는 Chunk 단위로 처리**된다는 것을 기억하면 된다.

## ChunkOrientedTasklet

```java
public class ChunkOrientedTasklet<I> implements Tasklet {
    private static final String INPUTS_KEY = "INPUTS";
    private final ChunkProcessor<I> chunkProcessor;
    private final ChunkProvider<I> chunkProvider;
    private boolean buffering = true;
    private static Log logger = LogFactory.getLog(ChunkOrientedTasklet.class);

    public ChunkOrientedTasklet(ChunkProvider<I> chunkProvider, ChunkProcessor<I> chunkProcessor) {
        this.chunkProvider = chunkProvider;
        this.chunkProcessor = chunkProcessor;
    }

    public void setBuffering(boolean buffering) {
        this.buffering = buffering;
    }

    @Nullable
    public RepeatStatus execute(StepContribution contribution, ChunkContext chunkContext) throws Exception {
        Chunk<I> inputs = (Chunk)chunkContext.getAttribute("INPUTS");
        if (inputs == null) {
          	// Reader에서 데이터 가져오기
            inputs = this.chunkProvider.provide(contribution);
            if (this.buffering) {
                chunkContext.setAttribute("INPUTS", inputs);
            }
        }


        this.chunkProcessor.process(contribution, inputs);      	// Processor & Writer 처리
        this.chunkProvider.postProcess(contribution, inputs);
        if (inputs.isBusy()) {
            logger.debug("Inputs still busy");
            return RepeatStatus.CONTINUABLE;
        } else {
            chunkContext.removeAttribute("INPUTS");
            chunkContext.setComplete();
            if (logger.isDebugEnabled()) {
                logger.debug("Inputs not busy, ended: " + inputs.isEnd());
            }

            return RepeatStatus.continueIf(!inputs.isEnd());
        }
    }
}
```

`ChunkOrientedTasklet`에서 Chunk 단위로 작업하기 위한 코드는 `execute()`에 있다.

- `this.chunkProvider.provide(contribution);` : Reaer에서 Chunk 크기만큼 데이터를 가져온다.
- `this.chunkProcessor.process(contribution, inputs);` Reader에서 받은 데이터를 가공하고 저장

## SimpleChunkProcessor

 `ChunkProcessor` 는 Processor와 Writer의 로직을 구현하고 있다.

```java
public interface ChunkProcessor<I> {
    void process(StepContribution var1, Chunk<I> var2) throws Exception;
}
```

`ChunkProcessor`는 인터페이스이기 때문에 실제 구현체가 있어야하며, 기본적으로 `SimpleChunkProcessor`가 사용된다.

```java
//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.springframework.batch.core.step.item;

import io.micrometer.core.instrument.Tag;
import io.micrometer.core.instrument.Timer.Sample;
import java.util.Iterator;
import java.util.List;
import org.springframework.batch.core.StepContribution;
import org.springframework.batch.core.StepExecution;
import org.springframework.batch.core.StepListener;
import org.springframework.batch.core.listener.MulticasterBatchListener;
import org.springframework.batch.core.metrics.BatchMetrics;
import org.springframework.batch.core.step.item.Chunk.ChunkIterator;
import org.springframework.batch.item.ItemProcessor;
import org.springframework.batch.item.ItemWriter;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.lang.Nullable;
import org.springframework.util.Assert;

public class SimpleChunkProcessor<I, O> implements ChunkProcessor<I>, InitializingBean {
    private ItemProcessor<? super I, ? extends O> itemProcessor;
    private ItemWriter<? super O> itemWriter;
    private final MulticasterBatchListener<I, O> listener;

		// ...
    protected final O doProcess(I item) throws Exception {
        if (this.itemProcessor == null) {
            return item;
        } else {
            try {
                this.listener.beforeProcess(item);
              	// ItemProcessor의 process()로 가공
                O result = this.itemProcessor.process(item);
                this.listener.afterProcess(item, result);
                return result;
            } catch (Exception var3) {
                this.listener.onProcessError(item, var3);
                throw var3;
            }
        }
    }
  
    protected final void doWrite(List<O> items) throws Exception {
        if (this.itemWriter != null) {
            try {
                this.listener.beforeWrite(items);
              	// 가공된 데이터들을 doWirte()로 일괄 처리
                this.writeItems(items);
                this.doAfterWrite(items);
            } catch (Exception var3) {
                this.doOnWriteError(var3, items);
                throw var3;
            }
        }
    }
  
    public final void process(StepContribution contribution, Chunk<I> inputs) throws Exception {
        this.initializeUserData(inputs);
        if (!this.isComplete(inputs)) {
          	// inputs는 이전에 `chunkProvider.privide()에서 받은 ChunkSize만큼 쌓인 item
            Chunk<O> outputs = this.transform(contribution, inputs);
            contribution.incrementFilterCount(this.getFilterCount(inputs, outputs));
          	// transform()을 통해 가공된 대량 데이터는 write()를 통해 일괄 저장된다.
          	// 이때 wirte()는 저장이 될 수도 있고, API 전송이 될 수도 있다. (ItemWriter 구현방식에 따라 다름)
            this.write(contribution, inputs, this.getAdjustedOutputs(inputs, outputs));
        }
    }

		// ...

    protected void write(StepContribution contribution, Chunk<I> inputs, Chunk<O> outputs) throws Exception {
        Sample sample = BatchMetrics.createTimerSample();
        String status = "SUCCESS";

        try {
            this.doWrite(outputs.getItems());
        } catch (Exception var10) {
            inputs.clear();
            status = "FAILURE";
            throw var10;
        } finally {
            this.stopTimer(sample, contribution.getStepExecution(), "chunk.write", status, "Chunk writing");
        }

        contribution.incrementWriteCount(outputs.size());
    }

  	// 전달받은 input을 doProcess()로 전달하고 변환 값을 받는다.
    protected Chunk<O> transform(StepContribution contribution, Chunk<I> inputs) throws Exception {
        Chunk<O> outputs = new Chunk();
        ChunkIterator iterator = inputs.iterator();

        while(iterator.hasNext()) {
            I item = iterator.next();
            Sample sample = BatchMetrics.createTimerSample();
            String status = "SUCCESS";

            Object output;
            try {
                output = this.doProcess(item);
            } catch (Exception var13) {
                inputs.clear();
                status = "FAILURE";
                throw var13;
            } finally {
                this.stopTimer(sample, contribution.getStepExecution(), "item.process", status, "Item processing");
            }

            if (output != null) {
                outputs.add(output);
            } else {
                iterator.remove();
            }
        }

        return outputs;
    }

}

```

여기서 Chunk 단위 처리를 담당하는 핵심 로직은 `process()`에 있다. 

## Page Size vs Chunk Size

**Chunk Size는 한번에 처리될 트랜잭션 단위**를 의미하며, **Page Size는 한번에 조회할  Item의 양을 의미**한다.

### AbstractPagingItemReader

```java
    @Nullable
    protected T doRead() throws Exception {
        synchronized(this.lock) {
         
            if (this.results == null || this.current >= this.pageSize) {
                if (this.logger.isDebugEnabled()) {
                    this.logger.debug("Reading page " + this.getPage());
                }

                this.doReadPage();
                ++this.page;
                if (this.current >= this.pageSize) {
                    this.current = 0;
                }
            }

            int next = this.current++;
            return next < this.results.size() ? this.results.get(next) : null;
        }
    }
```

현재 읽어올 데이터가 없거나, pageSize를 초과한 경우 `doReadPage()`를 호출하는 것을 볼 수 있다. 즉, Page 단위로 끊어서 호출하는 것을 볼 수 있다.



Page Size와 Chunk Size를 다르게 설정하는 경우의 예를 들어보자. 만약 PageSize가 10, Chunk Size가 50이라면, ItemReader에서 Page조회가 5번 일어나면 1번의 트랜잭션이 발생하여, Chunk가 처리될 것이다.

한번의 트랜잭션의 처리를 위해 5번의 쿼리 조회가 발생하는 것은 성능샹 이슈가 발생할 수 있다. Spring Batch에서는 다음과 같이 설명이 되어있다.

> Setting a fairly large page size and using a commit interval that matches the page size should provide better performance.
> (상당히 큰 페이지 크기를 설정하고 페이지 크기와 일치하는 커미트 간격을 사용하면 성능이 향상됩니다.)

추가적으로 JPA 사용시에도 `lazeException` 오류가 발생할 수 있다.

```java
org.hibernate.LazyInitializationException: failed to lazily initialize a collection of role: com.blogcode.example3.domain.PurchaseOrder.productList, could not initialize proxy - no Session
```

```java
public abstract class AbstractPagingItemReader<T> extends AbstractItemCountingItemStreamItemReader<T> implements InitializingBean {
    protected Log logger = LogFactory.getLog(this.getClass());
    private volatile boolean initialized = false;
    private int pageSize = 10;
```

`AbstractPagingItemReader`를 보면 pageSize의 default 크기는 10인 것을 확인할 수 있다.

```java

    protected void doReadPage() {
        EntityTransaction tx = null;
        if (this.transacted) {
            tx = this.entityManager.getTransaction();
            tx.begin();
            this.entityManager.flush();
            this.entityManager.clear();
        }

        Query query = this.createQuery().setFirstResult(this.getPage() * this.getPageSize()).setMaxResults(this.getPageSize());
        if (this.parameterValues != null) {
            Iterator var3 = this.parameterValues.entrySet().iterator();

            while(var3.hasNext()) {
                Entry<String, Object> me = (Entry)var3.next();
                query.setParameter((String)me.getKey(), me.getValue());
            }
        }

        if (this.results == null) {
            this.results = new CopyOnWriteArrayList();
        } else {
            this.results.clear();
        }

        if (!this.transacted) {
            List<T> queryResult = query.getResultList();
            Iterator var7 = queryResult.iterator();

            while(var7.hasNext()) {
                T entity = var7.next();
                this.entityManager.detach(entity);
                this.results.add(entity);
            }
        } else {
            this.results.addAll(query.getResultList());
            tx.commit();
        }

    }

```

그리고 `JpaPagingItemReader`의 `doReadPage()`를 보면 `this.entityManager.flush()`, `this.entityManager.clear()`로 이전 트랜잭션을 초기화 시키기때문에 만약 Chunk Size가 100, Page Size가 10이라면 마지막 조회를 제외한 9번의 조회결과들의 트랜잭션 세션이 전부 종료되어 오류가 발생하는 것을 볼 수 있다.

이 문제 또한, Page Size와 Chunk Size를 일치시키면 해결되는 것을 볼 수 있다.

2개의 값이 의미하는 바는 다르지만, 여러 이슈로 **2개 값을 일치 시키는 것이 보편적으로 좋은 방법이며, 2개 값을 일치 시키는 것을 권장**한다.

## 참고

- [기억보단 기록을 - Spring Batch에서 영속성 컨텍스트 문제 (processor에서 lazyException 발생할때) ](https://jojoldu.tistory.com/146)
- [기억보단 기록을 - 6. Spring Batch 가이드 - Chunk 지향 처리](https://jojoldu.tistory.com/331?category=902551)

