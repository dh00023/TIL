# Maze

여러가지 탐색방법을 이용해서 미로찾기를 구현해보았습니다.

## Recursion(순환)

### 구현

```c
#include <stdio.h>
#include "color.h"


#define MAX 10
#define PATH 0
#define WALL 1
#define BLOCKED 2  // 방문+경로상에 있지 않은 것
#define VISITED 3  // 방문+경로가 될 가능성이 있는것

int maze[MAX+2][MAX+2]= {
    {4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,1,1,4},
    {4,0,0,1,0,1,0,0,0,0,1,4},
    {4,0,1,0,1,0,1,1,1,0,0,4},
    {4,0,0,0,1,0,1,0,0,1,0,4},
    {4,0,1,0,1,0,0,0,1,1,0,4},
    {4,0,1,1,1,0,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,0,1,4},
    {4,0,1,1,1,0,1,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4}
};

int find_path(int x, int y){
    if(x<1 ||y<1||x>MAX||y>MAX)return 0;
    else if(maze[x][y] != PATH)return 0;
    else if(x==MAX&&y==MAX){
        maze[x][y]=VISITED;
        return 1;
    }else{
        maze[x][y] = VISITED;
        if(find_path(x-1, y)||find_path(x, y+1)||find_path(x+1, y)||find_path(x, y-1)) return 1;
        maze[x][y]=BLOCKED;
        return 0;
    }
}

int main(int argc, const char * argv[]) {
    print_maze(1, 1);
    find_path(1, 1);
    print_maze(MAX, MAX);
    return 0;
}
```

## Stack(DFS)

stack을 이용해서 미로를 푸는 코드입니다.

### 규칙

우선 입구는 (1,1)이며, 출구는 (n-2,n-2)입니다.

다음과 같은 규칙으로 길을 찾을 것입니다!

- 이미 **방문한** **위치에는** **표시**를 해서 **무한루프를** **방지**한다.

- 현재 위치에서 일정한 규칙으로 다음 위치로 이동한다.

- - **북, 동, 남, 서**의 순서로 검사합니다.
  - 그 방향으로 갈 수 있으면, 즉, **아직 안 가본 위치 && 벽이 아니면** 그 방향으로간다.

- 아무 방향으로도 갈 수 없으면 그 위치에 **오기** **직전** **위치로** **되돌아간다**.

위의 규칙을 자세히 살펴보면

1. 현재 위치는 출발점이다.

2. 다음을 반복한다.

   1. 현재 위치에 방문했다는 표시를 한다.(노란색)

   2. 현재 위치가 출구라면 종료한다.

   3. 현재 위치에서 북, 동, 남, 서 4방향에 대해 순서대로

      1. 그 방향으로 이동할 수 있는지(벽, 미로의 외부, 이미 방문한 위치)가 아닌지 검사한다.
      2. 만약 갈 수 있으면 그 방향으로 이동한다.

   4. 만약 3번에서 4방향 중 어느 쪽으로도 가지 못했다면 현재 위치에 도달하기 직전 위치로 돌아간다.



**1,2,3,4의 과정을 되풀이하여 최종적으로 출구에 도달하면 미로찾기는 성공하게 됩니다.** 

### C언어 구현

```
1. 미로는 2차원 배열로 구현된다. maze[x][y]
2. 현재 위치는 출발점(1,1)이다.
3. 다음을 반복한다.
	ㄱ. 현재 위치에 방문했다는 표시를 한다.(2)
	ㄴ. 현재 위치가 출구라면 종료한다. maze[n-2][n-2]
	ㄷ. 현재 위치에서 북, 동, 남, 서 4방향에 대해 순서대로 
		- 그 방향으로 이동할 수 있는지(벽, 미로의 외부, 이미 방문한 위치)가 아닌지 검사한다.
		- 만약 갈 수 있으면 현재 위치를 스택에 push하고 그 방향으로 이동
	ㄹ. 만약 ㄷ번에서 4방향 중 어느 쪽으로도 가지 못했다면  스택에서 pop한 위치로 돌아간다.
```



