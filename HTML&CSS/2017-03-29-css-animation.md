# CSS3와 애니메이션

## 변형(transform)

### 2차원 변형과 3차원 변형

2차원 변형(2D transform)은 웹 요소를 변형시킬 때 단순히 수평이나 수직으로 이동하고 회전하는 것.
3차원 변형(3D transform)은 x축과 y축에 원근감을 주는 z축을 추가해 변형시키는 것을 말한다.

### transform과 변형 함수

```
transform:변형함수;
```

```css
.photh{ transform: translate(50px, 100px); }
```

#### 2차원 변형 함수

최신 브라우저에서는 모두 지원되지만 인터넷 익스플로러 9를 비롯한 이전 브라우저는 브라우저 접두사(`-webkit`-, `-moz-`, `-ms-`, `-o-`)를 붙여야한다.

| 변형함수 | 설명 |
|--------|--------|
|`translate(tx, ty)`|지정한 크기만큼 x축과 y축으로 이동|
|`translateX(tx)`|지정한 크기만큼 x축으로 이동|
|`translateY(ty)`|지정한 크기만큼 y축으로 이동|
|`scale(sx,sy)`|지정한 크기만큼 x축과 y축으로 확대/축소|
|`scaleX(sx)`|지정한 크기만큼 x축으로 확대/축소|
|`scaleY(sy)`|지정한 크기만큼 y축으로 확대/축소|
|`rotate(각도)`|지정한 각도만큼 회전|
|`skew(ax,ay)`|지정한 각도만큼 x축과 y축으로 왜곡|
|`skewX(ax)`|지정한 각도만큼 x축으로 왜곡|
|`skewY(ay)`|지정한 각도만큼 y축으로 왜곡|

#### 3차원 변형 함수

최신 브라우저에서는 모두 지원되지만 인터넷 익스플로러 9를 비롯한 이전 브라우저는 브라우저 접두사(`-webkit`-, `-moz-`, `-ms-`, `-o-`)를 붙여야한다.

| 변형함수 | 설명 |
|--------|--------|
|`matrix3d(n,[,n])`|4*4행렬을 이용해 이동과 확대/축소,회전 등의 변환 지정|
|`translate(tx, ty, tz)`|지정한 크기만큼 x축과 y축,z축으로 이동|
|`translateZ(tz)`|지정한 크기만큼 z축으로 이동|
|`scale3d(sx, sy, sz)`|지정한 크기만큼 x축과 y축, z축으로 확대/축소한다.|
|`scaleZ(sz)`|지정한 크기만큼 z축으로 확대/축소|
|`rotate3d(rx,ry,rz,각도)`|지정한 각도만큼 회전|
|`rotateX(각도)`|지정한 각도만큼 x축으로 회전|
|`rotateY(각도)`|지정한 각도만큼 y축으로 회전|
|`rotateZ(각도)`|지정한 각도만큼 z축으로 회전|
|`perspective(길이)`|입체적으로 보일 수 있는 깊이 값을 지정|

## 변형과 관련된 속성들

- `transform-origin` : 변형 기준점 설정

축이 아닌 특정 지점을 변형의 기준으로 설정할 수 있다.

```
transform-origin: <x축> <y축> <z축> | initial | inherit;

<x축> : 길이 값, 백분율, left, center, right중에 사용
<y축> : 길이 값, 백분율, top, center, bottom 사용
<z축> : 길이 값
```

- `perspective`, `perspective-origin` : 원근감 표현하기

3차원 변형에서 사용하는 속성, 원래 위치에서 사용자가 있는 방향이나 반대방향으로 잡아당기거나 밀어내 원근감을 갖게한다.

```
perspective: <크기> | none;
```

```
perspective-origin: <x축 값> | <y축 값>;
<x축> : 길이 값, 백분율, left, center, right중에 사용
<y축> : 길이 값, 백분율, top, center, bottom 사용
기본은 50%이다.
```

- `transform-style` : 3D 변형 적용하기

부모 요소에 적용한 3D변형을 하위 요소에도 적용할 수 있다.

```
transform-style: flat | preserve-3d
```

- `backface-visibility` : 요소의 뒷면 표시하기

요소의 뒷면, 즉 반대쪽 면을 표시할 것인지를 결정

```
backface-visibility: visible | hidden
```

## 트랜지션

**트랜지션**이란 웹 요소의 배경 색이 바뀌거나 도형의 테두리가 바뀌는ㄴ 것처럼 스타일 속성이 바뀌는 것을 말한다.

