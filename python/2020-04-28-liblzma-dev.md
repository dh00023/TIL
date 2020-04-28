# Could not import the lzma module

```python
/.pyenv/versions/pandas/lib/python3.7/site-packages/pandas/compat/__init__.py:117: UserWarning: Could not import the lzma module. Your installed Python is incomplete. Attempting to use lzma compression will result in a RuntimeError.
  warnings.warn(msg)
```

`.py` 파일을 실행시켰을 때 다음과 같은 warning이 떴다. stackoverflow에 찾아보니 python 소스코드를 컴파일 하려면 반드시 **liblzma-dev**가 설치되어있어야한다고 한다.

## Install liblzma using homebrew


```bash
$ brew install xz
```

xz를 설치하고 난 후에 기존에 설치한 pyenv version을 삭제 후 재설치해줘야한다.

```bash
$ pyenv unsinstall 3.7.1
pyenv: remove /Users/jeongdaye/.pyenv/versions/3.7.1? y
```

```bash
$ pyenv install 3.7.1
```

설치가 완료되면 아래 코드가 `.zshrc`에 없다면 추가해준다.

```bash
eval "$(pyenv init -)"
```

```bash
$ source .zshrc
```

설치 후 다시 python 명령어를 수행하면 다음과 같이 warning message없이 실행되는 것을 확인할 수 있다.

```bash
python serires.py
<class 'pandas.core.series.Series'>


a    11
b     2
c     3
dtype: int64
```



## 참고

- [https://stackoverflow.com/questions/57743230/userwarning-could-not-import-the-lzma-module-your-installed-python-is-incomple](https://stackoverflow.com/questions/57743230/userwarning-could-not-import-the-lzma-module-your-installed-python-is-incomple)