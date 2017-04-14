# 데이터베이스(생활코딩 온라인 강의)

* nosql : 트위터와 같이 빅데이터를 다룰때는 관계형데이터는 한계가 있다.
	* mongodb
	* http://nosql-database.org/

![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/98/320.png)

Client : 요청 <-> server
client를 이용해서 서버에 있는 것을 사용할 수 있다.

## MYSQL 설치(homebrew)

1. `$ brew update` Homebrew를 update해준다.
2. `$ brew install mysql` 5.7.17 version이 설치가된다.
3. `$ mysql.server start` MySQL시작
4. `$ mysql_secure_installation` root비밀번호 설정 (처음 mysql을 설치하면 설정이 안되어있다.) 
	* `Would you like to setup VALIDATE PASSWORD plugin?` : 복잡한 비밀번호를 사용하도록 제한해주는 플러그인을 사용하려면 yes, 보안은 무시하고 그냥 쓰던 비밀번호 제한받지 않고 쓰고 싶다면 no.
	* `Remove anonymous users?` : 익명사용자 삭제할지/계속 사용할지 여부. no 하면 `$ mysql -uroot`가 아니라 `$ mysql`만으로도 접속 가능. yes하면 -u 옵션 필수.
	* `Disallow root login remotely?` : localhost외에 다른 ip에서 root 아이디로 원격접속 가능하게 할지. yes하면 원겹접속 불가.
	* `Remove test database and access to it?` : mysql에 기본적으로 설정된 test 디비 삭제 여부.
	* `Reload privilege tables now?` : 하나라도 권한 변경을 했다면 yes 해서 하는 게 정신건강에 좋을 것입니다.
5. `$mysql -uroot -p` 로그인
6. `mysql> status;` 상태확인
7. 데몬(daemon)은 사용자가 직접적으로 제어하지 않고, 백그라운드에서 돌면서 여러 작업을 하는 프로그램을 말한다.
	* `$ brew services start mysql`
	* `$ ln -sfv /usr/local/opt/mysql/*.plist ~/Library/LaunchAgents` 로그인시 자동실행

## 클라이언트
mysql-moniter : mysql설치하면 자동으로 설치되는!
1. mysql접속
	* `mysql -u아이디 -p비밀번호`
	* `mysql -h호스트주소 -p포트번호 -u아이디 -p비밀번호`

2. 데이터베이스 생성
`> CREATE DATABASE music CHARACTER SET utf8 COLLATE utf8_general_ci;` : music이름을 가진 데이터베이스를 생성함. set뒷부분은 인코딩부분.

3. 데이터베이스 확인
`> show databases`

4. 데이터베이스 선택
`> use 데이터베이스이름` 테이블이 어느데이터베이스에 포함되어있는지 알려주는것!

5. 테이블 생성
```sql
CREATE TABLE `favorite_music` (
  `title` varchar(255) NOT NULL,
  `musician` varchar(20) NOT NULL,
  `duration` varchar(20) NOT NULL,
  `album` varchar(30) NOT NULL
) ENGINE=innodb;
```

6. 테이블 확인
`> show tables`

7. 데이터 생성
```sql
insert into favorite_music (`title`,`musician`, `duration`, `album`) values('Chasing Pavements', '아델', '3:30', 19);
```

8. 입력된 데이터 조회
```sql
select * from favorite_music;
```

9. 종료
`quit` or `exit`