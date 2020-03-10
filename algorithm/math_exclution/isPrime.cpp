//소수 구하기
bool isPrime(int k){
    // 약수가 2개를 초과한다면 더 이상 탐색할 필요가 없다.
    // n이 소수라면 약수는 1과 n만 존재한다. 즉, 구간[2,n]에서 약수는 존재하지 않는다.
    // O(n^1/2)
    //
    for(int i=2;i*i<=k;i++){
        if(k%i==0)return false;
    }
    return true;
}
int main(){
	isPrime(4);
}