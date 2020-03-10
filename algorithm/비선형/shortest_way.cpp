//
//  main.cpp
//  shortest_way
//
//  Created by dahye Jeong on 2017. 6. 1..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <queue>


struct VERTEX{ int a,b; };
int h, w, Sa, Sb, Ga, Gb, visited[101][101];
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
char M[101][101];

bool safe(int a, int b){
    return (0<=a && a<h)&&(0<=b&&b<w);
}

void input(void)
{
    scanf("%d %d",&h,&w);
    for(int i=0;i<h;i++)
    {
        scanf("%s",M[i]);
        for(int j=0;j<w;j++)
            if(M[i][j]=='S')Sa=i,Sb=j;
            else if(M[i][j]=='G')Ga=i,Gb=j,M[i][j]='.';
    }
}

int solve(void)
{
    std::queue<VERTEX> Q;
    Q.push((VERTEX){Sa,Sb}), visited[Sa][Sb]=0;
    while(!Q.empty())
    {
        VERTEX cur = Q.front();Q.pop();
        if(cur.a==Ga&&cur.b==Gb) break;
        for(int i=0;i<4;i++)
        {
            int a=cur.a+dx[i],b=cur.b+dy[i];
            if(safe(a,b) && !visited[a][b] && M[a][b]=='.')
            {
                visited[a][b]=visited[cur.a][cur.b]+1;
                Q.push((VERTEX){a,b});
            }
        }
    }
    return visited[Ga][Gb];
}
int main() {
    input();
    printf("%d\n",solve());
    return 0;
}
