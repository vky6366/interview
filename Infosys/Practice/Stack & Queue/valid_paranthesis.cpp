#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;


bool isValid(string s){
    stack<char> st;

    for(char c:s){
        if(c == '(' || c =='{' || c == '['){
            st.push(c);
        }
        else{
            if(st.empty()){
                return false;
            }

            if ((c == '(' && st.top() == ')' || c == '(' && st.top() == ')' || c == '{' && st.top() == '}' || c == '[' && st.top() == ']')){
                st.pop();
            }
            else{
                return false;
            }
        }
    }

    return st.empty();
}