# 예외 처리

컴퓨터 하드웨어의 오동작 또는 고장으로 인해 응용프로그램 실행 오류가 발생하는 것을 error라고 한다. 에러는 JVM 실행에 문제가 생겼다는 것이므로 개발자는 이런 에러에 대처할 방법이 전혀 없다.

에러 이외에 **예외(exception)**라고 부르는 오류가 있다. 예외란 **사용자의 잘못된 조작 또는 개발자의 잘못된 코딩으로 인해 발생**하는 프로그램 오류이다. 예외는 **예외 처리(Exception Handling)**를 통해 프로그램을 종료하지 않고 정상 실행 상태가 유지되도록 할 수 있다.

- 일반 예외 : 컴파일러 체크 예외, 자바 소스를 컴파일 하는 과정에서 예외 처리 코드가 필요한지 검사한다.
- 실행 예외(Runtime Exception) : 컴파일하는 과정에서 예외 처리 코드를 검사하지 않는 예외를 말한다.

컴파일 시 예외 처리를 확인하는 차이일 뿐, 두가지 모두 예외 처리가 필요하다.

JVM은 프로그램 실행하는 도중에 예외가 발생하면 해당 예외 클래스로 객체를 생성한다. 그리고 나서 예외 처리 코드에서 예외 객체를 이용할 수 있도록 도와준다. 모든 예외 클래스는 `java.lang.Exception` 클래스를 상속받는다.

- 일반예외 :  Exception을 상속받지만, Runtime Exception을 상속받지 않는 클래스
- 실행 예외 : Exception + RuntimeException을 상속받는다.

## 실행 예외

실행 예외는 자바 컴파일러가 체크하지 않기 때문에 개발자의 경험에 의해서 예외처리 코드를 삽입해야한다.

### NullPointerException

가장 빈번하게 발생하는 실행 예외 일 것이다. 이것은 객체 참조가 없는 상태, 즉 null값을 갖는 참조 변수로 객체 접근 연산자인 `.`을 사용 했을 때 발생한다. 객체가 없는 상태에서 객체를 사용하려해 예외가 발생하는 것이다.

```java
public class NullPointerExceptionExample{
    public static void main(String[] args){
        String data = null;
        System.out.println(data.toString());
    }
}
```

```
Exception in thread "main" java.lang.NullPointerException
	at Test.main(Test.java:4)
```

### ArrayIndexOutOfBoundsException

배열에서 인덱시 범위를 초과하여 사용할 경우 발생하는 실행 예외이다.

```java
public class ArrayIndexOutOfBoundsExceptionEX{
    public static void main(String[] args){
        String data1 = args[0];
        String data2 = args[1];
        
        System.out.println("args[0] : "+data1);
        System.out.println("args[1] : "+data2);
    }
}
```

```
Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException: 0
	at Test.main(Test.java:4)
```

```java
public class ArrayIndexOutOfBoundsExceptionEX{
    public static void main(String[] args){
        if(args.length == 2){
            String data1 = args[0];
            String data2 = args[1];

            System.out.println("args[0] : "+data1);
            System.out.println("args[1] : "+data2);
        }else{
            System.out.println("java ArrayIndexOutOfBoundsException");
        }
    }
}
```

### NumberFormatException

문자열로 되어 있는 데이터를 숫자로 변경하는 경우가 자주 발생하는데 그 중에 다음 두가지가 많이 사용된다.

| 반환타입 | 메소드명(매개 변수)          | 설명                                 |
| -------- | ---------------------------- | ------------------------------------ |
| int      | Integer.parseInt(String s)   | 주어진 문자열을 정수로 변환해서 리턴 |
| double   | Double.parsedouble(String s) | 주어진 문자열을 실수로 변환해서 리턴 |

이 메소드들은 매개값인 문자열이 숫자로 변환될 수 있다면 숫자를 리턴하지만, 숫자로 변환될 수 없는 문자가 포함되어 있다면 실행 예외가 발생한다.

