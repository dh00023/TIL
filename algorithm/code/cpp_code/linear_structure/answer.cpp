//
//  answer.cpp
//  linear_structure
//
//  Created by dahye Jeong on 2017. 5. 30..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include "answer.hpp"

// 9개의 서로 다른 자연수가 주어질 때, 이들 중 최댓값을 찾고 그 값이 몇 번째 수인지 구하여라.
void test1(void){
    int S[9]={3,29,38,12,57,74,40,85,61};

    int ans,n;
    ans = 0;
    n=0;

    for (int i=0;i<9;i++){
        if(ans<S[i]){
            ans = S[i];
            n = i;
        }
    }
    printf("최대값: %d이고, 이값은 %d번째 수이다.",ans,n+1);
}

//3,6,9게임
void test2(void){
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        if(i%3 == 0) printf("X ");
        else printf("%d ",i);
    }
}

void test3(void){
    // 이분탐색의 예제 프로그램을 활용할 수 있는 문제
    // 2<=n<=1000000
    
    int n,f,ans;
    ans = 0;
    printf("입력수 : ");
    scanf("%d",&n);
    int S[n+1];
    for(int i = 0; i<n;i++){
        printf("%d번째: ",i+1);
        scanf("%d",&S[i]);
    }
    printf("찾고자 하는 수 : ");
    scanf("%d",&f);
    
    for(int i = 0; i<n;i++){
        if(S[i]==f)ans=i+1;
        else ans = -1;
    }
    printf("찾고자 하는 수 위치: %d",ans);
}
