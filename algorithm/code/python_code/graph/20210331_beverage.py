"""
N X M 크기의 얼음틀이 있다.
구멍이 뚫려 있는 부분은 0, 칸막이가 존재하는 부분은 1로 표시된다.
구멍이 뚤ㅎ려 있는 부분끼리 상,하,좌,우로 붙어 있는 경우 서로 연결되어 있는 것으로 간주한다. 이때 얼음 틀의 모양이 주어졌을 때 생성되는 총 아이스크림의 개수를 구하는 프로그램을 작성해라

ex)
00110
00011
11111

00000

3

입력조건
- 첫 번째 줄에 얼음 틀의 세로 길이 N과 가로 길이 M이 주어진다. (1<= N,M <= 1000)
- 두 번째 줄부터 N+1 번째 줄까지 얼음 틀의 형태가 주어진다.
- 이때 구멍이 뚫려있는 부분은 0, 아닌부분은 1이다.

출력조건
- 한번에 만들 수 있는 아이스크림 개수를 구하시오.
"""

n, m = map(int, input().split())

ice_case = []
for i in range(n):
    ice_case.append(list(map(int,input())))

def dfs(x,y):
    if(x<0 or x>=n or y<0 or y>=m):
        return False
    if(ice_case[x][y]==0):
        ice_case[x][y] = 1
        dfs(x, y - 1)
        dfs(x - 1, y)
        dfs(x + 1, y)
        dfs(x, y + 1)
        return True
    else:
        return False

result = 0

for i in range(n):
    for j in range(m):
        if dfs(i,j) == True:
            result += 1

print(result)


