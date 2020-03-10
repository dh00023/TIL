# 11. JSON-RPC 서버 만들기

## 11-1 JSON-RPC를 웹 서버에 적용하기

**RPC(Remote Procedure Call)**는 서버에 데이터를 요청해 응답받는 과정을 라이브러리에서 자동으로 처리한다. 단순히 로컬단말에서 함수를 호출하는 것처럼 코드를 만들기만 해도 클라이언트와 서버 간에 데이터를 주고받는 기능이 동작한다.

**JSON-RPC**는 JSON포맷으로 데이터를 주고받을 수 있어 자바스크립트를 사용하는 노드 프로그램에서 훨씬 자연스럽게 사용할 수 있다.

### JSON-RPC 모듈 설치하여 사용하기

서버와 데이터를 주고받는 기능은 RPC가 담당하기 때문에 개발자는 클라이언트에서 일반 함수를 사용하듯 서버에 데이터를 요청하기만 하면된다.

![](https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.progcomc/figures/A12C0bb01.jpg)

라이브러리에서는 **STUP**을 통해 서버로 요청을 보낸다. 필요한 데이터를 주고받을 때 사용하는 데이터 포맷은 **XML**,**바이너리 포맷**등이 있다.

[JSON-RPC 공식 사이트](http://www.jsonrpc.org)
[JSON-RPC Wiki 사이트](https://en.sikipedia.org/wiki/JSON-RPC)

JSON-RPC는 어떤 OS와 언어를 사용하든 서로 데이터를 주고 받을 수 있도록 다양한 언어로 작성된 라이브러리가 있다. 여기서는 **jayson모듈**을 사용한다.

```
$ npm install jayson --save
```

웹 서버로 요청하는 패스 중 한 가지 패스를 JSON-RPC로 실행하도록 만들 수 있다. 이러한 함수들을 보통 **Handler(핸들러)**라고 부른다.

```js
console.log("handler_info 파일 로딩됨");

var handler_info = [
	{file : './echo', method: 'echo'}
];

module.exports = handler_info;
```
file은 핸들러 모듈 파일의 이름이고 method는 등록한 핸들러의 이름이다.

### echo 함수 만들어 실행하기
**echo**핸들러는 클라이언트에서 보낸 데이터를 그대로 클라이언트로 다시 보내 주는 단순한 기능을 하는 함수이다.

```js
// echo 함수
var echo = function(params, callback) {
	console.log('JSON-RPC echo 호출됨.');
	console.dir(params);
	
	callback(null, params);
};

module.exports = echo;
```
첫번째 파라미터는 클라이언트로부터 전달받은 것이며 배열 객체로 되어있다. 두번째 파라미터는 함수로 클라이언트한테 응답을 보낼 때 사용한다.
클라이언트에서 보내 온 데이터를 그대로 다시 보낼 것이므로 **callback() **함수를 호출하면서 params객체를 그대로 넣어준다.

[jquery-jsonrpc 라이브러리](https://github.com/datagraph/jquery-jsonrpc)

#### `$.jsonRPC.request()` 속성

|속성|설명|
|------|------|
|id|요청 ID를 지정할 수 있다. 이 요청 ID는 서버로부터 받는 응답을 구별하는데 사용한다.|
|params|서버로 보낼 데이터를 넣는 배열 객체|
|success|응답을 성공적으로 받았을 때 호출되는 콜백 함수|
|error|오류 응답을 받았을 때 호출되는 콜백 함수|

#### 성공 응답을 받았을 때 전달되는 객체의 속성

|속성|설명|
|------|------|
|id|요청할 때 전달한 id 값이 들어 있다.|
|jsonrpc|JSON-RPC 스펙의 버전을 표기한다.|
|result|응답 데이터가 배열 객체로 들어있다.|

RPC와 기존 방식의 가장 큰 차이점은 서버에서 응답 받는 것이 웹 문서가 아니라 데이터라는 것이다.

### echo 함수의 오류 테스트하기

```js
// echo 에러 테스트 함수
var echo_error = function(params, callback) {
	console.log('JSON-RPC echo_error 호출됨.');
	console.dir(params);
	
	
	// 파라미터 체크
	if (params.length < 2) {  // 파라미터 부족
		callback({
            code: 400,
            message: 'Insufficient parameters'
        }, null);
		
		return;
	}
	
	var output = 'Success';
	callback(null, output);
};


module.exports = echo_error;
```
이 함수에서는 클라이언트에서 보내 온 데이터를 확인한다.