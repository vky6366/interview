#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

string get_freq(string s){
    int freq[26] = {0};

    for(char c : s){
        freq[c - 'a']++;
    }
    return string(freq, freq + 26);
}

vector<vector<string>> group_anagrams(vector<string>& strs){
    unordered_map<string, vector<string>> anagram_map;
    int n = strs.size();
    if(strs.empty() || strs.size() == 0){
        return {};
    }

    for(int i =0;i<n;i++){
        string freq = get_freq(strs[i]);
        anagram_map[freq].push_back(strs[i]);
    }

    vector<vector<string>> result;
    for(const auto& pair : anagram_map){
        result.push_back(pair.second);
    }

    return result;
}