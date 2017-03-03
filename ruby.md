# Ruby
High-level , Interpreted, Object-oriented, Easy to use

*Everything in Ruby is an Object*

### 1. Data type
* Numbers (숫자)
 > `my_num = 5`

* String (문자열)
 > `my_string = "Ruby" `(""을 해줘야한다.)

* Boolean(true, false) 
 >` my_boolean = true`

- - -

### 2. variable

variable as a word or name that grasps a single value.
> `my_num`, `my_string`, `my_boolean`이 variable이다.

- - -

### 3. MATH
* Addition (+)
* Subtraction (-)
* Multiplication (*)
* Division (/)
* Exponentiation ( ** )
* Modulo (%)
- - -

### 4. puts and print
print와 puts의 차이는 puts 는 자동으로 blank line을 추가한다.
 ```ruby
 print "Hello"
 puts "Konkuk Likelion 5th"
```
- - -

### 5.String Method
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
> <img src="/Users/dh0023/study/ruby/1.png" width="200">

* `.include?` 주로 조건문과 함께 쓰이며 포함하고 있으면 true, 아니면 false 
> <img src="/Users/dh0023/study/ruby/2.png" width="250">

* `.gsub` : global substitution 으로 문자를 바꾸고 싶을때 사용.
> <img src="/Users/dh0023/study/ruby/3.png" width="300">

- - -

### 6. 주석(Comment)
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

### 7. Getting input

`gets`는 루비의 method 로 사용자의 입력(input)을 받아온다. gets는 자동으로 blank line이 추가되는데 `chomp`는 이 line을 제거한다.
 ```ruby
 variable_name=gets.chomp
 ```
- - -

### 8. Printing the Output

`gets.chomp`를 통해 받아온 입력을 출력하기 위해서는 `#{variable_name}`를 통해서 출력할 수 있다.
 ```
 print "What's your first name?"
 first_name=gets.chomp
 print "my first name is #{first_name}"
 ```
- - -

### 9. 조건문
##### `if`/`else`/`elsif`/`end` 
 ```ruby
if x < y  # Assumes x and y are defined
  puts "x is less than y!"
elsif x > y
  puts "x is greater than y!"
else
  puts "x equals y!"
end
```
```ruby
expression if boolean
```
##### `unless`/`else`/`end`
 ```ruby
unless hungry
  # Write some 
else
  # Have some noms
end
```
```ruby
expression unless boolean
```

##### `case`/`when`/`else`/`end`
```ruby
case language
when "JS"
  	puts "Websites!"
when "Python"
  	puts "Science!"
when "Ruby"
  	puts "Web apps!"
else
  	puts "I don't know!"
end
```
```ruby
case language
  when "JS" then puts "Websites!"
  when "Python" then puts "Science!"
  when "Ruby" then puts "Web apps!"
  else puts "I don't know!"
end
```
##### ternary conditional expression
```ruby
boolean ? Do this if true: Do this if false
```
```ruby
puts 3 < 4 ? "3 is less than 4!" : "3 is not less than 4."
```
- - -

### 10. Comparators
##### relational operator
* `==` 와 `=` 의 차이점

 `==`는 같다는 표현으로 비교를 할 때 사용된다.
`=`는 대입을 할 때 사용된다.
 ```ruby
 x = 2
y = 2
if x == y
  print "x and y are equal!"
end
```

* `!=` : not equal
* `<`  : less than
* `<=` : less than or equal to
* `>` : greater than
* `>=` : greater than or equal to

##### logical operator
* `&&` : and (둘다 true 이면 true)
* `||` : or (둘중 하나만 true 이면 true)
* `!` : not (반대)
- - -

### 11. Loop(반복문)
##### while
: while은 조건이 만족되면 loop가 돌아간다.
```ruby
while 조건
# write something
end
```
> <img src="/Users/dh0023/study/ruby/4.png" width="250">

##### until
: until은 조건이 만족될때 까지 loop가 돌아간다.
```ruby
until 조건
# write something
end
```
> <img src="/Users/dh0023/study/ruby/5.png" width="250">

##### for
```ruby
for num in 1...10
  puts num
end
```
> <img src="/Users/dh0023/study/ruby/6.png" width="250">
> `1...3`은 3을 포함하지않고 `1..3`은 3을 포함하는 것을 볼 수 있다.
  
