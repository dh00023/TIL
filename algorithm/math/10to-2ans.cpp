#include <cstdio>
void go(int n) {
    if(n==0) {
        return;
    }
    if (n%2 == 0) {
        go(-(n/2));
        printf("0");
    } else {
        if (n > 0) {
            go(-(n/2));
        } else {
            go((-n+1)/2);
        }
        printf("1");
    }
}
int main(){
    int n;
    scanf("%d\n",&n);
    if(n==0) {
        printf("0\n");
    } else {
        go(n);
    }
    return 0;
}