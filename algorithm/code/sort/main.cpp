//
//  main.c
//  first
//
//  Created by dahye Jeong on 2017. 5. 30..
//  Copyright © 2017년 dahye Jeong. All rights reserved.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 퀵정렬 기반으로 동작하는 std::sort()사용하기 위해 추가
#include <algorithm>
#include "select.hpp"

int n,S[1000000];

void print_array(){
    for(int i=0; i<n;i++)
        printf("%d",S[i]);
    printf("\n");
}

int main() {
    srand(time(NULL));
    scanf("%d",&n);
    for(int i = 0 ;i<n;i++){
        S[i] = rand();
    }
    
    int start = clock();
    
    //selection_sort(); 선택정렬
    // 퀵정렬 기반으로 동작하는 std::sort()사용
    //std::sort(S,S+n);
    
    quick_sort(0, n-1);
    
    printf("reslut = %.3lf(sec)\n",(double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
