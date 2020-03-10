# 02. 변수와 타입

### 2.1 변수

```
변수(Variable)란, 하나의 값을 저장할 수 있는 메모리 공간
```

#### 작성규칙
1. **첫번째 글자는 문자, `$`, `_`이어야한다.(숫자로 시작할 수 없다.)**
2. **영어 대소문자가 구분된다.**
3. 첫 문자는 영어 소문자로 시작하되, 다른 단어가 붙을 경우 첫 문자를 대문자로 한다.
4. 문자 수(길이)의 제한은 없다.
5. **자바 예약어는 사용할 수 없다.**

```java
//타입 변수명
int age; // 초기화 되지 않음
age = 24;
double value = 40.8; // 초기화 됨
```
소스 코드 내에서 직접 입력된 값을 **리터럴(literal)**이라 부른다.
상수는 값을 한 번 저장하면 변경할 수 없는 변수로 정의한다.

```
변수는 선언된 블록 내에서만 사용가능하다.
```

### 2.2 데이터 타입(Type)

변수를 선언할 때 주어진 타입은 변수를 사용하는 도중에 변경할 수 없다.

|종류|기본타입|메모리크기|예|
|------|------|------|------|
|정수|byte|1byte||
||char|2byte|`char a = 'A';`|
||short|2byte||
||**int**|4byte|`int var1=10;`|
||long|8byte|`long var1=1000000000000L;`|
|실수|float|4byte|`float var1= 3.14F;`|
||**double**|8byte|`double var1= 3.14;`|
|논리|boolean|1byte|` boolean var1 = true;`|


```java
String memo = "Hello";
//String은 기본 타입이 아니다. 클래스 타입이며, 참조 변수이다.
```

#### 타입 변환

- 자동 타입 변환(promotion) : 프로그램 실행 도중에 자동적으로 타입 변환이 일어나는 것을 말한다. 작은 크기 타입이 큰 크기를 가지는 타입에 저장될 때 발생

```java
byte byteValue = 10;
int intValute = byteValue; //자동 타입 변환 발생

// 음수 값을 가질 수 있는 byte type은 음수 값을 가지지 않는 char type에 저장될 수 없다.
byte byteValue = 65;
char charValue = byteValue;(x) // 컴파일 에러
```

- 강제 타입 변환(Casting) : 큰 데이터 타입을 작은 데이터 타입으로 쪼개어서 저장하는 것

```java
int intValue = 103029770;
byte byteValue = (byte)intValue; // Casting
```
`.MAX_VALUE`와 `.MIN_VALUE`로 각 타입의 최대, 최소값과 비교해 값의 손실이 발생하지 않도록 해야한다.