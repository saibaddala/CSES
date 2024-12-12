#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// Function to compute modular inverse of a with respect to MOD
long long mod_inverse(long long a, long long m) {
    long long res = 1, exp = m - 2;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * a) % m;
        a = (a * a) % m;
        exp /= 2;
    }
    return res;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    cin >> n;

    // Calculate the sum of the first n natural numbers
    long long sum = (n * (n + 1)) / 2;

    // If the sum is odd, it's impossible to divide into two equal subsets
    if (sum % 2 == 1) {
        cout << "0" << endl;
        return 0;
    }

    long long target = sum / 2;

    // dp[i][j] represents the number of ways to select elements from {1,2,...,i} to sum to j
    vector<vector<long long>> dp(n + 1, vector<long long>(target + 1, 0));

    // Base case: There's one way to sum to 0 (by selecting no elements)
    dp[0][0] = 1;

    // Fill the dp table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];  // Don't take number i
            if (j >= i) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - i]) % MOD;  // Take number i
            }
        }
    }

    // The answer is the number of ways to form a subset with sum `target`, divided by 2 (since each solution is counted twice)
    long long ans = dp[n][target];
    ans = (ans * mod_inverse(2, MOD)) % MOD;

    cout << ans << endl;
    return 0;
}
