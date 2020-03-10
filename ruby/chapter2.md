## 조건문
### `if`/`else`/`elsif`/`end` 
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
### `unless`/`else`/`end`
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

### `case`/`when`/`else`/`end`
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
### ternary conditional expression
```ruby
boolean ? Do this if true: Do this if false
```
```ruby
puts 3 < 4 ? "3 is less than 4!" : "3 is not less than 4."
```
- - -

## Comparators
### relational operator
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

### logical operator
* `&&` : and (둘다 true 이면 true)
* `||` : or (둘중 하나만 true 이면 true)
* `!` : not (반대)
- - -
