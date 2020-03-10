# Validation

: 유효성검사 구현은 사용자가 잘못된 값을 입력할 가능성을 배제시켜 애플리케이션이 예상하지 못한 동작을 하거나 예외가 발생하는 경우를 막기 위해서 필요하다. 또한 유효성을 확인하는 것은 공격을 최소화 할 수 있는 보안 대책이다.

> 클라이언트측에서 유효성검사(jQuery validation)은 서버를 거치지않기 때문에 서버 부하를 줄여주거나 빠른 피드백을 전달해 줄 수 있지만 언제까지나 일차적인 검사이다. 클라이언트에서 예비 유효성 검사를해여 통신이 발생하는 낭비를 막고, 서버에서는 최종 검사를 하는 것이 일반적.


```ruby
validates field [, ...] name: params[, ...]
# filed : 검사대상필드이름
# name : 검사이름
# params :검사 매개변수
```

**save, save!, create, create!, update, update!**는 메서드가 호출되는 시점에 입력값을 검사처리해 검사가 성공적으로 이루어 지는 경우에만 수행된다.

반면에 **decrement!, decrement_counter, increment!, increment_counter, toggle!, touch, update_all, update_attribute, update_counters, update_column, save(validates: false)**는 검사 처리를 자동으로 하지않아 값의 유효성에 관계없이 데이터베이스에 객체를 바로 반영하므로 신뢰할 수 있다는 것이 확인된 경우에만 사용해야한다.

### 유효성 오류 표시
```erb
<%if @book.errors.any? %>
	<div id="error_explanation">
		<ul>
			<% @book.errors.full_messages.each do |msg| %>
				<li><%= msg %></li>
			<% end %>
		</ul>
	</div>
<% end %>
```

### Acceptance 유효성 검사(수락)
: 예를 들어 사용자가 이용약관에 동의했는지를 검사할 때 사용. acceptance는 데이터베이스에 관련 필드가 필요 없다.
```ruby
# controller
def user_params
	params.require(:user).permit(:agreement)
end
```
```ruby
validates :agreement, acceptance: true
```
```erb
<div class="field">
	<%= f.label :agreement %><br />
	<%= f.check_box :agreement %>
</div>
```
acceptance검사에서 체크박스를 체크할 때의 값을 나타내는 매개변수를 지정할 수 있다.
```ruby
validates :agreement, acceptance: {accept: 'yes'}
```
```erb
<div class="field">
	<%= f.label :agreement %><br />
	<%= f.check_box :agreement, {}, 'yes' %>
</div>
```

### confirmation 동일검사
: 비밀번호, 메일 주소등 중요한 항목을 확인하기위해 두번 입력할때 두값이 같은지 확인. 데이터베이스에 대응하는 필드가 필요없다.
```ruby
# controller
def user_params
	params.require(:user).permit(:email_confirmation, :email)
end
```
```ruby
validates :email, confirmation: true
```
```erb
<div class="field">
	<%= f.label :email_confirmation %><br />
	<%= f.text_field :email_confirmation %>
</div>
```

### Uniqueness 중복검사
: 중복되지 않음을 확인한다.
```ruby
validates :title, uniqueness: { scope: :publish}
```

### 유효성 검사 클래스 공통 매개변수
| 옵션 | 설명 |
|--------|--------|
| allow_nil | nil인경우 유효성 검사 생략|
| allow_blank | nil 또는 공백인경우 유효성 검사 생략|
| message | 오류 메세지 |
| on | 유효성 검사 시점(기본적으로 save)|
| if | 조건이 true일때만 유효성검사|
| unless | 조건이 false일때만 유효성검사|

다른 규칙들은 http://guides.rubyonrails.org/active_record_validations.html
참조.


### 스터디과제

```ruby
# user.rb
class User < ApplicationRecord
	has_and_belongs_to_many :groups
	has_many :posts
	has_many :likes
	has_many :comments

	validates :name, length: { maximum: 10 },presence: true
	def name=(s)
    	write_attribute(:name, s.to_s.capitalize) 
  	end
	validates :age, numericality: {only_integer: true,greater_than_or_equal_to: 20, less_than: 30}, presence: true
	validates :mail, uniqueness: true,presence: true
	validates_format_of :mail,:with => /\A[^@\s]+@([^@\s]+\.)+[^@\s]+\z/
end
```
* name: 첫글자 소문자인경우 대문자로 자동변경저장,최대 10글자
* age: 숫자형식 20대(20~29)
* mail: '이메일형식',중복안됨

```ruby
# post.rb
class Post < ApplicationRecord
  belongs_to :user
  has_many :comments

  validates :title, length: { in: 2..30 }, presence: true
  validates :content, presence: true
  def content=(c)
  	write_attribute(:content, c.gsub!(/shit/,"****").gsub!(/fuck/,"****").gsub!(/hell/,"****"))
  end

end
```
* title: 최소2글자,최대30글자
* content: 욕설필터링(****)

```ruby
# comment.rb
class Comment < ApplicationRecord
  belongs_to :user
  belongs_to :post

  validates :content, presence: true, length: {maximum: 200}
  def content=(c)
  	write_attribute(:content, c.gsub!(/shit/,"****").gsub!(/fuck/,"****").gsub!(/hell/,"****"))
  end 
end
```
* content: 욕설필터링(****),최대200글자

```ruby
# like.rb
class Like < ApplicationRecord
  belongs_to :user
  belongs_to :post
end

```

```ruby
# group.rb
class Group < ApplicationRecord
	has_and_belongs_to_many :users
	validates :name, length: { maximum: 20},presence: true
end
```

* name: 최대20글자