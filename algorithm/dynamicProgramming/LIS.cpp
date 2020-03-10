#include <stdio.h>
/*
 수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.
 
 예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.
 첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000)이 주어진다.
 
 둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. (1 ≤ Ai ≤ 1,000)
 */
int d[1001];
int main() {
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    for(int i=0;i<n;i++){
        d[i]=1;
        for(int j=0;j<i;j++){
            if(a[j]<a[i]&&d[i]<d[j]+1){
                d[i]=d[j]+1;
            }
        }
    }
    int ans =0 ;
    for(int i=1;i<=n;i++){
        if(ans<d[i])ans=d[i];
    }
    
    printf("%d",ans);
    return 0;
}
