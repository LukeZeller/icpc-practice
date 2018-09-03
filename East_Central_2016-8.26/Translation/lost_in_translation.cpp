// shortest path w/ modified BFS

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct edge{int to, w;};
typedef vector<vector<edge>> graph;

const int INF = 1231231234;

struct state
{
    int node, dist, cost;
};

vector <int> bfs(graph &g, int start)
{
    queue <state> q;
    q.push({start, 0, 0});

    vector <int> visited(g.size());
    vector <int> dist(g.size(), INF);
    vector <int> cost(g.size(), INF);

    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();

        if (curr.dist < dist[curr.node])
        {
            dist[curr.node] = curr.dist;
            cost[curr.node] = curr.cost;
        }
        else if(curr.dist == dist[curr.node])
        {
            cost[curr.node] = min(cost[curr.node], curr.cost);
        }
        for (edge e: g[curr.node]) if (!visited[e.to] or curr.dist + 1 <= dist[e.to])
        {
            state nxt = {e.to, curr.dist + 1, e.w};
            visited[e.to] = true;
            q.push(nxt);
        }
    }

    for (int i = 0; i < g.size(); i++)
    {
        if (!visited[i])
            cost[0] = INF;
    }

    return cost;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m)
    {
        map <string, int> names;
        names["English"] = 0;
        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;
            names[s] = i + 1;
        }
        graph g(n + 1);
        for (int i = 0; i < m; i++)
        {
            string a, b; int w;
            cin>>a>>b>>w;
            int na = names[a], nb = names[b];
            g[na].push_back({nb, w});
            g[nb].push_back({na, w});
        }
        auto costs = bfs(g, 0);
        bool hasInf = false;
        for (int i: costs)
        {
            if (i == INF)
                hasInf = true;
        }
        if (hasInf)
        {
            cout<<"Impossible"<<'\n';
        }
        else
        {
            int acc = 0;
            for (int i: costs)
            {
                acc += i;
            }
            cout<<acc<<'\n';
        }
    }
    
    return 0;
}
