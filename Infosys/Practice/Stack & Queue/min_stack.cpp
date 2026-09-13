#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

class MinStack{
    stack<pair<int,int>> st;

    public:
    void push(int x){
        if(st.empty()){
            st.push({x,x});
        }
        else{
            int min_val = min(x, st.top().second);
            st.push({x, min_val});
        }
    }
    void pop(){
        if(!st.empty()){
            st.pop();
        }
    }

    int top(){
        if(!st.empty()){
            return st.top().first;
        }
    }

    int getMin(){
        if(!st.empty()){
            return st.top().second;
        }
    }
};