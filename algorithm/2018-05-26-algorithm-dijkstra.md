# 다익스트라 알고리즘(Dijkstra's Algorithm)

다익스트라 알고리즘은 시작점으로 부터 나머지 정점까지 최단거리를 구할 때 사용한다. 주로 네트워크 경로 설계에 많이 적용된다.

- (ex) OSPF(Open Shortest Path First)라는 IP 망에서의 라우팅 프로토콜.

간선에 가중치가 있는 그래프에서 1:N 최단거리를 구하는 알고리즘이다. 다익스트라 알고리즘은 너비우선탐색(BFS)을 기본으로 한다. 이때 **가중치는 음수값을 갖지 않는다.**



## 구현방법

다익스트라 알고리즘은 각각의 정점에 대해서 정점 s에서 정점 v까지의 최단 거리를 d[v]에 저장하면서 탐색한다. 알고리즘 시작 시에 d[s] = 0이고, s가 아닌 다른 모든 정점에 대해서는 d[v] = ∞ 로 놓아 다른 정점에 대해서는 아직 최단 경로를 모른다는 것을 표시한다. 알고리즘이 종료되었을 때 d[v]는 s에서 v까지의 최단 경로의 거리를 나타내게 되고, 만약 경로가 존재하지 않으면 거리는 여전히 무한대로 남는다.

