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

## 10-2 일대일 채팅하기

일대일 채팅은 상대방을 지정하여 메시지를 보내야 하므로 서버에 연결된 각 클라이언트마다 고유한 정보가 있어야한다. 클라이언트가 로그인할 때 사용하는 로그인 아이디를 사용해 클라이언트를 구별할 수 있도록 하는 것이 좋다.

```xml
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>채팅 클라이언트 03</title>
        
        <script src="jquery-3.1.1.min.js"></script>    
        <script src="socket.io.js"></script>
        
        <script>
            var host;
            var port;
            var socket;
            
            // 문서 로딩 후 실행됨
            $(function() {

                // 연결하기 버튼 클릭 처리
                $("#connectButton").bind('click', function(event) {
                    println('connectButton이 클릭되었습니다.');
                    
                    host = $('#hostInput').val();
                    port = $('#portInput').val();

                    connectToServer();
                });

                // 전송 버튼 클릭 시 처리
                $("#sendButton").bind('click', function(event) {
                    var sender = $('#senderInput').val();
                    var recepient = $('#recepientInput').val();
                    var data = $('#dataInput').val();

                    var output = {sender:sender, recepient:recepient, command:'chat', type:'text', data:data};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('message', output);
                });

                // 로그인 버튼 클릭 시 처리
                $("#loginButton").bind('click', function(event) {
                    var id = $('#idInput').val();
                    var password = $('#passwordInput').val();
                    var alias = $('#aliasInput').val();
                    var today = $('#todayInput').val();

                    var output = {id:id, password:password, alias:alias, today:today};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('login', output);
                });

            });
            
            // 서버에 연결하는 함수 정의
            function connectToServer() {

                var options = {'forceNew':true};
                var url = 'http://' + host + ':' + port;
                socket = io.connect(url, options);

                socket.on('connect', function() {
                    println('웹소켓 서버에 연결되었습니다. : ' + url);

                    socket.on('message', function(message) {
                        console.log(JSON.stringify(message));

                        println('<p>수신 메시지 : ' + message.sender + ', ' + message.recepient + ', ' + message.command + ', ' + message.data + '</p>');
                    });

                    socket.on('response', function(response) {
                        console.log(JSON.stringify(response));
                        println('응답 메시지를 받았습니다. : ' + response.command + ', ' + response.code + ', ' + response.message);
                    });
                    
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
    <h3>채팅 클라이언트 03 : 일대일 채팅하기</h3>
    <br>
    <div>
        <input type="text" id="hostInput" value="localhost" />
        <input type="text" id="portInput" value="3000" />

        <input type="button" id="connectButton" value="연결하기" />
    </div>
    <br>
    <div>
        <input type="text" id="idInput" value="test01" />
        <input type="password" id="passwordInput" value="123456" />
        <input type="text" id="aliasInput" value="소녀시대" />
        <input type="text" id="todayInput" value="좋은 날!" />

        <input type="button" id="loginButton" value="로그인" />
        <input type="button" id="logoutButton" value="로그아웃" />
    </div>
    <br>
    <div>
        <div><span>보내는사람 아이디 :</span> <input type="text" id="senderInput" value="test01" /></div>
        <div><span>받는사람 아이디 :</span> <input type="text" id="recepientInput" value="ALL" /></div>
        <div><span>메시지 데이터 :</span> <input type="text" id="dataInput" value="안녕!"/> </div>
        <br>
        <input type="button" id="sendButton" value="전송" />
    </div>    
        
    <hr/>
    <p>결과 : </p>
    <div id="result"></div>
        
</body>
</html>
```

