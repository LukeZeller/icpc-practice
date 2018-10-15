# codeforces: C - Candies
# TIL I should really not do n / 2 >= m, instead I should n >= m * 2.
def simulate(n, k):
    m = n
    cnt = 0
    while m > 0:
        m -= k
        cnt += k
        if m >= 0:
             m -= m // 10
    return cnt + m

def descent(n, k):
    s = simulate(n, k)
    while s * 2 >= n:
        k -= 1
        if (k == 0):
            break
        s = simulate(n, k)
    return k + 1

def binsearch(n, l, h):
    if h == l + 1:
        return descent(n, h)
    m = (l + h) // 2
    s = simulate(n, m)
    if s * 2 > n:
        return binsearch(n, l, m)
    else:
        return binsearch(n, m, h)

def start(n):
    return binsearch(n, 0, n)

print(start(int(input())))