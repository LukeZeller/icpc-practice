#include <iostream>
#include <vector>
#include <queue>
#include <ios>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

int N, M;

const int MN = 1e5+1;

// if co-processor
bool co[MN];
int tt;

void toposort(graph &g) //PS: modify return type as needed
{
    int n = g.size();
    queue <int> q;
    queue <int> c;
    vector <int> inDegree(n), sorted;

    for (int i = 0; i < n; i++) for (edge e: g[i])
        inDegree[e.to]++;
    
    // push all nodes with indegree 0
    for (int i = 0; i < n; i++) if (inDegree[i] == 0) {
        if (co[i]) c.push(i);
        else q.push(i);
    }

    while (!q.empty() || !c.empty()) {
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            // sorted.push_back(curr);
            for (edge e: g[curr]) if (--inDegree[e.to] == 0) {
                if (co[e.to]) c.push(e.to);
                else q.push(e.to);
            }
        }

        if (!c.empty()) tt++;
        while (!c.empty()) {
            int curr = c.front();
            c.pop();
            for (edge e: g[curr]) if (--inDegree[e.to] == 0) {
                if (co[e.to]) c.push(e.to);
                else q.push(e.to);
            }
        }
    }
}

void addEdge(graph &g, int i, int j) {
    g[i].push_back({j});
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    graph g(N);

    for (int i = 0; i < N; i ++) {
        cin >> co[i];
    }

    for (int i = 0; i < M; i ++) {
        int u, v;
        cin >> u >> v;
        addEdge(g, v, u);
    }
    
    toposort(g);
    cout << tt << endl;
}
