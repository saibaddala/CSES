#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

int dfs(int node, int n, vector<vector<int>> &graph, vector<long long> &dp)
{
    if (node == n - 1)
        return 1;

    if (dp[node] != -1)
        return dp[node];

    long long cnt = 0;

    for (auto ad : graph[node])
    {
        cnt += dfs(ad, n, graph, dp);
        cnt = cnt % MOD;
    }

    return dp[node] = cnt;
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
    }

    vector<long long> ways(n, -1);

    int ans = dfs(0, n, graph, ways);

    cout << ans;

    return 0;
}

// Using Khans algo

// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;
// int n;
// vector<int> edge[100001];
// vector<int> backedge[100001];

// int main() {
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);
// 	int m;
// 	cin >> n >> m;
// 	int in_degree[n + 1], dp[n + 1];
// 	for (int i = 0; i <= n; i++) {
// 		in_degree[i] = 0;
// 		dp[i] = 0;
// 	}
// 	dp[1] = 1;
// 	for (int i = 0; i < m; i++) {
// 		int a, b;
// 		cin >> a >> b;
// 		edge[a].push_back(b);
// 		backedge[b].push_back(a);
// 		in_degree[b]++;
// 	}
// 	// uses Kahn's algorithm
// 	queue<int> q;
// 	for (int i = 0; i < n; i++) {
// 		if (in_degree[i] == 0) { q.push(i); }
// 	}

// 	while (!q.empty()) {
// 		int node = q.front();
// 		q.pop();
// 		for (int next : edge[node]) {
// 			in_degree[next]--;
// 			if (in_degree[next] == 0) q.push(next);
// 		}

// 		for (int prev : backedge[node]) {
// 			dp[node] = (dp[node] + dp[prev]) % 1000000007;
// 		}
// 	}
// 	cout << dp[n] << endl;
// 	return 0;
// }