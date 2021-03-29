#include <iostream>
#include <string>
using namespace std;

//두 수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.
void plus1(){
    int a,b;
    cin >> a >> b;
    cout << a+b;
}

//첫째 줄에 A, 둘째 줄에 B가 주어진다. (0 < A, B < 10)
void plus2(){
    int a,b;
    cin >> a;
    cin >> b;
    cout << a+b;
}

//첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A,B < 10)
//출력 : 각 테스트 케이스마다 A+B를 출력한다.
void plus3(){
    int t;
    int a,b;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&a,&b);
        printf("%d\n",a+b);
    }
}

//입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A,B < 10)
void plus4(){
    int a,b;
    while(scanf("%d %d",&a,&b)==2){
        printf("%d\n",a+b);
    }
}

//A와 B가 모두 0인 경우에 프로그램을 종료한다.
void plus5(){
    int a,b;
    while(scanf("%d %d",&a,&b)==2){
        if(a==0 && b ==0) break;
        printf("%d\n",a+b);
    }
}
/*
 첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. A와 B는 콤마(,)로 구분되어 있다. (0 < A,B < 10)
 */
void plus6(){
    int t;
    int a,b;
    scanf("%d",&t);
    while(t--){
        scanf("%d,%d",&a,&b);
        printf("%d\n",a+b);
    }
}

//각 테스트 케이스마다 "Case #x: "를 출력한 다음, A+B를 출력한다. 테스트 케이스 번호는 1부터 시작한다.
void plus7(){
    int a,b,t;
    int n=0;
    scanf("%d",&t);
    while(t--){
        n++;
        scanf("%d %d",&a,&b);
        printf("Case #%d: %d\n",n,a+b);
    }
}

//각 테스트 케이스마다 "Case #x: A + B = C" 형식으로 출력한다. x는 테스트 케이스 번호이고 1부터 시작하며, C는 A+B이다.
void plus8(){
    int a,b,t;
    int n=0;
    scanf("%d",&t);
    while(t--){
        n++;
        scanf("%d %d",&a,&b);
        printf("Case #%d: %d + %d = %d\n",n,a,b,a+b);
    }
}

// 각자리수의 합 구하기
void sum(){
    int N, sum=0;
    scanf("%d",&N);
    int a;
    while(N--){
        scanf("%1d",&a);
        sum += a;
    }
    printf("%d",sum);
}

//자연수 N이 주어졌을 때, 1부터 N까지 한 줄에 하나씩 출력하는 프로그램을 작성하시오.
void Nfrom1(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        printf("%d\n",i);
    }
}
void Nto1(){
    int n;
    scanf("%d",&n);
    for(int i=n;i>=1;i--){
        printf("%d\n",i);
    }
}
//N을 입력받은 뒤, 구구단 N단을 출력하는 프로그램을 작성하시오. 출력 형식에 맞춰서 출력하면 된다.
void gugudan(){
    int N;
    scanf("%d",&N);
    for(int i=1;i<=9;i++){
        printf("%d * %d = %d\n",N,i,N*i);
    }
}

//n이 주어졌을 때, 1부터 n까지 합을 구하는 프로그램을 작성하시오.
void sum1N(){
    int n,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        sum+=i;
    }
    printf("%d",sum);
}

//N개의 정수가 주어진다. 이 때, 최솟값과 최댓값을 구하는 프로그램을 작성하시오.
void maxnum(){
    int n,a,max=0x80000000,min=0x7fffffff;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a);
        if(a>max)max=a;
        if(a<min)min=a;
    }
    printf("%d %d",min,max);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //star11();
    plus1();
    plus2();
    
    return 0;
}
