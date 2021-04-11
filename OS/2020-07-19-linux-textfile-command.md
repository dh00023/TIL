# 텍스트 파일 관련 명령어

## cat(concatenate)

표준 입력으로 받는 값을 표준 출력으로 이어주는 명령으로 기본적으로는 텍스트 파일의 내용을 출력한다. 혹인 파일을 생성하거나 여러개의 텍스트 파일을 합치는 기능도 수행

```bash
$ cat [option] filename(s)
```



| 옵션 | 의미                                                         |
| ---- | ------------------------------------------------------------ |
| -b   | 텍스트 파일 출력할 때 행 번호를 붙여준다(공백만 있는 줄 제외) |
| -n   | 텍스트 파일 출력시, 행 번호를 붙여준다.(공백 포함)           |
| -E   | 각 라인의 맨 끝에 $표시 붙여 출력                            |
| -T   | 탭 문자를 ^\|로 표시하여 출력                                |
| -v   | 인쇄가 불가능한 문자를 식별할 수 있도록 출력                 |
| -A   | -vET 옵션을 통합한 옵션으로 일반적으로 출력되지 않는 문자를 모두 출력 |
| -s   | 인접한 여러 공백 줄을 하나의 공백줄로 출력                   |

## head

텍스트 파일의 첫 부분을 보여주는 명령어

```bash
$ head [option] filename(s)
```

| 옵션    | 설명                                                         |
| ------- | ------------------------------------------------------------ |
| -n 행수 | 파일의 앞에서부터 지정된 수만큼 출력. 보통 n을 생략하고 -5와 같이 입력 |
| -c n    | n바이트까지 출력                                             |
| -q      | 여러 개의 파일이 처리될 떄 파일 이름 헤더를 출력하지 않는다. |

```bash
$ head -3 *.md # .md파일로 끝나는 파일들 첫번째 3줄 출력
==> README.md <==
# Today I Learned

## OS(운영체제)

==> SUMMARY.md <==
# Summary

* OS(운영체제)
```

## tail

텍스트 파일의 끝 부분을 보여주는 명령으로 옵션 없이 사용하면 기본 10줄 출력

```bash
$ tail [option] filename
```

| 옵션    | 의미                                                         |
| ------- | ------------------------------------------------------------ |
| -n 행수 | 파일의 마지막 줄에서 지정된 수만큼 출력                      |
| -c n    | 마지막 n바이트만 출력                                        |
| **-f**  | **특정 파일의 끝부분에 새로운 행이 추가될 경우 실시간으로 출력(특정 로그 파일을 모니터링할 때 유용하게 사용)**<br>중단시에는 ctrl + c 누른다. |
| -q      | 여러 개으 ㅣ파일이 처리될 떄 파일 이름 헤더를 출력하지 않는다. |

## more

텍스트 파일의 내용이 긴 경우에 화면(page) 단위로 출력

```bash
$ more [option] filename
```

| 옵션 | 의미                          |
| ---- | ----------------------------- |
| -num | 한페이지를 num의 줄 수로 지정 |

### more 실행중 사용하는 명령어

| 명령키           | 의미                                   |
| ---------------- | -------------------------------------- |
| h                | more에 대한 도움말                     |
| `space` <br> `z` | 다음 페이지를 보여준다.                |
| Enter            | 한줄씩 보여준다.                       |
| d<br>ctrl+d      | 다음 반 페이지 보여준다.               |
| b<br>ctrl+b      | 이전 페이지를 보여준다.                |
| f                | 한페이지 skip 후 다음페이지 보여준다.  |
| /pattern         | 지정한 패턴을 검색                     |
| =                | 현재 줄번호 보여준다.                  |
| ctrl+I           | 화면을 다시 출력                       |
| :f               | 현재 파일명과 줄번호 보여준다.         |
| !                | 다른 명령을 입력할 수 있는 상태로 전환 |
| q                | more 명령어 종료                       |

## less

more 명령과 유사하게 한 화면 단위로 출력해 주는 명령으로, more 명령의 성능을 강화한 뒤에 반대의 뜻을 붙여서 만들었다. 커서키를 사용해 상하좌우 이동이 가능하고, vi에서 사용하는 다양한 명령들도 사용가능

```bash
$ less [option] filename
```

| 옵션    | 의미                                                         |
| ------- | ------------------------------------------------------------ |
| -?      | less 실행시 사용하는 명령어들에 대한 도움말 출력             |
| -c      | 화면에 출력하기 전에 화면을 정리하여 맨 처음에 위치하도록 해줌 |
| -s      | 인접한 여러 공백 줄을 하나으 ㅣ공백줄로 처리해 화면에 보여줌 |
| -e      | less 실행 후 맨 끝줄에 도달한 뒤 [Enter]나 [Space]키를 누르면 자동으로 명령 종료 |
| -N      | 줄번호를 보여준다.                                           |
| +행번호 | 지정한 행번호부터 1page씩 보여준다.                          |

### less 실행 상태에서 사용하는 명령어

