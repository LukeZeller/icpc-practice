// Problem on Kattis here: https://open.kattis.com/problems/hopscotch
#include <iostream>

#define min(X, Y) (((X) < (Y)) ? X : Y)

using namespace std;

long long MOD = 1000000007;

struct ff_int {
    long long val;
    ff_int(long long val) : val(val) {}
    ff_int operator+ (const ff_int& o) const {return {(val + o.val) % MOD};}
    ff_int operator* (const ff_int& o) const {return {(val * o.val) % MOD};}
    ff_int operator^ (long long e) const {
        if (e == 0) return {1};
        if (e == 1) return *this;
        ff_int sqrtish = *this ^ (e / 2);
        return sqrtish * sqrtish * (*this ^ (e % 2));
    }
    ff_int operator/ (const ff_int& o) const {return *this * (o^(MOD - 2));}
    explicit operator int() {return val;}
};

// Given orig = (N  + d - 1) choose (K + d), compute N choose K
// Works in O(d)
void update(ff_int& orig, int N, int K, int d) {
    orig = orig * (K + 1) / (N - K);
    for (int i = 1; i < d; ++i)
        orig = orig * (K + i + 1) / (N + i);
}

int solve(int n, int x, int y) {
    int Tx = n - x , Bx = Tx;
    int Ty = n - y, By = Ty;
    ff_int countx = 1, county = 1, s = 0;
    while (Bx >= 0 && By >= 0) {
        s = s + countx * county;
        Tx -= x - 1;
        Ty -= y - 1;
        Bx -= x;
        By -= y;
        update(countx, Tx, Bx, x);
        update(county, Ty, By, y);
    }
    return (int)s;
}

int main() {
    int n, x, y;
    cin >> n >> x >> y;

    cout << solve(n, x, y) << endl;
}


