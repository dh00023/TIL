//
//  main.cpp
//  n-queen
//
//  Created by dahye Jeong on 2017. 6. 1..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
#include <stdio.h>

int n, ans, col[10],inc[20],dec[20];

void solve(int r)
{
    if(r>n)
    {
        ans++;
        return;
    }
    for(int i=1;i<=n;i++)
        if(!col[i] && !inc[r+i] && !dec[n+(r-i)+1])
        {
            col[i]=inc[r+i]=dec[n+(r-i)+1]=1;
            solve(r+1);
            //백트랙 후 흔적 제거 매우중요하다.
            col[i]=inc[r+i]=dec[n+(r-i)+1]=0;
        }
}
int main() {
    scanf("%d",&n);
    solve(1);
    printf("%d",ans);
}
