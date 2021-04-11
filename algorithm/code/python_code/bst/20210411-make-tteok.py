"""
떡의 길이가 일정하지 않은 떡의 길이를 맞춰야한다.
절단기에 높이를 지정하면 줄지어진 떡을 한 번에 절단한다. 높이가 지정한 높이(H)보다 긴 경우 H의 윗부분이 잘릴 것이며, 낮은 떡은 잘리지 않는다.

ex)
19, 14, 10, 17 cm인 떡이 나란히 있고 지정 높이가 15cm로 자른다면
남은 떡 : 15, 14, 10 ,15 cm
잘린 떡 : 4, 0, 0, 2 cm
이 될 것이다.
이떄 손님은 잘린떡의 길이 6cm만큼 가져가게 된다.
손님이 왔을때 요청한 떡이 총 길이가 M일 때 적어도 M만큼의 떡을 얻기 위해 절단기에 설정할 수 있는 높이의 최대값을 구해라

입력 조건:
- 첫째 줄에 떡의 개수 N과 요청한 떡의 길이 M이 주어진다.(1 <= N <= 1,000,000  1 <= M <= 2,000,000,000)
- 둘째 줄에 떡의 개별 높이가 주어진다. 떡 높이의 총합은 항상 M이상이여야하며, 높이는 10억보다 작거나 같은 양의 정수 혹은 0이다.

출력 조건:
- 적어도 M만큼의 떡을 집에 가져가기 위해 절단기에 설정할 수 있는 높이의 최댓값을 출력해라.

"""



def binary_search(arr, tgt, s, e):

    ans = 0
    while s <= e:
        lefts = 0
        mid = (s + e) // 2

        for i in arr:
            if i>mid:
                lefts += (i-mid)

        if tgt == lefts:
            ans = mid
            break
        elif tgt > lefts:
            e = mid -1
        else:
            s = mid + 1

    print(ans)

n, m = map(int, input().split())
arr = list(map(int, input().split()))
binary_search(arr, m, 0, max(arr))




