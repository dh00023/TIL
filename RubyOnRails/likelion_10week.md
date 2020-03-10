#멋사4기강의 10주차

## 1. 검색 구현하기
```ruby
a=["강원도","경기도","서울"]
a=%w[강원도 경기도 서울]
```
%w는 배열을 저장할때 쉽게사용하는!.

데이터베이스를 만들때 seed.rb에 시드파일을 구성할 수 있다.
```ruby
# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

Student.create(name: "dahye", number: "201411809")
Student.create(name: "seonwook", number: "201411845")
```
seed파일을 수정한 후 `rake db:seed`를 하면 데이터베이스에 생성된다.

검색을 할 때 `.find_by`, `.where`을 이용해서 내가 원하는 파일을 찾아낼 수 있다.

`where`은 결과값이 배열으로 출력된다. 이때 하나의 값만 뽑아내고 싶다면 끝에 `.take`,`.limit(1)`를 해주면된다.

```ruby
a=Student.where("number LIKE ? ", "%2%")
```
`LIKE?`를 사용해 학번에 2가 포함된 사람들을 다 출력할 수 있다.

* Gem sunsopot
:Sunspot is a Ruby library for expressive, powerful interaction with the Solr search engine. 사용법이 어렵긴하나 데이터레코드를 뽑아내는 검색에 속도가 향상된다.

## 2. 반복되는 코드 줄이기(모델)
코드라인이 증가하면 버그가 생길 확률이 높아진다!
코드는 반복되면 안좋다. 최대한 줄여야한다!
반복적인 코드를 쓸때는 model로 빼주세요!