#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int a, b;
    cin >> a;
    cin >> b;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1));

    for (int i = 1; i <= min(a, b); i++)
        dp[i][i] = 0;

    for (int r = 1; r <= a; r++)
    {
        for (int c = 1; c <= b; c++)
        {
            if (r != c)
            {
                int ans = INT_MAX;

                for (int k = r - 1; k > 0; k--)
                {
                    ans = min(ans, 1 + dp[k][c] + dp[r - k][c]);
                }

                for (int k = c - 1; k > 0; k--)
                {
                    ans = min(ans, 1 + dp[r][k] + dp[r][c - k]);
                }

                dp[r][c] = ans;
            }
        }
    }

    int ans = dp[a][b];

    cout << ans;

    return 0;
}