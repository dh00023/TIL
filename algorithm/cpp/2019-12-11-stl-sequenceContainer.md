# STL Container - Sequence Container

STL Container는 같은 타입의 여러 객체를 저장하는 일종의 집합이라 할 수 있다. 컨테이너는 class template으로, 컨테이너 변수를 선언할 때 컨테이너에 포함할 요소의 타입을 명시할 수 있다.
컨테이너에는 복사 생성과 대입을 할 수 있는 타입의 객체만을 저장할 수 있으며, 요소의 추가 및 제거를 포함한 다양한 작업을 도와주는 여러 멤버 함수를 포함하고 있다.

## STL Sequence Container

데이터를 선형으로 저장하며, 특별한 제약이나 규칙이 없는 가장 일반적인 컨테이너이다. 시퀀스 컨테이너에서는 삽입된 요소의 순서가 그대로 유지된다.

1. 모든 요소가 직선 순서대로 배치되어 있어야한다.
2. 반복자가 최소한 순방향 반복자(forward iterator) 이상이어야한다.
3. 시퀀스 컨테이너의 요소들은 명확한 순서를 가지므로, 특정 위치를 참조하는 연산이 가능해야한다.

### vector
vector 컨테이너는 **대표적인 시퀀스 컨테이너로 배열과 비슷**하여 사용이 쉬우며 자주 사용된다. vector는 임의 접근 반복자(Random Access Iterator)를 지원하는 **배열 기반 컨테이너**이다. vector의 가장 큰 특징 중 하나는 원소가 **하나의 메모리 블록에 연속하게 저장된다**는 것이다. 
vector는 요소가 추가되거나 삭제될 때마다 자동으로 메모리를 재할당하여 크기를 재할당하여 크기를 동적으로 변경한다. 메모리 할당 크기를 알 수 있게 capacity() 함수를 제공하며 한번에 메모리를 할당할 수 있는 reserve() 함수도 제공된다. 원소가 연속하게 저장되므로 `[]` 연산자 또는 at 으로 읽기에는 빠르지만  insert(), erase(), push_back() 등은 비효율적으로 동작한다.

```cpp
#include <vector>
```

```cpp
vector<T> 객체명(생성자 인수);
```

생성자 인수로는 벡터 컨테이너의 초기 크기를 전달하며, 생략하면 요소를 가지지 않는 빈 벡터를 생성한다.


#### 생성자

| 생성자                                       | 설명 |
| -------------------------------------------- | ---- |
| vector v                                     |v는 빈 컨테이너        |
| vector v(n)                                  | v는 기본값으로 초기화된 n개의 원소를 갖는다. |
| vector v(n,x) | v는 x 값으로 초기화된 n개의 원소를 갖는다. |
| vector v(v2)                    | v는 v2 컨테이너의 복사본이다.(복사 생성자 호출) |
| vector v(a,b) | v는  반복자 구간 [b,e)로 초기화된 원소를 갖는다. |

#### 멤버함수

