/*
4. 두더지굴
모든 원소가 0 또는 1인 행렬이 있습니다.

1로 표시된 원소는 영역을 나타냅니다.
여기에서 상하좌우에 인접한 1은 같은 영역이라고 가정합니다.
각 영역의 크기는 1의 개수로 정의합니다.

주어진 N x N 크기의 행렬에서 영역의 개수와 각 영역의 크기를 오름차순으로 출력하세요.


[입력]

첫 번째 행은 행렬의 크기인 N입니다. N은 1 이상 10 이하의 자연수입니다.
입력 두 번째 행부터는 공백으로 구분된 0과 1로 행렬이 주어집니다. 각 행은 개행 문자(newline, \n)로 구분됩니다.


[출력]

첫 번째 행은 영역의 개수를 출력합니다.
두 번째 행은 각 영역의 크기를 공백으로 구분하여 오름차순으로 출력합니다.
한 행의 끝은 불필요한 공백 없이 개행 문자(newline, \n)로 끝나야 합니다.
영역이 존재하지 않을 경우 영역 수 0으로 1행으로만 출력합니다. 

[행렬 및 영역 예시]



영역은 3개이며, 각 영역의 크기는 4, 5, 7입니다. 

입/출력 예시
⋇ 입출력 형식을 잘 지켜주세요.
␣ : 공백↵ : 줄바꿈
보기 입력 1
6↵
0 ␣1 ␣1 ␣0 ␣0 ␣0↵
0 ␣1 ␣1 ␣0 ␣1 ␣1↵
0 ␣0 ␣0 ␣0 ␣1 ␣1↵
0 ␣0 ␣0 ␣0 ␣1 ␣1↵
1 ␣1 ␣0 ␣0 ␣1 ␣0↵
1 ␣1 ␣1 ␣0 ␣0 ␣0
출력 1
3↵
4 ␣5 ␣7↵

보기 입력 2
4↵
0 ␣0 ␣0 ␣0↵
0 ␣0 ␣0 ␣0↵
0 ␣0 ␣0 ␣0↵
0 ␣0 ␣0 ␣0
출력 2
0↵
*/
#include <stdio.h>
#include <algorithm>

int n,A[11][11],cnt,Size[11];

bool safe(int a, int b){
    return (0<=a && a<n)&&(0<=b &&b<n);
}
bool cmp(int a,int b){
    return a>b;
}
void dfs(int a,int b, int c){
    A[a][b]=c;
    if(safe(a+1,b)&&A[a+1][b]==1)
        dfs(a+1,b,c);
    if(safe(a-1,b)&&A[a-1][b]==1)
        dfs(a-1,b,c);
    if(safe(a,b+1)&&A[a][b+1]==1)
        dfs(a,b+1,c);
    if(safe(a,b-1)&&A[a][b-1]==1)
        dfs(a,b-1,c);
}
void solve(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(A[i][j]==1){
                cnt++;
                dfs(i,j,cnt+1);
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(A[i][j])
                Size[A[i][j]-2]++;
    std::sort(Size,Size+cnt,cmp);
    
}
void input(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&A[i][j]);
}
void output(){
		printf("%d\n",cnt);
    for(int i=cnt-1;i>=0;i--)
        printf("%d ",Size[i]);
}
int main(){
    input();
    solve();
    output();
}