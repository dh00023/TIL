# Math

수학과 관련된 알고리즘 문제를 풀어볼 것이다.

## 나머지연산

문제 중 나머지를 구하라는 문제가 있으면 답을 다 구한후에 구하면 범위를 초과할 수 있기때문에 중간에 해줘야한다.

```
(A+B)%C = ((A%C)+(B%C))%C

ex) A = q1*c + r1, B = q2*c + r2
A+B = (q1+q2)*c + (r1+r2)
(A+B)%c = (r1+r2)%c
A%c = r1, B%c = r2
```
- 곱하기의 경우에도 성립한다.
- 하지만 나누기의 경우에는 성립하지않는다.(Modular Inverse를 구해야한다.)
- 뺄셈의 경우 먼저 mod를 한 결과가 음수가 나올 수 있기때문에 **(A-B)%M = ((A%M)-(B%M)+M)%M**을 해줘야한다.

```cpp
#include <iostream>
using namespace std;

int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
	// 첫째 줄에 (A+B)%C, 둘째 줄에 (A%C + B%C)%C, 셋째 줄에 (A×B)%C, 넷째 줄에 (A%C × B%C)%C를 출력한다.
    printf("%d\n%d\n%d\n%d",(a+b)%c,(a%c+b%c)%c,(a*b)%c,(a%c*b%c)%c);
}
```

## 최대공약수(Gretest Common Divisor)
두 수 A와 B의 최대공약수 G는 A와 B의 공통된 약수 중에서 가장 큰 정수이다.
이때 최대공약수가 1인 두 수를 서로소(Coprime)이라고 한다.

1. 2부터 min(A,B)까지 모든 정수로 나누어보는 방법
2. 유클리드 알고리즘(a를 b로 나눈 나머지를 r이라 했을 때, GCD(a,b)=GCD(b,r), r=0이면 그 때 b가 최대공약수이다.)

```cpp
#include <iostream>
using namespace std;

//2. 유클리드 알고리즘 재귀
int gcd(int a, int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}
//3. 유클리드 알고리즘 비재귀
int gcd2(int a,int b){
    while(b!=0){
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}
int main(){
    int a,b,g;
    scanf("%d %d",&a,&b);
    g=1;
    //1. 모든 정수
    for(int i=2;i<=min(a,b);i++){
        if(a%i==0 && b%i==0){
            g=i;
        }
    }
}
```

`a<b`인 경우엔느 a%b=a이므로 자동으로 a와 b가 바뀌게 된다. 그러므로 따로 대소관계를 비교해줄 필요가 없다.

- 세 개이상의 최대공약수는 **GCD(a,b,c)=GCD(GCD(a,b),c)**와 같은 식으로 계속해서 구할 수 있다.

## 최소공배수(Least Common Multiple)
두 수의 공통된 배수 중에서 가장 작은 정수이다.
최소공배수는 최대공약수를 이용해서 구할 수 있다. 이 때, 최소공배수는 두 수보다 큰 수이므로 범위를 잘 확인해서 구해야한다.

- **`최대공약수 * 최소공배수 = A*B`**이다.
- 즉, **`최소공배수 = (A*B)/최대공약수`**이다.

```cpp
#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b==0)return a;
    else{
        return gcd(b,a%b);
    }
}
int main(){
    int a,b,g,l;
    scanf("%d %d",&a,&b); //이 둘은 10,000이하의 자연수이며 사이에 한 칸의 공백이 주어진다.
    
    g=gcd(a,b); //최대공약수
    l=(a*b)/g; //최소공배수
    printf("%d\n%d",g,l);
}
```
```cpp
#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b==0)return a;
    else{
        return gcd(b,a%b);
    }
}
int main(){
    int a,b,g,l,t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&a,&b); //이 둘은 10,000이하의 자연수이며 사이에 한 칸의 공백이 주어진다.

        g=gcd(a,b);
        l=(a*b)/g;
        printf("%d\n",l);
    }
}
```

```cpp
//양의 정수 n개가 주어졌을 때, 가능한 모든 쌍의 GCD의 합을 구하는 프로그램을 작성하시오.
#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b==0)return a;
    else return gcd(b,a%b);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        int num[101]={0};
        scanf("%d",&n);

        for(int i=0;i<n;i++)scanf("%d",&num[i]);
        long long int sum=0;
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                sum+=gcd(num[i],num[j]);
            }
        }
        printf("%lld\n",sum);
    }
}
```

## 진법 변환

10진법 수 N을 B진법으로 바꾸려면 N이 0이 될때까지 나머지를 계속해서 구하면된다.

