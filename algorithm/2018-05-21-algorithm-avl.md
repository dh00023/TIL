# AVL 트리

AVL 트리는 Balanced Binary Search Tree이다. AVL 트리는 각각 노드마다 왼쪽, 오른족 서브트리의 높이 차이에 대한 정보를가지고 서브트리의 높이 차이가 1보다 크지않다는 성질을 가진다.(*위키피디아* )

즉, 양쪽 서브트리의 높이 차이가 1이하이다.

균형잡힌 AVL 트리는 n개의 원소가 있을 때 O(logn)의 시간복잡도로 검색, 삽입, 삭제를 할 수 있다.

### 시간 복잡도

|      | 평균    | 최악의 경우 |
| ---- | ------- | ----------- |
| 공간 | O(n)    | O(n)        |
| 검색 | O(logn) | O(logn)     |
| 삽입 | O(logn) | O(logn)     |
| 삭제 | O(logn) | O(logn)     |

### Rotation

트리의 재구성 작업을 Rotation(회전)이라고 한다.

#### LL

```
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

```

y는 z의 왼쪽 자식, x는 y의 왼쪽 자식이다. 이때 T1, T2, T3, T4는 각각의 서브트리이다.

z의 오른족 자식과 왼쪽 자식이 불균형하므로 right Rotation 한번으로 균형을 잡아줄 수 있다.

```c
if (bal > 1 && key < node->left->key) return right_rotate(node);
```



#### LR

```
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
```

y는 z의 왼쪽 자식, x는 y의 오른쪽 자식이다. 이러한 경우에는 회전을 두번시켜줘야한다. 우선 y를 왼쪽 회전을 한번 시켜주고 z를 오른쪽 회전시켜주면 균형이 잡히게 된다.

```c
if (bal > 1 && key > node->left->key){
    node->left =  left_rotate(node->left);
    return right_rotate(node);
}
```



#### RR

```
 z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
```

y는 z의 오른쪽 자식이고, x는 y의 오른쪽 자식이다. 이러한 경우는 LL과 마찬가지로 한번의 rotation으로 균형을 잡을 수 있다.

```c
if (bal < -1 && key > node->right->key) return left_rotate(node);
```



#### RL

```
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
```

y는 z의 오른쪽자식, x는 y의 왼쪽 자식이다 .이러한 경우는 위의 LR과 정 반대인 경우이다. 이 때는 오른쪽 회전 후 왼쪽 회전을 하면 균형을 맞출 수 있다.

```c
if (bal < -1 && key < node->right->key){
    node->right = right_rotate(node->right);
    return left_rotate(node);
}
```



### 구현

```c
typedef struct node{
    int key;
    struct node * left, *right;
    int height; // 높이
}Node;

Node * new_node(int key){
    Node * new = (Node *)malloc(sizeof(Node));
    new->key = key;
    new->height = 0; //새로운 노드는 기본적으로 단말 노드의 height를 가진다.
    new->left = new->right = NULL;
    return new;
}

```

#### height

```c
int height(Node * node){
    if(node == NULL) return -1;
    return node->height;
}
```

#### Right Rotation

```c
/*
         z                                      y(l) 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z(node)
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3(r) T4
    / \
  T1   T2

*/
Node * right_rotate(Node * node){
    Node * l = node->left;
    Node * r = l->right;
    
    l->right = node;
    node->left = r;
    
    node->height = 1+MAX(height(node->left),height(node->right));
    l->height = 1+MAX(height(l->left),height(l->right));
    
    return l;
}
```

#### Left Rotation

```c
/*
 z                                 y(r)
 /  \                            /     \ 
T1   y     Left Rotate(z)       z(node)  x
    /  \   - - - - - - - ->    / \      / \
   T2   x                     T1 T2(l) T3  T4
       / \
     T3  T4
*/

Node * left_rotate(Node * node){
    Node * r = node->right;
    Node * l = r->left;
    
    r->left = node;
    node->right =l;
    
    node->height = 1+MAX(height(node->left),height(node->right));
    r->height = 1+MAX(height(r->left),height(r->right));
    
    return r;
}

```

#### balance

```c
int balance(Node * node){
    if(node == NULL) return 0;
    // 양쪽 서브트리의 높이를 비교한다.
    return height(node->left)-height(node->right);
}
```

#### 삽입

위의 Rotation을 이용해서 삽입을 구현할 수 있다.

1. 우선 BST의 삽입과 같이 삽입한다.
2. 현재의 height값을 update해준다.
3. balance한지 확인한다.(-1미만 1초과 불균형)
4. 불균형하다면 LL, LR, RR, RL 의 각각의 경우에 맞게 rotation해준다.

```c
Node * insert(Node * node, int key){
    
    // 1. 먼저 Binary Search Tree의 삽입과 같이 삽입한다.
    if (node == NULL)
        return(new_node(key));
    
    if (key < node->key)node->left  = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node; //값이 같은 경우에는 BST의 삽입과 같지 않고 바로 리턴해준다.
    
    // 2. height값을 변경해준다.
    node->height = 1 + MAX(height(node->left),height(node->right));
    
    // 3. balance한지 확인을 한다.(-1미만 1초과면 불균형)
    int bal = balance(node);
    
    // 4. 불균형한 경우에 rotation!
    // LL
    if (bal > 1 && key < node->left->key) return right_rotate(node);
    
    // RR
    if (bal < -1 && key > node->right->key) return left_rotate(node);
    
    // LR 두번회전(left->right)
    if (bal > 1 && key > node->left->key){
        node->left =  left_rotate(node->left);
        return right_rotate(node);
    }
    
    // RL
    if (bal < -1 && key < node->right->key){
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;
}
```

#### 삭제

1. 우선 BST의 삭제와 같이 삭제하다.
2. 현재 노드는 반드시 삭제노드의 조상노드 중 하나여야한다.
3. 현재의 height값을 update해준다.
4. balance한지 확인한다.(-1미만 1초과 불균형)
5. 불균형하다면 LL, LR, RR, RL 의 각각의 경우에 맞게 rotation해준다. 

```c
Node* delete(Node* root, int key){
    Node * tmp;
    
    // 1. BST 삭제
    if (root == NULL) return root;
    if ( key < root->key )root->left = delete(root->left, key);
    else if( key > root->key ) root->right = delete(root->right, key);
    else{// 키값이 같으면 그 노드를 삭제
        if(root->left == NULL || root->right == NULL){
            if(root->left!=NULL)tmp = root->left;
            else tmp =root->right;
            
            // 자식이 없는 경우
            if (tmp == NULL){
                tmp = root;
                root = NULL;
            }
            else *root = *tmp; // 자식이 한개인 경우
            
            free(tmp);
        }else{//자식이 두개인 경우
            
            tmp = min(root->right);
            root->key = tmp->key;
            root->right = delete(root->right, tmp->key);
        }
    }
    
    // 삭제 후에 root가 NULL인경우
    if (root == NULL) return root;
    
    // 현재 height를 update해준다.
    root->height = 1 + MAX(height(root->left),height(root->right));
    
    // balance 값을 가져온다.
    int bal = balance(root);
    
    // 불규칙한 경우
    // LL
    if (bal > 1 && balance(root->left) >= 0)
        return right_rotate(root);
    
    // LR
    if (bal > 1 && balance(root->left) < 0){
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }
    
    // RR
    if (bal < -1 && balance(root->right) <= 0)
        return left_rotate(root);
    
    // RL
    if (bal < -1 && balance(root->right) > 0){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}
```

