#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

pair<int, string> bfs(int i, int j, int dR, int dC, vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<int> dir = {-1, 0, 1, 0, -1};
    vector<char> direction = {'U', 'R', 'D', 'L'};

    queue<pair<int, int>> q;

    q.push({i, j});
    grid[i][j] = 1;

    int len = -1;
    string path = "";

    vector<int> par(m * n, -1);
    par[i * n + j] = i * n + j;

    bool found = false;

    while (!q.empty() && !found)
    {
        int size = q.size();
        while (size--)
        {
            int row = q.front().first, col = q.front().second;
            int parIdx = row * n + col;

            q.pop();

            if (row == dR && col == dC)
            {
                found = true;
                break;
            }

            for (int k = 0; k < 4; k++)
            {
                int nRow = row + dir[k];
                int nCol = col + dir[k + 1];
                int childIdx = nRow * n + nCol;

                if (nRow >= 0 && nRow < m && nCol >= 0 && nCol < n && (grid[nRow][nCol] == 0 || grid[nRow][nCol] == 3))
                {
                    grid[nRow][nCol] = 1;
                    par[childIdx] = parIdx;

                    q.push({nRow, nCol});
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

    vector<vector<int>> grid(m, vector<int>(n));

    int startR, startC, endR, endC;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char ch;
            cin >> ch;
            if (ch == '#')
                grid[i][j] = 1;
            else if (ch == '.')
                grid[i][j] = 0;
            else if (ch == 'A')
            {
                grid[i][j] = 2;
                startR = i, startC = j;
            }
            else
            {
                endR = i, endC = j;
                grid[i][j] = 3;
            }
        }
    }

    pair<int, string> ans;

    ans = bfs(startR, startC, endR, endC, grid);

    if (ans.first == -1)
        cout << "NO";
    else
    {
        cout << "YES" << endl;
        cout << ans.first << endl;
        cout << ans.second;
    }

    return 0;
}