| 명령키               | 의미                                                         |
| -------------------- | ------------------------------------------------------------ |
| h                    | less에 대한 도움말                                           |
| space<br>f<br>ctrl+f | 다음 페이지를 보여준다.                                      |
| Enter<br>e           | 한줄씩 보여준다.                                             |
| d<br>ctrl+d          | 다음 반 페이지 보여준다.                                     |
| u<br>ctrl+u          | 이전 반 페이지를 보여준다.                                   |
| b<br>ctrl+b          | 이전 페이지를 보여준다.                                      |
| q<br>Q               | less 명령어 종료                                             |
| y                    | 이전줄로 이동한다.                                           |
| /패턴                | 지정한 패턴을 아래 방향으로 검색                             |
| ?패턴                | 지정한 패턴을 윗방향으로 검색                                |
| n                    | 패턴 검색 시 아랫방향으로 다음 패턴의 문자열을 찾아 화면의 맨 첫줄에 위치 |
| N                    | 패턴 검색시 윗 방향으로 다음 패턴의 문자열을 찾아 화면의 맨 첫줄에 위치 |



## grep(Global Regualr Expression Print)

텍스트 파일에서 특정 패턴을 갖는 줄을 찾아서 출력해주는 명령어

```bash
$ grep [option] pattern file(s)
```

| 옵션 | 의미                                                         |
| ---- | ------------------------------------------------------------ |
| -b   | 패턴과 일치하는 줄의 시작점 출력                             |
| -c   | 패턴과 일치하는 줄의 개수 출력                               |
| -h   | 여러 개의 파일을 검색 시 출력하는 파일 명이 붙는 것을 방지   |
| -i   | 검색시 대소문자 구분하지 않는다.                             |
| -n   | 패턴과 일치하는 줄의 번호와 내용을 같이 출력                 |
| -v   | 패터과 일치하지 않는 줄을 출력                               |
| -w   | 패턴과 한 단어로 일치해야 출력                               |
| -l   | 주어진 패턴과 일치하는 패턴이 있는 파일의 이름만 출력        |
| -r   | 하위 디렉터리까지 주어진 패턴을 찾는다.                      |
| -o   | 지정한 패턴과 매칭되는 것만 출력                             |
| -E   | 이 옵션은 \|와 연계하여 여러 패턴을 찾는다. egrep과 같다.    |
| -F   | 지정한 문자들, 특수문자를 그대로 인식하여 출력해준다. fgrep과 같다. |

## wc(word count)

텍스트 파일의 행, 단어, 문자 수를 출력해주는 명령어

```bash
$ wc [option] file
```

| 옵션 | 의미                       |
| ---- | -------------------------- |
| -l   | 행수만 출력                |
| -w   | 단어 수만 출력             |
| -c   | 문자 수만 출력             |
| -L   | 가장 긴 라인의 길이를 출력 |

## sort

텍스트 파일의 내용을 행 단위로 정렬한다. 옵션을 지정하지 않으면, 공백, 숫자, 특수문자, 대문자, 소문자 순이다.

```bash
$ sort [option] file
```

| 옵션     | 의미                                                         |
| -------- | ------------------------------------------------------------ |
| -b       | 선행하는 공백문자 무시                                       |
| -d       | 공백과 알파벳, 숫자 만으로 정렬                              |
| -f       | 대소문자 무시                                                |
| -r       | 내림차순으로 정렬(소문자 > 대문자 > 특수 > 숫자 > 공백)      |
| -o       | 정렬한 결과를 파일명으로 저장                                |
| -c       | 파일이 정렬되어 있는지 검사                                  |
| -n       | 숫자를 문자가 아닌 숫자값으로 취급해서 수의 크기대로 정렬<br>(9와 10 정렬시 기본정렬은 10이 먼저, 이 옵션은 9가 먼저) |
| -u       | 중복되는 줄은 한줄만 출력                                    |
| -M       | 월 표시 문자로 정렬할 때 사용                                |
| -t       | 필드 구분자 지정시 사용                                      |
| -k n[,m] | 정렬할 위치를 지정하는 옵션으로 n번째 필드를 기준으로 정렬.<br>m이 지정되어 있다면 n에서 시작해서 m에서 끝낸다. |

```bash
$ sort -t: -n -k3 /etc/test # : 구분자를 지준으로 3번째 필드로 정렬
```



## cut

데이터의 열을 추출할 때 사용

```bash
$ cut [option] file
```

| 옵션 | 의미                        |
| ---- | --------------------------- |
| -c   | 문자수를 기준으로 추출      |
| -f   | 파일의 필드를 기준으로 추출 |
| -d   | 필드 구분자를 지정          |

```bash
$ cut -f 1,3 -d: /etc/test # 필드 구분 : 로 지정하고, 첫번째와 세번째 필드 값 출력
```

## split

하나의 파일을 여러개의 작은 파일로 분리하는 명령어로, 옵션을 지정하지 않으면 기본값 1000줄 단위로 파일 분리

```bash
$ split [option] file [file_name]
```

| 옵션      | 의미                                    |
| --------- | --------------------------------------- |
| -b 사이즈 | 파일을 주어진 바이트 크기로 분리        |
| -C        | 파일의 행을 주어진 사이즈에 맞춰서 분리 |
| -l 행수   | 파일을 주어진 행 수 단위로 분리         |
