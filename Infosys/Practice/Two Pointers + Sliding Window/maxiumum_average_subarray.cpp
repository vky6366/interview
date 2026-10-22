#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

double max_avg_subarray(vector<int>& nums, int k){
    int n = nums.size();
    int sum = 0;
    for(int i=0; i<k; i++){
        sum += nums[i];
    }

    double max_avg = (double)sum/k;
    int start = 0;
    int end = k-1;

    while(end<n-1){
        sum -= nums[start];
        start++;
        end++;
        sum += nums[end];
        double avg = (double)sum/k;

        max_avg = max(max_avg, avg);
    }

    return max_avg;
}