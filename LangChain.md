# LangChain Interview Guide

This guide covers the core concepts and components of LangChain, the most popular framework for developing applications powered by language models.

---

## 1. Introduction

### Why LangChain?
Large Language Models (LLMs) are powerful on their own, but they lack context about your specific data and cannot take actions in the real world. LangChain solves this by providing a standardized, modular framework to bridge the gap.
*   **Abstraction:** It provides simple, high-level APIs to interact with various LLM providers (OpenAI, Anthropic, local models), vector databases, and tools, so you don't have to write custom integrations for everything.
*   **Composability:** It allows you to link ("chain") different components together (e.g., Prompt -> LLM -> Output Parser) to create complex workflows.
*   **State Management (Memory):** It gives stateless LLMs the ability to remember past interactions.

---

## 2. Core Components (The Building Blocks)

### Prompt Template
A blueprint for generating prompts. Instead of hardcoding strings, Prompt Templates allow you to dynamically inject user inputs, context, or instructions into a standardized format before sending it to the LLM.
*   *Example:* `PromptTemplate.from_template("Tell me a joke about {topic}")`

### Output Parser
LLMs output raw text (strings). An Output Parser is used to structure that raw text into a more usable format, such as a JSON object, a Python dictionary, or a specific data schema (e.g., using Pydantic). It often works by injecting formatting instructions directly into the prompt.

### Retriever
An interface that returns documents given an unstructured query. While a Vector Store is a database that *stores* embeddings, a Retriever is the broader concept of fetching relevant information. It doesn't necessarily need to be backed by a vector store (e.g., it could be a Wikipedia retriever or a BM25 keyword retriever).

### Memory
LLMs are inherently stateless; they process each request independently. Memory is the component that allows the system to remember previous parts of a conversation. It stores chat history and injects it into the prompt so the LLM has conversational context.
*   *Types:* `ConversationBufferMemory` (stores everything), `ConversationSummaryMemory` (uses an LLM to summarize past chat to save token space).

### Tool
A function or capability that an Agent can use to interact with the outside world. Tools give LLMs "hands."
*   *Examples:* Web Search (Tavily/Google Search), Python REPL (to execute code), a SQL Database connector, or a custom API endpoint (like fetching weather).

---

## 3. Workflows: Chains vs. Agents

This is a crucial distinction in LangChain.

### Chain
A predetermined, hardcoded sequence of operations. The flow of execution is fixed by the developer.
*   *How it works:* Step A happens, its output is passed to Step B, which passes to Step C.
*   *Example (LLMChain):* Take user input -> Put it into a Prompt Template -> Send to LLM -> Parse Output.
*   *When to use:* For structured, predictable tasks (like summarizing a document or translating text) where you know exactly what steps need to happen.

### Agent
A dynamic workflow where the **LLM decides** the sequence of operations. The developer provides the LLM with a goal and a set of **Tools**, and the LLM determines which tools to use and in what order to achieve the goal.
*   *How it works:* The Agent receives a prompt, "thinks" about what to do, selects a tool, observes the tool's output, thinks again, and repeats until it determines the final answer is reached (often using a framework like ReAct - Reason and Act).
*   *When to use:* For complex, open-ended tasks where the required steps aren't known upfront (e.g., "Research the current stock price of Apple, compare it to last month, and write a summary report").

### Summary: Chain vs. Agent
| Feature | Chain | Agent |
| :--- | :--- | :--- |
| **Control Flow** | Deterministic (Hardcoded by developer) | Non-deterministic (Decided by the LLM) |
| **Flexibility** | Low (Follows a strict path) | High (Adapts based on tool outputs) |
| **Reliability** | Very High (Predictable) | Lower (Prone to infinite loops or bad tool choices) |
| **Use Case** | RAG pipelines, summarization, simple Q&A | Autonomous tasks, research, complex problem solving |

---

## 4. Advanced Concepts

### LCEL (LangChain Expression Language)
A declarative way to compose chains together. It makes it much easier to build complex pipelines using a pipe `|` operator (similar to Unix pipes).
*   *Example:* `chain = prompt | model | output_parser`
*   *Benefits:* It automatically handles streaming, asynchronous execution, and parallel processing under the hood.

### Document Loaders
The entry point for bringing data into LangChain. They load data from various sources (PDFs, CSVs, Notion, SQL databases, Web pages) and convert them into standard LangChain `Document` objects (which contain `page_content` and `metadata`).
