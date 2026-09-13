#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

vector<int> merge_intervals(vector<vector<int>>& intervals){
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());

    vector<int> ans;
    vector<int> temp = intervals[0];

    for(int i = 1; i<n; i++){
        if(temp[1]>=intervals[i][0]){
            temp[1] = max(temp[1], intervals[i][1]);
        }
        else{
            ans.push_back(temp[0]);
            ans.push_back(temp[1]);
            temp = intervals[i];
        }
    }

    ans.push_back(temp[0]);
    ans.push_back(temp[1]);

    return ans;
}