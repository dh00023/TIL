# 05 웹 서버 만들기

웹 서버는 다른 서버 기능을 추가할 수 있는 서버이다. 노드에는 웹 서버를 만들 때 필요한 **http모듈**이 들어 있는데 이 모듈을 사용하면 HTTP프로토콜로 요청하는 내용과 응답을 모두 처리할 수 있다. 그러나 좀 더 쉽고 빠르게 웹 서버를 구축하려면 **익스프레스**를 사용하는 것이 좋다. 익스프레스는 웹 서버 기능을 쉽게 만들 수 있게 코드를 자동으로 만들어 준다

## 05-1 간단한 웹 서버 만들기

노드에 기본으로 들어있는 `http 모듈`을 사용하면 웹 서버 기능을 담당하는 서버 객체를 만들 수 있다.

![](http://cfile29.uf.tistory.com/image/14258E3850AAA3993871B0)

```js
var http = require('http');

//웹 서버 객체 생성
var server = http.createServer();

//웹 서버를 시작해 3000번 포트에서 대기
var port = 3000;
server.listen(port,function(){
	console.log('웹 서버가 시작되었다. %s',port);
});
```
- `createServer()` 메소드

|메소드|설명|
|------|------|
|listen(prot[,hostname][,backlog][,callback])|서버를 실행하여 대기시킨다.|
|close([callback])|서버를 종료한다.|

**이더넷(Ethernet)카드**가 여려 개 있는 경우에는 서버에서 사용할 수 있는 IP주소가 여러개 존재한다. 특정 IP를 지정해서 서버를 실행해야할 때에는 `listen()`메소드를 호출하면서 IP주소를 직접 지정해준다. **backlog**란 실질적으로 동시 접속 연결 수를 결정하는 정보이다.

- `$ ifconfig`명령어를 실행하면 사용하고 있는 IP를 확인할 수 있다.

```js
var http = require('http');

//웹 서버 객체 생성
var server = http.createServer();


// 웹 서버를 시작해 127.0.0.1 IP와 3000번 포트에서 대기
var host = '127.0.0.1';
var port = 3000;
server.listen(port,host,'50000',function(){
	console.log('웹 서버가 시작되었다. %s %d',host,port);
});
```

### 클라이언트가 웹 서버에 요청할 때 발생하는 이벤트 처리하기

- 서버 객체에서 사용할 수 있는 주요 이벤트

|이벤트|설명|
|-----|-----|
|**connection**|클라이언트가 접속하여 연결이 만들어질 때 발생하는 이벤트|
|**request**|클라이언트가 요청할 때 발생하는 이벤트|
|close|서버를 종료할 때 발생하는 이벤트|

```js
var http = require('http');

//웹 서버 객체 생성
var server = http.createServer();

//웹 서버를 시작해 3000번 포트에서 대기
var port = 3000;
server.listen(port,function(){
	console.log('웹 서버 시작됨 %d',port);
});

// 클라이언트 연결 이벤트 처리
server.on('connection',function(socket){
	var addr = server.address();
	console.log('클라이언트가 접속했습니다 : %s %d',addr.address,addr.port);
});

//클라이언트 요청 이벤트 처리
server.on('request',function(req,res){
	console.log('클라이언트 요청이 들어왔습니ㅏㄷ.');
	console.dir(req);
});

//서버 종료 이벤트
server.on('close',function(){
	console.log('서버 종료');
});
```

그런데 웹 브라우저에서 페이지를 열어도 서버에서 아무런 응답을 보내지 않기 때문에 웹브라우저에서는 결과를 볼 수 없다.

```js
//클라이언트 요청 이벤트 처리
server.on('request',function(req,res){
	console.log('클라이언트 요청이 들어왔습니다.');
	
	res.writeHead(200,{"Content-Type": "text/html; charset=utf-8"});
	res.write("<!DOCTYPE html>");
	res.write("<html>");
	res.write("	<head>");
	res.write("		<title>응답페이지</title>");
	res.write("	</head>");
	res.write("	<body>");
	res.write("		<h1>노드제이에스로부터의 응답 페이지</h1>");
	res.write("	</body>");
	res.write("</html>");
	res.end();
});
```
`request`이벤트를 처리하는 콜백 함수에 다음과 같이 입력하면 응답 페이지가 나타난다.

|메소드|설명|
|-----|-----|
|writeHead(statusCode[,statusMessage][,headers])|응답으로 보낼 헤더를 만든다.|
|write(chunk[,encoding][,callback])|응답 본문의 데이터를 만든다. 여러번 호출될 수 있다.|
|end([data][,encoding][,callback])|클라이언트로 응답을 전송한다. 파라미터에 데이터가 들어있다면 이 데이터를 포함시켜 응답을 전송해야한다. 클라이언트 요청이 있을 때 한 번은 호출되어야 응답을 보내며, 콜백함수가 지정되면 응답이 전송된 후 콜백함수가 호출된다.|

```js
//클라이언트의 요청을 처리하는 콬ㄹ백 함수를 파라미터로 전달
var server = http.createServer(function(req,res){
	console.log('클라이언트 요청이 들어왔습니다.');
	
	res.writeHead(200,{"Content-Type": "text/html; charset=utf-8"});
	res.write("<!DOCTYPE html>");
	res.write("<html>");
	res.write("	<head>");
	res.write("		<title>응답페이지</title>");
	res.write("	</head>");
	res.write("	<body>");
	res.write("		<h1>노드제이에스로부터의 응답 페이지</h1>");
	res.write("	</body>");
	res.write("</html>");
	res.end();
});
```

이렇게 서버 객체를 만들 때 `createServer`메소드 호출 부분에 응답을 보내는 코드를 바로 입력할 수 있다.

### 클라이언트에서 요청이 있을 때 파일 읽어 응답하기

```js
var http = require('http');
var fs = require('fs');

...

//클라이언트 요청 이벤트 처리
server.on('request',function(req,res){
	console.log('클라이언트 요청이 들어왔습니다.');
	
	var filename = 'logo.png';
	fs.readFile(filename,function(err,data){
		res.writeHead(200,{"Content-Type": "image/png"});
		res.write(data);
		res.end();
	});
});

...
```

- `Content-Type`

|Content-Type 값|설명|
|------|------|
|text/plain|일반 텍스트 문서|
|text/html|HTML 문서|
|text/css|CSS 문서|
|text/xml|XML 문서|
|image/jpeg,image/png|JPEG,PNG 파일|
|video/mpeg, audio/mp3|MPEG 비디오파일, MP3 음악파일|
|applicaion/zip|ZIP 압축파일|

### 파일을 스트림으로 읽어 응답 보내기

파일을 스트림 객체로 읽어 들인 후 `pipe()`메소드로 응답 객체와 연결하면 별다른 코드 없이도 파일에 응답을 보낼 수 있다.

```js
//클라이언트 요청 이벤트 처리
server.on('request',function(req,res){
	console.log('클라이언트 요청이 들어왔습니다.');
	
	var filename = 'logo.png';
	var infile = fs.createReadStream(filename,{flags: 'r'});

	infile.pipe(res);
});
```

헤더를 설정할 수 없는 등 제약이 생기므로 필요할 때만 사용하길 권장한다.

### 파일을 버퍼에 담아 두고 일부부만 읽어 응답하기

```js
//클라이언트 요청 이벤트 처리
server.on('request',function(req,res){
	console.log('클라이언트 요청이 들어왔습니다.');
	
	var filename = 'logo.png';
	var infile = fs.createReadStream(filename,{flags: 'r'});
	var filelength = 0;
	var curlength = 0;

	fs.stat(filename, function(err,stats){
		filelength = stats.size;
	});

	// 헤더쓰기
	res.writeHeader(200,{"Content-Type": "image/png"});

	//파일 내용을 스트림에서 읽어 본문 쓰기
	infile.on('readable',function(){
		var chunk;
		while(null !== (chunk = infile.read())){
			console.log('일어 들인 데이터 크기 : %d',chunk.length);
			curlength +=chunk.length;
			res.write(chunk,'utf8',function(err){
				console.log('파일 부분 쓰기 완료 : %d, 파일 크기 : %d',curlength,filelength);
				if(curlength>=filelength){
					res.end();
				}
			});
		}
	});
	infile.pipe(res);
});
```

### 서버에서 다른 웹 사이트의 데이터를 가져와 응답하기

이러한 경우에는 서버에서 HTTP클라이언트 기능도 사용하게 된다. 즉, HTTP 클라이언트가 **GET**,**POST**방식으로 다른 웹 서버에 데이터를 요청할 수 있다.

- GET

```js
var http = require('http');

var options = {
	host: 'www.google.com',
	port: 80,
	path: '/'
};

var req = http.get(options,function(res){
	//응답처리
	var resData='';
	res.on('data',function(chunk){
		resData += chunk;
	});
	res.on('end',function(){
		console.log(resData);
	});
});

req.on('error',function(err){
	console.log('오류발생 :'+err.message);
});
```

수신 데이터의 용량에 따라 **data**이벤트를 한 번 또는 여러 번 발생할 수도 있다.

- POST

요청 헤더와 본문을 직접 설정해야한다.

```js
var http = require('http');

var opts = {
	host: 'www.google.com',
	port: 80,
	method: 'POST',
	path: '/',
	headers: {}
};

var resData='';
var req = http.request(opts,function(res){
	//응답 처리
	res.on('data',function(chunk){
		resData+=chunk;
	});
	res.on('end',function(){
		console.log(resData);
	});
});

opts.headers['Content-Type']='application/x-www-form-urlencoded';
req.data = "q=actor";
opts.headers['Content-Length']=req.data.length;

req.on('error',function(err){
	console.log('오류발생 '+ err.message);
});

req.write(req.data);
req.end();
```

## 05-2 익스프레스로 웹 서버 만들기

**express**모듈을 사용하면 간단한 코드로 웹 서버의 기능을 구현할 수 있다. **미들웨어**와 **라우터**를 사용하면 우리가 만들어야 하는 기능을 훨씬 편리하게 구성할 수 있다.

### 새로운 익스프레스 서버 만들기

`express` 모듈은 `http` 모듈 위에서 동작한다.

```js
//Express 기본 모듈 불러오기
var express = require('express')
	,http = require('http');

// 익스프레스 객체 생성
var app = express();

// 기본 포트를 app 객체에 속성으로 설정
// process.env객체에 PORT속성이 있으면 그 속성 사용, 아님 3000포트 사용
app.set('port',process.env.PORT || 3000);

// Express 서버 시작
http.createServer(app).listen(app.get('port'),function(){
	console.log('익스프레스 서버를 시작했습니다.'+app.get('port'));
});
```

- 익스프레스 서버 객체

|메소드|설명|
|------|------|
|set(name,value)|서버 설정을 위한 속성을 지정한다.`set()`메소드로 지정한 속성은 `get()`메소드로 꺼내 확인할 수 있다.|
|get(name)|서버 설정을 위해 지정한 속성을 꺼내온다.|
|use([,path]function[,function...])|미들웨어 함수를 사용|
|get([path,]fucntion)|특정 패스로 요청된 정보를 처리|

- 서버 설정을 위해 미리 정해진 app 객체 주요속성

|속성 이름|설명|
|------|------|
|env|서버모드 설정|
|views|뷰들이 들어 있는 폴더 or 폴더 배열 설정|
|view engine|디폴트로 사용할 뷰 엔진 설정 - `ejs`, `pug`많이 사용|

### 미들웨어로 클라이언트에 응답 보내기

`use()`메소드를 사용해 미들웨어 설정하는 방법.
노드에서는 미들웨어를 사용해 필요한 기능을 순차적으로 실행할 수 있다.

![](https://image.slidesharecdn.com/introtonode-140914093424-phpapp01/95/intro-to-nodejs-14-638.jpg?cb=1410687757)

익스프레스에서는 웹 요청과 응답에 관한 정보를 사용해 필요한 처리를 진행할 수 있도록 독립된 함수(미들웨어)로 분리한다. 각각의 미들웨어는 `next()`메소드를 호출해 그다음 미들웨어가 처리할 수 있도록 순서를 넘길 수 있다.
 라우터는 클라이언트의 요청 패스를 보고 이 요청 정보를 처리할 수 있는 곳으로 기능을 전달해주는 역할을 한다. 이러한 역할을 흔히 **라우팅**이라 부른다.

```js
var express = require('express') , http = require('http');

var app = express();

app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	res.writeHead('200',{'Content-Type': 'text/html;charset=utf-8'});
	res.end('<h1>서버에 응답한 결과입니다</h1>');
});

http.createServer(app).listen(3000,function(){
	console.log('3000포트에서 시작');
});
```

미들웨어 함수는 클라이언트 요청을 전달받을 수 있다. 클라이언트 요청은 등록된 미들웨어를 순서대로 통과하며, 요청 정보를 사용해 필요한 기능을 수행할 수 있다.

### 여러 개의 미들웨어를 등록해 사용하는 방법 알아보기

```js
var express = require('express') , http = require('http');

var app = express();

app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	req.user = 'seongwoo';
	next();
	res.writeHead('200',{'Content-Type': 'text/html;charset=utf-8'});
	res.end('<h1>서버에 응답한 결과입니다</h1>');
});

app.use('/',function(req,res,next){
	console.log('두 번재 미들웨어에서 요청을 처리함');

	res.writeHead('200',{'Content-Type': 'text/html;charset=utf-8'});
	res.end('<h1>서버에 응답한 결과입니다</h1>'+req.user);
});

http.createServer(app).listen(3000,function(){
	console.log('3000포트에서 시작');
});
```

반드시 `next()`메소드를 호출해 두 번째 미들웨어로 처리 순서를 넘겨줘야한다. 미들웨어 안에서는 기본적으로 요청 객체인 `req`와 응답 객체인 `res`객체를 파라미터로 전달받아 사용할 수 있다.

### 익스프레스의 요청 객체와 응답 객체 알아보기

- 주요 메소드

| 메소드 | 설명 |
|-----|-----|
|send([body])|클라이언트에 응답 데이터를 보낸다. (HTML 문자열,Buffer 객체,JSON 객체,배열)|
|status(code)|HTTP상태 코드를 반환. 상태코드는 `end()`, `send()`같은 전송 메소드를 추가로 호출해야 전송할 수 있다.|
|sendStatus(statusCode)|HTTP상태 코드를 반환. 상태 코드는 상태 메시지와 함께 전송|
|redirect([status,]path)|웹 페이지 경로를 강제로 이동|
|render(view[,locals][,callback])| 뷰 엔진을 사용해 문서를 만든 후 전송|

```js
app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	res.send({name:'박우진',age:20});
});
```

JSON데이터만 받아와서 게시물을 보여 줄 때 해당 데이터만 업데이트 하는 것이 효율적이다.

```js
// status()
res.status(403).send('Forbidden');

//snedStatus()
res.sendStatus(403);
```

```js
app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	res.redirect('http://google.co.kr');
});
```

### 익스프레스에서 요청 객체에 추가한 헤더와 파라미터 알아보기

|추가한 정보|설명|
|------|------|
|query|클라이언트에서 GET방식으로 전송한 요청 파라미터를 확인<br>예) req.query.name|
|body|클라이언트에서 POST방식으로 전송한 요청 파라미터 확인 <br>단, body-parser와 같은 외장 모듈을 사용해야한다.<br>예)req.body.name|
|header(name)|헤더를 확인한다.|

