#include <iostream>
#include <vector>

using namespace std;
const int MOD = 1e9 + 7;
int main()
{
    int n;
    cin >> n;

    if (n <= 1)
    {
        cout << "1";
        return 0;
    }

    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        for (int d = 1; d <= 6; d++)
        {
            if (i - d >= 0)
                dp[i] = (dp[i] % MOD + dp[i - d] % MOD) % MOD;
        }
    }

    cout << dp[n];
    return 0;
}