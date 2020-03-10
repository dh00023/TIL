/*
 8진수가 주어졌을 때, 2진수로 변환하는 프로그램을 작성하시오.
 첫째 줄에 8진수가 주어진다. 주어지는 수의 길이는 333,334을 넘지 않는다.
 첫째 줄에 주어진 수를 2진수로 변환하여 출력한다. 수가 0인 경우를 제외하고는 반드시 1로 시작해야 한다.
*/
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int main(){
    int n;
    scanf("%d",&n);
    string ans="";
    if(n==0)printf("%d",n);
    while(n!=1){
        if(n>0){
            if(n%(-2)==0){
                ans+='0';
            }else{
                ans+='1';
            }
        }else{
            if(n%(-2)==0){
                ans+='0';
            }else{
                ans+='1';
                n-=1;
            }
        }
        n/=-2;
    }
    ans+='1';
    reverse(ans.begin(), ans.end());
    cout << ans;
}
