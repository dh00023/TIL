# Bellman-Ford 알고리즘


밸만-포드 알고리즘은 [다익스트라](https://dh00023.github.io/algorithm/ds/2018/05/26/algorithm-dijkstra/)에서 할 수 없었던 **음의 가중치도 계산할 수 있도록 한 방법**이다. 그러므로 밸만포드도 다익스트라와 마찬가지로 단일노드 s에서 출발해 그래프 내의 모든 다른 노드에 도착하는 가장 짧은 경로를 찾는 문제이다. 하지만 다익스트라 알고리즘보다 시간복잡도가 높으므로 상황에 맞게 이용해야한다. 

## 개념

시작노드 s에서 도착노드 v까지 이르는 최단 경로는  s에서 u까지의 최단경로 + u에서 v사이의 가중치를 더한 값이다.

```
D(s,v) = D(s,u) + W(u,v)
```

밸만-포드 알고리즘은 s와 u사이의 최단 거리를 구할 때, 그래프 내 모든 edge에 대해서 **edge relaxation** 을 수행해준다.

밸만-포드 알고리즘에서는 모든 엣지에 대한 edge relaxation을 `|V|-1`회 수행한다.

### edge relaxation 이란? 

![](https://i.imgur.com/nqdnANR.png)

기존의 d(z)가 75였는데 탐색 과정에서 d(u)+e = 60으로 길이가 더 짧을 때, 노드와 엣지의 정보를 업데이트 해주는 것을 말한다.

### 예시



![](http://people.inf.elte.hu/hytruongson/Bellman-Ford/10-bellmanford.jpg)

모든 엣지에 대한 edge relaxation을 1회 수행한 것이다. edge relaxation을 수행할 때 거리 정보 뿐만아니라 최단경로 또한 update합니다.

### Negative Cycle

![](https://i.imgur.com/46tJqd7.png)

음수 가중치가 사이클을 이루고 있는 경우에는 밸만-포드 알고리즘은 작동하지 않는다.

위의 그림에서 *c,d*와 *e,f*가  사이클을 이루고 있는 것을 볼 수 있다. *c, d* 의 경우에는 사이클을 돌수록 distance가 커져서 최단 경로를 구할 때 문제가 되지 않지만, *e,f* 의 경우에는 사이클을 돌수록 distance가 작아져서 최단 경로를 구하는 것이 의미가 없어진다.

1. 초깃값 설정을 한다. (시작정점 / 시작정점외 정점들)
2. edge relaxation : 첫번째 반복을 한다. 최단거리를 찾기위함. (정점의개수(V)-1 번 (모든간선 순회) ) 
3. 두번째 반복을 한다. 음의사이클 판정하기 위함.

## 구현

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge{
    int src, dest, weight;
}Edge;

typedef struct graph{
    
    // V는 정점의 수 , E는 edge의수
    int V,E;
    Edge * edge;
}Graph;

Graph * create_graph(int V, int E){
    Graph * g = (Graph*)malloc(sizeof(Graph));
    
    g->V=V; g->E=E;
    g->edge = (Edge*)malloc((g->E)*sizeof(Edge));
    
    return g;
}

void print_array(int dis[], int n){
    printf("정점\t\t시작점으로부터거리\n");
    for(int i =0;i<n;i++)
        printf("%d\t\t\t%d\n",i,dis[i]);
}

void bellman(Graph * graph, int src){
    int v,u,weight;
    
    int V = graph->V;
    int E = graph->E;
    int distance[V];
    
    // 1단계 : 시작점으로 부터 거리 배열을 INT_MAX로 초기화
    // 단, 출발점에서 출발점으로 거리는 0이다.
    for(int i=0;i<V;i++)
        distance[i]=INT_MAX;
    distance[src]=0;
    
    // 2단계 : edge relaxation을 모든 엣지에 대해 |v|-1번 해준다.
    for(int i=1;i<=V-1;i++){
        for(int j=0;j<E;j++){
            u = graph->edge[j].src;
            v = graph->edge[j].dest;
            weight = graph->edge[j].weight;
            
            if(distance[u]!=INT_MAX && distance[u]+weight<distance[v])
                distance[v] = distance[u]+weight;
        }
    }
    
    // 3단계 : 음수사이클이 있는지 검사해준다.
    for(int i=0;i<E;i++){
        u = graph->edge[i].src;
        v = graph->edge[i].dest;
        weight = graph->edge[i].weight;
        if(distance[u]!=INT_MAX && distance[u]+weight<distance[v])
            printf("그래프가 음수 사이클을 포함하고 있습니다.\n");
    }
    
    print_array(distance, V);
}
int main(){
    
    int V = 5;
    int E = 8;
    Graph * graph = create_graph(V, E);
    
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;
    
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;
    
    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;
    
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;
    
    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;
    
    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 5;
    
    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;
    
    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;
    
    bellman(graph, 0);
    
    return 0;
}
```



## 단점

음수 가중치가 있는 경우 최단 거리를 구할 수 있지만 사이클이 있는 경우에는 작동하지 않는다.

## 시간복잡도

그래프에서 노드가 V개, 엣지가 E개 라면 시간복잡도는 O(VE)이다.



## 참조페이지

- [https://ratsgo.github.io/data%20structure&algorithm/2017/11/25/shortestpath/](https://ratsgo.github.io/data%20structure&algorithm/2017/11/25/shortestpath/)

