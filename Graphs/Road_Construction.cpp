#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int findPar(int node, vector<int> &par)
{
    if (par[node] == node)
        return node;

    return par[node] = findPar(par[node], par);
}

void unionBySize(int u, int v, vector<int> &par, vector<long long> &size)
{
    int u_par = findPar(u, par);
    int v_par = findPar(v, par);

    par[v_par] = u_par;
    size[u_par] = size[u_par] + size[v_par];
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

    int components = n;
    long long maxSize = 1;

    vector<int> par(n);
    vector<long long> size(n, 1);
    for (int i = 0; i < n; i++)
        par[i] = i;

    while (m--)
    {
        int a, b;
        cin >> a >> b;

        int a_par = findPar(a - 1, par);
        int b_par = findPar(b - 1, par);

        if (a_par == b_par)
        {
            cout << components << " " << maxSize;
            if (m != 0)
                cout << endl;
        }
        else
        {
            unionBySize(a - 1, b - 1, par, size);
            maxSize = max(maxSize, size[findPar(a - 1, par)]);
            components--;
            cout << components << " " << maxSize;
            if (m != 0)
                cout << endl;
        }
    }
    return 0;
}
