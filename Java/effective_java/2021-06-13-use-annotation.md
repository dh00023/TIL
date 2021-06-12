# ITEM39: 명명 패턴보다 애너테이션을 사용해라

## 명명패턴

기존에는 도구나 프레임워크가 다뤄야할 프로그램 요소에는 딱 구분되는 명명패턴을 적용했었다.
ex) JUnit 3까지는 테스트 메서드 이름을 `test`로 반드시 시작해야만 했다.(`testXxxx`)

### 단점

- 오타가 나면 안된다.
    - ex) JUnit3에서 `tsetSafetyOverride`로 지으면 해당 메서드는 무시하고 지나치며, 개발자는 테스트가 통과했다고 생각할 수 있다.
- 올바른 프로그램 요소에서만 사용된다는 보장이 없다.
    - ex) JUnit3에서 메서드가 아닌 클래스 이름을 `TestXxx`와 같이 지어 해당 클래스 내부 메서드를 테스트하고 싶어도, JUnit은 경고 메세지도 없이 해당 클래스 메서드 테스트를 수행하지 않고 넘어간다.
- 프로그램 요소를 매개변수로 전달할 적절한 방법이 없다.
    - 특정 예외를 던져야만 성공하는 테스트가 있을때, 테스트할 방법이 없다.

## 애너테이션

애너테이션은 명명패턴의 단점을 모두 해결할 수 있으며, JUnit 4부터 애너테이션을 전면 도입했다.

```java
import java.lang.annotation.*;

/**
 * 테스트 메서드임을 선언
 * 매개변수 없는 정적 메서드 전용
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface Test {
}
```

위 `@Test` 애너테이션은 자동으로 수행되는 간단한 테스트용으로, 예외가 발생하면 해당 테스트를 실패로 처리한다.

### 메타 애너테이션

애너테이션 선언에 다는 애너테이션