#### Position



- position.h

```c
//  position.h

#ifndef position_h
#define position_h

typedef struct pos{
    int x,y;
}Position;

Position move_to(Position pos, int dir);

#endif /* position_h */

```



- position.c

```c
//  position.c
#include "position.h"
// 북동남서방향으로 이동하는 것이다. 세로가 X, 가로가 Y
int offset[4][2] = {
    {-1,0},
    {0,1},
    {1,0},
    {0,-1}
};

Position move_to(Position pos,int dir){
    Position next;
    next.x = pos.x + offset[dir][0];
    next.y = pos.y + offset[dir][1];
    return next;
}

```



#### Stack



- stack.h

```c
//  stack.h

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"


typedef struct s{
    int dir;
    struct s * next;
}Stack;

Stack * new_node(int dir);
void init(Stack **s);
int is_empty(Stack *s);
int peak(Stack *s);
void push(Stack ** top, int dir);
void pop(Stack ** top);

#endif /* stack_h */

```



- stack.c

```c
//  stack.c

#include "stack.h"

Stack * new_node(int dir){
    Stack * new = (Stack *)malloc(sizeof(Stack));
    new->dir = dir;
    new->next=NULL;
    return new;
}
void init(Stack **s){
    *s = NULL; //스택초기화
}
int is_empty(Stack *s){
    // NULL이면 1(true)  아니면 0(false)
    return (s==NULL);
}
int peak(Stack *s){
    if(is_empty(s))return -1;
    return s->dir;
}
void push(Stack ** top,int dir){
    Stack * new = NULL;
    if(is_empty(*top)){
        new = new_node(dir);
    }else{
        new = new_node(dir);
        new->next=*top;
    }
    (*top)=new;
}
void pop(Stack ** top){
    Stack * p = *top;
    
    if(is_empty(*top))return;
    
    *top = p->next;
    free(p);
}
```



#### Color



```c
//  color.h

#ifndef color_h
#define color_h
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#endif /* color_h */

```



#### Main



