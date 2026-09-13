#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

string isunique(string s){
    unordered_map<char,int> m;
    int n = s.length();
    queue<int> q;
    for(int i =0;i<n;i++){
        if(m.find(s[i])==m.end()){
            q.push(s[i]);
        }
        m[s[i]]++;
    }
    while(q.size()>0 && m[s[q.front()]]>1){
        q.pop();
    }
    return q.empty()?"-1":string(1,s[q.front()]);

}