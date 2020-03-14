# List

리스트란 **순서**를 가진 항목들의 모임이다. 

#### 리스트 연산

- 새로운 항목을 리스트의 처음, 중간, 끝에 **추가**
- 기존의 항목 or 모든 항목 **삭제**
- 기존 항목 **변경**(대치)
- 특정 항목을 가지고 있는지 **검색**
- 특정위치 항목 **반환**
- **리스트 길이**
- 리스트가 **비었는지 찼는지**
- 모든 항목 **출력**



### 리스트 구현 방법

#### 순차적인 배열을 이용

![img](https://cdncontribute.geeksforgeeks.org/wp-content/uploads/Arrays-1.png)

- 구현이 간단하다.
- 삽입 또는 삭제 시 오버헤드가 발생할 수 있다.
- 항목의 개수가 제한된다.

이때 1차원 배열에 항목들을 순서대로 저장해 리스트를 구현한다. 삽입 / 삭제시 항목들을 이동해야한다.

- 이동횟수 = 마지막 원소 인덱스 - 삽입할 자리 인덱스 +1



#### 연결리스트를 이용

![](https://cdncontribute.geeksforgeeks.org/wp-content/uploads/Linkedlist-2.png)

하나의 노드가 데이터와 링크로 구성되어있고 링크가 노드를 연결하는 형태로 구현한다.

- 노드(node ) = 데이터필드 + 링크필드
  - 데이터 필드 : 리스트의 원소, 즉 데이터 값을 저장하는 곳
  - 링크 필드 : 다른 노드의 주소값을 저장하는 장소(포인터)

이때 메모리안에서의 노드의 물리적 순서가 리스트의 논리적 순서와 일치할 필요는 없다.

- Head pointer : 리스트의 첫 번째 노드를 가리키는 변수
- Tail : 리스트의 마지막 노드를 가리키는 변수

#### 장점

1. 삽입, 삭제가 효율적이다.
2. 연속된 메모리 공간이 필요없다.
3. 크기 제한이 없다.

#### 단점

1. 구현이 어렵다.
2. 오류가 발생하기 쉽다.



## 연결리스트 종류

<h3 id="singleLinkedList"> 단순 연결 리스트</h3>

- 하나의 링크 필드를 이용해서 연결한 리스트이다.
- 마지막 노드의 링크 값을 NULL

#### 삽입

- 맨 앞에 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2013/03/Linkedlist_insert_at_start.png)

```c
void add_first(Node **head, int data){
    Node *p = new_node();
    p->data = data;
    p->next = *head;
    *head = p;
}
```

- 중간에 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2013/03/Linkedlist_insert_middle.png)

```c
void add(Node *head, Node *tail, int data){
    Node *p = head;
    Node *new = NULL;
    while(p->next->data <= data && p->next!=NULL)
        p=p->next;
    
    if(p->data == data){
        printf("이미 존재하는 데이터 입니다.");
        return;
    }
    new = new_node();
    new->next = p->next;
    new->data = data;
    p->next = new;
}
```



- 마지막에 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2013/03/Linkedlist_insert_last.png)

```c
void add_last(Node **tail, int data){
    Node *new = new_node();
    Node *p = *tail;
    
    new->data = data;
    new->next = NULL;
    p->next = new;
    *tail = new;
}
```

- 삽입

```c
void create_list(Node **head,Node **tail){
    
    Node *p = *head;
    
    int data;
    
    while(1){
        printf("계수와 차수를 차례대로 입력해주세요.(0은 종료) : ");
        scanf("%d",&data);
        
        if(!data)break;
        
        if(p==NULL){
            p=new_node(data);
            (*head)=(*tail)=p;
        }else{
            while(p->next!=NULL)
                p=p->next;
            if(data<(*head)->data)add_first(head, data);
            else if(data>(*tail)->data)add_last(tail, data);
            else add(*head, data);
        }
    }
}

```

#### 삭제

- 노드 삭제

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2014/05/Linkedlist_deletion.png)

