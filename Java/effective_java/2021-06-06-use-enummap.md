# ITEM 37: ordinal 인덱싱 대신 EnumMap을 사용해라

```java
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
class Plant {
    enum LifeCycle { ANNUAL, PERENNIAL, BIENNIAL }

    final String name;
    final LifeCycle lifeCycle;

    @Override
    public String toString() {
        return name;
    }
}
```

```java
Set<Plant>[] plantsByLifeCycle = (Set<Plant>[]) new Set[Plant.LifeCycle.values().length];
for (int i = 0; i < plantsByLifeCycle.length; i++) {
  plantsByLifeCycle[i] = new HashSet<>();
}
for (Plant p : garden) {
  plantsByLifeCycle[p.lifeCycle.ordinal()].add(p)
}
```

다음은 정원에 심은 식물들을 배열 하나로 관리하고, 생애주기별로 묶는 예제이다. 이때, `ordinal()` 값을 그 배열의 인덱스로 사용하고 있는데, 여기에는 문제점이 많다.
배열은 제네릭과 호환되지 않기때문에, 비검사 형변환을 수행해야하고 깔끔하게 컴파일되지 않을 것이다. 또한, 배열과 인덱스의 의미를 모르기때문에 출력 결과에 직접 레이블을 달아야한다. 여기서 가장 큰 문제는 정수는 열거타입과 다르게 타입 안전성이 지켜지지 않으므로, 정확한 정숫값을 사용한다는 것을 직접 보장해야한다는 점이다.

**열거 타입을 키로 사용하도록 설계된 EnumMap을 사용해 위 문제점을 해결할 수 있다.**

```java
Map<Plant.LifeCycle, Set<Plant>> plantsByLifeCycle = new EnumMap<>(Plant.LifeCycle.class);

for (Plant.LifeCycle lc : Plant.LifeCycle.values())
  plantsByLifeCycle.put(lc, new HashMap<>());
  
for (Plant p : garden) 
  plantsByLifeCycle.get(p.lifeCycle).add(p);
```

더 짧고 명료할뿐만 아니라, 안전하고 성능도 이전과 비슷하다. 안전하지 않은 형변환은 쓰지 않고 있으며, Map의 키인 열거 타입이 그 자체로 출력용 문자열을 제공해 출력 결과에 직접 레이블을 추가할 필요도 없다.
또한, 배열 인덱스를 계산하는 과정에서 오류가 날 가능성도 없어진다.
`EnumMap`은 내부에서 배열을 사용하고 있으며, 내부 구현방식을 안으로 숨겨 `Map`의 타입 안전성과 배열의 성능을 가지고 있다. 여기서 `EnumMap`의 생성자가 받는 키 타입의 `Class` 객체는 한정적 타입 토큰으로, 런타임 제네릭 타입 정보를 제공하고 있다.

`stream` 을 사용해 코드를 더 줄일 수 있다.

#### EnumMap 미사용

```java
System.out.println(Arrays.stream(garden)
                  .collect(Collectors.groupingBy(p -> p.lifeCycle)));
```

`EnumMap`이 아닌  `Map` 구현체를 사용했기 때문에 `EnumMap`을 써서 얻은 공간과 성능 이점이 사라지는 문제가 있다.

#### EnumMap 사용

```java
System.out.println(Arrays.stream(garden)
                  .collect(Collectors.groupingBy(p -> p.lifeCycle,
                                                () -> new EnumMap<>(LifeCycle.class), Collectors.toSet())));
```

`Collectors.groupingBy`는 `mapFactory` 매개변수에 원하는 맵 구현체를 명시해 호출할 수 있다. 단순한 프로그램에서는 최적화가 꼭 필요하진 않지만, 맵을 빈번히 사용하는 프로그램에서는 반드시 필요하다.

`stream`을 사용하는건 `EnumMap`만 사용했을 때와는 다르게 동작한다.
`EnumMap`만 사용했을때는 항상 식물의 생애주기(LifeCycle) 당 중첩 맵을 한개씩 만들지만, 스트림을 사용한 버전에서는 해당 생애주기에 속하는 식물이 있을때만 만든다. 

```java
import lombok.RequiredArgsConstructor;

import java.util.EnumMap;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public enum Phase {
    SOLID, LIQUID, GAS;

    @RequiredArgsConstructor
    public enum Transition {
        MELT(SOLID, LIQUID),
        FREEZE(LIQUID, SOLID),
        BOIL(LIQUID, GAS),
        CONDENSE(GAS, LIQUID),
        SUBLIME(SOLID, GAS),
        DEPOSIT(GAS, SOLID),
        ;

        private final Phase from;
        private final Phase to;

        // 이전 상태에서 '이후 상태에서 전이로의 맵'에 대응하는 맵
        private static final Map<Phase, Map<Phase, Transition>> m
                = Stream.of(values()).collect(Collectors.groupingBy(t -> t.from, () -> new EnumMap<>(Phase.class), Collectors.toMap(t -> t.to, t -> t, (x, y) -> y, () -> new EnumMap<>(Phase.class))));

        public static Transition from(Phase from, Phase to) {
            return m.get(from).get(to);
        }
    }
}

```

다음은 `EnumMap` 을사용해 두 열거 타입의 값을 매핑한 예제이다. 
여기서 `groupingBy`로 전이를 이전 상태를 기준으로 묶고, `toMap`에서 이후 상태를 전이에 대응하는 `EnumMap`을 생성한다.
이렇게 `EnumMap`으로 구현하면, 새로운 상태값이 추가되었을때 다음과 같이 해당 상태 값들만 추가해주면 된다.

```java
public enum Phase {
    SOLID, LIQUID, GAS, PLASMA; // PLASMA 추가

    @RequiredArgsConstructor
    public enum Transition {
        MELT(SOLID, LIQUID),
        FREEZE(LIQUID, SOLID),
        BOIL(LIQUID, GAS),
        CONDENSE(GAS, LIQUID),
        SUBLIME(SOLID, GAS),
        DEPOSIT(GAS, SOLID),
        IONIZE(GAS, PLASMA), // 추가
        DEIONIZE(PLASMA, GAS) //추가
        ;

        private final Phase from;
        private final Phase to;

        // 이전 상태에서 '이후 상태에서 전이로의 맵'에 대응하는 맵
        private static final Map<Phase, Map<Phase, Transition>> m
                = Stream.of(values()).collect(Collectors.groupingBy(t -> t.from, () -> new EnumMap<>(Phase.class), Collectors.toMap(t -> t.to, t -> t, (x, y) -> y, () -> new EnumMap<>(Phase.class))));

        public static Transition from(Phase from, Phase to) {
            return m.get(from).get(to);
        }
    }
}


```

나머지는 기존 로직에서 처리해주므로 수정할 가능성이 적다. 또한, 실제 내부에서 맵이 배열들의 배열로 구현되므로 낭비되는 공간과 시간도 거의 없이 명확하고 안전하게 유지보수 할 수 있다.