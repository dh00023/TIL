# Serializers

**serializers** 는 queryset과 모델 인스턴스와 같은 복잡한 데이터를 `JSON`, `XML` 또는 다른 컨텐츠 유형으로 쉽게 렌더링할 수 있는 **python 기본 데이터 유형으로 변환**해준다. 또한 **deserialization** 을 제공하여, 들어오는 데이터의 유효성을 처음 확인한 후에 구문 분석이 된 데이터를 복합 형식으로 다시 변환할 수 있다.

REST 프레임워크의 **serializers** 는 Django의 `Form`, `modelForm` 클래스와 매우 유사하게 작동한다. **serializers** 는 `ModelSerializer`, `Serializer` 클래스를 제공한다.

사용전에 `djangorestframework` 가 설치되어있는지 확인해야한다.

```bash
$ pip list
Package             Version
------------------- -------
Django              2.1.7  
djangorestframework 3.9.2  
pip                 19.0.3 
pytz                2018.9 
setuptools          40.6.2            
```

## Serialzers 선언

간단한 예를들기 위해서 객체 한개를 생성한다.

```python
# models.py
from django.db import models
from datetime import datetime

# Create your models here.
class Comment(models.Model):
	email = models.CharField(max_length=100,blank=False)
	content = models.TextField()
	created_at = models.DateTimeField(default=datetime.now)
```

```c
$ ./manage.py shell
```



```python
>>> from quickstart.models import Comment
>>> from datetime import datetime
>>> c=Comment(email="test@test.com", content="testsetstsetset")
>>> c.save()
>>> Comment.objects.all()
<QuerySet [<Comment: Comment object (1)>, <Comment: Comment object (2)>]>
>>>
```

`comment` 객체에 해당하는 데이터를 serializer, deserializer화 할 수 있는 serializer를 선언한다.

```python
# app프로젝트에 serializers.py 추가
from rest_framework import serializers

class CommentSerializer(serializers.Serializer):
    email = serializers.EmailField()
    content = serializers.CharField(max_length=200)
    created = serializers.DateTimeField()
```



## Serializing Objects

생성한 `Serializer` 클래스를 사용하여 해당 객체를 serializing할 수 있다.

```python
>>> from quickstart.serializers import CommentSerializer
>>> c = Comment.objects.get(id=1)
>>> serializer = CommentSerializer(c)
>>> serializer.data
{'email': 'test@test.com', 'content': 'testsetstsetset', 'created_at': '2019-10-08T07:28:15.082464Z'}
```

이 시점에서는 모델 인스턴스를 파이썬 기본 데이터 유형으로 변환한 것이다.

JSON 데이터로 변환하기 위해서는 `JSONRenderer`를 이용해 json으로 바꿔준다.

```python
>>> from rest_framework.renderers import JSONRenderer
>>> json = JSONRenderer().render(serializer.data)
>>> json
b'{"email":"test@test.com","content":"testsetstsetset","created_at":"2019-10-08T07:28:15.082464Z"}'
```

## Deserializing Objects

serializing과 유사하다. 우선 json데이터를 파이썬 데이터 형식으로 parsing한 후에 기본 데이터를 검증된 데이터로 복원한다.

```python
>>> from django.utils.six import BytesIO
>>> from rest_framework.parsers import JSONParser
>>> stream = BytesIO(json)
>>> data = JSONParser().parse(stream)
>>> data
{'email': 'test@test.com', 'content': 'testsetstsetset', 'created_at': '2019-10-08T07:28:15.082464Z'}
```

```python
>>> serializer = CommentSerializer(data=data)
>>> serializer.is_valid()
True
>>> serializer.validated_data
OrderedDict([('email', 'test@test.com'), ('content', 'testsetstsetset'), ('created_at', datetime.datetime(2019, 10, 8, 7, 28, 15, 82464, tzinfo=<UTC>))])
```

## Return Instance

완전한 객체 인스턴스를 반환하기 위해서는 `create()`, `update()` 메소드를 구현해서 object instance 반환이 가능하다.

```python
from rest_framework import serializers

class CommentSerializer(serializers.Serializer):
    email = serializers.EmailField()
    content = serializers.CharField(max_length=200)
    created = serializers.DateTimeField()
    
    def create(self, validated_data):
      return Comment(**validated_data)
    
    def update(self, instance, validated_data):
      instance.email = validated_data.get('email',instance.email)
      instance.content = validated_data.get('content', instance.content)
      instance.created = validated_data.get('created', instance.created)
      return instance
```

 객체 인스턴스가 모델과 일치하는 경우에는 아래와 같이 객체를 데이터베이스에 저장되도록 해야한다. 

```python
from rest_framework import serializers

class CommentSerializer(serializers.Serializer):
    email = serializers.EmailField()
    content = serializers.CharField(max_length=200)
    created = serializers.DateTimeField()
    
    # 모델 객체와 일치하는 경우
	  def create(self, validated_data):
        return Comment.objects.create(**validated_data)

  	def update(self, instance, validated_data):
        instance.email = validated_data.get('email', instance.email)
        instance.content = validated_data.get('content', instance.content)
        instance.created = validated_data.get('created', instance.created)
        instance.save()
        return instance
```

