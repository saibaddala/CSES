#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

void bfs(int i, int j, vector<vector<int>> &building)
{
    int m = building.size();
    int n = building[0].size();
    vector<int> dir = {-1, 0, 1, 0, -1};

    queue<pair<int, int>> q;

    q.push({i, j});
    building[i][j] = 1;

    while (!q.empty())
    {
        int row = q.front().first, col = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++)
        {
            int nRow = row + dir[k];
            int nCol = col + dir[k + 1];
            if (nRow >= 0 && nRow < m && nCol >= 0 && nCol < n && building[nRow][nCol] == 0)
            {
                building[nRow][nCol] = 1;
                q.push({nRow, nCol});
            }
        }
    }
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int m, n;
    cin >> m >> n;

    vector<vector<int>> building(m, vector<int>(n));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char ch;
            cin >> ch;
            if (ch == '#')
                building[i][j] = 1;
            else
                building[i][j] = 0;
        }
    }

    long long ans = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (building[i][j] == 0 && ++ans)
                bfs(i, j, building);
        }
    }

    cout << ans;
    return 0;
}
