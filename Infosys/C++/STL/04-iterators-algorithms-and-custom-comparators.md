# 04. Iterators, STL Algorithms, and Custom Comparators

---

## 1. Iterators & Iterator Invalidation

### 🎯 2–4 Line Interview-Ready Explanation
> An **Iterator** is an object that acts as a generalized smart pointer, allowing traversal through the elements of an STL container without exposing the underlying container structure. The range $[ \text{begin()}, \text{end()} )$ represents a **half-open interval**, where `end()` points to the memory location **one past the last valid element**.

---

```cpp
#include <vector>
#include <iostream>

std::vector<int> v = {10, 20, 30, 40, 50};

// Forward iteration
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " "; // Dereference iterator
}

// Reverse iteration
for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
    std::cout << *rit << " "; // Prints: 50 40 30 20 10
}
```

### Iterator Invalidation Rules (Critical Trap)

| Container | Insertion Invalidation | Deletion / Erase Invalidation |
| :--- | :--- | :--- |
| **`std::vector`** | **If reallocation occurs:** ALL iterators invalidated. **If no reallocation:** Iterators at/after insertion point invalidated. | Iterators at and after the erased point are invalidated. |
| **`std::deque`** | ALL iterators invalidated (unless inserting at front/back where only pointers invalidated). | Erasing from front/back invalidates only those; middle invalidates all. |
| **`std::list`** | ❌ **No iterators invalidated.** | Only the iterator pointing to the erased element is invalidated. |
| **`std::map` / `std::set`** | ❌ **No iterators invalidated.** | Only the iterator pointing to the erased element is invalidated. |

```cpp
// Correct way to erase elements while iterating:
for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0) {
        it = v.erase(it); // erase() returns the next valid iterator!
    } else {
        ++it;
    }
}
```

---

## 2. Essential STL Algorithms (⭐ Priority Topic)

All STL algorithms reside in `<algorithm>` and `<numeric>`.

### Algorithmic Functions & Complexities

| Algorithm | Syntax & Example | Time Complexity | Notes / Requirements |
| :--- | :--- | :---: | :--- |
| **`std::sort`** | `sort(v.begin(), v.end())` | **$O(N \log N)$** | Uses **IntroSort** (QuickSort + HeapSort + InsertionSort). |
| **`std::reverse`** | `reverse(v.begin(), v.end())` | **$O(N)$** | Reverses elements in-place. |
| **`std::min` / `max`** | `int m = min({a, b, c})` | $O(1)$ | Returns copy of minimum/maximum. |
| **`std::min_element`** | `auto it = min_element(v.begin(), v.end())` | **$O(N)$** | Returns iterator to smallest element (`*it`). |
| **`std::find`** | `auto it = find(v.begin(), v.end(), val)` | **$O(N)$** | Linear search; returns `v.end()` if absent. |
| **`std::count`** | `int c = count(v.begin(), v.end(), val)` | **$O(N)$** | Counts frequency of target value. |
| **`std::accumulate`** | `accumulate(v.begin(), v.end(), 0LL)` | **$O(N)$** | Calculates sum. (In `<numeric>`). Pass `0LL` to avoid 32-bit integer overflow! |
| **`std::binary_search`**| `binary_search(v.begin(), v.end(), val)` | **$O(\log N)$** | Returns `bool` (true/false). **Array MUST be sorted!** |
| **`std::lower_bound`** | `lower_bound(v.begin(), v.end(), val)` | **$O(\log N)$** | Returns iterator to **first element $\ge val$**. |
| **`std::upper_bound`** | `upper_bound(v.begin(), v.end(), val)` | **$O(\log N)$** | Returns iterator to **first element $> val$**. |

---

### `lower_bound` vs `upper_bound` Visual Guide

```
Sorted Array:  [ 10,  20,  20,  20,  30,  40 ]
Index:            0    1    2    3    4    5

lower_bound(..., 20):  Points to Index 1 (First element >= 20)
upper_bound(..., 20):  Points to Index 4 (First element > 20)

Count of target (20) = upper_bound - lower_bound = 4 - 1 = 3 elements!
```

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> arr = {10, 20, 20, 20, 30, 40};

