# 07. 익스프레스 프로젝트를 모듈화하기

`app.js`파일에 들어있는 많은 코드를 별도의 모듈 파일로 분리하는 방법과 `app.js`파일을 자주 수정하지 않도록 수정 파일을 만들어 사용하는 방법을 알아볼 것이다.

## 07-1 모듈화 방법 자세히 살펴보기

별도의 파일로 분리한 것을 **모듈**이라한다.

### 다양한 방법으로 모듈 만들기

`exports`전역 변수는 어디에서나 접근할 수 있게 정의된 것이고 속성도 추가할 수 있다.
```js
//exports 객체 속성으로 함수 추가
exports.getUser = function(){
	return {id: 'test01',name: '박우진'};
}

//exports 객체 속성으로 객체추가
exports.group = {id: 'group1',name:'친구'};
```
```js
//require()메소드는 exports객체를 반환한다.
var user1 = require('./user1');

function showUser(){
	return user1.getUser().name + ','+user1.group.name;
}

console.log('사용자 정보 : %s',showUser());
```

### `exports`에 객체 지정하기

```js
/*exports는 속성으로, exports에 속성을 추가하면 모듈에서 접근하지만
exports에 객체를 지정하면 자바스크립트에서 새로운 변수로 처리한다. */
exports = {
	getUser: function(){
		return {id: 'test01',name: '박우진'};
	},
	group: {id: 'group1',name:'친구'}
}
```
```js
/* user2.js 파일에서 exports 객체를 할당하였으므로, 
	require()를 호출할 때 자바스크립트에서 새로운 변수로 처리한다.
	결국 아무 속성도 없는 {}가 반환된다. */
var user = require('./user2');

console.dir(user);

function showUser(){
	return user.getUser().name + ','+user.group.name;
}

console.log(showUser);
```

노드는 모듈을 처리할 때 `exports`를 속성으로 인식한다. 이 속성에 함수나 객체를 속성으로 추가하면 모듈을 불러들인 쪽에서 `exports`에 추가된 속성들을 참조할 수 있다. 그러나 `exports`에 **객체**를 할당하면 모듈 파일 안에서 선언한 `exports`는 모듈 시스템에서 처리할 수 있ㄴ는 전역변수가 아닌 단순 변수로 인식된다. 이때문에 참조할 수 없게된다.

### `module.exports`를 사용해 객체를 그대로 할당하기
```js
//module.exports에는 객체를 그대로 할당할 수 있다.
var user = {
	getUser : function(){
		return {id: 'test01',name: '박우진'};
	},
	group : {id: 'group1',name:'친구'}
}

module.exports = user;
```
```js
// require()메소드는 객체를 반환
var user = require('./user3');

function showUser(){
	return user.getUser().name + ',' + user.group.name;
}

console.log(showUser());
```

`module.exports`에 객체를 그대로 할당하면 모둘파일 안에서 할당한 객체를 참조할 수 있다.

### `module.exports`에 함수만 할당하기
```js
//인터페이스(함수 객체)를 그대로 할당할 수 있다.

module.exports = function(){
	return {id: 'test01',name: '박우진'}
};
```
```js
//require()메소드는 함수를 반환
var user = require('./user4');

function showUser(){
	return user().name+','+'No group';
}
console.log(showUser());
```
반환된 함수에 소괄호만 붙여주면 함수를 그대로 실행할 수 있다.

### `exports`와 `module.exports` 함께 사용하기

`module.exports`가 우섡으로 적용된다. 즉, 모듈을 불러오는 쪽에서는 `module.exports`에 할당된 객체나 속성을 참조할 수 있으며 exports 전역 변수는 무시된다.
```js
//module.exports가 사용되면 exports는 무시됨
module.exports = {
	getUser: function(){
		return {id:'test01',name:'박우진'};
	},
	group: {id:'group01',name:'친구'}
}

exports.group = {id: 'group02',name:'가족'};
```
```js
//require()메소드는 exports가 아닌 module.exports로 설정된 속성 반환
var user = require('./user5');

function showUser(){
	return user.getUser().name + user.group.name;
}

console.log(showUser());
```

### require() 메소드의 동작 방식 이해하기

```js
//가상으로 require()함수를 정의해 보면 require()함수가 내부적으로 처리되는 방식을 이해할 수 있따.

var require = function(path){
	var exports = {
		getUser : function(){
			return {id:'test01',name:'박우진'};
		},
		group: {id:'group01',name:'친구'}
	}
	return exports;
}

var user = require('...');
function showUser(){
	return user.getUser().name + user.group.name;
}

console.log(showUser());
```

### 모듈을 분리할 때 사용하는 전형적인 코드 패턴

|코드패턴|설명|
|------|-------|
|함수를 할당하는 경우| 모듈 안에서 함수를 만들어 할당한다.<br>모듈을 불러온 후 소괄호를 붙여 모듈을 실행한다.|
|인스턴스 객체를 할당하는 경우|모듈 안에서 인스턴스 객체를 만들어 할당한다.<br>모듈을 불러온 후 해당 객체의 메소드를 호출하거나 속성을 사용할 수 있다.|
|프로토타입 객체를 할당하는 경우|모듈 안에서 프로토타입 객체를 만들어 할당한다.<br>모듈을 불러온 후 new연산자로 인스턴스 객체를 만들어 사용할 수 있다.|

