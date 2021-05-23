# 개발 환경 설정

### JDK 설치

**JSP**및 **Servlet**은 JAVA를 기본언어로 사용됩니다. JAVA언어로 작성한 프로그램을 컴파일하기 위해서는 JDK(Java Development Kit)가 필요 하다.

### 이클립스 다운로드

### 톰캣 다운로드

[tomcat 다운로드](https://tomcat.apache.org/download-80.cgi) 에서 tar.gz를 다운로드 한다.

```bash
$ sudo mv ~/Downloads/apache-tomcat-8.5.31 /usr/local/
$ sudo rm -f /Library/Tomcat
$ sudo ln -s /usr/local/apache-tomcat-8.5.31/ /Library/Tomcat
$ sudo chown -R <user_name> /Library/Tomcat 
$ sudo ln -s /usr/local/apache-tomcat-8.5.31/ /Library/Tomcat
$ sudo chmod +x /Library/Tomcat/bin/*.sh
# 시작하기
$ /Library/Tomcat/bin/startup.sh
# 종료하기
$ /Library/Tomcat/bin/shutdown.sh
```

http://localhost:8080 으로 접속해 아래와 같은 이미지가 보이면 성공한 것이다.

![](images/3.png)

http://wonsama.tistory.com/410 참조



### 이클립스 아파치 톰캣 연동하기

servers를 열어 새로운 server를 추가해준다.

![](images/4.png)

설치해둔 tomcat 서버와 연동해준다.

![](images/5.png)

![](images/6.png)

성공적으로 연동이 되면 아래와 같이 뜬다.

![](images/7.png)

이때 더블클릭해서 세부사항을 수정해준다.

1. Server Locations에서 Use Tomcat installation으로 클릭해 내가 설치한 경로와 같게 바꿔준다.
2. public module contexts to separate XML files를 추가 클릭해준다.
3. HTTP port를 이후에 이용할 DB서버와 겹치지 않도록 8181로 변경해준다.

![](images/8.png)

이후에 http://localhost:8181로 접속해 성공이미지가 뜬다면 성공한 것이다.



## intellij + spring web을 이용한 환경설정

spring을 사용할 일은 없지만, 기본적으로 내장 tomcat이 있는 spring web으로 환경설정을 하면 더욱 간편하게 설정할 수 있다.

[https://start.spring.io/](https://start.spring.io/) 에서 다음과 같이 프로젝트를 생성한다.

![스크린샷 2021-05-23 오후 9.18.35](./assets/스크린샷 2021-05-23 오후 9.18.35.png)

여기서 jsp를 사용하기 위해 Packaging은 `War` 를 선택했으며, `Spring Web`은 내장 톰켓을 사용하기 위해서 추가했다.

추가로 Build Tools에서 Gradle - Build and run설정을  `Gradle`에서  `IntelliJ IDEA` 로 변경해 준다. (현재 기준 더 빠름)

![스크린샷 2021-04-11 오후 10.36.27](./assets/스크린샷 2021-04-11 오후 10.36.27.png)