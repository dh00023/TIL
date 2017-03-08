# Scaffold
scaffolding이란 '기반'이라는 의미로, 기본 기능을 미리 구현한 애플리케이션의 골격(기반)을 생성하기 위한 기능

### 1. rails project 생성
```vim
rails new learn_project
```
### 2. scaffold 생성
```vim
rails g scaffold name field:type [∙∙∙] [options] 
#name : 모델이름
#field : 필드 이름
#type : 자료형
#options :동작옵션
```
```vim
invoke  active_record
create    db/migrate/20170123090643_create_posts.rb
create    app/models/post.rb
invoke    test_unit
create      test/models/post_test.rb
create      test/fixtures/posts.yml
invoke  resource_route
route    resources :posts
invoke  scaffold_controller
create    app/controllers/posts_controller.rb
invoke    erb
create      app/views/posts
create      app/views/posts/index.html.erb
create      app/views/posts/edit.html.erb
create      app/views/posts/show.html.erb
create      app/views/posts/new.html.erb
create      app/views/posts/_form.html.erb
invoke    test_unit
create      test/controllers/posts_controller_test.rb
invoke    helper
create      app/helpers/posts_helper.rb
invoke      test_unit
invoke    jbuilder
create      app/views/posts/index.json.jbuilder
create      app/views/posts/show.json.jbuilder
create      app/views/posts/_post.json.jbuilder
invoke  assets
invoke    coffee
create      app/assets/javascripts/posts.coffee
invoke    scss
create      app/assets/stylesheets/posts.scss
invoke  scss
create    app/assets/stylesheets/scaffolds.scss
```
scaffold명령어를 통해서 자동으로 생성된 파일들 이다. 이 중에 posts_controller.rb , route, 각종 view파일들을 살펴 볼 것이다.


## RESTful
#### 1. HTTP란 무엇인가?
* **HTTP**란 **H**yper**T**ext **T**ransport **P**rotocol의 약자로 웹서버와 클라이언트간의 문서를 교환하기 위해 사용되는 프로토콜이다.

* World Wide Web( WWW )의 분산되어 있는 Server와 Client 간에 Hypertext를 이용한 정보교환이 가능하도록 하는 통신 규약이다.
 	> **하이퍼텍스트**는 문서 중간중간에 특정 키워드를 두고 문자나 그림을 상호 유기적으로 결합하여 연결시킴으로써, 서로 다른 문서라 할지라도 하나의 문서인 것처럼 보이면서 참조하기 쉽도록 하는 방식을 의미한다.

	> 인터넷 주소를 지정할 때 'http://www....' 와 같이 하는 것은 www로 시작되는 인터넷 주소에서 하이퍼텍스트 문서의 교환을 http 통신규약으로 처리하라는 뜻이다.

* http의 첫번째 버전은 인터넷을 통하여 가공되지 않은 데이터를 전송하기 위한 단순한 프로토콜이었으나, 데이터에 대한 전송과 요구·응답에 대한 수정 등 가공된 정보를 포함하는 프로토콜로 개선되었다.

#### 2. HTTP method에는 어떤것이 있고 왜 있는가?

##### GET
 1. URL에 해당하는 자료의 전송을 요청한다.
 2. 데이터가 URL에 노출된다.
 3. 인코딩/디코딩의 과정이 없기 때문에 POST보다 빠르다.
 4. URL의 길이 제약으로 인해 많은 데이터 전송은 무리이다.

##### POST
 1. 서버가 처리할 수 있는 자료를 보낸다.
 2. 데이터는 HTTP Boby에 숨겨서 서버로 전송한다.
 3. GET으로 보낼수 없는 자료를 전송할때 사용 가능하다.

##### HEAD
 1. GET과 같은 요청이지만, 웹 서버에서 헤더 정보 이외에는 어떤 데이터도 보내지 않는다.
 2. 웹 서버의 다운 여부 점검(Health Check)이나 웹 서버 정보(버전 등)등을 얻기 위해 사용될 수 있다.

