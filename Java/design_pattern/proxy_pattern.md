# Proxy Pattern

![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/75/Proxy_pattern_diagram.svg/800px-Proxy_pattern_diagram.svg.png)

Proxy 패턴을 UML로 살펴보면, 같은 인터페이스를 구현하고 있는 실제 요청처리 객체(real subject)와 프록시객체를 만들고, 프록시 객체가 실제 요청 처리객체를 가지고 있는 구조이다.

여기서의 Proxy는 target의 기능을 확장하거나 추가하지 않으며, 대신 클라이언트가 target에 접근하는 방식을 변경해준다. 즉, **target의 기능 자체에는 관여하지 않으면서 접근하는 방법을 제어해주는  Proxy를 이용**한것이다.



즉, **프록시는 클라이언트와 사용 대상 사이에 대리 역할을 맡은 object를 두는 방법을 총칭 하는 것이며, Proxy 패턴은 target에 대한 접근 방법을 제어하려는 목적을 가지고 Proxy를 사용하는 패턴**이다. 

실제 로직과 인과관계 처리를 분리하여 프로그래밍을 할 수 있으며, 지연, 초기화 등의 기법도 실제 로직을 담당하는 객체를 수정하지 않고 사용할 수 있게 해준다.

Spring AOP에서는 Dynamic Proxy기법을 이용해 AOP를 구현한다.



# Decolater Pattern

target에 부가적인 기능을 런타임 시 다이나믹하게 부여해주기 위해 Proxy를 사용하는 패턴이다. 데코레이터 패턴은 상속 없이 새로운 기능을 추가하기 위하여 객체를 wrapping하는 것이다.