##### loop
*ruby에서는 `{}`가 `do`~`end`대신해서 사용할 수 있다.*
`loop{ puts "hi" }`
```ruby
i = 0
loop do
  i += 1
  print "#{i}"
  break if i > 5
end
```
*여기서 `break`를 통해 무한 loop를 빠져나온다.*

* `next` :  can be used to skip over certain steps in the loop
```ruby
for i in 1..5
	next if i % 2 == 0
	print i
end
```
> <img src="/Users/dh0023/study/ruby/7.png" width="250">
> 예시를 보면 i % 4 == 0 인 4, 8, 12, 16, 20 부분은 넘어간 것을 확인 할 수 있다.

- - -

### 12. Array

```ruby
array1=[1,2,3]
array2=[true,2,"a",[1,2,3,4]]
```
배열에는 다양한 형태의 데이터 타입(boolean, number, string, array)을 같이 쓸 수 있다.

##### - 배열의 접근방법
index를 통해서 접근 할 수 있다!
배열의 index는 **0**부터 시작해 **배열의 크기-1** 까지가 범위이다.
> `arr=[1,2,3,4,5]`
> 
> | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|
|arr[0]| arr[1] | arr[2] | arr[3] | arr[4] |

> <img src="/Users/dh0023/study/ruby/8.png" width="300">

- - -

### 13. Hashes

 : a collection of key-value pairs

##### hash 생성방법
```ruby
hash = {
  key1 => value1,
  key2 => value2,
  key3 => value3
}
```
`=>`hash rocket를 이용해서 key를 지정해준다.
  ```
my_hash = Hash.new 
my_hash["key"] = "value"
```
#Hash는 반드시 H가 대문자여야한다.

default value 지정 `h=Hash.new(“default value”)`

##### hash  value에 접근하는 방법
	hash = "key"

#### Symbol(:)
`"string" == :string # false`

* aren’t strings
* there’s only one copy of any particular symbol at a given time
* 주로 hash의 키로 많이 사용된다.
```ruby
sounds = {
  :cat => "meow",
  :dog => "woof",
  :computer => 10010110,
}
```
* 만들어지면 바꿀 수 없다.
* Only one copy of any symbol exists at a given time, so they save memory;
* Symbol-as-keys are faster than strings-as-keys because of the above two reasons.

#### hash rocket(=>)에서 문법이 바뀜
```ruby
new_hash = {
  key1: value1,
  key2: value2,
  key3: value3
}
```
- - -

### 14. Method

##### Iterator
: Iterators are nothing but methods supported by collections. Objects that store a group of data members are called collections. In Ruby, arrays and hashes can be termed collections.
 Iterators return all the elements of a collection, one after the other. We will be discussing two iterators here, each and collect. Let's look at these in detail.

* `.each` 
 : which can apply an expression to each element of an object, one at a time.
```ruby
object.each { |item| # Do something }
```
```ruby
object.each do |item| # Do something end
```
> <img src="/Users/dh0023/study/ruby/9.png" width="250">
> 배열의 각각의 원소가 10씩 증가 한 것을 볼 수 있다.


* `.times`

 : 앞의 수 만큼 반복하라는 뜻이다. 
> <img src="/Users/dh0023/study/ruby/10.png" width="350">

* `.split` 

 :it takes in a string and returns an array (문자열을 분리해 배열로 만들어준다.)
> <img src="/Users/dh0023/study/ruby/11.png" width="350">
* `.sort_by` : 오름차순으로 정렬
* `.reverse` : 역순으로 출력  
* `.sort` : 정렬

* `.to_s` : string으로 data type 변경
* `.to_sym` or `.intern` : symbol로 data type 변경
> <img src="/Users/dh0023/study/ruby/13.png" width="230">

* `.push` or `<<` or `+` : 배열,문자열에 추가할 때 사용
> 문자열에 추가할 때는 string 이 아닌 것은 .to_s를 이용해서 string으로 만들어줘야한다. 아닌 경우에는 #{}을 통해서 해야한다.