```
ex)11을 3진법으로 바꾸는 방법
11/3=3...2
3/3=1...0
1/3=0...1

정답 102
```

### 10 to N

- 10진법 수 N이 주어진다. 이 수를 B진법으로 바꿔 출력하는 프로그램을 작성하시오.
- A: 10, B: 11, ..., F: 16, ..., Y: 34, Z: 35


```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int n,b;
    scanf("%d %d",&n, &b);
    string ans="";
    while(n>0){
        int r=n%b;
        if(r<10){
            ans+=(char)(r+'0');
        }else{
            ans+=(char)(r-10+'A');
        }
        n/=b;
    }
	reverse(ans.begin(),ans.end());
    cout << ans;
}
```

### B to 10

-  B진법 수 N이 주어진다. 이 수를 10진법으로 바꿔 출력하는 프로그램을 작성하시오.
-  A: 10, B: 11, ..., F: 16, ..., Y: 34, Z: 35

```cpp
#include <iostream>
#include <string>
using namespace std;


int main(){
    int ans=0;
    int b;
    string s;
    cin >> s >> b;
    for(int i=0;i<s.size();i++){
        if('0'<=s[i]&&s[i]<='9'){
            ans=ans*b+s[i]-'0';
        }else{
            ans=ans*b+s[i]-'A'+10;
        }
    }
    printf("%d",ans);
}
```

### 2 to 8

