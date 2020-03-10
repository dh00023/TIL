# 4. Servlet 본격적으로 살펴보기

servlet은 **JAVA언어를 사용하여 웹프로그램을 제작**하는 것이다.

```java
/**
 * Servlet implementation class HelloWorld
 */
@WebServlet("/HelloWorld")
public class HelloWorld extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */

```

Servlet Class는 HttpServlet 클래스를 상속받는다. 그렇기 때문에 Servlet 인터페이스와 GenericServlet, HttpServlet의 기능을 사용할 수 있다.

![](./images/12.png)

### 요청 / 응답 처리

요청 처리 객체 및 응답 처리 객체를 톰캣에서 받는다.

```java
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	...
}
/**
* @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
*/
protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	}
}

```

- `HttpServletRequest` : 클라이언트의 요청 처리 객체
- `HttpServletResponse` : 클라이언트에게 응답 처리 객체

#### doGet()

**GET 방식 : URL 값으로 정보가 전송되어 보안에 약함** 

```
Get : http://IP주소:port번호/컨텍스트/path/MemberJoin?id=“abcdefg”&name=“홍길동”
```

다음과 같이 url 값으로 정보가 전송되는 방법이다.

- html form 태그의 method 속성이 get인 경우 호출된다.

```xml
<form action="GetMethod" method="get"></form>
```

- 웹브라우저의 주소창을 이용해 servlet을 요청한 경우에도 호출된다.

```java
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doGet");
		// 무엇으로 응답할 지 구현해 줘야한다.
    	// 한글지정 charset=euc-kr
		response.setContentType("text/html; charset=euc-kr");

    	//웹 브라우저에 출력하기 위한 스트림  
		PrintWriter writer = response.getWriter();
		
		writer.println("<html>");
		writer.println("<head>");
		writer.println("</head>");
		writer.println("<body>");
		writer.println("<h1>Hello World</h1>");
		writer.println("</body>");
		writer.println("</html>");
		
		writer.close();
	}
```

#### doPost()

**POST 방식 : header를 이용해 정보가 전송되어 보안에 강하다.** 

```
Post : http://IP주소:port번호/컨텍스트/path/MemberJoin
```

- html form 태그의 method 속성이 post인 경우 호출된다.

```xml
<!-- post.html -->
<form action="PostMethod" method="post">
	<input type="sublmit" value="post">
</form>
```

```java
//PostMethod.java (servlet)
//...
protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doPost");
		
		response.setContentType("text/html; charset=euc-kr");
		PrintWriter writer = response.getWriter();
		writer.println("<html>");
		writer.println("<head>");
		writer.println("</head>");
		writer.println("<body>");
		writer.println("<h1>POST 방식입니다..</h1>");
		writer.println("</body>");
		writer.println("</html>");
	}
  
```

### Context Path

WAS(Web Application Server)에서 웹어플리케이션을 구분하기 위한 path 입니다. 이클립스에서 프로젝트를 생성하면, 자동으로 server.xml에 추가 됩니다.

```xml
<Valve className="org.apache.catalina.valves.AccessLogValve" directory="logs" pattern="%h %l %u %t &quot;%r&quot; %s %b" prefix="localhost_access_log" suffix=".txt"/>

      <Context docBase="ch05" path="/ch05" reloadable="true" source="org.eclipse.jst.jee.server:ch05"/></Host>
```



### Servlet 작동 순서

클라이언트에서 servlet 요청이 들어오면 서버에서는 servlet 컨테이너를 만들고 요청이 있을 때마다 스레드가 생성된다.

스레드를 이용해 request를 처리해 서버의 부하가 적게 걸린다. 

