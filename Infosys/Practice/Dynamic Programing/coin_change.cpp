#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include<climits>

using namespace std;

int coin(vector<int> coins, int amount){
    if(amount < 1){
        return 0;
    }
    vector<int> minCoins(amount+1);
    int n = coins.size();

    for(int i = 1; i<amount;i++){
        minCoins[i] = INT_MAX;

        for(int coin: coins){
            if(coin<=i && minCoins[i-1] != INT_MAX){
                minCoins[i] = min(minCoins[i], 1 + minCoins[i-coin]);
            }
        }
    }
    if(minCoins[amount] == INT_MAX){
        return -1;
    }
    return minCoins[amount];
}