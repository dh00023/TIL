# String , StringBuffer, StringBuilder

- java.lang

| 클래스                                                       | 용도                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| String                                                       | 문자열을 저장하고 여러 가지 정보를 얻을 때 사용              |
| StringBuffer, StringBuilder                                  | 문자열을 저장하고 내부 문자열을 조작할 때 사용               |



## String 클래스

자바의 문자열은 String 클래스의 인스턴스로 관린된다. String 클래스의 다양한 생성자를 이용해서 직접 String객체를 생성할 수 있다.

| 리턴 타입 | 메소드명(매개 변수)                                    | 설명                                                       |
| --------- | ------------------------------------------------------ | ---------------------------------------------------------- |
| char      | charAt(int index)                                      | 특정 위치의 문자 리턴                                      |
| boolean   | equals(Object anObject)                                | 두 문자열을 비교                                           |
| byte[]    | getBytes()                                             | byte[]로 리턴                                              |
| byte[]    | getBytes(charset charset)                              | 문자열 내에서 주어진 문자열의 위치를 리턴                  |
| int       | length()                                               | 총 문자수를 리턴                                           |
| String    | replace(CharSequence target, CharSequence replacement) | target부분을 replacement로 대체한 새로운 문자열 리턴       |
| String    | substring(int beginIndex)                              | beginIndex 위치에서 끝까지 잘라낸 새로운 문자열 리턴       |
| String    | substring(int beginIndex, int endIndex)                | beginIndex 위치에서 endIndex까지 잘라낸 새로운 문자열 리턴 |
| String    | toLowerCase()                                          | 알파벳 소문자로 변환한 새로운 문자열 리턴                  |
| String    | toUpperCase()                                          | 알파벳 대문자로 변환한 새로운 문자열 리턴                  |
| String    | trim()                                                 | 앞뒤 공백을 제거한 새로운 문자열 리턴                      |
| String    | valueOf(int i)<br>valueOf(double d)                    | 기본 타입 값을 문자열로 리턴                               |

### 사용 빈도가 높은 생성자

네트워크를 통해 받은 데이터는 보통 byte[] 배열이므로 이것을 문자열로 변환하기 위해 사용한다.

```java
//배열 전체를 String 객체로 생성
String str = new String(byte[] bytes);
//지정한 문자셋으로 디코딩
String str = new String(byte[] bytes, String charsetName);

//배열의 offset 인덱스 위치부터 length만큼 String 객체 생성
String str = new String(byte[] bytes,int offset, int length);
// 지정한 문자셋으로 디코딩
String str = new String(byte[] bytes, ,int offset, int length,String charsetName);
```

```java
public static void main(String[] args){
    byte[] bytes = {72, 101, 108, 111, 32, 74, 97, 118, 97};
    
    String str1 = new String(bytes);
    System.out.println(str1); //=> Hello Java
    String str2 = new String(bytes,6,4);
    System.out.println(str2); //=>Java
}
```

키보드로부터 입력받는 문자열에는 엔터키를 눌렀다면 `\r`, `\n`의 코드값이 바이트 배열에 저장된다. 영어는 1byte, 다른 나라 언어는 2byte로 표현되기 때문에 입력된 문자 수와 바이트 수가 다를 수 있다.

```java
public static void main(String[] args){
    byte[] bytes = new byte[100];
    
    System.out.println("입력 : ");
	int readByteNo = System.in.read(bytes);
    String str2 = new String(bytes,0,readByteNo-2);
    System.out.println(str2);
}
```


### 문자추출(charAt())

매개값으로 주어진 인덱스의 문자를 리턴한다.

```java
String sub = "자바 프로그래밍";
char charVal = sub.charAt(3);
//=>프
```

### 문자열 비교(equals())

```java
String val1 = new String("Java");
String val2 = "java";
va1.equals(val2);
//=>true
```

### 바이트 배열로 변환(getBytes())

네트워크로 문자열을 전송하거나, 문자열을 암호화할 때 문자열을 바이트 배열로 변환한다.

```java
byte[] bytes = "문자열".getBytes();
```