- 2진수가 주어졌을 때, 8진수로 변환하는 프로그램을 작성하시오.

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int n = s.size();
    if (n%3 == 1) {
        cout << s[0];
    } else if (n%3 == 2) {
        cout << (s[0]-'0')*2 + (s[1]-'0');
    }
    for (int i=n%3; i<n; i+=3) {
        cout << (s[i]-'0')*4 + (s[i+1]-'0')*2 + (s[i+2]-'0');
    }
    cout << '\n';
    return 0;
}
```

### 8 to 2

- 8진수가 주어졌을 때, 2진수로 변환하는 프로그램을 작성하시오.

```cpp
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
string eight[8] = {"000","001","010","011","100","101","110","111"};
int main(){
    string s;
    cin >> s;
    bool st = false;
    if(s.length() == 1 && s[0]-'0' == 0)cout << "0";
    for(int i = 0;i < s.length();i ++){
        int n = s[i]-'0';
        if(!st && n < 4){
            if(n == 0)    continue;
            else if(n == 1)  cout << "1";
            else if(n == 2)  cout << "10";
            else if(n == 3)  cout << "11";
            st = true;
        }
        else{
            cout << eight[n];
            st = true;
        }
    }
    return 0;
}
```

### 8 to -2

- -2진법은 부호 없는 2진수로 표현이 된다. 2진법에서는 20, 21, 22, 23이 표현 되지만 -2진법에서는 (-2)0 = 1, (-2)1 = -2, (-2)2 = 4, (-2)3 = -8을 표현한다. 10진수로 1부터 표현하자면 1, 110, 111, 100, 101, 11010, 11011, 11000, 11001 등이다.
- **나머지가 음수가 나오면 안된다.**
- 양수/-2
  - 2로 나누어 떨어지는 경우
- 음수/-2
  - 2로 나누어 떨어지는 경우

```cpp
/*
 8진수가 주어졌을 때, 2진수로 변환하는 프로그램을 작성하시오.
 첫째 줄에 8진수가 주어진다. 주어지는 수의 길이는 333,334을 넘지 않는다.
 첫째 줄에 주어진 수를 2진수로 변환하여 출력한다. 수가 0인 경우를 제외하고는 반드시 1로 시작해야 한다.
*/
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int main(){
    int n;
    scanf("%d",&n);
    string ans="";
    if(n==0)printf("%d",n);
    while(n!=1){
        if(n>0){
            if(n%(-2)==0){
                ans+='0';
            }else{
                ans+='1';
            }
        }else{
            if(n%(-2)==0){
                ans+='0';
            }else{
                ans+='1';
                n-=1;
            }
        }
        n/=-2;
    }
    ans+='1';
    reverse(ans.begin(), ans.end());
    cout << ans;
}
```

### A to B

- A진법을 B진법으로 바꾸기
- **A진법 -> 10진법 -> B진법**

```cpp
#include <iostream>
using namespace std;
void convert(int num, int base) {
    if (num == 0) return;
    convert(num/base, base);
    printf("%d ",num%base);
}
int main() {
    int a,b;
    cin >> a >> b;
    int n;
    cin >> n;
    int ans = 0;
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        ans = ans * a + x;
    }
    convert(ans,b);
    return 0;
}
```



## 소수

약수가 **1과 자기 자신** 밖에 없는 수이다.

N이 소수가 되려면, 2이상 N-1이하의 자연수로 나누어 떨어지면 안된다.

### 구현 방법

#### 방법1

```cpp
bool prime(int n){
    if(n<2)return false;
    for(int i=2;i<n;i++){
        if(n%i==0)return false;
    }
    return true;
}
```

- 시간복잡도 : O(n)

#### 방법2

 N의 약수 중에서 가장 큰 것은 N/2보다 작거나 같기 때문에 2이상 N/2이하의 자연수로 나누어 떨어지면된다.

```cpp
bool prime(int n){
    if(n<2)return false;
    for(int i=2;i<=n/2;i++){
        if(n%i==0)return false;
    }
    return true;
}
```

- 시간복잡도 : O(n)

#### 방법3

N이 소수가 아니라면, `N=a*b` 로 나타낼 수 있다.(a<=b)

두 수 a와 b의 차이가 가장 작은 경우는 루트(n) 이다. 그러므로 2이상 루트(n)이하 의 자연수로 나누어 떨어지지 않는 수를 비교해보면된다.  

예를 들어, N=24이다. 

- N=24의 약수 : 1 2 3 4 6 8 12 24
- 1과 자기자신(24)제외한 약수 : 2 3 4 6 8 12
- 루트(24) 는 약 4.xxxx이다. 루트(24)를 기준으로 반으로 나눌 수 있다.
- 2 3 4 | 6 8 12
- 루트(24)를 기준으로 작은수에서 나누어 떨어지는 수가 있다면 큰 쪽에서도 나누어 떨어지는 수가 있는 것이다. 그러므로 기준에서 작은수를 비교해 나누어 떨어지지 않는 수를 찾으면 된다.

```cpp
bool prime(int n){
    if(n<2)return false;
    for(int i=2;i*i<=n/2;i++){
        if(n%i==0)return false;
    }
    return true;
}
```

- 시간복잡도 : O(root(n))



### [소수 찾기](https://www.acmicpc.net/problem/1978)

주어진 수 N개 중에서 소수가 몇 개인지 찾아서 출력하는 프로그램을 작성하시오.

```cpp
bool prime(int n){
    if(n<2)return false;
    for(int i=2;i*i<=n;i++){
        if(n%i==0)return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    int n;
    int num,count = 0;
    scanf("%d",&n);
    
    while(n--){
        scanf("%d",&i);
        if(prime(num))count++;
    }
    printf("%d",count);
}
```



### 에라토스테네스의 체

1부터 N까지 **범위 안에 들어가는 모든 소수**를 구하려면 에라토스테네스의 체를 사용한다. 왜냐하면 각각의 수에 대해서 소수인지 아닌지 검사하는데 O(root(N))시간이 걸리는데, N개를 검사해야하므로 O(Nroot(N))의 시간이 걸리므로 너무 긴 시간이 걸린다.

에라토스테네스의 체는 다음과 같은 규칙으로 구한다.

1. 2부터 N까지 모든 수를 써놓는다.
2. 아직 지워지지 않은 수 중에서 가장 작은 수를 찾는다.
3. 그 수는 소수이다.
4. 이제 그 수의 배수를 모두 지운다.

![](http://mblogthumb2.phinf.naver.net/20160331_29/ptmosm_1459418759554UJOWk_JPEG/8-4.jpg?type=w2)

이렇게 지우고 남아 있는 수가 모두 소수이다.

#### 구현

```cpp
int p[100];		//소수 저장할 배열
int total_prime = 0; //소수의 개수
bool c[101];	//지워지면 true, 아니면 false
int n = 100;	//N까지의 수
for(int i=2;i<=n;i++){
    if(c[i]==false){
        p[total_prime++]=i;
        for(int j=i*i;j<=n;j+=i)c[j]=true;
    }
}
```

- 시간복잡도 : O(Nloglog(N))
  - n/2 + n/3 + n/4 + …. = loglog(N)
- 주의할 점 i*i는 N의 범위에 따라서 i+i로 변경해준다.(백만이상일 경우 범위 초과)



#### [소수 구하기](https://www.acmicpc.net/problem/1929)

M이상 N이하의 소수를 모두 출력하는 프로그램을 작성하시오.

```cpp
#include <iostream>
using namespace std;
#define MAX 1000000
int p[MAX];
int total_prime=0;
bool check_prime[MAX+1];

int main(int argc, const char * argv[]) {
    
    int n,m;
    scanf("%d %d",&m, &n);
    
    for(int i=2;i<=n;i++){
        if(check_prime[i]==false){
            if(i>=m){
                p[total_prime++]=i;
                printf("%d\n",i);
            }
            for(int j=i+i;j<=n;j+=i){
                check_prime[j]=true;
            }
        }
    }
}
```



#### [골드바흐의 추측](https://www.acmicpc.net/problem/6588)

증명이 되지 않은 문제여서 추측이라고 한다.

- 2보다 큰 모든 짝수는 **두 소수의 합**으로 표현이 가능하다.
- 5보다 큰 모든 홀수는 **세 소수의 합**으로 표현이 가능하다.
- 10^18이하에서는 참인 것이 증명되어 있다.

```cpp
#include <iostream>
using namespace std;
#define MAX 1000000
int p[MAX];
int total_prime=0;
bool check_prime[MAX+1];

int main(int argc, const char * argv[]) {
    
    int t;    
    for(int i=2;i<=MAX;i++){
        if(check_prime[i]==false){
            p[total_prime++]=i;
	        for(int j=i+i;j<=MAX;j+=i){
    	        check_prime[j]=true;
        }
    }
    while(1){
        scanf("%d",&t);
        if(t==0)break;
        for(int i=1;i<total_prime;i++){
            if(check_prime[t-p[i]]==false){
                printf("%d = %d + %d\n", t, p[i],t-p[i]);
                break;
            }
        }        
    }
}
```



## 소인수분해

정수 N을  소수의 곱으로 분해한 것이다.

- 소수를 구하지 않고도 해결할 수 있다.
- N을 소인수분해 했을 때, 나타날 수 있는 인수 중에서 가장 큰 값은 루트(N)이다.



#### [소인수분해 구하기](https://www.acmicpc.net/problem/11653)

```cpp
for(int i=2;i*i<=n;i++){
    while(n%i==0){
        printf("%d\n",i);
        n/=i;
    }
}
if(n>1){
    printf("%d\n",n);
}
```



## 팩토리얼

```
N! = 1* 2 * ... * N
```

팩토리얼은 **매우 큰 값**이다.

[03.Recursive](https://dh00023.github.io/algorithm/ds/2018/04/19/algorithm-3/)에서 팩토리얼을 순환과 반복으로 풀어본 문제가 있다.

우리가 팩토리얼을 풀 수 있는 규모는 10! = 3628800 까지이다.



### [팩토리얼 0의 개수](https://www.acmicpc.net/problem/1676)

N!에서 0이 몇개인지 알아내는 문제이다.

- ex) 10! = 36288**00**

0이 몇개인지는 N!를 소인수분해 해보면 알 수 있다.

- `10! = 2^6 * 3^4 * 7 * (2^2 * 5^2)`

하지만 실제로 구할 때 소인수분해를 다 할 필요는 없다. 5의 개수가 항상 2의 개수보다 적기 때문에 **5의 개수만 세어주면된다.**

N!의 0의 개수 = `[N/5]+[N/5^2]+[N/5^3]+…`

예를 들어 100!이면 (100/5 = 20) + (100/25) = 24개이다.

```cpp
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    scanf("%d",&n);
    int res = 0;
    for (int i=5; i<=n; i*=5) {
        res += n/i;
    }
    
    printf("%d",res);
}
```



### [조합 0의 개수](https://www.acmicpc.net/problem/2004)

nCm의 끝자리 0의 개수를 구하는 문제이다. 팩토리얼에서는 2의 개수가 5의 개수보다 항상 많기 때문에 5만 세어줬지만, 조합은 어떻게 될지 모르기 때문에 2와 5의 개수를 모두 세어줘야한다.

```cpp
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    long long  n,m;
    scanf("%lld %lld",&n,&m);
    long long  two=0, fiv=0;
    long long i;
    for (i=2; i<=n; i*=2) {
        two += n/i;
    }
    for (i=2; i<=n-m; i*=2) {
        two -= (n-m)/i;
    }
    for (i=2; i<=m; i*=2) {
        two -= m/i;
    }
    for (i=5; i<=n; i*=5) {
        fiv += n/i;
    }
    for (i=5; i<=n-m; i*=5) {
        fiv -= (n-m)/i;
    }
    for (i=5; i<=m; i*=5) {
        fiv -= m/i;
    }
    if(fiv>two)printf("%lld",two);
    else printf("%d",fiv);
}
```