- `transition-property` : 트랜지션을 적용할 속성 지정

```
transition-property: all | none | <속성이름>
```

```css
transition-property: all;
transition-property: background-color;
transition-property: width, height;
```

- `transition-duration` : 트랜지션 진행 시간 지정

```
transition-duration: <시간>
```

```css
transition-property: width, height;
transition-duration: 2s, 1s;
```

- `transition-timing-function` : 트랜지션 속도 곡선 지정하기

시작과 중간, 끝에서의 속도를 지정해 속도 곡선을 만들 수있다.

```
transition-timing-function: linear | ease | ease-in | ease-out | ease-in-out | cubic-bezier(n,n,n,n)

linear : 시작부터 끝까지 똑같은 속도로 트랜지션 진행
ease : 처음에는 천천히 시작하고 점점 빨라지다가 마지막에 천천히 끝남.(default)
ease-in : 시작을 느리게
ease-out : 끝은 느리게
ease-in-out : 시작과 끝을 느리게
cubic-bezier(n,n,n,n) : 베지에 함수를 직접 정의 (0~1사이 값)
```

- `transition-delay` : 지연 시간 설정하기

트랜지션이 두개 이상 있을 때 하나의 트랜지션이 끝나고 다음 트랜지션이 언제부터 시작할 것인지를 설정.

```
transition-delay: <시간>
(0s default)
```

- `trasition` : 트랜지션 속성 한꺼번에 표기하기

트랜지션 실행 시간이 대상별로 다르지 않고, 적용 대상이 전체이면 transition속성으로 한꺼번에 지정하는 것이 편리하다.

```
transition: <transition-property> | <transition-duration> | <transition-timing-function> | <transition-delay>
```

위의 순서대로 나열해야한다.

##### 두 개 이상의 변형 동시에 사용하기

transform 속성에 여러 개의 속성을 나열하면된다.

```css
transform: scale(2);
perspective: 120px;
transform: rotateX(180deg);
```

```css
transform: scale(2) perspective(120px) rotateX(180deg);
```

## 애니메이션

CSS3의 `animation`속성을 사용하면 자바스크립트나 플래시를 사용하지 않고도 웹 요소에 애니메이션을 추가할 수 있다.

CSS 애니메이션은 시작하고 끝나는 동안 원하는 곳 어디서든 스타일을 바꾸며 애니메이션을 정의할 수 있다는 점은 트랜지션과 다르다. 중간에 스타일이 바뀌는 지점을 keyframe(키프레임)이라 한다.

| 속성 | 설명 |
|:--------|--------|
|`@keyframes`|애니메이션이 바뀌는 지점 설정|
|`animation-delay`|애니메이션 지연 시간 지정|
|`animation-direction`|애니메이션 종료 후 처음부터 시작할지, 역방향으로 진행할지를 지정|
|`animation-duration`|애니메이션 실행 시간 설정|
|`animation-fill-mode`|애니메이션이 종료되었거나 지연되어 실행되지 않는 상태일 때 요소의 스타일 지정|
|`animation-iteration-count`|애니메이션 반복 횟수 지정|
|`animation-name`|@keyframes로 설정해 놓은 중간 상태 이름 지정|
|`animation-play-state`|애니메이션을 멈추가너 다시 시작|
|`animation-timing-function`|애니메이션의 속도 곡선 지정|
0|`animation`|하위 속성들을 한꺼번에 묶어지정|

1. `@keyframe`
```
@keyframe <이름>{
	<선택자> { <스타일> }
}
```
```css
@keyframe change-bg{
	from{
    	background-color: blue;
        border: 1px solid black;
    }
    to{
    	background-color: #a5d6ff;
        border: 1px solid blue;
        border-radius: 50%;
    }
}
```

2. 애니메이션 이름 지정
```
anymation-name: <키프레임 이름> | none
```

3. 애니메이션 실행시간 설정
```
animation-duration: <시간>
```

4. 애니메이션 방향 지정
```
animation-direction: normal | alternate
```

5. 반복 횟수 지정
```
animation-iteration-count: <숫자> | infinite
```

6. 애니메이션 속도 곡선 지정
```
animation-timing-function :  linear | ease | ease-in | ease-out | ease-in-out | cubic-bezier(n,n,n,n)
```

7. 애니메이션 관련속성 한꺼번에 표시하기
```
animation: <animation-name> | <animation-duration> | <animation-timing-function> | <animation-delay> | <animation-iteration-count> | <animation-direction>
```
나열된 속성 값 순서대로 값을 입력한다.

