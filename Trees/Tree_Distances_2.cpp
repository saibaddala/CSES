#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

pair<long long, long long> dfs(int node, int par, vector<vector<int>> &tree, vector<long long> &sumOfDistsOfChildren, vector<long long> &subTreeNodesCnt)
{
    long long cnt = 0, sum = 0;
    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        auto p = dfs(ad, node, tree, sumOfDistsOfChildren, subTreeNodesCnt);

        cnt += p.first;
        sum = sum + p.second + p.first;
    }

    sumOfDistsOfChildren[node] = sum;
    subTreeNodesCnt[node] = cnt;
    return {1 + cnt, sum};
}

void dfs2(int node, int par, int n, vector<vector<int>> &tree, vector<long long> &sumOfDists, vector<long long> &subTreeNodesCnt)
{
    if (par != -1)
    {
        long long ans = sumOfDists[par] + n - 2 * subTreeNodesCnt[node] - 2;
        sumOfDists[node] = ans;
    }

    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        dfs2(ad, node, n, tree, sumOfDists, subTreeNodesCnt);
    }
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

    vector<long long> sumOfDistsOfChildren(n, 0), subTreeNodesCnt(n, 0);

    dfs(0, -1, tree, sumOfDistsOfChildren, subTreeNodesCnt);

    vector<long long> sumOfDists = sumOfDistsOfChildren;

    dfs2(0, -1, n, tree, sumOfDists, subTreeNodesCnt);

    for (auto i : sumOfDists)
        cout << i << " ";

    return 0;
}
