"""
N X M 크기의 직사각형 형태의 미로 탈출
(1,1)에서 출발하며, (N,M) 위치에 출구가 존재한다.
한번에 한칸씩 이동할 수 있다.

미로벽은 0, 움직일 수 있는 길은 1로 표시되어 있다. 탈출하기위해 움직여야할 최소 값을 구해라.

입력조건
- 첫째 줄에 두 정수 N,M(4<=N,M<=200)이 주어진다. N개의 줄에는 각각 M개의 정수로 미로의 정보가 주어진다.
각각의 수들은 공백없이 붙어서 입력으로 제시되며, 시작칸과 마지막칸은 항상 1이다.

출력조건
- 첫째줄에 최소 이동 칸의 개수를 출력

ex)
5 6
101010
111111
000001
111111
111111

10
"""

# BFS 문제(queue 사용)

from collections import deque

n,m = map(int,input().split())

maze = []
for i in range(n):
    maze.append(list(map(int, input())))

# 상하좌우
dx = [1, -1, 0, 0]
dy = [0, 0, -1, 1]

def bfs(x,y):
    que = deque()
    que.append((x,y))

    while que:
        x,y = que.popleft()

        for i in range(4):
            temp_x = x + dx[i]
            temp_y = y + dy[i]
            if temp_x <0 or temp_x >= n or temp_y<0 or temp_y>=m:
                continue
            if maze[temp_x][temp_y] == 0:
                continue

            if maze[temp_x][temp_y] == 1:
                maze[temp_x][temp_y] = maze[x][y] + 1
                que.append((temp_x,temp_y))

    return maze[n-1][m-1]

print(bfs(0,0))