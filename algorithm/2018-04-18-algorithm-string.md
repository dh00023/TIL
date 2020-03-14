# String

**아스키코드(ASCII)** : 문자 인코딩 방법 중 하나이다.
- `0` => 48
- `A` => 65
- `a` => 97
- 0 => NULL


## 실습

### 알파벳 개수

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;

    for (int i='a'; i<='z'; i++) {
        cout << count(s.begin(), s.end(), i) << ' ';
    }

    cout << '\n';
}
```

여기서 `#include <algorithm>`에서 `count(s.begin(),s.end(),i);`는 s문자열에서 i가 포함된 수를 count해준다.

### 알파벳 위치

```cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


void alpha_loc() {
    string s;
    cin >> s;

    for (int i='a'; i<='z'; i++) {
        auto it = find(s.begin(), s.end(), i);
        if (it == s.end()) {
            cout << -1 << ' ';
        } else {
            cout << (it - s.begin()) << ' ';
        }
    }
    cout << '\n';
}
```
`find(s.begin(), s.end(), i);`는 위치를 알려준다.

### 문자열 분석
문자열 N개에 포함되어 있는 소문자, 대문자, 숫자, 공백의 개수를 세는 문제
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s;
    while(getline(cin,s)){
        int upper=0,lower=0,space=0,number=0;
        for(int i=0;i<s.length();i++){
            if('a'<=s[i]&&s[i]<='z'){
                lower+=1;
            }else if('A'<=s[i]&&s[i]<='Z'){
                upper+=1;
            }else if('0'<=s[i]&&s[i]<='9'){
                number+=1;
            }else if(s[i]==' '){
                space+=1;
            }
        }
        cout << lower <<' '<< upper <<' '<< number <<' '<< space<<'\n';
    }
    
    cout << '\n';
}
```

### 단어 길이 재기
- `strlen`
- `s.length()`
- `s.size()`
- 
```cpp
scanf("%s",s);
int len = 0;
for(int i=0;s[i];i++){//s[i]에 NULL값이 나오면 종료된다.
	len+=1;
}
```

### ROT13
ROT13으로 암호화하는 프로그램을 만드는 문제이다.
ROT13은 카이사르 암호의 일종으로 영어 알파벳을 13글자씩 밀어서 만든다.
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    getline(cin,s);
    int n = s.size();
    for(int i=0;i<n;i++){
        if('a'<=s[i]&&s[i]<='m'){
            s[i]=s[i]+13;
        }else if('n'<=s[i]&&s[i]<='z'){
            s[i]=s[i]-13;
        }else if('A'<=s[i]&&s[i]<='M'){
            s[i]=s[i]+13;
        }else if('N'<=s[i]&&s[i]<='Z'){
            s[i]=s[i]-13;
        }
    }
    cout << s <<"\n";
}
```

### 문자열 -> 정수

`#include <string>`에서 `stoi`,`stol`,`stoll`등등의 함수를 사용하면 된다.

|함수|변화|
|------|------|
|stoi|string->int|
|stol|string->long|
|stoll|string->long long|
|stof|string->float|
|stod|string->double|
|stold|string->long double|
|stoul|string->unsigned long|
|stoull|string->unsigned long long|

### 정수 -> 문자열
`to_string`함수를 사용하면된다.

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    long a,b,c,d;
    cin >> a >> b >> c >> d;

    string ab = to_string(a)+ to_string(b);
    string cd = to_string(c)+ to_string(d);

    cout << stoll(ab)+stoll(cd)<<"\n";
}
```

### 접미사 배열

문자열 S의 모든 접미사를 사전순으로 정해 놓은 배열이다.
```
ex)likelion
likelion, ikelion, kelion, elion, lion, ion, on, n
```
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s,str;
    cin >> s;

    vector<string> v;

    for(int i=0;i<s.size();i++){
        v.push_back(str.assign(s,i,s.size()));
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        cout << v[i]<<"\n";
    }
}
```