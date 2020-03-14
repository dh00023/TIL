# Array, Struct, Pointer

배열, 구조체, 포인터에 대해서 알아보자.

## 배열(Array)

**배열**(array)은 같은 형의 변수를 여러개 만드는 경우에 사용한다. 모든 자료형에 대해서 배열로 구성이 가능하다.

```c
int array[n];		//1차원 배열
int array2[n][m];	//2차원 배열
int array3[n][m][l];//3차원 배열
```

이때 index는 0부터 n-1까지로 배열요소를 구별하기 위해서 사용된다.



## 포인터(Pointer)

포인터는 다른 변수의 주소를 가지고 있는 변수이다.

```c
int i;
int *ptr = &i;
```

포인터의 엑세스 범위는 포인터 변수로 선언된 자료형(char, short, int...)에 따라 다르다.

- `&` 연산자 : 변수의 주소를 추출
- `*` 연산자 : 포인터가 가리키는 곳의 내용을 추출한다.

```
p			//포인터
*p			//포인터가 가리키는 값
*p++		//포인터가 가리키는 값을 가져온 후, 포인터 한칸 증가
*p--		//포인터가 가리키는 값을 가져온 후, 포인터 한칸 감소
(*p)++		//포인터가 가리키는 값 증가
```

연산자의 우선순위를 주의해서 사용해야한다.

## 배열과 포인터

배열의 이름은 사실상 포인터와 같은 역할을 한다. 컴파일러가 배열의 이름을 배열의 첫번째 주소로 대치한다.

### 주의할 점

- 포인터가 아무것도 가리키고 있지 않을 때는 **NULL**로 설정해야한다.
- 초기화가 안된 상태에서 사용하면 안된다.

### 메모리 할당

- 정적 메모리 할당 : 일반 변수, 배열
  - 프로그램이 시작하기 전에 메모리 크기가 결정된다.
  - 프로그램 수행 도중에 그 크기가 변경될 수 없다.
- **동적 메모리 할당** 
  - 프로그램 실행 도중에 메모리를 할당 받는 것이다.
  - 필요한 만큼만 할당을 받아 사용하고 반납한다.
  - 메모리를 매우 효율적으로 사용가능하다.

## 구조체(Structure)

배열과 다르게 **타입이 다른** 데이터를 하나로 묶는 방법이다.

- 구조체 선언 : 내부 구조를 정의

```c
struct 구조체이름{
    자료형 항목1;
    자료형 항목2;
    ...
};
```

- 구조체 변수 선언

```c
struct 구조체이름 구조체변수명;
```

### 구조체 선언과 사용

- 구조체형을 선언한 후에 구조체 변수 선언

```c
struct employee{
    char name[10];
    int year;
    int pay;
};

struct employee Lee, Kim, Park;
```

- 구조체형과 구조체 변수를 연결해 사용

```c
struct employee{
    char name[10];
    int year;
    int pay;
}Lee;
```

- 구조체형 이름을 생략하고 구조체 변수 이름만 선언

```c
struct{
    char name[10];
    int year;
    int pay;
}Lee;
```

- **typedef**이용

```c
typedef struct employee{
    char name[10];
    int year;
    int pay;
}Employee;

Employee Lee,Kim;
```

###  초기화

내부 항목의 자료형과 개수를 순서에 맞추어 `{}`를 사용해 지정한다.

```c
struc employee Lee = {"Ann",2018,4200};
```

### 멤버 변수 지정

구조체 멤버 변수에 개별적으로 접근

- 일반변수 : `.`
- 포인터변수 : `->`

```c
struct employee Lee;
Lee.name = "Ann";
Lee.year = 2015;

struct employee *sptr = &Kim;
//sptr->name = "Lion";
//배열로 선언된 변수에 string은 대입 불가능하다.
(*sptr).name = "Lion";
sptr->year = 2014;
```

### 자기참조 구조체

