//문자열 N개가 주어진다. 이 때, 문자열에 포함되어 있는 소문자, 대문자, 숫자, 공백의 개수를 구하는 프로그램을 작성하시오. 각 문자열은 알파벳 소문자, 대문자, 숫자, 공백으로만 이루어져 있다.
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void count_s(){
    string s;
    while(getline(cin, s)){
        int upper=0,lower=0,number=0,space=0;
        for(int i=0;i<s.size();i++){
            if('a'<=s[i]&&s[i]<='z'){
                lower+=1;
            }else if('A'<=s[i]&&s[i]<='Z'){
                upper+=1;
            }else if('0'<=s[i]&&s[i]<='9'){
                number+=1;
            }else if(s[i]==' ') space+=1;
        }
        printf("%d %d %d %d\n",lower,upper,number,space);
    }
    
}