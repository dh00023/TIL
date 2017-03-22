# HTML5 + CSS3 웹 표준의 정석

## Chapter2. 텍스트 관련 태그들

### 텍스트를 덩어리(block)로 묶어 주는 태그
* `<hn></hn>` : 제목 표시하기 (h1 > h2 > .. > h6 )
* `<p> </p>` : 줄바꿈 없이 텍스트 한 줄로 표시.
* `<br>` : 줄 바꾸기
* `<hr>` : 수평 줄 넣기
* `<blockquote></blockquote>` : 인용문 넣기( 들여쓰기가 다름 )
* `<pre></pre>` : 입력하는 그대로 화면에 표시하기


### 텍스트를 한 줄로 표시하는 태그
* `<strong></strong>` : 굵게 강조하기( **중요**도를 높이고 싶다면 여러번 겹쳐 쓸 수 있음 )
* `<b></b>` : 굵게 표시하기 ( 단순히 굵게 표시 )
* `<em></em>` : 이탤릭체로 **강조**
* `<i></i>` : 이탤릭체로 표시
* `<q></q>` : 인용 내용 표시( 줄바꿈 없이 다른 내용과 한 줄로 표시되며 인용내용에 "" 로 표시된다.)
```erb
<blockquote> blockquote 인용구</blockquote>
<q>q 태그 인용구</q>
```

* `<mark></mark>` : 형광팬 효과
* `<span></span>` : 줄바꿈 없이 영역 묶기 ( 줄바꿈 없이 일부 텍스트만 묶어 스타일을 적용하려고 할  때 사용)
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

* 그 외의

| 태그 | 설명 | 예제|
|:--------:|:--------|:--------|
|`<abbr>`| 약자표시 , title 속성 함께 사용| `<abbr title="Internet of Things">IOT</abbr>`|
|`<cite>`| 웹 문서나 포스트에서 참고 내용 표시 | `<p>할 수 있다. -펜싱선수 <cite>박상영</cite></p>`|
|`<code>`| 컴퓨터 인식을 위한 소스코드 | `<pre><code> var i= 0; </code></pre>`|
|`<kbd>`| 키보드 입력이나 음성 명령같은 사용자 입력내용 | `<p>웹화면 다시 불러오기 <kbd>F5</kbd> 키를 누릅니다</p>`|
|`<small>`|부가 정보처럼 작게 표시하는 텍스트| `<p>가격 13000원 <small>부가세별도</small></p>`|
|`<sub>`| 아래 첨자| `<p>물의 화학식 <b>H<sub>2</sub>0</b>다</p>`|
|`<sup>`| 위 첨자| `<p>E = mc<sup>2</sub></p>`|
|`<s>`|취소선| `<p><s>30000원</s><strong>190000원</strong></p>`|
|`<u>`|밑줄| `<p><u>밑줄</u></p>`|


### 목록을 만드는 태그

* `<ul>`, `<li>` : 순서 없는 목록
```erb
<ul>
	<li> 목록1 </li>
	<li> 목록2 </li>
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
	* `reserved` 속성을 이용해 역순표시
```erb
<ol type="a">
	<li>리스트1</li>
    <li>리스트2</li>
</ol>
<ol type="a" start=3>
	<li>리스트3</li>
    <li>리스트4</li>
</ol>
```

* `<dl>`, `<dt>`, `<dd>` : 제목과 설명이 한쌍인 목록 만들기
```erb
<dl>
	<dt>제목</dt>
	<dd>내용</dd>
	<dd>내용</dd>
</dl>
```

* 주석 `<!-- -->`
[W3W HTML 검사기](http://validator.w3.org/)

### 표를 만드는 태그

* `<table>`, `<tr>`, `<td>`, `<th>` : 기본적인 표 만들기
	* `<table> </table>` : 표 자리 만들기
		* `border` 속성은 테두리 굵기
		* `aria-describedby` 속성은 표에 대한 설명 제공하기
	* `<tr> </tr>` : 행 만들기
	* `<td> </td>` : 셀 만들기
	* `<th> </th>` : 제목 셀
		* `colspan`, `rowspan` 속성 : 행 또는 열 합치기(`<th>`,`<td>`)
	* `<caption>`, `<figcaption>` : 표에 제목 붙이기 (주로 `<caption>`사용)


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
