def ans(arr, w):
    return arr[0]**2 + arr[1]**2 + (arr[2] + w)**2 + 7 * arr[0]

n = int(input())
for n_i in range(n):
    a, b, c, w = input().split()
    tok = sorted([int(a), int(b), int(c)])
    w = int(w)
    ans_arr = []

    ans_arr.append(ans(tok, w))

    add_min = min(tok[1] - tok[0], w)
    tok[0] += add_min
    w -= add_min
    ans_arr.append(ans(tok, w))

    add_min = min(2*(tok[2] - tok[1]), w)//2
    tok[0] += add_min
    tok[1] += add_min
    w -= 2*add_min
    ans_arr.append(ans(tok, w))

    tok[0] += w // 3
    tok[1] += w // 3
    tok[2] += w // 3
    w -= 3 * (w // 3)
    ans_arr.append(ans(tok, w))

    print(max(ans_arr))
