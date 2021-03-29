#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b==0)return a;
    else{
        return gcd(b,a%b);
    }
}
int main(){
    int a,b,g,l,t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&a,&b); //이 둘은 10,000이하의 자연수이며 사이에 한 칸의 공백이 주어진다.

        g=gcd(a,b);
        l=(a*b)/g;
        printf("%d\n",l);
    }
}
