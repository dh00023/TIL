# ITEM 65: 리플렉션보다는 인터페이스를 사용해라

#### `java.lang.reflection`

[리플렉션](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/2019-01-21-reflection.md)을 사용하면 프로그램에서 임의의 클래스에 접근할 수 있다.

- 임의의 클래스에 접근하면 그 클래스의 생성자, 메서드, 필드 인스턴스를 가져올 수 있음.
- 인스턴스들로 해당 클래스의 멤버 명, 필드 타입, 메서드 시그니처 등을 가져올 수 있음
- 인스턴스를 활용해 각각에 연결된 실제 생성자, 메서드, 필드를 조작할 수 있다.
    - 생성자로 클래스 인스턴스 생성
    - 메서드 호출(`Method.invoke`)
    - 필드 접근
- 컴파일 당시에 존재하지 않던 클래스도 이용할 수 있다.

#### 단점

- 컴파일타임 타입 검사가 주는 이점을 하나도 누릴 수 없다. >> 런타임 오류 발생 가능
- 리플렉션을 이용하면 코드가 지저분하고 장황해진다.
- 성능이 떨어진다.
    - 리플렉션을 통한 메서드 호출은 일반 메서드 호출보다 훨씬 느리다.



위와 같은 단점으로 리플렉션은 제한된 형태로 사용해야 단점을 피하고 이점을 취할 수 있다.

```java
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Arrays;
import java.util.Set;

public class RflectionMain {
    public static void main(String[] args) {
        // 클래스명 Class 객체로 변환
        Class<? extends Set<String>> cl = null;
        try {
            cl = (Class<? extends Set<String>>) Class.forName(args[0]);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        // 생성자
        Constructor<? extends Set<String>> cons = null;
        try {
            cons = cl.getDeclaredConstructor();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }

        // 집합의 인스턴스를 만든다.
        Set<String> s = null;
        try {
            s = cons.newInstance();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }

        s.addAll(Arrays.asList(args).subList(1, args.length));

    }
}

```

대부분의 경우 리플렉션은 위 예시 정도만 사용해도 충분한 경우가 많다. 하지만, 이 예는 리플렉션의 단점을 2가지 보여준다.

1. 런타임시 총 6가지 예외를 던질 수 있다.
2. 클래스 이름만으로 인스턴스를 생성하기위해 25줄 코드 작성
    - `ReflectiveOperationException` (자바7부터 지원)을 잡도록 해 코드 길이를 줄일 수도 있다.

비검사 형변환 경고가 발생하나, [ITEM 27: 비검사 경고를 제거해라](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-05-20-remove-unchecked-warning.md)처럼 비검사 형변환 경고는 지워주는 것이 좋다.



리플렉션은 런타임에 존재하지 않을 수도 있는 다른 클래스, 메서드, 필드와 의존성을 관리할 때 적합하며, 버전이 여러개 존재하는 외부 패키지를 다룰 때 유용하다.