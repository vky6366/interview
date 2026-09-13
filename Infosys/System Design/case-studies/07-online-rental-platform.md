# Case Study 07 — Online Rental & Vacation Booking Platform (e.g., Airbnb / Vrbo)

## 1. Problem
Design an online vacation rental platform where guests search for properties using geospatial filters (e.g., "Find 2-bedroom cabins in Lake Tahoe for Dec 20–25 under $300/night"), view listing availability calendars, and book properties with **guaranteed zero double-booking across overlapping date ranges**.

---

## 2. Functional Requirements
1. **Host Listing Management**: Hosts can list properties with photos, pricing rules, amenities, and location coordinates (Latitude/Longitude).
2. **Geospatial & Filter Search**: Guests search properties by map bounding box or city, date range, guest count, price range, and amenities.
3. **Availability Calendar**: Display real-time available and blocked dates for any property.
4. **Reservation & Booking**: Guests select a date range `[check_in, check_out]`, hold dates temporarily, and complete payment.
5. **Dynamic Pricing**: Support weekday/weekend rates, seasonal multipliers, and cleaning fees.

---

## 3. Non-Functional Requirements
1. **Strict Concurrency (No Double-Booking)**: Overlapping date ranges for the same property must NEVER be booked by two different guests.
2. **Low Latency Geospatial Search**: Return matching map listings in $< 150\text{ms}$.
3. **High Availability ($99.99\%$) for Browsing**: Search and listing view must remain accessible globally.
4. **High Read-to-Write Ratio**: $1000:1$ (thousands of guests browsing for every 1 booking completed).

---

## 4. Assumptions & Constraints
- 5 Million active property listings globally.
- 50 Million Daily Active Searches; 100,000 bookings completed per day.
- Bookings are made for contiguous day intervals.

---

## 5. Practical Scale Estimation

### Traffic Calculations
- **Search Queries per Day**: $50\text{ Million searches/day}$.
- **Average Search RPS**:
  $$\text{Search RPS} = \frac{50,000,000}{86,400\text{ s}} \approx 600\text{ searches/sec (Peak: } 2,000\text{ RPS)}$$
- **Booking Writes per Day**: $100,000\text{ bookings/day} \approx 1.2\text{ bookings/sec (Peak: } 20\text{ RPS)}$.

### Storage Estimation (5 Years)
- Listing Record: 2 KB. 5M listings $\approx 10\text{ GB}$.
- Booking History: 100K bookings/day $\times 365 \times 5 \approx 180\text{ Million records} \approx 36\text{ GB}$.
- Photos: 5M listings $\times 20\text{ photos} \times 500\text{ KB} \approx 50\text{ TB}$ stored on AWS S3 with CDN delivery.

---

## 6. API Design

### 1. Geospatial Search Listings
- **Endpoint**: `GET /api/v1/search`
- **Query Params**: `lat=37.7749&lng=-122.4194&radius_km=25&check_in=2026-12-20&check_out=2026-12-25&guests=2&max_price=300`
- **Response** (`200 OK`):
```json
{
  "listings": [
    {
      "listing_id": "list_901",
      "title": "Cozy Sunny Cabin",
      "price_per_night": 220.00,
      "total_price": 1100.00,
      "rating": 4.95,
      "latitude": 37.7812,
      "longitude": -122.4210,
      "thumbnail_url": "https://cdn.rental.com/photos/901.jpg"
    }
  ],
  "total_matches": 84
}
```

### 2. Reserve Property Dates (Atomic Booking)
- **Endpoint**: `POST /api/v1/reservations`
- **Headers**: `Idempotency-Key: uuid-3344`
- **Request Body**:
```json
{
  "listing_id": "list_901",
  "check_in": "2026-12-20",
  "check_out": "2026-12-25",
  "guest_id": "usr_55",
  "payment_token": "tok_visa_7788"
}
```

---

## 7. Data Model

