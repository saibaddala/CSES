#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

bool dfs(int node, vector<bool> &mark, vector<vector<int>> &graph, vector<int> &visited)
{
    if (mark[node] == true)
        return true;
    visited[node] = 1;
    for (auto ad : graph[node])
    {
        if (!visited[ad])
        {
            if (dfs(ad, mark, graph, visited))
                return true;
        }
    }

    return false;
}

bool bellman_ford(int V, vector<vector<int>> &edges, int S, vector<long long> &dist, vector<bool> &mark)
{
    dist[S] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            if (dist[u] != LLONG_MAX && dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
            }
        }
    }
    bool flag = false;
    // Nth relaxation to check negative cycle
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if (dist[u] != LLONG_MAX && dist[u] + wt < dist[v])
        {
            flag = true;
            mark[v] = true;
        }
    }
    return flag;
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a - 1, b - 1, -c});
    }
    vector<bool> mark(n, false);
    vector<long long> dist(n, LLONG_MAX);

    bool ans = bellman_ford(n, edges, 0, dist, mark);

    if (ans == false)
        cout << -1 * dist[n - 1];
    else
    {
        vector<vector<int>> graph(n);
        for (int i = 0; i < m; i++)
            graph[edges[i][1]].push_back(edges[i][0]);

        vector<int> visited(n, 0);
        bool cycleInDesiredPath = dfs(n - 1, mark, graph, visited);

        if (cycleInDesiredPath)
            cout << "-1";
        else
            cout << -1 * dist[n - 1];
    }

    return 0;
}
