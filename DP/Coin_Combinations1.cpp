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

    vector<int> dp(target + 1);

    dp[0] = 1;

    for (int i = 1; i <= target; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            dp[i] += (coins[j] <= i) ? dp[i - coins[j]] : 0;
            dp[i] = dp[i] % MOD;
        }
    }

    int ans = dp[target];
    cout << ans;

    return 0;
}