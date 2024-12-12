#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

void getDepthsAndFillTable(int node, int par, int level, vector<vector<int>> &tree, vector<int> &depth, vector<vector<int>> &table)
{

    depth[node] = level;

    table[node][0] = par;

    for (int d = 1; d <= 19; d++)
        if (table[node][d - 1] != -1)
            table[node][d] = table[table[node][d - 1]][d - 1];

    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        getDepthsAndFillTable(ad, node, level + 1, tree, depth, table);
    }
}

int liftUp(int node, int k, vector<vector<int>> &table)
{
    for (int i = 0; i <= 19; i++)
    {
        if (k & (1 << i) && node != -1)
            node = table[node][i];
    }

    return node;
}

int LCA(int a, int b, vector<int> &depth, vector<vector<int>> &table)
{
    int d = abs(depth[a] - depth[b]);
    if (depth[a] > depth[b])
        a = liftUp(a, d, table);
    else if (depth[b] > depth[a])
        b = liftUp(b, d, table);

    if (a == b)
        return a;

    for (int d = 19; d >= 0; d--)
    {
        if (table[a][d] != table[b][d])
        {
            a = table[a][d];
            b = table[b][d];
        }
    }

    return table[a][0];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, q;
    cin >> n >> q;

    vector<vector<int>> table(n, vector<int>(20, -1));
    vector<vector<int>> tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a - 1].push_back(b - 1);
        tree[b - 1].push_back(a - 1);
    }

    vector<int> depth(n, -1);
    getDepthsAndFillTable(0, -1, 0, tree, depth, table);

    while (q--)
    {
        int a, b;
        cin >> a >> b;

        int ans = LCA(a - 1, b - 1, depth, table);

        cout << depth[a - 1] + depth[b - 1] - 2 * depth[ans] << endl;
    }
    return 0;
}
