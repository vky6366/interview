#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

string reverse_word(string s){
    int n = s.length();
    reverse(s.begin(),s.end());
    string ans = "";
    for(int i=0; i<n;i++){
        string word = "";
        while(i<n && s[i]!=' '){
            word += s[i];
            i++;
        }
        reverse(word.begin(),word.end());
        if(word.length()>0){
            ans+=word;
            ans+=" ";
        }
    }
    return ans.substr(1);
}