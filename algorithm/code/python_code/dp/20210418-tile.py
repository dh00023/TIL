"""
가로 길이가 N 새로길이가 2인 직사각형 타일이 있다.
이 타일을 1X2, 2X1, 2X2 작은 타일로 채우려고 한다.

이때 큰 타일을 채우는 모든 경우의 수를 구하는 프로그램을 작성해라.

입력조건
- 첫째줄에 N이 주어진다.(1 <= N <= 1000)
출력조건
- 첫째 줄에 2XN크기 바닥을 채우는 방법의 수를 796796으로 나눈 나머지를 구해라
"""

n = int(input())

d = [0] * (n+1)

d[1] = 1

for i in range(2 , n+1):
    # 짝수의 경우에는 이전 CASE의 1X2 타일을 양옆에 더하는 케이스에 추가로 2x2가 추가로 생김(+1)
    if i % 2 == 0:
        d[i] = (d[i-1] * 2 + 1) % 796796
    # 홀수의 경우에는 이전 CASE * 2(1X2)타일 양옆에 추가하는 케이스에 1X2 * n으로 이루어진 케이스가 중복으로 생기므로 -1
    else:
        d[i] = (d[i-1] * 2 - 1) % 796796


print(d[n])



