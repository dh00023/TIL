# ITEM 4: ENFORCE NONINSTANTIABILITY WITH A PRIVATE CONSTRUCTOR

```java
// Util이지만 생성자가 없음
public class ImageUtility {
    private static String IMAGE_DATE_FORMAT = "yyyyMMddHHmm";

    public static String makeImageFileNm(String imgFileNm) {
        return imgFileNm + "_" + new SimpleDateFormat(IMAGE_DATE_FORMAT).format(new Date());
    }
}
```

생성자를 명시하지 않으면 컴파일러가 자동으로 매개변수를 받지 않는 public 생성자를 만든다. 이때 사용자는 이 생성자가 자동으로 생성된 것인지 구분할 수 없으며, 

```java
// 다음과 같이 사용하기를 바랬으나,
ImageUtility.makeImageFileNm("test", ".png");
    
// 생성자를 생성해서 사용할 수도 있음
ImageUtility imageUtility = new ImageUtility();
String imageFileNm = imageUtility.makeImageFileNm("test", ".png");
```

이처럼 의도치 않게 인스턴스화할 수 있게된 클래스들도 발생한다.

```java
// Util이지만 생성자가 없음
abstract class ImageUtility {
    private static String IMAGE_DATE_FORMAT = "yyyyMMddHHmm";

    public static String makeImageFileNm(String imgFileNm) {
        return imgFileNm + "_" + new SimpleDateFormat(IMAGE_DATE_FORMAT).format(new Date());
    }
}
```

```java
public class ItemImageUtility extends ImageUtility {
  // ...
}
```

```java
// 추상클래스이기 때문에 생성자 생성 불가
// ImageUtility imageUtility = new ImageUtility();

// 상속받은 클래스에서 생성자 호출 가능
ItemImageUtility itemImageUtility = new ItemImageUtility();
```

**추상 클래스로 만드는 것으로는 인스턴스화를 막을 수 없으며, private 생성자를 추가하면 클래스의 인스턴스화를 막을 수 있다.**

```java
public class ImageUtility {
    // 기본 생성자가 만들어지는 것을 방어(인스턴스화 방지용)
    private ImageUtility(){
        throw new AssertionError();
    }
}
```

`private` 생성자이므로 클래스 외부에서는 접근할 수 없으며, 내부에서 실수로 생성자를 호출하는 경우에 대응하기 위해 `AssrtionError` 예외처리를 했다. 하지만, 생성자가 있는데 호출할 수 없는 것은 직관적이지 않으므로, 적절한 주석을 다는 것을 권장한다.

또한, private 생성자는 상속도 불가능하다. 모든 생성자는 상위 클래스의 생성자를 호출하게 되는데, 이를 `private` 선언으로 하위클래스가 상위 클래스의 생성자에 접근을 못해 상속이 불가능하다.



## 사용되는 Utility

### `java.util.Arrays`

```java
public class Arrays {

    /**
     * The minimum array length below which a parallel sorting
     * algorithm will not further partition the sorting task. Using
     * smaller sizes typically results in memory contention across
     * tasks that makes parallel speedups unlikely.
     */
    private static final int MIN_ARRAY_SORT_GRAN = 1 << 13;

    // Suppresses default constructor, ensuring non-instantiability.
    private Arrays() {}

    /**
     * A comparator that implements the natural ordering of a group of
     * mutually comparable elements. May be used when a supplied
     * comparator is null. To simplify code-sharing within underlying
     * implementations, the compare method only declares type Object
     * for its second argument.
     *
     * Arrays class implementor's note: It is an empirical matter
     * whether ComparableTimSort offers any performance benefit over
     * TimSort used with this comparator.  If not, you are better off
     * deleting or bypassing ComparableTimSort.  There is currently no
     * empirical case for separating them for parallel sorting, so all
     * public Object parallelSort methods use the same comparator
     * based implementation.
     */
    static final class NaturalOrder implements Comparator<Object> {
        @SuppressWarnings("unchecked")
        public int compare(Object first, Object second) {
            return ((Comparable<Object>)first).compareTo(second);
        }
        static final NaturalOrder INSTANCE = new NaturalOrder();
    }
   ...
```

인스턴스화를 하지 않기 위해 private 생성자를 선언한 것을 볼 수 있으며, 배열 관련 메서드들을 모아 놓두었다.

### `java.lang.Math`

```java
public final class Math {

    /**
     * Don't let anyone instantiate this class.
     */
    private Math() {}

    /**
     * The {@code double} value that is closer than any other to
     * <i>e</i>, the base of the natural logarithms.
     */
    public static final double E = 2.7182818284590452354;

    /**
     * The {@code double} value that is closer than any other to
     * <i>pi</i>, the ratio of the circumference of a circle to its
     * diameter.
     */
    public static final double PI = 3.14159265358979323846;

    /**
     * Returns the trigonometric sine of an angle.  Special cases:
     * <ul><li>If the argument is NaN or an infinity, then the
     * result is NaN.
     * <li>If the argument is zero, then the result is a zero with the
     * same sign as the argument.</ul>
     *
     * <p>The computed result must be within 1 ulp of the exact result.
     * Results must be semi-monotonic.
     *
     * @param   a   an angle, in radians.
     * @return  the sine of the argument.
     */
    public static double sin(double a) {
        return StrictMath.sin(a); // default impl. delegates to StrictMath
    }

```

Math에 대한 기본 타입(PI, E)이나 관련 메서드들을 모아두었다.

### `java.util.Collection`

특정 인터페이스르 구현하는 객체를 생성해주는 정적 메서드(팩터리)를 모아놓을 수 있다. (java8부터 이런 메서드를 인터페이스에 넣을 수 있음)

### final 클래스와 관련 메서드

final class를 상속해서 하위 클래스에 메서드를 넣는 것은 불가능하므로, final 클래스와 관련 메서드들을 모아놓을때도 사용한다.