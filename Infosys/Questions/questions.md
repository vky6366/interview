# Infosys Specialist Programmer L3 — Technical Interview Question Bank

**Total core questions: 112**

* Computer Networks: 22
* Operating Systems: 22
* DBMS + SQL: 30
* C++: 20
* OOP/OOPS: 18
* Rapid-Fire: 30
* Cross-Question Follow-Ups: 20

The core bank is approximately **30% Easy, 45% Medium, 20% Hard, and 5% Scenario/Cross-topic**.

---

# 1. Computer Networks — 22 Questions

## Easy / Fundamentals

### Q1. What is a computer network, and why do we need different layers in a networking model?

**Difficulty:** Easy
**Type:** Conceptual

### Q2. Explain the OSI model layer by layer. What responsibility does each layer have?

**Difficulty:** Easy
**Type:** Conceptual

### Q3. What is the TCP/IP model? How does it differ from the OSI model?

**Difficulty:** Easy
**Type:** Comparison

### Q4. What is the difference between TCP and UDP? Give practical examples where you would choose each.

**Difficulty:** Easy
**Type:** Comparison

### Q5. What is an IP address? Explain IPv4 addressing and subnet masks at a high level.

**Difficulty:** Easy
**Type:** Conceptual

### Q6. What is a MAC address? How is it different from an IP address?

**Difficulty:** Easy
**Type:** Comparison

---

## Medium / Interview-Level

### Q7. What problem does ARP solve? Walk me through what happens when a machine wants to communicate with another machine on the same LAN but only knows its IP address.

**Difficulty:** Medium
**Type:** Conceptual / Scenario

### Q8. What is DHCP? Explain the DHCP DORA process.

**Difficulty:** Medium
**Type:** Conceptual

### Q9. What happens when you type `google.com` into a browser and press Enter? Explain the process from DNS resolution through receiving the webpage.

**Difficulty:** Medium
**Type:** Scenario

### Q10. What is DNS? Explain recursive DNS resolution and DNS caching.

**Difficulty:** Medium
**Type:** Conceptual

### Q11. What is the difference between HTTP and HTTPS? What does TLS actually provide?

**Difficulty:** Medium
**Type:** Comparison

### Q12. Explain common HTTP methods such as GET, POST, PUT, PATCH, and DELETE. What makes a method idempotent?

**Difficulty:** Medium
**Type:** Conceptual / Practical

### Q13. Explain HTTP status codes 200, 201, 301, 302, 400, 401, 403, 404, 409, 429, 500, 502, 503, and 504. When would you use each?

**Difficulty:** Medium
**Type:** Conceptual

### Q14. What are cookies and sessions? How does a web server remember that a user is logged in?

**Difficulty:** Medium
**Type:** Conceptual / Practical

### Q15. What is a port number? Why can multiple applications communicate over the same IP address?

**Difficulty:** Medium
**Type:** Conceptual

### Q16. What is the difference between a switch and a router?

**Difficulty:** Medium
**Type:** Comparison

### Q17. Explain the TCP three-way handshake. Why are three steps required instead of two?

**Difficulty:** Medium
**Type:** Conceptual

### Q18. How does TCP provide reliable communication even though IP itself does not guarantee delivery?

**Difficulty:** Medium
**Type:** Conceptual

---

## Hard / Deeper Reasoning

### Q19. Explain TCP flow control versus TCP congestion control. Why are they different problems?

**Difficulty:** Hard
**Type:** Comparison / Conceptual

### Q20. Suppose a TCP connection has high latency but almost no packet loss. What factors could still reduce throughput?

**Difficulty:** Hard
**Type:** Debugging / Scenario

### Q21. What is the difference between a forward proxy and a reverse proxy? Where would you use each in a production architecture?

**Difficulty:** Hard
**Type:** Comparison / Scenario

### Q22. Explain L4 versus L7 load balancing. What information can an L7 load balancer use that an L4 load balancer cannot?

**Difficulty:** Hard
**Type:** Conceptual / Scenario

---

# 2. Operating Systems — 22 Questions

## Easy / Fundamentals

### Q23. What is a process? What is a thread?

**Difficulty:** Easy
**Type:** Conceptual

### Q24. What are the major states of a process? Explain the transitions between them.

**Difficulty:** Easy
**Type:** Conceptual

### Q25. What is the difference between a process and a thread in terms of memory and resources?

**Difficulty:** Easy
**Type:** Comparison

