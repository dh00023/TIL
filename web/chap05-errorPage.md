# 예외 페이지

## 예외 페이지의 필요성

JSP, Servlet에서 예외가 발생할 수 있다.

예외적인 상황이 발생했을 경우 웹컨테이너(tomcat)에서 제공되는 기본적인 예외 페이지가 보여집니다. 약간은 딱딱한 에러 페이지를 보다 친근한 느낌이 느껴지는 페이지로 유도할 수 있다.

## 예외 처리

### HTTP Status [[→http status 자세히 알아보기]](https://developer.mozilla.org/ko/docs/Web/HTTP/Status)

| HTTP Status | 설명                     |
| ----------- | ------------------------ |
| 500 Internal Server Error         | The server has encountered a situation it doesn't know how to handle.                 |
| 200 OK        | 정상적으로 완료된 페이지 |
| 404 Not Found        |The server can not find requested resource.|



### 페이지 지시자 이용하기

페이지 지시자를 이용해서 페이지가 발생하면 errorPage.jsp로 이동하도록 할 수 있다.

#### Error발생 페이지

```jsp
<%@ page errorPage = "errorPage.jsp" %>
```

#### Error발생 후 오류 페이지

isErrorPage가 true이면 exception 객체를 통해서 오류를 가져올 수 있다.

```jsp
<!-- isErrorPage 는 false가 default값이므로 true로 변경해줘야한다.-->
<%@ page isErrorPage = true %>
<!-- 정상페이지라고 설정해줘야한다.(오류난 페이지의 상태로 설정하는 경우를 방지하기 위해서)-->
<% response.setStatus(200); %>

<%= exception.getMessage() %>
```


#### 예제 코드

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page errorPage="pageError.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		int i = 40/0;
	%>
</body>
</html>
```

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page isErrorPage="true" %>
<% response.setStatus(200); %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h1>오류 발생!</h1>
	<%= exception.getMessage() %>
</body>
</html>
```



### web.xml 이용하기

#### xml 코드

```xml
  <error-page>
  	<error-code>404</error-code>
  	<location>/error404.jsp</location>
  </error-page>
  <error-page>
  	<error-code>500</error-code>
  	<location>/error500.jsp</location>
  </error-page>
```

#### error jsp 코드

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page isErrorPage="true" %>
<% response.setStatus(200); %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	500 오류입니다.
</body>
</html>
```

