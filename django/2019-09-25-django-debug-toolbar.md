# Django-debug-toolbar

[django-debug-toolbar](https://django-debug-toolbar.readthedocs.io/en/stable/installation.html) 를 이용하여 웹 프로젝트를 디버깅할 수 있다. 이 툴을 사용하면, 웹 브라우저에서 해당 웹 페이지에 사용된 HTTP 헤더, settings, SQL 문들, 템플릿 계층 구조 등 매우 다양한 디버깅 정보를 쉽게 파악할 수 있다.

## 설치

```bash
$ pip install django-debug-toolbar
$ pip list
Package              Version
-------------------- -------
Django               2.1.7
django-debug-toolbar 2.0
pip                  19.2.3
pytz                 2019.2
setuptools           40.6.2
```

가상 환경에서 pip를 사용하여 djnago-debug-toolbar 패키지를 설치한다.

## settings.py

설치가 완료되었으면 장고 프로젝트 `settings.py` 를 설정해준다.

```python
INSTALLED_APPS = [
  	...,
   'debug_toolbar',
]

MIDDLEWARE = [
    # ...
    'debug_toolbar.middleware.DebugToolbarMiddleware',
    # ...
]

# 디버그 모드를 확인할 IP설정
INTERNAL_IPS = ('127.0.0.1',)
```

## Urls.py

```python
from django.contrib import admin
from django.urls import path
from django.conf import settings
from django.conf.urls import include, url

urlpatterns = [
    path('admin/', admin.site.urls),
]

if settings.DEBUG:
    import debug_toolbar
    urlpatterns = [
        url(r'^__debug__/', include(debug_toolbar.urls)),
    ] + urlpatterns
```

