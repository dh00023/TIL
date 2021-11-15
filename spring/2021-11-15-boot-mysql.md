# MySql 연동하기

## Dependency 설정

### Maven pom.xml

```xml
<dependency>
  <groupId>mysql</groupId>
  <artifactId>mysql-connector-java</artifactId>
  <scope>runtime</scope>
</dependency>
```

### Gradle build.gradle

```js
dependencise {
  implementation 'mysql:mysql-connector-java'
}
```



## 프로퍼티 설정

### application.yml

```yaml
spring:
  datasource:
    driver-class-name: com.mysql.cj.jdbc.Driver
    url: jdbc:mysql://localhost:3306/spring_batch
    username: test
    password: 비밀번호
```

