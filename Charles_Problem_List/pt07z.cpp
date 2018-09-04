#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
int N;

vector<vector<int> > tree;

int mem_[10001];
int mem[10000];

int dp_(int n) {
    if (mem_[n] != -1) return mem_[n];
    int r = 0;
    for (int u : tree[n]) {
        r = max(r, 1 + dp_(u));
    }
    return mem_[n] = r;
}

int dp(int n) {
    if (mem[n] != -1) return mem[n];
    int r = -1;
    r = max(r, dp_(n));
    for (int u : tree[n]) {
        for (int v : tree[n]) {
            if (u == v) continue;
            r = max(r, dp_(u) + dp_(v) + 2);
        }
    }

    for (int u : tree[n]) {
        r = max(r, dp(u));
    }
    return mem[n] = r;
}


int main() {
    cin >> N;
    tree.reserve(N+1);
    memset(mem_, -1, sizeof mem_);
    memset(mem, -1, sizeof mem);
    for (int i = 0; i < N; i ++) {
        tree.push_back({});
    }
    for (int i = 0; i < N-1; i++) {
        int u,v;
        cin >> u >> v;
        tree[u].push_back(v);
    }
    cout << dp(1) << "\n";
}