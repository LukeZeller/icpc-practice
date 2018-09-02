t = int(input())

for t_i in range(t):
    args = input().split()
    args = [int(k) for k in args]
    n, m, a, b, c, d, r = args
    if m < 0:
        m, n = -m, -n
    itrs = [n]
    n_i = n
    while True:
        if n_i > 0:
            n_i = m - 2 * n_i
        else:
            n_i = -(m + 2 * n_i)
        if n_i in itrs:
            break
        itrs.append(n_i)
    ind = itrs.index(n_i)
    p, q = 1, 0
    ans = 0
    for i in reversed(range(len(itrs))):
        if itrs[i] <= 0:
            add = (a / r)
            mult = (b / r + (itrs[i] / m)**2)
        else:
            add = (c / r)
            mult = (d / r + (itrs[i] / m)**2)
        p *= mult
        q = q * mult + add
        if i == ind:
            ans = q / (1 - p)
            p, q = 1, 0
    print(p * ans + q)
