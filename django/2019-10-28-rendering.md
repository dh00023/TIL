# Client vs Server Rendering

## Client Side Rendering

클라이언트(Vue.js, React.js 등등)에서 렌더링을 한다.

첫 화면은 Server Rendering, 그 이후에 작업은 Client Rendering이된다.

SPA(Single Page Application) 방식으로 개발된다. 여기에서는 SEO 문제가 발생한다. Search Engine Optimization 검색엔진에 노출되지 않아, 페이지가 홍보되지 않는 문제가 있다.

## Server Side Rendering

서버단(여기서는 Django)에서 렌더링을 한다. Vue.js에서는 [Nuxt.js](https://ko.nuxtjs.org/)를 사용하면된다.

> Nuxt.js 
>
> SSR 방식
>
> - SEO 문제 해결 가능
> - Client + Server Rendering 방식으로 vue.js 개발할 수 있음
> - Client / Server 모두 Vue.js

첫화면은 Django Redering을 하고, 이후에는 Vue.js Rendering 하는 방식으로 해결할 수 있다.

> Rendering이란 브라우저(클라이언트)에서 화면을 그리는 과정을 말한다.
>
> - DOM + CSSOM  = Rendering Tree
> - Layout
> - Painting

DOM/CSSOM에 필요한 HTML 및 CSS를 누가 생성하느냐에 따라서 렌더링 용어가 차이가 난다.



더 정리 필요

## 참조

https://kdydesign.github.io/2019/04/10/nuxtjs-tutorial/

