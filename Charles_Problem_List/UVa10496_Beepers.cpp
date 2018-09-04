#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

int N;
int cnt;

int posX[22];
int posY[22];

int mem[2048][21];

int m_dis(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int dis(int a, int b) {
    return m_dis(posX[a], posY[a], posX[b], posY[b]);
}

int dp(bitset<11> bm, int cur) {
    int r = 1000000;
    int bm_i = (int) bm.to_ulong();
    if (mem[bm_i][cur] != -1) return mem[bm_i][cur];
    if (bm.none()) return dis(cur, 0);
    for (int i = 1; i < cnt + 1; i ++) {
        if (bm[i]) {
            // cout << "!" << cur << " " << dis(cur, i) << " " << i << endl;
            bitset<11> nbm = bm;
            r = min(r, dp(nbm.set(i, 0), i) + dis(cur, i));
        }
    }
    return mem[bm_i][cur] = r;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i ++) {
        int w, h;
        memset(mem, -1, sizeof mem);
        cin >> w >> h;
        cin >> posX[0] >> posY[0];
        
        cin >> cnt;
        for (int j = 0; j < cnt; j ++) {
            cin >> posX[1 + j] >> posY[1 + j];
        }
        bitset<11> bm;
        for (int j = 0; j < cnt + 1; j ++) {
            bm.set(j, 1);
        }
        bm.set(0,0);
        cout << "The shortest path has length " << dp(bm, 0) << endl;
    }
}