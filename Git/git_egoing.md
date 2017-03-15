# 지옥에서온 Git

codeOnWeb 사이트에서 언어와 환경에서 git선택하고 실행한후실습하면된다.

https://goo.gl/AMFYqE

## Git = 버전관리 시스템

* 버전관리 시스템이란?
	- 파일이름을 더럽히지 않는 버전관리.
	- **복원**, **백업**, **협업**
	- 작업의 지배자
	- CVS,SVN,**GIT**

## GIT실습
Dropbox,GoogleDrive라도 써라!

버전관리를 한다는 것은 프로젝트 폴더에 생성되는 파일들을 체계적으로 관리하겠다는 것이다. 프로젝트폴더는 저장소!

#### `git`
간단한 git사용방법
자세하게 알고싶은 경우
`git 명령어 --help`

#### `git init`
 나는 이 디렉토리를 체계적으로 관리할거야
모든것의 시작은 **init**
현재 디렉토리가 버전관리의 저장소가 되었다.
`ls -al`을 하면 .git directory가 생긴다.
이 .git안에 버전관리가 되는 것이다.

* `vi f1.txt`
> ```
> source 1
> ```

#### `git status`
 현재 상태를 확인 할 수 있다.
 untracked files: 는 버전관리가 되지않고 있는 파일.

#### `git add f1.txt`
 버전관리를 해라
 다시 `git status`를 해보면 changed to be Committed: 해서 파일이 버전관리 되고 있는 것을 확인 할 수 있다.

#### `git config`
 git의 기본설정을 바꾸는 것!
 각각의 버전은 누가 만든것인지 정보를 가지고 있어야한다.
 ```
 git config --global user.name "dahye"
 git config --global user.email "wjdekgp1750@naver.com"
 ```

#### `git commit`
 내가 만든 버전을 제출한다!
 버전에 대한 설명을 적어준다.
 `$ git commit -a`를 하면 add를 생략할 수 있다.
`$ git commit --amend`를 하면 추가적인 설명을 쓸 수 있다.
![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/217/735.png)
#### `git log`
잘 만들었는지 확인하는것!
로그는 역사라 생각하면된다.
commit 이상한문자는 이 버전에 대한 식별자.
`git log -p` : 어떤 코드가 바꼈는지

###비교
#### `git diff`
 달라진 부분을 알려준다.

### 취소
* Reset은 선택한 버전의 상태로 돌아가는 것, 버전을 지워버림.
* Revert는 선택한 버전을 취소해서 그 이전 상태로 돌리는것

###Branch
#### `git branch`
```
*master
```
master는 default branch이다.

* 실험적인 작업을 해야하는경우!
```
$ git branch exp
$ git branch
exp
*master
```
그럼 exp가 생성된 것을 확인할 수 있다. *붙은 것이 현재 branch.

branch를 바꿔주는 작업
```
$ git checkout ewp
*ewp
master
```
를 해주면 gitbranch가 ewp로 바뀐것을 확인 할 수 있다.

`cat 파일명` : 파일을 출력해라

fork같은거네!branch를 하기전까지의 작업이 그대로 복사가 된다. branch를 한 후에는 각각 작업!

#### branch병합(merge)

branch를 병합할 때 받아올 branch로 checkout해야한다.
branch를 이용해 병합을 하면 git이 자동으로 commit을 해준다.

#### branch 충돌(conflict)
만약에 여러개의 branch가 서로 같은 것을 수정할 경우에! 
이 경우에 깃은 충돌을 나타내고 우리가 수정할 수 있도록한다.

**충돌을 최소화 하려면!**
master에 있는 바뀐내용을 현재 branch에 merge를한다. 이런식으로 충돌은 발생하나 작은 충돌을 수정하면서 가는 것이 좋다! 충돌이 발생했을때 지금우리꺼나 다른 branch것으로 선택할 수도 있다.

### 협업
협업할때 pull을 해 병합해 충돌이 발생했는지 확인한 후 push를 해야한다.
어떠한 작업을 하기전에 pull을 하는 것이 가장 좋다!
`pull`->working->`commit`->`pull`->`push`

### stash
: 아직 commit하지 않은 것을 임시로 저장하는 것!
stash를 하면 임시로 저장된 후 마지막 버전상태로 돌아가고! 삭제된다.

### tag(github에선 releases)
:설명해주는 것! 과거의 특정한 버전에 대해서도 태그를 붙일 수 있다.

### Git ignore
.gitignore파일에 파일을 추가하면 git이 없는걸로 간주할 대상으로 된다.(github에 올릴때도 안올라감!)
https://www.gitignore.io 에서 ignore파일에 포함되어야할 목록들을 알려준다.

### 환경설정

중요한 id, 비밀번호, key값이 설정된 파일은 따로 저장한 후 `.gitignore`에 추가해 원격저장소에 올리지 않는다.

http://marklodato.github.io/visual-git-guide/index-ko.html
http://dogfeet.github.io/articles/2012/progit.html