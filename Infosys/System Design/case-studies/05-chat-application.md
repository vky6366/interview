# Case Study 05 — Real-Time Chat Application (e.g., WhatsApp / Slack / Discord)

## 1. Problem
Design a distributed real-time chat application supporting 1-on-1 messaging, group chats (up to 500 members), online presence status (Online/Offline/Last Seen), message delivery receipts (`SENT`, `DELIVERED`, `READ`), and offline push notification fallbacks for 50 million concurrent connected users.

---

## 2. Functional Requirements
1. **1-on-1 Messaging**: Low-latency bidirectional real-time text and media messaging.
2. **Group Messaging**: Group chats supporting up to 500 participants.
3. **Presence System**: Real-time display of user online status and "Last Seen" timestamps.
4. **Message Status Receipts**: Track `SENT` (one tick), `DELIVERED` (two grey ticks), and `READ` (two blue ticks).
5. **Offline Delivery**: Messages sent to offline users are stored durably and delivered automatically when they reconnect.
6. **Chat History Synchronization**: Sync conversation history across multiple devices (mobile, web, desktop).

---

## 3. Non-Functional Requirements
1. **Ultra-Low Latency**: Message delivery latency $< 100\text{ms}$ when recipient is online.
2. **High Availability ($99.99\%$)**: Connection drops must reconnect seamlessly with zero lost messages.
3. **Strict In-Order Message Delivery**: Messages within a conversation must be displayed in the exact order they were sent.
4. **Massive Concurrent Connections**: Support 50 Million simultaneous persistent WebSocket connections.

---

## 4. Assumptions & Constraints
- 50 Million Daily Active Users (DAU); 10 Million peak concurrent online connections.
- Average user sends 40 messages/day.
- Message retention: Unlimited historical chat sync.

---

## 5. Practical Scale Estimation

### Traffic Calculations
- **Total Messages per Day**: $50\text{M users} \times 40\text{ msgs} = 2\text{ Billion messages/day}$.
- **Average Message RPS**:
  $$\text{Average RPS} = \frac{2,000,000,000}{86,400\text{ s}} \approx 23,000\text{ messages/sec}$$
- **Peak Message RPS ($3\times$)**: $\approx 70,000\text{ messages/sec}$.
- **Presence Heartbeat Traffic**: 10M concurrent users sending heartbeat every 30 seconds $\approx 330,000\text{ requests/sec}$.

### Storage Calculations (5 Years)
- Message record: `message_id` (16B), `conversation_id` (16B), `sender_id` (8B), `text_content` (150B), `created_at` (8B), `status` (4B) $\approx 200\text{ bytes}$.
- **Daily Storage**: $2\text{ Billion} \times 200\text{ B} = 400\text{ GB/day}$.
- **5-Year Storage**: $400\text{ GB} \times 365 \times 5 \approx 730\text{ TB}$ (Requires distributed NoSQL like Cassandra).

### Connection Memory Sizing (WebSockets)
- 10 Million concurrent WebSocket connections.
- Each open Linux TCP socket + WebSocket context uses $\approx 10\text{ KB}$ of server RAM.
- **Total Memory for 10M Sockets**: $10\text{M} \times 10\text{ KB} \approx 100\text{ GB RAM}$.
- *Conclusion*: A cluster of 50 WebSocket servers (handling 200,000 connections each) comfortably handles peak load.

---

## 6. API Design

### 1. WebSocket Protocol Payloads (Real-Time Communication)

#### Send Message (Client $\to$ Gateway):
```json
{
  "type": "SEND_MESSAGE",
  "client_msg_id": "uuid-987-abc",
  "conversation_id": "conv_42",
  "recipient_id": "usr_88",
  "content": "Hey! Are you ready for the mock interview?",
  "media_url": null
}
```

#### Deliver Message (Gateway $\to$ Recipient Client):
```json
{
  "type": "RECEIVE_MESSAGE",
  "message_id": "msg_999888777",
  "conversation_id": "conv_42",
  "sender_id": "usr_99",
  "content": "Hey! Are you ready for the mock interview?",
  "created_at": "2026-09-11T19:50:00Z"
}
```

### 2. HTTP REST Endpoints (Sync & History)
- **Get Chat History**: `GET /api/v1/conversations/{conv_id}/messages?limit=50&before_msg_id=msg_100`

---

## 7. Data Model

### Apache Cassandra / ScyllaDB Schema (Time-Series Message Store)
```sql
CREATE TABLE messages (
    conversation_id VARCHAR,
    message_id TIMEUUID, -- Combines timestamp + uniqueness for strict ordering
    sender_id BIGINT,
    content TEXT,
    media_url VARCHAR,
    status VARCHAR, -- 'SENT', 'DELIVERED', 'READ'
    PRIMARY KEY (conversation_id, message_id)
) WITH CLUSTERING ORDER BY (message_id DESC);

CREATE TABLE user_conversations (
    user_id BIGINT,
    last_message_at TIMESTAMP,
    conversation_id VARCHAR,
    unread_count INT,
    PRIMARY KEY (user_id, last_message_at, conversation_id)
) WITH CLUSTERING ORDER BY (last_message_at DESC);
```

