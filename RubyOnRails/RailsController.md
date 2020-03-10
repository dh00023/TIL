# Rails Controller

## Strong Parameter
:대량 할당 취약성에 대한 화이트 리스트 대책 방법이다.
> 대량 할당 취약성 : 악의적인 사용자가 자신의 계정에 관리자 권한을 부여해 시스템을 조작할 위험이 있음.

```ruby
params.require(model).permit(attr, ...)
# model:모델이름
# attr : 추출을 허가할 필드 이름.
```
* `require` 메서드는 지정된 모델의 키가 존재하는지 확인 후 존재하면 해당 값들을 리턴하고, 존재하지 않으면 `ActionController::ParameterMissing` 예외가 발생한다.

* `permit`메서드는 모델에 일괄적으로 추가할 속성들을 허가하는 메서드이다. 리턴값으로 지정된 키만 포함하는 해시를 리턴한다.

```ruby
#scaffolding
def create
	@book=Book.new(book_params)
end

private

def book_params
	params.require(:book).permit(:isbn,:title,:price)
end
```
이렇게 Strong Parameters는 한꺼번에 입력할 수 있는 속성들을 필터링하므로 악의적인 사용자가 값을 임의로 넣는 것을 미연에 방지 할 수 있다.

## Filter
: 액션 메서드가 실행되기 이전과 이후에 부가 처리를 위해서 사용한다. 컨트롤러 전체에 적용된다.

### before & after filter(전,후 처리)
```ruby
before_action :method[, ...]
after_action :method[, ...]
```
### around filter(전후처리 한번에)
```ruby
around_action :method[, ...]
```
```ruby
# example
	around_action :around_logger
    
    def index
    	sleep3
        render text: 'index 액션실행'
    end
    
    private
    
    def around_logger
    	logger.debug('[Start1]'+Time.now.to_s)
        yield #액션을 실행
    	logger.debug('[Finish1]'+Time.now.to_s)
    end
end
```

### filter 적용 범위 지정
: 필터는 해당 컨트롤러 + 파생된 컨트롤러렝 적용된다.
#### only와 except 옵션( 필터 적용범위 제한)
```ruby
# example
before_action :start_logger, only: [:index, index2]
after_action :end_logger, except :index
```
`only`는 지정한 액션에만 필터를 적용, `except`옵션은 지정된 액션에 필터 적용을 제외.
> 이 옵션들은 최대한 적게 사용할 것을 권장한다. 많이 사용하게되면 코드의 가독성이 떨어지고 디버그할 때도 문제를 찾기 힘들어진다. 그러므로 컨트롤러 모든 액션에 공통적으로 적용할 수 있는 부분은 최대한 필터로 적용하고, 다른 부분은 검토해라.

#### skip_xxxxx_action (상속한 필터를 제외)
```ruby
# before, after, around로 적용된 모든 필터제거
skip_action_callback :my_logging
# 특정한 필터제거 xxxxx부분에 before,after,around중하나!
skip_before_action :my_logging
```

## Resource
: **CRUD** 할 수 있는 정보라고 생각하면 좋다.
```ruby
#routes.rb
resources :name [, ...]
resource :name [, ...]
```
`resources`는 여러개의 리소스를 관리하는 RESTful 인터페이스 생성, `resource`는 하나의 리소스를 관리하는 interface생성! 이때 차이점은 `resource`는 index액션이 정의되지 않았으므로, show,edit,delete에서 :id매개변수를 받지 않는다.

### 1. constraints(라우트 매개변수 제약조건)
`:id`의 라우트 매개변수가 포함이 되어있을때 모든 값을 전달할 수 있지만, 어떤 값이 전달될 지를 미리 알고 있다면 어느정도 제한을 걸어두는 것이 좋다.
```ruby
# {<매개변수이름> : <정규표현식>}
resources :books, constraints: {id: /[0-9]{1,2}/}
```

### 2. 제약 클래스 정의(복잡한 제약조건)
: 정규 표현식만으로 표현할 수 없는 복잡한 제약 조건을 설정하고 싶다면 제약 클래스를 사용한다.
```ruby
#TimeConstraint.rb
class TimeConstraint
	def matches?(request)
		current = Time.now
		current.hour >= 9 && current.hour < 18
	end
end
```
`matches?`메서드를 만들어주면된다. 이때 두가지 규칙을 지켜야한다.
* 매개변수로 요청정보(request 객체)를 받음
* 리턴 값으로는 라우트를 유효화 할지에 대한 true or false 리턴

```ruby
require 'TimeConstraint'

Railbook::Application.routes.draw do
	resources :books, constraint: TimeConstraint.new
end
```

### 3. format(form 매개변수제거)
```ruby
resources :books,format: false
```
URL패턴에서 format이 제거된 라우트가 생성된다.

### 4. controller & as(컨트롤러 클래스,url 헬퍼 이름수정)
```ruby
resources :users, controller: :members
# UsersController를 MembersController와 매핑
resources :reviews, as: :comments
# reviews_path를 comments_path의 이름으로 헬퍼 생성
```

### 5. namespace & scope (모듈 내부 컨트롤러 맵핑)
: 컨트롤러를 폴더로 정리하고 싶은 경우
`> rails generate controller Admin::Books`를 하면 controllers/admin폴더 아래에 books_controller가 생성된다. 이때 RESTful을 정의하려면
```ruby
namespace :admin do
	resources :books
end

# 모듈을 인식만 하고 url패턴과 헬퍼에 영향을 주고 싶지 않은경우
scope module: :admin do
	resources :books
end
```

### 6. collection & member(RESTful 인터페이스에 액션추가)
```ruby
resources :name do
	[collection do
		method Application
		...
	end]
	[member do
		method Application
		...
	end]
end
# name : 리소스 이름
# method : 적용할 HTTP 메서드(get, post, put, patch, delete)
# action : 적용할 액션
```

### 7. only  & except
: 기본적으로 생성되는 액션의 일부를 무효화 시키고 싶을ㄸ!
```
resources :users, except: [:show, :destroy]
resources :users, only: [:index, :create, :new, :update, :edit]
```

### 8. resources 중첩
: 애플리케이션 내부에서 계층 관계를 갖는 경우
```ruby
resources :books do
	resources :reviews
end
```
```ruby
resources :books do
	resources :reviews , shallow: true
end
```
`shallow`는 `:id` 매개변수를 받지 않는 액션에 :book_id 매개변수가 붙는다.