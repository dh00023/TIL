# HTML5 + CSS3 웹 표준의 정석

## Chapter8. 레이아웃을 위한 스타일

### CSS와 박스 모델

![](https://lh6.googleusercontent.com/Cekv1Jtqzb-ZaJ55LXOvvRjfC4JFAr5hn-XWO92K9KPGyeC6FMlpek0OffJrstUNyYa04wyYY8jmu-Xrm9X1vxWH-Zv4bV8OyWvLZw1vYgUb2EE8GC0_4Xi_fNGMtc3sGH8RJ5-g)

| 종류 | 해당 태그 |
|:--------|--------|
|블록 레벨|`<p>`, `<h1>`~`<h6>`,`<ul>`,`<ol>`,`<div>`,`<blockquote>`,`<form>`,`<hr>`,`<table>`,`<fieldset>`,`<address>`|
|인라인 레벨|`<img>`,`<object>`,`<br>`,`<sub>`,`<sup>`,`<span>`,`<input>`,`<textarea>`,`<label>`,`<button>`|

#### 박스 모델(box model)

블록 레벨 요소들은 모두 박스 형태이다.

![](https://i2.wp.com/www.bsidesoft.com/wp-content/uploads/2017/02/boxmodel.jpg?resize=660%2C419)

- `width`, `height` : 콘텐츠 영역의 크기(너비, 높이)

> 모던 브라이저에서 박스 모델의 전체 너비 = width + 좌우 패딩 + 좌우 테두리
> 인터넷 익스플로러 6에서 박스 모델의 width값 = 콘텐츠 너비 + 좌우 패딩 + 좌우 테두리

- `display` : 화면 배치 방법 결정
```css
display: none | contents | block | inline | inline-block | table | table-cee
```
블록 레벨 요소와 인라인 레벨 요소를 지정할 때 `display`속성을 이용하지만 원래 `display`속성은 해당 요소가 화면에 어떻게 보일지를 지정할 때 사용
	- `block` : 해당 요소를 블록 레벨로 지정
	- `inline` : 블록 레벨 요소를 인라인 레벨로 바꿀 수 있다.
	- `inline-block` : 요소를 인라인 레벨로 배치하면서 내용에는 블록 레벨 속성을 지정한다.
	- `none` : 해당 요소를 화면에 아예 표시하지 않는다.(공간조차 차지하지 않음)

### 테두리 관련 속성들

- `border-style` : 테두리 스타일 지정
```css
border-style: none | hidden | dashed | dotted | double | groove | inset | outset | ridge | solid
# none 기본값
```
![](https://www.data2type.de/fileadmin/images/xml/border.jpg)

- `border-width` : 테두리 두께
```css
border-top-width: <크기> | thin | medium | thick
border-right-width: <크기> | thin | medium | thick
border-bottom-width: <크기> | thin | medium | thick
border-left-width: <크기> | thin | medium | thick
border-width: <크기> | thin | medium | thick
```
`border-width`를 정할 때 속성 값이 2개라면 좌우, 위아래로 묶어 적용하고, 4개라면 위에 부터 시계방향으로 적용(top->right->bottom->left)

- `border-color` : 테두리 색상 지정
```css
border-top-color: <색상>
border-right-color: <색상>
border-bottom-color: <색상>
border-left-color: <색상>
border-color: <색상>
```

- `border` : 테두리 스타일 묶어 지정하기
```css
border-top: <두께> | <색상> | <스타일>
border-right: <두께> | <색상> | <스타일>
border-bottom: <두께> | <색상> | <스타일>
border-left: <두께> | <색상> | <스타일>
border: <두께> | <색상> | <스타일>
```
이때 순서는 상관없다.

- `border-radius` : 박스 모서리 둥글게 만들기
```css
border-top-left-radius: <크기> | <백분율>
border-top-right-radius: <크기> | <백분율>
border-bottom-right-radius: <크기> | <백분율>
border-bottom-left-radius: <크기> | <백분율>
border-radius: <크기> | <백분율>
# 타원 형태로 둥글게
border-top-left-radius: <가로크기>  <세로크기>
border-top-right-radius: <가로크기>  <세로크기>
border-bottom-right-radius: <가로크기>  <세로크기>
border-bottom-left-radius: <가로크기>  <세로크기>
border-radius: <가로크기> / <세로크기>
```