멤버 중에 **자기 자신을 가리키는 포인터가 한 개 이상 존재**하는 구조체이다.

```c
typedef struct list{
    int data;
    struct list *next;
}List;
```



## 실습

### 다항식

#### 다항식의 모든 항을 배열에 저장

- 모든 차수의 계수 값을 배열로 저장한다.
- 하나의 다항식을 하나의 배열로 표현한다.
- 장점 : 다항식의 각종 연산이 간단해진다.
- 단점 : 대부분의 항의 계수가 0이면 공간 낭비가 심해진다.

```c
#include <stdio.h>
#define MAX 100

//다항식의 모든항을 저장!
typedef struct poly{
    int degree;     //최고차수
    int coef[MAX];    //다항식 계수
}Poly;

void create_poly(Poly *);
void print_poly(Poly);
Poly add_poly(Poly , Poly);

Poly p1,p2,p3;


int main(){
    create_poly(&p1);
    print_poly(p1);
    create_poly(&p2);
    print_poly(p2);
    p3=add_poly(p1, p2);
    print_poly(p3);
}


void create_poly(Poly *p){
    
    int degree, coef;
    
    printf("항의 수를 입력하세요\n");
    scanf("%d",&degree);
    
    (*p).degree = degree;
    
    printf("차수의 계수를 차례대로 입력하세요.(내림차순)\n");
    while(degree--){
        printf("%d의 계수 : ",degree);
        scanf("%d",&coef);
        (*p).coef[degree] = coef;
    }
    
}

void print_poly(Poly p){
    for(int i=p.degree-1;i>0;i--){
        printf("%dx^%d + ",p.coef[i],i);
    }
    printf("%d\n",p.coef[0]);
}

Poly add_poly(Poly p1, Poly p2){
    Poly p3;
    int i1=0,i2=0,i3=0;
    int degree1=p1.degree, degree2=p2.degree;
    
    while(i1<=degree1||i2<=degree2){
        if(i1>i2){
            p3.coef[i3++]=p1.coef[i1++];
        }else if(i1==i2){
            p3.coef[i3++]=p1.coef[i1++]+p2.coef[i2++];
        }else{
            p3.coef[i3++]=p2.coef[i2++];
        }
    }
    
    p3.degree = --i3;
    
    
    return p3;
}

```



#### 다항식의 0이 아닌 항만을 저장(ver.구조체배열)

- (계수, 차수) 형식으로 배열에 저장한다.
- 하나의 배열로 여러 개의 다항식을 나타낼 수 있다.(하지만 각각 배열을 따로 구현할 것임.)
- 장점 : 메모리 공간 사용이 효율적이다.
- 단점 : 다항식의 연산들이 복잡해진다. (차수에 대한 조건처리)

