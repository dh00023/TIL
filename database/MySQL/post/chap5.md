# 관계형 데이터베이스의 필요성

데이터가 중복되어 나타나면 개선할 것이 있다는 강력한 증거이다.
- topic

| id   | title      | description       | created    | author | profile                |
| ---- | ---------- | ----------------- | ---------- | ------ | ---------------------- |
| 1    | MySQL      | MySQL is ...      | 2018-01-01 | dahye  | developer              |
| 2    | ORACLE     | ORACLE is ...     | 2018-01-01 | dahye  | developer              |
| 3    | SQL Server | SQL Server is...  | 2018-01-15 | mimi   | database administrator |
| 4    | PostgreSQL | PostgreSQL is ... | 2018-01-20 | taeho  | data scientist         |

기존의 테이블은 테이블만 보고 직관적으로 알 수 있다.



## 테이블 분리하기

- author

| id   | author | profile                |
| ---- | ------ | ---------------------- |
| 1    | dahye  | developer              |
| 2    |mimi   | database administrator |
| 3    |taeho  | data scientist         |

- topic

| id   | title      | description       | created    | author_id|
| ---- | ---------- | ----------------- | ---------- | ---------------------- |
| 1    | MySQL      | MySQL is ...      | 2018-01-01 | 1 |
| 2    | ORACLE     | ORACLE is ...     | 2018-01-01 |1  |
| 3    | SQL Server | SQL Server is...  | 2018-01-15 | 2 |
| 4    | PostgreSQL | PostgreSQL is ... | 2018-01-20 | 3 |

테이블을 쪼개게 되면 별도의 테이블로 보관해 중복된 데이터를 저장하지 않는다.



### 테이블명 변경하기

```sql
mysql> RENAME TABLE topic TO topic_backup;
Query OK, 0 rows affected (0.09 sec)
```



### 테이블 분리해 생성하기

- author

```sql
> CREATE TABLE `author` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) NOT NULL,
  `profile` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) 
 
> DESC author;
+---------+--------------+------+-----+---------+----------------+
| Field   | Type         | Null | Key | Default | Extra          |
+---------+--------------+------+-----+---------+----------------+
| id      | int(11)      | NO   | PRI | NULL    | auto_increment |
| name    | varchar(20)  | NO   |     | NULL    |                |
| profile | varchar(200) | YES  |     | NULL    |                |
+---------+--------------+------+-----+---------+----------------+
3 rows in set (0.01 sec)

> INSERT INTO `author` VALUES (1,'egoing','developer');
> INSERT INTO `author` VALUES (2,'duru','database administrator');
> INSERT INTO `author` VALUES (3,'taeho','data scientist, developer');

> SELECT * FROM author;
+----+--------+---------------------------+
| id | name   | profile                   |
+----+--------+---------------------------+
|  1 | egoing | developer                 |
|  2 | duru   | database administrator    |
|  3 | taeho  | data scientist, developer |
+----+--------+---------------------------+
3 rows in set (0.00 sec)
```



- topic

```sql
> CREATE TABLE `topic` (
    ->   `id` int(11) NOT NULL AUTO_INCREMENT,
    ->   `title` varchar(30) NOT NULL,
    ->   `description` text,
    ->   `created` datetime NOT NULL,
    ->   `author_id` int(11) DEFAULT NULL,
    ->   PRIMARY KEY (`id`)
    -> );
Query OK, 0 rows affected (0.07 sec)

> DESC topic;
+-------------+-------------+------+-----+---------+----------------+
| Field       | Type        | Null | Key | Default | Extra          |
+-------------+-------------+------+-----+---------+----------------+
| id          | int(11)     | NO   | PRI | NULL    | auto_increment |
| title       | varchar(30) | NO   |     | NULL    |                |
| description | text        | YES  |     | NULL    |                |
| created     | datetime    | NO   |     | NULL    |                |
| author_id   | int(11)     | YES  |     | NULL    |                |
+-------------+-------------+------+-----+---------+----------------+
5 rows in set (0.01 sec)

> INSERT INTO `topic` VALUES (1,'MySQL','MySQL is...','2018-01-01 12:10:11',1);
> INSERT INTO `topic` VALUES (2,'Oracle','Oracle is ...','2018-01-03 13:01:10',1);
> INSERT INTO `topic` VALUES (3,'SQL Server','SQL Server is ...','2018-01-20 11:01:10',2);
> INSERT INTO `topic` VALUES (4,'PostgreSQL','PostgreSQL is ...','2018-01-23 01:03:03',3);
> INSERT INTO `topic` VALUES (5,'MongoDB','MongoDB is ...','2018-01-30 12:31:03',1);

> > SELECT * FROM topic;
+----+------------+-------------------+---------------------+-----------+
| id | title      | description       | created             | author_id |
+----+------------+-------------------+---------------------+-----------+
|  1 | MySQL      | MySQL is...       | 2018-01-01 12:10:11 |         1 |
|  2 | Oracle     | Oracle is ...     | 2018-01-03 13:01:10 |         1 |
|  3 | SQL Server | SQL Server is ... | 2018-01-20 11:01:10 |         2 |
|  4 | PostgreSQL | PostgreSQL is ... | 2018-01-23 01:03:03 |         3 |
|  5 | MongoDB    | MongoDB is ...    | 2018-01-30 12:31:03 |         1 |
+----+------------+-------------------+---------------------+-----------+
5 rows in set (0.00 sec)
```