##### OPTIONS
 1. 서버가 특정 URL에 대해 어떠한 HTTP Method를 지원하는지 묻는다.

##### PUT
 1. 해당 URL에 자료를 저장한다.(POST와 유사한 전송 구조를 가지기 때문에 헤더 이외에 메시지(데이터)가 함께 전송된다.)
 2. 원격지 서버에 지정한 콘텐츠를 저장하기 위해 사용되며 홈페이지 변조에 많이 악용되고 있다. 

##### DELETE
 1. 해당 URL의 자료를 삭제한다.

##### TRACE
 1. 이전에 요청한 내용을 들을 것을 요청한다.
 2. 원격지 서버에 Loopback(루프백) 메시지를 호출하기 위해 사용된다. 

##### CONNECT
 1. 프록시가 사용하는 요청.

##### PATCH
 1. 리소스에 대한 부분적인 수정을 적용한다.

#### 3. RESTful 이란 무엇인가.
**RE**presentational **S**tate **T**ransfer의 약자로 장비간 통신을 위해 CORBA, RPC, SOAP등의 복잡한 방법을 사용하는 대신, 간단하게 HTTP를 이용하는 것이 목적이다.

HTTP URI를 통해 Resource를 명시하고, HTTP Method(Post, Get, Put, Delete)를 통해 해당 Resource에 대한 CRUD Operation을 적용한다. 즉, REST는 ROA(Resource Oriented Architecture) 설계의 중심에 Resource가 있고 HTTP Method를 통해 Resource를 처리하도록 설계된 아키텍쳐를 의미한다.

##### REST의 장점

- OPENAPI를 제공하기 쉽다.
- 멀티플랫폼 지원 및 연동이 용이하다.
- 원하는 타입으로 데이터를 주고받을수 있따. (XML, JSON, RSS )
- 기존 웹 인프라를(HTTP)를 그대로 사용가능하다 ( 방화벽, 장비 요건 불필요 )
- 사용하기 쉽다
- 세션을 사용하지 않는다. 각각의 요청에 독립적.

##### REST의 단점

- 표준이 없어서 관리가 어렵다.
- 사용할 수 있는 메소드가 4가지 밖에 없다.
- 분산환경에는 부적합하다.
- HTTP통신 모델에 대해서만 지원한다.

##### REST의 특징

- 클라이언트/서버 구조 : 일관적으로 독립되어야 한다.
- 무상태(Stateless) : 각요청 간 클라이언트의 Context는 서버에 저장되어서는 안 된다.
- 캐시가능(Cacheable) : WWW에서와 같이 클라이언트는 응답을 Caching 할 수 있어야 한다.
- 계층화(Layered System) : 클라이언트는 보통 대상 서버에 직접 연결 또는 중간 서버를 통해 연결되는지 모른다.
- Code on demand(option) : 자바 애플릿/ 자바스크립의 제공으로 서버가 클라이언트가 실행   시킬 수 있는 로직을 전송하여, 기능을 확장 할수 있다.
- 인터페이스 일관성 : 아키텍처를 단순화하고, 작은 단위로 분리하여, 클라이언트-서버 파트    별로 독립적으로 개선 될 수 있도록 한다.
- 자체 표현구조(Self-Descriptiveness) : API 메시지만 보고도 어떤 API인지를 이해 할수 있는 자체 표현 구조를 가진다.

#### 4. rake routes가 말해주는 것은?

#####  routes.rb
```ruby
Rails.application.routes.draw do
  resources :posts
end
```
resources 메서드로 resource의 표준적인 route(RESTful 인터페이스)가 정의 된 것이다.

#####  routes 정의 확인

1. rake routes 명령어로 현재 애플리케이션에 정의된 route를 목록으로 확인 할 수 있다.
2. 브라우저에서 http://localhost:3000/rails/info/routes 로도 확인 할 수 있다.

