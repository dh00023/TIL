# Customizing Admin Page

앞선 [Django Admin](./2019-03-08-admin.md) 에서 자동으로 생성된 관리자 페이지에 대해서 다뤘다. 여기서는 자동으로 생성된 관리자 페이지를 커스터마이징 해볼 것이다.



## Customize the admin form

```python
# polls/admin.py
from django.contrib import admin
from .models import Question, Choice

# Register your models here.
admin.site.register(Question)
admin.site.register(Choice)
```

다음과 같이 `admin.site.register` 으로 Question 모델을 등록하여 장고에서 디폴트 폼을 구성할 수 있다. 이때 객체 등록시 Django에 원하는 옵션을 주어 커스터마이징 할 수 있다.

### fieldsets

```python
fieldsets = [
  ('제목', {'fields': ['question_text']})
]
```

다음과 같이 `fieldsets` 을 이용하여 제목을 따로 설정할 수 있으며, 필드의 순서를 지정할 수 있다.

```python
from django.contrib import admin
from .models import Question

class QuestionAdmin(admin.ModelAdmin):
	fieldsets = [
		(None,{'fields': 'question_text'}),
		('Date information',{'fields': 'question_text'})
	]

admin.site.register(Question, QuestionAdmin)
```

### 관련 객체 추가

Question 모델과 foreign key 로 연결된 Choice를 등록 할 수있다.

```python
from django.contrib import admin
from .models import Question, Choice

class ChoiceInline(admin.TabularInline):
	model = Choice
	extra = 3

class QuestionAdmin(admin.ModelAdmin):
	fieldsets = [
		(None,{'fields': ['question_text']}),
		('Date information',{'fields': ['pub_date'],'classes' : ['collapse']})
	]
	inlines = [ChoiceInline]

admin.site.register(Question, QuestionAdmin)
```

다음과 같이 `inlines` 로 연결된 모델을 나타낼 수 있다.

## Customize the admin list

```python
class QuestionAdmin(admin.ModelAdmin):
	fieldsets = [
		(None,{'fields': ['question_text']}),
		('Date information',{'fields': ['pub_date'],'classes' : ['collapse']})
	]
	inlines = [ChoiceInline]
	list_display = ('question_text', 'pub_date', 'was_published_recently')
```

다음과 같이 `list_display` 옵션을 이용해 열로 표시 할 필드를 정할 수 있다.

```python
# models.py

from django.db import models
from django.utils import timezone

# Create your models here.
class Question(models.Model):
	question_text = models.CharField(max_length=200)
	pub_date = models.DateTimeField('date published')
	def __str__(self):
		return '%s' % (self.question_text)
	def was_published_recently(self):
		now = timezone.now()
		return now - datetime.timedelta(days=1) <= self.pub_date <= now
	was_published_recently.admin_order_field = 'pub_date'
	was_published_recently.boolean = True
	was_published_recently.short_description = 'published recently?'
```

- `.admin_order_field` 는 정렬할 기준 필드를 선택할 수 있다. 
- `.boolean` 을 True로 하는 경우에는 icon으로 결과 값이 나온다. 
- `.short_description` 은 그리드 상단에 필드 명을 수정할 수 있다.

### Filter

```python
list_filter = ['pub_date']
```

`list_filter` 는 화면 오른쪽에 필터기능을 통해서 구분하여 검색할 수 있다.

```python
search_fields = ['question_text']
```

`search_fields` 는 검색 기능을 구현할 수 있다. 내부적으로 `LIKE` 쿼리를 사용하기 때문에 검색 필드 수를 적당한 수로 제한하는 것이 좋다.

## 참고

- [공식문서](https://docs.djangoproject.com/ko/2.2/ref/contrib/admin/)

