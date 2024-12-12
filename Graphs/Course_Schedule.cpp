#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void bfs(vector<vector<int>> &graph, vector<int> &topo)
{
    int n = graph.size();
    queue<int> q;
    vector<int> indegree(n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph[i].size(); j++)
            indegree[graph[i][j]]++;

    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (auto ad : graph[node])
        {
            indegree[ad]--;
            if (indegree[ad] == 0)
                q.push(ad);
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

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }

    vector<int> topo;

    bfs(graph, topo);

    if (topo.size() != n)
        cout << "IMPOSSIBLE";
    else
        for (auto i : topo)
            cout << i + 1 << " ";

    return 0;
}
