#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

int subarray(vector<int>& nums, int target){
    int min_length = INT_MAX;
    int curr_sum = 0;

    int left = 0;
    int right = 0;

    while(right<nums.size()){
        curr_sum += nums[right];
        right++;

        while(curr_sum>=target){
            min_length = min(min_length, right-left);
            curr_sum -= nums[left];
            left++;
        }
    }
    return min_length == INT_MAX ? 0 : min_length;
}