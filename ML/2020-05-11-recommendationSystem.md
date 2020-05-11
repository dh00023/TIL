# 추천 시스템(Recommendation System)

추천이란 데이터를 통해서 사용자가 아직 소비하지 않은 아이템 중 선호할 만한 것을 예측하는 것을 말한다. 추천 시스템은 기본적으로  **콘텐츠 기반 필터링 방식(Content Based Filtering)**과 **협업 필터링 방식(Collaborative Filtering)**이 있다. 두 알고리즘의 차이는 **어느 데이터**를 사용하느냐에 따라서 구분된다.

## Content Based Filtering

![](https://socital.com/wp-content/uploads/2019/09/content-based-filtering-2.png)

Content Based Filtering은 사용자 혹은 아이템에 대한 프로필 데이터를 가지고 **사용자가 좋아했던 아이템과 비슷한 유형의 아이템을 추천하거나 비슷한 유형의 사람이 좋아하는 아이템을 추천**하는 방식이다. 

예를 들어보자면,  item-based recommedation방식은 슈퍼맨 영화에 대한 사전 분석을 통해 SF, 히어로물 등의 특징을 기록하고, 슈퍼맨을 본 사람에게 배트맨과 같이 비슷한 종류의 영화를 추천해준다.

user-based recommendation은 사용자에 대해서 성별, 연령대, 지역 등 프로필을 작성할 수 있으며, 사용자와 프로필이 비슷한 다른 사용자가 선호하는 영화를 추천해준다.

이러한 방식은 비슷한 상품을 계속해서 추천하기 때문에, 추천되는 아이템의 다양성이 떨어진다는 단점이 있다.



## Collaborative Filtering

![](https://miro.medium.com/max/1768/1*OaRdJVMD6XTNVvJbmKQ4VQ.png)

Collaborative Filtering은 프로필 데이터없이, **사용자의 과거 행동 데이터**만을 가지고 추천을 한다. 즉, 사용자가 남긴 평점 데이터를 가지고 취향이 비슷한 사람이 선호하는 아이템을 추천해준다.

이 알고리즘의 장점은 직관적이며, 데이터에 의한 결과이기 때문에 신뢰도가 높다. 하지만 그만큼 데이터에 대한 의존도가 높다보니 새로운 패턴에 대한 추천이 어려운 단점이 있다. 또한, 선호할 가능성이 있는 아이템이더라도 그 전에 아무도 선택하지 않은 아이템은 추천을 하지 않는 문제도 있다.

## Hybrid Filtering

Content Based Filtering과 Collaborative Filtering 모두 각각의 한계점이 있으므로, 이 둘을 함께 사용하는 Hybrid Filtering 기법이 등장했다.

두 가지 알고리즘을 모두 적용하고, 이의 가중 평균을 구하는 Combining Filtering 기법과 평점 데이터와 아이템 프로필을 조합하여 사용자 프로필을 만들어 추천하는 Collaboration via Content 기법이 있다.

또한, 일정 데이터가 쌓이기 전까지는 Content Based 기법을, 일정 데이터가 어느정도 쌓인 후에는 Collaborative Filtering을 사용하는 경우도 있다.



일반적으로 충분한 양의 평점 데이터가 주어진 경우에는 Collaborative Filtering이 Content Based Filtering보다 더 정확하다고 알려져있다. Collaborative Filtering은 클릭 로그를 일종의 평점으로 간주해 쇼핑몰의 상품 추천을 구현할 수 있다.



## 참고

- [https://yeomko.tistory.com/3](https://yeomko.tistory.com/3)

- [https://lsjsj92.tistory.com/563?category=853217](https://lsjsj92.tistory.com/563?category=853217)
- [https://post.naver.com/viewer/postView.nhn?volumeNo=12801167&memberNo=38946978](https://post.naver.com/viewer/postView.nhn?volumeNo=12801167&memberNo=38946978)