### Q26. What is context switching? Why does it have overhead?

**Difficulty:** Easy
**Type:** Conceptual

### Q27. What is multithreading? What are its advantages and disadvantages?

**Difficulty:** Easy
**Type:** Conceptual

### Q28. What is the difference between user mode and kernel mode?

**Difficulty:** Easy
**Type:** Conceptual

---

## Medium / Interview-Level

### Q29. Explain FCFS, SJF, Round Robin, and Priority CPU scheduling.

**Difficulty:** Medium
**Type:** Conceptual

### Q30. Why can SJF produce better average waiting time than FCFS?

**Difficulty:** Medium
**Type:** Conceptual / Why

### Q31. What is starvation in CPU scheduling? Which scheduling algorithms can cause it, and how can aging solve it?

**Difficulty:** Medium
**Type:** Conceptual

### Q32. What is a critical section? Give a real-world example of a race condition.

**Difficulty:** Medium
**Type:** Conceptual / Scenario

### Q33. What is a mutex? How is it different from a semaphore?

**Difficulty:** Medium
**Type:** Comparison

### Q34. What is synchronization? Why is synchronization necessary in multithreaded programs?

**Difficulty:** Medium
**Type:** Conceptual

### Q35. Explain deadlock. What are the four necessary conditions for deadlock?

**Difficulty:** Medium
**Type:** Conceptual

### Q36. Differentiate deadlock prevention, deadlock avoidance, deadlock detection, and recovery.

**Difficulty:** Medium
**Type:** Comparison

### Q37. Explain paging. Why is paging useful?

**Difficulty:** Medium
**Type:** Conceptual

### Q38. What is virtual memory? Why does an operating system use it?

**Difficulty:** Medium
**Type:** Conceptual

### Q39. What is a page fault? Walk through what happens when a process accesses a page that is not currently in physical memory.

**Difficulty:** Medium
**Type:** Scenario

---

## Hard / Deeper Reasoning

### Q40. Compare paging and segmentation. What problem does each solve?

**Difficulty:** Hard
**Type:** Comparison

### Q41. Explain FIFO, LRU, and Optimal page replacement. Why can FIFO sometimes perform worse when more frames are added?

**Difficulty:** Hard
**Type:** Conceptual

### Q42. What is thrashing? How can an operating system detect and reduce it?

**Difficulty:** Hard
**Type:** Conceptual / Debugging

### Q43. Two threads update the same bank account balance simultaneously. Explain exactly how a race condition can occur and how you would fix it.

**Difficulty:** Hard
**Type:** Debugging / Scenario

### Q44. A multithreaded application suddenly becomes extremely slow even though CPU utilization is low. What OS-level problems would you investigate?

**Difficulty:** Hard
**Type:** Debugging / Scenario

---

# 3. DBMS + SQL — 30 Questions

## DBMS Fundamentals

### Q45. What is a DBMS? How is an RDBMS different from a general DBMS?

**Difficulty:** Easy
**Type:** Conceptual

### Q46. Explain primary key, candidate key, super key, foreign key, and composite key.

**Difficulty:** Easy
**Type:** Conceptual

### Q47. What are database constraints? Explain PRIMARY KEY, FOREIGN KEY, UNIQUE, NOT NULL, CHECK, and DEFAULT.

**Difficulty:** Easy
**Type:** Conceptual

### Q48. Why can't a table have two primary keys?

**Difficulty:** Easy
**Type:** Conceptual / Why

### Q49. What is normalization? Why do we normalize databases?

**Difficulty:** Easy
**Type:** Conceptual

### Q50. Explain 1NF, 2NF, 3NF, and BCNF with examples.

**Difficulty:** Medium
**Type:** Conceptual

### Q51. What is denormalization? When might intentionally violating normalization be useful?

**Difficulty:** Medium
**Type:** Scenario / Conceptual

### Q52. What is a transaction? Explain ACID properties with a practical example.

**Difficulty:** Medium
**Type:** Conceptual

### Q53. What are COMMIT, ROLLBACK, and SAVEPOINT?

**Difficulty:** Easy
**Type:** Conceptual

### Q54. What problems can occur when multiple transactions execute concurrently?

**Difficulty:** Medium
**Type:** Conceptual

### Q55. Explain dirty read, non-repeatable read, and phantom read.

**Difficulty:** Medium
**Type:** Conceptual

### Q56. Explain the common SQL transaction isolation levels.

