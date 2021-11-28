# 스프링 웹 플럭스(WebFlux)

- Spring Framwork5에서 새로 추가된 모듈
- 비동기 non-blocking 처리
- 최소 쓰레드로 최대 성능(thread context 스위칭 비용 효율화)
- 함수형 스타일로 개발(동시 처리 코드 효율화)
- 서블릿 기술 사용X
- 실무에서 아직 많이 사용하고 있지는 않음.

## Reactive Stream

> The purpose of Reactive Streams is to provide a standard for asynchronous stream processing with non-blocking backpressure.

[www.reactive-streams.org](http://www.reactive-streams.org/) 에서  "**Reactie Stream의 목적은 non-blocking backpressure를 이용하여 비동기 스트림 처리의 표준을 제공하는 것이다.**" 라고 표현하고 있다.

### BackPressure

> 한 컴포넌트가 부하를 이겨내기 힘들 때, [시스템](https://www.reactivemanifesto.org/ko/glossary#System) 전체가 합리적인 방법으로 대응해야 한다. 과부하 상태의 컴포넌트에서 치명적인 장애가 발생하거나 제어 없이 메시지를 유실해서는 안 된다. 컴포넌트가 대처할 수 없고 장애가 발생해선 안 되기 때문에 **컴포넌트는 상류 컴포넌트들에 자신이 과부하 상태라는 것을 알려 부하를 줄이도록 해야 한다. 이러한 배압은 시스템이 부하로 인해 무너지지 않고 정상적으로 응답할 수 있게 하는 중요한 피드백 방법**이다. 배압은 사용자에게까지 전달되어 응답성이 떨어질 수 있지만, 이 메커니즘은 부하에 대한 시스템의 복원력을 보장하고 시스템 자체가 부하를 분산할 다른 자원을 제공할 수 있는지 정보를 제공할 것이다. [탄력성 (확장성과 대조)](https://www.reactivemanifesto.org/ko/glossary#Elasticity) 참조.  *[리액티드 선언문 용어집](https://www.reactivemanifesto.org/ko/glossary#Back-Pressure)

### 논 블로킹(Non-Blocking)

> 동시성 프로그래밍에서는 자원을 경쟁하는 스레드가 자원을 보호하는 상호 배제로 무기한 연기되지 않도록 논 블로킹 알고리즘이 고려된다. 일반적으로 이것은 API로 선언되는데, 만약 [자원](https://www.reactivemanifesto.org/ko/glossary#Resource) 이 사용 가능하다면 접근을 허용하고 그렇지 않다면 현재 자원을 사용할 수 없다는 응답이나 작업이 시작되었지만, 아직 완료되지 않았음을 호출자에게 즉시 반환한다. 자원에 대한 논 블로킹 API를 사용하면 호출자가 자원을 사용할 수 있을 때까지 기다리지 않고 다른 작업을 수행할 수 있다. 자원을 사용하려는 클라이언트를 등록하여 자원이 사용 가능해지거나 작업이 완료될 때가 알림을 받을 수 있도록 보완할 수 있다.  *[리액티드 선언문 용어집](https://www.reactivemanifesto.org/ko/glossary#Back-Pressure)

### Goals, Design and Scope

계속적으로 들어오는 스트림 데이터를 효율적으로 처리하기 위해서는 비동기 시스템이 효과적이다.
비동기 처리를 하면서 가장 중요한 것은 **데이터 처리가 목적지의 리소스 소비를 예측가능한 범위에서 제어할 수 있어야 하는 것**이다.

- 비동기는 네트워크를 통한 서버간의 협업 또는 단일 서버에서 컴퓨팅 리소스를 동시에 사용할 때 주로 사용

**Reactive Stream의 주된 목적은 비동기의 경계를 명확히하여 스트림 데이터의 교환을 효과적으로 관리하는것**에 있다. 즉, 비동기로 데이터를 처리하는 시스템에 어느정도의 data가 들어올 지 예측 가능하도록 하는 것이다. Reactive Stream에서는 **BackPressure** 가 이를 가능하게 해주는 핵심이다.

1. 잠재적으로 무한한 숫자의 데이터 처리
2. 순서대로 처리
3. 컴포넌트간에 데이터를 비동기적으로 전달
4. backpressure를 이용한 데이터 흐름제어



## 참고

- https://godekdls.github.io/Reactive%20Spring/springwebflux/
- 

