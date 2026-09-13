#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

int find_min(vector<int>& nums){
    int n = nums.size();

    int left = 0;
    int right = n-1;

    while(left<right){
        int mid = left + (right+left)/2;
        if(nums[mid] > nums[right]){
            left  = mid + 1;
        }
        else{
            right = mid;
        }
    }
    return nums[left];
}