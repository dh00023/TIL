# JDBC

JAVA 프로그램에서 SQL문을 실행하여 데이터를 관리하기 위한 JAVA API이다.

JDBC의 특징은 다양한 데이터 베이스에 대해서 별도의 프로그램을 만들 필요 없이, **해당 데이터 베이스의 JDBC를 이용하면 하나의 프로그램으로 데이터 베이스를 관리할 수 있다.**

## MySQL 연동하기

1. https://dev.mysql.com/downloads/connector/j/5.1.html 에서 **Platform Independent (Architecture Independent), Compressed TAR Archive** 를 다운받는다.
2. 압축을 푼 후 `mysql-connector-java-5.1.46-bin.jar` 파일을 복사한다.
3. `/Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home/jre/lib/ext ` 로 이동한 후 복사한 파일을 붙여넣는다.
4. Eclipse 환경설정 → Installed JREs→ 설치 버전 선택 → Edit → Add External JARs 로 위의 경로에 추가한 파일을 추가해준다.
5. DataSource Explorer → Database Connection을 우클릭 → New → MySQL 추가

해주면 성공적으로 연동 된 것을 확인할 수 있다.



## JDBC 살펴보기

### 데이터 베이스 연결 순서

![](https://www.ntu.edu.sg/home/ehchua/programming/java/images/JDBC_Cycle.png)

- JDBC 드라이버 로드(DriverManager) : 메모리에 MySQL Driver가 로드된다.

```java
Class.forName("com.mysql.jdbc.Driver");
```



- 데이터베이스 연결(Connection) : Connection 객체를 생성한다.

```java
Connection connection=DriverManager.getConnection(JDBC URL,계정아이디,비밀번호);
```



- SQL문 실행(Statement) : State 객체를 통해서 SQL문이 실행된다.

```java
Statement statement = connection.createStatement();
```



- 데이터베이스 연결 해제(ResultSet) : SQL문 결과 값을 ResultSet값으로 받는다.

```java
ResultSet rs = statement.executeQuery();
ResultSet rs = statement.executeUpdate();
```



## Statement 객체 살펴보기

### executeQuery()

SQL문 실행 후 여러 개의 결과 값이 생기는 경우에 사용한다. (ex) select

### ResultSet

executeQuery() 실행 후 반환되는 레코드 셋이다.

| 메소드                        | 설명                    |
| ----------------------------- | ----------------------- |
| next()                        | 다음 레코드 이동        |
| previous()                    | 이전 레코드로 이동      |
| first()                       | 처음으로 이동           |
| last()                        | 마지막으로 이동         |
| get메소드 (getString, getInt) | 해당되는 값을 가져온다. |

#### executeUpdate() 

SQL문 실행 후 테이블의 내용만 변경되는 경우 사용한다. (ex) insert, delete, update



### 예제 코드

```jsp
<%@page import="javax.servlet.jsp.tagext.TryCatchFinally"%>
<%@ page import="java.sql.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%!
	Connection connection;
	Statement statement;
	ResultSet resultSet;
	
	String driver = "com.mysql.jdbc.Driver";
	String url = "jdbc:mysql://localhost:3306/javaproject";
	String uid = "root";
	String upw = "비밀번호";
	String query = "SELECT * FROM member";
%>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
	try{
		Class.forName(driver);
		connection = DriverManager.getConnection(url,uid,upw);
		statement = connection.createStatement();
		resultSet = statement.executeQuery(query);
		
        // 다음데이터가 있으면 값을 받아온다.
		while(resultSet.next()){
			String id = resultSet.getString("id");
			String pw = resultSet.getString("pw");
			String name = resultSet.getString("name");
			String phone = resultSet.getString("phone");
			
			out.println("아이디 : "+id +", 비밀번호 : "+pw+", 이름 : "+name+", 전화번호 : "+phone+"<br />");
		}
	}catch(Exception e){
	}finally{
        //데이터베이스를 연결한 자원을 해제한다.
		try{
			if(resultSet != null) resultSet.close();
			if(statement != null) statement.close();
			if(connection != null) connection.close();
		} catch(Exception e){}
	}
	%>
</body>
</html>
```



연결이 제대로 됐으면 올바른 값이 나오는 것을 확인할 수 있다.