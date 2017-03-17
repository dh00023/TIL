# Responsive images

image는 web에서 약 62% 차지한다. 이미지의 사이즈는 매우 다양하다. 기계가 다양한만큼 이미지 크기도 거가에 맞춰져야한다.

"images consume more than 60% of the bytes that cross the web." This isn't strictly true: images on average consume more than 60% of the bytes to open a web page, but most of the bytes that "cross the web" are for video.


## Units, Formats, Environments

Total bits = pixels X bits per pixel
less pixels * better compression = less bytes

어떻게 파일크기가 늘어날때 퀄리티를 유지할까?

화면이 줄어들때 이미지의 크기를`width: 100%`로 해줌으로써 가려지는것을 해결할 수 있다. 하지만 화면크기를 키우면 이미지의 퀄리티가 깨진다.

`max-width: 100%` 를 하면 natural width만큼 커지고 그이상은 안커진다.

* `calc()` CSS function can be used anywhere a <length>, <frequency>, <angle>, <time>, <number>, or <integer> is required. 
```css
width: calc(100% - 80px);
# 100% 너비에서 80%만큼 뺀 너비
```
연산시 반드시 사칙연산 **+**,**-**기호 양쪽에는 **공백**을 삽입해야한다.

### Landscape and Portrait
: 화면을 가로로 했을때는 괜찮은데 세로로 했을때 이미지가 가려지는 문제가 생긴다.

Did you notice how setting both the height and the width to 100vmax or 100vmin changes the image's aspect ratio? It'll compress your images to squares, so be careful if you want to maintain a different aspect ratio!
`vmin`과 `vmax`를 이용해서 화면크기에 맞게 이미지가 바뀌도록 할 수 있다.

### Raster and Vertor
* Raster image(png,jpeg)는 일반적인 카메라, 스캐너로 찍은 이미지이며, Vector 이미지(svg)는 로고와같이 일러스트레이트로 만든 이미지이다.
> 두개의 이미지를 비교해봤을때 png는 화면의 크기를 키우면 이미지가 약간 깨지는 것을 확인할 수 있다.svg는 어느 사이즈에서나 perfect하다.
>jpeg보다 svg가 사이즈도 더 작은 것을 확인할 수 있다.
>png는 최대한 피하고 , svg를 최대한 사용해라.

### Grunt & ImageMagick & ImageOptim
이미지크기와 타입을 다양화해주며, 이미지로딩을 빠르게 해준다.
http://gruntjs.com/
https://imageoptim.com/mac
http://www.imagemagick.org/script/index.php

Grunt가 완전좋아!
grunt로 pagespeed도 확인해볼 수 있다.


### Html figure tag
:figure요소는 일러스트, 다이어그램, 사진, 코드등에 주석을 다는 용도로 사용됩니다.

* 이 요소가 제거 되더라도 문서의 주된 흐름에는 큰 영향을 미치지 않습니다.
* figure요소는 figcaption 요소를 포함할 수 있으며 * figure요소안에서 맨앞이나 맨 마지막에만 올 수 있습니다. 단, figcaption요소가 필수는 아닙니다.

## Images with Markup

### Text
텍스트를 사진위에 써서 jpeg로 저장한다면, 화면의 크기가 바뀔때 글자가 깨지게된다. 하지만 텍스트를 이미지와 별도로 쓰게된다면 깨지지도 않고, 스크롤을해서 긁어 올 수도 있다. 파일 크기또한 줄어든다.(CSS를 통해서!)
하지만 CSS 효과도 load time을 신경써야한다. 모바일에서 로딩을 할 때 오래걸릴 수 있기 때문에.

https://www.smashingmagazine.com/2013/04/build-fast-loading-mobile-website/

### CSS Background images

화면크기에 따라서 이미지를 다운받도록 할 수도 있다.
```css
background-size: cover;
background-size: contain;
```
* cover로 지정하면 배경 이미지의 가로, 세로 길이 모두 엘리먼트보다 크다라는 조건하에 가능한한 배경 이미지를 작게 조정합니다. 가로/세로 비율은 유지됩니다. 따라서 배경 이미지의 크기는 엘리먼트의 크기보다 항상 크거나 같습니다. 
* contain으로 지정하면 배경 이미지의 가로, 세로 길이 모두 엘리먼트 안에 들어온다라는 조건하에 가능한한 배경 이미지를 크게 조정합니다. 가로/세로 비율은 유지됩니다. 따라서 배경 이미지의 크기는 엘리먼트의 크기보다 항상 작거나 같습니다.

### Inline vs External images
: 실제로 해보고 더 빠른것을 선택해야한다.

## Full Responsiveness