시스템의 기본 문자셋으로 인코딩된 바이트 배열을 리턴한다. 만약 특정 문자셋으로 인코딩된 바이트 배열을 얻으려면 다음 메소드를 사용하면된다.

```java
byte[] bytes = "문자열".getBytes(Charset charset);
byte[] bytes = "문자열".getBytes("UTF-8");
```

여기서 EUC-KR은 한글 2byte, UTF-8은 3byte로 변환한다.

시스템 기본 문자셋과 다른 문자셋으로 인코딩된 바이트 배열일 경우 다음 String 생성자를 이용해 디코딩 할 수 있다.

```java
String str = new String(byte[] bytes,String charsetName);
```

`getBytes(Charset charset)` 메소드는 잘못된 문자셋을 매개값으로 줄 경우 UnsupportedEncodingException예외가 발생하므로 예외처리가 필요하다.

```java
try{
	byte[] bytes = "문자열".getBytes("UTF-8");
}catch(UnsupportedEncodingException e){
    e.printStackTrace();
}
```

### 문자열 찾기(indexOf())

매개값으로 주어진 문자열이 시작되는 인덱스를 리턴한다. 만약 주어진 문자열이 포함되어 있지않으면 -1을 리턴한다.

```java
String sub = "java programming";
int index = sub.indexOf("programming");
//=>5
```

```java
if(문자열.indexOf("찾는 문자열")!=-1){
    //포함된 경우
}else{
    //포함되어있지않은 경우
}
```

### 문자열 길이(length())

문자열의 길이를 리턴한다.

```java
String sub = "java programming";
int length = sub.length();
//=>16
```

### 문자열 대치(replace())

첫 번째 매개값인 문자열을 찾아 두번째 매개값인 문자열로 대치한 새로운 문자열을 생성하고 리턴한다.

```java
String old = "ruby programming";
String new = old.replace("ruby","java");
//=>java programming
```

### 문자열 잘라내기(substring())

주어진 인덱스에서 문자열을 추출한다.

```java
String old = "java programming";
String first = old.substring(0,4);
//=>java
String seconde = old.substring(5);
```

인덱스 포함 범위는 startIndex<= new < endIndex이다.

### 알파벳 대소문자 변경(toLowerCase(),toUpperCase())

toLowerCase()는 모두 소문자로 변경, toUpperCase()는 모두 대문자로 변경해준다.

```java
String str = "Java Programming";
str.toLowercase();
//=>"java programming"
str.toUppercase();
//=>"JAVA PROGRAMMING"
```

이때 대소문자 관계없이 같은지 비교해주려면 equalsIgnoreCase() 메소드를 사용할 수 있다.

```java
str1.equalsIgnoreCase(str);
```

### 문자열 앞뒤 공백 잘라내기(trim())

문자열의 앞뒤 공백을 제거한 새로운 문자열을 생성하고 리턴한다.

```java
String str = "   	Java Programming		";
str.trim();
//=>"Java Programming"
```

trim을 사용한다고 해서 원래 문자열의 공백이 제거되는 것은 아니다.

### 문자열 변환(valueOf())

기본 타입의 값을 문자열로 변환하는 기능을 가지고 있다. 매개변수 타입 별로 오버로딩 되어있다.

```java
static String valueOf(boolean b)
static String valueOf(char c)
static String valueOf(int i)
static String valueOf(long l)
static String valueOf(double d)
static String valueOf(float f)
```


## StringBuffer, StringBuilder 클래스

문자열을 저장하는 String은 내부의 문자열을 수정할 수 없다.  예를 들어서 String의 replace() 메소드는 대치된 새로운 문자열을 리턴하는 것이지 내부 문자열을 대치하는 것이 아니다.

`+` 연산에도 마찬가지 이다.

```java
String str1 = "abc";
str1+="defg";
```

는 "abc"객체는 그대로 있고, "abcdefg"의 새로운 객체가 생성된 후 새로 생성된 객체를 참조하게 된다.

**문자열을 결합하는 `+` 연산자를 많이 사용하면 할수록 그만큼 String 객체의 수가 늘어나기 때문에 프로그램 성능을 느리게 하는 요인**이 된다.

