// MCM-style dp (cyclic), gcd

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1231231234;
const int MAXN = 100;

int gcd(int a, int b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

int cost(vector <int> &a, int n)
{
    int dp[MAXN + 5][MAXN + 5];
    memset(dp, INF, sizeof(dp));

    int table[MAXN][MAXN];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            table[i][j] = gcd(a[i], a[j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        dp[i][(i + 1) % n] = 0;
    }
    for (int len = 3; len <= n; len++)
    {
        for (int i = 0; i < n; i++)
        {
            int j = (i + len - 1) % n;
            for (int dist = 1; ; dist++)
            {
                int k = (i + dist) % n;
                if (k == j)
                    break;

                int possible = dp[i][k] + dp[k][j] + table[i][j];
                dp[i][j] = min(dp[i][j], possible);
            }
        }
    }

    int best = INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) if (i != j)
        {
            int possible = dp[i][j] + dp[j][i] + table[i][j];
            best = min(best, possible);
        }
    }
    return best;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (true)
    {
        int n;
        cin>>n;
        if (n == 0)
            break;

        vector <int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        int sol = cost(a, n);
        cout<<sol<<'\n';
    }

    return 0;
}
