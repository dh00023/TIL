#include <cstdio>

//2. 유클리드 알고리즘 재귀
int gcd(int a, int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}
//3. 유클리드 알고리즘 비재귀
int gcd2(int a,int b){
    while(b!=0){
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}
int main(){
    int a,b,g;
    scanf("%d %d",&a,&b);
    g=1;
    //1. 모든 정수
    for(int i=2;i<=min(a,b);i++){
        if(a%i==0 && b%i==0){
            g=i;
        }
    }
}
