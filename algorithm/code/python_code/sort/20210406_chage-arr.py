"""
배열 A, B는 N개의 원소르 구성되어 있으며, 원소는 모두 자연수이다.
A의 원소와 B의 원소 하나를 골라서 두 원소를 서로 바꾸는 작업을 최대 K번 수행할 수 있다.
배열 A의 합이 최대가 되도록 하는것이 목표이다.

ex) N = 5, K = 3, A=[1,2,5,4,3], B=[5,5,6,6,5]
1. A의 1과 B의 6 바꾸기
2. A의 2와 B의 6 바꾸기
3. A의 3과 B의 5 바꾸기

A = [6,6,5,4,3]
B = [3,5,1,2,5]

26

입력 조건
- 첫번째 줄에 N, K가 공백으로 입력(1<=N<=100,000   0 <= K <= N)
- 두 번째 줄에 배열 A의 원소들이 공백으로 구분되어 입력된다. 모든 원소는 10,000,000보다 작은 자연수이다.
- 세 번째 줄에 배열 B의 원소들이 공백으로 구분되어 입력된다. 모든 원소는 10,000,000보다 작은 자연수이다.

출력 조건
- 최대 K번 바꿔치기 연산을 수행해 만들 수 있는 배열의 모든 원소의 합의 최댓갑
"""

n, k = map(int,input().split())

aArr = list(map(int, input().split()))
bArr = list(map(int, input().split()))

aArr.sort()
bArr.sort(reverse=True)

for i in range(k):
    if aArr[i] > bArr[i]:
        break
    aArr[i], bArr[i] = bArr[i], aArr[i]

print(sum(aArr))