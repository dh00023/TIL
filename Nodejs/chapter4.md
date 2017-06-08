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
|-------|-------|
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

같은 이름의 이벤트를 사용하는 경우에 충돌이 생길 수 있으므로 별도의 모듈 파일을 만들고 그 안에서 이벤트를 처리하도록 만드는 것이 좋다.

```js
// calc.js
var util = require('util');
// events모듈을 불러들인 후 EventEmitter객체참조
var EventEmitter = require('events').EventEmitter;

var Calc = function(){
	//프로토타입 객체로 this를 사용해 자기자신을 가리킴.
	// 그 객체안에 정의된 속성에 접근
	var self = this;

	this.on('stop',function(){
		console.log('Calc에 stop 이벤트 전달');
	});
};

// 상속은 util모듈의 inherits()메소드를 이용해서 정의
util.inherits(Calc,EventEmitter);

// new연산자를 이용해 Calc를 만들었을때 add()함수 사용할 수 있음.
Calc.prototype.add = function(a,b){
	return a+b;
}

// Calc객체 참조할 수 있도록 지
module.exports = Calc;
module.exports.title = 'calculator';
```
```js
//test.js
var Calc = require('./calc');

var cal = new Calc();
// 인스턴스 객체의 emit() 메소드 호출해 stop이벤트 전
cal.emit('stop');

console.log(Calc.title+'에 stop 이벤트 전달');
```

## 04-3 파일 다루기

노드의 파일 시스템은 파일을 다루는 기능과 디렉터리를 다루는 기능으로 구성되어 있다. 동기식 IO와 비동기식 IO를 함께 제공한다. 동기식 IO 메소드는 **Sync**단어를 붙여 구분한다.

### 파일을 읽어 들이거나 파일에 쓰기

#### 동기식 IO

```js
// 파일 시스템에 접근하기 위한 fs모듈
var fs=require('fs');

//파일을 동기식 IO로 읽어 들인다.
var data = fs.readFileSync('./package.json','utf8');

//읽어들인 데이터 출력
console.log(data);
```

#### 비동기식 IO

```js
// 파일 시스템에 접근하기 위한 fs모듈
var fs=require('fs');

//파일을 비동기식 IO로 읽어 들인다.
//이때 function은 파일을 읽어들이는 작업이 끝났을때 호출한다.
var data = fs.readFile('./package.json','utf8',function(err,data){
	//읽어들인 데이터 출력
	console.log(data);
});

console.log('프로젝트 폴더 안의 package.json 파일을 읽도록 요청');
```

비동기식으로 읽어 들이는 방식이 노드에서 더 자주 사용하는 코드이다.

파일을 읽어 들이는 것뿐만 아니라 파일을 쓰는 기능까지 fs모듈에서 정의한다.

|메소드|설명|
|------|------|
|readFile(filename,[encoding],[callback])|비동기식 IO로 파일을 읽어들인다.|
|readFileSync(filename,[encoding])|동기식 IO로 파일을 읽어들인다.|
|writeFile(filename,data,encoding='utf8',[callback])|비동기식 IO로 파일을 쓴다.|
|writeFileSync(filename,data,encoding='utf8')|동기식 IO로 파일을 쓴다.|

### 파일을 직접 열고 닫으면서 읽거나 쓰기

한꺼번에 모든 데이터를 읽거나 쓰지 않고 조금씩 읽거나 쓰는 방식을 사용하는 경우가 있다. 또한 다른 곳에서 받아 온 데이터를 파일에 쓰는 경우가 있다.

|메소드 |설명|
|-----|-----|
|open(path,flags[,model],[,callback])|파일을 연다.|
|read(fd,buffer,offset,length,position[,callback])|지정한 부분의 파일 내용을 읽어들인다.|
|write(fd,buffer,offset,length,position[,callback])|파일의 지정한 부분에 데이터를 쓴다.|
|close(fd[,callback])|파일을 닫는다.|

Buffer객체는 바이너리 데이터를 읽고 쓰는 데 사용한다.
```js
// 파일 시스템에 접근하기 위한 fs모듈
var fs=require('fs');

// 파일 열기
fs.open('./output.txt','w',function(err,fd){
	
	//데이터는 필요한 만큼 Buffer객체 안에 슨다.
	var buf = new Buffer('안녕\n');
    //fd객체로 파일을 구별한다.
	fs.write(fd,buf,0,buf.length,null,function(err,written,buffer){
		if(err) throw err;
		console.log(err,written,buffer);

		//파일닫기
		fs.close(fd,function(){
			console.log('파일 열고 데이터 쓰고 파일 닫기');
		})
	})
})
```

|플래그|설명|
|`r`|읽기에 사용하는 플래그, 파일이 없으면 예외 발생|
|`w`|쓰기에 사용하는 플래그, 파일이 없으면 만들어지고 파일이 있으면 이전 내용을 모두 삭제|
|`w+`|읽기와 쓰기에 모두 사용하는 플래그, 파일이 없으면 만들어지고 파일이 있으면 이전 내용을 모두 삭제|
|`a+`|읽기와 추가에 모두 사용하는 플래그, 파일이 없으면 만들어지고 파일이 있으면 이전 내용에 새로운 내용추가|

### 버퍼 객체 사용하는 방법 알아보기

