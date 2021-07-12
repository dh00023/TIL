# ITEM 53: 가변인수는 신중히 사용해라

가변인수(varargs) 메서드는 **명시한 타입의 인수를 0개 이상** 받을 수 있다.
가변인수 메서드 호출시, 가장 먼저 인수의 개수와 길이가 같은 배열을 만들고, 인수들을 배열에 저장해 가변인수 메서드에 넘겨준다.

- 가변인수 메서드 예 : int인수들의 합 계산

  ```java
  static int sum(int... args){
    int sum = 0;
    for (int arg : args){
      sum += arg;
    }
    return sum;
  }
  ```

이때, 인수가 1개 이상이어야 하는 경우가 있다. **가변 인수 개수는 런타임에 생성된 배열의 길이**로 알 수 있다.

- 인수가 1개 이상이여야하는 가변인수 메서드 - 잘못 구현한 예

  ```java
  static int min(int... args){
    if (args.length == 0)
      throw new IllegalArgumentException("인수가 1개 이상 필요");
    int min = args[0];
    for (int i = 1; i < args.length; i++){
      if (args[i] < min){
        min = args[i];
      }
    }
    return min;
  }
  ```

위 예제에서는 문제점이 몇가지 있다.

1. 인수를 0개만 넣어 호출한 경우 컴파일 타임이 아닌 런타임에 실패
2. 코드가 지저분함

- 인수가 1개 이상이여야하는 가변인수 메서드 - 제대로 구현

  ```java
  static int min(int firstArg, int... remainArgs)
    int min = firstArg;
  	for(int arg : remainArgs){
      if (arg < min) min = arg;
    }
  	return min;
  }
  ```
  
  다음과 같이 첫 번쨰는 평범한 매개변수를 받고, 가변인수는 두번째로 받아 앞선 문제를 해결할 수 있다.

**가변인수는 인수 개수가 정해지지 않았을 때 아주 유용**하다.

하지만, **가변인수 메서드는 호출될 때마다 배열을 새로 하나 할당하고 초기화 하므로, 성능에 민감한 상황에서는 걸림돌**이 될 수 있다.
비용을 감당할 수 없지만, 가변인수의 유연성이 필요한 경우 다중정의를 통해 해결할 수 있다.

```java
public void foo() { }
public void foo(int a1) { }
public void foo(int a1, int a2) { }
public void foo(int a1, int a2, int a3) { }
public void foo(int a1, int a2, int a3, int... rest) { }
```

만약, 95%가 인수 3개 이하로 사용한다면, 다음과 같이 다중정의를 통해 5%만 배열을 생성하도록 할 수 있다.
`EnumSet`의 정적 팩터리도 위 기법을 사용해 열거 타입의 집합 생성 비용을 최적화하고 있다.
