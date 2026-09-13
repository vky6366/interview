#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> meeting_rooms(vector<int> start, vector<int> end){
    int n = start.size();

    vector<tuple<int, int, int>> meetings;

    for(int i = 0;i<n;i++){
        meetings.push_back(make_tuple(end[i], start[i], i));
    }

    sort(meetings.begin(), meetings.end());

    vector<int> ans;
    int last_end = -1;

    for(int i = 0; i<n;i++){
        int s = get<1>(meetings[i]);
        int e = get<0>(meetings[i]);
        int idx = get<2>(meetings[i]);

        if(s>=last_end){
            ans.push_back(idx);
            last_end = e;
        }
    }
    return ans;
}