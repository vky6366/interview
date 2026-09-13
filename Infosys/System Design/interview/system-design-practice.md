# System Design Practice — 20 Interview Prompts (Self-Drill Bank)

Use these 20 curated design prompts to practice executing the **4-Step Interview Framework** and **8-Step Design Playbook** independently. For each prompt, review the requirements, formulate your clarifying questions, sketch your baseline architecture on paper, identify what breaks first, and practice articulating your trade-offs aloud before checking the relevant case study notes.

---

## 🟢 Easy Prompts (Screening & Warm-Up)

### Prompt 01: Design a URL Shortener (e.g., TinyURL / Bitly)
- **Core Requirements**: Shorten a long URL to 7 alphanumeric characters; redirect short URLs to original URLs with low latency ($< 15\text{ms}$).
- **Questions to Ask**: What is the read-to-write ratio? Do short links expire? Are custom aliases allowed?
- **Key Components to Consider**: Load Balancer, Stateless App Servers, Key Generation Service (KGS), PostgreSQL, Redis Cache-Aside.
- **Main Bottlenecks**: Hash collision handling during key generation; Redis RAM exhaustion on viral links.
- **Likely L3 Follow-ups**: *"Why use a Key Generation Service instead of computing Base62(MD5(url)) at runtime?"*, *"Why choose HTTP 302 over HTTP 301?"*

---

### Prompt 02: Design Pastebin / Code Sharing Service
- **Core Requirements**: Users paste text/code snippets, receive a unique shareable URL, specify snippet expiration (1 hour, 1 day, never), and optionally set a password.
- **Questions to Ask**: What is the maximum paste size (e.g., 10MB)? How long should pastes be retained?
- **Key Components to Consider**: S3 Object Storage (for text blobs $> 64\text{KB}$), PostgreSQL / Cassandra (for metadata), Base62 Key Generator, Redis Cache.
- **Main Bottlenecks**: Database bloat if storing large text blobs directly in relational database rows.
- **Likely L3 Follow-ups**: *"Why should large code pastes be stored in S3 instead of SQL database columns?"*, *"How do you cleanly purge expired pastes without running expensive full-table scans?"*

---

### Prompt 03: Design a Distributed Rate Limiter
- **Core Requirements**: Enforce rate limits (e.g., max 100 requests/minute per client IP / API token) across a cluster of distributed API gateways.
- **Questions to Ask**: Should the rate limiter fail open or fail closed if the cache crashes? What is the penalty for exceeding limits (HTTP 429)?
- **Key Components to Consider**: API Gateway middleware, Redis (Token Bucket / Sliding Window Log), Local in-memory caching.
- **Main Bottlenecks**: Redis network latency hop on every single API request; race conditions when multiple concurrent requests update counters.
- **Likely L3 Follow-ups**: *"How does the Sliding Window Counter algorithm prevent traffic spikes at boundary edges?"*, *"How do you execute atomic rate limit checks in Redis using Lua scripts?"*

---

### Prompt 04: Design a Multi-Channel Notification Platform
- **Core Requirements**: Deliver high-priority alerts (2FA OTPs $< 2\text{s}$) and bulk marketing notifications across Push (APNS/FCM), SMS (Twilio), and Email (SendGrid).
- **Questions to Ask**: How do we handle user quiet hours? What happens if a third-party vendor experiences an outage?
- **Key Components to Consider**: Ingestion API, Redis Atomic Deduplication, Priority Kafka Queues (High vs Low), Channel Workers, Dead Letter Queues (DLQ).
- **Main Bottlenecks**: Low-priority marketing blasts delaying urgent 2FA codes; duplicate SMS sends during network retries.
- **Likely L3 Follow-ups**: *"Why is physical queue isolation necessary for OTPs vs marketing?"*, *"How do you implement vendor circuit breaking and automatic failover?"*

---

## 🟡 Medium Prompts (Core L3 Interview Level)

### Prompt 05: Design a Real-Time Chat Application (e.g., WhatsApp / Slack)
- **Core Requirements**: 1-on-1 and group messaging (up to 500 members), online presence heartbeats, delivery receipts (`SENT`, `DELIVERED`, `READ`), offline push notifications.
- **Questions to Ask**: Is message history synced across multiple devices? Are messages end-to-end encrypted?
- **Key Components to Consider**: L4 Network Load Balancer, WebSocket Gateways, Redis Session Registry, Apache Kafka, Cassandra / ScyllaDB message store, Presence Service.
- **Main Bottlenecks**: Managing millions of persistent, long-lived TCP socket connections; message fanout in large groups.
- **Likely L3 Follow-ups**: *"Why use Cassandra instead of PostgreSQL for chat history?"*, *"How does presence tracking work without crashing databases with heartbeat writes?"*

