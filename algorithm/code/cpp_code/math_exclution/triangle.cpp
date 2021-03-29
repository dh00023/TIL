#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 삼각화단만들기 - a+b+c = n , a+b>c
// a와 b를 알면 c는 쉽게 구할 수 있다. => O(n^2)
// [n/3]<=c<n/2 , 1<=a<[n/3]
int main(){
    int n,a,b,c,count=0;
    scanf("%d",&n);
    
    for(c=n/3;c<=n/2;c++)
        for(a=1;a<=n/3;a++)
        {
            b=n-(a+c);
            if(a+b>c && (a<=b&&b<=c))count++;
        }
    printf("%d",count);
    return 0;
}
