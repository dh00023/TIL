# 텍스트 관련 태그들

## Block level element

* `<hn></hn>` : 제목 표시하기 (h1 > h2 > .. > h6 )
  
  * header 태그는 글자 크기를 줄이기 위해서 사용하면 안된다.
  * 만약 크기 조정이 필요한 경우 `font-size` css 속성을 사용해서 수정하는 것을 권장하며, h1~h6를 순차적으로 사용하는 것을 권장한다.
  * h1 태그는 1번만 사용되어야한다.
  
* `<p> </p>` : Paragaraph 줄바꿈 없이 텍스트 한 줄로 표시.

* `<br>` : 줄 바꾸기

* `<hr />` : **주제에 의한 문단의 분리**를 위해 사용한다. 

  * 대부분의 경우 수평 줄 넣기로 표시되나 의미적인 관점으로만 사용해야한다.

    ```css
    hr{
        /* 모든 선을 없앤 후 아래 혹은 위의 선만 생성하기*/
        border: none;
        border-top: 2px dashed black;
    }
    ```

* `<blockquote></blockquote>` : 인용문 넣기( 들여쓰기가 다름 )

  * cite : 인용된 정보의 URL을 추가하는 속성

  ```html
  <blockquote cite="https://ko.wikipedia.org/wiki/%EB%AC%B8%EC%9E%90_%EC%9D%B8%EC%BD%94%EB%94%A9">
    문자 인코딩영어: character encoding), 줄여서 인코딩은 사용자가 입력한 문자나 기호들을 컴퓨터가 이용할 수 있는 신호로 만드는 것을 말한다.
  </blockquote>
  ```

  

* `<pre></pre>` : 서식이 미리 지정된 텍스트를 설정한다.

  * 입력하는 그대로 화면에 표시하기
  * 텍스트의 공백과 줄바꿈을 유지해 표시할 수 있다.
  * 기본적으로 Monospace 글꼴 계열로 표시된다.
    * 모든 글자의 너비가 동일하다.

## Inline element

### Anchor

