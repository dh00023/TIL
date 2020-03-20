# Delegation pattern

한 클래스가 다른 객체들을 멤버로 갖는 형태이다.

한 객체가 모든 일을 수행하는 것이 아니라 **일부를 다른 객체에 위임**한다.

### 예제1) 데이터를 저장하고 읽어오는 작업

```java
class Data{
    ...
}
```

```java
class A{
	Data data = new Data();
    public String getMsg(){
    	return data.getMsg();    
    }
}
```

### 예제2) Printer

```java
public class RealPrinter{
    void print(){
        System.out.println("프린트");
    }
}
```

```java
public class Printer{
    RealPrinter p = new RealPrinter();
    void print(){
        p.print();
    }
}
```

```java
public class Main{
    public static void main(String[] args){
        Printer printer = new Printer();
        printer.print();
    }
}
```

Main 클래스에서 Printer 객체의 `print()`가 실행되지만, 실제 구현을 보면 RealPrinter 객체의 print() 메소드를 위임받아서 실행하고 있다.



### 예제3)

```java
Interface I{
    void f();
    void g();
}
class A implements I{
    public void f(){
        System.out.println("A f()");
    }
    public void g(){
        System.out.println("A g()");
    }
}
class B implements I{
    public void f(){
        System.out.println("B f()");
    }
    public void g(){
        System.out.println("B g()");
    }
}
class C implements I{
    I i = new A();
    
	public void f(){
        i.f();
    }
    public void g(){
        i.g();
    }
    public void toA(){
        i = new A();
    }
    public void toA(){
        i = new B();
    }
}

public class Main{
    public static void main(String[] args){
        C c = new C();
        c.f(); //=> "A f()"
        c.g(); //=> "A g()"
        
        c.toB();
        c.f(); //=> "B f()"
        c.g(); //=> "B g()"
    }
}
```

상속대신 Delegation과 Interface를 사용함으로써 클래스는 훨씬 더 유연해진다.