-  `@Retention(RetentionPolicy.RUNTIME)` : 런타임시에도 유지되어야 한다.
    - [@Retention](https://github.com/dh00023/TIL/blob/master/Java/%EC%8B%AC%ED%99%94/2021-06-12-retention-annotation.md) 
-  `@Target(ElementType.METHOD)` : 반드시 메서드 선언에서면 사용되어야 한다.
    - [@Target](https://github.com/dh00023/TIL/blob/master/Java/%EC%8B%AC%ED%99%94/2021-06-12-target-annotation.md) 

### 마커 애너테이션

아무 매개변수 없이 단순히 대상에 마킹

- 대상 코드의 의미는 그대로 두고, 그 어노테이션에 관심 있는 도구에서 특별한 처리를 할 수 있게 해준다.
- 실제 클래스에 영향은 주지 않으며, 애너테이션에 관심있는 프로그램에 추가 정보를 제공해준다.

```java
public class AnnotationSample {
    @Test public static void m1() { }

    @Test public static void m2() {
        throw new RuntimeException("fail");
    }

    /**
     * 정적 메서드가 아님 -> 잘못 적용
     */
    @Test public void m3() { }

    public static void m4(){ }
}

```

```java
public class RunTests {
    public static void main(String[] args) throws ClassNotFoundException {
        int cnt = 0;
        int passed = 0;

        Class<?> testClass = Class.forName("ch6.dahye.item39.AnnotationSample");

        for (Method m : testClass.getDeclaredMethods()) {
            if (m.isAnnotationPresent(Test.class)) {
                cnt++;
                try {
                    m.invoke(null);
                    passed++;
                } catch (InvocationTargetException e) {
                    Throwable exc = e.getCause();
                    System.out.println(m + " 실패: " + exc);
                } catch (Exception e) {
                    System.out.println("잘못 사용한 예 " + m);
                }
            }
        }
        System.out.printf("성공 : %d, 실패: %d%n", passed, cnt-passed);
    }
}
```

```
잘못 사용한 예 public void ch6.dahye.item39.AnnotationSample.m3()
public static void ch6.dahye.item39.AnnotationSample.m2() 실패: java.lang.RuntimeException: fail
성공 : 1, 실패: 2
```

### 매개변수 1개 받는 어노테이션

여기서 특정 예외를 던져야만 성공하는 테스트를 지원하기위해 `@ExceptionTest` 어노테이션을 한개 더 생성했다.

```java
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * 명시한 예외를 던져야만 성공하는 테스트 메서드용 어노테이션
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface ExceptionTest {
    Class<? extends Throwable> value();
}
```

`Class<? extends Throwable>` 매개변수 타입은 `Throwable`을 확장한 클래스 객체이므로 모든 예외와 오류 타입을 수용할 수 있다.

```java
public class AnnotationSample {
    @ExceptionTest(ArithmeticException.class)
    public static void m5(){
        int i = 0;
        i = i / i;
    }

    /**
     * 다른 예외 발생 실패
     */
    @ExceptionTest(ArithmeticException.class)
    public static void m6(){
        int[] a = new int[0];
        int i = a[1];
    }

    /**
     * 예외 발생하지 않음 실패
     */
    @ExceptionTest(ArithmeticException.class)
    public static void m7(){ }
}

```

```java
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;

public class RunTests {
    public static void main(String[] args) throws ClassNotFoundException {
        int cnt = 0;
        int passed = 0;

        Class<?> testClass = Class.forName("ch6.dahye.item39.AnnotationSample");

        for (Method m : testClass.getDeclaredMethods()) {
            if (m.isAnnotationPresent(ExceptionTest.class)) {
                cnt++;
                try {
                    m.invoke(null);
                    System.out.printf("test %s fail: 예외를 던지지 않음%n", m);
                }catch (InvocationTargetException e) {
                    Throwable exc = e.getCause();
                    Class<? extends Throwable> excType = m.getAnnotation(ExceptionTest.class).value();
                    if (excType.isInstance(exc)) {
                        passed++;
                    } else {
                        System.out.printf("test %s fail: 기대한 예외 %s, 발생한 예외 %s%n", m, excType.getName(), exc);
                    }
                } catch (Exception e) {
                    System.out.println("잘못 사용한 예 " + m);
                }
            }
        }
        System.out.printf("성공 : %d, 실패: %d%n", passed, cnt - passed);
    }
}

```

```
test public static void ch6.dahye.item39.AnnotationSample.m7() fail: 예외를 던지지 않음
test public static void ch6.dahye.item39.AnnotationSample.m6() fail: 기대한 예외 java.lang.ArithmeticException, 발생한 예외 java.lang.ArrayIndexOutOfBoundsException: Index 1 out of bounds for length 0

성공 : 1, 실패: 2
```

이 어노테이션은 `@Test` 어노테이션과 다른 점은 매개변수 값을 추출하여 테스트 메서드가 올바른 예외를 던지는지 확인하는데 사용한다는 것이다. 형변환 코드가 없어 `ClassCastException` 걱정이 없으므로, 테스트 프로그램이 문제없이 컴파일되면 어노테이션 매개변수가 가리키는 예외가 올바른 타입이라는 것이다.
이때, 예외 클래스 파일이 컴파일타임에는 존재했으나 런타임에는 존재하지 않을 수 있으며, 이런 경우 `TypeNotPresentException` 예외가 발생할 것이다.



### 배열 매개변수 받는 어노테이션

```java
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * 명시한 예외를 던져야만 성공하는 테스트 메서드용 어노테이션
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface ExceptionTest {
    Class<? extends Throwable>[] value();
}

```

배열 매개변수로 받는 어노테이션은 위 1개 매개변수를 받는 `@ExceptionTest` 들도 모두 수정없이 수용한다.

```java
@ExceptionTest({ IndexOutOfBoundsException.class, NullPointerException.class })
public static void doubleBad() {
  List<String> list = new ArrayList<>();
  
  // IndexOutOfBoundsException, NullPointerException
  list.addAll(5, null);
}
```

위 예제와 같이 원소들을 중괄호(`{}`)로 감싸고, 쉼표(`,`)로 구분해주면 된다.

```java
package ch6.dahye.item39;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;

public class RunTests {
    public static void main(String[] args) throws ClassNotFoundException {
        int cnt = 0;
        int passed = 0;

        Class<?> testClass = Class.forName("ch6.dahye.item39.AnnotationSample");

        for (Method m : testClass.getDeclaredMethods()) {
            if (m.isAnnotationPresent(ExceptionTest.class)) {
                cnt++;
                try {
                    m.invoke(null);
                    System.out.printf("test %s fail: 예외를 던지지 않음%n", m);
                }catch (InvocationTargetException e) {
                    Throwable exc = e.getCause();
                    int oldPassed = passed;
                    Class<? extends Throwable>[] excTypes = m.getAnnotation(ExceptionTest.class).value();
                    for (Class<? extends Throwable> excType : excTypes) {
                        if (excType.isInstance(exc)) {
                            passed++;
                            break;
                        } else {
                            System.out.printf("test %s fail: 기대한 예외 %s, 발생한 예외 %s%n", m, excType.getName(), exc);
                        }
                    }
                    if (passed == oldPassed) {
                        System.out.printf("테스트 %s 실패 : %s %n", m, exc);
                    }
                } catch (Exception e) {
                    System.out.println("잘못 사용한 예 " + m);
                }
            }
        }
        System.out.printf("성공 : %d, 실패: %d%n", passed, cnt - passed);
    }
}
```

`Class<? extends Throwable>[]`로 배열로 값을 받아온 후에 모든 예외 처리가 성공한 경우에만 테스트 성공으로 판단하도록 수정한 코드이다.

### 반복 가능한 어노테이션 타입

Java 8부터는 여러 개의 값을 받는 어노테이션을 배열 매개변수를 사용하는 대신 `@Repeatable` 메타 어노테이션을 달아서 구현할 수 있다.

- [@Repeatable](https://github.com/dh00023/TIL/blob/master/Java/%EC%8B%AC%ED%99%94/2021-06-13-repeatable-annotation.md) 

#### Repeatable 어노테이션

```java
import java.lang.annotation.*;

/**
 * 명시한 예외를 던져야만 성공하는 테스트 메서드용 어노테이션
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
@Repeatable(ExceptionTestContainer.class)
public @interface ExceptionTest {
    Class<? extends Throwable> value();
}
```

`@Repeatable` 어노테이션에는 해당 어노테이션을 반환할 컨테이너 어노테이션(`@ExcpetionTestContainer`)를 매개변수로 전달하고 있다.

#### Container Annotation

```java
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface ExceptionTestContainer {
    ExceptionTest[] value();
}

```

컨테이너 어노테이션은 `@Repeatable`을 단 어노테이션을 반환하는 어노테이션으로, 내부 어노테이션 타입(`@ExceptionTest`)의 배열을 반환하는 `value()` 메서드를 선언해줘야한다.
또한, 적절한 보존 정책(`@Retention`)과 적용 대상(`@Target`)을 명시해줘야 컴파일 오류가 발생하지 않을 것이다.

```java
    @ExceptionTest(IndexOutOfBoundsException.class)
    @ExceptionTest( NullPointerException.class)
    public static void doubleBad() {
        List<String> list = new ArrayList<>();
        // IndexOutOfBoundsException, NullPointerException
        list.addAll(5, null);
    }
```



```java
package ch6.dahye.item39;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;

public class RunTests {
    public static void main(String[] args) throws ClassNotFoundException {
        int cnt = 0;
        int passed = 0;

        Class<?> testClass = Class.forName("ch6.dahye.item39.AnnotationSample");

        for (Method m : testClass.getDeclaredMethods()) {
            if (m.isAnnotationPresent(ExceptionTest.class) || m.isAnnotationPresent(ExceptionTestContainer.class)) {
                cnt++;
                try {
                    m.invoke(null);
                    System.out.printf("test %s fail: 예외를 던지지 않음%n", m);
                }catch (InvocationTargetException e) {
                    Throwable exc = e.getCause();
                    int oldPassed = passed;
                    ExceptionTest[] excTypes = m.getAnnotationsByType(ExceptionTest.class);
                    for (ExceptionTest excType : excTypes) {
                        if (excType.value().isInstance(exc)) {
                            passed++;
                            break;
                        } else {
                            System.out.printf("test %s fail: 기대한 예외 %s, 발생한 예외 %s%n", m, excType.value().getName(), exc);
                        }
                    }
                    if (passed == oldPassed) {
                        System.out.printf("테스트 %s 실패 : %s %n", m, exc);
                    }
                } catch (Exception e) {
                    System.out.println("잘못 사용한 예 " + m);
                }
            }
        }
        System.out.printf("성공 : %d, 실패: %d%n", passed, cnt - passed);
    }
}

```

-  `getAnnotationsByType` 메서드 : 컨테이너 어노테이션과 반복 가능 어노테이션을 구분하지 않고 모두 가져옴.
- `isAnnotationPresent` 메서드: 컨테이너 어노테이션과 반복 가능 어노테이션을 명확히 구분
    - `@ExceptionTest`를 여러번 단 메서드는 `m.isAnnotationPresent(ExceptionTest.class)` 에 포함되지 않아 테스트를 모두 통과한다.
    - `@ExceptionTest`를 한번만 단 메서드는 `m.isAnnotationPresent(ExceptionTestContainer.class)`에 포함되지 않아 무시하고 지나친다.

`@Refeatable`을 사용해 코드의 가독성을 개선할 수 있다면, 이 방법을 사용하는 것이 좋으나 어노테이션을 선언하고 이를 처리하는 부분에서 코드가 늘어나며, 처리 코드가 복잡해진다는 사실을 명심해야한다.

어노테이션으로 할 수 있는 일을 명명 패턴으로 처리할 이유는 없으며, 자바 프로그래머라면 예외 없이 자바가 제공하는 어노테이션 타입을 사용해야한다. 