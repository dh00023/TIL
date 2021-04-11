"""
Binary Search 기본 구현
"""

def binary_search_loop(array, tgt, start, end):
    while start <= end:
        mid = (start+end)//2
        if array[mid] == tgt:
            return mid
        elif array[mid] < tgt:
            end = mid - 1
        else:
            start = mid + 1

    return None


def binary_search_recursion(array, tgt, start, end):
    if start > end:
        return None

    mid = (start+end) // 2
    if array[mid] == tgt:
        return mid
    elif array[mid] > tgt:
        return binary_search_recursion(array,tgt,start,mid-1)
    else:
        return binary_search_recursion(array, tgt, start+1, end)