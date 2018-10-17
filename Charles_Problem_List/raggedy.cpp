#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ios>

// I wrote one version in Python and TLEed
// so here I am rewriting this to C++

// and this is like redoing CLRS exercises

using namespace std;
vector<string> words;

int n; // total words
int l;

const int N = 505;

int pre[N][N];

int dp[N];
int sol[N];

const int INF = 1231231234;


// this function copied from stack overflow
vector<string> split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int w(int i, int j) {
    int x = 0;
    for (int k = i; k <= j; k ++) {
        x += words[k].size() + 1;
    }
    x--;
    return x;
}

int recons(int j) {
    int k;
    int i = sol[j];
    if (j == 0) k = 0;
    else k = recons(i) + 1;

    if (k > 0) {
        for (int q = i; q < j - 1 ; q ++) {
            cout << words[q] << " ";
        }
        cout << words[j - 1] << endl;
    }
    return k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> l) {
        if (l == 0) break;
        words = {};
        string ln;
        getline(cin,ln);
        while (getline(cin, ln)) {
            if (ln == "") {
                int n = words.size();
                
                for (int i = 0; i < n ; i ++) {
                    for (int j = 0; j < n ; j ++) {
                        if (j < i) continue;
                        int d = l - w(i, j);
                        if (d < 0) pre[i][j] = INF;
                        else {
                            if (j == n - 1) pre[i][j] = 0;
                            else pre[i][j] = d * d;
                        }
                    }
                }

                for (int x = 1; x <= n ; x ++) {
                    int m = INF;
                    for (int y = 1; y <= x; y ++) {
                        int val = dp[y - 1] + pre[y - 1][x - 1];
                        if (val < m) {
                            m = val;
                            sol[x] = y - 1;
                        }
                    }
                    dp[x] = m;
                }

                recons(n);

                cout << "===" << endl;
                break;
            } else {
                auto toks = split(ln, " ");
                words.insert(words.end(), toks.begin(), toks.end());
            }
        }
    }
}