# Case Study 02 — Ticket Booking System (e.g., BookMyShow / Ticketmaster)

## 1. Problem
Design a real-time ticket booking platform for high-demand concerts, movies, and sports events. The system must handle massive flash-sale traffic spikes (e.g., 500,000 users attempting to book 50,000 seats simultaneously) while **strictly preventing double-booking** and releasing unpurchased reserved seats after a 10-minute payment timeout.

---

## 2. Functional Requirements
1. **Browse & Search**: Users can search for events by city, genre, and date.
2. **Real-time Seat Map**: Users can view the venue layout with live seat availability statuses (`AVAILABLE`, `HELD`, `BOOKED`).
3. **Seat Reservation (Hold)**: A user can select up to 6 seats and place a **temporary 10-minute hold**.
4. **Checkout & Payment**: User completes payment within 10 minutes to permanently confirm the booking.
5. **Auto-Release Expired Holds**: If payment is not completed within 10 minutes, held seats are automatically returned to `AVAILABLE` status.

---

## 3. Non-Functional Requirements
1. **Strict Data Consistency (No Double Booking)**: Two users must NEVER be able to purchase the same physical seat.
2. **High Concurrency & Flash-Sale Resilience**: Handle $100\times$ traffic surges when tickets go on sale.
3. **Low Latency Browsing**: Event search and seat map rendering $< 50\text{ms}$.
4. **Fault Tolerance & Reliability**: Zero lost payments or lost confirmed tickets.

---

## 4. Assumptions & Constraints
- Large stadium capacity: 50,000 seats.
- Peak flash sale: 100,000 active users attempting to reserve seats in the first 60 seconds.
- Payment processing takes between 15 to 45 seconds.

---

## 5. Practical Scale Estimation

### Traffic Calculations
- **Active Event Browse RPS**: 20,000 reads/sec during a major flash sale launch.
- **Reservation Write RPS**: 5,000 concurrent seat hold requests/sec.
- **Confirmed Booking RPS**: Max 50,000 total tickets sold across 15 minutes $\approx 55\text{ writes/sec}$.

### Storage Estimation (5 Years)
- 1,000 venues $\times$ 500 events/year = 500,000 events/year.
- Each event has ~10,000 seats $\to 5\text{ Billion seat booking records}$ over 5 years.
- At 100 bytes per booking record $\to \approx 500\text{ GB}$ (Easily handled with PostgreSQL partitioning).

---

## 6. API Design

### 1. View Seat Map
- **Endpoint**: `GET /api/v1/events/{event_id}/seats`
- **Response** (`200 OK`):
```json
{
  "event_id": "evt_101",
  "seats": [
    {"seat_id": "A1", "status": "AVAILABLE", "price": 120},
    {"seat_id": "A2", "status": "HELD", "price": 120},
    {"seat_id": "A3", "status": "BOOKED", "price": 120}
  ]
}
```

### 2. Hold Seats (Temporary 10-Minute Lock)
- **Endpoint**: `POST /api/v1/bookings/hold`
- **Request Body**:
```json
{
  "event_id": "evt_101",
  "seat_ids": ["A1", "A2"],
  "user_id": "usr_99"
}
```
- **Response** (`200 OK`):
```json
{
  "reservation_id": "res_888",
  "held_until": "2026-09-11T19:30:00Z",
  "status": "HELD"
}
```
- **Response on Conflict** (`409 Conflict`):
```json
{
  "error": "SEATS_UNAVAILABLE",
  "message": "Seat A1 is already held by another user."
}
```

### 3. Confirm & Pay
- **Endpoint**: `POST /api/v1/bookings/confirm`
- **Headers**: `Idempotency-Key: 9b1deb4d-3b7d-4bad`
- **Request Body**:
```json
{
  "reservation_id": "res_888",
  "payment_token": "tok_stripe_444"
}
```

---

## 7. Data Model

### PostgreSQL Relational Schema
```sql
CREATE TYPE seat_status AS ENUM ('AVAILABLE', 'HELD', 'BOOKED');

CREATE TABLE seats (
    seat_id VARCHAR(32) NOT NULL,
    event_id VARCHAR(32) NOT NULL,
    row_num VARCHAR(8),
    seat_num INT,
    price DECIMAL(10, 2) NOT NULL,
    status seat_status DEFAULT 'AVAILABLE',
    held_by_user_id VARCHAR(64),
    held_until TIMESTAMP WITH TIME ZONE,
    version INT DEFAULT 1, -- For Optimistic Locking
    PRIMARY KEY (event_id, seat_id)
);

CREATE INDEX idx_seats_event_status ON seats(event_id, status);

CREATE TABLE bookings (
    booking_id VARCHAR(64) PRIMARY KEY,
    user_id VARCHAR(64) NOT NULL,
    event_id VARCHAR(32) NOT NULL,
    total_amount DECIMAL(10, 2) NOT NULL,
    status VARCHAR(32) NOT NULL, -- 'PENDING', 'CONFIRMED', 'CANCELLED'
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);
```

---

## 8. High-Level Architecture

