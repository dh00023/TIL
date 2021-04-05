x = [7,5,9,0,3,1,6,2,4,8]

"""
선택정렬 : 가장 작은 수를 찾아 차례대로 정렬
시간 복잡도 : O(N^2)
"""
def selection_sort(array):
    for i in range(0,len(array)-1):
        min = i;
        for j in range(i+1,len(array)):
            if array[j] < array[min]:
                min = j;

        array[i], array[min] = array[min], array[i];



result = selection_sort([7,5,9,0,3,1,6,2,4,8])


"""
삽입정렬 : 모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를 찾아 삽입함으로써 정렬을 완성하는 알고리즘
삽입 정렬은 필요할 때만 위치를 바꾸므로 데이터가 거의 정렬되어 있을 때 훨씬 효율적
시간복잡도 : 
- 최악의 경우 O(N^2)
- 최선의 경우 O(N)
"""

def insert_sort(array):
    # print(array)
    for i in range(1,len(array)):
        for j in range(i,0,-1):
            if array[j] < array[j-1]:
                array[j], array[j-1] = array[j-1], array[j]
            else:
                break
    # print(array)
    return array


print(insert_sort([7,5,9,0,3,1,6,2,4,8]))

"""
퀵 정렬 : pivot을 기준으로 pivot보다 작은수, 큰수를 나누어 정렬 한다.
"""

def quick_sort(array):
    if len(array) <= 1:
        return array

    pivot = array[0]
    temp = array[1:]

    left = [i for i in temp if i < pivot]
    right = [i for i in temp if i > pivot]

    return quick_sort(left) + [pivot] + quick_sort(right)


# print(quick_sort(x))

"""
계수 정렬 : 특정한 케이스의 경우 사용
"""

def count_sort(array):
    count = [0] * (max(array)+1)

    for i in array:
        count[i]+=1

    for j in range(len(count)):
        for x in range(count[j]):
            print(j, end=' ')

print(count_sort([7,5,9,0,3,1,6,2,9,1,4,8,0,5,2]))


def counting_sort(arr, digit):
    n = len(arr)

    # 배열의 크기에 맞는 output 배열을 생성하고 10개의 0을 가진 count란 배열을 생성한다.
    output = [0] * n
    count = [0] * 10

    # 각 자리수에 맞게 count를 증가시켜준다.
    for i in range(0, n):
        index = int(arr[i] / digit)
        count[(index) % 10] += 1

    # count 배열에 앞의 수를 차례대로 더해 각 자릿수를 정해준다.
    # ex) 123,134,151,121
    # before : [ 0, 2, 0, 1, 1 ]
    # after : [ 0, 2, 2, 3, 4 ]
    for i in range(1, 10):
        count[i] += count[i - 1]

    # 각 자릿수 별로 output 배열에 차례대로 정렬한다.
    # ex) 1의 자리 예제
    # [ 0, 121, 0, 0]
    # [ 151, 121, 0, 0]
    # [ 151, 121, 0, 134]
    # [ 151, 121, 123, 134]
    i = n - 1
    while i >= 0:
        index = int(arr[i] / digit)
        output[count[(index) % 10] - 1] = arr[i]
        count[(index) % 10] -= 1
        i -= 1

    # arr에 output을 할당한다.
    return output


# Method to do Radix Sort
def radix_sort(arr):
    # arr 배열중에서 최대값을 가져와 자릿수를 파악한다.
    # ex) 최대값이 9833 이면 1000까지
    maximum = max(arr)
    # 자릿수마다 countingSorting을 시작한다.
    digit = 1
    while int(maximum / digit) > 0:
        arr = counting_sort(arr, digit)
        digit *= 10

    return arr



# arr = [4, 2, 1, 5, 7, 2]
print(radix_sort([170, 45, 75, 90, 802, 24, 2, 66]))

