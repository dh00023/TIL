#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(){
    queue<int> q;
    
    int n;
    scanf("%d",&n);
    
    while(n--){
        string m;
        cin >> m;
        
        if(m=="push"){
            int x;
            scanf("%d",&x);
            q.push(x);
        }else if(m=="pop"){
            if(q.empty()){
                printf("-1\n");
            }else{
                cout << q.front()<< "\n";
                q.pop();
            }
        }else if(m=="size"){
            cout << q.size() << "\n";
        }else if(m=="empty"){
            cout << q.empty() << "\n";
        }else if(m=="front"){
            if(q.empty()){
                printf("-1\n");
            }else{
                cout << q.front()<< "\n";
            }
        }else if(m=="back"){
            if(q.empty()){
                printf("-1\n");
            }else{
                cout << q.back()<< "\n";
            }
        }
    }
}