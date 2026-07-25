# Python Interview Guide (50% Focus) ⭐⭐⭐⭐⭐

Python is the core language for AI and Data Science. This guide covers the most frequently asked questions and fundamental concepts.

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
*   *When to use:* Use lists for data that might change (e.g., a list of active users). Use tuples for data that should not change (e.g., coordinates, configuration settings) or as dictionary keys.

**Difference between Set and Dictionary?**
*   Both are backed by hash tables, providing very fast O(1) lookups.
*   Sets only store keys (unique values). Dictionaries store key-value pairs.
*   *When to use:* Use a set when you only need to know *if* an item exists or to remove duplicates from a list. Use a dict when you need to map a unique key to a specific value.

---

## 2. Loops and Iteration

*   **`for` loop:** Iterates over a sequence (list, tuple, string) or other iterable objects.
*   **`while` loop:** Executes a block of statements repeatedly as long as a condition is true.
*   **`break`:** Terminates the current loop completely and jumps to the next statement outside the loop.
*   **`continue`:** Skips the rest of the current iteration and moves to the next iteration of the loop.
*   **`enumerate(iterable)`:** Adds a counter to an iterable and returns it as an enumerate object. Very useful when you need both the index and the value.
    *   *Example:* `for idx, val in enumerate(["a", "b"]): print(idx, val)`
*   **`zip(*iterables)`:** Aggregates elements from two or more iterables (lists, tuples) into tuples.
    *   *Example:* `for name, age in zip(["Alice", "Bob"], [25, 30]): ...`

---

## 3. Functions

*   **`def`:** Keyword used to declare a function.
*   **`return`:** Keyword used to exit a function and return a value to the caller.
*   **`*args`:** Allows a function to accept any number of positional arguments. It packs them into a tuple.
*   **`**kwargs`:** Allows a function to accept any number of keyword (named) arguments. It packs them into a dictionary.
*   **`lambda`:** Small, anonymous functions defined in a single line. Often used as arguments for higher-order functions like `map()` or `filter()`.
    *   *Example:* `add = lambda x, y: x + y`

---

## 4. List Comprehensions

A concise and pythonic way to create lists. They are generally faster than standard `for` loops.
*   *Basic:* `[x*x for x in nums]` -> Creates a new list with the square of each number in `nums`.
*   *With Condition:* `[x for x in nums if x % 2 == 0]` -> Creates a new list containing only the even numbers from `nums`.

---

## 5. Object-Oriented Programming (OOP)

*   **Class:** A blueprint for creating objects. Defines attributes (data) and methods (functions).
*   **Object:** An instance of a class.
*   **Constructor (`__init__`):** A special method called automatically when a new object is created. Used to initialize object attributes.
*   **Inheritance:** A mechanism where a new class (child) inherits attributes and methods from an existing class (parent). Promotes code reusability.
*   **Encapsulation:** Bundling data and the methods that operate on that data into a single unit (class). Also involves restricting direct access to some of the object's components (using private variables, e.g., `_my_var`).
*   **Polymorphism:** The ability of different objects to respond to the same method call in their own way. E.g., a `draw()` method will behave differently for a `Circle` object versus a `Square` object.

---

## 6. Exception Handling

Used to gracefully handle runtime errors so the program doesn't crash.
```python
try:
    # Code that might cause an exception (e.g., dividing by zero, opening a missing file)
    result = 10 / 0
except ZeroDivisionError:
    # Code that runs if the specific exception occurs
    print("Cannot divide by zero!")
except Exception as e:
    # Catch-all for other exceptions
    print(f"An error occurred: {e}")
finally:
    # Code that ALWAYS runs, regardless of whether an exception occurred or not.
    # Often used for cleanup (closing files, releasing database connections).
    print("Execution complete.")
```

---

## 7. File Handling

*   **`open()`:** Opens a file and returns a file object. You must remember to call `.close()` when done to free up resources.
*   **`with open(...) as file:` (Context Manager):** The highly recommended way to handle files. It automatically handles closing the file for you, even if an exception occurs inside the block.
    *   *Example:* `with open('data.txt', 'r') as f: content = f.read()`

---

## 8. Standard Library Modules

*   **`os`:** Provides functions for interacting with the operating system (e.g., reading environment variables, manipulating file paths, creating directories).
*   **`math`:** Provides mathematical functions (e.g., `math.sqrt`, `math.sin`, `math.pi`).
*   **`random`:** Implements pseudo-random number generators for various distributions (e.g., `random.randint`, `random.choice`).
*   **`datetime`:** Classes for manipulating dates and times.

---

## 9. Essential Data Science & AI Libraries

### NumPy (Numerical Python)
The foundational package for numerical computing.
*   **Difference between NumPy array and Python list?**
    *   *Memory:* NumPy arrays store elements of the *same data type* sequentially in memory, making them incredibly dense and fast. Python lists store pointers to objects scattered in memory, which allows mixed data types but is much slower.
    *   *Operations:* NumPy supports vectorized operations. You can multiply an entire array by a number without writing a `for` loop.

### Pandas
Built on top of NumPy, it provides high-level data structures (DataFrames and Series).
*   *Purpose:* The ultimate tool for data manipulation, cleaning, and analysis (handling missing data, grouping, merging datasets).

### scikit-learn
The gold standard library for traditional Machine Learning.
*   *Purpose:* Provides clean, consistent APIs for classification, regression, clustering (e.g., Random Forests, SVMs, K-Means), as well as tools for model evaluation, data preprocessing, and cross-validation.
