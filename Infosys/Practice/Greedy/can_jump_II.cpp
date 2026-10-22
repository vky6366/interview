#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

int canjump(vector<int> &nums){
    int n = nums.size();

    int coverage = 0;
    int total_jumps = 0;
    int last_jump = 0;

    int destination = nums.size() - 1;

    for(int i=0; i<n;i++){
        coverage = max(coverage, i+nums[i]);

        if(i==last_jump){
            total_jumps++;
            last_jump = coverage;


            if(last_jump >= destination){
                return total_jumps;
            }
        }
    }
    return total_jumps;
}