```java
public class NumberFormatExceptionExample{
    public static void main(String[] args){
        String data1 = "100";
        String data2 = "a100";
        
        int value1 = Integer.parseInt(data1);
        int value2 = Integer.parseInt(data2);	// 예외발생
    }
}
```

```
Exception in thread "main" java.lang.NumberFormatException: For input string: "a100"
	at java.lang.NumberFormatException.forInputString(NumberFormatException.java:65)
	at java.lang.Integer.parseInt(Integer.java:580)
	at java.lang.Integer.parseInt(Integer.java:615)
	at Test.main(Test.java:8)
```

### ClassCastException

타입 변환(Casting)은 상위 클래스와 하위 클래스 간에 발생하고 구현 클래스와 인터페이스 간에도 발생한다. 이러한 관계가 아니라면 클래스는 다른 클래스로 타입 변환을 할 수 없다. 억지로 타입 변환을 시도할 경우 예외가 발생한다.

ClassCastException을 발생시키지 않으려면 타입 변환 전에 타입 변환이 가능한지 **`instanceof`** 연산자로 확인하는 것이 좋다.

```java
public class ClassCastExceptionExample{
    public static void main(String[] args){
        Dog dog = new Dog();
        ChangeDog(dog);
        
        Cat cat = new Cat();
        changeDog(cat);
    }
    public static void changeDog(Animal animal){
        if(animal instanceof Dog){
            Dog dog = (Dog) animal;
        }
    }
}
class Animal{}
class Dog extends Animal{}
class Cat extends Animal{}
```

```
Exception in thread "main" java.lang.ClassCastException: Cat cannot be cast to Dog
	at Test.changeDog(Test.java:12)
	at Test.main(Test.java:8)
```



## 예외 처리 코드

프로그램에서 예외가 발생했을 경우 프로그램의 갑작스러운 종료를 막고, 정상 실행을 유지할 수 있도록 처리하는 코드를 예외 처리 코드라고 한다. 자바 컴파일러는 일반 예외가 발생할 가능성이 있는 코드를 발견하면 컴파일 오류를 발생시켜 예외 처리 코드를 작성하도록한다. 하지만 실행 예외는 컴파일러가 체크해주지 않는다.

예외 처리 코드는 `try` - `catch` - `finally` 블록을 이용한다.

```java
try{
    예외 발생 가능 코드
}catch(예외클래스 e){
    예외처리
}finally{
    항상 실행;
}
```

try 블록에는 예외 발생 가능 코드가 위치한다. 예외 발생 없이 정상 실행되면 바로 finally코드를 실행하고, 예외가 발생하면 실행을 멈추고  catch 블록으로 이동하여 예외 처리 코드를 실행한다. 그 후에 finally 블록 코드를 실행한다. finally 블록은 옵션으로 생략가능하다.

```java
public class TryCatchFinallyExample{
    public static void main(String[] args){
        try{
            Class clazz = Class.forName("java.lang.String2");
        }catch(ClassNotFoundException e){
            System.out.println("클래스가 존재하지 않습니다.");
        }
    }
}
```

```java
public class TryCatchFinallyRuntimeExceptionExample{
    public static void main(String[] args){
        String data1 = null;
        String data2 = null;

        try{
			data1 = args[0];
            data2 = args[1];
        }catch(ArrayIndexOutOfBoundsException e){
            System.out.println("실행 매개값의 수가 부족합니다.");
            System.out.println("=== 실행 방법 ===");
            System.out.println("$ java TryCatchFinallyRuntimeExceptionExample num1 num2");
            return;
        }
        
        try{
            int value1 = Integer.parseInt(data1);
            int value2 = Integer.parseInt(data2);
            int result = value1 + value2;
            System.out.println(data1+"+"+data2+"="+result);
        }catch(NumberFormatException e){
            System.out.println("숫자로 변환할 수 없습니다.");
        }finally{
            System.out.println("다시 실행하세요");
        }
    }
}
```



## 예외 종류에 따른 처리 코드

### 다중 catch

try 블록 내부는 다양한 종류의 예외가 발생할 수 있다. 이럴 때는 다중 catch 블록을 작성하면된다.

