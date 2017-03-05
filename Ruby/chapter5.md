## Method

### Iterator
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
```ruby
array = [1, 2, 3, 4, 5]
#=> [1, 2, 3, 4, 5]
array.each do |x|
	x += 10
    puts x
end
# 11
# 12
# 13
# 14
# 15
# [1, 2, 3, 4, 5]
```
> 배열의 각각의 원소가 10씩 증가 한 것을 볼 수 있다.


* `.times`
 : 앞의 수 만큼 반복하라는 뜻이다. 
```ruby
3.times { puts "hi" }
# hi
# hi
# hi
#=> 3
```

* `.split` 
 :it takes in a string and returns an array (문자열을 분리해 배열로 만들어준다.)
```ruby
a = "Hello, This is example"
#=> "Hello, This is example"
a.split(" ")
#=> ["Hello,", "This", "is", "example"]
```

* `.sort_by` : 오름차순으로 정렬

* `.reverse` : 역순으로 출력

* `.sort` : 정렬

* `.to_s` : string으로 data type 변경

* `.to_sym` or `.intern` : symbol로 data type 변경
```ruby
:exam.to_s
# ==> "exam"
"exam".to_sym
# ==> :exam
```

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

## Methods(함수)

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

### parameters and arguments
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

## combined comparison operator  `<=>`
두개가 같을경우 0 반환 / 1번째가 더 크면 1반환 /2번째꺼가 더크면 -1반환

```ruby
m1 = "kingsman"
#=> "kingsman"
m2 = "ironman"
#=> "ironman"
m1 <=> m2
#=> 1
m3 = "ironman"
m2 <=> m3
#=> 0
m2 <=> m1
#=> -1
```
- - -

## Blocks
블록은 처리를 하나의 단위로 묶은 것으로, 메소드 호출 시 한번만 지정할 수 있는 인수의 일종이다.

- - -

## nil
: one of two non-true value in Ruby (=>nothing at all)
false 와 다르다.(=> not true)

- - -

## conditional assignment operator `||=`
using `||=`, the hash key's value is only set once(처음 지정한 것으로 지정된다.)
[참조페이지 바로가기](http://www.rubyinside.com/what-rubys-double-pipe-or-equals-really-does-5488.html)
- - -

## Yield 
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
