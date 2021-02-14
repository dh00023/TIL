# ITEM 25 : 톱레벨 클래스는 한 파일에 하나만 생성해라.

소스 파일 하나에 톱레벨 클래스를 여러개 선언하는 것은 아무런 득이 없을 뿐더러 심각한 위험을 감수해야하는 행위이다. 톱 레벨 클래스를 여러개 선언하면 한 클래스를 여러가지로 정의할 수 있으며, 그중 어느 것을 사용할지는 어느 소스 파일을 먼저 컴파일하느냐에 따라 달라지기 때문이다.

```java
// Utensil.java에 두 클래스 정의(잘못된 방법)
class Utensil {
  	static final String NAME = "pan";
}

class Dessert {
		static final String NAME = "cake";
}
```

```java
// Dessert.java에 두 클래스 정의(잘못된 방법)
class Utensil {
  	static final String NAME = "pot";
}

class Dessert {
		static final String NAME = "pie";
}
```

```java
public class Main {
  	public static void main(String[] args){
      	System.out.println(Utensil.NAME + Dessert.NAME);
    }
}
```

위와 같이 이름이 중복되는 경우 컴파일 에러가 발생하며, 컴파일러에 어느 소스파일을 먼저 건네느냐에 따라 동작이 달라지므로 반드시 바로잡아야 한다.

이는 단순히 톱레벨 클래스들을 서로 다른 소스 파일로 분리하면 해결할 수 있다. 여러 톱레벨 클래스를 한 파일에 담고 싶다면, [정적 멤버 클래스](./2021-02-14-favor-static-memeber.md)를 사용하는 방법을 고민해볼 수 있다.

```java
public class Test{
  public static void main(String[] args){
    System.out.println(Utensil.NAME + Dessert.NAME);
  }
  private static class Utensil {
    static final String NAME = "pan";
  }
  private static class Dessert {
    static final String NAME = "cake";
  }
}
```

**그러므로 소스 파일 하나에는 반드시 톱레벨 클래스를 하나만 담자.**