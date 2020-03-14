# STL Container - Associate Container

Associate Container(연관 컨테이너)는 키와 값처럼 관련있는 데이터를 하나의 쌍으로 저장하는 컨테이너이다.
키와 값을 이용하여 요소들에 대해 빠른 접근이 가능하다. 하지만 삽입되는 요소의 위치를 지정할 수 없다.

보통 balanced binary search tree나 hash table을 이용하여 구현한다.

## set & multiset

집합(set)은 저장하는 데이터 그 자체를 키로 사용하는 가장 단순한 연관 컨테이너이다. set와 달리 오름차순으로 정렬된 위치에 요소를 삽입하므로 검색속도가 매우 빠르다.

집합에서 키는 유일해야하므로, 키의 중복을 허용하지 않는다.

멀티집합(multiset)은 키의 중복을 허용하며, 같은 값을 여러번 저장할 수 있다.

```cpp
#include <set>
```

### 구조

```cpp
set<T> 객체명;
multiset<T> 객체명;
```
```cpp
set<int> st;
multiset<int> ms;
```

### 생성자

| 생성자                                       | 설명 |
| -------------------------------------------- | ---- |
| set s                                     |s는 빈 컨테이너        |
| set s(pred)                                  | s는 빈 컨테이너로 정렬 기준은 pred 조건자를 사용|
| set s(s2)                    | s는 s2 컨테이너의 복사본이다.(복사 생성자 호출) |
| set s(b,e) | s는 반복자 구간 [b,e)로 초기화된 원소를 갖는다.|
| set s(b,e,pred) | s는 반복자 구간 [b,e)로 초기화된 원소를 갖는다. 정렬기준은 pred 조건자를 이용한다.|

### 멤버함수

| 함수                                                | 설명                                                         |
| --------------------------------------------------- | ------------------------------------------------------------ |
| s.clear()                                           | s의 모든 원소를 제거                                         |
| n=s.count(k)                                        | 원소 k의 개수를 반환한다.                      |
| s.empty()                                           | v가 비었는지 조사                                            |
| p=s.begin()                                         | p는 s의 첫 원소를 가리킨다.                                  |
| p=s.end()                                           | p는 s의 끝을 표식하는 반복자                                 |
| pr=s.equeal_range(k)                                | pr는 원소 k의 반복자 구간인 pair 객체												 |
| q=s.erase(p)                                        | p가 가리키는 원소를 제거한다. q는 다음 원소를 가리킨다.      |
| q=s.erase(b,e)                                      | 반복자 구간 [b,e)의 모든 원소를 제거한다. q는 다음 원소를 가리킨다. |
| p=s.find(k) 																					| p는 k원소의 위치를 가리키는 반복자이다. 										 |
| pr=s.insert(k)                                     | s 컨테이너에 k를 삽입한다. pr은 삽입한 원소를 가리키는 반복자와 성공 여부의 bool인 pair 객체이다.|
| q=s.insert(p,x)                                     | p가 가리키는 위치에 k값을 삽입한다. q는 삽입한 원소를 가리키는 반복자다. |
| s.insert(b,e)                                     |  반복자 구간 [b,e)의 원소를 삽입한다.     |
| pred = s.key_comp() 																| pred는 s의 key 정렬기준인 조건자이다.(key_compare 타입)			 |
| pred = s.value_comp() 														| pred는 s의 value 정렬기준인 조건자이다.(value_compare 타입)			|
| p = s.lower_bound(k) 																| p는 k의 시작구간을 가리키는 반복자이다. 										|
| p = s.upper_bound(k) 																| p는 k의 끝 구간을 가리키는 반복자이다. 										|
| x=s.max_size()                                      | x는 s가 담을 수 있는 최대 원소의 개수(메모리의 크기)         |
| p=s.rbegin()                                        | p는 s의 역 순차열의 첫 원소를 가리키는 반복자다.             |
| p=s.rend()                                          | p는 s의 역 순차열의 끝을 표식하는 반복자                     |
| s.size()                                            | s의 원소 갯수                                                |
| s.swap(s2)                                          | s와 s2를 swap한다.                                           |

연관 컨테이너는 정렬 기준이 있으므로 `insert()`에 의해 삽입된 원소는 자동 정렬된다. set에서 원소를 key라 하며, 이 키를 비교하여 내부 원소를 정렬한다.

### 예시

- set

```cpp
#include <iostream>
#include <set>

using namespace std;

int main(void){
    set<int> s;

    pair<set<int>::iterator, bool> pr;
    pr = s.insert(50);

    if( pr.second == true ){
        cout << *pr.first << " 삽입 성공" << endl;
    }else{
        cout << *pr.first << " 삽입 실패" << endl;
    }
    
    s.insert(40);
    s.insert(80);

    set<int>::iterator iter;
    // insert로 삽입해 정렬된 것을 확인할 수 있다.
    for(iter=s.begin();iter!=s.end();++iter){
        cout << *iter << ' ';
    }
    cout << endl;
    
    pr = s.insert(50);
    if( pr.second == true ){
        cout << *pr.first << " 삽입 성공" << endl;
    }else{
        cout << *pr.first << " 삽입 실패" << endl;
    }
    copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // 50위치에 60삽입
    s.insert(pr.first, 60);
    copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // 내림차순 정렬
    set<int, greater<int> > s2;
    s2.insert(50);
    s2.insert(30);
    s2.insert(80);
    s2.insert(10);
    
    for(iter=s2.begin();iter!=s2.end();++iter){
        cout << *iter << ' ';
    }
    cout << endl;

    // key_compare(), value_compare()
    cout << "key_compare less : " << typeid(s.key_comp()).name() << endl;
    cout << "key_compare greater : " << typeid(s2.key_comp()).name() << endl;

    cout << "value_compare less : " << typeid(s.value_comp()).name() << endl;
    cout << "value_compare greater : " << typeid(s2.value_comp()).name() << endl;
}
```

