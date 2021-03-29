//알파벳 소문자로만 이루어진 단어 S가 주어진다. 각각의 알파벳에 대해서, 단어에 포함되어 있는 경우에는 처음 등장하는 위치를, 포함되어 있지 않은 경우에는 -1을 출력하는 프로그램을 작성하시오.
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void alp_loc(){
    string s;
    cin >> s;
    int n = s.size();
    int cnt[26];
    fill_n(cnt, 26, -1);
    for(int i=0;i<n;i++){
        if(cnt[s[i]-97]==-1) cnt[s[i]-97]=i;
    }
    for(int i=0;i<26;i++){
        printf("%d ",cnt[i]);
    }
}

void alpha_loc() {
    string s;
    cin >> s;
    
    for (int i='a'; i<='z'; i++) {
        auto it = find(s.begin(), s.end(), i);
        if (it == s.end()) {
            cout << -1 << ' ';
        } else {
            cout << (it - s.begin()) << ' ';
        }
    }
    cout << '\n';
}