```c
#include <stdio.h>

struct poly
{
    int coef; // 계수
    int expo; // 차수
};

/*
 두개의 다항식 a와 b, 그리고 연산의 결과를 저장할 p3배열 선언
 이때, 최고차항은 10으로 했다.
 */
struct poly p1[10],p2[10],p3[10];

int inputPoly(struct poly []); // 다항식의 계수와 차수의 값을 입력하는 함수
int addPoly(struct poly [],struct poly [],int ,int ,struct poly []); // 다항식 더하기연산
int minusPoly(struct poly [],struct poly [],int ,int ,struct poly []); // 다항식 뺄셈연산
void displayPoly( struct poly [],int total); // 다항식 연산 결과값을 보여주는 함수

int main()
{
    int total1,total2,total3; // 다항식 p1, p2, p3의 총 차수의 갯수
    
    printf("첫번째 ");
    total1=inputPoly(p1);
    printf("첫번째 다항식 : ");
    displayPoly(p1,total1);
    
    printf("두번째 ");
    total2=inputPoly(p2);
    printf("두번째 다항식 : ");
    displayPoly(p2,total2);
    
    
    total3=addPoly(p1,p2,total1,total2,p3);
    printf("\n덧셈 결과 다항식 : ");
    displayPoly(p3,total3);
    
    total3=minusPoly(p1,p2,total1,total2,p3);
    printf("\n뺄셈 결과 다항식 : ");
    displayPoly(p3,total3);
    
    return 0;
}

int inputPoly(struct poly p[10])
{
    int total,i;
    
    printf("다항식의 총 수를 입력하세요 :");
    scanf("%d",&total);
    
    printf("\n높은 차수부터 낮은 차수로 차례대로 차수와 계수를 입력하세요.\n");
    for(i=0;i<total;i++)
    {
        printf("%d번째 차수: ",i+1);
        scanf("%d",&p[i].expo);
        printf("%d번째 차수의 계수: ",i+1);
        scanf("%d",&p[i].coef);
        
    }
    return(total);
}

int addPoly(struct poly p1[10],struct poly p2[10],int total1,int total2,struct poly p3[10])
{
    
    int i=0,j=0,k=0;
    
    while(i<total1 && j<total2)
    {
        
        if(p1[i].expo==p2[j].expo){
            // p1과 p2의 차수가 같은 경우
            p3[k].coef=p1[i].coef + p2[j].coef;
            p3[k].expo=p1[i].expo;
            
            i++;j++;k++;
        }
        // p1의 차수가 p2보다 큰 경우
        else if(p1[i].expo>p2[j].expo){
            p3[k].coef=p1[i].coef;
            p3[k].expo=p1[i].expo;
            i++;k++;
        }
        // p1의 차수가 p2보다 작은 경우
        else{
            p3[k].coef=p2[j].coef;
            p3[k].expo=p2[j].expo;
            j++;k++;
        }
    }
    
    // p1의 차수의 갯수가 p2보다 많은경우
    while(i<total1){
        p3[k].coef=p1[i].coef;
        p3[k].expo=p1[i].expo;
        i++;k++;
    }
    // p2의 차수의 갯수가 p1보다 많은경우
    while(j<total2){
        p3[k].coef=p2[j].coef;
        p3[k].expo=p2[j].expo;
        j++;k++;
    }
    
    return(k); // 결과 다항식의 차수의 갯수
}

int minusPoly(struct poly p1[10],struct poly p2[10],int total1,int total2,struct poly p3[10])
{
    
    int i=0,j=0,k=0;
    
    while(i<total1 && j<total2)
    {
        
        if(p1[i].expo==p2[j].expo){
            // p1과 p2의 차수가 같은 경우
            p3[k].coef=p1[i].coef - p2[j].coef;
            p3[k].expo=p1[i].expo;
            
            i++;j++;k++;
        }
        // p1의 차수가 p2보다 큰 경우
        else if(p1[i].expo>p2[j].expo){
            p3[k].coef=p1[i].coef;
            p3[k].expo=p1[i].expo;
            i++;k++;
        }
        // p1의 차수가 p2보다 작은 경우
        else{
            p3[k].coef=-p2[j].coef;
            p3[k].expo=p2[j].expo;
            j++;k++;
        }
    }
    
    // p1의 차수의 갯수가 p2보다 많은경우
    while(i<total1){
        p3[k].coef=p1[i].coef;
        p3[k].expo=p1[i].expo;
        i++;k++;
    }
    // p2의 차수의 갯수가 p1보다 많은경우
    while(j<total2){
        p3[k].coef=-p2[j].coef;
        p3[k].expo=p2[j].expo;
        j++;k++;
    }
    
    return(k); // 결과 다항식의 차수의 갯수
}

void displayPoly(struct poly p[10],int total)
{
    for(int k=0;k<total-1;k++)
        printf("%d(x^%d)+",p[k].coef,p[k].expo);
    printf("%d(x^%d)\n\n",p[total-1].coef,p[total-1].expo);
}
```

