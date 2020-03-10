# JSTL(JSPstandard Tag Library)

## JSTL 개요 및 설치

JSP의 경우에는 HTML 태그와 같이 사용되어서 전체적인 코드의 가독성이 떨어진다. JSTL은 이러한 단점을 보완하고자 만들어진 태그 라이브러리이다.

#### 설치

[http://archive.apache.org/dist/jakarta/taglibs/standard/binaries/](http://archive.apache.org/dist/jakarta/taglibs/standard/binaries/) 에서  jakarta-taglibs-standard-1.1.2.zip를 다운받는다.

다운받아서 압축을 풀면 `/lib` 폴더 내에 있는 `jstl.jar` 파일과 `standard.jar` 파일을 apache 폴더 lib안에 붙여넣어준다.

## JSTL 라이브러리

다섯가지의 라이브러리를 지원해준다.

| lib             | URI                                    | Prefix | ex            |
| --------------- | -------------------------------------- | ------ | ------------- |
| Core            | http://java.sun.com/jsp/jstl/core      | c      | <c:tag        |
| XML Processing  | http://java.sun.com/jsp/jstl/xml       | x      | <x:tag        |
| I18N formatting | http://java.sun.com/jsp/jstl/fmt       | fmt    | <fmt:tag      |
| SQL             | http://java.sun.com/jsp/jstl/sql       | sql    | <sql:tag      |
| Functions       | http://java.sun.com/jsp/jstl/functions | fn     | fn:function() |



### Core

가장 기본적인 라이브러리로 출력, 제어문, 반복문과 같은 기능이 포함되어있다.

```jsp
<%@ taglib uri=http://java.sun.com/jsp/jstl/core prefix=“c” %>
```

해당 코어 라이브러리를 `c`로 쓰겠다고 prefix 해준다.

#### 출력태그 `<c:out>`

```jsp
<c:out value=“출력값” default=“기본값” escapeXml=“true or false”>
```

#### 변수 설정 태그 `<c:set>`

```jsp
<c:set var=“변수명” value=“설정값” target=“객체” property=“값” scope=“범위”>
```

#### 변수 제거 `<c:remove>`

```jsp
<c:remove var=“변수명” scope=“범위”>
```

#### 예외처리 `<c:catch>`

```jsp
<c:catch var=“변수명”>
```

#### 제어문(if) `<c:if>`

```jsp
<c:if test=“조건” var=“조건 처리 변수명” scope=“범위”>
```

#### 제어문(switch) `<c:choose>`

```jsp
<c:choose>
<c:when test=“조건”> 처리 내용 </c:when>
<c:otherwise> 처리 내용 </c:otherwise>
</c:choose>
```

#### 반복문(for) `<c:forEach>`

```jsp
<c:forEach items=“객체명” begin=“시작 인덱스” end=“끝 인덱스” step=“증감식” var=“변수명” varStatus=“상태변수”>
```

#### 페이지 이동 `<c:redirect>`

```jsp
<c:redirect url=“url”>
```

#### 파라미터 전달 `<c:param>`

```jsp
<c:param name=“파라미터명” value=“값”>
```



#### 예제

```jsp
<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>

	<c:set var="vatName" value="varValue"/>
	vatName : <c:out value="${vatName}"/>
	<br />
	<c:remove var="vatName"/>
	vatName : <c:out value="${vatName}"/></h3>
	
	<hr />
	
	<c:catch var="error">
		<%=2/0%>
	</c:catch>
	<br />
	<c:out value="${error}"/>
	
	<hr />

	<c:if test="${1+2==3}">
		1 + 2 = 3
	</c:if>
	
	<c:if test="${1+2!=3}">
		1 + 2 != 3
	</c:if>
	
	<hr />

	<c:forEach var="fEach" begin="0" end="30" step="3">
		${fEach}
	</c:forEach>

</body>
</html>
```

```
vatName : varValue 
vatName :

java.lang.ArithmeticException: / by zero
1 + 2 = 3
0 3 6 9 12 15 18 21 24 27 30
```

