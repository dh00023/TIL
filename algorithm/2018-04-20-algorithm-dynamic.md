# Dynamic Programming

큰 문제를 작은 문제로 나눠서 푸는 알고리즘이다.

1. **Overlapping Subproblem** (겹치는 부분문제)
2. **Optimal Substructure**(문제의 정답을 작은 부분에서 알 수 있을 때) : 작은 문제에서 구한 정답은 그것을 포함하는 큰 문제에서도 동일하다.

이 두가지 속성을 만족해야 다이나믹 프로그래밍으로 문제를 풀 수 있다.

### Overlapping Subproblem
- 문제 : N번째 피보나치 수를 구하는 문제
- 작은문제 : <span style="color:blue">N-1번째 피보나치 수를 구하는 문제</span>, <span style="color:red">N-2번째 피보나치 수를 구하는 문제</span>


- 문제 : <span style="color:blue">N-1번째 피보나치 수를 구하는 문제</span>
- 작은문제 : <span style="color:red">N-2번째 피보나치 수를 구하는 문제</span>, <span style="color:green">N-3번째 피보나치 수를 구하는 문제</span>


- 문제 : <span style="color:red">N-2번째 피보나치 수를 구하는 문제</span>
- 작은문제 : <span style="color:green">N-3번째 피보나치 수를 구하는 문제</span>, N-3번째 피보나치 수를 구하는 문제

작은 문제가 겹쳐야한다. 큰 문제와 작은 문제는 상대적이다.

1. **큰 문제와 작은 문제를 같은 방법**으로 풀 수 있다.
2. **문제를 작은 문제로 쪼갤 수 있다.**

### Optimal Substructure
**문제의 정답을 작은 문제의 정답에서 구할 수 있다.**

N-1번째 피보나치 수를 구하는 문제 = N-2번째 피보나치 수를 구하는 문제 + N-3번째 피보나치 수를 구하는 문제

## 다이나믹 프로그래밍

- 각 문제는 한번만 풀어야 한다.
- 같은 문제는 구할 때마다 정답이 같다.(Optimal Substructure)
- 정답을 구했으면, 정답을 어딘가에 메모해놓는다.(**배열**)=>**Memoization**


### Top-down
1. 문제를 작은 문제로 나눈다.
2. 작은 문제를 푼다.
3. 작은 문제를 풀었으니, 이제 문제를 푼다.

**재귀호출**을 이용해서 문제를 쉽게 풀 수 있다.
시간복잡도는 채워야하는 칸의 수 X 한 칸을 채우는 복잡도(함수하나의 시간 복잡도)이다.

```cpp
// cpp
int memo[100]; //memoization
int fibonacci(int n){
	if(n<=1){
    	return n;
    }else{
    	if(memo[n]>0){
        	return memo[n];
        }
        memo[n] = fibonacci(n-1)+fibonacci(n-2);
        return memo[n];
    }
}
```

```python
# python
# memorization
d = [0] * 100

def fibonacci_recursion(x):

    # 1 or 2 는 1
    if x == 1 or x == 2:
        return 1

    # 이미 한번 호출된 적 있는 값은 기억해둔 값 반환
    if d[x]!=0:
        return d[x]

    # 한번도 호출된적 없는 값은 추가
    d[x] = fibonacci_recursion(x-1) + fibonacci_recursion(x-2)
    return d[x]

print(fibonacci_recursion(6))
```

### Bottom-up

1. 문제를 크기가 작은 문제부터 차례대로 푼다.
2. 문제의 크기를 조금씩 크게 만들면서 문제를 푼다.
3. 작은 문제를 풀면서 왔기 때문에, 큰 문제는 항상 풀 수 있다.

```cpp
int d[100];
int fibonacci(int n){
	d[0]=1;
    d[1]=1;
    for(int i=2;i<=n;i++){
    	d[i]=d[i-1]+d[i-2];
    }
    return d[n];
}
```

```python
# bottom-up

# dp table
d = [0] * 100

def fibonacci_loop(n):
    d[1] = 1
    d[2] = 1

    for i in range(3,n+1):
        d[i] = d[i-1]+d[i-2]

    print(d[n])

fibonacci_loop(99)
```

memoization을 할 때 무엇을 기록해야할지 정의하는 것이 최우선이다.