**Difficulty:** Hard
**Type:** Conceptual

### Q57. What is a database deadlock? Give an example involving two transactions.

**Difficulty:** Medium
**Type:** Scenario

### Q58. What is an index? Why does an index make reads faster but writes potentially slower?

**Difficulty:** Medium
**Type:** Conceptual

### Q59. Explain the basic idea behind B-tree and B+ tree indexes. Why are B+ trees commonly useful for database indexes?

**Difficulty:** Hard
**Type:** Conceptual

### Q60. What is the difference between clustered and non-clustered indexes?

**Difficulty:** Medium
**Type:** Comparison

### Q61. What is query optimization? What factors might cause a database to choose one execution plan over another?

**Difficulty:** Hard
**Type:** Conceptual

### Q62. SQL vs NoSQL: what are the important architectural differences, and when might you choose one over the other?

**Difficulty:** Medium
**Type:** Comparison

### Q63. Explain replication and sharding. What problem does each solve?

**Difficulty:** Medium
**Type:** Comparison

### Q64. Explain the CAP theorem. What does consistency mean in this context?

**Difficulty:** Hard
**Type:** Conceptual

---

# SQL Coding Questions

For the following questions, assume the schemas below.

### `Employee`

| employee_id | name | department_id | salary | manager_id |
| ----------- | ---- | ------------- | -----: | ---------: |

### `Department`

| department_id | department_name |
| ------------- | --------------- |

### `Orders`

| order_id | customer_id | order_date | amount |
| -------- | ----------- | ---------- | -----: |

### `Customer`

| customer_id | customer_name | city |
| ----------- | ------------- | ---- |

### `Product`

| product_id | product_name | category | price |
| ---------- | ------------ | -------- | ----: |

### `OrderItem`

| order_id | product_id | quantity |
| -------- | ---------- | -------: |

---

### Q65. Write a query to retrieve all employees whose salary is greater than ₹50,000.

**Difficulty:** Easy
**Type:** Coding

### Q66. Write a query to find the second-highest salary in the Employee table.

**Difficulty:** Medium
**Type:** Coding

### Q67. Write a query to find the Nth-highest salary without assuming N = 2.

**Difficulty:** Medium
**Type:** Coding

### Q68. Write a query to find employees who earn more than the average employee salary.

**Difficulty:** Medium
**Type:** Coding / Subquery

### Q69. Write a query to find the highest-paid employee in every department.

**Difficulty:** Medium
**Type:** Coding / GROUP BY

### Q70. Write a query to find the top three highest-paid employees in every department.

**Difficulty:** Hard
**Type:** Coding / Window Function

### Q71. Write a query to find duplicate employee names.

**Difficulty:** Easy
**Type:** Coding

### Q72. Write a query to retrieve all employees who do not have a manager.

**Difficulty:** Easy
**Type:** Coding

### Q73. Write a query displaying employee name, department name, and salary using an appropriate JOIN.

**Difficulty:** Easy
**Type:** Coding

### Q74. Write a query to find departments having more than five employees.

**Difficulty:** Medium
**Type:** Coding / GROUP BY / HAVING

### Q75. Write a query to find customers who have never placed an order.

**Difficulty:** Medium
**Type:** Coding / LEFT JOIN

### Q76. Write a query to find the total order amount for every customer.

**Difficulty:** Easy
**Type:** Coding / GROUP BY

### Q77. Write a query to find the customer who has spent the most money.

**Difficulty:** Medium
**Type:** Coding

### Q78. Write a query to find the second-highest order amount for each customer.

**Difficulty:** Hard
**Type:** Coding / Window Function

### Q79. Write a query to find products that have never appeared in OrderItem.

**Difficulty:** Medium
**Type:** Coding / JOIN

### Q80. Write a query to find the most expensive product in each category.

**Difficulty:** Medium
**Type:** Coding / Window Function

### Q81. Explain the difference between WHERE and HAVING. Give an example where using WHERE instead of HAVING would be incorrect.

**Difficulty:** Medium
**Type:** Conceptual / Coding

### Q82. Explain INNER JOIN versus LEFT JOIN using a concrete example involving Customer and Orders.

**Difficulty:** Medium
**Type:** Comparison / Coding

### Q83. What is a correlated subquery? Write a query that uses one to find employees earning more than the average salary of their own department.

**Difficulty:** Hard
**Type:** Coding / Conceptual