```mermaid
flowchart TD
    Client[Mobile / Web Client] --> WAF["Cloudflare / WAF (Virtual Waiting Room Queue)"]
    WAF --> ALB[Application Load Balancer]
    
    subgraph AppCluster["Stateless Booking Services"]
        App1[Booking Service 1]
        App2[Booking Service 2]
    end
    
    ALB --> App1
    ALB --> App2
    
    subgraph DistributedLockTier["Distributed In-Memory Lock & Cache"]
        RedisCluster[("Redis Cluster (Distributed Locks with 10-min TTL)")]
    end
    
    subgraph DB_Tier["ACID Transactional Database"]
        DB_Master[("PostgreSQL Master (Pessimistic/Optimistic Concurrency)")]
        DB_Replica[("PostgreSQL Read Replica (Search & Browse)")]
    end
    
    subgraph AsyncPipeline["Async Expiration & Event Broker"]
        Kafka[Apache Kafka]
        DelayWorker[Hold Expiration Worker (Redis Delayed Queue / TTL)]
        PaymentWorker[Payment Processing Saga]
    end

    App1 <--> RedisCluster
    App2 <--> RedisCluster
    
    App1 --> DB_Master
    App2 --> DB_Master
    
    DB_Master -->|Streaming Replication| DB_Replica
    
    App1 -.->|Publish Event| Kafka
    Kafka -.-> PaymentWorker
    RedisCluster -.->|Key Expiration Event| DelayWorker
    DelayWorker -->|Reset Seat Status to AVAILABLE| DB_Master
```

---

## 9. Request / Data Flow

### The Critical Seat Hold Flow:
1. User selects seats `[A1, A2]` for `evt_101`.
2. **Fast Distributed Lock in Redis**:
   - Booking service executes atomic Redis Lua script:
     `SET lock:evt_101:A1 user_99 NX EX 600` (Sets lock with 10-minute expiration).
   - If Redis lock fails $\to$ Return `409 Conflict` immediately in $< 2\text{ms}$ without touching the database!
3. **Database Transaction (ACID)**:
   - If Redis lock succeeds, service begins PostgreSQL transaction with **Optimistic Locking**:
     ```sql
     UPDATE seats 
     SET status = 'HELD', held_by_user_id = 'user_99', held_until = NOW() + INTERVAL '10 minutes', version = version + 1
     WHERE event_id = 'evt_101' AND seat_id IN ('A1', 'A2') AND status = 'AVAILABLE';
     ```
   - If row count updated $= 2$, commit transaction and return `200 OK` with `reservation_id`.
4. User is redirected to Payment page with a 10-minute live countdown timer.

### The Payment & Confirm Flow:
1. User enters payment and clicks "Confirm".
2. Payment service charges payment gateway using `Idempotency-Key`.
3. Upon success, executes:
   ```sql
   UPDATE seats SET status = 'BOOKED' WHERE event_id = 'evt_101' AND seat_id IN ('A1', 'A2');
   INSERT INTO bookings VALUES (...);
   ```
4. Deletes temporary Redis hold lock.

### The Expired Hold Release Flow:
- If 10 minutes elapse without payment:
  - Redis key expires automatically.
  - A background cron/delayed worker queries `held_until < NOW() AND status = 'HELD'`, updating status back to `AVAILABLE`.

---

## 10. Concurrency Control: Optimistic vs Pessimistic Locking

| Method | Mechanism | Pros | Cons / L3 Decision |
|---|---|---|---|
| **Pessimistic Locking (`SELECT FOR UPDATE`)** | Database locks the physical seat rows until the transaction ends. | Guarantees zero double-booking at DB level. | ❌ **Connection Starvation**: Holding DB connections for 10 minutes will exhaust the DB connection pool in seconds! |
| **Optimistic Locking (`version` column)** | Checks if `version` matches before updating (`WHERE version = 1`). | Non-blocking, high throughput for low conflict. | ❌ Under high flash-sale contention, 99% of updates fail and roll back. |
| **Hybrid Approach (Redis Distributed Lock + Optimistic DB Update - RECOMMENDED)** | **Redis atomic lock (`SETNX`) absorbs 99.9% of contention in RAM** with a 600s TTL. Only the winner touches PostgreSQL. | ✅ Sub-millisecond conflict resolution; protects DB connection pool; guarantees strict ACID. | Requires managing Redis lock lifecycle. |

---

## 11. Database Choice: Why SQL over NoSQL?
- **Strict ACID Transactions are Mandatory**: Over-booking or lost ticket records directly cause legal and financial liability.
- **Relational Integrity**: Clear foreign-key relationships between `Venues`, `Events`, `Seats`, `Users`, and `Bookings`.
- **PostgreSQL** provides excellent row-level concurrency, JSON support, and read-replica scaling for event browsing.

---

## 12. Caching & Virtual Waiting Room (Flash-Sale Protection)
1. **Virtual Waiting Room (Queue-IT / Cloudflare Workers)**:
   - When 500,000 users arrive at 10:00 AM, the edge queue admits only 1,000 users/minute into the booking flow using token bucket admission.
   - Prevents backend infrastructure from melting.
