#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

bool isisomorphic(string s, string t){
    if(s.length()!=t.length()){
        return false;
    }

    unordered_map<char,char> m1;

    for(int i=0;i<s.length();i++){
        if(m1.find(s[i])==m1.end()){
            if(m1.find(t[i])!=m1.end()){
                m1[s[i]] = t[i];
            }
            return false;
        }
        else{
            if(m1[s[i]]!=t[i]){
                return false;
            }
        }
    }
    return true;
}