# Solutions to Sample Test Questions (SP / DSE Assessment)

This folder contains optimal C++ solutions for all 4 coding assessment questions from [`Sample_Test_SP_DSE.pdf`](file:///d:/Learning/DSA/Practice/Sample_Test_SP_DSE.pdf).

---

## 1. Easy: Tree Beauty Problem
- **File**: [`tree_beauty_problem.cpp`](file:///d:/Learning/DSA/Practice/Sample/tree_beauty_problem.cpp)
- **Core Concept**: Subtree DSU / Small-to-Large Merging & Number Theory (Square-free reduction).
- **Key Insight**: 
  - $a[i] \times a[j]$ is a perfect square if and only if their square-free cores are equal: $\text{core}(a[i]) = \text{core}(a[j])$.
  - We reduce each node's value to its square-free core in $O(\sqrt{a[i]})$.
  - We run a bottom-up DFS maintaining frequency maps with small-to-large merging (`std::swap`). When merging a child's map into the parent's map, the number of good pairs formed increases by $\text{count} \times \text{existing\_count}$.
- **Complexity**:
  - **Time**: $O(N \log^2 N + N \sqrt{\max A})$
  - **Space**: $O(N)$

---

## 2. Medium: Good Subsequence with GCD Problem
- **File**: [`good_subsequence_gcd_problem.cpp`](file:///d:/Learning/DSA/Practice/Sample/good_subsequence_gcd_problem.cpp)
- **Core Concept**: Segment Tree with Point Updates & Number Theory.
- **Key Insight**:
  - Only elements divisible by $p$ can be part of a subsequence whose GCD equals $p$.
  - Let $I = \{i \mid a[i] \pmod p == 0\}$.
    - If $|I| < n$: A valid subsequence of length $< n$ exists iff $\gcd_{i \in I}(a[i] / p) == 1$.
    - If $|I| == n$: All elements are multiples of $p$. We must remove at least 1 element so that $|S| \le n - 1$. A valid subsequence exists iff there exists an index $k$ such that $\gcd_{i \ne k}(a[i] / p) == 1$.
  - A segment tree tracks the count of divisible elements and their GCD. When all elements are divisible, we recursively check if removing one element yields GCD $1$ in $O(\omega(\max A) \log n)$ time.
- **Complexity**:
  - **Time**: $O((N + Q) \log N \log(\max A))$
  - **Space**: $O(N)$

---

## 3. Hard: Longest Non-Decreasing Subsequence with XOR Problem
- **File**: [`longest_non_decreasing_subsequence_xor.cpp`](file:///d:/Learning/DSA/Practice/Sample/longest_non_decreasing_subsequence_xor.cpp)
- **Core Concept**: 2D Dynamic Programming with Fenwick Tree (Binary Indexed Tree).
- **Key Insight**:
  - Given $A[i] \le N \le 1000$ and $M \le 500$, the maximum possible bitwise XOR sum is $< 1024$.
  - We define $DP[x][v]$ as the maximum length of a non-decreasing subsequence with XOR sum $x$ ending at value $\le v$.
  - To transition in $O(\log N)$, we maintain a Fenwick Tree for each XOR value $x \in [0, 1023]$ over the value range $[1, \max A]$.
  - For each element $A[i] = v$, we query previous maximum lengths for all $x$, and update the BIT at value $v$ with $(x \oplus v)$ and length $\text{len} + 1$.
- **Complexity**:
  - **Time**: $O(N \times 1024 \log(\max A)) \approx 10^7$ ops (~15 ms)
  - **Space**: $O(1024 \times \max A) \approx 4\text{ MB}$

---

## 4. Complex: Tree Edge Flipping with Pattern Matching Problem
- **File**: [`tree_edge_flipping_pattern_matching.cpp`](file:///d:/Learning/DSA/Practice/Sample/tree_edge_flipping_pattern_matching.cpp)
- **Core Concept**: Tree DP with String Matching Automaton (KMP/Aho-Corasick) & Maximum Weight Matching on Trees.
- **Key Insight**:
  - Flipping a parent-child edge toggles both endpoints' values and costs $M$ coins. Flipped edges must form a matching (no two flipped edges share a node).
  - For a query string $q$, we build a KMP automaton with states $0 \dots |q|$ where state $|q|$ is the terminal matched state.
  - Tree DP state: `dp[u][s][p_flipped]` stores `(max_natural_leaves, min_flips)` in the subtree of $u$ with incoming state $s$:
    - If `p_flipped == true`: Node $u$ was flipped by its parent, so its effective value is $Val[u] \oplus 1$. It cannot flip edges to its children.
    - If `p_flipped == false`: Node $u$ can either not flip to any child, or flip an edge to at most one child $v^*$.
  - Traceback reconstructs the flipped edges, updates the node values for subsequent queries, and calculates total cost.
- **Complexity**:
  - **Time**: $O(\sum |q| \times N)$
  - **Space**: $O(N \times |q|)$

---

## 5. Vacation with Obligations (Longest Range with at most K cancellations)
- **File**: [`vacation_with_obligations.cpp`](file:///d:/Learning/DSA/Practice/Sample/vacation_with_obligations.cpp)
- **Core Concept**: Sliding Window / Two Pointers / Padded Boundary Sentinels.
- **Key Insight**:
  - Finding the longest continuous vacation containing at most $K$ obligations is an instance of the "longest subarray with at most $K$ bad elements" pattern.
  - After sorting obligation days $D$, a window of obligations $D[left \dots right]$ of size $\le K$ can be cancelled.
  - The vacation extends to all available free days on both sides:
    - $\text{start} = (left == 0) \; ? \; 1 : D[left - 1] + 1$
    - $\text{end} = (right == M - 1) \; ? \; N : D[right + 1] - 1$
    - $\text{days} = \text{end} - \text{start} + 1$
  - Alternatively, with sentinel boundaries $P = [0, D[0], \dots, D[M-1], N+1]$, cancelling $K$ obligations from index $i$ gives length $P[i+K] - P[i-1] - 1$.
- **Complexity**:
  - **Time**: $O(M \log M)$ (dominated by sorting $D$)
  - **Space**: $O(1)$ auxiliary space

---

## 6. Fence / House Painting within Budget
- **File**: [`fence_painting_within_budget.cpp`](file:///d:/Learning/DSA/Practice/Sample/fence_painting_within_budget.cpp)
- **Core Concept**: Dynamic Programming (Paint House II pattern) + Budget thresholding.
- **Key Insight**:
  - The budget $B$ does not need to be stored in the DP state; we simply find the global minimum painting cost and return it if $\text{min\_cost} \le B$, else $-1$.
  - DP state: $dp[i][j]$ = minimum cost to paint houses $0 \dots i$ such that house $i$ has color $j$.
  - DP transition: $dp[i][j] = cost[i][j] + \min_{k \ne j} dp[i-1][k]$.
  - Tracking the top 2 minimums (`min1` and `min2`) from the previous row reduces the transition time from $O(C)$ to $O(1)$, giving overall $O(N \times C)$ time and $O(C)$ space.
  - Edge case: If $C = 1$ and $N > 1$, adjacent houses cannot have different colors $\implies -1$.
- **Complexity**:
  - **Time**: $O(N \times C)$ (Optimized) / $O(N \times C^2)$ (Baseline)
  - **Space**: $O(C)$ (Optimized) / $O(N \times C)$ (Baseline)


