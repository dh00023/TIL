# DTO와 JavaBean

## DTO(Data Transfer Object)

DTO는 계층 간 데이터 교환을 위해 사용하는 객체다.
*여기서 계층은 View-Controller-Service-DAO와 같은 계층을 의미*

데이터를 담을 private 속성과 그 속성에 접근할 수 있는 Getter, Setter 메소드로 구성되어있다.

> VO(Value Object)와 혼용되어 쓰이나,
VO는 내부 속성값을 변경할 수 없는(imuutable) Read-Only의 의미적 특성을 가진 객체이다.
> 즉, 변경없이 값으로 취급할 객체를 말한다.


## JavaBean(=Bean) 이란?

**반복적인 작업을 효율적으로 하기 위해서 사용**한다. 

Bean 이란 JAVA 언어의 데이터(속성)과 기능(메소드)로 이루어진 클래스이다. 

- Default 생성자 : 파라미터가 없는 Default  생성자를 갖고 있어야한다.
- Property : 자바빈이 노출하는 이름을 가진 속성을 Property라고 하며, Property는 set으로 시작하는 수정자 메소드(setter)와 get으로 시작하는 접근자 메소드(getter)를 이용해 수정 또는 조회할 수 있다.

*DTO와 Java Beans의 관계에 대해선 DTO의 형식으로 Java Beans를 따르고 있다고 생각하면 된다.*

> Spring에서 지칭하는 Bean이란, Spring의 IoC Container(=DI Container)를 통해 관리(생성, 제어)되는 객체를 말하며, 이는 [Spring IoC Container](https://dahye-jeong.gitbook.io/spring/spring/2020-03-20-IoC)에서 자세히 볼 수 있다.

### Bean 만들기

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



### Bean 사용하기

관련 액션 태그(useBean, getProperty, setProperty)로 주로 데이터를 업데이트하고, 얻어오는 역할을 한다.

#### useBean

특정 Bean을 사용한다고 명시할 때 사용한다.

```jsp
<jsp:useBean id = "빈이름" class="패키지명을 포함한 클래스명" scope="스코프 범위"/>
```

```jsp
<jsp:useBean id = "student" class="example.Student" scope="page"/>
```

-  Scope 범위

| scope       | 설명                                         |
| ----------- | -------------------------------------------- |
| page        | 생성된 페이지 내에서만 사용 가능             |
| request     | 요청된 페이지 내에서만 사용 가능             |
| session     | 웹 브라우저 생명주기와 동일하게 사용 가능    |
| application | 웹 어플리케이션 생명주기와 동일하게 사용가능 |

#### setProperty

데이터 값을 설정할 때 사용한다.(setter)

```jsp
<jsp:setProperty name="빈 이름" property="속성 이름" value ="속성 값" />
```

```jsp
<jsp:setProperty name="student" property="name" value ="홍길동" />
```



#### getProperty

데이터 값을 가져올 때 사용한다.(getter)

```jsp
<jsp:getProperty name="빈 이름" property="속성 이름" />
```

```jsp
<jsp:getProperty name="student" property="name" />
```



### 예제

- Java Class

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
- jsp로 구현하기

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

