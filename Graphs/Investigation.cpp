#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

void dijkstras(vector<vector<pair<int, int>>> &graph, vector<long long> &dist, vector<long long> &totalMinRoutes, vector<long long> &minFlightsInMinRoute, vector<long long> &maxFlightsInMinRoute)
{
    int n = graph.size();

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, 0});
    dist[0] = 0;
    totalMinRoutes[0] = 1;
    minFlightsInMinRoute[0] = maxFlightsInMinRoute[0] = 0;

    while (!pq.empty())
    {
        long long node = pq.top().second;
        long long minD = pq.top().first;

        pq.pop();

        if (dist[node] < minD)
            continue;

        for (auto it : graph[node])
        {
            int ad = it.first;
            long long d = it.second;

            if (minD + d < dist[ad])
            {
                dist[ad] = minD + d;
                totalMinRoutes[ad] = totalMinRoutes[node];
                minFlightsInMinRoute[ad] = 1 + minFlightsInMinRoute[node];
                maxFlightsInMinRoute[ad] = 1 + maxFlightsInMinRoute[node];
                pq.push({dist[ad], ad});
            }
            else if (minD + d == dist[ad])
            {
                totalMinRoutes[ad] += totalMinRoutes[node];
                totalMinRoutes[ad] = totalMinRoutes[ad] % MOD;
                minFlightsInMinRoute[ad] = min(minFlightsInMinRoute[ad], 1 + minFlightsInMinRoute[node]);
                maxFlightsInMinRoute[ad] = max(maxFlightsInMinRoute[ad], 1 + maxFlightsInMinRoute[node]);
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

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a - 1].emplace_back(b - 1, c);
    }

    vector<long long> dist(n, LLONG_MAX), totalMinRoutes(n, 0), minFlightsInMinRoute(n, LLONG_MAX), maxFlightsInMinRoute(n, LLONG_MIN);

    dijkstras(graph, dist, totalMinRoutes, minFlightsInMinRoute, maxFlightsInMinRoute);

    cout << dist[n - 1] << " " << totalMinRoutes[n - 1] << " " << minFlightsInMinRoute[n - 1] << " " << maxFlightsInMinRoute[n - 1];

    return 0;
}
