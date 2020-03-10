스프링에서 Proxy를 이용해 AOP 구현을 하고 있다. 

스프링에서 AOP를 구현할 수 있는 방법은 크게 두가지 방법이 있다.

1. xml
2. annotation

두 가지 구현 방법에 대해서 정리해 볼 것이다.

## XML 기반 구현

### AOP 설정구조

```xml
<aop:config>
	<aop:pointcut />			<!-- pointcut설정 -->
    <aop:aspect>				<!-- aspect설정 -->
        <aop:before />			<!-- method 실행 전 -->
        <aop:after-returning />	<!-- method 정상 실행 후 -->
        <aop:after-throwing />	<!-- method 예외 발생 시 -->
        <aop:after />			<!-- method 실행 후(예외발생 여부 상관 없음) -->
        <aop:around />			<!-- 모든 시점 적용 가능 -->
    </aop:aspect>
    
</aop:config>
```

```xml
<aop:config proxy-target-class="false"> 
<!--proxy-targetclass=true인 경우 CGLIB 사용, false인 경우 proxy-->
</aop:config>
```



## Annotation 구현





#### 참조 페이지

- [http://addio3305.tistory.com/86](http://addio3305.tistory.com/86)
- [http://private.tistory.com/43](http://private.tistory.com/43)
- [https://steemkr.com/kr-dev/@nhj12311/aop-jdk-dynamic-proxy-java-aop-2](https://steemkr.com/kr-dev/@nhj12311/aop-jdk-dynamic-proxy-java-aop-2)

