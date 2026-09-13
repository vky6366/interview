# System Design Interview Question Bank (Beginner $\to$ Intermediate $\to$ L3)

This question bank is structured specifically for technical interviews. Every question follows the formula:
**Question $\to$ Short Answer $\to$ Conversational Explanation $\to$ Possible Follow-up**.

---

## 🟢 Section 1: Beginner Questions (Fundamentals & Definitions)

### Q1.1: What is the difference between Scalability and Performance?
- **Short Answer**: Performance measures how fast a system processes a single unit of work (latency); scalability measures the system's ability to handle increasing total load by adding resources without performance degradation.
- **Conversational Explanation**: "If a search query takes 20ms for 1 user, that is performance. If that search query continues taking 20ms when 100,000 users search simultaneously because we added 10 app servers, that is scalability."
- **Possible Follow-up**: *"Can a system be scalable but have poor performance?"* $\to$ Yes, a batch processing system with high latency (takes 5 minutes per job) can scale horizontally to process 1 million jobs in parallel.

---

### Q1.2: What is the difference between a Forward Proxy and a Reverse Proxy?
- **Short Answer**: A Forward Proxy sits in front of **clients** to protect, filter, or anonymize them; a Reverse Proxy sits in front of **backend servers** to load balance, terminate SSL, and cache responses.
- **Conversational Explanation**: "When employees browse the internet through a corporate gateway that blocks restricted sites, that's a forward proxy. When millions of public users hit `api.netflix.com` and Nginx decrypts TLS and routes requests to internal microservices, that's a reverse proxy."
- **Possible Follow-up**: *"What is the difference between a Reverse Proxy and an API Gateway?"*

---

### Q1.3: What is the difference between TCP and UDP?
- **Short Answer**: TCP is connection-oriented, reliable, and guarantees in-order packet delivery via acknowledgments and handshakes; UDP is connectionless, unreliable, and fast with minimal packet overhead.
- **Conversational Explanation**: "We use TCP for web pages, file downloads, and databases where losing a single byte corrupts data. We use UDP for live video streaming, voice calls, and online multiplayer gaming where speed matters more than retransmitting a dropped frame from 2 seconds ago."
- **Possible Follow-up**: *"Why does HTTP/3 run on UDP instead of TCP?"*

---

### Q1.4: What is the difference between Horizontal and Vertical Scaling?
- **Short Answer**: Vertical scaling adds more CPU/RAM/SSD to a single machine (scale up); horizontal scaling adds more commodity machines to a pool behind a load balancer (scale out).
- **Conversational Explanation**: "Vertical scaling is simple and requires zero distributed system changes, but it has a hard hardware ceiling and represents a Single Point of Failure (SPOF). Horizontal scaling requires stateless services, but provides practically infinite scale and high fault tolerance."
- **Possible Follow-up**: *"What architectural property is required to make an application tier horizontally scalable?"* $\to$ It must be strictly **stateless** (sessions stored in external Redis/DB).

---

### Q1.5: What are the ACID properties in database management?
- **Short Answer**: Atomicity (all or nothing), Consistency (preserves schema constraints), Isolation (concurrent transactions execute without interference), Durability (committed writes survive crashes).
- **Conversational Explanation**: "In a bank transfer of $100 from Alice to Bob, Atomicity ensures we don't deduct Alice without crediting Bob; Consistency ensures account balances don't violate non-negative constraints; Isolation prevents concurrent transfers from creating race conditions; and Durability ensures the transaction persists on disk even if the power cuts 1 millisecond later."
- **Possible Follow-up**: *"What are the standard SQL Isolation Levels and what anomalies do they prevent?"*

---

## 🟡 Section 2: Intermediate Questions (Trade-offs & Architecture)

### Q2.1: How do you choose between SQL and NoSQL in an interview?
- **Short Answer**: Choose SQL when you require ACID transactions, structured schemas, and complex relational joins (Orders, Payments); choose NoSQL when you need massive horizontal write scaling, high availability (AP), flexible schemas, or key-value lookups (Sessions, Catalogs, Telemetry).
- **Conversational Explanation**: "I evaluate three criteria: first, **Data Structure** (relational vs document/key-value); second, **Transaction Integrity** (strict ACID vs eventual consistency); and third, **Write Scale** (will writes exceed a single SQL master?). In real-world systems, we practice **Polyglot Persistence**—using PostgreSQL for financial orders and Cassandra or Redis for time-series logs and sessions."
- **Possible Follow-up**: *"How do you handle relationships in a NoSQL database without foreign keys?"* $\to$ Denormalize data by embedding child documents or perform multi-query joins in the application layer.