```c
//  main.c

#include "stack.h"
#include "position.h"
#include "color.h"
#include <unistd.h>

#define MAX 8
#define PATH 0              // 지나갈 수 있는 길
#define WALL 1              // 지나갈 수 없는 길 == 벽 흰색!
#define VISITED 2           // 이미 방문한 위치
#define BACKTRACKED 3       // 방문했다 되돌아 나온 위치
#define EDGE 4              // 테두리
#define clear() printf("\033[H\033[J")

int maze[MAX+2][MAX+2]= {
    {4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,0,0,1,1,0,0,4},
    {4,0,1,1,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,1,1,0,1,0,0,4},
    {4,4,4,4,4,4,4,4,4,4}
};
int n=MAX; // 미로의 크기
//void make_maze();
void print_maze();
int movable(Position pos,int dir);



int main(int argc, const char * argv[]) {
    
    Stack * top;
    init(&top); 
//    make_maze();
    
    Position cur; // 항상 현재 위치를 표현
    cur.x=1;
    cur.y=1;
    
    int init_dir = 0; //한 위치에 도착했을 때 처음으로 시도해 볼 이동 방향
    
    while(1){
        maze[cur.x][cur.y] = VISITED;
        if(cur.x == n && cur.y == n){
            print_maze(cur.x,cur.y);
            printf("미로를 찾았습니다!\n");
            break;
        }
    
    // 방문했는지 기록하는 변수
        int forwarded = 0;

        // 북 동 서 남 순서대로 0, 1, 2, 3
        for(int dir = init_dir; dir<4;dir++){
            if(movable(cur,dir)){ //이동가능한지 검사
                push(&top,dir); // 스택에 현재 위치 대신 이동하는 방향을 push
                cur = move_to(cur,dir);
                forwarded = 1;
                init_dir = 0; //처음 방문하는 위치에서는 항상 0부터 시도
                break;
            }
        }
        // 4방향중 아무곳도 가지 못했다면
        if(!forwarded){
            // 왔다가 되돌아간 곳임을 표시
            maze[cur.x][cur.y]=BACKTRACKED;
            
            //원래 출구가 없는 미로
            if(is_empty(top)){
                printf("길이 없습니다.\n");
                break;
            }
            int d = peak(top);
            pop(&top);
            // 이전 위치에서 지금 위치에 올때 d방향으로 이동했다면 (d+2)%4번 방향으로 이동하면된다.
            // 되돌아가는 방향!
            cur = move_to(cur, (d+2)%4);
            // 위치에서 d+1번방향부터 시도하면된다.
            init_dir = d+1;
            print_maze(cur.x, cur.y);
            printf("길이없습니다. 되돌아갑니다.\n");
        }
        
    }
    

    return 0;
}

int movable(Position pos, int dir){
    Position tmp = move_to(pos, dir);
    //1. dir방향으로 이동한 좌표가 0~n-1이내에 있어야한다.
    print_maze(tmp.x,tmp.y);
    printf("maze[%d][%d]=%d\n",tmp.x,tmp.y,maze[tmp.x][tmp.y]);
    
    if( tmp.x<1 || tmp.x>n){
        printf("x범위초과\n");
        return 0;
    }
    if(tmp.y<1||tmp.y>n+1){
        printf("y범위초과\n");
        return 0;
    }
    //2. wall이 아니고, 벽이아니어야한다.
    switch (maze[tmp.x][tmp.y]) {
        case 0:
            printf("갈 수 있는 길입니다.\n");
            return 1;
        case 1:
            printf("벽입니다. 갈 수 없습니다.\n");
            return 0;
            
        case 2:
            printf("이미 방문한 길입니다. 갈 수 없습니다.\n");
            return 0;
            
        case 3:
            printf("이미 방문한 길입니다. 갈 수 없습니다.\n");
            return 0;
            
        default:
            return 0;
    }
    
}

void print_maze(int x,int y){
    sleep(1);
    clear();
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    
                    printf("ㅁ");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("ㅁ");
                    break;
                case 2:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("ㅁ");
                    printf(RESET);
                    break;
                    
                case 3:
                    printf(BOLDGREEN);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("ㅁ");
                    printf(RESET);
                    break;
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                        printf("ㅁ");
                    }else
                        printf("ㅁ");
                    printf(RESET);
                    break;
                default:
                    break;
            }
            printf(RESET);
            if(j==MAX+1)printf("\n");
        }
    }
    printf(RESET);
}
```

- 스택을 이용하는 방법은 한쪽 방향으로 갈 수 있는 만큼 깊이 간므로 DFS방법이다.

## Queue(BFS)

### 규칙
다음과 같은 순서로 cell들을 방문한다.

- L0 = {s}, 여기서 s는 출발 지점
- L1 = L0에서 1번에 갈 수 있는 모든 셀들
- L2 = L1에서 1번에 갈 수 있는 모든 셀들 중에 L0에 속하지 않는 셀들
- …
- Ln = Ln-1에서 1번에 갈 수 있는 셀들 중에 Ln-2에 속하지 않는 셀들

스택에서는 북->동->남->서로 찾기 때문에 최단 경로로 찾는지 보장할 수 없다.
하지만 큐에서는 **동심원 형태로 찾기때문에 입구에서 출구까지 최단 경로를 찾을 수 있다**.

```
- 하나의 큐를 만든다.
- 위치(0,0) 는 이미 방문한 위치임을 표시하고, 큐에 위치(0,0)을 넣는다. 
- 큐가 빌 때까지 다음을 반복한다.
    - 큐에서 하나의 위치 p를 꺼낸다.
    - p에서 한 칸 떨어진 위치들 중에서 이동 가능하면서 아직 방문하지 않은 모든 위치들을 방문된 위치임을 표시하고 큐에 넣는다.
    - 만약 그 위치가 출구라면 종료한다.
```
**출구에서 숫자가 감소하는 방향으로 따라가면 입구에 도달**한다.

