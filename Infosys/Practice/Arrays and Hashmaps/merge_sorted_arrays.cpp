#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int merge_sorted(vector<int> arr1, int m, vector<int> arr2, int n){
    int idx = m + n -1;
    int i = m - 1;
    int j = n - 1;

    while(i>=0 && j>=0){
        if(arr1[i]>arr2[j]){
            arr1[idx] = arr1[i];
            i--;
            idx--;
        }
        else{
            arr1[idx] = arr2[j];
            j--;
            idx--;
        }
    }

    while(j>=0){
        arr1[idx] = arr2[j];
        j--;
        idx--;
    }
    while(i>=0){
        arr1[idx] = arr1[i];
        i--;
        idx--;
    }
    return 0;
}