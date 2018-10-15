#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include <ios>
#include <iomanip>
#include <algorithm>

using namespace std;

// the union-find data structure
struct ele {
    int parent;
    int rank;
};

map<int, ele> forest;

void makeSet(int id) {
    if (forest.find(id) == forest.end()) {
        ele n = {id, 0};
        forest[id] = n;
    }
}

int find(int id) {
    if (!(forest[id].parent == id)) forest[id].parent = find(forest[id].parent);
    return forest[id].parent;
}

void merge(int a, int b) {
    int a_root = find(a);
    int b_root = find(b);
    if (a_root == b_root) return;

    if (forest[a].rank < forest[b].rank) {
        forest[a_root].parent = b_root;
    } else if (forest[a].rank > forest[b].rank) {
        forest[b_root].parent = a_root;
    } else {
        forest[b_root].parent = a_root;
        forest[a_root].rank ++;
    }
}


double posX[101];
double posY[101];

int N;
int M;


double dis(int a, int b) {
    return hypot(posX[a] - posX[b], posY[a] - posY[b]);
}

vector<tuple<int, int>> edges;

int main() {
    cin >> N;
    while(N--) {
        forest = {};
        cin >> M;
        for(int i = 0; i < M; i ++) {
            cin >> posX[i] >> posY[i];
        }

        edges = {};

        for (int i = 0; i < M; i ++) {
            for (int j = 0; j < i; j ++) {
                edges.push_back(make_tuple(i, j));
            }
        }

        sort(
            edges.begin(), edges.end(),
            [](const tuple<int, int> & l, const tuple<int, int> & r) -> bool {
                return dis(get<0>(l), get<1>(l)) < dis(get<0>(r), get<1>(r));
            });
        for (int i = 0; i < M; i ++) {
            makeSet(i);
        }

        vector<tuple<int, int> > r;

        for (tuple<int, int> uv : edges) {
            int u = get<0>(uv);
            int v = get<1>(uv);
            if (find(u) != find(v)) {
                r.push_back(uv);
                merge(u, v);
            }
        }

        double cnt = 0;
        for (tuple<int, int> uv : r) {
            int u = get<0>(uv);
            int v = get<1>(uv);
            cnt += dis(u, v);
        }

        cout <<  std::fixed << setprecision(2) << cnt << endl;

        if (N >= 1) cout << endl;
    }
}