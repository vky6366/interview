#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

vector<int>& sorted_square(vector<int>& nums){
    int n = nums.size();

    vector<int> ans(n);

    for(int i=0;i<n;i++){
        nums[i] = nums[i]*nums[i];
    }

    int i = 0;
    int j = n-1;
    while(i<=j){
        if(nums[i]<nums[j]){
            ans[n-1] = nums[j];
            j--;
        }
        else{
            ans[n-1] = nums[i];
            i++;
        }
    }
    return ans;
}