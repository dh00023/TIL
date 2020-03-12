# RestTemplate

*Spring 3.0 부터 지원*

HTTP 서버와의 통신을 단순화하고 RESTful 원칙을 지키는 HTTP 통신 template이다. RESTful 클라이언트는 HTTP Method(GET, POST, PUT, DELETE, HEAD, OPTIONS)를 모두 지원한다. 결과는 문자열 그대로 받을 수도 있으며, Converter를 이용해 Object로 변환할 수 있다.

- Synchronous API

- 기계적이고 반복적인 코드를 최대한 줄여준다.

RestTemplate은 `org.springframework.http.client` 패키지에 있으며, HttpClient 를 추상화해서 HttpEntity의 json, xml 등 제공해준다. 

## RestTemplate 동작 원리

![https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile26.uf.tistory.com%2Fimage%2F99300D335A9400A52C16C1](./assets/image.jpeg)

1. 어플리케이션이 `RestTemplate`을 생성하고, URI, HTTP Method 등의 header 담아 요청

2. `RestTemplate` 은 `HttpMessageConverter` 를 사용하여 `requestEntity` 를 요청메세지로 변환

3. `RestTemplate` 은 `ClientHttpRequestFactory` 로 부터 `ClientHttpRequest` 를 가져와 요청
4. `ClientHttpRequest` 는 요청메세지를 만들어 HTTP 프로토콜을 통해 서버와 통신

5. `RestTemplate` 는` ResponseErrorHandler` 로 오류를 확인

6. `ResponseErrorHandler` 는 오류가 있다면 `ClientHttpResponse` 에서 응답데이터를 가져와서 처리

7. `RestTemplate` 는 `HttpMessageConverter` 를 이용해 응답메세지를 java object(Class responseType) 로 변환



## Method

| Method          | HTTP    | 설명                                                      |
| :-------------- | :------ | :-------------------------------------------------------- |
| exchange        | any     | **HTTP header** setting 가능, ResponseEntity로 반환       |
| execute         | any     | Request/Response 콜백을 수정 가능                         |
| getForObject    | GET     | Java Object로 반환                                        |
| getForEntity    | GET     | ResponseEntity로 반환                                     |
| postForLocation | POST    | java.net.URI 로 반환                                      |
| postForObject   | POST    | Java Object로 반환                                        |
| postForEntity   | POST    | ResponseEntity로 반환                                     |
| delete          | DELETE  | HTTP DELETE 메서드를 실행                                 |
| headForHeaders  | HEAD    | 헤더의 모든 정보를 얻을 수 있으면 HTTP HEAD 메서드를 사용 |
| put             | PUT     | HTTP PUT 메서드를 실행                                    |
| patchForObject  | PATCH   | HTTP PATCH 메서드를 실행                                  |
| optionsForAllow | OPTIONS | 주어진 URL 주소에서 지원하는 HTTP 메서드를 조회           |

## 예제

그 중에 HTTP header를 설정할 수 있는 `exchange` 에 대해서 자세히 알아볼 것이다.

```java
// Header 설정
final HttpHeaders headers = new HttpHeaders();
headers.setContentType(MediaType.APPLICATION_JSON); // application/json
headers.set("apikey", "apikeyvalue"); 							// API에 따라 key 값을 설정
```

다음과 같이 `HttpHeaders` 로 header 값들을 설정할 수 있다. headers는 `HttpEntity`에 보내줄 파라미터와 함께 설정해준다.

`UricomponentsBuilder` 는 여러개의 파라미터를 연결해 하나의 URI로 만들어 반환해준다.

```java
// example : https://example.api.com/m/item?channelCode=30001001&count=3
UriComponentsBuilder builder = UriComponentsBuilder.fromHttpUrl("https://example.api.com");
builder.path("/m/item")
  		 .queryParam("channelCode", "30001001")
  		 .queryParam("count", 3);

String apiUrl = builder.build().encode().toUriString();
```

requestBody 값으로 보내줄 파라미터들은 `Map<>` 으로 각자 데이터 형태에 맞게 생성해준다.

```java
// ajax 통신시 data에 들어가는 값
Map<String, Object> requestBody = new HashMap<String, Object>();
requestBody.put("category_type", categoryType);
```

이제 `HttpEntity` 에 headers와 requestBody 객체를 담아준다.

```java
HttpEntity<Map<String, Object>> sendData = new HttpEntity<>(requestBody, headers);
```

만약 timeout을 설정하려면 `HttpComponentsClientHttpRequestFactory` 객체를 생성해 설정할 수 있다.

```java
HttpComponentsClientHttpRequestFactory factory = new HttpComponentsClientHttpRequestFactory();
factory.setConnectTimeout(3000); // 3초
factory.setReadTimeout(3000); // 3초
```

`RestTemplate` 으로 이제 HTTP 통신을 할 수 있다.

```java
RestTemplate restTemplate = new RestTemplate();
restTemplate.setRequestFactory(factory);	// timeout 설정

ResponseEntity<Map> response = restTemplate.exchange(apiUrl, HttpMethod.POST, sendData, Map.class);
```

## 참조 페이지

- [공식문서](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/client/RestTemplate.html) 
- [빨간색코딩]( https://sjh836.tistory.com/141)
- [Frank's blog](https://blog.advenoh.pe.kr/spring/스프링-RestTemplate/)
- [코딩32](https://vmpo.tistory.com/27)



