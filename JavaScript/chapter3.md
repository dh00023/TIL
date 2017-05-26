## 03 자바스크립트의 변수

기본형 변수를 제외한 모든 객체는 Object를 확장하는 형태를 취하며, 모든 함수는 내부적으로 Object를 사용하고있다.

### 03-1 자바스크립트의 기본형과 `typeof`

| type | 설명 |result|
|--------|--------|--------|
|undefined|정의되지 않은 값 또는 해당 값을 가진 변수|"undefined"|
|boolean|true/false 값 또는 해당 값을 가진 변수|"boolean"|
|number|숫자 값 또는 해당 값을 가진 변수|"number"|
|string|문자열 값 또는 해당 값을 가진 변수|"string"|
|object([[Call]])을 구현하지 않은 객체|객체 또는 객체를 저장하는 변수|"object"|
|object([[Call]])을 구현하지 않은 객체 중 비표준||브라우저 내 정의에 의존함|
|function|함수 또는 함수를 저장하는 변수|"function"|
|symbol|`Symbol()` 함수로 생성한 키|"symbol"|
|Null||"null"|

특정 변수가 어떤 형태인지 확인하는 연산자로 `typeof`가 있다.

```js
typeof myVariable;
```

```js
console.log(typeof 3); //number
console.log(typeof "str"); //string
console.log(typeof {}); //object
console.log(typeof []); //object
console.log(typeof function(){}); //function
console.log(typeof null); //object
```

만약 val의 종류가 reference인데 참조를 할 수 없으면 "undefined"반환한다.

### 03-2 `new String("")`과 `""`, 그리고 `String("")`의 차이

객체에 대하여 어떠한 객체인지 확인하는 연산자로 `instanceof`연산자가 있다.

```js
function Person(name, blog){
	this.name = name;
	this.blog = blog;
}

var unikys = new Person("unikys", "http://unikys.tistory.com");

console.log(unikys instanceof Person); // true
console.log(unikys instanceof Object); // true
console.log(typeof unikys); // Object
```

왼쪽에 받는 인자가 오른쪽 인자의 인스턴스인지 확인하고 결과로 true or false를 반환한다.

```js
var color1 = new String("red");
var color2 = "red";
var color3 = String("red");

console.log(color1 == color2); // true
console.log(color1 === color2); // false
console.log(color1 instanceof String); // true
console.log(color2 instanceof String); // false
console.log(color3 instanceof String); // false
console.log(color2 instanceof Object); // false
```

`new String`으로 생성한 문자열과 `""`로 생성한 문자열은 내부적으로 보면 서로 다르다는 것을 알 수 있다. color1은 Strin의 인스턴스이고, color2는 기본형이다.

`==`비교 연산자는 두 피연산자가 다른 형태일 때 대부분 비교를 위해 형변환이 일어나서 같은 값으로 판단하지만, `===`는 형변환이 일어나지 않는 엄격한 비교를 수행한다.

```js
console.log(color1.constructor === String); //true
console.log(color2.constructor === String); //true
```
color2의 생성자가 `String` 인 이유는 constructor를 연산 할 때 내부적으로 형변환이 일어난다음에 접근하기 때문이다.

#### GetValue(V) - 해당 동작 방식 세부적 살펴보기

1. 인자 V가 정상적이면 V값 사용
2. V가 레퍼런스가 아니면 V반환
3. base를 V를 포함한 객체로 설정
4. V가 참조할 수 없는 레퍼런스면 ReferenceError 발생
5. V 속성이 존재하면
	- V를 포함한 객체 base가 기본형이면
		- base는 null이나 undefined여서는 안됨
		- base를 ToObject(base)의 결과로 설정
	- base의 V 속성을 가져와 결과로 반환
6. 아니라면 base는 환결 레코드에 있어야한다.

#### ToObject(argument)

| 인자 유형 | 처리 결과 |
|--------|--------|
|Defined|TypeError발생|
|Null|TypeError발생|
|Boolean|Boolean 객체를 생성한 뒤 입력 값을 설정해 반환|
|Number|Number 객체를 생성한 뒤 입력 값을 설정해 반환|
|String|String 객체를 생성한 뒤 입력 값을 설정해 반환|