| 함수                                                | 설명                                                         |
| --------------------------------------------------- | ------------------------------------------------------------ |
| v.assign(n,x)                                       | v에 x 값으로 n개의 원소를 할당한다.                          |
| v.assign(a,b)                                       | v를 반복자 구간 [a,b)로 할당                                 |
| v.at(i)                                             | v의 i번째 원소를 참조                                        |
| v.front()                                           | v의 첫 번째 원소를 참조한다.                                 |
| v.back()                                            | v의 마지막 원소를 참조                                       |
| v.capacity()                                        | v에 할당된 공간의 크기                                       |
| v.clear()                                           | v의 모든 원소를 제거                                         |
| v.empty()                                           | v가 비었는지 조사                                            |
| p=v.begin()                                         | p는 v의 첫 원소를 가리킨다.                                  |
| p=v.end()                                           | p는 v의 끝을 표식하는 반복자                                 |
| q=v.erase(p)                                        | p가 가리키는 원소를 제거한다. q는 다음 원소를 가리킨다.      |
| q=v.erase(b,e)                                      | 반복자 구간 [b,e)의 모든 원소를 제거한다. q는 다음 원소를 가리킨다. |
| q=v.insert(p,x)                                     | p가 가리키는 위치에 x 값을 삽입한다. q는 삽입한 원소를 가리키는 반복자다. |
| v.insert(p,n,x)                                     | p가 가리키는 위치에 n개의 x 값을 삽입한다.                   |
| v.insert(p,b,e)                                     | p가 가리키는 위치에 반복자 구간 [b,e)의 원소를 삽입한다.     |
| x=v.max_size()                                      | x는 v가 담을 수 있는 최대 원소의 개수(메모리의 크기)         |
| v.pop_back()                                        | v의 마지막 원소를 제거한다.                                  |
| v.push_back()                                       | v의 끝에 x를 추가한다.                                       |
| p=v.rbegin()                                        | p는 v의 역 순차열의 첫 원소를 가리키는 반복자다.             |
| p=v.rend()                                          | p는 v의 역 순차열의 끝을 표식하는 반복자                     |
| v.reserve(n)                                        | n개의 원소를 저장할 공간을 예약한다.                         |
| v.resize(n)                                         | v의 크기를 n으로 변경하고 확장되는 공간의 값을 기본값으로 초기화 한다. |
| v.resize(n,x)                                       | v의 크기를 n으로 변경하고 확장되는 공간의 값을 x 값으로 초기화한다. |
| v.size()                                            | v의 원소 갯수                                                |
| v.swap(v2)                                          | v와 v2를 swap한다.                                           |

