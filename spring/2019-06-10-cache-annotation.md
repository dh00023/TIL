# Cache

## 캐시(cache)란?

프로그램이 수행될 때 나타나는 지역성을 이용해 메모리나 디스크에서 사용되었던 내용을 빠르게 접근할 수 있는 곳에 보관하고 관리함으로써 두 번째 접근 부터는 보다 빠르게 참조하도록 하는 것이다.

> 하드디스크는 용량이 아주 크지만 속도가 느리고, 메인 메모리(RAM)의 용량은 1/100정도로 작지만 속도는 십만배 정도 빠르다. 캐시 메모리는 메인 메모리(RAM)의 1/100 정도 용량이지만 속도는 훨씬 빠르다. 

즉, **사용되었던 데이터는 다시 사용되어질 가능성이 높다는 개념** 을 이용하여, 다시 사용될 확률이 높은 것은 더 빠르게 접근 가능한 저장소를 사용한다는 개념이다.

![](./assets/2018-04-07-cache-memory-structure.png)

## 웹서버

![](./assets/2018-04-07-browser-caching.png)

웹에 요청을 날리면, 요청은 웹 브라우저로부터 하드 디스크의 파일 시스템에 있는 정적 리소스를 제공하는 웹 서버로 전달된다.

첫 번째 요청에서는 하드 디스크는 캐시를 확인하여 **캐시 미스( cache miss)**를 발생시킨다. 그리고 하드 드라이브로부터 데이터를 가져와 추후에 다시 요청 받을 수 있음을 가정하고 캐시에 저장한다.

이후 요청뿌터는 캐시 조회시 **캐시 히트(cache hit)**를 발생시킨다. 이 데이터는 캐시 미스를 일으키기 전까지 버퍼에서 제공된다.

> Cache Miss
>
> CPU가 참조하고자 하는 메모리가 캐시에 존재하지 않을 때
>
> Cache Hit
>
> CPU가 참조하고자 하는 메모리가 캐시에 존재할 때

### 데이터베이스 캐싱

데이터베이스 쿼리는 데이터베이스 서버에서 수행되기 때문에 속도가 느려지고 부하가 몰릴 수 있다. 결과값을 데이터베이스에 캐싱함으로써 응답 시간을 향상시킬 수 있다. 대다수의 머신이 동일한 데이터베이스에 동일한 쿼리를 사용하는 경우에 유용하다. 대다수의 데이터베이스 서버는 최적화된 캐싱을 위한 기능을 기본적으로 지원하며, 요구사항에 맞게 수정할 수 있는 파라미터들이 존재한다.

### 응답 캐싱

웹 서버의 응답은 메모리에 캐싱된다. 애플리케이션 캐시는 로컬 인메모리에 저장되거나 캐시 서버 위에서 실행되는 redis와 같은 인메모리 데이터베이스에 저장할 수 있다.

### HTTP 헤더를 통한 브라우저 캐싱

모든 브라우저는 HTML, JS, CSS, 이미지와 같은 파일들을 임시 저장을 위해 HTTP 캐시(웹 캐시)의 구현을 제공하고 있다. 서버 응답이 올바른 HTTP 헤더 지시자를 제공해 브라우저가 응답을 캐싱할 수 있는 시기와 지속 기간을 지시할 때 사용한다.

- 리소스가 로컬 캐시로부터 빠르게 로드되기 때문에 사용자 경험이 향상도니다.
- 애플리케이션 서버 및 파이프라인의 다른 구성요소에 대한 부하가 줄어든다.
- 불필요한 대역폭에 대한 지불비용이 줄어든다.



## redis란?

**RE**mote **DI**ctionary **S**erver의 약자로 대용량 처리 관련 기술이다.

- 메모리 위에서 동작하는 Key/value 저장소(Store)인 Redis는 
  **NoSQL DBMS**로 분류되며 동시에 Memcached와 같은 **인메모리(In-memory) 솔루션**으로 분리된다.

- 명시적으로 삭제, expire를 설정하지 않으면 데이터는 삭제되지 않는다.(영구 보존)
- 여러대의 서버 구성이 가능하다.

**인메모리 캐시(In-memory Cache)란?**

인 메모리 캐시는 모든 데이터를 메모리(RAM)에만 올려놓고 사용하는 데이터베이스의 일종이다. 일반적인 데이터베이스(RDBMS)는 디스크(HDD, SSD)에 데이터를 영구적으로 저장해놓고, 필요한 데이터만 메모리에 읽어서 사용한다.

디스크에 접근하지 않고 메모리로만 모든 처리를 하기 때문에 데이터 저장 및 검색 속도가 매우 빠르지만 데이터는 딱 메모리 크기(운영체제 사용량 제외)까지만 저장할 수 있다.

![](./assets/1.png)

## Spring Cache

Spring Caching Abstraction는 다른 캐시 솔루션을 Spring CacheManager를 통해서 쉽게 사용할 수 있도록 해준다. Spring Caching Abstraction는 **자바 메소드에 캐싱을 적용**하며, 메소드가 실행될 때 넘어온 **파라미터 값에 따라서 캐시**를 적용한다.

### 사용방법

```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-cache</artifactId>
</dependency>
```

메이븐에 다음과 같이 라이브러리를 추가한 후 `@EnableCaching` 어노테이션을 선언하게 되면 Spring Container에 빈이 등록된다. 기본적으로는 `ConcurrentMapCacheManager` 가 등록되며, 상황에 맞게 다른 캐시 구현체를 등록할 수 있다.

적용하고 싶은 메소드에 `@Cacheable` 어노테이션을 붙이면 적용된다.

### Cache Annotation

| 어노테이션     | 설명                             |
| :------------- | :------------------------------- |
| @Cacheable     | 메소드에 캐시 트리거 설정        |
| @CachePut      | 메소드 실행과 방해없이 캐시 갱신 |
| @CacheEvict    | 캐시되어있는 데이터 지우기       |
| @CacheConfig   | 캐시 관련 설정                   |
| @EnableCaching | 스프링 캐시활성화                |

#### Annotation 속성

| 어노테이션     | 설명                                                    |
| :------------- | :------------------------------------------------------ |
| value          | 캐시의 이름                                             |
| key            | 캐시할 키를 설정(기본설정하지 않으면 파라미터로 설정됨) |
| condition      | 특정 조건에 따라 캐시를 할지 않을지 결정                |
| cacheManager등 | 해당 캐시 매니저 설정가능                               |

- [https://goodgid.github.io/Redis/](https://goodgid.github.io/Redis/)

- [공식문서](https://docs.spring.io/spring/docs/3.2.x/spring-framework-reference/html/cache.html)