#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

bool dfs(int node, int par, vector<vector<int>> &graph, vector<int> &visited, vector<int> &path)
{
    visited[node] = 1;

    for (auto ad : graph[node])
    {
        if (!visited[ad])
        {
            path.push_back(ad + 1);
            if (dfs(ad, node, graph, visited, path))
                return true;
            path.pop_back();
        }
        else if (ad != par)
        {
            path.push_back(ad + 1);
            return true;
        }
    }

    return false;
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

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            vector<int> path;
            path.push_back(i + 1);
            if (dfs(i, -1, graph, visited, path))
            {
                int lastCity = path.back();
                int startIdx = -1;
                for (int i = 0; i < path.size(); i++)
                {
                    if (path[i] == lastCity)
                    {
                        startIdx = i;
                        break;
                    }
                }

                cout << path.size() - startIdx << endl;
                for (int i = startIdx; i < path.size(); i++)
                    cout << path[i] << " ";

                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE";

    return 0;
}