클라이언트에서 서버로 요청할 때 문자열로 데이터를 전달하는 것을 요청파라미터(query string)이라한다.

```js
app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	var userAgent = req.header('User-Agent');
	var paramName = req.query.name;

	res.writeHead('200',{'Content-Type':'text/html;charset=utf-8'});
	res.write('<h1>Express 서버에서 응답한 값</h1>');
	res.write('<div><p>User-Agent :'+userAgent+'</p></div>');
	res.write('<div><p>paramName :'+paramName+'</p></div>');
	res.end();
});
```

## 05-3 미들웨어 사용하기

개발자가 다양한 기능을 사용할 수 있도록 미리 만들어 둔 여러가지 미들웨어를 제공한다.

### static 미들웨어

특정 폴더의 파일들을 특정 패스로 접근할 수 있도록 만들어준다.

```js
// public폴더의 모든 파일을 웹 서버의 루트패스로 접근하기
var static = require('serve-static');
...
app.use(static(path.join(__dirname,'public')));
app.use('/public',static(path.join(__dirname,'public')));
```

### body-parser 미들웨어

클라이언트가 POST 방식으로 요청할 때 본문 영역에 들어 있는 요청 파라미터들을 파싱하여 요청 객체의 `body`속성에 넣어준다.

```js
var express = require('express') , http = require('http'), path = require('path');

//익스프레스 미들웨어 불러오기
var bodyParser = require('body-parser'),static = require('serve-static');

//익스프레스 객체 생성
var app = express();

// 기본 속성설정
app.set('port',process.env.PORT || 3000);

// body-parser를 사용해 application/x-www-form-urlencoded 파싱
app.use(bodyParser.urlencoded({extended: false}));

// body-parser를 사용해 application/json 파싱
app.use(bodyParser.json());

app.use(static(path.join(__dirname,'public')));

//미들웨어 파라미터 확인
app.use(function(req,res,next){
	console.log('첫 번재 미들웨어에서 요청을 처리함');

	var paramId = req.body.id || req.query.id;
	var paramPassword = req.body.password || req.query.password;

	res.writeHead('200',{'Content-Type':'text/html;charset=utf-8'});
	res.write('<h1>Express 서버에서 응답한 값</h1>');
	res.write('<div><p>User-ID :'+paramId+'</p></div>');
	res.write('<div><p>param password :'+paramPassword+'</p></div>');
	res.end();
});

http.createServer(app).listen(3000,function(){
	console.log('3000포트에서 시작');
});
```