### Q84. Using a window function, calculate each employee's salary rank within their department.

**Difficulty:** Hard
**Type:** Coding

---

# 4. C++ — 20 Questions

## Fundamentals

### Q85. What are the major differences between C and C++?

**Difficulty:** Easy
**Type:** Comparison

### Q86. What is a class? What is an object?

**Difficulty:** Easy
**Type:** Conceptual

### Q87. What is a constructor? What is a destructor? When are they called?

**Difficulty:** Easy
**Type:** Conceptual

### Q88. What is the `this` pointer?

**Difficulty:** Easy
**Type:** Conceptual

### Q89. What is the difference between a pointer and a reference?

**Difficulty:** Easy
**Type:** Comparison

### Q90. What is the difference between stack memory and heap memory?

**Difficulty:** Medium
**Type:** Conceptual

### Q91. Explain `const` in C++. Where can it be used?

**Difficulty:** Medium
**Type:** Conceptual

### Q92. What are static data members and static member functions?

**Difficulty:** Medium
**Type:** Conceptual

---

## Medium / Advanced

### Q93. What is a copy constructor? When is it invoked?

**Difficulty:** Medium
**Type:** Conceptual

### Q94. What is the difference between a copy constructor and copy assignment operator?

**Difficulty:** Medium
**Type:** Comparison

### Q95. Explain shallow copy versus deep copy with an example involving dynamically allocated memory.

**Difficulty:** Medium
**Type:** Conceptual / Debugging

### Q96. Explain the Rule of 3 and how it relates to the Rule of 5.

**Difficulty:** Hard
**Type:** Conceptual

### Q97. What is RAII? How does C++ use RAII for resource management?

**Difficulty:** Hard
**Type:** Conceptual

### Q98. What are smart pointers? Explain `unique_ptr`, `shared_ptr`, and `weak_ptr`.

**Difficulty:** Medium
**Type:** Conceptual

### Q99. What happens if you delete an object through a base-class pointer when the base destructor is not virtual?

**Difficulty:** Hard
**Type:** Debugging

### Q100. What is a virtual function? How does runtime polymorphism work internally at a high level?

**Difficulty:** Medium
**Type:** Conceptual

### Q101. Explain exception handling in C++. What happens when an exception is thrown?

**Difficulty:** Medium
**Type:** Conceptual

### Q102. Compare `vector`, `list`, and `deque`. When would you choose each?

**Difficulty:** Medium
**Type:** Comparison

### Q103. Compare `map` and `unordered_map`. What are their typical time complexities and important trade-offs?

**Difficulty:** Medium
**Type:** Comparison

### Q104. Compare `set` and `unordered_set`.

**Difficulty:** Easy
**Type:** Comparison

---

# 5. OOP / OOPS — 18 Questions

## Fundamentals

### Q105. Explain the four major principles of OOP: encapsulation, abstraction, inheritance, and polymorphism.

**Difficulty:** Easy
**Type:** Conceptual

### Q106. What is encapsulation? Why is keeping data private useful?

**Difficulty:** Easy
**Type:** Conceptual

### Q107. What is abstraction? How is abstraction different from encapsulation?

**Difficulty:** Medium
**Type:** Comparison

### Q108. What is inheritance? What are the different forms of inheritance?

**Difficulty:** Easy
**Type:** Conceptual

### Q109. What is polymorphism? Explain compile-time and runtime polymorphism.

**Difficulty:** Medium
**Type:** Conceptual

### Q110. What is function overloading? How does it differ from function overriding?

**Difficulty:** Medium
**Type:** Comparison

### Q111. What is a virtual function? Why is it required for runtime polymorphism?

**Difficulty:** Medium
**Type:** Conceptual

### Q112. What is a pure virtual function? What is an abstract class?

**Difficulty:** Medium
**Type:** Conceptual

---

## Deeper OOP

### Q113. Explain public, protected, and private access specifiers. How do they affect inheritance?

**Difficulty:** Medium
**Type:** Conceptual

### Q114. What is multiple inheritance? What problems can it introduce?

**Difficulty:** Medium
**Type:** Conceptual

### Q115. Explain the diamond problem. How does virtual inheritance solve it?

**Difficulty:** Hard
**Type:** Conceptual

### Q116. Differentiate association, aggregation, and composition using real-world examples.

**Difficulty:** Medium
**Type:** Comparison

### Q117. Why is composition often preferred over inheritance in software design?

