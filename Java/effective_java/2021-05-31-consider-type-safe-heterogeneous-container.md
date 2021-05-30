# ITEM 33: 타입 안전 이종 컨테이너를 고려해라

- [기본 Generic 문법 알아보기](https://github.com/dh00023/TIL/blob/master/Java/%EB%AC%B8%EB%B2%95/java-generic.md)
- 관련 용어

  | 한글                     | 영문                    | 예                                 |
  | ------------------------ | ----------------------- | ---------------------------------- |
  | 매개변수화 타입          | parameterized type      | `List<String>`                     |
  | 실제 타입 매개변수       | actual type parameter   | `String`                           |
  | 제네릭 타입              | generic type            | `List<E>`                          |
  | 정규 타입 매개변수       | formal type parameter   | `E`                                |
  | 비한정적 와일드카드 타입 | unbounded wildcard type | `List<?>`                          |
  | 로 타입                  | raw type                | `List`                             |
  | 한정적 타입 매개변수     | bounded type parameter  | `<E extends Number>`               |
  | 재귀 타입 한정           | recursive type bound    | `<T extends Comparable<T>>`        |
  | 한정적 와일드카드 타입   | bounded wildcard type   | `List<? extends Number>`           |
  | 제네릭 메서드            | generic method          | `static <E> List<E> asList(E[] a)` |
  | 타입 토큰                | type token              | `String.class`                     |

------

컬렉션 API로 대표되는 일반적인 제네릭 형태에서는 한 컨테이너가 다룰 수 있는 타입 매개변수의 수가 고정되어 있다. 

- 제네릭은 `Set<E>`, `Map<K,V>` 등 컬렉션과 `ThreadLocal<T>`, `AtomicReference<T>` 등 단일원소 컨테이너에 흔히 쓰인다. 이런 쓰임에서 매개변수화되는 대상은 컨테이너 자신이며, 하나의 컨테이너에서 매개변수화할 수 있는 타입의 수가 제한된다.

이보다 더 유연한 수단이 필요하다면 타입 안전 이종 컨테이너를 사용하면된다.

- 컨테이너 자체가 아닌 키를 타입 매개변수로 바꾸어서 제약이 없는 타입 안정 이종 컨테이너를 만들 수 있다.

## 타입 안전 이종 컨테이너 패턴

타입 안전 이종 컨테이너 패턴(type safe heterogeneous container pattern)이란 무엇일까?

- 컨테이너 대신 키를 타입 매개변수화 한다.
- 컨테이너에서 값을 넣거나 뺄 때 매개변수화한 키를 함께 제공한다.
- 제네릭 타입 시스템이 값의 타입이 키와 같음을 보장해준다.

```java
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Favorites {
    private Map<Class<?>, Object> favorites = new HashMap<>();

    public <T> void putFavorite(Class<T> type, T instance) {
        favorites.put(Objects.requireNonNull(type), instance);
    }

    public <T> T getFavorite(Class<T> type) {
        return type.cast(favorites.get(type));
    }

    public static void main(String[] args) {
        Favorites f = new Favorites();

        f.putFavorite(String.class, "Java");
        f.putFavorite(Integer.class, 0xcafebabe);
        f.putFavorite(Class.class, Favorites.class);

        String favoriteString = f.getFavorite(String.class);
        int favoriteInteger = f.getFavorite(Integer.class);
        Class<?> favoriteClass = f.getFavorite(Class.class);

            System.out.printf("%s %x %s%n", favoriteString, favoriteInteger, favoriteClass.getName()); // Java cafebabe Favorites
    }
}
```

- `Class`의 리터럴 타입은 `Class`가 아닌 `Class<T>`이다.
    - `String.class` 는 `Class<String>`
    - `Integer.class`는 `Class<Integer>`
- 컴파일타임 타입 정보와 런타임 타입정보를 알아내기 위해 메서드들이 주고 받는 class리터럴를 **타입 토근(type token)**이라 한다.
- 즉, 타입 안전 이종 컨테이너는 `Class`를 키로 쓰며 이렇게 쓰이는 `Class` 객체를 타입 토큰이라 한다. (직접 구현한 키 타입도 사용 가능)

이 예제에서 `Favorites` 인스턴스는 타입 안전하며, `String`을 요구했는데, `Integer`를 반환할 일은 절대 없다. 또한 모든 키의 타입이 제각각이기 떄문에 여러가지 타입의 원소를 넣을 수 있다.

`Map<Class<?>, Object>` 의 Key가 비한정적 와일드카드 타입이기 때문에 모든 키가 서로 다른 매개변수화 타입을 가질 수 있다.
여기서 Value는 단순히 `Object`로 키와 값 사이의 타입관계를 보증하지 않는다. ( 모든 값이 키로 명시한 타입임을 보증하지 않음. ) 

`putFavorite()`은 주어진 `Class` 객체와 인스턴스를 추가해 관계를 맺고 있으며, 여기서 키와 값사이의 타입 링크(type linkage) 정보는 버려진다. 즉, 그 값이 해당  키 타입의 인스턴스라는 정보가 사라진다.

`getFavorite()`에서 우선 주어진 `Class`객체에 해당 하는 값을 `favorites` 맵에서 꺼낸다. 이 객체가 반환해야할 타입 객체는 맞지만, 잘못된 컴파일타임 타입(`Object`)을 갖고 있어 `T`타입으로 변환해서 반환해줘야한다. `Class`의 `cast()` 메서드를 사용해 객체가 가리키는 타입으로 동적 형변환하여 가져오는 것을 볼 수 있다.

```java
public final class Class<T> {
                                
        @SuppressWarnings("unchecked")
    @HotSpotIntrinsicCandidate
    public T cast(Object obj) {
        if (obj != null && !isInstance(obj))
            throw new ClassCastException(cannotCastMsg(obj));
        return (T) obj;
    }
}
```

`Class`의 `cast()` 메서드는 객체 참조를 객체가 가리키는 타입으로 동적 변환한다. `cast()` 메서드의 시그니처가 `Class` 클래스가 제네릭인 점을 완벽히 활용하고 있다. 
Favorites 를 `T`로 비검사 형변환하지 않고도 타입 안전하게 만들 수 있는 것이다.

### 제약

#### 악의적인 클라이언트가 `Class` 객체를 제네릭이 아닌 로타입으로 넘기면 안전성이 깨진다.

```java
favorites.put((Class) Integer.class, "Invalid Type");
int value = favorites.getFavorite(Integer.class); //ClassCastException 발생
```

여기서 컴파일은 가능하지만 비검사 경고가 발생하고, 런타임시 `ClassCastException` 오류가 발생한다.
여기서 `Favorites`가 타입 불변식을 어기는 일이 없도록 보장하기 위해서는 `putFavorite()` 메서드를 다음과 같이 수정해줘야한다.

```java
    public <T> void putFavorite(Class<T> type, T instance) {
        favorites.put(Objects.requireNonNull(type), type.cast(instance));
    }
```

`type.cast(instance))` 로 변경하여, 주어진 instance의 타입이 type으로 명시한 타입과 같은지 확인하면 된다.

- `Collections.checkedList`, `Collections.checkedSet `, `Collections.checkedMap`은 바로 이러한 방법을 적용한 컬렉션 래퍼들이다.
    - 이 정적 팩터리들은 컬렉션과 함께 1개 혹은 2개의 `Class` 객체를 받는다.
    - 이 메서드들은 모두 제네릭이므로, `Class` 객체와 컬렉션의 컴파일타임 타입이 같음을 보장한다.
    - 또한, 내부 컬렉션들을 실체화 한다.
    - 제네릭과 로 타입을 섞어 사용하는 코드가 컬렉션에 잘못된 타입의 원소를 넣지 못하게 하는데 도움을 준다.

#### 실체화 불가 타입에는 사용할 수 없다.

`String`, `String[]`는 저장할 수 있어도, `List<String>` 은 저장할 수 없다.
왜냐하면,  `List<String>`과 `List<Integer>`둘다  `List.class` 라는 객체를 공유하기 때문에  `List<String>` 용 `Class` 객체를 알 수 없다.

### 한정적 타입 토큰

`Favorites` 은 비한정적 타입 토큰을 사용한다. 다시말해 `getFavorite`과 `putFavorite`은 어떤 `Class` 객체든 받아들인다.
만약 허용하는 타입만을 제한하고 싶은 경우에는 한정적 타입 토큰을 활용하면 가능하다. 

**한정적 타입 토큰은 단순히 한정적 타입 매개변수나 한정적 와일드카드를 사용해 표현 가능한 타입을 제한하는 타입 토큰**이다.

```java
package java.lang.annotation;

public interface Annotation {
    boolean equals(Object obj);
    int hashCode();
    String toString();
    Class<? extends Annotation> annotationType();
}
```

`Annotation` 은 한정적 타입 토큰으로 적극적으로 활용된다. 

```java
public <T extends Annotation> T getAnnotation(Class<T> annotationType);
```

여기서 `annotationType` 인수는 어노테이션 타입을 뜻하는 한정적 타입토큰이다. 이 메서드는 토큰으로 명시한 타입의 어노테이션이 대상 요소에 달려 있다면 그 어노테이션을 반환하고, 없다면 `null`을 반환한다. 즉, 키가 어노테이션 타입인 타입 안전 이종 컨테이너인 것이다.

여기서  `Class<?>` 와 같이 비한정 와일드카드 타입을 한정적 타입 토큰을 받는 메서드에 전달할 때 객체를 `Class<? extends Annotation>`으로 형변환 할 수는 있지만 이 형변환은 비검사이므로 비검사 경고 문구가 뜰 것 이다.

`Class` 에서 이러한 형변환을 안전하게 동적으로 수행해주는 `asSubclass` 메서드를 제공해준다.

```java
        public <U> Class<? extends U> asSubclass(Class<U> clazz) {
        if (clazz.isAssignableFrom(this))
            return (Class<? extends U>) this;
        else
            throw new ClassCastException(this.toString());
    }
```

`asSubclass`는 호출된 인스턴스 자신의  `Class` 객체를 인수가 명시한 클래스로 형변환 해준다. 여기서 형변환된다는 것은 이 클래스가 인수로 명시한 클래스의 하위 클래스라는 의미이다. 형변환에 성공하면 인수로 받은 클래스 객체를 반환하고, 실패하면 `ClassCastException` 예외를 발생시킨다.

```java
static Annotation getAnnotation(AnnotatedElement element, String annotationTypeName) {
  Class<?> annotationType = null; //비한정적 타입 토큰
  try {
    annotationType = Class.forName(annotationTypeName);
  } catch (Exception ex) {
    throw new IllegalArgumentException(ex);
  }
  
  return element.getAnnotation(annotationType.asSubclass(Annotation.class));
}
```

다음과 같이 컴파일 시점에는 타입을 알 수 없는 애너테이션을  `asSubclass` 메서드를 사용해 런타임시에 알아내는 예시이다.