---

### Prompt 06: Design a Social Media News Feed (e.g., Twitter / Instagram)
- **Core Requirements**: Users publish posts with text/images, follow other users, and scroll through an aggregated chronological/ranked home feed.
- **Questions to Ask**: What is the read-to-write ratio? How do we handle celebrity accounts with 50M+ followers?
- **Key Components to Consider**: Feed Generation Workers, Redis Sorted Sets (`ZSET`) for timelines, Kafka, Cassandra (Post Store), PostgreSQL (Follow Graph), CDN.
- **Main Bottlenecks**: Fanout-on-write stampedes when celebrities post; feed generation latency for users following thousands of accounts.
- **Likely L3 Follow-ups**: *"Explain the Hybrid Fanout architecture for celebrities vs regular users."*, *"Why store only post IDs in Redis timelines instead of full post JSON objects?"*

---

### Prompt 07: Design a Flash-Sale Ticket Booking System (e.g., BookMyShow / Ticketmaster)
- **Core Requirements**: Real-time seat map viewing, 10-minute temporary seat hold during checkout, payment confirmation, and guaranteed zero double-booking during flash sales.
- **Questions to Ask**: How long is the hold timer? What happens if payment times out?
- **Key Components to Consider**: Edge Virtual Waiting Room, Redis Distributed Lock (`SETNX` with 10-min TTL), PostgreSQL (Optimistic Locking + GiST constraints), Payment Saga.
- **Main Bottlenecks**: Database connection pool exhaustion caused by long-running locks; race conditions on popular front-row seats.
- **Likely L3 Follow-ups**: *"Why shouldn't we use pessimistic `SELECT ... FOR UPDATE` in SQL for a 10-minute hold?"*, *"How does the system automatically release expired held seats back to the public pool?"*

---

### Prompt 08: Design an E-Commerce Platform (e.g., Amazon / Flipkart)
- **Core Requirements**: Product catalog search, shopping cart management, inventory deduction with zero overselling, and distributed payment saga execution.
- **Questions to Ask**: How is stock held during checkout? How do we prevent duplicate charges?
- **Key Components to Consider**: ElasticSearch (Catalog), Redis (Cart & Atomic Stock Counters), PostgreSQL (Orders & Inventory), Saga Orchestrator over Kafka.
- **Main Bottlenecks**: Inventory row lock contention on viral products; distributed transactions across isolated microservice databases.
- **Likely L3 Follow-ups**: *"Explain how the Saga pattern executes compensating transactions when payment fails."*, *"How do idempotency keys prevent double billing?"*

---

### Prompt 09: Design Cloud File Storage & Synchronization (e.g., Dropbox / Google Drive)
- **Core Requirements**: Upload/download large files (up to 50GB), cross-device automatic sync, delta sync (only upload modified chunks), file versioning, and resumable uploads.
- **Questions to Ask**: What is the chunk size? How do we detect file changes on the client desktop?
- **Key Components to Consider**: Client Sync Daemon, 4MB Chunking + SHA-256 Hashing, Pre-signed AWS S3 direct uploads, PostgreSQL (Metadata & Chunk mappings), WebSocket Sync Gateway.
- **Main Bottlenecks**: Uploading large multi-gigabyte files through application servers; bandwidth waste when modifying small file sections.
- **Likely L3 Follow-ups**: *"How does content-addressable storage enable global deduplication across multiple users?"*, *"How do you handle concurrent offline edits to the same document on two devices?"*

---

### Prompt 10: Design a Distributed Web Crawler
- **Core Requirements**: Crawl billions of web pages recursively from seed URLs, parse HTML, extract links, respect `robots.txt` and domain politeness, and store raw documents.
- **Questions to Ask**: What is the crawling refresh rate? How do we handle crawler traps and duplicate mirror pages?
- **Key Components to Consider**: URL Frontier (Priority & Politeness Queues), In-Memory Bloom Filter (URL dedup), SimHash content fingerprinting, Distributed Blob Store (S3/HDFS).
- **Main Bottlenecks**: DNS resolution bottleneck; getting trapped in infinite dynamic URL loops.
- **Likely L3 Follow-ups**: *"How does the URL Frontier enforce domain-level politeness delays?"*, *"How does a Bloom filter achieve 10-billion URL deduplication in just 12GB of RAM?"*

---

