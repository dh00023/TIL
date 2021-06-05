# ITEM 35: ordinal 메서드 대신 인스턴스 필드를 사용해라

대부분의 열거 타입 상수는 하나의 정숫값에 대응된다. 그리고 모든 열거 타입은 해당 상수가 그 열거 타입에서 몇 번째 위치인지를 반환하는 `ordinal` 메서드를 제공한다.

```java
public enum Esemble {
    SOLO, DUET, TRIO, QUARTET, QUINTET, SEXTET, SEPTET, OCTET, NONET, DECTET;

    // ordinal을 잘못 사용한 경우
    public int numberOfMusicians() {
        return ordinal() + 1;
    }
}
```

위 코드는 `ordinal()`를 잘못 사용한 경우이다. 상수 선언 순서를 바꾸는 순간 `numberOfMusicians`는 오동작하며, 이미 사용중인 정수와 값이 같은 상수는 추가할 방법이 없다. 예를 들어 8중주(`OCTET`) 상수가 이미 있으므로, 똑같이 8명이서 연주하는 복4중주는 추가할 수 없다.
또한, 값을 중간에 비워둘 수도 없다. 예를들어 12명이 연주하는 3중 4중주를 추가하고 싶으면, 중간에 11명짜리 상수도 더미값으로 같이 추가해야만 한다. 코드가 깔끔하지 않을 뿐더러, 실용성이 떨어진다.

**열거 타입 상수에 연결된 값은 ordinal 메서드로 얻지말고 인스턴스 필드에 저장**하여, 해결할 수 있다.

```java
public enum Esemble {
    SOLO(1), DUET(2), TRIO(3), QUARTET(4), QUINTET(5), SEXTET(6), SEPTET(7), OCTET(8), DOUBLE_QUARTET(8), NONET(9), DECTET(10), TRIPLE_QUARTET(12);

    private final int numberOfMusicians;

    Esemble(int size) {
        this.numberOfMusicians = size;
    }

    public int numberOfMusicians() {
        return numberOfMusicians;
    }
}
```

`Enum` API문서를 보면

![image-20210605234412577](./assets/image-20210605234412577.png)

"대부분 프로그래머는 이 메서드를 사용할 일이 없다. 이 메서드는 `EnumSet`과 `EnumMap` 같이 열거 타입기반의 범용 자료구조에 쓸 목적으로 설계되었다." 라고 쓰여 있다. 

즉, 이러한 용도가 아니라면, `ordinal` 메서드는 절대로 사용하지 말아야한다.