|Prefix| Verb |  URI Pattern | Controller#Action | 역할 |
|--------|--------|--------|--------|--------------|
|posts| GET  | /posts(.:format) | posts#index  | 목록 화면 표시|
| 	   | POST | /posts(.:format) | posts#create | 새로운 데이터 등록화면의 입력을 받아 데이터 등록 처리|
|new_post| GET | /posts/new(.:format)| posts#new | 새로운 데이터 등록 화면 표시 |
| edit_post | GET | /posts/:id/edit(.:format) | posts#edit | 수정 화면 표시|
| post | GET | /posts/:id(.:format) | posts#show | 개별 상세 화면 표시 |
|      | PATCH | /posts/:id(.:format) | posts#update | 수정화면의 입력을 받아 수정 처리|
|      | PUT | /posts/:id(.:format) | posts#update |	|
|      | DELETE | /posts/:id(.:format) | posts#destroy | 목록화면에서 지정된 데이터 제거처리|


## controller와 view파일 살펴보기
### View Helper


웹 애플리케이션에서의 폼(Form)은 유저 입력을 받기 위해서는 필수인 인터페이스입니다. 하지만 폼의 각 요소들의 명명법과 수많은 속성들 탓에 폼의 마크업은 쉽게 복잡해지고, 관리하기 어려워집니다. 그래서 Rails에서는 폼 마크업을 생성하기 위한 뷰 헬퍼를 제공하고, 이런 번잡한 작업을 할 필요를 없앴습니다.

템플릿 파일을 작성할 때 도움을 주는 메서드를 의미한다. 뷰 헬퍼를 이용하면 입력 양식 요소 생성을 비롯해 문자열 또는 숫자 정형화, 인코딩 처리 등 뷰에서 자주 사용되는 처리를 손쉽게 할 수 있습니다. 또한 뷰 헬퍼에는 모델 또는 라우터를 연동하는 등 Rails 자체와 함께 이용할 수 있는 기능이 많다.


### 1. index 액션
```ruby
class PostsController < ApplicationController
  def index
    @posts = Post.all
  end
end
```
Post.all은 현재 데이터베이스에 있는 모든 글(posts) 정보를 Post 모델로 반환하는 메소드 입니다. 이 호출의 결과는 글(post)의 배열이고 @posts 변수에 저장됩니다.
```erb
#index.html.erb

<p id="notice"><%= notice %></p>

<h1>Posts</h1>

<table>
  <thead>
    <tr>
      <th>Title</th>
      <th>Content</th>
      <th colspan="3"></th>
    </tr>
  </thead>

  <tbody>
    <% @posts.each do |post| %>
      <tr>
        <td><%= post.title %></td>
        <td><%= post.content %></td>
        <td><%= link_to 'Show', post %></td>
        <td><%= link_to 'Edit', edit_post_path(post) %></td>
        <td><%= link_to 'Destroy', post, method: :delete, data: { confirm: 'Are you sure?' } %></td>
      </tr>
    <% end %>
  </tbody>
</table>

<br>

<%= link_to 'New Post', new_post_path %>
```
index 뷰는 @posts 배열을 순환하면서 내용과 링크를 보여줍니다.

##### view helper
* `link_to(body, url [ , html_options])`는 세부 항목에 대한 링크를 만듭니다.
 > body : 링크 텍스트
 > url : 링크 대상 경로(or 매개변수정보)
 > html_options : 태그에 적용할 옵션정보

* 
```erb
   <%= link_to 'Show', post %>
```
* 이 부분에서 post는 each메서드에서 @posts변수로 부터 얻은 각각의 요소이다.
* `link_to` 메서드의 링크 대상 경로에 모델 객체를 적용하면 rails는 객체를 나타내는 id속성(post.id)를 사용한다. 따라서 "/posts/1"과 같은 경로가 생성된다.

