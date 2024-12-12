#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

void getDepths(int node, int par, int level, vector<vector<int>> &tree, vector<int> &depth)
{

    depth[node] = level;

    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        getDepths(ad, node, level + 1, tree, depth);
    }
}

int liftUp(int node, int k, vector<vector<int>> &boss)
{
    for (int i = 0; i <= 19; i++)
    {
        if (k & (1 << i) && node != -1)
            node = boss[node][i];
    }

    return node;
}

int LCA(int a, int b, vector<int> &depth, vector<vector<int>> &boss)
{
    int d = abs(depth[a] - depth[b]);
    if (depth[a] > depth[b])
        a = liftUp(a, d, boss);
    else if (depth[b] > depth[a])
        b = liftUp(b, d, boss);

    if (a == b)
        return a;

    for (int d = 19; d >= 0; d--)
    {
        if (boss[a][d] != boss[b][d])
        {
            a = boss[a][d];
            b = boss[b][d];
        }
    }

    return boss[a][0];
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

    vector<vector<int>> boss(n, vector<int>(20, -1));
    vector<vector<int>> tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int a;
        cin >> a;
        boss[i][0] = a - 1;
        tree[i].push_back(a - 1);
        tree[a - 1].push_back(i);
    }

    for (int d = 1; d <= 19; d++)
        for (int i = 1; i < n; i++)
            if (boss[i][d - 1] >= 0)
                boss[i][d] = boss[boss[i][d - 1]][d - 1];

    vector<int> depth(n, -1);
    getDepths(0, -1, 0, tree, depth);

    while (q--)
    {
        int a, b;
        cin >> a >> b;

        int ans = LCA(a - 1, b - 1, depth, boss);
        if (ans != -1)
            ans++;

        cout << ans << endl;
    }
    return 0;
}
