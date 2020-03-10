# 쿠키

## 쿠키란?

웹브라우저에서 서버로 데이터를 요청하면, 서버측에서는 알맞은 로직을 수행한 후 데이터를 웹브라우저에 응답한 후 서버는 웹브라우저와 **관계를 종료**한다.(http 프로토콜 특징)

**연결이 끊겼을 때 어떤 정보를 지속적으로 유지하기 위한 수단으로 쿠키를 사용**한다.

**쿠키는 서버에서 생성하며, 서버가 아닌 클라이언트측에 특정 정보를 저장한다**. 서버에 요청할 때 마다 쿠키의 속성값을 참조 또는 변경할 수 있다.

쿠키는 4kb로 용량이 제한적이며, 300개까지 데이터 정보를 가질 수 있다.

## 쿠키문법

![](http://mblogthumb4.phinf.naver.net/20141119_43/cds0915_1416372429384ItcNc_PNG/cookie.png?type=w2)



| 메소드                                                | 설명                         |
| ----------------------------------------------------- | ---------------------------- |
| setMaxAge()                                           | 쿠키 유효기간을 설정 합니다. |
| setpath() |쿠키사용의 유효 디렉토리를 설정 합니다.   |
| setValue() | 쿠키의 값을 설정 합니다.                 |
| setVersion() | 쿠키 버전을 설정 합니다.               |
| getMaxAge() | 쿠키 유효기간 정보를 얻습니다.          |
| getName() | 쿠키 이름을 얻습니다.                     |
| getPath() | 쿠키사용의 유효 디렉토리 정보를 얻습니다. |
| getValue() | 쿠키의 값을 얻습니다.                    |
| getVersion() | 쿠키 버전을 얻습니다.                  |

쿠키 생성(서버) → 속성 설정 →response객체에 탑재 순서로 진행된다.

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<% 
		Cookie cookie = new Cookie("CookieName","CookieValue");
		/* 얼마동안 유지될 것인지 최대 수명이다. */
		cookie.setMaxAge(60*60);
		response.addCookie(cookie);
	%>
	
	<a href="cookieget.jsp">cookie get</a>
</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Cookie[] cookies = request.getCookies();
	
		for(int i=0;i<cookies.length;i++){
			out.println("cookies[" + i + "] name : " + cookies[i].getName() + "<br />");
			out.println("cookies[" + i + "] value : " + cookies[i].getValue() + "<br />");
			out.println("=====================<br />");
		}
	%>
	
	<a href="cookiedel.jsp">cookie delete</a>
</body>
</html>
```

쿠키 삭제는 유효기간 setMaxAge를 0으로 설정하고 속성 변경한 것을 response 객체에 적용하면된다.

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Cookie[] cookies = request.getCookies();
		for(int i=0;i<cookies.length;i++){
			out.println("cookie name : "+cookies[i].getName() );
			cookies[i].setMaxAge(0);
			response.addCookie(cookies[i]);
		}
	%>
</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Cookie[] cookies = request.getCookies();
	
		if(cookies!=null){
			for(int i=0;i<cookies.length;i++){
				out.println("Cookie Name : "+cookies[i].getName());
				out.println("Cookie Value : "+cookies[i].getValue());
			}
		}else{
			out.println("삭제성공 ");	
		}
	%>
</body>
</html>
```



## 예제

쿠키를 가장 많이 이용하는 예제는 로그인이다.

```html
<!--login.html-->
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<form action="logincheck.jsp" method="post">
		아이디 : <input type="text" name="id" size="10"><br>
		비밀번호 : <input type="password" name="pw" size="10">
		<input type="submit" value="제출">
	</form>
</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%!
		String id,pw; 
	%>
	<%
		id = request.getParameter("id");
		pw = request.getParameter("pw");
		
		if(id.equals("abcde")&&pw.equals("12345")){
			Cookie cookie = new Cookie("id",id);
			cookie.setMaxAge(60*60);
			response.addCookie(cookie);
			response.sendRedirect("welcome.jsp");
		}else{
			response.sendRedirect("login.html");
		}
		
	%>

</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Cookie[] cookies = request.getCookies();
		
		if(cookies!=null){
			for(int i=0;i<cookies.length;i++){
				if(cookies[i].getValue().equals("abcde")){
					cookies[i].setMaxAge(0);
					response.addCookie(cookies[i]);
				}
			}	
		}
		
		response.sendRedirect("cookietest.jsp");
		
	%>

</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Cookie[] cookies = request.getCookies();
		
		for(int i=0;i<cookies.length;i++){
			String id = cookies[i].getValue();
			if(id.equals("abcde"))
				out.println(id  + "님 안녕하세요!");
		}
		
	%>
	
	<a href="logout.jsp">로그아웃하기</a>
</body>
</html>
```



쿠키는 보안상의 문제가 있을 수 있다. 해킹과 같은 하지만 꼭 알고 있어야하는 개념이다.