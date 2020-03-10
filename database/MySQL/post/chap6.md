# 인터넷과 데이터 베이스의 관계

인터넷이 동작하기 위해서는 컴퓨터가 최소한이면서 최대한 두대 필요하다. 각자 흩어져있는 컴퓨터들간의 사회가 인터넷이다. 한대의 컴퓨터가 갖고 있는 한계를 추월하게 된 것이다.

![](https://mdn.mozillademos.org/files/8973/Client-server.jpg)

정보를 요청하는(Client)쪽과 응답하는(Server) 쪽이 있다.

- 웹에서는?!

![](https://mdn.mozillademos.org/files/8659/web-server.svg)



## Database server

![](https://docs.oracle.com/cloud/latest/db112/CNCPT/img/cncpt083.gif)

데이터베이스 서버는 반드시 데이터베이스 클라이언트를 사용해서 다뤄야한다. 우리가 mysql에 접속하면 `Welcome to the MySQL monitor` 라고 뜬다. 우리가 사용하는 기본적인 클라이언트는 MySQL monitor이었다. 데이터베이스 Client를 두 개 이상 사용하게 되면 조금 더 분명하게 이해할 수 있다.

전 세계에 있는 수 많은 사람들이 하나의 데이터베이스 서버를 가지고 정보를 다룰 수 있다.



## MySQL Client

### MySQL monitor

MySQL server가 있는 곳에 MySQL monitor가 있다. 즉, 어디에서나 사용할 수 있다. 명령어기반 Client이다. 많은 서버에서 GUI기반을 제공하지 않는 경우가 많다.

- 장점 : 어디에서나 사용할 수 있다.
- 단점 : 명령어를 기억하고 있어야한다.

### MySQL Workbench

- 장점 : 손쉽게 사용할 수 있다.

```
Authentication plugin 'caching_sha2_password' cannot be loaded: dlopen(/usr/local/mysql/lib/plugin/caching_sha2_password.so, 2): image not found 
```

이러한 오류가 발생했다. Strong Password를 사용하면 실행이안된다. Use Legacy Password Encryption을 사용해야 Workbench에서도 사용할 수 있다.