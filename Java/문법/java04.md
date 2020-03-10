# 04. 조건문과 반복문

### 조건문(if문, switch문)

#### if문
```java
if(조건식1){
	실행문1;	//조건식1 true
}else if(조건식2){
	실행문2;	//조건문2 true
}else{
	실행문3;	//조건식1 and 조건식2 false
}
```

```java
//0.0과 1.0사이의 난수 값을 출력하는 메소드
Math.random();
```

#### switch문

```java
switch(변수){
	case 값1:

    	break;

	case 값2:

    	break;

	default:

}
```

java 7부터는 String 타입의 변수도 올 수 있다. 7이전 버전은 정수타입 변수나 정수값을 산출하는 연산식만 올 수 있다.

### 반복문(for, while, do-while)

for문은 반복 횟수를 알고 있을 때 주로 사용하고, while문은 조건에 따라 반복할 때 주로 사용한다.

#### for문

```java
int sum = 0;
for(초기화식; 조건식; 증감식){
	실행문;
}
```
```java
for(int i=1; i<=10; i++){
	System.out.println(i);
}
```
초기화식은 생략을 할 수도 있고, 둘 이상이 있을 수 있다.
```java
int i = 1;
for(; i<=100; i++){...}

for(int i=0, j=100; i<=50 && j>=50; i++,j--){...}
```

#### while문
while문은 조건식이 true일 경우에 계속해서 반복한다.
```java
while(조건식){
	실행문;
}
```
```java
while(i<=10){
	System.out.println(i);
	i++;
}
```

#### 키보드로부터 입력받기

```java
int keyCode = System.in.read();
```

![](http://fingswotidun.com/code/images/a/ab/Key_mouse_codes.png)

이때, `System.in.read()`메소드는 하나의 키 코드만 읽기 때문에 콘솔에 입력된 문자열을 한 번에 읽을 수 없다. 대신 `Scanner`객체를 생성한 후 `nextLine()`메소드를 호출하면 콘솔에 입력된 문자열을 한 번에 읽을 수 있다.
```java
Scanner scanner = new Scanner(System.in);
String inputString = scanner.nextLine();
```

#### do-while문

while문과의 차이점은 while문은 조건을 먼저 검사한 후 실행하고, do-while문은 실행문을 실행한 후에 조건을 검사한다.

```java
do{
	실행문;
}while(조건식);
```

#### break문
break문은 반목문인 for, while, do-whlie문을 실행 중지할 때 사용된다.(+switch문)

```java
while(true){
	int num = (int)(Math.randon*6)+1;
	System.out.println(num);
	if(num == 6){
		break;
	}
}
```

이때, break문은 가장 가까운 반복문만 종료한다.
만약 반복문이 중첩되어 있을 경우 Lavel을 붙이고 `break Lavel이름;`을 하면 라벨이 붙은 반복문까지 종료된다.

```java
Outter: for(int i=0;i<=10;i++){
	for(int j=1; j<=10;j++){
		if(i==8 && j==8){
			break Outter;
		}
	}
}
```

#### continue문

continue문은 반복문에서만 사용되는데, 블록 내부에서 continue문이 실행되면 for문의 증감식 또는 while, do-while문의 조건식으로 이동한다.
```java
for(int i=1; i<=10; i++){
	if(i%2 != 0){
		continue;
	}
}
```