Top-down(memorization) 방식은 '하향식'이라고도 하며, bottom-up 방식은 '상향식'이라고도 한다. DP의 전형적인 형태는 bottom-up 방식이다.

Bottom-up 방식에서 사용되는 결과 저장용 리스트(배열)는 **DP 테이블** 이라 부르며, memorization은 Top-down 방식에 국한되어 사용되는 표현이다.

## 실습

### 1로 만들기
D[N] = N을 1로 만드는데 필요한 연산의 최솟값
1. N이 3으로 나누어 떨어지면, 3으로 나눈다. `D[N/3]+1`
2. N이 2로 나누어 떨어지면, 2로 나눈다. `D[N/2]+1`
3. 1을 뺀다. `D[N-1]+1`

=> **D[N]=min(1,2,3)**

#### top-down

```cpp
#include <iostream>

//Top-Down(재귀)
int d[1000001];
int divn(int n){
    if(n==1) return 0;
    if(d[n]>0) return d[n];
    //-1
    d[n]=divn(n-1)+1;
    if(n%2==0){
        int temp=divn(n/2)+1;
        if(d[n]>temp) d[n] = temp;
    }
    if(n%3==0){
        int temp=divn(n/3)+1;
        if(d[n]>temp) d[n] = temp;
    }
    return d[n];
}
```

#### bottom-up

```cpp
//Bottom-up
void divbu(int n){
    d[1]=0;
    for(int i=2;i<=n;i++){
        d[i]=d[i-1]+1;
        if(i%2==0 && d[i]>d[i/2]+1){
            d[i]=d[i/2]+1;
        }
        if(i%3==0 && d[i]>d[i/3]+1){
            d[i]=d[i/3]+1;
        }
    }
    printf("%d",d[n]);
}
```

### 2Xn 타일링
2Xn 직사각형을 1x2,2x1타일로 채우는 방법의 수
=> **D[n]=2xi직사각형을 채우는 방법의 수**
=> **D[n]=D[n-1]+D[n-2]**

이 때, n=0일 때도 경우의 수이기 때문에 1을 출력한다.

#### bottom-up

```cpp
#include <iostream>
using namespace std;

int d[10001];
int main() {
    int x;
    cin >> x;
    d[1]=1;
    d[0]=1;
    for(int i=2;i<=x;i++){
        d[i]=d[i-1]+d[i-2];
        d[i]%=10007;
    }
    cout << d[x] << "\n";
}
```

### 2xn 타일링 2

2Xn 직사각형을 1x2,2x1,2x2타일로 채우는 방법의 수
=> **D[n]=2xi직사각형을 채우는 방법의 수**
=> **`D[n]=D[n-1]+2*D[n-2]`**

#### bottom-up

```cpp
#include <iostream>
using namespace std;

int d[10001];
int main() {
    int x;
    cin >> x;
    d[1]=1;
    d[0]=1;
    for(int i=2;i<=x;i++){
        d[i]=d[i-1]+2*d[i-2];
        d[i]%=10007;
    }
    cout << d[x] << "\n";
}
```

### 1,2,3 더하기
정수 n을 1,2,3의 조합으로 나타내는 방법의 수를 구하는 문제
=> **D[n]=정수 n을 1,2,3의 조합으로 나타내는 방법의 수**
=> **마지막에 오는 수가 중요하다.**
=> **D[n]=D[n-1]+D[n-2]+D[n-3]**

#### bottom-up

```cpp
#include <iostream>
using namespace std;

int d[10001];
int main() {
    int t;
    cin >> t;
    while(t--){
        int x;
        cin >> x;
        d[1]=1;
        d[0]=1;
        d[2]=2;
        for(int i=2;i<=x;i++){
            d[i]=d[i-1]+d[i-2]+d[i-3];
        }
        cout << d[x] << "\n";
    }
}
```

### 붕어빵 판매하기
붕어빵 i개를 팔아서 얻을 수 있는 수익 P[i]일 때, N개를 모두 판매해서 얻을 수 있는 최대 수익구하기
=> **D[n]=n개를 모두 판매해서 얻을 수 있는 최대수익**

|붕어빵 수|가격|남은 붕어빵의 수|최대수익 가능한 경우|
|------|------|------|------|
|1|P[1]|n-1|P[1]+D[n-1]|
|2|P[2]|n-2|P[2]+D[n-2]|
|...|...|...|...|
|n-1|P[n-1]|1|P[n-1]+D[1]|
|n|P[n]|0|P[n]+D[0]|

