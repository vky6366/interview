# Infosys Specialist Programmer (SP) L3 — Technical Interview Question Bank & Complete Solutions

> **Master Repository:** 112 Core Technical Interview Questions + 30 Rapid-Fire Questions + 20 Cross-Question Drill Chains.  
> **Target Role:** Infosys Specialist Programmer (SP) L3  
> **Format:** Subject-specific modular files with full technical answers, code/SQL snippets, diagrams, and multi-level drill-down explanations.

---

## 📚 Master Subject Navigation & Answer Modules

| Module | Subject File | Questions Covered | Core Topics & Highlights |
| :--- | :--- | :---: | :--- |
| **01** | [01. Computer Networks Answers](file:///d:/interview/Infosys/Questions/01-computer-networks-answers.md) | **Q1 – Q22** | OSI & TCP/IP models, TCP vs UDP, IP & Subnetting, MAC & ARP, DHCP DORA, URL Resolution Lifecycle, DNS hierarchy, HTTP vs HTTPS & TLS, HTTP Methods & Status Codes, Cookies vs Sessions, Port multiplexing, Switch vs Router, 3-Way Handshake, Flow vs Congestion Control, Forward/Reverse Proxies, L4 vs L7 Load Balancing. |
| **02** | [02. Operating Systems Answers](file:///d:/interview/Infosys/Questions/02-operating-systems-answers.md) | **Q23 – Q44** | Process vs Thread, PCB & Lifecycle states, Context Switching mechanics, User vs Kernel Mode, CPU Scheduling (FCFS, SJF, RR, Priority, Aging, Convoy Effect), Critical Section & Race Conditions, Mutex vs Semaphore, Deadlock 4 conditions & Handling (Banker's, WFG), Paging & Virtual Memory, Page Fault Lifecycle, Page Replacement (FIFO, LRU, Optimal, Belady's Anomaly), Thrashing, Multithreaded Race condition code fix & Debugging scenarios. |
| **03** | [03. DBMS & SQL Answers](file:///d:/interview/Infosys/Questions/03-dbms-and-sql-answers.md) | **Q45 – Q84** | **Theory (Q45–Q64):** DBMS vs RDBMS, Keys hierarchy, Constraints, Normalization (1NF to BCNF), Denormalization, Transactions & ACID, TCL commands, Concurrency anomalies, 4 Isolation Levels, Deadlocks, B-Trees vs B+ Trees, Clustered vs Secondary Index, Query Optimization, SQL vs NoSQL, Replication vs Sharding, CAP Theorem.<br>**SQL Coding (Q65–Q84):** Salary filters, 2nd/Nth highest salary, Earning > avg, Highest & Top 3 per dept, Duplicate records, Anti-joins, Total spending, 2nd highest order per customer, Unsold products, WHERE vs HAVING, INNER vs LEFT join, Correlated subqueries, Window functions. |
| **04** | [04. C++ Programming Answers](file:///d:/interview/Infosys/Questions/04-cpp-answers.md) | **Q85 – Q104** | C vs C++, Class vs Object, Constructor & Destructor lifecycle, `this` pointer, Pointer vs Reference, Stack vs Heap memory, `const` correctness, Static members & methods, Copy Constructor & Copy Assignment, Shallow vs Deep Copy, Rule of 3 / Rule of 5, RAII, Smart Pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`), Virtual Destructors, Virtual Functions & `vtable`/`vptr` runtime polymorphism, Exception Handling & Stack Unwinding, Container selection (`vector`, `list`, `deque`, `map`, `unordered_map`, `set`, `unordered_set`). |
| **05** | [05. OOP / OOPS Answers](file:///d:/interview/Infosys/Questions/05-oops-answers.md) | **Q105 – Q122** | 4 Pillars (Encapsulation, Abstraction, Inheritance, Polymorphism), Compile-Time vs Runtime Polymorphism, Overloading vs Overriding, Virtual & Pure Virtual Functions, Abstract Classes, Access Specifiers & Inheritance Modes, Multiple Inheritance & Diamond Problem (Virtual Inheritance), Association vs Aggregation vs Composition, Composition over Inheritance, SOLID Principles in detail, Extensible System Designs (Payment Strategy, Notification System, Dependency Injection in Car-Engine, Library Management System). |
| **06** | [06. Rapid-Fire Round Answers](file:///d:/interview/Infosys/Questions/06-rapid-fire-answers.md) | **R1 – R30** | Crisp, 20–45 second punchy answers covering all core domains for rapid-fire technical assessment rounds. |
| **07** | [07. Cross-Question Follow-Up Chains](file:///d:/interview/Infosys/Questions/07-cross-question-follow-up-chains.md) | **Chains 1 – 20** | **Multi-Level Interview Drill-Downs:** TCP Deep Dive, TCP Performance, DNS, URL Request, DB Indexing, Composite Index Leftmost Prefix, Query Optimization, Transactions & ACID, Isolation Levels, SQL Window Functions, C++ Memory, Copying & Rule of 3/5, Virtual Functions & vtable, OOP Design, Composition vs Inheritance, OS Threads, Race Conditions & Atomics, Deadlocks, Paging & Thrashing, Full-Stack E-Commerce Slow Checkout Drill. |

---

## 🎯 3-Level Technical Interview Framework

When answering in an SP L3 interview, structure responses across 3 distinct depths:

1. **Level 1 — Direct Definition (30–45s):** Give a crisp, authoritative conceptual definition without unnecessary filler.
2. **Level 2 — Mechanism & Why (1–2 mins):** Explain *how* it works internally (e.g., memory layout, data structures, algorithm time/space complexity, trade-offs).
3. **Level 3 — Real-World Scenario & Edge Cases:** Defend your architectural or coding decision against follow-ups (e.g., failure modes, race conditions, index selectivity, distributed network splits).
