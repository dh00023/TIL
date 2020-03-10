# HTML5 + CSS3 웹 표준의 정석

## Chapter3. 이미지와 하이퍼링크

### 이미지

웹 페이지에서 사용할 수 있는 이미지 파일은 파일 크기가 크지 않으면서도 화질ㄹ이 좋아야 하기 때문에 **GIF,JPG/JPEG,PNG**의 형식으로 변환해야한다.

* `<img>` : 이미지 삽입
	* `src` : 이미지 파일 경로 지정하기
```erb
<img src="경로" [속성="값"]>
<!--컴퓨터의 이미지 파일 경로지정-->
<img src="images/road.jpg" alt="">
<!--웹 상의 링크르 복사해 이미지 경로지정-->
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Lion_waiting_in_Namibia.jpg/440px-Lion_waiting_in_Namibia.jpg">
```
	* `alt` : 이미지를 설명해 주는 대체 텍스트
```erb
<img src="경로" alt="설명">
<!--컴퓨터의 이미지 파일 경로지정-->
<img src="images/home.jpg" alt="홈으로가기">
```
	* `width`, `height` : 이미지 크기 조정하기
```erb
<img src="images/road.jpg" width="250" height="90" alt="사려니 숲길">
```
(이 속성으로 작은 이미지를 크게 표시할 경우에는 화질이 나빠질 수 있음)

* `<figure>` : 설명 글을 붙일 대상 지정
> 설명 글을 붙여야 할 대상을 지정하거나 웹 문서에서 오디오,비디오(멀티미디어)파일을 비롯해 사진,표,소스코드 등 한 단위가 되는 요소를 묶을 때 사용

* `<figcaption>` : 설명 글 붙이기
```erb
<figure>
		<img src="http://cfile1.uf.tistory.com/image/145038365098EFDB16035E" alt="용눈이오름">
		<figcaption>완만하고 부드러운 용눈이오름</figcaption>
</figure>
```

### 링크 만들기

* `<a>` : 링크만들기

| 속성 | 설명 |
|:--------|:--------|
|`href`| 링크한 문서나 사이트 주소 입력|
|`target`| 링크한 내용이 표시될 위치(현재 창 or 새 창) 지정|
|`download`| 링크한 내용을 보여주는 것이 아닌 다운로드|
|`rel`| 현재 문서와 링크한 문서의 관계 알려줌|
|`hreflang`|링크한 문서의 언어 지정|
|`type`|링크한 문서의 파일 유형 알려줌|

* `target` 속성

| 속성 | 설명 |
|:--------|:--------|
|`_blank`| 새 탭, 새 창에서 열림|
|`_self`| default값, 링크가 있는 화면에서 열림|
|`_parent`| 프레임 사용시 부모 프레임에 표시|
|`_top`| 프레임 사용시 프레임에서 벗어나 링크 내용을 전체화면에 표시|

```erb
<h1>텍스트링크</h1>
	<a href="http://likelion.org">멋쟁이사자처럼 홈페이지</a>
<h1>이미지링크</h1>
	<a href="http://likelion.org target="_blank">
    	<img src="https://avatars.githubusercontent.com/likelionkonkuk?v=2&s=100">
    </a>
```

* `<iframe>` : 프레임의 일종으로 프레임 중에서 문서 본문에 액자처럼 삽입하는 것이다. 이때 현재 문서는 부모 문서가 되고 `iframe`에 삽입된 문서는 자식 문서가 된다.

```erb
<!--parent.html-->
<iframe src="child.html" width="600" height="400"></iframe>

<!--target을 _top으로 지정할경우 프레임을 벗어나 브라우저 창 전체에 링크 내용 표시-->
<a href="http://easyspub.co.kr/20_Menu/BookView/65" target="_top">
```

* 앵커(anchor) : 한 페이지 안에서 점프!
```erb
<태그 id = "앵커 이름">텍스트 또는 이미지</태그>
<a href="#앵커 이름">텍스트 또는 이미지</a>
```
```erb
<ul id="menu">
	<li><a href="#content1">메뉴1</a></li>
	<li><a href="#content2">메뉴2</a></li>
</ul>
	<h2 id="content1">내용1</h2>
		<p><a href="#menu">[메뉴로]</a></p>
	<h2 id="content2">내용2</h2>
```

* `<map>`, `<area>`, `usemap` : 이미지 맵 지정하기
	* 이미지 맵? 한 이미지상에서 클릭 위치에 따라 서로 다른 링크가 열린다.(메일에서 사용)

```erb
<img src="images/kids.jpg"  alt="" usemap="#favorites">
<map name="favorites">
  <area shape="rect" coords="10,10,160,200" href="http://cafe.naver.com/doithtml5" target="_blank" alt="do it html5 네이버 카페로 가기">
  <area shape="rect" coords="220,10,380,200" href="http://www.facebook.com/do.it.html5" target="_blank" alt="do it html5 페이스북 페이지로 가기">
</map>
```

| 속성 | 설명 |||
|:--------|:--------|:--------:|:--------|
|`alt`| 대체 택스트 지정 |||
|`coords`|링크로 사용할 영역을 시작 좌표와 끝 좌표를 이용해 지정 |||
|`download`| 링크를 클릭했을 때 링크 문서 다운 |||
|`href`| 링크문서 지정 |||
|`media`| 링크문서를 어떤 미디어에 최적화시킬지 지정 |||
|`rel`| 현재 문서와 링크 문서 사이의 관계지정 |속성 값|lternamte, bookmark, help, license, next, nofollow, noreferer, prefetch, prev, search, tag|
|`shape`| 링크로 사용할 영역의 형태 지정 | 속성 값 | default, rect, circle, poly|
|`target`| 링크를 표시할 대상 지정 | 속성 값 |_blank, _parent, _self, _top, 프레임 이름|
|`type`|링크 문서의 미디어 유형을 지정|||


### SVG 이미지

**SVG** 파일 형식은 이미지를 아무리 확대하거나 축소해도 원래의 깨끗한 상태 그대로 유지되는 이미지이다.

[d3.js](http://d3js.org/), [Raphael.js](http://dmitrybaranovskiy.github.io/raphael/)에서 표현하는 방식이 SVG이미지이다.

#### SVG이미지를 지원하지 않는 브라우저([Modernizr](https://modernizr.com/))

```erb
<!doctype html>
<html lang="ko">
<head>
	<meta charset="utf-8">
	<title>Insert SVG</title>
	<script src="modernizr-custom.js"></script>
</head>
<body>
	<h1>SVG 이미지 삽입하기</h1>
	<img src="images/muffin.svg">
	<script>
		if (!modernizr.svg) {
			$("img").attr("src", "images/muffin.png");
		}
	</script>
</body>
</html>
```