=> **D[n] = max(P[i]+D[n-i])(1<=i<=n)**

```cpp
#include <iostream>
using namespace std;

int d[10001];//붕어빵 n개를 팔아서 얻을 수 있는 최대수익
int p[10001];
int main(){
    int n;//붕어빵의 수
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            d[i]=max(d[i],d[i-j]+p[j]);
        }
    }
    cout<<d[n];
}
```

### 쉬운 계단 수

인접한 자리의 차이가 1이 나는 수를 계단 수라고 한다. ex)45656
길이가 N인 계단 수의 개수를 구하여라.(0으로 시작하는 수는 없다.)

=> **D[N][L]=N자리 계단수, 마지막 수 L**
L -> L+1 or L-1
=> **D[N][L]=D[N-1][L-1]+D[N-1]+D[L+1]**

```cpp
#include <iostream>
using namespace std;

int d[101][9];
int main(){
    int n,ans=0;
    scanf("%d",&n);
    
    for(int j=1;j<=9;j++){
        d[1][j]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=9;j++){
            d[i][j]=0;
            if(j-1>=0)d[i][j]+=d[i-1][j-1];
            if(j+1<=9)d[i][j]+=d[i-1][j+1];
        }
    }
    for(int j=0;j<=9;j++){
        ans+=d[n][j];
    }
    printf("%d",ans);
}
```

### 오르막 수
오르막 수는 수의 자리가 오름차순을 이루는 수를 말한다. 이 때, 인접한 수가 같아도 오름차순으로 친다.
예를 들어, 2234와 3678, 11119는 오르막 수이지만, 2232, 3676, 91111은 오르막 수가 아니다.
수의 길이 N이 주어졌을 때, 오르막 수의 개수를 구하는 프로그램을 작성하시오. 수는 0으로 시작할 수 있다.

=> **D[N][L]=N자리 오르막수, 마지막수 L**
=> **D[N][L]=sum(D[N-1][k])(0<=k<=L)**

```cpp
#include <iostream>
using namespace std;

int d[1001][10];
int main(){
    int n;
    scanf("%d",&n);
    
    for(int j=0;j<=9;j++){
        d[1][j]=1;
    }
    for(int i=2;i<=n;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=j;k++)
                d[i][j]+=d[i-1][k];
    int ans=0;
    for(int j=0;j<=9;j++){
        ans+=d[n][j];
    }
    printf("%d",ans);
}
```

### 이친수

0과 1로만 이루어진 수를 이진수라 한다. 이러한 이진수 중 특별한 성질을 갖는 것들이 있는데, 이들을 이친수(pinary number)라 한다. 이친수는 다음의 성질을 만족한다.

- 이친수는 0으로 시작하지 않는다.
- 이친수에서는 1이 두 번 연속으로 나타나지 않는다. 즉, 11을 부분 문자열로 갖지 않는다.

예를 들면 1, 10, 100, 101, 1000, 1001 등이 이친수가 된다. 하지만 0010101이나 101101은 각각 1, 2번 규칙에 위배되므로 이친수가 아니다.

=> **D[n]=D[n-1]+D[n-2] (n자리 2친수 = n번째 자리에 0+n번째 자리에 1)**

```cpp
#include <iostream>
using namespace std;

int d[91];
int main(){
    
    int n;
    scanf("%d",&n);
    
    d[1]=1;
    d[2]=1;
    
    for(int i=3;i<=n;i++){
        d[i]=d[i-1]+d[i-2];
    }
    
    printf("%d",d[n]);
}
```

### 스티커

스티커 2n개가 2Xn모양으로 배치되어있다. 스티커 한 장을 떼면 변을 공유하는 스티커는 모두 찢어져서 사용할 수 없다. 점수의 합을 최대로 만드는 문제. 즉, 2n개의 스티커 중에서 점수의 합이 최대가 되면서 서로 변을 공유 하지 않는 스티커 집합을 구해야 한다.

=> D[n][s]=2Xn 스티커 상태 s

- s = 0은 뜯지 않음
	- D[n][0]=n-1열에서 스티커를 어떻게 뜯었는지 상관이 없다. => `max(D[n-1][0],D[n-1][1],D[n-1][2])`
