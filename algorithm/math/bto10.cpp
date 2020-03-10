/*
 B진법 수 N이 주어진다. 이 수를 10진법으로 바꿔 출력하는 프로그램을 작성하시오.
 
 10진법을 넘어가는 진법은 숫자로 표시할 수 없는 자리가 있다. 이런 경우에는 다음과 같이 알파벳 대문자를 사용한다.
 
 A: 10, B: 11, ..., F: 16, ..., Y: 34, Z: 35
 */
#include <iostream>
#include <string>
using namespace std;


int main(){
    int ans=0;
    int b;
    string s;
    cin >> s >> b;
    for(int i=0;i<s.size();i++){
        if('0'<=s[i]&&s[i]<='9'){
            ans=ans*b+s[i]-'0';
        }else{
            ans=ans*b+s[i]-'A'+10;
        }
    }
    printf("%d\n",ans);
}
