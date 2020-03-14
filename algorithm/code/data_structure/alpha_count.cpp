//알파벳 소문자로만 이루어진 단어 S가 주어진다. 이 때, 각 알파벳이 단어에 몇 개가 포함되어 있는지 구하는 프로그램을 작성하시오.
#include <algorithm>
#include <iostream>
#include <string>

int cnt[26];
void alp(){
    string s;
    cin >> s;
    int n = s.size();
    for(int i=0;i<n;i++){
        cnt[s[i]-97]+=1;
    }
    for(int i=0;i<26;i++){
        printf("%d ",cnt[i]);
    }
}

int main() {
    string s;
    cin >> s;
    
    for (int i='a'; i<='z'; i++) {
        cout << count(s.begin(), s.end(), i) << ' ';
    }
    cout << '\n';
}