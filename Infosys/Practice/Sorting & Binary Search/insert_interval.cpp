#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

vector<int> insert_interval(vector<vector<int>>& intervals, vector<int>& newInterval){
    vector<int> result;

    int i = 0;
    int n = intervals.size();
    while(i<n && intervals[i][1]<newInterval[0]){
        result.push_back(intervals[i][0]);
        result.push_back(intervals[i][1]);
        i++;
    }

    while(i<n && intervals[i][0]<=newInterval[1]){
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }

    result.push_back(newInterval[0]);
    result.push_back(newInterval[1]);

    while(i<n){
        result.push_back(intervals[i][0]);
        result.push_back(intervals[i][1]);
        i++;
    }
    return result;
}