## Array

```ruby
array1=[1,2,3]
array2=[true,2,"a",[1,2,3,4]]
```
배열에는 다양한 형태의 데이터 타입(boolean, number, string, array)을 같이 쓸 수 있다.

### - 배열의 접근방법
index를 통해서 접근 할 수 있다!
배열의 index는 **0**부터 시작해 **배열의 크기-1** 까지가 범위이다.
> `arr=[1,2,3,4,5]`
> 
> | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|
|arr[0]| arr[1] | arr[2] | arr[3] | arr[4] |

```ruby
arr = [1,"a",3,"b",true]
#=> [1, "a", 3, "b", true]
arr
#=> [1, "a", 3, "b", true]
arr[0]
#=> 1
arr[4]
#=> true
```
- - -

## Hashes

 : a collection of key-value pairs

### hash 생성방법
```ruby
hash = {
  key1 => value1,
  key2 => value2,
  key3 => value3
}
```
`=>`hash rocket를 이용해서 key를 지정해준다.
```ruby
my_hash = Hash.new
my_hash["key"] = "value"

# Hash는 반드시 H가 대문자여야한다.

# default value 지정
h=Hash.new(“default value”)
```

##### hash  value에 접근하는 방법
```ruby
hash = "key"
```

### Symbol(:)
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

### hash rocket(=>)에서 문법이 바뀜
```ruby
new_hash = {
  key1: value1,
  key2: value2,
  key3: value3
}
```
- - -
