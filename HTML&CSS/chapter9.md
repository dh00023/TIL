# HTML5 + CSS3 웹 표준의 정석

## Chapter9. CSS 포지셔닝

### CSS 포지셔닝과 주요 속성들

- `box-sizing` : 박스 너비 기준 정하기

```
box-sizing: content-box | border-box
```
박스 너비를 **콘텐츠 영역 너**비 값으로 할지, 박스 모델 전체 너비 값으로 사용할지 지정해주는 속성이다.

- `float` : 왼쪽이나 오른쪽으로 배치하기

```
float: left | right | none
```

`float` 속성을 사용하면 그 주변을 다른 요소가 감싼다.

- `clear` : `float`속성 해제하기

```
clear: none | left | right | both
```

`float` 속성을 이용해서 웹 페이지 요소를 왼쪽이나 오른쪽에 배치하면 그 다음에 넣는 다른 요소들에도 똑같은 속성이 전달된다. 그래서 `float` 속성이 더 이상 유용하지 않다고 알려주는 속성이다.

> Lorem Ipsum(로렘 입숨) : 임의로 본문 내용 채워 넣기
> [한글 로렘 입숨](http://guny.kr/stuff/klorem/)

- `position` : 배치 방법 지정하기

```
position: static | relative | absolute | fixed
```

| 속성 값 | 설명 |
|--------|--------|
|**static**|요소를 문서의 흐름에 맞추어 배치 - 나열한 순서대로 `float: left or right`이용해서|
|relative|이전 요소에 자연스럽게 연결해 배치하되 위치를 지정할 수 있다. - 나열한 순서대로 배치|
|absolute|문서의 흐름과 상관없이 원하는 위치를 지정해 배치 - 가장 가까운 부모 요소나 조상요소중 position이 relative인 요소를 기준으로!|
|fixed|문서의 흐름과 상관없이 지정한 위치에 고정해 배치(화면에서 요소가 잘릴 수 있다.) - 브라우저 창을 기준으로!|

- `visibility` : 요소를 보이게 하거나 보이지 않게 하기

```
visibility: visible | hidden | collapse
```

| 속성 값 | 설명 |
|--------|--------|
|**visible**|화면에 요소를 표시|
|hidden|화면에서 요소를 감춤. 하지만 크기는 그대로 유지하기 때문에 배치에 영향을 미침|
|collapse|표의 행, 열, 행 그룹, 열 그룹등에서 지정하면 서로 겹치도록 조절. 그 외의 영역에서 사용하면 `hidden`처럼 처리|

- `z-index` : 요소 쌓는 순서 정하기

```
z-index: <숫자>
```

숫자 값이 작을수록 아래에 쌓인다. `z-index`를 명시하지 않으면 맨 먼저 삽입하는요소가 `z-index:1` 값을 가진다.

### 다단으로 편집하기

- `column-width` : 단의 너비 고정하고 다단 구성하기

```
column-width: <크기> | auto
```

- `column-count` : 단의 개수 고정하고 다단 구성하기

```
column-count: <숫자> | auto
```

- `column-gap` : 단과 단 사이 여백 지정

```
column-gap: <숫자> | normal
```

- `column-rule` : 구분선의 색상, 스타일, 너비 지정

```
column-rule-color: <색상>
column-rule-style: none | hidden | dotted | dashed | solid | double | groove | ridge | inset | outset
column-rule-width: <크기> | thin | medium | thick
column-rule: <너비> | <스타일> | <색상>
```

- `break-after` : 다단 위치 지정하기

```
break-after: column(단나눔) | avoid-column(단 나누지 않음)
break-before: column | avoid-column
break-inside: column | avoid-column
```

- `column-span` : 여러 단을 하나로 합치기

```
column-span: 1 | all
```

### 표 스타일

- `caption-side` : 표 제목 위치 정하기

`caption`태그를 이용해 표 제목을 표시할 때, `caption-side`속성을 이용해 위치를 바꿀 수 있다.

```
caption-side: top | bottom
```

- `border` : 표 테두리 스타일 결정하기

`<table border="1">` 처럼 사용하면 표에 테두리를 그릴 수 있다. 이때 `border`속성을 이용해 색상, 형태, 너비를 지정할 수 있다.

- `border-collapse` : 테두리 통합, 분리하기

```
border-collapse: collapse | seperate
```

- `border-spacing` : 인접한 셀 테두리 사이 거리 지정하기

```
border-spacing: <크기>
```
여기서 크기는 px이나 em등 크기와 단위를 직접 지정한다.

- `empty-cells` : 빈 셀의 표시 여부 지정하기

```
empty-cells: show | hide
```

- `width`, `height` :  표 너비와 높이 지정하기

- `table-layout` : 콘텐츠에 맞게 셀 너비 지정하기

영문 내용은 `width`의 속성이 무시되고 한줄로 쓰여진다. 그렇기 때문에 `table-layout`을 이용해서 셀 안의 내용 양에 따라 너비를 변하게할지, 고정시킬지 결정한다.

```
table-layout: fixed | auto
```
하지만 너비를 고정시킬경우 너비보다 긴 내용은 셀 밖으로 밀려나가게된다. 셀 너비안에 내용을 표시하려면 `word-break: break-all`속성을 함께 써줘야한다. 또한, 예상치 못한 줄 바꿈이 생기면 높이 값 예측이 쉽지않기 때문에 `height: auto;`도 지정해준다.

```css
.table1 {
	border-collapse:collapse;
	width:300px;
	table-layout:fixed;
	word-break:break-all;
	height:auto;
}
```

- `text-align` : 셀 안에 텍스트 수평 정렬하기

```
text-align: left | right | center
```

- `vertical-aligin` : 셀 안에서 수직 정렬하기

```
verticla-align: top | bottom | middle
```
