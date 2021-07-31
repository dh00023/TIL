# ITEM 63: 문자열 연결은 느리니 주의해라

**문자열 연결 연산자로 문자열 n개를 잇는 시간은 n^2에 비례**한다.
문자열은 불변이며, 두 문자열을 연결할 경우 양쪽의 내용을 모두 복사해야하므로 성능 저하는 피할 수 없다.

```java
public String statement() {
  String result = "";
  for (int i = 0; i < numItems(); i++){
    result += lineForItem(i);
  }
  return result;
}
```

위와 같이 구현할 경우 대상이 많아질수록 더 느려질 수 있다.
`String` 대신 `StringBuilder` 를 사용하면 성능 저하를 피할 수 있다.

```java
public String statement() {
  StringBuilder sb = new StringBuilder(numItems() * LINE_WIDTH);
  for (int i = 0; i < numItems(); i++){
    b.append(lineForItem(i));
  }
  return b.toString();
}
```

즉, 많은 문자열을 연결할 떄는 문자열 연결 연산자 `+` 대신 `StringBuilder` 를 사용해야 한다.