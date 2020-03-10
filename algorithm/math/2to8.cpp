/*
2진수가 주어졌을 때, 8진수로 변환하는 프로그램을 작성하시오.
첫째 줄에 2진수가 주어진다. 주어지는 수의 길이는 1,000,000을 넘지 않는다.
첫째 줄에 주어진 수를 8진수로 변환하여 출력한다.
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    string bin;
    cin >> bin;
    int n=bin.size();
    string answer="";
    for(int i=n-1;i>=0;i-=3){
        int ans=0;
        for(int j=2;j>=0;j--){
            if(i-j<0)j--;
            ans=ans*2+bin[i-j]-'0';
        }
        answer+=(char)(ans+'0');
    }
    reverse(answer.begin(),answer.end());
    cout << answer;
}

#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int n = s.size();
    if (n%3 == 1) {
        cout << s[0];
    } else if (n%3 == 2) {
        cout << (s[0]-'0')*2 + (s[1]-'0');
    }
    for (int i=n%3; i<n; i+=3) {
        cout << (s[i]-'0')*4 + (s[i+1]-'0')*2 + (s[i+2]-'0');
    }
    cout << '\n';
    return 0;
}
