# HTML5 + CSS3 웹 표준의 정석

## Chapter14. 반응형 웹이란?

### 모바일 기기와 웹 디자인

**반응형 웹 디자인**은 화면 요소들을 화면 크기에 맞게 재배치하고 각 요소의 표시 방법만 바꾸어 사이트를 구현해준다.

#### 장점

1. 사이트 하나만 만들면 데스크톱 PC , 모바일 모두 사용할 수 있다.
2. 모든 스마트 기기에서 접속 가능하다
3. 가로 모드에 맞춰 레이아웃 변경 가능하다
4. 사이트 유지, 관ㄹ리가 용이하다.

#### 뷰포트(viewport)

PC와 모바일 화면의 픽셀 표현 방법이 다른데 뷰포트를 지정하면, 기기 화면에 맞춰 확대하거나 축소 할 수 있다. **뷰포트**는 실제 내용이 표시되는 영역이다.

모바일 브라우저들의 기본 뷰포트 너비가 980px이다. 그래서 320px로 맞춰 페이지를 제작해도 980px로 표시하려고 하기때문에 글씨와 그림이 작게 표시되는 것ㅇ디ㅏ.

```
<meta name="viewprot" content="<속성1=값>, <속성2=값>, ...">
```

| 속성 | 설명 | 사용 가능한 값 | 기본 값 |
|--------|--------|--------|--------|
|width|뷰포트 너비| device-width 또는 크기 | 브라우저 기본 값|
|height|뷰포트 높이 | device-height 또는 크기 | 브라우저 기본 값|
|user-scalable|확대/축소 가능 여부 | yes or no | yes|
|initial-scale|초기 확대/축소 값|1~10|1|
|minimum-scale|최소 확대/축소 값|0~10|0.25|
|maximum-scale|최대 확대/축소 값|0~10|1.6|

가장 많이 사용하는 형태

```xml
<meta name="viewport" content="width=devise-width, initail-scale=1">
```

크롬 개발자 도구를 이용해서 반응형 웹 디자인을 쉽게 확인할 수 있다.

### 가변 그리드 레이아웃(fluid grid layout)

그리드 시스템을 사용하면 화면을 단순하게 만들면서도 규칙적으로 배열하기 때문에 레이아웃을 일관성 있게 유지할 수 있다는 장점이 있다.

주로 960px의 12칼럼 그리드를 사용한다.

![](http://dtechviews.com/wp-content/uploads/2015/05/Slide3.jpg)

사이트의 레이아웃을 백분율로 지정하는 것을 **가변 그리드 레이아웃**이라고 한다.

### 가변 레이아웃과 가변 요소

#### 가변 글꼴 - `em` , `rem`

1em=16px이기 때문에 `글자크기(em) = 글자크기(px) / 16px`로 구할 수 있다. `em`은 부모 요소의 글꼴을 기준으로 해서 중첩된 부모 요소의 글자 크기에 영향을 받는다.

`rem`은 처음부터 기본 크기를 지정하기 때문에 중간에 기본 값이 바뀌지 않는다.

#### 가변 이미지

- CSS 이용하기

```css
img{
	max-width: 100%;
    height: auto;
}
```

`max-width`를 100%로 지정하면 된다.

- `<img>`태그와 `srcset`속성

```xml
<img src="<이미지>" srcset="<이미지1>[, <이미지2>,<이미지3>, ...]">
```
```xml
<img src="imgaes/pencil.jpg" srcset="images/pencil-hd.jpg 2x" alt="색연필 제품 이미지">
```

- `<picture>`, `<source>` : 상황별 다른 이미지 표시하기

`<picture>` 태그와 `<source>`태그를 함께 사용해 화면 해상도뿐만 아니라 화면 너비에 따라 다른 이미지를 표시할 수 있다.

| 속성 | 설명 |
|--------|--------|
|srcset|이미지 파일 경로|
|media|secset에 지정한 이미지를 표시하기 위한 조건|
|type|파일 유형|
|sizes|파일의 크기|

```xml
<picture>
	<source srcset="images/shop-large.jpg" media="(min-width:1024px)">
	<source srcset="images/shop-medium.jpg" media="(min-width:768px)">
	<source srcset="images/shop-small.jpg" media="(min-width:320px)">
	<img src="images/shop.jpg" alt="fill with coffee" style="width:100%;">
</picture>
```

#### 가변 비디오

- CSS 이용하기

```css
video{
	max-width: 100%;
}
```

### 미디어 쿼리

사용자가 어떤 미디어를 사용하는가에 따라 사이트의 형태가 바뀌도록 CSS 작성하는 방법

```css
@media [only|not] 미디어 유형 [and 조건]*[and 조건]
```

```css
@media screen and (min-width:200px) and (max-width:360px){
}
```

#### 미디어 유형의 종류

| 미디어 유형 | 사용 가능한 미디어 |
|--------|--------|
|all|모든 미디어 유형|
|print|인쇄 장치|
|screen|컴퓨터 스크린(스마트폰 포함)|
|tv|음성과 영상이 동시 출력되는 TV|
|aural|음성 합성 장치(주로 화면을 읽어 소리로 출력)|
|braille|점자 표시 장치|
|handheld|패드처럼 손에 들고 다니는 장치|
|projection|프로젝터|
|tty|디스플레이 기능이 제한된 장치|
|embossed|점자 프린터|

단말기의 경우에는 `divice-width`로 쿼리를 작성.

#### 화면 회전

- `orientation: portrait` : 단말기 세로 방향
- `orientation: landscape` : 단말기 가로 방향

#### 화면 비율(`aspect-ratio`)

화면의 너비 값을 높이 값으로 나눈 것으로 화면비율을 사용할 수 있다.

#### 색상당 비트 수(color)