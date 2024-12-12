#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n, target;
    cin >> n;
    cin >> target;

    vector<int> coins(n);

    for (int i = 0; i < n; i++)
        cin >> coins[i];

    vector<vector<int>> dp(n + 1, vector<int>(target + 1, INT_MAX));

    for (int i = 0; i < n; i++)
        dp[i][0] = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= target; j++)
        {
            int notTake = dp[i + 1][j];
            int take = INT_MAX;

            if (coins[i] <= j)
                take = dp[i][j - coins[i]];

            if (take != INT_MAX)
                take++;

            dp[i][j] = min(take, notTake);
        }
    }

    int ans = dp[0][target] == INT_MAX ? -1 : dp[0][target];
    cout << ans;

    return 0;
}