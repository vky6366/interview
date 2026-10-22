#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool permutation_in_string(string s1, string s2){
    int n = s1.size();
    int m = s2.size();

    if(n>m) return false;

    vector<int> s1_map(26, 0);
    vector<int> s2_map(26, 0);

    for(int i=0; i<n;i++){
        s1_map[s1[i] - 'a']++;
    }
    
    int win_size = s1.size();

    for(int i = 0; i<m; i++){
        int win_start = 0;
        int idx = i;
        while(win_start < win_size && idx < m){
            s2_map[s2[idx] - 'a']++;
            win_start++;
            idx++;
        }
        if(s1_map == s2_map) return true;
    }
    return false;
}