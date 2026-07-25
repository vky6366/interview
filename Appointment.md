# Medical Appointment Scheduling System Interview Prep

## The Elevator Pitch (2 minutes)

If they say:
*Tell me about your Medical Appointment Scheduling System.*

Say:
"It is an AI-powered conversational appointment scheduling system built using FastAPI and LangGraph. Instead of following a fixed chatbot flow, it uses a stateful graph where each node is responsible for collecting or validating a specific piece of patient information before moving to the next step. The system combines deterministic business logic with LLM-based entity extraction, recommends doctors based on symptoms, retrieves available slots from the database, and finally books appointments while maintaining conversational state."

**Notice something?**
I didn't say LangChain, FastAPI, OpenAI, AWS just because. Everything was attached to a problem. That's how senior engineers explain projects.

## COMPLETE ARCHITECTURE

They LOVE diagrams.

```text
                  User
                    │
             React Frontend
                    │
                    ▼
              FastAPI Backend
                    │
        Authentication (Google OAuth)
                    │
                    ▼
            LangGraph Workflow
                    │
     ┌──────────────┴───────────────┐
     ▼                              ▼
Entity Extraction             Conversation State
(OpenAI + Regex)                 (PatientInfo)
     │                              │
     └──────────────┬───────────────┘
                    ▼
            Validation Nodes
                    │
                    ▼
          Doctor Recommendation
                    │
                    ▼
         PostgreSQL Appointment DB
                    │
                    ▼
          Available Slots Returned
                    │
                    ▼
             Appointment Booking
                    │
                    ▼
         Email Confirmation + Response
```

---

## Step 1: Why LangGraph?

This is probably the first technical question.

**Interviewer:**
Why didn't you use LangChain alone?

**Your answer:**
LangChain is excellent for prompt chains, tool calling, and RAG. But this project is **stateful**.
The patient can say:
I want an appointment. -> Tomorrow. -> Actually next Monday. -> Not Dr Smith. -> Any dentist.

The conversation isn't linear. We need branching, loops, retries, memory, and validation. LangGraph solves exactly this.

**Question:**
What is State?

**Answer:**
State is a shared object passed between every node.
Example: `PatientState { problem, doctor, date, returning, insurance, slot, next_step }`
Every node reads it. Every node updates it.

**Question:**
Why not store everything inside GPT?

**Answer:**
Because LLMs are probabilistic. Business logic must be deterministic.

---

## Step 2: FastAPI

**Question:**
Why FastAPI?

**Good answer:**
FastAPI provides:
- async support
- automatic validation
- OpenAPI docs
- excellent performance
- tight Python integration

Perfect for AI APIs.

**Question:**
What does `/chat` do?

**Answer:**
Flow:
`POST /chat` -> Receive Message -> Load Session -> Construct Graph State -> Run LangGraph -> Update Session -> Return Response

Exactly what your implementation does.

**Question:**
Why REST?

**Answer:**
Simple. Stateless. Frontend independent. Easy deployment.

**Question:**
Would you use WebSockets?

**Answer:**
YES. For streaming responses. Typing indicators. Live updates.

---

## Step 3: Session Store

**Question:**
How did conversation memory work?

**Answer:**
Each conversation -> Thread ID -> Mapped to -> Patient State -> Stored in -> Session Store
Your implementation uses an in-memory session store with a planned migration to Redis.

**Question:**
Why not store memory inside GPT?

**Answer:**
Because GPT doesn't remember between API calls. You need persistent application state.

**Question:**
Why Redis later?

**Answer:**
Memory is fast. TTL gives automatic expiration. Shared across multiple backend instances. Perfect for horizontal scaling.

---

## Step 4: Entity Extraction

This is a HUGE topic.

**Question:**
User says: *I have tooth pain tomorrow*
How do you extract Problem, Doctor, Date?

**Answer:**
Pipeline:
Raw Text -> Regex -> Simple mappings -> LLM Extraction -> Merge -> Patient State
Exactly what your project does with regex heuristics before invoking the LLM.

**Question:**
Why regex first?

**Answer:**
Much faster. No API cost. Deterministic. Only call GPT when necessary.

**Question:**
Why merge?

**Answer:**
Suppose earlier: `Doctor = Dentist`. User later says: `Next Tuesday`.
LLM shouldn't erase `Dentist`. Merge protects existing information.

**Question:**
Why not only GPT?

**Answer:**
Expensive. Slower. Hallucinates. Regex + Business Rules is more reliable.

