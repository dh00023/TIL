## Loop(반복문)
### while
: while은 조건이 만족되면 loop가 돌아간다.
```ruby
while 조건
# write something
end
```
```ruby
while a < 5
	puts a
	a += 1
end
# 0
# 1
# 2
# 3
# 4
```
### until
: until은 조건이 만족될때 까지 loop가 돌아간다.
```ruby
until 조건
# write something
end
```
```ruby
a=0
#=> 0
until a == 5
	puts a
    a += 1
end
# 0
# 1
# 2
# 3
# 4
```

##### for
```ruby
for num in 1...10
  puts num
end
```
```ruby
for num in 1...3
	puts num
end
# 1
# 2
#=> 1...3
for num in 1..3
	puts num
end
# 1
# 2
#3
#=> 1..3
```
> `1...3`은 3을 포함하지않고 `1..3`은 3을 포함하는 것을 볼 수 있다.

### loop
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
```ruby
for i in 1..10
	next if i % 2 ==0
    puts i
end
# 1
# 3
# 5
# 7
# 9
# 1..10
```
> 예시를 보면 i % 2 == 0 인 2, 4, 6, 8, 10 부분은 넘어간 것을 확인 할 수 있다.

- - -
