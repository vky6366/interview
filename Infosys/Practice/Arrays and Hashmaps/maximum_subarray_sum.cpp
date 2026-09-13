#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int maximum_subarray(vector<int> arr){
    int curr = 0;
    int maxi = -9999999;
    int n = arr.size();
    for(int i=0;i<n;i++){
        curr += arr[i];
        maxi = max(maxi,curr);
        if(curr<0){
            curr=0;
        }
    }
    return maxi;

}