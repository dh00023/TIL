# 배치 스케쥴러

## Crontab

- history 관리 불가능
- 실수로 해당 스케쥴링 전체를 날릴 수 있음
- 배치 수행 실패시 배치 모니터링 관리 대상나 오류 모니터링 로직을 별도로 추가하지 않으면 알기 어려움
- 운영배치를 예로 들면, crontab에 스케쥴링 관리가 제대로 되지 않음(주석 처리되어있는 job들 다수)
- crontab의 경우 **각 서버마다 따로 스케줄링을 관리해야 하며 무엇보다 클러스터링 기능이 제공되지 않아** 추천하지 않는다.

## Quartz

- [http://www.quartz-scheduler.org/](http://www.quartz-scheduler.org/)

Quartz는 오픈소스  Job Scheduling 라이브러리로, 완전히 자바로 개발되어 자바 환경, 규모와 상관없이 사용할 수 있다. Quartz는 수천 개의 작업도 실행 가능하며, 간단한 interval 형식이나 Cron 표현식으로 복잡한 스케쥴링도 지원한다.

![](../assets/quartz.png)

#### 장점

- DB 기반으로 스케줄러 간의 Clustering 기능을 제공
- 시스템 Fail-over와 Random 방식의 로드 분산처리를 지원한다
- In-memory Job Scheduler도 제공
- 여러 기본 Plug-in을 제공
- `ShutdownHookPlugin` - JVM 종료 이벤트를 캐치해서 스케줄러에게 종료를 알려줌
    - `LoggingJobHistoryPlugin` - Job 실행에 대한 로그를 남겨 디버깅할 때 사용
- 배치 수행중 이슈가 생겼을 때 쉽게 파악할 수 있는 구조로 설계되어있음(로그 관리/방어로직에 좋음)

#### 단점

- Clustering 기능을 제공하지만, 단순한 random 방식이라서 완벽한 Cluster 간의 로드 분산은 안됨.
- 어드민 UI을 제공하지 않음.
- 스케줄링 실행에 대한 History는 보관하지 않음.
- Fixed Delay 타입을 보장하지 않으므로 추가 작업이 필요
- 스케쥴링을 변경하려면 써드파티를 사용하거나, 배포가 필요함
- 모든 것을 커스텀해야해서 시간 소요가 많이든다.

## Jenkins

- groovy 기반으로 구성되어있음.
- 무료 CI툴로, 배치 스케쥴링으로 많이 사용
- 파이프라인 설정도 가능
- 배치 빌드 실패시 슬랙 등으로 바로 알림 생성 가능
- 해당 배치 로그도 확인 가능
- 수정 히스토리 관리 가능
- jenkins 자체에서 배치 수행 on/off 가능
- 클러스터링 가능
- 파라미터화, 스케쥴링, ssh 트리거 등 쉽게 가능
- 모든 이력, 설정정보들이 전부 파일로 관리됨
    - 설정 정보/실행 이력/현재 Job 정보등이 궁금하면 **Jenkins 가 제공하는 API 혹은 서버내에 존재하는 XML파일로만** 확인할 수 있음
- 백업&이중화가 어려움
- 신뢰할 수 없는 플러그인
    - 대부분의 플러그인에 대해 Jenkins가 확실하게 보장하지 않음.
    - 젠킨스 버전업시 대부분 사용 불가능
- [https://jojoldu.tistory.com/489](https://jojoldu.tistory.com/489)

## Airflow

- [https://github.com/apache/airflow](https://github.com/apache/airflow)

- 에어비앤비에서 개발한 워크플로우 스케줄링, 모니터링 플랫폼

    - 빅데이터는 수집, 정제, 적제, 분석 과정을 거치면서 여러가지 단계를 거치게 되는데 이 작업들을 관리하기 위한 도구

- DAG(Directed Acyclic Graph) 개념의 workflow 단위로 실행

- 파이썬 코드로 작성

    - 동일한 task 수행시에도 for문가 if문으로 파이프라인 잡 실행 가능

- 파라미터화가 되어있지않아, 실행시마다 dag.py를 계속 수정

    해줘야한다.

    - 에어플로우 파이프라인은 간결하고 명시적이며, **진자 템플릿(jinja template)**을 이용하여 **파라미터화 된 데이터를 전달하고 자동으로 파이프라인을 생성하는 것이 가능**
    - [https://jinja.palletsprojects.com/en/3.0.x/](https://jinja.palletsprojects.com/en/3.0.x/)
    - [https://dydwnsekd.tistory.com/62](https://dydwnsekd.tistory.com/62)

- ```
    operator
    ```

    를 이용해 복잡한 workflow 구성이 쉬움

    - t1 >> [t2,t3] >> t4 >> t1

- dag간 연결을 위해 

    ```
    externalTaskSensor
    ```

     사용

    - [https://tommybebe.github.io/2020/11/30/airflow-external-task-sensor/](https://tommybebe.github.io/2020/11/30/airflow-external-task-sensor/)

- Task 병렬 수행을 위해서는 

    ```
    celery executor
    ```

    을 사용 필요

    - `celery executor` 를 사용하기 위해서는 **RabbitMQ**나 **Redis**가 필요
    - meta store로 **mysql** or **postgresql** 사용필요.

- 혹은 

    `Kubernetes Executor`

     도 사용 가능

    - Task를 스케줄러가 실행가능 상태로 변경하면 메시지 브로커에 전달하는게 아니라 Kubernetes API를 사용하여 Airflow 워커를 pod 형태로 실행
    - 매 Task마다 pod가 생성되므로 가볍고, Worker에 대한 유지 보수가 필요없다는 장점
    - Kubernetes를 활용하여 지속적으로 자원을 점유하지 않기 때문에 효율적으로 자원을 사용할 수 있음.
    - 짧은 Task에도 pod을 생성하는 overhead가 있으며, celery executor에 비해 자료가 적고 구성이 복잡하다는 단점
    - **별도 서버 1개에서 운영할것이므로 맞지 않아 보임**

- [https://www.slideshare.net/YoungHeonKim1/airflow-workflow](https://www.slideshare.net/YoungHeonKim1/airflow-workflow)

- [https://www.bucketplace.co.kr/post/2021-04-13-버킷플레이스-airflow-도입기/](https://www.bucketplace.co.kr/post/2021-04-13-버킷플레이스-airflow-도입기/)

![https://airflow.apache.org/_images/airflow.gif](https://airflow.apache.org/_images/airflow.gif)



## Teamcity

- JetBrains의 CI 도구
- 파이프라인 / 스케줄링 등 Jenkins가 지원하는 대부분의 기능을 동일하게 지원
- Jetbrains 제품군 (IntelliJ, DataGrip, Upsource 등) 과 통합 지원이 좋음
    - Job 알람에 대해 IntelliJ에서 알람이 보여지는 등
- 설정 정보들이 DB로 관리
    - 백업/이중화는 DB에 모두됨
    - Teamcity는 어디든 설치만해서 바로 DB 연결만 하면 똑같은 Teamcity 환경이 구성
    - 여러대의 서버를 운영한다고 해도 스케줄링/설정 등에 대한 관리 요소가 전혀 없음.
    - DB에서 다 관리중이니, 각 TeamCity 서버에 대한 동기화 걱정이 필요 없음.
    - 당연히 별도의 기능이 필요한 경우 API를 사용해도 되고, 직접 Teamcity 설정 정보를 담고 있는 DB에 Query를 날려서 사용 가능

- 일정 규모이상에서는 **유료** 플랜이 필요
- 결국은 CI/CD 도구이다보니 배치쪽으로 발전 방향이 향하고 있진 않음.
- 플러그인 생태계가 Jenkins에 비해 약함.
    - 전체 플러그인 수가 10배 이상 차이남.
    - 그럼에도 Github 로그인 / 슬랙 연동 등 대부분의 플러그인들은 존재

## Spring Cloud Data Flow

- Spring에서 공식적으로 밀고 있는 Batch/Data Stream 매니저

- Spring에서 대놓고 Batch/Data Stream 매니저로 나온 도구라서 발전 방향이 그쪽으로 명확

- Teamcity와 마찬가지로 DB에 여러 설정 정보들을 관리

    - 별도로 지정하지 않으면 인메모리 DB (H2)를 사용

- 오픈소스

- **CloudFoundry 혹은 Kubernates 환경**이 아니면 제대로 활용하기가 어려움.

    - 위 환경에서만 스케줄링 기능을 사용 할 수 있음.

    - 즉, **단일 서버에서는 스케줄링 기능을 사용 못함.**

- 컨셉 자체가 **배치가 실행될때만 컨테이너를 별도로 생성해서 실행하고 종료**하기 위함이라 컨테이너 오케스트레이션 없이 사용하려면 굉장히 제한적

    - 당연히 위 단점으로 인해 **허들이 다른 어떤 도구들 보다 높음.**

    - Cloud Native Batch Application 을 위해 나온 서비스라 클라우드를 굉장히 단순하게만 사용하는 그룹에서 사용하기엔 초기 허들이 높음.
    - Spring Batch에 대한 공부보다 Kubernates 와 Docker 공부가 우선 되어야할 수도 있음.

- **단일 서버에 Kubernates 설치하고 그 서버안에서 Docker 생성&삭제를 하도록 하는건 거의 무의미(단일서버에서 사용하는것 권장하지 않음.)**

## 참고

- [https://advenoh.tistory.com/51](https://advenoh.tistory.com/51)
- [https://jojoldu.tistory.com/489](https://jojoldu.tistory.com/489)
- [https://www.slideshare.net/YoungHeonKim1/airflow-workflow](https://www.slideshare.net/YoungHeonKim1/airflow-workflow)
- [https://www.bucketplace.co.kr/post/2021-04-13-버킷플레이스-airflow-도입기/](https://www.bucketplace.co.kr/post/2021-04-13-버킷플레이스-airflow-도입기/)

