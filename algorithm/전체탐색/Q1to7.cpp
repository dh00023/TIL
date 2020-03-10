//
//  main.cpp
//  Question1to7
//
//  Created by dahye Jeong on 2017. 6. 1..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
#include <stdio.h>

// 약수의 합 구하기
int q1(){
    int n,sum;
    scanf("%d",&n);
    sum = 0;
    // 계산량 O(n)
    for(int i=1;i<=n;i++)
        if(n%i==0)sum+=i;
    return sum;
}

// 최댓값(L)구하기
void q2(){
    // int형 최대 값 0x7fffffff, 최소값 0x80000000
    // 계산량 O(행 X 열)
    int A[10][10],max,mx,my = 0;
    max=0;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++) scanf("%d",&A[i][j]);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(A[i][j]>max){
                max = A[i][j];
                mx=i+1;
                my=j+1;
            }
        }
    /*코드를 더 줄일 수 있는 방법
     for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            scanf("%d",&A[i][j]);
            if(A[i][j]>A[x][y]){
                x=i;
                y=j;
            }
        }
     */
    printf("\n최대값 : %d\n위치 : (%d, %d)",max,mx,my);
}

// 삼각화단 만들기
// a<=b<=c a+b<c a+b+c = n

void q3(int n, int a, int b, int c)
{
    int cnt,chk[21][21][21];
    cnt=0;
    if(a+b+c==n){
        if(a<=b && b<=c && a+b<c && chk[a][b][c]==0)
        {
            cnt++;
            chk[a][b][c]=1;
        }
        
    }
    q3(n,a+1,b,c);
    q3(n,a,b+1,c);
    q3(n,a,b,c+1);
    /*
    scanf("%d",&n);
    
    count = 0;
    
    for(a=1;a<=n;a++){
        for(b=a;b<=n;b++){
            for(c=b;c<=n;c++){
                if(a+b+c == n && a+b<c){
                    printf("(%d,%d,%d)\n",a,b,c);
                    count++;
                    printf("%d\n",count);
                }
            }
        }
    }
     */
}

// 고기잡이(S) - 연못의 폭(N<=100) 각 칸에 있는 물고기 가치,
//그물의 가로의 길이와 세로의 길이가 주어질때, 잡을 수 있는 물고기의 최대이익
//계산량 O(NW)
void q4(){
    int N,W,A[100],max,sum;
    max=0;
    
    scanf("%d %d",&N,&W);
    for(int i=0;i<N;i++)
        scanf("%d",&A[i]);
    for(int i=W-1;i<=N;i++){
        sum=0;
        for(int j=i;j>=i-W+1;j--)
            sum+=A[j];
        if(sum>max)max=sum;
    }
    printf("%d",max);
}

// 고기잡이(L) - 연못의 폭(N,M<=100), 그물의폭(W<=N,H<=M)
// 각 물고기의 가치 7이하
// 2차원 전체 탐색법 O(NMWH)
void q5()
{
    int N,M,W,H,A[101][101],sum,max;
    max=0;
    scanf("%d %d",&N,&M);
    scanf("%d %d",&W,&H);
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            scanf("%d",&A[i][j]);
    for(int k=0;k<N;k++)
        for(int i=0;i<=M-H;i++){
            sum=0;
            for(int j=i;j<=i+H-1;j++){
                sum+=A[k][j];
            }
            if(sum>max)max=sum;
        }
        
    printf("%d",max);
}

// 오목 바둑판(19x19) 같은색 바둑알 5개 연속으로 놓이면 승
//왼쪽에서 오른쪽으로 가는 방향을 선택해야한다.
int A[19+2][19+2];
int search1(int color,int i, int j,int cnt)
{
    for(;color==A[i][j];j++)
        cnt++;
    return cnt==5 ? 1:0;
}
int search2(int color,int i, int j,int cnt)
{
    for(;color==A[i+1][j+1];i++,j++)
        cnt++;
    return cnt==5 ? 1:0;
}
int search3(int color,int i, int j,int cnt)
{
    for(;color==A[i+1][j];i++)
        cnt++;
    return cnt==5 ? 1:0;
}
int search4(int color,int i, int j,int cnt)
{
    for(;color==A[i-1][j+1];i--,j++)
        cnt++;
    return cnt==5 ? 1:0;
}
void q6()
{
    
    
    // 검 1, 흰 2 ,알 X 0
    for(int i=1; i<=19;i++)
        for(int j=1;j<=19;j++)
            scanf("%d",&A[i][j]);
    
    // 대각선,가로, 세로 바둑돌이 5개연속으로 놓이면승 6개이면 안된다.동시 승은 없음.
    for(int i=0;i<19;i++)
        for(int j=0;j<19;j++)
            if(A[i][j]!=0){
                if(A[i][j-1]!=A[i][j] && search1(A[i][j],i,j,1)==1)
                {
                    printf("%d\n%d %d",A[i][j],i,j);
                }
                if(A[i-1][j-1]!=A[i][j] && search2(A[i][j],i,j,1)==1)
                {
                    printf("%d\n%d %d",A[i][j],i,j);
                }
                if(A[i][j]!=A[i][j] && search3(A[i][j],i,j,1)==1)
                {
                    printf("%d\n%d %d",A[i][j],i,j);
                }
                if(A[i+1][j-1]!=A[i][j] && search4(A[i][j],i,j,1)==1)
                {
                    printf("%d\n%d %d",A[i][j],i,j);
                }
            }
    printf("0");
}

// 연구활동 가는 길(S)
// 경유지역 n(10이하)개 한지역에서 다른지역가는방법 m(30이하)개 1->n으로가는 최소비용(200이하)을 구해라
// 그래프상 최단 경로 구하는 유명한 문제
//O(n)
int n,m,sol=0x7fffffff;
int G[11][11],chk[11];
void solve(int V, int W)
{
    if(V==n)
    {
        if(W>sol) sol=W;
        return;
    }
    for(int i=1;i<=n;i++)
        if(!chk[i]&&G[V][i])
        {
            chk[i]=1;
            solve(i,W+G[V][i]);
            chk[i]=0;
        }
}
void q7()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int s,e,w;
        scanf("%d %d %d",&s,&e,&w);
        G[s][e]=G[e][s]=w;
    }
    solve(1,0);
    printf("%d\n",sol==0x7fffffff ? -1:sol);
}

int main() {
    
    q7();
    //printf("%d",q1());
    return 0;
}
