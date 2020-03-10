# 세션

## 세션이란?

![](http://cfile9.uf.tistory.com/image/112A2F374E1D5C74352D28)

세션도 쿠키와 마찬가지로 서버와의 관계를 유지하기 위한 수단이다.

단, 쿠키와 달리 클라이언트의 특정 위치에 저장되는 것이 아니라, **서버상에 객체로 존재한다.** (쿠키는 로컬상에 저장되기 때문에 보안에 취약하다.)

따라서 **세션은 서버에서만 접근이 가능하여 보안이 좋고, 저장할 수 있는 데이터에 한계가 없다.**

로그인과 같이 정보를 저장할 때 많이 사용된다.

## 문법

세션은 클라이언트의 요청이 발생하면 자동으로 생성된다. session이라는 내부 객체를 지원하여 세션의 속성을 설정할 수 있다.

![](http://cfs7.tistory.com/image/28/tistory/2008/07/20/21/05/488329f68fcc7)



| 관련 메소드                                                  | 설명 |
| ------------------------------------------------------------ | ---- |
| setAttribute() | 세션에 데이터를 저장 합니다.                |
| getAttribute()| 세션에서 데이터를 얻습니다.                 |
| getAttributeNames() | 세션에 저장되어 있는 모든 데이터의 이름(유니크한 키값)을 얻습니다. |
| getId() | 자동 생성된 세션의 유니크한 아이디를 얻습니다.     |
| isNew() | 세션이 최초 생성되었는지, 이전에 생성된 세션인지를 구분 합니다. |
| getMaxInactiveInterval() | 세션의 유효시간을 얻습니다. 가장 최근 **요청시점을 기준으로 카운트**됩니다.<br>(C:\javalec\apache-tomcat-7.0.57\apache-tomcat-7.0.57\conf\web.xml 참조)  |
| removeAttribute() | 세션에서 특정 데이터 제거 합니다.        |
| Invalidate() | 세션의 모든 데이터를 삭제 합니다.             |

session.getAttribute()는 **Object타입으로 반환**된다. 변환이 필요하다.



### Init

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
		session.setAttribute("sessionName", "sessionValue");
		session.setAttribute("abcde", 12345);
	%>
	<a href="sessionget.jsp">session get</a>
</body>
</html>
```



### Get

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
		Object obj1 = session.getAttribute("mySessionName");
		String mySessionName = (String)obj1;
		out.println(mySessionName +"<br />");
		
		Object obj2 = session.getAttribute("myNum");
		Integer myNum = (Integer)obj2;
		out.println(myNum +"<br />");
		
		out.println("************************ <br />");
		
		String sName;
		String sValue;
		Enumeration enumeration = session.getAttributeNames();
		while(enumeration.hasMoreElements()){
			sName = enumeration.nextElement().toString();
			sValue = session.getAttribute(sName).toString();
			out.println("sName : " + sName + "<br />");
			out.println("sValue : " + sValue + "<br />");
		}
		
		out.println("************************ <br />");
		
		String sessionID = session.getId();
		out.println("sessionID : " + sessionID + "<br />");
		int sessionInter =  session.getMaxInactiveInterval();
		out.println("sessionInter : " + sessionInter + "<br />");
		
		out.println("************************ <br />");
		
		session.removeAttribute("mySessionName");
		Enumeration enumeration1 = session.getAttributeNames();
		while(enumeration1.hasMoreElements()){
			sName = enumeration1.nextElement().toString();
			sValue = session.getAttribute(sName).toString();
			out.println("sName : " + sName + "<br />");
			out.println("sValue : " + sValue + "<br />");
		}
		
		out.println("************************ <br />");
		
		session.invalidate();
		if(request.isRequestedSessionIdValid()) {
			out.println("session valid");
		} else {
			out.println("session invalid");
		}
	%>

</body>
</html>
```

## 예제

### 로그인

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

### 로그인확인

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

### 로그인 후 화면

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



### 로그아웃(세션 삭제)

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

