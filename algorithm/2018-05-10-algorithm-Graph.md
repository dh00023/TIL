# Graph

그래프는 자료구조의 일종으로 **정점(Node, Vertex)**과 **간선(Edge)**로 이루어져있다. 간선은 정점간의 관계를 나타내며, 정점 사이를 연결한다.

![](https://www.geeksforgeeks.org/wp-content/uploads/undirectedgraph.png)

`G = (V,E)` 로 나타낸다.

일상생활에서 그래프를 예로 들어보면,

1. 지하철 역 : 정점 / 역사이 : 간선
2. 교차로 : 정점 / 도로 : 간선
3. 페이스북 사람 : 정점 / 팔로우 : 간선

이 있다.

**비선형구조**란 i번째 원소를 탐색한 다음 그 원소와 연결된 다른 원소를 탐색하려고 할 때, 여러 개의 원소가 존재하는 탐색구조를 말한다. **그래프** 도 비선형 구조이다.



## 용어

- 노드(Node) or 정점(Vertex)
- 간선(Edge) or 링크(link): 정점간의 관계
- **경로(Path)** : 정점 A에서 B로가는 경로
  - 자동차 네비게이션 빠른길 찾기(최단 경로)
- 사이클(Cycle) or 회로 : 정점 A에서 다시 A로 돌아오는 경로 (시작 노드 == 도착 노드)
- 단순 경로와 단순 사이클 : **같은 정점을 두번 이상 방문하지 않는 경로/사이클**
  - 일반적으로 사용하는 경로와 사이클은 단순 경로/사이클이다.
- Directed Graph(방향 있는 그래프)

![](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1c/Directed_graph%2C_cyclic.svg/450px-Directed_graph%2C_cyclic.svg.png)

- Undirected Graph(방향 없는 그래프 ) == Bidirection Graph(양방향 그래프)
  - A-E는 A→E와 E→A를 나타낸다.
  - 양방향 그래프는 모두 Directed Graph로 변경해서 문제를 풀 수 있다.
  - 일반적으로 그래프라하면 방향이없는 그래프를 말하는 것이다.

![](https://i.stack.imgur.com/YA7NX.png)

- Multiple Edge  : 두 정점 사이에 간선이 여러 개일 수도 있다.
  - a-c는 연결하는 간선이 2개이다.
  - 두 간선은 서로 다른 간선이다.

![](http://www.cs.rpi.edu/academics/courses/spring18/csci2600/multigraph.png)

- Loop(루프) : 간선의 양 끝 점이 같은 경우(4번)

![](http://faculty.ycp.edu/~dbabcock/PastCourses/cs360/lectures/images/lecture15/digraph.png)



- **가중치(Weight)** : 간선에 가중치가 있는 경우이다.
  - 이동 거리, 이동하는데 필요한 시간, 필요한 비용 등등등
  - 가중치가 없는 경우에는 1이라고 생각하면된다.

![](https://i.stack.imgur.com/ea2UI.png)



- 차수(degree) : 정점과 연결되어 있는 간선의 개수이다.
  - 위의 가중치 그림으로 예를 들어보자면
    - 1의 차수 : 2
    - 2의 차수 : 4
  - Directed Graph의 경우에는 차수가 두가지가 있다.
    - in-degree(정점으로 들어오는 간선의 수)
    - out-degree(정점에서 나가는 간선의 수)

## 그래프의 표현

그래프의 표현은 그래프를 저장하는 방식이다. 이때 정점의 수는 정수로 저장하게 되고, 간선은 정점 사이의 관계를 저장한다. 그러므로 간선을 저장하는 것이 그래프를 저장하는 것이다.

![](http://www.ritambhara.in/wp-content/uploads/2017/06/Screen-Shot-2017-06-10-at-7.17.01-PM.png)

보통 알고리즘 문제에서는 첫째 줄에 정점의 개수(n)과 간선의 개수(m)을 입력 받고 간선의 개수만큼 둘째 줄부터 간선의 정보를 입력 받는다.

```
// 양방향인 경우
5 6
A B
A E
B D
C D
C E
D E
```

방향이 있는 그래프라면 인접행렬은 비대칭이다.

### 인접 행렬(adjacency matrix)

그래프에서 정점(node)과 간선(edge)들의 연결관계를 정사각 행렬로 표현한 것이다.

그래프 G = (V, E)를 `n >= 1`(n은 정점이 수)의 정점의 가진 그래프라고 하였을 때 그래프 G에 대한 인접행렬의 크기는 `n * n`이며 `a[n, n]` 크기의 2차원 배열로 표현된다. 이때 a[n, n]에서 `a[i, j] ∈ E(G)`라면 1값을 아니라면 0의 값을 가지게 된다. 



![](http://mathworld.wolfram.com/images/eps-gif/AdjacencyMatrix_1002.gif)

#### 가중치 없는 경우

정점의 개수를 V개라고 했을 때, `V*V` 크기의 이차원 배열을 이용한다.

```c
// i에서 j로 가는 간선이 있을 때
A[i][j] = 1
// i에서 j로 가는 간선이 없을 때
A[i][j] = 0
```

```
//위의 양방향 그래프(B)
0 1 0 0 1
1 0 0 1 0
0 0 0 1 1
0 1 1 0 1
1 0 1 1 0
```

- Undirected Graph 에서는 `A[i][j] == A[j][i]` 이다.
- 없는 간선도 저장하기 때문에 잘 사용하지 않는다.(쉬운 문제를 풀 때 사용)

```cpp
#include <cstdio>

int a[10][10];
int main(){
	int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v;
 		scanf("%d %d",&u,&v);
        a[u][v]=a[v][u]=1; // 양방향
        //단방향인 경우에는 a[u][v]=1;만 해주면된다.
    }
}
```

#### 가중치 있는 경우

가중치가 있을 경우에는 가중치도 같이 저장해주면된다.

```c
// i에서 j로 가는 간선이 있을 때
A[i][j] = w
// i에서 j로 가는 간선이 없을 때
A[i][j] = 0
```

만약 가중치가 0<=w일 경우에는 간선이 없는 경우에는 -1을 저장해주면된다.

하지만 가중치의 범위가 정수라면! 1. 간선의 존재 여부(1,0)를 저장하는 배열 2. 가중치 정보를 저장하는 배열 을 조합해서 사용할 수 있다.

```
//위의 양방향 그래프
0 6 0 0 1
6 0 0 8 0
0 0 0 2 3
0 8 2 0 4
1 0 3 4 0
```

```cpp
#include <cstdio>

int a[10][10];
int main(){
	int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v,w;
 		scanf("%d %d %d",&u,&v,&w);
        a[u][v]=a[v][u]=w;
    }
}
```

#### 공간복잡도

- O(V^2)

#### 시간복잡도

- 어떤 노드 v에 인접한 모든 노드 찾기 O(n)시간
- 어떤 에지(u,v)가 존재하는지 검사 O(1)

### 인접 리스트(adjacency list)

인접행렬은 표현할 때 연결되지 않았던 부분까지 모두 표현이 된다. (연결되지 않은 부분을 0으로 표현한다.) 알고리즘을 구현할 때에도 0까지 모두 조사를 해야하므로 효율이 떨어지는 경우가 많은데 인접리스트는 이러한 단점을 극복한다.

![](https://lh3.googleusercontent.com/22poilDCWxVN7yT5qhzxdzrw8en-V9qGjiTULqjtzDisaVWc4GdhtDOoVw1EP8Dcs2wcYF8WRBH1jEdnbm9HeDMsrCxOMWWCWzpm_zy6AnU3qD4Gk_aa76mul81GkqqS0hphsA)

`std::vector()`를 이용하여 간단하게 구현할 수 있다. ( *[vector 알아보기](https://dh00023.github.io/stl/2018/05/26/cpp-vector/)* )이때 인접행렬로 구현하는 것보다 공간을 적게 사용한다. 각 정점에서 연결되는 리스트의 순서는 중요하지 않다.

#### 가중치 없는 경우(c++)

linked list를 이용해서 구현한다. 이  때 A[i]는 i와 연결된 정점을 linked list로 포함하고 있다.(i와 연결된 정점이 총 몇개인지 알 수 없기 때문이다.)

``` 
A[1] B E
A[2] A D
A[3] D E
A[4] B C E
A[5] A C D
```

이때 연결된 정점을 저장하므로 간선을 나타내게 된다. 모든 간선이 한번 씩 저장(O(E)=간선의 수)된다. 

##### vector로 구현하기

그런데, linked list는 구현하는데 시간이 오래걸리기 때문에, 주로 vector와 같이 길이를 변경할 수 있는 배열을 이용해서 구현한다.

```cpp
#include <cstdio>
#include <vector>
using namespace std;
vector<int> a[10];

int main(){
	int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v;
 		scanf("%d %d",&u,&v);
        a[u].push_back(v);
		a[v].push_back(u);
    }
}
```

주의할점이 한가지 있다. cpp에서 vector의 표현에 주의해아한다.

- `vector<int> a(10)` 은 크기가 10인 1차원 배열을 의미한다. (=`int a[10]`)
- `vector<int> a[10]` 은 int a배열이 10개가 있다는 것을 의미한다.

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int main(){
	int n,m;
    scanf("%d %d",&n,&m);
    vector<vector<int>> a(n+1);
    for(int i=0;i<m;i++){
        int u,v;
 		scanf("%d %d",&u,&v);
        a[u].push_back(v);
		a[v].push_back(u);
    }
}
```

#### 가중치 없는 경우(c)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int vertext;
    struct node * next;
}Node;


typedef struct graph{
    int num_vertex; //vertex 수
    Node ** adjList;
}Graph;

Node * new_node(int v){
    Node * new = (Node *)malloc(sizeof(Node));
    new->vertext = v;
    new->next = NULL;
    return new;
}

Graph * create_graph(int verNum){
    Graph * g = (Graph *)malloc(sizeof(Graph));
    g->num_vertex = verNum;
    
    // verNum개의 정점을 가지는 인접리스트
    g->adjList = malloc(verNum*sizeof(Node));
    for(int i=0;i<verNum;i++)g->adjList[i] = NULL;
    return g;
}

void add_edge(Graph * g, int src, int dest){
    // src에서 dest로가는 edge 추가
    Node * new = new_node(dest);
    new->next = g->adjList[src];
    g->adjList[src] = new;
    
    // dest에서 src로 가는 edge추가
    new = new_node(src);
    new->next = g->adjList[dest];
    g->adjList[dest] = new;
    
}

void print_graph(Graph * g){
    int v;
    for(v=0;v<g->num_vertex;v++){
        Node * tmp = g->adjList[v];
        printf("인접리스트 %d 정점\n",v);
        while(tmp){
            printf(" -> %d",tmp->vertext);
            tmp=tmp->next;
        }
        printf("\n");
    }
}
int main(int argc, const char * argv[]) {
    Graph* graph = create_graph(6);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 4);
    add_edge(graph, 4, 6);
    add_edge(graph, 5, 1);
    add_edge(graph, 5, 6);
    
    print_graph(graph);
    
    return 0;
}
```

```
인접리스트 0 정점
 -> 2 -> 1
인접리스트 1 정점
 -> 5 -> 3 -> 4 -> 2 -> 0
인접리스트 2 정점
 -> 4 -> 1 -> 0
인접리스트 3 정점
 -> 4 -> 1
인접리스트 4 정점
 -> 6 -> 3 -> 2 -> 1
인접리스트 5 정점
 -> 6 -> 1
```



#### 가중치 있는 경우

A[i]는 i와 연결된 정점과 그 간선의 가중치를 linked list로 포함한다. 이때 vector 컨테이너의 타입으로 pair를 사용한다.( *[pair 알아보기](https://dh00023.github.io/stl/2018/05/26/cpp-pair/)* )

```
A[1] (B,6) (E,1)
A[2] (A,1) (D,8)
A[3] (D,2) (E,3)
A[4] (B,8) (C,2) (E,4)
A[5] (A,1) (C,3) (D,4)
```

```cpp
#include <cstdio>
#include <vector>
using namespace std;

vector<pair<int,int>> a[10];
int main(){
	int n,m;
    scanf("%d %d",&n,&m);
;
    for(int i=0;i<m;i++){
        int u,v,w;
 		scanf("%d %d %d",&u,&v,&w);
        a[u].push_back(make_pair(v,w);
        a[v].push_back(make_pair(u,w);
    }
}
```

#### 공간복잡도

- O(E)

#### 시간복잡도

- 어떤 노드 v에 인접한 모든 노드 찾기 O(degree(v))
- 어떤 엣지(u,v)가 존재하는 지 검사 O(degree(u))



### 간선 리스트

STL, array list를 사용할 수 없는 경우에는 간선리스트로 그래프를 저장할 수 있다.

간선리스트는 배열을 이용해서 구현하며, 간선을 모두 저장한다.

- 앞 정점을 기준으로 정렬

```
E[0] = A B
E[1] = A E
E[2] = B A
E[3] = B D
E[4] = C D
E[5] = C E
E[6] = D B
E[7] = D C
E[8] = D E
E[9] = E A
E[10] = E C
E[11] = E D
```

- 각 간선의 앞 정점을 기준으로 개수를 센다.

| i      | 0    | 1    | 2    | 3    | 4    | 5    |
| ------ | ---- | ---- | ---- | ---- | ---- | ---- |
| cnt[i] | 0    | 2    | 2    | 2    | 3    | 3    |

- 각 정점의 간선수의 누적합을 구한다.



| i      | 0    | 1    | 2    | 3    | 4    | 5    |
| ------ | ---- | ---- | ---- | ---- | ---- | ---- |
| cnt[i] | 0    | 2    | 4    | 6    | 9    | 12   |

- i번과 연결된 간선은 E[cnt[i-1]]부터 E[cnt[i]-1]까지 이다.
  - 3번과 연결된 간선은 E[4]~E[6-1]까지

#### 공간복잡도

- O(E)



### 참조페이지

- [https://kingpodo.tistory.com/46](https://kingpodo.tistory.com/46)