### 구현


#### Position

스택과 동일

#### Queue

```c
//
//  queue.h
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct node{
    Position pos;
    struct node * next;
}QNode;

typedef struct que{
    QNode *front, *rear;
}Queue;

void enQueue(Queue * q,Position pos);
void deQueue(Queue * q);
Position front(Queue *queue);
Position rear(Queue *queue);
QNode * new_node(Position pos);
Queue * creat_queue(void);

#endif /* queue_h */

```

```c
//
//  queue.c
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "queue.h"

QNode * new_node(Position pos){
    QNode * new = (QNode *)malloc(sizeof(QNode));
    new->pos.x = pos.x;
    new->pos.y = pos.y;
    new->next=NULL;
    return new;
}

Queue * creat_queue(void){
    Queue * new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear= NULL;
    return new;
}


Position front(Queue *q){
    return q->front->pos;
}

Position rear(Queue *q){
    return q->rear->pos;
}

int is_empty(Queue * q){
    return (q->front==NULL && q->rear==NULL);
}

//front 포인터는 삭제,  rear 포인터는 삽입할 때 사용
void enQueue(Queue * q,Position pos){
    QNode * tmp = new_node(pos);
    
    if(is_empty(q)){
        q->front = q->rear = tmp;
        return;
    }
    q->rear->next= tmp;
    q->rear=tmp;
}

void deQueue(Queue * q){
    if(q->front==NULL){
        return;
    }
    q->front = q->front->next;
    if(q->front==NULL) q->rear=NULL;
}
```
#### Main

```c
//
//  main.c
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "queue.h"
#include "position.h"
#include "color.h"
#include <unistd.h>

#define MAX 8
#define PATH 0              // 지나갈 수 있는 길
#define WALL 1              // 지나갈 수 없는 길 == 벽 흰색!
#define EDGE 4              // 테두리
#define clear() printf("\033[H\033[J")


int maze[MAX+2][MAX+2]= {
    {4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,0,0,1,1,0,0,4},
    {4,0,1,1,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,1,1,0,1,0,0,4},
    {4,4,4,4,4,4,4,4,4,4}
};

void print_maze();
int movable(Position pos,int dir);

int main(int argc, const char * argv[]) {
    
    
    Queue *q = creat_queue();
    
    Position cur;
    cur.x=1;
    cur.y=1;

    
    enQueue(q,cur);

    // 추가 배열을 사용하지 않기 위해 방문 표시를 음수로 저장
    maze[1][1]=-1;
    int found = 0;

    while(!is_empty(q)){
        Position cur = front(q);
        deQueue(q);
        for(int dir=0;dir<4;dir++){
            //그 셀이 1(벽)이 아니면서 방문하지 않은 곳인지 검사!
            if(movable(cur,dir)){
                //move_to도 동일한 함수
                Position pos = move_to(cur,dir);
                // 추가 배열을 사용하지 않기 위해 방문 표시를 음수로 저장
                maze[pos.x][pos.y] = maze[cur.x][cur.y]-1;

                if(pos.x==MAX&&pos.y==MAX){
                    printf("미로를 찾았습니다.\n");
                    final_path(pos);
                    found=1;
                    exit(0);
                }
                enQueue(q,pos);
            }
        }
    }

    return 0;
}
```

- movable함수

```c
int movable(Position pos, int dir){
    Position tmp = move_to(pos, dir);
    //1. dir방향으로 이동한 좌표가 1~MAX이내에 있어야한다.
    print_maze(tmp.x,tmp.y);
    printf("maze[%d][%d]=%d\n",tmp.x,tmp.y,maze[tmp.x][tmp.y]);
    
    if( tmp.x<1 || tmp.x>MAX){
        printf("x범위초과\n");
        return 0;
    }
    if(tmp.y<1||tmp.y>MAX){
        printf("y범위초과\n");
        return 0;
    }
    //2. wall이 아니고, 벽이아니어야한다.
    switch (maze[tmp.x][tmp.y]) {
        case 0:
            printf("갈 수 있는 길입니다.\n");
            return 1;
        case 1:
            printf("벽입니다. 갈 수 없습니다.\n");
            return 0;
        default:
            printf("이미 방문한 길입니다. 갈 수 없습니다.\n");
            return 0;
    }
    
}
```

