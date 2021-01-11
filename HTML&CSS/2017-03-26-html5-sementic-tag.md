# HTML5와 Sementic 태그

시맨틱(sementic) : '의미가 통하는'이라는 뜻으로 시맨틱태그는 태그만 보고도 페이지 구조를 쉽게 이해할 수 있도록 정의된 태그를 의미

## HTML4 vs HTML5 문서

HTML4는 `div`태그로 주로 화면 구성을 하였고, 수 많은 태그들을 다시 id 속성으로 구분했다. 하지만 수천 줄이 넘는 코드에서 일일이 헤더, 메뉴, 사이드바를 찾는 것은 쉽지 않았다. 그러한 이유때문에 HTML5에서 시맨틱 태그가 등장했다.

![](http://cfile10.uf.tistory.com/image/2572233758AE854230E538)

시맨틱 태그로 작성한 소스를 보면 태그만 보고도 어느 부분이 제목이고 메뉴이고 실제 내용인지 쉽게 알 수 있다.

### 문서 구조를 위한 HTML5 시맨틱 태그

* `<header>` : 머리말 지정
	
	*  주로 페이지 맨 위쪽이나 왼쪽에 삽입한다.
	*  `<nav>`를 이용해 사이트 메뉴를 넣는다.
*  그리고 본문 중에 사용해 머리말로 쓸 수도 있다.
	*  `<header>` 내부에 `<header>` 혹은 `<footer>`가 올 수 없다.
	
* `<main>` : 주요 콘텐츠

  *  주요 콘텐츠는 문서의 핵심 주제나 애플리케이션의 핵심 가능성에 대한 부연, 직접적으로 연관된 콘텐츠로 이루어짐
  * **IE에서 지원하지 않고 있다.**
  * 한 문서에 하나의 요소만 포함 가능

* `<section>` : 주제별 콘텐츠 영역 나타내기 / 문서의 일반적인 영역을 설정 / 문서를 다른 주제로 구분 짓기위해 사용
	
	* 섹션제목(`h1`~`h6`)
	* `<section>`안에 `<section>`을 쓸 수 있다.
* 문맥 흐름 중에서 콘텐츠를 주제별로 묶을 때 사용(`article`내에서도 사용가능)
	
* `<article>` : 콘텐츠 내용 넣기 / 독립적으로 구분되거나 재사용 가능한 영역을 설정
	
	* 웹상의 실제 내용을 넣는다.
* 태그를 적용한 부분을 떼어 **독립적으로 배포하거나 재사용해도 완전한 하나의 콘텐츠가 된다면 사용**
	* ex) 블로그 글, 포럼, 기사 등
	
* `<aside>` : 본문 이외의 내용 표시
	
* 사이드바(필수 요소 아님) - 광고, 링크모음 등등
	
* `<nav>` : 문서를 연결하는 내비게이션 링크(Navigation 약자)

  * 내비게이션 메뉴뿐만 아니라 footer에 사이트 링크 모음에도 많이 사용

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

* `<address>` : 사이트 제작자 정보, 연락처 정보(주소, 이메일, 전화번호)
	
* 주로 `footer`안에 사용
	
* `<div>` : 콘텐츠를 묶어 시각적 효과를 적용할 때 사용(CSS적용)

  * 본질적으로 아무것도 나타내지 않는 콘텐츠 영역을 설정

* `<footer>` : 제작 정보와 저작권 표시

  * `header`, `section`, `article`등 다른 레이아웃 태그들을 모두 사용할 수 있음
  * `<footer>` 내부에 `<header>` 혹은 `<footer>`가 올 수 없다.

```html
<!DOCTYPE html>
<html lang="ko">
    
<head>
    <meta charset="UTF-8" >
    <meta name="author" content="정다혜">
    <meta name="description" content="정다혜 연습 예제">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">    
    <title>contents 구분 예제</title>
    <link rel="stylesheet" href="./main2.css" type="text/css">
</head>
<body>
    <header>
        <nav>
            <ul>
                <li>menu 1</li>
                <li>menu 2</li>
                <li>menu 3</li>
            </ul>
        </nav>
    </header>
    <main>
        <section>
            <h1>Section</h1>
            <article>
                <h2>Article Title</h2>
                <p>Contents</p>
            </article>
            <article>
                <h2>Article2 Title</h2>
                <p>Contents</p>
            </article>
            <article>
                <h2>Article3 Title</h2>
                <p>Contents</p>
            </article>
        </section>
        <aside>
            Aside
        </aside>    
    </main>
    <footer>
        <address>
            <a href="mailto:dev.dh0023@gmail.com">dev.dh0023@gmail.com</a>
            <a href="tel:+821012345678">010-1234-5678</a>
        </address>
    </footer>
</body>
</html>
```

```css
/* css는 부모요소부터 입력해줘야함 */

header {
    background-color: tomato;
    margin:  10px;
    padding: 20px;
}

header nav{
    
}

header nav ul {
    display: flex; /* 한줄로 나열되도록 설정*/
}

header nav ul li{
    list-style: none; /* li태그 점 제거 */
    margin: 10px;
}

main{
    display: flex;    
}


section{
    width: 70%;
    background-color: tomato;
    margin: 10px;
    padding: 10px;
    box-sizing: border-box; /* padding시에 크기가 늘어나지 않도록 border-box로 설정*/
}

section h1 {

}

article {
    background-color: yellowgreen;
    margin-bottom: 10px;
    padding: 10px;
}

article h2{

}
article p{
    
}
aside {
    width: 30%;
    background-color: tomato;
    margin: 10px;
    padding: 10px;
    box-sizing: border-box;

}

footer{
    background-color: tomato;
    margin: 10px;
    padding: 20px;
}


footer address{
    
}

footer address a{
    display: block;
}
```



## IE8 이하 버전에서는 어떻게 하나요?(시맨틱 태그를 지원하지 않음)

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

#### 브라우저 사이의 차이를 메꾸어주는 pollyfill

파편화(브라우저 별로 가능한 기능이 다른 것)를 줄이고 비슷하게라도 같은 결과를 만들기 위한 방법을 **shim(심)** 또는 **fallback(폴백)**이라 부른다.
html4shiv도 shim의 일종이다.
**pollyfill**은 파편화가 생기는 브라우저에 삽입하는 자바스크립트로 브라우저를 스스로 진단해 필요한 **shim**을 넣어준다.
[[HTML5 Cross Browser Pollyfills]](https://github.com/Modernizr/wiki/HTML5-Cross-Browser-Pollyfills)



## 참고

- [Do it! HTML5+CSS3 웹 표준의 정석](https://book.naver.com/bookdb/book_detail.nhn?bid=15975063)
- [MDN web docs](https://developer.mozilla.org/ko/)