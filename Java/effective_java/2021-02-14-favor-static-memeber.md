# ITEM 24 : 멤버 클래스는 되도록 static으로 구현해라

## 중첩 클래스

Nested Class(중첩 클래스)란 다른 클래스 안에 정의된 클래스를 말한다. 중첩 클래스는 자신을 감싼 바깥 클래스에서만 사용돼야 하며, 그 외의 쓰임새가 있다면 톱레벨 클래스로 만들어야한다.

### 종류

#### 정적 멤버 클래스

흔히 바깥 클래스와 함께 쓰이는 public 도우미 클래스로 쓰인다. 바깥 인스턴스와 **독립적으로 인스턴스가 존재**한다.

```java
public class Caculator {
    // 열거 타입도 정적 멤버 클래스 
    public enum Operation {
        PLUS, MINUS
    }
}
```

```java
public class Caculator {
    // 보통 다음과 같이 선언
    public static class Operation{
      
    }
}
```

private 정적 멤버 클래스는 흔히 바깥 클래스가 표현하는 객체의 한 부분을 나타낼 때 사용한다.

#### (비정적) 멤버 클래스

정적 멤버 클래스와 차이점

- 구문상 : `static` 여부
- 의미상 : 비정적 멤버 클래스의 인스턴스는 바깥 클래스의 인스턴스와 연결되며, 비정적 멤버 클래스의 인스턴스 메서드에서 정규화된 this를 사용해 바깥 인스턴스의 메서드를 호출하거나 참조를 가져올 수 있다. 

비정적 멤버 클래스는 바깥 인스턴스 없이는 생성할 수 없다.

```java
public class NestedNonStaticExample {
    private final String name;

    public NestedNonStaticExample(String name) {
        this.name = name;
    }

    public String getName() {
        // 비정적 멤버 클래스와 바깥 클래스의 관계가 확립되는 부분
        NonStaticClass nonStaticClass = new NonStaticClass("nonStatic : ");
        return nonStaticClass.getNameWithOuter();
    }

    private class NonStaticClass {
        private final String nonStaticName;

        public NonStaticClass(String nonStaticName) {
            this.nonStaticName = nonStaticName;
        }

        public String getNameWithOuter() {
            // 정규화된 this 를 이용해서 바깥 클래스의 인스턴스 메서드를 사용할 수 있다.
            return nonStaticName + NestedNonStaticExample.this.getName();
        }
    }
}
```

비정적 멤버 클래스의 인스턴스와 바깥 인스턴스 사이의 관계는 멤버 클래스가 인스턴스화될 때 확립되며, 변경할 수 없다. 바깥 클래스의 인스턴스 메서드에서 비정적 멤버 클래스의 생성자를 호출할 때 자동으로 만들어지는게 보통이지만, 드물게는 직접 `바깥_인스턴스_클래스.new MemberClass(args)`를 호출해 수동으로 만드는 경우도 있다. 이 관계 정보는 **비정적 멤버 클래스의 인스턴스 안에 만들어져 메모리를 차지하며, 생성시간도 더 걸린다.**

- [Adapter Pattern](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/2021-02-14-adapter-pattern.md)를 정의할 때 자주 쓰인다.

- 어떤 클래스의 인스턴스를 감싸 마치 다른 클래스의 인스턴스처럼 보이게 하는 뷰로 사용

- Map 인터페이스의 구현체에서 자신의 컬렉션 뷰를 구현할 때 사용

- `Set`과 `List` 같은 다른 컬렉션 인터페이스 구현들도 자신의 반복자를 구현할 때 비정적 멤버 클래스를 주로 사용

  ```java
  public class MySet<E> extends AbstractSet<E>{
      ...
      @Override public Iterator<E> iterator() {
          return new MyIterator();
      }
    
      private class MyIterator implements Iterator<E> {
          ...
      }
  }
  ```