## JOIN

```sql
mysql> SELECT * FROM topic LEFT JOIN author ON topic.author_id = author.id;
+----+------------+-------------------+---------------------+-----------+------+--------+---------------------------+
| id | title      | description       | created             | author_id | id   | name   | profile                   |
+----+------------+-------------------+---------------------+-----------+------+--------+---------------------------+
|  1 | MySQL      | MySQL is...       | 2018-01-01 12:10:11 |         1 |    1 | egoing | developer                 |
|  2 | Oracle     | Oracle is ...     | 2018-01-03 13:01:10 |         1 |    1 | egoing | developer                 |
|  3 | SQL Server | SQL Server is ... | 2018-01-20 11:01:10 |         2 |    2 | duru   | database administrator    |
|  4 | PostgreSQL | PostgreSQL is ... | 2018-01-23 01:03:03 |         3 |    3 | taeho  | data scientist, developer |
|  5 | MongoDB    | MongoDB is ...    | 2018-01-30 12:31:03 |         1 |    1 | egoing | developer                 |
+----+------------+-------------------+---------------------+-----------+------+--------+---------------------------+
5 rows in set (0.00 sec)
```

- author_id와 id 가 두개다 나오므로 한개만 나오게하기

```sql
mysql> SELECT topic.id,title,description,created, name, profile FROM topic LEFT JOIN author ON topic.author_id = author.id;
+----+------------+-------------------+---------------------+--------+---------------------------+
| id | title      | description       | created             | name   | profile                   |
+----+------------+-------------------+---------------------+--------+---------------------------+
|  1 | MySQL      | MySQL is...       | 2018-01-01 12:10:11 | egoing | developer                 |
|  2 | Oracle     | Oracle is ...     | 2018-01-03 13:01:10 | egoing | developer                 |
|  3 | SQL Server | SQL Server is ... | 2018-01-20 11:01:10 | duru   | database administrator    |
|  4 | PostgreSQL | PostgreSQL is ... | 2018-01-23 01:03:03 | taeho  | data scientist, developer |
|  5 | MongoDB    | MongoDB is ...    | 2018-01-30 12:31:03 | egoing | developer                 |
+----+------------+-------------------+---------------------+--------+---------------------------+
5 rows in set (0.00 sec)

```

- id를 topic_id로 바꾸기

```sql
mysql> SELECT topic.id AS topic_id,title,description,created, name, profile FROM topic LEFT JOIN author ON topic.author_id = author.id;
+----------+------------+-------------------+---------------------+--------+---------------------------+
| topic_id | title      | description       | created             | name   | profile                   |
+----------+------------+-------------------+---------------------+--------+---------------------------+
|        1 | MySQL      | MySQL is...       | 2018-01-01 12:10:11 | egoing | developer                 |
|        2 | Oracle     | Oracle is ...     | 2018-01-03 13:01:10 | egoing | developer                 |
|        3 | SQL Server | SQL Server is ... | 2018-01-20 11:01:10 | duru   | database administrator    |
|        4 | PostgreSQL | PostgreSQL is ... | 2018-01-23 01:03:03 | taeho  | data scientist, developer |
|        5 | MongoDB    | MongoDB is ...    | 2018-01-30 12:31:03 | egoing | developer                 |
+----------+------------+-------------------+---------------------+--------+---------------------------+
5 rows in set (0.01 sec)
```

