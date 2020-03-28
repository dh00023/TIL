// https://algospot.com/judge/problem/read/BOGGLE
#include <iostream>
#include <vector>

using namespace std;

const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0};
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1};
char board[5][5];

bool inRange(int y, int x){
    if (y < 0 || y > 4 || x < 0 || x > 4) return false;
    else return true;
}

bool hasWord(int y, int x, const string& word){
    // basecase1 : (y,x)가 범위안에 포함안되면 무조건 false
    if(!inRange(y,x)) return false;
    // basecase2 : 위치 (y,x)에 있는 글자가 원하는 글자가 아닌경우 false
    if(board[y][x] != word[0]) return false;
    // 단어길이가 1인경우 성공
    if(word.size() == 1) return true;

    for(int direction = 0; direction < 8; ++direction){
        int nextX = x + dx[direction];
        int nextY = y + dy[direction];

        if(hasWord(nextY, nextX, word.substr(1))){
            return true;
        }
    }
}



int main(void){
    // <cstdio>와의 동기화를 끄면 훨씬 빨라진다.
    // 고수준 입력 방식을 사용하면 코드가 간단해지지만, 이에 의한 속도 저하 또한 클 수 있다.
    cin.sync_with_stdio(false);
    
    int C;
    int N;
    cin >> C;
    
    while(C--){
        for(int i=0; i<5; i++){
            cin >> board[i];
        }
    }
    
    cin >> N;

    while(N--){
        string word;
        cin >> word;
        bool isFoundOut = false;

        for(int i=0;i<5;i++){
            for(int j=0; j<5; j++){
                isFoundOut = hasWord(i, j, word);
                if( isFoundOut ) break;
            }
            if( isFoundOut ) break;
        }
        
        cout << word;
        if(isFoundOut){
            cout << " YES" << endl;
        }else{
            cout << " No" << endl;
        }
    }
    return 0;
}

// 시간 복잡도는 최대 8개의 이웃이 있고, 탐색은 단어의 길이 N에대해 N-1단계 진행된다.
// 우리가 검사하는 후보수는 최대 8^(N-1) = O(8^N)이다. => 매우 느림
// 단어의 길이가 조금만이라도 길어질 경우 다른 방법을 써야한다.