# 템플릿 확장하기

개발을 하다보면 웹 페이지마다 공통적으로 들어가는 HTML 코드가 있다. 이때 공통코드를 중복해서 넣어 주는 것은 효율적이지 않으므로 Django에서는 이러한 공통 부분을 **기본 템플릿(Base Template)**으로 만들고, 각 페이지마다 필요한 코드만 작성할 수 있게 **템플릿 확장(Template Extenstion)** 기능을 제공한다.

여기서 base template의 위치는 프로젝트 최상단에 생성해준다.(모든 애플리케이션에 적용하기 위해서)

```
├── admin
├── db.sqlite3
├── manage.py
├── templates
│   └── base.html
└── toast_grid
```

```html
<!-- base.html -->
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Admin 페이지</title>
</head>
<body>
	{% block content %}
	{% endblock content %}	
</body>
</html>
```

`{% block 블럭명 %}` `{% endblock 블럭명 %}` 으로 각 웹페이지에서 변경 혹은 삽입할 영역을 지정할 수 있다. 

그리고 나서 각 html 파일에서 `base.html` 을 확장하여 사용할 때는 `{% extends %}` 확장 템플릿 태그를 사용하면된다.	

```html
{% extends "base.html" %}

{% block content %}
<!-- 내부에 따라 다른 코드 입력 -->
{% endblock content %}
```

