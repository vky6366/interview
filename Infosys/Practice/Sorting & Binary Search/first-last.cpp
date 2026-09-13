#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

int binary_search(vector<int>& nums, int target, bool leftBias){
    int left = 0;
    int right = nums.size() - 1;
    int i = -1;
    while(left<right){
        int mid = (left+right)/2;

        if(nums[mid]>target){
            left = mid + 1;
        }
        else if(nums[mid]<target){
            right = mid;
        }
        else{
            i = mid;
            if(leftBias){
                right = mid - 1;
            }
            else{
                left = mid + 1;
            }
        }

    }
}