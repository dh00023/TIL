# Recursion

**재귀호출 / 순환**이란 알고리즘이나 함수가 수행도중 자기 자신을 다시 호출하여 문제를 해결하는 기법이다. 정의자체가 순환적으로 되어 있는 경우에 적합하다.

자기 자신을 호출하는 것이므로 현재 작업을 처리하기 위해서 같은 유형의 하위작업이 필요하다. 문제를 한번에 해결하기보다는 **같은 유형의 하위작업으로 분할하여 작은 문제부터 해결**하는 방법이다.
순환 함수에서 탈출할 수 있는 **basecase**가 반드시 하나 이상 있어야한다.

순환 알고리즘에서는 **순환 호출을 하는 부분(recursive case)**과 순환 호출을 **멈추는 부분(base case)**이 있다. 만약 멈추는 부분이 없다면 시스템 오류가 발생할 때까지 무한히 호출하게 된다.

멈추는 부분이 반드시 있어야한다. 없다면 **시스템 오류가 발생할때까지 무한 호출**



## 순환과 반복

| 순환                                                         | 반복                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 순환 호출 이용(재귀함수)                                     | for 또는 while                                               |
| 구현 속도가 빠름                                             | 수행 속도가 빠름                                             |
| 순환적인 문제에서는 자연스러운 방법이나 함수 호출의 오버헤드가 있을 수 있다. | 순환적인 문제에 대해서는 프로그램 작성이 아주 어려울 수도 있다. |

- 실행시간 : 컴퓨터가 실행하는 시간

- 개발시간 : 코딩하는 시간

```cpp
long int fact(int n){
  if(n<=1) return 1; // basecase
  else return(n*fact(n-1));
}
```

```cpp
long int fact(int n){
  int i, res = 1;
  if(n<=1)return 1;
  else{
    for(i=n; i>=0;i--){
      res = res * i;
    }
    return res;
  }
}
```

두 가지 방법 다 `O(n)` 의 시간 복잡도를 가진다. 순환 호출은 이해하기 쉽다는 장점이 있으나 수행시간과 메모리에 있어서는 비효율적인 경우가 많다. 

그러므로 각 문제의 경우에 맞게 반복과 순환을 선택해 풀어야한다. ( Dynamic Programming에서 중요 )

## 실습

### [팩토리얼 함수](https://www.acmicpc.net/problem/10872)

![](http://ncalculators.com/images/formulas/number-factorial-calculation.jpg)



- 순환

```c
#include <stdio.h>

int factorial(int n){
    if(n<=1) return 1;
    else return (factorial(n-1)*n);
}
```

- 반복

```c
#include <stdio.h>

int factorial(int n){
    int res = 1;
    if( n<=1 ) return res;
    else{
        for(int i = 2; i<=n;i++) res*=i;
		return res;
    }    
}
```



### 거듭제곱 구하기(x^n)

숫자 x의 n제곱 값을 구하는 문제

- 순환

```c
int power(int x, int n){
    if(n==0)return 1;
    else return (x*power(x,n-1));
}
```

이렇게 해도 되나 n이 짝수인 경우와 홀수인 경우를 나눠서 구하면 연산량이 더 줄어든다.

```c
int power(int x, int n){
    if(n==0)return 1;
    else if(n%2==0){
        return power(x*x,n/2);
    }else return x*power(x*x,(n-1)/2);
}
```

```
예시)
2^10
>> 10%2==0, power(4,5)
>> 5%2==1, 4*power(16,2)
>> 4%2==0, 4*power(256,1)
>> 1%2==1, 4*256(256*256,0) == 4*256*1
```

여기서 k번의 순환 호출이 일어난다. 한번 순환호출이 일어날때마다 1번의 곱셈과 1번의 나눗셈이 일어난다. 전체 연산 수는 k=log2(N)에 비례한다. 즉, 시간복잡도는 O(log2(n))이다.

- 반복

```c
int power(int x, int n){
    int res = 1;
    if(n==0)return res;
    else{
        for(int i=1; i<=n;i++){
            res*=x;
        }
        return res;
    }
}
```

여기서 시간복잡도는 O(n)이다.



### 피보나치 수열

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/00008893a71eebbf4e7d89a0c162fe6359f5ac8c)

피보나치 수열은 정의 자체는 순환적이나 순환 호출을 사용하면 비효율적인 대표적인 예시이다.

- 순환

```c
int fib(int n){
    if(n==0)return 0;
    if(n==1)return 1;
    return (fib(n-1)+fib(n-2));
}
```

```
fib(6)
>> fib(5) + fib(4)
>> fib(4)+fib(3) + fib(3)+fib(2)
>> fib(3)+fib(2) + fib(2)+fib(1) + fib(2)+fib(1) + fib(1)+fib(0)
```

위와 같이 같은 항이 계속해서 중복해서 계산되므로 비효율 적이다.

- 반복

```c
int fib(int n){
    if(n<2)return n;
    else{
    	int i, current=1, last=0, tmp;
        for(i=2;i<=n;i++){
 			tmp = current;
 			current += last;
 			last = tmp;
        }
        return current;
    }
}
```