---

### Q2.2: Explain the CAP Theorem with a real-world distributed example.
- **Short Answer**: In the event of a network partition ($P$), a distributed data system must choose between **Consistency ($CP$)** (refuse the write to prevent stale reads) or **Availability ($AP$)** (accept the write on isolated nodes, risking temporary inconsistency).
- **Conversational Explanation**: "Imagine two ATM database nodes in New York and London. If the transatlantic network cable breaks, a customer in London tries to withdraw money. A **CP system** (like PostgreSQL Master) returns an error because it cannot sync with NY, preserving 100% balance consistency at the cost of availability. An **AP system** (like Cassandra) dispenses the cash, remaining 100% available, and reconciles the account balance asynchronously when the network heals."
- **Possible Follow-up**: *"What is the PACELC theorem?"*

---

### Q2.3: What is the Cache-Aside pattern, and what happens on a Cache Miss?
- **Short Answer**: The application reads from the cache first; if the key is missing (Cache Miss), the app queries the database, writes the result to the cache with a TTL, and returns the response.
- **Conversational Explanation**: "Cache-Aside keeps the cache lean because only actually requested items enter memory. The trade-off is a latency penalty on the initial cache miss, and the risk of serving stale data if database updates don't properly invalidate or expire cache keys."
- **Possible Follow-up**: *"What is the difference between Cache-Aside and Write-Through caching?"*

---

### Q2.4: What is the difference between WebSockets and Server-Sent Events (SSE)?
- **Short Answer**: WebSockets are full-duplex and bidirectional over a custom TCP socket; SSE is unidirectional (server-to-client only) over standard persistent HTTP/2.
- **Conversational Explanation**: "If communication is strictly one-way—like streaming ChatGPT AI responses, stock tickers, or live sports scores—SSE is simpler, runs over standard HTTP/2, and has built-in browser reconnection. If communication requires real-time two-way messaging—like a multiplayer game or collaborative whiteboard—WebSockets are required."
- **Possible Follow-up**: *"How do you scale a WebSocket server horizontally across 10 instances?"* $\to$ Use a centralized **Redis Pub/Sub or Kafka message backplane** to route messages between WebSocket gateways.

---

### Q2.5: What is Database Sharding, and what are its main challenges?
- **Short Answer**: Sharding splits a massive database horizontally across multiple distinct database servers using a Shard Key.
- **Conversational Explanation**: "When a dataset exceeds 2TB or write throughput exceeds a single master's capacity, sharding divides rows by a shard key (e.g., `hash(user_id) % N`). The main challenges are: cross-shard `JOIN` queries become extremely slow or impossible, schema migrations become complex, and choosing a poor shard key causes uneven traffic hotspots."
- **Possible Follow-up**: *"How does Consistent Hashing minimize data migration when adding new shards?"*

---

## 🟣 Section 3: L3 Advanced Questions (Failures, Concurrency & Scale)

### Q3.1: How do you prevent a Cache Stampede (Thundering Herd) when a viral key expires?
- **Short Answer**: Use a Distributed Mutex Lock (via Redis `SETNX`) so only one thread queries the database and repopulates the cache, or use Probabilistic Early Expiration (XFetch).
- **Conversational Explanation**: "When a hot key expires during a live event, 50,000 requests miss the cache at the exact same millisecond and hammer the database. With a distributed lock, the first thread that misses the cache acquires a 5-second lock, fetches data from the DB, and updates Redis. The other 49,999 threads fail to get the lock, sleep for 50ms, and then read the freshly populated value directly from Redis."
- **Possible Follow-up**: *"What happens if the thread holding the lock crashes before updating the cache?"* $\to$ The lock must always have an automated TTL expiration (e.g., 5 seconds) to prevent permanent deadlocks.

---

