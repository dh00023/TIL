# JSP 액션태그

## 액션 태그란?

JSP페이지 내에서 어떠한 동작을 하도록 지식하는 태그이다. 예를 들어서 페이지 이동, 페이지 include 등등이다.

forward, include, param이외의 태그는 bean을 배운 후에 다뤄볼 것이다.

### forward 태그

현재 페이지에서 **다른 특정 페이지로 전환**할 때 사용한다.

```jsp
<%-- Main.jsp -- %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h1>Main page</h1>
	<jsp:forward page="testt.jsp"></jsp:forward>
</body>
</html>
```

```java
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h1>Test Page</h1>
</body>
</html>
```

Main page가 로딩되자마자 forward태그로 testt.jsp페이지로 전환한다. 이때 url은 변경되지 않고 forwarding한 페이지가 보이는 것을 확인할 수 있다.

### include 태그

현재 페이지에 다른 페이지를 삽입할 때 사용한다.

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
	<h1>include 1 페이지입니다.</h1>
	<jsp:include page="include2.jsp"></jsp:include>
	<h1>다시 include 1 페이지입니다.</h1>
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
	<h1>include 2 페이지입니다.</h1>
</body>
</html>
```

```jsp
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h1>include 1 페이지입니다.</h1>
	
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h1>include 2 페이지입니다.</h1>
</body>
</html>
	<h1>다시 include 1 페이지입니다.</h1>
</body>
</html>
```

source코드를 보면 include1.jsp를 불러온 후에 include2.jsp를 불러와 포함시킨 것을 확인 할 수 있다.

페이지 지시자를 통해서 포함할 수도 있고, include action태그를 통해서 구현할 수도 있다.

### param 태그

forward 및 include 태그에 **데이터를 전달을 목적**으로 사용하는 태그이다. `name` 과 `value`로 이루어져 있다.

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
	<jsp:forward page="param.jsp">
		<jsp:param value="abcd" name="id"/>
		<jsp:param value="1234" name="pw"/>
	</jsp:forward>
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
		String id, pw; 
	%>
	<% 
		id = request.getParameter("id"); 
		pw = request.getParameter("pw");
	%>
	<h1>params를 받아왔습니다.</h1>
	id: <%= id %>
	pw: <%= pw %>
</body>
</html>
```

params 태그를 이용해서 값을 받아올 수 있다.