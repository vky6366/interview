#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

vector<int> nextGreater(vector<int>& nums){
    vector<int> res(nums.size(), -1);
    stack<int> st;
    int n = nums.size();

    for(int i = n-1; i>=0;i--){
        while(st.size() > 0 && st.top() <= nums[i]){
            st.pop();
        }
        if(st.size()>0){
            res[i] = st.top();
        }
        else{
            res[i] = -1;
        }
        st.push(nums[i]);
    }
}