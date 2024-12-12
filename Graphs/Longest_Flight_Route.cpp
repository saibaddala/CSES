#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

long long dfs(int node, int n, vector<vector<int>> &graph, vector<int> &child, vector<long long> &dist)
{
    if (node == n - 1)
        return 1;

    if (dist[node] != -1)
        return dist[node];

    dist[node] = LLONG_MIN;
    for (auto ad : graph[node])
    {
        long long d = dfs(ad, n, graph, child, dist);

        if (d != LLONG_MIN && 1 + d > dist[node])
        {
            dist[node] = 1 + d;
            child[node] = ad;
        }
    }

    return dist[node];
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

    vector<int> child(n, -1);

    vector<long long> dist(n, -1);

    dfs(0, n, graph, child, dist);

    if (dist[0] == LLONG_MIN)
        cout << "IMPOSSIBLE";
    else
    {
        vector<int> path;
        path.push_back(1);
        int node = 0;
        while (child[node] != -1)
        {
            path.push_back(child[node] + 1);
            node = child[node];
        }

        cout << dist[0] << endl;

        for (auto i : path)
            cout << i << " ";
    }
    return 0;
}
