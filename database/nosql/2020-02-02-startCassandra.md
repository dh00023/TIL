# Start Cassandra 

## Installation

### Homebrew를 이용해 cassandra 설치하기

```
$ brew update
$ brew install cassandra
```

#### python 설치 오류

```
==> Installing cassandra dependency: python
==> Downloading https://homebrew.bintray.com/bottles/python-3.7.6_1.catalina.bot
==> Downloading from https://akamai.bintray.com/38/3871ef8b53270576c46489ae397f2
######################################################################## 100.0%
==> Pouring python-3.7.6_1.catalina.bottle.tar.gz
Error: The `brew link` step did not complete successfully
The formula built, but is not symlinked into /usr/local
Could not symlink Frameworks/Python.framework/Headers
Target /usr/local/Frameworks/Python.framework/Headers
is a symlink belonging to python@2. You can unlink it:
  brew unlink python@2

To force the link and overwrite all conflicting files:
  brew link --overwrite python

To list all files that would be deleted:
  brew link --overwrite --dry-run python

Possible conflicting files are:
/usr/local/Frameworks/Python.framework/Headers -> /usr/local/Cellar/python@2/2.7.16/Frameworks/Python.framework/Headers
/usr/local/Frameworks/Python.framework/Python -> /usr/local/Cellar/python@2/2.7.16/Frameworks/Python.framework/Python
/usr/local/Frameworks/Python.framework/Resources -> /usr/local/Cellar/python@2/2.7.16/Frameworks/Python.framework/Resources
/usr/local/Frameworks/Python.framework/Versions/Current -> /usr/local/Cellar/python@2/2.7.16/Frameworks/Python.framework/Versions/Current
==> /usr/local/Cellar/python/3.7.6_1/bin/python3 -s setup.py --no-user-cfg insta
==> /usr/local/Cellar/python/3.7.6_1/bin/python3 -s setup.py --no-user-cfg insta
==> /usr/local/Cellar/python/3.7.6_1/bin/python3 -s setup.py --no-user-cfg insta
==> Caveats
Python has been installed as
  /usr/local/bin/python3

Unversioned symlinks `python`, `python-config`, `pip` etc. pointing to
`python3`, `python3-config`, `pip3` etc., respectively, have been installed into
  /usr/local/opt/python/libexec/bin

If you need Homebrew's Python 2.7 run
  brew install python@2

You can install Python packages with
  pip3 install <package>
They will install into the site-package directory
  /usr/local/lib/python3.7/site-packages

See: https://docs.brew.sh/Homebrew-and-Python
==> Summary
🍺  /usr/local/Cellar/python/3.7.6_1: 3,977 files, 61MB

```

다음과 같이 brew link 관련해서 오류가 뜬다면

```
$ brew unlink python@2
```

를 해주면 정상적으로 연동되는 것을 확인할 수 있다.

### cql 설치하기

이때 pip가 설치되어있어야한다.

```
$ pip install --upgrade pip
$ pip install cql
```

## cassandra 사용하기

#### cassandra  시작하기

```
$ brew services start cassandra
```

### cassandra 종료

```
$ brew services stop cassandra 
```



## 참조페이지

- [https://www.javatpoint.com/how-to-install-cassandra-on-mac](https://www.javatpoint.com/how-to-install-cassandra-on-mac)

