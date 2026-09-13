# C++ Object-Oriented Programming (OOP) — Interview Mastery Handbook

> **Target Role:** Infosys Specialist Programmer (SP) L3 Interview  
> **Course Scope:** Lectures 70 through 77 (Complete OOP & C++ Core Fundamentals)

---

## 📚 Master Index & Study Guide

| # | Topic File | Core Focus & Key Interview Concepts | Status / Video Reference |
|---|---|---|---|
| 01 | **[01. Classes & Objects](01-classes-and-objects.md)** | Class vs Object, Memory Layout, Structure Padding, Greedy Alignment, Size of Empty Class (1 Byte), Access Specifiers, Static vs Dynamic allocation (`.` vs `->`). | 🎥 Lecture 70 |
| 02 | **[02. Constructors & Destructors](02-constructors-and-destructors.md)** | Default, Parameterized, Copy Constructor (`const ClassName&`), `this` pointer, **Shallow vs Deep Copy**, Copy Assignment Operator, Initializer Lists, Destructor LIFO execution order. | 🎥 Lecture 71 |
| 03 | **[03. Static Members & Encapsulation](03-static-members-and-encapsulation.md)** | Static Data Members (`::`), Static Member Functions (No `this`), `const` Member Functions, `mutable` keyword, `friend` Functions/Classes, **Encapsulation vs Abstraction**. | 🎥 Lecture 72 |
| 04 | **[04. Inheritance & Access Specifiers](04-inheritance-and-access-specifiers.md)** | Base vs Derived, The Master 3x3 Inheritance Mode Matrix (`public`, `protected`, `private`), Order of Constructor/Destructor execution in derived classes, Passing args to base constructor. | 🎥 Lecture 73 |
| 05 | **[05. Types of Inheritance & Diamond Problem](05-types-of-inheritance-and-diamond-problem.md)** | Single, Multilevel, Multiple, Hierarchical, Hybrid, Multiple Inheritance Scope Ambiguity (`::`), **The Diamond Problem**, **Virtual Base Class / Virtual Inheritance (`virtual public`)**, `vbptr`/`vbtable`. | 🎥 Lecture 74 |
| 06 | **[06. Polymorphism & Virtual Functions](06-polymorphism-and-virtual-functions.md)** | Compile-Time (Overloading) vs Runtime (Overriding), Operator Overloading, **`virtual` Functions**, Pure Virtual Functions (`= 0`), Abstract Classes, **`vptr` & `vtable` internal mechanism**, **Virtual Destructors**. | 🎥 Lecture 75 |
| 07 | **[07. Exception Handling](07-exception-handling.md)** | `try`, `catch`, `throw`, Multiple catches, Catch-All (`catch(...)`), `<stdexcept>` hierarchy, Custom Exception Classes (`what()`), **Stack Unwinding & RAII**, Rethrowing (`throw;`), `noexcept`. | 🎥 Lecture 76 |
| 08 | **[08. File Handling & Streams](08-file-handling.md)** | `ifstream`, `ofstream`, `fstream`, File Opening Modes (`ios::in`, `ios::out`, `ios::app`, `ios::binary`), Line-by-line reading, File Pointers (`seekg`, `seekp`, `tellg`, `tellp`), Binary Object I/O (`read`/`write`). | 🎥 Lecture 77 |

---

## ⚡ Top 10 Must-Know C++ OOP Interview Questions

1. **Why is the size of an empty class 1 byte in C++?**
   - *Answer*: To guarantee that every object instance receives a unique memory address so that pointers can differentiate between distinct instances.
2. **Why must a Copy Constructor take its parameter by reference (`const ClassName&`)?**
   - *Answer*: Passing by value would recursively trigger the copy constructor itself, causing an infinite recursive loop and stack overflow.
3. **What is the difference between Shallow Copy and Deep Copy?**
   - *Answer*: Shallow copy copies only pointer addresses (causing shared state and Double Free crashes); Deep copy allocates fresh heap memory and copies the actual underlying data.
4. **Why are static member functions unable to access `this` or non-static members?**
   - *Answer*: Static functions are invoked at the class level (`Class::func()`) without an object instance context; therefore, no `this` pointer exists.
5. **How does Virtual Inheritance resolve the Diamond Problem?**
   - *Answer*: Using `virtual public Base` ensures the most-derived class receives only **one single shared instance** of the virtual base class via internal virtual base table pointers (`vbptr`), eliminating duplicate copies and ambiguity.
6. **How do Virtual Functions work internally?**
   - *Answer*: The compiler builds a static **`vtable`** of virtual function pointers per class and injects a hidden **`_vptr`** pointer (8 bytes) into each object instance pointing to its class's `vtable` for late runtime dispatch.
7. **Why must a Base class destructor always be `virtual`?**
   - *Answer*: If a derived object is deleted through a base class pointer (`Base* ptr = new Derived(); delete ptr;`), a non-virtual base destructor will only call `~Base()`, skipping `~Derived()` and causing severe memory leaks.
8. **What is Stack Unwinding during an exception?**
   - *Answer*: It is the automatic process of cleaning the call stack by executing destructors for all active local stack objects between the `try` block and the `throw` statement.
9. **What are the operators in C++ that CANNOT be overloaded?**
   - *Answer*: `.` (Dot), `.*` (Pointer-to-member), `::` (Scope resolution), `?:` (Ternary), `sizeof`, and `typeid`.
10. **What is the difference between Encapsulation and Abstraction?**
    - *Answer*: Encapsulation is **data hiding and binding** within a class capsule via access modifiers; Abstraction is **implementation hiding** showing only essential interfaces via abstract classes.
