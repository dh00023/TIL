# Adapter Pattern

![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/35/ClassAdapter.png/300px-ClassAdapter.png)

Adapter Pattern은 **한 클래스의 인터페이스를 사용하고자 하는 다른 인터페이스로 변환하는 것을 의미**한다. 어뎁터 패턴을 이용하면 인터페이스 호환성 문제 때문에 같이 사용할 수 없는 클래스들을 같이 쓸 수 있다.

Adapter Pattern은 구조 패턴으로 인터페이스나 구현을 복합하는 것이 아닌, 객체를 합성하는 방법을 제공한다. 이는 컴파일 단계에서가 아닌 런타임 단계에서 복합 방법이나, 대상을 변경할 수 있다는 점에서 유연성을 가진다.



어뎁터 패턴은 **Class Adapter**와 **Object Adapter** 방식이 있다.

- Class Adapter : 자바 상속(inheritance)을 이용한 방법
- Object Adapter : 자바 합성(Composite)을 이용한 방법

## 예제

- volt 값을 가지고 있는 POJO 클래스

```java
public class Volt {
 
    private int volts;
	
    public Volt(int v){
        this.volts=v;
    }
 
    public int getVolts() {
        return volts;
    }
 
    public void setVolts(int volts) {
        this.volts = volts;
    }
	
}
```

- Socket : 120 Volt 생성 클래스

```java
public class Socket {
 
    public Volt getVolt(){
        return new Volt(120);
    }
}
```

- 120 볼트 외의 추가적으로 3, 12 volt도 추가로 생성하는 어뎁터

```java
public interface SocketAdapter {
 
    public Volt get120Volt();
		
    public Volt get12Volt();
	
    public Volt get3Volt();
}
```

- Class Adapter 방식

```java
public class SocketClassAdapterImpl extends Socket implements SocketAdapter{
 
    @Override
    public Volt get120Volt() {
        return getVolt();
    }
 
    @Override
    public Volt get12Volt() {
        Volt v= getVolt();
        return convertVolt(v,10);
    }
 
    @Override
    public Volt get3Volt() {
        Volt v= getVolt();
        return convertVolt(v,40);
    }
	
    private Volt convertVolt(Volt v, int i) {
        return new Volt(v.getVolts()/i);
    }
 
}
```

- Object Adapter 방식

```java
public class SocketObjectAdapterImpl implements SocketAdapter{
 
    //Using Composition for adapter pattern
    private Socket sock = new Socket();
	
    @Override
    public Volt get120Volt() {
        return sock.getVolt();
    }
 
    @Override
    public Volt get12Volt() {
        Volt v= sock.getVolt();
        return convertVolt(v,10);
    }
 
    @Override
    public Volt get3Volt() {
        Volt v= sock.getVolt();
        return convertVolt(v,40);
    }
	
    private Volt convertVolt(Volt v, int i) {
        return new Volt(v.getVolts()/i);
    }
}
```



- main

```java
		public static void main(String[] args) {
       	// object adapter
				SocketAdapter sockAdapter = new SocketObjectAdapterImpl();
        Volt v3 = sockAdapter.get3Volt();
        Volt v12 = sockAdapter.get12Volt();
        Volt v120 = sockAdapter.get120Volt();

      	// class adapter
      	SocketAdapter sockAdapter = new SocketClassAdapterImpl();
        Volt v3 = sockAdapter.get3Volt();
        Volt v12 = sockAdapter.get12Volt();
        Volt v120 = sockAdapter.get120Volt();
    }
```



## 참고

- [준비된 개발자 - 구조 패턴 어댑터 패턴(Adapter Pattern) 이해 및 예제](https://readystory.tistory.com/125)

