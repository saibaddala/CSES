#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void bfs(int node, vector<vector<int>> &graph, vector<int> &visited)
{

    queue<int> q;

    q.push(node);
    visited[node] = 1;

    while (!q.empty())
    {
        int NODE = q.front();
        q.pop();

        for (auto ad : graph[NODE])
        {
            if (!visited[ad])
            {
                visited[ad] = 1;
                q.push(ad);
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

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    vector<int> visited(n, 0);
    vector<int> roads;
    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            ans++;
            roads.push_back(i + 1);
            bfs(i, graph, visited);
        }
    }

    cout << ans - 1 << endl;

    for (int i = 0; i < roads.size() - 1; i++)
        cout << roads[i] << " " << roads[i + 1] << endl;

    return 0;
}
