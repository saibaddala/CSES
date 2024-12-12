#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    int n, m;
    cin >> n;
    cin >> m;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        if (nums[i] > m || (i > 0 && nums[i] != 0 && nums[i - 1] != 0 && abs(nums[i] - nums[i - 1]) > 1))
        {
            cout << "0";
            return 0;
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 2, 0));

    if (nums[n - 1] == 0)
    {
        for (int val = 1; val <= m; val++)
        {
            dp[n - 1][val] = 1;
        }
    }
    else
    {
        dp[n - 1][nums[n - 1]] = 1;
    }

    for (int i = n - 2; i >= 0; i--)
    {
        if (nums[i] == 0)
        {
            for (int val = 1; val <= m; val++)
            {
                dp[i][val] = ((dp[i + 1][val - 1] % MOD + dp[i + 1][val] % MOD) % MOD + dp[i + 1][val + 1] % MOD) % MOD;
            }
        }
        else
        {
            int val = nums[i];
            dp[i][val] = ((dp[i + 1][val - 1] % MOD + dp[i + 1][val] % MOD) % MOD + dp[i + 1][val + 1] % MOD) % MOD;
        }
    }

    int ans = 0;

    for (int i = 1; i <= m; i++)
        ans = (ans % MOD + dp[0][i] % MOD) % MOD;

    cout << ans;

    return 0;
}