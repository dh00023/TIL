# 04. 노드의 기본 기능 알아보기

## 04-1 주소 문자열과 요청 파라미터 다루기

웹 사이트에 접속하기 위한 사이트 주소 정보는 노드에서 **URL 객체**로 만들 수 있다.
**url 모듈**은 일반 주소 문자열을 URL 객체로 만드는 것을 쉽게 해준다.

#### 주소 문자열을 URL 객체로 변환하기

|메소드|설명|
|------|------|
|parse()|주소 문자열을 파싱하여 URL 객체를 만들어 준다.|
|format()|URL 객체를 주소 문자열로 변환한다.|

```js
// require() 메소드를 이용해 url모듈을 사용했다.
var url = require('url');

// 주소 문자열 url객체로 만들기
var curURL = url.parse('https://search.naver.com/search.naver?where=nexearch&sm=top_sug.pre&fbm=1&acr=1&acq=steve&qdt=0&ie=utf8&query=steve+jobs');

//url 객체를 주소 문자열로 만들기
var curStr = url.format(curURL);

console.log('%s',curStr);
console.dir(curURL)
```
결과창을 보면 query속성은 요청 파라미터 정보를 가지고 있다. 웹 서버에서는 클라이언트에서 요청한 요청 파라미터를 받아 처리할 때가 많으므로 이 query 속성에 들어 있는 문자열을 다시 각각의 요청 파라미터로 분리해야한다.
```
  query: 'where=nexearch&sm=top_sug.pre&fbm=1&acr=1&acq=steve&qdt=0&ie=utf8&query=steve+jobs',
```

**querystring 모듈**을 이용하면 요청 파라미터를 쉽게 분리할 수 있다.

|메소드|설명|
|------|------|
|parse()|요청 파라미터 문자열을 파싱하여 요청 파라미터 객체로 만들어준다.|
|stringify()|요청 파라미터 객체를 문자열로 변환|

## 04-2 이벤트 이해하기

노드에는 이벤트를 보내고 받을 수 있도록 **EventEmitter**라는 것이 만들어져 있습니다.

> 이벤트는 한쪽에서 다른 쪽으로 어떤 일이 발생했음을 알려주는 것이다. 이때 다른 쪽에서 이 이벤트를 받고 싶다면 **Event Listener**를 등록할 수있다. 이벤트 리스너는 특정 이벤트가 전달되었을때 그 이벤트를 처리할 수 있도록 만들어 둔것을 말한다.

### 이벤트 보내고 받기

- 노드의 객체는 EventEmitter를 상속받을 수 있다.
- 상속받은 후에는 EventEmitter 객체의 `on()`과 `emit()`메소드를 사용할 수 있다.

보통은 노드 내부에서 미리 만들어 제공하는 이벤트를 받아 처리하지만, 필요할 때는 직접 이벤트를 만들어 전달할 수 있다.

|메소드|설명|
|------|-------|
|on(event,listener)|지정한 이벤트의 리스너를 추가|
|once(event,listener)|지정한 이벤트의 리스너를 추가하지만 한 번 실행한 후 자동으로 제거|
|removeListener(event,listener)|지정한 이벤트에 대한 리스너 제거|

```js
process.on('exit',function(){
	console.log('exit 이벤트 발생');
});

setTimeout(function(){
	console.log('2초 후에 시스템 종료 시도');

	process.exit();
},2000);
```
`process` 객체는 노드에서 언제든지 사용할 수 있는 객체인데, 내부적으로 EventEmitter를 상속받도록 만들어져있다.

## 04-3 파일 다루기

## 04-4 로그 파일 남기기