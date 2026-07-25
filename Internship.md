# Internship Interview Prep

## Statement 1: Built hybrid retrieval pipelines (BM25 + embeddings + query compression)

This sentence has three separate technologies.

### Step 1 — Why Retrieval?

**Interviewer:**
Why do we even need retrieval? Why can't we just send everything to GPT?

**Answer:**
LLMs have a limited context window. Even if the model supports a large context, sending all documents is inefficient, increases latency and cost, and often reduces answer quality because irrelevant information can distract the model. Retrieval selects only the most relevant context before generating a response.

**Pipeline:**
```text
User Query
      │
      ▼
Retriever
      │
Relevant Chunks
      │
      ▼
LLM
      │
Answer
```

### Step 2 — Why Vector Search?

Suppose documents contain:
*The patient experiences myocardial infarction.*

User asks:
*heart attack treatment*

Keyword search struggles because the words differ.
Embeddings capture semantic meaning.

`heart attack` -> **Embedding** -> *close to* -> **Embedding** -> `myocardial infarction`

That's why embeddings are used.

### Step 3 — Why BM25?

Now imagine:

**Document:**
*Take 500mg Paracetamol.*

**User asks:**
*Paracetamol dosage*

BM25 wins here because **exact keywords** ("Paracetamol") appear directly.
Embedding search sometimes retrieves *Pain relief medicine* instead.

### Step 4 — Why Hybrid Retrieval?

**Interviewer:**
Why combine them?

**Answer:**
Because they solve different problems.

**BM25:**
✔ Exact keywords
✔ Rare medical terms
✔ Drug names
✔ IDs

**Embeddings:**
✔ Semantic similarity
✔ Synonyms
✔ Natural language

**Together:**
```text
BM25 Results
        │
        │
Embedding Results
        │
        ▼
Merge
        ▼
Rank
```
Higher recall.

### Step 5 — Which Embedding Model?

Expect:
*Which embedding model?*

Possible answers:
- OpenAI `text-embedding-3-small`
- BGE
- E5
- Sentence Transformers

If you actually used one, explain why.
If you do not remember, say: *"I used an OpenAI embedding model through the API."*
**Never invent.**

### Step 6 — Why Qdrant?

**Question:**
Why Qdrant?

**Answer:**
Because it is optimized for vector similarity search.
Supports:
- HNSW indexing
- metadata filtering
- payload storage
- scalable vector search
- REST/gRPC APIs

**Question:**
Why not FAISS?

**Answer:**
FAISS is a great library, but it is **not a database**.
- No REST API
- No persistence
- No filtering
- No distributed deployment

Qdrant provides those production capabilities.

### Step 7 — Query Compression

This is where many candidates struggle.

**Example:**
User asks: *My 74-year-old diabetic father has chest pain after taking aspirin yesterday. What medication should he avoid if he already has hypertension?*

Retriever sees lots of words. Many are irrelevant.

Compression transforms it into:
- diabetic
- hypertension
- chest pain
- aspirin interactions

Cleaner query -> Better retrieval -> Less latency -> Better answers

**Question:**
How is compression done?

**Answer:**
Usually: Small LLM -> Extract important concepts -> Rewrite query -> Retriever

**Question:**
Why not retrieve directly?

**Answer:**
Because: Long noisy questions -> Poor embeddings -> Poor retrieval

### Step 8 — Retrieval Pipeline

Complete architecture:
```text
User
  │
  ▼
Query Compression
  │
  ▼
BM25
  │
  ▼
Embedding Search
  │
  ▼
Merge Results
  │
  ▼
Deduplicate
  │
  ▼
Top K
  │
  ▼
Prompt
  │
  ▼
GPT
  │
  ▼
Answer
```
Know every arrow.

---

## Statement 2: reducing retrieval latency by approximately 2× compared to a baseline dense retrieval pipeline

This is interview gold.

**Question:**
What is baseline?

**Answer:**
Dense Retrieval only: User -> Embedding -> Vector Search -> Top K

**Question:**
How did you measure?

