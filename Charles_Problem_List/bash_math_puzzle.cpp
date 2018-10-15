#include <iostream>
#include <numeric>
#include <ios>

int n, q;
const int N = 10e5 + 10;
int t[2 * N];


/*
 * I can't seem to really grok the "better" segment tree implementation.
 * So I used another segment tree tutorial's segment tree.
 * I guess I should know how to actually implement segment trees.
*/

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

void build(int l, int r, int x) {
    if (l == r) {
        int v;
        cin >> v;
        t[x] = v;
    } else {
        int m = (l + r) / 2;
        build(l, m, x * 2);
        build(m + 1, r, x * 2 + 1);
        t[x] = gcd(t[x<<1], t[x<<1|1]);
    }
}

void modify(int l, int r, int x, int a, int b) {
    if (l == r) {
        t[x] = b;
    } else {
        int m = (l + r) / 2;
        if ( a <= m ) {
            modify(l, m, x<<1, a, b);
        } else {
            modify(m+1,r,x<<1|1,a,b);
        }
        t[x] = gcd(t[x<<1], t[x<<1|1]);
    }
}

int cnt;
void query(int l, int r, int x, int a, int b, int v) {
    if (cnt >= 2) return;
    if (l == r) {
        cnt ++;
    } else {
        int m = (l + r) / 2;
        if ( a <= m && t[x<<1] % v) {
            query(l, m, x<<1, a, b, v);
        }
        if ( b >= m + 1 && t[x<<1|1] % v && cnt <= 1) {
            query(m+1, r, x<<1|1, a, b, v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    build(1, n, 1);
    cin >> q;
    for (int i = 0; i < q; i ++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            cnt = 0;
            query(1, n, 1, l, r, x);
            if (cnt <= 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            int i, y;
            cin >> i >> y;
            modify(1, n, 1, i, y);
        }
    }
}