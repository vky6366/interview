#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

int twosum(vector<int>& nums, int target){
    int n = nums.size();
    int i = 0;
    int j = n-1;
    while(i<j){
        if(nums[i]+nums[j]==target){
            return 1;
        }
        else if(nums[i]+nums[j]<target){
            i++;
        }   
        else{
            j--;
        } 
    }
    return 0;
}