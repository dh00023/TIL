# M : N relation
:예를들어 한명의 학생은 많은 과목을 수강할 수 있고, 하나의 강좌는 여러명의 학생이 들을 수 있습니다.

## 1. has_and_belongs_to_many Association

![](http://guides.rubyonrails.org/images/habtm.png)
: assemblies_parts처럼 형식적인 중간 테이블을 사용해 표현하는 것!

```
rails new week4again
rails g model user name mail age:integer
rails g model group name
# string은 default

rails g migration CreateJoinTableGroupUser group user
rails db:migrate
```
```ruby
#group.rb
has_and_belongs_to_many :users
```
```ruby
#user.rb
has_and_belongs_to_many :groups
```
association이름은 모두 **복수형**으로 지정한다.
```ruby
# rails c
User.create!(name: "minwoo")
Group.create!(name:"old")
Group.create!(name:"young")
u=User.find(1)
u.group_ids = 2
u.save
```

## 2.has_many through Association
![](http://guides.rubyonrails.org/images/has_many_through.png)
M:N관계를 표현할 때 사용할 수 있는 간단한 방법이지만, 단점 또한 존재한다.

```ruby
# book.rb
has_many :reviews
has_many :users, through :reviews
```
```ruby
# review.rb
belongs_to :book
belongs_to :user
```
```ruby
# user.rb
has_many :reviews
has_many :books, through :reviews
```

has_many through Association을 사용하면 Book모델에서 곧바로 User모델에 접근할 수 있다.
through을 이용안하면 Book->Review=>User처럼 접근해야한다.

1번 방법은 중간테이블에서 양쪽 모델의 키라는 단순한 정보만을 가지고 있으므로 위의 M:N과 같은 경우는 중간 모델이 필요하다.