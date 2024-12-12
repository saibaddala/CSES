#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> lis;
    lis.push_back(nums[0]);

    for (int i = 1; i < n; i++)
    {
        if (nums[i] > lis.back())
            lis.push_back(nums[i]);
        else
        {
            int idx = lower_bound(lis.begin(), lis.end(), nums[i]) - lis.begin();
            lis[idx] = nums[i];
        }
    }

    cout << lis.size();

    return 0;
}