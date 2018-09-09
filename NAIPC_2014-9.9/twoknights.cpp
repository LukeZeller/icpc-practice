#include <iostream>
#include <string>
#include <ctype.h>
#include <cstring>

using namespace std;

char dic[10][4][2];
int offsets[8][2] = {
    {1,2},{2,1},
    {-1,2},{-2,1},
    {1,-2},{2,-1},
    {-1,-2},{-2,-1}
};

bool shiftMap[10][4];

string S;

void initDic() {
    string row = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    for (int x = 0; x < 10; x ++) {
        dic[x][0][0] = row[x];
        dic[x][0][1] = toupper(row[x]);
    }

    row = "asdfghjkl;";

    for (int x = 0; x < 9; x ++) {
        dic[x][1][0] = row[x];
        dic[x][1][1] = toupper(row[x]);
    }

    dic[9][1][0] = ';';
    dic[9][1][1] = ':';

    row = "zxcvbnm,./";
    string upper = "<>?";

    for (int x = 0; x < 10; x ++) {
        dic[x][2][0] = row[x];
        if (x < 7) {
            dic[x][2][1] = toupper(row[x]);
        } else {
            dic[x][2][1] = upper[x - 7];
        }
    }

    row = "!!      !!";
    for (int x = 0; x < 10; x ++) {
        dic[x][3][0] = row[x];
        dic[x][3][1] = row[x];
    }

    shiftMap[0][3] = true;
    shiftMap[1][3] = true;
    shiftMap[8][3] = true;
    shiftMap[9][3] = true;
}


bool flag = false;
bool prune[10][4][10][4][102];

void knights(int k1_x, int k1_y, int k2_x, int k2_y, int target) {
    if (flag) return;
    if (prune[k1_x][k1_y][k2_x][k2_y][target]) return;
    if (target >= S.size()) {
        flag = true;
        return;
    }

    prune[k1_x][k1_y][k2_x][k2_y][target] = true;

    char c = S[target];

    for (int i = 0; i < 8; i ++) {
        int ox = offsets[i][0];
        int oy = offsets[i][1];

        int nx = k1_x + ox;
        int ny = k1_y + oy;

        if (!(0 <= nx && nx < 10 && 0 <= ny && ny < 4)) continue;
        if (nx == k2_x && ny == k2_y) continue;
        if (shiftMap[nx][ny]) {
            knights(nx, ny, k2_x, k2_y, target);
        }

        if (dic[nx][ny][shiftMap[k2_x][k2_y]] == c) {
            knights(nx, ny, k2_x, k2_y, target + 1);
        }
    }

    for (int i = 0; i < 8; i ++) {
        int ox = offsets[i][0];
        int oy = offsets[i][1];

        int nx = k2_x + ox;
        int ny = k2_y + oy;

        if (!(0 <= nx && nx < 10 && 0 <= ny && ny < 4)) continue;
        if (nx == k1_x && ny == k1_y) continue;
        if (shiftMap[nx][ny]) {
            knights(k1_x, k1_y, nx, ny, target);
        }
        if (dic[nx][ny][shiftMap[k1_x][k1_y]] == c) {
            knights(k1_x, k1_y, nx, ny, target + 1);
        }
    }
}

int main() {
    initDic();
    while (getline(std::cin, S)) {
        flag = false;
        memset(prune, 0, sizeof prune);
        if (S == "*") break;
        knights(0,3,9,3,0);
        cout << flag << endl;
    }
    return 0;
}