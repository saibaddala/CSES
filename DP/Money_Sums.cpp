#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    int n;
    cin >> n;

    vector<int> coins(n);

    for (int i = 0; i < n; i++)
        cin >> coins[i];

    sort(coins.begin(), coins.end());

    int sum = 0;

    for (auto i : coins)
        sum += i;

    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= sum; j++)
        {
            bool notTake = dp[i + 1][j];
            bool take = false;

            if (coins[i] <= j)
                take = dp[i + 1][j - coins[i]];

            dp[i][j] = take | notTake;
        }
    }

    int cnt = 0;
    vector<int> sums;

    for (int s = 1; s <= sum; s++)
    {
        if (dp[0][s] == true)
        {
            cnt++;
            sums.push_back(s);
        }
    }

    cout << cnt << endl;

    for (auto s : sums)
        cout << s << " ";

    return 0;
}