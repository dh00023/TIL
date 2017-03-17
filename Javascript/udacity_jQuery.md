# Jquery

Jqeury는 javascript library이다.

```vim
> jQuery
> function (e,t){return new le.fn.init(e,t)}
> $
> function (e,t){return new le.fn.init(e,t)}
```
* `jQuery`는 fucntion + object이다.
* `jQuery` Object와 `$`는 정확히 같은것을 가르킨다.
* `$`는 자바스크립트 객체를 가리키는 포인터이다.
= jQuery Collection (like an array but with additional methods)
```jquery
$(string)
$(function)
$(DOM Element)
$.ajax()
```

DOM은 데이터 구조이다.(트리 형태)
부모, 자식관계
CDN을 통해서 사용할 것을 권장한다.!(google, jQuery official)
jQuery's CDN
http://jquery.com/download/#using-jquery-with-a-cdn
jQuery hosted by Google
https://developers.google.com/speed/libraries/#jquery

jQuery를 이용하면 DOM의 구조를 매우 쉽게 쓸 수 있다.
`$` : jQuery Object라 부르며 ()의 문자열을 jQuery selector라 부른다.
$('tag')
> 예를들어 div요소를 다 보고 싶다면
> divelements=$('div');
> 이것보다 더 좋은 방법이 있다.
$('.class')
> 클래스의 모든 요소를 찾기위해선 .class이름 으로 찾아라!
> $('green')
$('#id#)
> id는 단하나의 요소에 해당된다.  id를 선택하려면 #을 이용해서 할 수 있다.


div의 하위 요소들을 다 선택하고 싶을때?
부모요소를 어떻게 찾을까요?
$('#cameron').parent() 1단계
$('#cameron').parents() 최상위까지 올라감
$('#cameron').parents("div")이런식으로 특정 id한개만 넣으면 그 노드만 선택이된다.
$('#cameron').children() 1단계
$('#cameron').find() 1단계이상
$('#cameron').siblings() 형제요소

# jQuery API method

### Attribute
http://api.jquery.com/

* `.addClass`
* `.toggleClass` : 클래스를 더하거나 없애기도함
* `.next()` 
* `.attr()`
* `.first()`
```js
var article2, article3;
article2 = $(.featured);
article3 = article2.next();
article2.toggleClass('featured');
article2.toggleClass('featured');
```


jQuery로 CSS를 변경하는 방법이 있다.
CSS나 jQuery중 뭘로 변경할지 결정해야한다.

`.css` : css를 변경하는!



`.html` : 태그, 클레스, 속성을 다 볼 수 있음.   

`.text` : html요소를 다 없애고 텍스트만 볼 수 있음.
`.val` : 해당 value값을 볼 수 있음.


#### 새로운 DOM 추가요소
`.append()`

`.prepend()`

 `.insertBefore()`

`.insertAfter()`

# event

`monitorEvents()` :크롬개발자에서만사용하는 function (함수의 이벤트를 관찰하고 기록)

`.on`
`.keypress`는 `.on('keypress',handler)`의 간략한 method이다.


























