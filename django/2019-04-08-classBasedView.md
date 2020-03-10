# Class-Based View

앞선 튜토리얼에서는 `HttpResonse`, `render`를 이용하여 **함수형 뷰(Function-Based View)** 를 구현했다. 하지만 그 과정에서 코드가 반복되고, 구현이 복잡해지는 것을 볼 수 있었다. **클래스 뷰(Class-Based View)**가 함수형 뷰와 달리 어떻게 구현되고, 어떤 장점이 있는지 살펴 볼 것이다.

## Function-Based View

```python
def index(request):
    latest_question_list = Question.objects.order_by('-pub_date')[:5]
    template = loader.get_template('polls/index.html')
    
    context = {
        'latest_question_list': latest_question_list,
    }
    
    return HttpResponse(template.render(context, request))
```

가장 기초적인 구현 방법이다. 

```python
from django.shortcuts import render

def index(request):
    latest_question_list = Question.objects.order_by('-pub_date')[:5]

    context = {
        'lastest_question_list': latest_question_list,
    }

    return render(request, 'polls/index.html', context)
```

`render` 를 이용하여 구현한 방법이다. 위의 구현 방법보다는 더 간단해지는 것을 확인할 수 있다. `template` 코드 부분이 없어지고, render로 바로 전달하는 것을 볼 수 있다.



## Class-based View

### Class-Based View 사용 가이드라인

- 뷰는 간단 명료해야 한다.
- 뷰 코드의 양은 적으면 적을수록 좋다.
- 뷰 안에서 같은 코드를 반복적으로 사용하지 않는다.
- 뷰는 프레젠테이션 로직에서 관리하고 비즈니스 로직은 모델에서 처리한다. 매우 특별한 경우에만 폼에서 처리한다.
- 403, 404, 500 에러 핸들링에는 CBV를 이용하지 않고 FBV를 이용한다.
- 믹스인은 간단명료해야 한다.

### Generic Views

위의 함수형 뷰에서 반복되는 부분을 패턴화하여서 사용하기 쉽게 추상화 하였다. Generic View는 웹 개발시 자주 사용하는 기능을 장고에서 미리 제공해준다.

```python
from django.views import generic

class IndexView(generic.ListView):
    model = Question
```

위와 같이 최소한 그 뷰가 어떤 모델을 사용할 것인지만 지정해주면 generic view가 모든걸 알아서 해준다. 필요에 따라 각 뷰마다 달라지는 값을 넣어주기만 하면된다. Class-based View를 사용하면 다음과 같은 장점이 있다.

- GET, POST등 HTTP 메소드에 따른 처리 코드 작성시 코드 구조가 깔끔해진다. 가독성이 높아진다.
- 다중상속 같은 객체지향 기법을 활용해 제너릭 뷰, 믹스인 클래스 등을 사용해 코드의 재사용과 개발 생산성을 높여준다.
- 복잡한 구현을 가능하게 해준다.

하지만 클래스형 뷰가 함수형 뷰를 완전히 대체하지는 않는다. 상황에 따라 선택하여 사용하는 것이지 어느 한쪽이 더 좋다고 말하기는 어렵다.

Generic View는 `from django.views import generic` 외부 모듈 적용이 필요하며 다음과 같이 분류할 수 있다.

- Base View : 뷰 클래스를 생성하고 다른 제너릭 뷰의 부모 클래스가 되는 기본 뷰
  - View : 최상위 부모 제너릭 뷰 클래스
  - TemplateView : 주어진 템플릿으로 렌더링
  - RedirectView : 주어진 URL로 redirect
- Genreic Display View : **객체의 목록** 또는 하나의 객체 상세 정보를 보여주는 뷰
  - DetailView : 조건에 맞는 하나의 객체 출력
  - ListView : 조건에 맞는 객체 목록 출력
- Generic Edit View : **Form을 통해 객체를 생성, 수정, 삭제**하는 기능을 제공하는 뷰
  - FormView : 폼이 주어지면 해당 폼을 출력
  - CreateView : 객체를 생성하는 폼 출력
  - UpdateView : 기존 객체를 수정하는 폼 출력 
  - DeleteView : 기존 객체를 삭제하는 폼 출력 
- Generic Date View :  **날짜 기반 객체**의 연/월/일 페이지로 구분해 보여주는 뷰
  - YearArchiveView: 주어진 연도에 해당하는 객체 출력
  - MonthArchiveView: 주어진 월에 해당하는 객체 출력
  - DayArchiveView: 주어진 날짜에 해당하는 객체 출력
  - TodayArchiveView: 오늘 날짜에 해당하는 객체 출력
  - DateDetailView: 주어진 연, 월, 일 PK(또는 슬러그)에 해당하는 객체 출력

### 예제

```python
from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
# from django.template import loader
# from django.http import Http404

from .models import Question

# Create your views here.
class IndexView(generic.ListView):
	template_name = 'polls/index.html'
	context_object_name = 'latest_question_list'
	
	def get_queryset(self):
		return Question.objects.order_by('-pub_date')[:6]
  """기본 뷰(View, Template, RedirectView) 3개를 제외하고 모든 제너릭 뷰에서 사용한다. 
  디폴트는 queryset 속성을 반환한다. 
  queryset 속성이 지정되지 않은 경우 모델 매니저 클래스의 all() 메소드를 호	출해 QuerySet 객체를 생성해 반환한다."""

class DetailView(generic.DetailView):
	model = Question
	template_name = 'polls/detail.html'

class ResultsView(generic.DetailView):
	model = Question
	template_name = 'polls/results.html'

def vote(request, question_id):
	question = get_object_or_404(Question, pk = question_id)
	try:
		selected_choice = question.choice_set.get(pk=request.POST['choice'])
	except (KeyError, Choice.DoesNotExist):
		return render(request, 'polls/detail.html', {'question' : question, 'error_message':"You didn't select a choice"})
	else:
		selected_choice.votes += 1
		selected_choice.save()
		return HttpResponseRedirect(reverse('polls:results', args=(question.id,)))

```



## 참고

- [https://jwkcp.github.io/2016/11/08/python-jango-why-generic-views/](https://jwkcp.github.io/2016/11/08/python-jango-why-generic-views/)
- [https://wikidocs.net/9623](https://wikidocs.net/9623)
- [https://docs.djangoproject.com/en/2.2/topics/class-based-views/](https://docs.djangoproject.com/en/2.2/topics/class-based-views/)

