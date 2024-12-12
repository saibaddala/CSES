#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

long long getSubordinates(int node, vector<vector<int>> &tree, vector<long long> &ans)
{
    long long cnt = 0;

    for (int i = 0; i < tree[node].size(); i++)
        cnt += getSubordinates(tree[node][i], tree, ans);

    ans[node] = cnt;
    return ans[node] + 1;
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
        int par;
        cin >> par;
        tree[par - 1].push_back(i);
    }

    vector<long long> ans(n, 0);

    getSubordinates(0, tree, ans);

    for (auto i : ans)
        cout << i << " ";

    return 0;
}
