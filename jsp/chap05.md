# JSP 본격적으로 살펴보기

## JSP 태그의 개념 이해

**JSP**는 Servlet과 반대로 **HTML코드에 JAVA언어를 삽입**하여 동적 문서를 만들 수 있다. (View로 많이 이용한다.)

|            | 태그                           | 설명              |
| ---------- | ------------------------------ | ----------------- |
| 지시자     | <%@ 속성 %>              | 페이지 속성       |
| 주석       | <%— 주석내용  —%>            |                   |
| 선언( declaration ) | <%! java코드 %>                  | 변수, 메소드 선언 |
| 표현식( expression ) | <%= java코드 %>                    | 결과값 출력    |
| 스크립트릿( scriptlet ) | <% java코드 %>                   | JAVA코드          |
| 액션태그   | `<jsp:action>` `</jsp:action>` | 자바빈 연결       |

HTML 코드는 브라우저에서 읽혀진다. (소스 보기를 하면 주석을 다 볼 수 있다.)

JSP는 서버에서 처리하기 때문에 주석은 브라우저에서 보여지지 않는다.



### JSP Scripe

JSP 문서안에 JAVA언어를 넣기 위한 방식들이다. 실제 개발에서 많이 사용

#### 스크립트릿

JSP내에서 JAVA언어 사용하기 위해 가장 많이 사용되는 요소이다.

```jsp
<body>
<%
	int i=0;
	while(true){
        i++;
        out.println("2*"+i+"="+(2*i)+"<br/>");
%>
=======<br>
<%
	if(i>=9)break;
	}
%>
</body>
```

#### 선언

JSP페이지 내에서 사용되는 변수 또는 메소드를 선언할 때 사용한다. 여기서 선언된 변수와 메소드는 **전역** 의 의미로 사용된다.

```jsp
<body>
<%!
	int i =10;
    String str = "ABCDE";
%>
<%!
    public int sum(int a,int b){
	    return 	a+b;
	}
%>
</body>
```

#### 표현식

JSP페이지 내에서 사용되는 변수의 값 또는 메소드 호출 결과값을 출력하기 위해 사용한다. 결과값은 **String 타입**이며, `;`를 사용 할 수 없다.

```jsp
<%!
	int i =10;
    String str = "ABCDE";
%>
<%!
    private int sum(int a,int b){
	    return 	a+b;
	}
%>

<%= i %><br />
<%= str %><br />
<%= sum(1,5) %><br />
```



### 지시자

JSP페이지의 **전체적인 속성**을 지정할 때 사용한다.

| 지시자  | 설명                               |
| ------- | ---------------------------------- |
| page    | 해당 페이지의 전체적인 속성 지정   |
| include | 별도의 페이지를 현재 페이지에 삽입 |
| taglib  | 태그라이브러리의 태그 사용         |

#### page

주로 사용되는 언어 지정 및 import문을 많이 사용한다.

```jsp
<%@ page import="java.util.Arrays" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
```

#### include

현재 페이지에 다른 페이지를 삽입할 때 사용하며, file 속성을 이용한다.

```jsp
<%@ include file="include.jsp" %>
```

#### taglib

**사용자가 만든 tag들을 태그라이브러리**라고 한다. 태그라이브러리를 사용하기 위해 **taglib지시자를 사용** 한다.

**uri 및 prefix 속성**이 있으며, uri는 태그라이브러리의 **위치 값**을 가지며, prefix는 태그를 가리키는 **이름 값**을 가진다.



### 주석

실제 프로그램에는 영향이 없고, **프로그램 설명들의 목적으로 사용되는 태그** 이다.

#### HTML 주석

```html
<!-- 주석 -->
```

#### jsp 주석

```jsp
<%-- 주석 --%>
```



## JSP 동작 원리

