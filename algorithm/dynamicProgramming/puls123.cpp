/*
 정수 4를 1, 2, 3의 조합으로 나타내는 방법은 총 7가지가 있다.
 
 1+1+1+1
 1+1+2
 1+2+1
 2+1+1
 2+2
 1+3
 3+1
 정수 n이 주어졌을 때, n을 1,2,3의 합으로 나타내는 방법의 수를 구하는 프로그램을 작성하시오.
 
 첫쨰 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있고, 정수 n이 주어진다. n은 양수이며 11보다 작다.
 */
#include <iostream>
using namespace std;

//Bottomup
int d[100001];


int main() {
    int t;
    scanf("%d",&t);
    
    while(t--){
        int n;
        scanf("%d",&n);
        d[0]=1,d[1]=1,d[2]=2;
        for(int i = 3;i<=n;i++){
            d[i]=d[i-1]+d[i-2]+d[i-3];
        }
        printf("%d\n",d[n]);
    }
    return 0;
}
