#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

string iscommon(vector<string> s){
    int n = s.size();
    sort(s.begin(),s.end());
    string start = s[0];
    string end = s[n-1];
    string ans = "";
    for(int i =0; i<start.length();i++){
        if(start[i]==end[i]){
            ans+=start[i];
        }
        else{
            return ans;
        }
    }
    return start;
}