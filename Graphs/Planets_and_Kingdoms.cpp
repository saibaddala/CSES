#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>> &graph, stack<int> &st, vector<int> &visited)
{
    visited[node] = 1;

    for (auto ad : graph[node])
        if (!visited[ad])
            dfs(ad, graph, st, visited);

    st.push(node);
}

void dfs2(int node, int component, vector<vector<int>> &graph, vector<int> &visited, vector<int> &belongsTo)
{
    visited[node] = 1;
    belongsTo[node] = component;

    for (auto ad : graph[node])
        if (!visited[ad])
            dfs2(ad, component, graph, visited, belongsTo);
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

    stack<int> st;
    vector<int> visited(n, 0);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, graph, st, visited);

    fill(begin(visited), end(visited), 0);
    int scc = 0, k = 1;
    vector<int> belongsTo(n, -1);

    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        if (!visited[node])
        {
            scc++;
            dfs2(node, k, revGraph, visited, belongsTo);
            k++;
        }
    }

    cout << scc << endl;
    for (auto i : belongsTo)
        cout << i << " ";

    return 0;
}