```java
try{
    ArrayIndexOutOfBoundsException 발생
    
    NumberFormatException 발생
}catch(ArrayIndexOutOfBoundsException e){
    예외처리1
}catch(NumberFormatException e){
    예외처리2
}
```

catch블록이 여러개라 할지라도 단 하나의 catch블록만 실행된다. 그 이유는 try 블록에서 동시 다발적으로 예외가 발생하지 않고, 하나의 예외가 발생하면 즉시 실행을 멈추고 해당 catch블록으로 이동하기 때문이다.

```java
public class TryCatchFinallyRuntimeExceptionExample{
    public static void main(String[] args){
        String data1 = null;
        String data2 = null;

        try{
			data1 = args[0];
            data2 = args[1];
            int value1 = Integer.parseInt(data1);
            int value2 = Integer.parseInt(data2);
            int result = value1 + value2;
            System.out.println(data1+"+"+data2+"="+result);
        
        }catch(ArrayIndexOutOfBoundsException e){
            System.out.println("실행 매개값의 수가 부족합니다.");
            System.out.println("=== 실행 방법 ===");
            System.out.println("$ java TryCatchFinallyRuntimeExceptionExample num1 num2");
            return;
        }catch(NumberFormatException e){
            System.out.println("숫자로 변환할 수 없습니다.");
        }finally{
            System.out.println("다시 실행하세요");
        }
    }
}
```

#### catch 순서

다중 catch 블록 작성시 주의 할 점은 **상위 예외 클래스가 하위 예외 클래스보다 아래 위치**해야한다.

만약 상위 예외 클래스의 catch블록이 위에 있다면 하위 예외 클래스의 catch블록은 실행되지 않는다. 왜냐하면 하위 예외 클래스는 상위 예외를 상속했기 때문에 상위 예외 타입도 되기 때문이다.

```java
try{
    ArrayIndexOutOfBoundsException 발생
    
    다른 Exception 발생
}catch(ArrayIndexOutOfBoundsException e){
    예외처리1
}catch(Exception e){
    예외처리2
}
```

```java
public class CatchOrderExample{
    public static void main(String[] args){
        String data1 = null;
        String data2 = null;

        try{
			data1 = args[0];
            data2 = args[1];
            int value1 = Integer.parseInt(data1);
            int value2 = Integer.parseInt(data2);
            int result = value1 + value2;
            System.out.println(data1+"+"+data2+"="+result);
        
        }catch(ArrayIndexOutOfBoundsException e){
            System.out.println("실행 매개값의 수가 부족합니다.");
            System.out.println("=== 실행 방법 ===");
            System.out.println("$ java TryCatchFinallyRuntimeExceptionExample num1 num2");
            return;
        }catch(Exception e){
            System.out.println("실행에 문제가 있습니다.");
        }finally{
            System.out.println("다시 실행하세요");
        }
    }
}
```

### 멀티 catch

자바7부터 **하나의 catch블록에서 여러 개의 예외를 처리**할 수 있도록 multi catch 기능을 추가했다.

```java
try{
    ArrayIndexOutOfBoundsException or NumberFormatException발생   
    다른 Exception 발생
}catch(ArrayIndexOutOfBoundsException e | NumberFormatException e){
    예외처리1
}catch(Exception e){
    예외처리2
}
```

`|`로 예외를 연결하면된다.

```java
public class MultiCatchExample{
    public static void main(String[] args){
        String data1 = null;
        String data2 = null;

        try{
			data1 = args[0];
            data2 = args[1];
            int value1 = Integer.parseInt(data1);
            int value2 = Integer.parseInt(data2);
            int result = value1 + value2;
            System.out.println(data1+"+"+data2+"="+result);
        
        }catch(ArrayIndexOutOfBoundsException e | NumberFormatException e){
            System.out.println("실행 매개값의 수가 부족하거나 숫자로 변환할 수 없습니다.");
        }catch(Exception e){
            System.out.println("실행에 문제가 있습니다.");
        }finally{
            System.out.println("다시 실행하세요");
        }
    }
}
```

### 자동 리소스 닫기

