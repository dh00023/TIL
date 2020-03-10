/*
2. 암복호화

사내 개발자 커플인 철수와 영희에게 둘만의 비밀 통신 프로그램이 필요합니다. 아래 기능 명세를 만족하는 비밀 통신 프로그램을 구현하세요.

이 프로그램은 암호화와 복호화 두 가지 동작을 수행합니다.

메시지를 암호화하려면 다음과 같이 입력합니다,
encrypt secretword 3 helloworld
이 입력을 받아 프로그램은 암호화된 문장을 출력합니다.

cspkfcgzin


반대로 복호화는 다음과 같이 수행합니다.
decrypt secretword 3 cspkfcgzin
아래와 같이 복호화된 문장을 출력합니다.

helloworld


[암호화/복호화 방식]

암호화는 '비밀키'를 이용해서 원문자를 다른 영문자로 바꾸고,
'로테이트' 연산을 통해서 문자 배치를 바꾸는 방식을 사용합니다.
'비밀키'에서 사용되는 a~z는 0~25를 의미하며,
원본 문자를 비밀키만큼 이동시킨 알파벳 소문자로 변환하기 위해 사용합니다.
예시) e(원본 문자) + b(비밀키 문자) = f(변환된 문자)
비밀키는 원본 메시지 길이만큼 반복해서 사용합니다.
변환된 메시지는 '로테이트 횟수'만큼 로테이트 된 후 출력됩니다.
'로테이트 횟수'에서 양의 정수는 왼쪽 로테이트 횟수, 음의 정수는 오른쪽 로테이트 횟수를 의미합니다.
예시) 로테이트 횟수가 2이면 iloveyou는 oveyouil 로 변환됩니다.
복호화는 암호화의 역순으로 수행되며, 원본 메시지를 출력합니다.

[입력]
첫 번째 자리는 '암호화/복호화 명령'를 나타내며,
'encrypt' 이면 암호화 수행, 'decrypt'이면 복호화를 수행합니다.
두 번째 자리는 '비밀키'입니다.
'비밀키' 길이는 1~30자이며, 알파벳 소문자로만 구성됩니다.
세 번째 자리는 문자열의 '로테이트 횟수'입니다.
로테이트 횟수는 -10000 이상, 10000 이하 범위의 정수입니다.
네 번째 자리는 '메시지'입니다.
'메시지'는 최대 30자이며, 알파벳 소문자로만 구성됩니다.
'비밀키'와 '메시지'는 모두 알파벳 소문자로만 구성됩니다.


[출력]

주어진 입력 조건에 따라 암호화 또는 복호화로 변환한 메시지를 출력합니다.


[예시]
비밀키가 secretword이고, 로테이트 횟수 3, 메시지가 helloworld 인 경우 다음과 같이 됩니다.




입/출력 예시
⋇ 입출력 형식을 잘 지켜주세요.
␣ : 공백↵ : 줄바꿈
보기 입력 1
encrypt secretword 3 helloworld
출력 1
cspkfcgzin

보기 입력 2
decrypt secretword 3 cspkfcgzin
출력 2
helloworld

*/
#include <iostream>
#include <queue>
using namespace std;

int main() {
    
    string secret,origin;
    queue<char> c;
    int r;
    string m;
    cin >> m>> secret >> r >> origin;
    int secs=secret.size();
    if(m=="encrypt"){
        for(int i=0;i<secs;i++){
            if(secret[i]+origin[i]-97>122){
                c.push(secret[i]+origin[i]-97-26);
            }else{
                c.push(secret[i]+origin[i]-97);
            }
        }
        for(int i=0;i<r;i++){
            c.push(c.front());
            c.pop();
        }
    }else if(m=="decrypt"){
        for(int i=0;i<secs;i++){
            c.push(origin[i]);
        }
        for(int i=0;i<secs-r;i++){
            c.push(c.front());
            c.pop();
        }
        for(int i=0;i<secs;i++){
            if(c.front()-secret[i]+97<97){
                c.push(c.front()-secret[i]+97+26);
                c.pop();
            }else{
                c.push(c.front()-secret[i]+97);
                c.pop();
            }
        }
    }
    int n=c.size();
    for(int i=0;i<n;i++){
        if(!c.empty()){
            cout<<c.front();
            c.pop();
        }else{
            break;
        }
    }
}
