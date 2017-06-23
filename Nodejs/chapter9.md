# 09. 패스포트로 사용자 인증하기

노드의 **Passport**모듈을 사용하면 아주 간단한 작업만으로도 로그인과 회원가입 기능을 만들 수 있다.

## 09-1 패스포트로 로그인하기

**Passport**는 노드에서 사용할 수 있는 사용자 인증 모듈이다. 특히, 익스프레스를 사용할 경우에는 미들웨어로 끼워 넣을 수 있어 몇 가지 간단한 설정만으로도 로그인 기능을 만들 수 있다. 패스포트는 순전히 인증 기능만 담당한다.

- 로컬 인증 방식(Local Strategy) : 데이터베이스에 저장된 사용자 정보와 비교
- OAuth 인증 방식 : 페이스북, 트위터 계정 사용

### 패스포트의 기본 사용 방법 살펴보기

```js
router.route('/login').post(passport.authenticate('local',
  {
	successRedirect: '/',
    failuerRedirect: '/login'
  }
));
```

클라이언트에서 보낸 인증 정보로 인증하려면 `passport.authenticate()`메소드를 호출하면서 동시에 어떤 Strategy를 사용할지 지정해야한다.
```js
router.route('/login').post(passport.authenticate('local'),fucntion(req,res){
	//인증에 성공했을 때 호출
    //`req.user`는 인증된 사용자의 정보임
    res.redirect('/users/',req.user.username);
});
```

`authenticate()`메소드를 호출해 인증을 시도한 후, 인증에 실패했을 때는 디폴트 값으로 401 Unauthorized상태가 응답으로 돌아온다.

### 플래시 메시지와 커스텀 콜백 이해하기

플래시 메시지는 상태 메시지를 응답 웹 문서 쪽으로 전달할 대 사용한다. 플래시 메시지를 사용하려면 `connect-flash`외장 모듈을 사용해야 하므로 먼저 명령 프롬프트 창에서 모듈을 설치해야한다.

`flash()`메소드를 사용할 때 파라미터가 두 개면 플래시 메시지를 설정하는 것이고, 하나면 플래시 메시지를 조회하는 것이다.

```js
req.flash('loginMessage','등록된 계정이 없습니다.');
req.flash('loginMessage');
```

`passport.authenticate()`호출 시 **failuereFlash**옵션을 줄 수 있다. 그러면 인증과정에서 오류가 발생했을 때 플래시 메시지로 오류가 전달된다.

이 오류 메시지는 Strategy설정 시 **검증 콜백(Verify Callback)**이 설정되어 있다면 자동으로 설정된다.

**커스텀 콜백(Custom Callback)**은 인증을 성공했거나 실패했을 때 어떻게 처리할 것인지를 직접 설정할 수 있다.

```js
router.route('/login').get(function(req,res,next){
	passport.authenticate('local',function(err,user,info){
    	if(err){return next(err);}
        if(!user){return res.redirect('/login');}
        //패스포트 인증 결과에 따른 로그인 진행
        req.login(user,function(err){
        	return res.redirect('/users/',user.username);
        });
    })(req,res,next);
});
```
클로저를 통해서 `req`,`res`객체에 접근할 수 있다.

### 스트래티지 설정과 검증 콜백

#### LocalStrategy
```js
var passport = require('passport')
	, LocalStrategy = require('passport-local').Strategy;

passport.use(new LocalStrategy(function(username,password,done){
	UserModel.findOne({username: username},fucntion(err,user){
    	if(err){return done(err);}
        if(!user){
        	return done(null,false,{message: 'Incorrect username'});
        }
        if(!user.validPassword(password)){
        	return done(null,false,{message: 'Incorrct password'});
        }
        return done(null,user);
    });
}));
```

passport의 `use()`메소드를 사용해 스트래티지를 설정할 수 있다. 콜백함수로 전달되는 username,password 파라미터는 클라이언트로부터 전달받은 요청 파라미터이다. 스트래티지를 설정할 때 검증콜백에서 인증 결과를 처리하게 된다. 이 검증 콜백의 목적은 **인증 정보**들을 가지고 있는 사용자를 찾아내는 것이며 클라이언트가 보내 온 요청 파라미터들을 사용해 사용자를 찾아내는 과정을 처리한다.

## 09-2 로컬 인증하기

로그인 이후에는 인증 정보가 전달되지 않는다. 따라서 로그인 이후에 들어오는 요청정보는 세션으로 확인해야한다. 인증에 성공하면 세션이 만들어지고 사용자의 브라우저에 쿠기로 유지된다. 패스포트에서는 로그인 세션을 지원하는데 사용자 인증을 성공했을 때 사용자 정보를 세션에 **저장(Serialize)**하거나 세션으로부터 사용자 정보를 **복원(Deserialize)**할 수 있다.

```js
passport.serializeUser(function(user,done){
	done(null,user.id);
});
...
passport.deserializeUser(function(id,done){
	UserModel.findById(id,function(err,user){
    	done(err,user);
    });
});
```

세션에 사용자 id만 저장하므로써 세션에 저장되는 데이터의 양을 줄일 수 있다.

### 로그인 회원가입 화면을 만들기 위한 라우팅 함수 등록하기

|요청 패스|요청 방식|설명|
|-------|-------|-------|
|/|get|홈 화면 조회|
|/login|get|로그인 화면 조회|
|/login|post|패스포트로 사용자 인증을 처리하는 함수 호출|
|/signup|get|회원가입 화면 조회|
|/signup|post|패스포트로 회원가입을 처리하는 함수 호출|
|/profile|get|사용자 프로필화면 조회|
|/logout|get|로그아웃을 처리하는 함수|

### 뷰 템플릿
|템플릿 이름|설명|
|------|-------|
|index.ejs|홈 화면|
|login.ejs|로그인 화면|
|signup.ejs|회원가입 화면|
|profile.ejs|사용자 프로필 화면|