자바7에서 새로 추가된 `try` - `with` - `resources` 를 사용하면 예외 발생 여부와 상관없이 사용했던 리소스 객체(각종 입출력 스트림, 서버 소켓, 소켓, 각종 채널)의 close() 메소드를 호출해서 안전하게 리소스를 닫아준다.

리소스란 여러 가지 의미가 있겠지만 여기서는 데이터를 읽고 쓰는 객체라고 생각하자.

```java
try(FileInputStream fis = new FileInputStream("file.txt")){
    ...
}catch(IOException e){
    
}
```

try 블록이 정상적으로 실행을 완료했거나 도중에 예외가 발생하게 되면 자동으로 close() 메소드가 호출된다. try{}에서 예외가 발생하면 우선적으로 close()로 리소스를 닫고 catch블록을 실행한다.

try - with - resources를 사용하기 위해서는 조건이 있다.

- 리소스 객체는 AutoCloseable 인터페이스를 구현하고 있어야한다.

```java
public class FileInputStream implements AutoCloseable{
    private String file;
    
    public FileInputStream(String file){
        this.file = file;
    }
    
    public void read(){
        System.out.println(file+"을 읽습니다.");
    }
    
    @Override
    public void close() throws Exception{
        System.out.println(file+"을 닫습니다.");
    }
}
```

```java
public class TryWithResourceExample{
    public static void main(String[] args){
        try(FileInputStream fis = new FileInputStream("file.txt")){
            fis.read();
            throw new Exception(); //강제 예외 발생
        }catch(Exception e){
            System.out.println("예외 처리 코드가 실행 되었습니다.");
        }
    }
}
```

### 예외 떠넘기기

경우에 따라서는 메소드를 호출한 곳으로 예외를 떠넘길 수 있다. 이때 사용하는 키워드가 **throws**이다. throws 키워드는 메소드 선언부 끝에 작성되어 메소드에서 처리하지 않은 예외를 호출한 곳으로 떠넘기는 역할을 한다.

```java
리턴타입 메소드명(매개변수,...) throws 예외클래스1, 예외클래스,...{
}
```

발생할 수 있는 예외의 종류별로 throws뒤에 나열하는 것이 일반적이지만, 다음과 같이 throws Exception만으로 모든 예외를 간단히 떠넘길 수 있다.

```java
리턴타입 메소드명(매개변수, ...) throws Exception{
}
```

**throws 키워드가 붙어있는 메소드는 반드시 try 블록 내에서 호출되어야한다.** 그리고 catch블록에서 떠넘겨 받은 예외를 처리 해아한다.

```java
public void method1(){
    try{
        method2();
    }catch(ClassNotFoundException e){
        //예외처리코드
        System.out.println("클래스가 존재하지 않습니다.");
    }
}

public void method2() throws ClassNotFoundException{
    Class clazz = Class.forName("java.lang.String2");
}
```

자바 API 도큐먼트를 보면 클래스 생성자와 메소드 선언부에 throws 키워드가 붙어있는 것을 흔히 볼 수 있다. 이러한 생성자와 메소드를 사용하고 싶다면, 반드시 try-catch 블록으로 예외처리를 해야한다. 그렇지않으면 컴파일 오류가 발생한다.

```java
public class ThrowsExample{
    public static void main(String[] args){
        try{
            findClass();
        }catch(ClassNotFoundException e){
            System.out.println("클래스가 존재하지 않습니다.");
        }
    }
    public static void findClass() throws ClassNotFoundException{
        Class clazz = Class.forName("java.lang.String2");
    }
}
```

main()메소드에서도 throws 키워드르 사용해서 예외를 떠넘길 수 있는데, 결국 JVM이 최종적으로 예외 처리를 하게된다. JVM은 예외 내용을 콘솔(console)에 출력하는 것으로 예외 처리를 한다.



## 사용자 정의 예외와 예외 발생

애플리케이션 예외(Application Exception)는 개발자가 직접 정의해서 만들어야 하므로 사용자 정의 예외라고도 한다.

### Application Exception 클래스 선언

