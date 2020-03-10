# 모델 분리하기

```
app/
├── __init__.py
└── models.py
```

현재 프로젝트에서 모델과 관련된 부분만 살펴보면 다음과 같은 구조이다.  application과 관련된 모델을 하나의 파일(`models.py`)에 저장하고 있다.

더 직관적으로 관리하고, 쉽게 관리하기 위해서 모델을 패키지로 구성할 것이다. 우선 models.py 파일을 제거한 뒤 models 폴더를 생성해준다. 폴더 하위에 `__init__.py` 파일을 생성해준다. 그리고 필요한 모델 파일을 생성해준다.

```
app1/
    views.py
    __init__.py
    models/
        __init__.py
        model1.py
        model2.py
app2/
    views.py
    __init__.py
    models/
        __init__.py
        model3.py
        model4.py
```

그러면 다음과 같은 구조가 된다. 그 후에 `__init__.py` 파일에 아래와 같이 모델 패키지를 import 해준다.

```python
# project/app1/models/__init__.py:
from .model1 import Model1
from .model2 import Model2

# project/app2/models/__init__.py:
from .model3 import Model3
from .model4 import Model4
```

## 참고

- [https://stackoverflow.com/questions/6336664/split-models-py-into-several-files](https://stackoverflow.com/questions/6336664/split-models-py-into-several-files)

