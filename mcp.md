# AI-Powered SOC Analyst Platform Interview Prep

## First explain it in 2 minutes

If they ask:
*Tell me about your SOC Analyst platform.*

Don't start with: "I used FastAPI..."
Start with the problem.

**Good answer:**
"The project is an AI-powered SOC Analyst that automates the initial stages of incident investigation. Instead of security analysts manually reading logs, correlating threat intelligence, mapping attacks to MITRE ATT&CK, checking IP reputation, searching security playbooks, and generating reports, the system orchestrates multiple AI agents using LangGraph. Each agent performs one specialized responsibility, while deterministic business logic ensures the workflow remains reliable and auditable."

That sounds like an engineer.

## What problem are you solving?

**Traditional SOC**
Analyst -> Reads logs -> Finds indicators -> Searches MITRE -> Checks AbuseIPDB -> Reads Playbooks -> Calculates Severity -> Writes Report -> Manager Reviews
**Time:** 30 minutes -> Several hours

**Your system**
Logs -> AI Agents -> Threat Intel -> Classification -> Response -> Human Approval -> Report
**Time:** Much faster.

---

## Entire Architecture

```text
                          Security Logs
                                │
                                ▼
                        FastAPI Endpoint
                                │
                                ▼
                      LangGraph State Machine
                                │
    ┌──────────────┬────────────┼─────────────┬──────────────┐
    ▼              ▼            ▼             ▼              ▼
 Ingest        Detect      Threat Intel    Classify      Response
    │              │            │             │              │
    └──────────────┴────────────┴─────────────┴──────────────┘
                                │
                                ▼
                        Human Approval
                                │
                                ▼
                             Report
                                │
                                ▼
                          PostgreSQL
```

This is almost exactly your architecture.

---

## Why LangGraph?

Guaranteed question.

**Question:**
Why not LangChain?

**Answer:**
LangChain is excellent for prompt chains, retrieval, and tool calling.
But incident response is **stateful**. Every incident changes state.
Example:
Incident -> Threat Found -> Enrichment Done -> Risk Calculated -> Waiting Approval -> Approved -> Report Generated
That's a workflow. Not a chat. LangGraph is perfect.

**Question:**
Why StateGraph?

**Answer:**
Because every node shares **one** state.
Example State:
`{ raw_logs, clean_logs, threats, severity, approved, report }`
Exactly like your TypedDict.

---

## Node 1: Ingest

**Question:**
Why have an Ingest node?

**Answer:**
Raw logs are messy. Different formats. Different vendors. Need normalization.
Pipeline:
`JSON Logs -> Validation -> Standard Schema -> Graph`

**Question:**
Why Pydantic?

**Answer:**
Validation. Type Safety. Missing fields. Automatic parsing. Exactly what your `LogEntry` model does.

**Question:**
Why preserve unknown fields?

**Answer:**
Suppose Log contains: `{ user, ip, cmdline, powershell, process_id, user_agent }`
Tomorrow another product adds `dll_hash`. Don't lose it. Store in `kwargs`. Very smart design.

---

## Node 2: Threat Detection

**Question:**
What happens?

**Answer:**
Pipeline:
`Logs -> Prompt -> GPT -> Structured Output -> Threats`
Exactly your detect node.

**Question:**
Why structured output?

**Answer:**
Instead of "Looks like brute force...", return:
```json
{
  "threat": "Brute Force",
  "confidence": 0.93
}
```
Reliable. Easy parsing.

**Question:**
Why not regex?

**Answer:**
Regex -> Known attacks.
GPT -> Unknown attacks.
Need both.

**Question:**
Why fallback heuristics?

**Answer:**
Suppose OpenAI is down. Still detect "Repeated Failed Login". Exactly what your project does.

---

## Node 3: Threat Intelligence

This is the coolest part.

**Question:**
Why Threat Intelligence?

**Answer:**
Suppose GPT says "Suspicious IP". Need context. Is it a Known attacker? MITRE? CVE? History?
Pipeline:
`Threat -> MCP Server -> MITRE -> AbuseIPDB -> Knowledge Base -> NVD -> Memory`
Exactly your implementation.

### MCP (Their favorite topic)

**Question:**
What is MCP?

**Answer:**
Model Context Protocol. Standard protocol between LLMs and Tools. Instead of custom integrations.
Architecture:
`LLM -> MCP Client -> MCP Server -> Security Tools`