### PostgreSQL Relational Schema with PostGIS & Range Types
```sql
CREATE EXTENSION IF NOT EXISTS postgis;
CREATE EXTENSION IF NOT EXISTS btree_gist;

CREATE TABLE listings (
    listing_id VARCHAR(32) PRIMARY KEY,
    host_id BIGINT NOT NULL,
    title VARCHAR(256) NOT NULL,
    base_price DECIMAL(10, 2) NOT NULL,
    max_guests INT NOT NULL,
    location GEOGRAPHY(POINT, 4326) NOT NULL, -- PostGIS Lat/Lng Point
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX idx_listings_location ON listings USING GIST(location);

-- Overlap Exclusion Table (Guarantees Zero Double Booking at DB Level)
CREATE TABLE reservations (
    reservation_id VARCHAR(64) PRIMARY KEY,
    listing_id VARCHAR(32) NOT NULL,
    guest_id BIGINT NOT NULL,
    stay_dates DATERANGE NOT NULL, -- e.g., '[2026-12-20, 2026-12-25)'
    total_price DECIMAL(10, 2) NOT NULL,
    status VARCHAR(32) NOT NULL, -- 'PENDING', 'CONFIRMED', 'CANCELLED'
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    -- EXCLUDE constraint prevents any overlapping date range for the same listing!
    EXCLUDE USING GIST (listing_id WITH =, stay_dates WITH &&)
);
```

---

## 8. High-Level Architecture

```mermaid
flowchart TD
    Client[Web / Mobile Client] --> CDN[CDN Edge (Images & Static Maps)]
    Client --> ALB[Application Load Balancer]
    
    subgraph AppCluster["Stateless Web Microservices"]
        SearchService[Search Service]
        BookingService[Booking & Reservation Service]
        ListingService[Listing Management Service]
    end
    
    ALB --> SearchService
    ALB --> BookingService
    ALB --> ListingService
    
    subgraph SearchEngineTier["Geospatial & Faceted Search"]
        ElasticSearch[("ElasticSearch Cluster (Geo-Distance & Facets)")]
    end
    
    subgraph AvailabilityCache["In-Memory Calendar Bitmaps"]
        RedisCalendar[("Redis Cluster (365-day Availability Bitmaps)")]
    end
    
    subgraph ACID_Storage["Relational Transactional DB"]
        DB_Master[("PostgreSQL Master + PostGIS (Exclusion Constraints)")]
        DB_Replica[("PostgreSQL Read Replica")]
    end
    
    SearchService --> RedisCalendar
    SearchService --> ElasticSearch
    ElasticSearch -.->|CDC Sync via Kafka| DB_Master
    
    BookingService -->|Atomic Date Range Lock| DB_Master
    BookingService -->|Update Availability Bitmap| RedisCalendar
```

---

## 9. Request / Data Flow

### 1. Geospatial & Date Availability Search Flow:
1. Guest searches for properties in *San Francisco* for *Dec 20–25*.
2. **Geospatial & Metadata Filtering**:
   - `Search Service` queries **ElasticSearch** using `geo_distance` filter ($< 25\text{km}$) combined with price/guest filters.
   - ElasticSearch returns matching 500 `listing_id` candidates in $< 30\text{ms}$.
3. **Date Availability Filtering (Redis Bitmaps)**:
   - Search Service queries Redis for the 500 listing IDs against Dec 20–25 (Day index `354` to `359`).
   - Bitwise check returns only the 120 listings whose calendar bits are completely free (`0 = FREE`, `1 = BOOKED`).
4. Search Service calculates total pricing and returns sorted results to the user in $< 80\text{ms}$.

### 2. The Atomic Booking Flow (Zero Double-Booking):
1. Guest submits `POST /reservations` for listing `list_901` for `[2026-12-20, 2026-12-25)`.
2. **PostgreSQL GiST Exclusion Constraint Execution**:
   - Booking Service begins a transaction in PostgreSQL:
     ```sql
     INSERT INTO reservations (reservation_id, listing_id, guest_id, stay_dates, total_price, status)
     VALUES ('res_101', 'list_901', 55, '[2026-12-20, 2026-12-25)', 1100.00, 'CONFIRMED');
     ```
   - **How it prevents double-booking**: PostgreSQL's `EXCLUDE USING GIST (listing_id WITH =, stay_dates WITH &&)` uses an R-Tree index to verify if the requested `daterange` intersects (`&&`) with any existing confirmed reservation.
   - If overlap detected $\to$ Database immediately raises an exclusion violation error $\to$ Service returns `409 Conflict` ("Dates already booked").
   - If no overlap $\to$ Transaction commits successfully.
