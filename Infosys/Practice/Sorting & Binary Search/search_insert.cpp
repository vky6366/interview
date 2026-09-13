#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

int search_insert(vector<int>& nums, int target){
    int left = 0;
    int right = nums.size()-1;

    while(left<right){
        int mid = (left + right) /2;
        if(nums[mid] == target){
            return mid;
        }
        else if(nums[mid]>target){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    return left;
}