### Tripple 피보나치 수열

1, 2, 3, 6, 11, 20, 37, 68 ...

- 순환

```c
int fib_tri(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    if(n==2) return 2;
    else{
 	     return  fib_tri(n-3)+fib_tri(n-2)+fib_tri(n-1);
    }
}
```



###  하노이 탑

막대 A에 있는 원판을 막대 C로 옮기는 문제이다.

**조건**

1. 한 번에 하나의 원판만 이동할 수 있다.
2. 맨 위에 있는 원판만 이동할 수 있다.
3. 크기가 작은 원판 위에 큰 원판이 쌓일 수 없다.
4. 중간의 막대를 임시적으로 이용할 수 있으나 앞의 조건들을 지켜야 한다.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ8vudlhhc4OZz1XrdvaWkNXTvCWMRnZvsbXdcPAHNOWuaYHuub)

1단계. 막대 A에서 원반(1~n-1)을 막대 C를 이용해 막대 B로 옮긴다. **Hanoi(m-1,a,c,b)**

2단계. 막대 A에서 원반(n)을 막대 C로 옮긴다. if(m==1)

3단계. 막대 B에서 원반(1~n-1)을 막대 A를 이용해 막대 C로 옮긴다. **Hanoi(m-1,b,a,c)**

- 순환

```c
void hanoi(int n, char a, char b, char c){
	if(n==1)printf("원반%d이 막대[%c]에서 막대[%c]로 옮겨집니다.",n,a,c);
    else{
        hanoi(n-1,a,c,b);
        printf("원반%d이 막대[%c]에서 막대[%c]로 옮겨집니다.",n,a,c);
        hanoi(n-1,b,a,c);
    }
}
```



### Ackermann 함수

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/1a15ea2fcf1977e497bccdf1916ae23edc412fff)

[위키백과 아커만 함수](https://ko.wikipedia.org/wiki/%EC%95%84%EC%BB%A4%EB%A7%8C_%ED%95%A8%EC%88%98)에 함수에 대한 자세한 설명이 있다.

- 순환

```c
int ackermann(int m, int n){
    if(m==0)return n+1;
    if(m>0 && n==0)return ackermann(m-1,1);
	return ackermann(m-1,ackermann(m,n-1));
}
```

- 반복

basecase가 없다면 순환이 아니다! 이것에 초점을 두고 코드를 짜보았다. 

```c
int ackermann_loop(int m, int n){
    int mm = m, nn = n;
    while(mm!=0){
        if(nn == 0) nn = 1;
        else nn = ackermann_loop(mm,nn-1);
        mm--;
        printf("nn : %d \n",nn);
    }
    return nn+1;
}
```

2차원 배열로 구현했을 때는 범위를 지정해주지 않으면 계속해서 범위를 초과하는 문제발생했다.

```c
int A[100][100];
int ackermann_loop(int m, int n){
    for(int i = 0;i<=m;i++){
        for(int j = 0; j<=50; j++){
            if(i==0)A[i][j]=n+1;
            else if(j==0)A[i][j]=A[i-1][j];
            else{
                int tmp = A[i][j-1];
                A[i][j] = A[i-1][tmp];
            }
        }
    }
    return A[m][n];
}
```

또 규칙을 찾아서 구현하는 방법도 있다.

```c
int Acker_nonrecursive3(int m, int n)
     int i;
     int val=2;

     if(m==0) return n+1;
     if(m==1) return n+2;
     if(m==2) return 2*n+ 3;
     if(m==3) {  
        // return pow(2, n+3) -3;  또는 아래 for loop 으로 
		for(i=1; i<n+3; i++)
			val *=2;

		return val -3;
     }

     if(m==4){
		for(i=1; i< n+3; i++)
			val *=val;
		return val=val-3;
     }
}
```

## 완전 탐색

재귀 호출은 가능한 방법을 전부 만들어 보는 알고리즘으로 완전 탐색(Exhaustive Search)이라 볼 수 있다.

어떤 문제를 완전 탐색으로 해결하기 위해서 필요한 과정은 대략 다음과 같다.
1. 완전 탐색은 존재하는 모든 답을 하나씩 검사하므로, 걸리는 시간은 가능한 답의 수에 정확히 비례한다. 최대 크기의 입력을 가정했을 때 답의 개수를 계산하고, 이들을 모두 제한 시간안에 생성할 수 있을지 가늠해보고 적용해야한다.
2. 가능한 모든 답의 후보를 만드는 과정을 여러 개의 선택으로 나눈다. 각각의 선택은 답의 후보를 만드는 과정의 한 조각이다.
3. 그중 한 조각을 선택해 답의 일부를 만들고, 나머지 답을 재귀 호출을 통해 완성한다.
4. 조각이 하나밖에 남지 않은 경우, 혹은 하나도 남지 않은 경우에는 답을 생성했으므로 basecase로 선택해 처리한다.

[관련 알고리즘 문제 풀이 보러가기](./code/recursive)

