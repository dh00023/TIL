# Web Server & WAS



![https://gmlwjd9405.github.io/images/web/static-vs-dynamic.png](./assets/static-vs-dynamic.png)

## Web Server

- 웹서버 = HTTP 프로토콜(GET, POST, DELETE)로 요청이 왔을때 응답
- 정적인 데이터만 처리한다.(HTML,CSS, JS, 이미지, 영상 등)
- 정적 리소스 제공, 기타 부가기능
- port:80
- Ngnix, Apache

### Apache

아파치 소프트웨어 재단의 오픈소스 프로젝트이다. 일명 **웹서버**로 불리며, 클라이언트 요청이 왔을때만 응답하는 **정적 웹페이지**에 사용된다.

아파치만 쓰면 정적인 웹페이지만 처리하므로 처리속도가 매우 빠르고 안정적이다.

## WAS(Web Application Service)

- HTTP 기반 동작
- 웹 서버 기능 포함 ( + 정적 리소스 제공 가능 )
- 컨테이너, 웹 컨테이너, 서블릿 컨테이너라고 부름
- 프로그램 코드를 실행하여 애플리케이션 로직 수행
  - 동적 HTTP, HTTP API(JSON)
  - JSP, Servlet, HTTP요청 수신 및 응답
  - 동적인 데이터 처리 가능(DB 연결, 데이터 조작, 다른 응용프로그램과 상호작용)
- port:8080
- Tomcat, Jetty, Undertow

### Apache  Tomcat

Tomcat은 **dynamic(동적)인 웹을 만들기 위한 웹 컨테이너, 서블릿 컨테이너**라고 불리며, 웹서버에서 정적으로 처리해야할 데이터를 제외한 JSP, ASP, PHP 등은 웹 컨테이너(tomcat)에 전달한다. 

Tomcat은 흔히 **WAS(Web Application Service)**라고 하며, **웹 서버와 웹 컨테이너의 결합**으로 다양한 기능을 컨테이너에 구현하여 다양한 역할을 수행한다.

## Web Server(Apache) vs WAS(Apache Tomcat)

![https://gmlwjd9405.github.io/images/web/web-service-architecture.png](./assets/web-service-architecture.png)

Apache(Web Server)와 Apache Tomcat(WAS)를 구분하는 이유는 뭘까?

- Web Server가 필요한 이유?
  Web Server를 통해 **정적인 파일들을 Application Server까지 가지 않고 앞단에서 빠르게 보내줄 수 있다.**
  따라서 Web Server에서는 정적 컨텐츠만 처리하도록 기능을 분배하여 서버의 부담을 줄일 수 있다.
- WAS가 필요한 이유?
  사용자의 요청에 맞게 적절한 동적 컨텐츠를 만들어서 제공해야 한다. 이때, Web Server만을 이용한다면 사용자가 원하는 요청에 대한 결과값을 모두 미리 만들어 놓고 서비스를 해야 한다. 하지만 이렇게 수행하기에는 자원이 절대적으로 부족하다. 따라서  **WAS를 통해 요청에 맞는 데이터를 DB에서 가져와서 비즈니스 로직에 맞게 그때 그때 결과를 만들어서 제공함으로써 자원을 효율적으로 사용**할 수 있다.
-  WAS와 Web Server의 분리 이유
  - **서버 부하 방지**
    WAS는 DB 조회나 다양한 로직을 처리하느라 바쁘기 때문에 단순한 정적 컨텐츠는 Web Server에서 빠르게 클라이언트에 제공하는 것이 좋다. WAS는 기본적으로 동적 컨텐츠를 제공하기 위해 존재하는 서버이다. 만약 정적 컨텐츠 요청까지 WAS가 처리한다면 정적 데이터 처리로 인해 부하가 커지게 되고, 동적 컨텐츠의 처리가 지연됨에 따라 수행 속도가 느려진다. 즉, 이로 인해 페이지 노출 시간이 늘어나게 될 것이다.
  - SSL에 대한 암복호화 처리에 Web Server를 사용해 물리적으로 분리하여 **보안 강화**
  - **여러 대의 WAS를 연결** 가능
    특히 대용량 웹 어플리케이션의 경우(여러 개의 서버 사용) Web Server와 WAS를 분리하여 무중단 운영을 위한 장애 극복에 쉽게 대응할 수 있다.
    예를 들어, 앞 단의 Web Server에서 오류가 발생한 WAS를 이용하지 못하도록 한 후 WAS를 재시작함으로써 사용자는 오류를 느끼지 못하고 이용할 수 있다.
  - 여러 웹 어플리케이션 서비스 가능

즉, 자원 이용의 효율성 및 장애 극복, 배포 및 유지보수의 편의성 을 위해 Web Server와 WAS를 분리한다.
**Web Server를 WAS 앞에 두고 필요한 WAS들을 Web Server에 플러그인 형태로 설정하면 더욱 효율적인 분산 처리가 가능**하다.

## 참조 페이지

- [[Web] Web Server와 WAS의 차이와 웹 서비스 구조](https://gmlwjd9405.github.io/2018/10/27/webserver-vs-was.html)
- [아파치 톰캣이란 ?](https://wodonggun.github.io/wodonggun.github.io/study/아파치-톰캣-차이.html)
- [망나니 개발자](https://mangkyu.tistory.com/14)

