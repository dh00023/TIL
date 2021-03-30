"""
factorial(n)

n! = n * (n-1) * .. * 2 * 1

0! = 1
1! = 1
"""

def factorial_recursive(n):
    if n <= 1:
        return 1
    return n * factorial_recursive(n-1)


def factorial_iterative(n):
    result = 1
    for i in range(1, n+1):
        result *= i
    return result

print(factorial_recursive(5))
print(factorial_iterative(5))