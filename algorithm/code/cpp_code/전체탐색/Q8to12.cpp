//
//  main.cpp
//  Question8to12
//
//  Created by dahye Jeong on 2017. 6. 3..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;

/* 리모컨 - 냉난방기의 온도 조절
  온도 1,5,10도 내리고 올리는 버튼
  현재 설정 온도와 변경하고자 하는 목표온도가 주어지면 이버튼을 이용해 목표온도로 변경
*/
//int a,b,res=40;
struct ELE{int v, cnt;};
queue<ELE> Q;

void q8()
{
    /* 깊이우선탐색
    
    if(cnt>res)return;
    if(temp == b)
    {
        if(cnt<res)res=cnt;
        return;
    }
    if(temp<b){
        q8(temp+10,cnt+1);q8(temp+5,cnt+1);q8(temp+1,cnt+1);
    }
    else{
        q8(temp-10,cnt+1);q8(temp-5,cnt+1);q8(temp-1,cnt+1);
    }
     */
    //너비우선탐색
    int a,b;
    ELE temp;
    scanf("%d %d",&a,&b);
    Q.push({a,0});
    while(!Q.empty())
    {
        temp = Q.front(),Q.pop();
        if(temp.v == b)
            break;
        if(temp.v<b)
        {
            Q.push({temp.v+10,temp.cnt+1});
            Q.push({temp.v+5,temp.cnt+1});
            Q.push({temp.v+1,temp.cnt+1});
        }
        else
        {
            Q.push({temp.v-10,temp.cnt+1});
            Q.push({temp.v-5,temp.cnt+1});
            Q.push({temp.v-1,temp.cnt+1});
        }
    }
    printf("%d",temp.cnt);
}

//minimum sum(S)
int m[11][11];
int col_check[11];
int n,min_sol=0x7fffffff;

void input(void)
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&m[i][j]);
    
}
void solve10(int row,int score)
{
    if(row==n)
    {
        if(score<min_sol)
            min_sol=score;
        return;
    }
    for(int i=0;i<n;i++)
    {
        if(col_check[i]==0)
        {
            col_check[i]=1;
            solve10(row+1,score+m[row][i]);
            col_check[i]=0;
        }
    }
    return;
}
void q10(){
    input();
    solve10(0, 0);
    printf("%d",min_sol);
}

// 거스름돈 (s)
// 거스름돈에 사용될 동전의 수 최소화
int m16,n16,coin[10],ans = 987654321;

// d개의 동전으로 mon원을 사용한 상태
void solve16(int mon,int d){
    if(mon>m16) return;
    if(mon==m16)
    {
        if(d<ans)ans = d;
        return;
    }
    for(int i=0;i<n;i++)
        solve16(mon+coin[i],d+i);
}
//k번째 이하의 동전을 cnt개 사용하여  mon원을 거슬러 준 상태.
void solve16_(int mon,int k, int cnt){
    if(k==n || mon> m16 ) return;
    if(mon==m16)
    {
        if(ans>cnt)ans = cnt;
        return;
    }
    for(int i=0;mon+coin[k]*i<=m16;i++)
        solve16_(mon+coin[k]*i,k+i,cnt+i);
}
void q16(){
    scanf("%d %d",&m16,&n16);
    for(int i=0;i<n;i++)
        scanf("%d",coin+i);
    solve16(0,0);
    printf("%d",ans);
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
int E[1010][2], n23,m23, ans23 = 987654321;

int min(int a, int b)
{
    return a>b? b:a;
}
int abs(int a)
{
    return a>0? a:-a;
}

int dis(int a,int b)
{
    return abs(E[a][0]-E[b][0])+abs(E[a][1]-E[b][1]);
}
//max(a,b)번 사건까지 처리하면서 d만큼 이동한 후, 1번 경찰차는 a사건 위치에, 2번경찰차는 b사건 위치에 있는 상태
//0<=a,b<w+2, 다음사건= max(a,b)+1
void solve23(int a, int b, int d)
{
    int next=(a>b? a:b)+1;
    if(next>=m23+2)
    {
        if(d<ans23)ans23=d;
        return;
    }
    solve23(next,b,d+dis(a,next));
    solve23(a,next,d+dis(b,next));
}
void q23(){
    scanf("%d%d",&n23,&m23);
    E[0][0]=E[0][1]=1; // 1번경찰차
    E[1][0]=E[1][1]=n23; // 2번경찰차
    for(int i=2;i<m23+2;i++)
        scanf("%d%d",&E[i][0],&E[i][1]);
    solve23(0,1,0);
    printf("%d",ans23);
}
int main() {
    
    q23();
    
    return 0;
}
