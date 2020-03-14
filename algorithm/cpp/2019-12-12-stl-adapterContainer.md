# STL Container - Container Adapter

간결함과 명료성을 위해 인터페이스를 제한한 시퀀스나 연관 컨테이너의 변형이다.
반복자를 지원하지 않으므로 STL 알고리즘에서는 사용할 수 없다.

## stack

스택은 vector 클래스의 인터페이스를 제한하여, 전형적인 스택 메모리 구조의 인터페이스를 제공한다.

```cpp
#include <stack>
```

### 구조


| 멤버 함수 |  설명 |
|:-----------:|:-----------:|
| empty() | 스택이 비어 있으면 true를, 비어 있지 않으면 false를 반환함. |
| size() | 스택 요소의 총 개수를 반환함. |
| top() | 스택의 제일 상단에 있는(제일 마지막으로 저장된) 요소에 대한 참조를 반환함. |
| push() | 스택의 제일 상단에 요소를 삽입함. |
| pop() | 스택의 제일 상단에 있는 요소를 삭제함. |

### 예제

```cpp
#include <iostream>
#include <stack>

using namespace std;

int main(void){

    stack<int> st;
    int decimal = 123;

    do {
        st.push(decimal % 2);
        decimal /= 2;
    }while(decimal);

    while(!st.empty()){
        cout << st.top();
        st.pop();
    }
    return 0;
}
```

## queue

queue는 deque 클래스의 인터페이스를 제한하여, 전형적인 큐 메모리 구조의 인터페이스를 제공한다.

```cpp
#include <queue>
```

### 구조

| 멤버 함수 |  설명 |
|:-----------:|:-----------:|
| empty() | 큐가 비어 있으면 true를, 비어 있지 않으면 false를 반환함. |
| size() | 큐 요소의 총 개수를 반환함. |
| front() | 큐의 맨 앞에 있는(제일 먼저 저장된) 요소에 대한 참조를 반환 |
| back() | 큐의 맨 뒤에 있는(제일 나중에 저장된) 요소에 대한 참조를 반환 |
| push() | 큐의 맨 뒤에 요소를 삽입 |
| pop() | 큐의 맨 앞의 요소를 삭제 |

### 예제

```cpp
#include <iostream>
#include <queue>

using namespace std;

int main(void){

    int n;

    cin >> n;

    queue<int> que;
    que.push(0);
    que.push(1);

    for(int i=2; i<n; i++){
        int tmp = que.front();
        cout << tmp << ' ';
        que.pop();
        que.push(tmp + que.front());
    }

    return 0;
}
```

## priority queue

우선순위 큐는 큐와 달리 맨 앞의 요소로 가장 먼저 저장된 요소가 아닌, 가장 큰 값을 지닌 요소가 위치하게된다.
우선순위 큐는 **vector** 클래스를 기반으로 한다.

하지만 사용할 수 있는 멤버함수는 큐 컨테이너와 같다.

```cpp
#include <queue>
```
### 예제

```cpp
#include <iostream>
#include <queue>

using namespace std;

int main(void){

    priority_queue<int> pq;

    pq.push(10);
    pq.push(30);
    pq.push(100);
    pq.push(20);

    while(!pq.empty()){
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << endl;
    return 0;
}
```

## 참조

- [TCPSCHOOL.com](http://tcpschool.com/)