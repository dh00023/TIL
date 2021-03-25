# 거시름돈 500, 100, 50, 10 동전이 무한히 존재한다. 이때 손님에게 거슬러줘야할 돈이 N원일때 거슬러줘야 할 동전의 최소 개수를 구해라.
# 단, 거슬러 줘야 할 돈 N은 항상 10의 배수이다.

N = 1260
cnt = 0


coin_types = [500, 100, 50, 10]

for coin in coin_types:
	count += N // coin # 몫 반환
	N %= coin # 나머지 반환


print(count)


# 시간복잡도 : O(K)