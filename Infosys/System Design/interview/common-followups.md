# Common Interview Follow-ups & Failure Scenarios

In an **Infosys Specialist Programmer (SP) L3 interview**, interviewers frequently probe your architecture with emergency scenarios: *"What happens if component X fails?"*, *"How does it handle a $10\times$ spike?"*, *"Where is the bottleneck?"*.

Use these battle-tested, structured answers to navigate every emergency scenario with senior-level confidence.

---

## 1. "What happens if Redis goes down completely?"

### 🗣️ Good Conversational Answer:
> "First, we prevent single-node outages by deploying Redis in a **High-Availability Cluster with Redis Sentinel and Master-Replica replication across multiple Availability Zones**. If the master crashes, Sentinel automatically promotes a replica within 3 to 5 seconds.
> 
> Second, if the entire Redis tier becomes unreachable (catastrophic network outage), our application layer implements **Graceful Degradation and Fail-Open protection**:
> 1. **Circuit Breakers**: We trip a circuit breaker so application servers don't hang waiting for Redis connection timeouts.
> 2. **Fallback to Database with Rate Limiting**: Read requests fall back to querying the database directly, but we enforce strict token-bucket rate limiting at the API Gateway to prevent the database from melting.
> 3. **Non-Critical Features Disabled**: Features like live view counts or recent activity feeds are temporarily degraded or hidden until Redis recovers."

---

## 2. "What happens if the Primary Database crashes?"

### 🗣️ Good Conversational Answer:
> "We design the storage tier for automated zero-data-loss failover:
> 1. **Synchronous Standby Replication**: The Primary database continuously replicates synchronously to a standby instance in a secondary Availability Zone (Multi-AZ).
> 2. **Automated Health Check & Promotion**: Tools like AWS RDS Multi-AZ or Patroni/ZooKeeper monitor the primary via heartbeats. If the primary fails 3 consecutive probes (15 seconds), the coordinator automatically promotes the standby replica to become the new Primary.
> 3. **DNS / Connection Endpoint Update**: The database endpoint hostname switches to the new primary, and application connection pools seamlessly reconnect.
> 4. **Read Traffic Remains Intact**: Dedicated Read Replicas continue serving read traffic uninterrupted during the failover, achieving an **RTO $< 45\text{ seconds}$ and RPO $= 0$**."

---

## 3. "What happens during a sudden 10x traffic spike (e.g., Flash Sale / Breaking News)?"

### 🗣️ Good Conversational Answer:
> "We handle a $10\times$ traffic surge through four defensive layers:
> 1. **Edge Offloading**: 90%+ of static assets and cacheable public responses are absorbed at the **CDN Edge (Cloudflare)** before hitting origin servers.
> 2. **Edge Virtual Waiting Room**: If traffic exceeds provisioned backend capacity, an edge queue (Cloudflare Waiting Room / Token Bucket) holds incoming users and admits them at a steady rate of 2,000 users/minute.
> 3. **Horizontal Auto-Scaling**: The stateless application cluster auto-scales based on CPU utilization ($>70\%$) and HTTP request queue depth.
> 4. **Asynchronous Ingestion Buffering**: Write-heavy requests are pushed into **Apache Kafka / AWS SQS**, buffering traffic safely in the queue so background workers can process jobs at a steady, controlled pace without dropping transactions."

---

## 4. "Where is the bottleneck in your design, and what breaks first?"

### 🗣️ Good Conversational Answer:
> "Under extreme load, the first component to hit a bottleneck is almost always the **Database Write I/O (Disk IOPS and Lock Contention)**.
> 
> While stateless app servers and Redis cache scale horizontally with ease, the primary relational database has a finite write throughput on a single master.
> 
> If write volume surges beyond the primary master's IOPS capacity, our remediation steps are:
> 1. Buffer writes using **Kafka** and perform batch database inserts.
> 2. Move write-heavy non-transactional streams (like clickstreams or chat history) to an append-only LSM-tree database like **Cassandra / ScyllaDB**.
> 3. If transactional SQL writes exceed limits, we **Shard the PostgreSQL database horizontally** by `user_id` or `tenant_id` using Consistent Hashing."

---

## 5. "How do you prevent duplicate requests and double payments (Idempotency)?"

### 🗣️ Good Conversational Answer:
> "We enforce **Idempotency Keys** across the entire transaction lifecycle:
> 1. The client generates a unique UUID `Idempotency-Key: uuid-12345` in the HTTP header when submitting a payment.
> 2. The API Gateway executes an atomic Redis command: `SET lock:payment:uuid-12345 PROCESSING NX EX 120`.
> 3. If `SETNX` returns 0 (key exists), the system knows this request is a duplicate:
>    - If status is `PROCESSING`, return `409 Conflict` (Duplicate in-flight request).
>    - If status is `SUCCESS`, return the previously cached payment response immediately.
> 4. If `SETNX` succeeds, the backend processes the charge with Stripe, commits the database transaction, updates the Redis key with status `SUCCESS` + response body, and returns. This guarantees zero duplicate charges even if the user double-clicks or the network retries."

