#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void dijkstra(vector<vector<pair<int, int>>> &graph, int n, vector<vector<long long>> &dist)
{
    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
    pq.push({0, {0, 0}}); // {current_cost, {coupon_used, node}}
    dist[0][0] = dist[0][1] = 0;

    while (!pq.empty())
    {
        long long currCost = pq.top().first;
        int couponUsed = pq.top().second.first;
        int node = pq.top().second.second;
        pq.pop();

        if (currCost != dist[node][couponUsed])
            continue;
        // Explore neighbors
        for (auto &edge : graph[node])
        {
            int neighbor = edge.first;
            long long price = edge.second;
            long long discountPrice = price / 2;

            // If the coupon hasn't been used yet
            if (!couponUsed)
            {
                // Try using the coupon
                if (currCost + discountPrice < dist[neighbor][1])
                {
                    dist[neighbor][1] = currCost + discountPrice;
                    pq.push({dist[neighbor][1], {1, neighbor}});
                }
                // Normal path without coupon
                if (currCost + price < dist[neighbor][0])
                {
                    dist[neighbor][0] = currCost + price;
                    pq.push({dist[neighbor][0], {0, neighbor}});
                }
            }
            // If the coupon is already used
            else
            {
                if (currCost + price < dist[neighbor][1])
                {
                    dist[neighbor][1] = currCost + price;
                    pq.push({dist[neighbor][1], {1, neighbor}});
                }
            }
        }
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

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    // Read the graph
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a - 1].emplace_back(b - 1, c);
    }

    // Distance array to store the minimum cost with and without using a coupon
    vector<vector<long long>> dist(n, vector<long long>(2, LLONG_MAX));

    // Run Dijkstra's algorithm
    dijkstra(graph, n, dist);

    // The answer is the minimum cost to reach city n-1 (Metsälä) with the coupon used
    cout << dist[n - 1][1];

    return 0;
}
