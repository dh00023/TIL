# Queue / Deque

## 큐(Queue)

한쪽 끝에서만 자료를 넣고 다른 한쪽 끝에서만 뺄 수 있는 자료구조이다.

- **FIFO**(First In First Out)먼저 넣은 것이 가장 먼저 나온다.
  - 시뮬레이션의 대기열(공항에서 비행기, 은행에서의 대기열)
  - 통신에서의 데이터 패킷들의 모델링
  - 프린터와 컴퓨터 사이의 버퍼링



![](https://mblogthumb-phinf.pstatic.net/20150101_31/javaking75_1420090455748JsXB6_JPEG/%C6%F7%B8%CB%BA%AF%C8%AF_%C5%A5%B1%B8%C1%B6_coolten.jpg?type=w2)

|연산|설명|
|------|------|
|push / enQueue|큐에 자료를 넣는 연산|
|pop / deQueue|큐에서 자료를 빼는 연산|
|front|큐의 가장 앞에 있는 자료를 보는 연산|
|back / rear|큐의 가장 뒤에 있는 자료를 보는 연산|
|empty|큐가 비어있는지 아닌지를 알아보는 연산|
|size|큐에 저장되어있는 자료의 개수를 알아보는 연산|

### 배열

#### 선형 큐

- 1차원 배열로 구현이 쉽지만, 삽입 시 자료의 이동이 많다.
- 상태 인식의 오류가 발생하고 비효율적이다. 거의 사용하지 않는다.

| 종류    | 삽입 위치     | 삭제 위치       |
| ------- | ------------- | --------------- |
| 순차 큐 | rear = rear+1 | front = front+1 |

![](http://cfile28.uf.tistory.com/image/264CB741591C27DF02B25C)



- 초기상태 : front = rear = -1
- 공백상태 : front = rear
- 포화상태 : rear = n-1

순차 큐는 나중에 공간이 비어있는데 사용하지 못하는 경우가 발생한다.

```c
#include <iostream>
#include <string>
using namespace std;
struct Queue {
    int data[10000];
    int begin, end;
    Queue() {
        begin = 0;
        end = 0;
    }
    void push(int num) {
        data[end] = num;
        end += 1;
    }
    bool empty() {
        if (begin == end) {
            return true;
        } else {
            return false;
        }
    }
    int size() {
        return end - begin;
    }
    int front() {
        return data[begin];
    }
    int back() {
        return data[end-1];
    }
    int pop() {
        if (empty()) {
            return -1;
        }
        begin += 1;
        return data[begin-1];
    }
};
int main() {
    int n;
    cin >> n;

    Queue q;

    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd == "push") {
            int num;
            cin >> num;
            q.push(num);
        } else if (cmd == "pop") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.front() << '\n';
                q.pop();
            }
        } else if (cmd == "size") {
            cout << q.size() << '\n';
        } else if (cmd == "empty") {
            cout << q.empty() << '\n';
        } else if (cmd == "front") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.front() << '\n';
            }
        } else if (cmd == "back") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.back() << '\n';
            }
        }
    }

    return 0;
}
```



#### 원형 큐

- 논리적으로 머리와 꼬리가 연결되어있다고 가정한다.

| 종류   | 삽입 위치            | 삭제 위치               |
| ------ | -------------------- | ----------------------- |
| 원형큐 | rear = (rear+1)mod n | front = (front+1) mod n |

![](http://cfile27.uf.tistory.com/image/2102763B5602C2D42B5384)

- 초기 공백 상태 : front = rear = 0
- 포화상태 : 나머지 연산자를 이용해서 구한다.
  - (rear+1)%n = front

```cpp
void push(int num) {
    data[end] = num;
    end = (end+1)%MAX_QUEUE;
}

bool full() {
	if (begin == (end+1)%MAX_QUEUE) {
		return true;
	} else {
		return false;
	}
}

int pop() {
	if (empty()) {
		return -1;
	}
	begin = (begin+1)%MAX_QUEUE;
	return data[begin-1];
}
```

### 연결리스트

![](http://cfile1.uf.tistory.com/image/264D3C4953490B601EE36D)

[[04. List](https://dh00023.github.io/algorithm/ds/2018/04/22/algorithm-4/)]의 단순연결리스트를 참고하여 구현하면된다.

```c
//  queue.h

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct node{
    int data;
    struct que * next;
}QNode;

typedef struct que{
    QNode * front, * rear;
}Queue;

void enQueue(Queue * q,int data);
void deQueue(Queue * q,int data);
int front(Queue *queue);
int rear(Queue *queue);
int is_empty(Queue *queue);
Queue * creat_queue();
QNode * new_node(int data);
#endif /* queue_h */
```
```c
//  queue.c


#include "queue.h"
QNode * new_node(int data){
    QNode * new = (QNode *)malloc(sizeof(QNode));
    new->data = data;
    new->next=NULL;
    return new;
}

Queue * creat_queue(){
    Queue * new = (Queue *)malloc(sizeof(Queue));
    new->front=new->rear=NULL;
    return new;
}

int is_empty(Queue *q){
    return (q->front==NULL && q->rear==NULL);
}

int front(Queue *q){
    if(is_empty(q)) return -1;
    else return q->front->data;
}

int rear(Queue *q){
    if(is_empty(q)) return -1;
    else return q->rear->data;
}



//front 포인터는 삭제,  rear 포인터는 삽입할 때 사용
void enQueue(Queue * q,int data){
    QNode * tmp = new_node(data);
    
    if(q->rear==NULL){
        q->front = q->rear = tmp;
        return;
    }
    q->rear->next= tmp;
    q->rear=tmp;
}

void deQueue(Queue * q,int data){
    if(q->front==NULL){
        return;
    }
    q->front = q->front->next;
    if(q->front==NULL) q->rear=NULL;
}

```


### `<queue>` 라이브러리

```cpp
#include <iostream>
#include <string>
#include <queue>
using namespace std;
int main() {
    int n;
    cin >> n;

    queue<int> q;

    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd == "push") {
            int num;
            cin >> num;
            q.push(num);
        } else if (cmd == "pop") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.front() << '\n';
                q.pop();
            }
        } else if (cmd == "size") {
            cout << q.size() << '\n';
        } else if (cmd == "empty") {
            cout << q.empty() << '\n';
        } else if (cmd == "front") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.front() << '\n';
            }
        } else if (cmd == "back") {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.back() << '\n';
            }
        }
    }

    return 0;
}
```


## 실습

### 조세퍼스 문제

- 1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있는다.
- 양의 정수 M(<=N)이 주어진다.
- 순서대로 M번째 사람을 제거한다.
- 이과정을 N명의 사람이 모두 제거될 때까지 계속한다.

```cpp
#include <iostream>
#include <string>
#include <queue>
using namespace std;


int main(){
    int n,m,cnt=0;
    scanf("%d %d",&n,&m);

    queue<int> q;
    for(int i=0;i<n;i++){
        q.push(i+1);
    }

    while(!q.empty()){
        for(int i =0;i<m-1;i++){
            q.push(q.front());
            q.pop();
        }
        cout << q.front();
        q.pop();
    }
}
```



<h2 id="deque">덱(Deque)</h2>

양 끝에서만 자료를 넣고 양 끝에서 뺄 수 있는 자료구조이다. Double-ended queue의 약자이다.
![](http://cfile5.uf.tistory.com/image/273851475639BB6510A002)

|연산|설명|
|------|------|
|push_front|덱의 앞에 자료를 넣는 연산|
|push_back|덱의 뒤에 자료를 넣는 연산|
|pop_front|덱의 앞에서 자료를 빼는 연산|
|pop_back|덱의 뒤에서 자료를 빼는 연산|
|front|큐의 가장 앞에 있는 자료를 보는 연산|
|back|큐의 가장 뒤에 있는 자료를 보는 연산|
|empty|큐가 비어있는지 아닌지를 알아보는 연산|
|size|큐에 저장되어있는 자료의 개수를 알아보는 연산|

### 이중 연결 리스트

양쪽에서 삽입, 삭제가 가능하여야 하므로 일반적으로 이중 연결 리스트를 사용한다.

[[04. List](https://dh00023.github.io/algorithm/ds/2018/04/22/algorithm-4/)]의 이중연결리스트를 참고하여 구현하면된다.

### `<deque>` 라이브러리

```cpp
#include <iostream>
#include <string>
#include <deque>
using namespace std;


int main(){
    int n;
    cin >> n;
    deque<int> dq;
    
    while(n--){
        string m;
        cin >> m;
        if(m=="push_front"){
            int x;
            scanf("%d",&x);
            dq.push_front(x);
        }else if(m=="push_back"){
            int x;
            scanf("%d",&x);
            dq.push_back(x);
        }else if(m=="pop_front"){
            if(!dq.empty()){
                cout << dq.front()<<"\n";
                dq.pop_front();
            }else{
                cout << -1<<"\n";
            }
        }else if(m=="pop_back"){
            if(!dq.empty()){
                cout << dq.back()<<"\n";
                dq.pop_back();
            }else{
                cout << -1<<"\n";
            }
        }else if(m=="size"){
            cout << dq.size()<<"\n";
        }else if (m=="empty"){
            cout << dq.empty()<<"\n";
        }else if(m=="front"){
            if(dq.empty()){
                cout << -1<<"\n";
            }else{
                cout << dq.front()<<"\n";
            }
        }else if(m=="back"){
            if(dq.empty()){
                cout << -1<<"\n";
            }else{
                cout << dq.back()<<"\n";
            }
        }
    }
}
```