---

## 6. "How do you handle retries without causing a self-inflicted DDoS (Thundering Herd)?"

### 🗣️ Good Conversational Answer:
> "We strictly enforce **Exponential Backoff with Full Jitter**:
> 1. Never retry immediately in a tight while-loop.
> 2. On failure, wait with exponential delay: $100\text{ms} \to 200\text{ms} \to 400\text{ms} \to 800\text{ms}$.
> 3. Add **Full Jitter** (randomized noise):
>    $$\text{Sleep Time} = \text{random}(0, \text{BaseDelay} \times 2^{\text{attempt}})$$
> 4. Full jitter spreads out retry attempts across a time spectrum, preventing thousands of retrying mobile clients from synchronizing and hammering a recovering backend at the exact same millisecond.
> 5. We also cap the maximum retries to 3 attempts before routing permanently failed requests to a **Dead Letter Queue (DLQ)**."

---

## 7. "What happens if a downstream service partially fails or slows down?"

### 🗣️ Good Conversational Answer:
> "To prevent a single slow downstream dependency from causing cascading outages across the entire platform, we implement the **Circuit Breaker and Bulkhead Patterns**:
> 1. **Circuit Breakers (e.g., Resilience4j / Envoy)**: If a downstream recommendation service error rate exceeds 50% or response latency exceeds 2 seconds, the circuit breaker trips to `OPEN`. All subsequent calls fail fast within 1ms and return a fallback cached result without waiting for network timeouts.
> 2. **Bulkhead Isolation**: We allocate isolated thread pools and connection limits per downstream service. If the recommendation service stalls, it only exhausts its dedicated 20-thread pool, leaving the remaining 200 threads available for critical checkout and order services.
> 3. **Strict HTTP Client Timeouts**: We configure aggressive connect timeouts (500ms) and read timeouts (2s) on all outbound RPC calls."

---

## 8. "How do you migrate 1TB of production database data with zero downtime?"

### 🗣️ Good Conversational Answer:
> "We execute a **Dual-Write + CDC (Change Data Capture) Migration Strategy** in 5 phases:
> 
> ```mermaid
> flowchart LR
>     App[App Server] -->|1. Dual-Write to Old & New DB| OldDB[(Old DB)]
>     App -->|1. Dual-Write| NewDB[(New DB)]
>     OldDB -.->|2. Historical Backfill Migration| NewDB
> ```
> 
> 1. **Phase 1 (Dual-Write)**: Update application code to write all new `INSERT`, `UPDATE`, and `DELETE` operations to both the Old DB and New DB simultaneously (using asynchronous message queues to prevent slowing down requests).
> 2. **Phase 2 (Historical Backfill)**: Run a background batch script to migrate historical data created prior to the dual-write deployment.
> 3. **Phase 3 (Verification & Reconciliation)**: Run a reconciliation script to verify 100% data parity and checksum matches between both databases.
> 4. **Phase 4 (Read Cutover)**: Switch application read traffic from Old DB to New DB.
> 5. **Phase 5 (Deprecation)**: Stop writing to Old DB and decommission the old database cluster."

---

## 9. "How do you debug high p99 latency in a microservices architecture?"

### 🗣️ Good Conversational Answer:
> "We debug tail latency using **Distributed Tracing (OpenTelemetry / Jaeger)** and correlated structured logs:
> 1. **Correlation IDs**: The API Gateway attaches a unique `X-Trace-ID` header to every incoming request, which is passed down through all internal gRPC/REST service calls.
> 2. **Flame Graphs**: We inspect the Jaeger trace flame graph to pinpoint the exact microservice span taking the longest time.
> 3. **Common Root Causes We Investigate**:
>    - **Database Full Table Scans**: Checking `EXPLAIN ANALYZE` on SQL queries executed in that span.
>    - **Garbage Collection (GC) Pauses**: Checking JVM/Go runtime GC stop-the-world pause metrics.
>    - **Lock Contention & Thread Starvation**: Checking thread pool queue depths and connection pool wait times.
>    - **Cache Misses & Cold Starts**: Verifying Redis hit rates."

---

## 10. "How do you handle clock drift across distributed nodes?"

### 🗣️ Good Conversational Answer:
> "In distributed systems, physical machine clocks drift due to temperature and hardware variations (NTP sync can still leave 50–200ms offsets). Therefore, **we never rely on physical wall-clock timestamps for strict transaction ordering or concurrency decisions**:
> 1. **Logical Timestamps (Lamport / Vector Clocks)**: Used to establish causal ordering of events ($A \to B$) without trusting physical clocks.
> 2. **Monotonic Sequence IDs (Snowflake IDs / UUIDv7)**: Generate 64-bit unique IDs composed of `(timestamp + worker_id + sequence_counter)` where the sequence counter guarantees in-order monotonicity within each millisecond.
> 3. **Single Authoritative Sequencer**: For critical order transactions, a centralized coordinator (like PostgreSQL auto-increment sequence or Redis Lua script) assigns the authoritative monotonic sequence number."
