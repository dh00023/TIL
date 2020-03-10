# Git] Rebase, Cherri-Pick

![merge전](https://git-scm.com/figures/18333fig0327-tn.png)

위의 그림에서는 experiment와 master두개의 브랜치가 나누어져있는 것을 볼 수 있다.
이 두개의 브랜치를 master브랜치에서 merge하게 되면 새로운 commit이 생기며 아래와 같이 합쳐지는 것을 볼 수 있다.
![merge후](https://git-scm.com/figures/18333fig0328-tn.png)

즉, 두개의 branch가 나누어졌다가 합쳐진다.

히스토리를 한 줄로 관리하고싶다면 **Rebase**나 **Cherry-Pick**을 사용하면된다.

### Cherry-Pick

Commit 전체를 merge하는게 아니라 1~2개만 골라서 merge하고 싶을 때 사용한다.

```
[master c7d4ca5] commit1
[master 4de8b93] commit2
[master ea017e9] commit3
```

다음과 같이 3개의 commit는데 이중 한개(commit2)만 cherry-pick해서 merge를 하고 싶다면

```console
$ git cherry-pick 4de8b93
```

다음과 같이 해주면된다.

### Rebase

rebase는 cherry-pick을 여러번 해주는 것과 같다. 연결된 커밋을 그 순서대로 한방에 Cherry-pick 해온다.

![](https://git-scm.com/book/en/v2/images/basic-rebase-2.png)

다음 그림은 experiment와 master branch가 merge하여 새로운 commit이 생긴 경우이다.

```console
$ git checkout experiment
$ git rebase master
```

![](https://git-scm.com/book/en/v2/images/basic-rebase-3.png)

다음과 같이 이동한 다음에 차례대로 적용하게 된다.

```console
$ git checkout master
$ git merge experiment
```

![](https://git-scm.com/book/en/v2/images/basic-rebase-4.png)
rebase후에 merge를 하게 되면 다음과 같이 한줄로 히스토리를 관리할 수 있는 것을 볼 수 있다.
