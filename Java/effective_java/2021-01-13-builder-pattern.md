# ITEM 2: CONSIDER A BUILDER WHEN FACED WITH MANY CONSTRUCTOR PARAMETERS 

생성자와 정적 팩토리는 **선택적 매개변수가 많을 때 적절히 대응하기 어렵다.** 선택적 매개 변수가 많은 경우에 사용하는 생성자 패턴에 대해서 살펴 볼 것이다.

## 생성자 패턴 1. 점층적 생성자 패턴

점층적 생성자 패턴(telescoping constructor pattern)은 다음과 같이 필수 인자를 받는 생성자를 정의한 후, 선택적인자를 하나씩 추가해가며 정의하는 것이다. 

```java
public class Item {
  private final String itemCd; // 필수
  private final String itemNm; // 필수
  private final String ctgId;  // 필수
  private final BigDecimal price; // 선택
  private final String sellTypeCd; // 선택
  
  public Item(String itemCd, String itemNm, String ctgId){
    this(itemCd, itemNm, ctgId, 0);
  }
  
  public Item(String itemCd, String itemNm, String ctgId, BigDecimal price){
    this(itemCd, itemNm, ctgId, price, "10");
  }
  
  public Item(String itemCd, String itemNm, String ctgId, BigDecimal price, String sellTypeCd){
    this.itemCd = itemCd;
    this.itemNm = itemNm;
    this.ctgId = ctgId;
    this.price = price;
    this.sellTypeCd = sellTypeCd;
  }
  
}
```

예시에서는 인자가 5개라 간단해 보일 수 있지만, **매개변수가 더 늘어날 수록 코드를 작성하기 어려워지고, 가독성이 떨어지게 된다**. 

## 생성자 패턴 2. JavaBeans Pattern

자바빈즈 패턴은 매개변수가 없는 생성자로 객체를 만든 후 setter 메서들르 호출해 원하는 매개변수의 값을 설정하는 방식이다.

```java
public class Item {
    private String itemCd; // 필수
    private String itemNm; // 필수
    private String ctgId;  // 필수
    private BigDecimal price; // 선택
    private String sellTypeCd; // 선택

    public Item(){
    }
  
		public void setItemCd(String itemCd){ this.itemCd = itemCd; }
  	public void setItemNm(String itemNm){ this.itemNm = itemNm; }
  	public void setCtgId(String ctgId){ this.ctgId = ctgId; }
  	public void setPrice(BigDecimal price){ this.price = price; }
  	public void setSellTypeCd(String sellTypeCd){ this.sellTypeCd = sellTypeCd; }
  
}
```

```java
Item item = new Item();
item.setItemCd("12345678");
item.setItemNm("Effective Java 3/E");
item.setCtgId("9999");
item.setPrice("36000");
item.setSellTypeCd("20");
```

자바빈즈 패턴은 점층적 생성자 패턴의 단점을 보완해 인스턴스 생성이 쉽고, 더 가독성이 좋아졌다. 

하지만, **자바빈즈 패턴에서는 객체 하나를 만드려면 메서드를 여러 개 호출해야하고, 객체가 완전히 생성되기 전까지는 일관성(consistency)이 무너진 상태**에 있게 된다. 일관성이 깨지므로 자바빈즈 패턴에서는 클래스를 [불변]()으로 만들 수 없으며, 스레드 안정성을 얻으려면 개발자가 추가 작업을 해줘야한다. 이러한 단점을 보완하기 위해 `freeze` 메서드를 사용할 수 있으나, `freeze` 메서드를 확실히 호출해줬는지 컴파일러가 보증할 방법이 없어 런타임 오류에 취약하다.

## 생성자 패턴 3. Builder Pattern

빌더 패턴은 점층적 생성자 패턴의 안정성과 자바빈즈 패턴의 가독성을 겸비한 생성자 패턴이다.

```java
public class Item {
    private final String itemCd; // 필수
    private final String itemNm; // 필수
    private final String ctgId;  // 필수
    private final BigDecimal price; // 선택
    private final String sellTypeCd; // 선택

    public static class Builder {
      private final String itemCd; // 필수
    	private final String itemNm; // 필수
      private final String ctgId;  // 필수
      
      // 선택적 매개변수는 default 값으로 초기화
      private BigDecimal price = BigDecimal.ZERO; 
      private String sellTypeCd = "00";
      
      public Builder(String itemCd, String itemNm, String ctgId){
        this.itemCd = itemCd;
        this.itemNm = itemNm;
        this.ctgId = ctgId;
      }
      public Builder price(BigDecimal price){
        this.price = price;
        return this;
      }
      
      public Builder sellTypeCd(String sellTypeCd){
        this.sellTypeCd = sellTypeCd;
        return this;
      }
      
      public Item build(){
        return new Item(this);
      }
    }
  
  	private Item(Builder builder){
      itemCd = builder.itemCd;
      itemNm = builder.itemNm;
      ctgId = builder.ctgId;
      price = builder.price;
      sellTypeCd = builder.sellTypeCd;
    }
  
}
```

```java
Item item = new Item.Builder("12345678", "Effective Java 3/E", "9999").price(36000).sellTypeCd("90").build();
```

