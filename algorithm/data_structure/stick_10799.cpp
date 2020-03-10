#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(){
    int cnt=0;
    
    stack<int> s;
    
    string ps;
    cin >> ps;
    
    for(int i=0;i<=ps.size();i++){
        if(ps[i]=='('){
            s.push(i);
        }else if(ps[i]==')'){
            if(i==s.top()+1){
                s.pop();
                cnt+=s.size();
            }else{
                s.pop();
                cnt+=1;
            }
        }
    }
    cout << cnt << "\n";   
}