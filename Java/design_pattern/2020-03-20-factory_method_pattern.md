# Factory Method Pattern
![https://www.dofactory.com/images/diagrams/net/factory.gif](./assets/factory.gif)

팩토리 메소드 패턴은  Super Class에 알려지지 않은 구체 클래스를 생성하는 패턴이며, **자식 클래스가 어떤 객체를 생성할지를 결정하도록 하는 패턴**이기도 하다.

즉, **객체 생성 처리를 서브 클래스로 분리 해 처리하도록 캡슐화하는 패턴** 으로 객체의 생성 코드를 별도의 클래스/메서드로 분리함으로써 객체 생성의 변화에 대비하는 데 유용하다.

주로 인터페이스 타입으로 오브젝트를 반환하므로 Super Class에서는 Sub Class에서 정확히 어떤 클래스의 오브젝트를 만들어 반환할지 알지 못한다.

```java
public interface Shape{
  abstract void draw();
}
```

```java
public class Star extends Shape{
  @Override
  public void draw(){
    System.out.println("별 그리기");
  }
}
```

```java
public class Square extends Shape{
  @Override
  public void draw(){
    System.out.println("네모 그리기");
  }
}
```

```java
public class ShapeFactory{
  public Shape getShape(String shapeType){
    if(StringUtils.isEmpty(shapeType)){
      return null;
    }
    if(shapeType.equalsIgnoreCase("SQUARE")){
      return new Square();
    }else if(shapeType.equalsIgnoreCase("STAR")){
      return new Star();
    }
		return null;
  }
}
```

```java
public FactoryPatternTest{
  public static void main(String[] args){
    ShapeFactory shapeFactory = new ShapeFactory();
    
    Shape shape1 = shapeFactory.getShape("STAR");
    shape1.draw();
    
    Shape shape2 = shapeFactory.getShape("SQUARE");
    shape2.draw();
  }
}
```

즉, **서브 클래스에서 오브젝트 생성 방법 클래스를 결정할 수 있도록 미리 정의해둔 메소드를 팩토리 메소드라고 하며, 이 방식을 통해 오브젝트를 생성하는 방법을 팩토리 메소드 패턴**이라고 한다.

## Factory Method Pattern을 왜 사용할까?

팩토리 메소드 패턴을 사용하는 이유는 클래스간의 결합도를 낮추기 위한것입니다. 결합도라는 것은 간단히 말해 **클래스의 변경점이 생겼을 때 얼마나 다른 클래스에도 영향을 주는가**입니다. 팩토리 메소드 패턴을 사용하는 경우 **직접 객체를 생성해 사용하는 것을 방지하고 서브 클래스에 위임함으로써 보다 효율적인 코드 제어를 할 수 있고 의존성을 제거**합니다. 결과적으로 결합도 또한 낮출 수 있습니다.

## 예제

Sub Class의 getConnection()을 통해 만들어진 Connection 종류가 달라질 수 있게 하는 것을 목적으로 하는 팩토리 메소드 패턴의 예시이다.

```java
package springbook.user.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import springbook.user.domain.User;

public abstract class UserDao {
	public void add(User user) throws ClassNotFoundException, SQLException {
		Connection c = getConnection();

		PreparedStatement ps = c.prepareStatement(
			"insert into users(id, name, password) values(?,?,?)");
		ps.setString(1, user.getId());
		ps.setString(2, user.getName());
		ps.setString(3, user.getPassword());

		ps.executeUpdate();

		ps.close();
		c.close();
	}


	public User get(String id) throws ClassNotFoundException, SQLException {
		Connection c = getConnection();
		PreparedStatement ps = c
				.prepareStatement("select * from users where id = ?");
		ps.setString(1, id);

		ResultSet rs = ps.executeQuery();
		rs.next();
		User user = new User();
		user.setId(rs.getString("id"));
		user.setName(rs.getString("name"));
		user.setPassword(rs.getString("password"));

		rs.close();
		ps.close();
		c.close();

		return user;
	}

	abstract protected Connection getConnection() throws ClassNotFoundException, SQLException ;

}
```

```java
package springbook.user.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DUserDao extends UserDao {
	protected Connection getConnection() throws ClassNotFoundException,
			SQLException {
		Class.forName("com.mysql.jdbc.Driver");
		Connection c = DriverManager.getConnection(
				"jdbc:mysql://localhost/springbook?characterEncoding=UTF-8",
				"DuserId", "DUserPassword");
		return c;
	}
}
```

```java
package springbook.user.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class NUserDao extends UserDao {
	protected Connection getConnection() throws ClassNotFoundException,
			SQLException {
		Class.forName("com.mysql.jdbc.Driver");
		Connection c = DriverManager.getConnection(
				"jdbc:mysql://localhost/springbook?characterEncoding=UTF-8",
				"NUserId", "NUserPassword");
		return c;
	}
}
```

```java

	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		UserDao dao = new NUserDao();

		User user = new User();
		user.setId("admin");
		user.setName("test1");
		user.setPassword("admintest");

		dao.add(user);
			
		System.out.println(user.getId() + " 등록 완료");
		
		User user2 = dao.get(user.getId());
		System.out.println(user2.getName());
		System.out.println(user2.getPassword());
			
		System.out.println(user2.getId() + " 호출 완료");
	}
```

NUserDao와 DUserDao가 Connection을 생성하는 방법이 다르므로, 팩토리 메소드 패턴으로 볼 수 있다.



## 참고

- [https://niceman.tistory.com/143?category=940951](https://niceman.tistory.com/143?category=940951)
- 토비의 스프링
- https://gmlwjd9405.github.io/2018/08/07/factory-method-pattern.html