**Question:**
Why not REST?

**Answer:**
REST: Different API for every tool.
MCP: Unified interface. One protocol. Many tools.

**Question:**
Why separate MCP Server?

**Answer:**
Excellent architecture. Because tomorrow replace AbuseIPDB -> VirusTotal. Only MCP changes. Graph doesn't. Loose coupling.

**Question:**
What tools?

**Answer:**
Exactly your project: MITRE, AbuseIPDB, Knowledge Base, NVD.

**Question:**
Why ChromaDB?

**Answer:**
Need Semantic Search. Instead of "Password Attack", find "Credential Access", "Brute Force", "Dictionary Attack".

**Question:**
Why vector search?

**Answer:**
Playbooks don't contain exact keywords. Need semantic similarity.

### MITRE

**Question:**
Why MITRE?

**Answer:**
Standard language. Instead of "Bad Login", say "Credential Access T1110". Everyone understands.

### AbuseIPDB

**Question:**
Why?

**Answer:**
Suppose IP already reported 1000 times. Much higher confidence.

### Memory

**Question:**
Why PostgreSQL Memory?

**Answer:**
Suppose Same IP attacked Yesterday, Today, Tomorrow. Need Historical Context. Your project checks historical incidents for recurring IPs.

---

## Node 4: Classification

**Question:**
Why another node?

**Answer:**
Detection -> Found threat.
Classification -> How serious?
Different problem.

**Question:**
Explain Risk Score.

**Answer:**
Exactly: `Confidence + Bad IP + Previous Incidents + MITRE + CVE -> Risk Score -> Severity`
Your project uses weighted scoring rather than relying only on the LLM.

**Question:**
Why not GPT?

**Answer:**
Business Rules must be deterministic.

---

## Node 5: Response

**Question:**
What happens?

**Answer:**
Generate Response Actions. Store DB. Extract IoCs. Exactly your implementation.

**Question:**
Why Regex?

**Answer:**
Need IPs, Domains, Users, Hashes. Fast. Reliable.

---

## Human Approval

**Question:**
Why pause graph?

**Answer:**
Suppose Severity is Critical. AI should NOT automatically block the entire company. Need Human. Exactly why LangGraph interrupts before the approval node.

**Question:**
Why LangGraph interrupt?

**Answer:**
Because Execution Stops. Human Approves. Graph Resumes. Beautiful design.

---

## Report

**Question:**
Why Markdown?

**Answer:**
Easy. Portable. Readable. Auditable.

---

## PostgreSQL

**Question:**
Why PostgreSQL?

**Answer:**
Need Relationships.
`Incident -> Threats -> Artifacts -> Audit Logs -> Approvals`
Perfect Relational Model.

**Question:**
Why SQLAlchemy?

**Answer:**
ORM. Cleaner. Portable. Safer.

---

## AWS

**Question:**
How deploy?

**Answer:**
`Frontend -> S3 -> CloudFront -> ALB -> ECS -> FastAPI -> RDS -> MCP -> Secrets Manager`
Exactly what your deployment section describes.

---

## Biggest Design Decision

**Question:**
Why multiple agents instead of one huge prompt?

**Excellent answer:**
One agent doing everything -> Hard to debug. Hard to improve. Hard to test.
Multi-Agent -> One responsibility. Each node easy to replace.

---

## Hallucination

**Question:**
How reduce hallucination?

**Your answer:**
Never allow GPT to decide Severity. Never write Database. Never choose MITRE. Never calculate Risk.
GPT only extracts. Business Logic does everything else.
That's exactly how your architecture separates AI reasoning from deterministic logic.

---

## The killer question Rushikesh is likely to ask

**"Why did you build an MCP server instead of simply calling the APIs directly from your LangGraph node?"**

This is where many candidates fail.

**The answer is:**
"I wanted to decouple AI orchestration from tool implementation. The LangGraph agent only knows it needs capabilities like IP reputation, MITRE mapping, CVE lookup, or knowledge-base search. The MCP server abstracts those implementations behind a standard protocol. That makes the architecture modular—if I switch from AbuseIPDB to VirusTotal or add a new threat intelligence source, I only update the MCP server, not every AI agent. It also allows the same tools to be reused across different AI workflows."
