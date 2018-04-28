# 04. 객체

## 04-1 객체

자바스크립트는 객체(Object)기반 언어이다. 객체를 구성하는 요소로는 Property(속성)과 Method(기능)이 있다.
```
#예시

객체(TV)

메서드 : 켜다, 끄다, 볼륨높이다, 볼륨줄이다
속성 : 너비, 높이, 색상, 무게
```

```js
Object.Method();
Object.property; or Object.property=value;
```

### 객체의 종류

1. 내장 객체
 자바스크립트 엔진에 내장되어있다. `String`,`Date`,`Array`,`Math` 객체 등이 있다.

2. BOM(브라우저 객체 모델)
 브라우저에 내장되어 있는 객체들이다. `window`,`screen`,`location`,`history`,`navigator` 등이 있다. 브라우저(window)는 document와 location객체의 상위 객체이다.

```js
window.location.href="사이트 URL"->location.herf="사이트 URL"
```

3. DOM(문서 객체 모델)

DOM은 HTML 문서 구조를 말한다.

## 04-2 내장 객체

### 내장 객체 생성하기

```js
참조변수(instance name)=new 생성 함수()
```
```js
var tv=new Object();
```

### 날짜 정보 객체
```js
//현재 날짜 정보
참조 변수 = new Date();
var t = new Date();
```
```js
//특정 날짜 정보
var d=new Date("2002/5/31");
var d=new Date(2002/4/31); //new Date(연, 월-1,일)
```