#### 다항식의 0이 아닌 항만을 저장(ver.List)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int coef;   //계수
    int exp;    //차수
    struct node * next;
}Node;

Node * new_node(int coef,int exp){
    Node * new = (Node *)malloc(sizeof(Node));
    new->coef = coef;
    new->exp = exp;
    new->next = NULL;
    return new;
}


void create_poly(Node **head,int coef, int exp){
    Node * p = *head;
    
    if(p==NULL){
        p=new_node(coef,exp);
        *head = p;
    }else{
        while(p->next!=NULL)
            p=p->next;
        Node * new =new_node(coef,exp);
        p->next = new;
    }
}

void add_first(Node **head,int coef,int exp){
    Node * new = new_node(coef,exp);
    new->next = *head;
    *head = new;
}
void add_last(Node **tail,int coef,int exp){
    Node * p =*tail;
    
    Node * new = new_node(coef,exp);
    p->next = new;
    *tail = new;
}
void add(Node *head, int coef, int exp){
    Node *p = head;
    
    while(p->next!=NULL&&p->next->exp>=exp)
        p=p->next;
    
    if(p->exp == exp){
        printf("계수(%d)는 이미 존재합니다.\n",exp);
        return;
    }
    
    Node * new = new_node(coef,exp);
    new->next = p->next;
    p->next = new;
}
void print_poly(Node *head){
    
    Node *p =head;
    
    while(p!=NULL){
        printf("(%d)x^%d",p->coef,p->exp);
        if(p->next!=NULL)printf(" + ");
        p=p->next;
    }
    printf("\n\n");
}


void input_poly(Node **head,Node **tail){
    
    Node *p = *head;
    
    int coef, exp;
    
    while(1){
        printf("계수와 차수를 차례대로 입력해주세요.(0 0은 종료) : ");
        scanf("%d %d",&coef,&exp);
        
        if(!(coef||exp))break;
        
        if(p==NULL){
            p=new_node(coef,exp);
            (*head)=(*tail)=p;
        }else{
            while(p->next!=NULL)
                p=p->next;
            if(exp>(*head)->exp)add_first(head, coef, exp);
            else if(exp<(*tail)->exp)add_last(tail, coef, exp);
            else add(*head, coef, exp);
        }
//        print_poly(*head);
    }
    
}

void add_poly(Node * head, Node *head2, Node **p3){
    Node * p1 = head;
    Node * p2 = head2;
    
    while(p1&&p2 != NULL){
        if(p1->exp==p2->exp){
            create_poly(p3,p1->coef+p2->coef,p1->exp);
            p1=p1->next;p2=p2->next;
        }else if(p1->exp>p2->exp){
            create_poly(p3,p1->coef,p1->exp);
            p1=p1->next;
        }else{
            create_poly(p3,p2->coef,p2->exp);
            p2=p2->next;
        }
    }
    while(p1 != NULL){
        create_poly(p3,p1->coef,p1->exp);
        p1=p1->next;
    }
    while(p2 != NULL){
        create_poly(p3,p2->coef,p2->exp);
        p2=p2->next;
    }
}

void minus_poly(Node * head, Node *head2, Node **p3){
    Node * p1 = head;
    Node * p2 = head2;
    
    while(p1&&p2 != NULL){
        if(p1->exp==p2->exp){
            create_poly(p3,p1->coef-p2->coef,p1->exp);
            p1=p1->next;p2=p2->next;
        }else if(p1->exp>p2->exp){
            create_poly(p3,p1->coef,p1->exp);
            p1=p1->next;
        }else{
            create_poly(p3,-p2->coef,p2->exp);
            p2=p2->next;
        }
    }
    while(p1 != NULL){
        create_poly(p3,p1->coef,p1->exp);
        p1=p1->next;
    }
    while(p2 != NULL){
        create_poly(p3,-p2->coef,p2->exp);
        p2=p2->next;
    }
}

