# Infosys Specialist Programmer (SP) L3 — DSA Revision Checklist

---

## 🔥 Tier 1 — Must Revise (Core High-Yield Patterns)

| Status | # | Problem | Pattern / Strategy | LeetCode Equivalent |
| :---: | :---: | :--- | :--- | :--- |
| [x] | 1 ⭐ | **Two Sum** | Hashing ($O(N)$ with target complement lookup) | [LC 1](https://leetcode.com/problems/two-sum/) |
| [x] | 2 ⭐ | **Maximum Subarray (Kadane's Algorithm)** | Greedy / Dynamic Programming ($O(N)$ running sum) | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| [ ] | 3 ⭐ | **Subarray Sum Equals K** | Prefix Sum + HashMap ($O(N)$ prefix frequency) | [LC 560](https://leetcode.com/problems/subarray-sum-equals-k/) |
| [x] | 4 ⭐ | **Longest Substring Without Repeating Characters** | Sliding Window + HashSet / Index Map | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| [x] | 5 ⭐ | **Longest Repeating Character Replacement** | Sliding Window (window length - max_freq $\le k$) | [LC 424](https://leetcode.com/problems/longest-repeating-character-replacement/) |
| [x] | 6 ⭐ | **Minimum Size Subarray Sum** | Variable-size Sliding Window ($O(N)$ two pointers) | [LC 209](https://leetcode.com/problems/minimum-size-subarray-sum/) |
| [x] | 7 ⭐ | **Search in Rotated Sorted Array** | Modified Binary Search (identify sorted half) | [LC 33](https://leetcode.com/problems/search-in-rotated-sorted-array/) |
| [x] | 8 ⭐ | **Merge Intervals** | Sorting + Intervals ($O(N \log N)$ sort by start time) | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| [x] | 9 ⭐ | **Valid Parentheses** | Stack (LIFO matching open/close brackets) | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| [ ] | 10 ⭐ | **Daily Temperatures** | Monotonic Stack (Decreasing stack of indices) | [LC 739](https://leetcode.com/problems/daily-temperatures/) |
| [x] | 11 ⭐ | **Reverse Linked List** | Linked List (Iterative 3-pointers `prev, curr, next`) | [LC 206](https://leetcode.com/problems/reverse-linked-list/) |
| [x] | 12 ⭐ | **Linked List Cycle** | Floyd's Fast & Slow Pointers ($O(1)$ space cycle check) | [LC 141](https://leetcode.com/problems/linked-list-cycle/) |
| [x] | 13 ⭐ | **Binary Tree Level Order Traversal** | Tree BFS (`std::queue` with queue size per level) | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| [x] | 14 ⭐ | **Validate Binary Search Tree** | Tree DFS (Pass valid range bounds `(min_val, max_val)`) | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) |
| [x] | 15 ⭐ | **Number of Islands** | Graph DFS / BFS (Matrix traversal & connected components) | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| [ ] | 16 ⭐ | **Graph Cycle Detection** | DFS / BFS (Visited array + Path visited / Parent pointer / Kahn's) | [LC 207](https://leetcode.com/problems/course-schedule/) |
| [x] | 17 ⭐ | **Climbing Stairs** | Dynamic Programming (Fibonacci state transition $dp[i] = dp[i-1] + dp[i-2]$) | [LC 70](https://leetcode.com/problems/climbing-stairs/) |
| [x] | 18 ⭐ | **House Robber** | Dynamic Programming ($dp[i] = \max(dp[i-1], dp[i-2] + nums[i])$) | [LC 198](https://leetcode.com/problems/house-robber/) |
| [ ] | 19 ⭐ | **Coin Change** | Dynamic Programming (Unbounded knapsack / Min coins $dp[i] = \min(dp[i - c] + 1)$) | [LC 322](https://leetcode.com/problems/coin-change/) |

---

## 🧠 Tier 2 — Strong Second-Pass Revision

| Status | # | Problem | Pattern / Strategy | LeetCode Equivalent |
| :---: | :---: | :--- | :--- | :--- |
| [x] | 20 | **Majority Element** | Boyer-Moore Voting Algorithm ($O(N)$ time, $O(1)$ space) | [LC 169](https://leetcode.com/problems/majority-element/) |
| [x] | 21 | **Missing Number** | Bit Manipulation (XOR cancellation) / Gauss Sum Formula | [LC 268](https://leetcode.com/problems/missing-number/) |
| [x] | 22 | **Container With Most Water** | Two Pointers (Shrink pointer with smaller height) | [LC 11](https://leetcode.com/problems/container-with-most-water/) |
| [ ] | 23 | **Remove Duplicates from Sorted Array** | Two Pointers (In-place partition write pointer) | [LC 26](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) |
| [x] | 24 | **Find Minimum in Rotated Sorted Array** | Binary Search (Compare `mid` with `right` boundary) | [LC 153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) |
| [x] | 25 | **Next Greater Element I** | Monotonic Stack + Hash Map | [LC 496](https://leetcode.com/problems/next-greater-element-i/) |
| [x] | 26 | **Evaluate Reverse Polish Notation** | Stack (Evaluate operators by popping 2 operands) | [LC 150](https://leetcode.com/problems/evaluate-reverse-polish-notation/) |
| [x] | 27 | **Merge Two Sorted Lists** | Linked List (Dummy head pointer iteration) | [LC 21](https://leetcode.com/problems/merge-two-sorted-lists/) |
| [ ] | 28 | **Maximum Depth of Binary Tree** | Tree DFS ($1 + \max(\text{depth}(left), \text{depth}(right))$) | [LC 104](https://leetcode.com/problems/maximum-depth-of-binary-tree/) |
| [ ] | 29 | **Diameter of Binary Tree** | Tree DFS (Global max update: $left\_height + right\_height$) | [LC 543](https://leetcode.com/problems/diameter-of-binary-tree/) |
| [x] | 30 | **House Robber II** | Circular DP ($\max(\text{Rob}(0 \dots n-2), \text{Rob}(1 \dots n-1))$) | [LC 213](https://leetcode.com/problems/house-robber-ii/) |

---

## 🎯 Quick Revision Strategy for Infosys SP L3

1. **Explain First, Code Second:** For every problem above, practice speaking the intuition aloud (e.g., *"Why does Boyer-Moore work?"*, *"Why does a monotonic stack give $O(N)$ amortized time?"*).
2. **State Edge Cases:** Empty array, single element, negative numbers, overflow boundaries, duplicates, non-existent targets.
3. **Analyze Complexity:** State Time and Space complexities immediately before writing code.