![ë¤ìµì¤í¸ë¼ ìê³ ë¦¬ì¦ì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](https://lh3.googleusercontent.com/nriXR42Kaq1uwLkXLqiAi5r8naWSA2Ur2Wp_za6DA7boHk0m6f79zovVJsNVL4qua3_Q2jpnExWtJiSSACClvmxbDRCn0vkPbl2nEMsX0kB_bf1kQ3iX)

다익스트라 알고리즘은 다음과 같다.` G[A][B]`는 A와 B 사이의 거리라고 하자.

1. 출발점으로부터의 최단거리를 저장할 배열 d[v]를 만들고, 출발 노드에는 0을, 출발점을 제외한 다른 노드들에는 매우 큰 값 INF(자료형의 최대값)를 채워 넣는다.
2. 현재 노드 A에 출발 노드를 저장한다.
3. A로부터 갈 수 있는 임의의 노드 B에 대해, `d[A]+G[A][B]`와 d[B]의 값을 비교한다.
4. 만약 `d[A]+G[A][B]`가 더 짧다면, d[B]의 값을 이 값으로 갱신시킨다. (*edge relaxtion*)
5. 모든 이웃 노드 B에 대해 이 작업을 수행한다.
6. A의 상태를 "방문 완료"로 바꾼다. 그러면 이제 더 이상 A는 사용하지 않는다.
7. "미방문" 상태인 모든 노드들 중, 출발점으로부터의 거리가 제일 짧은 짧은 노드 하나를 골라서 그 노드를 A에 저장한다.
	- 모든 노드를 순회해 거리가 제일 짧은 노드를 찾아야한다. 이때 우선순위큐를 활용하면 이 비용을 줄일 수 있다.
8. 도착 노드가 "방문 완료" 상태가 되거나, 혹은 더 이상 미방문 상태의 노드를 선택할 수 없을 때까지, 3~7의 과정을 반복한다.

도착 노드에 저장된 값이 A로부터의 최단거리이다. 만약 도착노드의 값이 INF라면, 중간에 경로가 끊긴 것을 의미한다.

### edge relaxation?



![](https://i.imgur.com/nqdnANR.png)

기존의 d(z)가 75였는데 탐색 과정에서 d(u)+e = 60으로 길이가 더 짧을 때, 노드와 엣지의 정보를 업데이트 해주는 것을 말한다.



## 구현

### 인접행렬

```c
#include <stdio.h>
#include <limits.h> //INT_MAX
#define V 9
typedef enum { false, true } bool;

// 최단 거리를 찾는 함수
int min_distance(int dist[], bool visited[])
{
    // 자료형의 최대값으로 min값 설정
    int min = INT_MAX, min_index=0;

    for (int v = 0; v < V; v++){
        //visited[v]가 false이면서 dist[v]가 최소값보다 적은 경우
        if (visited[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }

    }
    return min_index;
}

void print_path(int parent[], int j){
    if (parent[j] == - 1)
        return;
    
    print_path(parent, parent[j]);
    
    printf("%d ", j);
}

// dist 배열을 출력해주는 함수
void print_distance(int dist[], int n, int parent[])
{
    int src =0;
    printf("Vertex\t시작 정점으로부터 거리\t경로\n");
    for (int i = 0; i < V; i++){
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, dist[i], src);
        print_path(parent, i);
    }
    
    
}

// 다익스트라 함수
void dijkstra(int graph[V][V], int src)
{
    // dist배열은 최단거리를 저장하는 배열이다. 즉, 결과값
    // src에서 정점 i까지 가는 거리
    int dist[V];
    bool visited[V]; //방문했는지 기록하는 배열
    int parent[V]; // 부모 노드를 기억할 배열

    // dist배열은 자료형의 최대값, visited배열은 false 로 초기화
    parent[0] = -1;
    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // 시작점(src)에서 자기자신의 거리는 0이다.
    dist[src] = 0;

    // 모든 정점에서 최단거리 찾기
    for (int count = 0; count < V-1; count++){

        int u = min_distance(dist, visited); // 최소거리의 정점을 저장한다. u는 count가 0일때 src와 같다.

        visited[u] = true; //방문했음을 표시한다.

        // 값을 update해준다.
        for (int v = 0; v < V; v++){
            // visited이 false이면서, u->v로의 엣지가 있고
            // 엣지를 더한 값이 현재 distance보다 작은 경우
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }


    }
    // 시작점으로 부터 각 정점의 최단거리 출력
    print_distance(dist, V,parent);
}

int main()
{
    
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {5, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {0, 12, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);

    return 0;
}
```

### 인접 리스트

최소힙(minheap)은 우선순위큐로 아직 포함되지 않은 정점으로 부터 최소 거리 정점을 가져온다. 

1. 크기 V(그래프 정점 수)의 최소 힙을 생성 ( 정점 번호, 정점의 거리 값 포함 )
2. src를 시작 루트로 하여 최소힙을 초기화한다. (src->src의 거리는 0, 나머지는 INF)
3. 최소힙이 빌때까지 반복해서 수행한다.
   1. 최소 거리값 정점을 추출(u)한다.
   2. 추출된 정점(u)의 모든 인접한 정점(v)에 대해서 v가 최소힙에 있는지 확인한다. 최소 힙에 있고, 거리값이 u+v의 가중치보다 작다면 distance를 업데이트한다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void print_array(int dis[],int n){
    printf("정점\t\t시작노드로부터거리\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t\t%d\n",i,dis[i]);
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
                decrease_key(heap,v,dis[v]);
            }
            trav=trav->next;
        }
    }
    print_array(dis, V);
}
int main(){
    int V = 9;
    Graph * graph = create_graph(V);
    
    add_edge(graph, 0, 1, 4);
    add_edge(graph, 0, 7, 8);
    add_edge(graph, 1, 2, 8);
    add_edge(graph, 1, 7, 11);
    add_edge(graph, 2, 3, 7);
    add_edge(graph, 2, 8, 2);
    add_edge(graph, 2, 5, 4);
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 3, 5, 14);
    add_edge(graph, 4, 5, 10);
    add_edge(graph, 5, 6, 2);
    add_edge(graph, 6, 7, 1);
    add_edge(graph, 6, 8, 6);
    add_edge(graph, 7, 8, 7);
    
    dijkstra(graph, 0);
    
    return 0;
}
```



## 단점

![](https://i.imgur.com/71eZ0Fo.png)



- 가중치가 음수인 경우 처리할 수 없다.

![](http://chunchu.yonsei.ac.kr/news/photo/201603/21321_9235_5528.JPG)

- 출발점으로부터 거리가 가까우면서 동시에 도착점의 방향과 무관한 점들의 최단 경로를 먼저 찾는 헛수고를 하는 경우가 있다. 출발점이 a이고 도착점이 d일 때, 다익스트라 알고리즘은 도착점과 무관한 방향에 있는 점 e, f, g, h, i 모두의 최단 경로를 찾은 후에서야 도착점 d를 향해 최단 경로 찾기를 수행한다. 