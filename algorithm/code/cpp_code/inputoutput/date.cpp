#include <stdio.h>

int main(int argc, const char * argv[]) {
    int x,y;
    int mon[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    char Day[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    scanf("%d %d",&x,&y);
    int date = 0;
    while(x--){
        date+=mon[x];
    }
    date+=y;
    printf("%s\n", Day[date%7]);
}
