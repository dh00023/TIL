# 속깊은 JavaScript

## 자바스크립트의 스코프와 클로저

### 스코프란?

**스코프**란 현재 접근할 수 있는 변수들의 범위를 뜻한다.

```xml
<div id="div0">Click me! DIV 0</div>
<div id="div1">Click me! DIV 1</div>
<div id="div2">Click me! DIV 2</div>
<script>
	var i, len=3;
	for(i=0;i<len;i++){
		document.getElementById("div"+i).addEventListener("click",function(){
				alert("You clicked div #"+ i);
		},false);
	}
</script>
```

 별도의 스코프가 생성되지 않고 `i`는 글로벌 스코프에 존재한다. 각 `<div>`의 클릭 이벤트에 설정되었던 콜백 함수들은 모두 같은 스코프의 변수 `i`를 참조한다. 이러한 현상은 자바스크립트에서 스코프가 함수로 인해 생성되고 함수가 호출될 때도 계속 지속되어 변수들을 참조하는 특성 때문에 발생한다.

#### 스코프의 생성

```js
for(var i = 0; i < 10; i++){
	var total = (total || 0) + i;
	var last = i;
	if(total > 16){
		break;
	}
}

console.log(typeof total !== "undefined");
console.log(typeof last !== "undefined");
console.log(typeof i !== "undefined");
console.log("total === " + total + ", last === "+ last);
// true
// true
// true
// total === 21, last === 6
```

자바스크립트에서는 스코프 밖에서도 모든 값에 접근 할 수 있다.

이처럼 자바스크립트는 일반적은 블록 스코프를 따르지 않는다.

- `function`
- `with`
- `catch`

이런 구문들이 사용될 때만 스코프가 생성되고, 다른 프로그래밍 언어처럼 `{}`를 이용해 블록을 생성한다고 해서 스코프가 생성되는 것이 아니라는 점이다.

##### `function` 구문의 스코프 생성

```js
function foo(){
	var b = "Can you access me?";
}
console.log(typeof b === "undefined");
// => true
```


foo함수 외부에서 내부에 선언된 변수에 접근할 수 없다. 이것으로 function 구문을 통해서 스코프가 생성된다는 것을 알 수 있다.

##### `catch` 구문의 스코프 생성

괄호 안에 인자로 받는 변수들만 새로운 내부 스코프에 포함되어 다음으로 오는 블록 안에서만 접근 할 수 있다. 반면에 블록 안에서 새로 정의한 변수들은 블록 외부에서도 접근할 수 있다.

```js
try{
	throw new exception("fake exception");
}catch (err){
	var test = "can you see me";
	console.log(err instanceof ReferenceError === true);
}
console.log(test === "can you see me");
console.log(typeof err === "undefined");
// true
// true
// true
```

여기서 주목해야할 점은 `catch`구문의 파라미터인 err는 `catch`블록 내부에서는 접근할 수 있으나 외부에서는 접근할 수 없다. 그러나 test변수는 `catch`구문 외부에서도 접근할 수 있다.

##### `with` 구문의 스코프 생성

`with`도 `catch`와 비슷하다.

```js
with({inScope: "You can't see me"}){
	var notInScope = "but you can see me";
	console.log(inScope === "You can't see me");
}
console.log(typeof inScope === "undefined");
console.log(notInScope === "but you can see me");
// true
// true
// true
```

파라미터로 받은 변수만 스코프 내부에서 접근할 수 있다. `with`구문은 `eval`구문과 함께 사용하지 말아야 할 구문 중 하나이다.

`with`를 이용해서 위의 `scope`문제를 해결할 수 있다.

```xml
<div id="div0">Click me! DIV 0</div>
<div id="div1">Click me! DIV 1</div>
<div id="div2">Click me! DIV 2</div>
<script>
	var i, len=3;
	for(i=0;i<len;i++){
		with({num: i}){
			document.getElementById("divWith"+num).addEventListener("click", function(){
				alert("You clicked div #"+ num);
			},false);
		}
	}
</script>
```

각각 `div`에서 클릭 이벤트 콜백 함수 상위에 스코프가 형성된다.

#### 스코프의 지속성

함수가 선언된 곳이 아닌 전혀 다른 곳에서 함수가 호출될 수 있어서, 해당 함수가 현재 참조하는 스코프를 지속할 필요가 있는 것이다.


함수로 분리하는 것은 비동기 처리를 많이 하는 자바스크립트의 특성에서는 중요하게 생각해야한다.

```xml
<div id="div0">Click me! DIV 0</div>
<div id="div1">Click me! DIV 1</div>
<div id="div2">Click me! DIV 2</div>
<script>
	function setDivClick(index){
		document.getElementById("div"+index).addEventListener("click",function(){
				alert("You clicked div #"+ index);
		},false);
	}
	var i, len=3;
	for(i=0;i<len;i++){
		setDivClick(i);
	}
</script>
```

