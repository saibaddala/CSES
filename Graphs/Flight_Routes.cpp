#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void dijkstras(vector<vector<pair<int, int>>> &graph, vector<priority_queue<long long>> &dist, int k)
{
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, 0});
    dist[0].push(0);

    while (!pq.empty())
    {
        int node = pq.top().second;
        long long d = pq.top().first;

        pq.pop();

        if (d > dist[node].top())
            continue;

        for (auto it : graph[node])
        {
            int ad = it.first;
            long long D = it.second;

            if (dist[ad].size() < k)
            {
                dist[ad].push(d + D);
                pq.push({d + D, ad});
            }
            else if (d + D < dist[ad].top())
            {
                dist[ad].pop();
                dist[ad].push(d + D);
                pq.push({d + D, ad});
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

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a - 1].emplace_back(b - 1, c);
    }

    vector<priority_queue<long long>> dist(n);

    dijkstras(graph, dist, k);

    vector<long long> ans;

    while (!dist[n - 1].empty())
    {
        ans.push_back(dist[n - 1].top());
        dist[n - 1].pop();
    }

    reverse(begin(ans), end(ans));

    for (auto i : ans)
        cout << i << " ";
    return 0;
}
