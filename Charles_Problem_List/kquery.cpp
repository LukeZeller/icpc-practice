#include <iostream>
#include <algorithm>
#include <ios>


// Thank god I have these:
// https://www.quora.com/What-is-a-segment-tree-and-what-are-its-applications
// http://codeforces.com/blog/entry/18051

// and this is like the first time I need to use fast io...
using namespace std;

const int N = 3e5 + 10 + 200000;

int q, n;

// a tagged union
struct value {
    int type;
    int value;
    int left;
    int right;
    int pos;
} values[N];

// now to write the segment tree
int t[2 * N];
void modify(int p, int value) {
    for (t[p += n] = value; p > 1; p >>= 1) {
        t[p >> 1] = t[p] + t[p^1];
    }
}

int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += t[l++];
        if (r & 1)
            res += t[--r];
    }
    return res;
}

const int NAT = 0;
const int KQ = 1;

int r[200010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i ++) {
        int v;
        cin >> v;
        values[i] = {NAT, v, 0, 0, i + 1};
    }

    cin >> q; 
    for (int i = 0; i < q; i ++) {
        int a, b, k;
        cin >> a >> b >> k;
        values[i + n] = {KQ, k, a, b, i};
    }

    int total = n + q;
    sort(values, values + total,
        [](const value & lhs, const value & rhs) {
            if (lhs.value != rhs.value) {
                return lhs.value > rhs.value;
            } else {
                // if NAT then placed before KQ
                return lhs.type > rhs.type;
            }
        });

    for (int i = 0; i < total; i ++) {
        value v = values[i];
        if (v.type == NAT) {
            modify(v.pos, 1);
        } else {
            r[v.pos] = query(v.left, v.right + 1);
        }
    }

    for (int i = 0; i < q; i ++) {
        cout << r[i] << "\n";
    }
}