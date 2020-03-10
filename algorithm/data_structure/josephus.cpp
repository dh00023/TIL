/*
 조세퍼스 문제는 다음과 같다.
 
 1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 M(≤ N)이 주어진다. 이제 순서대로 M번째 사람을 제거한다. 한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 원에서 사람들이 제거되는 순서를 (N, M)-조세퍼스 순열이라고 한다. 예를 들어 (7, 3)-조세퍼스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.
 
 N과 M이 주어지면 (N,M)-조세퍼스 순열을 구하는 프로그램을 작성하시오.
 */
#include <iostream>
#include <string>
#include <queue>
using namespace std;


int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    
    queue<int> qu;
    for(int i=1;i<=n;i++){
        qu.push(i);
    }
    printf("<");
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m-1;j++){
            qu.push(qu.front());
            qu.pop();
        }
        printf("%d, ",qu.front());
        qu.pop();
    }
    printf("%d>",qu.front());
}