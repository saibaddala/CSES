#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void dfs(int node, int &steps, vector<int> &graph, queue<int> &path, vector<int> &pathLength, vector<int> &visited)
{
    path.push(node);

    if (visited[node])
    {
        steps += pathLength[node];
        return;
    }

    visited[node] = 1;
    steps++;
    dfs(graph[node], steps, graph, path, pathLength, visited);
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> graph(n);

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        graph[i] = a - 1;
    }

    vector<int> pathLength(n, 0);
    vector<int> visited(n, 0);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            queue<int> path;
            int steps = 0;
            dfs(i, steps, graph, path, pathLength, visited);

            int decrement = 1;

            while (!path.empty())
            {
                if (path.front() == path.back())
                    decrement = 0;

                pathLength[path.front()] = steps;
                steps = steps - decrement;
                path.pop();
            }
        }
    }

    for (auto i : pathLength)
        cout << i << " ";

    return 0;
}
