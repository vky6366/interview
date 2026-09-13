# System Design Trade-off Cheatsheet & Comparison Matrix

In a Senior / L3 System Design interview, **there are no perfect solutions, only trade-offs**. Use this cheat sheet to defend your architectural decisions and articulate what you gain vs what you sacrifice.

---

## 1. Storage & Database Trade-offs

### SQL vs NoSQL
| Dimension | SQL (PostgreSQL, MySQL) | NoSQL (Cassandra, MongoDB, DynamoDB) |
|---|---|---|
| **Data Schema** | Strict, structured, normalized tabular schema. | Dynamic, flexible, semi-structured (JSON/Key-Value). |
| **Transactions** | **Strict ACID** guarantees across multiple tables. | **BASE** (Basically Available, Soft-state, Eventual consistency). |
| **Joins** | Native relational `JOIN` operations. | No native joins (Denormalization / App-level joins). |
| **Scaling** | Vertical scale; Horizontal via Read Replicas & complex Sharding. | **Native horizontal scaling** across commodity clusters. |
| **Best Used For** | Financial ledgers, E-commerce checkout, User auth, Orders. | Time-series telemetry, Chat history, Catalogs, User sessions. |
| **L3 Trade-off Rule** | **Gain ACID integrity & joins $\longleftrightarrow$ Sacrifice horizontal write elasticity**. |

---

### Database Replication vs Sharding
| Dimension | Database Replication (Master-Replica) | Database Sharding (Horizontal Partitioning) |
|---|---|---|
| **Primary Goal** | **Scale Read Traffic & High Availability**. | **Scale Write Traffic & Massive Storage Volume**. |
| **Data Distribution** | Every replica holds an identical copy of the entire dataset. | Dataset is split across multiple servers using a Shard Key. |
| **Write Capacity** | Single Master remains the write bottleneck. | Writes scale linearly across all shard nodes. |
| **Complexity** | Low (Handled natively by database engines). | High (Requires Shard Router, Consistent Hashing, No Cross-Shard Joins). |
| **L3 Trade-off Rule** | **Always add Read Replicas first $\longleftrightarrow$ Resort to Sharding only when dataset $>2\text{TB}$ or write IOPS saturate**. |

---

### Optimistic Locking vs Pessimistic Locking
| Dimension | Optimistic Locking (`version` column) | Pessimistic Locking (`SELECT FOR UPDATE`) |
|---|---|---|
| **Mechanism** | Updates record only if `version` matches (`WHERE version = 1`). | Database physically locks the row until transaction commits. |
| **Concurrency** | Non-blocking; high throughput for low conflict. | Blocking; serializes transactions strictly. |
| **Failure Impact** | Fails and requires retry on collision. | Threads wait in queue; risks DB connection exhaustion & deadlocks. |
| **Best Used For** | Low-contention updates (Profile edits, Document saves). | Strict inventory checkouts, Bank balance deductions. |
| **L3 Trade-off Rule** | **Gain non-blocking throughput $\longleftrightarrow$ Sacrifice retry overhead under high contention**. |

---

## 2. Compute & Architectural Trade-offs

### Monolith vs Microservices vs Modular Monolith
| Dimension | Monolith | Microservices | Modular Monolith |
|---|---|---|---|
| **Deployment** | Single deployable binary / container. | 20+ independently deployable services. | Single deployable binary with strict internal module boundaries. |
| **Communication** | In-memory function calls (nanoseconds). | Network RPC calls (REST/gRPC: milliseconds). | In-memory module calls / events. |
| **Operational Overhead** | Low (Single deployment pipeline). | High (Requires Kubernetes, Distributed Tracing, Service Mesh). | Low-to-Moderate. |
| **Failure Domain** | Single bug can bring down entire app. | Faults isolated to individual microservice. | Single bug can crash process, but modular testing prevents it. |
| **Best For** | Small teams (<15 engineers), greenfield startups. | Large engineering orgs (50+ engineers, multiple squads). | Medium-to-large teams scaling without microservice complexity. |
| **L3 Trade-off Rule** | **Gain extreme simplicity & latency $\longleftrightarrow$ Sacrifice independent team deployment velocity**. |

