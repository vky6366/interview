# Navigation & Path Planning for Autonomous Robots: Master Technical Interview Guide
**Role Target:** Robotics Intern – Autonomy (ATI Robotics)  
**Focus Areas:** Graph Search (A*, Dijkstra, BFS), Costmaps & C-Space, Sampling-Based Planning (RRT/RRT*, PRM), Local Planning (DWA, TEB), Kinematics & Trajectory Generation  
**Level:** Comprehensive Foundational Theory to Advanced Mathematical & Algorithmic Interview Mastery  

---

## 📌 Categorization Legend
- 🔴 **[MUST KNOW]**: Mandatory for passing the technical interview. High probability of live whiteboard coding, grid tracing, or mathematical derivations.
- 🟡 **[GOOD TO KNOW]**: Demonstrates engineering depth and strong systems understanding; distinguishes top candidates during follow-ups.
- 🔵 **[ADVANCED / OPTIONAL]**: Specialized kinematic formulations, non-holonomic trajectory optimization, and state lattice planners.
- ⚠️ **[INTERVIEW TRAP]**: Common misconceptions, edge cases, and theoretical pitfalls tested in interviews.
- 🤖 **[ROBOTICS CONNECTION]**: Direct application to autonomous mobile robots (AMRs), industrial tuggers (e.g., ATI Sherpa), warehouse AGVs, and self-driving vehicles.

---

