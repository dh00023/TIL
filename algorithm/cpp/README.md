# C++

## 표준 입출력 라이브러리

```cpp
#include <iostream>
```
iostream 라이브러리는 c++ 표준 입출력 라이브러리이다. c언어의 `stdio.h`와 흡사하게 사용된다.
c++에서는 형식 지정자(ex `%d`, `%f`)를 넣어주지 않아도 변수를 타입에 맞게 적절히 입출력을 해준다.
c++ 기본 입출력 라이브러리에서는 `>>`와 `<<` 연산자를 제공한다. 이때 입력을 받는 `>>` 연산자는 공백문자(space, Enter, Tab)을 기준으로 입력을 받는다.

```cpp
#include <iostream>
#include <string>

int main(){
	std::string input;
	std::cin >> input;
	std::cout << input << std::endl;
	return 0;
}
```

### cin

고수준 입력 방식을 사용하면 코드가 간단해지지만, 이에 의한 속도 저하 또한 클 수 있다.
`<cstdio>`와의 동기화를 끄면 훨씬 빨라진다.

```cpp
#include <iostream>
using namespace std;

int main(void){
    cin.sync_with_stdio(false);    
    return 0;
}
```

## namespace

namespace는 특정 영역에 이름을 설정할 수 있도록 하는 문법이다. 서로 다른 개발자가 공동으로 프로젝트를 진행할 때 각자 개발한 모듈을 하나로 합칠 수 있게 해준다.

```
[namespace]::[변수 혹은 함수]
```
namespace라는 소속 공간에 따라 변수나 함수가 같은 이름임에도 다르게 구분이 될 수 있다.

```cpp
#include <iostream>

namespace A{
    void function(){
        cout << "A namespace"<< endl;
    }
}
namespace B{
    void function(){
        cout << "B namespace"<< endl;
    }
}
int main(){
    A::function();
    B::function();
    return 0;
}
```
여기서 `::`는 범위지정 연산자로 어떤 namespace에서 어떤 function을 사용할 것인지 명시할 수 있다.

```cpp
using namespace <namespace>
```
기본적으로 표준 라이브러리를 `using` 키워드를 이용해 namespace로 선언해두고 앞에 명시하지 않고 사용할 수 있다.

```cpp
using namespace std;

int main(){
	string input;
	cin >> input;
	cout << input << endl;
	return 0;
}
```

## string 문자열 자료형

c++은 표준 문자열 자료형을 제공한다. 이는 string 헤더 파일에 정의되어 있다. 클래스로 구현되어있어 각 자료형별로 내장함수가 있으며, 이를 이용할 수 있다는 장점이 있다.

```cpp
char arr[SIZE]; // c언어
string s; 			// cpp
```

위에서 말한 `>>` 연산자는 공백을 기준으로 입력받는데, 한 줄 전체를 입력받고 싶은 경우에는 `getline()`함수를 사용할 수 있다.

```cpp
int main(){
	string input;
	getline(cin, input);
	cout << input << endl;
	return 0;
}
```

또한, c++의 string은 다른 자료형으로의 변환이 간편하다. `to_string()`, `stoi()`와 같이 정수를 문자열로, 문자열을 정수로 쉽게 변환할 수 있다.

```cpp
 		int i = 123;
 		string s = to_string(i);
    cout << "정수 -> 문자열" << s << endl;

    s = "456";
    i = stoi(s);
    cout << "문자열 -> 정수" << i << endl;
```

동적할당도 c++에서 더 간단하게 할 수 있다.

```cpp
#include <iostream>
#define SIZE 100

using namespace std;
int *arr;

int main(){
	arr = new int[SIZE]; // 동적할당
	for(int i=0; i < SIZE; i++){
		cout << arr[i] << ' ';
	}
	delete arr; // 할당 해제
	return 0;
}
```

`new` 키워드로 동적할당을 할 수 있으며, 할당 해제시에는 `delete`로 할 수 있다.

## c언어와 비교

- c++는 객체 지향 패러다임을 따르고 있는 언어, c언어는 절차적 프로그래밍 언어
- 즉, c++은 객체 중심의 언어이고, c언어는 함수 기반의 언어이다.
- c++은 c언어의 구조체(struct)대신에 class를 사용한다.
- c++은 공식적으로 예외처리 기술을 지원한다.