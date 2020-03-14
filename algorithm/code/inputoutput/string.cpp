#include <iostream>
#include <string>
using namespace std;

//입력이 주어진다. 입력은 최대 100줄로 이루어져 있고, 알파벳 소문자, 대문자, 공백, 숫자로만 이루어져 있다. 각 줄은 100글자를 넘지 않으며, 빈 줄은 주어지지 않는다. 또, 각 줄은 공백으로 시작하지 않고, 공백으로 끝나지 않는다.
void prin1(){
    char s[101];
    
    while(scanf("%[^\n]\n", s)==1){
        printf("%s\n",s);
    }
}

//공백포함해서 똑같이 출력하기
void prin2(){
    char c;
    while ((c = getchar()) && c != EOF) {
        printf("%c",c);
    }

//알파벳 소문자와 대문자로만 이루어진 길이가 N인 단어가 주어진다. 한 줄에 10글자씩 끊어서 출력하는 프로그램을 작성하시오.
char c[100];
void prin10(){
    while (scanf("%10s",c)==1) {
        printf("%s\n",c);
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //star11();a
    
    return 0;
}