# Table of Contents
1. [What is Robot Navigation?](#1-what-is-robot-navigation)
2. [Path vs. Trajectory (Crucial Distinction)](#2-path-vs-trajectory--very-important)
3. [Robot Geometric & Kinematic Representation](#3-robot-representation)
4. [Configuration Space (C-Space & Minkowski Sums)](#4-configuration-space)
5. [Occupancy Grids](#5-occupancy-grid)
6. [Costmaps & Inflation Layers](#6-costmaps)
7. [Graph Search Fundamentals](#7-graph-search-fundamentals)
8. [Breadth-First Search (BFS)](#8-bfs--must-know)
9. [Depth-First Search (DFS)](#9-dfs)
10. [Dijkstra's Algorithm](#10-dijkstra--high-priority)
11. [A* Search Algorithm (Core Principles)](#11-a--extremely-important)
12. [A* Step-by-Step Hand-Solving Grid Problems](#12-a-step-by-step-grid-problem)
13. [A* Implementation (Python & C++)](#13-a-implementation)
14. [A* High-Frequency Interview Questions](#14-a-interview-questions)
15. [Heuristics & Mathematical Admissibility](#15-heuristics)
16. [Search Algorithm Master Comparison](#16-search-algorithm-comparison)
17. [Greedy Best-First Search](#17-greedy-best-first-search)
18. [Global Planning vs. Local Planning](#18-global-vs-local-planning)
19. [Local Planning & Dynamic Window Approach (DWA)](#19-local-planning)
20. [Path Smoothing & Geometric Splines](#20-path-smoothing)
21. [Trajectory Generation & Jerk Optimization](#21-trajectory-generation)
22. [Kinematic Constraints: Holonomic vs. Non-Holonomic](#22-kinematic-constraints)
23. [Differential-Drive Kinematics & Unicycle Model](#23-differential-drive-robot)
24. [Car-Like Robot Kinematics (Bicycle Model & Dubins/Reeds-Shepp)](#24-car-like-robot)
25. [Collision Checking & Geometric Intersection Tests](#25-collision-checking)
26. [Sampling-Based Planning Foundations](#26-sampling-based-planning)
27. [Rapidly-Exploring Random Trees (RRT & RRT*)](#27-rrt-step-by-step)
28. [Probabilistic Roadmap (PRM)](#28-prm)
29. [Multi-Objective Optimal Path Planning](#29-optimal-path-planning)
30. [Obstacle Avoidance Paradigms](#30-obstacle-avoidance)
31. [Artificial Potential Field Method](#31-potential-field-method)
32. [Dynamic Obstacles & Time-Expanded Planning](#32-dynamic-obstacles)
33. [Replanning & Incremental Search (D* / D* Lite)](#33-replanning)
34. [10 Navigation Failure Modes & Diagnostic Fixes](#34-navigation-failure-modes)
35. [Planning vs. Control Interaction](#35-planning-vs-control)
36. [Navigation & Localization Coupling](#36-navigation--localization)
37. [Coordinate Frames & Spatial Transformations (TF2)](#37-coordinate-frames)
38. [Autonomous Navigation System Architecture](#38-navigation-system-architecture)
39. [ROS2 Navigation Stack (Nav2 Architecture)](#39-ros2-navigation-connection)
40. [Algorithm Asymptotic Complexity Cheat Sheet](#40-algorithm-complexity)
41. [Progressive Python Coding Problems](#41-python-coding-problems)
42. [Interview-Ready C++ Coding Problems](#42-c-coding-problems)
43. [20+ Hand-Solvable Mathematical Interview Problems](#43-mathematical-problems)
44. [Whiteboard Reasoning & Scenario Questions](#44-whiteboard-problems)
45. [Full Autonomy System Design Interview Problem](#45-system-design-interview-question)
46. [50+ Core Navigation Interview Questions](#46-common-interview-questions)
47. [Common Interview Traps & Fallacies](#47-common-interview-traps)
48. [Navigation & Planning Master Cheat Sheet](#48-cheat-sheet)
49. [30-Minute Pre-Interview Revision Sheet](#49-30-minute-pre-interview-revision)
50. [Mock Interview Readiness Test (with Complete Solutions)](#50-interview-readiness-test)

---

# 1. What is Robot Navigation?

### Core Definition 🔴 [MUST KNOW]
Autonomous Robot Navigation is the capability of a mobile robotic system to determine its own position within an environmental reference frame, understand its surrounding geometry, and plan and safely execute collision-free motions to reach a desired destination goal.

---

### The Complete Autonomous Sense-Plan-Act Loop 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
|                         AUTONOMOUS NAVIGATION PIPELINE                             |
+------------------------------------------------------------------------------------+
|                                                                                    |
|  1. SENSORS           [ LiDAR 2D/3D ]    [ Wheel Encoders ]    [ IMU 6-DOF ]       |
|                             │                   │                   │              |
|                             ▼                   ▼                   ▼              |
|  2. PERCEPTION        [ Point-Cloud Filter / Ground Removal / Clustering ]         |
|                             │                                                      |
|                             ▼                                                      |
|  3. LOCALIZATION      [ EKF / Particle Filter (AMCL) / SLAM ] ──> Pose (x, y, θ)   |
|                             │                                                      |
|                             ▼                                                      |
|  4. MAPPING           [ 2D Occupancy Grid / 3D Voxel Octree / Costmap Layering ]   |
|                             │                                                      |
|                             ▼                                                      |
|  5. GLOBAL PLANNING   [ Global Path Planner (A*, Dijkstra, RRT*) ] (1-2 Hz)        |
|                             │ Global Waypoint Path: { (x0, y0), (x1, y1), ... }    |
|                             ▼                                                      |
|  6. LOCAL PLANNING    [ Local Trajectory Planner (DWA, TEB, MPC) ] (20-50 Hz)      |
|                             │ Local Feasible Trajectory: { (x(t), y(t), v(t), ω(t))|
|                             ▼                                                      |
|  7. CONTROL           [ Path Tracker (Pure Pursuit, Stanley, Motor PID) ] (100 Hz) |
|                             │ Motor Voltage / Torque Commands (PWM / CAN Frames)   |
|                             ▼                                                      |
|  8. ACTUATION         [ Motor Drivers ──> Wheel Hub Motors ──> Robot Motion ]      |
|                                                                                    |
+------------------------------------------------------------------------------------+
```

---

### Key Terminology Disambiguation 🔴 [MUST KNOW]
- **Navigation:** The overarching umbrella process that integrates Localization, Mapping, Path Planning, Obstacle Avoidance, and Motor Control.
- **Path Planning:** Purely geometric computation of a collision-free curve/polyline in space connecting start to goal without any time or velocity parameterization.
- **Motion Planning:** Planning motions under kinematic and differential constraints (e.g., steering limits, arm joint limits).
- **Trajectory Planning:** Generating a time-parameterized path specifying position, linear velocity, angular velocity, and acceleration at every instant: $\mathbf{s}(t) = [x(t), y(t), \theta(t), v(t), \omega(t), a(t)]^T$.
- **Control:** Generating low-level actuator commands (wheel torques, PWM duty cycles) to force the physical hardware to track the planned trajectory despite friction, wheel slip, and disturbances.

---

# 2. Path vs. Trajectory — VERY IMPORTANT

```
+-----------------------------------+------------------------------------+
| Feature                           | Geometric Path                     | Time-Parameterized Trajectory     |
+-----------------------------------+------------------------------------+
| Definition                        | Pure spatial curve in workspace:   | Spatial curve + Time profile:      |
|                                   | $\sigma(s) = (x(s), y(s))$         | $\mathbf{q}(t) = (x(t), y(t), v(t))|
| Time Dependency                   | Independent of time ($t$)          | Explicitly indexed by time ($t$)   |
| Velocity / Acceleration           | Contains no velocity/accel profile | Explicit $v(t)$, $\omega(t)$, $a(t)$|
| Dynamic Constraints               | Ignores motor torque limits & slip | Constrained by actuator & friction |
| Generated By                      | Global Planner (A*, Dijkstra, RRT*)| Local Planner / Trajectory Gen     |
+-----------------------------------+------------------------------------+
```

> ⚠️ **INTERVIEW TRAP**: An interviewer will ask: *"Can a differential drive robot directly follow a geometric path produced by A*?"*  
> **Answer:** *"No. An A* grid path consists of sharp, discontinuous point-to-point line segments with instantaneous $90^\circ$ or $45^\circ$ heading changes. A physical robot with mass and non-zero inertia cannot achieve infinite angular acceleration ($\dot{\omega} = \infty$) to execute instantaneous heading changes. The geometric path must first be smoothed into a kinematically feasible, continuous-curvature trajectory with bounded velocity, acceleration, and jerk."*

---

# 3. Robot Representation

### Geometric Models for Collision Checking 🔴 [MUST KNOW]

```
1. Point Robot:           2. Circular Robot:         3. Oriented Bounding Box (OBB):
        •                        ┌───────┐                  ┌─────────────────┐
     (x, y)                      │   •   │ Radius R         │        • (x,y,θ)│ Length L
                                 └───────┘                  └─────────────────┘
                                                                  Width W
```

- **Point Robot ($\mathbb{R}^2$):** Assumes robot has zero radius. Used only after expanding obstacles via Configuration Space.
- **Circular Robot ($\text{Radius } R$):** Invariant to robot orientation ($\theta$). Collision checking requires only Euclidean distance testing between obstacle points and robot center: $\text{dist}(\mathbf{p}_{\text{obs}}, \mathbf{p}_{\text{robot}}) \le R$. Computationally trivial.
- **Oriented Bounding Box (OBB - Length $L$, Width $W$, Heading $\theta$):** Necessary for rectangular industrial tuggers (e.g. ATI Sherpa). Requires checking polygonal intersections or Separating Axis Theorem (SAT). Highly orientation-dependent.

---

# 4. Configuration Space

### What is Configuration Space ($\mathcal{C}\text{-Space}$)? 🔴 [MUST KNOW]
The Configuration Space ($\mathcal{C}$) of a robot is the space of all possible configurations (poses) the robot can attain.
- For a 2D planar mobile robot: $\mathcal{C} = \mathbb{R}^2 \times SO(2) = (x, y, \theta)$ (3 Degrees of Freedom).
- $\mathcal{C}\text{-Space}$ is partitioned into two disjoint sets:
  1. **$\mathcal{C}_{\text{free}}$ (Free Space):** Configurations where the robot does not intersect any obstacle.
  2. **$\mathcal{C}_{\text{obs}}$ (Obstacle Space):** Configurations that cause a collision between the robot body and the environment.

---

### The Minkowski Sum & Obstacle Expansion 🔴 [MUST KNOW]
To avoid performing expensive geometric polygon collision checks at every step of search, we **shrink the robot to a single point** and **inflate the environmental obstacles** by the robot's geometry using the **Minkowski Sum ($\oplus$)**:

$$\mathcal{C}_{\text{obs}} = \mathcal{W}_{\text{obs}} \oplus (-\mathcal{A}(0)) = \{ \mathbf{p} + \mathbf{r} \mid \mathbf{p} \in \mathcal{W}_{\text{obs}}, \, \mathbf{r} \in -\mathcal{A}(0) \}$$

where $\mathcal{W}_{\text{obs}}$ is the workspace obstacle and $\mathcal{A}(0)$ is the robot footprint centered at the origin.

```
Workspace (Real World):                   Configuration Space (C-Space):

  ┌──────────────┐                          ┌────────────────────┐
  │ Obstacle     │                          │ Inflated Obstacle  │
  └──────────────┘       Minkowski Sum      │ (Expanded by R)    │
                         ─────────────>     └────────────────────┘
     ┌───────┐                                        •
     │ Robot │ Radius R                          Point Robot
     └───────┘
```

> 🤖 **ROBOTICS CONNECTION**: In 2D grid planning, inflating all obstacles by the robot's inscribed radius $R_{\text{inscribed}}$ transforms complex polygon-robot collision testing into a single $O(1)$ grid lookup: `if (grid[x][y] == OCCUPIED)`.

---

# 5. Occupancy Grid

### Grid Representation & Resolution Tradeoffs 🔴 [MUST KNOW]
An Occupancy Grid discretizes continuous 2D space into a regular matrix of square cells, where each cell $(i, j)$ represents the probability that the region is occupied:
- `0`: Free space (navigable).
- `100`: Lethal obstacle (wall, machine, pallet).
- `-1` or `255`: Unknown space (unmapped).

```
Occupancy Grid Layout (5x5 Grid):
  (Row 0)   S  .  .  #  .      Legend:
            .  #  .  #  .      S = Start (0, 0)
            .  #  .  .  .      G = Goal  (3, 4)
            .  .  .  #  G      # = Occupied Cell (Obstacle)
  (Row 4)   .  .  .  .  .      . = Free Cell
           (Col 0)    (Col 4)
```

---

### Resolution vs. Memory vs. Computation Tradeoff 🔴 [MUST KNOW]

$$\text{Memory Cells} = \left(\frac{\text{Map Width (m)}}{\text{Resolution (m/cell)}}\right) \times \left(\frac{\text{Map Height (m)}}{\text{Resolution (m/cell)}}\right)$$

```
+--------------------+-------------------------+-------------------------+----------------------------------+
| Resolution (m/cell)| 100m x 100m Warehouse   | Memory Usage (1 byte/cl)| A* Graph Expansion Time (Nodes)  |
+--------------------+-------------------------+-------------------------+----------------------------------+
| 0.50 m (Coarse)    | 200 x 200 = 40,000 cells| 40 KB                   | ~1 ms (Blazing fast, cuts corners|
| 0.05 m (Standard)  | 2,000 x 2,000 = 4M cells| 4.0 MB                  | ~50 ms (Precise for docking)     |
| 0.01 m (Fine)      | 10k x 10k = 100M cells  | 100.0 MB                | ~2.5 s (Too slow for real-time)  |
+--------------------+-------------------------+-------------------------+----------------------------------+
```

---

# 6. Costmaps

### Occupancy Grid vs. Costmap with Inflation Layers 🔴 [MUST KNOW]
A binary occupancy grid only knows `0` (Free) and `100` (Obstacle). A path planner running on a binary grid will plan paths that scrape millimeters against walls. A **Costmap** assigns a continuous cost penalty gradient that decays exponentially away from obstacles.

```
Cost Value
  ▲
254 ┼ ─── Lethal Obstacle (Physical Obstacle Cell)
253 ┼ ─── Inscribed Cost (Robot Center here causes guaranteed collision)
    │     \
    │      \  Decay Cost: cost = 253 * exp(-k * (dist - r_inscribed))
    │       \
  1 ┼ - - - - \ - - - - - - - - Free Space Threshold (Cost = 0)
  0 ┼──────────────────────────────► Distance from Obstacle (meters)
    0     r_inscribed   r_inflation
```

```
Costmap Inflation Zones:
  [████] Lethal Obstacle (Cost = 254)
  [▓▓▓▓] Inscribed Inflation Zone: Distance < R_robot (Cost = 253) -> LETHAL FOR PLANNER
  [▒▒▒▒] Non-Lethal Decay Zone (Cost = 1 to 252) -> Plan here only if no other path
  [    ] Free Space (Cost = 0)
```

---

# 7. Graph Search Fundamentals

### Converting a Continuous World into a Search Graph 🔴 [MUST KNOW]
- **Node ($V$):** A discretized grid cell coordinate $(r, c)$ or continuous waypoint $(x, y, \theta)$.
- **Edge ($E$):** A valid kinematic transition connecting two adjacent nodes.
- **Edge Cost ($c(u, v)$):** The physical distance or energy penalty to traverse from node $u$ to node $v$.
  - 4-Connected Grid: Up, Down, Left, Right (Cost = $1.0$).
  - 8-Connected Grid: Includes Diagonals (Diagonal Cost = $\sqrt{2} \approx 1.414$).

---

# 8. BFS — MUST KNOW

### Breadth-First Search (BFS) Mechanics 🔴 [MUST KNOW]
- **Data Structure:** First-In-First-Out (FIFO) **Queue** (`std::queue` / `collections.deque`).
- **Property:** Guarantees finding the **shortest path in terms of the number of edges** on unweighted graphs ($c(u, v) = 1$).
- **Time Complexity:** $O(|V| + |E|)$.
- **Space Complexity:** $O(|V|)$ (Stores full wavefront frontier in RAM).

```
Wavefront Expansion from Start (S):
  3  2  1  2  3
  2  1  S  1  2     Expands uniformly in concentric circles (Radial Wavefront)
  3  2  1  2  3
```

---

# 9. DFS

### Depth-First Search (DFS) Mechanics 🔴 [MUST KNOW]
- **Data Structure:** Last-In-First-Out (LIFO) **Stack** (`std::stack` or recursion).
- **Property:** Plunges deeply along a single branch until hitting an obstacle or dead end before backtracking.
- ⚠️ **INTERVIEW TRAP:** **DFS DOES NOT FIND THE SHORTEST PATH.** It can produce wildly suboptimal, zigzag paths in robotics and can get trapped in infinite loops on cyclic graphs without a visited set.

---

# 10. Dijkstra — HIGH PRIORITY

### Dijkstra’s Algorithm Mechanics 🔴 [MUST KNOW]
- **Purpose:** Finds the guaranteed shortest path on **weighted graphs** with non-negative edge costs ($c(u, v) \ge 0$).
- **Data Structure:** **Min-Priority Queue** (Binary Heap) ordered by cumulative path cost $g(n)$.
- **Relaxation Step:** For edge $(u, v)$ with cost $c(u, v)$:
  $$\text{if } g(u) + c(u, v) < g(v): \quad g(v) = g(u) + c(u, v), \quad \text{parent}[v] = u$$

```
Algorithm Step-by-Step:
1. Initialize g[start] = 0, and g[v] = infinity for all other nodes v.
2. Insert (g[start], start) into Min-Priority Queue (Open Set).
3. While Open Set is not empty:
   a. Pop node u with smallest g(u).
   b. If u == goal, reconstruct and return path.
   c. If u already in Closed Set (visited), continue.
   d. Add u to Closed Set.
   e. For each neighbor v of u:
      If v not in Closed Set and g(u) + cost(u, v) < g(v):
         g(v) = g(u) + cost(u, v)
         parent[v] = u
         Push (g(v), v) into Open Set.
```

---

# 11. A* — EXTREMELY IMPORTANT

### The Core A* Equation 🔴 [MUST KNOW]

$$f(n) = g(n) + h(n)$$

- **$g(n)$ (Exact Past Cost):** The exact cost of the shortest path discovered so far from the start node to node $n$.
- **$h(n)$ (Heuristic Future Estimate):** An estimated cost to travel from node $n$ to the goal.
- **$f(n)$ (Total Estimated Cost):** The estimated total cost of the cheapest path passing through node $n$ from start to goal.

---

### Standard Metric Heuristics 🔴 [MUST KNOW]

```
+--------------------+---------------------------------------+------------------------------------------+
| Heuristic Metric   | Mathematical Formula                  | Appropriate Motion Grid Model            |
+--------------------+---------------------------------------+------------------------------------------+
| Manhattan Distance | $h(n) = |x_n - x_g| + |y_n - y_g|$     | 4-Connected Grid (No diagonal motion)    |
| Euclidean Distance | $h(n) = \sqrt{(x_n - x_g)^2 + (y_n - y_g)^2}$ | Continuous Space / Any-angle motion|
| Octile Distance    | $h(n) = \Delta x + \Delta y + (\sqrt{2}-2)\min(\Delta x, \Delta y)$ | 8-Connected Grid (Diagonals cost $\sqrt{2}$) |
| Chebyshev Distance | $h(n) = \max(|x_n - x_g|, |y_n - y_g|)$| 8-Connected Grid (Diagonals cost $1.0$)  |
+--------------------+---------------------------------------+------------------------------------------+
```

---

# 12. A* Step-by-Step Grid Problem

### Hand-Trace Example 1: 4-Connected Grid 🔴 [MUST KNOW]
Given a $4 \times 4$ grid where movement cost is $1.0$ per orthogonal step. Manhattan heuristic $h(r, c) = |r - r_g| + |c - c_g|$ is used.
Start = $(0, 0)$, Goal = $(3, 3)$.

```
Grid Layout:
      Col 0   Col 1   Col 2   Col 3
Row 0 [ S ]   [ . ]   [ # ]   [ . ]       Legend:
Row 1 [ . ]   [ # ]   [ . ]   [ . ]       S = Start (0, 0)
Row 2 [ . ]   [ . ]   [ . ]   [ # ]       G = Goal  (3, 3)
Row 3 [ # ]   [ . ]   [ . ]   [ G ]       # = Obstacle
```

#### Step-by-Step Hand Execution:
1. **Initialize:** $g(0,0) = 0$, $h(0,0) = |3-0| + |3-0| = 6$. $f(0,0) = 0 + 6 = \mathbf{6}$.  
   `OpenSet = { (0,0): f=6 }`, `ClosedSet = {}`.

2. **Iteration 1:** Pop $(0,0)$ ($f=6, g=0$). Add to ClosedSet.  
   Neighbors of $(0,0)$:
   - Down $(1,0)$: $g=1, h=|3-1|+|3-0|=5 \implies f = 1 + 5 = \mathbf{6}$. Push $(1,0)$.
   - Right $(0,1)$: $g=1, h=|3-0|+|3-1|=5 \implies f = 1 + 5 = \mathbf{6}$. Push $(0,1)$.  
   `OpenSet = { (1,0): f=6, (0,1): f=6 }`.

3. **Iteration 2:** Pop $(1,0)$ ($f=6, g=1$). Add to ClosedSet.  
   Neighbors of $(1,0)$:
   - Down $(2,0)$: $g=2, h=|3-2|+|3-0|=4 \implies f = 2 + 4 = \mathbf{6}$. Push $(2,0)$.
   - Right $(1,1)$ is Obstacle `[#]`. Skip.  
   `OpenSet = { (2,0): f=6, (0,1): f=6 }`.

4. **Iteration 3:** Pop $(2,0)$ ($f=6, g=2$). Add to ClosedSet.  
   Neighbors of $(2,0)$:
   - Down $(3,0)$ is Obstacle `[#]`. Skip.
   - Right $(2,1)$: $g=3, h=|3-2|+|3-1|=3 \implies f = 3 + 3 = \mathbf{6}$. Push $(2,1)$.  
   `OpenSet = { (2,1): f=6, (0,1): f=6 }`.

5. **Iteration 4:** Pop $(2,1)$ ($f=6, g=3$). Add to ClosedSet.  
   Neighbors of $(2,1)$:
   - Right $(2,2)$: $g=4, h=|3-2|+|3-2|=2 \implies f = 4 + 2 = \mathbf{6}$. Push $(2,2)$.
   - Down $(3,1)$: $g=4, h=|3-3|+|3-1|=2 \implies f = 4 + 2 = \mathbf{6}$. Push $(3,1)$.  
   `OpenSet = { (2,2): f=6, (3,1): f=6, (0,1): f=6 }`.

6. **Iteration 5:** Pop $(3,1)$ ($f=6, g=4$). Add to ClosedSet.  
   Neighbors of $(3,1)$:
   - Right $(3,2)$: $g=5, h=|3-3|+|3-2|=1 \implies f = 5 + 1 = \mathbf{6}$. Push $(3,2)$.  
   `OpenSet = { (3,2): f=6, (2,2): f=6, (0,1): f=6 }`.

7. **Iteration 6:** Pop $(3,2)$ ($f=6, g=5$). Add to ClosedSet.  
   Neighbors of $(3,2)$:
   - Right $(3,3)$ [GOAL!]: $g=6, h=0 \implies f = 6 + 0 = \mathbf{6}$. Push $(3,3)$.

8. **Iteration 7:** Pop $(3,3)$ [Goal reached].  
   **Path Reconstruction:** $(0,0) \to (1,0) \to (2,0) \to (2,1) \to (3,1) \to (3,2) \to (3,3)$.  
   **Total Path Cost:** $g = 6.0$.

---

# 13. A* Implementation

### Clean, Production-Grade C++ A* Implementation 🔴 [MUST KNOW]

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>

struct Node {
    int r, c;
    double g_cost;
    double f_cost;

    bool operator>(const Node& other) const {
        return f_cost > other.f_cost; // Min-Heap comparator
    }
};

class AStarGridPlanner {
private:
    int rows_, cols_;
    std::vector<std::vector<int>> grid_; // 0: Free, 1: Obstacle

    double calculateHeuristic(int r, int c, int gr, int gc) {
        // Euclidean Heuristic
        return std::hypot(r - gr, c - gc);
    }

public:
    AStarGridPlanner(const std::vector<std::vector<int>>& grid) 
        : grid_(grid), rows_(grid.size()), cols_(grid[0].size()) {}

    std::vector<std::pair<int, int>> plan(std::pair<int, int> start, std::pair<int, int> goal) {
        auto [sr, sc] = start;
        auto [gr, gc] = goal;

        if (grid_[sr][sc] == 1 || grid_[gr][gc] == 1) return {}; // Blocked

        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
        std::vector<std::vector<double>> g_costs(rows_, std::vector<double>(cols_, 1e9));
        std::vector<std::vector<std::pair<int, int>>> parent(rows_, std::vector<std::pair<int, int>>(cols_, {-1, -1}));
        std::vector<std::vector<bool>> closed_set(rows_, std::vector<bool>(cols_, false));

        g_costs[sr][sc] = 0.0;
        double f_start = calculateHeuristic(sr, sc, gr, gc);
        open_set.push({sr, sc, 0.0, f_start});

        // 8-Connected motion offsets
        int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};
        double costs[] = {1.0, 1.0, 1.0, 1.0, 1.414, 1.414, 1.414, 1.414};

        while (!open_set.empty()) {
            Node current = open_set.top();
            open_set.pop();

            int r = current.r;
            int c = current.c;

            if (r == gr && c == gc) {
                // Reconstruct Path
                std::vector<std::pair<int, int>> path;
                std::pair<int, int> curr = goal;
                while (curr != std::make_pair(-1, -1)) {
                    path.push_back(curr);
                    if (curr == start) break;
                    curr = parent[curr.first][curr.second];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            if (closed_set[r][c]) continue;
            closed_set[r][c] = true;

            for (int i = 0; i < 8; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < rows_ && nc >= 0 && nc < cols_) {
                    if (grid_[nr][nc] == 1 || closed_set[nr][nc]) continue;

                    double tentative_g = g_costs[r][c] + costs[i];
                    if (tentative_g < g_costs[nr][nc]) {
                        g_costs[nr][nc] = tentative_g;
                        parent[nr][nc] = {r, c};
                        double f = tentative_g + calculateHeuristic(nr, nc, gr, gc);
                        open_set.push({nr, nc, tentative_g, f});
                    }
                }
            }
        }
        return {}; // No valid path found
    }
};
```

---

# 14. A* Interview Questions

### High-Frequency Interview Probing & Model Responses 🔴 [MUST KNOW]

#### Q1: Why is A* faster than Dijkstra in practice?
- **Answer:** Dijkstra expands nodes radially in all directions like an expanding circle ($f = g$). A* uses the heuristic $h(n)$ to bias node expansion directly toward the goal, creating a focused, directed ellipse and exploring dramatically fewer nodes.

#### Q2: What happens if $h(n) = 0$ for all nodes?
- **Answer:** A* becomes mathematically identical to **Dijkstra’s algorithm** ($f(n) = g(n) + 0 = g(n)$).

#### Q3: What is an Admissible Heuristic?
- **Answer:** A heuristic is **admissible** if it **never overestimates** the true minimal cost to reach the goal: $h(n) \le h^*(n)$ for all $n$, where $h^*(n)$ is the true optimal cost. Admissibility guarantees that A* will find the mathematically optimal shortest path.

#### Q4: What is a Consistent (Monotonic) Heuristic?
- **Answer:** A heuristic is **consistent** if for every node $n$ and every neighbor $p$ generated by action $a$:
  $$h(n) \le c(n, p) + h(p)$$
  Consistency satisfies the triangle inequality. It guarantees that once a node is expanded (popped from the open set), its shortest path $g(n)$ is final, and it never needs to be reopened.

#### Q5: What happens if $h(n)$ overestimates the true cost ($h(n) > h^*(n)$)?
- **Answer:** A* loses its guarantee of optimality (it may return a suboptimal path), but search speed often increases dramatically because it behaves more aggressively like Greedy Best-First Search.

---

# 15. Heuristics

### Weighted A* ($w\text{-A*}$) 🟡 [GOOD TO KNOW]

$$f(n) = g(n) + \epsilon \cdot h(n) \quad (\text{where } \epsilon > 1.0)$$

- **$\epsilon = 1.0$:** Standard optimal A*.
- **$\epsilon > 1.0$ (e.g., $\epsilon = 1.5$):** **Weighted A***. Sacrifices strict optimality for massive speedups (often 10x-50x faster expansion).
- **Bounded Suboptimality:** The resulting path cost is guaranteed to be at most $\epsilon \times \text{Optimal Cost}$.

---

# 16. Search Algorithm Comparison

```
+------------------+----------+---------------+----------------------+------------------+-------------------+
| Algorithm        | Weighted?| Optimal Path? | Guiding Heuristic    | Time Complexity  | Space Complexity  |
+------------------+----------+---------------+----------------------+------------------+-------------------+
| BFS              | No       | Yes (Unweight)| None (FIFO)          | O(|V| + |E|)     | O(|V|)            |
| DFS              | No       | NO            | None (LIFO Stack)    | O(|V| + |E|)     | O(|V|)            |
| Dijkstra         | YES      | YES           | None (f = g)         | O(|E| + |V|log|V|)| O(|V|)           |
| Greedy Best-First| YES      | NO            | Pure Goal (f = h)    | O(|V|log|V|) worst| O(|V|)           |
| A* Search        | YES      | YES (if adms) | Combined (f = g + h) | O(|E| + |V|log|V|)| O(|V|)           |
+------------------+----------+---------------+----------------------+------------------+-------------------+
```

---

# 17. Greedy Best-First Search

### Greedy Search ($f(n) = h(n)$) 🔴 [MUST KNOW]
- **Mechanism:** Expands the node that appears closest to the goal according to $h(n)$, completely ignoring the accumulated path cost $g(n)$.
- **Strengths:** Very fast in open, obstacle-free environments.
- **Fatal Weakness in Robotics:** Easily trapped by U-shaped concave obstacles or wall traps, exploring dead-end corridors and producing long, highly suboptimal paths.

---

# 18. Global vs. Local Planning

```
+------------------------------------------------------------------------------------+
|                             GLOBAL VS LOCAL PLANNER                                |
+------------------------------------------------------------------------------------+
|                                                                                    |
|   Static Map / SLAM Occupancy Grid (100m x 100m)                                   |
|   └──> [ GLOBAL PLANNER ] (A* / Dijkstra @ 1 Hz)                                   |
|        └──> Produces: Global Path (Polyline: [(0,0), (5,2), (10,8), ...])          |
|                 │                                                                  |
|                 ▼                                                                  |
|   Real-Time LiDAR / Ultrasonic Sensor Stream (360° @ 20 Hz)                        |
|   └──> [ LOCAL PLANNER / DWA / TEB ] (20-50 Hz)                                    |
|        ├── Feeds on local 5m x 5m rolling window costmap                           |
|        ├── Accounts for dynamic obstacles (pedestrians, moving forklifts)          |
|        └── Produces: Velocity Commands cmd_vel: v = 1.2 m/s, ω = -0.3 rad/s        |
|                 │                                                                  |
|                 ▼                                                                  |
|        [ Low-Level PID Motor Controllers @ 500 Hz ]                                |
|                                                                                    |
+------------------------------------------------------------------------------------+
```

---

# 19. Local Planning

### Dynamic Window Approach (DWA) 🔴 [MUST KNOW]
DWA is the standard local obstacle avoidance algorithm for differential-drive robots:
1. **Search Space:** Operates directly in the robot's **Velocity Space $(v, \omega)$** rather than Cartesian space $(x, y)$.
2. **Dynamic Window ($V_d$):** Restricts reachable velocities in the next time step $\Delta t$ based on physical motor acceleration limits:
   $$V_d = [v_{\text{current}} - a_{\max}\Delta t, \, v_{\text{current}} + a_{\max}\Delta t] \cap [v_{\min}, v_{\max}]$$
   $$W_d = [\omega_{\text{current}} - \alpha_{\max}\Delta t, \, \omega_{\text{current}} + \alpha_{\max}\Delta t] \cap [\omega_{\min}, \omega_{\max}]$$
3. **Forward Simulation:** For each candidate velocity pair $(v, \omega) \in V_d \times W_d$, simulate the circular arc trajectory over a short time window $T_{\text{sim}}$ ($1-2\text{ s}$).
4. **Trajectory Objective Scoring Function:**
   $$\text{Score}(v, \omega) = \alpha \cdot \text{Heading}(v, \omega) + \beta \cdot \text{ObstacleClearance}(v, \omega) + \gamma \cdot \text{Velocity}(v, \omega)$$
5. **Selection:** Pick the $(v, \omega)$ pair with the highest score and send it to the motor driver.

---

# 20. Path Smoothing

### Why Grid Paths Require Smoothing 🔴 [MUST KNOW]
Grid-based paths from A* contain jagged $45^\circ$ and $90^\circ$ corners.
- **Path Smoothing Techniques:**
  1. **Ray-Casting Shortcutter:** Check line-of-sight between non-adjacent waypoints $(w_i, w_{i+2})$. If collision-free, delete intermediate waypoint $w_{i+1}$.
  2. **Bézier Curves & B-Splines:** Fit parametric polynomial curves through waypoints to achieve continuous curvature ($\mathcal{C}^2$ continuity).

---

# 21. Trajectory Generation

### Kinematic Motion Profiles & Jerk 🔴 [MUST KNOW]
- **Jerk ($j(t) = \frac{da(t)}{dt} = \frac{d^3 x(t)}{dt^3}$):** The rate of change of acceleration.
- **Why Jerk Matters in Robotics:**
  - Discontinuous acceleration (infinite jerk $\dot{a} = \infty$) causes sharp mechanical shock, gearbox wear, wheel slip, and spills carried cargo.
  - **S-Curve (Trapezoidal Acceleration) Profiles** bound jerk ($|j(t)| \le j_{\max}$), ensuring smooth velocity ramp-up and ramp-down.

---

# 22. Kinematic Constraints

### Holonomic vs. Non-Holonomic Systems 🔴 [MUST KNOW]

```
+-----------------------------------+------------------------------------+
| Holonomic Robot                   | Non-Holonomic Robot                |
+-----------------------------------+------------------------------------+
| Controllable DOF == Total DOF     | Controllable DOF < Total DOF       |
| Can translate in any direction    | Cannot move instantaneously in     |
| instantaneously without rotating  | lateral direction ($\dot{y}_b = 0$)|
| Examples: Mecanum / Omni wheels   | Examples: Car-like, Diff-Drive     |
+-----------------------------------+------------------------------------+
```

---

# 23. Differential-Drive Robot

### Differential-Drive Kinematics Formulation 🔴 [MUST KNOW]

```
               ▲ Y_world
               │            Robot Heading θ
               │               / v (Linear Velocity)
               │              /
               │             ┌─────────┐
    Left Wheel │             │   [X]   │ Right Wheel
    Speed v_L  │    ======[  │         │ ]====== Speed v_R
               │             └─────────┘
               │                 ◄──L──► (Wheelbase / Track Width)
               │
               └────────────────────────► X_world
```

1. **Forward Kinematics (Wheel Speeds $\to$ Body Twist):**
   $$v = \frac{v_R + v_L}{2} \quad (\text{m/s}), \qquad \omega = \frac{v_R - v_L}{L} \quad (\text{rad/s})$$
2. **Inverse Kinematics (Body Twist $\to$ Individual Wheel Setpoints):**
   $$v_R = v + \frac{\omega L}{2}, \qquad v_L = v - \frac{\omega L}{2}$$
3. **Continuous Unicycle Kinematic Evolution:**
   $$\dot{x} = v \cos(\theta), \qquad \dot{y} = v \sin(\theta), \qquad \dot{\theta} = \omega$$

---

# 24. Car-Like Robot

### The Kinematic Bicycle Model 🔴 [MUST KNOW]

$$\dot{x} = v \cos(\theta), \qquad \dot{y} = v \sin(\theta), \qquad \dot{\theta} = \frac{v}{L} \tan(\delta)$$

where $L$ is vehicle wheelbase and $\delta$ is the front steering angle.
- **Path Curvature ($\kappa$):** $\kappa = \frac{1}{R_{\text{turn}}} = \frac{\tan(\delta)}{L}$.
- **Dubins Car Path:** Shortest path between two poses $(x, y, \theta)$ with constrained minimum turning radius $R_{\min}$ moving **forward only** (Sequences of Left (L), Right (R), Straight (S): e.g., $LSL, RSR, LSR$).
- **Reeds-Shepp Car Path:** Optimal paths for vehicles capable of moving both **forward and reverse** (allows 3-point turns).

---

# 25. Collision Checking

### Geometric Collision Detection Primitives 🔴 [MUST KNOW]
1. **Point-in-Polygon (Ray Casting):** Cast a horizontal ray from test point to infinity. If ray intersects polygon edges an **odd number of times**, point is inside.
2. **Circle-to-Line Segment Distance:** Find projection $t = \frac{(\mathbf{p} - \mathbf{a}) \cdot (\mathbf{b} - \mathbf{a})}{\|\mathbf{b} - \mathbf{a}\|^2}$, clamp $t \in [0, 1]$, and check $\|\mathbf{p} - (\mathbf{a} + t(\mathbf{b} - \mathbf{a}))\| \le R$.
3. **Separating Axis Theorem (SAT):** Two convex polygons do not intersect if there exists a 1D projection axis along which their 1D projections do not overlap.

---

# 26. Sampling-Based Planning

### Why Sampling-Based Planners for High-Dimensional Spaces? 🔴 [MUST KNOW]
In high-dimensional spaces (e.g., a 6-DOF robotic manipulator or a 2D vehicle pulling trailers $\mathcal{C} = (x, y, \theta_1, \theta_2)$), grid-based search suffers from the **Curse of Dimensionality** ($O(N^d)$ cells). Sampling-based algorithms avoid explicit grid building by sampling random valid configurations.

---

# 27. RRT Step-by-Step

### Rapidly-Exploring Random Trees (RRT) 🔴 [MUST KNOW]

```
RRT Algorithmic Flow:
                  Sample q_rand
                        •
                       /
                      / (Unit step towards sample)
  q_near             /
    •───────────────►• q_new
    │
    │
    • Tree Root (Start)
```

```
Step-by-Step Algorithm:
1. Initialize Tree T with start configuration q_start.
2. For iteration 1 to Max_Iterations:
   a. Sample a random configuration q_rand in C-space. (With probability p_bias, set q_rand = q_goal).
   b. Find the nearest node in tree T to q_rand: q_near = Nearest(T, q_rand).
   c. Steer from q_near toward q_rand by step size delta_q to create q_new.
   d. If the segment from q_near to q_new is collision-free:
         Add q_new to tree T with parent q_near.
         If q_new is within tolerance of q_goal:
             Return reconstructed path.
```

- **RRT vs. RRT*:**
  - **RRT (Standard):** Finds **any** feasible collision-free path quickly. **Not asymptotically optimal** (path remains jagged and long even if ran for infinite time).
  - **RRT* (Optimal):** Introduces **Near-Neighbor Rewiring**. As iterations $N \to \infty$, the path cost converges **asymptotically to the mathematically optimal shortest path**.

---

# 28. PRM

### Probabilistic Roadmap (PRM) 🔴 [MUST KNOW]
- **Multi-Query Architecture:**
  1. **Learning Phase (Offline):** Sample $N$ random points in $\mathcal{C}_{\text{free}}$ and connect $k$-nearest neighbors with local collision-free straight lines to build a persistent roadmap graph.
  2. **Query Phase (Online):** Connect $q_{\text{start}}$ and $q_{\text{goal}}$ to the nearest roadmap nodes and run Dijkstra/A* in milliseconds.
- **RRT vs. PRM:** Use RRT for single-query dynamic path searches (e.g. mobile robot obstacle avoidance). Use PRM for static multi-query environments (e.g. robotic arm pick-and-place).

---

# 29. Optimal Path Planning

### Multi-Objective Optimization 🔴 [MUST KNOW]
In real autonomy, "optimal" is rarely just geometric distance:

$$J = w_1 \cdot \text{PathLength} + w_2 \cdot \text{ObstacleProximityPenalty} + w_3 \cdot \int \kappa(s)^2 ds + w_4 \cdot \text{TravelTime}$$

---

# 30. Obstacle Avoidance

### Static vs. Dynamic Obstacle Avoidance 🔴 [MUST KNOW]
- **Reactive Avoidance (Artificial Potential Fields / Bug Algorithms):** Reacts instantly to sensor readings. Zero planning horizon. Susceptible to local minima.
- **Predictive Horizon Avoidance (DWA / MPC):** Simulates motion forward over time window $T_{\text{sim}}$ considering velocity obstacles.

---

# 31. Potential Field Method

### Artificial Potential Fields Formulation 🔴 [MUST KNOW]

$$U_{\text{total}}(\mathbf{q}) = U_{\text{attractive}}(\mathbf{q}) + U_{\text{repulsive}}(\mathbf{q})$$
$$\mathbf{F}(\mathbf{q}) = -\nabla U_{\text{total}}(\mathbf{q}) = \mathbf{F}_{\text{att}}(\mathbf{q}) + \mathbf{F}_{\text{rep}}(\mathbf{q})$$

1. **Attractive Potential to Goal:** $U_{\text{att}}(\mathbf{q}) = \frac{1}{2} k_{\text{att}} \|\mathbf{q} - \mathbf{q}_{\text{goal}}\|^2 \implies \mathbf{F}_{\text{att}} = -k_{\text{att}}(\mathbf{q} - \mathbf{q}_{\text{goal}})$.
2. **Repulsive Potential from Obstacle:**
   $$U_{\text{rep}}(\mathbf{q}) = \begin{cases} \frac{1}{2} k_{\text{rep}} \left(\frac{1}{d(\mathbf{q})} - \frac{1}{d_0}\right)^2 & \text{if } d(\mathbf{q}) \le d_0 \\ 0 & \text{if } d(\mathbf{q}) > d_0 \end{cases}$$

> ⚠️ **CRITICAL INTERVIEW TRAP — Local Minima in Potential Fields:**  
> When the attractive force toward the goal and repulsive force from an obstacle are **equal and opposite** ($\mathbf{F}_{\text{att}} + \mathbf{F}_{\text{rep}} = \mathbf{0}$), the robot gets permanently stuck in a **local minimum** (e.g., in front of a flat wall or inside a U-shaped barrier).

---

# 32. Dynamic Obstacles

### Time-Expanded Search ($x, y, t$) 🔴 [MUST KNOW]
When obstacles move with velocity $\mathbf{v}_{\text{obs}}$, 2D planning fails because a space that is blocked now will be free in 2 seconds.
- **Solution:** Add time as a third planning dimension: $\mathcal{C}_{\text{space-time}} = (x, y, t)$. Obstacles become 3D slanted cylinders/prisms in space-time.

---

# 33. Replanning

### Incremental Replanning: D* and D* Lite 🟡 [GOOD TO KNOW]
When a mobile robot discovers a new obstacle blocking its pre-planned global route:
- **Naive Approach:** Re-run full A* from current position to goal (expensive).
- **D* Lite Approach:** Re-uses the search tree from previous iterations, updating only the affected graph edges locally. Runs in **sub-millisecond time**, enabling 50 Hz real-time replanning on embedded processors.

---

# 34. Navigation Failure Modes

### 10 Real-World Autonomy Failure Modes & Fixes 🔴 [MUST KNOW]

```
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| Failure Mode Scenario                             | Root Cause Diagnosis                              | Engineering Fix                                   |
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| 1. Robot gets permanently stuck in front of wall  | Potential field local minimum (F_att == -F_rep)   | Switch to global graph search (A* / Costmap)      |
| 2. Robot oscillates between two doorways          | DWA scoring weights oscillating between paths     | Add path hysteresis penalty term to local planner |
| 3. Robot cuts corners and clips pallet edges      | Obstacle inflation radius < Robot inscribed radius| Increase costmap inflation radius > R_inscribed   |
| 4. Robot reaches goal with 180° reversed yaw      | Global planner planned (x,y) only, ignoring θ     | Use Reeds-Shepp / Hybrid A* with goal heading     |
| 5. Robot works in simulation, collides in hardware| Simulation assumes zero motor acceleration lag    | Incorporate acceleration limits in DWA window     |
| 6. Robot continuously stops and replans           | Sensor noise adding transient obstacles in path   | Add temporal ray-clearing filter in costmap       |
| 7. Robot cannot enter narrow warehouse aisle      | Inflation radius overly conservative              | Use exact oriented polygon footprint check        |
| 8. Robot spins in circles at goal waypoint        | Goal tolerance radius smaller than turning circle | Increase goal tolerance or switch to pure rotation|
| 9. Robot drifts into wall on slick floor          | Wheel encoder slip causing localization drift     | Fuse wheel odometry with 6-DOF IMU and LiDAR AMCL |
| 10. Planner reports "No Path" in mapped free room | Costmap raytracing cleared map with max range bug | Verify LiDAR minimum and maximum sensor ranges    |
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
```

---

# 35. Planning vs. Control

### Division of Authority 🔴 [MUST KNOW]
- **Planner Failure:** Output path passes through an unmodeled obstacle or requests physically impossible curvature.
- **Controller Failure:** Controller fails to follow a feasible trajectory due to poorly tuned PID gains, excessive wheel slip, or actuator saturation.

---

# 36. Navigation + Localization

### The Interdependence of Navigation & Localization 🔴 [MUST KNOW]
Planning computes trajectory in the **Global Map Frame**. If localization drifts by $0.5\text{ m}$, the planner believes the robot is centered in the hallway while it is physically scraping the wall.
- **Covariance-Aware Planning:** High-reliability planners expand inflation zones dynamically when localization uncertainty (covariance $\mathbf{P}$) grows.

---

# 37. Coordinate Frames

### ROS Coordinate Frame Tree Hierarchy (REP-105) 🔴 [MUST KNOW]

```
[ map ] (Global World Frame: Fixed, Drift-Free, Discrete jumps via SLAM/AMCL)
   │
   ▼ (Continuous Transform: Drifts smoothly over time due to wheel slip)
[ odom ] (Odometry Frame: Continuous, Smooth, High-Frequency @ 100 Hz)
   │
   ▼ (Fixed Kinematic Calibration Transform)
[ base_link ] (Robot Center Frame: Rigidly attached to mobile robot chassis)
   │
   ├──> [ laser_frame ] (LiDAR Sensor Optical Origin)
   ├──> [ imu_link ] (IMU Accelerometer / Gyro Origin)
   └──> [ camera_link ] (RGB-D Camera Optical Center)
```

---

# 38. Navigation System Architecture

### Full Enterprise Autonomy Stack Design 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
|                         ATI AUTONOMOUS ROBOT ARCHITECTURE                          |
+------------------------------------------------------------------------------------+
|  Inputs: Mission Dispatch Goal (x, y, θ), 2D LiDAR (20Hz), IMU (200Hz), Encoders   |
|                                                                                    |
|  [ Layer 1: Sensor & State Estimation ]                                            |
|  └── EKF Node (100 Hz): Fuses Encoders + IMU -> /odom -> /base_link                |
|  └── AMCL Node (20 Hz): Fuses LiDAR + Static Map -> /map -> /odom                  |
|                                                                                    |
|  [ Layer 2: Environment Representation ]                                           |
|  └── Global Costmap (1 Hz): Inflated static warehouse layout                      |
|  └── Local Costmap (20 Hz): 5m rolling window tracking dynamic obstacles           |
|                                                                                    |
|  [ Layer 3: Planning Hierarchy ]                                                   |
|  └── Global Planner (A* / NavFn @ 1 Hz): Generates optimal global polyline         |
|  └── Local Planner (TEB / DWA @ 30 Hz): Generates collision-free cmd_vel (v, ω)    |
|                                                                                    |
|  [ Layer 4: Actuator Execution & Safety ]                                          |
|  └── Safety Guard Node: Hard E-Stop monitor (Stops if obstacle < 0.2m)             |
|  └── Motor CAN Interface (500 Hz): Translates cmd_vel to wheel RPMs                |
+------------------------------------------------------------------------------------+
```

---

# 39. ROS2 Navigation Connection

### Key Nav2 Architectural Components 🔴 [MUST KNOW]
- **BT Navigator (Behavior Tree):** Coordinates mission actions, recovery behaviors, and replanning triggers.
- **Planner Server:** Hosts global planning plugins (e.g., NavFn, Smac Planner A*/Hybrid A*).
- **Controller Server:** Hosts local trajectory tracking plugins (e.g., DWA, TEB, Regulated Pure Pursuit).
- **Costmap2D Server:** Manages global and local costmap 2D voxel and inflation layers.

---

# 40. Algorithm Complexity

### Path Planning Complexity Master Table 🔴 [MUST KNOW]

```
+---------------------+-------------------------------+-------------------------------+-----------------------------------+
| Algorithm           | Time Complexity               | Space Complexity              | Optimality / Completeness         |
+---------------------+-------------------------------+-------------------------------+-----------------------------------+
| BFS                 | O(|V| + |E|)                  | O(|V|)                        | Optimal on unweighted graphs      |
| DFS                 | O(|V| + |E|)                  | O(|V|)                        | NOT optimal                       |
| Dijkstra            | O(|E| + |V| log |V|)          | O(|V|)                        | Strictly Optimal on non-neg graphs|
| A* (Admissible)     | O(|E| + |V| log |V|)          | O(|V|)                        | Strictly Optimal                  |
| RRT                 | O(N log N) with KD-Tree       | O(N)                          | Probabilistically Complete (Non-opt|
| RRT*                | O(N log N) with KD-Tree       | O(N)                          | Asymptotically Optimal            |
| PRM                 | O(N log N + N*K*Collision)    | O(N*K)                        | Probabilistically Complete        |
+---------------------+-------------------------------+-------------------------------+-----------------------------------+
```

---

# 41. Python Coding Problems

#### Problem 41.1: Complete 8-Connected A* with Path Smoothing 🔴 [MUST KNOW]

```python
import heapq
import math
from typing import List, Tuple, Optional

class AutonomousGridPlanner:
    def __init__(self, grid: List[List[int]]):
        self.grid = grid
        self.rows = len(grid)
        self.cols = len(grid[0])
        # 8-Connected motion: (dr, dc, cost)
        self.motions = [
            (-1, 0, 1.0), (1, 0, 1.0), (0, -1, 1.0), (0, 1, 1.0),
            (-1, -1, 1.414), (-1, 1, 1.414), (1, -1, 1.414), (1, 1, 1.414)
        ]

    def a_star(self, start: Tuple[int, int], goal: Tuple[int, int]) -> Optional[List[Tuple[int, int]]]:
        if self.grid[start[0]][start[1]] == 1 or self.grid[goal[0]][goal[1]] == 1:
            return None

        open_set = []
        # (f_cost, g_cost, (r, c))
        heapq.heappush(open_set, (math.hypot(start[0]-goal[0], start[1]-goal[1]), 0.0, start))
        
        g_costs = {start: 0.0}
        parent = {}
        visited = set()

        while open_set:
            f, g, curr = heapq.heappop(open_set)

            if curr == goal:
                # Reconstruct Path
                path = []
                while curr in parent:
                    path.append(curr)
                    curr = parent[curr]
                path.append(start)
                return path[::-1]

            if curr in visited:
                continue
            visited.add(curr)

            for dr, dc, cost in self.motions:
                nr, nc = curr[0] + dr, curr[1] + dc
                neighbor = (nr, nc)

                if 0 <= nr < self.rows and 0 <= nc < self.cols:
                    if self.grid[nr][nc] == 1 or neighbor in visited:
                        continue

                    new_g = g + cost
                    if new_g < g_costs.get(neighbor, float('inf')):
                        g_costs[neighbor] = new_g
                        parent[neighbor] = curr
                        h = math.hypot(nr - goal[0], nc - goal[1])
                        heapq.heappush(open_set, (new_g + h, new_g, neighbor))

        return None
```

---

# 42. C++ Coding Problems

#### Problem 42.1: Geometric Ray-Casting Obstacle Line-of-Sight Checker 🔴 [MUST KNOW]

```cpp
#include <iostream>
#include <cmath>
#include <vector>

bool isLineOfSightClear(int x0, int y0, int x1, int y1, const std::vector<std::vector<int>>& grid) {
    // Bresenham's Line Algorithm for discrete grid ray-tracing
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int x = x0;
    int y = y0;

    while (true) {
        if (grid[x][y] == 1) return false; // Hit Obstacle
        if (x == x1 && y == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    return true; // Clear line of sight
}
```

---

# 43. Mathematical Problems

### Hand-Solvable Problem Set 🔴 [MUST KNOW]

#### Problem 43.1: Differential-Drive Wheel Speed Resolution
An autonomous tugger with track width $L = 0.8\text{ m}$ is commanded to follow an arc with linear velocity $v = 1.5\text{ m/s}$ and angular velocity $\omega = 0.5\text{ rad/s}$.
1. Calculate the required right wheel velocity $v_R$ and left wheel velocity $v_L$.
2. Calculate the instantaneous turning radius $R_{\text{ICC}}$.

#### Problem 43.2: Bicycle Model Curvature Calculation
An autonomous car with wheelbase $L = 2.5\text{ m}$ turns its front wheels by steering angle $\delta = 30^\circ$ ($\approx 0.5236\text{ rad}$).
1. Calculate the resulting path curvature $\kappa$.
2. Calculate the turning radius $R$.

*(Solutions in Section 50)*

---

# 44. Whiteboard Problems

### 1. "How do you prevent a robot from cutting corners around pallet obstacles?" 🔴
- **Reasoning:** Explain that grid planners naturally cut corners because diagonal movement across an obstacle vertex has the same cost as open space. Fix by applying **Costmap Inflation** where cells within distance $R_{\text{inscribed}}$ are given lethal cost ($253$), and non-lethal decay costs extend to $R_{\text{inflation}}$.

### 2. "How would you handle a dynamic forklift crossing your path?" 🔴
- **Reasoning:** Do not trigger an immediate global replan (causes CPU thrashing). The **Local Planner (DWA/TEB)** detects the dynamic obstacle in its local costmap and slows down or maneuvers locally. If blocked for $> 3\text{ seconds}$, trigger a global replan.

---

# 45. System Design Interview Question

### Full Autonomy Design: Factory AMR Tugger Navigation 🔴 [MUST KNOW]
> **Prompt:** *"Design the navigation software stack for an industrial autonomous tugger operating in a mixed environment with pedestrians, forklifts, and static machinery."*

#### Structured Response Architecture:
1. **Sensors:** 2x Safety 2D LiDARs (Front/Rear for $360^\circ$ FOV), dual wheel quadrature encoders, 6-DOF industrial IMU.
2. **State Estimation:** EKF fusing wheel odometry ($200\text{ Hz}$) and IMU, localized against pre-built static LiDAR occupancy grid via AMCL ($20\text{ Hz}$).
3. **Layered Costmaps:**
   - Global Costmap ($1\text{ Hz}, 0.05\text{ m}$ resolution): Static walls and permanent machines with $0.8\text{ m}$ inflation radius.
   - Local Costmap ($30\text{ Hz}, 0.025\text{ m}$ resolution, $6\text{ m} \times 6\text{ m}$ window): Cleared and updated in real-time from LiDAR point-clouds.
4. **Global Planner:** **A* Planner** with Euclidean heuristic generating smooth waypoints.
5. **Local Trajectory Planner:** **Timed-Elastic-Band (TEB) Planner** optimizing trajectory under kinematics, acceleration bounds, and dynamic obstacle velocity predictions.
6. **Safety & Hardware Watchdog:** Certified Safety PLC executing hardware emergency stop if obstacles breach the $0.3\text{ m}$ safety zone.

---

# 46. Common Interview Questions

### 50+ High-Frequency Interview Questions 🔴 [MUST KNOW]

#### Graph Search & A*
1. **Q:** What is the difference between Dijkstra and A*?  
   - **Answer:** Dijkstra is uninformed ($f = g$); A* is informed by a heuristic ($f = g + h$), directing search toward the goal.
2. **Q:** What is an admissible heuristic?  
   - **Answer:** A heuristic that never overestimates the true minimal cost to the goal ($h(n) \le h^*(n)$).
3. **Q:** Can A* return a suboptimal path with an admissible heuristic?  
   - **Answer:** No, admissibility guarantees global optimality on graphs with non-negative edge costs.
4. **Q:** What is heuristic consistency?  
   - **Answer:** $h(n) \le c(n, p) + h(p)$ (Triangle inequality). Ensures no node needs to be visited more than once.
5. **Q:** What happens if the heuristic is Manhattan on an 8-connected grid?  
   - **Answer:** Manhattan overestimates diagonal travel ($\Delta x + \Delta y > \sqrt{2}\max$), violating admissibility and risking suboptimal paths.

#### Costmaps & Kinematics
6. **Q:** What is the Minkowski sum in C-space?  
   - **Answer:** The geometric convolution of the workspace obstacle and the inverted robot footprint, allowing the robot to be treated as a single point.
7. **Q:** Why do we inflate obstacles in costmaps?  
   - **Answer:** To enforce a safety buffer and prevent the path planner from choosing paths where the robot's physical body collides with corners.
8. **Q:** What is a non-holonomic constraint?  
   - **Answer:** A constraint on velocity that cannot be integrated into a positional constraint (e.g., wheels cannot slide sideways: $\dot{y}_{\text{body}} = 0$).
9. **Q:** State the forward kinematics of a differential drive robot.  
   - **Answer:** $v = \frac{v_R + v_L}{2}, \quad \omega = \frac{v_R - v_L}{L}$.
10. **Q:** What is the kinematic bicycle model?  
    - **Answer:** A 2-wheel approximation of a car where heading changes as $\dot{\theta} = \frac{v}{L} \tan(\delta)$.

#### Sampling-Based & Local Planning
11. **Q:** What is RRT and when is it preferred over A*?  
    - **Answer:** Rapidly-exploring Random Trees. Preferred in high-dimensional continuous configuration spaces ($d > 3$) where grid search suffers exponential complexity.
12. **Q:** What is the difference between RRT and RRT*?  
    - **Answer:** RRT finds any feasible path; RRT* re-wires local tree connections to achieve asymptotic optimality.
13. **Q:** How does DWA work?  
    - **Answer:** Samples reachable velocity pairs $(v, \omega)$ in dynamic acceleration window, forward-simulates trajectories, scores them by heading, clearance, and speed, and executes the best pair.
14. **Q:** What is a local minimum in Artificial Potential Fields?  
    - **Answer:** A point where attractive and repulsive gradient forces cancel ($\mathbf{F}_{\text{att}} + \mathbf{F}_{\text{rep}} = \mathbf{0}$), trapping the robot before reaching the goal.
15. **Q:** What is D* Lite?  
    - **Answer:** An incremental heuristic search algorithm that repairs existing search trees when map changes occur, avoiding full replanning from scratch.

---

# 47. Common Interview Traps

- ⚠️ **Trap 1:** *"A* is always faster than Dijkstra."*  
  **Correction:** In an environment filled with maze-like dead ends, A*'s heuristic can lead it repeatedly into dead ends, making it explore as many or more nodes than Dijkstra.
- ⚠️ **Trap 2:** *"The shortest geometric path is always the best path."*  
  **Correction:** The shortest geometric path often cuts tightly around obstacle corners, forcing the robot to slow down to near-zero speed. A slightly longer, smooth-curvature path allows higher continuous velocity and lower travel time.
- ⚠️ **Trap 3:** *"Path planning and trajectory planning are identical."*  
  **Correction:** Path planning is purely spatial. Trajectory planning assigns velocities, accelerations, and timestamps to every point along the path.

---

# 48. Cheat Sheet

```
+---------------------+---------------------------------------+---------------------------------------------+
| Concept             | Core Formula / Definition             | Practical Robotics Meaning                  |
+---------------------+---------------------------------------+---------------------------------------------+
| A* Search           | f(n) = g(n) + h(n)                    | Optimal heuristic-guided graph search       |
| Admissibility       | h(n) <= h*(n)                         | Guarantees shortest path optimality         |
| Euclidean Heuristic | sqrt(dx^2 + dy^2)                     | Standard continuous straight-line distance  |
| Diff-Drive Forward  | v = (v_R + v_L)/2, ω = (v_R - v_L)/L  | Translates wheel speeds to body twist       |
| Diff-Drive Inverse  | v_R = v + ωL/2, v_L = v - ωL/2        | Translates body twist to wheel commands     |
| Bicycle Model       | dθ/dt = (v / L) * tan(δ)              | Curvature steering for car-like robots      |
| C-Space Obstacle    | C_obs = W_obs ⊕ (-Robot)              | Inflates obstacles to treat robot as point  |
| Potential Field     | F_total = -∇(U_att + U_rep)           | Gradient-based reactive avoidance           |
+---------------------+---------------------------------------+---------------------------------------------+
```

---

# 49. 30-Minute Pre-Interview Revision

1. **A* Equation:** $f(n) = g(n) + h(n)$. $g$ is exact cost from start; $h$ is admissible estimate to goal. If $h=0 \to$ Dijkstra.
2. **Heuristics:** Manhattan for 4-connected grid; Octile for 8-connected grid; Euclidean for continuous space.
3. **C-Space:** Inflates obstacles by robot footprint using Minkowski Sum so the robot is simplified to a dimensionless point.
4. **Global vs Local:** Global planner (A* @ 1 Hz) plans global path on static map. Local planner (DWA/TEB @ 20 Hz) outputs motor velocities $(v, \omega)$ avoiding dynamic obstacles.
5. **Diff-Drive Formulas:** $v = \frac{v_R + v_L}{2}, \quad \omega = \frac{v_R - v_L}{L}$. Wheelbase is $L$.
6. **RRT vs RRT*:** RRT finds any valid path; RRT* rewires tree to converge to the optimal path.

---

# 50. Mock Interview Readiness Test

### Questions (Attempt before viewing solutions)

#### Conceptual & Mathematical (10 Questions)
1. Explain why an admissible heuristic must never overestimate true cost.
2. Given a differential-drive robot with $L = 0.6\text{ m}$, what wheel velocities $v_R, v_L$ produce pure in-place counter-clockwise rotation at $\omega = 1.5\text{ rad/s}$?
3. Calculate the Manhattan distance and Euclidean distance between $(2, 3)$ and $(7, 15)$.
4. What is the difference between holonomic and non-holonomic motion?
5. Why does pure potential field control fail in front of a flat wall?
6. An AMR travels at $v = 2.0\text{ m/s}$ and turns at $\omega = 0.4\text{ rad/s}$. What is its turning radius $R$?
7. Explain the function of the Open Set versus Closed Set in A*.
8. What is the time complexity of Dijkstra's algorithm implemented with a binary heap?
9. Why is jerk limitation critical for autonomous mobile robot trajectory generation?
10. In ROS 2, what coordinate frame transform does AMCL publish?

---

<details>
<summary><b>🔍 Click to Expand Complete Mock Test Solutions</b></summary>

### Solutions
1. **Admissibility:** If $h(n) > h^*(n)$, A* may overestimate the cost of the true optimal path and prematurely terminate with a suboptimal path.
2. **In-place Rotation:** For pure rotation, $v = 0$.  
   $v_R = 0 + \frac{\omega L}{2} = \frac{1.5 \times 0.6}{2} = \mathbf{0.45\text{ m/s}}$.  
   $v_L = 0 - \frac{\omega L}{2} = \mathbf{-0.45\text{ m/s}}$.
3. $\Delta x = |7 - 2| = 5, \Delta y = |15 - 3| = 12$.  
   Manhattan $= 5 + 12 = \mathbf{17.0}$.  
   Euclidean $= \sqrt{5^2 + 12^2} = \sqrt{25 + 144} = \sqrt{169} = \mathbf{13.0}$.
4. **Holonomic vs Non-Holonomic:** Holonomic robots can translate in any direction instantaneously ($\dot{x}, \dot{y}$ independent). Non-holonomic robots have differential constraints ($\dot{y}_{\text{body}} = 0$) and must rotate to translate in a new direction.
5. **Local Minima:** At a flat wall directly between robot and goal, repulsive force points directly away from the wall while attractive force points directly toward the goal. They cancel ($\mathbf{F}_{\text{net}} = \mathbf{0}$), causing the robot to stop permanently.
6. **Turning Radius:** $R = \frac{v}{\omega} = \frac{2.0}{0.4} = \mathbf{5.0\text{ meters}}$.
7. **Open vs Closed Set:** Open Set stores discovered candidate frontier nodes prioritized by $f(n)$. Closed Set stores expanded nodes whose shortest path is finalized to prevent re-expansion cycles.
8. **Dijkstra Complexity:** $O(|E| + |V| \log |V|)$ using a binary min-heap.
9. **Jerk Limitation:** Bounding jerk ($\dot{a}$) prevents sudden mechanical stress, eliminates motor current spikes, prevents wheel slip, and ensures smooth passenger/cargo transport.
10. **AMCL Transform:** AMCL calculates and publishes the transform from `map` frame to `odom` frame (`map -> odom`), correcting for wheel odometry drift.

#### Solutions to Mathematical Problems (from Section 43):
- **Problem 43.1:**  
  1. $v_R = v + \frac{\omega L}{2} = 1.5 + \frac{0.5 \times 0.8}{2} = 1.5 + 0.2 = \mathbf{1.7\text{ m/s}}$.  
     $v_L = v - \frac{\omega L}{2} = 1.5 - 0.2 = \mathbf{1.3\text{ m/s}}$.  
  2. $R_{\text{ICC}} = \frac{v}{\omega} = \frac{1.5}{0.5} = \mathbf{3.0\text{ meters}}$.
- **Problem 43.2:**  
  1. $\kappa = \frac{\tan(\delta)}{L} = \frac{\tan(30^\circ)}{2.5} = \frac{1/\sqrt{3}}{2.5} = \frac{0.57735}{2.5} \approx \mathbf{0.2309\text{ m}^{-1}}$.  
  2. $R = \frac{1}{\kappa} = \frac{2.5}{\tan(30^\circ)} = 2.5 \times \sqrt{3} \approx \mathbf{4.33\text{ meters}}$.

</details>
