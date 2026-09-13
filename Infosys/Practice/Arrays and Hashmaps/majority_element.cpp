#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int majority_element(vector<int> nums){
    unordered_map<int, int> m;
    int n = nums.size();
    for(int i =0; i<n;i++){
        m[nums[i]]++;
    }
    for(auto it:nums){
        if(m[it]>(n/2)){
            return it;
        }
    }
    return -1;
}