---

## 8. High-Level Architecture

```mermaid
flowchart TD
    ClientA[User A (Mobile)] <-->|WebSocket| WS1[WebSocket Gateway 1]
    ClientB[User B (Mobile)] <-->|WebSocket| WS2[WebSocket Gateway 2]
    
    subgraph RoutingTier["Session Registry & Message Broker"]
        RedisSession[("Redis Session Store (User -> WS Server ID)")]
        KafkaCluster["Apache Kafka / RabbitMQ Message Broker"]
    end
    
    subgraph CoreServices["Backend Services"]
        MsgService[Message Service]
        PresenceService[Presence Service]
        GroupService[Group Management Service]
    end
    
    subgraph StorageTier["Databases"]
        MsgDB[("Cassandra / ScyllaDB (Message History)")]
        UserDB[("PostgreSQL (Users & Group Memberships)")]
    end
    
    subgraph OfflinePush["Offline Fallback"]
        PushService[Push Notification Service]
        APNS_FCM["Apple APNS / Google FCM"]
    end

    WS1 <--> RedisSession
    WS2 <--> RedisSession
    
    WS1 --> MsgService
    MsgService --> MsgDB
    MsgService --> KafkaCluster
    KafkaCluster --> WS2
    
    MsgService -.->|If User Offline| PushService
    PushService -.-> APNS_FCM
    
    ClientA -.->|Heartbeat every 30s| PresenceService
    PresenceService <--> RedisSession
```

---

## 9. Request / Data Flow (1-on-1 Chat)

### Step-by-Step Message Delivery Flow:
1. **User A connects**: Client opens WebSocket connection to `WS Server 1`. `WS Server 1` saves session mapping in Redis: `SET user:session:usr_A "ws_server_1"`.
2. **User A sends message** to User B:
   - Message travels over active WebSocket to `WS Server 1`.
3. **Persistence & Sequencing**:
   - `WS Server 1` forwards message to `Message Service`.
   - `Message Service` generates a strictly increasing `TIMEUUID` (`message_id`) and writes the record to Cassandra.
   - Sends ACK back to User A (`status = SENT`).
4. **Session Lookup**:
   - `Message Service` checks Redis for User B's active session: `GET user:session:usr_B`.
5. **Case 1: User B is ONLINE (Connected to `WS Server 2`)**:
   - Message published to Kafka topic for `ws_server_2`.
   - `WS Server 2` consumes event and pushes message frame down User B's open WebSocket connection in $< 20\text{ms}$.
   - User B's client automatically returns delivery receipt $\to$ User A's ticks update to `DELIVERED`.
6. **Case 2: User B is OFFLINE**:
   - Redis returns `nil`.
   - Message Service dispatches async event to `Push Notification Service`.
   - Push Service delivers alert via Apple APNS / Google FCM.
   - When User B opens app, client queries `GET /conversations/{id}/messages` to sync missed history.

---

## 10. Presence System (Online / Offline Tracking)
- **Problem**: 10 Million users sending HTTP presence pings would overwhelm backend databases.
- **Mechanism: Heartbeats with Redis Key Expiration (TTL)**:
  1. Client sends a lightweight ping over WebSocket every 30 seconds.
  2. Presence Service sets a Redis key with a 60-second TTL:
     `SET user:presence:usr_A "ONLINE" EX 60`
  3. If user loses Wi-Fi or closes app without clean disconnect, the 60s TTL expires $\to$ User status automatically becomes `OFFLINE`.
  4. When User A opens a chat with User B, client queries `GET user:presence:usr_B`.

---

## 11. Group Chat Scaling (Fanout Mechanism)
- **Small Groups ($< 100\text{ members}$)**:
  - Sender publishes 1 message $\to$ `Message Service` fetches group members from DB $\to$ Fans out message to all 100 members' individual session queues.
- **Large Groups (500–10,000 members, e.g., Discord / Telegram)**:
  - **Do NOT duplicate message per member**.
  - Instead, the group has a dedicated **Kafka Channel/Topic**. All connected WebSocket servers hosting active group members subscribe to that group channel. The broker multicasts 1 message to the relevant WebSocket servers.

---

## 12. Database Choice: Why Cassandra over SQL?
- **Extreme Write Throughput**: 2 Billion messages/day requires write-optimized LSM-trees. Cassandra writes sequentially to commit log and MemTable in memory without disk seeks.
- **Natural Time-Series Clustering**: `PRIMARY KEY (conversation_id, message_id)` allows fetching the latest 50 messages for any conversation in a single lightning-fast sequential disk slice query.
- **Linear Horizontal Scalability**: Adding 10 new Cassandra nodes scales storage and write throughput linearly with zero downtime.

---

## 13. Caching Strategy
- **Redis Session Registry**: Maps `user_id -> ws_server_ip` (In-memory, sub-millisecond lookups).
- **Redis Presence Cache**: In-memory heartbeat TTL flags.
- **Redis Group Membership Cache**: Cached list of `user_id`s in a group to avoid repeated Postgres joins.

