//
//  select.cpp
//  sort
//
//  Created by dahye Jeong on 2017. 5. 30..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include "select.hpp"

int n,S[1000000];

void swap(int a, int b){
    int t = S[a];
    S[a]=S[b];
    S[b]=t;
}
//  선택정렬
void selection_sort(void){
    for(int i=0;i<n-2;i++)
        for(int j=i+1;j<n;j++)
            if(S[i]>S[j])
                swap(i,j);
}

//quick sort
void quick_sort(int s, int e){
    if(s<e)
    {
        int p = s, l =s+1, r=e;
        while(l<=r)
        {
            while(l<=e&&S[l]<=S[p])l++;
            while(r>=s+1 && S[r]>=S[p])r--;
            if (l<r) swap(l, r);
        }
        swap(p,r);
        quick_sort(s, r-1);
        quick_sort(r+1, e);
    }
}