**Difficulty:** Hard
**Type:** Conceptual

### Q118. Explain the Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, and Dependency Inversion principles.

**Difficulty:** Hard
**Type:** Conceptual

### Q119. You are designing a payment system supporting UPI, credit card, and net banking. How would you use interfaces/abstract classes and polymorphism?

**Difficulty:** Hard
**Type:** Scenario / Design

### Q120. You are designing a notification system supporting Email, SMS, WhatsApp, and push notifications. How would you structure the classes so that adding a new notification channel requires minimal changes?

**Difficulty:** Hard
**Type:** Scenario / OOP Design

### Q121. Suppose a class `Car` directly creates an object of `Engine`, `Logger`, and `PaymentService`. What design problems might this cause, and how could dependency injection improve the design?

**Difficulty:** Hard
**Type:** Scenario / Design

### Q122. Design a basic library management system using OOP. Identify the major classes, their relationships, and where inheritance/polymorphism would be useful.

**Difficulty:** Hard
**Type:** Scenario / Design

---

# High-Priority Questions

These are the questions I would make sure you can explain **without memorized definitions**, including examples and follow-up questions.

## CN

1. **Q9** — What happens when you type a URL?
2. **Q10** — DNS resolution and caching
3. **Q11** — HTTP vs HTTPS and TLS
4. **Q14** — Cookies vs sessions
5. **Q17** — TCP three-way handshake
6. **Q18** — How TCP provides reliability
7. **Q19** — Flow control vs congestion control
8. **Q21** — Forward proxy vs reverse proxy
9. **Q22** — L4 vs L7 load balancing

## OS

10. **Q25** — Process vs thread
11. **Q26** — Context switching
12. **Q31** — Starvation and aging
13. **Q32** — Critical section and race condition
14. **Q33** — Mutex vs semaphore
15. **Q35** — Deadlock and four conditions
16. **Q36** — Prevention vs avoidance vs detection
17. **Q39** — Page fault
18. **Q41** — Page replacement algorithms
19. **Q42** — Thrashing
20. **Q43** — Multithreaded race-condition debugging

## DBMS / SQL

21. **Q50** — 1NF, 2NF, 3NF, BCNF
22. **Q52** — ACID
23. **Q54–Q56** — Concurrency and isolation levels
24. **Q58** — Indexing
25. **Q59** — B-tree/B+ tree
26. **Q61** — Query optimization
27. **Q63** — Replication vs sharding
28. **Q64** — CAP theorem
29. **Q66** — Second-highest salary
30. **Q69** — Highest salary per department
31. **Q70** — Top 3 per department
32. **Q75** — Customers with no orders
33. **Q78** — Second-highest amount per customer
34. **Q83** — Correlated subquery
35. **Q84** — Window functions

## C++

36. **Q90** — Stack vs heap
37. **Q93–Q96** — Copy constructor, assignment, deep copy, Rule of 3/5
38. **Q97** — RAII
39. **Q98** — Smart pointers
40. **Q99** — Virtual destructor
41. **Q100** — Virtual functions and runtime polymorphism
42. **Q102** — STL container selection
43. **Q103** — map vs unordered_map

## OOP

44. **Q107** — Abstraction vs encapsulation
45. **Q109** — Compile-time vs runtime polymorphism
46. **Q110** — Overloading vs overriding
47. **Q112** — Pure virtual function / abstract class
48. **Q115** — Diamond problem
49. **Q117** — Composition vs inheritance
50. **Q118** — SOLID
51. **Q119–Q122** — Real-world OOP design

---

# Rapid-Fire Round — 30 Questions

Answer these in roughly **20–45 seconds each**.

### CN

**R1.** What is the default port of HTTP?

**R2.** What is the default port of HTTPS?

**R3.** What protocol translates domain names into IP addresses?

**R4.** What is the difference between TCP and UDP in one sentence?

**R5.** What does ARP map?

**R6.** Why is TCP called connection-oriented?

### OS

**R7.** Process vs thread?

**R8.** What is a context switch?

**R9.** What is a race condition?

**R10.** Mutex vs semaphore?

**R11.** Name the four conditions required for deadlock.

**R12.** What is a page fault?

### DBMS

**R13.** What is a primary key?

**R14.** Primary key vs unique key?

**R15.** What does ACID stand for?

**R16.** WHERE vs HAVING?

**R17.** INNER JOIN vs LEFT JOIN?

**R18.** Why are indexes useful?

