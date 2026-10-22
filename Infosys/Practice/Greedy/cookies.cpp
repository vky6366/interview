#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;


int assign(vector<int> &cookies, vector<int> &children){
    sort(cookies.begin(), cookies.end());
    sort(children.begin(), children.end());

    int n = cookies.size();
    int m = children.size();

    int i = 0, j = 0;

    while(i<n && j<m){
        if(cookies[i]>=children[j]){
            j++;
        }

        i++;
    }
    return j;
}