3. Upon commit, service updates the Redis calendar bitmap for `list_901` setting bits `354-359` to `1`.

---

## 10. Geospatial Indexing Comparison (Level 2 Deep Dive)

| Indexing Method | How it Works | Pros | Cons / Trade-offs |
|---|---|---|---|
| **PostGIS (R-Tree / GiST)** | Hierarchical bounding boxes indexing latitude/longitude directly in PostgreSQL. | Native SQL queries; exact distance math; handles polygon boundaries. | Moderate throughput under heavy search scale. |
| **GeoHash (Base32 String)** | Recursively divides the world into hierarchical grid cells. Closer points share common prefix (e.g., `9q8yy`). | String prefix search (`WHERE geohash LIKE '9q8%'`); easily cached in Redis/NoSQL. | **Edge / Boundary Problem**: Two houses 10 meters apart across a grid boundary share completely different geohash prefixes. |
| **Google S2 / Uber H3 (Hexagons)** | Projects Earth onto a sphere and subdivides into equal-area cells (S2 = Squares; H3 = Hexagons). | **Uniform neighbor distances**; ideal for dynamic radius searches and heatmap aggregations. | Requires external library for coordinate mapping. |
| **ElasticSearch (Geo-Point / BKD-Tree - RECOMMENDED)** | Multi-dimensional BKD-trees supporting rapid radial and bounding box filters combined with text filters. | ✅ Combines geo-search with complex filters (amenities, price, reviews) in $< 20\text{ms}$. | Requires eventual consistency sync from PostgreSQL. |

---

## 11. Availability Calendar Modeling: Bitmaps vs Date Rows

| Modeling Approach | Schema Structure | Pros | Cons |
|---|---|---|---|
| **1 Row Per Day** | `(listing_id, date, status, price)` $\to$ 365 rows per property per year! | Simple SQL queries. | ❌ Massive DB table bloat (5M listings $\times$ 365 days = **1.8 Billion rows/year**!). Slow bulk checking. |
| **Date Range (`DATERANGE`) + Redis 365-Bit Bitmap (RECOMMENDED)** | Store bookings as single range in SQL; Cache yearly calendar as **365-bit string in Redis (46 bytes per property!)**. | ✅ **Extremely compact** (5M properties = **230 MB total RAM!**); $O(1)$ bitwise intersection check for availability. | Requires translating calendar dates to day-of-year bit offsets. |

---

## 12. Database Choice
- **Source of Truth & Booking Transactions**: **PostgreSQL + PostGIS** (ACID transactions, `DATERANGE` native types, and `EXCLUDE` constraints guarantee zero double booking).
- **Search Engine**: **ElasticSearch** (High-throughput geo-distance queries and multi-attribute faceted filters).

---

## 13. Caching Strategy
- **Redis Calendar Bitmaps**: 46-byte bitmap per listing representing 365 days of availability.
- **Listing Details**: Cache-Aside in Redis for property photos, host details, and description.

---

## 14. Scaling Strategy ($1K \to 100K \to 10M$ Searches)
- **1,000 Searches**: Single PostgreSQL instance with PostGIS bounding box queries.
- **100,000 Searches**: ElasticSearch cluster for geospatial search + PostgreSQL Read Replicas.
- **10,000,000 Searches**:
  - Redis cluster caching 365-day availability bitmaps.
  - Multi-region ElasticSearch clusters synced via Debezium / Kafka CDC from Postgres.
  - Shard PostgreSQL by `listing_id` or geographical region (e.g., US, Europe, Asia).

---

## 15. Reliability & Fault Tolerance
- **CDC Ingestion Resilience**: Kafka connect buffers database changes to ElasticSearch. If ElasticSearch restarts, it replays missed CDC events without data drift.
- **Master DB Failover**: Multi-AZ RDS with synchronous standby promotion in $< 30\text{s}$.