![](https://www.javatpoint.com/images/jspflow.JPG)



클라이언트가 웹 브라우저로 `.jsp` 를 요청하게 되면 jsp컨테이너가 jsp파일을 Servlet파일(`.java`)로 변환한다.

그리고 Servlet파일(`.java`)은 컴파일 된 후 클래스 파일(`.class`)로 변환되고, 요청한 클라이언트한테 html파일 형태로 응답한다.

![](http://cfile23.uf.tistory.com/image/1464B1474E65A0C01FCC36)

- servlet이 없는 경우에는 `.java` / `.class ` 를 만들고 메모리에 올려둔다. 그 이후에는 메모리에 올려둔 것을 사용한다. 클라이언트에서 호출할 때마다 생성하는 것이 아니다.

## JSP 내부 원리

개발자가 **객체를 생성하지 않고 바로 사용할 수 있는 객체가 내부객체** 이다. JSP에서 제공되는 내부객체는 J**SP컨테이너에 의해 Servlet으로 변화될 때 자동으로 객체가 생성** 된다.

| 종류        | 객체                   |
| ----------- | ---------------------- |
| 입출력 객체 | request, response, out |
| 서블릿 객체 | page, config           |
| 세션 객체   | session                |
| 예외 객체   | exception              |

### request 객체

웹브라우저를 통해 **서버에 어떤 정보를 요청하는 것을 request**라고 한다. 그리고 이러한 **요청 정보는 request객체가 관리** 한다.

| request 객체 관련 메소드 | 설명                                      |
| ------------------------ | ----------------------------------------- |
| getContextPath()         | 웹 어플리케이션의 context path 를 얻는다. |
| getMethod()              | 세션 객체를 얻는다.                       |
| getProtocol()            | 해당 프로토콜을 얻습니다.                 |
| getRequestURL()          | 요청 URL을 얻는다.                        |
| getRequestURI()          | 요청 URI를 얻는다.                        |
| getQueryString()         | Query String을 얻는다.                    |
| getServerPort()          | 서버 포트를 얻는다.                       |
| getServerName()          | 서버 이름을 얻는다.                       |

```jsp
<% 
	request.getServerName(); 
	request.getServerPort(); 
%>
```

다음과 같이 사용한다.



#### Parameter 메소드

JSP 페이지를 제작하는 목적이 데이터 값을 전송하기 위해서 이므로, parameter관련 메소드는 중요하다.

| Parameter 메소드                | 설명                                 |
| ------------------------------- | ------------------------------------ |
| getParameter(String name)       | name에 해당하는 파라미터 값을 구함.  |
| getParameterNames()             | 모든 파라미터 이름을 구함.           |
| getParameterValues(String name) | name에 해당하는 파라미터값들을 구함. |

```jsp
<%! 
    String name, id, pw;
    String[] majors;
%>

<%
 	request.setCharacterEncoding("UTF-8");
	name = request.getParameter("name");
	name = request.getParameter("id");
	name = request.getParameter("pw");

	majors = request.getParameterValue("majors");
%>
이름 : <%= name %> <br/>
아이디 : <%= id %> <br/>
비밀번호 : <%= pw %> <br/>
전공 : <%= Arrays.toString(majors) %> <br/>
```



### response 객체

**웹브라우저의 요청에 응답하는것을 response**라고 하며, 이러한 응답(response)의 정보를 가지고 있는 객체를 response객체 라고한다.

| response 응답 객체     | 설명                                    |
| ---------------------- | --------------------------------------- |
| getCharacterEncoding() | 응답할때 문자의 인코딩 형태를 구합니다. |
| addCookie(Cookie)      | 쿠키를 지정 합니다.                     |
| sendRedirect(URL)      | 지정한 URL로 이동합니다.                |

```jsp
<%
 	String str  = request.getParameter("age");
	age = Integer.parseInt(str);

	if(age>=20){
        // 지정한 URL, 다른 파일로 보낼 수 있다.
    	response.sendRedirect("pass.jsp?age="+age);
    }else{
        response.sendRedirect("ng.jsp?age="+age);
    }
%>
```