#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

typedef long long ll;

bool isOperator(char c)
{
    return c == '+' or c == '-' or c == '*' or c == '=';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;
    for (int test = 1; test <= T; test++)
    {
        string s;
        cin>>s;

        string nums[3];
        bool neg[3];
        for (int t = 0; t < 3; t++)
        {
            neg[t] = false;
            nums[t] = "";
        }

        int stage = 0;
        bool prevOpp = true;

        char op;
        bool found[10];
        memset(found, 0, sizeof(found));
        for (int i = 0; i < s.length(); i++)
        {
            if (prevOpp and s[i] == '-')
            {
                neg[stage] = true;
                prevOpp = false;
            }
            else if (!isOperator(s[i]))
            {
                nums[stage] += s[i];
                if (s[i] != '?')
                    found[s[i] - '0'] = true;
                prevOpp = false;
            }
            else
            {
                if (stage == 0)
                    op = s[i];
                stage++;
                prevOpp = true;
            }
        }

        bool startq = false;
        for (int t = 0; t < 3; t++)
        {
            if (nums[t][0] == '?' and (neg[t] or nums[t].length() > 1))
                startq = true;
        }

        int res = -1;
        for (int dig = startq ? 1 : 0; dig < 10; dig++) if (!found[dig])
        {
            string cpy[3];
            int vals[3];
            for (int i = 0; i < 3; i++)
            {
                cpy[i] = "";
                for (char c: nums[i])
                {
                    if (c == '?')
                        cpy[i] += '0' + dig;
                    else
                        cpy[i] += c;
                }

                stringstream iss(cpy[i]);
                iss >> vals[i];
                if (neg[i])
                    vals[i] = -vals[i];
            }

            bool feasible = false;
            if (op == '-')
            {
                feasible = vals[0] - vals[1] == vals[2];
            }
            else if(op == '+')
            {
                feasible = vals[0] + vals[1] == vals[2];
            }
            else if(op == '*')
            {
                feasible = vals[0] * vals[1] == vals[2];
            }
            if (feasible)
            {
                res = dig;
                break;
            }
        }
        cout<<res<<'\n';
    }

    return 0;
}
