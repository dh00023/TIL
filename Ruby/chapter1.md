## Data type
* Numbers (숫자)
 > `my_num = 5`

* String (문자열)
 > `my_string = "Ruby" `(""을 해줘야한다.)

* Boolean(true, false) 
 >` my_boolean = true`

- - -

## variable

variable as a word or name that grasps a single value.
> `my_num`, `my_string`, `my_boolean`이 variable이다.

- - -

## MATH
* Addition (+)
* Subtraction (-)
* Multiplication (*)
* Division (/)
* Exponentiation ( ** )
* Modulo (%)
- - -

## puts and print
print와 puts의 차이는 puts 는 자동으로 blank line을 추가한다.
 ```ruby
 print "Hello"
 puts "Konkuk Likelion 5th"
```
- - -

## String Method
Method는 `.`을 이용해서 사용된다.
* `.length` : 문자열의 길이를 계산.
> `"Hello, I am Dahye".length`
> 결과 ==> 17

* `.reverse` : 문자열을 역순으로 출력
> `"Konkuk".reverse`
> 결과 ==> kuknoK

* `.upcase` & `.downcase` : 문자열을 대문자로 & 소문자로
> `"eric".upcase`
> 결과 ==> ERIC

* `.capitalize` : 첫번째글자만 대문자, 뒤의 글자는 소문자.
> `"konkuk".capitalize`
> 결과 ==> Konkuk

* `!` method끝에 !를 붙이게 되면 수정된값이 variable에 저장이된다.
```ruby
a="ruby"
#=>"ruby"
a.upcase
#=>"RUBY"
a
#=>"ruby"
a.upcase!
#=>"RUBY"
a
#=>"RUBY"
```

* `.include?` 주로 조건문과 함께 쓰이며 포함하고 있으면 true, 아니면 false 
```ruby
i="Hello, I am Dahye"
#=> "Hello, I am Dahye"
if i.include? "a"
	print "hahaha"
end
#=> hahaha=> nil
i.include? "a"
#=> true
```

* `.gsub` : global substitution 으로 문자를 바꾸고 싶을때 사용.
```ruby
i="Hello, I am Dahye"
#=> "Hello, I am Dahye"
i.gsub!(/a/,"e")
#=> "Hello, I em Dehye"
```
- - -

## 주석(Comment)
###### 주석은 코드를 짤 때 넣는 설명문이다. 코드를 읽는 사람으로 하여금 쉽게 이해할 수 있게 하기 위한 것으로 실행에는 영향을 미치지 않는다.
* `#`은 한 줄의 주석으로 사용된다.
*  `=begin =end`는 주석을 여러줄 사용해야하는경우
  ```ruby
 =begin
 I'm a comment.
 주석을 여러줄로 쓰는경우!
 =end
 ```
- - -

## Getting input

`gets`는 루비의 method 로 사용자의 입력(input)을 받아온다. gets는 자동으로 blank line이 추가되는데 `chomp`는 이 line을 제거한다.
 ```ruby
 variable_name=gets.chomp
 ```
- - -

## Printing the Output

`gets.chomp`를 통해 받아온 입력을 출력하기 위해서는 `#{variable_name}`를 통해서 출력할 수 있다.
 ```ruby
 print "What's your first name?"
 first_name=gets.chomp
 print "my first name is #{first_name}"
 ```
- - -
