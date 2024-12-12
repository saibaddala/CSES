#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int MOD = 1e9 + 7;

int main()
{
    int n, target;
    cin >> n;
    cin >> target;

    vector<int> coins(n);

    for (int i = 0; i < n; i++)
        cin >> coins[i];

    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

    for (int i = 0; i < n; i++)
        dp[i][0] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= target; j++)
        {
            int notTake = dp[i + 1][j];
            int take = 0;

            if (coins[i] <= j)
                take = dp[i][j - coins[i]];

            dp[i][j] = (take % MOD + notTake % MOD) % MOD;
        }
    }

    int ans = dp[0][target];
    cout << ans;

    return 0;
}