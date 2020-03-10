# Intro to HTML/CSS (Udacity)

HTML은 집의 구조와 같고, CSS는 집의 디자인과 같다.

트리형태로 구조가 이루어져있다.
![](https://lh4.ggpht.com/HhgTF4192zojydoQpvvMNEbD5M-fEfEEVI3kZNsy1YVelT2D5VjrYzX7lUQIUWu_C2kgPgLzUvfdCo-bJQ=s0#w=598&h=384)

### HTML-CSS-DOM
* HTML - HyperText Markup Language - the standard markup language used to create web pages.
> tag -> elements in tree `<tag> content </tag>` 형태로 되어있다.

* CSS - Cascading Style Sheets - style sheet language used for describing the look and formatting of a document written in a markup language.

* DOM - Document Object Model - a cross-platform and language-independent convention for representing and interacting with objects in HTML (and other markup languages). The nodes of every document are organized in a tree structure, called the DOM tree.

### Boxes, Grids and Rules
모든 구조의 요소는 직사각형모양으로 되어있다.(grid)
boxes가 어떻게 구성되어있는지 찾을때는 큰부분에서 작은부분으로 찾아가라!(연필로)
boxes는 다양한 크기, 위치에 있다. 어떻게 꾸밀까?
* "Cascading" means that rules are applied not only to the elements they directly match, but also to all of those elements' child elements. However, if a child element has multiple, overlapping rules defined for it, the more specific rule takes effect.


![](https://www.chenhuijing.com/images/posts/box-model.jpg)

* margin은 box크기에 해당되지 않는다. 

#### Positioning Boxes

* flex box 
![](https://css-tricks.com/wp-content/uploads/2014/05/flex-container.svg)
![](https://css-tricks.com/wp-content/uploads/2014/05/flex-items.svg)
https://css-tricks.com/snippets/css/a-guide-to-flexbox/

1. Look for natural boxes
2. Look for repeated styles and semantic elements
3. write your html
4. appply styles(from biggest to smallest)
5. fix things

### Grid Based Design

##### CSS frameworks 
: collections of CSS classes that make page layout easy to implement
framework는 기본적인 설계의 기반이 되는 부분을 지원받는 것이며, 개발자는 그 framework를 이용해 구현해야할 컨텐츠 개발에 집중할 수 있다.

##### Responsive Web Pages
사람들이 사용하는 기계는 각각 다양하고 화면의 크기도 다양하다. 그러므로 그것을 고려해서 responsive web page를 만들어야한다. 모바일이나 테블릿은 마우스가 아닌 손가락을 이용한다는 것도 기억하고 있어야한다.

pixel로 지정할 수도 있지만 %로 지정할 수도 있다.

Having **12 columns** would allow all of the mentioned layouts.

css는 .row of 100% page width, colums of 1/12~12/12 page width를 이용해 만든다.
![](http://www.cssreflex.com/wp-content/uploads/2013/12/simple-grid1.png)

`overflow: auto;`는 자동으로 넘어간 부분을 스크롤로 나타나게 해준다.!

* Media Queries : change CSS properites depending on device, scereen size and color.


normalize.css : this will help ensure that your CSS sytles are interpreted the same across all browsers.

```html
<link rel="stylesheet" src="//normalize-css.googlecode.com/svn/trunk/normalize.css">
```

### Bootstrap

* Minified CSS Files
To use the Bootstrap files in your project just copy the css and js folders to your project folder. 
minified CSS files는 우리가 알아보기 힘들게되어있지만 파일크기가 작고, 빠름.
CSS minification does not happen automatically by default, therefore if you edit your unminified CSS file, but include the minified version in your HTML, the page will not use the updated CSS by default.


#### **grid**에서 중요한 개념.
- Rows must be placed within a .container (fixed-width) or .container-fluid (full-width) for proper alignment and padding.
- Use rows to create horizontal groups of columns.
- Content should be placed within columns, and only columns may be immediate children of rows.


> modal.js는 사진클릭하면 글이 보이는!!!! 나중에 책판매 페이지 만들때 좋겠다.