int main(){
    Node *head=NULL, *tail=NULL;
    Node *head2=NULL, *tail2=NULL;
    Node *head3=NULL, *head4=NULL;
    
    input_poly(&head, &tail);
    print_poly(head);
    
    input_poly(&head2, &tail2);
    print_poly(head2);
    
    print_poly(head);
    print_poly(head2);
    add_poly(head,head2, &head3);
    minus_poly(head,head2, &head4);
    print_poly(head3);
    print_poly(head4);
    
}
```

### 희소행렬

희소 행렬은 대부분의 항들이 0인 행렬이다.

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/dbbd270e3e174daa36d9c2460211fe6f8569c0e6)

#### 2차원 배열을 이용하여 배열의 전체 요소 저장

- 장점 : 행렬의 연산을 간단하게 구현할 수 있다.
- 단점 : 메모리 공간 낭비

```c
//
//  sparse1.c
//  test
//
//  Created by dahye Jeong on 2018. 4. 2..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include <stdio.h>

#define ROWS 4
#define COLS 5

// 희소 행렬 덧셈 함수
void add_sparse(int A[ROWS][COLS],
                        int B[ROWS][COLS], int C[ROWS][COLS]) {
    int r,c;
    for(r=0;r<ROWS;r++)
        for(c=0;c<COLS;c++)
            C[r][c] = A[r][c] + B[r][c];
}

// 희소 행렬 덧셈 함수
void minus_sparse(int A[ROWS][COLS],
                        int B[ROWS][COLS], int C[ROWS][COLS]) {
    int r,c;
    for(r=0;r<ROWS;r++)
        for(c=0;c<COLS;c++)
            C[r][c] = A[r][c] - B[r][c];
}


// 희소 행렬 출력 함수
void print_matrix(int C[ROWS][COLS]){
    int r,c;
    for(r=0;r<ROWS;r++){
        for(c=0;c<COLS;c++){
            printf("%d ",C[r][c]);
        }
        printf("\n");
    }
}

int main2()
{
    int array1[ROWS][COLS] = {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };
    int array2[ROWS][COLS] = {
        {1 , 0 , 5 , 0 , 4 },
        {0 , 0 , 0 , 5 , 0 },
        {0 , 3 , 0 , 0 , 0 },
        {0 , 2 , 2 , 0 , 0 }
    };
    
    int array3[ROWS][COLS];
    add_sparse(array1,array2,array3);
    printf("희소행렬 덧셈 결과 \n\n");
    print_matrix(array3);
    
    minus_sparse(array1,array2,array3);
    printf("\n\n희소행렬 뺄셈 결과\n\n");
    print_matrix(array3);
    return 0;
}
```

#### 0이 아닌 요소들만 저장([LIST 바로가기](https://dh00023.github.io/algorithm/ds/2018/04/23/algorithm-8/))

- 장점 : 메모리 공간 절약
- 각종 행렬 연산들이 복잡해진다.

```c
#include <stdio.h>
#include <stdlib.h>
#define ROWS 4
#define COLS 5
typedef struct node{
    int row;
    int col;
    int data;
    struct node * next;
}Node;

Node * new_node(int data,int row, int col){
    Node * new = (Node *)malloc(sizeof(Node));
    new->row = row;
    new->col = col;
    new->data = data;
    new->next = NULL;
    return new;
}

void create_sparse(Node ** head,int arr[ROWS][COLS]){
    Node * p = *head;
    
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(arr[i][j]!=0){
                if(p==NULL){
                    p=new_node(arr[i][j],i, j);
                    *head = p;
                }else{
                    while(p->next!=NULL)
                        p=p->next;
                    Node * new = new_node(arr[i][j],i,j);
                    p->next = new;
                }
            }
}
void result_sparse(Node ** head,int data,int row, int col){
    Node * p = *head;
    
    if(p==NULL){
        p=new_node(data,row, col);
        *head = p;
    }else{
        while(p->next!=NULL)
            p=p->next;
        Node * new = new_node(data,row, col);
        p->next = new;
    }
}


