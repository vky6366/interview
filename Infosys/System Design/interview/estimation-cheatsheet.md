# System Design Scale Estimation Cheatsheet (Mental-Math Playbook)

During an interview, **do NOT waste time performing complex long division**. Use these standardized rounding rules, conversion shortcuts, and mental-math constants to calculate RPS, Storage, and Bandwidth in under 60 seconds.

---

## 1. Golden Mental-Math Constants

### ⏱️ Time Conversions
| Time Unit | Exact Seconds | Mental-Math Approximation (Use This!) |
|---|---|---|
| **1 Day** | $86,400\text{ seconds}$ | **$100,000\text{ seconds } (10^5\text{ s})$** |
| **1 Month (30 Days)** | $2.59 \times 10^6\text{ seconds}$ | **$2.5 \times 10^6\text{ seconds (2.5 Million s)}$** |
| **1 Year (365 Days)** | $3.15 \times 10^7\text{ seconds}$ | **$3 \times 10^7\text{ seconds (30 Million s)}$** |

---

### 💾 Powers of Two & Storage Units
| Power of 2 | Exact Bytes | Unit | Approximation |
|---|---|---|---|
| **$2^{10}$** | $1,024\text{ Bytes}$ | **$1\text{ KB}$** | Thousand ($10^3$) |
| **$2^{20}$** | $1,048,576\text{ Bytes}$ | **$1\text{ MB}$** | Million ($10^6$) |
| **$2^{30}$** | $1,073,741,824\text{ Bytes}$ | **$1\text{ GB}$** | Billion ($10^9$) |
| **$2^{40}$** | $1,099,511,627,776\text{ Bytes}$ | **$1\text{ TB}$** | Trillion ($10^{12}$) |
| **$2^{50}$** | $1,125,899,906,842,624\text{ Bytes}$ | **$1\text{ PB}$** | Quadrillion ($10^{15}$) |

---

## 2. Quick Requests Per Second (RPS) Conversion Table

$$\text{RPS} = \frac{\text{Daily Requests}}{100,000\text{ seconds}}$$

| Daily Request Volume | Average RPS (Mental Math) | Peak RPS ($2.5\times$ Rule) |
|---|---|---|
| **1 Million / day** | $\approx \mathbf{10\text{ RPS}}$ | $\approx \mathbf{25\text{ RPS}}$ |
| **10 Million / day** | $\approx \mathbf{100\text{ RPS}}$ | $\approx \mathbf{250\text{ RPS}}$ |
| **100 Million / day** | $\approx \mathbf{1,000\text{ RPS}}$ | $\approx \mathbf{2,500\text{ RPS}}$ |
| **1 Billion / day** | $\approx \mathbf{10,000\text{ RPS}}$ | $\approx \mathbf{25,000\text{ RPS}}$ |

---

## 3. Storage Estimation Formulas

### Formula:
$$\text{Storage per Day} = \text{Daily Writes} \times \text{Average Payload Size}$$
$$\text{Storage for 5 Years} = \text{Storage per Day} \times 365 \times 5 \approx \text{Storage per Day} \times \mathbf{1,800 \text{ (or } 2,000\text{)}}$$

### Standard Data Payload Sizes (Rules of Thumb):
- `UUID` / `ID`: 16 to 32 bytes
- `Timestamp`: 8 bytes
- `Short String (Username, Email)`: 32 to 64 bytes
- `Text Tweet / Message`: 200 to 500 bytes
- `Rich Article / Post Metadata`: 1 to 2 KB
- `Compressed Thumbnail Image`: 20 to 50 KB
- `High-Res Photo`: 500 KB to 2 MB
- `1 Minute Transcoded Video (1080p)`: 15 to 20 MB

---

## 4. Bandwidth Estimation Formulas

$$\text{Incoming / Outgoing Bandwidth (Bytes/sec)} = \text{RPS} \times \text{Average Payload Size}$$
$$\text{Bandwidth in Megabits per second (Mbps)} = \frac{\text{Bandwidth in MB/s} \times 8}{1}$$

### Example:
- If Read RPS $= 10,000\text{ RPS}$ and average response payload $= 50\text{ KB}$:
  $$\text{Bandwidth} = 10,000 \times 50\text{ KB} = 500,000\text{ KB/sec} = 500\text{ MB/sec}$$
  $$\text{In Gbps} = 500\text{ MB/sec} \times 8 = \mathbf{4\text{ Gbps}}$$

---

## 5. Memory & Cache Sizing (The 80/20 Rule)

In system design, we assume **20% of hot daily unique entities generate 80% of total read traffic**.

$$\text{Cache RAM Needed} = \text{Daily Unique Read Entities} \times 20\% \times \text{Entity Size} \times 1.25\text{ (Safety Buffer)}$$

### Example (URL Shortener Cache):
- 350 Million read redirects/day.
- Unique URLs requested daily $\approx 35\text{ Million}$.
- Hot 20% to cache $= 0.20 \times 35\text{M} = 7\text{ Million URLs}$.
- Size per URL record $= 500\text{ bytes}$.
- **RAM Needed**:
  $$7,000,000 \times 500\text{ bytes} \approx 3.5\text{ GB RAM}$$
- *Conclusion*: A single small Redis instance easily holds all hot URLs!

---

## 6. Full Step-by-Step Example Walkthrough

### Scenario: "Estimate scale for Twitter/X"
1. **Assumptions**:
   - 200 Million Daily Active Users (DAU).
   - Each user posts 1 tweet/day; each user reads 100 tweets on their timeline/day.
   - Read-to-Write ratio $= 100:1$.
   - Average tweet text $= 250\text{ bytes}$; 10% of tweets contain a 500KB photo.

2. **RPS Calculation**:
   - **Write RPS**:
     $$\text{Write RPS} = \frac{200,000,000\text{ tweets}}{100,000\text{ s}} = \mathbf{2,000\text{ tweets/sec (Peak: } 5,000\text{ RPS)}}$$
   - **Read RPS**:
     $$\text{Read RPS} = 2,000 \times 100 = \mathbf{200,000\text{ reads/sec (Peak: } 500,000\text{ RPS)}}$$

3. **Storage Calculation (5 Years)**:
   - Text per day: $200\text{M} \times 250\text{ B} = 50\text{ GB/day}$.
   - Media per day: $200\text{M} \times 10\% \times 500\text{ KB} = 20\text{M} \times 500\text{ KB} = 10\text{ TB/day}$.
   - **Total Storage (5 Years)**:
     $$\text{5-Year Text Storage} = 50\text{ GB/day} \times 365 \times 5 \approx \mathbf{91\text{ TB (Cassandra/NoSQL)}}$$
     $$\text{5-Year Media Storage} = 10\text{ TB/day} \times 365 \times 5 \approx \mathbf{18.25\text{ PB (AWS S3)}}$$

4. **Network Bandwidth Calculation**:
   - Egress: $200,000\text{ reads/sec} \times 2\text{ KB (Timeline payload)} = 400\text{ MB/sec} \approx \mathbf{3.2\text{ Gbps}}$.
   - Media Egress: $\approx \mathbf{40\text{ Gbps}}$ (Offloaded 95% to Cloudflare/CloudFront CDN).
