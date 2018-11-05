/*
* I think this should also be possible using heavy-light decomposition?
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

vector<vector<int>> children(50002);
int w[50002];

struct binaryLift
{
    int sz, h;
    graph g;
    vector <vector<int>> table;
    vector <int> depths;

    binaryLift(graph &gr)
    {
        g = gr, sz = g.size(), h = 0, calcHeight();
        table.resize(sz, vector<int>(h, -1)), depths.resize(sz);
        build(0);
    }

    void calcHeight(){while (1 << h < sz) h++;}

    void build(int curr, int depth = 0)
    {
        depths[curr] = depth;
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
        }
        for (edge e: g[curr]) if (e.to != table[curr][0])
        {
            table[e.to][0] = curr;
            children[curr].push_back(e.to);
            build(e.to, depth + 1);
        }
    }

    int lca(int l, int r)
    {
        if (depths[l] > depths[r]) swap(l, r);
        for (int i = h - 1; i >= 0; i--)
        {
            if ((1 << i) & (depths[r] - depths[l]))
                r = table[r][i];
        }
        if (l == r) return l;
        for (int i = h - 1; i >= 0; i--) if (table[l][i] != table[r][i])
        {
            l = table[l][i], r = table[r][i];
        }
        return table[l][0];
    }

    int distance(int i, int j)
    {
        return depths[i] + depths[j] - 2 * depths[lca(i, j)];
    }

    // returns -1 if no parent
    int parent(int i)
    {
        if (i == 0) return -1;
        return table[i][0];
    }
};

void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j});
    g[j].push_back({i});
}

int mx = 0;
void dfs(graph &g, int cur = 0)
{
    for (auto c : children[cur]) {
        dfs(g, c);
        w[cur] += w[c];
    }
    mx = max(mx, w[cur]);
}

int n, k;

int main()
{

    ifstream in ("maxflow.in");
    ofstream out ("maxflow.out");
    in >> n >> k;
    graph g(n);

    for (int i = 0 ; i < n-1 ; i ++) {
        int u, v;
        in >> u >> v;
        addEdge(g, u - 1, v - 1);
    }

    auto bl = binaryLift(g);
    for (int i = 0; i < k ; i ++) {
        int u, v;
        in >> u >> v;
        u--; v--;
        int a = bl.lca(u, v);
        w[u]++;
        w[v]++;
        int p = bl.parent(a);
        if (bl.parent(a) != -1) {
            w[p]--;
        }
        w[a]--;
    }
    dfs(g);

    // for (int i = 0; i < n ; i ++) {
    //     cout << w[i] << endl;
    // }
    // cout << mx << endl;
    out << mx << endl;
    // cout << mx << endl;
}