- print_maze

```c
void print_maze(int x,int y){
//    sleep(1);
//    clear();
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    
                    printf("ㅁ");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("ㅁ");
                    break;
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                        printf("ㅁ");
                    }else
                        printf("ㅁ");
                    printf(RESET);
                    break;
                default:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("ㅁ");
                    printf(RESET);
                    break;
                    
                    break;
            }
            printf(RESET);
            if(j==MAX+1)printf("\n");
        }
    }
    printf(RESET);
}
```

- final_path

마지막으로 찾은 최종 경로를 표시해주기 위한 함수입니다.

```c
void final_path(Position pos){
    
    Position cur = pos;
    Position next;
    
    int offset[4][2] = {
        {-1,0},{0,1},{1,0},{0,-1}
    };
    int num=maze[cur.x][cur.y]+1;
    
    maze[cur.x][cur.y]=FINAL;
    
    while(1){
        for(int i=0;i<4;i++){
            next.x=cur.x+offset[i][0];
            next.y=cur.y+offset[i][1];
            if(maze[next.x][next.y]==num){
                maze[next.x][next.y]=FINAL;
                cur=next;
                num++;
                break;
            }
        }
        if(cur.x==1&&cur.y==1)break;
    }
    print_maze(n-2, n-2);
}
```
## Dijkstra

