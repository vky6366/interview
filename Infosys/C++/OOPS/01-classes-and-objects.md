# 01 — Classes, Objects & Memory Layout in C++

> **Course Reference:** Lecture 70 — Object Oriented Programming in C++

---

## 1. What is Object-Oriented Programming (OOP)?
Object-Oriented Programming is a programming paradigm based on the concept of **objects**, which contain **data** (attributes / state) and **code** (methods / behavior).

It aims to implement real-world entities like inheritance, data hiding, polymorphism, and encapsulation in programming to make code modular, reusable, and scalable.

---

## 2. Class vs Object

| Feature | Class | Object |
|---|---|---|
| **Definition** | User-defined blueprint / template / prototype. | An instance of a class occupying physical memory. |
| **Memory Allocation** | Does NOT allocate memory when defined. | Allocates memory on the Stack or Heap when instantiated. |
| **Physical Existence** | Logical entity (type definition). | Physical entity residing in memory. |
| **Analogy** | Architectural blueprint of a house. | The physical house built from that blueprint. |

```cpp
#include <iostream>
using namespace std;

// Class Definition (Blueprint - No memory allocated here)
class Hero {
public:
    // Properties / Data Members
    char name[50];
    int health;
    int level;

    // Methods / Member Functions
    void attack() {
        cout << "Hero attacks with full power!" << endl;
    }
};

int main() {
    // Object Instantiation (Memory allocated here)
    Hero h1; // Static allocation on Stack
    h1.health = 100;
    h1.level = 5;
    h1.attack();

    return 0;
}
```

---

## 3. Size of an Empty Class (Crucial Interview Question)

```cpp
class Empty {
    // No data members
};

int main() {
    Empty e;
    cout << "Size of empty class: " << sizeof(e) << " byte" << endl; // Output: 1
}
```

### 💡 Why is the size of an empty class 1 byte (and not 0)?
- In C++, every object must have a **unique memory address** so that pointers can differentiate between two distinct objects.
- If `sizeof(Empty)` were 0 bytes, then in `Empty e1, e2;`, both `&e1` and `&e2` would point to the exact same memory address, making it impossible to identify individual objects.
- To ensure every object has a distinct address, the compiler assigns a **minimum size of 1 byte**.

---

## 4. Memory Layout, Structure Padding & Greedy Alignment

When an object has data members, its size is not always equal to the sum of individual data member sizes due to **Structure Padding / Data Alignment**.

```cpp
#include <iostream>
using namespace std;

class A {
    char c;   // 1 byte
    int i;    // 4 bytes
    char d;   // 1 byte
};

class B {
    int i;    // 4 bytes
    char c;   // 1 byte
    char d;   // 1 byte
};

int main() {
    cout << "Size of class A: " << sizeof(A) << " bytes" << endl; // Output: 12 bytes!
    cout << "Size of class B: " << sizeof(B) << " bytes" << endl; // Output: 8 bytes!
}
```

### 🔍 Why is `sizeof(A) == 12` while `sizeof(B) == 8`?
- **CPU Word Alignment**: CPUs read memory in 4-byte (32-bit) or 8-byte (64-bit) word chunks for maximum memory bus efficiency.
- An `int` (4 bytes) must start at a memory address divisible by 4.

#### Memory Layout of Class A:
```text
[ char c (1B) ][ Pad (3B) ][ int i (4B) ][ char d (1B) ][ Pad (3B) ] = 12 Bytes
```

#### Memory Layout of Class B (Optimized / Greedy Alignment):
```text
[ int i (4B) ][ char c (1B) ][ char d (1B) ][ Pad (2B) ] = 8 Bytes
```

> [!TIP]
> **Greedy Alignment Rule**: Always declare data members in descending order of size (largest to smallest: `double` $\to$ `int` $\to$ `short` $\to$ `char`) to minimize compiler padding and save memory.

---

## 5. Access Specifiers / Modifiers

Access modifiers define the scope and visibility of class members:

| Access Specifier | Within Same Class | Derived Class | Outside Class |
|---|---|---|---|
| `public` | ✅ Yes | ✅ Yes | ✅ Yes |
| `protected` | ✅ Yes | ✅ Yes | ❌ No |
| `private` (Default in C++ class) | ✅ Yes | ❌ No | ❌ No |

> [!NOTE]
> In C++, `struct` members are **public by default**, while `class` members are **private by default**.

---

## 6. Getters and Setters (Encapsulation Practice)

```cpp
#include <iostream>
using namespace std;

class Account {
private:
    double balance; // Hidden / Private data member

public:
    // Getter (Read access)
    double getBalance() const {
        return balance;
    }

    // Setter (Controlled write access with validation)
    void setBalance(double amount) {
        if (amount >= 0) {
            balance = amount;
        } else {
            cout << "Error: Negative balance not allowed!" << endl;
        }
    }
};
```

---

## 7. Static vs Dynamic Allocation of Objects

```cpp
#include <iostream>
using namespace std;

class Hero {
public:
    int health;
    void attack() { cout << "Attacking with health: " << health << endl; }
};

int main() {
    // 1. Static Allocation (Stack Memory)
    Hero h1;
    h1.health = 80;
    h1.attack(); // Dot (.) operator used

    // 2. Dynamic Allocation (Heap Memory)
    Hero* h2 = new Hero();
    
    // Accessing via dereference and dot:
    (*h2).health = 95;
    
    // Accessing via arrow operator (preferred):
    h2->health = 95;
    h2->attack();

    // MUST manually deallocate heap memory to prevent memory leak!
    delete h2;
    h2 = nullptr; // Avoid dangling pointer

    return 0;
}
```

| Dimension | Static Allocation (Stack) | Dynamic Allocation (Heap) |
|---|---|---|
| **Syntax** | `Hero h1;` | `Hero* h2 = new Hero();` |
| **Operator** | Dot operator `h1.member` | Arrow operator `h2->member` |
| **Lifetime** | Automatically destroyed when scope ends. | Persists until explicitly freed using `delete`. |
| **Memory Location** | Fast Stack memory. | Heap memory (dynamic pool). |
| **Risk** | Stack overflow on huge allocations. | Memory leaks if `delete` is omitted. |

---

## 8. Common Interview Questions & Answers

### Q1: What is the difference between `.` (dot) and `->` (arrow) operator?
- **Answer**: The dot operator (`.`) is used to access members directly on an **object instance** (`h1.health`). The arrow operator (`->`) is used when accessing members through a **pointer to an object** (`hPtr->health`), which is syntactic shorthand for `(*hPtr).health`.

### Q2: What happens if you don't use `delete` after `new`?
- **Answer**: The memory allocated on the heap remains occupied even after the pointer goes out of scope, causing a **Memory Leak**. If repeated in long-running processes, it eventually exhausts system RAM.

### Q3: Why does a class default to private access in C++?
- **Answer**: To enforce **Data Hiding** and security by default, preventing accidental direct mutation of internal object state from external code.
