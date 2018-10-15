#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define newl '\n'
#define REP(i, x) for(int i = 0; i < x; i++)

const ll LINF = 123123123123123123;
const int INF = 1231231234;
const int MOD = 1000000007;
const double EPS = .000001;

const int MAXN = 120;

int gcd(int a, int b)
{
    if (a < b) return gcd(b, a);
    if (!a || !b) return a + b;
    return gcd(a % b, b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> A(n);

    for (int& a_i : A)
        cin >> a_i;

    int cnt = 0;
    for (int gcd_itr = 1; gcd_itr <= 100; ++gcd_itr) {
        int curr_gcd = 0;
        for (int a_i : A) {
            if (a_i % gcd_itr != 0) {
                curr_gcd = 0;
                continue;
            }
            curr_gcd = gcd(curr_gcd, a_i);
            if (curr_gcd == gcd_itr) {
                ++cnt;
                break;
            }
        }
    }

    cout << cnt << newl;
    
    return 0;
}