int print_sparse(Node *head){
    int i=0;
    
    Node *p =head;
    
    while(p!=NULL){
        printf("arr[%d][%d] : %d \n",p->row,p->col,p->data);
        i++;
        p=p->next;
    }
    printf("\n\n");
    return i;
}

void plus_sparse(Node *head, Node *head2, Node **head3){
    Node * arr1 = head, *arr2 = head2;
    
    while(arr1&&arr2!=NULL){
        if(arr1->row==arr2->row){
            if(arr1->col < arr2->col){
                result_sparse(head3,arr1->data,arr1->row,arr1->col);
                arr1=arr1->next;
            }else if(arr1->col > arr2->col){
                result_sparse(head3,arr2->data,arr2->row,arr2->col);
                arr2=arr2->next;
            }else{
                result_sparse(head3,arr1->data+arr2->data,arr1->row,arr1->col);
                arr1=arr1->next;
                arr2=arr2->next;
            }
        }else if(arr1->row<arr2->row){
            result_sparse(head3,arr1->data,arr1->row,arr1->col);
            arr1=arr1->next;
        }else{
            result_sparse(head3,arr2->data,arr2->row,arr2->col);
            arr2=arr2->next;
        }
    }
    while(arr1!=NULL){
        result_sparse(head3,arr1->data,arr1->row,arr1->col);
        arr1=arr1->next;
    }
    while(arr2!=NULL){
        result_sparse(head3,arr2->data,arr2->row,arr2->col);
        arr2=arr2->next;
    }
}
void minus_sparse(Node *head, Node *head2, Node **head3){
    Node * arr1 = head, *arr2 = head2;
    
    while(arr1&&arr2!=NULL){
        if(arr1->row==arr2->row){
            if(arr1->col < arr2->col){
                result_sparse(head3,arr1->data,arr1->row,arr1->col);
                arr1=arr1->next;
            }else if(arr1->col > arr2->col){
                result_sparse(head3,-arr2->data,arr2->row,arr2->col);
                arr2=arr2->next;
            }else{
                result_sparse(head3,arr1->data-arr2->data,arr1->row,arr1->col);
                arr1=arr1->next;
                arr2=arr2->next;
            }
        }else if(arr1->row<arr2->row){
            result_sparse(head3,arr1->data,arr1->row,arr1->col);
            arr1=arr1->next;
        }else{
            result_sparse(head3,-arr2->data,arr2->row,arr2->col);
            arr2=arr2->next;
        }
    }
    while(arr1!=NULL){
        result_sparse(head3,arr1->data,arr1->row,arr1->col);
        arr1=arr1->next;
    }
    while(arr2!=NULL){
        result_sparse(head3,arr2->data,arr2->row,arr2->col);
        arr2=arr2->next;
    }
}
int main(){
    Node *head=NULL, *head2=NULL , *head3=NULL, *head4=NULL;
    int array1[ROWS][COLS] = {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };
    int array2[ROWS][COLS] = {
        {1 , 0 , 5 , 0 , 4 },
        {0 , 0 , 0 , 5 , 0 },
        {0 , 3 , 0 , 0 , 0 },
        {0 , 2 , 2 , 0 , 0 }
    };
    
    
    create_sparse(&head, array1);
    print_sparse(head);
    
    create_sparse(&head2, array2);
    print_sparse(head2);
    
    plus_sparse(head, head2, &head3);
    print_sparse(head3);
    
    minus_sparse(head, head2, &head4);
    print_sparse(head4);
}
```

이 실습으로 메모리 공간은 낭비되더라도 구현시간이 더 간단한 방법1을 사용하는 것이 더 좋다는 것을 알 수 있다.
또한, 다항식연산 문제는 Sorted List로 희소행렬 문제와 유사하게 구현할 수 있다.