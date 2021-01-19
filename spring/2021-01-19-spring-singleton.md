# Spring Singleton

Spring에서의 singleton pattern을 알아보기 이전에 

- [Singleton 디자인패턴](https://github.com/dh00023/TIL/blob/master/Java/design_pattern/singleton_pattern.md)
- [Item3 - Singleton](https://github.com/dh00023/TIL/blob/master/Java/effective_java/2021-01-14-singleton.md)

를 선행하면 더 이해하는데 좋다.

## Spring에서의 Singleton Pattern

spring의 bean들은 Bean Factory에 의해서 관리되고 있으며, 기본적으로 이러한 bean의 생명주기의 scope는 singleton을 따르고 있다.

Spring Boot에서는 별도의 설정이 없다면, `DefaultListableBeanFactory`를 기본으로 사용하며, `resolveBean` 메소드를 보면 알 수 있다.

```java
    @Nullable
    private <T> T resolveBean(ResolvableType requiredType, @Nullable Object[] args, boolean nonUniqueAsNull) {
        // 1. 등록되어있는 bean들의 이름을 검색
        NamedBeanHolder<T> namedBean = resolveNamedBean(requiredType, args, nonUniqueAsNull);

        // 2. 등록되어있다면 해당 bean을 리턴(인스턴스)
        if (namedBean != null) {
            return namedBean.getBeanInstance();
        }

        // 3. 다른 beanfactory에서 요청한 bean 찾기    
        BeanFactory parent = getParentBeanFactory();
        if (parent instanceof DefaultListableBeanFactory) {
            return ((DefaultListableBeanFactory) parent).resolveBean(requiredType, args, nonUniqueAsNull);
        }
        else if (parent != null) {
            ObjectProvider<T> parentProvider = parent.getBeanProvider(requiredType);
            if (args != null) {
                return parentProvider.getObject(args);
            }
            else {
                return (nonUniqueAsNull ? parentProvider.getIfUnique() : parentProvider.getIfAvailable());
            }
        }
        // 4. 찾지 못했을 시 null 반환
        return null;
    }
```

하지만 여기에서는 private static 접근 제어자를 통한 singleton 패턴은 찾아볼 수 없다. 

### 안티 패턴

안티 패턴이란, 습관적으로 많이 사용하는 패턴이지만 성능, 디버깅, 유지보수, 가독성 측면에서 부정적인 영향을 줄 수 있어 지양하는 패턴이다.

Singleton 패턴은 다음과 같은 단점이 있다.

1. private 생성자를 가지고 있어 상속을 할 수 없다.( 다형성 제공 불가능, 객체지향 설계 적용 불가)
2. 테스트가 어렵다.
3. 서버환경에서는 1개의 instance를 보장하지 못한다.
4. 전역 상태를 만들 수 있기 때문에 바람직하지 못하다.
	- singleton은 어디에서든지 누구나 접근해 사용할 수 있으므로, 객체지향에서 권장하지 되지 않는 프로그래밍 모델이다.

이러한 이유로 Spring에서 직접 싱글톤 패턴을 사용하지 않으며, **Singleton Registry** 방식을 사용한다.

## 참고

- [https://sabarada.tistory.com/25](https://sabarada.tistory.com/25)