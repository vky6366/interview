# C++ Standard Template Library (STL) — Master Interview Repository

> **Target Role:** Infosys Specialist Programmer (SP) L3 Interview  
> **Course Scope:** Complete C++ STL Curriculum (Sequence Containers, Associative & Unordered Containers ⭐, Container Adapters & Heaps ⭐, Iterators & Algorithms ⭐, Custom Comparators ⭐, Modern C++ Features & Complexity Cheat Sheet ⭐).

---

## 🎯 The Core Philosophy: "Container Selection at a Glance"

For the Infosys SP L3 interview, your goal is to immediately identify the optimal STL container and algorithm for any given DSA problem constraint:

```mermaid
mindmap
  root((C++ STL Architecture))
    Sequence Containers
      std::vector: Contiguous, O(1) random access
      std::deque: Double-ended chunk array
      std::list: Doubly linked list
      std::string: SSO character buffer
      std::array: Fixed stack array
      std::pair: 2-tuple utility
    Associative Containers
      std::map: Red-Black Tree, Sorted Keys O(log N)
      std::set: Unique Sorted Elements O(log N)
      std::multiset: Sorted with Duplicates
    Unordered Containers
      std::unordered_map: Hash Table, Avg O(1)
      std::unordered_set: Unique Hash Filter, Avg O(1)
    Container Adapters
      std::stack: LIFO O(1)
      std::queue: FIFO O(1)
      std::priority_queue: Max/Min Heap O(log N)
    Algorithms
      std::sort: IntroSort O(N log N)
      std::lower_bound / upper_bound: Binary Search O(log N)
```

---

## 📚 Master Topic Index & Curriculum Roadmap

| Module | File | Core Concepts Covered |
| :--- | :--- | :--- |
| **01** | [01. Sequence Containers](file:///d:/interview/Infosys/C++/STL/01-sequence-containers-vector-string-array-list-deque.md) | `std::vector` (reserve vs resize, amortized $O(1)$, capacity doubling), `std::string` (substr, find, SSO), `std::array` vs C-array vs vector, `std::pair` & Structured Bindings, `std::list` (doubly linked list), `std::deque` (double-ended chunk array). |
| **02** | [02. Associative & Unordered Containers](file:///d:/interview/Infosys/C++/STL/02-associative-containers-map-set-unordered.md) | `std::map` (Red-Black Tree, $O(\log N)$, `operator[]` insertion trap vs `find()`), `std::unordered_map` (Hash Table buckets, average $O(1)$ vs worst $O(N)$), `std::set` & `std::unordered_set`, `std::multiset` (single element erase vs all elements erase). |
| **03** | [03. Container Adapters (Stack, Queue, Heaps)](file:///d:/interview/Infosys/C++/STL/03-adapters-stack-queue-priority-queue.md) | `std::stack` (LIFO), `std::queue` (FIFO), `std::priority_queue` (Max-Heap vs Min-Heap syntax `std::greater<int>`, Custom Comparator structs, Push/Pop $O(\log N)$, Top $O(1)$), Exception safety in `pop()`. |
| **04** | [04. Iterators, Algorithms & Comparators](file:///d:/interview/Infosys/C++/STL/04-iterators-algorithms-and-custom-comparators.md) | Half-open intervals $[ \text{begin}, \text{end} )$, Iterator invalidation rules, Essential algorithms (`sort`, `reverse`, `min_element`, `accumulate`), `lower_bound` vs `upper_bound`, Custom Comparators (Lambda, Strict Weak Ordering rule). |
| **05** | [05. Modern C++ & Complexity Cheat Sheet](file:///d:/interview/Infosys/C++/STL/05-modern-cpp-and-stl-complexity-cheatsheet.md) | Modern C++ features (`const auto&`, Structured Bindings `auto [k, v]`, `emplace_back` vs `push_back`), Master Complexity Reference Table, DSA Container Decision Flowchart. |

---

## ⚡ Top 10 High-Yield C++ STL Interview Q&A (Quick Revision)

### 1. What is the difference between `push_back()` and `emplace_back()`?
`push_back()` creates an object (or temporary object) and then copies or moves it into the container. `emplace_back()` forwards constructor arguments directly and constructs the object **in-place** in the vector's allocated memory, eliminating temporary copies.

### 2. What is the difference between `std::map` and `std::unordered_map`?
- `std::map` is implemented as a **Red-Black Tree** (Self-Balancing BST), maintains keys in strictly sorted order, and guarantees **$O(\log N)$** search/insert/delete time.
- `std::unordered_map` is implemented as a **Hash Table**, maintains no key order, and achieves **average $O(1)$** operations (worst-case $O(N)$ on hash collisions).

### 3. How do you declare a Min-Heap in C++?
```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
```

### 4. What is the difference between `std::lower_bound` and `std::upper_bound`?
On a sorted array:
- `lower_bound(begin, end, val)` returns an iterator to the **first element $\ge val$**.
- `upper_bound(begin, end, val)` returns an iterator to the **first element $> val$**.

### 5. Why does `std::map::operator[]` have side effects?
If the queried key does not exist in the map, `map[key]` **automatically inserts a new entry** with that key and a default-constructed value (e.g., 0) and returns a reference to it. To inspect without insertion, always use `map.find(key)`.

### 6. What is the Strict Weak Ordering requirement in custom comparators?
A comparator function `comp(a, b)` must return `true` if and only if $a$ strictly precedes $b$. If $a$ and $b$ are equal, it **must return `false`**. Returning `<=` or `true` on equality violates strict weak ordering and causes undefined behavior / segmentation faults in `std::sort`.

### 7. What is the difference between `v.reserve()` and `v.resize()`?
- `reserve(N)` allocates memory capacity for $N$ elements without modifying `size()` or constructing elements.
- `resize(N)` modifies the actual `size()` of the vector, default-constructing new elements if growing, or destroying excess elements if shrinking.

### 8. How does `std::sort()` achieve $O(N \log N)$ worst-case time?
`std::sort()` uses **IntroSort** (Introspective Sort). It starts with QuickSort for speed, but monitors recursion depth; if recursion depth exceeds $2 \log N$, it switches to **HeapSort** to guarantee an $O(N \log N)$ worst-case time bound.

### 9. What is the time complexity of `lower_bound` on `std::set` vs `std::vector`?
On `std::vector`, `std::lower_bound` is **$O(\log N)$** due to random-access pointer math. On `std::set`, using the global algorithm `std::lower_bound(s.begin(), s.end(), val)` takes **$O(N)$**; you must use the member function **`s.lower_bound(val)`** to achieve **$O(\log N)$** tree traversal.

### 10. Why should you iterate using `const auto& x` instead of `auto x`?
`auto x` makes a full value copy of each container element on every loop iteration, causing expensive heap copies for strings and vectors. `const auto& x` creates a zero-cost immutable reference.
