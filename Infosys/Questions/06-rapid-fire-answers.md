# Rapid-Fire Round — 30 High-Yield Answers (R1 – R30)

> **Format:** Crisp, 20–45 second punchy answers optimized for rapid-fire technical interview rounds.

---

## Computer Networks (R1 – R6)

### R1. What is the default port of HTTP?
**Answer:**
**Port 80** (TCP).

---

### R2. What is the default port of HTTPS?
**Answer:**
**Port 443** (TCP).

---

### R3. What protocol translates domain names into IP addresses?
**Answer:**
**DNS (Domain Name System)**, running over UDP/TCP port 53.

---

### R4. What is the difference between TCP and UDP in one sentence?
**Answer:**
**TCP** is a connection-oriented, reliable protocol that guarantees in-order data delivery with flow and congestion control, while **UDP** is a connectionless, lightweight, best-effort protocol that prioritizes speed and low latency over reliability.

---

### R5. What does ARP map?
**Answer:**
**Address Resolution Protocol (ARP)** maps a Layer 3 **Logical IP Address** to a Layer 2 **Physical MAC Address** on a local subnet.

---

### R6. Why is TCP called connection-oriented?
**Answer:**
Because before any application payload data can be exchanged, a formal logical full-duplex connection must be established between sender and receiver via the **TCP 3-Way Handshake (`SYN` $\to$ `SYN-ACK` $\to$ `ACK`)**.

---

## Operating Systems (R7 – R12)

### R7. Process vs thread?
**Answer:**
A **process** is an independent execution unit with its own private virtual address space, while a **thread** is a lightweight unit of execution within a process that shares memory and heap space with sibling threads.

---

### R8. What is a context switch?
**Answer:**
The kernel procedure of saving the CPU register state and program counter of the currently running process/thread to its PCB/TCB and loading the saved state of another process/thread to resume its execution.

---

### R9. What is a race condition?
**Answer:**
A concurrency flaw where two or more threads access shared mutable state simultaneously, causing the final program output to depend unpredictably on the non-deterministic order of thread execution.

---

### R10. Mutex vs semaphore?
**Answer:**
A **Mutex** is a locking mechanism with **strict thread ownership** (only the locking thread can unlock it), whereas a **Semaphore** is a **signaling mechanism** with an integer counter (any thread can signal it) used for resource pooling.

---

### R11. Name the four conditions required for deadlock.
**Answer:**
1. **Mutual Exclusion**
2. **Hold and Wait**
3. **No Preemption**
4. **Circular Wait**

---

### R12. What is a page fault?
**Answer:**
A hardware interrupt/trap triggered by the MMU when a program attempts to access a virtual memory page that is not currently mapped into physical RAM (Valid bit = 0), requiring the OS to load it from disk swap space.

---

## DBMS & SQL (R13 – R22)

### R13. What is a primary key?
**Answer:**
A column (or set of columns) that uniquely identifies each row in a database table; it strictly forbids duplicate values and cannot contain `NULL`.

---

### R14. Primary key vs unique key?
**Answer:**
A table can have **only one Primary Key** (which strictly forbids `NULL`), but can have **multiple Unique Keys** (which allow `NULL` values in standard SQL).

---

### R15. What does ACID stand for?
**Answer:**
- **A** — Atomicity ("All or nothing")
- **C** — Consistency (Preserves database rules and constraints)
- **I** — Isolation (Concurrent transactions do not interfere)
- **D** — Durability (Committed updates persist permanently across crashes)

---

### R16. WHERE vs HAVING?
**Answer:**
`WHERE` filters individual rows **before** aggregation takes place and cannot use aggregate functions, whereas `HAVING` filters aggregated groups **after** `GROUP BY` and can filter on aggregate functions.

---

### R17. INNER JOIN vs LEFT JOIN?
**Answer:**
`INNER JOIN` returns only records that have **matching values in both tables**, while `LEFT JOIN` returns **all records from the left table** along with matching right records (or `NULL` if no match exists).

---

### R18. Why are indexes useful?
**Answer:**
Indexes organize data in a B+ Tree structure, reducing disk search time from an $O(N)$ full table scan to an **$O(\log N)$ fast index seek**.

---

### R19. Why can too many indexes be harmful?
**Answer:**
They consume significant disk storage and **severely degrade write performance** because every `INSERT`, `UPDATE`, and `DELETE` must rebalance and write to every single index tree on the table.

---

### R20. What is normalization?
**Answer:**
The database design process of organizing tables and decomposing data to **minimize data redundancy** and eliminate **insertion, deletion, and update anomalies**.

---

### R21. What is a foreign key?
**Answer:**
A column in a child table that references the Primary Key of a parent table, enforcing **Referential Integrity** between tables.

---

### R22. What is a window function?
**Answer:**
A function that performs calculations across a set of table rows related to the current row **without collapsing rows into a single output row** (e.g., `ROW_NUMBER()`, `RANK()`, running totals).

---

## C++ Programming (R23 – R27)

### R23. Pointer vs reference?
**Answer:**
A **pointer** is a variable that stores a memory address and can be null or reseated, while a **reference** is a permanent, non-null **alias** for an existing variable that cannot be reseated.

---

### R24. What is the purpose of a destructor?
**Answer:**
To automatically release dynamic heap memory, close file descriptors, and unlock mutexes when an object goes out of scope, preventing resource leaks.

---

### R25. What is a copy constructor?
**Answer:**
A constructor that creates a new object by copying data members from an existing object of the same class (`ClassName(const ClassName& other)`).

---

### R26. What is RAII?
**Answer:**
**Resource Acquisition Is Initialization**: A C++ idiom where resource allocation is tied to object construction, and deallocation is guaranteed in the destructor upon scope exit.

---

### R27. `map` vs `unordered_map`?
**Answer:**
`std::map` is a **Red-Black Tree** maintaining **sorted keys in $O(\log N)$**, while `std::unordered_map` is a **Hash Table** with **unordered keys and average $O(1)$** lookup.

---

## Object-Oriented Programming (R28 – R30)

### R28. What are the four pillars of OOP?
**Answer:**
1. **Encapsulation** (Data Hiding)
2. **Abstraction** (Hiding Complexity)
3. **Inheritance** (Code Reusability)
4. **Polymorphism** (Many Forms / Dynamic Behavior)

---

### R29. Overloading vs overriding?
**Answer:**
**Overloading** is compile-time polymorphism with the **same function name but different parameter signatures in the same class**, while **Overriding** is runtime polymorphism where a **derived class redefines a base class virtual function with the exact same signature**.

---

### R30. What is a virtual function?
**Answer:**
A member function in a base class declared with `virtual` that allows derived classes to override it, enabling **dynamic late binding at runtime via a vtable**.