* 
```erb
<%= link_to 'Edit', edit_post_path(post) %>
```
* edit_post_path 와 new_post_path 는 레일즈가 제공하는 RESTfule 라우팅 부분입니다. resources 메서드를 호출할 때 자동으로 사용되는 뷰 헬퍼이다.
* 
```erb
<%= link_to 'Destroy', post, method: :delete, data: { confirm: 'Are you sure?' } %>
```
* data-confirm옵션을 지정하면 링크를 클릭할 때 확인 대화상자가 표시된다.
* HTTP GET이외의 것으로 요청을 할때 method로 지정할 수 있다. method: :delete는 HTTP DELETE 메소드를 사용한다는 것이다.

### 2. Show 액션

```ruby
#posts_controller.rb

class PostsController < ApplicationController
  before_action :set_post, only: [:show, :edit, :update, :destroy]

  def show
  end

  private
    def set_post
      @post = Post.find(params[:id])
    end

end
```
* `before_action method, only: action` 는 action 메서드가 실행되기 전에 실행할 메서드를 지정하는 메서드 입니다.
> method: 필터로 실행되는 메서드
> action: 필터를 적용할 액션 메서드
	
    여기서는 show액션이 실행되기 전에 set_post가 실행됩니다.

* private는 액션으로 호출되지 않도록 해준다. 그래서 filter method에서 처리하는 내용을 private에 선언된 것이다.

* url에서 전달받은 매개변수(id)를 추출할 수 있게 하는 것이 `params` method이며 이 매개변수(id)를 키로 Posts테이블을 검색하는 것이 `find`method의 역할이다. 즉, set_post는 매개변수(id)를 추출해 Posts테이블을 검색하고 결과를 @post에 저장하는 method이다.

```erb
#show.html.erb

<p id="notice"><%= notice %></p>

<p>
  <strong>Title:</strong>
  <%= @post.title %>
</p>

<p>
  <strong>Content:</strong>
  <%= @post.content %>
</p>

<%= link_to 'Edit', edit_post_path(@post) %> |
<%= link_to 'Back', posts_path %>

```
##### view helper
index와 동일함.


### 3. New / Create 액션

```ruby
class PostsController < ApplicationController
  before_action :set_post, only: [:show, :edit, :update, :destroy]

  def new
    @post = Post.new
  end

  def create
    @post = Post.new(post_params)

    respond_to do |format|
      if @post.save
        format.html { redirect_to @post, notice: 'Post was successfully created.' }
        format.json { render :show, status: :created, location: @post }
      else
        format.html { render :new }
        format.json { render json: @post.errors, status: :unprocessable_entity }
      end
    end
  end

  private
    def set_post
      @post = Post.find(params[:id])
    end

    def post_params
      params.require(:post).permit(:title, :content)
    end
end
```
입력 양식을 출력하는 new action, 버튼을 클릭했을때 호출되는 데이터 등록 처리를 하는 create action이 있다.

* new action은 `@post = Post.new` 비어있는 post객체를 생성하며, 이때 생성되는 객체로 템플릿파일(new.html.erb)에서 모델의 속성을 알 수 있다.
* post_params는 입력양식으로 부터 입력받은 데이터를 추출할 때 사용된다.
* create action에서 `post = Post.new(post_params)`는 hash값이 모델에 대응되는 속성으로 한꺼번에 설정이되며, 오류가 발생할때 템플릿으로 피드백 하는게 가능하다.
* ```ruby
respond_to do |format|
	if @post.save
    	format.html { redirect_to @post, notice: 'Post was successfully created.' }
    	format.json { render :show, status: :created, location: @post }
	else
    	format.html { render :new }
    	format.json { render json: @post.errors, status: :unprocessable_entity }
	end
end
```
* `respond_to`메소드로 지정된 형식으로 템플릿이 출력되는 형태이다. 
=> html이라면 new.html.erb를 호출하고, json이라면 @post.errors에 JSON형식으로 바꾸어 출력한다. 
* `.save` 메소드는 데이터베이스와 관련된 처리의 결과를 true or false로 반환한다. 이러한 성질을 이용해서 저장성공여부를 확인하고 성공한 경우와 아닌 경우를 나눠서 처리한 것이다.
* `redirect_to url [, option]`는 매겨변수로 지정한 url로 이동하게 만든 것이다.