![](http://www.geeklabs.co.in/images/rt-sol/introserv/Servlet%20Achitecture.jpg)

Servlet 컨테이너에서 1. 스레드 생성 2. servlet 객체를 생성한다.



### Servlet life cycle(생명주기)

Servlet의 사용도가 높은 이유는 **빠른 응답 속도** 때문이다. Servlet은 최초 요청 시 객체가 만들어져 메모리에 로딩되고, 이후 요청에는 기존의 객체를 재활용하게 되므로 동작 속도가 빠르다.

![servlet life cycleì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](http://1.bp.blogspot.com/-f3E1HmjaxnY/VIND_AhjJ2I/AAAAAAAAABw/txxrGXKdxj0/s1600/servlet%2Blifecycle.png)



```java
@WebServlet("/LifeCycleEx")
public class LifeCycleEx extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LifeCycleEx() {
        super();
        // TODO Auto-generated constructor stub
    }

//	@Override
//	public void service(ServletRequest arg0, ServletResponse arg1)
//			throws ServletException, IOException {
//		// TODO Auto-generated method stub
//		System.out.println("service");
//	}
    
    @Override
    public void init() throws ServletException {
    	// TODO Auto-generated method stub
    	System.out.println("init");
    }

	@Override
	public void destroy() {
		// TODO Auto-generated method stub
		System.out.println("destroy");
	}


	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doGet");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doPost");
	}
}
```

```
init
doGet
doGet
doGet
destroy
```

새로 고침하면 doGet만 반복해서 호출되는 것을 확인할 수 있다. 어느 시점에 호출이 되는지 알고 있어야한다.

### Servlet 선처리 / 후처리

![](http://cfile1.uf.tistory.com/image/277C893E56869D23018D3B)

#### 선처리 @PostConstruct

init전에 한번 호출되는 것

```java
@PostConstruct
private void initPostConstruct() {
	// TODO Auto-generated method stub
	System.out.println("initPostConstruct");
}
```



#### 후처리 @PreDestroy

destroy 후에 호출된다.

```java
@PreDestroy
private void destoryPreDestory() {
	// TODO Auto-generated method stub
	System.out.println("destoryPreDestory");
}
```

```
initPostConstruct
init
doGet
doGet
doGet
doGet
destroy
destoryPreDestory
```



### HTML Form tag

form태그는 서버쪽으로 정보를 전달할 때 사용하는 태그이다.[[HTML - form](https://dh00023.gitbooks.io/til/HTML&CSS/chapter4.html) ]태그와 관련해서 정리해둔 자료이다.

```html
<form action="요청하는 컴포넌트 이름" method=["post"|"get"]>
</form>
```

요청하는 컴포넌트 이름에는 이동할 위치를 넣어준다. (ex) join.jsp, info.html, HWorldServlet Parameter

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<form action="FormMethod" method="get">
		이름 : <input type="text" name="name" size="10"><br/>
		아이디: <input type="text" name="id" size="10"><br/>
		비밀번호 : <input type="password" name="pw" size="10"><br/>
		취미 : <input type="checkbox" name="hobby" value="read">독서
		<input type="checkbox" name="hobby" value="cook">요리
		<input type="checkbox" name="hobby" value="run">조깅
		<input type="checkbox" name="hobby" value="swim">수영
		<input type="checkbox" name="hobby" value="sleep">취침<br/>
		<input type="radio" name="major" value="kor">국어
		<input type="radio" name="major" value="eng" checked="checked">영어
		<input type="radio" name="major" value="mat" >수학
		<input type="radio" name="major" value="des" >디자인<br/>
		<select name="protocol">
			<option value="http">http</option>
			<option value="ftp" selected="selected">ftp</option>
			<option value="smtp">smtp</option>
			<option value="pop">pop</option>
		</select><br/>
		<input type="submit" value="제출"><input type="reset" value="초기화">
	</form>
</body>
</html>
```



### Servlet Parameter

form 태그의 submit 버튼을 클릭하여 데이터를 서버로 전송하면, 해당파일(servlet)에서는 **HttpServletRequest 객체를 이용해서 Parameter값을 얻을 수 있다**.

반환값은 다 String이다.

- getParameter(name) : name에 해당하는 value값을 리턴
- getParameterValues(name) : value값들이 여러개인 경우(체크박스를 사용하는 경우)에 사용
- getParameterNames() : name들의 배열이 넘어온다.

```java
protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		System.out.println("doPost");
		request.setCharacterEncoding("utf-8");
		
		String name = request.getParameter("name");
		String id = request.getParameter("id");
		
		
		String pw = request.getParameter("pw");
		
		String[] hobbys = request.getParameterValues("hobby");
		String major = request.getParameter("major");
		String protocol = request.getParameter("protocol");
		
		response.setContentType("text/html; charset=utf-8");
		PrintWriter writer = response.getWriter();
		
		writer.println("<html><head></head><body>");
		writer.println("이름 : " + name + "<br />");
		writer.println("아이디 : " + id + "<br />");
		writer.println("비밀번호 : " + pw + "<br />" );
		writer.println("취미 : " + Arrays.toString(hobbys) + "<br />");
		writer.println("전공 : " + major + "<br />");
		writer.println("프로토콜 : " + protocol);
		writer.println("</body></html>");
	}

}
```



#### ServletConfig

 **특정 Servlet**이 생성될 때 초기에 필요한 데이터들을 초기화 파라미터이다.

`web.xml` 에 기술하고 Servlet파일에서는 `ServletConfing` 클래스를 이용해서 접근(사용)한다.

+`web.xml`이 아닌 Servlet파일에 직접 기술하는 방법도 있습니다.

#### web.xml이용하기

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://java.sun.com/xml/ns/javaee" xsi:schemaLocation="http://java.sun.com/xml/ns/javaee http://java.sun.com/xml/ns/javaee/web-app_3_0.xsd" id="WebApp_ID" version="3.0">
  <display-name>jsp_8_1_ex1_initparamex</display-name>
  <welcome-file-list>
    <welcome-file>index.html</welcome-file>
    <welcome-file>index.htm</welcome-file>
    <welcome-file>index.jsp</welcome-file>
    <welcome-file>default.html</welcome-file>
    <welcome-file>default.htm</welcome-file>
    <welcome-file>default.jsp</welcome-file>
  </welcome-file-list>
  
  <servlet>
  	<servlet-name>ServletInitParam</servlet-name>
  	<servlet-class>com.javalec.ex.ServletInitParam</servlet-class>
  	
  	<init-param>
  		<param-name>id</param-name>
  		<param-value>abcdef</param-value>
  	</init-param>
  	<init-param>
  		<param-name>pw</param-name>
  		<param-value>1234</param-value>
  	</init-param>
  	<init-param>
  		<param-name>path</param-name>
  		<param-value>C:\\javalec\\workspace</param-value>
  	</init-param>
  	
  </servlet>
  <servlet-mapping>
  	<servlet-name>ServletInitParam</servlet-name>
	<url-pattern>/InitParam</url-pattern>
  </servlet-mapping>
  
</web-app>
```

```java
package com.javalec.ex;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class ServletInitParam
 */
//@WebServlet("/ServletInitParam")
public class ServletInitParam extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ServletInitParam() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doGet");
		
		String id = getInitParameter("id");
		String pw = getInitParameter("pw");
		String path = getInitParameter("path");
		
		response.setContentType("text/html; charset=EUC-KR");
		PrintWriter writer = response.getWriter();
		writer.println("<html><head></head><body>");
		writer.println("아이다 : " + id + "<br />");
		writer.println("비밀번호 : " + pw + "<br />");
		writer.println("path : " + path);
		writer.println("</body></html>");
		
		writer.close();
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("doPost");
	}

}
```



#### Servlet 파일에 직접 기술하기

```java
@WebServlet(urlPatterns={"/ServletInitParam"}, initParams={@WebInitParam(name="id", value="abcdef"), @WebInitParam(name="pw", value="1234")})
```



### 데이터 공유 : ServletContext

여러 Servlet에서 특정 데이터를 공유해야할 경우 context parameter를 이용해서 `web.xml` 에 기술하고, Servlet에서 공유하면서 사용할 수 있다.

이때 `<servlet>`보다 위쪽에 있어야한다.

```xml
  <context-param>
  	<param-name>id</param-name>
  	<param-value>abcdef</param-value>
  </context-param>
  <context-param>
  	<param-name>pw</param-name>
  	<param-value>1234</param-value>
  </context-param>
  <context-param>
  	<param-name>path</param-name>
  	<param-value>C:\javalec\workspace</param-value>
  </context-param>
```

```java
String id = getServletContext().getInitParameter("id");
String pw = getServletContext().getInitParameter("pw");
String path = getServletContext().getInitParameter("path");		
```



### 웹어플리케이션 감시

웹어플리케이션의 **생명주기(LifeCycle)를 감시하는 리스너(Listener)**가 있습니다. 바로 **ServletContextListener** 입니다.

리스너의 해당 메소드가 **웹 어플리케이션의 시작과 종료 시 호출** 됩니다.(contextInitialized(), contextDestroyed())

(클래스 생성 + implements ServletContextListener)를 해줘야한다.

```xml
<listener>
	<listener-class>com.javalec.ex.ContextListenerEx</listener-class>
</listener>
```

```java
package com.javalec.ex;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class ContextListenerEx implements ServletContextListener{

	public ContextListenerEx() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void contextDestroyed(ServletContextEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("contextDestroyed");
	}

	@Override
	public void contextInitialized(ServletContextEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("contextInitialized");
	}
	
}
```



### 한글 처리

 Tomcat 서버의 기본 문자 처리방식은 **IOS-8859-1** 방식이다. 따라서 개발자가 따로 한글 인코딩을 하지않으면 한글이 깨져보인다.

#### Get방식 - server.xml 수정

```xml
<Connector URIEncoding="utf-8" connectionTimeout="20000" port="8181" protocol="HTTP/1.1" redirectPort="8443"/>
```

#### Post 방식 - `.setCharacterEncoding`

```java
request.setCharacterEncoding("utf-8");
```