* `.select` : filter {}안에 있는 조건대로 거른다.
```ruby
grades = {
	alice: 100,
  	bob: 92,
  	chris: 95,
  	dave: 97
}
grades.select {|name, grade| grade < 97}
# ==> {:bob=>92, :chris=>95}
grades.select { |k, v| k == :alice }
# ==> {:alice=>100}
```

* `.each_key` : key만 뽑는 hash methods
* `.each_value` : hash 에서 value만 뽑아내는 hash methods
* `.delete` : hash에서 삭제됨.
* `.upto` , `.downto`
```ruby
for i in 1..10
  	print i, " "
end
# => 1 2 3 4 5 6 7 8 9 10
# Compare this with upto, which does exactly the same thing:
1.upto(10) { |i| print i, " " } 
# => 1 2 3 4 5 6 7 8 9 10
```
* `.respond_to?` : takes a symbol and returns true if an object can receive that method and false otherwise
```ruby
[1, 2, 3].respond_to?(:push)
# => true (.push on an array object)
[1, 2, 3].respond_to?(:to_sym)
# => false (can't turn an array into a symbol.)
```
* `.collect` or `.map` : takes a block and applies the expression in the block to every element.
* `.floor` : rounds a float
* `.is_a? Object` : object 인지 확인
```ruby
:hello.is_a? Symbol
# ==> true
```
- - -

### 15. Methods(함수)

```ruby
def method_name(argument, *argu)
    # Do something!
	return somting
end

method_name(argument)
```
여러개의 argument를 사용하고 싶을 때는 *를 이용한다.(splat)
함수호출은 함수이름을 적어 호출한다. 
return은 함수의 반환값

##### parameters and arguments
arguments는 전달되는 값을 뜻하며, parameters는 그 이름을 뜻한다.
> 예를 들어 
> ```ruby
> def add(a,b)
> 	puts a+b
>end
>
>add(2,4)
>```
>에서 a,b는 parameter이고, 2,4는 arguments이다.

- - - -

#### 16. combined comparison operator  `<=>`
두개가 같을경우 0 반환 / 1번째가 더 크면 1반환 /2번째꺼가 더크면 -1반환

> <img src="/Users/dh0023/study/ruby/12.png" width="250">

- - -

### 17. Blocks
블록은 처리를 하나의 단위로 묶은 것으로, 메소드 호출 시 한번만 지정할 수 있는 인수의 일종이다.

- - -

### 18. nil
: one of two non-true value in Ruby (=>nothing at all)
false 와 다르다.(=> not true)

- - -