문자열을 변경하는 작업이 많을 경우에는 String 클래스를 사용하는 것보다 `StringBuffer`, `StringBuilde` 클래스를 사용하는 것이 좋다. 이 두 클래스는 내부 Buffer(:데이터를 임시로 저장하는 메모리)에 문자열을 저장해두고, 그 안에서 추가, 수정, 삭제 작업을 할 수 있도록 설계되어 있다. 즉, **String처럼 새로운 객체를 만들지 않고도 문자열을 조작할 수 있는 것**이다.

두 클래스의 사용방법은 동일하나 차이점은 **StringBuffer는 멀티 스레드 환경에서 사용할 수 있도록 동기화가 적용되어 있어 멀티 스레드에 안전(thread-safe)**하지만, **StringBuilder 는 단일 스레드 환경에서만 사용하도록 설계**되어 있다.

### StringBuilder

```java
// 16개 문자들을 저장할 수 있는 초기버퍼
StringBuilder sb = new StringBuilder();
//주어진 개수만큼 문자들을 저장할 수 있는 초기 버퍼
StringBuilder sb = new StringBuilder(16);
// 주어진 str매개값을 버퍼의 초기값으로 저장
StringBuilder sb = new StringBuilder("Java");
```

버퍼가 부족할 경우 자동으로 버퍼 크기를 늘리기 때문에 초기 버퍼의 크기는 그다지 중요하지 않다.

| 메소드                                  | 설명                                              |
| --------------------------------------- | ------------------------------------------------- |
| append(...)                             | 문자열 끝에 주어진 매개값을 추가                  |
| insert(...)                             | 문자열 중간에 주어진 매개값 추가                  |
| delete(int start,int end)               | 문자열의 일부분 삭제                              |
| deleteCharAt(int index)                 | 문자열에서 주어진 index의 문자를 삭제             |
| replace(int start, int end, String str) | 문자열의 일부분을 다른 문자열로 대치              |
| StringBuilder reverse()                 | 문자열의 순서를 뒤바꿈                            |
| setCharAt(int index, char ch)           | 문자열에서 주어진 index의 문자를 다른 문자로 대치 |

append와 insert 메소드는 매개변수가 다양한 타입으로 오버로딩 되어 있으므로 대부분 값을 문자로 추가, 삽입할 수 있다.

```java
StringBuilder sb = new StringBuilder();

sb.append("JAVA ");
sb.append("Programming");
// 버퍼에 있는 것을 String타입으로 리턴
sb.toString();

sb.insert(4,"2");
//=>JAVA2 Programming

sb.setCharAt(4,'6');
//=>JAVA6 Programming

sb.replace(6,17,"Book");
//=>JAVA6 Book

sb.delete(4,5);
//=>JAVA Book
```

### StringBuffer

```java
StringBuffer stringBuffer = new StringBuffer();
StringBuilder stringBuilder = new StringBuilder();

new Thread(() -> {
    for(int i=0; i<10000; i++) {
        stringBuffer.append(i);
        stringBuilder.append(i);
    }
}).start();

new Thread(() -> {
    for(int i=0; i<10000; i++) {
        stringBuffer.append(i);
        stringBuilder.append(i);
    }
}).start();

new Thread(() -> {
    try {
        Thread.sleep(5000);

        System.out.println("StringBuffer.length: "+ stringBuffer.length());
        System.out.println("StringBuilder.length: "+ stringBuilder.length());
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
}).start();
```

```console
    StringBuffer.length: 77780
    StringBuilder.length: 76412
```

StringBuilder와 StringBuffer의 결과 값이 다른 것을 볼 수 있다. 이는 thread들이 동시에 StringBuilder 클래스에 접근할 수 있어 더 작은 수가 나온 것이다. String Buffer는 multi-thread 환경에서 다른 값을 변경하지 못하도록 동기화(Synchronization)되어있다. 

그러므로 **Web이나 Socket과 같이 비동기로 동작하는 경우가 많을때는 StringBuffer**를 사용하는 것이 안전하다.


## 참조 문서

- [https://novemberde.github.io/2017/04/15/String_0.html](https://novemberde.github.io/2017/04/15/String_0.html)