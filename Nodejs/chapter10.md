# 10. 채팅 서버 만들기

노드에서 채팅 기능을 만들려면 **웹 소켓(Web Socket)**을 사용해야한다. 웹 소켓은 웹 서버로 소켓을 연결한 후 데이터를 주고받을 수 있도록 만든 HTML5표준이다. 이러한 웹 소켓은 HTTP 프로토콜로 소켓 연결을 하기 때문에 웹 브라우저가 이 기능을 지원하지 않으면 사용할 수 없다. **socket.io**모듈을 사용하면 웹 소켓을 지원하지 않는 웹 브라우저에서도 웹 소켓을 사용할 수 있다.

## 10-1 socket.io 사용하기

```
$ npm install socket.io --save
```
`socket.io`를 사용하려면 `cors`모듈도 설치되어 있어야한다. CORS(Corss-Origin Resource Sharing)를 사용하면 Ajax를 사용해 데이터를 가져올 때 현재 보고 있는 브라우저의 웹 문서를 제공한 웹 서버 이외에 다른 웹 서버에서는 접속할 수 없는 제약이 풀린다.

```
$ npm install cors --save
```

#### 프로젝트 구성
|파일 or 폴더 | 설명|
|------|-------|
|app.js|기본 코드가 들어 있는 메인 파일|
|/config/config.js|설정 정보가 들어 있는 파일<br>스키마 모듈이나 라우팅 모듈을 만들어 추가했다면 이 파일에 설정 정보를 추가|
|/database|데이터베이스의 스키마 모듈 파일들을 만들어 넣는 폴더|
|/routes|라우팅 함수들을 모듈 파일로 만들어 넣는 폴더|
|/views|뷰 템플릿 파일들을 만들어 넣는 폴더|

```js
//app.js
...

// socket.io 모듈 불러들이기
var socketio = require('socket.io');

// cors 사용 - 클라이언트에서 ajax로 요청하면 CORS 지원
var cors = require('cors');

...

//cors를 미들웨어로 사용하도록 등록
app.use(cors());

...

// socket.io 서버를 시작
var io = socketio.listen(server);
console.log("socket.io 요청을 받아들일 준비가 되었습니다.");
```

http모듈로 실행한 익스프레스 서버는 server변수에 저장되어 있으므로 그 아랫부분에서 socket.io모듈 객체의 `listen()`메소드를 호출한다.

####  socket.io모듈로 웹 소켓 요청 처리 메소드
|메소드 이름|설명|
|------|------|
|attach(httpServer,options)|웹 서버 인스턴스가 socket.io를 처리한다.|
|listen(httpServer,options)|웹 서버 인스턴스가 socket.io를 처리한다.|

socket.io 서버를 웹 서버 위에서 동작하도록 설정하면 웹 소켓과 관련된 요청은 모두 socket.io에서 처리한다. socket.io객체는 **io변수**에 할당되었는데 이 객체에 들어 있는 sockets객체는 클라이언트가 접속하거나 데이터를 전송했을 때 이벤트를 발생시킨다.

```js
...
//클라이언트가 연결했을 때의 이벤트 처리
io.sockets.on('connection',function(socket){
	console.log('connection info : ',socket.request.connection._peername);

	// 소켓 객체에 클라이언트 Host, Port 정보 속성으로 추가
	socket.remoteAddress = socket.request.connection._peername.address;
	socket.remotePort = socket.request.connection._peername.port;
});
```
`on()` 메소드로 connection 이벤트를 처리하는 콜백함수를 등록하면 콜백 함수 쪽으로 소켓 객체가 전달된다.

```xml
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>채팅 클라이언트 01</title>
		
		<script src="jquery-3.1.1.min.js"></script>      
		<script src="socket.io.js"></script>
        
        <script>
            var host;
            var port;
            var socket;
            
         	// 문서 로딩 후 실행됨
            $(function() {

				$("#connectButton").bind('click', function(event) {
					println('connectButton이 클릭되었습니다.');
					
                    host = $('#hostInput').val();
                    port = $('#portInput').val();

                    connectToServer();
                });

            });
            
			// 서버에 연결하는 함수 정의
            function connectToServer() {

                var options = {'forceNew':true};
                var url = 'http://' + host + ':' + port;
                socket = io.connect(url, options);

                socket.on('connect', function() {
                	println('웹소켓 서버에 연결되었습니다. : ' + url);
                });

                socket.on('disconnect', function() {
                    println('웹소켓 연결이 종료되었습니다.');
                });

            }
            
			function println(data) {
				console.log(data);
				$('#result').append('<p>' + data + '</p>');
			}
        </script>
	</head>
<body>
	<h3>채팅 클라이언트 01</h3>
	<br>
    <div>
        <input type="text" id="hostInput" value="localhost" />
        <input type="text" id="portInput" value="3000" />

        <input type="button" id="connectButton" value="연결하기" />
    </div>
        
    <hr/>
    <p>결과 : </p>
    <div id="result"></div>
        
</body>
</html>
```

socket.io는 메시지를 주고받을 때 **이벤트 처리 방식**을 사용한다.

#### 송수신 이벤트 처리 메소드

|메소드|설명|
|------|------|
|on(event,callback)|이벤트 수신 형태로 메시지를 수신했을 때 처리할 콜백 함수를 등록한다. 콜백 함수의 파라미터로 수신한 객체가 전달된다.|
|emit(event,object)|이벤트 송신 형태로 메시지를 송신한다.|

이벤트의 이름은 마음대로 정할 수 있다. 즉, **사용자 정의 이벤트**와 같다. **Echo**기능은 서버에 보낸 데이터를 그대로 다시 돌려받는 기능이다.

```js
socket.on('connect', function() {
   println('웹소켓 서버에 연결되었습니다. : ' + url);

   socket.on('message',function(message){
   console.log(JSON.stringify(message));

   println('<p>수신 메시지 : '+message.sender+','+message.recepient+','+ message.command+','+message.type+','+message.data+'</p>');
	});
});
```

- sender : 보내는 사람의 아이디
- recepient :  받는 사람의 아이디
- command : 데이터의 종류
- type : 전송될 데이터의 형태
- data : 데이터

#### 메세지 전송방법
|메소드|설명|
|------|------|
|io.sockets.emit(event,object)|나를 포함한 모든 클라이언트에 전송|
|socket.broadcast.emit(event,object)|나를 제외한 모든 클라이언트에 전송|