## 05-4 요청 라우팅하기

**라우터 미들웨어(router middleware)**는 요청 url을 일일이 확인해야하는 번거로운 문제를 해결한다.

### 라우터 미들웨어 사용하기

라우터 미들웨어는 익스프레스에 포함되어있다.
```js
//라우터 객체 참조
var router = express.Router();

//라우팅 함수 등록
router.route('/process/login').get(...);
router.route('/process/login').post(...);

//라우터 객체를 app객체에 등록
app.use('/',router);
```

#### 요청 패스 메소드

|메소드|설명|
|------|------|
|get(callback)|GET 방식으로 특정 패스 요청이 발생했을 때 사용할 콜백 함수 지정|
|post(callback)|POST 방식으로 특정 패스 요청이 발생했을 때 사용할 콜백 함수 지정|
|put(callback)|PUT 방식으로 특정 패스 요청이 발생했을 때 사용할 콜백 함수 지정|
|delete(callback)|DELETE 방식으로 특정 패스 요청이 발생했을 때 사용할 콜백 함수 지정|
|all(callback)|몯ㄴ 요청 방식을 처리하며, 특정 패스 요청이 발생했을 때 사용할 콜백 함수 지정|

```js
var router = express.Router();

//라우팅 함수 등록
router.route('/process/login').post(function(req,res){
	console.log('/process/login 처리함');

	var paramID = req.body.id || req.query.id;
	var paramPassword = req.body.password || req.query.password;

	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>Express서버응답</h1>');
	res.write('<div><p>User-ID :'+paramID+'</p></div>');
	res.write('<div><p>param password :'+paramPassword+'</p></div>');
	res.write("<br><br><a href = '/login2.html'>로그인 페이지</a>");
	res.end();
});

//라우터 객체를 app객체에 등록
app.use('/',router);
```

