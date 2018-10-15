/*
* the checking part is ugly... 
*/

#include <iostream>
#include <cstring>

using namespace std;

int K, n, m, k;

int tmp;
int dp[31];

int solve(int i) {
    if (i == 0) return 0;
    if (dp[i] > -1) return dp[i];
    int sm = !(i >= m && (i - m) % k == 0);
    for (int j = 1; j < i; j ++) {
        if (j >= m && (j - m) % k == 0) {
            continue;
        };
        sm += solve(i - j);
    }
    return dp[i] = sm;
}

int main () {
    cin >> K;
    int cnt = 0;
    while(K--) {
        cnt++;
        memset(dp, -1, sizeof dp);
        cin >> tmp;
        cin >> n >> m >> k;
        cout << cnt << " " << solve(n) << endl;
    }
}