```js
// Express 기본 모듈 불러오기
var express = require('express')
  , http = require('http')
  , path = require('path');

// Express의 미들웨어 불러오기
var bodyParser = require('body-parser')
  , cookieParser = require('cookie-parser')
  , static = require('serve-static')
  , errorHandler = require('errorhandler');

// 에러 핸들러 모듈 사용
var expressErrorHandler = require('express-error-handler');

// Session 미들웨어 불러오기
var expressSession = require('express-session');
  

//===== Passport 사용 =====//
var passport = require('passport');
var flash = require('connect-flash');


// 모듈로 분리한 설정 파일 불러오기
var config = require('./config/config');

// 모듈로 분리한 데이터베이스 파일 불러오기
var database = require('./database/database');

// 모듈로 분리한 라우팅 파일 불러오기
var route_loader = require('./routes/route_loader');

 

// Socket.IO 사용
var socketio = require('socket.io');

// cors 사용 - 클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
var cors = require('cors');



// 익스프레스 객체 생성
var app = express();


//===== 뷰 엔진 설정 =====//
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
console.log('뷰 엔진이 ejs로 설정되었습니다.');


//===== 서버 변수 설정 및 static으로 public 폴더 설정  =====//
console.log('config.server_port : %d', config.server_port);
app.set('port', process.env.PORT || 3000);
 

// body-parser를 이용해 application/x-www-form-urlencoded 파싱
app.use(bodyParser.urlencoded({ extended: false }))

// body-parser를 이용해 application/json 파싱
app.use(bodyParser.json())

// public 폴더를 static으로 오픈
app.use('/public', static(path.join(__dirname, 'public')));
 
// cookie-parser 설정
app.use(cookieParser());

// 세션 설정
app.use(expressSession({
  secret:'my key',
  resave:true,
  saveUninitialized:true
}));



//===== Passport 사용 설정 =====//
// Passport의 세션을 사용할 때는 그 전에 Express의 세션을 사용하는 코드가 있어야 함
app.use(passport.initialize());
app.use(passport.session());
app.use(flash());
 

//클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
app.use(cors());



//라우팅 정보를 읽어들여 라우팅 설정
var router = express.Router();
route_loader.init(app, router);


// 패스포트 설정
var configPassport = require('./config/passport');
configPassport(app, passport);

// 패스포트 라우팅 설정
var userPassport = require('./routes/user_passport');
userPassport(router, passport);



//===== 404 에러 페이지 처리 =====//
var errorHandler = expressErrorHandler({
 static: {
   '404': './public/404.html'
 }
});

app.use( expressErrorHandler.httpError(404) );
app.use( errorHandler );


//===== 서버 시작 =====//

//확인되지 않은 예외 처리 - 서버 프로세스 종료하지 않고 유지함
process.on('uncaughtException', function (err) {
  console.log('uncaughtException 발생함 : ' + err);
  console.log('서버 프로세스 종료하지 않고 유지함.');
  
  console.log(err.stack);
});

// 프로세스 종료 시에 데이터베이스 연결 해제
process.on('SIGTERM', function () {
    console.log("프로세스가 종료됩니다.");
    app.close();
});

app.on('close', function () {
  console.log("Express 서버 객체가 종료됩니다.");
  if (database.db) {
    database.db.close();
  }
});

// 시작된 서버 객체를 리턴받도록 합니다. 
var server = http.createServer(app).listen(app.get('port'), function(){
  console.log('서버가 시작되었습니다. 포트 : ' + app.get('port'));

  // 데이터베이스 초기화
  database.init(app, config);
   
});


//===== Socket.IO를 이용한 채팅 테스트 부분 =====//


// 로그인 아이디 매핑 (로그인 ID -> 소켓 ID)
var login_ids = {};


// socket.io 서버를 시작합니다.
var io = socketio.listen(server);
console.log('socket.io 요청을 받아들일 준비가 되었습니다.');

// 클라이언트가 연결했을 때의 이벤트 처리
io.sockets.on('connection', function(socket) {
  console.log('connection info :', socket.request.connection._peername);

    // 소켓 객체에 클라이언트 Host, Port 정보 속성으로 추가
    socket.remoteAddress = socket.request.connection._peername.address;
    socket.remotePort = socket.request.connection._peername.port;
    

    // 'login' 이벤트를 받았을 때의 처리
    socket.on('login', function(login) {
      console.log('login 이벤트를 받았습니다.');
      console.dir(login);

        // 기존 클라이언트 ID가 없으면 클라이언트 ID를 맵에 추가
        console.log('접속한 소켓의 ID : ' + socket.id);
        login_ids[login.id] = socket.id;
        socket.login_id = login.id;

        console.log('접속한 클라이언트 ID 갯수 : %d', Object.keys(login_ids).length);

        // 응답 메시지 전송
        sendResponse(socket, 'login', '200', '로그인되었습니다.');
    });

    
    // 'message' 이벤트를 받았을 때의 처리
    socket.on('message', function(message) {
      console.log('message 이벤트를 받았습니다.');
      console.dir(message);
      
        if (message.recepient =='ALL') {
            // 나를 포함한 모든 클라이언트에게 메시지 전달
          console.dir('나를 포함한 모든 클라이언트에게 message 이벤트를 전송합니다.')
            io.sockets.emit('message', message);
        } else {
          // 일대일 채팅 대상에게 메시지 전달
          if (login_ids[message.recepient]) {
            io.sockets.connected[login_ids[message.recepient]].emit('message', message);
            
            // 응답 메시지 전송
            sendResponse(socket, 'message', '200', '메시지를 전송했습니다.');
          } else {
            // 응답 메시지 전송
            sendResponse(socket, 'login', '404', '상대방의 로그인 ID를 찾을 수 없습니다.');
          }
        }
    });
    
});


// 응답 메시지 전송 메소드
function sendResponse(socket, command, code, message) {
  var statusObj = {command: command, code: code, message: message};
  socket.emit('response', statusObj);
}
```

대상 소켓을 찾기위해서는 `io.sockets.connected[login_ids[messagae.recepient]]`를 사용해야한다.

배열의 요소는 `delete`키워드나 배열의 `splice()`메소드등을 이용해 여러가지 방법을 사용할 수 있다.

## 10-3 그룹 채팅하기

그룹 채팅은 방을 만들고 그 방에 초대된 사람끼리 동시에 메시지를 주고받는다.

### 방만들기