### URL 파라미터 사용하기

URL 뒤에 `?` 기호를 붙이면 요청 파라미터(query string)를 추가하여 보낼 수 있다. URL 파라미터는 요청 파라미터와는 달리 URL 주소의 일부로 들어간다.

```js
router.route('/process/login/:name').post(function(req,res){
	console.log('/process/login/:name 처리함');

	var paramName = req.params.name;

	var paramID = req.body.id || req.query.id;
	var paramPassword = req.body.password || req.query.password;

	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>Express서버응답</h1>');
	res.write('<div><p>User-name :'+paramName+'</p></div>');
	res.write('<div><p>User-ID :'+paramID+'</p></div>');
	res.write('<div><p>param password :'+paramPassword+'</p></div>');
	res.write("<br><br><a href = '/login2.html'>로그인 페이지</a>");
	res.end();
});
```

`/process/login/:name`은 뒤에오는 파라미터를 `req.params.name`으로 접근 할 수 있다. 이것을 **토큰(Token)**이라한다.

### 오류 페이지 보여주기

```js
app.all('*',function(req,res){
	res.status(404).send('<h1>ERROR - 페이지를 찾을 수 없습니다.</h1>');
});
```
다른 사람이 만들어 둔 미들웨어를 사용할 수도 있다.

### express-error-handler 미들웨어로 오류페이지 보내기