2. **Redis Seat Map Caching**:
   - Seat map status is cached in Redis Bitmaps or Hash maps (`HGETALL evt_101:seats`).
   - Browsing users read seat maps directly from Redis, generating zero SQL reads.

---

## 13. Scaling Strategy ($1K \to 100K \to 10M$ Users)
- **1,000 Users**: Single PostgreSQL instance with basic `SELECT FOR UPDATE`.
- **100,000 Users**:
  - Virtual waiting room at Cloudflare edge.
  - Redis Cluster for distributed locks and fast seat status cache.
  - PostgreSQL Master for writes + 3 Read Replicas for event search and catalog.
- **10,000,000 Users**:
  - Database Partitioning by `event_id` (each event's seats live in isolated table partitions).
  - Multi-region CDN for static seat map layouts and event details.

---

## 14. Reliability & Failure Scenarios
- **What if a user closes the browser while holding seats?** $\to$ The 10-minute Redis TTL and DB background worker automatically reset the seats to `AVAILABLE` after 10 minutes.
- **What if the Payment Gateway is slow?** $\to$ If payment webhook arrives at minute 11, the system checks if the seat was already released and re-booked. If re-booked, the system automatically triggers a full refund.

---

## 15. Performance Optimizations
- **Redis Bitmaps for Seat Map**: Represent 50,000 seats as a 50,000-bit string (only **6.25 KB of RAM** per event!). `0 = AVAILABLE`, `1 = BOOKED`.

---

## 16. Security Considerations
- **Anti-Bot & Scalping Protection**: Cloudflare Turnstile / CAPTCHA before entering seat selection. Max 6 tickets per user ID.
- **Idempotency**: Prevent duplicate credit card charges via `Idempotency-Key` headers.

---

## 17. Key Trade-offs
- **Virtual Waiting Room vs Direct Access**: Sacrificed immediate instant entry in exchange for 100% backend uptime and zero crashes during flash sales.
- **Hybrid Redis Locks vs Pure SQL Locks**: Sacrificed architectural simplicity in exchange for protecting database connection pools from exhaustion.

---

## 18. Bottlenecks (What Breaks First?)
- **The First Bottleneck**: **Database lock contention on popular seats** (e.g., VIP Row 1).
- *Fix*: The Redis distributed lock layer absorbs contention in RAM before requests ever hit the database.

---

## 19. Interview Follow-ups & Conversational Answers

### Interviewer: "Why shouldn't we use pessimistic locking (`SELECT ... FOR UPDATE`) in the database for the 10-minute hold?"
> **Good Answer**: "Pessimistic locking holds open an active database connection and row lock for the entire duration of the hold. If 5,000 users hold seats for 10 minutes, the database connection pool (typically 200–500 connections) will be completely exhausted within seconds, freezing the entire platform. Instead, we use Redis distributed locks with a 10-minute TTL and write the timestamp to PostgreSQL in a quick 5ms transaction."

### Interviewer: "What happens if the server crashes right after charging the user's card but before marking the seat as BOOKED?"
> **Good Answer**: "We use the Saga Pattern with a Payment Webhook listener and database transaction logging. When Stripe charges the card, it emits an asynchronous webhook `payment_intent.succeeded` to Kafka. The webhook worker verifies the booking status and completes the DB update. If the seat hold expired and was taken, the worker automatically invokes Stripe's Refund API to return the user's money."

---

## 20. 2-Minute Interview Verbal Script
> "To design a high-concurrency ticket booking platform like BookMyShow handling flash-sale surges:
> 
> The biggest challenge is **preventing double-booking without exhausting database connections**.
> 
> At the ingress layer, I introduce an **Edge Virtual Waiting Room** to throttle flash-sale surges and admit users in fair queued batches.
> 
> For seat reservation, I implement a **Hybrid Concurrency Model**: When a user selects seats, the service first executes an atomic Redis Lua script (`SETNX` with a 10-minute TTL). This absorbs 99% of race conditions in memory in sub-milliseconds. Once the Redis lock is acquired, we execute a fast 5ms ACID transaction in PostgreSQL with an expiration timestamp (`held_until = NOW() + 10 mins`).
> 
> The user gets 10 minutes to pay. If payment succeeds with an idempotency key, we mark the seat `BOOKED` and remove the Redis lock. If the timer expires, a delayed worker automatically resets the seat back to `AVAILABLE`."

---

## Reusable Patterns Extracted

| Pattern | Why It Was Used | Other Systems Where It Applies |
|---|---|---|
| **Edge Virtual Waiting Room** | Smooths out sudden $100\times$ flash-sale spikes into a steady stream. | Sneaker drops, Black Friday e-commerce, Airline ticket releases. |
| **Temporary Distributed Hold (TTL Lock)** | Locks inventory temporarily without exhausting DB connections. | Hotel room booking, Uber ride reservation, Rental cars. |
| **Idempotent Payment Webhooks** | Guarantees eventual consistency between payment gateway and order state. | E-commerce checkout, SaaS subscription billing, Ride hailing. |
| **Bitmap State Representation** | Represents thousands of binary states (available/booked) in mere kilobytes. | Feature flags, User online presence, Permission bitmasks. |