---

## 14. Scaling Strategy ($1K \to 100K \to 10M \to 50M$ Connections)
- **1,000 Users**: Single Node.js server with Socket.io + SQLite.
- **100,000 Users**: 5 WebSocket servers behind AWS NLB (L4 Network Load Balancer) + Redis Pub/Sub backplane.
- **10,000,000 Users**:
  - Cluster of 50 WebSocket Gateways using Go / Netty (high memory density).
  - Apache Kafka message broker partitioned by `conversation_id`.
  - ScyllaDB cluster sharded across 20 nodes for message storage.

---

## 15. Reliability & Fault Tolerance
- **WebSocket Gateway Crash**: If `WS Server 1` dies, 200k clients detect connection loss, wait a randomized 1–5s backoff jitter, and reconnect to another healthy gateway via NLB. Redis session mapping is updated upon reconnection.
- **Message Ordering Guarantee**: Using `TIMEUUID` or distributed Snowflake IDs guarantees monotonic in-order sequence within every individual conversation partition.

---

## 16. Security Considerations
- **End-to-End Encryption (E2EE)**: Implement Signal Protocol (Double Ratchet Algorithm). The server stores only encrypted ciphertext blobs; decryption keys exist strictly on client devices.
- **TLS Termination**: All WebSocket traffic encrypted via `WSS://` (TLS 1.3).

---

## 17. Key Trade-offs
- **L4 NLB vs L7 ALB for WebSockets**: Used Layer 4 Network Load Balancer for extreme throughput and long-lived TCP connection stability, terminating TLS at the WebSocket gateway.
- **Eventual Consistency on Read Receipts**: Allowed read receipt delivery ticks to update asynchronously via Kafka to prevent blocking message transmission.

---

## 18. Bottlenecks (What Breaks First?)
- **The First Bottleneck**: **Linux File Descriptor Limits (`ulimit -n`)** on WebSocket servers.
- *Fix*: Tune Linux OS kernel parameters (`/etc/security/limits.conf`) to allow $1,000,000$ open socket descriptors per instance.

---

## 19. Interview Follow-ups & Conversational Answers

### Interviewer: "Why use an L4 Load Balancer instead of an L7 Load Balancer for WebSockets?"
> **Good Answer**: "WebSocket connections are persistent and long-lived (staying open for hours). Layer 7 load balancers incur heavy memory and CPU overhead maintaining application-level HTTP state for millions of connections. An L4 Network Load Balancer (like AWS NLB) routes raw TCP packets with ultra-high throughput and minimal memory overhead, distributing connections via round-robin or least-connections directly to the WebSocket gateway nodes."

### Interviewer: "How do you handle out-of-order messages if a client's network connection drops and reconnects?"
> **Good Answer**: "Every message is assigned a monotonically increasing `TIMEUUID` or Snowflake sequence ID at the server upon receipt. The client maintains the `last_synced_message_id`. Upon reconnecting, the client queries `GET /messages?since_id=12345`. The client-side UI renders messages sorted strictly by this sequence ID, ensuring that even if packets arrive out of order over the network, they are presented in correct chronological order."

---

## 20. 2-Minute Interview Verbal Script
> "To design a real-time chat application like WhatsApp for 50M DAU:
> 
> The architecture is divided into **Connection Management**, **Routing & Presence**, and **Durable Storage**.
> 
> For real-time delivery, clients establish persistent bidirectional **WebSockets** connections terminating on a stateless cluster of **WebSocket Gateways** behind an L4 Network Load Balancer.
> 
> When User A sends a message:
> 1. The Gateway sends the payload to the Message Service, which writes it to **Cassandra/ScyllaDB** (optimized for write-heavy time-series chat data) and returns a `SENT` ACK.
> 2. The service queries a **Redis Session Registry** to locate User B's active WebSocket gateway.
> 3. If online, the message is routed via **Apache Kafka** to User B's gateway and pushed down the socket in $< 50\text{ms}$.
> 4. If offline, the message triggers an asynchronous **APNS/FCM Push Notification**.
> 
> For **Online Presence**, clients send a lightweight heartbeat every 30s updating a Redis key with a 60s TTL, automatically managing disconnects without noisy DB writes."

---

## Reusable Patterns Extracted

| Pattern | Why It Was Used | Other Systems Where It Applies |
|---|---|---|
| **Session Registry Mapping (Redis)** | Maps dynamic stateful connections (`user_id -> server_ip`) for stateless routing. | Multiplayer gaming servers, Collaborative whiteboard editors, Live trading terminals. |
| **Heartbeat with TTL Expiration** | Scalable presence tracking without explicit disconnect events. | IoT device health monitoring, Distributed worker heartbeats, Service discovery. |
| **Time-Series Clustering (Cassandra)** | Stores append-only sequential streams with high write throughput. | Financial ledger audits, Sensor telemetry, Activity feeds. |
| **L4 Connection Termination** | Handles millions of concurrent persistent TCP/WebSocket connections. | Live audio streaming, Raw TCP gateways, VoIP signaling. |
