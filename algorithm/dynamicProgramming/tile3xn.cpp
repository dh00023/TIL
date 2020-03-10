//
//  main.cpp
//  dynamicProgramming
//
//  Created by dahye Jeong on 2017. 6. 23..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include <iostream>
/*
3×N 크기의 벽을 2×1, 1×2 크기의 타일로 채우는 경우의 수를 구해보자.
 첫째 줄에 N(1 ≤ N ≤ 30)이 주어진다
 */
int d[31];
int main() {
    int n;
    scanf("%d",&n);
    d[0]=1;
    for(int i=2;i<=n;i+=2){
        d[i]=3*d[i-2];
        for(int j=4;j<=i;j+=2){
            d[i]+=2*d[i-j];
        }
    }
    printf("%d\n",d[n]);
    return 0;
}