**멤버 클래스에서 바깥 인스턴스에 접근할 일이 없다면 무조건 static을 붙여서 정적 멤버클래스로 만들자**. static을 생략하면 바깥 인스턴스의 숨은 외부 참조를 갖게되어 시공간이 소비되며, 가비지 컬렉션이 바깥 클래스의 인스턴스를 수거하지 못해 메모리 누수가 생길 수 있다.



### 익명 클래스

- 이름이 없다.
- 바깥 클래스의 멤버가 아니다.
- 쓰이는 시점에 선언과 동시에 인스턴스가 생성된다.
- 코드의 어디서든 생성이 가능하며, 오직 비정적인 문맥에서 사용될 때만 바깥 클래스의 인스턴스를 참조할 수 있다.
- 상수 정적 변수 외에는 정적 변수를 가질 수 없다.

```java
public class AnonymousExample {
    private double x;
    private double y;

    public double operate() {
        Operator operator = new Operator() {
            @Override
            public double plus() {
                System.out.printf("%f + %f = %f\n", x, y, x + y);
                return x + y;
            }
            @Override
            public double minus() {
                System.out.printf("%f - %f = %f\n", x, y, x - y);
                return x - y;
            }
        };
        return operator.plus();
    }
}

interface Operator {
    double plus();
    double minus();
}
```

#### 제약 사항

1. 선언한 지점에만 인스턴스를 만들 수 있다.
2. `instanceof` 검사나 클래스 이름이 필요한 작업은 수행 불가능
3. 여러 인터페이스 구현 불가능
4. 인터페이스를 구현하는 동시에 다른 클래스 상속 불가능
5. 클라이언트는 익명 클래스가 상위 타입에서 상속한 멤버 외에는 호출 불가능
6. 표현식 중간에 있어, 코드가 긴 경우 가독성이 떨어진다.



정적 팩터리 메서드 구현시 사용되기도 한다.

```java
static List<Integer> intArrayAsList(int[] a){
    Objects.requireNonNull(a);
  
    // Java9부터 다이아몬드 연산자를 아래와 같이 사용 가능. 더 낮은 버전에서는 AbstractList<Integer>로 변경
    return new AbstractList<>(){
      
        // AbstractList의 abstract 메서드로 반드시 구현해야함
        @Override public Integer get(int i){
            return a[i]; 
        }
      
        // 선택적으로 구현
        @Override public Integer set(int i,Integer val){
            int oldVal = a[i];
            a[i] = val;
            return oldVal;
        }
        
        // AbstractCollection의 abstract 메서드로 반드시 구현해야함
        @Override public int size(){
            return a.length; 
        }
    }
}
```

### 지역 클래스

중첩 클래스 중 가장 드물게 사용된다. 

- 지역 클래스는 지역 변수를 선언할 수 있는 곳이면 실질적으로 어디서든 선언할 수 있고, 유효 범위도 지역변수와 같다. 
- 멤버 클래스 처럼 이름이 있으며, 반복해서 사용할 수 있다.
- 익명 클래스처럼 비정적 문맥에서 사용될 떄만 바깥 인스턴스를 참조할 수 있으며, 정적 멤버는 가질 수 없고, 가독성을 위해 짧게 작성해야한다.

```java
public class LocalExample {
    private int number;

    public LocalExample(int number) {
        this.number = number;
    }

    public void foo() {
        // 지역변수처럼 선언해서 사용할 수 있다.
        class LocalClass {
            private String name;

            public LocalClass(String name) {
                this.name = name;
            }

            public void print() {
                // 비정적 문맥에선 바깥 인스턴스를 참조 할 수 있다.
                System.out.println(number + name);
            }
        }
        LocalClass localClass = new LocalClass("local");
        localClass.print();
    }
}
```

## 결론

중첩 클래스가 한 메서드 안에서만 쓰이면서 그 인스턴스를 생성하는 지점이 단 한 곳이고, 해당 타입으로 쓰기에 적합한 클래스나 인터페이스가 이미 있는 경우 익명 클래스로, 그렇지 않다면 지역 클래스로 구현해라.

## 참고

- [https://jyami.tistory.com/86](https://jyami.tistory.com/86)