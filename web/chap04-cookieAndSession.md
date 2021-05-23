# Cookie And Session 

## Cookie

### 쿠키란?

웹브라우저에서 서버로 데이터를 요청하면, 서버측에서는 알맞은 로직을 수행한 후 데이터를 웹브라우저에 응답한 후 서버는 웹브라우저와 **관계를 종료**한다.(http 프로토콜 특징)

**연결이 끊겼을 때 어떤 정보를 지속적으로 유지하기 위한 수단으로 쿠키를 사용**한다. **쿠키는 서버에서 생성하며, 서버가 아닌 클라이언트측에 특정 정보를 저장한다**. 서버에 요청할 때 마다 쿠키의 속성값을 참조 또는 변경할 수 있다.

쿠키는 4kb로 용량이 제한적이며, 300개까지 데이터 정보를 가질 수 있다.



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
	<% 
		Cookie cookie = new Cookie("CookieName","CookieValue");
		/* 얼마동안 유지될 것인지 최대 수명이다. */
		cookie.setMaxAge(60*60);
		response.addCookie(cookie);
	%>
```

```jsp
	<%
		Cookie[] cookies = request.getCookies();
	
		for(int i=0;i<cookies.length;i++){
			out.println("cookies[" + i + "] name : " + cookies[i].getName() + "<br />");
			out.println("cookies[" + i + "] value : " + cookies[i].getValue() + "<br />");
			out.println("=====================<br />");
		}
	%>
```

쿠키 삭제는 유효기간 setMaxAge를 0으로 설정하고 속성 변경한 것을 response 객체에 적용하면된다.

```jsp
	<%
		Cookie[] cookies = request.getCookies();
		for(int i=0;i<cookies.length;i++){
			out.println("cookie name : "+cookies[i].getName() );
			cookies[i].setMaxAge(0);
			response.addCookie(cookies[i]);
		}
	%>
```
- 쿠키 사용 예제
  - 자동 로그인
  - 팝업  ex)"오늘 더 이상 이 창을 보지 않음"
  - 쇼핑몰의 장바구니

쿠키는 보안상의 문제가 있을 수 있다. 해킹과 같은 하지만 꼭 알고 있어야하는 개념이다.


## 세션

### 세션이란?

![](http://cfile9.uf.tistory.com/image/112A2F374E1D5C74352D28)

세션도 쿠키와 마찬가지로 서버와의 관계를 유지하기 위한 수단이다.

단, 쿠키와 달리 클라이언트의 특정 위치에 저장되는 것이 아니라, **서버상에 객체로 존재한다.** (쿠키는 로컬상에 저장되기 때문에 보안에 취약하다.)따라서 **세션은 서버에서만 접근이 가능하여 보안이 좋고, 저장할 수 있는 데이터에 한계가 없다.**

로그인과 같이 정보를 저장할 때 많이 사용된다.

### 문법

세션은 클라이언트의 요청이 발생하면 자동으로 생성된다. session이라는 내부 객체를 지원하여 세션의 속성을 설정할 수 있다.

![](http://cfs7.tistory.com/image/28/tistory/2008/07/20/21/05/488329f68fcc7)



| 관련 메소드              | 설명                                                         |
| ------------------------ | ------------------------------------------------------------ |
| setAttribute()           | 세션에 데이터를 저장 합니다.                                 |
| getAttribute()           | 세션에서 데이터를 얻습니다.                                  |
| getAttributeNames()      | 세션에 저장되어 있는 모든 데이터의 이름(유니크한 키값)을 얻습니다. |
| getId()                  | 자동 생성된 세션의 유니크한 아이디를 얻습니다.               |
| isNew()                  | 세션이 최초 생성되었는지, 이전에 생성된 세션인지를 구분 합니다. |
| getMaxInactiveInterval() | 세션의 유효시간을 얻습니다. 가장 최근 **요청시점을 기준으로 카운트**됩니다.<br>(C:\javalec\apache-tomcat-7.0.57\apache-tomcat-7.0.57\conf\web.xml 참조) |
| removeAttribute()        | 세션에서 특정 데이터 제거 합니다.                            |
| Invalidate()             | 세션의 모든 데이터를 삭제 합니다.                            |

session.getAttribute()는 **Object타입으로 반환**된다. 변환이 필요하다.



#### Init

```jsp
	<%
		session.setAttribute("sessionName", "sessionValue");
		session.setAttribute("abcde", 12345);
	%>
```

#### Get

```jsp
	<%
		Object obj1 = session.getAttribute("mySessionName");
		String mySessionName = (String)obj1;
		out.println(mySessionName +"<br />");
	%>
```

세션은 로그인 정보를 유지하는데 있어서 가장 많이 사용한다.

## Session vs Cookie

| 차이점        | Session                                                | Cookie                                          |
| ------------- | ------------------------------------------------------ | ----------------------------------------------- |
| 저장위치      | 서버에 저장                                            | 클라이언트에 저장                               |
| 보안          | 보안 수준 높음                                         | 보안 취약 <br />클라이언트 로컬에 저장되기 때문 |
| 라이프 사이클 | 세션도 만료시점을 정할 수 있지만, 브라우저 종료시 삭제 | 지정한 쿠키 만료시간                            |

 세션은 서버의 자원을 사용하기때문에 무분별하게 만들다보면 서버의 메모리가 감당할 수 없어질 수가 있고 속도가 느려질 수 있기 때문에 주의해야한다.


## 예제

### 쿠키

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


### 세션

#### 로그인

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<form action="logincheck2.jsp" method="post">
		아이디 : <input type="text" name="id" size="10"><br>
		비밀번호 : <input type="password" name="pw" size="10">
		<input type="submit" value="제출">
	</form>
</body>
</html>
```

#### 로그인확인

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
			session.setAttribute("id", id);
			response.sendRedirect("welcome2.jsp");
		}else{
			response.sendRedirect("login.html");
		}
		
	%>


</body>
</html>
```

#### 로그인 후 화면

```jsp
<%@page import="java.util.Enumeration"%>
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
		String sName, sValue;
		Enumeration enumeration = session.getAttributeNames();
		
		while(enumeration.hasMoreElements()){
			sName = enumeration.nextElement().toString();
			sValue = session.getAttribute(sName).toString();
			out.println( sValue + "님 안녕하세요!<br />");
		}
		
	%>
	
	<a href="logout2.jsp">로그아웃하기</a>
</body>
</html>
```



#### 로그아웃(세션 삭제)

```jsp
<%@page import="java.util.Enumeration"%>
<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
	
	<%
		Enumeration enumeration = session.getAttributeNames();
		while(enumeration.hasMoreElements()) {
			String sName = enumeration.nextElement().toString();
			String sValue = (String)session.getAttribute(sName);
			
			if(sValue.equals("abcde")) session.removeAttribute(sName);
		}
		
	%>
	
	<a href="sessiontest.jsp">sessionTest</a>
	
</body>
</html>
```



## 참고페이지

- [기본기를 쌓는 정아마추어 코딩블로그](https://jeong-pro.tistory.com/80 )