#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

int max_water(vector<int>& height){
    int n = height.size();
    int i= 0;
    int j = n-1;

    int max_area = 0;

    while(i<j){
        int area = min(height[i],height[j])*(j-i);
        max_area = max(max_area, area); 
        if(height[i]<height[j]){
            i++;
        }
        else{
            j--;
        }
    }
    return max_area;
}