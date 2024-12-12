#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

long long maxi = 0;

long long getDia(int node, int par, vector<vector<int>> &tree)
{
    long long dia = 0;
    multiset<int> dist;
    for (int i = 0; i < tree[node].size(); i++)
    {
        if (tree[node][i] != par)
        {
            dia = getDia(tree[node][i], node, tree);
            dist.insert(dia);
        }
    }

    if (dist.size() == 0)
        return 0;
    else if (dist.size() == 1)
    {
        long long hei = 1 + *dist.begin();
        maxi = max(maxi, hei);
        return hei;
    }
    else
    {
        long long s = 0;
        auto it = dist.rbegin();
        s += *it;
        it--;
        s += *it;
        s += 2;
        maxi = max(maxi, s);
        return *dist.rbegin() + 1;
    }

    return -1;
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

    long long ans = getDia(0, -1, tree);

    cout << maxi;

    return 0;
}