```c
void delete_node(Node **head, Node **tail, int data){
    Node *p = *head;
    Node *tmp=NULL;
    
    while(p!=NULL){
        if(p->data == data)break;
        tmp = p;
        p = p->next;
    }
    
    if(p==NULL){
        printf("리스트가 비어져있거나 삭제하고 싶은 데이터(%d)가 존재하지 않습니다.\n",data);
        return;
    }
    
    if( p == *head ){
        
        *head = p->next;
        free(p);
        return;
    }
    tmp->next = p->next;
    free(p);
    if(tmp->next==NULL) *tail = tmp;
    printf("데이터(%d)를 리스트에서 삭제했습니다. \n",data);
}

```

- 전체삭제

```c
void delete_list(Node **head){
    Node *p = *head;
    Node *tmp = NULL;
    
    while(p!=NULL){
        tmp=p->next;
        free(p);
        p=tmp;
    }
    *head = NULL;
}
```

#### 출력

```c
int print_node(Node *head){
    Node *p = head;
    int i=0;
    
    while(p!=NULL){
        i++;
        printf("[%d] : %d ",i,p->data);
        p=p->next;
    }
    printf("\n\n");
    return i;
}
```



#### 수정

```c
void edit_node(Node **head,int before,int after){
    Node *p = *head;
    while(p!=NULL){
        if(p->data==before){
            p->data=after;
            return;
        }
    }
    printf("리스트가 비어져있거나 변경하고 싶은 데이터가 없습니다.\n");
}
```



### 원형 연결 리스트

