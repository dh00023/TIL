# A* 알고리즘

최단 경로를 찾을 때 가장 많이 사용하는 알고리즘으로 다익스트라 알고리즘을 확장시킨 알고리즘이다. A* 알고리즘은 출발점을 제외한 각각의 점에 대해 도착점까지의 예상 거리 (예를 들어, 지도상의 좌표로 계산된 직선 거리)를 추가하여 고려한다. 즉, **A\* 알고리즘은 각 지점마다 출발점으로부터의 거리뿐만 아니라 도착점까지의 예상 거리의 합까지 고려하여 다익스트라 알고리즘을 수행**한다. 도착점과 반대 방향에 있는 점이 출발점에 가깝다 하더라도, A* 알고리즘은 도착점 방향에 있는 점들의 최단 경로를 우선적으로 계산해 출발점과 도착점간의 최단 경로를 다익스트라 알고리즘보다 빨리 찾는다. A* 알고리즘은 **휴리스틱 함수(heuristic function)**를 이용한다.

### 탐색과정

![]({{ "/assets/images/algo/astar1.png" | absolute_url }})  

녹색 출발지점(A), 빨간색 도착지점(B), 파란색 벽일때, 검색지역(흰색)이 사각형 Grid형태로 나누어져있다. 이 탐색범위를 단순히 2차원 배열로 만들어준다.

갈 수 있는길(흰색), 갈 수 없는길(파란색, 장애물)로 상태가 기록해두어 갈 수 있는 길만 탐색한다.

![]({{ "/assets/images/algo/astar2.png" | absolute_url }})  

- 출발노드(A)에 붙어있고 지나갈 수 있는 모든 길(벽, 범위를 벗어난 곳)을 open list에 추가한다. 추가된 노드들은 출발노드(A)를 부모 노드라 기록한다.(Backtracking)
- 출발노드를 open list에서 빼고, 방문했다는 것을 표시하기 위해서 closed list에 추가한다.

open list에 저장된 인접노드(화살표)중 어떤 노드를 선택해야할까? 가장 적은 F비용을 가진 것을 선택한다.

A* 알고리즘은 출발 노드로부터 목표 노드까지의 최적 경로를 탐색하기 위한 것이다. 이를 위해서는 각각의 노드에 대한 평가 함수를 정의해야 한다. 이를 위한 평가 함수  f(n)은 다음과 같다.

f(n) = g(n) + h(n)

- g(n) : 출발 노드로부터 현재 노드 까지의 경로 가중치
  - g(n) 은 부모노드(이전노드)로 부터 경로 가중치를 얻어와 더해준다.
- h(n) : 현재 노드로부터 목표 노드까지의 추정 경로 가중치( 장애물에 대해서 고려하지 않고 계산한다.)
  - h(n) 은 노드의 위치의 변화에 따라서 예측할 수 있다. h(n)이 휴리스틱 함수이며, 여기서는 맨하탄 방식(manhattan method)를 사용할 것이다.  : 대각선 이동을 제외한 가로, 세로 이동한 총 숫자 * 10

보통 가로, 세로 10, 대각선은 14의 경로 가중치를 할당한다.

![]({{ "/assets/images/algo/astar3.png" | absolute_url }}) 


1. 출발노드 open list(우선순위 큐)에 넣는다.
2. 출발노드 open list에서 pop(), closed list에 추가
3. 출발노드를 기준으로 주변노드를 탐색해 F가중치와 부모노드 구함
4. 계산된 주변 노드 open list에 push()

![]({{ "/assets/images/algo/astar4.png" | absolute_url }})


1. open list에서 F값이 가장 작은 노드 pop()
2. 주변 탐색 가능한 노드 찾기
    - 출발노드는 closed list에 존재하므로 무시
    - 장애물도 무시
3. F가 54인 두개 노드는 open list에 있으므로 현재 노드를 거쳐가는 경로 가중치와 비교
    - F=54의 G=14가  F=40을 거쳐가는 G=20보다 작으므로 값을 변경하지 않음
4. F=40 closed list push

![]({{ "/assets/images/algo/astar5.png" | absolute_url }})


1. open list에서 F값이 가장 작은 노드 pop() : F=54
2. 주변 탐색 가능한 노드 찾기
    - closed list에 존재하는 노드 무시
    - 장애물도 무시
3. F가중치를 비교해 기전의 값이 더 작으면 갱신하지 않음
4. open list에 없는 노드 F 가중치 계산후 push()

**위와 같은 과정을 반복한다.**

![]({{ "/assets/images/algo/astar6.png" | absolute_url }})

![]({{ "/assets/images/algo/astar7.png" | absolute_url }})

![]({{ "/assets/images/algo/astar8.png" | absolute_url }})

![]({{ "/assets/images/algo/astar9.png" | absolute_url }})

![]({{ "/assets/images/algo/astar10.png" | absolute_url }})

목표노드에서 부터 부모노드를 따라서 되돌아가면 최단경로가 구해지는 것을 볼 수 있다.  

### C언어 구현

#### heuristic

```c
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
            if(map[i][j]!=0)continue;      // 길이 아니면 통과
            
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
        
        // 새로운 인접노드를 추가해준다.
        add_openlist(q, v);   
    }   
}
```

#### backtracking

```c
void backtracking(){
    int i, j, back;
    
    i  = parent[end.x][end.y] / MAX+2;
    j  = parent[end.x][end.y] % MAX+2;
    
    while( parent[i][j] != -1)
    {
        back = parent[i][j];
        
        maze[i][j] = FINAL;
        
        i  = back / MAX+2;
        j  = back % MAX+2;
    }
    map[start.x][start.y] = FINAL;
}
```



### 단점

맵의 크기가 커지면 open list나 close list의 목록에 수백에서 수천 개의 노드가 들어갈 수 있기 때문에, 메모리를 많이 사용하게 된다. 또한 시작노드에서 목표노드까지 경로가 존재하지 않는다면, A*는 시작 위치에서 도달 할 수 있는 모든 위치를 검색해 비효율적이다. 

A* 알고리즘의 가장 근본적인 약점은 열린 목록과 닫힌 목록을 관리하는 비용이다. 이를 극복하기 위하여 열린 목록과 닫힌 목록을 사용하지 않는 IDA* 알고리즘이 제안되었다. 그러나 IDA* 알고리즘은 깊이 우선 검색을 사용하여 메모리 공간을 적게 사용하는 대신 노드들을 재 방문해야하는 단점이 있다. 



## 참고사이트

- [http://egloos.zum.com/cozycoz/v/9748811](http://egloos.zum.com/cozycoz/v/9748811)
- 위키피디아

