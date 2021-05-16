# Template Method Pattern

![https://www.cs.unc.edu/~stotts/GOF/hires/Pictures/tmethod.gif](./assets/tmethod.gif)

상속을 통해 Super Class의 기능을 확장할 때 사용하는 가장 대표적인 방법이다. 
Super Class에서 추상 메소드 또는 오버라이드 가능한 메소드를 정의해두고 이를 활용해 코드의 기본 알고리즘을 담고 있는 템플릿 메소드를 만든다. 이렇게 서브 클래스에서 선택적으로 오버라이드할 수 있도록 만들어둔 메소드를 hook(훅) 메소드라고 한다.

```java
public abstract class Super{
  public void templateMethod() {
    // 기본 알고리즘 코드
    hookMethod();
    abstractMethod();
  }
  protected void hookMethod(){ } // 선택적으로 오버라이드 가능한 훅메소드
  public abstract void abstractMethod(); // 반드시 SubClass에서 구현해야하는 추상 메소드
}
```
```java
public Sub extends Super{
  @Override
  protected void hookMethod(){
    //...
  }
  @Override
  public void abstractMethod(){
    //...
  }
}
```

**전체적으로는 동일하면서 부분적으로는 다른 구문으로 구성된 메서드의 코드 중복을 최소화** 할 때 유용하다. **즉, 변경될 기능은 Super Class에 만들어두고 자주 변경되며 확장할 기능을 SubClass에 만들때 사용하면 좋다.**

예를 들어, 각 회사별로 동일한 EP 데이터를  전달해야 하는 경우에 Template(Super Class)를 생성해두고, 해당 Template을 상속받아 확장할 기능을 Sub Class에서 각각 처리하는 경우에 사용할 수 있다.



## 예시

붕어빵을 만드는 과정을 생각해보자. 슈프림 붕어빵, 팥 붕어빵, 초코 붕어빵 등 원하는 재료를 안에 넣을 수 있다.

```java
public abstract class BoongABangTemplate{
  // final 선언으로 Override 금지
  public final void makeBoongABang(){
    buyOven();
    makeIngredient();
    secretRecipe();
    bake();
  }
  
  protected void buyOven(){}; // 같은 오븐을 살지는 선택할 수 있음.

  // 붕어빵안에 재료랑 굽는거는 각자 구현 필요
  public abstract void makeIngredient();
  public abstract void bake();
  
  // 기본으로 구현, 못바꿈!
  private void secretRecipe(){
    System.out.println("비법");
  };
}
```

```java
public PuffBoongABbang extends BoongABangTemplate{
  @Override
  public abstract void makeIngredient(){
     System.out.println("반죽을 꾸덕하게 만든다.");
     System.out.println("슈크림을 만든다.");
  };
  
  @Override
  public abstract void bake(){
     System.out.println("100도에 붕어빵을 바삭하게 2분 굽는다.");
  };
}
```

```java
public RedBeanBoongABbang extends BoongABangTemplate{

  @Override
  protected void buyOven(){
     System.out.println("최신 붕어빵틀을 산다."); 
  }
  
  @Override
  public abstract void makeIngredient(){
     System.out.println("반죽을 묽게 만든다.");
     System.out.println("팥을 만든다.");
  };
  
  @Override
  public abstract void bake(){
     System.out.println("100도에 붕어빵을 바삭하게 2분 굽는다.");
  };
}
```





## 참고

- [좋은 사람의 개발노트](https://niceman.tistory.com/142)