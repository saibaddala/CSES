#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void dijkstras(int start, vector<vector<pair<int, int>>> &graph, vector<long long> &dist)
{
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty())
    {
        auto node = pq.top().second;
        auto minDistToNode = pq.top().first;

        pq.pop();

        // If the current distance is greater than the minimum distance, we skip the node
        if (minDistToNode > dist[node])
            continue;

        for (auto it : graph[node])
        {
            int ad = it.first;
            int d = it.second;
            if (minDistToNode + d < dist[ad])
            {
                dist[ad] = minDistToNode + d;
                pq.push({dist[ad], ad});
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

    vector<long long> dist(n, LLONG_MAX);

    dijkstras(0, graph, dist);

    for (auto i : dist)
        cout << i << " ";

    return 0;
}
