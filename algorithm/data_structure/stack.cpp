#include <iostream>
#include <stack>
#include <string>
using namespace std;


int main ()
{
    stack<int> mystack;
    int n;
    scanf("%d",&n);

    while(n--){
        string ss;
        cin >> ss;

        if(ss=="push"){
            int num;
            scanf("%d",&num);
            mystack.push(num);
        } else if(ss=="top"){
            cout << (mystack.empty() ? -1 : mystack.top())<<"\n";
        } else if(ss=="size"){
            cout << mystack.size()<<"\n";
        } else if(ss=="empty"){
            cout << mystack.empty()<<"\n";
        } else if(ss=="pop"){
            cout << (mystack.empty() ? -1 : mystack.top())<<"\n";
            if(!mystack.empty()){
                mystack.pop();
            }
        }
    }
}