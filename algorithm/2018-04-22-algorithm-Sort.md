# Sort

**정렬**이란 물건을 크기 순으로 **오름차순이나 내림차순으로 나열**한 것이다.

- 단순하지만 비효율적 : 삽입, 선택, 버블 정렬
- 복잡하지만 효율적 : 퀵, 히프, 합병, 기수 정렬

### 선택정렬(selection sort)

**가장 작은 데이터를 선택**해 맨 앞에 있는 데이터와 바꾸고, 그 다음 작은 데이터를 선택해 앞에서 두 번째 데이터와 바꾸는 과정을 반복하는 방법

![](https://www.safaribooksonline.com/library/view/learning-functional-data/9781785888731/graphics/image_13_007-1.jpg)

1. 주어진 리스트 중에 최솟값을 찾는다.
2. 그 값을 맨 앞에 위치한 값과 교체한다(패스(pass)).
3. 맨 처음 위치를 뺀 나머지 리스트를 같은 방법으로 교체한다.

```c
void selection_sort(int list[], int n){
    int i, j, least,tmp;
    
    for(i=0;i<n-1;i++){
        least = i;
        for(j=i+1;j<n;j++){
            if(list[j]<list[least]){
                least = j;
            }
            SWAP(list[i],list[j],tmp);
        }
    }
}
```

```python
array = [7,5,9,0,3,1,6,2,4,8]



for i in range(0,len(array)-1):
    min = i;
    for j in range(i+1,len(array)):
        if array[j] < array[min]:
            min = j;

    array[i], array[min] = array[min], array[i];
    print(array)

```

비교하는 것이 상수 시간에 이루어진다는 가정 아래, n개의 주어진 리스트를 이와 같은 방법으로 정렬하는 데에는 **O(n^2) 만큼의 시간**이 걸린다. 이는 정렬해야하는 데이터 개수가 100배 늘어나면 이론적으로 수행시간은 10,000배 늘어나는 것이다.

### 삽입정렬(insertion sort)

 자료 배열의 **모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를 찾아 삽입함으로써 정렬을 완성하는 알고리즘**이다.

![](http://cfile25.uf.tistory.com/image/2569FD3854508BE8114B33)

삽입 정렬은 필요할 때만 위치를 바꾸므로 데이터가 거의 정렬되어 있을 때 훨씬 효율적이다.

```c
void insert_sort(int arr[],int n){
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i-1;
        
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}
```

```python
def insert_sort(array):
    # print(array)
    for i in range(1,len(array)):
        for j in range(i,0,-1):
            if array[j] < array[j-1]:
                array[j], array[j-1] = array[j-1], array[j]
            else:
                break
    # print(array)
    return array
```

- 복잡도 
  - 최선의 경우(이미 정렬) : O(n)
  - 최악의 경우(역순으로 정렬된 경우) : O(n^2)

보통 삽입 정렬이 퀵 정렬보다 비효율 적이나, 이미 정렬되어있는 경우에는 퀵정렬보다 더 강력하다. 따라서 거의 정렬되어 있는 상태라면, 삽입 정렬을 이용하는 것이 더 좋다.

### 버블정렬(bubble sort)

![](http://cfile5.uf.tistory.com/image/275F9A4A545095BD010D47)

인점한 2개의 레코드를 비교하여 순서대로 되어 있지 않으면 서로 교환한다.

```c
void bubble_sort(int list[], int n){
    int i,j,tmp;
    for(i=n-1;i>0;i--){
        for(j=0;j<i;j++){
            if(list[i]<list[j])SWAP(list[i], list[j], tmp);
        }
    }
}
```

- 복잡도(최상, 평균, 최악) : O(n^2)



### 합병 정렬(merge_sort)

![](https://www.geeksforgeeks.org/wp-content/uploads/Merge-Sort-Tutorial.png)



1. 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분리시트를 정렬한다.
2. 정렬된 두개의 부분 리스트를 합하여 전체 리스트를 정렬한다.

```c
void merge(int array[], int left, int mid, int right)
{
    int i, j, k, m;

    i = left;
    j = mid + 1;
    k = left;    //결과 배열의 인덱스

    int tempArray[MAX];

    //left부터 mid 까지의 블록과 mid+1부터 right까지의 블록을 서로 비교하는 부분
    while (i <= mid && j <= right) {
        if (array[i] < array[j]){   //left index 값이 right index 값보다 작으면 left index 값을 결과 result에 복사
            tempArray[k] = array[i];
            i++;
        }else{        //아니라면 right index 값을 결과 result에 복사
            tempArray[k] = array[j];
            j++;
        }
        k++;
    }

    // left 블록의 값은 다 처리되었는데 right 블록의 index가 아직 남아있을 경우
    // right index를 순차적으로 결과 result에 복사
    if (i > mid){
        for (m = j; m <= right; m++){
            tempArray[k] = array[m];
            k++;
        }
    } else {                    // left 블록의 index가 아직 남아있을 경우 left index를 순차적으로 결과 result에 복사
        for (m = i; m <= mid; m++){
            tempArray[k] = array[m];
            k++;
        }
    }

    for(m = left; m <= right; m++){
        array[m] = tempArray[m];
    }
}

void merge_sort(int array[], int left, int right)
{
    int mid;
    
    // 분할이 다 되지 않았을 경우 if 문 실행
    if(left < right){
        mid = (left + right)/2;
        
        merge_sort(array, left, mid);      //왼쪽 블록 분할
        merge_sort(array, mid+1, right);  //오른쪽 블록 분할
        merge(array, left, mid, right);   //분할된 블록 병합
    }
}
```

- 복잡도 : O(n*log(n))

### 기수정렬(Radix Sort)

![](https://2.bp.blogspot.com/-9uE2Cjc9JT4/Vz0uxpmuqoI/AAAAAAAAANI/UgEdj2oQEK8ofwZF4TkKG1Ak9EOA8Yc9gCLcB/s1600/%25EC%25BA%25A1%25EC%25B2%2598.PNG)

기수 정렬은 정수의 자리수를 기준으로 낮은 자리수부터 비교해 정렬하는 알고리즘입니다. 

예를 들어 3자리 수라면 1의자리, 10의자리 , 100의 자리 숫자를 순서대로 비교해서 정렬하는 방법입니다.

```c
void radix_sort(int a[])
{
    int i, b[MAX], m=0, exp=1;


    // m에 최대값을 저장
    for( i=0 ; i<MAX ; i++ )
    {
        if( a[i] > m )
            m = a[i];
    }

    // m의 자리수보다 exp가 커지면 종료
    while( m/exp > 0 )
    {
        int bucket[10] = {0}; //수별로 비교해서 임시로 저장해둘 공간

        for( i=0 ; i<MAX ; i++ )
            bucket[a[i]/exp%10]++;

        for( i=1 ; i<10 ; i++ )
            bucket[i] += bucket[i-1];

        for( i=MAX-1 ; i>=0 ; i-- )
            b[--bucket[a[i]/exp%10]] = a[i];

        for( i=0 ; i<MAX ; i++ )
            a[i] = b[i];

        exp *= 10; //자리수 비교가 끝나면 다음 자리수!
    }
}
```
```python

def counting_sort(arr, digit):
    n = len(arr)

    # 배열의 크기에 맞는 output 배열을 생성하고 10개의 0을 가진 count란 배열을 생성한다.
    output = [0] * n
    count = [0] * 10

    # 각 자리수에 맞게 count를 증가시켜준다.
    for i in range(0, n):
        index = int(arr[i] / digit)
        count[(index) % 10] += 1

    # count 배열에 앞의 수를 차례대로 더해 각 자릿수를 정해준다.
    # ex) 123,134,151,121
    # before : [ 0, 2, 0, 1, 1 ]
    # after : [ 0, 2, 2, 3, 4 ]
    for i in range(1, 10):
        count[i] += count[i - 1]

    # 각 자릿수 별로 output 배열에 차례대로 정렬한다.
    # ex) 1의 자리 예제
    # [ 0, 121, 0, 0]
    # [ 151, 121, 0, 0]
    # [ 151, 121, 0, 134]
    # [ 151, 121, 123, 134]
    i = n - 1
    while i >= 0:
        index = int(arr[i] / digit)
        output[count[(index) % 10] - 1] = arr[i]
        count[(index) % 10] -= 1
        i -= 1

    # arr에 output을 할당한다.
    return output


# Method to do Radix Sort
def radix_sort(arr):
    # arr 배열중에서 최대값을 가져와 자릿수를 파악한다.
    # ex) 최대값이 9833 이면 1000까지
    maximum = max(arr)
    # 자릿수마다 countingSorting을 시작한다.
    digit = 1
    while int(maximum / digit) > 0:
        arr = counting_sort(arr, digit)
        digit *= 10

    return arr

```

- 복잡도 : O(dn) d는 자릿수

### 퀵정렬(Quick sort)



![](http://cfile7.uf.tistory.com/image/271D2B3354545F7A135A7B)

1. pivot(기준값) 정하기
2. pivot보다 작은 원소들은 왼쪽, 큰 원소는 오른쪽
3. pivot을 기준으로 왼쪽 배열과 오른쪽 배열을 새로운 배열로 정하고 각 배열구간에서 1번과정 재귀적 반복
4. 일반적으로 처음 또는 마지막 원소를 pivot으로 잡는다.

```c
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        //pi = partition index
        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

```cpp
#include <algorithm>

bool compare(int a, int b){
// 오름차순   
//	return a<b;
// 내림차순
    return a>b;
}

bool comparep(POINT a, POINT b){
    if(a.x == b.x ) return a.y < b.y;
    else return a.x < b.x;
}

//처음부터 n-1번째까지 원소를 compare함수의 정의대로 정렬
//퀵정렬 기반으로 정렬한다.
//std::sort(정렬할 자료의 시작 주소, 정렬할 자료의 마지막 주소,[비교함수 주소])
std::sort(S,S+n,compare);
```

```python
def quick_sort(array):

    if len(array) <= 1:
        return

    pivot = array[0]
    temp = array[1:]

    left = [i for i in temp if i < pivot]
    right = [i for i in temp if i > pivot]

    return quick_sort(left) + [pivot] + quick_sort(right)
```

- 시간 복잡도
  - 평균적 : O(nlog(n))
  - 최악의 경우 : O(N^2)

| 데이터 수 | N^2(선택정렬, 삽입 정렬) | NlogN(퀵 정렬) |
| --------- | ------------------------ | -------------- |
| 1,000     | 약 1,000,000             | 약 10,000      |
| 1,000,000 | 약 1,000,000,000,000     | 약 20,000,000  |

다만 퀵정렬은 평균적으로 시간복잡도가 O(NlogN)이지만 최악의 경우(이미 정렬되어 있는 경우) O(N^2)인 것을 주의해야한다.

### [힙](https://dh00023.github.io/algorithm/ds/2018/06/02/algorithm-heap/) 정렬(heap sort)

1. n개의 노드에 대한 완전이진트리를 구성한다. 이때 루트 노드부터 부노드, 왼쪽 자노드, 오른쪽 자노드 순으로 구성한다.
2. **최대 힙**을 구성한다. 
3. 한번에 하나씩 요소를 힙에서 삭제하면서 저장한다.

힙 정렬이 최대로 유용한 경우는 전체 자료가 아닌 **가장 큰 값 몇개만 필요할 때**이다.

#### 구현

- 힙구현은 [힙(heap)](https://dh00023.github.io/algorithm/ds/2018/06/02/algorithm-heap/)에서 확인할 수 있다.

```c
void heap_sort(int arr[], int n){
    int i;
    Heap heap;
    init(&heap);
    
    for(i=0;i<n;i++){
        insert_max(&heap, arr[i]);
    }
    for(i=n-1;i>=0;i--){
        arr[i]=delete_max(&heap);
    }
}
```



- 복잡도
  - 힙 삭제 시간 O(logn)*n = **O(nlogn)**



### 계수 정렬(Count Sort)

계수 정렬은 **특정한 조건이 부합할 때만 사용할 수 있지만 매우 빠른 정렬 알고리즘**이다. 

모든 데이터가 양의 정수인 상황을 가정해볼 것이다. 데이터의 개수가 N, 데이터 중 최대값이 K일 때, 계수 정렬은 최악의 경우에도 수행시간 O(N+K)를 보장한다.

계수 정렬은 데이터의 크기 범위가 제한되어 정수 형태로 표현할 수 있을 때만 사용할 수 있다. 만약 데이터의 값이 무한한 범위를 가질 수 있는 실수형 데이터가 주어지는 경우에는 계수 정렬은 사용하기 어렵다. 일반적으로 가장 큰 데이터와 가장 작은 데이터의 차이가 1,000,000을 넘지 않을 때 효과적으로 사용할 수 있다. 

![정렬 (12) - 계수 정렬 (Counting Sort)](https://blog.kakaocdn.net/dn/cxTgc0/btqBXFFlwbq/a9NU4KvqhkpO0VWUv8x1Mk/img.gif)

계수 정렬은 위와 모든 범위를 담을 수 있는 크기의 리스트를 선언해야하기 때문에, 크기에 제한이 있다.

```python
def count_sort(array):
    count = [0] * (max(array)+1)

    for i in array:
        count[i]+=1

    for j in range(len(count)):
        for x in range(count[j]):
            print(j, end=' ')
```

- 시간 복잡도 : O(N+K),  최대값 크기 K, 데이터수 N

### 파이썬 3.7 정렬 알고리즘 비교

| 데이터 수(N) | 선택 정렬 | 퀵 정렬 | 기본 정렬 라이브러리 |
| ------------ | --------- | ------- | -------------------- |
| 100          | 0.0123    | 0.00156 | 0.00000753           |
| 1000         | 0.354     | 0.00343 | 0.0000365            |
| 10000        | 15.475    | 0.0312  | 0.000248             |

<<<<<<< HEAD

선택 정렬은 기본 정렬 라이브러리를 포함해 다른 알고리즘과 비교했을 때 매우 비효율 적이지만, 특정한 리스트에서 가장 작은 데이터를 찾을때는 유용하게 사용된다.

#### sorted()

파이썬 기본 정렬 라이브러리에서 제공하는 `sorted()`는 퀵정렬 과 동작 방식이 비슷한 병합 정렬을 기반(병합 정렬 + 삽입정렬)으로 만들어졌다. 병합 정렬은 퀵정렬보다 일반적으로 느리지만, 최악의 경우에도 O(NlogN) 시간 복잡도를 보장한다.

**리스트, 딕셔너리** 자료형을 받아서 정렬된 결과를 출력한다.

```python
arr = [7, 5, 9, 0, 3, 1, 6, 2, 4, 8]
result = sorted(arr)
print(result)  # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(arr) # [7, 5, 9, 0, 3, 1, 6, 2, 4, 8]
```

정렬시에 Key 매개변수를 입력받아 정렬할 수 있는데, **key값으로는 정렬 기준의 하나의 함수가 입력된다.**

```python
arr = [('페이커', 26), ('테디', 25), ('케리아', 20)]

def setting(data):
    return data[1]
  
print(sorted(arr, key=setting)) # [('케리아', 20), ('테디', 25), ('페이커', 26)]
```



#### sort()

리스트 변수가 하나 있을 때 내부 원소를 바로 정렬할 수도 있다. `sort()` 를 이용하면 별도의 정렬된 리스트가 반환되지 않고 내부 원소가 바로 정렬된다.

```python
arr.sort()
print(arr) # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

```python
arr = [('페이커', 26), ('테디', 25), ('케리아', 20)]

def setting(data):
    return data[1]
arr.sort(key=setting)
print(arr) # [('케리아', 20), ('테디', 25), ('페이커', 26)]
```



정렬 라이브러리는 항상 최악의 경우에도 시간복잡도  O(NlogN)을 보장한다.
=======
선택 정렬은 기본 정렬 라이브러리를 포함해 다른 알고리즘과 비교했을 때 매우 비효율 적이지만, 특정한 리스트에서 가장 작은 데이터를 찾을때는 유용하게 사용된다.
>>>>>>> algorithm
