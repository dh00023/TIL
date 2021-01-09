# SOAP 통신 Client 실습

현재 제휴 업무를 하고 있는데, 특정 제휴사에서는 SOAP 통신을 이용해 상품연동을 하고 있어 SOAP 통신에 대해 알아보고, Client 서비스를 제공받는 쪽에서 어떻게 통신을 하는지 알아볼 것이다.


## 프로젝트 시작

[영화진흥위원회](http://www.kobis.or.kr/kobisopenapi/homepg/apiservice/searchServiceInfo.do) 의 OPEN API를 이용해서 데이터를 가져오는 부분을 이용해 개발을 진행할 것이다.

### wsdl2java

[WSDL을 JAVA로 변환하기](./2021-01-09-axis2-wsdl2java.md)에서 자세한 내용을 알 수 있다.
이번 프로젝트에서는 `axis2-1.7.9` version 1.7.9를 이용하여 변환했다.

```bash
$ ./wsdl2java.sh -u -uri http://www.kobis.or.kr/kobisopenapi/webservice/soap/boxoffice\?wsdl
 Using AXIS2_HOME: /Users/dh0023/Downloads/teste/axis2-1.7.9
 Using JAVA_HOME:  /Library/Java/Home
Retrieving document at 'http://www.kobis.or.kr/kobisopenapi/webservice/soap/boxoffice?wsdl'.
Retrieving document at 'http://www.kobis.or.kr:80/kobisopenapi/webservice/soap/boxoffice?wsdl=BoxOfficeAPIService.wsdl', relative to 'http://www.kobis.or.kr/kobisopenapi/webservice/soap/boxoffice?wsdl'.
Retrieving document at 'http://www.kobis.or.kr/kobisopenapi/webservice/soap/boxoffice?wsdl'.
Retrieving document at 'http://www.kobis.or.kr:80/kobisopenapi/webservice/soap/boxoffice?wsdl=BoxOfficeAPIService.wsdl', relative to 'http://www.kobis.or.kr/kobisopenapi/webservice/soap/boxoffice?wsdl'.
```

생성된 파일들을 Spring 프로젝트 하위로 Refactoring 해준다.


### pom.xml 설정

wsdl2java에서 파일을 변환한 버전으로 axis2를 설정해준다.

```xml
        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-kernel</artifactId>
            <version>1.7.9</version>
        </dependency>

        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-adb</artifactId>
            <version>1.7.9</version>
        </dependency>

        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-transport-local</artifactId>
            <version>1.7.9</version>
        </dependency>

        <dependency>
            <groupId>org.apache.axis2</groupId>
            <artifactId>axis2-transport-http</artifactId>
            <version>1.7.9</version>
        </dependency>
```

만약 pom.xml을 제대로 설정하지 않으면 아래와 같이 `java.lang.ClassNotFoundException:` 오류가 발생한다.

```console
java.lang.ClassNotFoundException: org.apache.axis2.transport.http.CommonsHTTPTransportSender
    at java.net.URLClassLoader.findClass(URLClassLoader.java:381)
    at java.lang.ClassLoader.loadClass(ClassLoader.java:424)
    at sun.misc.Launcher$AppClassLoader.loadClass(Launcher.java:331)
    at java.lang.ClassLoader.loadClass(ClassLoader.java:357)
    at java.lang.Class.forName0(Native Method)
    at java.lang.Class.forName(Class.java:264)
    at org.apache.axis2.util.Loader.loadClass(Loader.java:261)
    at org.apache.axis2.deployment.AxisConfigBuilder.processTransportSenders(AxisConfigBuilder.java:711)
    at org.apache.axis2.deployment.AxisConfigBuilder.populateConfig(AxisConfigBuilder.java:123)
    at org.apache.axis2.deployment.DeploymentEngine.populateAxisConfiguration(DeploymentEngine.java:629)
    at org.apache.axis2.deployment.FileSystemConfigurator.getAxisConfiguration(FileSystemConfigurator.java:116)
    at org.apache.axis2.context.ConfigurationContextFactory.createConfigurationContext(ConfigurationContextFactory.java:64)
    at org.apache.axis2.context.ConfigurationContextFactory.createConfigurationContextFromFileSystem(ConfigurationContextFactory.java:210)
    at org.apache.axis2.client.ServiceClient.configureServiceClient(ServiceClient.java:151)
    at org.apache.axis2.client.ServiceClient.<init>(ServiceClient.java:143)
    at kobisopenapi.apiservice.server.boxoffice.service.BoxOfficeAPIServiceImplServiceStub.<init>(BoxOfficeAPIServiceImplServiceStub.java:44)
    at kobisopenapi.apiservice.server.boxoffice.service.BoxOfficeAPIServiceImplServiceStub.<init>(BoxOfficeAPIServiceImplServiceStub.java:30)
    at kobisopenapi.apiservice.server.boxoffice.service.BoxOfficeAPIServiceImplServiceStub.<init>(BoxOfficeAPIServiceImplServiceStub.java:76)
    at kobisopenapi.apiservice.server.boxoffice.service.BoxOfficeAPIServiceImplServiceStub.<init>(BoxOfficeAPIServiceImplServiceStub.java:68)
    at com.example.movie.MovieApplication.main(MovieApplication.java:30)
org.apache.axis2.deployment.DeploymentException: org.apache.axis2.transport.http.CommonsHTTPTransportSender
Disconnected from the target VM, address: '127.0.0.1:63082', transport: 'socket'
```

#### 참고
- [Stackoverflow](https://stackoverflow.com/questions/320178/whats-the-minimum-classpath-for-an-axis2-client
http://www.kobis.or.kr/kobisopenapi/homepg/board/findTutorial.do?targetId=section_5)

#### 키발급

영화진흥위원회에서 키를 발급 받아야 API를 호출할 수 있다. 회원가입 후에 키 발급/관리 -> 키 발급받기를 하여 API Key를 발급받는다.

![](./assets/key발급.png)



#### API 호출 간략하게 해보기

```java
public class MovieApplication {

    public static void main(String[] args) {

        String secretKey = "{발급받은 키값}";

        try{

            SearchDailyBoxOfficeList list = new SearchDailyBoxOfficeList();
            list.setKey(secretKey);
            list.setMultiMovieYn("Y");
            list.setItemPerPage("10");
            list.setTargetDt("20201231");

            SearchDailyBoxOfficeListE entity = new SearchDailyBoxOfficeListE();
            entity.setSearchDailyBoxOfficeList(list);

            BoxOfficeAPIServiceImplServiceStub stub = new BoxOfficeAPIServiceImplServiceStub();
            SearchDailyBoxOfficeListResponseE result = stub.searchDailyBoxOfficeList(entity);
            result.getSearchDailyBoxOfficeListResponse();
        }catch(Exception e){
            System.out.println(e);

        }

    }



}
```

API 가이드 문서를 통해 필수 값을 입력하면 정상적으로 API 결과 값을 받아 올 수 있는것을 확인할 수 있다.

### spring sample

Spring에서 SOAP 웹서비스에 대한 샘플을 제공해준다.

- Producer(서비스 제공) : [https://spring.io/guides/gs/producing-web-service/](https://spring.io/guides/gs/producing-web-service/)
- Client(서비스 사용)([https://github.com/spring-guides/gs-consuming-web-service](https://github.com/spring-guides/gs-consuming-web-service)


각각 프로젝트를 다운 받아서 보보면 initial에 가장 기본적인 설정(`pom.xml`)이 되어있고, complete 하위에서 해당 내용을 확인해 볼 수 있다.