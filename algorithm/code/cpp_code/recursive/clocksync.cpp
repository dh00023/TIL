// https://algospot.com/judge/problem/read/CLOCKSYNC

#include <iostream>
#include <vector>

using namespace std;
// 시계는 12, 3, 6, 9 로 계속 반복되므로, 어떤 스위치라도 0~3번 누른다
const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS+1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",
    "...xxx...x...x.."
};

bool areAligned(const vector<int>& clocks){
    for(int i=0; i<CLOCKS; ++i){
        if(clocks[i] != 12){
            return false;
        } 
    }
    return true;
}

void push(vector<int>& clocks, int switchNum){
    for(int clock = 0; clock < CLOCKS; ++clock){
        if(linked[switchNum][clock] == 'x'){
            clocks[clock] += 3;
            if(clocks[clock] == 15)clocks[clock]=3;
        }
    }
}
int solve(vector<int>& clocks, int switchNum){
    if(switchNum == SWITCHES) return areAligned(clocks) ? 0 : INF;
    int result = INF;
    for(int count = 0; count < 4; ++count){
        result = min(result, count + solve(clocks, switchNum+1));
        push(clocks, switchNum);
    }
    return result;
}

int main(){
    cin.sync_with_stdio(false);

    int c;
    cin >> c; // c<=30
    while(c--){
        vector<int> clocks;
        for(int i = 0; i<CLOCKS; ++i){
            int num;
            cin >> num;
            clocks.push_back(num);
        }

        int result = solve(clocks, 0);
        cout << result << endl;
    }

    return 0;
}