### Q3.2: How do you guarantee Zero Double-Booking in a flash-sale ticketing platform?
- **Short Answer**: Combine a fast in-memory Redis distributed lock (`SETNX` with a 10-minute TTL) to absorb contention in RAM, followed by an atomic SQL update with Optimistic Concurrency (`WHERE status = 'AVAILABLE'`) or PostgreSQL `EXCLUDE` date range constraints.
- **Conversational Explanation**: "Pessimistic database locking (`SELECT FOR UPDATE`) exhausts DB connection pools within seconds under flash sales. By placing an atomic Redis Lua lock first, 99.9% of concurrent attempts fail in $< 1\text{ms}$ in RAM without touching SQL. Only the winning request executes the quick 5ms database reservation transaction."
- **Possible Follow-up**: *"How does the system release held seats if the user closes their browser without paying?"* $\to$ The 10-minute Redis TTL expires and an asynchronous delayed worker resets the seat status back to `AVAILABLE`.

---

### Q3.3: How does the Saga Pattern manage distributed transactions across microservices?
- **Short Answer**: A Saga replaces blocking Two-Phase Commit (2PC) with a sequence of local transactions; if any local transaction fails, the Saga executes **Compensating Transactions** in reverse order to undo prior state changes.
- **Conversational Explanation**: "In an e-commerce checkout involving Order, Inventory, and Payment services: Step 1 reserves inventory; Step 2 attempts to charge the customer's credit card. If the card is declined in Step 2, the Saga Orchestrator triggers a compensating action on the Inventory Service to release the held stock and marks the order as cancelled, achieving eventual consistency without distributed locks."
- **Possible Follow-up**: *"When do you choose Saga Orchestration over Saga Choreography?"* $\to$ Use Choreography for simple 2-service workflows; use Orchestration (central coordinator) for complex 4+ step workflows to prevent cyclic dependency chaos.

---

### Q3.4: How do you handle the "Celebrity Problem" (Hotspot) in a social media feed?
- **Short Answer**: Use a **Hybrid Fanout Model**: Fanout-on-write for regular users ($< 25k$ followers); Fanout-on-read (dynamic merge) for celebrity accounts.
- **Conversational Explanation**: "If a user with 50M followers posts, fanout-on-write attempts to write 50M timeline records to Redis, crashing worker queues. In a hybrid architecture, the celebrity's post is written to only 1 place. When a follower opens their home feed, the Feed Service reads their cached Redis timeline and merges the celebrity's recent posts on the fly in memory using a Min-Heap in $< 15\text{ms}$."
- **Possible Follow-up**: *"Why should Redis timelines store only post IDs rather than full post JSON objects?"* $\to$ Storing only 8-byte IDs saves over 85% RAM and makes post edits/deletions reflect instantly across all followers.

---

### Q3.5: How do you design an API to guarantee idempotency on financial transactions?
- **Short Answer**: Require the client to send a unique `Idempotency-Key` (UUID) in the request header, and use Redis atomic locking (`SETNX`) to enforce single execution.
- **Conversational Explanation**: "When a client sends `POST /payments` with `Idempotency-Key: uuid-123`, the API Gateway executes `SET lock:uuid-123 PROCESSING NX EX 120`. If `SETNX` succeeds, the backend processes the charge, writes the result to the DB, caches the final JSON response in Redis, and returns. If the client retries due to a network timeout, the second request detects the existing key and returns the cached payment response immediately without charging the card again."
- **Possible Follow-up**: *"What status code should be returned if a duplicate request arrives while the first request is still in the 'PROCESSING' state?"* $\to$ Return `HTTP 409 Conflict` or `HTTP 425 Too Early`.

---

### Q3.6: What happens if your Primary Database crashes in an Active-Passive setup?
- **Short Answer**: Automated health checks detect the failure, promote the synchronous standby replica to Primary, update internal DNS / routing endpoints, and spin up a new standby replica.
- **Conversational Explanation**: "Tools like AWS RDS Multi-AZ or Patroni for PostgreSQL run heartbeats every 2–5 seconds. If the primary fails 3 consecutive health probes, the coordinator initiates automated failover: it promotes the standby (which has zero data loss due to synchronous replication), updates the internal connection pool endpoint, and brings services back online within 30–60 seconds (RTO $< 1\text{ min}$, RPO $= 0$)."
- **Possible Follow-up**: *"What is a split-brain scenario during database failover, and how is it prevented?"* $\to$ Prevented via **Quorum Consensus** (a node is promoted only if a strict majority $\lfloor N/2 \rfloor + 1$ of nodes vote for it).
