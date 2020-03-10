# Collection

collection은 model들을 모아 놓은 것이다. Backbone Model은 DB에서 **레코드 하나**와 비교할 수 있고, Collection은 DB 쿼리 결과로 받은 **레코드들** 이라 생각할 수 있다.



간단한 예제를 통해서 Collection을 생성하고 model들을 넣는 것을 볼 것이다.

```js
var Book = Backbone.Model.extend({
	defaults: {
    id: '',
		sort: 'default',
		title: 'default Title'
	}
});
 
var book1 = new Book({id: 0, sort: 'JavaScript', title: 'JavaScript Book 1'}),
		book2 = new Book({id: 1, sort: 'JavaScript', title: 'JavaScript Book 2'}),
		book3 = new Book({id: 2, sort: 'JavaScript', title: 'JavaScript Book 3'});
	
// Books 라는 collection 생성
var Books = Backbone.Collection.extend({		
	model: Book
});
 
var books = new Books();	

// add 메서드를 사용해서 model들을 books에 추가
books.add([book1, book2, book3]);	

// 생성시에 model들 books에 추가
var books2 = new Books([book1, book2, book3]);	
```



### Model 참조

Collection에 들어있는 모델들에 접근할 수 있는 방법은 다음과 같다.

- `collection.models` property에 배열 형태로 있다.

```js
books.models[0];	//=> book1
books.models[1];	//=> book2
books.models[2];	//=> book3
```

- `.at()` 메서드를 이용해 접근할 수도 있다.

```js
books.at(0);	//=> book1
books.at(1);	//=> book2
books.at(2);	//=> book3
```

- `.get(id)` : id attribute를 통해 접근하기

```js
books.get(0);	//=> book1
books.get(1);	//=> book2
books.get(2);	//=> book3
```

- `getByCid()` : cid로 접근하기

```js
books.getByCid('c0');	//=> book1
books.getByCid('c1');	//=> book2
books.getByCid('c2');	//=> book3
```



## Collection Events

```js
s.listenTo ( s.collection, 'add', s.render );
s.listenTo ( s.collection, 'change:orderQty', s.selectedItemChange );
s.listenTo ( s.collection, 'remove', s.selectedItemChange );
```

- `add` : **모델이 콜렉션에 추가**되었을 때(collection.add(model)을 실행했을 때)
- `remove` : **모델이 콜렉션에서 제거**되었을 때 (collection.remove(model)을 실행했을 때)
- `reset` : 콜렉션이 초기화되었을 때 (collection.reset()을 실행했을 때)
- `sort` : 콜렉션이 어떠한 comparator에 의해 정렬되었을 때 (collection.sort()를 실행했을 때)
- `change` : 모델의 어떠한 값이 변화되었을 때 (model.set(attr: value)를 실행했을 때)
- `change:[attr]` : **모델의 특정한 값이 변화**되었을 때
- `destroy` : 모델이 삭제되었을때 (model.destroy()를 실행했을 때)





## fetch

이 메소드는 서버의 DB나 브라우저의 localStorage에 저장된 데이터를 받아와서 바로 collection에 추가할 수 있다. 이때는 collection을 만들때 model property가 있어도, 없어도 된다. **url property는 반드시 있어야한다.**

model, collection에 지정된 url에 http 호출을 통해서 JSON타입의 데이터를 서버에서 가져온다.

`fetch()` 는 서버에서 주는 데이터 들로 간단하게 collection을 만들 수 있다. 

`fetch()`메소드가 실행되면 url property에 있는 url로 ajax request를 한다. 그 결과 받아온 데이터들이 collection에 들어간다.

```js
var bookModel = new BookModel();
bookModel.fetch({data: })
```

fetch호출시 $.Deffered (Promise) 객체를 리턴

fetch호출시 기본적인 response의 유효성검증 (isValidateResponse 함수) - 실패시 error이벤트발생
<!--url정보가 있고, 전달되는 파라미터(key)값이 있으면 그 값과 비교해서 서버의 DB에 저장된 데이터를 받아오는 함수 인거같아!
어떻게 사용하는지를 알아야하는데..!!!!-->

## Event Bind / Unbind

#### On

예를 들어 movie라는 모델 인스턴스에 change 이벤트와 handler를 바인드한다면

```js
movie.on("change",moiveChangeHandler);
```

간단하게 이벤트 맵핑을 적용할 수도 있다.

```js
movie.on({
    "change:title": titleChangeHandler,
    "change:actor": actorChangeHandler
})
```

또한 Custom 이벤트도 만들 수 있다.

```js
movie.on("selected", movieSelectHandler);
```

```js
movie.trigger("selected");
```

커스텀 이벤트들은 사용자가 직접 이벤트를 호출하여 사용해야하며, **`trigger(event)`** ㅁㅔ소드를 이용하면된다.

즉, trigger 메소드는 **built-in 이벤트나 직접 만든 이벤트등을 직접 호출하고 싶을 때 사용**합니다.

#### off

이벤트 unbinding은 `off()` 메소드를 이용하면된다.

```js
//특정 이벤트에 대한 특정 이벤트핸들러를 제거할 때
movie.off("change:title", titleChangeHandler);

//특정 이벤트에 대한 모든 이벤트핸들러를 제거할 때
movie.off("change:title");

//모든 이벤트에 대한 특정 이벤트핸들러를 제거할 때
movie.off(null, eventHandler);

//모델에 대한 모든 종류의 이벤트핸들러를 제거할 때
movie.off();
```

#### once

해당 이벤트에 대해 한번만 사용되고 바로 제거되는 역할

(jQuery의 one() 메소드와 유사하다.)

####  listenTo

위의 메소드들은 모두 model, collection에 직접 사용된다. Model, Collectiondl 아닌 **Backbone.View** 인스턴스에 기반한 event binding이 필요한 경우에 사용한다.

```js
//movie 모델에 'title' 속성이 바뀌게 되면, view 인스턴스의 'render' 함수를 실행하라
view.listenTo(movie, "change:title", view.render);
```



#### 참조링크

[http://webframeworks.kr/tutorials/backbonejs/backbone_events/](http://webframeworks.kr/tutorials/backbonejs/backbone_events/)

[http://codefactory.kr/2011/12/25/getting-started-with-backbonejs-3-collection/](http://codefactory.kr/2011/12/25/getting-started-with-backbonejs-3-collection/)

