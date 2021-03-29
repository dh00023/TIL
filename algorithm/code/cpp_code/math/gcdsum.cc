//양의 정수 n개가 주어졌을 때, 가능한 모든 쌍의 GCD의 합을 구하는 프로그램을 작성하시오.
#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b==0)return a;
    else return gcd(b,a%b);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        int num[101]={0};
        scanf("%d",&n);
        
        for(int i=0;i<n;i++)scanf("%d",&num[i]);
        long long int sum=0;
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                sum+=gcd(num[i],num[j]);
            }
        }
        printf("%lld\n",sum);
    }
}