socket.io모듈은 몇 명의 사용자를 하나으 ㅣ방에 모아 두고 방에 들어온 특정 클라이언트에만 메시지를 전송할 수 있는 기능을 제공한다.
```xml
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>채팅 클라이언트 04</title>
		
		<script src="jquery-3.1.1.min.js"></script>     
		<script src="socket.io.js"></script>
        
        <script>
            var host;
            var port;
            var socket;
            
         	// 문서 로딩 후 실행됨
            $(function() {

            	// 연결하기 버튼 클릭 처리
				$("#connectButton").bind('click', function(event) {
					println('connectButton이 클릭되었습니다.');
					
                    host = $('#hostInput').val();
                    port = $('#portInput').val();

                    connectToServer();
                });

				// 전송 버튼 클릭 시 처리
                $("#sendButton").bind('click', function(event) {
                    var sender = $('#senderInput').val();
                    var recepient = $('#recepientInput').val();
                    var data = $('#dataInput').val();

                    var output = {sender:sender, recepient:recepient, command:'chat', type:'text', data:data};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('message', output);
                });

				// 로그인 버튼 클릭 시 처리
                $("#loginButton").bind('click', function(event) {
                    var id = $('#idInput').val();
                    var password = $('#passwordInput').val();
                    var alias = $('#aliasInput').val();
                    var today = $('#todayInput').val();

                    var output = {id:id, password:password, alias:alias, today:today};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('login', output);
                });
				
             	// 방만들기 버튼 클릭 시 처리
                $("#createRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    var roomName = $('#roomNameInput').val();
                    var id = $('#idInput').val();
                    
                    var output = {command:'create', roomId:roomId, roomName:roomName, roomOwner:id};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });
             	
             	// 방이름바꾸기 버튼 클릭 시 처리
                $("#updateRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    var roomName = $('#roomNameInput').val();
                    var id = $('#idInput').val();
                    
                    var output = {command:'update', roomId:roomId, roomName:roomName, roomOwner:id};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });

             	// 방없애기 버튼 클릭 시 처리
                $("#deleteRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    
                    var output = {command:'delete', roomId:roomId};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });

            });
            
			// 서버에 연결하는 함수 정의
            function connectToServer() {

                var options = {'forceNew':true};
                var url = 'http://' + host + ':' + port;
                socket = io.connect(url, options);

                socket.on('connect', function() {
                	println('웹소켓 서버에 연결되었습니다. : ' + url);

                    socket.on('message', function(message) {
                        console.log(JSON.stringify(message));

                        println('<p>수신 메시지 : ' + message.sender + ', ' + message.recepient + ', ' + message.command + ', ' + message.data + '</p>');
                    });

                    socket.on('response', function(response) {
                    	console.log(JSON.stringify(response));
                    	println('응답 메시지를 받았습니다. : ' + response.command + ', ' + response.code + ', ' + response.message);
                    });

                    // 그룹 채팅에서 방과 관련된 이벤트 처리
                    socket.on('room', function(data) {
                        console.log(JSON.stringify(data));

                        println('<p>방 이벤트 : ' + data.command + '</p>');
                        println('<p>방 리스트를 받았습니다.</p>');
                        if (data.command == 'list') { // 방 리스트
                        	var roomCount = data.rooms.length;
                        	$("#roomList").html('<p>방 리스트 ' + roomCount + '개</p>');
                        	for (var i = 0; i < roomCount; i++) {
                        		$("#roomList").append('<p>방 #' + i + ' : ' + data.rooms[i].id + ', ' + data.rooms[i].name + ', ' + data.rooms[i].owner + '</p>');
                        	}
                        }
                    });

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
	<h3>채팅 클라이언트 04 : 그룹 채팅하기</h3>
	<br>
    <div>
        <input type="text" id="hostInput" value="localhost" />
        <input type="text" id="portInput" value="3000" />

        <input type="button" id="connectButton" value="연결하기" />
    </div>
    <br>
    <div>
		<input type="text" id="idInput" value="test01" />
		<input type="password" id="passwordInput" value="123456" />
		<input type="text" id="aliasInput" value="소녀시대" />
		<input type="text" id="todayInput" value="좋은 날!" />

		<input type="button" id="loginButton" value="로그인" />
		<input type="button" id="logoutButton" value="로그아웃" />
	</div>
    <br>
    <div>
		<input type="text" id="roomIdInput" value="meeting01" />
		<input type="text" id="roomNameInput" value="청춘들의대화" />

		<input type="button" id="createRoomButton" value="방만들기" />
		<input type="button" id="updateRoomButton" value="방이름바꾸기" />
		<input type="button" id="deleteRoomButton" value="방없애기" />
	</div>
	<br>
	<div id="roomList">
		
	</div>
    <br>
    <div>
    	<div><span>보내는사람 아이디 :</span> <input type="text" id="senderInput" value="test01" /></div>
	    <div><span>받는사람 아이디 :</span> <input type="text" id="recepientInput" value="ALL" /></div>
	    <!-- command 선택 <select> 채팅, 그룹채팅 -->
	    <div><span>메시지 데이터 :</span> <input type="text" id="dataInput" value="안녕!"/> </div>
		<br>
		<input type="button" id="sendButton" value="전송" />
	</div>    
        
    <hr/>
    <p>결과 : </p>
    <div id="result"></div>
        
</body>
</html>
```
클라이언트에서는 만든 방의 리스트만 전달받는다.

