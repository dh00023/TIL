# HTML5와 멀티미디어

## 이미지와 하이퍼링크

이미지는 크게 비트맵과 벡터로 구분된다.

### 비트맵

각 픽셀이 모여 만들어진 정보의 집합으로 Raster 이미지라고도 불리며, 픽셀 단위로 화면에 렌더링한다. 

#### JPG(JPEG)

JPG는 압축률이 훌륭해 사진이나 예술 분야에서 많이 사용됨

- 손실 압축
- 표현 색상도(24bit, 약 1600만 색상) 뛰어나 고해상도 표시장치에 적합
- 이미지의 품질과 용량을 쉽게 조절 가능
- 가장 널리 이용

#### PNG

Portable Network Graphics는 GIF의 대체 포맷으로 개발됐다.

- 비손실 압축
- 8bit/24bit 컬러 이미지 처리
- 투명도(Alpha Channel) 지원
- W3C 권장 포맷

#### GIF

Graphics Interchange Format는 이미지 파일 내 이미지 및 문자열 같은 정보를 저장할 수 있다.

- 비손실 압축
- 여러장의 이미지를 한 개의 파일에 담을 수 있음
- 8bit 컬러만 지원

#### WEBP

JPG, PNG, GIF를 모두 대체할 수 있는 구글이 개발한 이미지 포맷

