//
//  solution.cpp
//  linear_structure
//
//  Created by dahye Jeong on 2017. 5. 30..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include "solution.hpp"


void solution1()
{
    int i, ans, index, A[MAXN+1];
    ans = 0;
    index =0;
    for(i =1;i<MAXN+1;i++){
        scanf("%d",&A[i]);
    }
    for(i=1;i<MAXN+1;i++)
        if(ans<A[i]){
            ans = A[i];
            index = i;
        }
    printf("%d \n %d \n",ans,index);
}
/* 
 이분탐색을 사용한다.
 탐색 범위[s,e] 가운데 값 m
 A[m]==k인 경우와 A[m]<k,A[m]>k 경우로 나누어 처리
 */
int k,A[1000001];

int solve(int s, int e){
    int m;
    while(e-s>=0)
    {
        m=(s+e)/2;
        if(A[m]==k) return m+1;
        if(A[m]<k) s=m+1;
        else e=m-1;
    }
    return -1;
}

int selfsolve(int s, int e){
    
    if(s>e) return -1;
    int m=(s+e)/2;
    if(A[m]==k)return m+1;
    if(A[m]<k) return(s+1,e);
    else return(s,e-1);
}

int solution3()
{
    int n;
    
    scanf("%d",&n);
    for(int i = 0; i<n;i++){
        scanf("%d",A+i);
    }
    scanf("%d",&k);
    
    printf("%d \n",solve(0,n-1));
    return 0;
}


int solve4(int s, int e){
    //A[m-1]<k A[m]>=k
    int m;
    while(e-s>0)
    {
        m=(s+e)/2;
        if(A[m]<k)s=m+1;
        else m=e;
    }
    return e+1;
}

int solution4() {
    int n;
    // n개로 이루어진 정수 집합에서 원하는 수 k 이상인 수가 처음으로 등장하는 위치
    // 오름차순으로 정렬, 같은 수가 여러개 존재할 수 있다.
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d ",A+i);
    scanf("%d",&k);
    
    printf("%d\n",solve(0,n));
    return 0;
    /*실제로는 std::lower_bound(S,S+n,k,[compare))함수를 활용하게된다.*/
}
