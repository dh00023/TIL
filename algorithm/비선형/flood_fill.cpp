//
//  main.cpp
//  nonlinear_structure
//
//  Created by dahye Jeong on 2017. 5. 31..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue> //너비우선

struct VERTEX{ int a, b;}; //너비우선
int n, A[101][101],cnt,Size[101];
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};

//flood_fill 알고리즘(지뢰찾기, 뿌요뿌요 등 게임에 많이 활용)

//장소가 지도의 경계를 넘었는지 판단하는함수
bool safe(int a, int b)
{
    return (0<=a && a<n)&&(0<=b&&b<n);
}
//내림차순 비교하기위한 비교함수
bool cmp(int a, int b){
    return a>b;
}
void dfs(int a, int b, int c)
{
    A[a][b] = c;
    if(safe(a+1,b)&&A[a+1][b]==1)
        dfs(a+1,b,c);
    if(safe(a-1,b)&&A[a-1][b]==1)
        dfs(a-1,b,c);
    if(safe(a,b+1)&&A[a][b+1]==1)
        dfs(a,b+1,c);
    if(safe(a,b-1)&&A[a][b-1]==1)
        dfs(a,b-1,c);
}

void bfs(int a, int b, int c)
{
    std::queue<VERTEX> Q;
    Q.push( (VERTEX){a,b}),A[a][b]=c;
    while(!Q.empty())
    {
        VERTEX curr = Q.front(); Q.pop();
        for(int i=0;i<4;i++)
            if(safe(curr.a+dx[i],curr.b+dy[i])&& A[curr.a+dx[i]][curr.b+dy[i]]==1)
            {
                A[curr.a+dx[i]][curr.b+dy[i]]=c;
                Q.push((VERTEX){curr.a+dx[i],curr.b+dy[i]});
            }
    }
}

void solve()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(A[i][j]==1)
            {
                cnt++;
                dfs(i,j,cnt+1);
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(A[i][j])
                Size[A[i][j]-2]++;
    std::sort(Size,Size+cnt,cmp);
}
void input()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&A[i][j]);
}
void output()
{
    printf("%d\n",cnt);
    for(int i=0;i<cnt;i++)
        printf("%d\n",Size[i]);
}
int main() {
    //따로 분리해야 디버깅하기 편리하다.
    input();
    solve();
    output();
    return 0;
}