#### 19. conditional assignment operator `||=`
using `||=`, the hash key's value is only set once(처음 지정한 것으로 지정된다.)
[참조페이지 바로가기](http://www.rubyinside.com/what-rubys-double-pipe-or-equals-really-does-5488.html)
- - -

### 20. Yield 
: `yield`를 이용해서 method 안에 내가 원하는 값을 나중에 추가할 수 있음.
(You can also pass parameters to yield.)

```ruby
def block_test
  puts "We're in the method!"
  puts "Yielding to the block..."
  yield
  puts "We're back in the method!"
end
block_test { puts ">>> We're in the block!" }
# => We're in the method!
	Yielding to the block...
	>>> We're in the block!
	We're back in the method!
	nil
```
```ruby
def double(num)
  yield num
end
double(2) { |n| n*2 }
# => 4
```
- - -

### 21. Proc

- Procs are full-fledged objects, so they have all the powers and abilities of objects. (Blocks do not.)
- Unlike blocks, procs can be called over and over without rewriting them. This prevents you from having to retype the contents of your block every time you need to execute a particular bit of code.

```ruby
cube = Proc.new{ |x| x ** 3 }
```
> ```ruby
> [1, 2, 3].collect!(&cube)
# ==> [1, 8, 27]
[4, 5, 6].map!(&cube)
# ==> [64, 125, 216]
```
`&` is used to convert the cube proc into a block

* `.call` 을 이용해서 proc을 쉽게 호출할 수 있다.
```ruby
test = Proc.new { # does something }
test.call
# does that something!
```
* convert symbols to procs using that handy little `&`
```ruby
strings = ["1", "2", "3"]
nums = strings.map(&:to_i)
# ==> [1, 2, 3]
```
- - -

### 22. Lambda

```ruby
lambda { |param| block }
```
```ruby
lambda { puts "Hello!" } == Proc.new { puts "Hello!" }
```

##### proc과 lambda의 차이
1. argument 가 오류가 났을때 proc은 무시하고 nil처리 후 넘어가는데 lambda는 오류가난다.
2. lambda는 call이 되면 다시 마지막 코드로 돌아가는데  proc은 끝난다.
- - -

### 23. Scope
1. global variables : available everywhere
2. local variables : available certain methods
3. class variables : members of a certain class
4. instance variables : only available to particular instances of a class
- - -

### 24. Class

```ruby
class NewClass
  # Class magic here
end
```
```ruby
class NewClass; end
```

* class는 instance를 작성 할 수 있다.
* class는 상속하거나 상속 될 수 있다.
* `@` instance variable : the variable is attached to the instance of the class
```ruby
class Car
  def initialize(make, model)
    @make = make
    @model = model
  end
end
```
Each instance of Car will have its own @make,@model
* Create an instance of class `.new`
```ruby
kitt = Car.new("Pontiac", "Trans Am")
```

* `$` : global variable
* `@@` : class variable

#### Inheritance (상속) `<`
```ruby
class DerivedClass < BaseClass
  # Some stuff!
end
```
`<`말고도 `Class.new`에서는 인수에 상속하고 싶은 부모 클래스를 지정하면 된다.
```ruby
SecondClass=Class.new(FirstClass) 
#==> secondclass(자식 클래스)
SecondClass.superclass
#==> firstclass(부모 클래스)
```
상속된 함수나 변수를 override할 수 있다.
```ruby
class Creature
  def initialize(name)
    @name = name
  end
  
  def fight
    return "Punch to the chops!"
  end
end

class Dragon<Creature
    def fight
        return "Breathes fire!"
    end
end
```

#### `super` 
directly access the attributes or methods of a super class
```ruby
class DerivedClass < Base
  def some_method
    super(optional args)
      # Some stuff
    end
  end
end
```

#### Public and Private

* `public` : allow for an interface with the rest of the program( This method can be called from outside the class )
* `private` : for your classes to do their own work undisturbed( This method can't!)
```ruby
class ClassName
  	# Some class stuff
  	public
  	# Public methods go here
  	def public_method; end

  	private
  	# Private methods go here
  	def private_method; end
end 
```

##### `attr_reader` / `attr_writer` /`attr_accessor`

* `attr_reader` : to access a variable
* `attr_writer` : to change it
* `attr_accessor` : to make a variable readable and writeable in one fell swoop
```ruby
class Person

	attr_reader :name
	attr_writer :name
  	
    def initialize(name)
    	@name = same
    end
end
```
```ruby
def name
	@name
end
def name=(value)
	@name = value
end
```
That `name=`  allowed to put an = sign in a method name. 
- - -

### 25. module 
a toolbox that contains a set methods and constants
	
```ruby
module ModuleName
  # Bits 'n pieces
end
```

##### ModuleName규칙
-모듈은 시작할때 대문자! ex)Math
-모듈의 constant는 모든 문자를 대문자로 ex)PI

* namespacing : to separate methods and constants into named spaces  
 ```ruby
	Math::PI
```
Ruby knows to look inside the Math module to get that PI



--`require`
: already present in the interperter
```ruby
require ‘module’
```


##### Mixin 
: when module is used to mix additional behavior and information into a class
* `include` : mixes a module’s methods( any class that includes a certain module can use those module's methods!)
```ruby
class Angle
    include Math
    attr_accessor :radians
  
    def initialize(radians)
      @radians = radians
    end
  
    def cosine
      cos(@radians)
    end
end
```
* `extend` : mixes a module’s methods at the class 
```ruby
module ThePresent
	def now
      puts "It's #{Time.new.hour > 12 ? 'PM' : 'AM'} (GMT)."
  	end
end
class TheHereAnd
	extend ThePresent
end
```
- - -

*참고사이트 바로가기*
* [opentutorials.org](https://opentutorials.org/module/11)
* [codecademy.com](https://www.codecademy.com/learn/ruby)
* [apidock.com](http://apidock.com/ruby)
* [tutorialspoint.com](https://www.tutorialspoint.com/ruby/)
