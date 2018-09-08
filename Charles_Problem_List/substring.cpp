#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    vector<int> to;
    char ch;
    int indegree;
} V[300002];

int dp[300002][30];

int n, m;

bool toposort() {
    memset(dp, 0, sizeof dp);
    queue<int> todo;

    int cnt = 0;

    for (int i = 1; i <= n ; i ++) {
        if (V[i].indegree == 0) {
            todo.push(i);
            cnt++;
            dp[i][V[i].ch] = 1;
        }
    }

    while (!todo.empty()) {
        int v = todo.front();
        todo.pop();
        for (int next : V[v].to) {
            
            for (int i = 0; i < 26; i ++) {
                dp[next][i] = max(
                    dp[next][i],
                    dp[v][i] + (V[next].ch == i)
                    );
            }

            V[next].indegree --;

            if (V[next].indegree == 0) {
                todo.push(next);
                cnt++;
            }
        }
    }

    return cnt == n;
}

int main() {
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; i ++) {
        cin >> c;
        V[i].ch = c - 'a';
        V[i].indegree = 0;
    }

    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        V[u].to.push_back(v);
        V[v].indegree ++;
    }

    bool r = toposort();

    if (r) {
        int r_ = -1;
        for (int i = 0; i <= n; i ++) {
            for (int j = 0; j < 26; j ++) {
                r_ = max(r_, dp[i][j]);
            }
        }
        cout << r_ << endl;
    } else {
        cout << -1 << endl;
    }
}