크기를 먼저 지정하면 나머지 공간이 그대로 버퍼에 남아있게 된다. 버퍼인지 아닌지 확인하는 메소드 `isBuffer()`, 하나의 버퍼 객체를 다른 버퍼 객체로 복사 메소드 `copy()`, 두 개의 버퍼를 하나로 붙여서 새로운 버퍼 객체 만드는 메소드 `concat()` 사용

### 스트림 단위로 파일 읽고 쓰기

스트림은 데이터가 전달되는 통로와 같은 개념이다.

|메소드|설명|
|------|------|
|createReadStream(path[,option])|파일을 읽기 위한 스트림 객체를 만든다|
|createWriteStream(path[,option])|파일을 쓰기 위한 스트림 객체를 만든다|

옵션으로는 `flags`,`encoding`,`autoClose`속성이 들어 있는 자바스크립트 객체를 전달할 수 있다.

```js
var fs = require('fs');

var infile =  fs.createReadStream('./output.txt',{flags:'r'});
var outfile =  fs.createWriteStream('./output2.txt',{flags:'w'});

infile.on('data',function(data){
	console.log('읽어 들인 데이터', data);
	outfile.write(data);
});

infile.on('end',function(){
	console.log('종료');

	outfile.end(function(){
		console.log('파일쓰기 종료');
	});
});
```

`pipe()`메소드는 두 개의 스트림을 붙여주는 역할을 한다.

```js
var fs = require('fs');

var inname =  './output.txt';
var outname = './output2.txt';

fs.exists(outname,function(exists){
	//파일을 만들기 전에 파일이 이미 존재하면 삭제한다.
	if(exists){
		fs.unlink(outname, function(err){
			if(err) throw err;
			console.log('기존 파일 ['+outname+']삭제함');
		});
	}
	var infile = fs.createReadStream(inname,{flags: 'r'});
	var outfile = fs.createWriteStream(outname,{flags: 'w'});
	//두개의 스트림을 pipe()메소드로 연결해 복사
	infile.pipe(outfile);
	console.log('파일 복사'+inname +outname);
});
```

스트림을 서로 연결하는 방법은 웹 서버를 만들고 사용자의 요청을 처리할 대 유용하다.

### http 모듈로 요청받은 파일 내용을 읽고 응답하기

파일에서 만든 스트림 객체와 웹 서버의 스트림 객체를 `pipe()`메소드로 연결할 수 있다. 파일에서 데이터를 읽어 오기 위해 만든 것도 스트림 객체, 데이터를 쓰기 위해 웹서버 클라이언트 쪽에 만든 것도 스트림객체이기 때문에 연결이 가능하다.

```js
var fs = require('fs');
var http = require('http');
var server = http.createServer(function(req,res){
	//파일을 읽어 응답 스트림과 pipe로 연결
	var instream = fs.createReadStream('./output.txt');
	instream.pipe(res);
});
server.listen(7001,'127.0.0.1');
```

### fs모듈로 새 디렉터리 만들고 삭제하기

```js
 var fs = require('fs');

 fs.mkdir('./docs',0666,function(err){
 	if(err) throw err;
 	console.log('새로운 docs폴더를 생성');

 	fs.rmdir('./docs',function(err){
 		if(err) throw err;
 		console.log('폴더 삭제');
 	});
 });
```

## 04-4 로그 파일 남기기

프로그램의 크기가 커질수록 로그의 양도 많아지고 로그를 보관했다가 나중에 확인해야하는 경우도 생긴다. 따라서 어떻게 로그를 보관하고 남길지가 중요해진다.
**winston**모듈로 로그를 남기는 법을 알아볼 것이다.

```js
var winston = require('winston'); // 로그 처리 모듈
var winstonDaily = require('winston-daily-rotate-file'); // 로그 일별 처리 모듈
var moment = require('moment'); //시간처리 모듈

function timeStampFormat(){
	return moment().format('YYYY-MM-DD HH:mm:ss/SSS ZZ');
};

var logger = new (winston.Logger)({
transports: [
		new(winstonDaily)({
			name: 'info-file',
			filename: './log/server',
			datePatter: '_yyyy-MM-dd.log',
			colorize: false,
			maxsize: 50000000,
			maxFiles: 1000,
			level: 'info',
			showLevel: true,
			json: false,
			timestamp: timeStampFormat
		}),
		new(winston.transports.Console)({
			name: 'debug-console',
			colorize: true,
			level: 'debug',
			showLevel: true,
			json: false,
			timestamp: timeStampFormat
		})
	],
	exceptionHandlers:[
		new(winstonDaily)({
			name: 'exception-file',
			filename: './log/exception',
			datePatter: '_yyyy-MM-dd.log',
			colorize: false,
			maxsize: 50000000,
			maxFiles: 1000,
			level: 'error',
			showLevel: true,
			json: false,
			timestamp: timeStampFormat
		}),
		new(winston.transports.Console)({
			name: 'exception-console',
			colorize: true,
			level: 'debug',
			showLevel: true,
			json: false,
			timestamp: timeStampFormat
		})
	]
});
```

**Logger**는 로그를 출력하는 객체를 말한다. 로거는 transports라는 속성 값으로 여러 개의 설정 정보를 전달할 수 있다.

이 파일을 실행하기 전에는 몇가지 모듈을 설치해야한다.

```
% npm install winston --save
% npm install winston-daily-rotate-file --save
% npm install moment --save
```