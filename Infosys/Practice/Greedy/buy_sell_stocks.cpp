#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

int maxprofit(vector<int> &prices){
    int n = prices.size();

    int profit = 0;
    for(int i=1; i<n; i++){
        if(prices[i]>prices[i-1]){
            profit += prices[i] - prices[i-1];
        }
    }
    return profit;
}