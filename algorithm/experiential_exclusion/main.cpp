//
//  main.cpp
//  experiential_exclusion
//
//  Created by dahye Jeong on 2017. 6. 3..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <stdio.h>

// 현재 탐색한 거리 > 지금까지 구한 최소 경로의 거리 의 조건을 만족한 경우 더 이상 탐색하지 않아도 된다.
int n,m,G[1001][1001],sol,chk[1001],greedy_chk[1001];//단순 탐욕법
int counter; // 성능 검증을 위해 해를 구하기까지 몇 개의 상태를 탐색하는 지 카운팅

void greedy_ans(int V)
{
    int W=0,t;
    greedy_chk[V]=1;
    while(V!=n)
    {
        int min = 0x7fffffff;
        for(int i=0;i<=n;i++)
            if(!greedy_chk[i]&&G[V][i]&&G[V][i]<min)
            {
                greedy_chk[i]=1;
                min=G[V][i];
                t=i;
            }
        sol+=G[V][t];
        V=t;
    }
}
void solve(int V, int W)
{
    if(W>sol) return; //커팅
    counter++;
    if(V==n)
    {
        if(W<sol)sol=W;
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
void q1()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int s,e,w;
        scanf("%d %d %d",&s,&e,&w);
        G[s][e]=G[e][s]=w;
    }
    greedy_ans(1);
    solve(1,0);
    printf("%d\n",sol);
    printf("탐색한 정점수 %d",counter);
}

// minimum sum
// 현재까지의 합 > 지금까지 최소 합이면 배제할 수있다.
int m2[11][11];
int col_check[11],greedy_chk2[11];
int n2,min_sol,counter2;

void input(void)
{
    scanf("%d",&n2);
    for(int i=0;i<n2;i++)
        for(int j=0;j<n2;j++)
            scanf("%d",&m2[i][j]);
    
}
/* 단순 탐욕법
 1. 1행에서 가장 작은 수를 택하고 다음 행으로 진행한다.
 2. 다음 행에서 아직까지 선택되지 않은 열 중 가장 작은 수를 택하고 다음 행으로 진행한다.
 3. 아직 마지막 행을 마치지 않았으면 2단계로 간다.
 4. 지금까지 선택한 수들의 합을 처음 해로 한다.
 */
void greedy_ans2(int row)
{
    for(int i=row;i<n;i++)
    {
        int min = 0x7fffffff,k;
        for(int j=0;j<n;j++)
            if(!greedy_chk2[j]&& min > m2[i][j])
            {
                min = m2[i][j];
                k=j;
            }
        min_sol+=min;
        greedy_chk[k]=1;
    }
}
void solve2(int row,int score)
{
    if(score>min_sol)return; //커팅
    counter++;
    if(row==n2)
    {
        if(score<min_sol)
            min_sol=score;
        return;
    }
    for(int i=0;i<n2;i++)
    {
        if(col_check[i]==0)
        {
            col_check[i]=1;
            solve2(row+1,score+m2[row][i]);
            col_check[i]=0;
        }
    }
    return;
}
void q2(){
    input();
    greedy_ans2(0);
    solve2(0, 0);
    printf("%d",min_sol);
}

// 거스름돈
// 현재까지 사용한 동전의 수 > 지금까지 구해둔 최소 동전의 수 이면 배제
int m3,n3,coin[10],ans = 987654321,counter3;

/*
 단순탐욕법
 1. 현재 금액에서 지불할 수 있는 가장 큰 동전으로 가능한 만큼 지불한다.
 2. 만약 아직 돈이 남았다면, 다시 1단계로 간다.
 3. 지금까지 지불한 동전의 개수를 처음 해로 설정한다.
 */
void greedy_ans3(int mon)
{
    ans=0;
    while(mon)
    {
        for(int i=n3-1;i>=0;i--)
        {
            ans+=mon/coin[i];
            mon%=coin[i];
        }
    }
}
// d개의 동전으로 mon원을 사용한 상태
void solve3(int mon,int d){
    if(d>ans) return; //커팅
    if(mon>m3) return;
    counter3++;
    if(mon==m3)
    {
        if(d<ans)ans = d;
        return;
    }
    for(int i=0;i<n3;i++)
        solve3(mon+coin[i],d+1);
}
void q3(){
    scanf("%d %d",&m3,&n3);
    for(int i=0;i<n3;i++)
        scanf("%d",coin+i);
    greedy_ans3(m3);
    solve3(0,0);
    printf("%d\n",ans);
    printf("%d\n",counter3);
}

/*
 경찰차
 도로 사이의 거리는 모두 1, 동서방향 도로(n)와 남북방향 도로(n)가 교차하는 교차로의 위치는 두 도로의 번호 쌍으로 나타난다.
 경찰차1(1,1) 경찰차2(n,n) 처리할 사건이 있으면 발생한 위치의 두 경찰차 중 한대에 알려주고 가장빠른길로가서 처리
 처리해야할 사건은 항상 교차로에서 발생한다.
 즉, 처리해야할 사건(교차로)들이 순서대로 주어질 대, 두 대의 경찰차가 이동하는 거리의 합을 최소화 하는 프로그램을 작성해라.
 */
// 실제로 경찰차가 위치할 수 있는 가능성 w+1번 경찰차 초기위치 + 2번경찰차 초기위치 =  w+2

// E 각사건의 위치 저장
int E[1010][2], n4,m4, ans4 = 987654321;
int counter4;

int min(int a, int b)
{
    return a>b?b:a;
}
int abs(int a)
{
    return a>0?a:-a;
}

int dis(int a,int b)
{
    return abs(E[a][0]-E[b][0])+abs(E[a][1]-E[b][1]);
}
/*
 단순 탐욕법
 1. 사건 dl발생하면 두 대의 경찰차들 중 더 가까운 경찰차가 사건을 처리
 2. 만약 아직 남은 사건이 있다면 1단계로간다.
 3. 지금까지 이동한 거리의 합을 처음해로 ㅈ설정
 */
void greedy_ans4(int a, int b)
{
    ans4=0;
    for(int i=2;i<m4+2;i++)
    {
        if(dis(i,a)>dis(i,b))
            ans4+=dis(i,b),b=i;
        else
            ans4+=dis(i,a),a=i;
    }
}
//max(a,b)번 사건까지 처리하면서 d만큼 이동한 후, 1번 경찰차는 a사건 위치에, 2번경찰차는 b사건 위치에 있는 상태
//0<=a,b<w+2, 다음사건= max(a,b)+1

// 현재까지 이동거리 > 현재까지 최소 거리인 경우는 배제할 수 있다.
void solve4(int a, int b, int d)
{
    int next=(a>b? a:b)+1;
    if(d>ans4)return; //bounding
    counter4++;
    if(next>=m4+2)
    {
        if(d<ans4)ans4=d;
        return;
    }
    solve4(next,b,d+dis(a,next));
    solve4(a,next,d+dis(b,next));
}

void q4(){
    scanf("%d%d",&n4,&m4);
    E[0][0]=E[0][1]=1; // 1번경찰차
    E[1][0]=E[1][1]=n4; // 2번경찰차
    for(int i=2;i<m4+2;i++)
        scanf("%d%d",&E[i][0],&E[i][1]);
    greedy_ans4(0,1);
    solve4(0,1,0);
    printf("%d",ans4);
    printf("탐색한 정점의 수 : %d\n",counter4);
}


int main() {
    q4();
    return 0;
}
