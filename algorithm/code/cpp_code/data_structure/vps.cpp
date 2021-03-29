#include <iostream>
#include <stack>
#include <string>
using namespace std;

string valid(string s){
    int cnt=0;
    for(int i=0;i<=s.size();i++){
        if(s[i]=='('){
            cnt += 1;
        }else if(s[i]==')'){
            cnt -= 1;
        }
        if (cnt < 0) {
            return "NO";
        }
    }
    if (cnt == 0) {
        return "YES";
    }else{
        return "NO";
    }
}
int main(){
    int t;
    cin >> t;
    
    while(t--){
        string ps;
        cin >> ps;
        
        cout<<valid(ps)<<"\n";       
    }
}