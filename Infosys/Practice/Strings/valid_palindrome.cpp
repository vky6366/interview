#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int ispalindrome(string s){
    int n = s.size();
    int i = 0;
    int j = n-1;

    while(i<j){
        if(s[i]!=s[j]){
            return 0;
        }
        if(!isalnum(tolower(s[i]))){
            i++;
        }
        if(!isalnum(tolower(s[j]))){
            j--;
        }
        else{
            i++;
            j--;
        }
    }
    return 1;
}