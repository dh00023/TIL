# 네트워크 기본 규칙

## 프로토콜

컴퓨터간 정보를 주고받을 때 **통신 방법에 대한 규칙이나 표준**

## OSI 모델

OSI모델은 ISO(International Organization for Standardization) 국제표준화 기구에서 정한 표준규격이다.

데이터 송수신시 컴퓨터 내부에서 여러가지 일을 하는데, 이때 7개 계층(레이어)이 역할을 나누어 한다.

![](./assets/osi7.png)

| 계층  | 이름                                    | 설명                                                         |
| ----- | --------------------------------------- | ------------------------------------------------------------ |
| 7계층 | 응용 계층<br />(Application Layer)      | 이메일, 파일 전송, 웹 사이트 조회 등 애플리케이션에 대한 서비스 제공 |
| 6계층 | 표현 계층<br />(Presentation Layer)     | 문자 코드, 압축, 암호화 등 데이터를 변환                     |
| 5계층 | 세션 계층<br />(Session Layer)          | 세션 체결, 통신 방식 결정                                    |
| 4계층 | 전송 계층<br />(Transport Layer)        | 신뢰할 수 있는 통신 구현                                     |
| 3계층 | 네트워크 계층<br />(Network Layer)      | 다른 네트워크와 통신하기 위한 경로 설정 및 논리 주소 결정    |
| 2계층 | 데이터 링크 계층<br />(Data Link Layer) | 네트워크 기기 간의 데이터 전송 및 물리주소 결정              |
| 1계층 | 물리 계층<br />(Physical Layer)         | 시스템 간의 물리적인 연결과 전기 신호 변환 및 제어           |

- 데이터 송신측에서 데이터를 보내기 위해 상위 계층에서 하위 계층으로 데이를 전달
- 각 계층은 독립적이므로, 데이터가 전달되는 동안 다른 계층의 영향을 받지 않음
- 데이터 수신측은 하위 계층에서 상의 계층으로 전달된 데이터를 받음


## TCP/IP 모델

![](./assets/tcpip.png)

## 캡슐화와 역캡슐화

![](./assets/cap.png)

데이터를 보내기 위해서는 데이터의 앞부분에 전송하는데 필요한 정보(헤더)를 붙여 다음 계층으로 보낸다.

- **헤더** : 저장되거나 전송되는 데이터의 맨 앞에 위치하는 **추가적인 정보 데이터**
    - 데이터의 내용이나 성격을 식별하고 제어하는데 사용
    - 전달받을 상대방에 대한 정보도 포함
- 트레일러 : 데이터 전달시 데이터의 마지막에 추가하는 정보
- 캡슐화 : 상위 계층의 통신 프로토콜 정보(헤더/트레일러)를 데이터에 추가하여 하위 계층으로 전송
    - 응용 -> 전송 -> 네트워크 -> 데이터링크 순서로 캡슐화
- 역캡슐화 :  상위 계층의 통신 프로토콜에서 하위 계층에서 추가한 정보(헤더/트레일러)와 데이터를 분리하는 기술
    - 데이터 링크 -> 네트워크 -> 전송 -> 응용 순서로 역캡슐화
- 데이터 링크 계층에서 만들어진 데이터는 전기 신호로 변환되어 수신 측에 전송



> VPN(Virtual Private Network) 가상 사설망
>
> 가상 통신 터널을 만들어 기업 본사나 지사와 같은 거점 간을 연결하여 통신하거나 외부에서 인터넷으로 사내에 접속하는 것을 말한다.
>
> - 인터넷 VPN
>     거점 간 접속은 IPsec 암호 기술 프로토콜을 사용해 접속하고, 원격 접속 연결은 외부에서 사용하는 컴퓨터와 사내 네트워크를 연결하기 떄문에 암호화된 통신로를 만든다.
> - IP-VPN
>     MPLS 기술을 사용해 인터넷망이 아닌 통신 사업자 전용 폐쇄망을 사용하며, 폐쇄망을 사용하기 때문에 해킹이나 데이터 변조 위험이 없어, 암호화 기능이 불필요하다.

## OSI 모델의 각 계층에서 사용되는 프로토콜과 기술

![image-20210712215208070](./assets/image-20210712215208070.png)

## 참고

- [https://handreamnet.tistory.com/501](https://handreamnet.tistory.com/501)