데이터는 deserializing할 때 `.save()`를 호출하여 유효성이 검사된 데이터를 기반으로 객체 인스턴스를 반환할 수 있다.

```python
>>> deserializer = CommentSerializer(data=serializer.data)
>>> comment = deserializer.save()
>>> comment
<Comment: Comment object (3)>
```

 여기서 `save()`는 instance가 존재하면 update를 존재하지않으면 create를 해준다.

```python
# .save() will create a new instance.
serializer = CommentSerializer(data=data)

# .save() will update the existing `comment` instance.
serializer = CommentSerializer(comment, data=data)
```

인스턴스를 저장하는 시점에 뷰 코드가 데이터를 추가할 수 있어야하며, 이 추가 데이터에는 다른 정보가 포함될 수 있다.

```python
>>> serializer.save(writer=request.user)
```

추가된 데이터는 `.create()` 혹은 `.update()`가 호출될 때 validated_data에 포함된다.

## Validation

데이터를 deserializer할 때 유효성이 검증된 데이터에 접근하기 전에 `is_valid()` 를 호출하거나 객체 인스턴스를 저장해야한다.

```python
>>> deserializer = CommentSerializer(data={'email':'admin@test.com', 'content':'This is test'})
>>> deserializer.save()
Traceback (most recent call last):
  File "<console>", line 1, in <module>
  File "/Users/jeongdaye/.pyenv/versions/restful/lib/python3.7/site-packages/rest_framework/serializers.py", line 179, in save
    'You must call `.is_valid()` before calling `.save()`.'
AssertionError: You must call `.is_valid()` before calling `.save()`.
>>> deserializer.is_valid()
False
>>> deserializer.errors
{'created_at': [ErrorDetail(string='This field is required.', code='required')]}
```

만약에 `is_valid()`가 False라면, `.errors()`를 통해서 결과 오류메세지를 확인할 수 있다.

```python
>>> deserializer.is_valid(raise_exception=True)
Traceback (most recent call last):
  File "<console>", line 1, in <module>
  File "/Users/jeongdaye/.pyenv/versions/restful/lib/python3.7/site-packages/rest_framework/serializers.py", line 243, in is_valid
    raise ValidationError(self.errors)
rest_framework.exceptions.ValidationError: {'created_at': [ErrorDetail(string='This field is required.', code='required')]}
```

`raise_exception=True` 플래그를 사용해 `serializers.validationError` 예외를 발생시킬 수 있다.

### Field 레벨 검증

#### validate_field

serializer 서브 클래스에 `.validate_<field_name>` 메소드를 추가해 custom field 유효성 검증을 지정할 수 있다.

```python
import re 
emailRegex = '^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$'

class CommentSerializer(serializers.Serializer):
	email = serializers.CharField()
	content = serializers.CharField()
	created_at = serializers.DateTimeField()

	def validate_email(self, value):
		if(re.search(eamilRegex, value)):
			return value
		else:
			raise serializers.ValidationError("이메일 형식이 잘못되었습니다.")
```

```python
>>> from quickstart.serializers import CommentSerializer
>>> from datetime import datetime
>>> serializer = CommentSerializer(data={'email':'asdfsdaf', 'content':'asdfasdfasdfasf', 'created_at': datetime.now()})
>>> serializer.is_valid()
False
>>> serializer.errors
{'email': [ErrorDetail(string='이메일 형식이 잘못되었습니다.', code='invalid')]}
```

#### validate

여러 필드에 대한 유효성 검사를 하려면 `.validate()` 메서드를 추가하면된다. 이 메서드는 필드값의 dict 자료형을 단일 인수로 취한다.

```python
class CommentSerializer(serializers.Serializer):
	email = serializers.CharField()
	content = serializers.CharField()
	created_at = serializers.DateTimeField()

	def validate(self, data):
		if (len(data['content']) < 10) & (data['created_at'] < timezone.now()):
			raise serializers.ValidationError("error")
		return data
```

```python
>>> from quickstart.serializers import CommentSerializer
>>> from datetime import datetime
>>> serializer = CommentSerializer(data={'email':'asdfsdaf', 'content':'asdfasdfasdfasf', 'created_at': datetime.now()})
>>> serializer.is_valid()
True
>>> serializer = CommentSerializer(data={'email':'test@test.com', 'content':'asf', 'created_at': datetime.now()})
>>> serializer.is_valid()
False
>>> serializer.errors
{'non_field_errors': [ErrorDetail(string='error', code='invalid')]}
```

#### validators

Serializer의 개별필드에 validators를 통해 유효성 검사를 할 수 있다.

```python
from rest_framework import serializers
import re

emailRegex = '^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$'

def email_check(value):
	if(re.search(emailRegex, value)):
		return value
	else:
		raise serializers.ValidationError("이메일 형식이 잘못되었습니다.")

class CommentSerializer(serializers.Serializer):
	email = serializers.CharField(validators=[email_check])
	content = serializers.CharField()
	created_at = serializers.DateTimeField()
```