```xml
//404.html
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>오류페이지</title>
</head>
<body>
	<h3>ERROR - 페이지를 찾을 수 없습니다.</h3>
	<hr>
	<p>/public/404.html 파일의 오류 페이지 표시</p>
</body>
</html>
```
```js
var errorHandler=expressErrorHandler({
	static: {
		'404': './public/404.html'
	}
});

app.use(expressErrorHandler.httpError(404));
app.use(errorHandler);
```

### 토큰과 함께 요청한 정보 처리하기

```js
//라우터 객체 참조
var router = express.Router();

//라우팅 함수 등록
router.route('/process/users/:id').get(function(req,res){
	console.log('/process/users/:id 처리함');

	var paramid = req.params.id;
	
	console.log('/process/users와 토큰 %s를 이용해 처리',paramid);

	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>Express서버응답</h1>');
	res.write('<div><p>User-ID :'+paramid+'</p></div>');
	res.end();
});

//라우터 객체를 app객체에 등록
app.use('/',router);
```

`http://localhost:3000/process/users/2` 이렇게 토큰을 사용하면 사용자 리스트 중에서 특정 사용자 정보를 id 값으로 조회하기에 편리하다.

## 05-5 쿠키와 세션 관리하기

사용자가 로그인한 상태인지 아닌지 확인하고 싶을 때에는 **쿠키**나 **세션**을 사용한다. 쿠키는 클라이언트 웹 브라우저에 저장되는 정보이며, 세션은 웹 서버에 저장되는 정보이다.

