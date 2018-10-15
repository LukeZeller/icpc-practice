// math

#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (true)
    {
        int n;
        cin>>n;
        if (n == 0)
            break;

        int sol = 0;
        for (int i = 1; i * i <= 2 * n; i++)
        {
            int f = i;
            if (2 * n % f == 0)
            {
                int f2 = 2 * n / f;

                int sum = f + f2;
                if (sum & 1)
                {
                    int b = (sum - 1) / 2;
                    int a = f2 - b;

                    if (a >= 2)
                        sol++;
                }
            }
        }
        cout<<sol<<'\n';
    }

    return 0;
}
