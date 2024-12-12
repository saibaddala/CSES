#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

int getKthAncestor(int node, int k, vector<vector<int>> &boss)
{
    for (int i = 0; i <= 19; i++)
    {
        if (k & (1 << i) && node != -1)
            node = boss[node][i];
    }

    return node;
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

    for (int i = 1; i <= n - 1; i++)
    {
        int a;
        cin >> a;
        boss[i][0] = a - 1;
    }

    for (int d = 1; d <= 19; d++)
        for (int i = 1; i < n; i++)
            if (boss[i][d - 1] >= 0)
                boss[i][d] = boss[boss[i][d - 1]][d - 1];

    while (q--)
    {
        int node, k;
        cin >> node >> k;

        int ans = getKthAncestor(node - 1, k, boss);
        if (ans != -1)
            ans++;

        cout << ans << endl;
    }
    return 0;
}
