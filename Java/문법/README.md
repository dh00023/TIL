# Java

- 컴퓨터 응용프로그래밍 : 최윤정 교수님
- '이것이 자바다'
- 각종 블로그
을 참조해 공부한 내용을 정리한 것입니다.

## 자바에 대해서

### 특징
1. 이식성이 높은 언어
2. 객체 지향 언어
3. 함수적 스타일 코딩 지원( 대용량 데이터의 병렬 처리, 이벤트 지향 프로그래밍에 적합)
4. 메모리를 자동으로 관리
5. 다양한 애플리케이션 개발 가능
6. 멀트 스레드를 쉽게 구현
7. 동적 로딩(Dynamic Loading) 지원 : 객체가 필요한 시점에 클래스를 동적 로딩해서 객체를 생성
8. 막강한 오픈소스 라이브러리

### JVM(자바 가상 기계)
JVM은 실 운영체제를 대신해서 자바 프로그램을 실행하는 가상의 운영체제 역할을 한다. 운영체제와 자바 프로그램을 중계하는 JVM을 두어 자바 프로그램이 여러 운영체제에서 동일한 결과가 나오도록 설계한 것이다.
즉, 개발자는 운영체제와 상관없이 자바 프로그램을 개발할 수 있다.

![](https://qph.ec.quoracdn.net/main-qimg-8a01da5bb92284a0ceae50d61096f761-c)

java는 JVM에 의해 기계어로 번역되고 실행되기 때문에, C, C++의 컴파일 단계에서 만들어지는 완전한 기계어보다는 속도가 느리다는 단점을 가지고 있다.(격차는 점점 줄어들고 있음.)

### 개발환경
- JRE(Java Runtime Environment) = JVM + 표준 클래스 라이브러리
- JDE(Java Development Kit) = JRE + 개발에 필요한 도구

### [API 바로가기](https://docs.oracle.com/javase/8/docs/api/)

### 자바 프로그램 개발 순서
`.java `소스 파일 작성 → 컴파일러(`javac.exe`)로 바이트 코드 파일(`.class`)생성 → JVM 구동 명령어(`java.exe`)로 실행

### 프로그램 소스 분석

- 클래스 : 필드 또는 메소드를 포함하는 블록
- 메소드 : 어떤 일을 처리하는 실행문들을 모아 놓은 블록

```java
public class Hello{
	public static void main(String[] args){
    	System.out.println("Hello World!");
    }
}
```

### 주석과 실행문
```java
// 행주석
/*
범위 주석
여러줄 주석
*/
```

### 키보드 입력받기

```java
int keyCode = System.in.read();
```

![](http://fingswotidun.com/code/images/a/ab/Key_mouse_codes.png)

이때, `System.in.read()`메소드는 하나의 키 코드만 읽기 때문에 콘솔에 입력된 문자열을 한 번에 읽을 수 없다. 대신 `Scanner`객체를 생성한 후 `nextLine()`메소드를 호출하면 콘솔에 입력된 문자열을 한 번에 읽을 수 있다.

```java
Scanner scanner = new Scanner(System.in);
String inputString = scanner.nextLine();
```
