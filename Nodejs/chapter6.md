# 06 데이터베이스 사용하기

몽고디비는 자바스크립트 객체를 그대로 저장할 수 있어서 자바스크립트 언어를 사용하는 노드에서 데이터를 저장하기 좋은 데이터베이스이다.

## 06-1. 몽고디비 시작하기

몽고디비는 관계형 데이터베이스와 달라 SQL을 사용하지 않는다.

### 몽고디비란?

**비관계형 데이터베이스**로 **NoSQL**, **Not Only SQL**이라고 한다. NoSQL 데이터베이스는 성능을 최우선으로 생각하기 때문에 실시간으로 처리해야 하는 경우나 대용량 트래픽을 감당할 수 있는 메시징 시스템 등에 활용된다.

몽고디비는 테이블 개념이 없이 여러거 데이터가 모인 하나의 단위를 **Collection(컬렉션)**이라 부른다. 컬렉션은 테이블과 달리 데이터를 정해 놓은 column의 형태대로 넣어야 한다는 제약은 없다.

즉, 데이터베이스는 컬렉션의 집합이라고 할 수 있다. 그리고 각각의 컬렉션은 여러 개의 문서 객체를 가질 수 있다. 이 문서 객체들은 관계형 데이터베이스에서 한 줄의 데이터인 레코드와 비슷하다. 하지만 다른 문서 객체와 똑같은 속성을 가질 필요가 없어서 필요에 따라 완전히 다른 속성을 넣어 둘 수 있다.

### 몽고디비에 데이터를 추가하거나 조회하기

#### 셸(Shell)

셸이란 명령을 받아서 실행하는 프로그램이다.

```
$ mongo
```

데이터 베이스는 **db**라는 이름으로 접근할 수 있으며 그 안에 컬렉션을 만들고 문서를 저장할 수 있다. 컬렉션을 별도로 만들지 않고 해당 컬렉션에 필요한 작업을 실행하도록 지정만해도 자동으로 만들어진다.

- `insert()` : 데이터 추가
```
$ db.users.insert({name:'박우진',age:19})
```

- `find()` : 데이터 조회
```
$ db.users.find().pretty()
```

- `remove()` : 데이터 삭제

## 06-2. 익스프레스에서 몽고디비 사용하기

**regexp 표현식** : 정규표현식의 약자로 특정한 규칙을 가진 문자열의 집합이다.

```js
//몽고디비 모듈 사용
var MongoClient = require('mongodb').MongoClient;

//데이터베이스 객체를 위한 변수 선언
var database;

//데이터 베이스 연결
function connectDB(){
	//DB 연결정보
	var databaseUrl = 'mongodb://localhost:27017/local';

	//DB연결
	MongoClient.connect(databaseUrl,function(err,db){
		if(err) throw err;

		console.log('데이터베이스에 연결되었습니다. : ',databaseUrl);

		//database변수 할당
		database = db;
	});
}

...

http.createServer(app).listen(3000,function(){
	console.log('3000포트에서 시작'+app.get('port'));

	connectDB();
});
```

### 사용자가 보내온 아이디 비밀번호 비교

```js
//사용자를 인증하는 함수
var authUser = function(database,id,password,callback){
	console.log('authUser호출');

	//users collection
	var users = database.collection('users');

	//id,password검색
	users.find({"id" : id, "password" : password}).toArray(function(err,docs){
		if(err){
			callback(err,null);
			return;
		}
		if(docs.length>0){
			console.log('id : %s, password : %s find',id,password);
			callback(null,docs);
		}else{
			console.log('일치하는 사용자 찾지못함.');
			callback(null,null);
		}
	});
}
```

### 로그인 처리를 요청하는 패스에 라우팅 함수 추가