- [날짜 관련 메서드](https://www.w3schools.com/js/js_date_methods.asp)

### 숫자 객체
표현 가능한 수의 속성과 숫자 표기법에 대한 메서드를 제공한다.
```js
var 참조변수 = new Number(값); or var 참조변수=값;
```

- [Number 속성](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Number)
- [Number method](https://www.w3schools.com/js/js_number_methods.asp)

일부는 `new`키워드와 생성함수를 사용하지 않고 값만으로 객체를 생성하는 객체들이 있다.
즉, 날짜 객체를 제외한 모든 객체는 변수에 값만 참조해도 객체자 생성된다.

### 수학 객체

- [수학 객체 method](https://www.w3schools.com/js/js_math.asp)

#### 난수 생성하기
```js
//난수 발생시켜 원하는 구간 정수의 값 구하기
Math.floor(Math.random()*(최댓값-최소값+1)+최소값;)
```

### 배열 객체
여러 개의 데이터를 하나의 저장소에 저장할 때 사용한다.
```js
var d=new Array();
d[0]=30;
d[1]="정다혜";
d[2]=false;

var d2=new Array(30,"정다혜",true);

var ddd=[30,"정다혜",false];
```
각각의 배열에는 인덱스(index)번호가 부여된다. 이때 인덱스는 0부터 시작한다.

```js
d[0];
```
참조변수[인덱스번호]로 저장된 데이터를 불러올 수 있다.

- [Array method & property](https://www.w3schools.com/jsref/jsref_obj_array.asp)

### 문자 객체

자바스크립트에서 가장 많이 사용한다.
```js
var t= new String("Likelion");
var t="Likelion";
```

- [String method $ property](https://www.w3schools.com/jsref/jsref_obj_string.asp)

### 정규 표현 객체
입력 요소에 데이터를 규칙에 맞게 작성했는지 판단해서 알려주는 객체이다.

```js
var 참조변수 = new RegExp(패턴,검색 옵션)
var 참조변수 = /패턴/검색 옵션
```
검색 옵션은 일치하는 단어를 찾을 때, 다양한 조건과 규칙을 붙여 검색할 수 있다.

- [정규식 참조](https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/%EC%A0%95%EA%B7%9C%EC%8B%9D)
- [정규식 참조-W3School](https://www.w3schools.com/jsref/jsref_obj_regexp.asp)
- [정규 표현 객체 생성 사이트](http://www.regexr.com/v1/)

## 04-3 브라우저 객체 모델(BOM)

`window`는 브라우저 객체의 최상위 객체이다. `window`객체는 하위 객체를 포함하고 있다.
즉, 계층적 구조로 이루어져 있다. 이를 **BOM**(Browser Object Model)이라한다.

![](https://www.javatpoint.com/images/javascript/bom.jpg)

### window 객체

- [w3schools window](https://www.w3schools.com/jsref/obj_window.asp)

#### open()
새 브라우저 창을 띄울 때 사용한다.
```js
window.open("url","name","option")
```
```js
window.open("http://konkuk.likelion.org/","pop1","width=400,height=500,left=50,top=10,scrollbars=no,toolbars=no,location=no");
```

- [open 메서드 속성](https://www.w3schools.com/jsref/met_win_open.asp)

#### alert()
경고 창을 띄운다.
```js
alert("messages");
```

#### prompt()
질의응답 창을 띄울 때 사용한다.
```js
prompt("question","기본답변");
```

#### confirm()
확인/취소 창을 띄울 때 사용한다.
```js
confirm("내용");
```
확인버튼을 누르면 true, 취소 버튼 누르면 false를 반환한다.

#### moveTo()
브라우저 창의 위치를 이동시킬 때 사용한다.(크롬, 오페라 예외)
```js
moveTo(x,y);
```

#### resizeTo()
브라우저 창의 너비와 높이를 바꿀 때 사용(크롬, 오페라 예외)
```js
resizeTo(w,h);
```

#### setInterval()/clearInterval()
일정한 시간 간격으로 스크립트 실행문을 반복하여 실행 / setInterval()을 취소하고자 할 때 사용
```
var t=setInterval("i++",3000); //3초마다 변수 i값 1씩증가
clearInterval(t);
```
시간 간격은 1/1000초 단위인 msc로 작성을한다.

#### setTimeout()/clearTimeout()
일정한 간격으로 스크립트 실행문을 한 번만 실행 / 실행할 예정인 실행문을 취소
```js
var t = setTimeout("console.log(++i);",5000);
clearTimeout(t);
```
시간 간격은 1/1000초 단위인 msc로 작성을한다.

### screen 객체
사용자의 모니터 정보(속성)을 제공하는 객체이다.
```js
screen.속성;
```

- [screen 속성](https://www.w3schools.com/js/js_window_screen.asp)

### location 객체
브라우저의 주소 창에 url에 대한 정보와 기능을 제공하는 객체이다.
```js
location.속성;
location.메소드();
```

- [location 속성&메소드](https://www.w3schools.com/jsref/obj_location.asp)

### history 객체
사용자가 방문한 사이트 중 이전에 방문한 사이트와 다음 방문한 사이트로 다시 돌아갈 수 있는 속성과 메서드를 제공한다.
```js
history.메소드();
history.속성;
```

- [history 속성/메소드](https://www.w3schools.com/jsref/obj_history.asp)

### navigator 객체
현재 방문자가 사용하는 브라우저 정보와 운영체제 정보를 제공한다.
```js
navigator.속성;
```
- [navigator 속성](https://www.w3schools.com/jsref/obj_navigator.asp)

## 04-4 문서 객체 모델(DOM)

HTML 문서 구조를 가리켜 DOM이라 한다.
문서 객체 구조를 그림으로 표현하면 트리 구조로 되어있다. 뿌리(root)에서 가지처럼 뻗어나가는 것을 노드(node)라 부른다.

### 선택자
HTML에서 사용하는 CSS와 자바스크립트 내에서 사용하는 스타일은 모두 HTML 선택한 요소에 디자인 속성을 바꿀 때 사용한다. HTML내에서 작성된 스타일은 '정적'이며, 자바스크립트 내에서 작성한 스타일은 '동적'이다.

#### 선택자 종류

원거리에 있는 요소를 선택할 때는 직접 선택자 사용, 근접해 있는 요소를 선택할 때는 인접 관계 선택자 사용.

- 직접 선택자(`document.getElementById()`,`document.getElementsByTagName()`,`document.formName.iputName`)
- 인접 관계 선택자(`parentNode`,`childNodes`,`children`,`firstchild`,`previousSibling`,`nextSibling`)

선택자 사용시에 적용 위치가 중요하다.
```xml
<!DOCTYPE html>
<html lang="en">
<head>
</head>
<body>
	HTML 문단 태그 작성
    자바스크립트 선언 <!--HTML 문단 태그가 로딩된 후에 실행-->
</body>
</html>
```

```xml
<!DOCTYPE html>
<html lang="en">
<head>
	<script>
    	// HTML문단 태그가 로딩된 후 실행
    	window.onload="function(){
        	스크립트 실행문
        }
    </script>
</head>
<body>
	HTML 문단 태그 작성
</body>
</html>
```

자바스크립트에서 CSS를 사용시에는 `-`대신 대문자로 써준다.
ex) `font-size` => `fontSize`

인접 관계 선택자는 브라우저 호환성 문제가 있다.

- `getAttribute()` 선택한 태그의 속성값을 불러온다.
- `setAttribute()` 속성값을 변경하거나 또는 새 속성을 만든다.
- `innerHTML` 선택한 요소의 하위 요소를 반환

### 이벤트 핸들러
방문자가 사이트에서 행하는 모든 행위를 '이벤트'라 부르고, 자바스크립트 코드가 실행되는 것을 '이벤트 핸들러'라 한다.

- `onclick` 마우스로 클릭했을 때 이벤트 발생
- `onmouseover` 마우스를 올렸을 때 이벤트 발생
- `onmouseout` 마우스가 벗어났을 때 이벤트 발생
- `submit` 전송이 일어났을 때 이벤트 발생

```js
요소선택.이벤트종류=function(){
	실행문;
}
```
```js
document.getElementById("btn1").onclick=function(){
	alert("welcome!");
}
```