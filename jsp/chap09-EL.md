# EL(Expression Language)

## EL이란?

표현식`<%= %>` 또는 액션 태그`<jsp:></jsp:> `를 대신해서 값을 표현하는 언어이다.

EL은 `${value}` 로 표현된다.

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
	${ 10 }<br/>
	${ 99.99 }<br/>
	${ "ABC" }<br/>
	${ true }<br/>
</body>
</html>
```

### EL 연산자

| 연산자 | 종류                  |
| ------ | --------------------- |
| 산술   | +, - , *, /, %        |
| 관계형 | ==, !=, <, > , <=, >= |
| 조건   | a?b:c                 |
| 논리   | &&, \|\|              |

```jsp
${ 1+2 }
${ 1-2 }
${ 1*2 }
${ (1>2)?1:2 }
```



## 액션태그로 사용되는 EL

`<jsp:getProperty name=*"member" property="name"/>* ` 를 `${ member.name } ` 로 사용할 수 있다.

```java
package com.javalec.ex;

public class MemberInfo {

		private String name;
		private String id;
		private String pw;
		
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
		public String getId() {
			return id;
		}
		public void setId(String id) {
			this.id = id;
		}
		public String getPw() {
			return pw;
		}
		public void setPw(String pw) {
			this.pw = pw;
		}
}

```

```jsp
<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<jsp:useBean id="member" class="com.javalec.ex.MemberInfo" scope="page" />
<jsp:setProperty name="member" property="name" value="이름"/>
<jsp:setProperty name="member" property="id" value="abc"/>
<jsp:setProperty name="member" property="pw" value="123"/>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
	이름 : <jsp:getProperty name="member" property="name"/><br />
	아이디 : <jsp:getProperty name="member" property="id"/><br />
	비밀번호 : <jsp:getProperty name="member" property="pw"/><br />
	
	<hr />
	
	이름 : ${ member.name }<br />
	아이다 : ${ member.id }<br />
	비밀번호 : ${ member.pw }<br />
	
</body>
</html>
```



## 내장 객체



| 내장 객체        | 설명                                |
| ---------------- | ----------------------------------- |
| pageScope        | page객체를 참조하는 객체            |
| requestScope     | request객체를 참조하는 객체         |
| sessionScope     | session객체를 참조하는 객체         |
| applicationScope | application객체를 참조하는 객체     |
| param            | 요청 파라미터를 참조하는 객제       |
| paramValues      | 요청 파라미터(배열)를 참조하는 객제 |
| initParam        | 초기화 파라미터를 참조하는 객체     |
| cookie           | cookie객체를 참조하는 객체          |

### web.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://java.sun.com/xml/ns/javaee" xsi:schemaLocation="http://java.sun.com/xml/ns/javaee http://java.sun.com/xml/ns/javaee/web-app_3_0.xsd" id="WebApp_ID" version="3.0">
  <display-name>jsp_23_3_ex1_elex</display-name>
  <welcome-file-list>
    <welcome-file>index.html</welcome-file>
    <welcome-file>index.htm</welcome-file>
    <welcome-file>index.jsp</welcome-file>
    <welcome-file>default.html</welcome-file>
    <welcome-file>default.htm</welcome-file>
    <welcome-file>default.jsp</welcome-file>
  </welcome-file-list>
  
  <context-param>
  	<param-name>con_name</param-name>
  	<param-value>con_name은 홍길동 입니다.</param-value>
  </context-param>
  <context-param>
  	<param-name>con_id</param-name>
  	<param-value>con_id는 abcde 입니다.</param-value>
  </context-param>
  <context-param>
  	<param-name>con_pw</param-name>
  	<param-value>con_pw는 12345 입니다.</param-value>
  </context-param>
  
</web-app>
```

여러 servlet에서 특정 데이터를 공유해야하는 경우 context parameter를 이용해서 공유하면서 사용할 수 있다.

### obj.jsp

```jsp
<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
	
	<form action="objelOk.jsp" method="get">
		아이디 : <input type="text" name="id"><br />
		비밀번호 : <input type="password" name="pw">
		<input type="submit" value="login">
	</form>
	
	<% 
		application.setAttribute("application_name", "application_value");
		session.setAttribute("session_name", "session_value");
		pageContext.setAttribute("page_name", "page_value");
		request.setAttribute("request_name", "request_value");
	%>
	
</body>
</html>
```

#### objelOk.jsp

```jsp
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
		String id = request.getParameter("id");
		String pw = request.getParameter("pw");
	%>
	
	아이디 : <%= id %> <br />
	비밀번호 : <%= pw %>
	
	<hr />
	
	아이디 : ${ param.id } <br />
	비밀번호 : ${ param.pw } <br />
	아이디 : ${ param["id"] } <br />
	비밀번호 : ${ param["pw"] }
	
	<hr />
	
	applicationScope : ${ applicationScope.application_name }<br />
	sessionScope : ${ sessionScope.session_name }<br />
	pageScope : ${ pageScope.page_name }<br />
	requestScope : ${ requestScope.request_name }
	
	<hr />
	<!-- context parameter값을 참조해서 가져 올 수 있다.-->
	context 초기화 파라미터<br />
	${ initParam.con_name } <br />
	${ initParam.con_id } <br />
	${ initParam.con_pw } <br />
</body>
</html>
```



EL표기법을 통해서 코드가 긴 것(가독성이 떨어지는)을 더 간단하게 구현할 수 있다.