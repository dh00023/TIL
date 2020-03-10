#include <iostream>
#include <vector>

using namespace std;

// 중첩 반복문 대체하기
// 0부터 n까지 n개의 원소 중 네 개를 고르는 모든 경우의 수를 출력하는 코드
void ex2(int n){
    for(int i=0;i<n-3;++i)
        for(int j=i+1;j<n-2;++j)
            for(int k=j+1;k<n-1;++k)
                for(int l=k+1;l<n;++l)
                    cout << "( " << i << ", "<< j << ", "<< k << ", "<< l << " )";
}

void printPicked(vector<int>& picked){
    cout << "(";
    copy(picked.begin(), picked.end(), ostream_iterator<int>(cout,","));
    cout << ")" << endl;
}

void recursivePick(int n, int toPick, vector<int>& picked){
    if(toPick == 0){
        printPicked(picked);
        return;
    }
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for(int next = smallest; next < n; ++next){
        picked.push_back(next);
        recursivePick(n, toPick-1,picked);
        picked.pop_back();
    }
}
int main(void){
    // <cstdio>와의 동기화를 끄면 훨씬 빨라진다.
    // 고수준 입력 방식을 사용하면 코드가 간단해지지만, 이에 의한 속도 저하 또한 클 수 있다.
    cin.sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v;
    recursivePick(n,4,v);

    return 0;
}