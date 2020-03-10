/*
1. 숫자 이어 붙이기

여러 개의 자연수를 표준 입력(standard input)에서 읽은 후, 그 수들을 이어 붙여서 만들 수 있는 가장 큰 수와 가장 작은 수의 합을 구하세요.



[입력]

주어지는 입력은 10개 이하이며, 각각의 숫자는 2자리 이하의 자연수입니다.
숫자는 공백으로 구분됩니다.
두 번째 예시에 대해 주의 깊게 살펴보시기 바랍니다.

[출력]
올바른 출력은 하나의 문장이어야 하며, 문장의 마지막은 불필요한 공백 없이 개행 문자(newline, \n)로 끝나야 합니다. 


[예시 설명 (1)]

입력이 1 2 3일 경우, 만들 수 있는 가장 큰 수는 321이고 가장 작은 수는 123이며 두 수의 합은 444이다. 
따라서 결과는 다음과 같다.
444


[예시 설명 (2)]

입력이 2 9 10 21 24일 경우, 
만들 수 있는 가장 큰 수는 92422110이고, 가장 작은 수는 10212249이며 두 수의 합은 102634359
따라서 결과는 다음과 같다. 
102634359
보기 입력 1
1 ␣2 ␣3
출력 1
444↵

보기 입력 2
2 ␣9 ␣10 ␣21 ␣24
출력 2
102634359↵
*/

#include <iostream>
#include <string>
using namespace std;

long long int n[10][2],m[10][2];
int main() {
    int l=0;
    long long int max=0,min=0;
    int num = 0;
    while(scanf("%lld",&n[num][0])!=EOF){
        if(n[num][0]<1||n[num][0]>99) break;
        
        m[num][0]=n[num][0];
        num++;
        if(num == 10) break;
    }
    
    int t=num;
    while(t--){
        long long int maxn=0;
        for(int i=0;i<num;i++){
            if(n[i][1]!=1){
                if(n[i][0]<10){
                    if(maxn<n[i][0]){
                        maxn=n[i][0];
                        l=i;
                    }
                }else{
                    if(maxn<n[i][0]/10){
                        maxn=n[i][0];
                        l=i;
                    }else if(maxn==n[i][0]/10){
                        if(maxn<=n[i][0]%10){
                            l=i;
                        }
                    }
                }
            }
        }
        n[l][1]=1;
        if(n[l][0]>10){
            max=max*100+n[l][0];
        }else{
            max=max*10+n[l][0];
        }
    }
    t=num;
    while(t--){
        long long int minn=99;
        for(int i=0;i<num;i++){
            if(m[i][1]!=1){
                if(m[i][0]<10){
                    if(minn>m[i][0]){
                        minn=m[i][0];
                        l=i;
                    }
                }else{
                    if(minn>m[i][0]/10){
                        minn=m[i][0];
                        l=i;
                    }else if(minn==m[i][0]/10){
                        if(minn>m[i][0]%10){
                            l=i;
                        }
                    }
                }
            }
        }
        m[l][1]=1;
        if(m[l][0]>10){
            min=min*100+m[l][0];
        }else{
            min=min*10+m[l][0];
        }
    }
    cout << max+min<<"\n";
    cout <<max<<"\n";
    return 0;
}