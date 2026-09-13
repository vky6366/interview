/**
 * Problem 1 (EASY): Tree Beauty Problem
 * 
 * Description:
 * Given a tree of n nodes rooted at node 1, where each node i has value a[i].
 * A pair of nodes (i, j) with 1 <= i < j <= n is GOOD if a[i] * a[j] is a perfect square.
 * beauty(u) is the number of good pairs in the subtree of u.
 * Calculate sum(beauty(i)) for all 1 <= i <= n modulo 10^9 + 7.
 * 
 * Key Mathematical Insight:
 * Two positive integers x and y multiply to a perfect square iff their square-free cores are identical:
 * core(x) = core(y).
 * 
 * Approach:
 * - Reduce each a[i] to its square-free core: core(a[i]) in O(sqrt(a[i])).
 * - Use Subtree Merging (Small-to-Large merging / Sack) with frequency maps.
 * - In DFS, for node u, merge child frequency maps into the largest map:
 *   When adding count elements with core value 'c' to existing 'cur_count' elements:
 *   Subtree good pairs increase by (count * cur_count).
 * - Total time complexity: O(n * sqrt(max_a) + n log^2 n) or O(n log n).
 * - Space complexity: O(n).
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const int MOD = 1000000007;

// Function to compute the square-free core of a number x
long long get_square_free(long long x) {
    long long res = 1;
    for (long long d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            int cnt = 0;
            while (x % d == 0) {
                cnt++;
                x /= d;
            }
            if (cnt % 2 != 0) {
                res *= d;
            }
        }
    }
    if (x > 1) {
        res *= x;
    }
    return res;
}

struct NodeInfo {
    unordered_map<long long, int> freq;
    long long good_pairs = 0; // Total good pairs in this subtree
};

void dfs(int u, const vector<vector<int>>& adj, const vector<long long>& core,
         vector<NodeInfo*>& maps, long long& total_beauty) {
    NodeInfo* cur = new NodeInfo();
    cur->freq[core[u]] = 1;
    cur->good_pairs = 0;

    for (int v : adj[u]) {
        dfs(v, adj, core, maps, total_beauty);
        NodeInfo* child = maps[v];

        // Small-to-large merge
        if (cur->freq.size() < child->freq.size()) {
            swap(cur, child);
        }

        // Add internal good pairs from child
        cur->good_pairs += child->good_pairs;

        // Add cross good pairs between subtrees
        for (const auto& p : child->freq) {
            long long val = p.first;
            int count = p.second;
            int cur_count = cur->freq[val];
            cur->good_pairs += (1LL * count * cur_count);
            cur->freq[val] += count;
        }
        delete child;
    }

    maps[u] = cur;
    total_beauty = (total_beauty + (cur->good_pairs % MOD)) % MOD;
}

int get_ans(int n, vector<int>& par, vector<int>& a) {
    // par[0] = 0 (root), par[i] is parent of node i+1 (1-indexed nodes)
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int parent = par[i];
        int child = i + 1;
        adj[parent].push_back(child);
    }

    vector<long long> core(n + 1);
    for (int i = 0; i < n; ++i) {
        core[i + 1] = get_square_free(a[i]);
    }

    vector<NodeInfo*> maps(n + 1, nullptr);
    long long total_beauty = 0;
    dfs(1, adj, core, maps, total_beauty);

    delete maps[1];
    return total_beauty % MOD;
}

int main() {
    cout << "=== Problem 1: Tree Beauty Problem ===" << endl;

    // Sample Test Case 1
    int n1 = 5;
    vector<int> par1 = {0, 1, 1, 2, 2};
    vector<int> a1 = {2, 3, 6, 12, 27};
    cout << "Sample 1 Output: " << get_ans(n1, par1, a1) << " | Expected: 6" << endl;

    // Sample Test Case 2
    int n2 = 2;
    vector<int> par2 = {0, 1};
    vector<int> a2 = {4, 9};
    cout << "Sample 2 Output: " << get_ans(n2, par2, a2) << " | Expected: 1" << endl;

    // Sample Test Case 3
    int n3 = 3;
    vector<int> par3 = {0, 1, 1};
    vector<int> a3 = {2, 8, 18};
    cout << "Sample 3 Output: " << get_ans(n3, par3, a3) << " | Expected: 3" << endl;

    return 0;
}
