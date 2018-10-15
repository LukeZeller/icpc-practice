#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> ii;

const int INF = 1231231234;

struct edge{int to, id;};

typedef vector<vector<edge>> graph;
typedef int flowT;


struct fordfulkerson
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> visited;

    fordfulkerson(int s)
    {
        sz = s, g.resize(sz);
        visited.resize(sz);
    }

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id)
    {
        return capacities[id] - flow[id];
    }

    int dfs(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink) return sent;

        if (visited[curr]) return 0;

        visited[curr] = true;

        for (edge e : g[curr]) if (residual(e.id) > 0)
        {
            flowT augment = dfs(e.to, sink, min(sent, residual(e.id)));
            if (augment > 0)
            {
                flow[e.id] += augment;
                flow[e.id ^ 1] -= augment;
                return augment;
            }
        }

        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0, delta;
        visited.assign(sz, 0);
        while (delta = dfs(source, sink))
        {
            res += delta;
            fill(visited.begin(), visited.end(), 0);
        }
        return res;
    }
};

int dist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector <ii> bot(n), cour(m);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        bot[i] = {x, y};
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        cour[i] = {x, y};
    }
    int rx, ry;
    cin >> rx >> ry;

    int sz = n + m + 2;
    int source = sz - 2, sink = sz - 1;

    fordfulkerson ffa(sz);

    for (int i = 0; i < n; i++)
    {
        ffa.addEdge(source, i, INF);
    }
    for (int i = 0; i < m; i++)
    {
        ffa.addEdge(i + n, sink, INF);
    }

    int mn = INF;
    int sm = 0;
    for (int i = 0; i < n; i++)
    {
        auto restToBottle = dist(rx, ry, bot[i].first, bot[i].second);
        sm += 2 * restToBottle;
        for (int j = 0; j < m; j++)
        {
            auto courToBottle = dist(cour[j].first, cour[j].second, bot[i].first, bot[i].second);

            if (restToBottle > courToBottle)
                ffa.addEdge(i, j + n, (restToBottle - courToBottle));

            auto cost = -(restToBottle - courToBottle);
            mn = min(mn, cost);

            //cout << i << " to " << j + n << " with : " << restToBottle - courToBottle << endl;
        }
    }

    auto res = ffa.maxflow(source, sink);

    if (res == 0)
    {
        cout << mn + sm << endl;
    }
    else
    {
        //cout << res << '\n';
        cout << sm - res << '\n';
    }
}
