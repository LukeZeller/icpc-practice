def down(n, d, arr):
    if d < 0:
        return 0;
    if arr[n][d] > 0:
        return arr[n][d]
    ans = 0
    if n == 1:
        ans = d + 1
    elif d == 0:
        ans = 1
    else:
        ans = down(n, d - 1, arr) + down(n - 1, d, arr)
    arr[n][d] = ans
    return ans

def hill(n, d, arr, d_arr):
    if arr[n][d] > 0:
        return arr[n][d]
    ans = 0
    if n == 1:
        ans = 1
    else:
        for i in range(d, 10):
            ans += hill(n - 1, i, arr, d_arr)
        ans += down(n - 1, d - 1, d_arr)
    arr[n][d] = ans
    return ans
        
t = int(input())

for t_i in range(t):
    numStr = input()
    n = len(numStr)
    num = [0]
    isHill = True
    isDown = False
    for c in numStr:
        num.append(int(c))
        if num[-1] < num[-2]:
            isDown = True
        elif num[-1] > num[-2] and isDown:
            isHill = False

    if not isHill:
        print("-1")
    else:
        h = [[0 for i in range(10)] for j in range(n + 1)]
        d = [[0 for i in range(10)] for j in range(n + 1)]
        ans = 0
        isDown = False
        for i in range(n):
            if num[i] < num[i + 1]:
                for j in range(num[i], num[i + 1]):
                    ans += hill(n - i, j, h, d)
            elif num[i] > num[i + 1]:
                isDown = True
            ans += down(n - i, min(num[i], num[i + 1]) - 1, d)
        print(ans)