auto lb = std::lower_bound(arr.begin(), arr.end(), 20); // Iterator to arr[1]
auto ub = std::upper_bound(arr.begin(), arr.end(), 20); // Iterator to arr[4]

int firstIdx = lb - arr.begin(); // Index 1
int count20 = ub - lb;           // 3 occurrences
```

---

## 3. Custom Comparators (⭐ Priority Topic)

A **Custom Comparator** defines the ordering criteria for sorting algorithms and ordered associative containers.

> [!IMPORTANT]
> **Strict Weak Ordering Rule:**
> In C++ STL sorting, the comparator `comp(a, b)` must return `true` **if and only if `a` strictly precedes `b`**. If $a = b$, it **MUST return `false`**. Returning `true` or `<=` when $a = b$ causes **Undefined Behavior / Segmentation Fault** in `std::sort`.

---

### Pattern 1: Sorting Pairs (Ascending by First, Descending by Second)

```cpp
#include <algorithm>
#include <vector>
#include <utility>

// Problem: Sort pairs by score (first) ASCENDING; for ties, sort by ID (second) DESCENDING
std::vector<std::pair<int, int>> pairs = {{80, 1}, {90, 2}, {80, 5}, {80, 3}};

// Method A: Lambda Comparator (Fastest & Modern C++ preferred)
std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
    if (a.first != b.first) {
        return a.first < b.first; // Ascending by score
    }
    return a.second > b.second;   // Descending by ID on tie
});

// Result: [{80, 5}, {80, 3}, {80, 1}, {90, 2}]
```

---

### Pattern 2: Sorting Custom Structs / Objects

```cpp
#include <algorithm>
#include <vector>
#include <string>

struct Interval {
    int start;
    int end;
};

// Sort intervals by start time ascending
std::vector<Interval> intervals = {{5, 10}, {1, 3}, {2, 6}};

std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
    return a.start < b.start;
});
```

---

### Pattern 3: Custom Functor for `std::priority_queue`

```cpp
#include <queue>
#include <vector>

struct Node {
    int val;
    int frequency;
};

// Functor for Priority Queue (Min-Heap based on frequency)
struct CompareFreq {
    bool operator()(const Node& a, const Node& b) const {
        return a.frequency > b.frequency; // '>' creates Min-Heap in priority_queue
    }
};

std::priority_queue<Node, std::vector<Node>, CompareFreq> pq;
```

---

## 4. Infosys SP L3 Interview Questions & Answers

### Q1: What underlying sorting algorithm is used by `std::sort()` in C++?
**Answer:**
`std::sort()` uses **IntroSort (Introspective Sort)**, a hybrid algorithm that combines the average-case speed of **QuickSort**, the worst-case $O(N \log N)$ guarantee of **HeapSort**, and the low-overhead small-array speed of **InsertionSort**:
1. Starts with QuickSort.
2. If the recursion depth exceeds $2 \log N$ (detecting quadratic behavior), it switches dynamically to **HeapSort** to guarantee $O(N \log N)$ worst-case time.
3. For small partitions ($N < 16$), it switches to **InsertionSort** for cache efficiency.

---

### Q2: What happens if your custom comparator returns `<= ` instead of `<` in `std::sort()`?
**Answer:**
It violates the **Strict Weak Ordering** requirement. For two identical elements $a$ and $b$, both `comp(a, b)` and `comp(b, a)` would return `true` (claiming $a < b$ and $b < a$ simultaneously). This breaks IntroSort's partitioning logic, causing it to read past array bounds and trigger a **Segmentation Fault** or memory corruption.

---

### Q3: How do `std::lower_bound` on a `std::vector` vs `s.lower_bound()` on a `std::set` differ in complexity?
**Answer:**
- On `std::vector`: `std::lower_bound(v.begin(), v.end(), val)` takes **$O(\log N)$ time** because vectors provide $O(1)$ random-access iterators allowing binary pointer arithmetic.
- On `std::set`: Calling `std::lower_bound(s.begin(), s.end(), val)` takes **$O(N)$ time** because `std::set` iterators are bidirectional (cannot jump). You must call the member function **`s.lower_bound(val)`**, which traverses the internal Red-Black tree directly in **$O(\log N)$ time**.
