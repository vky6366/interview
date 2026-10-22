#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include<climits>

using namespace std;

int climbing(int n){
    if(n==1) return 0;

    vector<int> dp(n+1);
    dp[1] = 1;
    dp[2] = 2;


    for(int i = 3; i<n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}