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

- requirement.txt (공부를 하면서 사용하게 될 라이브러리)

```txt
pandas==0.23.4
numpy==1.15.4
matplotlib==3.0.2
scipy==1.1.0
scikit-learn==0.20.1
xlrd==1.2.0
beautifulsoup4==4.6.3
googlemaps==2.5.1
seaborn==0.9.0
folium==0.7.0
```

```bash
$ pip install --upgrade pip
$ pip install -r requirements.txt
```

