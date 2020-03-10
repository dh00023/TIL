# underscore.js

> underscore.js는 기본 JavaScript 객체들을 확장하지 않고, 함수형 프로그래밍을 지원할 수 있는 100가지 이상의 함수를 가진 유용한 JavaScript 라이브러리다. 

**자바스크립트를 확장하여 편리하게 코드를 작성하거나 웹표준, 크로스 브라우징에 많이 사용**된다.

#### context와 iteratee

```js
_.each(list, iteratee, [context]);
```

- iteratee : 반복을 처리 시키는 내용
- context : context가 있는 경우 this로 바인딩해준다.

```js
var someOtherArray = ["name","patrick","d","w"];

_.each([1, 2, 3], function(num) { 
    console.log( this[num] ); 
}, someOtherArray);

// "patrick"
// "d"
// "w"
```



| 그룹함수 | 설명 |
| -------- | ---- |
| utilities|유틸리티 함수 |
|collection| 배열 또는 객체를 다루는 함수|
|arrays| 배열을 다루는 함수|
|objects| 객체를 다루는 함수|
|functions| 함수를 다루는 함수|

underscore.js 로딩 후 예약어 `_`를 사용한다. (JQuery의 `$` 예약어와 유사) 수십가지 함수들은 카테고리별로 분류되어있다.

각각 함수에 대해서는 [underscore.js](https://underscorejs.org/) 에서 자세히 살펴볼 수 있다.

### extend

`extend()` 는 객체를 확장하는 용도로 사용한다.

```js
_.extend(destination, *sources)
```

source 객체에 있는 모든 프로퍼티를 destination 객체에 복사하고, destination 객체를 리턴합니다. source는 순서대로 처리하므로, 마지막 source의 프로퍼티가 앞의 인자들이 가진 같은 이름의 프로퍼티를 덮어쓸 수 있다.

### 

#### 참조페이지

- [http://blog.jeonghwan.net/underscore-js/](http://blog.jeonghwan.net/underscore-js/)
- [extend 참조](https://hyunseob.github.io/2016/07/23/underscore-extend/)
- [https://harrythegreat.tistory.com/entry/%EC%96%B8%EB%8D%94%EC%8A%A4%EC%BD%94%EC%96%B4-%EC%A0%95%EB%A6%AC](https://harrythegreat.tistory.com/entry/언더스코어-정리)

