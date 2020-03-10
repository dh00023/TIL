/*
 정수를 저장하는 큐를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.
 
 명령은 총 여섯 가지이다.
 
 push X: 정수 X를 큐에 넣는 연산이다.
 pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 size: 큐에 들어있는 정수의 개수를 출력한다.
 empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
 front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 */
#include <iostream>
#include <string>
using namespace std;
int q[100001];

void queue1(){
    int n;
    scanf("%d",&n);
    int front=0,back = 0;
    while(n--){
        string s;
        cin >> s;
        if(s == "push"){
            int m;
            scanf("%d",&m);
            q[back]=m;
            back+=1;
        }else if(s == "pop"){
            if(front==back){
                printf("%d\n",-1);
            }else{
                printf("%d\n",q[front]);
                q[front]=0;
                front+=1;
            }
        }else if(s=="size"){
            printf("%d\n",back - front);
        }else if(s=="empty"){
            if(front==back){
                printf("%d\n",1);
            }else printf("%d\n",0);
        }else if (s == "front"){
            if(front==back){
                printf("%d\n",-1);
            }else{
                printf("%d\n",q[front]);
            }
        }else if (s == "back"){
            if(front==back){
                printf("%d\n",-1);
            }else{
                printf("%d\n",q[back-1]);
            }
        }
    }
}