#### String(value)

인자가 없다면 s를 `""`로 설정한다. 인자가 있다면, 생성자로 호출된 것이아니고, value가 Symbol이면 Symbol을 나타내는 문자열을 반환한다. s를 ToString(value)로 설정한다.
생성자로 호출된 것이 아니면 s를 반환하며, 생성자로 호출된 것이면 s를 값으로 가지는 String 객체를 생성해 반환한다.

#### ToString(argument)

| 인자 유형 | 처리 결과 |
|--------|--------|
|Undefined|"undefined"|
|Null|"null"|
|Boolean|"true" or "false"|
|Number|ECMAScript 참조|
|String|argument그대로 반환|
|Symbol|TypeError발생|
|Object|argument를 기본형으로 변환 시도후 primValue에 설정하고, ToString(primValue)를 반환|

`String.prototype`에 함수를 추가로 구현해두면 기본형에서도 해당 함수를 사용할 수 있다.

```js
String.prototype.trim = function(){
	return this.replace(/^\s+|\s+$/g,"");
};

console.log("    unikys    ".trim() === "unikys"); //true
```

### 03-3 글로벌 변수

```xml
<script>
// 글로벌 변수를 사용하고 있는 대표적인 예
var element = document.getElementById("div"),
	insertHTML = "<b>Hello world</b>";
element.innerHTML = insertHTML;
</script>
```
위와 같이 그냥 `<script>` 태그 안에서 다른 처리 없이 바로 `var`키워드로 변수를 선언하여 사용한다면, 글로벌 변수를 사용하고 있는 대표적인 예이다.
무의식적으로 글로벌 변수를 사용하는 것도 자제하는 것이 좋다.

##### 글로벌 변수를 자제해야 하는 이유

**'웹'**이라는 특수성 때문에 조심하고 자제해야한다.
- 소스와 데이터의 공개성과 다양한 라이브러리 등 외부 소스 활용
- 비동기 로직과 이벤트 기반 처리
- PC와 같이 좋은 성능에서부터 모바일의 안 좋은 성능까지 다양한 브라우징 환경

글로벌 변수는 도중에 속성값들이 변경되는 등 잠재적인 충돌 위험성이 있다. 특히 AJAX를 통해 비동기로 처리하는 경우 이러한 위험성은 전체 소스를 알고 있지 않다면 원인 분석을 하기가 어려워진다.

이러한 충돌은 모듈화를 하거나 클로저를 통해서 예방할 수 있다. 클로저를 사용하면 일반적인 방법으로 변숫값에 접근하기 힘들어 소스를 보호하는 차원에서도 좋다.

```js
(function(){
	var appendDiv = document.getElementById("appendDiv"),
		callback = {
			"1": (function(){
				var div = document.createElement("div");
				div.innerHTML = "#1";
				return function(){
					return div.cloneNode(true);
				};
			}()),
			"2": (function(){
				var img = document.createElement("img");
				img.src = "http://cfile24.uf.tistory.com/image/203E5A424F471E3025Fa01";
				return function(){
					return img.cloneNode(true);
				};
			}()),
			"delete": function(){
				appendDiv.innerHTML="";
			}
		};

	function append(e){
		var target = e.target || e.srcElement || event.srcElement,
			callbackFunction = callback[target.getAttribute("data-cb")];
		appendDiv.appendChild(callbackFunction());
	}
	document.getElementById("wrapper").addEventListener("click",append);
}());
```

이벤트 호출 콜백에 사용되는 함수와 관련된 변수들은 클로저 안에 선언 함으로써 다른 소스와 충돌을 피하고 있다.

### 03-4 글로벌 변수 정의

글로벌 변수는 말 그대로 선언하면 어디서든지 접근할 수 있는 변수이다.

`<script>`태그 안에 그냥 `var`변수 정의를 하면 글로벌 변수이다.
`var`키워드 없이 변수를 사용하면 글로벌 변수라는 말은 정확하게 보면 특정상황에만 맞고 자바스크립트에서는 많은 상황에 틀린 말이 된다.

### 03-5 window 객체