#### 예제

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){

    vector<int> v;
    vector<int> v2(5);    // 0으로 초기화된 5개의 원소
    // 메모리크기 8만큼 할당
    v.reserve(8);

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    for (vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] << endl;
    cout << endl;

    // 벡터의 원소 갯수를 10개로 확장, 추가된 공간은 디폴트 0으로 채워진다.
    v.resize(10);                
}
```

여기서 v.size()만큼 for문을 실행하려면 v.size()의 타입과 i 가 같아야 한다. 

- `vector<int>::size_type` : 벡터의 size 의 반환 타입을 가져온다 (unsigned int)


### deque

[depue](https://dh00023.github.io/algorithm/ds/2018/04/25/algorithm-10#deque)는 double-ended queue를 의미하며, 양방향 큐이다. 컨테이너의 양 끝에서 빠르게 요소를 삽입하거나 삭제할 수 있다.

#### 구조

```cp
deque<T> 변수명;
```

#### 생성자

| **생성자**    |                                                  |
| ------------- | ------------------------------------------------ |
| deque dq       | dq는 빈 컨테이너이다.                            |
| deque dq(n)    | dq는 기본값으로 초기화된 n개의 원소를 갖는다.    |
| deque dq(n, x) | dq는 x 값으로 초기화된 n개의 원소를 갖는다.      |
| deque dq(dq2)  | dq는 dq2 컨테이너의 복사본이다                   |
| deque dq(b,e)  | dq는 반복자 구간 [b,e)로 초기화된 원소를 갖는다. |

#### Member Function

| **멤버 함수**           |                                                              |
| ----------------------- | ------------------------------------------------------------ |
| dq.assign(n,x)          | dq에 x 값으로 n개의 원소를 할당한다.                         |
| dq.assign(b,e)          | dq를 반복자 구간 [b,e)로 할당한다.                           |
| dq.back()               | dq의 마지막 원소를 참조한다.                                 |
| p=lt.begin()            | p는 dq의 첫 원소를 가리키는 반복자다                         |
| dq.clear()              | dq의 모든 원소를 제거한다.                                   |
| dq.empty()              | dq가 비었는지 조사한다.                                      |
| p=dq.end()              | p는 dq의 끝을 표식하는 반복자다                              |
| q=dq.erase(p)           | p가 가리키는 원소를 제거한다. q는 다음 원소를 가리킨다.      |
| q= dq.erase(b,e)        | 반복자 구간 [b,e)의 모든 원소를 제거한다. q는 다음 원소다    |
| dq.front()              | dq의 첫 번째 원소를 참조한다.                                |
| q=dq.insert(p,x)        | p가 가리키는 위치에 x 값을 삽입한다. q는 삽입한 원소를 가리키는 반복자다 |
| dq.insert(p,n,x)        | p가 가리키는 위치에 n 개의 x 값을 삽입한다.                  |
| dq.insert(p,b,e)        | p가 가리키는 위치에 반복자 구간 [b,e)의 원소를 삽입한다.     |
| x=dq.max_size()         | x는 dq가 담을 수 있는 최대 원소의 개수                       |
| dq.pop_back()           | dq의 마지막 원소를 제거한다.                                 |
| dq.pop_front()          | dq의 첫번째 원소를 제거한다.                                 |
| dq.push_back(x)         | dq의 끝에 x를 추가한다.                                      |
| dq.push_front(x)        | dq의 앞쪽에 x를 추가한다.                                    |
| p=dq.rbegin()           | p는 dq의 역 순차열의 첫 원소를 가리키는 반복자다             |
| p=dq.rend()             | p는 dq의 역 순차열의 첫 원소를 가리키는 반복자다             |
| dq.resize(n)            | dq의 크기를 n으로 변경하고 확장되는 공간의 값을 기본값으로 초기화한다. |
| dq.resize(n,x)            | dq의 크기를 n으로 변경하고 확장되는 공간의 값을 x 로 초기화한다. |
| dq.size()               | dq 원소의 갯수다                                             |
| dq.swap(dq2)            | dq와 dq2를 swap 한다.                                        |

#### 예제

```cpp
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(){
    // deque 선언 및 초기화
    deque<int> dq;
    dq.push_back(20);
    dq.push_back(30);
    dq.push_front(10);

    cout << "deque : ";
    copy(dq.begin(), dq.end(), ostream_iterator<int>(cout," "));

    dq.pop_front();
    cout << "deque : ";
    deque<int>::iterator iter;
    for(iter=dq.begin();iter!=dq.end();++iter){
        cout << * iter << ' ';
    }
    cout << endl;
}
```

### list
STL List는 [double linked list](https://dh00023.github.io/algorithm/ds/2018/04/23/algorithm-8#doubleLinkedList), forward_list는 [single linked list](https://dh00023.github.io/algorithm/ds/2018/04/23/algorithm-8#singleLinkedList)와 같다.  

- list는 노드 기반 컨테이너로 `at()`과 `[]` 연산자가 없으며 임의 접근 반복자가 아닌 양방향 반복자(`++`, `--`)를 제공
- 중간에 원소를 삽입(insert), 제거(erase) 하더라도 상수 시간 복잡도(O(n))의 수행 성능

#### 구조

```cpp
template < class T, class Allocator = allocator<T> > class list;
```

```cpp
list<int> intList;
list<string> stringList;
```

#### 생성자

| **생성자**    |                                                  |
| ------------- | ------------------------------------------------ |
| list lt       | lt는 빈 컨테이너이다.                            |
| list lt(n)    | lt는 기본값으로 초기화된 n개의 원소를 갖는다.    |
| list lt(n, x) | lt는 x 값으로 초기화된 n개의 원소를 갖는다.      |
| list lt(lt2)  | lt는 lt2 컨테이너의 복사본이다                   |
| list lt(b,e)  | lt는 반복자 구간 [b,e)로 초기화된 원소를 갖는다. |

#### Member Function

| **멤버 함수**           |                                                              |
| ----------------------- | ------------------------------------------------------------ |
| lt.assign(n,x)          | lt에 x 값으로 n개의 원소를 할당한다.                         |
| lt.assign(b,e)          | lt를 반복자 구간 [b,e)로 할당한다.                           |
| lt.back()               | lt의 마지막 원소를 참조한다.                                 |
| p=lt.begin()            | p는 lt의 첫 원소를 가리키는 반복자다                         |
| lt.clear()              | lt의 모든 원소를 제거한다.                                   |
| lt.empty()              | lt가 비었는지 조사한다.                                      |
| p=lt.end()              | p는 lt의 끝을 표식하는 반복자다                              |
| q=lt.erase(p)           | p가 가리키는 원소를 제거한다. q는 다음 원소를 가리킨다.      |
| q= lt.erase(b,e)        | 반복자 구간 [b,e)의 모든 원소를 제거한다. q는 다음 원소다    |
| lt.front()              | lt의 첫 번째 원소를 참조한다.                                |
| q=lt.insert(p,x)        | p가 가리키는 위치에 x 값을 삽입한다. q는 삽입한 원소를 가리키는 반복자다 |
| lt.insert(p,n,x)        | p가 가리키는 위치에 n 개의 x 값을 삽입한다.                  |
| lt.insert(p,b,e)        | p가 가리키는 위치에 반복자 구간 [b,e)의 원소를 삽입한다.     |
| x=lt.max_size()         | x는 lt가 담을 수 있는 최대 원소의 개수                       |
| lt.merge(lt2)           | lt2를 lt로 합병 정렬한다.                                    |
| lt.merge(lt2, pred)     | lt2를 lt로 합병 정렬한다. pred(조건자)를 가지누으로 합병한다. |
| lt.pop_back()           | lt의 마지막 원소를 제거한다.                                 |
| lt.pop_front()          | lt의 첫번째 원소를 제거한다.                                 |
| lt.push_back(x)         | lt의 끝에 x를 추가한다.                                      |
| lt.push_front(x)        | lt의 앞쪽에 x를 추가한다.                                    |
| p=lt.rbegin()           | p는 lt의 역 순차열의 첫 원소를 가리키는 반복자다             |
| lt.remove(x)            | x 원소를 모두 제거한다.                                      |
| lt.remove_if(pred)      | pred(단항 조건자)가 '참'인 모든 원소를 제거한다.             |
| p=lt.rend()             | p는 lt의 역 순차열의 첫 원소를 가리키는 반복자다             |
| lt.resize(n)            | lt의 크기를 n으로 변경하고 확장되는 공간의 값을 기본값으로 초기화한다. |
| lt.reverse()            | lt 순차열을 뒤집는다.                                        |
| lt.size()               | lt 원소의 갯수다                                             |
| lt.sort()               | lt의 모든 원소를 오름 차순 으로 정렬한다.                    |
| lt.sort(pred)           | lt의 모든 원소를 pred(조건자)를 기준으로 정렬한다.           |
| lt.splice(p, lt2)       | p가 가리키는 위치에 lt2의 모든 원소를 잘라 붙인다.           |
| lt.splice(p, lt2, q)    | p가 가리키는 위치에 lt2의 q가 가리키는 원소를 잘라 붙인다.   |
| lt.splice(p, lt2, b, e) | p가 가리키는 위치에 lt2의 순차열 [b,e)를 잘라 붙인다.        |
| lt.swap(lt2)            | lt와 lt2를 swap 한다.                                        |
| lt.unique()             | 인접한 원소의 값이 같다면 유일한 원소의 순차열로 만든다.     |
| lt.unique(pred)         | 인접한 원소가 pred(이항 조건자)의 기준에 맞다면 유일한 원소의 순차열로 만든다 |

#### 예제

```cpp
#include <iostream>
#include <list>
using namespace std;

