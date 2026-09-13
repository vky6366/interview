/**
 * Problem 2 (MEDIUM): Good Subsequence with GCD Problem
 * 
 * Description:
 * Given an array 'a' of length n and an integer p.
 * A non-empty subsequence of 'a' is GOOD if:
 * 1. The length of the subsequence is strictly less than n (length < n).
 * 2. The greatest common divisor (GCD) of its elements is exactly p.
 * 
 * We process q queries of the form:
 * i j : replace a[i] with j (1-indexed position i).
 * After each query, determine if there exists ANY good subsequence (Answer YES/NO).
 * Return the total number of queries answered YES.
 * 
 * Key Mathematical & Algorithmic Insight:
 * - Any valid subsequence whose GCD is p can only consist of elements divisible by p.
 * - Let I be the indices such that a[i] % p == 0.
 *   - If |I| == 0: No element is a multiple of p => Impossible.
 *   - If 1 <= |I| < n: The subsequence of all elements in I has length < n.
 *     Its GCD must equal p (or equivalently GCD of (a[i]/p) for i in I must equal 1).
 *     If GCD(I) > p, any subset will also have GCD >= GCD(I) > p, so impossible.
 *     Hence a good subsequence exists iff GCD(I) == p.
 *   - If |I| == n (all elements in array are multiples of p):
 *     We need to exclude at least 1 element to get length <= n - 1.
 *     A good subsequence exists iff there is some element k such that GCD(a \ {a[k]}) == p.
 * 
 * Data Structure:
 * - We use a Segment Tree over the array.
 * - Each leaf stores (cnt, gcd) of a[i] / p if a[i] % p == 0, else (0, 0).
 * - Queries and single-point updates run in O(log n * log(max_val)).
 * - Checking if removing one element yields GCD == 1 takes O(log n * log(max_val)) using GCD branching.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

long long gcd_func(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct SegNode {
    long long g = 0; // GCD of a[i] / p for elements divisible by p
    int cnt = 0;    // Count of elements divisible by p
};

struct SegTree {
    int n;
    long long p;
    vector<SegNode> tree;

    SegTree(int n, long long p, const vector<int>& a) : n(n), p(p), tree(4 * n + 4) {
        build(1, 0, n - 1, a);
    }

    SegNode combine(const SegNode& left, const SegNode& right) {
        SegNode res;
        res.cnt = left.cnt + right.cnt;
        res.g = gcd_func(left.g, right.g);
        return res;
    }

    void build(int node, int l, int r, const vector<int>& a) {
        if (l == r) {
            if (a[l] % p == 0) {
                tree[node].cnt = 1;
                tree[node].g = a[l] / p;
            } else {
                tree[node].cnt = 0;
                tree[node].g = 0;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            if (val % p == 0) {
                tree[node].cnt = 1;
                tree[node].g = val / p;
            } else {
                tree[node].cnt = 0;
                tree[node].g = 0;
            }
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, r, idx, val);
        }
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    // Check if removing one leaf from the entire tree leaves GCD == 1
    bool can_remove_one(int node, int l, int r, long long out_gcd) {
        if (out_gcd == 1) {
            return true;
        }
        if (l == r) {
            return out_gcd == 1;
        }
        int mid = (l + r) / 2;

        // Try removing an element in the left child (outside includes right child)
        long long out_for_left = gcd_func(out_gcd, tree[2 * node + 1].g);
        if (out_for_left == 1) {
            return true;
        }
        if (can_remove_one(2 * node, l, mid, out_for_left)) {
            return true;
        }

        // Try removing an element in the right child (outside includes left child)
        long long out_for_right = gcd_func(out_gcd, tree[2 * node].g);
        if (out_for_right == 1) {
            return true;
        }
        if (can_remove_one(2 * node + 1, mid + 1, r, out_for_right)) {
            return true;
        }

        return false;
    }

    bool is_good() {
        if (n <= 1) return false;
        if (tree[1].cnt == 0) return false;
        if (tree[1].cnt < n) {
            return tree[1].g == 1;
        }
        // tree[1].cnt == n: all elements divisible by p
        if (tree[1].g != 1) {
            return false;
        }
        return can_remove_one(1, 0, n - 1, 0);
    }
};

int get_ans(int n, vector<int>& a, int p, int q, vector<vector<int>>& queries) {
    SegTree st(n, p, a);
    int yes_count = 0;

    for (int k = 0; k < q; ++k) {
        int idx = queries[k][0] - 1; // 1-indexed to 0-indexed
        int val = queries[k][1];
        a[idx] = val;
        st.update(1, 0, n - 1, idx, val);
        if (st.is_good()) {
            yes_count++;
        }
    }
    return yes_count;
}

int main() {
    cout << "=== Problem 2: Good Subsequence with GCD Problem ===" << endl;

    // Sample Test Case 1
    int n1 = 2;
    vector<int> a1 = {3, 6};
    int p1 = 3, q1 = 2;
    vector<vector<int>> q_list1 = {{2, 3}, {1, 6}};
    cout << "Sample 1 Output: " << get_ans(n1, a1, p1, q1, q_list1) << " | Expected: 2" << endl;

    // Sample Test Case 2
    int n2 = 4;
    vector<int> a2 = {9, 12, 15, 18};
    int p2 = 3, q2 = 3;
    vector<vector<int>> q_list2 = {{1, 9}, {2, 6}, {4, 12}};
    cout << "Sample 2 Output: " << get_ans(n2, a2, p2, q2, q_list2) << " | Expected: 3" << endl;

    // Sample Test Case 3
    int n3 = 3;
    vector<int> a3 = {4, 5, 6};
    int p3 = 2, q3 = 3;
    vector<vector<int>> q_list3 = {{1, 3}, {2, 4}, {3, 5}};
    cout << "Sample 3 Output: " << get_ans(n3, a3, p3, q3, q_list3) << " | Expected: 1" << endl;

    return 0;
}
