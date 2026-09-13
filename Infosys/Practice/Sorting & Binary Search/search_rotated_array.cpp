#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

int search_rotated(vector<int>& nums, int target){
    int left = 0;
    int right = nums.size() - 1;

    while(left<right){
        int mid = (left + right) / 2;
        if(nums[mid] == target){
            return mid;
        }

        if(nums[left] <= nums[mid]){
            if(nums[left]<=target && target<nums[mid]){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        else{
            if(nums[mid]<target && target<=nums[right]){
                left = mid + 1;
            }
            else{
                right = mid;
            }
        }
    }
    return -1;
}