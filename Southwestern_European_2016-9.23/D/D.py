N, D, C = input().split()
N, D, C = int(N), int(D), int(C)

ans_dp = [[[-1 for i in range(C + 1)] for j in range(C + 1)] for k in range(C + 1)]

def choose(N, K):
    if N < K or K < 0:
        return 0
    if K == 0 or N == K:
        return 1
    return N * choose(N - 1, K - 1) / K

def expected(i, j, k):
    if ans_dp[i][j][k] >= 0:
        return ans_dp[i][j][k]
    if j == 0 and (i == 0 or k == 0):
        ans = 0
    else:
        ans = 0
        p = 0
        for i_it in range(i + 1):
            for j_it in range(j + 1):
                for k_it in range(k + 1):
                    m1 = choose(i, i - i_it) * choose(j, j - j_it) * choose(k, k - k_it)
                    m2 = choose(N - i - j - k, D - i - j - k + i_it + j_it + k_it)
                    p_trans = m1 * m2 / choose(N, D)
                    if i == i_it and j == j_it and k == k_it:
                        p = p_trans
                    else:
                        ans += p_trans * expected(i_it, j_it, k_it)
        ans = (1 + ans) / (1 - p)
    ans_dp[i][j][k] = ans
    return ans

overlap = len(set(input().split()) &  set(input().split()))
print(expected(C - overlap, overlap, C - overlap))

