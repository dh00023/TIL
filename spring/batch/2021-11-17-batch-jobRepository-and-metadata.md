# JobRepository와 메타데이터

## JobRepository

![https://github.com/cheese10yun/TIL/raw/master/assets/batch-obejct-relrationship.png](/Users/dh0023/Develop/gitbook/TIL/spring/assets/batch-obejct-relrationship.png)

`JobRepository`는 **배치 처리 정보**를 담고 있는 \*매커니즘이다. 

- 배치 수행과 관련된 수치 데이터(시작/종료 시간, 상태, 읽기/쓰기 횟수)
- Job의 상태 유지 관리
- RDBMS(관계형 데이터베이스) 사용하며, 배치 내 대부분 주요 컴포넌트가 공유

예를 들어, `Job` 한개가 실행되면 `JobRepository`에서 배치 실행에 관련된 정보를 담고 있는 도메인 `JobExcution`을 생성하며, `Step`의 실행정보를 담고 있는 `StepExecution`도 저장소에 저장해 **전체 메타데이터를 저장/관리하는 역할을 수행**한다.

1. Job 실행하면 Job은 각 Step실행
2. 각 Step이 실행되면 `JobRepository` 현재 상태로 갱신

즉, 실행된 Step,  현재 상태, 읽은 아이템 및 처리된 아이템 수 등이 모두 저장된다.

*\*매커니즘 : 어떠한 사물의 구조, 또는 그것이 작동하는 원리*