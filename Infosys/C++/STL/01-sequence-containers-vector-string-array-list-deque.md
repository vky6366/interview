# 01. Sequence Containers: Vector, String, Array, Pair, List, and Deque

---

## 1. `std::vector` (Dynamic Contiguous Array)

### 🎯 2–4 Line Interview-Ready Explanation
> `std::vector` is a dynamic contiguous sequence container that automatically manages its storage, resizing itself when elements are added. It provides **$O(1)$ random access** and **amortized $O(1)$ insertions/deletions at the end**, backed by contiguous memory that maximizes CPU cache spatial locality.

---

### Core Operations, Methods & Complexity

```cpp
#include <vector>
#include <iostream>

// 1. Initializations
std::vector<int> v1;                     // Empty vector
std::vector<int> v2(5, 10);              // Size 5, all initialized to 10
std::vector<int> v3 = {1, 2, 3, 4, 5};   // Initializer list
std::vector<int> v4(v3.begin(), v3.end()); // Range copy

// 2. Modifiers
v1.push_back(10);          // Appends copy/move: O(1) amortized
v1.emplace_back(20);       // Constructs in-place (avoids temp copy): O(1) amortized
v1.pop_back();             // Removes last element: O(1)
v1.clear();                // Removes all elements (size = 0, capacity unchanged): O(N)

// 3. Capacity & Size
size_t s = v2.size();      // Number of current active elements: O(1)
size_t c = v2.capacity();  // Allocated memory buffer slots: O(1)
bool empty = v2.empty();   // true if size == 0: O(1)
v2.reserve(100);           // Pre-allocates memory capacity without changing size (avoids reallocations)

// 4. Element Access
int a = v3[0];             // Direct unchecked indexing: O(1) (Fast, no bounds check)
int b = v3.at(2);          // Checked indexing: O(1) (Throws std::out_of_range exception)
int first = v3.front();    // Reference to first element v3[0]: O(1)
int last = v3.back();      // Reference to last element v3[size-1]: O(1)
```

### Vector Growth Factor & Amortized $O(1)$
* When `size == capacity` and an element is pushed, the vector allocates a new memory block **$2\times$ (GCC/Clang)** or **$1.5\times$ (MSVC)** larger, moves all existing elements to the new block, and deletes the old block.
* Because resizing doubles capacity, copying $N$ elements across $N$ insertions costs $\sum \frac{N}{2^k} \approx 2N$ total operations $\implies \frac{2N}{N} = \mathbf{O(1) \text{ amortized cost}}$ per insertion.

> [!WARNING]
> **Iterator Invalidation Trap:** Adding elements that trigger a reallocation **invalidates all existing pointers, references, and iterators** pointing into that vector.

---

## 2. `std::string` (Character Sequence)

### 🎯 2–4 Line Interview-Ready Explanation
> `std::string` is a contiguous character container similar to `std::vector<char>`, with specialized member functions for string manipulation, substring slicing, searching, and concatenation. In modern C++, strings implement **Small String Optimization (SSO)** to avoid heap allocation for short strings ($\le 15$ characters).

---

```cpp
#include <string>
#include <algorithm>

std::string s = "Infosys Specialist Programmer";

// Substring: substr(start_index, length) -> O(length)
std::string sub = s.substr(8, 10); // "Specialist"

// Finding: find(pattern) -> Returns index or std::string::npos
size_t pos = s.find("Programmer");
if (pos != std::string::npos) {
    // Found at index pos
}

// Modifiers
s.push_back('!');          // Appends character: O(1)
s.pop_back();              // Removes last character: O(1)
s.insert(0, "Target: ");   // Inserts at index: O(N)
s.erase(0, 8);             // Erases range [start, start + count]: O(N)
std::reverse(s.begin(), s.end()); // In-place reverse: O(N)
```

---

## 3. `std::array` vs. C-Style Array vs. `std::vector`

```mermaid
graph LR
    subgraph Storage_Mechanisms
        A[C-Style Array: int arr[10]] --- B[std::array<int, 10>]
        B --- C[std::vector<int>]
    end
```

