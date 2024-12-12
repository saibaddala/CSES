#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

long long prims(vector<vector<pair<int, int>>> &graph, vector<bool> &mst)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    long long minCost = 0;

    while (!pq.empty())
    {
        int d = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        if (mst[node])
            continue;

        minCost += d;
        mst[node] = true;

        for (auto it : graph[node])
            pq.push({it.second, it.first});
    }

    return minCost;
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
        graph[b - 1].emplace_back(a - 1, c);
    }

    vector<bool> mst(n, false);

    long long mstCost = prims(graph, mst);

    for (auto i : mst)
        if (i == false)
        {
            cout << "IMPOSSIBLE";
            return 0;
        }

    cout << mstCost;

    return 0;
}
