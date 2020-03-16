# Java Bean

## Bean 이란?

**반복적인 작업을 효율적으로 하기 위해서 사용**한다. 

Bean 이란 JAVA 언어의 데이터(속성)과 기능(메소드)로 이루어진 클래스이다. 

jsp페이지를 만들고, **액션태그를 이용해서 Bean을 사용**한다. 그리고 Bean의 내부 데이터를 처리한다.

## Bean 만들기

빈을 만든다는 것은 데이터 객체를 만들기 위한 클래스를 만드는 것이다. ( getter, setter )

```java
package example;

public class Student {
	
	private String name;
	private int age;
	private int grade;
	
	
	public Student() {
		
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public int getGrade() {
		return grade;
	}

	public void setGrade(int grade) {
		this.grade = grade;
	}
	
}
```



## Bean 사용하기

관련 액션 태그(useBean, getProperty, setProperty)로 주로 데이터를 업데이트하고, 얻어오는 역할을 한다.

### useBean

특정 Bean을 사용한다고 명시할 때 사용한다.

```jsp
<jsp:useBean id = "빈이름" class="패키지명을 포함한 클래스명" scope="스코프 범위"/>
```

```jsp
<jsp:useBean id = "student" class="example.Student" scope="page"/>
```

#### Scope 범위

| scope       | 설명                                         |
| ----------- | -------------------------------------------- |
| page        | 생성된 페이지 내에서만 사용 가능             |
| request     | 요청된 페이지 내에서만 사용 가능             |
| session     | 웹 브라우저 생명주기와 동일하게 사용 가능    |
| application | 웹 어플리케이션 생명주기와 동일하게 사용가능 |

### setProperty

데이터 값을 설정할 때 사용한다.(setter)

```jsp
<jsp:setProperty name="빈 이름" property="속성 이름" value ="속성 값" />
```

```jsp
<jsp:setProperty name="student" property="name" value ="홍길동" />
```



### getProperty

데이터 값을 가져올 때 사용한다.(getter)

```jsp
<jsp:getProperty name="빈 이름" property="속성 이름" />
```

```jsp
<jsp:getProperty name="student" property="name" />
```



## 예제

### class파일

```java
package example;

public class Student {
	
	private String name;
	private int age;
	private int grade;
	
	
	public Student() {
		
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public int getGrade() {
		return grade;
	}

	public void setGrade(int grade) {
		this.grade = grade;
	}
	
}
```



### jsp파일

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<jsp:useBean id="student" class="example.Student" scope="page" />
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	
	<jsp:setProperty name="student" property="name" value="박서"/>
	<jsp:setProperty name="student" property="age" value="13"/>
	<jsp:setProperty name="student" property="grade" value="6"/>
	
	이름  : <jsp:getProperty name="student" property="name" /><br />
	나이  : <jsp:getProperty name="student" property="age" /><br />
	학년  : <jsp:getProperty name="student" property="grade" /><br />
	
</body>
</html>
```

