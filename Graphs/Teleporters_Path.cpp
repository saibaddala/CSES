#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void getEulerianPath(int node, vector<vector<pair<int, int>>> &graph, vector<int> &ans, vector<bool> &visited)
{
    while (!graph[node].empty())
    {
        pair<int, int> edge = graph[node].back();
        graph[node].pop_back();

        int adjNode = edge.first;
        int edgeIdx = edge.second;

        if (!visited[edgeIdx])
        {
            visited[edgeIdx] = true;
            getEulerianPath(adjNode, graph, ans, visited);
        }
    }

    ans.push_back(node);
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
    vector<int> indegree(n, 0), outdegree(n, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].emplace_back(b, i);
        outdegree[a]++;
        indegree[b]++;
    }

    int startNode = -1, endNode = -1;
    for (int i = 0; i < n; i++)
    {
        if (outdegree[i] - indegree[i] > 1 || indegree[i] - outdegree[i] > 1)
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
        else if (outdegree[i] - indegree[i] == 1)
        {
            startNode = i;
        }
        else if (indegree[i] - outdegree[i] == 1)
        {
            endNode = i;
        }
    }

    if (!((startNode == -1 && endNode == -1) || (startNode == 0 && endNode == n - 1)))
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> ans;
    vector<bool> visited(m, 0);

    getEulerianPath(0, graph, ans, visited);

    reverse(begin(ans), end(ans));

    if (ans.size() != m + 1 || ans.back() != n - 1)
        cout << "IMPOSSIBLE";
    else
        for (auto node : ans)
        {
            cout << node + 1 << " ";
        }

    return 0;
}
