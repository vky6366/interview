#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int length_longest_substring(string s){
    int n = s.size();
    unordered_map<char, int> mp;


    int start = 0;
    int max_len = 0;

    for(int end = 0; end< n; end++){
        while(mp.find(s[end]) != mp.end()){
            mp.erase(s[start]);
            start++;
        }
        mp[s[end]] = end;
        int max_len = max(max_len, end - start + 1);
    }
    return max_len;
}