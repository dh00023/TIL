## Proc

- Procs are full-fledged objects, so they have all the powers and abilities of objects. (Blocks do not.)
- Unlike blocks, procs can be called over and over without rewriting them. This prevents you from having to retype the contents of your block every time you need to execute a particular bit of code.

```ruby
cube = Proc.new{ |x| x ** 3 }
```
```ruby
[1, 2, 3].collect!(&cube)
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

## Lambda

```ruby
lambda { |param| block }
```
```ruby
lambda { puts "Hello!" } == Proc.new { puts "Hello!" }
```

### proc과 lambda의 차이
1. argument 가 오류가 났을때 proc은 무시하고 nil처리 후 넘어가는데 lambda는 오류가난다.
2. lambda는 call이 되면 다시 마지막 코드로 돌아가는데  proc은 끝난다.
- - -

## Scope
1. global variables : available everywhere
2. local variables : available certain methods
3. class variables : members of a certain class
4. instance variables : only available to particular instances of a class
- - -