---

## Step 5: Validation Nodes

**Question:**
Why separate nodes?

**Answer:**
Instead of one huge prompt, we have: `Problem -> Returning -> Doctor -> Date`.
Each has one responsibility. Much easier debugging.

**Question:**
What happens if Doctor is missing?

**Answer:**
Graph -> `ensure_doctor()` -> Ask user -> Pause -> Continue later.
Exactly how your workflow routes between nodes.

---

## Step 6: Doctor Recommendation

**Question:**
How does "Any Doctor" work?

**Answer:**
Pipeline:
`Problem -> Symptom -> Specialty -> Doctors -> Available Doctor`
Example:
`Tooth Pain -> Dentistry -> Dr Patel`

**Question:**
Why not GPT?

**Answer:**
Because medical mapping is Business Logic. Business logic must be deterministic.

**Question:**
Where is it stored?

**Answer:**
`SPECIALTY_MAP`. Exactly as described in your project.

---

## Step 7: Slot Retrieval

**Question:**
What happens?

**Answer:**
`Doctor + Date -> SQL Query -> Available Slots -> Top Results -> User Chooses`

**Question:**
Why SQL?

**Answer:**
Need Consistency, Transactions, Relationships (Appointments, Doctors, Availability).

**Question:**
Could MongoDB work?

**Answer:**
Yes. But Appointments are relational. PostgreSQL is better.

---

## Step 8: Booking

**Question:**
Suppose two users select the same slot. What happens?

**Good answer:**
Before booking:
`Check is_booked -> Transaction -> Update -> Commit -> Prevent double booking.`
Your booking node explicitly checks slot availability before marking it booked.

---

## Step 9: Google OAuth

**Question:**
Why Google?

**Answer:**
Don't store passwords. Google verifies identity.
Backend -> Creates JWT.
Future requests -> JWT only.

**Question:**
Why JWT?

**Answer:**
Stateless. Scalable. No session lookup.

---

## Step 10: Database

Know your tables.
- Users
- Doctors
- Availability
- Appointments

Relationships. Foreign Keys. Indexes.

**Question:**
Why SQLAlchemy?

**Answer:**
ORM. Safer. Cleaner. Database agnostic.

---

## Step 11: Email

**Question:**
When do you send it?

**Answer:**
Only after Booking Success. Never before. Otherwise: False confirmation.

**Question:**
Is it Blocking?

**Answer:**
No. Background task. Better UX.

---

## Step 12: AWS

Know architecture.

```text
React
  ↓
S3
  ↓
CloudFront
  ↓
FastAPI
  ↓
ECS
  ↓
RDS
  ↓
SES
  ↓
Email
```

**Question:**
If they ask, Why ECS?

**Answer:**
Docker. Easy deployment. Scaling. Rolling updates.

---

## Step 13: Why not a chatbot?

Important. This isn't just chat. It's **Workflow Automation**.
- Chat -> Conversation.
- Graph -> Decision Engine.

---

## Step 14: Failure Cases

**Suppose:**
User says Tomorrow -> Actually Friday -> Actually Monday.
**Result:** State updates. Graph continues.

**Suppose:**
Book Dr Smith -> Dr unavailable.
**Result:** Graph -> Recommend Alternative.

**Suppose:**
GPT fails.
**Result:** Regex still works.

---

## Step 15: Scalability

**Question:**
If 100,000 users tomorrow. How?

**Answer:**
```text
Load Balancer
     ↓
Multiple FastAPI
     ↓
   Redis
     ↓
 PostgreSQL
     ↓
Worker Queue
     ↓
   Email
```

---

## Step 16: Hallucination Prevention

**Question:**
How do you stop GPT hallucinating?

**Your answer:**
- Regex first
- Business rules
- LangGraph validation
- Structured outputs
- Database lookup
- Never let GPT book directly
- Deterministic state transitions

This is exactly the kind of answer FinStocks engineers will like.

---

## The killer question I would ask you

If I were Rushikesh, I'd ask:

**Why didn't you simply ask GPT: "Book an appointment." Why create 20+ nodes?**

**The answer should be:**
"Because healthcare booking is a deterministic workflow with business constraints. Missing one required field or allowing the model to invent unavailable slots would create incorrect bookings. LangGraph lets the LLM handle natural language understanding while deterministic nodes enforce validation, routing, and database operations. This separation keeps the conversational experience flexible while ensuring the booking process is reliable."