---

### Horizontal Scaling vs Vertical Scaling
| Dimension | Vertical Scaling (Scale Up) | Horizontal Scaling (Scale Out) |
|---|---|---|
| **Mechanism** | Upgrade server to 128 cores, 512GB RAM, NVMe SSD. | Add 20 commodity instances behind a Load Balancer. |
| **Complexity** | Zero architectural changes; simple single box. | Requires stateless app tier, load balancers, and distributed sessions. |
| **Limits** | Hard hardware ceiling; expensive; Single Point of Failure. | Virtually unlimited linear scaling; high availability. |
| **Downtime** | Requires server downtime to upgrade CPU/RAM. | Zero downtime elastic scaling. |
| **L3 Trade-off Rule** | **Gain instant zero-code-change scaling $\longleftrightarrow$ Sacrifice fault tolerance & hit hard hardware ceiling**. |

---

## 3. Communication & Protocol Trade-offs

### Synchronous (REST/gRPC) vs Asynchronous (Event-Driven / Queues)
| Dimension | Synchronous (REST / gRPC) | Asynchronous (Kafka / RabbitMQ) |
|---|---|---|
| **Interaction** | Request-Response. Caller blocks and waits for reply. | Fire-and-Forget / Pub-Sub. Caller returns immediately. |
| **Coupling** | **Tight coupling** (Caller must know callee availability). | **Loose coupling** (Producer only emits events to broker). |
| **Failure Impact** | **Cascading failures** if downstream service is slow. | **Fault tolerant** (Events buffer safely in queue during outages). |
| **Consistency** | Immediate consistent response. | Eventual consistency (consumers process at own pace). |
| **L3 Trade-off Rule** | **Gain immediate user response $\longleftrightarrow$ Sacrifice resilience against cascading downstream failures**. |

---

### REST vs gRPC vs GraphQL
| Dimension | REST (over JSON) | gRPC (HTTP/2 + Protobuf) | GraphQL |
|---|---|---|---|
| **Data Format** | Human-readable JSON. | **Binary Protocol Buffers**. | JSON. |
| **Performance** | Moderate (Text serialization overhead). | **Ultra-Fast (7-10x faster; compact payload)**. | Moderate (Query parsing overhead). |
| **Streaming** | Limited (Chunked transfer / SSE). | **Native Bidirectional Streaming**. | Subscriptions (over WebSockets). |
| **Client Control** | Fixed endpoints (Over/Under-fetching). | Strict RPC method contract. | Client requests exact fields needed. |
| **Best Used For** | Public APIs, CRUD web services. | **Internal Microservice-to-Microservice RPC**. | Complex client UIs with nested relational data. |
| **L3 Trade-off Rule** | **gRPC gains 7x performance $\longleftrightarrow$ Sacrifices direct human readability & browser debugging**. |

---

### Polling vs Long Polling vs SSE vs WebSockets
| Technology | Direction | Protocol | Overhead | Best Use Case |
|---|---|---|---|---|
| **Short Polling** | Client $\to$ Server | HTTP | High (Repeated TCP handshakes). | Infrequent status checks. |
| **Long Polling** | Client $\to$ Server | HTTP | Moderate (Hangs until data arrives). | Fallback when WebSockets blocked by firewalls. |
| **Server-Sent Events (SSE)** | **Server $\to$ Client** | HTTP/2 | Low (Single persistent HTTP stream). | Live stock tickers, AI text streaming (ChatGPT). |
| **WebSockets** | **Bidirectional** | TCP (WSS) | **Ultra-Low (2-byte frame overhead)**. | Real-time chat, Multiplayer games, Co-editing. |
| **L3 Trade-off Rule** | **WebSockets gain full duplex $\longleftrightarrow$ Sacrifices stateless load balancing (requires session backplane)**. |