```js
//로그인 라우팅 함수-DB정보와 비교
app.post('/process/login',function(req,res){
	console.log('/process/login 호출');
	
	var paramId = req.param('id');
	var paramPassword = req.param('password');

	if(database){
		authUser(database,paramId,paramPassword,function(err,docs){
			if(err) {throw err;}

			if(docs){
				console.dir(docs);

				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>로그인성공</h1>');
				res.write('<div><p>User-ID :'+paramId+'</p></div>');
				res.write("<br><br><a href = '/public/login.html'>다시로그인하기</a>");
				res.end();
			}else{
				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>로그인 실패</h1>');
				res.write('<div><p>아이디와 비밀번호를 다시 확인하십시오</p></div>');
				res.write("<br><br><a href = 'public/login.html'>로그인 페이지</a>");
				res.end();
			}
		});
	}else{
	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>DB연결 실패</h1>');
	res.end();
	}
});
```

### 사용자 추가기능 만들기

```js
//사용자를 추가하는 함수
var addUser = function(database,id,password,name,callback){
	console.log('addUser호출' +id+password+name);

	//users collection
	var users = database.collection('users');

	//사용자 추가
	users.insertMany([{"id":id,"password":password,"name":name}],function(err,result){
		if(err){
			callback(err,null);
			return;
		}
		if(result.insertedCount>0){
			console.log('사용자 레코드 추가'+result.insertedCount);
		}else{
			console.log('추가된 레코드 없음');
		}
		callback(null,result);
	});
}
```
```js
//사용자 추가 라우팅 함수
router.route('/process/adduser').post(function(req,res){
	console.log('/process/adduser 호출');
	
	var paramId = req.body.id || req.query.id;
	var paramPassword = req.body.password || req.query.password;
	var paramName = req.body.name || req.query.name;

	console.log('요청 파라미터'+paramId+paramPassword+paramName);

	if(database){
		addUser(database,paramId,paramPassword,paramName,function(err,result){
			if(err) {throw err;}

			if(result&&result.insertedCount>0){
				console.dir(result);

				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>사용자 추가 성공</h1>');
				res.end();
			}else{
				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>사용자 추가 실패</h1>');
				res.end();
			}
		});
	}else{
	res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
	res.write('<h1>DB연결 실패</h1>');
	res.end();
	}
});
```

### 데이터베이스 관리도구 사용하기

