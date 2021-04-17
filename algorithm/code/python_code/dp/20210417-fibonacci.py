# memorization
d = [0] * 100

# top-down
def fibonacci_recursion(x):

    # 1 or 2 는 1
    if x == 1 or x == 2:
        return 1

    # 이미 한번 호출된 적 있는 값은 기억해둔 값 반환
    if d[x]!=0:
        return d[x]

    # 한번도 호출된적 없는 값은 추가
    d[x] = fibonacci_recursion(x-1) + fibonacci_recursion(x-2)
    return d[x]

# print(fibonacci_recursion(6))

# bottom-up
def fibonacci_loop(n):
    d[1] = 1
    d[2] = 1

    for i in range(3,n+1):
        d[i] = d[i-1]+d[i-2]

    print(d[n])

fibonacci_loop(99)