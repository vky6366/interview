# Graph Data Structures & Algorithms in C++ — Master Interview Repository

> **Target Role:** Infosys Specialist Programmer (SP) L3 Interview  
> **Topic Scope:** Graph Fundamentals, Representations (Adjacency Matrix & Adjacency List), Traversals (BFS, DFS), Cycle Detection, Shortest Path & Topological Sort.

---

## 🧭 Graph Representations at a Glance

```mermaid
graph TD
    GR[Graph Representations in C++]
    GR --> AM[Adjacency Matrix: 2D Array<br/>int adj[V][V]<br/>Space: O(V²)<br/>Edge Lookup: O(1)<br/>Best for: Dense Graphs & Floyd-Warshall]
    GR --> AL[Adjacency List: Vector of Vectors<br/>vector<vector<int>> adj<br/>Space: O(V + E)<br/>Edge Lookup: O(deg(u))<br/>Best for: Sparse Graphs & BFS/DFS/Dijkstra]
```

---

## 📚 Master Topic Index & Curriculum Roadmap

| Module | File | Core Concepts Covered |
| :--- | :--- | :--- |
| **01** | [01. Graph Representations (Matrix vs. List)](file:///d:/interview/Infosys/C++/Graphs/01-graph-representation-matrix-and-list.md) | Graph Terminology (Directed/Undirected, Weighted/Unweighted, Degree, Handshaking Lemma), Adjacency Matrix implementation & $O(V^2)$ analysis, Adjacency List implementation & $O(V+E)$ analysis, Decision Matrix, Tree vs. Graph comparative breakdown, Top Interview Q&A. |

---

## ⚡ Key Graph Complexity Cheat Sheet

| Operation | Adjacency Matrix (`int adj[V][V]`) | Adjacency List (`vector<vector<int>> adj`) |
| :--- | :---: | :---: |
| **Space Complexity** | $\mathbf{O(V^2)}$ | $\mathbf{O(V + E)}$ |
| **Add Vertex** | $O(V^2)$ | $O(1)$ |
| **Add Edge** | $O(1)$ | $O(1)$ |
| **Remove Edge** | $O(1)$ | $O(\text{deg}(u))$ |
| **Query Edge Existence (`u -> v`)** | $\mathbf{O(1)}$ | $O(\text{deg}(u))$ |
| **Iterate All Neighbors of `u`** | $O(V)$ | $\mathbf{O(\text{deg}(u))}$ |
| **BFS / DFS Traversal Time** | $O(V^2)$ | $\mathbf{O(V + E)}$ |
