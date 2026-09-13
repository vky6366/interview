#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int missing(vector<int> arr, int n){
    int total_sum = n*(n+1)/2;

    int arr_sum = 0;
    for(int i = 0;i<n;i++){
        arr_sum += arr[i];
    }
    int missing_element = total_sum - arr_sum;

    if(missing_element==0){
        return -1;
    }
    else{
        return missing_element;
    }
}