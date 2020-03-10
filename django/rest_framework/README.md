# Django REST framework

[Django REST framework](https://www.django-rest-framework.org/) 공식문서와 일부 글들을 보고 정리한 내용이다. 

front-end와 back-end의 작업 효율성을 높이기 위해서는 개발영역을 완전히 구별되는 것이 이상적이며, 그러기 위해서는 <a href="./2019-04-19-RestAPI.md">REST API</a>가 필요하며, 재활용성도 높아진다.

여기서는 공식문서 tutorial을 보고 따라해보았으며, 자세한 설명은 뒤에 나온다.

### settings

```bash
$ pip install djangorestframework
```

```python
# settings.py
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'rest_framework',
]
```

설치가 완료되면 `INSTALLED_APPS` 에 추가해준다.

### 프로젝트 시작하기

```bash
$ django-admin startproject tutorial
$ cd tutorial
$ django-admin startapp quickstart

$ ./manage.py migrate
$ ./manage.py createsuperuser --email admin@example.com --username admin
```

<h3><a href="./2019-04-19-serializers.md">Serializers</a></h3>
`tutorial/quickstart` 하위에 `serializers.py` 파일을 만들어준다.

```python
from django.contrib.auth.models import User, Group
from rest_framework import serializers

class UserSerializer(serializers.HyperlinkedModelSerializer):
	class Meta:
		model = User
		fields = ['url','username','email','groups']

class GroupSerializer(serializers.HyperlinkedModelSerializer):
	class Meta:
		model = Group
		fields = ['url', 'name']
```

<h3><a href="./2019-04-22-ViewSet.md">Views</a></h3>
`tutorial/quickstart/views.py` 파일을 열어 다음과 같이 수정한다.

```python
from django.contrib.auth.models import User, Group
from rest_framework import viewsets
from quickstart.serializers import UserSerializer, GroupSerializer

class UserViewSet(viewsets.ModelViewSet):
	queryset = User.objects.all().order_by('-date_joined')
	serializer_class = UserSerializer

class GroupViewSet(viewsets.ModelViewSet):
	queryset = Group.objects.all()
	serializer_class = GroupSerializer
```

### URLs

```python
from django.contrib import admin
from django.urls import path, include
from rest_framework import routers
from quickstart import views

router = routers.DefaultRouter()
router.register(r'users', views.UserViewSet)
router.register(r'groups', views.GroupViewSet)

urlpatterns = [
    path('', include(router.urls)),
    path('api-auth/',include('rest_framework.urls',namespace='rest_framework'))
]

```

### Pagination

각 페이지마다 몇개의 게시글을 노출할지 지정할 수 있다.

```python
# tutorial/settings.py

REST_FRAMEWORK = {
    'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.PageNumberPagination',
    'PAGE_SIZE': 15
}
```

`tutorial/settings.py` 하단에 위와 같이 코드를 추가해준다.

```bash
$ ./manage.py runserver
```

을 한후 `http://localhost:8000` 으로 들어가보면 확인할 수 있다.

