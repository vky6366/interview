# Large Language Models (LLMs) Interview Guide

This guide covers fundamental and advanced concepts in Large Language Models (LLMs), a specialized branch of Deep Learning, to help you prepare for interviews.

---

## 1. Core Concepts

### What is an LLM?
A Large Language Model (LLM) is a type of artificial intelligence model designed to understand, generate, and interact with human language. They are typically based on the Transformer architecture and are pre-trained on massive amounts of text data. "Large" refers to both the massive number of parameters (often in the billions) the model has, and the vast size of the dataset it was trained on.

### Tokenization
Tokenization is the process of breaking down raw text into smaller, manageable pieces called tokens. A token can be a single character, a subword (like "sub" or "word" in "subword"), or a whole word. LLMs process these tokens, not raw text. Common tokenizers include Byte-Pair Encoding (BPE), WordPiece, and SentencePiece.

### Embeddings
An embedding is a numerical representation (a dense vector) of a token that captures its semantic meaning. Words with similar meanings will have embeddings that are close to each other in the high-dimensional vector space. Embeddings allow neural networks to process language by converting discrete tokens into continuous mathematical vectors.

### What is a Transformer?
Introduced in the seminal paper "Attention Is All You Need" (2017), the Transformer is a deep learning architecture that relies entirely on a mechanism called "self-attention" to compute representations of its input and output, eschewing recurrent (RNN) and convolutional (CNN) layers. It allows for highly parallelized processing of data, enabling the training of massive models.

### Self-Attention Mechanism
Self-attention is a mechanism that allows the model to weigh the importance of different words in a sentence relative to a specific word being processed. For example, in the sentence "The bank of the river," the attention mechanism helps the model understand that "bank" refers to a riverbank rather than a financial institution by heavily attending to the word "river." It computes "queries," "keys," and "values" for each token to determine these relationships.

---

## 2. Architectures & Models

### Difference between GPT and BERT
Both are based on the Transformer architecture but serve different purposes:
*   **BERT (Bidirectional Encoder Representations from Transformers):**
    *   *Architecture:* Uses only the **Encoder** part of the transformer.
    *   *Mechanism:* It reads the entire sequence of words at once (bidirectional).
    *   *Task:* Designed to understand the deep context of language. Good for tasks like sentiment analysis, named entity recognition, and question answering. It is trained using Masked Language Modeling (MLM).
*   **GPT (Generative Pre-trained Transformer):**
    *   *Architecture:* Uses only the **Decoder** part of the transformer.
    *   *Mechanism:* It reads words sequentially from left to right (unidirectional/autoregressive).
    *   *Task:* Designed for text generation. It predicts the next word in a sequence. Good for tasks like writing essays, translating languages, and writing code.

---

## 3. Inference Parameters

When generating text with an LLM, you can control its output using inference parameters.

### Temperature
Controls the randomness or "creativity" of the model's responses.
*   **Low Temperature (e.g., 0.1 - 0.3):** Makes the output more deterministic, focused, and predictable by favoring high-probability tokens. Good for factual answers or code generation.
*   **High Temperature (e.g., 0.7 - 1.0+):** Makes the output more diverse and creative by giving lower-probability tokens a higher chance of being selected. Good for brainstorming or creative writing.

### Top-P (Nucleus Sampling)
An alternative to Temperature. It controls the cumulative probability distribution of the next token.
*   If `top_p = 0.9`, the model will only consider the smallest set of tokens whose combined probability is at least 90%. It essentially cuts off the "long tail" of low-probability words. Like temperature, a lower Top-P makes the model more deterministic.

---

## 4. Prompt Engineering & Generation Techniques

Prompt engineering is the practice of designing and refining inputs (prompts) to get the desired output from an LLM.

### Zero-Shot Prompting
Asking the model to perform a task without providing any examples. The model relies entirely on its pre-trained knowledge.
*   *Example:* "Classify the sentiment of this sentence: 'I love this movie!'"

### Few-Shot Prompting
Providing the model with a few examples (demonstrations) of the task within the prompt before asking it to perform the task. This helps the model understand the desired format and pattern.
*   *Example:*
    "Awesome -> Positive
    Terrible -> Negative
    Okay -> Neutral
    I had a great day ->"

### Chain of Thought (CoT) Prompting
Encouraging the model to explain its reasoning step-by-step before arriving at a final answer. This significantly improves performance on complex reasoning, math, and logic problems.
*   *Example:* Instead of just asking for the answer, you add: "Let's think step by step."

---

## 5. Advanced Concepts & Challenges

### Hallucination
Occurs when an LLM generates information that is factually incorrect, nonsensical, or not supported by the given context, yet presents it confidently as the truth. This happens because LLMs are probabilistic models predicting the next word; they don't possess actual "understanding" or a built-in fact-checker.

### RAG (Retrieval-Augmented Generation)
A technique used to ground the LLM's responses in external knowledge sources to reduce hallucinations. It retrieves relevant documents from a database (often using vector embeddings) and provides them to the LLM as context within the prompt, allowing it to generate accurate answers based on the retrieved information.

### Fine-Tuning
The process of taking a pre-trained LLM and training it further on a smaller, specialized dataset to adapt it to a specific task or domain (e.g., medical texts, legal documents, or a specific company's coding style).

### LoRA (Low-Rank Adaptation)
A highly efficient parameter-efficient fine-tuning (PEFT) method. Instead of updating all the billions of weights in a pre-trained model (full fine-tuning), LoRA freezes the original weights and injects small, low-rank matrices into the model architecture, which are then trained. This drastically reduces the memory and compute requirements for fine-tuning.
