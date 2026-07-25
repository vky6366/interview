# Retrieval-Augmented Generation (RAG) Interview Guide

This guide covers everything you need to know about RAG, a critical architecture for building real-world generative AI applications.

---

## 1. Core Concepts

### What is RAG?
Retrieval-Augmented Generation (RAG) is a framework that improves the quality of Large Language Model (LLM) responses by grounding the model on external sources of knowledge. Instead of relying solely on its internal, pre-trained knowledge, a RAG system first retrieves relevant information from a database (like a company's internal documents) and then provides that information to the LLM as context to generate an accurate, up-to-date, and hallucination-free answer.

### The RAG Pipeline
Here is a step-by-step breakdown of a standard RAG pipeline:
1.  **Ingestion (PDF/Documents):** Raw data (e.g., PDFs, web pages, Notion docs) is collected and parsed into raw text.
2.  **Chunking:** The parsed text is broken down into smaller, manageable pieces called "chunks." This ensures that the text fits within the LLM's context window and that the embeddings represent specific, targeted information.
3.  **Embeddings:** Each text chunk is passed through an embedding model (e.g., OpenAI's `text-embedding-3-small`) to convert the semantic meaning of the chunk into a high-dimensional dense vector.
4.  **Vector DB (e.g., Qdrant, Pinecone, Chroma):** These embedding vectors, along with the original text chunk (metadata), are stored and indexed in a specialized Vector Database for fast retrieval.
5.  **User Query & Embedding:** When a user asks a question, the question itself is converted into an embedding vector using the *same* embedding model used in step 3.
6.  **Similarity Search:** The Vector DB performs a search (usually k-Nearest Neighbors) to find the top 'k' most similar document vectors to the user's query vector.
7.  **Context Construction:** The text chunks corresponding to the most similar vectors are retrieved.
8.  **LLM Generation:** The retrieved text chunks are injected into the prompt as context, along with the user's original query. The prompt looks something like: *"Given this context: [Retrieved Chunks], answer this question: [User Query]."*. The LLM then generates the final answer.

---

## 2. RAG vs. Fine-Tuning

A very common interview question is deciding when to use which approach.

### Difference between Fine-Tuning and RAG

| Feature | RAG (Retrieval-Augmented Generation) | Fine-Tuning |
| :--- | :--- | :--- |
| **Primary Use Case** | Injecting factual, dynamic, or private knowledge. Answering questions based on specific documents. | Changing the model's behavior, tone, style, or teaching it a new domain-specific language/task. |
| **Knowledge Updates** | Very easy. Just add, update, or delete documents in the Vector Database. | Difficult. Requires retraining the model (or adapters like LoRA) on a new dataset. |
| **Hallucination Risk** | Lower. The model is grounded by the retrieved context. | Higher. The model still relies on probabilistic generation from its internal weights. |
| **Interpretability** | High. You can see exactly which retrieved chunks the LLM used to generate the answer. | Low. It's difficult to know exactly why a fine-tuned model generated a specific response. |
| **Cost & Effort** | Generally lower compute cost, but requires maintaining database infrastructure. | High compute cost and significant effort required to curate high-quality training datasets. |

### Why RAG instead of fine-tuning?
You should choose RAG over fine-tuning when the primary goal is knowledge retrieval. Fine-tuning is meant for teaching a model *how* to act (e.g., talk like a pirate, output strictly JSON), while RAG is meant for teaching a model *what* to know (e.g., your company's HR policies). Furthermore, RAG allows for real-time knowledge updates without expensive retraining, prevents hallucinations by grounding answers, and offers source traceability.

---

## 3. Databases and Mathematics

### Why use Vector Databases?
Traditional relational databases (SQL) use keyword matching (lexical search), which fails if the exact words aren't present (e.g., searching for "automobile" won't find documents with "car").
Vector Databases are designed to store and query high-dimensional embeddings. They enable **semantic search**, meaning they search based on the *meaning* and *context* of the query rather than exact keyword matches. They use specialized indexing algorithms (like HNSW - Hierarchical Navigable Small World) to perform similarity searches across millions of vectors in milliseconds, something traditional databases cannot do efficiently.

### What is Cosine Similarity?
Cosine similarity is a metric used to measure how similar two vectors are, irrespective of their size or magnitude. It calculates the cosine of the angle between two vectors projected in a multi-dimensional space.
*   **Value Range:** -1 to 1.
*   **Meaning:**
    *   **1:** The vectors are pointing in the exact same direction (highly similar/identical meaning).
    *   **0:** The vectors are orthogonal (unrelated meaning).
    *   **-1:** The vectors are pointing in opposite directions (opposite meaning).
*   *Why use it in RAG?* When a user submits a query, cosine similarity is often the mathematical operation the Vector DB uses to compare the query embedding against the document embeddings to find the most relevant chunks.

---

## 4. Advanced RAG Concepts

To truly stand out, mention techniques that improve the basic RAG pipeline.

### Chunking Strategies
*   **Fixed-size chunking:** Splitting by a set number of characters or tokens with some overlap.
*   **Semantic chunking:** Splitting text logically based on sentences, paragraphs, or markdown headers (e.g., using LangChain's RecursiveCharacterTextSplitter).

### Advanced Retrieval Techniques
*   **Hybrid Search:** Combining traditional keyword search (BM25) with vector semantic search. This handles cases where exact names or IDs need to be matched perfectly alongside semantic meaning.
*   **Re-ranking (e.g., Cohere Rerank):** Using a smaller, more precise model (Cross-Encoder) to re-evaluate and re-order the top 'k' documents retrieved by the Vector DB before passing them to the LLM. This significantly improves context relevance.
*   **Query Expansion/Transformation:** Using an LLM to rewrite the user's initial query into multiple slightly different queries to ensure a broader and more robust retrieval.

### Evaluation Metrics (RAGAS / TruLens)
How do you know if your RAG system is good? You evaluate it on two fronts:
1.  **Retrieval Quality:**
    *   *Context Precision:* Did we retrieve only relevant information? (Are there distracting, irrelevant chunks?)
    *   *Context Recall:* Did we retrieve all the necessary information to answer the question?
2.  **Generation Quality:**
    *   *Faithfulness (No Hallucinations):* Is the LLM's answer directly supported by the retrieved context?
    *   *Answer Relevance:* Does the answer directly address the user's original query?