#### 1. 함수를 할당하는 코드 패턴
```js
//사용패턴 : exports에 속성으로 추가된 함수 객체를 그대로 참조한 후 호출
exports.printUser = function(){
	console.log('user이름은 박우진');
};
```
```js
//exports에 속성으로 추가된 함수 객체를 그대로 참조한 후 호출
var printUser = require('./user7').printUser;

printUser();
```

#### 2.인스턴스 객체를 할당하는 코드 패턴

```js
// module.exports에 인스턴스 객체를 만들어 할당

// 생성자 함수
function User(id,name){
	this.id = id;
	this.name = name;
}

User.prototype.getUser = function(){
	return {id:this.id,name:this.name};
}

User.prototype.group = {id: 'group1',name:'친구'};

User.prototype.printUser = function(){
	console.log(this.name  + this.group.name);
}
module.exports = new User('test01','박우진');
```
```js
// new연산자로 만든 인스턴스 객체를 할당한 후 인스턴스 객체 호출
var user = require('./user8');

user.printUser();
```

```js
// exports에 인스턴스 객체를 할당할 경우
exports.user = new User('test01','박우진');

// new연산자로 만든 인스턴스 객체를 할당한 후 인스턴스 객체 호출
var user = require('./user9').user;

user.printUser();
```

#### 3.프로토타입 객체를 할당하는 코드 패턴

```js
//user.js
...
exports.user = User;

//module_test.js
var User = require('./user10');
var user  = new User('test01','박우진');

user.printUser();
```

## 07-2 사용자 정보 관련 기능을 모듈화하기

### 스키마 파일을 별도의 모듈 파일로 분리하기

스키마는 컬렉션의 구조를 결정하는 것으로 데이터베이스와 분리해서 독립적으로 정의할 수 있다.
```js
var crypto = require('crypto');

var Schema={ };


Schema.createSchema= function(mongoose){

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
	
	return UserSchema;
}

//module.exports에 UserSchema 객체 직접할당
module.exports = Schema;
```
```js
//app.js
// user 스키마 및 모델 객체 생성
function createUserSchema() {
	//user_schema.js 모듈 불러오기
	UserSchema = require('./database/user_schema').createSchema(mongoose);
	// User 모델 정의
	UserModel = mongoose.model("users3", UserSchema);
	console.log('users3 정의함.');
}
```

### 사용자 처리 함수를 별도의 모듈 파일로 분리해보기
```
router.route('/process/login').post(function(){});
router.route('/process/adduser').post(function(){});
router.route('/process/listuser').post(function(){});
```

## 07-3 설정 파일 만들기

웹 서버 안의 각 기능을 별도의 파일로 분리하여 모듈로 만들면 기능 수정이 필요할 때 웹 서버의 메인 파일을 수정하지 않고 모듈 부분만 수정해도된다. 또 새로운 모듈을 추가할 때도 메인 파일을 수정하지 않아도 되기 때문에 서버 유지관리에 아주 좋은 구성이 된다.

설정파일을 만들고 메인파일이 설정파일을 불러오도록 할 것이다.

### 설정 파일 분리하기

- `config.js` : 서버를 실행할 때 필요한 정보, 데이터베이스 연결시 필요한 정보

#### db_schemas속성
|속성이름|설명|
|-----|-----|
|file|스키마 파일을 지정|
|collection|데이터베이스의 컬렉션 이름 지정|
|schemaName|스키마 파일을 불러들인 후 반환된 객체를 어떤 속성 이름으로 할 것인지 지정|
|modelName|스키마에서 모델 객체를 만든 후 어떤 속성이름으로 할 것인지 지정|

```js
db_schemas: [
	{file:'./user_schema',collection:'user3',schemaName:'UserSchema',modelName:'UserModel'}
	],
```

#### 스키마를 새로 정의하고 싶다면?
1. 스키마 정의 파일을 추가한다.
2. 새로만든 스키마정보를 `config.js`에 추가한다.

#### route속성
|속성이름|설명|
|-----|-----|
|file|라우팅 파일 지정|
|path|클라이언트로부터 받은 요청패스 지정|
|method|라우팅 파일 안에 만들어 놓은 객체의 함수 이름을 지정|
|type|get이나 post같은 요청방식 지정|

#### 라우팅 함수를 새로 추가
1. 라우팅 코드가 들어있는 모듈 파일을 추가한다.
2. 새로 만든 라우팅 모듈의 정보를 `config.js`설정 파일 안에 추가한다.

## 07-4 UI 라이브러리로 웹 문서 예쁘게 꾸미기

### Sementic UI 라이브러리로 웹 문서 꾸미기

태그만으로도 버튼이나 입력 상자와 같은 웬만한 UI구성요소를 만들 수 있다.
[http://semantic-ui.com](http://semantic-ui.com)