---

## 4. Performance & Caching Trade-offs

### Cache-Aside vs Write-Through vs Write-Behind
| Strategy | Read Flow | Write Flow | Pros | Cons / Trade-offs |
|---|---|---|---|---|
| **Cache-Aside (Lazy Loading)** | Read Cache $\to$ On miss read DB $\to$ Populate Cache. | Write directly to DB $\to$ Invalidate Cache. | Only caches requested data; safe against cache crashes. | **Cache Miss latency penalty**; risk of stale reads. |
| **Write-Through** | Read Cache $\to$ On miss read DB. | App writes to Cache $\to$ Cache synchronously writes to DB. | High data consistency; cache is always fresh. | **Higher write latency** (Must wait for both Cache and DB). |
| **Write-Behind (Write-Back)** | Read Cache. | App writes to Cache $\to$ Cache asynchronously flushes to DB. | **Ultra-low write latency**; absorbs massive write spikes. | **Data Loss Risk** if cache crashes before flushing to disk! |
| **L3 Trade-off Rule** | **Write-Behind gains extreme write throughput $\longleftrightarrow$ Sacrifices durability guarantees**. |

---

### Message Queue (RabbitMQ) vs Distributed Streaming Log (Apache Kafka)
| Dimension | RabbitMQ / AWS SQS | Apache Kafka |
|---|---|---|
| **Architecture** | Smart Broker, Dumb Consumer (Broker tracks delivery & ACK). | Dumb Broker, Smart Consumer (Broker is append-only log; consumer tracks offset). |
| **Message Deletion** | Deleted immediately after consumer ACK. | Persisted on disk for days/weeks; replayable from offset 0. |
| **Throughput** | High ($10k–50k\text{ msg/sec}$). | **Extreme ($1M+\text{ msg/sec}$ via sequential disk I/O & batching)**. |
| **Routing** | Complex routing (Exchange topics, direct, headers). | Topic + Partition Key routing. |
| **Best Used For** | Background worker tasks (Send email, generate PDF). | Event streaming, Clickstream logs, CDC, Event sourcing. |
| **L3 Trade-off Rule** | **Kafka gains 1M+ throughput & replayability $\longleftrightarrow$ Sacrifices simplicity & per-message routing**. |

---

## 5. Distributed Consistency & Reliability Trade-offs

### Strong Consistency vs Eventual Consistency
| Dimension | Strong Consistency (Linearizability) | Eventual Consistency (BASE) |
|---|---|---|
| **Guarantee** | Every read returns the absolute latest write immediately. | All replicas will eventually converge, but reads may temporarily return stale data. |
| **Latency** | Higher (Must synchronize across quorum nodes before returning). | Lower (Writes and reads return immediately from local node). |
| **Availability** | Lower (Rejects writes during network partitions). | Higher (Accepts writes on isolated nodes). |
| **Best Used For** | Bank transfers, Inventory checkout, Stock trading. | Social media feeds, Video view counts, DNS records. |
| **L3 Trade-off Rule** | **Strong consistency gains correctness $\longleftrightarrow$ Sacrifices latency and partition availability**. |

---

### Operational Transformation (OT) vs CRDTs
| Dimension | Operational Transformation (OT) | Conflict-free Replicated Data Types (CRDT) |
|---|---|---|
| **Architecture** | **Centralized Server Authority** (Transforms operation indices). | **Decentralized / P2P Friendly** (Unique fractional index per char). |
| **Memory Overhead** | **Zero memory bloat** (Stores plain text). | **High memory bloat** (1.5x–3x RAM; metadata per character). |
| **Implementation** | Complex transformation mathematical matrix. | Simpler data structure algorithms (Yjs, Automerge). |
| **Adoption** | **Google Docs, Microsoft Office Online**. | **Figma, Notion, Apple Notes, Linear**. |
| **L3 Trade-off Rule** | **OT gains light memory & central control $\longleftrightarrow$ Sacrifices offline peer-to-peer decentralization**. |