- `<a>` : 다른 URL로 연결할 수 있는 하이퍼링크 설정(Anchor)

	| 속성         | 설명                                                         |
  | :----------- | :----------------------------------------------------------- |
  | **`href`**   | 링크한 문서나 사이트 주소 입력                               |
  | **`target`** | 링크한 내용이 표시될 위치(현재 창 or 새 창) 지정             |
  | `download`   | 링크한 내용을 보여주는 것이 아닌 다운로드                    |
  | `rel`        | 현재 문서와 링크한 문서의 관계 알려줌                        |
  | `hreflang`   | 링크한 문서의 언어 지정                                      |
  | `type`       | 링크한 문서의 파일 유형 알려줌([MDN MIME type](https://developer.mozilla.org/ko/docs/Web/HTTP/Basics_of_HTTP/MIME_types)) |

- `target` 속성

- | 속성        | 설명                                                        |
  | :---------- | :---------------------------------------------------------- |
  | `_blank`    | 새 탭, 새 창에서 열림                                       |
  | **`_self`** | default값, 링크가 있는 화면에서 열림                        |
  | `_parent`   | 프레임 사용시 부모 프레임에 표시                            |
  | `_top`      | 프레임 사용시 프레임에서 벗어나 링크 내용을 전체화면에 표시 |

  ```html
  <h1>텍스트링크</h1>
  <a href="http://likelion.org">멋쟁이사자처럼 홈페이지</a>
  <h1>이미지링크</h1>
  <a href="http://likelion.org" target="_blank">
    <img src="https://avatars.githubusercontent.com/likelionkonkuk?v=2&s=100">                                                                                                                   </a>
  <a href="./images/logo.png" download>로고 다운로드</a>
  ```

* 같은 페이지 내에서 이동하기
  ```html
  <태그 id = "앵커 이름">텍스트 또는 이미지</태그>
  <a href="#앵커 이름">텍스트 또는 이미지</a>
  ```
  ```html
  <ul id="menu">
    <li><a href="#content1">메뉴1</a></li>
    <li><a href="#content2">메뉴2</a></li>
  </ul>
  <h2 id="content1">내용1</h2>
    <p><a href="#menu">[메뉴로]</a></p>
  <h2 id="content2">내용2</h2>
  ```

### 문자 표시

- `<mark></mark>` : 형광팬(하이라이팅) 효과
  * 형광팬을 사용해 관심있는 부분을 표시하는 것을 의미
  * 시각적인 효과


* `<strong></strong>` : <strong>의미의 중요성</strong>을 나타내기 위해 사용

  * 굵게 강조하기( **중요**도를 높이고 싶다면 여러번 겹쳐 쓸 수 있음 )
  
* `<b></b>` : 굵게 표시하기 ( 단순히 굵게 표시 )

  * 특별한 의미를 가지지 않음.
  * 읽기 흐름에 도움을 주는 용도로 사용
  * 다른 태그가 적합하지 않는 경우 마지막에 사용
  
* `<em></em>` : <em>단순한 의미 강조</em>

  * 중첩이 가능
  * 중첩될수록 강조 의미가 강해짐
  * 정보통신보조기기에서 구두 강조로 발음됨
  * 기본적으로 이탤릭체로 표시
  
* `<i></i>` :  `<em>`, `<strong>`, `<mark>`, `<cite>`, `<dfn>` 등에서 표현할 수 있는 적합한 의미가 아닌 경우에 사용

  * **아이콘, 특수기호**와 같이 평범한 글자와 구분하기 위해 사용
  * 기본적으로  <i>이탤릭체</i>로 표시
  * [fontawesome](https://fontawesome.com/) 에서 아이콘을 주로 사용한다.

* `<q></q>` : **짧은 인용 내용** 표시( 줄바꿈 없이 다른 내용과 한 줄로 표시되며 인용내용에 "" 로 표시된다.)


  * cite : 인용정보의 url

  ```erb
  <blockquote>긴 인용구 blockquote 인용구</blockquote>
  <q>q 태그 인용구</q>
  ```

* `<span></span>` : 본질적으로 아무의미 없이 inline 설정

	
  * 줄바꿈 없이 영역 묶기 ( 줄바꿈 없이 일부 텍스트만 묶어 스타일을 적용하려고 할  때 사용)
  
  ```erb
  <span style="color: blue;">일부 텍스트만 묶어 스타일 적용</span>
  <div style="color: red;">
    <h3>div</h3>
      <p>블록단위, 즉 단락을 통째로 묶을때 사용.</p>
  </div>
  ```
  
* `<ruby></ruby>` : 동아시아 글자 표시

* `<rt></rt>` : ruby태그안에 주석
  ```erb
  <P>루비(Ruby)는 마츠모토 유키히로(<ruby> 松本行弘 <rt>まつもとゆきひろ</rt></ruby>)가 개발한 동적 객체 지향 스크립트 프로그래밍 언어이다</p>
  ```

### 그 외

| 태그 | 설명 | 예제|
|--------|:--------|:--------|
|`<abbr>`| 약자(Abbriviation)표시 , title(전역 속성) 속성 함께 사용 | `<abbr title="Internet of Things">IOT</abbr>`|
|`<dfn>`| 용어를 정의할 때 사용(Definition) | `<p>A <dfn>The Internet</dfn> is ...</p>` |
|`<cite>`| 웹 문서나 포스트에서 참고 내용 표시<br>(책, 논문, 영화, TV 프로그램, 노래 등) | `<p>할 수 있다. -펜싱선수 <cite>박상영</cite></p>`|
|`<code>`| 컴퓨터 인식을 위한 소스코드 | `<pre><code> var i= 0; </code></pre>`|
|`<kbd>`| 키보드 입력이나 음성 명령같은 사용자 입력내용 | `<p>웹화면 다시 불러오기 <kbd>F5</kbd> 키를 누릅니다</p>`<br><p>웹화면 다시 불러오기 <kbd>F5</kbd> 키를 누릅니다</p> |
|`<small>`|부가 정보처럼 작게 표시하는 텍스트| `<p>가격 13000원 <small>부가세별도</small></p>`|
|`<sub>`| 아래 첨자| `<p>물의 화학식 <b>H<sub>2</sub>0</b>다</p>`<br><p>물의 화학식 <b>H<sub>2</sub>0</b>다</p> |
|`<sup>`| 위 첨자| `<p>E = mc<sup>2</sup></p>`<br><p>E = mc<sup>2</sup></p> |
|`<s>`|취소선| `<p><s>30000원</s><strong>190000원</strong></p>`|
|`<u>`|밑줄(underline)<br>css로 활용할 수 있으면, css로 설정하는 것을 권장<br>`<a>` 태그와 헷갈릴 수 있는 위치에서 사용하지 않도록 주의| `<p><u>밑줄</u></p>`|
|`<time>`|날짜나 시간을 나타내기 위한 목적으로 사용<br>IE에서 지원 안함| `<p>현재시간 <time dateitme="2021-01-05">January 1</time></p>`<br><p>현재시간 <time dateitme="2021-01-05">January 1</time></p> |
|`<br>`|줄바꿈 설정| `<p>다음에 줄띄우기<br>안녕</p>`<br><p>다음에 줄띄우기<br/>안녕</p> |
|`<del>`|삭제된 텍스트의 범위를 지정| `<del cite="변경사항에 대한 주소" datetime="삭제된 날짜">Delete</del>` |
|`<ins>`|새로 추가된 텍스트의 범위를 지정| `<ins cite="변경사항에 대한 주소" datetime="새로 생성된 날짜">INSERT</ins>` |


## 목록을 만드는 태그

* `<ul>`, `<li>` : 순서 없는 목록
```erb
<ul> <!-- ul display: block; -->
	<li> 목록1 </li>
	<li> 목록2 </li> <!-- li는 display: list-item; -->
  <ul>
    들여쓰기 목록
    <li> 목록1 </li>
    <li> 목록2 </li>
	</ul>
</ul>
```
> CSS의 `list-style-type`속성을 통해 불릿 수정

* `<ol>`, `<li>` : 순서 있는 목록
	
* `type` 속성을 이용해 숫자의 종류를 다양하게 조절할 수 있다.
	
	| column | column |
	|:--------:|:--------|
	|1| 숫자(기본값) |
	|a| 영문(소문자) |
	|A| 영문(대문자) |
	|i| 로마숫자(소문자) |
|I| 로마숫자(대문자) |
	
	* `start` 속성을 이용해 중간번호부터 시작 할 수 있다.
	* `reserved` 속성을 이용해 역순표시(IE 지원 불가)
	
    ```erb
    <ol type="a" reserved> <!-- ol display: block; -->
      <li>리스트1</li>
      <li>리스트2</li>
    </ol>
    <ol type="a" start=3>
      <li>리스트3</li>
      <li>리스트4</li>
    </ol>
    ```

* `<li>` 태그에 value를 지정하면 새로운 값부터 다시 시작한다.

	```html
  <ol type="1">
    <li value="3">리스트1</li>
    <li>리스트2</li>
    <ol type="a" start=3>
      <li>리스트3</li>
      <li>리스트4</li>
    </ol>
    <li value="10">리스트5</li>
    <li>리스트6</li>
  </ol>
  ```

* `<dl>`, `<dt>`, `<dd>` : 제목과 설명이 한쌍인 목록 만들기

  ```erb
  <!-- dt(용어)와 dd(정의) dl(쌍들의 영역)-->
  <dl>
  	<dt>제목</dt>
  	<dd>내용</dd>
  	<dd>내용</dd>
  </dl>
  ```

  * `<dl>` 태그는  `<dt>`, `<dd>` 만 포함하고 있을 수 있다.

  * Key/Value 형태를 표시할 때 유용하다.

  * `<dl>` 태그 내에는 `<div>` 등 다른 태그가 올 수 없어 제한적인 부분이 많다. 그래서 `<ul>` / `<ol>` 태그로 대체하여 사용하는 경우가 많다.

    ```erb
    <dl>
      <!-- dl 내부에는 div 태그가 올 수 없어 많이 사용되지 않는다. ul/ol로 대체가 많이된다.-->
      <dt>Coffee</dt>
      <dd>Coffee is a brewed drink prepared from ...</dd>
      <dt>Milk</dt>
      <dd>Milk is nutrient-rich, white liquid ...</dd>
    </dl>
    <ul>
      <li>
        <dfn>Coffee</dfn> <!-- definition 약어 태그-->
        <p>Coffee is a brewed drink prepared from ...</p>
      </li>
    
      <li>
        <dfn>Milk</dfn> <!-- definition 약어 태그-->
        <p>Milk is nutrient-rich, white liquid ...</p>
      </li>
    </ul>
    ```

* 주석 `<!-- -->`

## 표를 만드는 태그

* `<table>`, `<tr>`, `<td>`, `<th>` : 기본적인 표 만들기
  * `<table> </table>` : 표 자리 만들기
  	
  	* `border` 속성은 테두리 굵기
  	* `aria-describedby` 속성은 표에 대한 설명 제공하기
  	
  * `<tr> </tr>` : **행** 만들기

  * `<th> </th>` : 헤더(머리글 칸)

    | 속성    | 의미                                           | 값                                                           |
    | ------- | ---------------------------------------------- | ------------------------------------------------------------ |
    | abbr    | 열에 대한 간단한 설명                          |                                                              |
    | headers | 관련된 하나 이상의 다른 머리글 칸 `id` 속성 값 |                                                              |
    | colspan | 확장(병합)하려는 열의 수                       | default : 1                                                  |
    | rowspan | 확장(병합)하려는 행의 수                       | default : 1                                                  |
    | scope   | 자신이 누구의 '헤더 칸'인지 명시               | `col` : 자신의 열<br>`colgroup` : 모든 열<br>`row` : 자신의 행<br>`rowgroup` : 모든 행<br>`auto` (defulat) |

  * `<td> </td>` : **셀** 만들기
    
      * `headers`, `colspan`, `rowspan`

```css
/* 표를 만들기 위해 사용하는 것이므로, 아래 display는 별도로 수정해서 쓸 일이 없다.*/

table { display: table; } /* block과 매우 유사 */
tr { display: table-row; }
th, td { display: table-cell; }
```

- `<caption>` :  표에 제목 설정
  - `<table>` 태그 바로 다음에 작성해야함
  - `<table>` 태그 당 하나의 `<caption>` 만 사용가능

```css
table { display: table-caption;}
```

```erb
<p id="summary">표에 대한 설명</p>
<table border="1" aria-describedby="summary">
	<caption>
		<strong>제목</strong>
		<p>caption으로 여러줄 꾸밀 수도 있어</p>
	</caption>
	<tr>
		<th>이름</th>
		<td></td>
		<th>연락처</th>
		<td></td>
	</tr>
	<tr>
		<th>주소</th>
		<td colspan="3"></td>
	</tr>
	<tr>
		<th>자기소개</th>
		<td colspan="3"></td>
	</tr>
</table>
```
<table border="1">
	<caption>
		<strong>제목</strong>
		<p>caption으로 여러줄 꾸밀 수도 있어</p>
	</caption>
	<tr>
		<th>이름</th>
		<td></td>
		<th>연락처</th>
		<td></td>
	</tr>
	<tr>
		<th>주소</th>
		<td colspan="3"></td>
	</tr>
	<tr>
		<th>자기소개</th>
		<td colspan="3"></td>
	</tr>
</table>

```erb
<figure>
	<figcaption>
		<p>figcaption이용한 제목</p>
	</figcaption>
	<table border="1">
		<tr>
			<th>이름</th>
			<td></td>
			<th>연락처</th>
			<td></td>
		</tr>
		<tr>
			<th>주소</th>
			<td colspan="3"></td>
		</tr>
		<tr>
			<th>자기소개</th>
			<td colspan="3"></td>
		</tr>
	</table>
</figure>
```

<figure>
	<figcaption>
		<p>figcaption이용한 제목</p>
	</figcaption>
	<table border="1">
		<tr>
			<th>이름</th>
			<td></td>
			<th>연락처</th>
			<td></td>
		</tr>
		<tr>
			<th>주소</th>
			<td colspan="3"></td>
		</tr>
		<tr>
			<th>자기소개</th>
			<td colspan="3"></td>
		</tr>
	</table>
</figure>


* `<thead>` - 머리글, `<tbody>`-본문, `<tfoot>`-바닥글: 표 구조 정의하기
  * 기본적으로 테이블의 레이아웃에 영향을 주지 않는다.
  ```css
  thead { display: table-thead-group; }
  tbody { display: table-tbody-group; }
  tfoot { display: table-tfoot-group; }
  ```

* `<col>` : 한 열에 있는 모든 셀에 같은 스타일 적용(닫는 태그 없음)

* `<colgroup>` : 여러 열을 묶어 스타일 적용 할 수 있다. **묶는 열의 개수**만큼 `<col>`태그를 넣으면된다.
  **`<colgroup>` 와 `<col>`는 `<caption>`태그 뒤 `<tr>`, `<td>`태그 이전에 사용해야한다.**

  | 속성 | 의미            | 값         |
  | ---- | --------------- | ---------- |
  | span | 연결되는 열의수 | defualt(1) |

  
```css
colgroup { display: table-column-group; }
col { display: table-column; }
```



```erb
<table border="1">
	<caption>colgroup연습</caption>
	<colgroup>
		<col>
		<col span="2" style="background-color: blue;">
		<col style="background-color: yellow;">
	</colgroup>
	<tr>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
</table>
```
<table border="1">
	<caption>colgroup연습</caption>
	<colgroup>
		<col>
		<col span="2" style="background-color: blue;">
		<col style="background-color: yellow;">
	</colgroup>
	<tr>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
</table>


## 참고

- [Do it! HTML5+CSS3 웹 표준의 정석](https://book.naver.com/bookdb/book_detail.nhn?bid=15975063)
- [HEROPY Tech - 한눈에 보는 HTML 요소 총정리](https://heropy.blog/2019/05/26/html-elements/)
- [MDN web docs](https://developer.mozilla.org/ko/)