#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n, budget;
    cin >> n;
    cin >> budget;

    vector<int> prices(n), pages(n);

    for (int i = 0; i < n; i++)
        cin >> prices[i];
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= budget; j++)
        {
            int notTake = dp[i + 1][j];
            int take = 0;

            if (prices[i] <= j)
                take = pages[i] + dp[i + 1][j - prices[i]];

            dp[i][j] = max(notTake, take);
        }
    }

    int ans = dp[0][budget];
    cout << ans;

    return 0;
}