"""
게임 캐릭터가 맵 안에서 움직이는 시스템을 개발 중이다. 캐릭터가 있는 장소는 1 X 1의 정사각형으로 이뤄진 N X M 크기의 직사각형으로,
각 칸은 육지 또는 바다이다. 캐릭터는 동서남북 중 한 곳을 바라본다.

맵의 각 칸은 (A,B)로 나타낼 수 있고, A는 북쪽으로부터 떨어진 칸의 개수, B는 서쪽으로부터 떨어진 칸의 개수이다.
캐릭터는 상하좌우로 움직일 수 있고, 바다로 되어있는 공간에는 갈 수 없다.

1단계. 현재 위치에서 현재 방향을 기준으로 왼쪽 방향(반시계 방향으로 90도 회전한 방향)부터 차례대로 갈 곳을 정한다.
2단계. 캐릭터의 바로 왼쪽 방향에 아직 가보지 않은 칸이 존재한다면, 왼쪽 방향으로 회전한 다음 왼쪽으로 한칸을 전진한다.
      왼쪽 방향에 가보지 않은 칸이 없다면, 왼쪽 방향으로 회전만 수행하고 1단계로 돌아간다.
3단계. 만약 네 방향 모두 이미 가본 칸이나 바다로 되어있는 칸인 경우에는 바라보는 방향을 유지한 채로 한 칸 뒤로 가고 1단계로 돌아간다.
      단, 이때 뒤쪽 방향이 바다인 칸이라 뒤로 갈 수 없는 경우에는 움직임을 멈춘다.

입력조건
- 첫째 줄에 맵의 세로 크기 N과 가로크기 M을 공백으로 구분해 입력한다.(3 <= N,M <= 50)
- 둘째 줄에 게임 캐릭터가 있는 칸의 좌표 (A, B)와 바라보는 방향 d가 각각 서로 공백으로 구분해 주어진다.
    0: 북, 1: 동, 2: 남, 3: 서
- 셋째 줄부터 맵이 육지인지 바다인지에 대한 정보가 주어진다. N개의 줄에 맵의 상태가 북쪽부터 남쪽 순서대로, 각 줄의 데이터는 서쪽부터 동쪽 순서대로 주어진다.
  맵의 외각은 항상 바다다.
    0: 육지, 1:바다
- 처음에 캐릭터가 위치한 칸의 상태는 항상 육지이다.

출력조건
- 첫째 줄에 이동을 마친 후 캐릭터가 방문한 칸의 수 출력

ex)
4 4     # 4X4 맵
1 1 0   # (1,1)에 북(0)을 보고 서있음
1111
1001
1101
1111

3
"""

n, m = map(int, input().split())

dp = [ [0]*m for _ in range(n) ] # LC를 이용해서 2차원 list 생성

x, y, di = map(int, input().split())

dx = [-1,0,1,0] # 북동남서
dy = [0,1,0,-1] # 북동남서

game_map = []
for i in range(n):
    game_map.append(list(map(int, input().split())))

dp[x][y] = 1


def turn_left():
    global di
    if di == 0:
        di = 3
    else:
        di -= 1

cnt = 1
turn_cnt = 0

while(True):
    turn_left()
    turn_cnt += 1

    temp_x = x+dx[di]
    temp_y = y+dy[di]

    if 0 <= temp_x < m and 0<=temp_y<n and game_map[temp_x][temp_y] == 0 and dp[temp_x][temp_y] == 0 :
        x,y = temp_x,temp_y
        dp[x][y] = 1
        turn_cnt = 0
        cnt += 1

        continue

    if turn_cnt == 4:
        temp_x, temp_y = x-dx[di], y-dy[di]
        if temp_x < 0 or temp_y < 0 or temp_y >= m or temp_x >=n or game_map[temp_x][temp_y] == 1:
            break
        else:
            x, y = temp_x, temp_y
            turn_cnt = 0


print(cnt)
