#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void floyds(vector<vector<long long>> &dist)
{
    int n = dist.size();

    for (int via = 0; via < n; via++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                long long d1 = dist[i][via];
                long long d2 = dist[via][j];
                if (d1 != LLONG_MAX && d2 != LLONG_MAX)
                    dist[i][j] = min(dist[i][j], d1 + d2);
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m, q;
    cin >> n >> m >> q;

    // Initialize distances with LLONG_MAX, except for diagonal which is 0 (self-loops)
    vector<vector<long long>> dist(n, vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    // Read edges
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a - 1][b - 1] = min(dist[a - 1][b - 1], (long long)c); // Handle multiple edges
        dist[b - 1][a - 1] = min(dist[b - 1][a - 1], (long long)c); // Handle multiple edges
    }

    // Read queries
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        queries[i] = {a, b};
    }

    // Run Floyd-Warshall algorithm
    floyds(dist);

    // Answer queries
    for (const auto &q : queries)
    {
        int a = q.first;
        int b = q.second;

        if (dist[a - 1][b - 1] != LLONG_MAX)
            cout << dist[a - 1][b - 1] << " ";
        else
            cout << "-1 ";
    }

    return 0;
}
