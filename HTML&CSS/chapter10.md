# HTML5 + CSS3 웹 표준의 정석

## Chapter10. HTML5와 시맨틱 태그

시맨틱(sementic) : '의미가 통하는'이라는 뜻으로 시맨틱태그는 태그만 보고도 페이지 구조를 쉽게 이해할 수 있도록 정의된 태그를 의미

### HTML4 vs HTML5 문서

HTML4는 `div`태그로 주로 화면 구성을 하였고, 수 많은 태그들을 다시 id 속성으로 구분했다. 하지만 수천 줄이 넘는 코드에서 일일이 헤더, 메뉴, 사이드바를 찾는 것은 쉽지 않았다. 그러한 이유때문에 HTML5에서 시맨틱 태그가 등장했다.

![](http://cfile10.uf.tistory.com/image/2572233758AE854230E538)

시맨틱 태그로 작성한 소스를 보면 태그만 보고도 어느 부분이 제목이고 메뉴이고 실제 내용인지 쉽게 알 수 있다.

### 문서 구조를 위한 HTML5 시맨틱 태그

* `<header>` : 머리말 지정
	*  주로 페이지 맨 위쪽이나 왼쪽에 삽입한다.
	*  `<nav>`를 이용해 사이트 메뉴를 넣는다.
	*  그리고 본문 중에 사용해 머리말로 쓸 수도 있다.

* `<nav>` : 문서를 연결하는 내비게이션 링크
	* 내비게이션 메뉴뿐만 아니라 footer에 사이트 링크 모음에도 많이 사용

* `<section>` : 주제별 콘텐츠 영역 나타내기
	* 섹션제목(`h1`~`h6`)
	* `<section>`안에 `<section>`을 쓸 수 있다.
	* 문맥 흐름 중에서 콘텐츠를 주제별로 묶을 때 사용(`article`내에서도 사용가능)

* `<article>` : 콘텐츠 내용 넣기
	* 웹상의 실제 내용을 넣는다.
	* 태그를 적용한 부분을 떼어 독립적으로 배포하거나 재사용해도 완전한 하나의 콘텐츠가 된다면 사용

* `<aside>` : 본문 이외의 내용 표시
	* 사이드바(필수 요소 아님) - 광고, 링크모음 등등

* `<iframe>` : 외부 문서 삽입
	* 웹 문서 안에 다른 웹 문서를 가져와 표시하는 것(inline frame)
	```erb
    <iframe src="삽입할 문서 주소" [속성 = "속성 값"]></iframe>
    ```

    | 속성 | 설명 |
|:--------:|:--------|
|width|인라인 프레임의 너비(픽셀, 백분율)|
|height|인라인 프레임의 높이(픽셀, 백분율)|
|name|인라인 프레임의 이름|
|src|프레임에 표시할 문서의 주소 지정|
|seamless|프레임의 테두리를 없애 마치 본문의 일부처럼 보이도록 만든다.(chrome, safari)|

* `<footer>` : 제작 정보와 저작권 표시
	* `header`, `section`, `article`등 다른 레이아웃 태그들을 모두 사용할 수 있음

* `<address>` : 사이트 제작자 정보, 연락처 정보
	* 주로 `footer`안에 사용

* `<div>` : 콘텐츠를 묶어 시각적 효과를 적용할 때 사용(CSS적용)

### IE8 이하 버전에서는 어떻게 하나요?(시맨틱 태그를 지원하지 않음)

[[시맨틱 태그 지원 상황]](http://caniuse.com) -> [Index of features] -> [New semantic elements]

1. CSS에서 블록 레벨로 정의하기
 브라우저는 자신이 인식하지 못하는 태그를 인라인 태그로 취급한다. 인라인 태그는 위치값을 가질 수 없다. HTML5 시맨틱 태그를 인식하지 못하는 브라우저에서는 `<style>`태그를 이용해 자신만의 영역을 가질 수 있는 블록 레벨 태그로 바꾸어준다.
 ```css
 header, section, nav, article, footer{
 	display: block;
 }
 ```

2. 시맨틱 태그 직접 정의하기
 브라우저에서 태그를 이해할 수 있도록 자바스크립트를 이용해 태그를 만들어준다.
 ```erb
 <script>
		document.createElement('article');
		document.createElement('section');
		document.createElement('aside');
		document.createElement('nav');
		document.createElement('header');
		document.createElement('footer');
		.....
 </script>
 ```

3. HTML5 Shiv 사용하기
[[html5shiv.js다운로드]](https://github.com/aFarkas/html5shiv) -> [latest zip package] -> 압축푼 후 원하는 폴더로 복사해 사용

```erb
<!--[if lt IE 9]>
<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
<![endif]-->
```

#### 브라우저 사이의 차이를 메꾸어주는 폴리필(pollyfill)

파편화(브라우저 별로 가능한 기능이 다른 것)를 줄이고 비슷하게라도 같은 결과를 만들기 위한 방법을 **shim(심)** 또는 **fallback(폴백)**이라 부른다.
html4shiv도 shim의 일종이다.
**pollyfill**은 파편화가 생기는 브라우저에 삽입하는 자바스크립트로 브라우저를 스스로 진단해 필요한 **shim**을 넣어준다.
[[HTML5 Cross Browser Pollyfills]](https://github.com/Modernizr/wiki/HTML5-Cross-Browser-Pollyfills)
