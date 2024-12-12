#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>> &graph, vector<int> &visited, vector<bool> &Reached)
{
    visited[node] = 1;
    Reached[node] = true;

    for (auto ad : graph[node])
    {
        if (!visited[ad])
            dfs(ad, graph, visited, Reached);
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

    vector<vector<int>> graph(n), revGraph(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        revGraph[b - 1].push_back(a - 1);
    }

    vector<bool> fromZero(n, false), toZero(n, false);
    vector<int> visited(n, 0);
    dfs(0, graph, visited, fromZero);

    fill(begin(visited), end(visited), 0);
    dfs(0, revGraph, visited, toZero);

    for (int i = 0; i < n; i++)
    {
        if (!fromZero[i] || !toZero[i])
        {
            cout << "NO" << endl;
            if (!fromZero[i])
                cout << "1 " << i + 1;
            else
                cout << i + 1 << " " << "1";

            return 0;
        }
    }

    cout << "YES";
    return 0;
}
