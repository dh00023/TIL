# tree

트리(tree)는 사이클이 없는 그래프로 계층적인 구조(나를 기준으로 위아래 관계가 있다는 것)를 나타내는 자료구조이다.

- 정점(node)의 개수 : V
- 간선(edge)의 개수 : V-1

그렇다면 정점이 V개 간선이 V-1개라면 트리일까? No! 모든 정점이 연결되어 있다면 tree이다.

트리는 1:n 관계를 가지는 **비선형** 구조이다.

## 트리의 용어

![](http://lh5.ggpht.com/-eOm502n5XpU/ULBxUcQDGGI/AAAAAAAACEE/pAbAbm3brXA/clip_image001_thumb%25255B1%25255D.gif?imgmax=800)



( *위의 그림을 기준으로 설명*  )

- 정점/노드(node) : 트리의 구성요소( A, B, C, D, E, F, G, H, I, J )
- 루트(root) : 부모가 없는 노드, 트리의 시작 노드 ( A )
- 간선(edge, link) : 노드와 노드를 연결하는 선 (A,B), (A,C), ...
- 서브트리(subtree) : 하나의 노드와 그 노드의 자손으로 이루어진 트리
  - 부모 노드와 연결된 링크를 끊어 생성되는 트리이다.
  - 각 노드는 자식 노드의 개수만큼 서브트리를 갖는다.
- 형제노드(sbling node) : 부모노드가 같은 자식 노드들
  - B-C , D-E, F-G, H-I
- 조상노드( ancestor ) : 간선을 따라 루트 노드 경로에 있는 모든 노드들
  - H의 조상노드 : D, B, A
- 자식노드( descendants ) : 서브트리에 있는 하위 레벨의 노드
  -  B의 자식노드 : D, E, H, I, J

![](https://i.stack.imgur.com/E43Ll.jpg)
![](https://i.stack.imgur.com/RHEqu.png)

- 레벨(level) : 트리의 각 층의 번호(루트의 level을 0으로 하는 경우와 1로하는 경우가 있다.)
- 깊이(depth) :  **루트에서부터** 거리 
  - root에서부터 해당노드까지의 edge or node 개수
- 높이(height) : **단말노드에서 부터** 거리
  - 노드의 높이 : 노드에서 단말노드에 이르는 edge의 개수
  - 트리의 높이 : 깊이 중 가장 큰 값
    - Empty(null) tree의  height = -1 (왜냐하면 height는 포인터가 아니라 숫자로 표현하기 때문에!)
    - Single-element tree의 height = 0
- 차수(degree) : 노드가 가지고 있는 자식 노드의 개수
  - A의 degree : 3 / B의 degree : 2
  - 트리의 차수 : 트리에 있는 노드의 차수 중 가장 큰 값
- 단말노드(terminal, external, leaf node) : degree / height가 0인 노드, 자식노드가 없는 노드이다.
- 비단말노드(nonterminal, internal node) : 적어도 하나의 자식을 가지는 노드
- 포리스트(forest) : 서브트리의 집합
  - 트리 A에서 A를 제거하면 자식노드 B, C에 대한 서브트리가 생기고, 이들의 집합은 forest가된다.



## Performance of Tree Operation

| Operations                     | Times    |
| ------------------------------ | -------- |
| size, isEmpty                  | O(1)     |
| elements, nodes                | O(n)     |
| replace                        | O(1)     |
| root, parent                   | O(1)     |
| children(v)                    | O(Cv) |
| isInternal, isExternal, isRoot | O(1)     |

모든 연산의 시간 복잡도는 n번 이내에 끝나서 엄청 빠른 구조이다.

## Non-Binary Tree

![non-binary tree search and insertion - Stack Overflow](https://i.stack.imgur.com/F5aFS.png)


non-binary tree의 노드는 element, parent node, children의 리스트를 가지고 있는 연결 리스트 구조이다.




## Binary Tree(이진 트리)

자식을 최대 2개만 가지고 있는 트리를 이진트리(binary tree)라고한다.

```
  A				A
 /		!= 		 \
B				  B
```

값이 같더라도 왼쪽 트리와 오른쪽 트리는 다른 트리로 본다.

- 자식이 최대 2개이므로 모든 노드의 degree는 2이하이다. (=subtree 최대 2개)
- 구현이 편리하다.

*Decision tree / 연산방식 / Search에 많이 사용*

### Binary Tree 성질

- 노드의 개수가 n개이면, 간선의 수는 n-1개이다.
- 높이(height)가 h인 이진트리의 자식 노드 수
  - 최대 2^h -1
  - 최소 h
- n개의 노드를 가지는 이진트리의 높이
  - 최대 n
  - 최소 log(n+1)
- 

### Binary Tree 종류

![](https://2.bp.blogspot.com/-iD61KYN8-CM/Wgz89po2SNI/AAAAAAAAJDI/xRplbDnsPToTNyBSTd1Da16ZoFLkg2UBwCLcBGAs/s1600/%25EC%259D%25B4%25EC%25A7%2584%25ED%258A%25B8%25EB%25A6%25AC_%25EB%25AA%25A8%25EC%259D%258C.PNG)

#### Full Binary Tree (= Proper binary tree)

모든 노드가 0개 또는 2개의 자식 노드를 갖는 트리

#### Complete Binary Tree

**마지막 레벨을 제외하고 모든 레벨이 완전히 채워져 있으며, 마지막 레벨의 모든 노드는 가능한 한 가장 왼쪽**에 있다. 마지막 레벨 *h*에서 1부터 2*h-1* 개의 노드를 가질 수 있다. 또 다른 정의는 가장 오른쪽의 잎 노드가 (아마도 모두) 제거된 포화 이진 트리다. 어떤 저술자는 **완전(complete)**라는 용어를 사용해 위에서 정의한 포화 이진 트리 대신, 이러한 종류의 트리를 **거의 완전한(almost complete)** 이진 트리 또는 **대체로 완전한(nearly complete)** 이진 트리라고 하는 경우도 있다. 완전 이진 트리는 배열을 사용해 효율적으로 표현 가능하다.(*위키피디아*)

#### Perfect Binary Tree

모든 내부 노드가 두 개의 자식 노드를 가지며 모든 잎 노드가 동일한 깊이 또는 레벨을 갖는다.

#### Skewed Binary Tree

한쪽으로 기울어진 트리이다.



<!--## Binary Search Tree(BTS)-->

### Link 방법 구현

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct node{
    int data;
    struct node *left, *right;
}Node;

Node * new_node(int data){
    Node * new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    
    return new;
}
```

#### height

```c
int get_height(Node * node){
    int height = -1;
    
    if(node!=NULL)height = 1 + MAX(get_height(node->left),get_height(node->right));
    
    return height;
}
```

#### 노드 수

```c
int get_node_count(Node * node){
    int count = 0;
    if(node!=NULL)count = 1 + get_node_count(node->left)+get_node_count(node->right);
    return count;
}
```

#### 노드 data의 합 + 과정

```c
int calc_direc_size(Node *node, char *s)
{
    int left_size=0, right_size=0;
    printf("%s ",s);
    if (node==NULL) { printf("    NULL return \n");return 0;}
    else {
        printf("    node : %d \n", node->data);
        left_size += calc_direc_size(node->left,"left");
        right_size += calc_direc_size(node->right,"right");
        
        return (node->data +left_size + right_size);
    }
}
```

#### 노드의 level

```c
int node_level(Node *node, int key, int level)
{
    int downlevel;
    
    if (node == NULL)return -1;
    
    // node의 데이터 찾는 데이터가 같다면 level을 리턴해준다.
    if (node->key == key) return level;
    
    // tree의 왼쪽 노드 level이 내려갈 수록 +1씩 해준후 그 값을 저장 리턴
    downlevel = node_level(node->left, key, level+1);
    if (downlevel != -1) return downlevel;
    // tree의 오른쪽 노드 level이 내려갈 수록 +1씩 해준후 그 값을 저장
    downlevel = node_level(node->right, key, level+1);
    return downlevel;
}
```


## 트리의 표현

### 트리의 부모만 저장하는 방식

트리의 모든 노드는 부모를 하나 또는 0개만 가지기 때문에 부모만 저장하는 방식으로 저장할 수 있다.

![](http://www.algolist.net/img/nearly-complete-binary-tree-correct.png)

| i         | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| --------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| parent[i] | 0    | -1   | 1    | -1   | 3    | 1    | -1   | 6    | 3    |

- 장점 : 한 노드의 부모 노드를 바로 찾을 수 있다.
- 단점 : 자식노드를 찾기 힘들다.

### 배열 표현(이진 트리)

![representation of treeì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](http://www.cse.hut.fi/en/research/SVG/TRAKLA2/tutorials/heap_tutorial/KekoTRAKLA-89_1.gif)

이진 트리의 경우에는 배열로 표현할 수 있다.

부모의 노드가 x인 경우에 자식노드는 왼쪽, 오른쪽 (`2*x`, `2*x+1`) 로 나타내면된다. (주의사항 index는 1부터 시작!한다는 점을 주의해야한다.)

노드  x의 부모 노드 인덱스는 x/2로 알 수 있다.

![](http://www.icodeguru.com/vc/10book/books/book1/224_a.gif)

다음 (a)의 이미지처럼 한 방향으로만 있을 때 5개의노드를 저장하기위해서 배열 크기가 10이 필요하므로 비효율적이다.

이런 경우는 아래와 같은 perfect binary 트리에서 효율적이다.

![](https://1.bp.blogspot.com/-4V266slC8f0/Vb2fiBQVXMI/AAAAAAAAHqo/04CsmIUVky0/s1600/images%2B%25281%2529.png)

#### 이차원배열

```
A[i][0] = i의 왼쪽 자식
A[i][1] = i의 오른쪽 자식
```

다음과 같이 저장할 수 있다. 이런 경우는 많이 사용하지 않는다.



#### Link

![](http://btechsmartclass.com/DS/images/BT%20Linked%20List%20Representation.png)

포인터를 이용하여 부모노드가 자식노드를 가리키게 하는 방법이다.


## Tree Traversal(트리의 순회)

트리의 **모든 노드를 방문하는 순서**이다. 

그래프([11. Graph](https://dh00023.github.io/algorithm/ds/2018/05/10/algorithm-11/) )의 경우에는 **DFS**와 **BFS** 가 있었다. 트리에서도 두 방법을 사용할 수 있지만, 트리에서만 사용할 수 있는 3가지 방법이 있다. 세 방법의 차이는 **노드 방문을 언제 하냐의 차이** 이다.

![](http://www.csharpstar.com/wp-content/uploads/2017/02/BinarySearchTree_Csharp.jpg)

### Preorder(전위 순회)

1. 노드 방문(pre)
2. 왼쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**
3. 오른쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**

*프리 오더는 그래프의 DFS와 순서가 같다.*

### Inorder(중위순회)

1. 왼쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**
2. 노드 방문(in)
3. 오른쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**

*Binary Search Tree에서 Delete 구현시 주로 사용*

### Postorder(후위순회)

1. 왼쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**
2. 오른쪽 자식 노드를 루트로 하는 **서브 트리 프리오더**
3. 노드 방문(post)

*file 드라이브에서 드라이브 용량을 계산할 때 사용되는 방법*



이진트리가 아닌 경우에는 preorder와 postorder만 구현할 수 있다.

### Binary Tree Traversal 구현

#### linked list

```c
void preorder(Node * node){
    if (node == NULL)
        return;
    
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void inorder(Node * node)
{
    if (node == NULL)
        return;
    
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}


void postorder(Node * node){
    if (node == NULL)
        return;
    
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}
```



#### [2차원 배열](https://www.acmicpc.net/problem/1991)

첫째 줄에는 이진 트리의 노드의 개수 N(1≤N≤26)이 주어진다. 둘째 줄부터 N개의 줄에 걸쳐 각 노드와 그의 왼쪽 자식 노드, 오른쪽 자식 노드가 주어진다. 노드의 이름은 **A부터 차례대로 영문자 대문자**로 매겨지며, **항상 A가 루트 노드**가 된다. 자식 노드가 없는 경우에는 `.`으로 표현된다.

```cpp
#include <iostream>
using namespace std;
int A[26][2];

void preorder(int x){
    if(x==-1) return;
    cout << char(x+'A');
    preorder(A[x][0]);
    preorder(A[x][1]);
}
void inorder(int x){
    if(x==-1) return;
    inorder(A[x][0]);
    cout << char(x+'A');
    inorder(A[x][1]);
}
void postorder(int x){
    if(x==-1) return;
    postorder(A[x][0]);
    postorder(A[x][1]);
    cout << char(x+'A');
}

int main(int argc, const char * argv[]) {
    int n; //노드의 수
    scanf("%d",&n);
    
    while(n--){
        char node, left, right;
        cin>>node>>left>>right;
        node -= 'A';
        if(left == '.'){
            A[node][0]=-1;
        }else{
            A[node][0]=left-'A';
        }
        
        if(right == '.'){
            A[node][1]=-1;
        }else{
            A[node][1]=right-'A';
        }
    }
    
    preorder(0);
    printf("\n");
    inorder(0);
    printf("\n");
    postorder(0);
    printf("\n");
    
}
```


## 트리의 탐색

트리의 탐색은 DFS/BFS 알고리즘을 이용해서 할 수 있다. (*[13. DFS와 BFS](https://dh00023.github.io/algorithm/ds/2018/05/21/algorithm-graph-search/) 참조*)

트리는 **사이클이 없는 그래프**이기 때문에 임의의 **두 정점 사이의 경로는 1개**이다. 따라서 **BFS** 알고리즘을 이용해서 최단 거리를 구할 수 있다.

### [트리의 부모찾기](https://www.acmicpc.net/problem/11725)

루트 없는 트리가 주어진다. 이 때, 트리의 루트를 1이라고 정했을 때, 각 노드의 부모를 구하는 프로그램을 작성하시오.

- 입력 : 첫째 줄에 노드의 개수 N (2 ≤ N ≤ 100,000)이 주어진다. 둘째 줄부터 N-1개의 줄에 트리 상에서 연결된 두 정점이 주어진다.
- 출력 : 첫째 줄부터 N-1개의 줄에 각 노드의 부모 노드 번호를 2번 노드부터 순서대로 출력한다.

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
vector<int> a[100000];
bool check[100000];
int depth[100000];
int parent[100000];

void bfs(){
    queue<int> q;
    depth[1]=0;parent[1]=0;
    check[1]=true;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for(int y : a[x]){
            if (check[y] == false) {
                depth[y]=depth[x]+1;
                check[y] = true;
                parent[y]=x;
                q.push(y);
            }
        }
    }
    
}
int main() {
    int n;
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    
    bfs();
    
    for(int i=2;i<=n;i++){
        printf("%d\n",parent[i]);
    }
    return 0;
}
```

## 참고자료

- https://www.geeksforgeeks.org/