**Good answer:**
Average retrieval time:
- Dense: 220 ms
- Hybrid: 110 ms
*(or similar)*

If you don't remember exact values, say: *"We benchmarked retrieval time across the same evaluation queries and observed approximately a two-fold reduction."*

**Question:**
Why faster?

**Possible reasons:**
- BM25 quickly narrows candidates.
- Compression reduces unnecessary searches.
- Smaller retrieved context.
- Less token usage.
- Fewer chunks.

**Expect these follow-ups:**
- How many documents?
- How many chunks?
- Chunk size?
- Top K?

---

## Statement 3: developed FastAPI-based RAG endpoints

**Question:**
What endpoints?

**Typical:**
- `POST /query`
- `POST /chat`
- `POST /upload`
- `GET /health`
- `POST /feedback`

**Question:**
Walk me through `/query`

**Answer:**
Client -> FastAPI -> Compress Query -> Retriever -> Prompt -> GPT -> Response

**Question:**
Why FastAPI?

**Answer:**
- Async
- Validation
- Automatic docs
- Performance
- Python ecosystem

---

## Statement 4: BYOK endpoints

**Question:**
What's BYOK?

**Answer:**
Bring Your Own Key.
Instead of: *Your API Key -> Server -> OpenAI*
User supplies: *their own key -> Server forwards request -> OpenAI*

**Advantages:**
- No API cost (for you)
- Better security
- Personal quotas

**Question:**
How would you validate?

**Answer:**
- Check key format
- Test authentication
- Store securely
- Never log it

---

## Statement 5: Containerized FastAPI, Qdrant, and MongoDB

**Question:**
Why Docker?

**Answer:**
- Consistent environment
- No dependency conflicts
- Easy deployment
- Isolation

**Architecture:**
```text
Docker Compose
├── FastAPI
├── Qdrant
└── MongoDB
```

**Question:**
Why separate containers?

**Answer:**
Microservice philosophy. Each service is independent, scalable, and replaceable.

**Question:**
Networking?

**Answer:**
Docker bridge network.
FastAPI connects to:
- `http://qdrant:6333`
- `mongodb://mongo:27017`

**Question:**
Volumes?

**Answer:**
Persist MongoDB and Qdrant across container restarts.

---

## Statement 6: analyzed user interaction data

This is where interviewers see whether you think like a product engineer.

**Question:**
What data?

**Examples:**
- Query
- Retrieved Chunks
- Latency
- Feedback
- Click-through
- Session Length
- Failure Cases

**Question:**
Why analyze?

**Answer:**
To improve:
- Chunking
- Embeddings
- Prompt
- Top K
- Compression
- Hybrid weights

**Question:**
Suppose users dislike answers. What do you do?

**Answer:**
Look at retrieved documents.
- Were they relevant?
- Prompt?
- Hallucination?
- Missing metadata?
- Wrong chunk size?

---

## Statement 7: improve retrieval quality

**Question:**
How do you measure?

**Possible metrics:**
- Precision@K
- Recall@K
- MRR
- nDCG
- Hit Rate
- Faithfulness
- Groundedness
- Human evaluation

Even if you didn't formally compute all of these, knowing them is valuable.

---

## Statement 8: improve healthcare recommendation relevance

**Question:**
How?

**Example:**
User feedback -> Wrong recommendations -> Investigate retrieval -> Improve chunking -> Add metadata -> Better retrieval -> Better recommendation

---

## Final Architecture Diagram

They will likely ask you to draw your architecture. Draw something like this:

```text
                    User
                      │
                      ▼
                 FastAPI API
                      │
         ┌────────────┴────────────┐
         │                         │
         ▼                         ▼
  Query Compression          Authentication (optional)
         │
         ▼
   Hybrid Retriever
   ┌───────────────┐
   │               │
   ▼               ▼
 BM25         Qdrant Vector Search
   │               │
   └──────┬────────┘
          ▼
   Merge & Rank Results
          ▼
   Prompt Construction
          ▼
      OpenAI LLM
          ▼
        Response
          ▼
      MongoDB Logs
```
