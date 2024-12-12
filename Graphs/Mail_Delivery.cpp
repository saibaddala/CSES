#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void getEulerianCircuit(int node, vector<vector<pair<int, int>>> &graph, vector<int> &ans, vector<bool> &visited)
{
    while (!graph[node].empty()) // While there are edges connected to this node
    {
        pair<int, int> edge = graph[node].back(); // Get the last edge
        graph[node].pop_back();                   // Remove the edge from the adjacency list

        int adjNode = edge.first;  // The adjacent node
        int edgeIdx = edge.second; // The edge index

        if (!visited[edgeIdx])
        {
            visited[edgeIdx] = true; // Mark this edge as visited
            getEulerianCircuit(adjNode, graph, ans, visited);
        }
    }

    ans.push_back(node); // Equivalent to stack's push
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n); // Adjacency list representation
    vector<int> degree(n, 0);                // To track the degree of each node

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--; // Adjusting 1-based input to 0-based index
        graph[a].emplace_back(b, i);
        graph[b].emplace_back(a, i);
        degree[a]++;
        degree[b]++;
    }

    // Check if all vertices have even degree
    for (auto i : degree)
    {
        if (i % 2 == 1)
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    vector<int> ans;            // To store the final Eulerian circuit
    vector<bool> visited(m, 0); // To track visited edges

    getEulerianCircuit(0, graph, ans, visited);

    if (ans.size() != m + 1) // There should be exactly m+1 nodes in the Eulerian circuit
        cout << "IMPOSSIBLE";
    else
        for (auto node : ans)
        {
            cout << node + 1 << " "; // Converting 0-based index back to 1-based output
        }

    return 0;
}
