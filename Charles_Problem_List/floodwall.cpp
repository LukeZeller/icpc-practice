// I really don't like this problem, its sample test cases are so weak

#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <ios>

using namespace std;

typedef unsigned long long ll;

typedef pair<ll, ll> r;

int N;
r rs[200010];
ll starts[200010];
ll finishes[200010];
int nxt[200010];
ll dp[200010];
string l;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(cin >> N) {
        getline(cin, l);

        for (int i = 0; i < N; i ++) {
            getline(cin, l);
            stringstream stream(l);
            
            if (l.length() == 2) {
                ll n;
                stream >> n;
                rs[i].first = n / 10;
                rs[i].second = n % 10;
            } else {
                stream >> rs[i].first >> rs[i].second;
            }
        }

        sort(rs, rs + N,
            [](const r & a, const r & b) -> bool {
                if (a.first == b.first) {
                    return a.second > b.second;
                } else {
                    return a.first < b.first;
                }
            });

        for (int i = 0; i < N; i ++) {
            starts[i] = rs[i].first;
            finishes[i] = rs[i].second;
        }
        
        for (int i = 0; i < N; i ++) {
            int ind = lower_bound(starts, starts + N, finishes[i]) - starts;
            nxt[i] = ind;
        }
        memset(dp, 0, sizeof(dp));
        dp[N] = 0;
        for (int i = N - 1 ; i >= 0; i --) {
            dp[i] = max(dp[i + 1], finishes[i] - starts[i] + dp[nxt[i]]);
        }
        cout << dp[0] << endl;
    }
}