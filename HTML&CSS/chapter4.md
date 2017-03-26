# HTML5 + CSS3 웹 표준의 정석

## Chapter4. 폼 관련 태그들

### 폼만들기

* 폼 동작 방식
![](https://simfatic.com/forms/help/v40/form-working.jpg)

* `form`태그 : 폼만들기
```erb
<form [속성="속성 값"]>여러 폼 요소 </form>
```

| 속성 | 설명 |속성값|
|:--------|:--------|:--------|
|method|사용자가 입력한 내용들을 서버 쪽 프로그램으로 어떻게 넘겨줄지 지정|`get` : 주소 표시줄에 사용자가 입력한 내용이 그대로 드러남 <br> `post`: 사용자의 입력을 표준입력으로 넘겨줘 입력내용의 길이에 제한을 받지않고 사용자가 입력한 내용이 드러나지 않는다.|
|name|폼의 이름을 지정 (한 문서 안에 여러 개의 `<form>`있을 경우 구분하기 위해 사용)||
|action|`<form>`태그 안의 내용들을 처리해줄 서버상의 프로그램 지정||
|target|`<action>`태그에서 지정한 스크립트 파일을 현재 창이 아닌 다른 위치에 열리도록 함||

* `autocomplete` : 자동 완성 기능
	* on / off : 자동완성기능 설정(on), 끄기(off)

* `label` : 폼 요소에 레이블 붙이기
```erb
<label [속성="속성 값"]>레이블<input ....></label>
<label for="id이름">레이블</label>
<input id="id이름" [속성="속성 값"]>
```

라디오 버튼과 체크박스에서 `label`태그를 사용하면 텍스트만 클릭해도 선택이된다. 즉, 텍스트 영역까지 클릭 범위가 확장된다.

* `<fieldset>`, `<legend>` : 폼 요소 그룹으로 묶기

`<fieldset>`은 폼들을 하나의 영역으로 묶어 외곽선을 그려주고, `<legend>`는 `<fieldset>` 태그로 묶은 그룹에 제목을 붙인다.
```erb
<fieldset>
	<legend>로그인 정보</legend>
	<ul>
		<li>
			<label for="id">아이디</label>
			<input type="text" id="id">
		</li>
		<li>
			<label for="pwd">비밀번호</label>
			<input type="text" id="pwd">
		</li>
	</ul>
<fieldset>
```

### 사용자 입력을 위한 `<input>` 태그

`<input>`태그 안의 `type`속성을 이용해 로그인 버튼, 텍스트, 비밀번호 등등 을 구분한다.

* type 속성

| 속성 | 설명 |
|:--------:|:--------|
|`hidden`|사용자에게는 보이지 않는, 서버로 넘겨지는 값|
|`text`|한 줄짜리 텍스트를 입력할 수 있는 텍스트 상자|
|`search`|검색 상자|
|`tel`|전화번호 입력 필드|
|`url`|url 주소를 입력할 수 있는 필드|
|`email`|메일 주소 입력할 수 있는 필드|
|`password`|비밀번호 입력할 수 있는 필드|
|`datetime`|국제표준시(UTC)로 설정된 날짜,시간|
|`datetime-local`|사용자가 있는 지역을 기준인 날짜,시간|
|`date`|사용자 지역을 기준인 날짜(연,월,일)|
|`month`|사용자 지역 기준인 날짜(연,월)|
|`week`|사용자 지역 기준인 날짜(연,주)|
|`time`|사용자 지역 기준인 시간|
|`number`|숫자 조절 할 수 있는 화살표|
|`range`|숫자 조절할 수 있는 슬라이드 막대|
|`color`|색상 표|
|`checkbox`|2개이상 선택 가능한 체크박스|
|`radio`|1개만 선택 할 수 있는 라디오 버튼|
|`file`|파일을 첨부할 수 있는 버튼|
|`submit`|서버 전송 버튼|
|`image`|`submit`버튼 대신 사용할 이미지|
|`reset`|리셋 버튼|
|`button`|버튼|

[버전별 지원 상황](http://caniuse.com)

* `hidden` : 폼에서는 보이지 않지만 사용자가 입력을 마치고 서버로 전송할 때 함께 전송되는 요소( 사용자에게 보여 줄 필요가 없지만 관리자가 알아야 하는 것)
```erb
<input type="hidden" name="이름" value="서버로 넘길 값">
```
