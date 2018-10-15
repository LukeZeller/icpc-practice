// max flow

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

const int INF = 1031231234;

struct dinic
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> level, startEdge;

    dinic(int s)
    {
        sz = s, g.resize(sz);
        level.resize(sz), startEdge.resize(sz);
    }

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    bool buildLevelGraph(int source, int sink)
    {
        queue <int> q;
        q.push(source);
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (edge e: g[curr]) if (level[e.to] == -1 and residual(e.id) > 0)
            {
                q.push(e.to);
                level[e.to] = level[curr] + 1;
            }
        }
        return level[sink] != -1;
    }

    flowT blockingFlow(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink) return sent;
        for (; startEdge[curr] < g[curr].size(); startEdge[curr]++)
        {
            edge e = g[curr][startEdge[curr]];
            if (level[e.to] == level[curr] + 1 and residual(e.id) > 0)
            {
                flowT augment = blockingFlow(e.to, sink, min(sent, residual(e.id)));
                if (augment > 0)
                {
                    flow[e.id] += augment;
                    flow[e.id ^ 1] -= augment;
                    return augment;
                }
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0;
        while (buildLevelGraph(source, sink))
        {
            fill(startEdge.begin(), startEdge.end(), 0);
            while (flowT delta = blockingFlow(source, sink)) res += delta;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, p;
    while (cin >> n >> m >> p)
    {
        vector <vector<int>> children(n);
        for (int i = 0; i < n; i++)
        {
            int num;
            cin>>num;
            for (int j = 0; j < num; j++)
            {
                int x;
                cin>>x;
                children[i].push_back(--x);
            }
        }
        map <int, int> category;
        map <int, int> limits;
        for (int i = 0; i < p; i++)
        {
            int num;
            cin>>num;
            for (int j = 0; j < num; j++)
            {
                int x;
                cin>>x;
                category[--x] = i;
            }
            cin >> limits[i];
        }

        int sz = n + p + m + 2;
        dinic dnc(sz);
        int source = sz - 2, sink = sz - 1;
        for (int i = 0; i < n; i++)
        {
            dnc.addEdge(source, i, 1);
            for (int j: children[i])
            {
                int toy = j + n;
                dnc.addEdge(i, toy, 1);
            }
        }
        for (int i = 0; i < m; i++)
        {
            int toy = i + n;
            if (category.count(i))
            {
                int cat = category[i] + n + m;
                dnc.addEdge(toy, cat, 1);
            }
            else
            {
                dnc.addEdge(toy, sink, 1);
            }
        }
        for (int i = n + m; i < source; i++)
        {
            dnc.addEdge(i, sink, limits[i - n - m]);
        }
        int mf = dnc.maxflow(source, sink);
        cout<<mf<<'\n';

    }

    return 0;
}
