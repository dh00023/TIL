# Vue Animation

뷰 애니메이션은 뷰 프레임워크 자체에서 지원하는 애니메이션 기능으로, 데이터 추가, 변경, 삭제에 대해서 페이드 인, 페이드 아웃 등 여러가지 애니메이션 효과를 지원한다. 기타 자바스크립트 애니메이션 라이브러리나 CSS 애니메이션 라이브러리도 같이 사용할 수 있다.

```html
<transition-group name="list" tag="ul">
			<li v-for="(todoItem,index) in propsdata" v-bind:key="todoItem" class="shadow">
				<i class="checkBtn fa fa-check" aria-hidden="true"></i>{{ todoItem }}
				<span class="removeBtn" type="button" @click="removeTodo(todoItem, index)"><i class="fas fa-trash" aria-hidden="true"></i></span>
			</li>
</transition-group>
```

```vue
<transition-group name="list" tag="ul"></transition-group>
```

`<transition-group>` 태그는 목록에 애니메이션을 추가할 때 사용되는 태그이며, tag명을 지정하면된다. name 속성은 CSS클래스와 연관있다.

```html
<style>
	.list-item{
		display: inline-block;
		margin-right: 10px;
	}
	.list-move{
		transition: transform 1s;
	}
	.list-enter-active, .list-leave-active{
		transition: all 1s;
	}
	.list-enter, .list-leave-to{
		opacity: 0;
		transform: translateY(30px);
	}
</style>
```

css 속성의 클래스를 보면 모두 앞에서 설정한 name 속성 값(list)을 접두사로 갖고 있다. 뒤에오는 부분은 데이터가 들어가고 나가는 동작을 정의하는 CSS이다.

## 참조

- [공식문서](https://kr.vuejs.org/v2/guide/transitions.html)