/**
 * Problem 4 (COMPLEX): Tree Edge Flipping with Pattern Matching Problem
 * 
 * Description:
 * You are given a rooted tree with N nodes labeled 0...N-1 (root 0).
 * Each node has a binary value Val[i] in {0, 1}.
 * Array Parent[i] defines the tree structure (Parent[0] = 0; Parent[i] is parent of node i).
 * 
 * You may flip a set of parent-child edges such that no two flipped edges share a node (a matching).
 * Flipping an edge toggles both endpoints' binary values (0 <-> 1) and costs M coins.
 * A root-to-leaf path is NATURAL if its node values after flips contain query string 'q' as a contiguous substring.
 * 
 * For each of Q queries:
 * 1. Choose valid flips (an edge matching) to MAXIMIZE the number of natural root-to-leaf paths.
 * 2. Among choices with maximum natural paths, pick the one with MINIMUM total cost (M * flips).
 * Apply the optimal flips to the tree, and return the SUM OF MINIMUM COSTS over all Q queries.
 * 
 * Approach:
 * - Build a KMP / string automaton for the query string q (m = |q| states).
 * - State in Tree DP:
 *   dp[u][s][p_flipped] = (max_leaves_matched, min_flips) in subtree of u
 *   where 's' is the incoming automaton state, and 'p_flipped' indicates if the edge (parent(u), u) was flipped.
 * - Transitions:
 *   1. If p_flipped is TRUE:
 *      Node u's value is Val[u] ^ 1. It cannot flip edges to its children.
 *      All children are evaluated with p_flipped = false and new state s_out = nxt[s][Val[u] ^ 1].
 *   2. If p_flipped is FALSE:
 *      - Option A (No child flipped): u's value is Val[u]. All children get p_flipped = false.
 *      - Option B (Flip edge to one child v*): u's value is Val[u] ^ 1. Child v* gets p_flipped = true.
 *        Other children get p_flipped = false. Total flips += 1.
 * - Reconstruction:
 *   Trace back the optimal choices from the root to identify flipped edges, mutate Val, and add cost.
 * 
 * Complexity:
 * - Time: O(sum(|q|) * N) per query.
 * - Space: O(N * |q|).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct DpResult {
    int leaves = 0;
    int flips = 0;

    bool operator>(const DpResult& other) const {
        if (leaves != other.leaves) return leaves > other.leaves;
        return flips < other.flips;
    }
};

struct KMPAutomaton {
    int m;
    vector<vector<int>> nxt;

    KMPAutomaton(const string& q) : m(q.size()), nxt(m + 1, vector<int>(2, 0)) {
        vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && q[i] != q[j]) j = pi[j - 1];
            if (q[i] == q[j]) j++;
            pi[i] = j;
        }

        for (int s = 0; s <= m; ++s) {
            for (int bit = 0; bit < 2; ++bit) {
                if (s == m) {
                    nxt[s][bit] = m;
                } else {
                    char c = '0' + bit;
                    if (q[s] == c) {
                        nxt[s][bit] = s + 1;
                    } else {
                        int j = (s > 0) ? pi[s - 1] : 0;
                        while (j > 0 && q[j] != c) j = pi[j - 1];
                        if (q[j] == c) j++;
                        nxt[s][bit] = j;
                    }
                }
            }
        }
    }
};

struct TreeDPSolver {
    int N;
    int M;
    vector<int> Parent;
    vector<int> Val;
    vector<vector<int>> children;

    vector<vector<vector<DpResult>>> dp;
    vector<vector<vector<int>>> choice;
    vector<vector<vector<bool>>> computed;

    TreeDPSolver(int N, int M, const vector<int>& Parent, const vector<int>& Val)
        : N(N), M(M), Parent(Parent), Val(Val), children(N) {
        for (int i = 1; i < N; ++i) {
            children[Parent[i]].push_back(i);
        }
    }

    DpResult dfs(int u, int s, int p_flipped, const KMPAutomaton& aut) {
        if (computed[u][s][p_flipped]) {
            return dp[u][s][p_flipped];
        }

        DpResult res;
        int best_child = -1;

        if (p_flipped) {
            int cur_val = Val[u] ^ 1;
            int s_out = aut.nxt[s][cur_val];

            if (children[u].empty()) {
                res.leaves = (s_out == aut.m ? 1 : 0);
                res.flips = 0;
            } else {
                res.leaves = 0;
                res.flips = 0;
                for (int v : children[u]) {
                    DpResult c_res = dfs(v, s_out, 0, aut);
                    res.leaves += c_res.leaves;
                    res.flips += c_res.flips;
                }
            }
            best_child = -1;
        } else {
            // Option 1: No edge flipped to any child
            int cur_val = Val[u];
            int s_out = aut.nxt[s][cur_val];

            DpResult opt1;
            if (children[u].empty()) {
                opt1.leaves = (s_out == aut.m ? 1 : 0);
                opt1.flips = 0;
            } else {
                opt1.leaves = 0;
                opt1.flips = 0;
                for (int v : children[u]) {
                    DpResult c_res = dfs(v, s_out, 0, aut);
                    opt1.leaves += c_res.leaves;
                    opt1.flips += c_res.flips;
                }
            }

            res = opt1;
            best_child = -1;

            // Option 2: Flip edge to one child v
            if (!children[u].empty()) {
                int cur_val_flipped = Val[u] ^ 1;
                int s_out_flipped = aut.nxt[s][cur_val_flipped];

                int sum_leaves_noflip = 0;
                int sum_flips_noflip = 0;
                vector<DpResult> no_flip_res(children[u].size());
                for (size_t i = 0; i < children[u].size(); ++i) {
                    no_flip_res[i] = dfs(children[u][i], s_out_flipped, 0, aut);
                    sum_leaves_noflip += no_flip_res[i].leaves;
                    sum_flips_noflip += no_flip_res[i].flips;
                }

                for (size_t i = 0; i < children[u].size(); ++i) {
                    int v = children[u][i];
                    DpResult flip_v = dfs(v, s_out_flipped, 1, aut);

                    DpResult opt2;
                    opt2.leaves = sum_leaves_noflip - no_flip_res[i].leaves + flip_v.leaves;
                    opt2.flips = 1 + sum_flips_noflip - no_flip_res[i].flips + flip_v.flips;

                    if (opt2 > res) {
                        res = opt2;
                        best_child = v;
                    }
                }
            }
        }

        computed[u][s][p_flipped] = true;
        dp[u][s][p_flipped] = res;
        choice[u][s][p_flipped] = best_child;
        return res;
    }

    void reconstruct(int u, int s, int p_flipped, const KMPAutomaton& aut, vector<int>& flipped_nodes) {
        if (p_flipped) {
            int cur_val = Val[u] ^ 1;
            int s_out = aut.nxt[s][cur_val];
            for (int v : children[u]) {
                reconstruct(v, s_out, 0, aut, flipped_nodes);
            }
        } else {
            int best_child = choice[u][s][0];
            if (best_child == -1) {
                int cur_val = Val[u];
                int s_out = aut.nxt[s][cur_val];
                for (int v : children[u]) {
                    reconstruct(v, s_out, 0, aut, flipped_nodes);
                }
            } else {
                flipped_nodes.push_back(u);
                flipped_nodes.push_back(best_child);
                int cur_val = Val[u] ^ 1;
                int s_out = aut.nxt[s][cur_val];
                for (int v : children[u]) {
                    if (v == best_child) {
                        reconstruct(v, s_out, 1, aut, flipped_nodes);
                    } else {
                        reconstruct(v, s_out, 0, aut, flipped_nodes);
                    }
                }
            }
        }
    }

    int process_queries(int Q, const vector<string>& queries) {
        long long total_cost = 0;

        for (int i = 0; i < Q; ++i) {
            const string& q = queries[i];
            KMPAutomaton aut(q);
            int m = aut.m;

            dp.assign(N, vector<vector<DpResult>>(m + 1, vector<DpResult>(2)));
            choice.assign(N, vector<vector<int>>(m + 1, vector<int>(2, -1)));
            computed.assign(N, vector<vector<bool>>(m + 1, vector<bool>(2, false)));

            DpResult best = dfs(0, 0, 0, aut);
            total_cost += 1LL * best.flips * M;

            vector<int> flipped_nodes;
            reconstruct(0, 0, 0, aut, flipped_nodes);
            for (int node : flipped_nodes) {
                Val[node] ^= 1;
            }
        }

        return total_cost;
    }
};

int get_ans(int N, int M, vector<int>& Parent, vector<int>& Val, int Q, vector<string>& queries) {
    TreeDPSolver solver(N, M, Parent, Val);
    return solver.process_queries(Q, queries);
}

int main() {
    cout << "=== Problem 4: Tree Edge Flipping with Pattern Matching ===" << endl;

    // Sample Test Case 1
    int N1 = 6, M1 = 3;
    vector<int> Parent1 = {0, 0, 0, 1, 1, 2};
    vector<int> Val1 = {1, 0, 1, 1, 0, 0};
    int Q1 = 2;
    vector<string> queries1 = {"10", "011"};
    cout << "Sample 1 Output: " << get_ans(N1, M1, Parent1, Val1, Q1, queries1) << " | Expected: 6" << endl;

    // Sample Test Case 2
    int N2 = 4, M2 = 3;
    vector<int> Parent2 = {0, 0, 1, 1};
    vector<int> Val2 = {0, 0, 0, 0};
    int Q2 = 2;
    vector<string> queries2 = {"10", "11"};
    cout << "Sample 2 Output: " << get_ans(N2, M2, Parent2, Val2, Q2, queries2) << " | Expected: 3" << endl;

    // Sample Test Case 3
    int N3 = 5, M3 = 3;
    vector<int> Parent3 = {0, 0, 1, 1, 2};
    vector<int> Val3 = {0, 1, 0, 1, 0};
    int Q3 = 2;
    vector<string> queries3 = {"01", "10"};
    cout << "Sample 3 Output: " << get_ans(N3, M3, Parent3, Val3, Q3, queries3) << " | Expected: 3" << endl;

    return 0;
}