```erb
#_form.html.erb
<%= form_for(post) do |f| %>
  <% if post.errors.any? %>
    <div id="error_explanation">
      <h2><%= pluralize(post.errors.count, "error") %> prohibited this post from being saved:</h2>

      <ul>
      <% post.errors.full_messages.each do |message| %>
        <li><%= message %></li>
      <% end %>
      </ul>
    </div>
  <% end %>

  <div class="field">
    <%= f.label :title %>
    <%= f.text_field :title %>
  </div>

  <div class="field">
    <%= f.label :content %>
    <%= f.text_area :content %>
  </div>

  <div class="actions">
    <%= f.submit %>
  </div>
<% end %>

```
* **부분 템플릿**은  메인 템플릿에서 불러들이는 템플릿이다.
`_<이름>.html.erb`형태로 파일이름 앞에 `_`가 붙여야한다.
> form에쓰인 입력양식은 신규등록(new)/수정(update)페이지에서 공통으로 사용하기 때문에 따로 빼서 사용함으로써 코드의 중복입력을 피한 것이다. 

	##### view helper
```erb
<%= form_for(post) do |f| %>
# -------- 생략 -------
  <div class="field">
    <%= f.label :content %>
    <%= f.text_area :content %>
  </div>

  <div class="actions">
    <%= f.submit %>
  </div>
<% end %>
```
* 모델과 연동되는 입력 양식을 생성할 때 사용
```
form_for(model) do |f|
	--입력 양식--
end
```
	1. 입력값을 모델의 속성으로 변환
	2. 수정, 오류가 발생할때ㅐ 모델의 현재값을 입력 양식에 출력

* form_for블록 내부에서 `f.label`, `f.text_filed(f.text_area)`,  `f.data_select`, `f.check_box`, `f.submit`등의 메소드를 호출함.

	form for내부에서 사용할 수 있는 뷰 헬퍼로 각각 모델과 관련된 라벨, 텍스트상자, 날짜 선택 상자, 체크박스, 제출버튼을 생성한다.

```erb
#new.html.erb

<h1>New Post</h1>

<%= render 'form', post: @post %>

<%= link_to 'Back', posts_path %>
```
`<%= render 'form', post: @post %>` render를 통해서 부분템플릿 호출을 하고 있다.


### 4. Edit / Update 액션

```ruby
class PostsController < ApplicationController
  before_action :set_post, only: [:show, :edit, :update, :destroy]

  def edit
  end

  def update
    respond_to do |format|
      if @post.update(post_params)
        format.html { redirect_to @post, notice: 'Post was successfully updated.' }
        format.json { render :show, status: :ok, location: @post }
      else
        format.html { render :edit }
        format.json { render json: @post.errors, status: :unprocessable_entity }
      end
    end
  end

  private
    
    def set_post
      @post = Post.find(params[:id])
    end
    
    def post_params
      params.require(:post).permit(:title, :content)
    end
end
```
수정화면은 편집 입력 양식을 출력하는 edit액션과 데이터 수정처리를 수행하는 update액션으로 연결되어있다.

* `update`메소드는 매개변수로 받은 값을 사용해 데이터를 변경하고 결과를 데이터베이스에 저장한다. update도 save와 마찬가지로 수정성공여부를 true or false값을 반환한다. 

```erb
#edit.html.erb
<h1>Editing Post</h1>

<%= render 'form', post: @post %>

<%= link_to 'Show', @post %> |
<%= link_to 'Back', posts_path %>
```
*이 외의 것은 앞에서 다 설명됨*

### Destroy 액션


```ruby
class PostsController < ApplicationController
  before_action :set_post, only: [:show, :edit, :update, :destroy]

  def destroy
    @post.destroy
    respond_to do |format|
      format.html { redirect_to posts_url, notice: 'Post was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
  
    def set_post
      @post = Post.find(params[:id])
    end

end
```
destroy 액션은 id매개변수를 키로 객체를 추출하고 이를 제거한다. 데이터를 제가할때는 `.destroy`메소드를 사용한다.