[Robomongo](https://robomongo.org/download)를 사용하면 간단하게 컬렉션이나 문서 객체를 추가, 수정, 삭제 할 수 있다.

## 06.3 몽구스로 데이터베이스 다루기

몽고디비를 사용하면서 하나의 컬렉션 안에 똑같은 속성을 가진 문서 객체를 반복적으로 넣어 둔다면 데이터를 조회할 때도 어떤 속성들이 들어 있는 지 미리 알고 있는 상태에서 조회할 수 있다. 모듈 중 대표적인 것이 **몽구스(mongoose)**이다.

### 몽구스 모듈 사용하기

**스키마(Schema)**란 데이터베이스의 구조를 정의한 것을 말한다. 스키마에 따라 문서 객체를 저장하는 것이 때로는 편리하다.
자바스크립트 객체와 데이터베이스 객체를 서로 매칭하여 바꿀 수 있게 하는 것을 **Object Mapper**라 한다.

```
$ npm install mongoose --save
```

```js
//몽구스 모듈 불러들이기
var mongoose = require('mongoose');
```

|메소드|설명|
|-----|-----|
|connect(uri(s),[options],[callback])|mongoose를 사용해 데이터베이스에 연결<br>연결 후에는 `mongoose.connection`객체를 사용해 연결 관련 이벤트를 처리할 수 있다.|
|Schema()|스키마를 정의하는 생성자|
|model(name,[schema],[collection],[skiplnit])|모델을 정의한다. [collection]이 지정되면 이 컬렉션을 사용하며, 지정하지 않으면 name으로 유추한 컬렉션을 사용한다.|

```js
//데이터베이스 스키마 객체를 위한 변수 선언
var UserSchema;

//데이터베이스 모델 객체를 위한 변수 선언
var UserModel;

//데이터 베이스 연결
function connectDB(){
	//DB 연결정보
	var databaseUrl = 'mongodb://localhost:27017/local';

	console.log('데이터베이스 연결을 시도합니다.');
	mongoose.Promise = global.Promise;
	mongoose.connect(databaseUrl);
	database = mongoose.connection;

	database.on('error',console.error.bind(console,'mongoose connection error'));
	database.on('open',function(){
		console.log('데이터베이스에 연결되었습니다.'+databaseUrl);

		//스키마정의
		UserSchema = mongoose.Schema({
			id: String,
			name: String,
			password: String
		});
		console.log('schema정의');

		//모델 정의
		UserModel = mongoose.model("users",UserSchema);
		console.log('모델정의');
	});

	//연결끊어지면 5초후 재연결
	database.on('disconnected',function(){
		console.log('연결이 끊어짐. 재연결');
		setInterval(connectDB,5000);
	});
}
```

### 몽구스로 사용자 인증하기

#### 데이터 처리 메소드
|메소드|설명|
|-----|-----|
|find([criteria],[callback])|조회 조건을 사용해 컬렉션의 데이터 조회. <br>조회결과는 콜백함수 전달|
|save([options],[callback])|모델 인스턴스 객체의 데이터 저장<br>저장 결과는 콜백함수 전달|
|update([criteria],[doc],[options],[callback])|컬렉션의 데이터 조회한 후 업데이트<br>`where()`메소드 함께 사용|
|remove([criteria],[callback])|컬렉션의 데이터 삭제|

```
UserModel.where({id: 'test01'}).update({name: "옹성우"},fucntion(err...){...})
```

```js
//사용자를 인증하는 함수
var authUser = function(database,id,password,callback){
	console.log('authUser호출');

	//id,password검색
	UserModel.find({"id" : id, "password" : password},function(err,results){
		if(err){
			callback(err,null);
			return;
		}
		console.log('id : %s, password : %s find',id,password);
		console.dir(results);
		if(docs.length>0){
			console.log('id : %s, password : %s find',id,password);
			callback(null,results);
		}else{
			console.log('일치하는 사용자 찾지못함.');
			callback(null,null);
		}
	});
};
```

## 06-4 인덱스와 메소드 사용하기

빠른 검색을 위해 각각의 속성에 인덱스를 만들 수 있다. 스키마를 만들 때 각 속성의 스키마 타입에는 여러 정보가 들어갈 수 있는데 인덱스도 그중 하나다.

```js
var USerSchema = new mongoose.Schema({
	id: {type: String,required: true, unique: true},
    password: {type: String,required: true},
    name: {type: String, index: 'hashed'},
    age: Number,
    created_at: {type:Date, index: {unique:false, expires: '1d'}},
    updated_at: Date
});
```

id속성값에 `unique`가 true이면 자동으로 인덱스가 만들어진다. 위치 기반 서비스를 위해 저장되는 경위도 좌표에 **공간 인덱싱**이 사용된다.`{type: [Number],index:'2d',sparse: true}`

#### 스키마 객체 메소드

|메소드|설명|
|-----|-----|
|static(name,fn)|모델 객체에서 사용할 수 있는 함수 등록<br>함수의 이름과 함수 객체를 마라미터로 전달|
|method(name,fn)|모델 인스턴스 객체에서 사용할 수 있는 함수 등록<br>함수의 이름과 함수 객체를 마라미터로 전달|

### 사용자 리스트 조회 기능 추가

```js
//데이터 베이스 연결
function connectDB(){
	//DB 연결정보
	var databaseUrl = 'mongodb://localhost:27017/local';

	console.log('데이터베이스 연결을 시도합니다.');
	mongoose.Promise = global.Promise;
	mongoose.connect(databaseUrl);
	database = mongoose.connection;

	database.on('error',console.error.bind(console,'mongoose connection error'));
	database.on('open',function(){
		console.log('데이터베이스에 연결되었습니다.'+databaseUrl);

		//스키마정의
		UserSchema = mongoose.Schema({
			id: {type: String,required: true, unique: true},
		    password: {type: String,required: true},
		    name: {type: String, index: 'hashed'},
		    age: { type: Number,'default': -1},
		    created_at: {type:Date, index: {unique:false}, 'default': Date.now},
		    updated_at: {type:Date, index: {unique:false}, 'default': Date.now}
		});

		// 스키마에 static메소드 추가
		UserSchema.static('findById',function(id,callback){
			return this.find({id: id},callback);
		});

		UserSchema.static('findAll',function(callback){
			return this.find({ },callback);
		});
		console.log('schema정의');

		//모델 정의
		UserModel = mongoose.model("users2",UserSchema);
		console.log('모델정의');
	});

	//연결끊어지면 5초후 재연결
	database.on('disconnected',function(){
		console.log('연결이 끊어짐. 재연결');
		setInterval(connectDB,5000);
	});
}

//사용자를 인증하는 함수
var authUser = function(database,id,password,callback){
	console.log('authUser호출');

	
	//id,password검색
	UserModel.findById(id,function(err,results){
		if(err){
			callback(err,null);
			return;
		}
		
		console.log('id : %s로 사용자 검색 결과',id);
		console.dir(results);

		if(results.length>0){
			console.log('아이디와 일치하는 사용자 찾음');

			//비밀번호 확인
			if(results[0]._doc.password == password){
				console.log('비밀번호 일치');
				callback(null,results);
			}else{
			console.log('비밀번호 일치하지 않음');
			callback(null,null);
			}
		}else{
			console.log('아이디와 일치하는 사용자를 찾지못함');
			callback(null,null);
		}
	});
}
...

//사용자 리스트 함수
router.route('/process/listuser').post(function(req,res){
	console.log('/process/listuser 호출');

	//데이터베이스 객체가 최기화된 경우, 모델객체의 findAll메소드 호출
	if(database){
		//1.모든 사용자 검색
		UserModel.findAll(function(err,results){
			//오류가 발생햇을 때 클라이언트로 오류 전송
			if(err){
				console.log('사용자 리스트 조회 중 오류 발생'+err.stack);

				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>사용자 리스트 조회 중 오류 발생</h1>');
				res.write('<p>'+err.stack+'</p>');
				res.end();	

				return;
			}

			if(results){ // 결과 객체 있으면 리스트 전송
				console.dir(results);

				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>사용자 리스트</h1>');
				res.write('<div><ul>');
				
				for(var i=0;i<results.length;i++){
					var curId = results[i]._doc.id;
					var curName = results[i]._doc.name;
					res.write('		<li>#'+i+' : '+curId+','+curName+'</li>');
				}
				res.write('</ul></div>');
				res.end();
			}else{ // 결과 객체가 없으면 실패 응답 전송
				res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
				res.write('<h1>사용자 리스트 조회 실패</h1>');
				res.end();
			}
		});
	}else{ // 데이터베이스 객체가 초기화되지 않았을때 실패응답 전송
		res.writeHead('200',{'Content-Type':'text/html;charset=utf8'});
		res.write('<h1>DB연결 실패</h1>');
		res.end();
	}
});
...
```
`_doc`속성은 각 문서 객체의 정보를 담고 있다.

## 06-5 비밀번호암호화하여 저장하기

### virtual 함수 사용하기

비밀번호는 단방향으로 암호화하여 원본 비밀번호 문자열을 알 수 없도록 만든다.

> 단방향 암호화는 암호화된 데이터는 다시 원본으로 복구 할 수 없다. 원본 글자를 복구하는 과정을 복호화라고 하는데 복호화할 수 있는 방법이 없으므로 한쪽 방향으로만 암호화가 가능하다는 의미이다.

`virtual()`은 문서 객체에 실제로 저장되는 속성이 아니라 가상의 속성을 지정할 수 있다. 문서 객체를 저장할 때 `set()`메소드로 지정한 함수가 필요한 작업을 수행하며, 문서 객체를 조회할 때 get()메소드로 지정한 함수가 실행된다.

### 스키마 객체의 virtual()함수 사용법 알아보기

```js
//====모듈 불러들이기 ====//

var mongodb = require('mongodb');
var mongoose = require('mongoose');

//db연결

var database;
var UserSchema;
var UserModel;

//데이터베이스에 연결하고 응답 객체의 속성으로 db객체 추가
function connectDB(){
	//db 연결 정보
	var databaseUrl = 'mongodb://localhost:27017/local';

	//db 연결
	mongoose.connect(databaseUrl);
	database = mongoose.connection;

	database.on('error',consol.error.bind(console,'mongoose connection error.'));
	database.on('open',function(){
		console.log('db연결됨'+databaseUrl);

		//user 스키마 및 모델 객체 생성
		createUserSchema();

		//test
		doTest();
	});
	database.on('disconnected',connectDB);
}

// user스키마 및 모델 객체 생성
function createUserSchema(){
	//스키마 정의
	//password를 hashed_password로 변경,default속성 추가, salt속성 추가
	UserSchema = mongoose.Schema({
		id: {type: String,required: true, unique: true},
		name: {type: String, index: 'hashed','default':''},
		age: { type: Number,'default': -1},
		created_at: {type:Date, index: {unique:false}, 'default': Date.now},
		updated_at: {type:Date, index: {unique:false}, 'default': Date.now}
	});

	//info를  virtual 메소드로 정의
	UserSchema
		.virtual('info')
		.set(function(info){
			var splitted = info.split(' ');
			this.id = splitted[0];
			this.name = splitted[1];
			console.log('virtual info 설정 : %s %s',this.id,this.name);
		})
		.get(function(){ return this.id + ' '+this.name});

	console.log('UserSchema정의');

	//UserModel 모델 정의
	UserModel = mongoose.model("users4",UserSchema);
	console.log('UserModel 정의함');

	function doTest(){
		//UserModel 인스턴스 생성
		//id, name 속성은 할당하지 않고 info속성만 할당
		var user = new UserModel({"info":'test01 박우진'});

		//save()로 저장
		user.save(function(err){
			if(err){throw err;}

			console.log("사용자 데이터 추가함");

			findAll();
		});
		console.log('info속성에 값 할당함');
		console.log('id: %s, name : %s',user.id, user.name);
	}

	function findAll(){
		UserModel.find({},function(err,results){
			if(err){throw err;}

			if(results){
				console.log('조회된 user문서 객체 #0 -> id : %s, name :%s',results[0]._doc.id,results[0]._doc.name);
			}
		});
	}
}
```

### 비밀번호 암호화하여 저장하는 코드 적용하기

노드는 암호화를 위해 **crypto**모듈을 제공한다.

```js
...
//===== 데이터베이스 연결 =====//

// 데이터베이스 객체를 위한 변수 선언
var database;

// 데이터베이스 스키마 객체를 위한 변수 선언
var UserSchema;

// 데이터베이스 모델 객체를 위한 변수 선언
var UserModel;

//데이터베이스에 연결
function connectDB() {
	// 데이터베이스 연결 정보
	var databaseUrl = 'mongodb://localhost:27017/local';
	 
	// 데이터베이스 연결
    console.log('데이터베이스 연결을 시도합니다.');
    mongoose.Promise = global.Promise;  // mongoose의 Promise 객체는 global의 Promise 객체 사용하도록 함
	mongoose.connect(databaseUrl);
	database = mongoose.connection;
	
	database.on('error', console.error.bind(console, 'mongoose connection error.'));	
	database.on('open', function () {
		console.log('데이터베이스에 연결되었습니다. : ' + databaseUrl);
		
        
		// user 스키마 및 모델 객체 생성
		createUserSchema();
		
		
	});
	
    // 연결 끊어졌을 때 5초 후 재연결
	database.on('disconnected', function() {
        console.log('연결이 끊어졌습니다. 5초 후 재연결합니다.');
        setInterval(connectDB, 5000);
    });
}


// user 스키마 및 모델 객체 생성
function createUserSchema() {

	// 스키마 정의
	// password를 hashed_password로 변경, 각 칼럼에 default 속성 모두 추가, salt 속성 추가
	UserSchema = mongoose.Schema({
	    id: {type: String, required: true, unique: true, 'default':''},
	    hashed_password: {type: String, required: true, 'default':''},
	    salt: {type:String, required:true},
	    name: {type: String, index: 'hashed', 'default':''},
	    age: {type: Number, 'default': -1},
	    created_at: {type: Date, index: {unique: false}, 'default': Date.now},
	    updated_at: {type: Date, index: {unique: false}, 'default': Date.now}
	});
	
	// password를 virtual 메소드로 정의 : MongoDB에 저장되지 않는 가상 속성임. 
    // 특정 속성을 지정하고 set, get 메소드를 정의함
	UserSchema
	  .virtual('password')
	  .set(function(password) {
	    this._password = password;
	    this.salt = this.makeSalt();
	    this.hashed_password = this.encryptPassword(password);
	    console.log('virtual password의 set 호출됨 : ' + this.hashed_password);
	  })
	  .get(function() {
           console.log('virtual password의 get 호출됨.');
           return this._password;
      });
	
	// 스키마에 모델 인스턴스에서 사용할 수 있는 메소드 추가
	// 비밀번호 암호화 메소드
	UserSchema.method('encryptPassword', function(plainText, inSalt) {
		if (inSalt) {
			return crypto.createHmac('sha1', inSalt).update(plainText).digest('hex');
		} else {
			return crypto.createHmac('sha1', this.salt).update(plainText).digest('hex');
		}
	});
	
	// salt 값 만들기 메소드
	UserSchema.method('makeSalt', function() {
		return Math.round((new Date().valueOf() * Math.random())) + '';
	});
	
	// 인증 메소드 - 입력된 비밀번호와 비교 (true/false 리턴)
	UserSchema.method('authenticate', function(plainText, inSalt, hashed_password) {
		if (inSalt) {
			console.log('authenticate 호출됨 : %s -> %s : %s', plainText, this.encryptPassword(plainText, inSalt), hashed_password);
			return this.encryptPassword(plainText, inSalt) === hashed_password;
		} else {
			console.log('authenticate 호출됨 : %s -> %s : %s', plainText, this.encryptPassword(plainText), this.hashed_password);
			return this.encryptPassword(plainText) === this.hashed_password;
		}
	});

	// 값이 유효한지 확인하는 함수 정의
	var validatePresenceOf = function(value) {
		return value && value.length;
	};
		
	// 저장 시의 트리거 함수 정의 (password 필드가 유효하지 않으면 에러 발생)
	UserSchema.pre('save', function(next) {
		if (!this.isNew) return next();

		if (!validatePresenceOf(this.password)) {
			next(new Error('유효하지 않은 password 필드입니다.'));
		} else {
			next();
		}
	})
	
	// 필수 속성에 대한 유효성 확인 (길이값 체크)
	UserSchema.path('id').validate(function (id) {
		return id.length;
	}, 'id 칼럼의 값이 없습니다.');
	
	UserSchema.path('name').validate(function (name) {
		return name.length;
	}, 'name 칼럼의 값이 없습니다.');
	
	UserSchema.path('hashed_password').validate(function (hashed_password) {
		return hashed_password.length;
	}, 'hashed_password 칼럼의 값이 없습니다.');
	
	   
	// 스키마에 static으로 findById 메소드 추가
	UserSchema.static('findById', function(id, callback) {
		return this.find({id:id}, callback);
	});
	
    // 스키마에 static으로 findAll 메소드 추가
	UserSchema.static('findAll', function(callback) {
		return this.find({}, callback);
	});
	
	console.log('UserSchema 정의함.');
	
	// User 모델 정의
	UserModel = mongoose.model("users3", UserSchema);
	console.log('users3 정의함.');
	
}


...

// 사용자를 인증하는 함수 : 아이디로 먼저 찾고 비밀번호를 그 다음에 비교하도록 함
var authUser = function(database, id, password, callback) {
	console.log('authUser 호출됨 : ' + id + ', ' + password);
	
    // 1. 아이디를 이용해 검색
	UserModel.findById(id, function(err, results) {
		if (err) {
			callback(err, null);
			return;
		}
		
		console.log('아이디 [%s]로 사용자 검색결과', id);
		console.dir(results);
		
		if (results.length > 0) {
			console.log('아이디와 일치하는 사용자 찾음.');
			
			// 2. 패스워드 확인 : 모델 인스턴스를 객체를 만들고 authenticate() 메소드 호출
			var user = new UserModel({id:id});
			var authenticated = user.authenticate(password, results[0]._doc.salt, results[0]._doc.hashed_password);
			if (authenticated) {
				console.log('비밀번호 일치함');
				callback(null, results);
			} else {
				console.log('비밀번호 일치하지 않음');
				callback(null, null);
			}
			
		} else {
	    	console.log("아이디와 일치하는 사용자를 찾지 못함.");
	    	callback(null, null);
	    }
		
	});
	
}

...
```