# history.scrollRestoration

`history.back()`로 이전 페이지 진입시 `window.scrollTop()` 으로 해당 위치 이벤트를 처리했을때, 스크롤위치를 브라우저에서 자동으로 옮겨가 페이지 전체가 로딩된 후 최상단으로 이동하는 이슈가 있었다.

이렇게 동작하는 이유는 크롬이 사용자가 보고 있던 스크롤 위치를 저장하고 있다가 해당 페이지에 다시 접근하면 브라우저 레벨에서 자동으로 스크롤링하기 때문이다.

이러한 경우에 `history.scrollRestoration` 속성 값을 변경해주면된다.

scrollRestoration은 히스토리 네비게이션의 스크롤 복원 기능을 명시적으로 지정할 수 있는 속성이다. 속성값은 ‘auto’와 ‘manual’이 전부이다.

```js
history.scrollRestoration = 'auto'; // default 설정값
history.scrollRestoration = 'manual'; // manual로 설정하여 scroll 위치 조정 가능
```

기본으로 `auto` 값을 가지고 있는데, 이를 `manual`로 설정하면 스크롤 위치가 정상적으로 이동하는 것을 확인할 수 있다.

## 참조페이지

- [https://developers.google.com/web/updates/2015/09/history-api-scroll-restoration](https://developers.google.com/web/updates/2015/09/history-api-scroll-restoration)