# KoNLPy

KoNLPy는 python 한국어 자연어 처리 도구이다.

```bash
$ pip install konlpy
```

다음 명령어로 간단하게 설치 할 수 있다.

[https://konlpy-ko.readthedocs.io/ko/v0.5.2/#](https://konlpy-ko.readthedocs.io/ko/v0.5.2/#) 공식 문서에서 사용법을 확인할 수 있다.

NLP(Natural Language Processing, 자연어 처리)는 텍스트에서 의미있는 정보를 분석, 추출하고 이해하는 일련의 기술 집합이다.

## 형태소 분석 및 품사 태깅

- **형태소 분석** : 형태소를 비롯해, 어근, 접두사/접미사, 품사 등 다양한 언어적 속성의 구조를 파악하는 것
- **품사 태깅** : 형태소의 뜻과 문맥을 고려해 그것에 마크업을 하는 일

```
아버지가방에들어가신다 -> 아버지/NNG + 가방/NNG + 에/JKM + 들어가/VV + 시/EPH + ㄴ다/EFN
```

[한국어 품사 태그 표](https://docs.google.com/spreadsheets/d/1OGAjUvalBuX-oZvZ_-9tEfYD2gQe7hTGsgUpiiBSXI8/edit#gid=0)에서 Tag를 확인할 수 있다.


- Kkma : 세종 말뭉치를 이용해 생성된 사전(꼬꼬마)
- Komoran : Java로 쓰여진 오픈소스 한글 형태소 분석기
- Hannanum : KAIST 말뭉치를 이용해 생성된 사전
- Twitter(Okt) : 오픈소스 한글 형태소 분석기
- Mecab : 세종 말뭉치로 만들어진 CSV 형태의 사전

각 tagger들의 성능은 다음과 같다.

1. 로딩 시간: 사전 로딩을 포함하여 클래스를 로딩하는 시간.

Kkma: 5.6988 secs
Komoran: 5.4866 secs
Hannanum: 0.6591 secs
Okt (previous Twitter): 1.4870 secs
Mecab: 0.0007 secs

2. 실행시간: 10만 문자의 문서를 대상으로 각 클래스의 pos 메소드를 실행하는데 소요되는 시간.

Kkma: 35.7163 secs
Komoran: 25.6008 secs
Hannanum: 8.8251 secs
Okt (previous Twitter): 2.4714 secs
Mecab: 0.2838 secs

자세한 성능분석은 [공식문서](https://konlpy-ko.readthedocs.io/ko/v0.5.2/morph/)에서 확인할 수 있다.

| 기능                                                         | tagger    |
| ------------------------------------------------------------ | --------- |
| morphs (형태소로 나누기)<br>nouns (명사로 나누기)<br>pos (형태소로 나누고, 태그까지 반환) | 공통 제공 |
| analyze(형태소 후보를 모두 반환)                             | Hannanum  |
| sentences(텍스트를 문장별로 나눔)                            | Kkma      |
| phrases(텍스트를 구문별로 나눔)                              | Okt       |



```python
from konlpy.tag import Okt
okt = Okt()      
 
#형태소 분석
print(okt.morphs(u'아이폰 기다리다 지쳐 애플공홈에서 언락폰질러버렸다 6+ 128기가실버ㅋ'))
['아이폰', '기다리다', '지쳐', '애플', '공홈', '에서', '언', '락폰', '질러', '버렸다', '6', '+', '128', '기', '가', '실버', 'ㅋ']

#명사 분석
print(okt.nouns(u'아이폰 기다리다 지쳐 애플공홈에서 언락폰질러버렸다 6+ 128기가실버ㅋ'))
['아이폰', '애플', '공홈', '락폰', '기', '실버']

#구(Phrase) 분석
print(okt.phrases(u'아이폰 기다리다 지쳐 애플공홈에서 언락폰질러버렸다 6+ 128기가실버ㅋ'))
['아이폰', '애플공홈', '언락폰', '128기', '실버', '애플', '공홈', '128']

#형태소 분석 태깅
print(okt.pos(u'아이폰 기다리다 지쳐 애플공홈에서 언락폰질러버렸다 6+ 128기가실버ㅋ'))
[('아이폰', 'Noun'), ('기다리다', 'Verb'), ('지쳐', 'Verb'), ('애플', 'Noun'), ('공홈', 'Noun'), ('에서', 'Josa'), ('언', 'Modifier'), ('락폰', 'Noun'), ('질러', 'Verb'), ('버렸다', 'Verb'), ('6', 'Number'), ('+', 'Punctuation'), ('128', 'Number'), ('기', 'Noun'), ('가', 'Josa'), ('실버', 'Noun'), ('ㅋ', 'KoreanParticle')]
```



## 참고

- [https://konlpy-ko.readthedocs.io/ko/v0.5.2/morph/](https://konlpy-ko.readthedocs.io/ko/v0.5.2/morph/)
- [https://m.blog.naver.com/PostView.nhn?blogId=myincizor&logNo=221629109172&proxyReferer=https:%2F%2Fwww.google.com%2F](https://m.blog.naver.com/PostView.nhn?blogId=myincizor&logNo=221629109172&proxyReferer=https:%2F%2Fwww.google.com%2F)