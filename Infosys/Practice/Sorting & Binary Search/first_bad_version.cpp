#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

int first_bad(vector<int>& nums){
    int left = 0;
    int right = nums.size() - 1;

    while(left<right){
        int mid = (left + right) / 2;
        if(nums[mid] == 1){
            right = mid;
        }
        else{
            left = mid + 1;
        }
        }
    return left;
    }