#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

int remove_duplicate(vector<int>& nums){
    int n = nums.size();
    if(n==0){
        return 0;
    }

    int i = 0;
    for(int j =0;j<n;j++){
        if(nums[i]!=nums[j]){
            i++;
            nums[i] = nums[j];
        }
    }
    return vector<int>(nums.begin(), nums.begin()+i+1).size();
}