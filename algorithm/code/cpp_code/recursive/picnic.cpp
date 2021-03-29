// https://algospot.com/judge/problem/read/PICNIC

#include <iostream>

using namespace std;

int n;
bool areFriends[10][10];

// taken[i] : i번째 학생이 짝을 이미 찾은 경우 true
int countParings(bool taken[10]){
    int freeStudent = -1;
    for(int i=0; i<n; ++i){
        if(!taken[i]){
            freeStudent = i;
            break;
        }
    }

    // 남은 학생이 없는 경우 이므로 return
    if(freeStudent == -1) return 1;

    int result = 0;
    for(int pairStudent = freeStudent +1; pairStudent<n; ++pairStudent){
        if(!taken[pairStudent] && areFriends[freeStudent][pairStudent]){
            taken[freeStudent] = taken[pairStudent] = true;
            result += countParings(taken);
            taken[freeStudent] = taken[pairStudent] = false;
        }
    }
    return result;
}

int main(void){
    // <cstdio>와의 동기화를 끄면 훨씬 빨라진다.
    // 고수준 입력 방식을 사용하면 코드가 간단해지지만, 이에 의한 속도 저하 또한 클 수 있다.
    cin.sync_with_stdio(false);
    
    int c; // c<=50
    bool taken[10];
    cin >> c;
    
    while(c--){
        int m; //  (2 <= n <= 10), 0 <= m <= n*(n-1)/2
        cin >> n >> m;

        // false로 초기화
        memset(areFriends, false, sizeof(areFriends));
        memset(taken, false, sizeof(taken));
        for(int i=0; i<m; i++){
            int student1, student2;
            cin >> student1 >> student2;
            areFriends[student1][student2] = areFriends[student2][student1] = true;
        }
        int result = countParings(taken);
        cout << result << endl;
    }
    
    return 0;
}