별도의 `function`을 추가해 `with`구문과 똑같은 개념으로 스코프가 생성되고 지속된다.
`with`가 가진 모호성을 배제하고, 완벽하게 이벤트 처리를 위한 별도의 스코프를 하나 만들어서 사용하게 된다.

**클로저**를 통해서도 해결할 수 있다.

```xml
<div id="div0">Click me! DIV 0</div>
<div id="div1">Click me! DIV 1</div>
<div id="div2">Click me! DIV 2</div>
<script>
	var i, len=3;
	for(i=0;i<len;i++){
		document.getElementById("div"+i).addEventListener("click", (function(index){
				return function(){
					alert("You clicked div #"+ index);
				};
		}(i)),false);
	}
</script>
```

구문 안에서 스코프 체인을 `fucntion`으로 만들어 해결하고 있다.

```js
var func = function(index){/*생략*/}
var returnValue = func(i);
returnValue = (function(index){/*생략*/}(i));
```

위 소스의 위의 두줄을 한줄로 표현한 것이 3번째 줄과 같다. **IIFE**(Immediate Invoke Function Expression)라고 불린다. 스코프 체인을 생성해 클로저를 활용하는 데 매우 유용하게 쓰인다.

#### `with` 구문

사용하면 안 좋은 구문이 두 가지 있다.(**`with` , `eval`**)

`eval`은 보안, 퍼포먼스, 코드의 컨텍스트 변환 등으로 유지보수상 사용하지 말라고 한다.
`with`는 "처음부터 없었던 것처럼 생각하라"고 말했다.

우선 `with`는 파라미터로 받은 객체를 스코프 체인에 추가해 동작한다.

```js
with(object)
	statement;
```
```js
with(object){
	statement;
}
```

`with`구문은 블록 괄호는 옵션이고, 인자로 받는 `object`는 스코프 체인에 추가해 해당 변수들을 로컬 변수처럼 사용할 수 있다.


```js
var user={
	name: "Dahye",
	homepage: "dh00023.github.io",
	language: "Korean"
}
with(user){
	console.log(name === "Dahye");
	console.log(homepage === "dh00023.github.io");
	console.log(language === "Korean");
	language = "javascript";
	nickname = "crong";
}
console.log(user.language === "javascript");
console.log(user.nickname === "crong");
// true
// true
// true
// true
// false
```

#### `with`구문을 자제해야하는 이유

1. 스코프를 생성함으로써 생기는 추가 자원 소모
2. 소스의 모호성
3. ECMAScript6 표준에서 `with` 구문 제외
4. DOM 스타일 설정 문제와 대안

### 클로저(closure)란?

특정 함수가 참조하는 변수들이 선언된 lexical scope는 계속 유지되는데, 그 함수와 스코프를 묶어서 클로저라고 한다.

클로저가 나타나는 가장 기본적인 환경은 스코프 안에 스코프가 있을 때, 즉, function안에 function이 선언되었을 때이다.

```js
function outer(){
	var count = 0; // outer로컬 변수 , 함수 내부에서 접근
	var inner = function(){
		return ++count;
	};
	return inner;
}
var increase = outer();

console.log(increase());
console.log(increase());
// 1
// 2
```

일반적으로 count변수는 outer()함수의 로컬 변수이므로 외부에서 접근 할 수 없다. 그런데 count변수에 접근하는 또 다른 함수 inner를 outer()함수의 반환값으로 지정하고, 이를 글로벌 영역에 있는 increase변수에 할당함으로써 함수 외부에서도 count변수에 접근할 수 있게 되었다. 이게 가장 기본적인 클로저의 개념이다.

클로저를 가장 많이 사용하는 것은 자바스크리브 라이브러리나 모듈에서 private로 나의 변수를 보호하고 싶을 때나 static 변수를 이용하고 싶을 때이다. 그리고 콜백 함수에 추가적인 값들을 넘겨줘서 활용하거나 처음에 초기화했던 값을 계속 유지하고 싶을 때도 사용할 수 있다.

**"즉, 반복적으로 같은 작업을 할 때, 같은 초기화 작업이 지속적으로 필요할 때, 콜백 함수에 동적인 데이터를 넘겨주고 싶을 때 클로저를 사용하자!"**

#### 클로저의 단점

1. 클로저는 메모리를 소모한다.
2. 스코프 생성과 이후 변수 조회에 따른 퍼포먼스 손해가 있다.

클로저는 아무 때나 사용하기보다는 정말 필요한 곳에 사용해야한다.

클로저는 함수가 메모리에서 없어질 때까지 유지되며, 같은 함수라도 다른 클로저를 가지고 있을 수 있다.