### Srcset & Sizes
```xml
<img src="small.jpg"
     srcset="large.jpg 1024w, medium.jpg 640w, small.jpg 320w"
     sizes="(min-width: 36em) 33.3vw, 100vw"
     alt="A rad wolf">
```
`<img>` 태그에 새로 srcset과 sizes 속성이 덧붙었다. 여기 예제의 srcset 속성에서는 각각 가로폭 1024px, 640px, 320px인 3개의 이미지를 쉼표로 분리된 문자열 형식으로 적었다. 이럴 경우 브라우저(srcset을 지원하는 브라우저)는 이 값을 읽어 현재의 화면 상태에 맞는 적절한 이미지를 불러오게 된다. sizes 속성도 추가할 수 있는데, 이 속성은 미디어쿼리의 중단점(breakpoint) 별로 필요한 이미지의 정보를 추가로 제공함으로써 역시 브라우저로 하여금 현재의 상태에 가장 잘 맞는 이미지를 불러오는데 도움을 주게 된다. 위 예제에서는 미디어쿼리의 중단점으로 가로폭이 36em 이상인 경우에는 33.3vw (‘viewport width’를 의미)의 이미지가 필요함을 브라우저에 알리고 있으며 뒤의 100vw는 디폴트값이다. 물론 srcset과 sizes를 지원하지 않는 브라우저에서는 기존의 src 속성이 폴백(fallback)으로 사용된다.

srcset과 sizes 속성을 사용하면 앞에서 제기한 네 가지 문제들 중 적어도 처음 두 가지 문제는 손쉽게 해결된다. 브라우저가 화면 크기에 맞춰 적절한 용량의 이미지를 불러오고 또한 고밀집도 디스플레이 화면에 대한 대응도 브라우저가 판단하여 대응하기 때문이다.

#### srcset syntax
one using `x` to differentiate between device pixel ratios (DPR), and the other using `w` to describe the image's width.

* Reacting to Device Pixel Ration
```xml
<img src="image_2x.jpg" srcset="image_2x.jpg 2x, image_1x.jpg 1x" alt="a cool image">
```
1x represents `1x` displays and `2x` represents displays with twice the pixel density, like Apple's Retina display

* Reacting to Image Width
```xml
<img src="image_200.jpg" srcset="image_200.jpg 200w, image_100.jpg 100w" alt="a cool image">
```
widthDescriptor is measured in pixels and must be an integer followed by a `w`.

#### sizes Syntax
sizes attribute to the image with a media query and a vw value. 
* ```xml
<img  src="images/great_pic_800.jpg"
      sizes="(max-width: 400px) 100vw, (min-width: 401px) 50vw"
      srcset="images/great_pic_400.jpg 400w, images/great_pic_800.jpg 800w"
      alt="great picture">
```
sizes consists of comma separated mediaQuery width pairs. sizes tells the browser early in the load process that the image will be displayed at some width when the mediaQuery is hit.
In fact, if sizes is missing, the browser defaults sizes to 100vw, meaning that it expects the image will display at the full viewport width.

### Picture

srcset/sizes 속성만으로 해결할 수 없는 문제들, 예컨대 아트 디렉션 처리나 여러 이미지 포맷 지원 등은 `<picture>` 엘리먼트로 해결할 수 있다.
```xml
<picture>
  <source media="(min-width: 40em)" 
  		srcset="big.jpg 1x, big-hd.jpg 2x">
  <source srcset="small.jpg 1x, small-hd.jpg 2x">
  <img src="fallback.jpg" alt="">
</picture>
```
<picture> 엘리먼트는 하위 요소로 `<source>` 엘리먼트를 두어 각각의 이미지 소스를 처리한다. 위 예제에서는 미디어쿼리로 min-width값이 40em 이상인 경우는 big.jpg 파일을, 그 이하인 경우는 small.jpg 파일을 각각 로드하게끔 설정되어 있다. 이 때 각각의 `<source>` 엘리먼트 내에는 srcset 속성을 추가하여 밀집도(여기서는 1x와 2x를 사용했는데, 2x는 196 DPI 이상을 일컫는다)에 따라 각기 다른 이미지 파일을 로드하게끔 설정하는데, 이 부분은 앞서의 `<img>` 태그에 붙은 srcset 속성과 동일하다.
```xml
<picture>
  <source media="(min-width: 800px)"
          sizes="80vw"
          srcset="lighthouse-landscape-640.jpg 640w,
                  lighthouse-landscape-1280.jpg 1280w,
                  lighthouse-landscape-2560.jpg 2560w">
  <img src="lighthouse-160.jpg" alt="lighthouse"
       sizes="80vw"
       srcset="lighthouse-160.jpg 160w,
               lighthouse-320.jpg 320w,
               lighthouse-640.jpg 640w,
               lighthouse-1280.jpg 1280w">
</picture>
```
이 `<picture>` 엘리먼트를 이용하면 앞서 `<img>` 태그에 붙여 사용했던 srcset/sizes 방식보다 조금 더 다양한 처리가 가능해 진다. 예를 들어, 아트디렉션(art direction) 은 다음과 같이 처리할 수 있다. 여기서는 미디어쿼리로 width값이 800px 이상인 경우(lighthouse-landscape)와 그 이하인 경우(lighthouse) 각각 다른 이미지를 사용하며 그 결과 좁은 폭의 화면에서는 넓은 폭과는 다른 모양의 이미지가 보여짐을 알 수 있다.
```xml
<picture>
  <source type="image/webp" srcset="images/butterfly.webp">
  <img src="images/butterfly.jpg" alt="a butterfly">
</picture>
```
`<picture>` 엘리먼트는 다양한 이미지 형식을 처리하는 데도 사용될 수 있다. 아래 예제를 보면 webp를 지원하는 브라우저인 경우 jpg 파일이 아닌 webp 파일을 표시하도록 하고 있다.

[참조페이지]
http://www.usefulparadigm.com/2014/11/03/processing-images-on-responsive-web/