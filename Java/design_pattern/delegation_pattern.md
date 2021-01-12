# Delegation pattern

Delegation Pattern은 쉽게 표현하자면 어떤 객체에서 일어나는 이벤트에 관한 혹은 어떤 객체에 뿌려줄 데이터에 관한 코드를 다른 객체에서 작성해주는 것을 말합니다. 즉 **A객체의 일을 B객체에서 대신해주는 일을 위임하는 행위**입니다.

다시말하면 한 객체가 모든 일을 수행하는 것이 아니라 **일부를 다른 객체에 위임**한다.

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
   	public void print(){
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



## Delegation Pattern 사용하는 이유?

1. 여러 클래스에서 겹치는 매소드를 줄이기는것이 필요하기 위해 사용
2. 하나의 독립적인 행동이 필요하지만, 미래에 이 행동이 바뀔 수 있는 상황에서 사용
3. 하나의 상속된 형태를 위임과 함께 사용하기 위해 사용



