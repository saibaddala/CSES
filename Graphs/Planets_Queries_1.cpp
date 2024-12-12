#include <iostream>
using namespace std;

const int MAXN = 200005; // Assuming maximum 'n' size
const int MAXD = 30;     // Maximum depth for binary lifting (log2(10^9) ≈ 30)

int nextNode[MAXN][MAXD]; // Array to store ancestors for binary lifting

int getDest(int node, int steps)
{
    // Move the node 'steps' times according to the binary representation of steps
    for (int i = 0; i < MAXD; i++)
    {
        if (steps & (1 << i))
        {                             // Check if the i-th bit is set in 'steps'
            node = nextNode[node][i]; // Move to the i-th ancestor
        }
    }
    return node;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, q;
    cin >> n >> q;

    // Read the 1st ancestor for each node
    for (int i = 1; i <= n; i++)
    {
        cin >> nextNode[i][0]; // The first ancestor
    }

    // Precompute the ancestors using dynamic programming (binary lifting)
    for (int d = 1; d < MAXD; d++)
    {
        for (int i = 1; i <= n; i++)
        {
            nextNode[i][d] = nextNode[nextNode[i][d - 1]][d - 1];
        }
    }

    // Process each query
    while (q--)
    {
        int node, steps;
        cin >> node >> steps;

        // Find the destination using the optimized 'getDest' function
        cout << getDest(node, steps) << endl;
    }

    return 0;
}