- s = 1은 위쪽 스티커 뜯음
	- D[n][1]= n-1열의 위쪽 스티커는 뜯으면 안됨. `max(D[n-1][0],D[n-1][2])+A[n][0]`
- s = 2는 아래쪽 스티커 뜯음
	- D[n][1]= n-1열의 아래쪽 스티커는 뜯으면 안됨. `max(D[n-1][0],D[n-1][1])+A[n][1]`

=> **max(D[n][0],D[n][1],D[n][2])**

```cpp
#include <iostream>
using namespace std;

int d[100000][3];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);

        int array[n][2];
        for(int i=0;i<2;i++){
            for(int j=0;j<n;j++){
                scanf("%d",&array[j][i]);
            }
        }
        d[0][0]=0;
        d[0][1]=array[0][0];
        d[0][2]=array[0][1];
        for(int i=1;i<n;i++){
            d[i][0]=max(max(d[i-1][0], d[i-1][1]),d[i-1][2]);
            d[i][1]=max(d[i-1][0],d[i-1][2])+array[i][0];
            d[i][2]=max(d[i-1][0],d[i-1][1])+array[i][1];
        }
        printf("%d\n",max(max(d[n-1][0],d[n-1][1]),d[n-1][2]));
    }
}
```

### 포도주시식

1. 포도주 잔을 선택하면 그 잔에 들어있는 포도주는 모두 마셔야 하고, 마신 후에는 원래 위치에 다시 놓아야 한다.
2. 연속으로 놓여 있는 3잔을 모두 마실 수는 없다.

1부터 n까지의 번호가 붙어 있는 n개의 포도주 잔이 순서대로 테이블 위에 놓여 있고, 각 포도주 잔에 들어있는 포도주의 양이 주어졌을 때, 가장 많은 양의 포도주를 마실 수 있도록 하는 프로그램을 작성하시오.

D[i][j] = A[1]~A[n]까지 포도주를 마셧을 때 마실 수 있는 포도주의 최대 양
- 0번연속 : A[i]를 마시지 않음
	- max(D[i-1][0],D[i-1][1],D[i-1][2])
- 1번연속 : A[i-1]을 마시지 않음.
	- D[i-1][0]+A[i]
- 2번연속 : A[i-1]마시고, A[i-2]마시지 않음
	- D[i-1][1]+A[i]

```cpp
#include <iostream>
using namespace std;

int d[10001][3];
int main(){
    int n;
    scanf("%d",&n);
    
    int g[n];
    
    for(int i=1;i<=n;i++){
        scanf("%d",&g[i]);
    }
    
    d[0][0]=d[0][1]=d[0][2]=0;
    
    for(int i=1;i<=n;i++){
        d[i][0]= max(max(d[i-1][0],d[i-1][1]),d[i-1][2]);
        d[i][1]= d[i-1][0]+g[i];
        d[i][2]= d[i-1][1]+g[i];
    }
    printf("%d",max(max(d[n][0],d[n][1]),d[n][2]));
}
```

D[i] = A[1]~A[n]까지 포도주를 마셧을 때 마실 수 있는 포도주의 최대 양
- 0번연속 : A[i]를 마시지 않음
	- D[i-1]
- 1번연속 : A[i-1]을 마시지 않음.
	- D[i-2]+A[i]
- 2번연속 : A[i-1]마시고, A[i-2]마시지 않음
	- D[i-3]+A[i-1]+A[i]

=> D[i]=max(D[i-1], D[i-2]+A[i], D[i-3]+A[i-1]+A[i])

```cpp
d[0]=0;
d[1]=g[1];
d[2]=g[1]+g[2];

for(int i=3;i<=n;i++){
	d[i]= max(max(d[i-1],d[i-2]+g[i]),d[i-3]+g[i]+g[i-1]);
}
```

### 가장 긴 증가하는 부분 수열

수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예) 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {**10**, **20**, 10, **30**, 20, **50**} 이고, 길이는 4이다.

D[i]= A[1]~A[n]까지 수열이 있을 때, A[i]를 마지막으로 하는 가장 긴 증가하는 부분 수열의 길이(A[i]를 반드시 포함해야한다.)

