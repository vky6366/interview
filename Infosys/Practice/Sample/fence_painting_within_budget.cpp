#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

long long solve(vector<vector<int>>& cost, long long B) {
    int N = cost.size();
    if (N == 0) return 0;
    int C = cost[0].size();

    // If only 1 color is available and more than 1 house, impossible
    if (C == 1 && N > 1)
        return -1;

    vector<vector<long long>> dp(N, vector<long long>(C));

    // First house
    for (int j = 0; j < C; j++) {
        dp[0][j] = cost[0][j];
    }

    // Remaining houses
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < C; j++) {
            long long best = LLONG_MAX;

            // Previous house must have a different color
            for (int k = 0; k < C; k++) {
                if (k != j) {
                    best = min(best, dp[i - 1][k]);
                }
            }

            dp[i][j] = cost[i][j] + best;
        }
    }

    // Minimum cost for the last house
    long long answer = LLONG_MAX;
    for (int j = 0; j < C; j++) {
        answer = min(answer, dp[N - 1][j]);
    }

    // Check against budget
    if (answer <= B)
        return answer;

    return -1;
}

int main() {
    // Example: cost = [[1, 5, 3], [2, 9, 4], [3, 1, 7]], Budget = 10
    // Minimum painting cost = 1 + 4 + 1 = 6 <= 10
    vector<vector<int>> cost = {
        {1, 5, 3},
        {2, 9, 4},
        {3, 1, 7}
    };
    long long B = 10;

    cout << solve(cost, B) << endl; // Output: 6

    return 0;
}
