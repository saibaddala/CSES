#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

long long bfs(int node, vector<vector<int>> &graph, vector<int> &visited, vector<int> &par)
{

    int n = graph.size();
    queue<int> q;

    q.push(node);
    visited[node] = 1;
    par[node] = 0;

    long long dist = 0;

    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            int NODE = q.front();
            q.pop();

            if (NODE == n - 1)
                return dist;

            for (auto ad : graph[NODE])
            {
                if (!visited[ad])
                {
                    visited[ad] = 1;
                    par[ad] = NODE;
                    q.push(ad);
                }
            }
        }
        dist++;
    }

    return -1;
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

    vector<int> visited(n, 0), par(n, -1);

    long long ans =
        bfs(0, graph, visited, par);

    if (ans == -1)
        cout << "IMPOSSIBLE";
    else
    {
        cout << ans + 1 << endl;

        vector<int> path;
        int node = n - 1;
        path.push_back(node);
        while (par[node] != node)
        {
            path.push_back(par[node]);
            node = par[node];
        }
        reverse(path.begin(), path.end());
        for (auto i : path)
            cout << i + 1 << " ";
    }
    return 0;
}