```js
// Express 기본 모듈 불러오기
var express = require('express')
  , http = require('http')
  , path = require('path');

// Express의 미들웨어 불러오기
var bodyParser = require('body-parser')
  , cookieParser = require('cookie-parser')
  , static = require('serve-static')
  , errorHandler = require('errorhandler');

// 에러 핸들러 모듈 사용
var expressErrorHandler = require('express-error-handler');

// Session 미들웨어 불러오기
var expressSession = require('express-session');
  

//===== Passport 사용 =====//
var passport = require('passport');
var flash = require('connect-flash');


// 모듈로 분리한 설정 파일 불러오기
var config = require('./config/config');

// 모듈로 분리한 데이터베이스 파일 불러오기
var database = require('./database/database');

// 모듈로 분리한 라우팅 파일 불러오기
var route_loader = require('./routes/route_loader');

 

// Socket.IO 사용
var socketio = require('socket.io');

// cors 사용 - 클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
var cors = require('cors');



// 익스프레스 객체 생성
var app = express();


//===== 뷰 엔진 설정 =====//
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
console.log('뷰 엔진이 ejs로 설정되었습니다.');


//===== 서버 변수 설정 및 static으로 public 폴더 설정  =====//
console.log('config.server_port : %d', config.server_port);
app.set('port', process.env.PORT || 3000);
 

// body-parser를 이용해 application/x-www-form-urlencoded 파싱
app.use(bodyParser.urlencoded({ extended: false }))

// body-parser를 이용해 application/json 파싱
app.use(bodyParser.json())

// public 폴더를 static으로 오픈
app.use('/public', static(path.join(__dirname, 'public')));
 
// cookie-parser 설정
app.use(cookieParser());

// 세션 설정
app.use(expressSession({
  secret:'my key',
  resave:true,
  saveUninitialized:true
}));



//===== Passport 사용 설정 =====//
// Passport의 세션을 사용할 때는 그 전에 Express의 세션을 사용하는 코드가 있어야 함
app.use(passport.initialize());
app.use(passport.session());
app.use(flash());
 

//클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
app.use(cors());



//라우팅 정보를 읽어들여 라우팅 설정
var router = express.Router();
route_loader.init(app, router);


// 패스포트 설정
var configPassport = require('./config/passport');
configPassport(app, passport);

// 패스포트 라우팅 설정
var userPassport = require('./routes/user_passport');
userPassport(router, passport);



//===== 404 에러 페이지 처리 =====//
var errorHandler = expressErrorHandler({
 static: {
   '404': './public/404.html'
 }
});

app.use( expressErrorHandler.httpError(404) );
app.use( errorHandler );


//===== 서버 시작 =====//

//확인되지 않은 예외 처리 - 서버 프로세스 종료하지 않고 유지함
process.on('uncaughtException', function (err) {
  console.log('uncaughtException 발생함 : ' + err);
  console.log('서버 프로세스 종료하지 않고 유지함.');
  
  console.log(err.stack);
});

// 프로세스 종료 시에 데이터베이스 연결 해제
process.on('SIGTERM', function () {
    console.log("프로세스가 종료됩니다.");
    app.close();
});

app.on('close', function () {
  console.log("Express 서버 객체가 종료됩니다.");
  if (database.db) {
    database.db.close();
  }
});

// 시작된 서버 객체를 리턴받도록 합니다. 
var server = http.createServer(app).listen(app.get('port'), function(){
  console.log('서버가 시작되었습니다. 포트 : ' + app.get('port'));

  // 데이터베이스 초기화
  database.init(app, config);
   
});


//===== Socket.IO를 이용한 채팅 테스트 부분 =====//


// 로그인 아이디 매핑 (로그인 ID -> 소켓 ID)
var login_ids = {};


// socket.io 서버를 시작합니다.
var io = socketio.listen(server);
console.log('socket.io 요청을 받아들일 준비가 되었습니다.');

// 클라이언트가 연결했을 때의 이벤트 처리
io.sockets.on('connection', function(socket) {
  console.log('connection info :', socket.request.connection._peername);

    // 소켓 객체에 클라이언트 Host, Port 정보 속성으로 추가
    socket.remoteAddress = socket.request.connection._peername.address;
    socket.remotePort = socket.request.connection._peername.port;
    

    // 'login' 이벤트를 받았을 때의 처리
    socket.on('login', function(login) {
      console.log('login 이벤트를 받았습니다.');
      console.dir(login);

        // 기존 클라이언트 ID가 없으면 클라이언트 ID를 맵에 추가
        console.log('접속한 소켓의 ID : ' + socket.id);
        login_ids[login.id] = socket.id;
        socket.login_id = login.id;

        console.log('접속한 클라이언트 ID 갯수 : %d', Object.keys(login_ids).length);

        // 응답 메시지 전송
        sendResponse(socket, 'login', '200', '로그인되었습니다.');
    });

    
    // 'message' 이벤트를 받았을 때의 처리
    socket.on('message', function(message) {
      console.log('message 이벤트를 받았습니다.');
      console.dir(message);
      
        if (message.recepient =='ALL') {
            // 나를 포함한 모든 클라이언트에게 메시지 전달
          console.dir('나를 포함한 모든 클라이언트에게 message 이벤트를 전송합니다.')
            io.sockets.emit('message', message);
        } else {
          // 일대일 채팅 대상에게 메시지 전달
          if (login_ids[message.recepient]) {
            io.sockets.connected[login_ids[message.recepient]].emit('message', message);
            
            // 응답 메시지 전송
            sendResponse(socket, 'message', '200', '메시지를 전송했습니다.');
          } else {
            // 응답 메시지 전송
            sendResponse(socket, 'login', '404', '상대방의 로그인 ID를 찾을 수 없습니다.');
          }
        }
    });

    // room 이벤트를 받았을 때의 처리
    socket.on('room',function(room){
    	console.log("room 이벤트를 받았습니다.");
    	console.dir(room);

    	if(room.command == 'create'){
    		if(io.sockets.adapter.rooms[room.roomId]){//방이 이미 만들어져 있는경우
    			console.log("방이 이미 만들어져 있습니다.");
    		}else{
    			console.log("방을 새로 만듭니다.");

    			socket.join(room.roomId);

    			var curRoom = io.sockets.adapter.rooms[room.roomId];
    			curRoom.id = room.roomId;
    			curRoom.name = room.roomName;
    			curRoom.owner = room.roomOwner;
    		}
    	}else if(room.command == 'update'){
    		var curRoom = io.sockets.adapter.rooms[room.roomId];
    			curRoom.id = room.roomId;
    			curRoom.name = room.roomName;
    			curRoom.owner = room.roomOwner;
    	}else if (room.command == 'delete') {
    		socket.leave(room.roomId);

    		if(io.sockets.adapter.rooms[room.roomId]){//방이 만들어져 있는 경우
    			delete io.sockets.adapter.rooms[room.roomId];
    		}else{
    			console.log("방이 만들어져 있지 않습니다.");
    		}
    	}

    	var roomList = getRoomList();

    	var output = {command : 'list',rooms: roomList};
    	console.log("클라이언트로 보낼 데이터 : "+JSON.stringify(output));

    	io.sockets.emit('room',output);
    });
    
});

function getRoomList() {
	console.dir(io.sockets.adapter.rooms);
	
    var roomList = [];
    
    Object.keys(io.sockets.adapter.rooms).forEach(function(roomId) { // for each room
    	console.log('current room id : ' + roomId);
    	var outRoom = io.sockets.adapter.rooms[roomId];
    	
    	// find default room using all attributes
    	var foundDefault = false;
    	var index = 0;
        Object.keys(outRoom.sockets).forEach(function(key) {
        	console.log('#' + index + ' : ' + key + ', ' + outRoom.sockets[key]);
        	
        	if (roomId == key) {  // default room
        		foundDefault = true;
        		console.log('this is default room.');
        	}
        	index++;
        });
        
        if (!foundDefault) {
        	roomList.push(outRoom);
        }
    });
    
    console.log('[ROOM LIST]');
    console.dir(roomList);
    
    return roomList;
}

// 응답 메시지 전송 메소드
function sendResponse(socket, command, code, message) {
  var statusObj = {command: command, code: code, message: message};
  socket.emit('response', statusObj);
}
```