### 쿠키 처리하기

**cookie-parser 미들웨어**를 사용해 쿠키를 설정하거나 확인할 수 있다.

```js
var cookieParser = require('cookie-parser');

...

app.use(cookieParser());

...

//라우터 객체 참조
var router = express.Router();

//라우팅 함수 등록
router.route('/process/showCookie').get(function(req,res){
	console.log('/process/showCookie 처리함');

	res.send(req.cookies);
});

router.route('/process/setUserCookie').get(function(req,res){
	console.log('/process/setUserCookie 처리함');

	res.cookie('user',{
		id: 'dahye',
		name: '정다혜',
		authorized: true
	});

	res.redirect('/process/showCookie');
});

//라우터 객체를 app객체에 등록
app.use('/',router);
```

쿠키가 브라우저에 제대로 되었는지 확인하기 위해서는 [개발자도구-Application -Cookies]에서 확인할 수 있다.

### 세션 처리하기

```xml
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>상품 페이지</title>
</head>
<body>
	<h3>상품 정보 페이지</h3>
	<hr>
	<p>로그인 후 볼 수 있는 상품정보 페이지</p>
	<br><br>
	<a href="/process/logout">로그아웃하</a>
</body>
</html>
```
```js
//product
var cookieParser = require('cookie-parser');
var expressSession = require('express-session');

app.use(cookieParser());
app.use(expressSession({
	secret: 'my kye',
	resave: true,
	saveUninitialized: true
}));

router.route('/process/product').get(function(req,res){
	console.log('/process/product 처리함');

	if(req.session.user){
		res.redirect('/product.html');
	}else{
		res.redirect('/login2.html');
	}
});
```
```js
//login
router.route('/process/login').post(function(req,res){
	console.log('/process/login 처리함');

	var paramId = req.body.id || req.query.id;
	var paramPassword = req.body.password || req.query.password;

	if(req.session.user){
		console.log('이미 로그인되어 상품 페이지로 이동');

		res.redirect('/product.html');
	}else{
		//세션저장
		req.session.user = {
			id: paramId,
			name: '박우진',
			authorized: true
		};

	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>로그인 성공</h1>');
	res.write('<div><p>User-ID :'+paramId+'</p></div>');
	res.write('<div><p>param password :'+paramPassword+'</p></div>');
	res.write("<br><br><a href = '/process/product'>상품페이지 페이지</a>");
	res.end();

	}
});
```
```js
//logout
router.route('/process/logout').get(function(req,res){
	console.log('/process/logout 처리함');

	if(req.session.user){
		console.log('로그아웃합니다.');

		req.session.destroy(function(err){
			if(err) {throw err;}

			console.log('세션을 삭제하고 로그아웃함.');
			res.redirect('/login2.html');
		});
	}else{
		console.log('아직 로그인 안되어ㅣㅆ습니다.');
		res.redirect('/login2.html');
	}
});
```
로그인하여 세션이 만들어지면 **connect.sid 쿠키**가 브라우저에 저장된다. 이 쿠키는 세션 정보를 저장할 때 만들어진 것이다.