```c
/*
출발점으로 부터 모든노드의 최단거리
다익스트라 인접리스트로 미로찾기 최단거리 구함!
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "color.h"
#define MAX 8
#define PATH 0
#define WALL 1
#define VISITED 2
#define FINAL 3
#define EDGE 4

int maze[MAX+2][MAX+2]={
    {4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,0,0,1,1,0,0,4},
    {4,0,1,1,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,1,1,0,1,0,0,4},
    {4,4,4,4,4,4,4,4,4,4}
};
int parent[100];
int end, start;

void print_maze(int x, int y);
typedef struct node{
    int dest;       //목적노드
    int weight;     //가중치
    struct node * next;
} Node;

typedef struct list{
    Node * head;
}List;

typedef struct graph{
    int V;
    List * array;
}Graph;

Node * new_node(int dest, int weight){
    Node * new = (Node*)malloc(sizeof(Node));
    new->dest=dest;
    new->weight=weight;
    new->next=NULL;
    return new;
}

Graph * create_graph(int V){
    Graph * g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->array = (List*)malloc(V*sizeof(List));
    for(int i=0;i<V;i++){
        g->array[i].head=NULL;
    }
    return g;
}

void add_edge(Graph *g,int src, int dest, int weight){
    Node * new = new_node(dest, weight);
    new->next=g->array[src].head;
    g->array[src].head=new;
    
    new=new_node(src, weight);
    new->next = g->array[dest].head;
    g->array[dest].head = new;
}

typedef struct hnode{
    int v;
    int dis;
}HNode;

typedef struct heap{
    int size;
    int capacity;
    int *pos;       //decrease key()에 필요하다.
    HNode **array;
}Heap;

HNode * new_hnode(int v, int dis){
    HNode * new = (HNode*)malloc(sizeof(HNode));
    new->v=v;
    new->dis=dis;
    return new;
}

Heap * create_heap(int capacity){
    Heap * heap = (Heap*)malloc(sizeof(Heap));
    heap->pos=(int*)malloc(capacity*sizeof(int));
    heap->size=0;
    heap->capacity=capacity;
    heap->array=(HNode**)malloc(capacity*sizeof(HNode*));
    return heap;
}


void swap_node(HNode ** a, HNode **b){
    HNode * tmp =*a;
    *a=*b;
    *b=tmp;
}

void heapify(Heap* heap,int i){
    int min,left,right;
    min=i;
    left = i*2+1;
    right = i*2+2;
    
    if(left < heap->size && (heap->array[left]->dis < heap->array[min]->dis))min=left;
    if(right<heap->size && heap->array[right]->dis<heap->array[min]->dis)min=right;
    if(min!=i){
        HNode * smallest = heap->array[min];
        HNode * inode = heap->array[i];
        heap->pos[smallest->v]=i;
        heap->pos[inode->v]=min;
        
        swap_node(&heap->array[min], &heap->array[i]);
        heapify(heap,min);
    }
}

int is_empty(Heap * h){
    return h->size==0;
}

HNode * delete(Heap * h){
    if(is_empty(h))return NULL;
    
    HNode * root = h->array[0];
    HNode * last = h->array[h->size - 1];
    
    h->array[0]=last;
    
    h->pos[root->v]=h->size-1;
    h->pos[last->v]=0;
    
    --h->size;
    heapify(h, 0);
    
    return root;
}


void decrease_key(Heap * h, int v, int dis){
    
    // heap array의 정점 v에 대한 index
    int i = h->pos[v];
    
    h->array[i]->dis = dis; //distance update
    while(i && ( h->array[i]->dis < h->array[(i-1)/2]->dis)){
        h->pos[h->array[i]->v] = (i-1)/2;
        h->pos[h->array[(i-1)/2]->v] = i;
        swap_node(&h->array[i], &h->array[(i-1)/2]);
        i=(i-1)/2;
    }
}

int is_min(Heap * h, int v){
    if(h->pos[v] < h->size) return 1;
    else return 0;
}

void backtracking(int end){
    int i, j, back;
    int m = MAX+2;
    back = end;
    i  = end / m;
    j  = end % m;
    
    while( parent[back] != -1)
    {
        back = parent[back];
        
        maze[i][j] = FINAL;
        
        i  = back / 10;
        j  = back % 10;
    }
    maze[1][1] = FINAL;
}

void print_array(int dis[],int n){
    printf("정점\t\t시작노드로부터거리\n");
    int e = 88;
    for(int i=0;i<n;i++){
        if(i==e)printf("도착지!!\n");
        printf("%d\t\t\t%d\n",i,dis[i]);
    }
    
}

void dijkstra(Graph * g,int src){
    int V= g->V;
    int dis[V];
    
    Heap * heap = create_heap(V);
    
    for(int i=0;i<V;i++){
        dis[i]=INT_MAX;
        heap->array[i]=new_hnode(i, dis[i]);
        heap->pos[i]=i;
    }
    
    // 출발점의 거리를 0으로 만듦
    heap->array[src]=new_hnode(src, dis[src]);
    heap->pos[src]=src;
    dis[src]=0;
    decrease_key(heap,src,dis[src]);
    
    heap->size=V;
    
    while(!is_empty(heap)){
        HNode * min = delete(heap);
        int u = min->v;
        
        Node * trav = g->array[u].head;
        while(trav!=NULL){
            int v = trav->dest;
            
            if(is_min(heap, v)&&dis[u]!=INT_MAX && trav->weight+dis[u]<dis[v]){
                dis[v] = dis[u] + trav->weight;
                parent[v]=u;
                maze[u/(MAX+2)][u%(MAX+2)]=VISITED;
                print_maze(u/(MAX+2), u%(MAX+2));
                decrease_key(heap,v,dis[v]);
            }
            trav=trav->next;
        }
    }
    print_array(dis, V);
}
void print_maze(int x,int y){
    // sleep(1);
    // clear();
    
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    
                    printf("[]");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    break;
                case 3:
                    printf(BOLDGREEN);
                    printf("[]");
                    printf(RESET);
                    break;
                    
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                        printf("[]");
                    }else
                        printf("[]");
                    printf(RESET);
                    break;
                default:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    printf(RESET);
                    break;
                    
                    break;
            }
            printf(RESET);
            if(j==MAX+1)printf("\n");
        }
    }
    printf(RESET);
}

int main()
{
    // create the graph given in above fugure
    
    int m = MAX+2, s;
    Graph * graph = create_graph(m*m);
    
    start = m*1+1;
    end = m*8+8;
    
    parent[start] = -1;
    for(int i=1;i<m-1;i++){
        for(int j=1;j<m-1;j++){
            s=i*m+j;
            if(maze[i][j]==PATH){
                if(i==1){
                    if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                    if(j==1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }else if(j==m-1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                    }else{
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }
                }else if(i==m-2){
                    if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    if(j==1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }else if(j==m-1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                    }else{
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }
                }else if(j==1){
                    if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    if(i!=1&&i!=m-2){
                        if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                        if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    }
                }else if(j==m-2){
                    if(maze[i][j-1]==PATH)add_edge(graph, s, s-1, 1);
                    if(i!=1&&i!=m-2){
                        if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                        if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    }
                }else{
                    if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                    if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    if(maze[i][j-1]==PATH)add_edge(graph, s, s-1, 1);
                }
            }
            
        }
    }
    print_maze(start/m, start%m);
    dijkstra(graph, 11);
    backtracking(end);
    print_maze(end/m, end%m);
    
    return 0;
}
```

