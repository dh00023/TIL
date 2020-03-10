# 데이터 베이스1

## 데이터베이스의 본질

파일이 가진 한계를 극복하기 위해서 보안화된 전문화된 소프트웨어가 database이다. 데이터베이스는 안전하고, 빠르게 사용할 수 있다.

데이터베이스는 광대한 기능을 가지고 있다. 데이터베이스의 입력(input)과 출력(output) 방법을 아는 것이 가장 중요하다.

### CRUD

데이터는 **CRUD** ([위키피디아](https://ko.wikipedia.org/wiki/CRUD)) 로 처리될 수 있다.

- **C**reate(생성)
- **R**ead(읽기)
- **U**pdate(갱신)
- **D**elete(삭제)

여기서 input(CRD)과 output(R)로 구분하여 볼 수 있다.

## file vs database

### 파일

```
MySQL.txt
Oracle.txt
MongoDB.txt
PostgreSQL.txt
Cassandra.txt
```

위의 파일이 5개가 아니라 1억개라면, 또한 파일 본문안에 있는 내용에서 필요없는 내용(노이즈)도 가져온다. 또한 본문내용만 보고싶은데 볼 수 없게된다.

### 스프레드 시트

![](https://cdn.ablebits.com/_img-blog/google-charts/sample-spreadsheet-data.png)

스프레드 시트를 이용하면 위와 같은 문제를 해결할 수 있다.

정리정돈 했을때 얻을 수 있는 중요한 효과가 있다. Filter기능을 이용해서 특정 행만을 볼 수 있다. 파일에 직접 데이터를 저장하는 것과 비교해 스프레드 시트를 이용해서 데이터를 구조적으로 다루면 효율적인 것을 볼 수 있다.



### 데이터베이스

데이터베이스를 사용하면 데이터를 자동화할 수 있다. 사람들이 일일이 작성하지 않아도 자동으로 CRUD기능을 할 수 있다.



## Next

![](https://cdn-images-1.medium.com/max/957/1*RrKMZXY9pRvdv4phlOo4Mw.png)

https://db-engines.com/en/ranking 에서 데이터 베이스 ranking을 볼 수 있다. 현재 RDBMS 관계형데이터 베이스가 시장에서 차지하는 비율이 높은 것을 볼 수 있다. 우선 관계형 데이터베이스 중 한개를 먼저 배우고, 그 이후에 nosql(관계형데이터베이스가 아닌 것)을 배우는 것을 추천한다.



- Oracle : 주로 관공서, 대기업에서 많이 사용함(비쌈)
- MySQL : 무료, open source(초심자 추천)
- MongoDB : nosql