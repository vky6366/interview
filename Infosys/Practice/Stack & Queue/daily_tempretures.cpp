#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

vector<int> daily_temp(vector<int>& temp){
    int n = temp.size();

    vector<int> result(n,0);
    stack<int> st;

    for(int i=n-1; i>=0;i--){
        while(!st.empty() && temp[i] > temp[st.top()]){
            st.pop();
            
        }
        if(!st.empty()){
            result[i] = st.top() - i;
        }

        st.push(i);
    }
    return result;
}