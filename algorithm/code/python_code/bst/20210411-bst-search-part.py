"""
부품 찾기

전자 매장에 정수 형태의 고유한 번호가 있는 부품 N개가 있다.
어느 날 손님이 M개 종류의 부품을 대량으로 구매 요청이와, 주인은 부품 M개의 종류를 모두 확인해 견적서를 작성해야한다.
이때 가게안에 부품이 모두 있는지 확인하는 프로그램을 구현해라.(모든 부품이 있으면 yes, 없으면 no)

ex)
N = 5
[8, 3, 7, 9, 2]

M = 3
[5, 7, 9]

no

입력 조건
- 첫째 줄에 정수 N 입력(1<=N<=1,000,000)
- 둘째 줄에 공백으로 구분하여 N개의 정수 입력
- 셋째 줄에 정수 M 입력(1<=M<=100,000)
- 넷째 줄에 공백으로 구분하여 M개의 정수 입력

출력 조건
첫째 줄에 공백으로 구분하여 각 부품이 존재하면 yes, 없으면 no
"""
import sys

n = int(input())
array = list(map(int,sys.stdin.readline().rstrip().split()))

m = int(input())
tgt = list(map(int,sys.stdin.readline().rstrip().split()))

array.sort()


def binary_search(array, target, start, end):
    if start > end:
        return False

    mid = (start+end)//2

    if array[mid] == target:
        return True
    elif array[mid] > target:
        return binary_search(array,target,start,end-1)
    else:
        return binary_search(array, target, start+1, end)


for i in tgt:
    ans = binary_search(array,i,0,n-1)
    if ans:
        print('yes',end=' ')
    else:
        print('no',end=' ')


# 이진 탐색 외에 계수 정렬 or 집합을 이용해서도 풀 수 있는 문제
# 계수 정렬

n = int(input())
array = [0] * 1000001 # 최대입력가능한 N의 값만큼 배열 생성

for i in input().split():
    array[int(i)] = 1

m = int(input())
tgt = list(map(int,input().split()))

for i in tgt:
    if array[int(i)] == 1:
        print('yes', end=' ')
    else:
        print('no', end=' ')


# 집합

n = int(input())
array = set(map(int, input().split()))

m = int(input())
tgt = list(map(int,input().split()))

for i in tgt:
    if i in array:
        print('yes', end=' ')
    else:
        print('no', end=' ')
