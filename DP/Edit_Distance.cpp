#include <iostream>
#include <vector>
#include <climits>

using namespace std;
int minDistance(string word1, string word2)
{
    int m = word1.length(), n = word2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    dp[m][n] = 0;
    for (int j = 0; j < n; j++)
        dp[m][j] = n - j;
    for (int i = 0; i < m; i++)
        dp[i][n] = m - i;

    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (word1[i] == word2[j])
                dp[i][j] = dp[i + 1][j + 1];
            else
            {
                int del = 1 + dp[i + 1][j];
                int rep = 1 + dp[i + 1][j + 1];
                int ins = 1 + dp[i][j + 1];

                dp[i][j] = min(min(del, rep), ins);
            }
        }
    }
    return dp[0][0];
}

int main()
{
    string s1, s2;

    cin >> s1;
    cin >> s2;

    int ans = minDistance(s1, s2);

    cout << ans;

    return 0;
}