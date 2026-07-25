# LangGraph Interview Guide

As AI applications mature from simple chatbots to autonomous agents, frameworks like LangGraph are becoming highly sought-after. This guide covers the essentials of LangGraph.

---

## 1. Introduction

### Why LangGraph?
While LangChain is excellent for building linear chains (like RAG pipelines) and simple agents, it struggles when you need to build complex, reliable, and highly controllable agentic workflows.
LangGraph was built to solve this. It allows you to define complex agent architectures as **graphs**, enabling you to introduce loops (cycles), strict state management, human-in-the-loop approvals, and precise control over how an agent reasons and acts over time.

### Difference between LangChain and LangGraph

| Feature | LangChain (Chains/LCEL) | LangGraph |
| :--- | :--- | :--- |
| **Architecture** | Typically linear or Directed Acyclic Graphs (DAGs). | Supports **Cyclic Graphs** (loops). |
| **Execution Flow** | Flows from start to finish without looping back. | Can loop back on itself (e.g., an agent trying a tool, failing, and trying again). |
| **State Management** | Implicit, passed along the chain or managed via external Memory objects. | **Explicit and core to the framework**. State is maintained and updated at every step. |
| **Primary Use Case** | Data pipelines, Q&A, RAG, simple single-agent setups. | Complex multi-agent systems, highly autonomous workflows, human-in-the-loop applications. |

---

## 2. Core Concepts of LangGraph

LangGraph models applications as stateful graphs. Here are the three fundamental building blocks:

### 1. State
State is the central nervous system of a LangGraph application. It is a shared data structure (often a Python `TypedDict` or Pydantic model) that is passed between every component in the graph.
*   *How it works:* As the graph executes, each node receives the current State, performs its task, and returns an *update* to the State.
*   *Why it matters:* It ensures that every part of your complex agent system has access to the accumulated context, conversation history, and intermediate results.

### 2. Nodes
Nodes are the "workers" in the graph. A node is simply a Python function (or an LCEL runnable/chain) that receives the current State, does some work (like calling an LLM or executing a tool), and returns a State update.
*   *Examples:* An "Agent Node" that decides what tool to call; a "Tool Node" that actually executes a web search; a "Summarize Node" that condenses text.

### 3. Edges
Edges are the "routing logic" that connects Nodes together. They dictate the flow of execution.
*   **Standard Edges:** Unconditionally route from Node A to Node B. (e.g., after the Tool Node finishes, always go back to the Agent Node).
*   **Conditional Edges:** Use a function to inspect the current State and dynamically decide which Node to go to next based on the result.
    *   *Example:* If the Agent Node decides a tool is needed, route to the "Tool Node". If it decides it has the final answer, route to the "END" node.

---

## 3. The Power of Graphs

### Why use Graphs for Agents?
1.  **Loops and Cycles:** Unlike standard data pipelines (which are DAGs - Directed Acyclic Graphs), cognitive processes are inherently cyclical. An agent needs to reason, act, observe the result, and *loop back* to reason again. Graphs naturally model this cyclical behavior.
2.  **Controllability:** By explicitly defining Nodes and Conditional Edges, developers have granular control over the agent's logic. You aren't just relying on a black-box LLM to do the right thing; you define the guardrails and the exact flow.
3.  **Human-in-the-Loop (HitL):** Because LangGraph maintains explicit State, you can easily pause a graph at a specific Node, ask a human for approval or input, and then resume the graph from exactly where it left off.
4.  **Multi-Agent Architectures:** You can design systems where different nodes represent different specialized agents (e.g., a "Researcher" agent node passing state to a "Writer" agent node), allowing for sophisticated collaborative workflows.

### Checkpointers (Persistence)
LangGraph includes built-in persistence through Checkpointers (e.g., saving to SQLite or Postgres). Every time a node finishes, the State is saved. This provides:
*   **Memory:** Agents remember past interactions across different sessions.
*   **Time Travel:** You can rewind the graph to a previous state and replay it, which is invaluable for debugging complex agent failures.