#### 방에 입장 / 퇴장 메소드
|메소드|설명|
|------|------|
|join(roomName)|방에 입장한다. 방이 없으면 방을 새로 만든다.|
|leave(roomName)|방에서 나온다.|


socket.io 모듈에서 방정보를 관리하고 있다. 방 객체에 속성을 추가하는 것도 가능하다. 방 정보는 `io.sockets.adapter.rooms`에 들어있다.
`getRoomList()`는 처음부터 만들어져 있던 방이다.

### 그룹 채팅에서 메시지 보내기

```xml
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>채팅 클라이언트 05</title>
        
        <script src="jquery-3.1.1.min.js"></script>     
        <script src="socket.io.js"></script>
        
        <script>
            var host;
            var port;
            var socket;
            
            // 문서 로딩 후 실행됨
            $(function() {

                // 연결하기 버튼 클릭 처리
                $("#connectButton").bind('click', function(event) {
                    println('connectButton이 클릭되었습니다.');
                    
                    host = $('#hostInput').val();
                    port = $('#portInput').val();

                    connectToServer();
                });

                // 전송 버튼 클릭 시 처리
                $("#sendButton").bind('click', function(event) {
                    
                    // chattype 구분
                    var chattype = $('#chattype option:selected').val();

                    var sender = $('#senderInput').val();
                    var recepient = $('#recepientInput').val();
                    var data = $('#dataInput').val();

                    var output = {sender:sender, recepient:recepient, command:chattype, type:'text', data:data};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));
                    
                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('message', output);
                });

                // 로그인 버튼 클릭 시 처리
                $("#loginButton").bind('click', function(event) {
                    var id = $('#idInput').val();
                    var password = $('#passwordInput').val();
                    var alias = $('#aliasInput').val();
                    var today = $('#todayInput').val();

                    var output = {id:id, password:password, alias:alias, today:today};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('login', output);
                });
                
                // 방만들기 버튼 클릭 시 처리
                $("#createRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    var roomName = $('#roomNameInput').val();
                    var id = $('#idInput').val();
                    
                    var output = {command:'create', roomId:roomId, roomName:roomName, roomOwner:id};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });
                
                // 방이름바꾸기 버튼 클릭 시 처리
                $("#updateRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    var roomName = $('#roomNameInput').val();
                    var id = $('#idInput').val();
                    
                    var output = {command:'update', roomId:roomId, roomName:roomName, roomOwner:id};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });

                // 방없애기 버튼 클릭 시 처리
                $("#deleteRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();
                    
                    var output = {command:'delete', roomId:roomId};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });

                // 방입장하기 버튼 클릭 시 처리
                $("#joinRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();

                    var output = {command:'join', roomId:roomId};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });
                
                // 방나가기 버튼 클릭 시 처리
                $("#leaveRoomButton").bind('click', function(event) {
                    var roomId = $('#roomIdInput').val();

                    var output = {command:'leave', roomId:roomId};
                    console.log('서버로 보낼 데이터 : ' + JSON.stringify(output));

                    if (socket == undefined) {
                        alert('서버에 연결되어 있지 않습니다. 먼저 서버에 연결하세요.');
                        return;
                    }

                    socket.emit('room', output);
                });
                
            });
            
            // 서버에 연결하는 함수 정의
            function connectToServer() {

                var options = {'forceNew':true};
                var url = 'http://' + host + ':' + port;
                socket = io.connect(url, options);

                socket.on('connect', function() {
                    println('웹소켓 서버에 연결되었습니다. : ' + url);

                    socket.on('message', function(message) {
                        console.log(JSON.stringify(message));

                        println('<p>수신 메시지 : ' + message.sender + ', ' + message.recepient + ', ' + message.command + ', ' + message.data + '</p>');
                    });

                    socket.on('response', function(response) {
                        console.log(JSON.stringify(response));
                        println('응답 메시지를 받았습니다. : ' + response.command + ', ' + response.code + ', ' + response.message);
                    });

                    // 그룹 채팅에서 방과 관련된 이벤트 처리
                    socket.on('room', function(data) {
                        console.log(JSON.stringify(data));

                        println('<p>방 이벤트 : ' + data.command + '</p>');
                        println('<p>방 리스트를 받았습니다.</p>');
                        if (data.command == 'list') { // 방 리스트
                            var roomCount = data.rooms.length;
                            $("#roomList").html('<p>방 리스트 ' + roomCount + '개</p>');
                            for (var i = 0; i < roomCount; i++) {
                                $("#roomList").append('<p>방 #' + i + ' : ' + data.rooms[i].id + ', ' + data.rooms[i].name + ', ' + data.rooms[i].owner + '</p>');
                            }
                        }
                    });

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
    <h3>채팅 클라이언트 05 : 그룹 채팅하기</h3>
    <br>
    <div>
        <input type="text" id="hostInput" value="localhost" />
        <input type="text" id="portInput" value="3000" />

        <input type="button" id="connectButton" value="연결하기" />
    </div>
    <br>
    <div>
        <input type="text" id="idInput" value="test01" />
        <input type="password" id="passwordInput" value="123456" />
        <input type="text" id="aliasInput" value="소녀시대" />
        <input type="text" id="todayInput" value="좋은 날!" />

        <input type="button" id="loginButton" value="로그인" />
        <input type="button" id="logoutButton" value="로그아웃" />
    </div>
    <br>
    <div>
        <input type="text" id="roomIdInput" value="meeting01" />
        <input type="text" id="roomNameInput" value="청춘들의대화" />

        <input type="button" id="createRoomButton" value="방만들기" />
        <input type="button" id="updateRoomButton" value="방이름바꾸기" />
        <input type="button" id="deleteRoomButton" value="방없애기" />
    </div>
    <br>
    <div id="roomList">
        
    </div>
    <br>
    <div>
        <input type="button" id="joinRoomButton" value="방입장하기" />
        <input type="button" id="leaveRoomButton" value="방나가기" />
    </div>
    <br>
    <div>
        <div>
            <span>보내는사람 아이디 :</span> 
            <input type="text" id="senderInput" value="test01" />
        </div>
        <div>
            <span>받는사람 아이디 :</span>
            <input type="text" id="recepientInput" value="ALL" />
        </div>

        <!-- command 선택 <select> 채팅, 그룹채팅 -->
        <select name="chattype" id="chattype">
            <option value="chat">채팅</option>
            <option value="groupchat" selected>그룹채팅</option>
        </select>

        <div>
            <span>메시지 데이터 :</span>
            <input type="text" id="dataInput" value="안녕!"/>
        </div>
        <br>
        <input type="button" id="sendButton" value="전송" />
    </div>    
        
    <hr/>
    <p>결과 : </p>
    <div id="result"></div>
        
</body>
</html>
```

