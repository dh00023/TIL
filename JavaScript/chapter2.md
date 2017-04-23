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