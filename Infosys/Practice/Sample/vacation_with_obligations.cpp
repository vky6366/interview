#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solve(int N, int M, int K, vector<int>& D) {
    // If no obligations or we can cancel all of them, take entire vacation
    if (M == 0 || K >= M)
        return N;

    sort(D.begin(), D.end());

    // If no cancellations allowed, find largest gap between obligations
    if (K == 0) {
        long long ans = D[0] - 1;
        for (int i = 0; i < M - 1; i++) {
            ans = max(ans, (long long)D[i + 1] - D[i] - 1);
        }
        ans = max(ans, (long long)N - D[M - 1]);
        return ans;
    }

    int left = 0;
    long long ans = 0;

    // Sliding window: window D[left...right] represents cancelled obligations
    for (int right = 0; right < M; right++) {
        // Maintain at most K cancelled obligations in the window
        while (right - left + 1 > K) {
            left++;
        }

        // Start vacation right after previous obligation (or day 1)
        long long start = (left == 0) ? 1 : D[left - 1] + 1;

        // End vacation right before next obligation (or day N)
        long long end = (right == M - 1) ? N : D[right + 1] - 1;

        long long days = end - start + 1;
        ans = max(ans, days);
    }

    return ans;
}

int main() {
    // Example: N = 15, M = 5, K = 2, D = [2, 5, 6, 10, 14]
    // Cancelling 10 and 14 gives vacation from day 7 to 15 (length = 9)
    int N = 15, M = 5, K = 2;
    vector<int> D = {2, 5, 6, 10, 14};

    cout << solve(N, M, K, D) << endl; // Output: 9

    return 0;
}
