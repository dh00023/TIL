## Class

### 정의

```ruby
class NewClass
end
```
```ruby
class NewClass; end
```

* 클래스 명은 영문 대문자로 시작해야한다.
### 인스턴스

* (인스턴스) 메소드 = 클래스 정의 내에 정의한 메소드는 해당 클래스의 **인스턴스**로 호출될 수 있다. 
```ruby
class Myclass
    def hello
      puts 'Hello'
    end
end
```

- 인스턴스 생성 / 호출

```ruby
클래스명.new
my_object = Myclass.new
my_object.hello
```

* class는 상속하거나 상속 될 수 있다.
루비는 기본형이 존재하지 않고 모든 것이 객체이다. 

```ruby
p 1.to_s
#=> "1"

p true.to_s
#=> "true"
```

1과 같은 숫자나 true/false와 같은 진릿 값도 객체이다. 객체이기 때문에 메소드도 호출 할 수 있다.

```ruby
p 'hello'.class
#=> String
p String.ancestors
#=> [String, Comparable, Object, Kernel, BasicObject]
p 10.class
#=> Integer
Integer.ancestors
#=> [Integer, Numeric, Comparable, Object, Kernel, BasicObject]
p true.class
#=> TrueClass
TrueClass.ancestors
#=> [TrueClass, Object, Kernel, BasicObject]
```

문자열, 수치 뿐만 아니라 true/false, nil과 같은 객체에도 클래스가 존재한다. Object의 클래스의 자식 관계로 구성된다.

BasicObject가 최상위 클래스이다.



### 변수와 상수

#### 지역변수

스코프(참조 가능 범위)가 가장 좁은 종류의 변수다. 지역 변수명은 `ruby`나 `_ruby`처럼 첫글자는 소문자 영어 또는 언더바여야한다.

- 블록
- 메소드 정의
- 클래스/모듈 정의
- 톱 레벨

스코프 밖에 있는 지역변수를 참조하면 에러가 발생한다. 블록 안이면 블록 밖에서 정의된 지역 변수를 참조할 수 있지만, 반대로 블록안에서 정의된 지역 변수는 블록 밖에서 참여할 수 없다.

```ruby
greeting = "Hello, "
people = %w[다혜 현경 현진]

people.each do |p|
	puts greeting + p
end
#=> Hello, 다혜
#=> Hello, 현경
#=> Hello, 현진

puts p
#=> nil
```

#### 전역변수($)

어디에서든 참조 및 변경이 가능한 변수이다. 프로그램 규모가 커지면 커질수록 전역 변수가 존재하는 코드는 해석이 어려워진다.

정말로 필요한 경우가 아니라면 사용을 자제하는 것이 좋다.

```ruby
$lion = "like"
$undefined
#=> nil
```

`$undefined`와 같이 존재하지 않는 전역변수를 참조하면 `nil`이 반환된다.

#### 인스턴스 변수(@)

 인스턴스 내에서만 참조할 수 있는 변수이다. 이것을 사용해서 객체의 상태를 저장할 수 있다. 외부에서 인스턴스 변수에 접근하려면 별도의 메소드를 정의해야한다.

```ruby
# setter
class Ruler
    def length=(val)
        @length = val
    end
    
    def length
        @length
    end
end

ruler = Ruler.new

ruler.length = 30
ruler.length
```

설명을 위해서 메소드를 정의했으나 실제로는 `attr_accessor`를 이용한다.

```ruby
class Ruler
    attr_accessor :length
end
```

를 하면 Ruler#length=라는 인스턴스 변수가 정의된다.



#### 클래스 변수(@@)

클래스와 해당 인스턴스를 범위로 하는 변수이다.

클래스 변수는 클래스 정의 안이나 클래스 메소드에서 참조할 수 있다.

```ruby
class MyClass
    @@cvar = 'class variable'
    
    def cvarin
        puts @@cvar
    end
    def self.cvarin_class
        puts @@cvar
    end
end
```



### self

self는 인스턴스를 참조한다. 메소드 내부에서 receiver를 생략하면 default로 self가 리시버가 된다.

```ruby
class Ruler
    attr_accessor :length
    def set_default_length
        self.length = 30
        #self를 생략하면 length라는 지역변수가 선언됨
    end
end
```

### 초기화(생성자)

인스턴스를 생성할 때 인스턴스 초기화가 필요한 경우가 있다. 이때 `initialize` 메소드를 정의하면 된다.

```ruby
class Car
  def initialize(make, model)
    @make = make
    @model = model
  end
end
```
- Create an instance of class .new

```ruby
kitt = Car.new("Pontiac", "Trans Am")
```



### 클래스 메소드

클래스 메소드는 메소드명 앞에 `self`를 붙여서 정의한다.

```ruby
class Ruler
    attr_accessor :length
    def self.pair
		[Ruler.new, Ruler.new]
    end
end

Ruler.pair
#=> [#<Ruler:0x00007ff8530e86b8>, #<Ruler:0x00007ff8530e8690>]
```

클래스 메소드 안에 있는 self는 해당 메소드가 속해 있는 클래스를 가리킨다. 클래스 메소드는 클래스 명으로 접근 할 수 있다.



### Inheritance (상속) `<`
```ruby
class 서브 클래스 < 슈퍼 클래스명
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
   # 오버라이딩
    def fight
        return "Breathes fire!"
    end
end
```

#### 오버라이드

super 클래스에서 이미 정의된 메소드를 sub 클래스에서 다시 정의하는 것을 메소드 오버라이드라고한다.

#### `super` 

super는 부모클래스(super class)에 정의되어있는 initialize, 메소드를 호출할 수 있다.
```ruby
class DerivedClass < Base
  def some_method
    super(optional args)
      # Some stuff
    end
  end
end
```

### Public and Private

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

### `attr_reader` / `attr_writer` /`attr_accessor`

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

## module 
인스턴스화 할 수 없는 클래스와 같은 것이다.
	
```ruby
module ModuleName
  # Bits 'n pieces
end
```

### ModuleName규칙
-모듈은 시작할때 대문자! ex)Math
-모듈의 constant는 모든 문자를 대문자로 ex)PI

- 내포한 클래스나 모듈은 `::`를 통해서 접근할 수 있다.

 ```ruby
Math::PI
 ```
모듈 내에서도 메소드를 정의할 수 있다. 그러나 클래스에 정의한 메소드랑은 다른 용도로 사용된다.

1. 특정 메소드를 인스턴스 메소드로 포함
2. 특정 객체의 메소드로 포함
3. 모듈 함수 사용

--`require`
: already present in the interperter
```ruby
require ‘module’
```


### Mixin 
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
