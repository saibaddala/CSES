#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;
const int MOD = 1e9 + 7;

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, capacity;
    cin >> n >> capacity;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    long long ans = 0;

    cout << ans;
    return 0;
}