## 05-6 파일 업로드 기능 만들기

파일을 업로드할 때는 멀티파트포맷으로 된 파일 업로드 기능을 사용하여 파일 업로드 상태를 확인할 수 있다.

### multer 미들웨어 설치해서 파일 업로드하기

파일을 업로드할 때는 클라이언트에서 POST 방식으로 데이터를 전송하므로 body-parser 미들웨어 함께 사용한다.

- multer미들웨어 사용 : 미둘웨어 사용 순서가 중요하다. **body-parser->multer->router**

#### 주요속성
|속성 / 메소드 | 설명 |
|------|------|
|**destination**|업로드한 파일이 저장될 폴더를 지정|
|filename|업로드한 파일의 이름을 바꾼다.|
|limits|파일 크기나 파일 개수 등의 제한 속성을 설정하는 객체|

### 클라이언트의 요청 처리 함수 추가하기

```js
//Express 기본 모듈
var express = require('express') 
	, http = require('http')
	, path = require('path');

//익스프레스 미들웨어 불러오기
var bodyParser = require('body-parser')
	,cookieParser = require('cookie-parser')
	,static = require('serve-static')
	,errorHandler=require('errorhandler');

//오류 핸들러 모듈 사용
var expressErrorHandler = require('express-error-handler');

//Session 미들웨어
var expressSession = require('express-session');

//파일 업로드용 미들웨어
var multer = require('multer');
var fs = require('fs');

//클라이언트에서 ajax로 요청했을 때 CORS(다중서버) 지원
var cors = require('cors');

//익스프레스 객체 생성
var app = express();
// 기본 속성설정
app.set('port',process.env.PORT || 3000);

// body-parser를 사용해 application/x-www-form-urlencoded 파싱
app.use(bodyParser.urlencoded({extended: false}));

// body-parser를 사용해 application/json 파싱
app.use(bodyParser.json());

//public,uploads 폴더 오픈
app.use('/public',static(path.join(__dirname,'public')));
app.use('/uploads',static(path.join(__dirname,'uploads')));

//cookie - parser 설정
app.use(cookieParser());

//session설정
app.use(expressSession({
	secret: 'my kye',
	resave: true,
	saveUninitialized: true
}));

//ajax 요청했을때 다중서버접속 지원
app.use(cors());

//multer미들웨어 사용 : 미둘웨어 사용 순서가 중요하다. body-parser->multer->router
//파일 제한 10개,1G
var storage = multer.diskStorage({
	destination: function(req,file,callback){
		callback(null,'uploads');
	},
	filename: function(req,file,callback){
		callback(null,file.originalname+Date.now());
	}
});

var upload = multer({
	storage: storage,
	limits: {
		files: 10,
		filesize: 1024*1024*1024
	}
});

//라우터 사용해 라우팅 함수 등록
var router = express.Router();


router.route('/process/photo').post(upload.array('photo',1),function(req,res){
	console.log('/process/photo 처리함');

	try{
		var files = req.files;

		console.dir('#===== 업로드된 첫번째 파일 정보 =====#');
		console.dir(req.files[0]);
		console.dir('#================================#');

		//현재의 파일 정보를 저장할 변수 선언
		var originalname ='',
			filename = '',
			mimetype='',
			size=0;

			//배열에 들어가 있는 경우(설정에서 1개의 파일도 배열에 넣음)
			if(Array.isArray(files)){
				console.log('배열에 들어있는 파일 수 : %d',files.length);

				for (var index = 0; index< files.length; index ++) {
					originalname=files[index].originalname;
					filename=files[index].filename;
					mimetype=files[index].mimetype;
					size=files[index].size;
				}
			}else{ // 배열에 들어가 있지않은 경우
				console.log('파일 갯수 : 1');

				originalname=files[index].originalname;
				filename=files[index].filename;
				mimetype=files[index].mimetype;
				size=files[index].size;
			}
			console.log('현재 파일 정보 : '+originalname+','+filename+','+mimetype+','+size);

			//클라이언트에 응답 전송

			res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
			res.write('<h3>파일업로드 성공</h3>');
			res.write('<hr>');
			res.write('<p>원본 파일 이름 :'+originalname+'-> 저장 파일명 : '+filename+'</p>');
			res.write('<p>mime type :'+mimetype+'</p>');
			res.write('<p>파일 크기 :'+size+'</p>');
			res.end();
		}catch(err){
			console.dir(err.stack);
		}
});

//라우터 객체를 app객체에 등록
app.use('/',router);

http.createServer(app).listen(3000,function(){
	console.log('3000포트에서 시작');
});
```

```xml
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>파일 업로드</title>
</head>
<body>
	<h1>파일업로드</h1>
	<br>
	<form action="/process/photo" method="post" enctype="multipart/form-data">
		<table>
			<tr>
				<td><label>파일</label></td>
				<td><input type="file" name="photo"></td>
			</tr>
		</table>
		<input type="submit" value="업로드" name="submit">
	</form>
</body>
</html>
```

[http://expressjs.com/ko/guide/using-middleware.html](http://expressjs.com/ko/guide/using-middleware.html)에 미들웨어 설명 참조하기