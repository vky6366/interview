#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> findanagrams(string s, string p){
    int n = s.size();
    int m = p.size();
    vector<int> s_freq(26, 0);
    vector<int> p_freq(26, 0);
    vector<int> res;

    for(int i = 0; i<m; i++){
        p_freq[p[i] - 'a']++;
    }

    for(int i = 0; i<n; i++){
        s_freq[s[i] - 'a']++;

        if(i>m){
            s_freq[s[i - m] - 'a']--;
        }

        if(s_freq == p_freq){
            res.push_back(i - m + 1);
        }
    }
    return res;

}