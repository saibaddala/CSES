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

void dfs2(int node, int component, vector<vector<int>> &graph, vector<int> &visited, vector<int> &belongsTo, long long &coins, vector<int> &coinsInRoom)
{
    visited[node] = 1;
    belongsTo[node] = component;
    coins += coinsInRoom[node];

    for (auto ad : graph[node])
        if (!visited[ad])
            dfs2(ad, component, graph, visited, belongsTo, coins, coinsInRoom);
}

void createComponentGraph(int node, vector<vector<int>> &graph, vector<int> &belongsTo, vector<unordered_set<int>> &sccGraph, vector<int> &visited)
{
    visited[node] = 1;

    for (auto ad : graph[node])
    {
        if (belongsTo[node] != belongsTo[ad])
            sccGraph[belongsTo[node]].insert(belongsTo[ad]);
        if (!visited[ad])
            createComponentGraph(ad, graph, belongsTo, sccGraph, visited);
    }
}

long long collect(int node, vector<unordered_set<int>> &sccGraph, vector<long long> &coinsInComponent, vector<long long> &dp)
{
    if (dp[node] != -1)
        return dp[node];

    long long coins = LLONG_MIN;

    // If the SCC has no outgoing edges, it can only collect its own coins
    bool hasOutgoing = false;
    for (auto ad : sccGraph[node])
    {
        coins = max(coins, collect(ad, sccGraph, coinsInComponent, dp));
        hasOutgoing = true;
    }

    // If no outgoing SCC, collect only coins in this SCC
    if (!hasOutgoing)
        dp[node] = coinsInComponent[node];
    else
        dp[node] = coinsInComponent[node] + (coins != LLONG_MIN ? coins : 0);

    return dp[node];
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<int> coinsInRoom(n, -1);

    for (int i = 0; i < n; i++)
        cin >> coinsInRoom[i];

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
    int scc = 0, k = 0;
    vector<int> belongsTo(n, -1);
    vector<long long> coinsInComponent;

    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        if (!visited[node])
        {
            long long coins = 0;
            dfs2(node, k, revGraph, visited, belongsTo, coins, coinsInRoom);
            coinsInComponent.push_back(coins);
            scc++;
            k++;
        }
    }

    vector<unordered_set<int>> sccGraph(scc);

    fill(begin(visited), end(visited), 0);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            createComponentGraph(i, graph, belongsTo, sccGraph, visited);

    vector<long long> dp(scc, -1);

    for (int i = 0; i < scc; i++)
        collect(i, sccGraph, coinsInComponent, dp);

    long long ans = LLONG_MIN;

    for (auto i : dp)
        ans = max(ans, i);

    cout << ans;
    return 0;
}
