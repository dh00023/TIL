# ITEM 11: ALWAYS OVERRIDE HASHCODE WHEN YOU OVERRIDE EQUALS

**equals를 재정의한 클래스는 hashCode도 재정의해야 한다.** 만약 hashCode를 재정의하지 않는다면, 일반 규약을 어기게 되어 HashSet이나 HashMap과 같은 컬렉션의 원소로 사용시 문제를 일으킬 수 있다.

- equals 비교에 사용되는 정보가 변경되지 않았다면, 애플리케이션이 실행되는 동안 그 객체의 hashCode 메서드는 몇번을 호출해도 일관되게 항상 같은 값을 반환해야한다.
- **`equals(Object)`가 두 객체를 같다고 판단했다면, 두 객체의 hashCode는 똑같은 값을 반환**해야한다.
- `equals(Object)`가 두 객체를 다르다고 판단했더라도, 두 객체의 hashCode가 서로 다른 값을 반환할 필요는 없으며, 하지만 **다른 객체에 대해서는 다른 값을 반환해야 해시테이블의 성능이 좋아진다**. 만약 모든 객체의 hashCode가 동일한 값을 반환한다면, 평균 수행시간이 O(1)에서 O(n)으로 느려져, 객체가 많아지면 쓸 수 없게 된다.

**논리적으로 같은 객체는 같은 해쉬코드를 반환**해야하며, hashCode 재정의를 잘못했을 때 가장 크게 문제가 되는 부분이다.

```java
public final class PhoneNumber {
    private final short areaCode, prefix, lineNum;

    public PhoneNumber(short areaCode, short prefix, short lineNum){
        this.areaCode = rangeCheck(areaCode, 999, "지역코드");
        this.prefix = rangeCheck(prefix, 999,"프리픽스");
        this.lineNum = rangeCheck(lineNum, 9999, "가입자번호");
    }
    private static short rangeCheck(int val, int max, String arg){
        if(val < 0 || val > max){
            throw new IllegalArgumentException(arg+" : "+val);
        }
        return  (short) val;
    }

    @Override
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(!(o instanceof PhoneNumber)){
            return false;
        }

        PhoneNumber pn = (PhoneNumber) o;
        return pn.lineNum == lineNum && pn.prefix == prefix && pn.areaCode == areaCode;
    }

}
```

```java
Map<PhoneNumber, String> map = new HashMap<>();
map.put(new PhoneNumber((short) 707,(short) 867,(short) 5309), "제니");
System.out.println(map.get(new PhoneNumber((short) 707,(short) 867,(short) 5309))); // null
```

여기서 `PhoneNumber` 클래스는 hashCode를 재정의하지 않아, 논리적 동치인 두 객체가 서로 다른 해시코드를 반환하여 두 번째 규약을 지키지 못하게된다. 

```java

    @Override
    public int hashCode(){
        // int 변수 result 초기화 후 해당 필드의 해시코드 계산
        // 기본타입 필드라면 Type.hashCode() 여기서는 Short.hashCode();
        int result = Short.hashCode(areaCode);
        // 앞에서 계산한 해시코드로 result 갱신
        // 여기서 31은 홀수이면서 소수이기 때문에 사용
        // 짝수는 2를 곱하면 시프트 연산과 같은 결과를 발생시켜 오버플로가 발생하면 정보를 잃게 됨.
        result = 31 * result + Short.hashCode(prefix);
        result = 31 * result + Short.hashCode(lineNum);
        // result 반환
        return result;
    }
```

위의 hashCode는 좋은 hashCode를 작성하는 가장 간단한 요령이다. 여기서는 기본 타입 필드이기 때문에 `Type.hashCode(f)`를 수행했지만, 만약 참조 타입 필드이면서, 이 클래서의 equals 메서드가 해당필드의 equals를 재귀적으로 호출해 비교한다면, 해당 필드의 hashCode를 재귀적으로 호출하면된다. 만약 필드의 값이 null인 경우 0을 사용하면 된다.

필드가 배열이라면, 핵심 원소 각각을 별도의 필드처럼 다루고, 배열에 핵심 원소가 없다면 단순히 상수(0)를 사용한다. 만약 모든 원소가 핵심 원소라면 `Arrays.hashCode`를 사용하면 된다.

```java
Map<PhoneNumber, String> map = new HashMap<>();
map.put(new PhoneNumber((short) 707,(short) 867,(short) 5309), "제니");
System.out.println(map.get(new PhoneNumber((short) 707,(short) 867,(short) 5309))); // "제니"
```

위와 같이 hashCode를 작성후 테스트 코드를 수행하면 동치인 인스턴스에 대해 똑같은 해시코드를 반환하는 것을 볼 수 있다. 파생필드(다른 필드로부터 계산해 낼 수 있는 필드)는 모두 무시해도 되며, **equals 비교에 사용되지 않은 필드는 반드시 제외**해야 한다.

만약 해시 충돌이 더욱 적은 방법을 꼭 써야한다면, [구아바의 `com.google.common.hash.Hashing`](https://guava.dev/releases/21.0/api/docs/com/google/common/hash/Hashing.html)을 참고하는 것이 좋다.

클래스가 불변이고 해시코드를 계산하는 비용이 크다면, 매번 새로 계산하기 보다는 캐싱하는 방식을 고려하는 것이 좋다. 

```java
private int hashCode;

@Override
public int hashCode() {
    int result = hashCode;

    if(result == 0) {
        result = Short.hashCode(areaCode);
        result = 31 * result + Short.hashCode(prefix);
        result = 31 * result + Short.hashCode(lineNum);
        hashCode = result;
    }
    return result;
}
```

해시의 키로 사용되지 않는 경우라면 다음과 같이 hashCode가 처음 호출될때 계산하는 지연 초기화 전략도 있다. 이때 스레드 안정성까지 고려해야하며, 성능을 높이고자 해시코드 계산시 핵심 필드를 생략해서는 안된다. 

**hashCode가 반환하는 값의 생성 규칙을 API 사용자에게 자세히 공표하지 않아야 클라이언트가 이 값에 의지하지 않게되고, 추후에 계산 방식을 바꿀 수 있다.**

