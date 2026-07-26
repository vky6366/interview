# Python Interview Guide (Comprehensive) ⭐⭐⭐⭐⭐

Python is the core language for many software engineering, AI, and Data Science roles. This guide covers the most frequently asked questions and fundamental concepts for Python interviews.

---

## 1. Data Structures

### Lists, Tuples, Sets, and Dictionaries
*   **Lists:** Ordered, mutable (changeable), allows duplicate elements. E.g., `my_list = [1, 2, 2, 3]`
*   **Tuples:** Ordered, **immutable** (unchangeable), allows duplicate elements. E.g., `my_tuple = (1, 2, 2, 3)`
*   **Sets:** Unordered, mutable, **no duplicate elements**. Fast membership testing. E.g., `my_set = {1, 2, 3}`
*   **Dictionaries:** Unordered (ordered in Python 3.7+), mutable, stores **key-value pairs**. Keys must be unique and immutable. E.g., `my_dict = {"name": "Alice", "age": 25}`

### Key Comparisons
**Difference between List and Tuple?**
*   Lists are mutable (can be changed after creation), tuples are immutable.
*   Tuples are slightly faster and consume less memory.
*   *When to use:* Use lists for data that might change. Use tuples for data that should not change (e.g., coordinates, configuration settings) or as dictionary keys.

**Difference between Set and Dictionary?**
*   Both are backed by hash tables, providing very fast O(1) lookups.
*   Sets only store keys (unique values). Dictionaries store key-value pairs.

---

## 2. Variables and Mutability

### Mutable vs Immutable Types
*   **Mutable:** State can be changed after creation (Lists, Dictionaries, Sets).
*   **Immutable:** State cannot be changed after creation (Integers, Floats, Strings, Tuples, Frozensets).
*   *Gotcha:* If you pass a mutable object to a function and modify it, the original object is also modified (passed by object reference).

### Shallow Copy vs Deep Copy
*   **Shallow Copy (`copy.copy()`):** Creates a new object, but inserts references into it to the objects found in the original. (Nested objects are still shared).
*   **Deep Copy (`copy.deepcopy()`):** Creates a new object and recursively inserts copies of the objects found in the original. (Fully independent clone).

### `is` vs `==`
*   `==` checks for **value equality** (do they have the same data?).
*   `is` checks for **identity** (do they point to the same object in memory?).

---

## 3. Loops and Iteration

*   **`for` loop:** Iterates over a sequence or other iterable objects.
*   **`while` loop:** Executes a block repeatedly as long as a condition is true.
*   **`break` / `continue`:** `break` exits the loop entirely. `continue` skips to the next iteration.
*   **`enumerate(iterable)`:** Adds a counter and returns it as an enumerate object. `for idx, val in enumerate(my_list):`
*   **`zip(*iterables)`:** Aggregates elements from multiple iterables into tuples.

---

## 4. Functions and Lambda

*   **`*args` & `**kwargs`:**
    *   `*args`: Passes a variable number of non-keyword arguments (as a tuple).
    *   `**kwargs`: Passes a variable number of keyword arguments (as a dictionary).
*   **`lambda`:** Small anonymous functions. Syntax: `lambda arguments: expression`. E.g., `add = lambda x, y: x + y`

---

## 5. Comprehensions and Generators

### List, Set, and Dict Comprehensions
*   Concise, fast ways to create collections.
*   *List:* `[x*2 for x in range(10) if x % 2 == 0]`
*   *Dict:* `{x: x*2 for x in range(5)}`

### Generators and `yield`
*   **Generators** are a simple way of creating iterators. Instead of returning an entire list (which takes up memory), they generate values one at a time using `yield`.
*   *Why use them?* Highly memory efficient for large datasets (Lazy evaluation).
```python
def my_generator():
    for i in range(1000000):
        yield i  # Pauses execution and returns 'i'
```

---

## 6. Decorators
*   A decorator is a function that takes another function and extends its behavior without explicitly modifying it.
*   Used for logging, authentication, timing functions, etc.
```python
def my_decorator(func):
    def wrapper():
        print("Something before the function is called.")
        func()
        print("Something after the function is called.")
    return wrapper

@my_decorator
def say_hello():
    print("Hello!")
```

---

## 7. Object-Oriented Programming (OOP)
*   **Class/Object:** Blueprint vs Instance.
*   **Constructor (`__init__`):** Initializes object attributes.
*   **Inheritance:** Child class inherits from parent class (`class Child(Parent):`).
*   **Encapsulation:** Hiding internal state. Python uses `_private` (convention) and `__very_private` (name mangling).
*   **Polymorphism:** Different objects responding to the same method in their own ways.
*   **Dunder (Magic) Methods:** Special methods starting and ending with double underscores.
    *   `__str__`: User-friendly string representation.
    *   `__repr__`: Developer-friendly string representation (ideally valid Python code).
    *   `__eq__`: Custom logic for `==`.

---

## 8. Memory Management and The GIL

### Reference Counting & Garbage Collection
*   Python tracks how many references point to an object. When the reference count drops to zero, the memory is deallocated.
*   Python also has a cyclic garbage collector to detect and clean up circular references (e.g., Object A points to Object B, and Object B points to Object A).

### The Global Interpreter Lock (GIL)
*   **What is it?** A mutex that protects access to Python objects, preventing multiple native threads from executing Python bytecodes at once in CPython.
*   **Impact:** True multithreading is not possible for CPU-bound tasks in standard Python.
*   **Solution:** Use the `multiprocessing` module (which spawns separate processes with their own memory space and GIL) for CPU-bound tasks. Threads are still useful for I/O-bound tasks (network requests, file reading).

---

## 9. Exception and Context Handling

### Exception Handling
```python
try:
    result = 10 / 0
except ZeroDivisionError as e:
    print("Cannot divide by zero!")
finally:
    print("Executes no matter what (cleanup).")
```

### Context Managers (`with` statement)
*   Used to properly manage resources (like files, network connections) ensuring they are cleaned up/closed after use, even if an error occurs.
*   Behind the scenes, relies on `__enter__` and `__exit__` dunder methods.

---

## 10. Type Hinting (Python 3.5+)
*   Python is dynamically typed, but type hints improve IDE support and code readability.
```python
from typing import List, Dict, Optional

def process_data(name: str, scores: List[int]) -> Optional[float]:
    if not scores:
        return None
    return sum(scores) / len(scores)
```

---

## 11. Essential Data Science & AI Libraries (Briefly)
*   **NumPy:** Fast, dense C-based arrays for numerical computing. Supports vectorized operations.
*   **Pandas:** DataFrames for data manipulation and analysis.
*   **scikit-learn:** Traditional Machine Learning algorithms and tools.
