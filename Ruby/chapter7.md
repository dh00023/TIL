
## Class

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

### Inheritance (상속) `<`
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

### `super` 
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
a toolbox that contains a set methods and constants
	
```ruby
module ModuleName
  # Bits 'n pieces
end
```

### ModuleName규칙
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
