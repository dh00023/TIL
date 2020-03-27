# HTML vs JSON

모바일 웹 페이지를 보다보면 API context-type을 `application/json`형태로 데이터를 받는 곳도 있고, `text/html` 형태로 받는 곳도 있었다.
두 개의 차이점이 궁금해져 해당 부분을 찾아보았다.

보통 필요한 것이 데이터이며, 추가적인 계산이 필요할때 application/json 타입을 사용하고,
어떤 계산도 필요하지 않으며, 보여주는 용도로 사용할떄는 HTML을 사용한다.

- text/html은 parsing하기 전까지 잘못된 부분을 찾기 힘들며, application/json은 잘못된 부분이 있으면 쉽게 찾을 수 있다.(디버깅이 용이)
- application/json은 즉시 js object로 변환되어 `obj.firstnode.childnode`로 접근할 수 있다.
- applicaton/json은 callback이 가능하나, text/html은 불가능하다.
- applcation/json보다 text/html이 조금 더 빠르다.

- **HTML은 클라이언트단에서 추가적으로 계산이 필요한 경우에는 사용하면 안된다.**
- **JSON을 페이지의 DOM tree에 포함하는 것이 전부라면 사용하지 않는 것이 좋다.**

## 참고

- [https://stackoverflow.com/questions/14946845/performance-text-html-vs-application-json](https://stackoverflow.com/questions/14946845/performance-text-html-vs-application-json)
- [https://stackoverflow.com/questions/1284381/why-is-it-a-bad-practice-to-return-generated-html-instead-of-json-or-is-it](https://stackoverflow.com/questions/1284381/why-is-it-a-bad-practice-to-return-generated-html-instead-of-json-or-is-it)
- [https://medium.com/@fagnerbrack/html-is-an-api-8508362107a3](https://medium.com/@fagnerbrack/html-is-an-api-8508362107a3)