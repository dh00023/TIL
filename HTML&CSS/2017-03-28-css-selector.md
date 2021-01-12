# 다재다능한 CSS3 선택자

## 연결 선택자(combination selector)

- 하위선택자(descendant selector) : 지정한 모든 하위 요소에 스타일 적용하기

```css
section p { color: blue; }
```

여기서 section이 상위요소 p가 하위요소이다. 하위 선택자를 이용해 section안에 있는 모든 p 요소의 글자색을 파란색으로 지정한 것이다.

- 자식 선택자(child selector) : 자식 요소에만 스타일 적용하기

```css
section > p { color: blue; }
```

- 인접 형제 선택자(adjacent selector) : 가장 가까운 형제 요소에 스타일 적용

문서 구조상 같은 부모를 가진 형제 요소 중 첫 번째 동생 요소에만 스타일이 적용된다. `+`로 표시

```css
h1 + p { text-decoration: underline; }
```

`h1`요소 다음에 오는  `p`요소들 중 첫번째로 오는 요소에만 밑줄을 그으라는 의미이다.

- 형제 선택자(sibling selector) : 형제 요소에 스타일 적용하기

모든 형제 요소에 적용된다. `~`로 표시

## 속성 선택자

- [속성] 선택자 : 지정한 속성에 스타일 적용하기

```css
a[href] {
	background: yellow;
}
```

`a`태그 중 `href`속성이 있는 요소에만 적용된다.

- [속성 = 값] 선택자 : 특정 값을 갖는 속성에 스타일 적용하기

```css
a[href="_blank"] {
	padding-right: 30px;
    background:url(images/newwindow.png) no-repeat center right;
}
```

- [속성 ~= 값] 선택자 : 여러 값 중 특정 값이 포함된 속성에 스타일 적용하기

```css
[class ~="button"]{
	border: 2px solid black;
    box-shadow: rgba(0,0,0,0.4) 5px 5px;
}
```

- [속성 |= 값] 선택자 : 특정 값이 포함된 속성에 스타일 적용하기

이 선택자는 속성 값이 지정한 값이거나 "값-"으로 시작하면 스타일을 적용한다. 즉 `-`으로 연결한 단어가 있더라도 스타일을 적용한다.

```css
a[title |="us"]{
	background: url(images/us.png) no-repeat left center;
    padding: 5px 25px;
}
```

- [속성 ^= 값] 선택자 : 특정 값으로 시작하는 속성에 스타일 적용하기

```css
a[title ^="eng"]{
	background: url(images/us.png) no-repeat left center;
    padding: 5px 25px;
}
```
```xml
<a href="#" title="english">영어</a>
```

- [속성 $= 값] 선택자 : 특정 값으로 끝나는 속성에 스타일 적용하기

```css
a[title $="hwp"]{
	background: url(images/us.png) no-repeat left center;
    padding: 5px 25px;
}
```
```xml
<a href="#" title="intro.hwp">hwp 파일</a>
```

- [속성 *= 값] 선택자 : 값의 일부가 일치하는 속성에 스타일 적용

```css
a[href *="w3"]{
	background: blue;
    color: white;
}
```
```xml
<a href="http://www.w3c.org/TR/html">HTML 표준안 사이트</a>
<a href="http://www.w3c.org/TR/css3-mediaqueries">미디어쿼리</a>
```

## 가상 클래스(:)와 가상 요소(::)

- 사용자 동작에 반응하는 가상 클래스

사용자가 웹 요소를 클릭하거나 마우스 커서를 올려놓는 등 특정 동작을 할 때 스타일이 바뀌도록 만들고 싶다면 가상 클래스 선택자를 이용한다.

| 가상 클래스 | 설명 |
|--------|--------|
|`:link`|방문하지 않은 링크에 스타일 적용|
|`:visited`|방문한 링크에 스타일 적용|
|`:hover`|웹 요소에 마우스 커서를 올려놓을 때의 스타일 적용|
|`:active`|웹 요소를 활성화했을 때의 스타일 적용|
|`:focus`|웹 요소에 초점이 맞추어졌을때 스타일 적용|

여기서 순서가 중요하다. `:link` > `:visited` > `:hover`, `:active`순서대로 정의한다.

- UI 요소 상태에 따른 가상 클래스

웹 사이트나 앱 화면을 디자인할 때 웹 요소의 상태에 따라 스타일을 지정하기 위해 사용

| 가상 클래스 | 설명 |
|--------|--------|
|`:enabled` , `:disabled`| 요소를 사용할 수 있을 때와 없을 때의 스타일 지정|
|`:checked`|라디오 박스나 체크 박스에서 해당 항목을 선택했을 때 스타일 지정|

- 구조 가상 클래스

웹 문서 구조를 기준으로 특정 위치에 있는 요소를 찾아 스타일을 지정할 때 사용하는 가상 클래스 선택자이다.

| 가상 클래스 | 설명 |
|--------|--------|
|`:root`|문서 전체에 적용하기|
|`:nth-child(n)`, `:nth-last-child(n)`|자식 요소의 위치에 따라 스타일 적용하기(주로 메뉴 항목)|
|`:nth-of-type(n)`,`:nth-last-of-child(n)`|특정 태그 위치에 스타일 적용하기|
|`:first-child`,`:last-child`|첫번째, 마지막 요소에 스타일 적용|
|`:first-of-child`,`:last-of-child`|형제 관계 요소의 위치에 따라 스타일 적용|
|`:only-child`,`:only-of-type`|하나뿐인 자식 요소에 스타일 적용|

- 그 외 가상 클래스

| 가상 클래스 | 설명 |
|--------|--------|
|`:target`| 앵커 목적지에 스타일 적용하기 |
|`:not`|특정 요소가 아닐 때 스타일 적용하기|

- 가상 요소

가상 요소는 내용의 일부만 선택해 스타일을 적용할 때 사용한다.

| 가상 요소 | 설명 |사용할 수 있는 속성|
|--------|--------|--------|
|`::first-line`,`::first-letter`|첫 번째 줄, 첫 번째 글자에 스타일 적용|font, background, color, word-spacing, letter-spacing, text-decoration, verticla-align, text-transform, line-height|
|`::before`,`::after`|내용의 앞뒤에 콘텐츠 추가하기|



