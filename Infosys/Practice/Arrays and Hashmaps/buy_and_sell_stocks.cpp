#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int maxprofit(vector<int> prices){
    int mini = prices[0];
    int max_profit = 0;
    int n = prices.size();

    for(int i=0;i<n;i++){
        mini = min(mini,prices[i]);
        max_profit = max(max_profit, prices[i]-mini);
    }

    return max_profit;
}