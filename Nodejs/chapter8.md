# 08. 뷰 템플릿 적용하기

자바스크립트 코드 안에 응답 문자열을 입력하는 것보다 응답 웹문서를 별도 파일로 만들어 사용하는 것이 더 좋다.

## 08-1 ejs 뷰 템플릿 사용하기

뷰 템플릿을 사용하면 웹 문서의 기본 형태는 뷰 템플릿으로 만들고 데이터베이스에서 조회한 데이터를 이 템플릿 안의 적당한 위치에 넣어 웹 문서를 만들게된다. 이렇게 뷰 템플릿을 사용해 결과 웹 문서를 자동으로 생성한 후 응답을 보내는 역할을 하는 것이 **View Engine**이다.

### 뷰 템플릿으로 로그인 웹 문서 만들기

```js
//뷰 엔진 설정
app.set('views',__dirname+'/views');
app.set('view enginge','ejs');
console.log('뷰 엔진이 ejs로 설정되었습니다.');
```
`set()`은 속성을 설정하는 역할을 한다.

```ejs
//login_success.ejs
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>로그인 성공 페이지</title>
</head>
<body>
	<h1>로그인 성공</h1>
	<div><p>사용자 아이디 : <% = userid %> </p></div>
	<div><p>사용자 이름 : <% = username %> </p></div>
	<br><br><a href="/public/login.html">다시 로그인하기</a>
</body>
</html>
```
```js
	res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
	var context = {userid:paramId, username:paramName};
	req.app.render('login_success',context,function(err,html){
		if (err) {
			console.log('뷰 렌더링 중 오류 발생'+err.stack);

			res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
			res.write('<h1>뷰 렌더링 중 오류 발생</h1>');
			res.write('<p>' + err.stack+'</p>');
			res.end();

			return;
		}
		console.log('rendered: '+html);

		res.end(html);
	});
```

`render()`메소드를 호출하면 뷰 엔진이 템플릿 파일을 읽어 들인 후 파라미터로 전달한 context객체의 속성으로 들어 있는 값들을 적용하고 그 결과를 콜백함수로 돌려준다.

### 뷰 템플릿으로 사용자 리스트 웹 문서 만들기

```ejs
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>사용자 리스트 페이지</title>
</head>
<body>
	<h2>사용자 리스트</h2>
	<div>
		<ul>
			<% for(var i=0;i<results.length;i++){
				var curId = results[i]._doc.id;
				var curName = results[i]._doc.name;%>
				<li>#<%= i %>-아이디 <%=curId%>,이름: <%=curName%></li>
			<%}%>
		</ul>
	</div>
	<br><br><a href="/public/listuser.html">다시 요청하기</a>
</body>
</html>
```
```js
res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
// 뷰 템플릿을 이용하여 렌더링한 후 전송
var context = {results : results};
req.app.render('listuser',context,function(err,html){
	if(err){throw err;}
	res.end(html);
});
```

### 뷰 템플릿으로 사용자 추가 웹 문서 만들기

```ejs
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>헤드 부분 - ejs에서 include된다.</title>
</head>
<body>
	<h2><%=title%></h2>
	<br><br><a href="/public/login.html">로그인으로 - ejs에서 include됨</a>
</body>
</html>
```
```js
res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
//뷰 템플릿으로 렌더링한 후 전송
var context = {title:'사용자 추가 성공'};
req.app.render('adduser',context,function(err,html){
	if(err){
		console.log('뷰 렌더링 중 오류 발생'+err.stack);
		res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
		res.write('<h2>뷰 렌더링 중 오류 발생</h2>');
		res.write('<p>' + err.stack + '</p>');
		res.end();

		return;
	}
	console.log('rendered:'+html);
	res.end(html);
});
```

## 08-2 pug 뷰 템플릿 사용하기

`pug`포맷은 웹 문서의 태그를 그대로 사용하지 않고 최대한 간단한 형태로 입력하기 때문에 **공백,들여쓰기**를 기준으로 태그의 구조가 결정된다.

[[pugjs.org](http://pugjs.org)]

```js
//뷰 템플릿 설정
app.set('views',__dirname+'/views');
app.set('view engine','pug');
```

### pug로 HTML문서 만들기

`pug`는 공백을 **두 개**사용하여 들여쓰기를 한다.

### pug 템플릿으로 로그인 웹 문서 만들기
```pug
doctype html
html
  head
  	meta(charset='utf8')
  	title 로그인 성공 페이지
  body
  	h1 로그인 성공
  	div
  	  p 사용자 아이디 : #{userid}
  	div
  	  p 사용자 이름 : #{username}
  	br
  	br
  	a(href = '/public/login.html') 다시 로그인하기
```

```js
res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});

//뷰 템플릿으로 렌더링한 후 전송
var context = {userid: paramId,username:username};
req.app.render('login_success',context,function(err,html){
	if(err){throw err;}
	console.log('rendered : '+html);

	res.end(html);
});
```

### pug 템플릿으로 사용자 리스트 웹 문서 만들기

```pug
doctype html
html
  head
    meta(charset='utf8')
    title 사용자 리스트 페이지
  body
    h1 사용자 리스트
    div
      ul
        - for (var i=0;i<results.length;i++){
        -  var curId = results[i]._doc.id;
        -  var curName = results[i]._doc.name;
          li #{i} - 아이디 : #{curId},이름 #{curName}
        - }
    br
    br
    a(href = '/public/listuser.html') 다시 요청하기
```
```js
//뷰 템플릿으로 렌더링한 후 전송
var context = {results : results};
req.app.render('listuser',context,function(err,html){
	if(err){
		console.error('뷰 렌더링 중 오류 발생'+err.stack);

		res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
		res.write('<h2>뷰 렌더링 중 에러 발생</h2>');
		res.write('<p>' + err.stack + '</p>');
		res.end();

		return;
	}
	console.log('rendered : '+html);

	res.end(html);
});
```

### pug 템플릿으로 사용자 추가 웹 문서 만들기

```pug
doctype html
html
  head
    meta(charset='utf8')
    title extends로 상속함
    script(src = 'public/jquery-2.1.4.min.js')
  body
    block content
    include ./footer.pug
```

- `block`코드는 이 파일을 상속받는 파일에서 이 부분을 대체할 수 있다는 것이다.
- `include`는 다른 pug템플릿 파일을 읽어와서 코드를 붙여준다.
```pug
div#fotter
  a(href='/public/login.html') 로그인으로 - pug include됨
```

```pug
extends layout

block content
  h2 #{title}
```

```js
if (addedUser) {
	console.dir(addedUser);

	res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});

	// 뷰 템플릿으로 렌더링한 후 전송
	var context = {title : '사용자 추가 성공'};
	req.app.render('adduser',context,function(err,html){
		if(err){
			console.error('뷰 렌더링 중 오류 발생'+err.stack);

			res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
			res.write('<h2>뷰 렌더링 중 에러 발생</h2>');
		    res.write('<p>' + err.stack + '</p>');
			res.end();

			return;
		}
		console.log('rendered : '+html);

		res.end(html);
	});
}
```