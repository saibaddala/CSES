#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

void find(int val, unordered_set<int> &digits)
{
    while (val > 0)
    {
        digits.insert(val % 10);
        val = val / 10;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> dp(n + 1, INT_MAX);

    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        unordered_set<int> digits;
        find(i, digits);
        for (auto d : digits)
        {
            if (d != 0)
            {
                dp[i] = min(dp[i], 1 + dp[i - d]);
            }
        }
    }

    int ans = dp[n];

    cout << ans;
    return 0;
}