#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MOD = 1e9 + 7;

long long dfs(int node, int mask, int n, vector<vector<int>> &graph, vector<vector<long long>> &dp)
{
    if (node == n - 1)
    {
        mask = mask | (1 << node);
        return mask == (1 << n) - 1; // All nodes have been visited when at the destination
    }

    if (mask & (1 << node)) // If this node is already visited
        return 0;

    if (dp[node][mask] != -1)
        return dp[node][mask];

    int mask1 = mask | (1 << node); // Mark this node as visited

    long long ans = 0;
    for (auto ad : graph[node])
    {
        ans += dfs(ad, mask1, n, graph, dp);
        ans %= MOD;
    }

    return dp[node][mask] = ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }

    // DP table with size n x (2^n)
    vector<vector<long long>> dp(n, vector<long long>(1 << n, -1));

    // Start from node 0 with an empty mask (no nodes visited)
    long long ans = dfs(0, 0, n, graph, dp);

    cout << ans;
    return 0;
}
