#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool isAnagram(string s, string t){
    if(s.length()!=s.length()){
        return false;
    }

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    if(s==t){
        return true;
    }
    else{
        return false;
    }
}