![](https://cdncontribute.geeksforgeeks.org/wp-content/uploads/CircularLinkeList.png)

원형 연결 리스트는 마지막 노드의 링크가 첫 번째 노드를 가리키는 리스트이다. 하나의 노드에서 다른 모든 노드로의 접근이 가능해진다.

보통 **헤드포인터가 마지막 노드를 가리키게 구성**하면 리스트의 처음이나 마지막에 노드를 삽입하는 연산이 매우 간단해진다.

#### 삽입

다른 연산은 단순 연결 리스트와 같다.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

Node *new_node(int data){
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;
    
    return new;
}

/*
 * p->next = p;
 * new->next = head
 */
// 원형에서는 현재 가리키고 있는 head의 위치가 마지막 노드이며, head->next는 맨 앞노드를 가리킨다.

int insert_node(Node *head, int data){
    Node *p = NULL, *new;
    p=head;
    
    while(p->next->data <=  data )
        p=p->next;
    
    if(data == p->data){
        printf("이미 존재하는 데이터입니다.\n");
        return 0;
    }

    new = new_node(data);
    
    new->next = p->next;
    p->next = new;
    
    return 1;
}

int push_back(Node **head, int data){
    Node * new = new_node(data);
    Node * p = *head;
    
    if(p->data == data){
        printf("이미 존재하는 데이터입니다.\n");
        return 0;
    }
    
    new->next = p->next;
    p->next = new;
    
    (*head)=new;
    return 1;
}

void create_node(Node **head){
    
    Node *p = NULL;
    int data,i=0,j=0;
    
    
    while(1){
        printf("삽입할 데이터를 입력해주세요: (종료는 0)");
        scanf("%d",&data);
        if(!data)break;
        if(p==NULL){
            p=new_node(data);
            p->next = p;
            *head = p;
            i++;
        }else{
            p=*head;
            if (data >= (*head)->data) j=push_back(head,data);
            else j=insert_node(*head, data);
        }
        i+=j;
    }
    return i;
    
}

```
여기서 head 포인터가 마지막 노드를 가리키게 만들어서 삽입 함수를 더 간단하게 구현하였다.

#### 출력

```c
//보여줄때는 length를 보내줘서 몇개의 노드가 있는지 받은 후에 돌려야한다.
void show_node(Node *head, int length){
    Node *p = head->next;
    int i;
    for(i=0;i<length;i++){
        printf("[%d] : %d\n",i+1,p->data);
        p=p->next;
    }
}
```

#### 삭제

```c
void delete_node(Node **head,int data){
    Node *p = (*head)->next , *tmp=NULL;
    
    
    if(p==NULL){
        printf("비어있는 스택입니다.\n");
        return;
    }
    
    while(p->data!=data){
        tmp = p;
        p=p->next;
    }
    
    if(p==(*head)->next){
        if(p->data==data&&)tmp=(*head);
        else{
            printf("찾는 데이터가 없습니다.\n");
            return;
        }
    }
    
    tmp->next = p->next;
    if(p==*head)*head = tmp;
    free(p);
    count--;
}

void delete_list(Node **head){
    Node *p = *head ,*tmp=NULL;
    
    while(p->next!=*head){
        tmp = p;
        free(p);
        count--;
        p=tmp->next;
    }

    free(p);

    (*head)=NULL;
}
```



<h3 id="doubleLinkedList">이중 연결 리스트</h3>

![dll](https://www.geeksforgeeks.org/wp-content/uploads/gq/2014/03/DLL1.png)

단순 연결 리스트는 선행 노드(prev)를 찾기 힘든 단점이 있다. 삽입 또는 삭제 시에는 반드시 선행 노드가 필요하다.

이중 연결 리스트는 하나의 노드가 **선행 노드와 후속 노드에 대한 두 개의 링크를 가지는 리스트**이다. 링크가 양방향이므로 양방향 검색이 가능하다.

- 단점
  - 이전 노드를 지정하기 위해 변수를 하나 더 사용해야하므로 그만큼 메모리를 더 많이 사용한다.
  - 구현이 복잡해진다.
- 헤드노드 : 데이터를 가지지 않고 단지 삽입, 삭제 코드를 간단한게 할 목적으로 사용한다.(헤드 포인터와 구별이 필요하다.)

#### 노드 구조체 멤버

```c
typedef struct node{
    int data;
    struct node * prev;
    struct node * next;
}Node;
```

#### 삽입

- 맨 앞 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2014/03/DLL_add_front1.png)

```c
void add_first(Node **head, int data){
    Node *p = new_node();
    p->data = data;
    p->next = *head;
    p->prev = NULL;
    (*head)->prev = p;
    *head = p;
}
```



- 중간 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2014/03/DLL_add_middle1.png)

```c
//리스트의 중간에 추가
void add(Node *head, Node *tail, int data){
    Node *p = head;
    Node *new = NULL;
    while(p->next->data <= data)
        p=p->next;
    
    if(p->data == data){
        printf("이미 존재하는 데이터 입니다.\n");
        return;
    }
    new = new_node();
    new->next = p->next;
    new->data = data;
    new->prev = p;
    p->next->prev = new;
    p->next = new;
}
```



- 맨 뒤 삽입

![](https://www.geeksforgeeks.org/wp-content/uploads/gq/2014/03/DLL_add_end1.png)

```c
// 리스트의 끝에 추가
void add_last(Node **tail, int data){
    Node *new = new_node();
    Node *p = *tail;
    
    new->data = data;
    new->next = NULL;
    new->prev = p;
    p->next = new;
    *tail = new;
}
```

#### 삭제

![](https://codeforwin.org/wp-content/uploads/2015/10/deletion-of-a-node.png)

```c
void delete_node(Node **head, Node **tail, int data){
    Node *p = *head;
    Node *tmp=NULL;
    
    while(p!=NULL){
        if(p->data == data)break;
        tmp = p;
        p = p->next;
    }
    
    if(p==NULL){
        printf("리스트가 비어져있거나 삭제하고 싶은 데이터(%d)가 존재하지 않습니다.\n",data);
        return;
    }
    
    if( p == *head ){
        *head = p->next;
        p->next->prev = NULL;
        free(p);
        return;
    }
    
    if(p==*tail){
        (*tail)=tmp;
        tmp->next=NULL;
        free(p);
        return;
    }
    
    tmp->next = p->next;
    p->next->prev = tmp;
    free(p);
    printf("데이터(%d)를 리스트에서 삭제했습니다. \n",data);
}
```


#### 출력

```c
//오름차순
int print_node(Node *head){
    Node *p = head;
    int i=0;
    
    while(p!=NULL){
        printf("[%d] : %d ",i,p->data);
        p=p->next;
        i++;
    }
    printf("\n\n");
    return i;
}
//내림차순
int print_node2(Node *tail){
    Node *p = tail;
    int i=0;
    
    while(p!=NULL){
        printf("[%d] : %d ",i,p->data);
        p=p->prev;
        i++;
    }
    printf("\n\n");
    return i;
}
```



