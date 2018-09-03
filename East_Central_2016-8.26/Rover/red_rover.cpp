// brute force

#include <iostream>

using namespace std;

const int INF = 1231231234;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    while (getline(cin, s))
    {
        string mac = "";
        int best = INF;
        for (int i = 0; i < s.length(); i++)
        {

            for (int j = i; j < s.length(); j++)
            {

                mac = s.substr(i, j - i + 1);
                int cost = mac.length();
                int k;
                for (k = 0; k + mac.length() - 1 < s.length(); )
                {
                    if (s.substr(k, mac.length()) == mac)
                    {
                        ++cost;
                        k = k + mac.length();
                    }
                    else
                    {
                        ++k;
                        ++cost;
                    }
                }
                for (; k < s.length(); k++)
                {
                    ++cost;
                }

                if (cost < best)
                {
                    best = cost;
                }
            }
        }
        best = min(best, (int) s.length());
        cout<<best<<'\n';
    }

    return 0;
}
