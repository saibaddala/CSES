#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Comparator function for upper_bound
bool upperBoundComparator(int endTime, const vector<long long> &project)
{
    return endTime < project[0]; // Compare project start time with endTime
}

// Comparator function for sorting by start time
bool sortComparator(const vector<long long> &v1, const vector<long long> &v2)
{
    return v1[0] < v2[0]; // Compare by start time (v1[0] and v2[0])
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<vector<long long>> nums(n, vector<long long>(3));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> nums[i][j]; // start, end, reward
        }
    }

    // Sort by the start time (nums[i][0]) using the comparator function
    sort(nums.begin(), nums.end(), sortComparator);

    // DP array to store the maximum reward up to each project
    vector<long long> dp(n + 1, 0);

    // Process projects in reverse order
    for (int i = n - 1; i >= 0; i--)
    {
        // Find the first project that starts after the current project ends
        int idx = upper_bound(nums.begin() + i + 1, nums.end(), nums[i][1], upperBoundComparator) - nums.begin();

        // Option 1: Do not take the current project
        long long notTake = dp[i + 1];

        // Option 2: Take the current project and add the reward from the next valid project
        long long take = nums[i][2];
        if (idx < n)
        {
            take += dp[idx]; // Add reward from the next non-overlapping project
        }

        // Update dp[i] with the best option (take or not take)
        dp[i] = max(notTake, take);
    }

    // Output the result, which is dp[0]
    cout << dp[0];

    return 0;
}
