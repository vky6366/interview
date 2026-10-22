#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include<climits>

using namespace std;

int robberhelp(vector<int> nums){
    int n = nums.size();
    vector<int> dp(n+1);
    if(n<2){
        return nums[0];
    }

    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for(int i = 2; i<n; i++){
        dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
    }

    return dp[n-1];
}

int robber(vector<int> nums){
    int n = nums.size();

    vector<int> skip_first(n);
    vector<int> skip_last(n);

    for(int i = 0; i<n; i++){
        skip_last[i] = nums[i];
        skip_first[i] = nums[i+1];
    }

    int clock_wise = robberhelp(skip_last);
    int anti_clock_wise = robberhelp(skip_first);

    return max(clock_wise, anti_clock_wise);
}