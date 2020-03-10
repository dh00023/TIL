# 01. 노드에 대해 알아보고 개발 도구 설치하기

## 01-1 노드란 무엇일까?

노드는 자바스크립트를 이용해 **서버**를 만들 수 있는 개발 도구이다.
하나의 요청 처리가 끝날 때까지 기다리지 않고 다른 요청을 동시에 처리할 수 있는 **비동기 입출력(Non-Blocking IO)**방식을 적용했다.


#### 동기 입출력(Blocking IO)

![](http://cfile4.uf.tistory.com/image/2371EC4955160B871447D2)

1. read함수를 호출하면, 커널 모드로 요청이 가고 입력을 기다린다.
2. 애플리케이션은 데이터 입력이 되기까지 다른 작업을 진행하지 않고 대기하게 된다.
3. 데이터가 입력되면, 커널 모드에서 유저모드로 데이터가 복사된다.

즉, 프로그램을 실행하는 중간중간 대기 시간이 발생하면서 속도가 느려지는 문제가 생긴다.

```js
var contents = file.read('a.txt');
// ---- 대기 ----
doShow(contents);
var result = doAdd(10,10);
```

#### 비동기 입출력(Non-Blocking IO)
![](http://cfile24.uf.tistory.com/image/253D9E475516150118BA1C)

프로그램에서 해당 파일의 내용을 처리할 수 있는 시점이 되면 **콜백 함수(Callback Fucntion)**가 호출된다. 파일 시스템은 파일 처리가 끝나면 자동으로 콜백 함수를 호출하기 때문에 프로그램이 파일 읽기 작업이 끝날 때까지 대기하지 않아도 된다.

> 자바스크립트에서는 변수에 함수를 할당할 수 있다. 따라서 변수에 할당된 함수를 다른 함수의 파라미터로 전달할 수 있는데 이렇게 파라미터로 전달된 함수를 다른 함수의 내부에서 호출하는 것이 콜백 함수이다.
> 
> [콜백 함수 참조페이지](http://yubylab.tistory.com/entry/%EC%9E%90%EB%B0%94%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8%EC%9D%98-%EC%BD%9C%EB%B0%B1%ED%95%A8%EC%88%98-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0)

```js
file.read('a.txt',function(contents){
	doShow(contents);
});
var result = doAdd(10,10);
```

[동기/비동기 입출력 참조페이지](https://www.joinc.co.kr/w/Site/Network_Programing/AdvancedComm/AIO)

#### 노드의 Architecture

![](http://cfile21.uf.tistory.com/image/247730485326FAE50E17EA)

이 아키텍처에서 가장 중요한 부분 중 하나가 이벤트를 받아 처리하는 기능이다. 특히 노드는 서버 쪽에서 동작하는 프로그램을 만드는 것이 주 임무이기 때문에 기본 기능인 소켓이나 HTTP프로토콜을 사용해 데이터를 송수신하는 기능을 포함하고 있다. 따라서 **데이터 송수신 부분에도 이벤트 처리 방식을 그대로 사용할 수 있다.**

```js
http.request(option, function(res){
	res.on('data',function(chunk){
    	console.log('BODY:'+chunk);
    });
});
```

http객체는 HTTP 프로토콜로 웹 서버에 데이터를 요청할 수 있는 기능이 있다. `request()`함수를 호출해 웹 서버에 데이터를 요청할 수 있고 응답을 받으면 콜백 함수가 자동으로 호출된다.
`on()`메소드를 사용해 이벤트를 콜백 함수와 **바인딩(Binding)**할 수 있다.

> 바인딩이란 서로 묶어서 연결해 준다는 의미이다.

#### 모듈(Module)

모듈은 메인이 되는 자바스크립트 파일의 일부 코드를 떼어 별도의 파일로 만든 것이다. 여러 프로그램에서 공통으로 사용하는 기능은 모듈로 분리하여 구성하는 것이 일반적이다. 또한 여러 개의 모듈을 합쳐서 하나의 패키지(npm으로 손쉽게 설치가능)로 만들 수 있다.


