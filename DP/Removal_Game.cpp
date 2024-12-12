#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i; j < n; j++)
        {
            if (i == j)
                dp[i][j] = nums[i];
            else if (i == j - 1)
                dp[i][j] = max(dp[i][i], dp[j][j]);
            else
            {
                long long takeFront = nums[i] + min(dp[i + 2][j], dp[i + 1][j - 1]);
                long long takeBack = nums[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);

                dp[i][j] = max(takeFront, takeBack);
            }
        }
    }

    long long ans = dp[0][n - 1];

    cout << ans;
    return 0;
}
