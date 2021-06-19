# ITEM 45: 스트림은 주의해서 사용해라

- 스트림 : **데이터 원소의 유한/무한 시퀀스**를  뜻함
- 스트림 파이프라인 : **원소들로 수행하는 연산 단계**를 표현

스트림의 원소는 어디로 부터든 올 수 있으며, 대표적으로 배열, 컬렉션, 파일 등을 통해서 만들 수 있다.

## 스트림 파이프라인

스트림을 생성하는 연산을 시작으로, 최종 처리(종단 연산)을 통해 끝나며, 그 사이에는 스트림을 변환하거나 계산하는 한개 이상의 중간 연산이 포함될 수 있다.

- 중간 연산
    - 중간 연산들은 모두 한 스트림을 다른 스트림으로 변환
    - 변환된 스트림의 원소 타입은 변환전과 같을 수도 다를 수 도 있다.
- 최종 연산 
    - 마지막 중간 연산의 스트림에 최후 연산
    - 정렬, 특정 원소 선택, 집계, 모든 원소 출력

### 지연 평가(lazy evaluation)

평가는 종단 연산이 호출될 때 진행되며, 종단 연산에 사용되지 않은 데이터 원소는 계산에 쓰이지 않는다. 이러한 지연 평가가 무한 스트림을 다룰 수 있게 해주는 핵심인 것이다.
종단 연산이 없는 스트림 파이프라인은 아무 일도 하지 않는 명령어인 `no-op`과 같으므로, 종단 연산을 빼먹는 일이 없도록 주의해야한다.

### 특징

-  파이프라인 여러개를 연결해 표현식 하나로 구현 가능
- 기본적으로 순차적으로 수행
    - 병렬로 수행하고 싶은 경우 `paralle` 메서드를 호출하면 되나, 효과를 볼 수 있는 상황은 많지 않음([ITEM 48]())
- 사실상 어떠한 계산이라도 할 수 있음

### 가독성

스트림을 제대로 사용하면 프로그램이 짧고 깔끔해지지만, 잘못 사용하면 읽기 어렵고 유지보수도 힘들어진다.

- 스트림을 과하게 사용하는 예

  ```java
  public class Anagrams {
      public static void main(String[] args) throws IOException {
          Path dictionary = Paths.get(args[0]);
          int minGroupSize = Integer.parseInt(args[1]);
  
          try (Stream<String> words = Files.lines(dictionary)) {
              words.collect(groupingBy(word -> word.chars().sorted()
                      .collect(StringBuilder::new,
                          (sb, c) -> sb.append((char) c),
                          StringBuilder::append).toString()))
                  .values().stream()
                  .filter(group -> group.size() >= minGroupSize)
                  .map(group -> group.size() + ": " + group)
                  .forEach(System.out::println);
          }
      }
  }
  ```

사전 파일을 여는 부분만 제외하면, 프로그램 전체가 단 하나의 표현식으로 처리된다. 이 코드는 짧지만 읽기 어렵다. 이처럼 스트림을 과용하면 프로그램이 읽거나 유지보수하기 어려워진다.

- 스트림을 적절히 활용한 예

  ```java
  public class Anagrams {
      public static void main(String[] args) {
          Path dictionary = Paths.get(args[0]);
          int minGroupSize = Integer.parseInt(args[1]);
  
          try (Stream<String> words = Files.lines(dictionary)) {
              words.collect(groupingBy(word -> alphabetize(word)))
                  .values().stream()
                  .filter(group -> group.size() >= minGroupSize)
                  .forEach(g -> System.out.println(g.size() + ": " + g));
          }
      }
  
      private static String alphabetize(String s) {
          char[] a = s.toCharArray();
          Arrays.sort(a);
          return new String(a);
      }
  }
  ```

모든 반복문과 같은 로직을 스트림으로 변경하는 것보다 적절히 분리하는 것이 좋다. 특정 로직은 도우미 메서드로 적절하게 분리하는 것이 도움이된다.

람다를 구현할때, 매개변수 이름은 주의해서 정해야한다. 람다에서는 타입 이름을 자주 생략하므로, 매개변수 이름을 잘 지어야 스트림 파이프라인의 가독성이 유지되기 때문이다.

여기서 `alphabetize` 메서드도 스트림을 사용해 다르게 구현할 수 있다. 하지만 자바가 `char` 용 스트림을 제공하지 않아 명확성이 떨어지고 잘못 구현할 확률이 높다.

```java
"Hello world!".chars().forEach(System.out::print);
// 721011081081113211911111410810033
```

`chars()`는  `int` 값을 반환해주며 이름은 `chars`이지만 `int` 스트림을반환해주기때문에 헷갈릴 수 있다.
`(char) x)`와 같이 형변환을 명시적으로 해줘서 원하는 값을 얻을 수는 있지만, `char` 값들을 처리할 때는 스트림을 삼가하는 편이 좋다.

### 코드 블록 vs 람다 블록

#### 코드블록

- 범위 안의 지역변수를 읽고 수정할 수 있음.
- `return` 문을 사용해 메서드를 빠져나가거나, `break`, `continue` 문으로 블록 바깥의 반복문을 종료하거나 반복을 한 번 건너 뛸 수 있음.
- 메서드 선언엔 명시된 검사 예외를 던질 수 있음.

#### 람다블록

- `final` 이거나 사실상 `final`인 변수만 읽을 수 있으며, 지역변수를 수정하는건 불가능
- `return`, `break`, `continue` 문 사용 불가능
- 명시된 검사 예외 던지는것 불가능

코드블록에서만 수행가능한걸 수행해야하는 경우에 스트림과는 맞지 않다.

### 스트림을 사용하기 좋은 경우

- 원소들의 시퀀스를 일관되게 변환
- 원소들의 시퀀스를 필터링
- 원소들의 시퀀스를 하나의 연산을 사용하여 결합(더하기, 최솟값 구하기 등)
- 원소들의 시퀀스를 컬렉션에 모으는 경우
- 원소들의 시퀀스에서 특정 조건을 만족하는 원소를 찾는 경우

위 5가지 케이스 중 하나를 수행하는 로직이라면 스트림을 적용하기 좋은 경우이다.

### 스트림으로 처리하기 어려운 일

- 한 데이터가 파이프라인의 여러 단계를 통과할 때, 각 단계에서 값들에 동시에 접근하기 어려운 경우
    - 스트림은 한 값을 다른 값에 매핑하고 나면 원래의 값은 잃는 구조
- 매핑 객체가 필요한 단계가 여러 곳인 경우



## 결론

스트림으로 바꾸는게 가능하더라도 코드 가독성과 유지보수 측면에서 손해볼 수 있기때문에 기존 코드는 스트림을 사용하도록 리팩터링하되, 새 코드가 더 나아 보일때만 반영해야한다.

즉, **스트림과 반복 중 어느쪽이 나은지 확신하기 어렵다면, 둘다 구현해보고 더 나은 쪽을 정하는 것**을 권장한다.