일대일 채팅에서는 `io.sockets.connected`객체에 들어 있는 소켓 객체들 중에서 대상이 되는 소켓 객체를 소켓 ID로 찾은 후 `emit()`메소드를 호출하여 메시지를 전송했다. 이와 다르게 그룹 채팅에서는 `io.sockets.in()`메소드를 사용해 대상이 되는 방에 들어 있는 소켓 객체들을 찾은 후 메시지를 전송한다.

```js
// Express 기본 모듈 불러오기
var express = require('express')
  , http = require('http')
  , path = require('path');

// Express의 미들웨어 불러오기
var bodyParser = require('body-parser')
  , cookieParser = require('cookie-parser')
  , static = require('serve-static')
  , errorHandler = require('errorhandler');

// 에러 핸들러 모듈 사용
var expressErrorHandler = require('express-error-handler');

// Session 미들웨어 불러오기
var expressSession = require('express-session');
  

//===== Passport 사용 =====//
var passport = require('passport');
var flash = require('connect-flash');


// 모듈로 분리한 설정 파일 불러오기
var config = require('./config/config');

// 모듈로 분리한 데이터베이스 파일 불러오기
var database = require('./database/database');

// 모듈로 분리한 라우팅 파일 불러오기
var route_loader = require('./routes/route_loader');

 

// Socket.IO 사용
var socketio = require('socket.io');

// cors 사용 - 클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
var cors = require('cors');



// 익스프레스 객체 생성
var app = express();


//===== 뷰 엔진 설정 =====//
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
console.log('뷰 엔진이 ejs로 설정되었습니다.');


//===== 서버 변수 설정 및 static으로 public 폴더 설정  =====//
console.log('config.server_port : %d', config.server_port);
app.set('port', process.env.PORT || 3000);
 

// body-parser를 이용해 application/x-www-form-urlencoded 파싱
app.use(bodyParser.urlencoded({ extended: false }))

// body-parser를 이용해 application/json 파싱
app.use(bodyParser.json())

// public 폴더를 static으로 오픈
app.use('/public', static(path.join(__dirname, 'public')));
 
// cookie-parser 설정
app.use(cookieParser());

// 세션 설정
app.use(expressSession({
  secret:'my key',
  resave:true,
  saveUninitialized:true
}));



//===== Passport 사용 설정 =====//
// Passport의 세션을 사용할 때는 그 전에 Express의 세션을 사용하는 코드가 있어야 함
app.use(passport.initialize());
app.use(passport.session());
app.use(flash());
 

//클라이언트에서 ajax로 요청 시 CORS(다중 서버 접속) 지원
app.use(cors());



//라우팅 정보를 읽어들여 라우팅 설정
var router = express.Router();
route_loader.init(app, router);


// 패스포트 설정
var configPassport = require('./config/passport');
configPassport(app, passport);

// 패스포트 라우팅 설정
var userPassport = require('./routes/user_passport');
userPassport(router, passport);



//===== 404 에러 페이지 처리 =====//
var errorHandler = expressErrorHandler({
 static: {
   '404': './public/404.html'
 }
});

app.use( expressErrorHandler.httpError(404) );
app.use( errorHandler );


//===== 서버 시작 =====//

//확인되지 않은 예외 처리 - 서버 프로세스 종료하지 않고 유지함
process.on('uncaughtException', function (err) {
  console.log('uncaughtException 발생함 : ' + err);
  console.log('서버 프로세스 종료하지 않고 유지함.');
  
  console.log(err.stack);
});

// 프로세스 종료 시에 데이터베이스 연결 해제
process.on('SIGTERM', function () {
    console.log("프로세스가 종료됩니다.");
    app.close();
});

app.on('close', function () {
  console.log("Express 서버 객체가 종료됩니다.");
  if (database.db) {
    database.db.close();
  }
});

// 시작된 서버 객체를 리턴받도록 합니다. 
var server = http.createServer(app).listen(app.get('port'), function(){
  console.log('서버가 시작되었습니다. 포트 : ' + app.get('port'));

  // 데이터베이스 초기화
  database.init(app, config);
   
});


//===== Socket.IO를 이용한 채팅 테스트 부분 =====//


// 로그인 아이디 매핑 (로그인 ID -> 소켓 ID)
var login_ids = {};


// socket.io 서버를 시작합니다.
var io = socketio.listen(server);
console.log('socket.io 요청을 받아들일 준비가 되었습니다.');

// 클라이언트가 연결했을 때의 이벤트 처리
io.sockets.on('connection', function(socket) {
  console.log('connection info :', socket.request.connection._peername);

    // 소켓 객체에 클라이언트 Host, Port 정보 속성으로 추가
    socket.remoteAddress = socket.request.connection._peername.address;
    socket.remotePort = socket.request.connection._peername.port;
    

    // 'login' 이벤트를 받았을 때의 처리
    socket.on('login', function(login) {
      console.log('login 이벤트를 받았습니다.');
      console.dir(login);

        // 기존 클라이언트 ID가 없으면 클라이언트 ID를 맵에 추가
        console.log('접속한 소켓의 ID : ' + socket.id);
        login_ids[login.id] = socket.id;
        socket.login_id = login.id;

        console.log('접속한 클라이언트 ID 갯수 : %d', Object.keys(login_ids).length);

        // 응답 메시지 전송
        sendResponse(socket, 'login', '200', '로그인되었습니다.');
    });

    
    // 'message' 이벤트를 받았을 때의 처리
    socket.on('message', function(message) {
      console.log('message 이벤트를 받았습니다.');
      console.dir(message);
      
        if (message.recepient =='ALL') {
            // 나를 포함한 모든 클라이언트에게 메시지 전달
          console.dir('나를 포함한 모든 클라이언트에게 message 이벤트를 전송합니다.')
            io.sockets.emit('message', message);
        } else {
          // command 속성으로 일대일 채팅과 그룹채팅 구분
          if (message.command == 'chat') {
            // 일대일 채팅 대상에게 메시지 전달
            if (login_ids[message.recepient]) {
              io.sockets.connected[login_ids[message.recepient]].emit('message', message);
              
              // 응답 메시지 전송
                  sendResponse(socket, 'message', '200', '메시지를 전송했습니다.');
            } else {
              // 응답 메시지 전송
                  sendResponse(socket, 'login', '404', '상대방의 로그인 ID를 찾을 수 없습니다.');
            }
          } else if (message.command == 'groupchat') {
            // 방에 들어있는 모든 사용자에게 메시지 전달
            io.sockets.in(message.recepient).emit('message', message);
              
            // 응답 메시지 전송
              sendResponse(socket, 'message', '200', '방 [' + message.recepient + ']의 모든 사용자들에게 메시지를 전송했습니다.');
          }
          
        }
    });

    // room 이벤트를 받았을 때의 처리
    socket.on('room',function(room){
    	console.log("room 이벤트를 받았습니다.");
    	console.dir(room);

    	if(room.command == 'create'){
    		if(io.sockets.adapter.rooms[room.roomId]){//방이 이미 만들어져 있는경우
    			console.log("방이 이미 만들어져 있습니다.");
    		}else{
    			console.log("방을 새로 만듭니다.");

    			socket.join(room.roomId);

    			var curRoom = io.sockets.adapter.rooms[room.roomId];
    			curRoom.id = room.roomId;
    			curRoom.name = room.roomName;
    			curRoom.owner = room.roomOwner;
    		}
    	}else if(room.command == 'update'){
    		var curRoom = io.sockets.adapter.rooms[room.roomId];
    			curRoom.id = room.roomId;
    			curRoom.name = room.roomName;
    			curRoom.owner = room.roomOwner;
    	}else if (room.command == 'delete') {
    		socket.leave(room.roomId);

    		if(io.sockets.adapter.rooms[room.roomId]){//방이 만들어져 있는 경우
    			delete io.sockets.adapter.rooms[room.roomId];
    		}else{
    			console.log("방이 만들어져 있지 않습니다.");
    		}
    	}else if(room.command == 'join'){
        socket.join(room.roomId);

        sendResponse(socket,'room','200','방에 입장했습니다.');
      }else if(room.command == 'leave'){
        socket.leave(room.roomId);

        sendResponse(socket,'room','200','방에서 나갔습니다.');
      }

    	var roomList = getRoomList();

    	var output = {command : 'list',rooms: roomList};
    	console.log("클라이언트로 보낼 데이터 : "+JSON.stringify(output));

    	io.sockets.emit('room',output);
    });
    
});

function getRoomList() {
	console.dir(io.sockets.adapter.rooms);
	
    var roomList = [];
    
    Object.keys(io.sockets.adapter.rooms).forEach(function(roomId) { // for each room
    	console.log('current room id : ' + roomId);
    	var outRoom = io.sockets.adapter.rooms[roomId];
    	
    	// find default room using all attributes
    	var foundDefault = false;
    	var index = 0;
        Object.keys(outRoom.sockets).forEach(function(key) {
        	console.log('#' + index + ' : ' + key + ', ' + outRoom.sockets[key]);
        	
        	if (roomId == key) {  // default room
        		foundDefault = true;
        		console.log('this is default room.');
        	}
        	index++;
        });
        
        if (!foundDefault) {
        	roomList.push(outRoom);
        }
    });
    
    console.log('[ROOM LIST]');
    console.dir(roomList);
    
    return roomList;
}

// 응답 메시지 전송 메소드
function sendResponse(socket, command, code, message) {
  var statusObj = {command: command, code: code, message: message};
  socket.emit('response', statusObj);
}
```