### Prompt 11: Design a Distributed In-Memory Key-Value Store (Redis Clone)
- **Core Requirements**: $O(1)$ sub-millisecond `GET` and `SET` operations, TTL expiration, eviction policies (LRU), and data durability snapshots.
- **Questions to Ask**: Is data single-threaded or multi-threaded? What durability guarantees are needed (RDB snapshots vs AOF logs)?
- **Key Components to Consider**: Hash Table, Doubly Linked List (for LRU eviction), Non-blocking I/O multiplexer (`epoll`), Append-Only File (AOF) logger, Master-Replica sync.
- **Main Bottlenecks**: Memory fragmentation; lock contention if implemented with multithreading.
- **Likely L3 Follow-ups**: *"Why does Redis use a single-threaded event loop for command execution?"*, *"How does LRU eviction operate efficiently in constant $O(1)$ time?"*

---

### Prompt 12: Design a Proximity Service / Nearby Places (e.g., Yelp / Google Maps Places)
- **Core Requirements**: Search for nearby businesses (e.g., "Find coffee shops within 3km"), view business profiles and ratings, and add new places.
- **Questions to Ask**: Are business locations static or dynamic? What is the search QPS?
- **Key Components to Consider**: Geospatial Indexing (Uber H3 / QuadTree / GeoHash / PostGIS), Redis Geospatial Cache, PostgreSQL (Business Profiles), Read Replicas.
- **Main Bottlenecks**: Slow SQL queries calculating Euclidean distance math across millions of coordinates.
- **Likely L3 Follow-ups**: *"Compare GeoHash vs QuadTrees vs Uber H3 Hexagons for spatial proximity searches."*, *"How do you handle grid boundary / edge disconnection issues in GeoHash?"*

---

## 🟣 Level 3 Advanced Prompts (High-Complexity Systems)

### Prompt 13: Design a Taxi Hailing & Dispatch Platform (e.g., Uber / Lyft)
- **Core Requirements**: Ingest 125,000 driver GPS pings/sec, perform real-time proximity matching ($< 5\text{km}$ radius) in $< 1\text{s}$, compute dynamic surge pricing, and live track trips.
- **Questions to Ask**: What is the driver GPS ping interval? How do we ensure a driver is not matched with two riders simultaneously?
- **Key Components to Consider**: WebSocket Location Ingestion Gateway, Uber H3 Hexagonal spatial index in Redis, Redis Distributed Lock (15s driver offer state machine), PostgreSQL (Trips), Kafka.
- **Main Bottlenecks**: 125k writes/sec saturating database disks; lock contention on driver assignment during peak rush hours.
- **Likely L3 Follow-ups**: *"Why are hexagonal grids (H3) superior to square grids for proximity search?"*, *"How is dynamic surge pricing calculated per geographical cell in real-time?"*

---

### Prompt 14: Design a Global Video Streaming Platform (e.g., YouTube / Netflix)
- **Core Requirements**: Multi-gigabyte video uploads, asynchronous distributed video transcoding pipeline (DAG engine), Adaptive Bitrate Streaming (HLS/DASH), and global CDN video delivery.
- **Questions to Ask**: What video codecs and resolutions are supported? How do we prevent video playback buffering on poor networks?
- **Key Components to Consider**: Pre-signed S3 Multipart Uploads, GPU Transcoding Worker Pool (FFmpeg), HLS `.m3u8` Playlist & 6-second `.ts` chunks, Global CDN Edge, Redis HyperLogLog (View counter).
- **Main Bottlenecks**: Long transcoding durations for 4K video; massive egress bandwidth costs during viral streaming events.
- **Likely L3 Follow-ups**: *"Explain how Adaptive Bitrate Streaming switches video quality mid-stream without buffering."*, *"How do you count 100M daily views without overwhelming SQL databases?"*

---

### Prompt 15: Design a Web Search Engine (e.g., Google Search)
- **Core Requirements**: Crawl 10 Billion pages, build a distributed Inverted Index, rank results using TF-IDF and PageRank principles, and execute multi-keyword queries in $< 100\text{ms}$.
- **Questions to Ask**: How fresh must search results be? What is the query QPS?
- **Key Components to Consider**: Distributed Crawler, Bloom Filters, Distributed Inverted Index (Document-Partitioned), PageRank Link Graph Engine, Redis Top-20% Query Cache.
- **Main Bottlenecks**: Network shuffle latency during multi-word posting list intersections across distributed shards.
- **Likely L3 Follow-ups**: *"Explain the trade-offs between Document-Partitioned vs Term-Partitioned Inverted Indexes."*, *"How does the system return search results in under 50ms for broad, common search terms?"*

---

