# Kaggle

캐글(Kaggle)은 2010년 설립된 예측모델 및 분석 대회 플랫폼이다. 기업 및 단체에서 데이터와 해결과제를 등록하면, 데이터 과학자들이 이를 해결하는 모델을 개발하고 경쟁한다. _위키피디아_

## Kaggle API

[kaggle-api](https://github.com/Kaggle/kaggle-api)를 사용해서 쉽게 데이터셋을 다운받고 제출할 수 있다.

```bash
$ pip install kaggle
```

[https://www.kaggle.com/{username}/account](https://www.kaggle.com/{username}/account)로 들어가 Create New API Token으로 API 토큰을 생성한다.

다운받은 `kaggle.json` 파일을 `~/.kaggle` 로 이동시켜준다.

보안을 위해 사용자만 read/write할 수 있는 권한을 설정할 수 있다.

```bash
$ chmod 600 ~/.kaggle/kaggle.json
```

### Command

다음과 같은 명령어를 사용할 수 있다.

```bash
kaggle competitions {list, files, download, submit, submissions, leaderboard}
kaggle datasets {list, files, download, create, version, init}
kaggle kernels {list, init, push, pull, output, status}
kaggle config {view, set, unset}
```


만약 다운받고 싶은 데이터 셋이 있으면, 해당 kaggle 페이지에서 api 명령어를 확인할 수 있다.

```bash
$ kaggle competitions download -c titanic
```

더 자세한 내용은 해당 API 문서에 자세히 나와있다.


## 참고

- [https://ko.wikipedia.org/wiki/%EC%BA%90%EA%B8%80](https://ko.wikipedia.org/wiki/%EC%BA%90%EA%B8%80)
- [https://teddylee777.github.io/kaggle/Kaggle-API-%EC%82%AC%EC%9A%A9%EB%B2%95](https://teddylee777.github.io/kaggle/Kaggle-API-%EC%82%AC%EC%9A%A9%EB%B2%95)
- [https://github.com/Kaggle/kaggle-api](https://github.com/Kaggle/kaggle-api)