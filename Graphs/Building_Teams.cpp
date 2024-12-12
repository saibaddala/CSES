#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int bfs(int node, vector<vector<int>> &graph, vector<int> &visited, vector<int> &colors)
{

    queue<int> q;

    q.push(node);
    visited[node] = 1;
    colors[node] = 1;

    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            int NODE = q.front();
            q.pop();

            for (auto ad : graph[NODE])
            {
                if (!visited[ad])
                {
                    colors[ad] = colors[NODE] == 1 ? 2 : 1;
                    visited[ad] = 1;
                    q.push(ad);
                }
                else if (colors[ad] == colors[NODE])
                    return -1;
            }
        }
    }

    return 0;
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

    vector<int> visited(n, 0), colors(n, -1);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            int ans = bfs(i, graph, visited, colors);

            if (ans == -1)
            {
                cout << "IMPOSSIBLE";
                return 0;
            }
        }
    }

    for (auto i : colors)
        cout << i << " ";

    return 0;
}