- 완벽한 손실/비손실 압축 지원
- GIF와 같은 애니메이션 지원
- 투명도(Alpha Channel) 지원
- [지원 브라우저](https://caniuse.com/webp)가 적음

### 벡터(Vector)

이미지가 가지고 있는 점, 선, 좌표, 색상 등의 정보를 온전히 가지고 있으며, 그것을 화면에 렌더링한다. 조금 더 많은 연산을 하지만 해상도(픽셀)로부터 자유롭게 렌더링할 수 있다. 즉, 확대 및 축소를 해도 이미지가 깨지지 않고, 수학적 정보만 가지고 있기때문에 이미지 확대/축소에도 용량 변화가 없다.

#### SVG

Scalable Vector Graphics는 마크업 언어 기반의 벡터 그래픽을 표현하는 포맷

- 해상도의 영향에서 자유로움
- CSS로 스타일링 가능
- Javascript로 event handling 가능
- 코드 혹은 파일로 사용 가능
- [d3.js](http://d3js.org/), [Raphael.js](http://dmitrybaranovskiy.github.io/raphael/)에서 표현하는 방식이 SVG이미지이다.

- SVG이미지를 지원하지 않는 브라우저([Modernizr](https://modernizr.com/)) 대응

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



## 이미지 관련 태그

#### `<img>` : 이미지 삽입

```html
<img src="경로" [속성="값"]>
<img src="이미지 상대/절대 경로" alt="이미지를 설명해 주는 대체 텍스트" width="이미지가로">
```

width, height 중 한개만 입력하면 이미지 비율이 유지되면서 크기만 줄어든다.

```css
/* CSS로 이미지 크기도 조절할 수 있다. */
img {
  width: 666px;
}
```


<h3 id="responsiveImg"> 가변 이미지(반응형 웹에서 주로 사용)</h3>

#### **CSS 이용하기**

```css
img{
		max-width: 100%;
    height: auto;
}
```

`max-width`를 100%로 지정하면 된다.

#### `<img>`태그와 `srcset`속성

```xml
<img src="<이미지>" srcset="<이미지1>[, <이미지2>,<이미지3>, ...]">
```
```xml
<img src="imgaes/pencil.jpg" srcset="images/pencil-hd.jpg 2x" alt="색연필 제품 이미지">
```


| 속성        | 설명                                                         |
| ----------- | ------------------------------------------------------------ |
| **srcset**  | 이미지 파일 경로(브라우저에 제시할 이미지 URL과 **원본 크기**의 목록을 정의)<br>`w`(이미지의 가로 너비), `x`(이미지의 비율 의도) 단위를 입력해야하며, 작은 단위 부터 입력해준다.<br>(IE 미지원) |
| media       | srcset에 지정한 이미지를 표시하기 위한 조건                  |
| type        | 파일 유형                                                    |
| **sizes**   | 미디어조건과 그 조건에 해당하는 이미지의 **최적화 출력 크기** 지정(IE 미지원) |
| crossorigin | 가져 오기가 CORS 사용하여 수행되어야하는지 여부              |

```html
<img srcset="images/pencil-small.jpg 400w,
             images/pencil-medium.jpg 700w,
             images/pencil-large.jpg 1000w"
     sizes="(max-width: 500px) 444px,
            (max-width: 800px) 777px,
            1222px"
     src="images/pencil.jpg"
     alt="색연필 제품 이미지" />
<img srcset="images/pencil-small.jpg 1x,
             images/pencil-medium.jpg 1.75x,
             images/pencil-large.jpg 2.5x"
     sizes="(min-width: 1000px) 700px"
     src="images/pencil.jpg"
     alt="색연필 제품 이미지" />
```

- `srcset` 속성은 ','로 구분된 사용할 이미지들의 경로와 해당 이미지의 원본 크기를 지정하고, `sizes`  속성은 미디어 조건(선택적)과 그에 따라 출력될 이미지 크기를 지정한다.
- `src` 는 `srcset` 에서 활용되지 못한 이미지가 있으면 활용된다!
- 일반적으로 `w` 단위를 사용하는 것을 권장한다.
- 일반 출력(`width`)은 일반적으로 크기만 변경하고, 최적화 출력은 srcset에서 최적화 출력에 맞는 이미지를 사용한다.
- `width` 와 `srcset` 두 개다 선언된 경우, `width` 가 우선순위를 갖는다.
#### `<picture>`, `<source>` : 상황별 다른 이미지 표시하기

`<picture>` 태그와 `<source>`태그를 함께 사용해 화면 해상도뿐만 아니라 화면 너비에 따라 다른 이미지를 표시할 수 있다.

```xml
<picture>
	<source srcset="images/shop-large.jpg" media="(min-width:1024px)">
	<source srcset="images/shop-medium.jpg" media="(min-width:768px)">
	<source srcset="images/shop-small.jpg" media="(min-width:320px)">
	<img src="images/shop.jpg" alt="fill with coffee" style="width:100%;">
</picture>
```

  

#### `<figure>`, `<figcaption>`

- `<figure>` : 설명 글을 붙일 대상 지정
  - 설명 글을 붙여야 할 대상을 지정하거나 웹 문서에서 오디오,비디오(멀티미디어)파일을 비롯해 사진,표,소스코드 등 한 단위가 되는 요소를 묶을 때 사용

- `<figcaption>` : 설명 글 붙이기

```erb
<figure>
		<img src="http://cfile1.uf.tistory.com/image/145038365098EFDB16035E" alt="용눈이오름">
		<figcaption>완만하고 부드러운 용눈이오름</figcaption>
</figure>
```





## 웹과 멀티미디어

웹 사이트에서 플러그인을 이용해 멀티미디어를 재생하는 것은 문제점이 많다. 미디어 파일 형식에 따라 사용하는 플러그인 프로그램이 달라진다는 점이 가장 큰 문제다. ActiveX는 개발자가 원하는 대로 수정이 가능해 원래 의도한 목적 외에도 여러파일을 자동 설치할 수 있다. 심지어 바이러스가 포함 될 수도 있다.

**HTML5**웹 표준이 지정되면서 플러그인 프로그램들이 사라지고 있다. 이제는 대부분 **HTML5 플레이어**를 사용한다.

플러그인(plug-in) : 웹 브라우저에서 처리할 수 없는 작업을 위해 웹 문서 안에 포함시킨 외부 프로그램 기능

* `<object>` : 외부 파일 삽입하기
	* 자바 애플릿, PDF 파일, 플래시 무비 같은 콘텐츠를 웹 문서안에 포함시키기 위해 사용.

| 속성 | 설명 |
|:--------:|:--------|
| **data** | 외부 파일의 경로 지정 |
| **type** | 포함시킨 내용의 유형 지정|
| name | 다른 요소와 구분할 수 있는 이름 지정|
| width | 포함시킨 내용의 너비 값 지정|
| height | 포함시킨 내용의 높이 값 지정|

```erb
<object data="경로" type="유형" name="이름" width="넓이" height="높이"></object>

<object data="CalmBay.swf" type="application/x-shockwave-flash" width="450" height="400"></object>
```

* `<embed>` : 외부 파일 삽입하기
```erb
<embed src="경로" type="유형" width="너비" height="높이">
<embed src="CalmBay.swf" width="450" height="400">
```

* 인코딩 : 원본 비디오를 최대한 압축해 컴퓨터에서 사용할 수 있는 비디오 파일로 변환
* 디코딩 : 비디오 파일에 저장되어 있는 비디오 정보를 가져와 비디오 플레이어에 보여주는 과정
* 비디오 코덱 : 인코딩과 디코딩을 수행하는 것

| 비디오코덱 | 설명 |
|:--------|:--------|
| H.264/AVC | mp4 파일에서 사용한다. 고화질 영상을 지원하기 때문에 멀티미디어 업계에서 표준으로 사용하고 있다. 유료 코덱이지만 온라인 상에서 사용할 경우에 한해 무료로 사용할 수 있다.|
| v8, v9| 구글에서 오픈소스로 공개한 코덱. webm 파일에서 사용한다. H.264보다 하드웨어 지원이 부족한 단점. 화질이 우수, 무료로 제공됨|
| Ogg Theora(오그 테오라) | 무료 공개 코덱, ogv파일에서 사용. 다른 코덱보다 화질은 떨어짐|

* 오디오 코덱

| 오디오 코덱 | 설명 |
|--------|--------|
|MPEG-1 AUDIO Layer3| 흔히 'MP3 코덱'이라 부름. mp3파일에선 이 코덱 사용 |
|Ogg Vorbis|MP3와 달리 오픈 소스, 누구나 무료로 사용가능 ,`.ogg`, `.oga`사용, 재생할 수 있는 플레이어가 적고, 인코딩 시간이 오래걸리는 단점|

* HTML5 비디오 변환 하기
	* [[카카오인코더(mp4, webm)변환]](http://blog.naver.com/cacaotools)
	* [[팟 인코더(ogv) 변환]](http://www.daum.net/)

## 오디오 & 비디오 재생하기

### `<audio>` : 오디오 파일 삽입

```erb
<audio src="오디오 파일 경로"[속성][속성="속성 값"]></audio>
```

| 속성 | 설명 |  |
|--------|--------|--------|
|autoplay|오디오 자동 재생|  |
|controls|웹 화면에 컨트롤 막대 표시(재생/멈춤/진행 바/ 볼륨)|  |
|loop| 오디오를 반복 재생 |  |
|muted| 오디오를 재생해 진행하지만 소리는 끈다(음소거) |  |
|preload| 재생 버튼을 눌러 재생하기 전에 오디오 파일을 다운로드해 준비해 둔다. | `none` : 로드하지 않음<br>`metadata` : 메타데이터만 로드(default)<br>`auto`: 전체 파일 로드 |

```html
<audio src="https://interactive-examples.mdn.mozilla.net/media/cc0-audio/t-rex-roar.mp3" controls autoplay></audio>
```

자세한 부분은 js로 제어할 수 있다.

### `<video>` : 비디오 파일 삽입

```erb
<video src="오디오 파일 경로"[속성][속성="속성 값"]></video>
```

| 속성 | 설명 |  |
|--------|--------|--------|
|autoplay|자동 재생-사용하지 않기를 권함|  |
|controls|웹 화면에 컨트롤 막대 표시(재생/멈춤/진행 바/ 볼륨)|  |
|loop| 반복 재생 |  |
|muted| 소리는 끄고 화면만 재생|  |
|preload| 재생하기 전에 파일을 모두 다운할 것인지 일부만 다운할 것인지 지정(none, metadata, auto) | `none` : 로드하지 않음<br/>`metadata` : 메타데이터만 로드(default)<br/>`auto`: 전체 파일 로드 |
|width, height| 비디오 크기 조절 |  |
|poster| 동영상 썸네일 이미지 URL |  |
|crossorigin| 가져 오기가 CORS 사용하여 수행되어야하는지 여부 | `use-credentials`, `anonymous` |

* `<source>` : 여러 미디어 파일 한꺼번에 지정

```erb
<source src="video.ogv" type="video/ogg; codecs='theora,vorbis'"]>

<video controls>
	<source src="media/Painting.ogv" type="video/ogg">
	<source src="media/Painting.mp4" type="video/mp4">
	<source src="media/Painting.webm" type="video/webm">
</video>
```

| 속성 | 설명 |
|--------|--------|
|src|미디어 파일 경로를 지정하는 필수속성|
|type|웹 브라우저가 해당 미디어파일을 재생할 수 있는지 여부 확인을 위한 미디어 파일 유형|
|codecs| 비디오 코덱지정|

이전 브라우저를 고려해 여러형식의 파일을 올려도 재생되지 않는 경우가 있다. 이건 웹 서버에서 확장자를 인식하지 못했기 때문이다. **MIME**유형 추가해야한다. **MIME**란 서버에서 클라이언트 쪽에 파일을 보낼때 표시법을 알려주기 위해 함께 보내는 파일 형식 정보.

* `<track>` : 비디오 화면에 자막 추가하기

```erb
<track kind="자막종류" src="경로" srclang="언어" label="제목" default=""></track>
```

- kind속성 값

| 속성 값 | 설명 |
|--------|--------|
|**subtitles**|자막입니다.|
|captions|캡션(청각장애인용 자막이거나 소리를 들을 수 없거나 켤 수 없는 경우에 사용)|
|descriptions|비디오 콘텐츠에 대한 설명(화면표시X)|
|chapters|비디오 탐색을 위한 장 제목(화면표시X)|
|metadata|비디오 콘텐츠 정보(화면표시X)|

주로 자막 파일로는 HTML5에서는 **srt**파일을 사용하지만 모든 브라우저에서 공식적으로 지원하는 자막 파일형식은 WebVTT(`.vtt`)이다.

```vtt
WEBVTT

시작시간 --> 종료시간
자막내용

00:00.000 --> 00:02.172
예술이란

00:02.172 --> 00:05.719
자연이 인간에 투영된 것입니다

00:05.719 --> 00:07.716
중요한 것은

00:07.716 --> 00:11.061
깨끗하게 투영될 수 있도록

00:11.061 --> 00:20.879
늘 깨끗하게 거울을 닦는 일입니다
```

[**HTML5 Video Caption Maker**](https://testdrive-archive.azurewebsites.net/graphics/captionmaker/)사이트로 쉽게 비디오에 자막 추가할 수 있다.

## 멀티미디어 링크 만들기

### `<iframe>`

: 다른 HTML 페이지를 현재 페이지에 삽입할 수 있다.

- 프레임의 일종으로 **프레임 중에서 문서 본문에 액자처럼 삽입**하는 것이다. 이때 현재 문서는 부모 문서가 되고 `iframe`에 삽입된 문서는 자식 문서가 된다.
- inline element이다.

```erb
<!--parent.html-->
<iframe src="child.html" width="600" height="400"></iframe>

<!--target을 _top으로 지정할경우 프레임을 벗어나 브라우저 창 전체에 링크 내용 표시-->
<a href="http://easyspub.co.kr/20_Menu/BookView/65" target="_top">
```

### `<canvas>`

: 그래픽이나 애니메이션 랜더링시 사용한다.

### `<map>`, `<area>`, `usemap` 

: 이미지 맵 지정하기

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


## 참고 

- [HEROPY Tech - 입문자에게 추천하는 HTML, CSS 첫걸음](https://heropy.blog/2019/04/24/html-css-starter/)
- [Do it! HTML5+CSS3 웹 표준의 정석](https://book.naver.com/bookdb/book_detail.nhn?bid=15975063)
- [MDN web docs](https://developer.mozilla.org/ko/)
- [HEROPY Tech - 한눈에 보는 HTML 요소 총정리](https://heropy.blog/2019/05/26/html-elements/)
