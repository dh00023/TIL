#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> board;
const int coverType[4][3][2] = {
    {{0,0}, {1,0}, {0,1}},
    {{0,0}, {0,1}, {1,1}},
    {{0,0}, {1,0}, {1,1}},
    {{0,0}, {1,0}, {1,-1}}
};

// board[y][x]를 coverType으로 덮거나, 덮었던 블록을 지우는 함수
// willCover은 채울지 지울지 여부 1이면 채우기, -1이면 지우기.
bool set(vector<vector<int>>& board, int y, int x, int type, int willCover){
    bool ok = true;
    for(int i=0; i< 3; ++i){
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        // board를 벗어나는 경우 false
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[y].size()){
            ok = false;
        // 또는 검은 돌을 덮는 경우 false
        }else if ((board[ny][nx] += willCover) > 1){
            ok = false;
        }
    }
    return ok;
}


int canCover(vector<vector<int>>& board){
    int x=-1, y=-1;
    for(int i=0; i<board.size(); ++i){
        for(int j=0; j<board[i].size(); ++j){
            if(board[i][j]==0){
                y = i;
                x = j;
                break;
            }

        }
        if(y != -1) break;
    }
    // 모든 칸을 채웠으므로 1 return;
    if( y == -1 ) return 1;
    int result = 0;
    for(int type = 0; type < 4; ++type){
        if(set(board, y, x, type, 1)){
            // 해당 타입이 빈부분이면 result에 추가
            result += canCover(board);
        }
        set(board, y, x, type, -1);
    }
    return result;
}

int main(void){
    // <cstdio>와의 동기화를 끄면 훨씬 빨라진다.
    // 고수준 입력 방식을 사용하면 코드가 간단해지지만, 이에 의한 속도 저하 또한 클 수 있다.
    cin.sync_with_stdio(false);
    
    int c; // c<=30
    cin >> c;
    
    while(c--){
        int h, w;// height, width (1 <= H,W <= 20)
        cin >> h >> w;

        board.resize(h);  // vector 크기 조정
        for(int i=0;i<h;++i){
            string str;
            cin >> str;
        
            board[i].resize(w);

            for(int j=0;j<w;++j){
                if(str.at(j)=='#')board[i][j]=1;
                else board[i][j]=0;
            }
        }

        int result = canCover(board);
        cout << result << endl;
        
    }
    
    return 0;
}