**R19.** Why can too many indexes be harmful?

**R20.** What is normalization?

**R21.** What is a foreign key?

**R22.** What is a window function?

### C++

**R23.** Pointer vs reference?

**R24.** What is the purpose of a destructor?

**R25.** What is a copy constructor?

**R26.** What is RAII?

**R27.** `map` vs `unordered_map`?

### OOP

**R28.** What are the four pillars of OOP?

**R29.** Overloading vs overriding?

**R30.** What is a virtual function?

---

# Cross-Question Follow-Ups

These are designed specifically to simulate an interviewer **drilling deeper after your first answer**.

The important skill here is not merely answering Q1 correctly. It is being able to survive the **Q1 → Q2 → Q3 → Q4 chain**.

---

## Chain 1 — TCP Deep Dive

**Q1.** What is TCP?

→ **Q2.** Why is TCP reliable?

→ **Q3.** How does TCP detect lost packets?

→ **Q4.** What is the purpose of sequence numbers and acknowledgements?

→ **Q5.** Explain the three-way handshake.

→ **Q6.** Does the three-way handshake itself provide reliability?

---

## Chain 2 — TCP Performance

**Q1.** What is flow control?

→ **Q2.** Why does TCP need flow control?

→ **Q3.** What is congestion control?

→ **Q4.** Flow control vs congestion control?

→ **Q5.** What happens if the receiver is fast but the network is congested?

---

## Chain 3 — DNS

**Q1.** What is DNS?

→ **Q2.** What happens when DNS information is not present in the local cache?

→ **Q3.** What is recursive DNS resolution?

→ **Q4.** Why does DNS use caching?

→ **Q5.** What happens if the DNS server itself is unavailable?

→ **Q6.** Can DNS use TCP?

---

## Chain 4 — URL Request

**Q1.** What happens when you enter `https://example.com`?

→ **Q2.** How does DNS resolve the domain?

→ **Q3.** How does the machine determine the destination MAC address?

→ **Q4.** Explain the TCP handshake.

→ **Q5.** What happens during TLS?

→ **Q6.** What HTTP request is eventually sent?

→ **Q7.** How does the server return the response?

---

## Chain 5 — Database Indexing

**Q1.** What is an index?

→ **Q2.** Why does it make searches faster?

→ **Q3.** What data structure is commonly used for database indexes?

→ **Q4.** Why are B+ trees suitable for databases?

→ **Q5.** What happens when you insert a new row into an indexed table?

→ **Q6.** Why can indexes slow down INSERT/UPDATE/DELETE?

---

## Chain 6 — Composite Index

**Q1.** What is a composite index?

→ **Q2.** Suppose you create an index on `(department_id, salary)`. Which queries can efficiently use it?

→ **Q3.** Does the order of columns in a composite index matter?

→ **Q4.** What is the leftmost-prefix principle?

→ **Q5.** Would an index on `(A, B)` necessarily help a query filtering only on B?

---

## Chain 7 — Query Optimization

**Q1.** What is query optimization?

→ **Q2.** What is an execution plan?

→ **Q3.** Why might the database choose a full table scan instead of an index?

→ **Q4.** How does selectivity affect index usefulness?

→ **Q5.** How would you investigate a slow SQL query in production?

---

## Chain 8 — Transactions

**Q1.** What is a transaction?

→ **Q2.** Explain ACID.

→ **Q3.** What happens if a transaction fails halfway through?

→ **Q4.** What does rollback do?

→ **Q5.** What happens when two transactions modify the same row simultaneously?

→ **Q6.** Which isolation level would affect this behavior?

---

## Chain 9 — Isolation Levels

**Q1.** What is a dirty read?

→ **Q2.** Which isolation levels allow dirty reads?

→ **Q3.** What is a non-repeatable read?

→ **Q4.** What is a phantom read?

→ **Q5.** What is the trade-off of using stronger isolation?

---

## Chain 10 — SQL Window Functions

**Q1.** What is a window function?

→ **Q2.** How is it different from GROUP BY?

→ **Q3.** Explain `ROW_NUMBER()`, `RANK()`, and `DENSE_RANK()`.

→ **Q4.** How would you find the top three salaries in every department?

→ **Q5.** What happens when multiple employees have the same salary?

---

## Chain 11 — C++ Memory

**Q1.** Stack vs heap?

→ **Q2.** When would you allocate memory dynamically?

