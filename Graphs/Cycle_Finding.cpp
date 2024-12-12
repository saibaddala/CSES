#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

pair<bool, int> bellman_ford(int V, vector<vector<int>> &edges, int S, vector<long long> &dist, vector<int> &par)
{
    par[S] = S;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            if (dist[u] + wt < dist[v])
            {
                par[v] = u;
                dist[v] = dist[u] + wt;
            }
        }
    }

    bool flag = false;
    int cycleNode = -1;

    // Nth relaxation to check negative cycle
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if (dist[u] + wt < dist[v])
        {
            flag = true;
            par[v] = u;
            cycleNode = v;
        }
    }

    return {flag, cycleNode};
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

    // Input edges
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a - 1, b - 1, c});
    }

    // If you don't care about the shortest path and simply want to detect a negative cycle, you can set the initial distance of all vertices to 0. This has the same effect as creating an imaginary source s and connecting s to all other vertices with weight 0 edges.
    vector<long long> dist(n, 0);
    vector<int> par(n, -1);

    // Run Bellman-Ford algorithm
    pair<bool, int> ans = bellman_ford(n, edges, 0, dist, par);

    if (ans.first == false)
        cout << "NO"; // No negative cycle found
    else
    {
        cout << "YES" << endl;

        int cycleNode = ans.second;

        // Move n steps back to ensure we are in the cycle
        for (int i = 0; i < n; i++)
            cycleNode = par[cycleNode];

        // Reconstruct the cycle path
        int start = cycleNode;
        vector<int> cycle;
        cycle.push_back(start + 1);

        int node = par[start];
        while (node != start)
        {
            cycle.push_back(node + 1);
            node = par[node];
        }
        cycle.push_back(start + 1);
        reverse(cycle.begin(), cycle.end());

        // Output the cycle
        for (auto i : cycle)
            cout << i << " ";
    }

    return 0;
}
