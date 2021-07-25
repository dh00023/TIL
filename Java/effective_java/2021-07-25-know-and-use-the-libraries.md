# ITEM 59: 라이브러리를 익히고 사용해라

```java
static Random rnd = new Random();

static int random(int n) {
  return Math.abs(rnd.nextInt()) % n;
}
```

위 코드에는 3가지 문제점이 있다.

1. n이 크지 않은 2의 제곱수라면 얼마 지나지 않아 같은 수열이 반복된다.
2. n이 2의 제곱수가 아니라면, 일부 숫자가 평균적으로 더 자주 반환되며, n값이 크면 위 현상은 더 두드러진다.

```java
int n = 2 * (Integer.MAX_VALUE / 3);
int low = 0;

for(int i = 0; i < 1000000; i++)
  if(random(n) < n/2)
    low++;
```

random코드가 이상적으로 동작한다면 50만개가 출력되야하지만, 실제로 돌리는 경우 666, 349가 나왔으며 약 2/3정도가 낮은 값으로 나온 것을 볼 수 있다.

3. `rnd.nextInt()` 가 반환 값을 `Math.abs`를 이용해 음수가 아닌 정수로 매핑하기 때문에 지정한 범위 '바깥' 수가 종종 나올 수 있다.

이러한 모든 문제점은 `Random.nextInt(int)`가 모든 것을 해결했으며, 이 라이브러리를 사용하면된다.

java7부터는 `Random`을 사용하지 않는 것이 좋으며, `ThreadLocalRandom`으로 대체해 사용하는 것이 좋다. 고품질의 무작위 수를 생성할 뿐만 아니라 속도도 더 빠르다.
포크-조인 풀이나 병렬 스트림에서는 `SplittableRandom`을 사용하면 된다.

## 표준 라이브러리를 사용해야 되는 이유

1. 그 코드를 작성한 지식과 앞서 사용한 다른 프로그래머들의 경험을 활용할 수 있다.
2. 핵심적인 일과 크게 관련 없는 문제를 해결하느라 시간을 허비하지 않아도 된다.
3. 따로 노력하지 않아도 성능이 지속해서 개선된다.
4. 기능이 점점 많아진다.
5. 내가 작성한 코드가 다른 사람에게 낯익은 코드가 되어, 다른 개발자들에게 가독성 좋고, 유지보수하기 좋고, 재활용하기 쉬운 코드가 된다.

## 라이브러리 메이저 릴리스

메이저 릴리스마다 수많은 기능이 추가된다.

- [JDK 10 Release Notes](https://www.oracle.com/java/technologies/javase/10-relnote-issues.html#NewFeature)
- [JDK 11 Release Notes](https://www.oracle.com/java/technologies/javase/jdk-11-relnote.html#NewFeature)

## 꼭 알아야하는 라이브러리

- `java.lang`
- `java.util`
- `java.io`

위 3개 패키지와 그 하위 패키지는 익숙해지는 것이 좋으며, 다른 라이브러리도 필요시마다 익히는 것이 좋다.



라이브러리가 필요한 기능을 충분히 제공하지 못하는 경우에도, 최대한 라이브러리를 사용하려고 시도해보는 것이 좋다.
표준 라이브러리에서 원하는 기능을 찾지 못한다면, 고품질의 서드파티 라이브러리(ex Guava)를 사용하는 것이 좋다.
