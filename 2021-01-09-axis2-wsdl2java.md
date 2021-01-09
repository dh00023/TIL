# Axis2 wsdl2java

Axis2를 이용해서 WSDL을 Java로 변환할 수 있다.


### AXIS/JAVA 다운로드

[https://axis.apache.org/axis2/java/core/download.html](https://axis.apache.org/axis2/java/core/download.html)에서 원하는 Release notes 버전을 선택해 다운로드 받을 수 있다.

여기서 terminal을 이용해 파일을 생성할 것이므로 `axis2-1.7.9-bin.zip`를 다운 받았다.

파일을 다운받아 압축 해제를 하면 `axis2-1.7.9/bin` 하위에 `wsdl2java.sh` shell script가 있는것을 볼 수 있다.

### 환경 설정하기

#### sh 실행 권한 설정

우선 해당 shellscript를 실행할 수 있는 권한을 설정해준다.

```bash
# 권한 확인하기
$ ll
-rw-rw-r--@ 1 dh0023  staff   866B 11 16  2018 wsdl2java.sh
```

```bash
$ chomd +x ./axis2-1.7.9/bin/wsdl2java.sh
```

```bash
# 권한 확인하기
$ ll
-rwxrwxr-x@ 1 dh0023  staff   866B 11 16  2018 wsdl2java.sh
```


#### JAVA_HOME 설정

```bash
$ export JAVA_HOME=/Library/Java/Home
$ echo $JAVA_HOME 
/Library/Java/Home
```

### axis2 wsdl2java 실행

```bash
$ ./axis2-1.7.9/bin/wsdl2java.sh -u -uri {wsdl 경로}
```

현재 directory 하위에 `./src` directory가 생성 된 것을 확인할 수 있다.


