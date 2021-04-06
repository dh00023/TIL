"""
N명의 학생의 학생 이름과 성적 정보가 있다.
각 학생의 이름과 성적 정보가 주어졌을 떄 성적이 낮은 순서대로 학생의 이름을 출력하는 프로그램을 작성해라.

입력조건
- 첫 번째 줄에 학생 수 N 입력(1<=N<=100,000)
- 두번째 줄부터 N+1 번째 줄에는 학생의 이름을 나타내는 문자열 A와 학생의 성적을 나타내는 점수 B가 공백으로 구분되어 입력된다.
  A의 길이와 학생의 성적은 100 이하의 자연수이다.

출력조건
- 모든 학생의 이름을 성적이 낮은 순서대로 출력한다. 성적이 동일한 학생의 순서는 자유롭게 출력
"""

n = int(input())

arr = []
for i in range(n):
    student = tuple(input().split())
    arr.append(student)


#
# def setting(tup):
#     return tup[1]

# arr.sort(key=setting)

arr.sort(key=lambda std: std[1])
for std in arr:
    print(std[0], end=' ')

