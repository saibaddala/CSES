#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

pair<int, string> bfs(vector<vector<char>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<int> dir = {-1, 0, 1, 0, -1};
    vector<char> direction = {'U', 'R', 'D', 'L'};
    vector<int> par(m * n, -1);

    vector<vector<char>> visitedBy(m, vector<char>(n));
    queue<pair<char, pair<int, int>>> q;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'M')
            {
                q.push({'M', {i, j}});
                grid[i][j] = '#';
                visitedBy[i][j] = 'M';
                par[i * n + j] = i * n + j;
            }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'A')
            {
                q.push({'A', {i, j}});
                grid[i][j] = '#';
                visitedBy[i][j] = 'A';
                par[i * n + j] = i * n + j;
            }

    int len = -1;
    string path = "";

    int dR, dC;
    bool found = false;

    while (!q.empty() && !found)
    {
        int size = q.size();
        while (size--)
        {
            char by = q.front().first;
            int row = q.front().second.first, col = q.front().second.second;
            int parIdx = row * n + col;

            if ((row == 0 || col == 0 || row == m - 1 || col == n - 1) && visitedBy[row][col] == 'A')
            {
                found = true;
                dR = row, dC = col;
                break;
            }

            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int nRow = row + dir[k];
                int nCol = col + dir[k + 1];
                int childIdx = nRow * n + nCol;

                if (nRow >= 0 && nRow < m && nCol >= 0 && nCol < n && (grid[nRow][nCol] == '.'))
                {
                    grid[nRow][nCol] = '#';
                    visitedBy[nRow][nCol] = by;
                    par[childIdx] = parIdx;

                    q.push({by, {nRow, nCol}});
                }
            }
        }
        len++;
    }

    if (!found)
        return {-1, ""};

    int destIdx = dR * n + dC;

    while (par[destIdx] != destIdx)
    {
        int currR = destIdx / n, currC = destIdx % n;
        int movedToR = par[destIdx] / n, movedToC = par[destIdx] % n;

        char d;
        if (currC == movedToC)
        {
            if (movedToR < currR)
                d = 'D';
            else
                d = 'U';
        }
        else if (currR == movedToR)
        {
            if (movedToC < currC)
                d = 'R';
            else
                d = 'L';
        }

        path += d;
        destIdx = par[destIdx];
    }

    reverse(path.begin(), path.end());

    return {len, path};
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int m, n;
    cin >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    pair<int, string> ans = bfs(grid);

    if (ans.first == -1)
        cout << "NO";
    else
        cout << "YES" << endl
             << ans.first << endl
             << ans.second;

    return 0;
}
