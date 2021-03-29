//
//  deque.cpp
//  data_structure
//
//  Created by dahye Jeong on 2017. 6. 18..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//
#include <iostream>
#include <string>
#include <deque>
using namespace std;
/*
 정수를 저장하는 덱(Deque)를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.
 
 명령은 총 여덟 가지이다.
 
 push_front X: 정수 X를 덱의 앞에 넣는다.
 push_back X: 정수 X를 덱의 뒤에 넣는다.
 pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 size: 덱에 들어있는 정수의 개수를 출력한다.
 empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
 front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
 */
void deq(){
    int n;
    scanf("%d",&n);
    
    deque<int> dq;
    
    while(n--){
        string s;
        cin >> s;
        if(s=="push_front"){
            int x;
            scanf("%d",&x);
            dq.push_front(x);
        }else if(s=="push_back"){
            int x;
            scanf("%d",&x);
            dq.push_back(x);
        }else if(s=="pop_front"){
            if(!dq.empty()){
                printf("%d\n",dq.front());
                dq.pop_front();
            }else printf("%d\n",-1);
        }else if(s=="pop_back"){
            if(!dq.empty()){
                printf("%d\n",dq.back());
                dq.pop_back();
            }else printf("%d\n",-1);
        }else if(s=="size"){
            printf("%ld\n", dq.size());
        }else if(s=="empty"){
            if(dq.empty()){
                printf("%d\n",1);
            }else{
                printf("%d\n",0);
            }
        }else if (s=="front"){
            if(dq.empty()){
                printf("%d\n",-1);
            }else printf("%d\n",dq.front());
        }else if (s=="back"){
            if(dq.empty()){
                printf("%d\n",-1);
            }else printf("%d\n",dq.back());
        }
    }
}