## A*

[A* 알고리즘](https://dh00023.github.io/algorithm/ds/2018/05/29/algorithm-astar/) 에 알고리즘에 대해서 자세히 설명되어있다.

#### queue

enQueue할 때, 삽입정렬을 해서 값을 넣어준다. (가중치가 낮은 값을 먼저 꺼내기 위해서!)

```c
typedef struct vertex{
    int x,y;
    int g_x;
}Vertex;

typedef struct node{
    Vertex ver;
    struct node * next;
}QNode;

typedef struct que{
    QNode *front, *rear;
}Queue;

```

```c
QNode * new_node(Vertex v){
    QNode * new = (QNode *)malloc(sizeof(QNode));
    new->ver.x = v.x;
    new->ver.y = v.y;
    new->ver.g_x = v.g_x;
    new->next=NULL;
    return new;
}

Queue * creat_queue(void){
    Queue * new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear= NULL;
    return new;
}

Vertex front(Queue *q){
    return q->front->ver;
}

Vertex rear(Queue *q){
    return q->rear->ver;
}

int is_empty(Queue * q){
    return (q->front==NULL && q->rear==NULL);
}


//front 포인터는 삭제,  rear 포인터는 삽입할 때 사용
void enQueue(Queue * q,Vertex v){
    QNode * new = new_node(v);
    QNode * tq  =q->front;
    Vertex tmp;
    int key;
    
    if(is_empty(q)){
        q->front = q->rear = new;
        return;
    }
    
    //우선순위큐
    // with insertion-sort, begin sorting process.
    while( tq!= NULL){
        key = weight[v.x][v.y];
        
        if( key < weight[tq->ver.x][tq->ver.y]){
            tmp = tq->ver;
            tq->ver = v;
            v  = tmp;
        }
        tq = tq->next;
    }
    new->ver = v;
    q->rear->next= new;
    q->rear=new;
}


void deQueue(Queue * q){
    if(q->front==NULL){
        return;
    }
    q->front = q->front->next;
    if(q->front==NULL) q->rear=NULL;
}
```

#### heuristic

```c
// heuristic함수로 가중치를 계산하는 함수
// 여기서 pre는 이전정점의 gx값을 받아온다.
int heuristic(Vertex v, int x,int y, int *pre){
    int res;
    
    // h(x)함수 즉, 출구에서 얼마나 걸리는지 계산한다.(맨하탄)
    res = ((abs(end.x-x)+abs(end.y-y))*10);
    
    *pre = v.g_x;
    
    // 대각선인 경우
    if(abs(v.x-x)==abs(v.y-y)){
        *pre = *pre +14;
    }else{
        *pre = *pre +10;
    }
    // f(x) = g(x) + h(x)
    return res+(*pre);
}
```

#### open list

```c
// 인접노드를 queue에 추가하기
void add_openlist(Queue * q,Vertex v){
    Vertex tmp;
    
    // pw는 이전 weigt
    int i,j,w,pre;
    
    // 인접한 정점 확인
    for(i=v.x-1;i<=v.x+1;i++){
        
        if(i<1||i>MAX)continue;             // 범위를 벗어나면 통과한다.
        for(j=v.y-1;j<=v.y+1;j++){
            if(j<1||j>MAX)continue;         // 범위를 벗어나면 통과한다.
            if(i==v.x&&j==v.y)continue;     // i와 j가 현재 노드랑 같으면 통과
            if(maze[i][j]!=0)continue;      // 길이 아니면 통과
            
            // 가중치 f(x)
            w = heuristic(v, i, j, &pre);
            
            // 가중치가 현재보다 낮거나 기록이 안되어있으면 갱신
            if(w<weight[i][j]||weight[i][j]==0){
                weight[i][j]=w;
                // 부모 노드의 정보를 저장한다.
                parent[i][j] = (v.x*MAX+2)+v.y;
                
                // 출구를 찾으면 종료
                if(end.x == i && end.y ==j)return;
                
            }
            tmp.x = i;
            tmp.y = j;
            tmp.g_x = pre;
            enQueue(q, tmp);
        }
    }
    
}
```

#### astar

```c
void astar(Vertex s,Vertex e){
    
    Queue * q = creat_queue();
    
    Vertex v;
    
    // 시작점의 weight는 0이다.
    weight[s.x][s.y] = 0;
    // 시작점은 부모노드를 갖고 있지 않는다.
    parent[s.x][s.y]=-1;
    // 시작점에서 움직인 거리(gx)는 0이다.
    s.g_x = 0;
    
    v = s;
    
    add_openlist(q,v);
    
    while(!is_empty(q)){
        
        
        // 현재 점을 Closed list에 추가 >> maze에 바로표시
        maze[v.x][v.y]=CLOSED;
        v = front(q);
        deQueue(q);
        if(v.x==end.x && v.y==end.y)return;
        
        // 새로운 인접노드를 추가해준다.
        add_openlist(q, v);
        
    }   
}
```

#### backtracking

```c
void backtracking(){
    int i, j, back;
    
    if(parent[end.x][end.y]==0){
        printf("경로가 없습니다.\n");
        return;
    }
        
    i  = parent[end.x][end.y] / MAX+2;
    j  = parent[end.x][end.y] % MAX+2;
    
    while( parent[i][j] != -1)
    {
        back = parent[i][j];
        
        maze[i][j] = FINAL;
        
        i  = back / MAX+2;
        j  = back % MAX+2;
    }
    maze[start.x][start.y] = FINAL;
}
```

#### print
```c
void print_weight(){
    int i,j;
    for(i=0;i<MAX+2;i++){
        for(j=0;j<MAX+2;j++)
            printf("%6d",weight[i][j]);
        printf("\n");
    }
    
}
void print_maze(int x,int y){
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    
                    printf("[]");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    break;
                case 3:
                    printf(BOLDGREEN);
                    printf("[]");
                    printf(RESET);
                    break;
                    
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                        printf("[]");
                    }else
                        printf("[]");
                    printf(RESET);
                    break;
                default:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    printf(RESET);
                    break;
                    
                    break;
            }
            printf(RESET);
            if(j==MAX+1)printf("\n");
        }
    }
    printf(RESET);
}
```
#### main

```c
int main(){
    start.x=1;start.y=1;
    end.x=MAX;end.y=MAX;
    astar(start, end);
    print_weight();
    print_maze(end.x,end.y);
    backtracking();
    print_maze(end.x,end.y);
}
```

