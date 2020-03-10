# 03. 노드의 자바스크립트와 친해지기

## 03-1 자바스크립트의 객체와 함수 이해하기

자바스크립트는 자료형을 명시하지 않는다. 이 때문에 자바스크립트는 모든 변수를 `var`키워드로 선언하고 사용한다. 자바스크립트에서도 숫자를 넣어 둘 때 문자열보다 작은 크기의 변수를 만들게 되므로 실제 변수의 크기는 다를 수 있다.

### 자료형

| 자료형 | 설명  |
|------|------|
| Boolean |[기본 자료형]true or false|
| Number | [기본 자료형]정수나 부동소수 값을 가지는 자료형 + 몇가지 상징적인 값(NaN,+-무한대)|
| String | [기본 자료형] 문자열 값을 가지는 자료형|
| undefined | 값을 할당하지 않은 변수의 값|
|null|존재하지 않는 값|
|Object|객체를 값으로 가지는 자료형|

`typeof`연산자를 이용해서 자료형을 확인 할 수 있다.
`parseInt()`,`parseFloat()`를 이용해 문자열을 숫자로 바꿀 수 있다.

### 객체

자바스크립트에서 객체를 만들고 싶다면 **중괄호**를 이용해서 만들 수 있다.

### 함수

`function name(a,b){...}`

**자바스크립트의 변수에는 함수도 할당할 수 있다**.

`var name = function(a,b){...}`

함수가 변수에 할당될 수 있다면 객체 안에 속성으로도 들어갈 수 있다.

## 03-2 배열 이해하기

**배열**은 여러개의 데이터를 하나의 변수에 담아 둘 수 있으며 `[]`를 이용해 접근합니다.
배열의 요소들은 **인덱스(0부터 시작)**로 접근 할 수 있다. 그리고 배열에 요소를 추가할 때는 `push()`메소드를 이용한다.

배열에 들어 있는 요소들의 개수를 알아내려면 `length`속성을 사용.

`for`문과 `forEach()`메소드를 사용하면 배열의 각 요소에 하나씩 접근할 수 있다.
`forEach(function(item,index)`는 첫번째 파라미터는 배열의 각 요소이며, 두번째 파라미터는 요소의 인덱스 값이다.

### 배열에 값 추가, 삭제하기

|속성/메소드|설명|
|-------|--------|
|push(object)|배열의 끝에 요소 추가|
|pop()|배열의 끝에 요소 삭제|
|unshift()|배열의 앞에 요소 추가|
|shift()|배열의 앞에 요소 삭제|
|splice(index, removeCount[,object])|여러 개의 객체를 요소로 추가, 삭제|
|slice(index,copyCount)|여러 개의 요소를 잘라내여 새로운 배열로 객체 생성|

`delete`를 사용해 인덱스를 이용해 배열 요소를 삭제할 수 있다. 하지만 배열의 개수는 그대로 이다. 배열 안에 공간은 두고 요소만 삭제되었기 때문이다. 그러므로 `splice()` 메소드를 사용하는 것이 좋다.

```js
delete Users[2];

Users.splice(2,2);
//시작위치, 삭제할 요소 개수
```

`splice(n,0,추가할요소)` 처럼 두 번째 파라미터를 0으로 입력하면 값을 추가할 수 있다.

## 03-3 콜백 함수 이해하기

### 함수를 호출했을 때 또 다른 함수를 파라미터로 전달하는 방법

이러한 경우는 대부분 비동기 프로그래밍(Non-Blocking)방식으로 코드를 만들 때이다. 이때 파라미터로 전달되는 함수를 **콜백함수(Callback fucntion)**라 한다. 콜백 함수는 함수가 실행되는 중간에 호출되어 상태 정보를 전달하거나 결과 값을 처리하는데 사용된다.

```js
function add(a,b, callback){
	var result = a+b;
	callback(result);
}

add(10,10, function(result){
	console.log('파라미터로 전달된 콜백 함수 호출됨.');
	console.log('더하기 결과 %d',result);
});
```

### 함수 안에서 값을 반환할 때 새로운 함수를 만들어 반환하는 방법

 어떤 함수를 실행했을 때 또 다른 함수를 반환받으면 반환받은 함수를 기대로 실행할 수 있다.

```js
function add(a,b,callback){
	var result = a+b;
	callback(result);

	var history = function(){
		return a +'+'+b+'='+result;
	};
	return history;
}

var add_history = add(10,10,function(result){
	console.log('파라미터로 전달된 콜백 함수 호출됨.');
	console.log('더하기 결과 %d',result);
});

console.log('결과 값으로 받은 함수 실행 결과:'+add_history);
```

함수 안에서 새로운 함수를 만들어 반환하는 경우에는 예외적인 변수 접근을 허용하는데 이것을 **클로저**라고 한다.

## 03-4 프로토타입 객체 만들기

객체 지향언어에서 객체의 원형인 클래스를 만들고, 클래스에서 새로운 인스턴스 객체를 여러 개 만들어 내듯이 자바스크립트에서도 객체의 원형을 정의한 후 그 원형에서 새로운 인스턴스 객체를 만들어 낼 수 있다.

붕어빵 틀에서 실제 붕어빵을 만들어 내듯이 프로토타입을 틀로 이해하면 쉽다.

```js
function Person(name, age){
	this.name = name;
	this.age = age;
}

Person.prototype.walk = function(speed){
	console.log(speed + 'km로 걸어간다.');
}

// new 연산자 는 생성자라고 불린다.
var person0 = new Person('박우진',19);
var person1 = new Person('옹성우',23);

console.log(person0.name);
person0.walk(10);
```

prototype 객체는 객체 자신을 가리키도록 되어있다.

```js
Person.prototype.walk = function(){}
Person.walk = function(){}
```
위의 두 코드는 같은 결과를 보여준다. 다만 prototype속성으로 추가하면 인스턴스 객체를 만들 때 메모리를 효율적으로 관리 할 수 있다는 점이 서로 다르다.