# Database

### 모델 클래스 생성
```
rails generate model name field:type
```

| 종류 | 설명 | 예 |
|--------|--------|
| 모델 클래스|첫 글자 대문자,단수형|Book|
|모델 클래스 파일 이름| 첫글자 소문자, 단수형 | book.rb|
|테이블|첫글자 소문자, 복수형| books|
|테스트 스크립트|xxxx_test.rb(첫글자 소문자,단수형)|book_test.rb|

### 마이그레이션 파일로 테이블 생성
마이그레이션 : 테이블 레이아웃을 생성 또는 변경하기 위한 구조.

`rails dbconsole`or `rails db`을 사용하면 config/database.yml에 정의된 정보를 기반으로 데이터베이스 클라이언트를 실행할 수 있다.

`.tables` : 테이블 목록표시
`.schema books` : books테이블의 구조확인
`select*from books;` : books테이블내용확인
> 이때 이쁘게 보고싶다면 `.headers on` `.mode columns`를 해주면 된다.

`.exit` or `.quit` : 데이터베이스 클라이언트 종료

### 데이터 추출

##### 1. Primary Key로 검색을 한다. (`find`)

`find(keys)`
keys:주 키(배열로 지정할 수도 있다.)

##### 2. 임의의 필드로 검색(`find_by`)
:검색 조건으로 가장 처음 검색되는 레코드를 추출한다.
`find_by key: value [, ... ]`

`find_by`가 리턴하는 데이터는 항상 하나이다. 그러므로 테이블 조건에 맞는 레코드가 하나만 있을때만 사용한다.

##### 3. 지정한 필드 데이터를 배열 추출(`pluck(column, ... )`)
: 여러개의 필드를 지정해서 추출하는 것이 가능해졌다.
> ex) `Book.where(publish: '제이펍').pluck(:title, :price)`

##### 4. 데이터 존재확인(`exists?`)
: 데이터를 추출하지 않고 지정된 데이터가 있는지 없는지 정도만 확인하고 싶을때.

##### 5. Named Scope(이름있는 스코프)
`scope name , -> {exp}` :  특정한 조건식 또는 정렬식을 미리 모델쪽에 이름을 붙여 저장해두고, 후에 이용하고 싶을때 이름을 호출해서 사용한다.

> ex)
> ```ruby
 scope :top10, -> {newer.limit(10)}
 ```

##### 6. 기본스코프 정의(`default_scope exp`)
: 모델 관련 메서드를 호출할 때 자동으로 조건이 적용되게하는 기본스코프
> ex)
> ```ruby
> default_scope{order(updated_at: :desc)}
> ```

##### 7. 조건에 맞는 레코드 수 추출(`count`)
: 특정 조건에 맞는 결과 집합 개수를 추출할 때 사용.
> ex)
> ```ruby
> Book.where(school: 'konkuk').count
> ```

##### 평균(`average(col)`) / 최소(`minimum(col)`) / 최대(`maximum(col)`) / 합 (`sum(col)`)


### 검색처리 - 쿼리 메서드
:`find`, `find_by` 메서드와 다르게 호출하는 시점에는 데이터베이스에 접근하지 않는다. 이후에 쿼리 결과가 필요한 시점에 데이터베이스에 접근한다. (지연로드(Lazy Load))


1.`where`
*  `where(exp)` : 기본적인 조건식 (exp는 조건식을 나타내는 해시)
> ex) `@books = Book.where(name: 'dahye')`
where에서 AND는 `,`, BETWEEN 은 `..`, IN은 `name: [dahye, miyoen]`을 통해서 여러가지 조건을 한번에 검색할 수 있다.
* `where((exp [value, ... ])` : placeholder(매개 변수를 두는 장소)를 이용한 조건식.

2.`not` : 부정조건식
> ex) ` Book.where.not(isbn: parmas[:id])`

3.`order(sort)` : 데이터정렬

4.`redorder` : 데이터 재정렬

5.`select(cols)` : 추출할 필드 명시적 지정

6.`distinct([flag])` : 중복되지 않는 레코드 추출(중복제거)

7.`limit(rows)` / `offset(off)` : 지정범위 레코드 추출

8.`first`/ `last` : 첫 레코드 / 마지막 레코드 추출

9.`group(key)` : 데이터 그룹화(특정한 키로 데이터를 그룹화하고 싶은 경우

10.`having(exp, [,value, ... ])` : 그룹화한 결과에 추가 조건

11.`!` : 끝에 `!`를 붙여 조건식을 여러개의 줄에걸쳐 단계적으로 적용하는게 가능해짐.

12.`unscope(skips)` : 쿼리로 만든 조건제거

13.`none` : 아무것도 없는 결과

### 레코드 추가 / 수정 / 제거

##### 여러개 레코드 한번에 수정(`update_all(updates)`)
>ex) 
>```ruby
>Book.where(publish: '한빛미디어').update_all(publish: 'jpub')
>```

##### 레코드 제거(`destroy` / `delete` / `destroy_all(cond)`)
: `destroy`는 SELECT -> DELETE 순서, `delete`는 DELETE만 호출한다. 이러한 차이로 association or callback 기능에 차이가 난다.
간단하게 데이터 제거만 할 때는 delete를 사용하는게 좋다.

: `destroy_all`은 특정조건에 맞는 레코드를 한꺼번에 제거할때 사용.

##### 트랜잭션 처리(`transaction`)
: 모든 명령어의 성공, 실패를 한꺼번에 모아서 처리하는 것이다. 만약 한개라도 실패한다면 트랜잭션 처리도 실패하고 이때까지 실행됐던 모든 명령아가 무효화된다.

* commmit : 트랜잭션 처리를 확정하는 것
* Rollback : 처리를 실패해 트랜잭션 상태를 되돌리는것.
* 트랜잭션 분리 레벨 : 여러개의 트랜잭션을 동시 실행한 경우에 동작을 표시. 분리 레벨이 높으면 그만큼 데이터의 정합성은 높아지지만 실행성은 낮아진다.

##### **충돌** : 동시에 수정하는 경우에 발생

1. 테이블에 `lock_version`추가 
2. 동시실행제어준비
3. 실행제어 작동확인
4. 예외검출된 경우의 처리


### 용어정리
`rake db:seed` : 시드파일을 이용해서 데이터를 초기화하는 명령어이다.
`rake db:drop` : 데이터베이스 파일 삭제