#include<stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool twoSum(int n, vector<int> nums, int target){

    unordered_map<int, int> m;

    for(int i =0;i<n;i++){
        int diff = target - nums[i];
        if(m.find(diff)!=m.end()){
            return true;
        }
        else{
            m[nums[i]] = i;
        }
        }
    return false;
}
    
bool twoSum2(int n, vector<int> nums, int target){
    sort(nums.begin(), nums.end());
    int left = 0;
    int right = n-1;
    while(left<right){
        int sum = nums[left] + nums[right];
        if(sum == target){
            return true;
        }
        else if(sum < target){
            left++;
        }
        else{
            right++;
        }
    }
}