### Prompt 16: Design a Real-Time Collaborative Document Editor (e.g., Google Docs / Figma)
- **Core Requirements**: Multiple concurrent editors on a single document, $< 100\text{ms}$ keystroke synchronization, live cursor tracking, conflict resolution with guaranteed convergence, and offline sync.
- **Questions to Ask**: Does the system use Operational Transformation (OT) or CRDTs? How is revision history maintained?
- **Key Components to Consider**: WebSocket Gateways, Centralized Document Session Coordinator (OT Engine), Cassandra (Append-only Operation Log), S3 (Periodic Snapshots), Redis (Cursors).
- **Main Bottlenecks**: Operation transformation CPU overhead on a single hot document with 100+ simultaneous typists.
- **Likely L3 Follow-ups**: *"What is the core difference between Operational Transformation (OT) and CRDTs?"*, *"How does document snapshotting prevent replaying millions of historical operations on document load?"*

---

### Prompt 17: Design a Real-Time Live Auction Platform (e.g., eBay Live)
- **Core Requirements**: High-concurrency live bidding, sub-millisecond atomic bid evaluation, live bid price broadcast ($< 200\text{ms}$), anti-sniping dynamic timer extension, and payment escrow.
- **Questions to Ask**: How are bids serialized? What happens if a bid is placed with 2 seconds remaining?
- **Key Components to Consider**: Redis Master (Single-threaded Lua script for atomic bid evaluation and anti-sniping extension), Redis Pub/Sub, WebSocket Broadcast Gateways, PostgreSQL (Audit Ledger), Kafka.
- **Main Bottlenecks**: Lock contention and race conditions on the highest bid in the final 5 seconds of the auction.
- **Likely L3 Follow-ups**: *"Why use an atomic Redis Lua script instead of SQL database transactions for bidding?"*, *"How do you prevent malicious bidders from manipulating client device clocks?"*

---

### Prompt 18: Design a Distributed Time-Series Metrics & Monitoring System (e.g., Datadog / Prometheus)
- **Core Requirements**: Ingest millions of metric data points per second `(metric_name, timestamp, value, tags)`, execute time-window aggregation queries (`avg`, `p99`, `sum`), and trigger alerts.
- **Questions to Ask**: What is the metric retention policy? Are metrics downsampled over time?
- **Key Components to Consider**: Metric Ingestion Agent (UDP / gRPC), Kafka buffer, Time-Series Database (ClickHouse / InfluxDB / Cassandra), In-Memory Rollup Engine, Alert Evaluator.
- **Main Bottlenecks**: Massive write IOPS from millions of servers; high cardinality tags causing index memory explosion.
- **Likely L3 Follow-ups**: *"Why are Columnar / Time-Series storage engines optimal for metrics?"*, *"How does data downsampling (e.g., roll up 1-second raw points to 1-minute averages after 7 days) save petabytes of storage?"*

---

### Prompt 19: Design a Global Payment Gateway & Transaction Ledger (e.g., Stripe)
- **Core Requirements**: Process credit card payments, enforce double-entry bookkeeping ledger, support idempotency across network retries, and reconcile bank settlements with zero data loss.
- **Questions to Ask**: What is the consistency requirement (ACID vs Eventual)? How do we handle partial failures with third-party banking networks?
- **Key Components to Consider**: API Gateway (Idempotency Key validation), Double-Entry Accounting Ledger (Immutable append-only SQL tables), Payment Orchestration State Machine, Vault (PCI-DSS tokenization), Bank Settlement Batch Workers.
- **Main Bottlenecks**: Distributed lock contention on user account balances; network timeouts during bank clearing calls.
- **Likely L3 Follow-ups**: *"Why is Double-Entry Bookkeeping mandatory in financial systems?"*, *"How do you design a database schema where money can NEVER be created or destroyed out of thin air?"*

---

### Prompt 20: Design a Distributed Message Broker (Apache Kafka Clone)
- **Core Requirements**: High-throughput distributed publish-subscribe messaging, partitioned commit log, persistent disk storage, consumer group offset tracking, and message replayability.
- **Questions to Ask**: What is the message retention policy? How is partition leader election handled?
- **Key Components to Consider**: Distributed Append-Only Commit Log, Zero-Copy OS Network Transfer (`sendfile`), Partition Leader Election (Raft / ZooKeeper / KRaft), Consumer Offset Storage.
- **Main Bottlenecks**: Disk I/O bottlenecks if using random writes; network bandwidth saturation during massive multi-consumer fanout.
- **Likely L3 Follow-ups**: *"How does Kafka achieve millions of messages/sec using Sequential Disk I/O and Zero-Copy OS memory transfers?"*, *"What happens when a partition leader broker crashes?"*
