#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

long long getMaxMatching(int node, int prev, int par, vector<vector<int>> &tree)
{
    long long cnt = 0;

    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        if (prev)
        {
            long long subCnt = getMaxMatching(ad, !prev, node, tree);
            cnt += subCnt;
        }
        else
        {
            long long subCnt = max(getMaxMatching(ad, prev, node, tree), 1 + getMaxMatching(ad, !prev, node, tree));
            cnt += subCnt;
        }
    }

    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<vector<int>> tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a - 1].push_back(b - 1);
        tree[b - 1].push_back(a - 1);
    }

    long long ans = getMaxMatching(0, 0, -1, tree);

    cout << ans;
    return 0;
}
