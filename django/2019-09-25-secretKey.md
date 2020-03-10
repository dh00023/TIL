# Secret Key 관리

장고 프로젝트에서 AWS 시크릿 코드 or 장고 시크릿 키 등의 비밀 값은 프로젝트 코드에 포함되면 안된다. 이러한 값들을 별도의 `JSON` 파일로 보관하고, 해당 값들을 장고에서 불러올 것이다.

#### 프로젝트 구조

```
django_project
├── .git
├── .gitignore												
├── app
│   ├── config														# 장고프로젝트 설정 패키지
│   │   ├── __init__.py
│   │   ├── settings.py
│   │   ├── urls.py
│   │   └── wsgi.py
│   ├── db.sqlite3
│   └── manage.py
├── requirements.txt												# 설치할 pip 패키지 목록 파일
└── secrets.json													# secret값들 모아둔 JSON파일
```

#### Secrets.json 내용

```json
{
    "SECRET_KEY": "<Django secret key>"
}
```

#### Settings.py

```python
import sys
import json

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOT_DIR = os.path.dirname(BASE_DIR)
SECRETS_PATH = os.path.join(ROOT_DIR, '.config_secret/secrets.json')

# json 파일을 python 객체로 변환
secrets = json.loads(open(SECRETS_PATH).read())

# json은 dict 자료형으로 변환되므로 .items() 함수를 이용해 key와 value값을 가져온다.
# 이때 settings 모듈에 동적으로 할당한다.
for key, value in secrets.items():
    setattr(sys.modules[__name__], key, value)
```

#### .gitignore에 추가

```
# .gitignore
secrets.json
```

[python-decouple](https://pypi.org/project/python-decouple/) 모듈을 이용하여 environment varioables를 관리할 수도 있다.

## 참고 페이지

- [Django에서 비밀 값(secrets) 관리하기](https://lhy.kr/django-secrets)

