/*
접미사 배열은 문자열 S의 모든 접미사를 사전순으로 정렬해 놓은 배열이다.

baekjoon의 접미사는 baekjoon, aekjoon, ekjoon, kjoon, joon, oon, on, n 으로 총 8가지가 있고, 이를 사전순으로 정렬하면, aekjoon, baekjoon, ekjoon, joon, kjoon, n, on, oon이 된다.

문자열 S가 주어졌을 때, 모든 접미사를 사전순으로 정렬한 다음 출력하는 프로그램을 작성하시오.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void answer() {
    string s;
    cin>>s;
    int n = s.size();
    vector<int> a;
    for (int i=0; i<n; i++) a.push_back(i);
    sort(a.begin(),a.end(), [&s](int u, int v) {
        return strcmp(s.c_str()+u,s.c_str()+v) < 0;
    });
    for (auto &x : a) {
        cout << s.substr(x) << '\n';
    }
}

int main() {
    string s,str;
    cin >> s;
    
    vector<string> v;
    
    
    for(int i=0;i<s.size();i++){
        v.push_back(str.assign(s,i,s.size()));
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        cout << v[i]<<"\n";
    }
}