| Feature | C-Style Array (`int arr[10]`) | `std::array<int, 10>` | `std::vector<int>` |
| :--- | :--- | :--- | :--- |
| **Size Bound** | Fixed at compile time. | Fixed at compile time. | **Dynamic at runtime**. |
| **Memory Location** | Stack (if local). | **Stack** (zero heap overhead). | **Heap** (via pointer on stack). |
| **Decay to Pointer** | Automatically decays to `int*`, losing size info. | **Does NOT decay**; retains object semantics. | Does not decay. |
| **STL Compatibility** | Primitive (no `.size()`, `.begin()`, `.end()`). | **Full STL support** (`.size()`, iterators, `.at()`). | Full STL support. |
| **Copyable / Assignable** | ❌ Cannot be assigned (`arr1 = arr2;` fails). | ✅ **Assignable and copyable by value**. | ✅ Assignable and copyable by value. |

---

## 4. `std::pair` & Structured Bindings

```cpp
#include <utility>
#include <string>

// 1. Creation
std::pair<int, std::string> p1 = {101, "Alice"};
auto p2 = std::make_pair(202, "Bob");

// 2. Access
int id = p1.first;
std::string name = p1.second;

// 3. Nested Pairs
std::pair<int, std::pair<int, int>> point3D = {1, {2, 3}};
int z = point3D.second.second;

// 4. Modern C++17 Structured Binding (Cleaner DSA code!)
auto [emp_id, emp_name] = p1; // Directly binds emp_id = 101, emp_name = "Alice"
```

---

## 5. `std::list` (Doubly Linked List) vs. `std::vector`

### 🎯 When to Use `std::list` in DSA?
> `std::list` is a **Doubly Linked List**. It provides **$O(1)$ insertions and deletions anywhere in the list once an iterator is known**, and iterators are never invalidated by insertions/deletions. However, it does **not support random access ($O(N)$ traversal)** and suffers poor cache locality due to scattered node heap allocations.

```cpp
#include <list>

std::list<int> l = {10, 20, 30};
l.push_front(5);   // O(1)
l.push_back(40);   // O(1)
l.pop_front();     // O(1)
l.pop_back();      // O(1)

// Insertion at iterator: O(1)
auto it = l.begin();
std::advance(it, 2); // O(N) traversal
l.insert(it, 25);    // O(1) pointer update
```

---

## 6. `std::deque` (Double-Ended Queue)

### 🎯 2–4 Line Interview-Ready Explanation
> `std::deque` (Double-Ended Queue) is an indexed sequence container that allows **fast $O(1)$ insertions and deletions at BOTH its beginning and end**. Unlike `std::vector`, elements are not stored in a single contiguous block, but in a dynamic array of fixed-size chunks (paged memory blocks).

```cpp
#include <deque>

std::deque<int> dq;
dq.push_back(10);   // O(1)
dq.push_front(5);   // O(1)
dq.pop_back();      // O(1)
dq.pop_front();     // O(1)
int val = dq[0];    // O(1) Random access
```

* **When to use in DSA:** **Sliding Window Maximum** (monotonic deque), Breadth-First Search (BFS) queues where popping from the front and pushing to the back is frequent.

---

## 7. Infosys SP L3 Interview Questions & Answers

### Q1: What is the difference between `v.reserve()` and `v.resize()` in `std::vector`?
**Answer:**
- **`reserve(n)`:** Allocates memory capacity for at least $n$ elements **without constructing any objects**. The `size()` remains unchanged, and accessing elements via `v[i]` before inserting is undefined behavior. Used to prevent expensive reallocations when the expected count is known.
- **`resize(n)`:** Changes the actual `size()` to $n$. If $n > \text{current size}$, it default-constructs new elements to fill the gap. If $n < \text{current size}$, it destroys excess elements from the back.

---

### Q2: Why is `std::vector` usually faster than `std::list` even for insertions in the middle?
**Answer:**
Due to **CPU Cache Locality**. A vector stores elements in contiguous physical memory, allowing the CPU hardware prefetcher to load whole cache lines ($64$ bytes) into L1/L2 cache. A linked list (`std::list`) allocates individual nodes scattered across the heap, causing **CPU cache misses** on every pointer hop during traversal to the insertion point, which often dwarfs the cost of the vector's contiguous memory shift.

---

### Q3: What is the difference between `push_back()` and `emplace_back()`?
**Answer:**
- **`push_back()`** takes an existing object (or constructs a temporary object), and copies or moves it into the vector's storage.
- **`emplace_back()`** takes constructor arguments directly and constructs the object **in-place** directly within the vector's allocated memory buffer, avoiding the creation and destruction of intermediate temporary objects.
