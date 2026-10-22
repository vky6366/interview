#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

bool canjump(vector<int> &nums){
    int n = nums.size();
    int final = n-1;

    for(int i=n-2; i>=0;i--){
        if(i+nums[i]>=final){
            final = i;
        }
    }

    return final == 0;
}