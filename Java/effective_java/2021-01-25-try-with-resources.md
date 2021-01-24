# ITEM 9: PREFER TRY-WITH-RESOURCES TO TRY-FINALLY

자바 라이브러리에는 `close` 메서드를 호출해 직접 닫아줘야하는 자원들이 많다.(`InputStream`, `OutputStream`, `java.sql.Connection` 등) 자원 닫기는 클라이언트가 놓치기 쉬워 예측할 수 없는 성능 문제로도 이어진다. 이러한 경우 상당수가 안전망으로 `finalizer`를 활용하고 있지만, `finalizer`는 믿을만 하지 못하다.([item 8](2021-01-25-avoid-finalizer-and-cleaner.md))

전통적으로 자원이 제대로 닫힘을 보장하는 수단으로 `try-finally` 가 사용되었다. 

```java
		static String firstLineOfFile(String path) throws IOException{
      	BufferedReader br = new BufferedReader(new FileReader(path));
        try{
          	return br.readLine();
        }finally {
            br.close();
        }
    }
```

기기에 물리적인 문제가 생겨 `firstLineOfFile` 메서드 안의 `readLine` 메서드가 문제가 생긴다면 `readLine()` 메서드가 예외를 던지고, 같은 이유로 `close` 메서드도 실패할 것이다. 이러한 상황에서 두번째 예외가 첫번째 예외를 삼켜, 스택 추적 내역에 첫번째 예외에 대한 정보는 남지 않게 된다. 두 번째 예외 대신 첫 번째 예외를 남길 수는 있지만, 코드가 너무 지저분해져서 실제로 그렇게 하는 경우는 거의 없다.

이러한 문제들은 java 7의 `try-with-resources` 덕에 모두 해결되었다. `try-with-resources` 구조를 사용하려면 해당 자원이 `AutoCloseable` 인터페이스를 구현해야하는데, 수 많은 인터페이스가 이미 `AutoCloseable`을 구현하거나 확장해두었다.

```java
		static String firstLineOfFile(String path) throws IOException{
      	// try - with - resources
      	try(BufferedReader br = new BufferedReader(new FileReader(path)){
          	return br.readLine();
        }
    }
```

`readLine()`과 `close()` 호출 양쪽에서 예외가 발생하면, `close`에서 발생한 예외는 숨겨지고, `readLine`에서 발생한 예외만 기록이 된다. 또한, 숨겾니 예외들도 스택추적 내역에 **suppressed**라는 꼬리표를 달고 출력되며, `Throwable`에 추가된 `getSuppressed` 메서드를 이용해 프로그램 코드에서도 가져올 수 있다.

```java
		static void copy(String src, String dst) throws IOException{
      	try(InputStream in = new FileInputStream(src);
            OutputStream out = new FileOutputStream(dst))
      	{
        		byte[] buf = new byte[BUFFER_SIZE];
            int n;
            while((n = in.read(buf))>= 0)
            		out.write(buf, 0, n);
        }
    }
```



## try - with -resources

```java
try (SomeResource resource = getResource()) {
    use(resource);
} catch(...) {
    ...
}
```

try에 자원 객체를 전달하면, **try 코드 블록이 끝나면 자동으로 자원을 종료해주는 기능**으로 따로 `finally` 블록이나 모든 `catch` 블록에 종료 처리를 해주지 않아도 된다.

하지만, 이 구조를 사용하려면 해당 자원이 `AutoCloseable` 인터페이스를 구현해야한다.

```java
public interface AutoCloseable {

    void close() throws Exception;
}

```

또한, try안에 복수의 자원 객체를 전달할 수도 있다.

```java
try(Something1 s1 = new Something1();
    Something2 s2 = new Something2()) {

} catch(...) {
    ...
}
```

```java
static void copy(String src, String dst) throws IOException{
		try(InputStream in = new FileInputStream(src);
    		OutputStream out = new FileOutputStream(dst))
    {
    		byte[] buf = new byte[BUFFER_SIZE];
        int n;
        while((n = in.read(buf))>= 0)
        		out.write(buf, 0, n);
    }
}
```



즉, 꼭 회수해야 하는 자원을 다룰 때는 `try-finally`말고 `try-with-resources`를 사용해라. **코드는 더 짧고 분명해지며, 만들어지는 예외정보도 훨씬 유용**하다. 정확하고 쉽게 자원을 회수할 수 있다.



## 참고

- [https://ryan-han.com/post/java/try_with_resources/](https://ryan-han.com/post/java/try_with_resources/)