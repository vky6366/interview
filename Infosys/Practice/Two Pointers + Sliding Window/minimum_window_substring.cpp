#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include<climits>

using namespace std;

bool contains(const vector<int> &Bcount, const vector<int> &Scount){
    for(int i =0; i<256; i++){
        if(Scount[i] > Bcount[i]){
            return false;
        }
    }
    return true;
}

int min_window(string small, string big){
    int s_size = small.size();
    int b_size = big.size();

    vector<int> big_freq(256, 0);
    vector<int> small_freq(256, 0);

    for(int i = 0; i<s_size; i++){
        small_freq[small[i]]++;
    }
    int left = 0;
    int minLen = INT_MAX;
    int minstart = 0;

    for(int right = 0; right < b_size; right++){
        big_freq[big[right]]++;

        while(contains(small_freq, big_freq)){
            if(right - left + 1 < minLen){
                minLen = right - left + 1;
                minstart = left;
            }
            big_freq[big[left]]--;
            left++;
           
        }
    }
    return minLen;
}