→ **Q3.** What happens if dynamically allocated memory is never released?

→ **Q4.** What is a memory leak?

→ **Q5.** How do smart pointers help?

→ **Q6.** Why shouldn't everything simply use `shared_ptr`?

---

## Chain 12 — Copying Objects

**Q1.** What is a copy constructor?

→ **Q2.** When is it called?

→ **Q3.** What is shallow copy?

→ **Q4.** Why can shallow copy cause problems with pointers?

→ **Q5.** What is deep copy?

→ **Q6.** What is the Rule of 3?

→ **Q7.** How does the Rule of 5 extend it?

---

## Chain 13 — Virtual Functions

**Q1.** What is a virtual function?

→ **Q2.** Why do we need it?

→ **Q3.** What is runtime polymorphism?

→ **Q4.** What is a vtable?

→ **Q5.** How does a vtable help dispatch the correct function?

→ **Q6.** Why should a polymorphic base class often have a virtual destructor?

---

## Chain 14 — OOP Design

**Q1.** What is polymorphism?

→ **Q2.** Give a real-world example.

→ **Q3.** Suppose you have multiple payment methods. How would you design them?

→ **Q4.** Would you use inheritance or composition?

→ **Q5.** What happens when a new payment method is added?

→ **Q6.** Which SOLID principle is relevant?

---

## Chain 15 — Composition vs Inheritance

**Q1.** What is inheritance?

→ **Q2.** What is composition?

→ **Q3.** When would composition be preferable?

→ **Q4.** Give an example where inheritance creates unnecessary coupling.

→ **Q5.** How does composition reduce that coupling?

---

## Chain 16 — OS Threads

**Q1.** What is a thread?

→ **Q2.** Why are threads generally cheaper than processes?

→ **Q3.** Do threads have separate memory?

→ **Q4.** Which memory areas are shared?

→ **Q5.** What problems arise because threads share memory?

→ **Q6.** How do mutexes solve one of those problems?

---

## Chain 17 — Race Condition

**Q1.** What is a race condition?

→ **Q2.** Give an example involving a shared counter.

→ **Q3.** Why isn't `counter++` necessarily atomic?

→ **Q4.** How can you fix it?

→ **Q5.** Mutex or atomic variable — when might you choose each?

---

## Chain 18 — Deadlock

**Q1.** What is deadlock?

→ **Q2.** What are its four necessary conditions?

→ **Q3.** Give an example involving two locks.

→ **Q4.** How can lock ordering prevent deadlock?

→ **Q5.** What is deadlock prevention versus avoidance?

---

## Chain 19 — Paging

**Q1.** What is paging?

→ **Q2.** Why does the OS use virtual memory?

→ **Q3.** What happens during a page fault?

→ **Q4.** What is page replacement?

→ **Q5.** Compare LRU and FIFO.

→ **Q6.** What is thrashing?

---

## Chain 20 — Full-Stack Cross-Topic Drill

Imagine you have an e-commerce application where users report that **checkout is randomly slow**.

**Q1.** How would you determine whether the problem is networking, application code, database performance, or the operating system?

→ **Q2.** What network metrics would you check?

→ **Q3.** How would you investigate slow SQL queries?

→ **Q4.** What database indexes would you inspect?

→ **Q5.** Could thread contention cause the issue?

→ **Q6.** Could connection pooling cause it?

→ **Q7.** Could a load balancer be involved?

→ **Q8.** How would you systematically isolate the bottleneck?

---

# Final Interview Preparation Rule

For each **High-Priority** question, prepare yourself to answer at three levels:

### Level 1 — Direct answer

Explain the concept in **30–60 seconds**.

### Level 2 — Why / How

Be ready when the interviewer asks:

> "Why?"

> "How exactly?"

> "What happens internally?"

> "Give me an example."

### Level 3 — Drill-down

Be prepared for the interviewer to suddenly change direction:

> "Okay, you said TCP is reliable. How?"

> "You said indexes make queries faster. Why?"

> "You said threads share memory. Which memory?"

> "You said virtual functions enable runtime polymorphism. How?"

> "You said this follows OOP principles. Which principle?"

The **L3-style preparation target should therefore be understanding the chain of reasoning**, not memorizing isolated answers.

For SQL, actually write and execute the queries rather than only reading solutions. For C++ and OS, practice explaining what happens **in memory and at runtime**. For CN and DBMS, repeatedly ask yourself **"why was this mechanism designed this way?"**
