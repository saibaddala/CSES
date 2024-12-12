#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

void getFirstAndSecondMaxInSubTrees(int node, int par, vector<vector<int>> &tree, vector<long long> &firstMax, vector<long long> &secondMax, vector<int> &maxDistAlongTheChild)
{

    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        getFirstAndSecondMaxInSubTrees(ad, node, tree, firstMax, secondMax, maxDistAlongTheChild);

        if (firstMax[ad] + 1 > firstMax[node])
        {
            secondMax[node] = firstMax[node];
            firstMax[node] = firstMax[ad] + 1;
            maxDistAlongTheChild[node] = ad;
        }
        else if (firstMax[ad] + 1 > secondMax[node])
        {
            secondMax[node] = firstMax[ad] + 1;
        }
    }
}

void getMaxDistsConsideringParentsAlso(int node, int par, vector<vector<int>> &tree, vector<long long> &firstMax, vector<long long> &secondMax, vector<int> &maxDistAlongTheChild)
{
    for (auto ad : tree[node])
    {
        if (ad == par)
            continue;

        if (maxDistAlongTheChild[node] == ad)
        {
            if (secondMax[node] + 1 > firstMax[ad])
            {
                secondMax[ad] = firstMax[ad];
                firstMax[ad] = secondMax[node] + 1;
                maxDistAlongTheChild[ad] = node;
            }
            else if (secondMax[node] + 1 > secondMax[ad])
            {
                secondMax[ad] = secondMax[node] + 1;
            }
        }
        else
        {
            secondMax[ad] = firstMax[ad];
            firstMax[ad] = firstMax[node] + 1;
            maxDistAlongTheChild[ad] = node;
        }

        getMaxDistsConsideringParentsAlso(ad, node, tree, firstMax, secondMax, maxDistAlongTheChild);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<vector<int>> tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a - 1].push_back(b - 1);
        tree[b - 1].push_back(a - 1);
    }

    vector<long long> firstMax(n, 0), secondMax(n, 0);
    vector<int> maxDistAlongTheChild(n);

    getFirstAndSecondMaxInSubTrees(0, -1, tree, firstMax, secondMax, maxDistAlongTheChild);

    getMaxDistsConsideringParentsAlso(0, -1, tree, firstMax, secondMax, maxDistAlongTheChild);

    for (auto i : firstMax)
        cout << i << " ";

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <unordered_set>
// #include <unordered_map>
// #include <queue>
// #include <climits>
// #include <math.h>
// #include <algorithm>

// using namespace std;

// void getFarthestNode(int node, int currDist, int par, vector<vector<int>> &tree, int &farthestDist, int &farthestNode)
// {
//     if (currDist > farthestDist)
//         farthestDist = currDist, farthestNode = node;

//     for (int i = 0; i < tree[node].size(); i++)
//         if (tree[node][i] != par)
//             getFarthestNode(tree[node][i], currDist + 1, node, tree, farthestDist, farthestNode);
// }

// void dfs(int node, int currDist, int par, vector<vector<int>> &tree, vector<int> &dist)
// {
//     dist[node] = currDist;
//     for (int i = 0; i < tree[node].size(); i++)
//         if (tree[node][i] != par)
//             dfs(tree[node][i], currDist + 1, node, tree, dist);
// }

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

//     int n;
//     cin >> n;

//     vector<vector<int>> tree(n);

//     for (int i = 1; i <= n - 1; i++)
//     {
//         int a, b;
//         cin >> a >> b;
//         tree[a - 1].push_back(b - 1);
//         tree[b - 1].push_back(a - 1);
//     }

//     int farthestNode = -1, farthestDist = -1;
//     getFarthestNode(0, 0, -1, tree, farthestDist, farthestNode);
//     int nodeA = farthestNode;

//     farthestDist = -1;
//     getFarthestNode(farthestNode, 0, -1, tree, farthestDist, farthestNode);
//     int nodeB = farthestNode;

//     vector<int> distFromNodeA(n, 0);
//     dfs(nodeA, 0, -1, tree, distFromNodeA);

//     vector<int> distFromNodeB(n, 0);
//     dfs(nodeB, 0, -1, tree, distFromNodeB);

//     for (int i = 0; i < n; i++)
//         cout << max(distFromNodeA[i], distFromNodeB[i]) << " ";

//     return 0;
// }
