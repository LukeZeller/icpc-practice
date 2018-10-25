#include <iostream>
#include <vector>
#include <deque>
#include <ios>

using namespace std;

#define ll long long

struct edge{int to;};
typedef vector <vector<edge>> graph;

graph getTranspose(graph &g)
{
    graph t(g.size());
    for (int i = 0; i < g.size(); i++) for (edge e: g[i])
    {
        t[e.to].push_back({i});
    }
    return t;
}

struct kosarajuSCC
{
    int n, sz = 0; //sz is # of scc -> caution!! don't use components.size()
    graph g, t;
    vector <bool> visited; deque <int> ordered;
    vector <vector<int>> components; vector <int> category; /*PS*/

    kosarajuSCC(graph &gr)
    {
        g = gr, t = getTranspose(gr), n = g.size();
        visited.resize(n), components.resize(n), category.resize(n); /*PS*/
        getScc();
    }

    void getScc()
    {
        for (int i = 0; i < n; i++) if (!visited[i])
            ordering(i);
        for (int i: ordered) if (visited[i])
            categorize(i), ++sz;
    }

    void ordering(int curr)
    {
        if (visited[curr]) return;
        visited[curr] = true;
        for (edge e: g[curr]) if (!visited[e.to])
            ordering(e.to);
        ordered.push_front(curr);
    }

    void categorize(int curr)
    {
        if (!visited[curr]) return;
        visited[curr] = false;
        components[sz].push_back(curr), category[curr] = sz; /*PS*/
        for (edge e: t[curr]) if (visited[e.to])
            categorize(e.to);
    }
};

void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j});
}


const int M = 1e5 + 2;
const int MOD = 1e9 + 7;
int n, m;
int cost[M];
const int INF = 1e9+2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    graph g(n);

    for (int i = 0; i < n ; i ++) {
        cin >> cost[i];
    }

    cin >> m;

    for (int i = 0 ; i < m ; i ++) {
        int u, v;
        cin >> u >> v;
        addEdge(g, u - 1, v - 1);
    }

    auto scc = kosarajuSCC(g);
    
    ll ways = 1;
    ll tt = 0;
    for (int i = 0; i < scc.sz; i++)
    {
        int minMoney = INF;
        int minMult = 0;
        for (int j : scc.components[i]) {
            int m = cost[j];
            if (m < minMoney) {
                minMoney = m;
                minMult = 0;
            }

            if (m == minMoney) {
                minMult++;
            }
        }
        tt += minMoney;
        ways = (ways * minMult) % MOD;
    }

    cout << tt << " " << ways << endl;
}