int main(){

    list<int> list1;

    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    list1.push_back(40);
    list1.push_back(50);

    list<int>::iterator iter;
    for (iter = list1.begin(); iter != list1.end(); ++iter){
        cout << *iter << ' ';
    }
    cout << endl;
  // 10 20 30 40 50

    // erase 삭제
  	iter = list1.begin();
    iter++;
    iter++;

    list<int>::iterator iter2 = list1.erase(iter);
    for (iter = list1.begin(); iter != list1.end(); ++iter){
        cout << *iter << ' ';
    }
    cout << endl;
  	// 10 20 40 50
  
  
    cout << "iter2 : " << *iter2 << endl;
  	// iter2 : 40

    list1.push_back(10);
    list1.push_back(10);

    for (iter = list1.begin(); iter != list1.end(); ++iter){
        cout << *iter << ' ';
    }
    cout << endl;
   	// 10 20 40 50 10 10

    // 리스트에서 원소 10 제거
    list1.remove(10);

    for (iter = list1.begin(); iter != list1.end(); ++iter){
        cout << *iter << ' ';
    }
    cout << endl;
  	// 20 40 50
  
    return 0;
}
```

### forward_list

- `<forward_list>` 헤더에 존재한다.
- 단순연결리스트 자료구조를 이용하여 만든 sequence container
- 단방향리스트로만 충분한 경우에 사용(한 방향으로만 이동 가능하다.)
- `std::list` 보다 삽입/삭제 속도가 더 빠르며, 메모리를 더 적게 사용한다.(차이는 크지 않다.)

#### 구조

```cpp
template< class T, class Allocator = std::allocator<T> > class forward_list;
```

```cpp
forward_list<int> singleList;
```

#### 특징

1. 특별한 이유가 없다면 `forward_list`는 기존의 `list`의 설계에 맞춘다.

2. `std::list`의 `insert`와 `erase`를 `forward_list`에서 구현이 복잡해지고 성능 측면에서 좋지 않아 제공하지 않는다.
3. 다른 STL의 container에 있는 `size` 함수를 제공하지 않는다. 이유는 요소 수를 보존하는 멤버를가지고 있으면 C언어에서 구현한 것과 비교해서 불필요한 메모리를 사용한다. 만약 이런 멤버를 가지고 있지 않으면서 size 함수를 지원하면 호출할 때마다 모든 요소를 세어야 하므로 계산량이 O(N)이 된다.

#### 멤버 변수

##### Member types

|                   |                                                              |
| ----------------- | ------------------------------------------------------------ |
| Member type       | Definition                                                   |
| `value_type`      | T                                                            |
| `allocator_type`  | 할당자                                                       |
| `size_type`       | 부호 없는 정수(unsigned int) 타입 (일반적으로 `std::size_t`) |
| `difference_type` | 부호 있는 정수(signed int) 타입 (보통 `std::ptrdiff_t`)      |
| `reference`       | `value_type&`                                                |
| `const_reference` | `const value_type&`                                          |
| `pointer`         | `std::allocator_traits<Allocator>::pointer`                  |
| `const_pointer`   | `std::allocator_traits<Allocator>::const_pointer`            |
| `iterator`        | `ForwardIterator`                                            |
| `const_iterator`  | 상수(constant) 양방향 반복자(iterator)                       |



##### Member Function

| Member Function                    | 설명                                                         |
| ---------------------------------- | ------------------------------------------------------------ |
| `assign`                           | 컨테이너에 값을 할당                                         |
| `befor_begin` <br> `cbefore_begin` | 시작하기 전에 요소에 반복자(iterator)를 반환                 |
| `begin` <br> `cbegin`              | 첫번째 원소의 반복자(iterator)를 반환                        |
| `end` <br> `cend`                  | 마지막 원소로의 반복자(iterator) 반환                        |
| `empty`                            | 현재 컨테이너가 비어있는지 확인                              |
| `max_size`                         | 원소의 최대 개수를 반환                                      |
| `clear`                            | 모두 삭제                                                    |
| `resize`                           | 사이즈 변경                                                  |
| `insert_after`                     | 삽입                                                         |
| `erase_after`                      | 삭제                                                         |
| `push_front`                       | 새로운 원소를 앞에 삽입                                      |
| `pop_front`                        | 첫번째 원소 삭제                                             |
| `swap`                             | 원소들을 서로 교환                                           |
| `remove` <br> `remove_if`          | 조건삭제                                                     |
| `unique`                           | 중복요소 삭제                                                |
| `reverse`                          | 전환(역으로 바꿈)                                            |
| `merge`                            | 병합                                                         |
| `sort`                             | 정렬                                                         |
| `splice_after`                     | 해당 요소를 원본 순방향 리스트에서 삭제하고, 대상 순방향 리스트의 지정된 위치에 삽입 |
|                                    |                                                              |

####  예시

```cpp
#include <iostream>
#include <forward_list>

using namespace std;

int main(){
  // forward_list 객체의 선언 및 초기화
	forward_list<int> singleList = {10, 20, 400, 30}; 
	forward_list<int> singleList2 = {40, 50};
	forward_list<int>::iterator itr;
	// 값이 400인 모든 요소를 삭제함.
	singleList.remove(400);              

  // singleList 첫 번째 요소를 가리키도록 반복자를 초기화
	itr = singleList.begin();            

  //singleList2 모든 요소를 singleList 첫 번째 요소 다음에 삽입
	singleList.splice_after(itr, singleList2); 

}
```


### 참조페이지

- [개발이하고싶어요](http://hyeonstorage.tistory.com/)
- [TCPSCHOOL.com](http://tcpschool.com/)
- [https://shaeod.tistory.com/469](https://shaeod.tistory.com/469)
- [https://ko.cppreference.com/w/cpp/container/forward_list](https://ko.cppreference.com/w/cpp/container/forward_list)