클라이언트는 필수 매개변수만으로 생성자를 호출해 빌더 객체를 얻고, 빌더 객체가 제공하는 setter 메서드들로 원하는 선택 매개변수들을 설정할 수 있다. 마지막으로 매개변수가 없는 `build()` 메서드를 호출해 필요한 객체를 얻을 수 있다. 이렇게 연쇄적으로 메서드를 호출하는 방법을 **fluent API** or **method chaining**이라 한다.

> 불변 : 어떠한 변경도 허용하지 않는다. 대표적으로 String 객체는 한번 만들어지면 절대 값을 바꿀 수 없는 불변 객체
>
> 불변식 : 프로그램이 실행되는 동안(혹은 정해진 기간) 반드시 만족해야하는 조건을 말한다. 변경을 허용할 수 는 잇으나, 주어진 조건 내에서만 허용한다는 뜻이다.

불변식을 보장하기 위해서는 빌더로 부터 매개변수를 복사한 후 해당 객체 필드도 검사해야한다.([item50]()) 검사시 잘못된 점을 발견하면 어떤 매개변수가 잘못되었는지에 대한 메세지를 담아 `IllegalArgumentException` ([item75]()) 오류 발생을 해주면된다.

### 계층적으로 설계된 클래스

빌더 패턴은 계층적으로 설계된 클래스와 사용하기에 좋다.

```java
public abstract class Allnco {
  public enum ApiType { ADD_ITEM, UPDATE_ITEM, UPDATE_IMAGE, UPDATE_PRC }
  final Set<ApiType> apiTypes;
  
  abstract static class Builder<T extends Builder<T>> {
    EnumSet<ApiType> apiTypes = EnumSet.noneOf(ApiType.class);
    
    public T addApiType(ApiType apiType){
      apiTypes.add(Objects.requireNonNull(apiType));
      return self();
    }
    
    abstract Allnco build();
    
    // 하위 클래스는 이 메서드를 overriding해 "this"를 반환하도록 구현해야함.
    protected abstract T self();
  }
  
  Allnco(Builder<?> builder){
    apiTypes = builder.apiTypes.clone();
  }
}
```

여기서 Allnco.Builder 클래스는 [재귀적 타입 한정]()을 이용하는 제네릭 타입이다. 여기에 추가적으로 추상 메서드인 `self()` 를 추가해 하위 클래스에서 형 변환 하지 않고도 method chaining을 할 수 있다.

```java

public class Gmarket extends Allnco{
    public enum Chnl { ONLINE, OUTLET, MART, DEPARTMENT, BUYING }
    private final Chnl chnl; // final -> immutable

    public static class Builder extends Allnco.Builder<Builder> {
        private final Chnl chnl;

        public Builder(Chnl chnl){
            this.chnl = Objects.requireNonNull(chnl);
        }

        @Override
        public Gmarket build(){
            return new Gmarket(this);
        }

        @Override
        protected Builder self(){
            return this;
        }
    }
    private Gmarket(Builder builder){
        super(builder);
        chnl = builder.chnl;
    }
}

```

```java
public class Naver extends Allnco{
    private final boolean isHapi;

    public static class Builder extends Allnco.Builder<Builder> {
        public boolean isHapi = false;

        public Builder connectToHapi(){
            isHapi = true;
            return this;
        }

        @Override
        public Naver build(){
            return new Naver(this);
        }

        @Override
        protected Builder self(){
            return this;
        }

    }
    private Naver(Builder builder){
        super(builder);
        isHapi = builder.isHapi;
    }
}
```

```java
Gmarket gmarket = new Gmarket.Builder(Gmarket.Chnl.MART).addApiType(Gmarket.ApiType.UPDATE_ITEM).addApiType(Gmarket.ApiType.UPDATE_PRC).build();

Naver naver = new Naver.Builder().addApiType(Naver.ApiType.ADD_ITEM).connectToHapi().build();
```

각각의 하위 클래스의 빌더가 정의한 `build` 메서드는 해당 하위 클래스(`Naver`, `Gmarket`)을 반환하도록 되어있다. 이렇게 하위 클래스의 메서드가 상위 클래스가 정의한 리턴 타입이 아닌, 그 하위 타입을 리턴하는 것을 **Convariant return typing**(공변 반환 타이핑)이라 한다. 이 기능으로 클라이언트가 형변환에 신경 쓰지 않고 빌더를 사용할 수 있다.



### 결론

빌더 패턴은 빌더 하나로 여러 객체를 만들 수 있고, 빌더에 넘기는 매개변수에 따라 다른 객체를 만들 수 있으므로 **매우 유연**하다.

하지만 객체를 만들려면, 그에 앞서 빌더부터 만들어야한다. 또한, 성능에 민감한 상황에서는 빌더 생성 비용이 문제가 될 수 있다. 또한 매개변수가 4개 이상이 되어야 값어치를 한다.

즉**, 인자가 많은 생성자**나 **정적 팩터리가 필요한 클래스를 설계**할 때, **대부분의 인자가 선택적 인자**인 상황에 유용하다.  빌더는 점층적 생성자보다 간결하고, 자바빈즈보다 훨씬 안전하다.