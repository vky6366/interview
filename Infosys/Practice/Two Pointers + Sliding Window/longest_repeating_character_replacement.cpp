#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int repeating_char(string s, int k){
    int n = s.size();
    int start = 0;
    int max_win = 0;
    int max_freq = 0;
    unordered_map<char, int> mp;

    for(int end = 0; end<n; end++){
        mp[s[end]]++;
        max_freq = max(max_freq, mp[s[end]]);

        while((end - start + 1) - max_freq > k){
            mp[s[start]]--;
            start++;
        }
        max_win = max(max_win, (end - start + 1));
    }
    return max_win;
}