사용자 정의 예외 클래스는 컴파일러가 체크하는 일반 예외로 선언할 수도 있고, 컴파일러가 체크하지 않는 실행 예외로 선언할 수도 있다. 일반 예외로 선언할 경우 Exception을 상속, 실행 예외로 선언할 경우에는 RuntimeException을 상속하면된다.

```java
public class XXXException extends [ Exception | RuntimeException ]{
    public XXXException(){}
    public XXXException(String message){super(message);}
}
```

사용자 정의 예외 클래스 이름은 Exception으로 끝나는 것이 좋다. 사용자 정의 예외 클래스도 필드, 생성자, 메소드 선언을 포함할 수 있지만 대부분 생성자 선언만을 포함한다. 생성자는 매개 변수가 없는 기본생성자, 예외 발생 원인(메시지)을 전달하기 위한 매개변수를 갖는 생성자 두 개를 선언하는 것이 일반적이다. 예외 메세지는 catch{} 블록의 예외 처리 코드 에서 이용하기 위해서이다.

### 예외 발생시키기

```java
throw new XXXException();
throw new XXXException("메시지");
```

예외 객체를 생성할 때는 기본 생성자, 예외 메시지를 갖는 생성자 중 어떤 것을 사용해도된다. 만약 catch 블록에서 예외 메시지가 필요하다면 예외메시지를 갖는 생성자를 이용해야한다.

```java
public void method() throws XXXException{
    throw new XXXException("메시지");
}
```

대부분은 자신이 호출한 곳에서 예외를 처리하도록 throws 키워드로 예외를 떠넘긴다. 그렇기 때문에 throws 키워드를 포함하고 있는 메소드는 호출한 곳에서 예외처리를 해주어야한다.

```java
try{
    method()''
}catch(XXXException e){
    //예외처리
}
```

- 예시

```java
public class BalanceInsufficientException extends Exception{
    public BalanceInsufficientException(){}
    public BalanceInsufficientException(String message){super(message);}
}
```

```java
public class Account{
    private long balance;

    public Account(){}
    
    public long getBalance(){
        return balance;
    }
    public void deposit(int money){
        balance += money;
    }
    public void withdraw(int money) throws BalanceInsufficientException{
        if(balance < money){
            throw new BalanceInsufficientException("잔고부족:"+(money-balance)+"모자람");
        }
        balance -= money;
    }
 }
```

## 예외 정보 얻기

try 블록에서 예외가 발생되면 예외 객체는 catch 블록의 매개 변수에서 참조하게 되므로 매개 변수를 이용하면 예외 객체의 정보를 알 수 있다. 모든 예외 객체는 Exception 클래스를 상속하기 때문에 Exception이 가지고 있는 메소드들을 모든 예외 객체에서 호출할 수 있다. 그 중 **getMessage()**와 **printStackTrace()**를 가장 많이 사용한다. 

```java
throw new XXXException("예외 메시지");
```

메시지를 갖는 생성자를 이용했다면, 자동적으로 예외 객체 내부에 메시지는 저장된다.

```java
try{
    //예외 객체 생성
}catch(예외클래스 e){
    // 예외가 가지고 있는 메시지 얻기
    String message = e.getMessage();
    //예외 발생 경로 추적
    e.printStackTrace();
}
```

예외 메시지의 내용에는 왜 예외가 발생했는지 간단한 설명이 포함된다. 이와 같은 메시지는 catch 블록에서 getMessage()메소드의 리턴값으로 얻을 수 있다.

printStackTrace()는 예외 발생 코드를 추적해서 모두 콘솔에 출력한다. 어떤 예외가 어디에서 발생했는지 상세하게 알려준다.



- 예시

```java
public class AccountExample{
    public static void main(String[] args){
        Account account = new Account();
        
        account.deposit(10000); //예금하기
        System.out.println("예금액 : "+account.getBalance());
        
        //출금하기
        try{
            accound.withdraw(30000);
        }catch(BalanceInsufficientException e){
            String message = e.getMessage();
            System.out.println(message);
            
            e.printStackTrace();
        }
    }
}
```

