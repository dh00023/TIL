/*
 2×n 직사각형을 2×1과 2×2 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.
 
 아래 그림은 2×17 직사각형을 채운 한가지 예이다.
 
 첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)
 첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다.
 */

#include <iostream>
using namespace std;

//Bottomup
int d[10001];

int main() {
    
    int n;
    scanf("%d",&n);
    d[0]=1,d[1]=1;
    for(int i = 2;i<=n;i++){
        d[i]=d[i-1]+2*d[i-2];
        d[i]%=10007;
    }
    printf("%d",d[n]);
    return 0;
}