---

## 16. Security Considerations
- **Host PII Masking**: Exact property address and door lock codes are hidden until the booking is confirmed and paid.
- **Review Fraud Prevention**: Only guests who completed a verified stay can submit a review.

---

## 17. Key Trade-offs
- **ElasticSearch for Search vs PostgreSQL Direct**: Sacrificed instantaneous write consistency on search indexing (1-2s CDC lag) in exchange for sub-50ms multi-facet geo-searches.
- **Postgres Exclusion Constraints vs Application Locks**: Enforced range overlap constraints directly in the database engine to provide mathematical zero-double-booking guarantees.

---

## 18. Bottlenecks (What Breaks First?)
- **The First Bottleneck**: **Geospatial bounding box queries during holiday peak seasons** (e.g., Dec 31 in Paris).
- *Fix*: ElasticSearch BKD-tree indexing combined with Redis availability bitmaps filters 99% of queries in memory.

---

## 19. Interview Follow-ups & Conversational Answers

### Interviewer: "How do you mathematically guarantee that two users don't book overlapping date ranges simultaneously?"
> **Good Answer**: "We enforce this at the database level using PostgreSQL's GiST `EXCLUDE` constraint on `DATERANGE` columns: `EXCLUDE USING GIST (listing_id WITH =, stay_dates WITH &&)`. When two concurrent transactions attempt to insert overlapping intervals like `[Dec 20, Dec 25)` and `[Dec 22, Dec 27)`, the database engine locks the index slice and raises an exclusion violation on the second transaction, rolling it back immediately."

### Interviewer: "How do you search for available properties without scanning 1.8 Billion daily availability rows?"
> **Good Answer**: "Instead of storing one row per day, we represent each property's 365-day availability calendar as a **365-bit string (46 bytes) in Redis**. When a guest searches for dates from Day 354 to Day 359, we perform a bitwise `AND` operation against the listing's bitmap in memory. If all 5 bits are `0`, the property is available. 5 million listings consume only ~230MB of RAM in Redis!"

---

## 20. 2-Minute Interview Verbal Script
> "To design an online vacation rental platform like Airbnb:
> 
> The architecture addresses two core challenges: **Fast Geospatial Search** and **Guaranteed Zero Double-Booking of Date Ranges**.
> 
> For search, we index listings in **ElasticSearch** with BKD-trees for geo-distance coordinates and faceted filters. To filter available dates rapidly, we maintain **365-bit availability bitmaps in Redis** (only 46 bytes per listing), enabling sub-millisecond calendar availability checks in RAM.
> 
> For booking transactions, we use **PostgreSQL with PostGIS and native DATERANGE types**. We configure a GiST `EXCLUDE` constraint: `(listing_id WITH =, stay_dates WITH &&)`. When a guest checks out, the database atomically validates that no intersecting interval exists. If two guests submit overlapping dates at the exact same millisecond, the second transaction is rejected by the database engine with an exclusion error, guaranteeing 100% mathematical prevention of double-booking."

---

## Reusable Patterns Extracted

| Pattern | Why It Was Used | Other Systems Where It Applies |
|---|---|---|
| **Date Range (`DATERANGE`) Exclusion Constraints** | Prevents overlapping interval collisions at the ACID database layer. | Hotel bookings, Car rentals, Meeting room scheduling, Doctor appointments. |
| **Yearly Calendar Bitmaps in Redis** | Encodes 365 days of availability in 46 bytes of RAM per entity. | Staff shift scheduling, Equipment reservation, Parking spot availability. |
| **Dual-Engine Search & Transaction Split (ES + Postgres)** | ElasticSearch handles fuzzy geospatial & faceted search; Postgres handles strict ACID bookings. | E-commerce product search, Job boards, Real estate listings. |
| **CDC (Change Data Capture) Pipeline** | Syncs primary transactional database writes to search engines asynchronously. | Cache invalidation, Data warehouse ingestion, ElasticSearch indexing. |