```python
>>> from quickstart.serializers import CommentSerializer
>>> from datetime import datetime
>>> serializer = CommentSerializer(data={'email':'asdfsdaf', 'content':'asdfasdfasdfasf', 'created_at': datetime.now()})
>>> serializer.is_valid()
False
>>> serializer.errors
{'email': [ErrorDetail(string='이메일 형식이 잘못되었습니다.', code='invalid')]}
```

## 	ModelSerializer

`ModelSerializer` 클래스는 모델 필드가 포함된 Serailzer 클래스를 간단하게 만들 수 있다.

- 모델을 기반으로 일련의 필드가 자동으로 생성
- `unique_together validator` 와 같은 serializer에 대한 validator를 자동 생성
- `.create()`와 `.update()`의 간단한 기본 구현을 포함

```python
from rest_framework import serializers

class CommentSerializer(serializers.ModelSerializer):
  class Meta:
      model = Comment
      fields = ('email','content','created_at')
```

만약 전체 필드를 포함하고 싶다면 `__all__` 으로 속성을 설정하면된다.

```python
from rest_framework import serializers

class CommentSerializer(serializers.ModelSerializer):
  class Meta:
      model = Comment
      fields = '__all__'
```

```python
>>> from quickstart.serializers import CommentSerializer
>>> serializer = CommentSerializer()
>>> print(repr(serializer))
CommentSerializer():
    id = IntegerField(label='ID', read_only=True)
    email = CharField(max_length=100)
    content = CharField(style={'base_template': 'textarea.html'})
    created_at = DateTimeField(required=False)
```

`exclude` 속성으로 제외하고 싶은 필드만 설정할 수도 있다.

```python
from rest_framework import serializers

class CommentSerializer(serializers.ModelSerializer):
  class Meta:
      model = Comment
      exclude = ('email','content','created')
```

## HyperlinkedModelSerializer

`HyperlinkedModelSerializer` 클래스는 **기본 키가 아닌 관계를 나타내기 위해 하이퍼링크를 사용한다**는 점을 제외하고는 `ModelSerialzer` 클래스와 유사하다. 기본적으로 기본 키 필드 대신 `url` 필드가 포함된다.

```python
class CommentSerializer(serializers.HyperlinkedModelSerializer):
	class Meta:
		model = Comment
		fields = ('url','id','email', 'content', 'created_at')
```

```python
>>> from quickstart.serializers import CommentSerializer
>>> serializer = CommentSerializer()
>>> print(repr(serializer))
CommentSerializer():
    url = HyperlinkedIdentityField(view_name='comment-detail')
    id = IntegerField(label='ID', read_only=True)
    email = CharField(max_length=100)
    content = CharField(style={'base_template': 'textarea.html'})
    created_at = DateTimeField(required=False)
```

url field는 HyperlinkedIdentityField를 사용한다.

`HyperlinkedModelSerializer` 클래스를 인스턴스화 할때는 현재 `request` 를 serializer 컨텍스트에 포함해야한다.

```python
serializer = AccountSerializer(queryset, context={'request': request})
```

이렇게 전달하면 정규화된 URL을 사용한다.

```
http://api.example.com/accounts/1/
```

만약 상대 URL을 사용하려면 `{'request': None}` 을 명시적으로 전달하면된다.

```
/accounts/1
```

### How hyperlinked views are determined

모델인스턴스에 하이퍼링크하기 위해 어떤 뷰를 사용했는지 알려줘야한다. 기본적으로 `{model_name} -detail` 스타일과 view 이름이 일치해야하며, `pk` 키워드 인수로 인스턴스를 찾는다. 만약 따로 지정해주고 싶다면 `extra_kwargs` 설정에서 `view_name` 또는 `lookup_field` 옵션을 설정하면된다.

```python
class AccountSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Account
        fields = ('account_url', 'account_name', 'users', 'created')
        extra_kwargs = {
            'url': {'view_name': 'accounts', 'lookup_field': 'account_name'},
            'users': {'lookup_field': 'username'}
        }
```

또는 serializer에서 필드를 명시적으로 설정할 수 있다.

```python
class AccountSerializer(serializers.HyperlinkedModelSerializer):
    url = serializers.HyperlinkedIdentityField(
        view_name='accounts',
        lookup_field='slug'
    )
    users = serializers.HyperlinkedRelatedField(
        view_name='user-detail',
        lookup_field='username',
        many=True,
        read_only=True
    )

    class Meta:
        model = Account
        fields = ('url', 'account_name', 'users', 'created')
```



## 참고링크

- [https://kimdoky.github.io/django/2018/07/11/drf-Serializers.html](https://kimdoky.github.io/django/2018/07/11/drf-Serializers.html)

- [Django RestFramework - serializers](https://kimdoky.github.io/django/2018/07/11/drf-Serializers/)

  