```cpp
#include <iostream>
using namespace std;

int d[1001];
int main(){
    int n; //수열의 크기
    scanf("%d",&n);
    
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    for(int i=0;i<n;i++){
        d[i]=1;
        for(int j=0;j<i;j++){
            if(a[i]>a[j]&&d[i]<d[j]+1)d[i]=d[j]+1;
        }
    }
    int maxd=0;
    for(int i=0;i<n;i++){
        if(maxd<d[i])maxd=d[i];
    }
    printf("%d",maxd);
}
```

### 가장 긴 감소하는 부분 수열

수열 A가 주어졌을 때, 가장 긴 감소하는 부분 수열을 구하는 프로그램을 작성하시오.

예) 수열 A = {10, 30, 10, 20, 20, 10} 인 경우에 가장 긴 감소하는 부분 수열은 A = {10, **30**, 10, **20**, 20, **10**}  이고, 길이는 3이다.

D[i]= A[1]~A[n]까지 수열이 있을 때, A[i]를 마지막으로 하는 가장 긴 감소하는 부분 수열의 길이(A[i]를 반드시 포함해야한다.)

```cpp
#include <iostream>
using namespace std;

int d[1001];
int main(){
    int n; //수열의 크기
    scanf("%d",&n);
    
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    for(int i=0;i<n;i++){
        d[i]=1;
        for(int j=0;j<i;j++){
            if(a[i]<a[j]&&d[i]<d[j]+1)d[i]=d[j]+1;
        }
    }
    int maxd=0;
    for(int i=0;i<n;i++){
        if(maxd<d[i])maxd=d[i];
    }
    printf("%d",maxd);
}
```

### 가장 긴 바이토닉 부분 수열

수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면, 그 수열을 바이토닉 수열이라고 한다.

예) {10, 20, **30**, 25, 20}과 {10, 20, 30, **40**}, {**50**, 40, 25, 10} 은 바이토닉 수열이지만,  {1, 2, 3, 2, 1, 2, 3, 2, 1}과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.

**가장 긴 증가하는 부분 수열(D1)과 가장 긴 감소하는 부분 수열(D2)를 구한다음 D1+D2-1을 구하면된다.**
```cpp
#include <stdio.h>
/*
 수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면, 그 수열을 바이토닉 수열이라고 한다.
 
 예를 들어, {10, 20, 30, 25, 20}과 {10, 20, 30, 40}, {50, 40, 25, 10} 은 바이토닉 수열이지만,  {1, 2, 3, 2, 1, 2, 3, 2, 1}과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.
 
 수열 A가 주어졌을 때, 그 수열의 부분 수열 중 바이토닉 수열이면서 가장 긴 수열의 길이를 구하는 프로그램을 작성하시오.
 
 첫째 줄에 수열 A의 크기 N이 주어지고, 둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. (1 ≤ N ≤ 1,000, 1 ≤ Ai ≤ 1,000)
 */
int d[1001];
int d2[1001];
int main() {
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        d[i]=1;
        for(int j=0;j<=i;j++){
            if(a[i]>a[j]&&d[i]<d[j]+1){
                d[i]=d[j]+1;
            }
        }
    }
    for (int i=n-1; i>=0; i--) {
        d2[i] = 1;
        for (int j=i+1; j<n; j++) {
            if (a[i] > a[j] && d2[j]+1 > d2[i]) {
                d2[i] = d2[j]+1;
            }
        }
    }
    int ans =0 ;
    for(int i=0;i<n;i++){
        if(ans<d[i]+d2[i]-1){
           ans=d[i]+d2[i]-1;
        }
    }
    
    printf("%d",ans);
    return 0;
}
```

### 연속합
n개의 정수로 이루어진 임의의 수열이 주어진다. 우리는 이 중 연속된 몇 개의 숫자를 선택해서 구할 수 있는 합 중 가장 큰 합을 구하려고 한다. 단, 숫자는 한 개 이상 선택해야 한다.

예) 10, -4, 3, 1, 5, 6, -35, 12, 21, -1 이라는 수열이 주어졌다고 하자. 여기서 정답은 12+21인 33이 정답이 된다.

D[i]=A[i]로 끝나는 최대 연속합
- A[i-1]로 끝나는 연속합에 포함 D[i-1]+A[i]
- 새로운 연속합 시작 A[i]

```cpp
#include <iostream>
using namespace std;

int d[100001]; //A[i]로 끝나는 최대 연속합

int main(){
    int n; //연속된 숫자의 수
    scanf("%d",&n);
    
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    d[0]=a[0];
    for(int i=1;i<n;i++){
        d[i]=max(d[i-1]+a[i],a[i]);
    }
    int ans=d[0];
    for(int i=1;i<n;i++){
        if(ans<d[i])ans=d[i];
    }
    printf("%d",ans);
}
```

