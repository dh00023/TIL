# Pandas란

Pandas Library는 데이터를 수집하고 정리하는데 최적화된 도구이며, 오픈소스이다. Pandas를 이용하면 데이터과학의 80% ~ 90% 업무를 처리할 수 있다.

데이터 분석을 위해 다양한 소스로부터 수집하는 데이터는 형태와 속성이 매우 다양하다. 서로 다른 형식을 갖는 여러 종류의 데이터를 컴퓨터가 이해할 수 있도록 동일한 형식을 갖는 구조로 통합할 필요가 있다.

Pandas Library는 여러 종류의 class와 내장 함수로 구성되어있다.

## 환경설정

Mac OS에서 pyenv, virtual-env 가상 환경에 환경설정을 할 것이다.

- virtual-env 생성 및 local 설정

```bash
$ pyenv virtualenv 3.7.1 pandas
$ pyenv local panda
```
- 관련 라이브러리들을 설치하기 이전에 pip를 upgrade해준다.

```bash
$ pip install --upgrade pip
```

- pandas : 데이터 분석용

```bash
$ pip install pandas
```

- numpy : Numerical Python의 약자로 파이썬 기반 수치 해석 라이브러리

```bash
$ pip install numpy
```

- matplotlib : 그래프나 차트 등 그래픽으로 표현하는데 사용하는 파이썬 기반 2D 시각화 도구

```bash
$ pip install matplotlib
```

- scipy : 과학용 연산(미적분, 선형대수, 행렬 연산, 방정식 계산 등)에 필요한 패키지를 모아 놓은 라이브러리

```bash
$ pip install scipy
```

- scikit-learn : 머신러닝 학습을 위한 라이브러리이다. numpy와 scipy가 설치된 상태여야한다.

```bash
$ pip install -U scikit-learn
```

- seaborn : Matplotlib을 기반으로 다양한 색상 테마와 통계용 차트 등의 기능을 추가한 시각화 패키지이다. ([Seaborn Data](https://github.com/mwaskom/seaborn-data))

```bash
$ pip install seaborn
```

```bash
$ pip list

Package         Version
--------------- ------------
cycler          0.10.0
joblib          0.14.1
kiwisolver      1.2.0
matplotlib      3.2.1
numpy           1.18.3
pandas          1.0.3
pip             20.0.2
pyparsing       2.4.7
python-dateutil 2.8.1
pytz            2019.3
scikit-learn    0.22.2.post1
scipy           1.4.1
setuptools      39.0.1
six             1.14.0
```

설치를 완료하고 후에 requirements.txt로 라이브러리 버전을 관리할 수 있다.

```bash
$ pip freeze > requirements.txt
```


### DataSet

데이터 분석과 머신러닝 공부 시에 데이터셋을 제공하는 곳을 알아두면 좋다.

- scikit-learn, seaborn 등 python 라이브러리 제공 데이터셋
- [kaggle](https://www.kaggle.com/)
- [UCI 머신러닝 저장소](https://archive.ics.uci.edu/ml/datasets.html)
- 공공 데이터
  - 해외 : WorldBank, WTO등 국제기구
  - 국내 : 공공데이터 포탈, 국가통계포털
