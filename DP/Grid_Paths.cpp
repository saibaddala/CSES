#include <iostream>
#include <vector>

using namespace std;
const int MOD = 1e9 + 7;

int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<int> rPlus1(n + 1, 0);

    for (int r = m - 1; r >= 0; r--)
    {
        int cPlus1 = 0;
        vector<int> curr(n + 1, 0);
        for (int c = n - 1; c >= 0; c--)
        {
            if (obstacleGrid[r][c] == 1)
            {
                curr[c] = cPlus1 = 0;
            }
            else if (r == m - 1 && c == n - 1)
            {
                curr[c] = 1;
                cPlus1 = 1;
            }
            else
            {
                curr[c] = (rPlus1[c] % MOD + cPlus1 % MOD) % MOD;
                cPlus1 = curr[c];
            }
        }
        rPlus1 = curr;
    }

    return rPlus1[0];
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char ch;
            cin >> ch;
            grid[i][j] = ch == '*' ? 1 : 0;
        }
    }
    int ans = uniquePathsWithObstacles(grid);
    cout << ans;

    return 0;
}