### 계단 오르기

계단 오르기 게임은 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임이다. 각각의 계단에는 일정한 점수가 쓰여 있는데 계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 된다.

1. 계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다. 즉, 한 계단을 밟으면서 이어서 다음 계단이나, 다음 다음 계단으로 오를 수 있다.
2. 연속된 세 개의 계단을 모두 밟아서는 안된다. 단, 시작점은 계단에 포함되지 않는다.
3. 마지막 도착 계단은 반드시 밟아야 한다.
따라서 첫 번째 계단을 밟고 이어 두 번째 계단이나, 세 번째 계단으로 오를 수 있다. 하지만, 첫 번째 계단을 밟고 이어 네 번째 계단으로 올라가거나, 첫 번째, 두 번째, 세번째 계단을 연속해서 모두 밟을 수는 없다.

D[i][j]=i번째 계단에 올랐을 때 총 점수의 최대값. (i번째 계단은 j개 연속해서 오른 계단)
- D[i][0]=0개연속(i번째 계단에 올라가야 하기 때문에 불가능한 경우)
- D[i][1]=1개연속(i-1은 밟으면 안된다.)=max(D[i-2][1],D[i-2][2])+a[i]
- D[i][2]=2개연속(i번째 계단은 밟아야하고, 반드시 1개 연속해서 올라온 계단이어야한다.)=D[i-1][1]+a[i]

```cpp
#include <iostream>
using namespace std;

int d[301][3]; //A[i]로 끝나는 최대 점수

int main(){
    int n; //계단수
    scanf("%d",&n);
    
    int a[n];//각 계단 점수
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    d[0][1]=a[0];
    d[1][1]=a[1];
    d[1][2]=a[1]+a[0];
    for(int i=2;i<n;i++){
        d[i][1]=max(d[i-2][1],d[i-2][2])+a[i];
        d[i][2]=d[i-1][1]+a[i];
    }
    printf("%d",max(d[n-1][1],d[n-1][2]));
}
```

이때 경우의 수로 밖으로 빼준다면 2차원에서 1차원으로 차원을 줄일 수 있다.

D[i]=i번째 계단에 올라갔을 때, 최대 점수
- 1개 연속 : i-1번째 계단은 밟으면 안됨
	- i-2는 반드시 밟았어야 함
	- D[i-2]+A[i]
- 2개 연속 : i-1번째 계단은 밟고, i-2는 밟으면 안됨
	- i-3번째 계단은 반드시 밟아야 함
	- D[i-3]+A[i-1]+A[i]

```cpp
#include <iostream>
using namespace std;

int d[301]; //A[i]로 끝나는 최대 점수
int a[301];//각 계단 점수
int main(){
    int n; //계단수
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    d[1]=a[1];
    d[2]=a[1]+a[2];
    
    for(int i=3;i<=n;i++){
        d[i]=max(d[i-2]+a[i],d[i-3]+a[i-1]+a[i]);
    }
    printf("%d",d[n]);
}
```

### 제곱수의 합

어떤 자연수 N은 그보다 작은 제곱수들의 합으로 나타낼 수 있다. 예를 들어 11=3^2+1^2+1^2(3개 항)이다. 이런 표현방법은 여러 가지가 될 수 있는데, 11의 경우 11=2^2+2^2+1^2+1^2+1^2(5개 항)도 가능하다. 이 경우, 수학자 숌크라테스는 “11은 3개 항의 제곱수 합으로 표현할 수 있다.”라고 말한다. 또한 11은 그보다 적은 항의 제곱수 합으로 표현할 수 없으므로, 11을 그 합으로써 표현할 수 있는 제곱수 항의 최소 개수는 3이다.

D[i]=자연수 N을 이렇게 제곱수들의 합으로 표현할 때에 그 항의 최소개수
- **마지막항**이 중요하다.
- min(D[i-j^2]+1) (1<=i<=j^2)