- multiset

```cpp
#include <iostream>
#include <set>

using namespace std;

int main(void){
    multiset<int> ms;

    ms.insert(50);
    ms.insert(30);
    ms.insert(40);
    ms.insert(30);
    ms.insert(80);
    ms.insert(50);
    ms.insert(30);
    ms.insert(50);
    ms.insert(10);

    multiset<int>::iterator iter;
    for(iter=ms.begin(); iter!=ms.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
    
    cout << "30 count : " << ms.count(30) << endl;

    
    // 원소 30의 첫번째 위치
    multiset<int>::iterator lower_iter;
    lower_iter = ms.lower_bound(50);
    // 원소 30의 마지막 위치 다음 위치
    multiset<int>::iterator upper_iter;
    upper_iter = ms.upper_bound(50);
    cout << "lower iter : " << *lower_iter << ", upper_iter : " << *upper_iter << endl;
    
    pair<multiset<int>::iterator, multiset<int>::iterator> iter_pair;
    iter_pair = ms.equal_range(30);

    for(iter = iter_pair.first; iter != iter_pair.second; ++iter){
        cout << *iter << ' ';
    }
    cout << endl;

    // 해당 요소 전체 삭제
    ms.erase(50);
    copy(ms.begin(), ms.end(), ostream_iterator<int>(cout, " "));
}
```

## map & multimap

map은 키와 값의 쌍으로 데이터를 관리하는 컨테이너이다. 집합 컨테이너와 마찬가지로 정렬된 위치에 요소를 삽입하므로 검색 속도가 매우 빠르다.

map에서 키는 유일해야하므로, 하나의 키에 하나의 값만이 연결될 수 있다.
multimap은 값의 중복을 혀용하므로, 하나의 키에 여러 개의 값과 연결될 수 있다.

```cpp
#include <map>
```

### 구조

```cpp
map<T> 객체명;
multimap<T> 객체명;
```

### 예시

map은 set과 같은 인터페이스 멤버 함수를 제공하며, 템플릿 형식과 내장 멤버 형식만이 약간 차이를 보인다.
- map은 `[]`연산자를 제공하여 key에 해당하는 원소의 value에 쉽게 접근하거나 변경할 수 있다.

- map

```cpp
#include <iostream>
#include <map>

using namespace std;

int main(void){

    map<string, int> m;

    m.insert(pair<string,int>("수학",100));
    m.insert(pair<string,int>("국어",80));

    pair<string,int> p("영어",50);
    m.insert(p);

    map<string, int>::iterator iter;
    for(iter = m.begin(); iter != m.end(); ++iter){
        cout << (*iter).first << " : " << (*iter).second << endl;
    }

    m["영어"] = 90;

    for(iter = m.begin(); iter != m.end(); ++iter){
        cout << iter->first << " : " << iter->second << endl;
    }

    pair<map<string,int>::iterator, bool> pr;

    pr = m.insert(pair<string, int>("과학", 60));
    
    if(pr.second){
        cout << pr.first->first << " : " << pr.first->second << endl;
    }
    return 0;
}
```

- multimap

```cpp
#include <iostream>
#include <map>

using namespace std;

int main(void){
    multimap<string, int> mm;

    mm.insert(pair<string, int>("국어", 30));
    mm.insert(pair<string, int>("수학", 100));
    mm.insert(pair<string, int>("수학", 90));
    mm.insert(pair<string, int>("국어", 60));

    multimap<string, int>::iterator iter;
    for(iter=mm.begin(); iter!=mm.end(); ++iter){
        cout << iter->first << " : " << iter->second << endl;
    }
    cout << endl;

    cout << "count('국어') : "<< mm.count("국어") << endl;

    mm.insert(pair<string, int>("영어", 60));
    mm.insert(pair<string, int>("과학", 80));

    map<string, int>::iterator lower_iter;
    map<string, int>::iterator upper_iter;

    lower_iter = mm.lower_bound("수학");
    // upper는 가장 큰 수학 다음!
    upper_iter = mm.upper_bound("수학");

    cout << "lower " << lower_iter->first << " : " << lower_iter->second << endl;
    cout << "upper " << upper_iter->first << " : " << upper_iter->second << endl;

    pair<map<string, int>::iterator, map<string,int>::iterator> iter_pair;
    iter_pair = mm.equal_range("수학");

    for(iter=iter_pair.first; iter!=iter_pair.second;++iter){
        cout << iter->first << " : " << iter->second << endl;
    }
    return 0;
}
```

## unordered associate container

순서가 지정되지 않은 연관 컨테이너는 순서가 지정된 기존 연관 컨테이너와 같은 동작을 한다. 기존의 연관 컨테이너는 tree 구조를 기반으로 동작하지만, 이 컨테이너는 hash table을 기반으로 동작한다.

따라서, 요소의 추가, 삭제 속도가 빨라졌으며, 다양한 검색 알고리즘을 사용할 수 있게 되었다.
순서가 지정된 연관 컨테이너는 양방향 반복자를 지원하지만, 이 컨테이너는 순반향 반복자만을 지원한다.

- unordered_set
- unordered_multiset
- unordered_map
- unordered_multimap

## 참조

- [개발이하고싶어요](http://hyeonstorage.tistory.com/)
- [TCPSCHOOL.com](http://tcpschool.com/)
