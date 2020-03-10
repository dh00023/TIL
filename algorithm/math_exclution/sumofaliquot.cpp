#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 약수의 합 구하기
int main(){
    // 입력값 n이 100억이 최대값일 경우에는 int로는 값을 처리할 수 없으므로 long long int형을 활용해야한다.
    
    long long int n,sum=0,i;
    scanf("%lld",&n);
    //영역배제 - 1.모든 자연수 n에 대해 1과 n은 항상 n의 약수이다.
    // 2. 모든 자연수 n에 대하여, 2이상 n미만의 자연수들 중 가장 큰 n 의 약수는 n/2를 넘지 않는다.
    // 3. n = d(k) X d(c-k+1) k번째 원소와 c-k+1번째 원소의 곱은 항상 n이다.
    for(i=2;i*i<=n;i++)
        if(n%i==0)sum+=(i+n/i);
    if(i*i==n)sum+=i;
    printf("%lld",sum);
    return 0;
}
