#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool containsDuplicate(int n, vector<int> nums){
    unordered_set<int> s;

    for(int i=0;i<n;i++){
        if(s.find(nums[i])!=s.end()){
            return true;
        }
        s.insert(nums[i]);
    }
    return false;
}