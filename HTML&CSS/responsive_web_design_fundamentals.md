170201 유다시티
#  Responsive Web Design Fundamentals

컴퓨터보다 모바일을 더 많이 이용하는 세상이다. 그러므로 response design을 하지 않으면 안된다. 다양한 기기의 size별로 적용이 되도록 해야한다.

### Simulator / Emulator

Emulator는 한 시스템에서 다른 시스템을 복제한다. 그리하여 두 번째 시스템이 첫 번째 시스템을 따라 행동하는 것이다. 외부의 행동에 대해 똑같이 따라하려고 하는 이 관점은 시뮬레이션과는 정 반대이다. 왜냐하면, 시뮬레이션은 자주 내부 상태와 관련하여, 흉내내는 시스템의 추상적인 모델과 관계가 있기 때문이다. Simulation은 실제로 실행하기 어려운 실험을 간단히 행하는 모의실험을 뜻한다.

* crome Web Development : `⌘+⌥+j`

### Pixels

* Device Independent Pixels
* Hardware Pixels

Hardware Pixels / DPR  = DIP

### setting the viewport
```html
<meta name="viewport" content="width=device-width,initial=scale=1">
```
viewport를 셋팅하는 것을 잊지마라!

### CSS는 viewport가 overview되는 것을 허락한다.

```css
img, embed, object, video {
	max-width: 100%
}
```
를 설정해주는 것을 추천한다.

적어도 클릭(보여야)하는건 **48px**는 되어야한다.
```css
button {
	min-width: 48px;
	min-height: 48px;
}
```
https://www.w3.org/community/webed/wiki/CSS/Properties#Border

### Stylesheet
```html
<link rel="stylesheet" media="screen and (min-width: 500px)" href="name.css">
```
##### media
```css
@media screen and (min-width: 500px){
	body{background-color: green;}
}
```
~~@import url("no.css") only screen and (min-width: 500px);~~

import tag는 피해라!

`min-devise-width`나 `max-devise-width`의 사용을 피해라. 왜냐하면 기계의 화면의 값을 가져오는 것인데 안드로이드의 경우에는 잘못된 값을 반환하는 경우도 있다.

### Breakpoints
: the point a which your sites content will respond to provide the user with the best possible layout to consume the information.

* breakpoint를 어디에 설정해야하나요?
based on specific devices, products, brand names or anything else, will almost always result in a maintenance nigthmare.

breakpoint는 발견하는 것이다.

### Flexbox

```css
display: flex;
flex-wrap: wrap;
```
flex는 row가 기준이다.
flex-wrap: wrap은 가려지는 경우 다음줄로!

```css
header{ width: 100%; order: 1;}
.red{ width: 50%; order:2; }
```
order은 나타나는 순서를 나타낸다.

### Patterns

1. Mostly Fluid
```html
 <div class="container">
 	<div class="box dark_blue"></div>
 	<div class="box light_blue"></div>
 	<div class="box green"></div>
 	<div class="box red"></div>
 	<div class="box orange"></div>
 </div>
```
```css
.container{
	display: flex;
	flex-wrap: wrap;
}
.box{
	width: 100%;
}
@media screen and (min-width: 450px){
	.light_blue, .green{
    	width: 50%;
    }
}
@media screen and (min-width: 550px){
	.dark_blue, .light_blue,{
    	width: 50%;
    }
     .green, .red, .orange{
     	width: 33.333333%;
     }
}
@media screen and (min-width: 700px){
	.container{
		width: 700px;
		margin-left: auto;
		margin-right: auto;
	}
}
```

2. Layout Shifter
```html
<div class="container">
	<div class="box dark_blue"></div>
	<div class="container" id="container2">
		<div class="box light_blue"></div>
		<div class="box green"></div>
	</div>
	<div class="box red"></div>
</div>
```
```css
.container{
	width: 100%;
	display: flex;
	flex-wrap: wrap;
}
.box{
	width: 100%;
}
@media screen and (min-width: 500px){
	.dark_blue{
    	width: 50%;
    }
    #container2{
    	width: 50%;
    }
}
@media screen and (min-width: 600px){
	.dark_blue{
    	width: 25%;
        order: 1;
    }
    #container2{
    	width: 50%;
    }
    .red{
    	width: 25%;
        order: -1;
    }
}
```

3. Column Drop
```html
<div class="container">
	<div class="box dark_blue"></div>
	<div class="box light_blue"></div>
	<div class="box green"></div>
</div>
```
```css
.container{
	display: flex;
	flex-wrap: wrap;
}
.box{
	width: 100%;
}
@media screen and (min-width: 450px){
	.dark_blue{
    	width: 25%;
    }
    .light_blue{
    	width: 75%;
    }
}
@media screen and (min-width: 550px){
	.dark_blue, .green{
    	width: 25%;
    }
    .light_blue{
    	width: 50%;
    }
}
```

4. Off Canvas
```js
menu.addEventListener('click', function(e) {
  drawer.classList.toggle('open');
  e.stopPropagation();
});
```
```css
nav {
  width: 300px;
  position: absolute;
  /* This trasform moves the drawer off canvas. */
  -webkit-transform: translate(-300px, 0);
  transform: translate(-300px, 0);
  /* Optionally, we animate the drawer. */
  transition: transform 0.3s ease;
}
nav.open {
  -webkit-transform: translate(0, 0);
  transform: translate(0, 0);
}
@media screen and (min-width: 600px){
	nav{
 		position: relative;
 		transform: translate(0,0);
    }
    body{
    	display: flex;
    	flex-flow: row nowrap;
    }
    main{
    	width: auto;
    	flex-grow: 1;
    }
}
```

### Responsive Tables
* Hidden Column : `display: none;`은 보여지지 않게 숨기는 것.
* No More Tables : 
 ```css
       table {
        border: 1px solid #ddd;
      }
      tr:nth-child(odd) {
        background-color: #f9f9f9;
      }
      @media screen and (max-width: 500px) {
        table, thead, tbody, th, td, tr {
          display: block;
        }
        thead tr {
          position: absolute;
          top: -9999px;
          left: -9999px;
        }
        td {
          position: relative;
          padding-left: 50%;
        }
        td:before {
          position: absolute;
          left: 6px;
          content: attr(data-th);
          font-weight: bold;
        }
        td:first-of-type {
          font-weight: bold;
        }
      }
      ```
      ```css
            td {
        min-width: 75px;
        text-align: center;
      }
      th:first-of-type {
        min-width: 125px;
      }
      div {
        width: 50%;
        overflow-x: auto;
      }
      ```

### Minor BreakPoints
:fontsize, icon size과 같은 사소한 변화