```cpp
#include <iostream>
using namespace std;

int d[100001]; //제곱합으로 표현하는 최소항 개수
int main(){
    int n; //자연수
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        d[i]=i; //1^2으로 표현한 개수(즉, 최대항)
        for(int j=1;j*j<=i;j++){
            if(d[i]>d[i-j*j]+1)d[i]=d[i-j*j]+1;
        }
    }
    printf("%d",d[n]);
}
```



### 타일 채우기
3×N 크기의 벽을 2×1, 1×2 크기의 타일로 채우는 경우의 수를 구해보자.

D[i]=3Xi를 채우는 방법의 수
- `D[i]=3*D[i-2]+2*D[i-4]+2*D[i-6]+...`

```cpp
#include <iostream>
using namespace std;

int d[31]; //3*i를 표현할 수 있는 경우의 수
int main(){
    int n;
    scanf("%d",&n);
    d[0]=1;
    for (int i=2; i<=n; i+=2) {
        d[i] = d[i-2]*3;
        for (int j=i-4; j>=0; j-=2) {
            d[i] += d[j]*2;
        }
    }
    printf("%d",d[n]);
}
```

### 파도반 수열
![](https://www.acmicpc.net/upload/images/pandovan.png)

그림과 같이 삼각형이 나선 모양으로 놓여져 있다. 첫 삼각형은 정삼각형으로 변의 길이는 1이다. 그 다음에는 다음과 같은 과정으로 정삼각형을 계속 추가한다. 나선에서 가장 긴 변의 길이를 k라 했을 때, 그 변에 길이가 k인 정삼각형을 추가한다.

파도반 수열 P(N)은 나선에 있는 정삼각형의 변의 길이이다. P(1)부터 P(10)까지 첫 10개 숫자는 1, 1, 1, 2, 2, 3, 4, 5, 7, 9이다.

N이 주어졌을 때, P(N)을 구하는 프로그램을 작성하시오.

D[i]=P(i)파도반 수열
- D[i-2]+D[i-3]
- D[i-5]+D[i-1]

```cpp
#include <iostream>
using namespace std;

int d[101]; //파도반수열
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        d[0]=0;
        d[1]=d[2]=1;
        for (int i=3; i<=n; i++) {
            d[i] = d[i-2]+d[i-3];
        }
        printf("%d\n",d[n]);
    }
}
```

### 합분해

0부터 N까지의 정수 K개를 더해서 그 합이 N이 되는 경우의 수를 구하는 프로그램을 작성하시오.

덧셈의 순서가 바뀐 경우는 다른 경우로 센다(1+2와 2+1은 서로 다른 경우). 또한 한 개의 수를 여러 번 쓸 수도 있다.

D[K][N]=정수 0부터 N까지의 정수 K개를 더해서 N이 만들어지는 경우의 수
- +=D[K-1][N-L] (0<=L<=N)

```cpp
#include <iostream>
using namespace std;

long long int d[201][201]; //합분해
int main(){
    int n,k;
    scanf("%d %d",&k,&n);
    d[0][0]=1LL;
    for(int i=1;i<=k;i++){
        for(int j=0;j<=n;j++){
            for(int l=0;l<=j;l++){
                d[i][j]+=d[i-1][j-l];
                d[i][j]%=1000000000;
            }
        }
    }
    printf("%lld",d[k][n]);
}
```

### 암호 코드

상근: 그냥 간단히 암호화 하자. A를 1이라고 하고, B는 2로, 그리고 Z는 26으로 하는거야.
선영: 그럼 안돼. 만약, "BEAN"을 암호화하면 25114가 나오는데, 이걸 다시 글자로 바꾸는 방법은 여러가지가 있어.
상근: 그렇네. 25114를 다시 영어로 바꾸면, "BEAAD", "YAAD", "YAN", "YKD", "BEKD", "BEAN" 총 6가지가 나오는데, BEAN이 맞는 단어라는건 쉽게 알수 있잖아?
선영: 예가 적절하지 않았네 ㅠㅠ 만약 내가 500자리 글자를 암호화 했다고 해봐. 그 때는 나올 수 있는 해석이 정말 많은데, 그걸 언제 다해봐?
상근: 얼마나 많은데?
선영: 구해보자!
어떤 암호가 주어졌을 때, 그 암호의 해석이 몇 가지가 나올 수 있는지 구하는 프로그램을 작성하시오.

D[i]=i번째 문자까지 해석했을 때, 나올 수 있는 해석의 가짓 수
- 1자리 암호(0제외)
- 2자리 암호(10~26)