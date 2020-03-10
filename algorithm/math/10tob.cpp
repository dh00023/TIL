/*
 10진법 수 N이 주어진다. 이 수를 B진법으로 바꿔 출력하는 프로그램을 작성하시오.
 
 10진법을 넘어가는 진법은 숫자로 표시할 수 없는 자리가 있다. 이런 경우에는 다음과 같이 알파벳 대문자를 사용한다.
 
 A: 10, B: 11, ..., F: 16, ..., Y: 34, Z: 35
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int n,b;
    scanf("%d %d",&n, &b);
    string ans="";
    while(n>0){
        int r=n%b;
        if(r<10){
            ans+=(char)(r+'0');
        }else{
            ans+=(char)(r-10+'A');
        }
        n/=b;
    }
    reverse(ans.begin(),ans.end());
    cout << ans;
}