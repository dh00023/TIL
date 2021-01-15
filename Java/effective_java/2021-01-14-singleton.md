# ITEM 3: ENFORCE THE SINGLETON PROPERTY WITH A PRIVATE CONSTRUCTOR OR AN ENUM TYPE

 [**singleton**](../design_pattern/singleton_pattern.md) 이란 인스턴스를 오직 하나만 생성할 수 있는 클래스이다.  인터페이스를 구현한 Singleton 객체가 아니라면 **mock**  객체를 만들 수 없어 이를 사용하는 클라이언트를 테스트하기 어려워 질 수 있다.

## public static final 필드 방식

```java
public class Elvis {
    public static final Elvis INSTANCE = new Elvis();
    private Elvis() { ... }
}
```

**private 생성자**는 **public static final** 필드인 `Elvis.INSTANCE` 를 초기화할 때 딱 한번 호출된다. public 혹은 protected 생성자가 없으므로, Elvis 클래스가 초기화될 때 만들어진 인스턴스는 하나뿐임이 보장된다. 

### 장점

1. public 필드 방식은 해당 클래스가 싱글턴임이 API에 명백하게 드러난다.([**final**](../문법/java-class.md)이므로 다른 객체 참조 불가)
2. 간결함

## static factory 방식

```java
public class Elvis {
    private static final Elvis INSTANCE = new Elvis();
    private Elvis() { ... }
  
  	/**/
  	public static Elvis getInstance() { return INSTANCE; }
}
```

`Elvis.getInstance()` 는 항상 같은 객체의 참조를 반환하므로 인스턴스가 하나임을 보장한다.

### 장점

1. 현재는 singleton 객체를 리턴하는 정적 메서드이지만, 향후에 필요에 따라 변경할 수 있는 확장성이 있다. 유일한 메서드를 반환하는 팩터리 메서드가 호출하는 스레드별로 다른 인스턴스를 넘겨주도록 리턴하는 방법과 같이 확장성이 열려있다.
2. 정적 팩터리를 [제네릭 싱클턴 팩터리]()로 만들 수 있다.
3. 정적 팩터리의 메서드 참조를 공급자(supplier)로 사용할 수 있다.([item43](), [item44]())

다음과 같은 장점이 필요하지 않다면, public static private 방식이 더 좋다.

## Reflection 방어

이때, public static final 방식과 static factory 방식은 권한이 있는 클라이언트가 [Reflection API]() 인 `AccessibleObject.setAccessible`을 사용해 private 생성자를 호출할 수 있는 문제점이 있다. 이러한 공격을 방어하려면 두번 째 객체가 생성되려할 때 다음과 같이 예외처리를 해 막을 수 있다.

```java
public class Elvis {
    public static final Elvis INSTANCE = new Elvis();
    private Elvis() { 
      	if( INSTANCE != null) {
            throw new RuntimeException("Can't create Constructor");
        }	
      	//... 
    }
}
```

## Singleton Class 직렬화

Singleton class를 직렬화하려면 단순히 `Serializable`을 구현하는 것만으로는 부족하다. 모든 인스턴스 필드를 `transient`(일시적) 약어를 선언하고 `readResolve` 메서드를 제공해야한다. ([item 89]()) 이렇게 하지 않으면, 역직렬화(deserialize)시 새로운 인스턴스가 생성디ㅗㄴ다.

```java
public class Elvis implements Serializable{
    private static final Elvis INSTANCE = new Elvis();
    private Elvis() { ... }
  
  	public static Elvis getInstance() { return INSTANCE; }
  
  	// singleton임을 보장
  	private Object readResolve() {
      	// 역직렬화가 되어 새로운 인스턴스가 생성되더라도 INSTANCE를 반환하여 싱글턴 보장
       	// 새로운 인스턴스는 GC에 의해 UnReachable 형태로 판별되어 제거
      	return INSTANCE;
    }
}
```

## Enum 방식

```java
public enum Elvis {
  	INSTANCE;
}
```

원소가 하나인 Enum타입을 선언해 singleton을 만들 수 있다.

### 장점

1. public static 방식보다 더 간결
2. 추가 코드없이 직렬화 가능
3. **Reflection 공격과 아주 복잡한 직렬화 상황에도 제 2의 인스턴스가 생기는 일을 완벽히 방어** 

**대부분의 상황에서는 원소가 하나뿐인 열거 타입이 singleton을 만드는 가장 좋은 방법**이다. 하지만, 만들려는 singleton이 `Enum` 이외의 클래스를 상속해야하는 경우 이 방법은 사용할 수 없다.



## 참고

- [Carrey's 기술블로그 - Item3](https://jaehun2841.github.io/2019/01/07/effective-java-item3/#%EC%97%B4%EA%B1%B0-%ED%83%80%EC%9E%85enum%EC%9D%84-%EC%9D%B4%EC%9A%A9%ED%95%9C-%EC%8B%B1%EA%B8%80%ED%84%B4-%EA%B0%9D%EC%B2%B4-%EC%83%9D%EC%84%B1)