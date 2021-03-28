"""
여행가 A는 N x N 크기의 정사각형 공간 위에 서 있다.
공간은 1 x 1 크기의 정사각형으로 나누어져 있으며, 가장 왼쪽 위 좌표는 (1,1), 가장 오른쪽 아래 좌표는 (N,N)에 해당한다.
여행가는 상, 하, 좌, 우 방향으로 이동할 수 있으며, 시작 좌표는 항상 (1,1)이다.
L : 왼쪽으로 한 칸 이동
R : 오른쪽으로 한 칸 이동
T : 위로 한 칸 이동
D : 아래로 한 칸 이동

이때 여행가가 N x N 크기의 정사각형 공간을 벗어나는 움직임은 무시된다.

N = 5, R->R->R->U->D->D이면, U는 공간을 벗어나므로 무시되며, A가 도착하는 위치는 (3,4)이다.
"""

n = int(input())

guides = { 'R': [0,1], 'L': [0, -1], 'U': [-1,0], 'D': [1,0] }
input_guide = map(str, input().split())


x, y = 1, 1

for g in input_guide:
    temp_x = x + guides[g][0]
    temp_y = y + guides[g][1]

    if temp_y<1 or temp_x<1 or temp_y>n or temp_x>n:
        continue

    x, y = temp_x, temp_y

print(x, y)
