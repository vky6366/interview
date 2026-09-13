# Database Management Systems (DBMS) — Master Interview Repository

> **Target Role:** Infosys Specialist Programmer (SP) L3 Interview  
> **Course Scope:** Complete 11.5-Hour DBMS Curriculum (Architecture, ER/EER Design, Relational Theory, Normalization, Transactions & Concurrency, Indexing & Recovery, NoSQL Engines, Distributed Databases & CAP).

---

## 📚 Master Topic Index & Curriculum Roadmap

| Module | File | Core Concepts Covered |
| :--- | :--- | :--- |
| **01** | [01. Fundamentals & Architecture](file:///d:/interview/Infosys/DBMS/01-dbms-fundamentals-and-architecture.md) | File System vs. DBMS, 3-Schema ANSI-SPARC Architecture, Physical & Logical Data Independence, 1-Tier/2-Tier/3-Tier DB Architecture, Database Administrator (DBA) roles. |
| **02** | [02. ER Model & Extended ER](file:///d:/interview/Infosys/DBMS/02-er-model-and-extended-er.md) | Entities & Attributes (Simple/Composite, Single/Multivalued, Stored/Derived), Cardinality & Participation, Weak Entity Sets, Extended ER (Generalization, Specialization, Aggregation), Real-World Case Study: Facebook ER Model. |
| **03** | [03. Relational Model & ER Mapping](file:///d:/interview/Infosys/DBMS/03-relational-model-keys-and-er-mapping.md) | Relational Model Concepts (Tuples, Cardinality, Degree, Domain), Comprehensive Keys Hierarchy (Super, Candidate, Primary, Foreign, Alternate, Composite), Integrity Constraints (Domain, Entity, Referential), 6 Formal ER-to-Relational Transformation Rules. |
| **04** | [04. Normalization & FDs](file:///d:/interview/Infosys/DBMS/04-normalization-and-functional-dependencies.md) | Modification Anomalies (Insert, Delete, Update), Functional Dependencies (Trivial, Full, Partial, Transitive), Armstrong's Axioms, Attribute Closure Algorithm & Finding Candidate Keys, 1NF, 2NF, 3NF, BCNF, Lossless Join & Dependency Preservation, Denormalization Trade-offs. |
| **05** | [05. Transactions & Concurrency](file:///d:/interview/Infosys/DBMS/05-transactions-acid-and-concurrency-control.md) | Transaction Lifecycle & State Transitions, In-depth ACID Properties, Concurrency Anomalies (Dirty Read, Non-Repeatable Read, Phantom Read, Lost Update), ANSI SQL 4 Isolation Levels, Lock Protocols (Shared, Exclusive, 2PL, Strict 2PL, Rigorous 2PL), Deadlock Handling (WFG, Wait-Die, Wound-Wait). |
| **06** | [06. Atomicity, Recovery & Indexing](file:///d:/interview/Infosys/DBMS/06-atomicity-recovery-and-indexing.md) | Atomicity & Durability via Write-Ahead Logging (WAL), Log anatomy (Undo/Redo), Immediate vs Deferred Updates, Checkpointing & ARIES Algorithm, Dense vs Sparse Indexing, Primary/Clustering/Secondary Indexes, B-Trees vs B+ Trees (Fan-out, Range Scans, Linked Leaves), Clustered vs Secondary Index (InnoDB), Hash Indexes. |
| **07** | [07. SQL vs. NoSQL & DB Types](file:///d:/interview/Infosys/DBMS/07-sql-vs-nosql-and-database-types.md) | SQL vs NoSQL Paradigm Comparison, ACID vs BASE Model, 4 Major NoSQL Types (Document / MongoDB, Key-Value / Redis, Columnar / Cassandra & ClickHouse, Graph / Neo4j), Index-Free Adjacency, Polyglot Persistence Enterprise Architecture. |
| **08** | [08. Distributed DBs, Replication & CAP](file:///d:/interview/Infosys/DBMS/08-distributed-databases-replication-sharding-cap.md) | Clustering & High Availability, Synchronous vs Asynchronous Replication, Topologies (Master-Slave, Multi-Master, Leaderless Quorum $W+R>N$), Replication Lag & "Read-Your-Own-Writes", Vertical vs Horizontal Partitioning, Sharding (Range, Hash, Consistent Hashing), CAP & PACELC Theorems, MySQL Binlog Internals. |

---

## ⚡ Top 20 High-Yield DBMS Interview Q&A (Quick Revision)

### 1. What is the fundamental difference between DBMS and RDBMS?
**DBMS** stores data as flat files or hierarchical trees with no enforced relationships between tables or mathematical relational algebra foundation. **RDBMS** (Relational DBMS) organizes data into tables (relations) with strict primary-foreign key relationships, enforces ACID properties, and adheres to Codd's 12 Rules.

### 2. What is Data Independence and what are its two levels?
The ability to modify a schema at one level of the 3-schema architecture without altering the schema at the next higher level:
- **Logical Data Independence:** Modifying the conceptual schema (e.g., adding/renaming a column/table) without breaking external views or user queries.
- **Physical Data Independence:** Modifying internal storage structures, indexes, or disk file organization without affecting the conceptual schema.

### 3. What is a Candidate Key vs. Super Key vs. Primary Key?
- **Super Key:** Any set of attributes that uniquely identifies a tuple in a relation.
- **Candidate Key:** A **minimal** Super Key (no proper subset is a super key).
- **Primary Key:** The single Candidate Key officially chosen by the database designer to uniquely identify records across the table (cannot contain `NULL`).

### 4. What is the difference between Generalization and Specialization in EER?
- **Generalization (Bottom-Up):** Combining common attributes of multiple lower-level entity sets into a higher-level generalized entity set (e.g., `Car` and `Truck` generalized into `Vehicle`).
- **Specialization (Top-Down):** Breaking down a higher-level entity set into specialized sub-entities based on distinguishing characteristics (e.g., `Employee` specialized into `Developer` and `Manager`).

### 5. How are 1:N and M:N relationships converted from ER diagrams into SQL tables?
- **1:N Relationship:** Place the Primary Key of the "1" side as a **Foreign Key** in the "N" (many) side table. No new table required.
- **M:N Relationship:** Create a **new junction/bridge table** whose Primary Key is a composite of the Primary Keys of both participating entities.

### 6. What are the 3 modification anomalies prevented by Normalization?
- **Insertion Anomaly:** Inability to record information about an entity without artificially creating unrelated records of another entity.
- **Deletion Anomaly:** Loss of unrelated critical data as a side-effect of deleting a record.
- **Update Anomaly:** Inconsistent data caused by needing to update duplicated values across multiple rows.

### 7. What is the exact mathematical difference between 3NF and BCNF?
For every non-trivial functional dependency $X \to Y$:
- **3NF:** $X$ is a Super Key **OR** $Y$ is a Prime Attribute.
- **BCNF:** $X$ **MUST** be a Super Key unconditionally.

### 8. Why do relational databases choose 3NF over BCNF in production?
BCNF guarantees lossless join, but does **not guarantee dependency preservation**. If an FD spans multiple decomposed tables in BCNF, validating that business rule requires an expensive `JOIN` on every write. 3NF guarantees both lossless join and dependency preservation.

### 9. What are the 4 ACID properties in DBMS?
- **Atomicity:** Entire transaction executes or rolls back completely ("all or nothing").
- **Consistency:** Database transitions from one valid state to another, preserving constraints.
- **Isolation:** Concurrent transactions execute without exposing intermediate states to each other.
- **Durability:** Committed changes persist permanently on non-volatile disk despite system crashes.

### 10. Explain the 4 Concurrency Anomalies.
- **Dirty Read:** Reading uncommitted data written by a transaction that subsequently rolls back.
- **Non-Repeatable Read:** Re-reading the same row and observing modified column values from another committed transaction.
- **Phantom Read:** Re-executing a range query and observing new rows inserted by another committed transaction.
- **Lost Update:** Two concurrent transactions overwrite each other's changes without locking.

### 11. What are the 4 ANSI SQL Isolation Levels?
1. `READ UNCOMMITTED` (Allows Dirty, Non-Repeatable, Phantom reads).
2. `READ COMMITTED` (Prevents Dirty reads).
3. `REPEATABLE READ` (Prevents Dirty and Non-Repeatable reads; prevents Phantom in MySQL InnoDB via Gap Locks).
4. `SERIALIZABLE` (Prevents all anomalies via strict range locking or SSI).

### 12. What is Two-Phase Locking (2PL) and Strict 2PL?
- **2PL:** A transaction acquires all locks during the **Growing Phase** and cannot acquire any new locks once it begins releasing locks in the **Shrinking Phase**. Guarantees conflict serializability.
- **Strict 2PL:** Holds all **Exclusive ($X$) locks** until the transaction terminates (`COMMIT`/`ROLLBACK`), completely preventing cascading rollbacks.

### 13. How does Write-Ahead Logging (WAL) work?
WAL mandates that log records (containing undo and redo values) must be written and flushed to non-volatile disk **before** the corresponding data page is written to disk, and before sending a `COMMIT` acknowledgment to the client.

### 14. Why do databases use B+ Trees instead of Binary Search Trees or B-Trees?
- **Vs BST:** B+ Trees have huge fan-out ($1000+$ keys per page), reducing tree height to $3-4$ levels on billions of rows and minimizing slow disk I/Os.
- **Vs B-Tree:** B+ Tree internal nodes store only search keys and child pointers (no row data), maximizing memory packing. Crucially, all leaf nodes form a **doubly linked list**, allowing $O(\log N)$ point lookups followed by sequential range scans without tree re-traversal.

### 15. What is the difference between a Clustered and Non-Clustered Index?
- **Clustered Index:** The leaf nodes contain the **actual table row data** physically ordered on the index key. Only 1 clustered index per table (typically Primary Key).
- **Non-Clustered (Secondary) Index:** The leaf nodes contain the indexed column value and a reference pointer (in InnoDB, the Primary Key value). A table can have multiple secondary indexes.

### 16. What is a Covering Index?
A secondary index that includes all columns requested in the query (`SELECT`, `WHERE`, `JOIN`). The database satisfies the query directly from the index tree without executing a secondary-to-primary index lookup ("bookmark lookup").

### 17. Compare SQL vs. NoSQL databases.
- **SQL (RDBMS):** Rigid schema, ACID transactions, relational joins, vertical scaling (Postgres, MySQL).
- **NoSQL:** Dynamic/schemaless, BASE eventual consistency, denormalized, native horizontal sharding across distributed clusters (MongoDB, Redis, Cassandra).

### 18. What is the CAP Theorem and why is CA impossible in distributed systems?
A distributed system can only provide two of **Consistency (C)**, **Availability (A)**, and **Partition Tolerance (P)**. Because physical network cables and switches inevitably drop messages ($P$ is mandatory), distributed systems must architecturally choose between **CP** (Consistency over Availability during network cut) and **AP** (Availability over Consistency).

### 19. What is the PACELC Theorem?
An extension of CAP describing normal operations:
If **Partition (P)** $\implies$ choose **Availability (A)** or **Consistency (C)**;  
**Else (E)** under normal operation $\implies$ choose **Latency (L)** or **Consistency (C)**.

### 20. How is MySQL Master-Slave replication implemented?
The Master logs all mutations to its **Binary Log (`binlog`)**. The Slave's **I/O Thread** connects to the Master and streams binlog events into the local **Relay Log**. The Slave's **SQL Thread** sequentially reads and executes the relay log commands to update the local database engine.
