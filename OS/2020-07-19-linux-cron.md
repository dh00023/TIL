# Linux Cron

## cron

cron은 유닉스/리눅스 사용자로 하여금 특정한 명령이나 스크립트를 지정한 시간/날짜에 자동으로 작업을 실행하게 해주는 프로그램이다. 즉, cron은 미리 구성된 시간에 실행되도록 작업을 할당하는 **스케줄링 도구** 이다.



### crontab

cron 설정 파일로, crontable을 줄여 crontab이라 부른다. 시스템 운영에 필요한 작업은 root권한으로 `/etc/crontab` 에 등록해서 주기적으로 수행할 수 있고, 사용자는  crontab명령을 수행해서 등록할 수 있다.(mac에서는 `/var/at/tabs` 에 `crontab -e`로 등록 가능)

```bash
$ ps -ef | grep crond # cron의 실행 확인
```

| 필드         | 설정 값 및 내용                                              |
| ------------ | ------------------------------------------------------------ |
| minute       | 0~59로 설정                                                  |
| hour         | 0~23으로 설정                                                |
| day of month | 1~31으로 설정                                                |
| month        | 1~12로 설정                                                  |
| day of week  | 요일, 0~7로 설정<br>0,7 : 일요일, 1~6: 월~토<br>직접 sun, mon, tue, wed,thu,fri,sat으로 입력해도된다. |
| user-name    | 사용자 이름을 명시(일반적으로 생략)                          |
| command      | 실행할 명령얼르 기입한다.                                    |

각 필드값은 위의 표에 명시된 값이외의 값들을 사용할 수 있다.

| 값   | 설명                                             |
| ---- | ------------------------------------------------ |
| *    | 모든(all)                                        |
| -    | 연결된 설정 값 지정시 사용                       |
| ,    | 연결되지 않은 값을 나열할 때 사용                |
| /    | 연결된 설정 값 범위에서 특정 주기로 나눌 때 사용 |

```bash
# 월~금까지 오후 12시에 work.sh 스크립트 수행
0 12 * * 1-5 /home/dh0023/work.sh 
# 1월~12월까지 2개월마다 1일 오전 4시 10분에 check.sh 실행
10 4 1 1-12/2 * /etc/check.sh
# 월요일 오전 10시에 Notice라는 제목으로 root/notice 파일의 내용을 지정한 메일로 발송
0 10 * * 1 cat /root/notice | mail -s "Notice" example@naver.com
# 월, 수, 금 오전 4시에 `.bak` 파일 찾아 삭제
0 4 * * 1,3,5 find / -name `*.bak` -exec rm -rf {} \;
```



#### 명령어

```bash
$ crontab [option] 파일명
```

| 옵션 | 설명                                                   |
| ---- | ------------------------------------------------------ |
| -l   | crontab에 설정된 내용 출력                             |
| -e   | crontab의 내용 작성하거나 수정                         |
| -r   | crontab 내용 삭제                                      |
| -u   | root사용자가 특정 사용자의 crontab 파일을 다룰 때 사용 |

```bash
$ crontab -l
$ crontab -e
$ crontab -r
$ crontab -e -u example # example 사용자의 crontab 내용을 수정하기나 작성
```

### 사용자 제한

`/etc/cron.allow` , `/etc/cron.deny` 파일로 cron 사용자를 제한할 수 있다. `/etc/cron.allow` 파일이 존재하는 경우에는 `cron.deny` 파일 여부와 상관없이 등록된 사용자만 사용이 가능하다. `.allow` 파일이 존재하지 않고, `.deny` 파일만 존재하는 경우에는 `.deny` 파일에 등록된 사용자는 사용이 불가능하다. 


## 참조

- [리눅스 마스터 1급 정복하기](http://www.yes24.com/Product/Goods/19103870)