# Remote Repository

Remote Repository(리모트 저장소)는 인터넷이나 네트워크 어딘가에 있는 저장소를 말한다. 

### 현재 프로젝트에 등록된 Remote Repository 확인하기

```console
$ git remote
origin
```

`-v` 옵션을 주면 단축이름, URL을 함께 볼 수 있다.

```console
$ git remote -v
origin	https://github.com/dh00023/gitpractice.git (fetch)
origin	https://github.com/dh00023/gitpractice.git (push)
```
### Remote Repository 추가하기

```console
$ git remote add [단축이름] [url]
```
```console
$ git remote add origin https://github.com/dh00023/gitpractice.git
```

### Remote Repository 살펴보기

```console
$ git remote show [단축이름]
```

```console
$ git remote show origin
* remote origin
  Fetch URL: https://github.com/dh00023/gitpractice.git
  Push  URL: https://github.com/dh00023/gitpractice.git
  HEAD branch: master
  Remote branches:
    master   tracked
    practice tracked
  Local branch configured for 'git pull':
    master merges with remote master
  Local refs configured for 'git push':
    master   pushes to master   (up to date)
    practice pushes to practice (up to date)
```

### Remote Repository 이름 변경

```console
$ git remote rename [AS-IS] [TO-BE]
```

### Remote Repository 제거

```console
$ git remote rm [이름]
```
