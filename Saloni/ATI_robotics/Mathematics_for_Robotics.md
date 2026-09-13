# Mathematics for Robotics, Autonomy & Computer Vision: Master Technical Interview Guide

**Role Target:** Robotics Intern – Autonomy (ATI Robotics)  
**Core Focus:** Linear Algebra, Spatial Coordinate Transformations ($SO(3), SE(3)$), Lie Groups, Multivariable Calculus & Jacobians, Probability & Multivariate Gaussians, State Estimation (KF / EKF / Particle Filter), Non-Linear Optimization (Gauss-Newton, Levenberg-Marquardt), Differential Drive & Bicycle Kinematics, Computer Vision Geometry, and Numerical Methods in C++ (Eigen) & Python (NumPy/SciPy).  
**Level:** Comprehensive Fundamentals to Mathematical Derivations, Whiteboard Problem Solving, and High-Pressure Technical Interview Mastery.

---

## 📌 Categorization Legend
- 🔴 **[MUST KNOW]**: Essential interview concepts. High probability of live derivation, hand-calculation on paper/whiteboard, or core algorithmic implementation.
- 🟡 **[GOOD TO KNOW]**: Demonstrates advanced theoretical maturity, mathematical rigor, and production software competence.
- 🔵 **[ADVANCED / OPTIONAL]**: Deep mathematical formulation ($SE(3)$ manifold optimization, Lie algebra $\mathfrak{se}(3)$, Cholesky Schur complement) for top-tier autonomy engineering.
- ⚠️ **[INTERVIEW TRAP]**: Subtle mathematical gotchas, convention mismatches, numerical singularities, and common candidate misconceptions.
- 🤖 **[ROBOTICS CONNECTION]**: Direct application to autonomous industrial tuggers (e.g., ATI Sherpa), warehouse AMRs, factory AGVs, perception, and closed-loop control.
- ✍️ **[WHITEBOARD TIP]**: Exact sketches, matrix layouts, and reasoning steps to draw under interview pressure.

---

# Table of Contents
1. [Mathematical Mindset for Robotics](#1-mathematical-mindset-for-robotics)
2. [Vectors & Vector Operations](#2-vectors)
3. [Dot Product & Geometric Projections](#3-dot-product)
4. [Cross Product & Angular Mechanics](#4-cross-product)
5. [Matrices & Matrix Algebra](#5-matrices)
6. [Matrix Multiplication & Composition](#6-matrix-multiplication)
7. [Matrix Inverse & Linear Solvers](#7-matrix-inverse)
8. [Determinants & Geometric Scaling](#8-determinants)
9. [Eigenvalues, Eigenvectors & PCA](#9-eigenvalues-and-eigenvectors)
10. [Positive Definite Matrices & Covariance Metrics](#10-positive-definite-matrices)
11. [Coordinate Systems & Coordinate Conversions](#11-coordinate-systems)
12. [2D Rotations & Rotation Matrices](#12-2d-rotations)
13. [3D Rotation Matrices ($SO(3)$)](#13-3d-rotation-matrices)
14. [Orthonormal Rotation Properties & Constraints](#14-rotation-properties)
15. [Homogeneous Coordinates & Projective Space](#15-homogeneous-coordinates)
16. [Rigid Body Transformations ($SE(2), SE(3)$)](#16-rigid-body-transformations)
17. [Transformation Inverses & Homogeneous Mechanics](#17-transform-inverse)
18. [Coordinate Frame Reasoning & ROS 2 TF2 Graphs](#18-coordinate-frame-reasoning)
19. [Unit Quaternions ($\mathbb{H}$) & Spatial Rotations](#19-quaternions)
20. [Euler Angles, Rotation Sequences & Gimbal Lock](#20-euler-angles)
21. [Lie Groups & Lie Algebras ($SO(3), SE(3), \mathfrak{so}(3), \mathfrak{se}(3)$)](#21-lie-groups--interview-level)
22. [Differential Calculus & Kinematic Rates](#22-differential-calculus)
23. [Multivariable Calculus, Gradients & Directional Derivatives](#23-multivariable-calculus)
24. [Jacobian Matrices & First-Order Linearization](#24-jacobians)
25. [Jacobians in Robotics Kinematics & Velocity Mapping](#25-jacobian-in-robotics)
26. [Hessian Matrices & Second-Order Curvature](#26-hessians)
27. [Taylor Series Expansions in State Estimation](#27-taylor-series)
28. [Probability Fundamentals & Discrete/Continuous Distributions](#28-probability-fundamentals)
29. [Bayes' Theorem & Recursive Belief Estimation](#29-bayes-theorem)
30. [Random Variables, Expectation & Variance](#30-random-variables)
31. [Gaussian (Normal) Distributions](#31-gaussian-distribution)
32. [Covariance Matrices & Geometric Uncertainty Ellipsoids](#32-covariance)
33. [Multivariate Gaussian Distributions & Mahalanobis Distance](#33-multivariate-gaussian)
34. [Conditional Probability in Sensor Fusion](#34-conditional-probability-in-sensor-fusion)
35. [Bayes Filter: Unified State Estimation Paradigm](#35-bayes-filter)
36. [Linear Kalman Filter (KF) Mathematical Derivations](#36-kalman-filter-mathematics)
37. [Extended Kalman Filter (EKF) Mathematics & Linearization](#37-ekf-mathematics)
38. [Particle Filter (Sequential Monte Carlo) Mathematics](#38-particle-filter-mathematics)
39. [Linear Least Squares & The Normal Equation](#39-least-squares)
40. [Weighted Least Squares & Maximum Likelihood](#40-weighted-least-squares)
41. [Non-Linear Least Squares (NLLS) Formulation](#41-nonlinear-least-squares)
42. [Gauss-Newton Optimization Algorithm](#42-gauss-newton)
43. [Levenberg-Marquardt (Damped Least Squares) Algorithm](#43-levenberg-marquardt)
44. [Gradient Descent & First-Order Optimization](#44-gradient-descent)
45. [Convexity & Optimization Feasibility](#45-convexity)
46. [Constrained Optimization & Karush-Kuhn-Tucker (KKT)](#46-constraints-and-optimization)
47. [Lagrange Multipliers & Duality](#47-lagrange-multipliers)
48. [Linear Programming (LP) & Quadratic Programming (QP) in MPC](#48-linear-programming--quadratic-programming)
49. [Numerical Stability, Precision & Conditioning ($\kappa(\mathbf{A})$)](#49-numerical-stability)
50. [Computational Complexity & Real-Time Big-$\mathcal{O}$ Performance](#50-complexity-and-numerical-cost)
51. [Robot Kinematics Mathematics (Planar Manipulators)](#51-robotics-kinematics-mathematics)
52. [Differential Drive Mobile Robot Kinematics](#52-differential-drive-mathematics)
53. [Differential Drive Dead Reckoning & Odometry Integration](#53-differential-drive-odometry)
54. [Bicycle Kinematic Model & Ackermann Steering Geometry](#54-bicycle-model-mathematics)
55. [Control Systems Mathematics (State-Space, LQR, Controllability)](#55-control-mathematics-review)
56. [Discrete-Time Dynamics & Numerical Integration (Euler, RK4)](#56-discrete-time-robotics-mathematics)
57. [Computer Vision Mathematics Review (Epipolar, PnP, Homography)](#57-computer-vision-mathematics-review)
58. [SLAM Mathematics & Factor Graph Optimization](#58-slam-mathematics-review)
59. [Multi-Sensor Fusion Mathematics (IMU, Odometry, LiDAR, Camera)](#59-sensor-fusion-mathematics-review)
60. [30 Whiteboard Mathematics Interview Problems](#60-whiteboard-mathematics-problems)
61. [25 Numerical Interview Problems (Tiered by Level)](#61-numerical-interview-problems)
62. [C++ Mathematics Coding with Eigen](#62-c-mathematics-coding)
63. [Python Mathematics Coding with NumPy & SciPy](#63-python-mathematics-coding)
64. [20 Real-World Mathematical Robotics Debugging Scenarios](#64-debugging-mathematical-robotics-systems)
65. [System Design: Mathematical Architecture of an Autonomous Tugger](#65-system-design-mathematics)
66. [60 Core Mathematics Interview Questions & Answers](#66-60-interview-questions)
67. [15 High-Pressure Interviewer Follow-Up Chains](#67-high-pressure-interview-chains)
68. ["Explain It in 30 Seconds" Elevator Pitches](#68-explain-it-in-30-seconds)
69. [Common Mathematical Traps in Autonomy Interviews](#69-common-interview-traps)
70. [Unit & Dimensional Consistency Analysis](#70-unit-and-dimensional-analysis)
71. [Mental Math & Estimation Shortcuts for Robotics Interviews](#71-mental-math-for-robotics-interviews)
72. [10 Integrated Autonomy Multi-Disciplinary Challenge Problems](#72-integrated-autonomy-problems)
73. [Master Mathematics Cheat Sheet](#73-final-mathematics-cheat-sheet)
74. [Must-Memorize Formula Sheet](#74-formula-memorization-list)
75. [30-Minute Pre-Interview Revision Protocol](#75-30-minute-mathematics-revision)
76. [Full Mock Mathematics Readiness Test & Scoring Rubric](#76-final-readiness-test)

---

# 1. Mathematical Mindset for Robotics

### Why Mathematics is the Core Language of Autonomous Systems 🔴 [MUST KNOW]
In autonomous robotics, software is never just CRUD logic or generic data manipulation. Every line of algorithms in localization, motion planning, control, and computer vision is a direct discrete-time implementation of **linear algebra, projective geometry, multivariable calculus, and probability theory**.

```
+---------------------------------------------------------------------------------------------------+
|                                 THE ROBOTICS TRANSLATION CHAIN                                    |
+---------------------------------------------------------------------------------------------------+
|                                                                                                   |
|  1. PHYSICAL REALITY    ──► Robot chassis, wheel slippage, optical photons, noisy IMU silicon     |
|                                     │                                                             |
|                                     ▼                                                             |
|  2. MATHEMATICAL MODEL  ──► SE(3) poses, Covariance Σ, Jacobians J, Differential Equations ẋ = f(x,u)|
|                                     │                                                             |
|                                     ▼                                                             |
|  3. NUMERICAL ALGORITHM ──► EKF, Gauss-Newton, Cholesky LL^T, Runge-Kutta 4, A* Dijkstra          |
|                                     │                                                             |
|                                     ▼                                                             |
|  4. REAL-TIME SOFTWARE  ──► C++ Eigen, ROS 2 C++ nodes, fixed-size buffers, lock-free queues      |
|                                     │                                                             |
|                                     ▼                                                             |
|  5. PHYSICAL ACTUATION  ──► CAN Bus motor torque, hydraulic steering, autonomous docking          |
+---------------------------------------------------------------------------------------------------+
```

### The 4 Stages of Mathematical Competence in Robotics Interviews 🔴 [MUST KNOW]
1. **Knowing a Formula:** Recalling that $\mathbf{K} = \mathbf{P} \mathbf{H}^T (\mathbf{H} \mathbf{P} \mathbf{H}^T + \mathbf{R})^{-1}$. (Junior level).
2. **Understanding a Formula:** Explaining that Kalman gain $\mathbf{K}$ balances the ratio of model covariance against measurement noise covariance to minimize trace of posterior covariance. (Interview level).
3. **Implementing a Formula:** Writing numerically stable C++ Eigen code using Cholesky decomposition ($LL^T$ or $LDLT$) rather than naive explicit inversion `A.inverse()`. (Production level).
4. **Applying to a Real Robot:** Knowing what happens when wheel encoders slip on wet industrial factory floors, how process noise covariance $\mathbf{Q}$ must adapt dynamically, and how sensor outages are handled gracefully without divergence. (Autonomous systems engineer level).

---

# 2. Vectors

### Vector Fundamentals 🔴 [MUST KNOW]
A vector in robotics represents both a **magnitude and a direction** in a defined coordinate frame. It is the fundamental primitive for positions, linear/angular velocities, forces, accelerations, and sensor measurement spaces.

```
Coordinate Representation in R^3:
       ^ Z (Up)
       |
       |     / p = [x, y, z]^T  (Point or Direction Vector)
       |    /
       |   /
       |  /
       +----------------> Y (Left)
      /
     /
    v X (Forward - ROS REP-105 standard)
```

- **Vector Notation:** Bold lowercase $\mathbf{v} \in \mathbb{R}^n$, column vector convention:
$$\mathbf{v} = \begin{bmatrix} v_1 \\ v_2 \\ v_3 \end{bmatrix} = [v_1, v_2, v_3]^T$$
- **Euclidean Norm (Magnitude / $L_2$ Norm):**
$$\|\mathbf{v}\|_2 = \sqrt{v_1^2 + v_2^2 + \dots + v_n^2} = \sqrt{\mathbf{v}^T \mathbf{v}}$$
- **Unit Vector (Direction):**
$$\hat{\mathbf{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|}, \qquad \|\hat{\mathbf{v}}\| = 1$$

---

### Core Physical Vectors in Autonomous Mobile Robots (AMRs) 🤖 [ROBOTICS CONNECTION]
1. **Position Vector $\mathbf{p} = [x, y, z]^T$:** Location of the robot base center relative to the origin of the world coordinate frame (units: $\text{m}$).
2. **Linear Velocity Vector $\mathbf{v} = [\dot{x}, \dot{y}, \dot{z}]^T$:** Time-derivative of position in world or robot body frame (units: $\text{m/s}$).
3. **Angular Velocity Vector $\boldsymbol{\omega} = [\omega_x, \omega_y, \omega_z]^T$:** Instantaneous rotational rate about orthogonal axes (units: $\text{rad/s}$).
4. **Force / Torque Vectors $\mathbf{F}, \boldsymbol{\tau}$:** Dynamic actuation efforts driving vehicle inertia (units: $\text{N}, \text{N}\cdot\text{m}$).
5. **Sensor Innovation Vector $\mathbf{y} = \mathbf{z} - \hat{\mathbf{z}}$:** Difference between real physical sensor measurement and predicted observation (units: dependent on sensor).

---

### 10 Vector Practice Exercises 🔴 [MUST KNOW]

1. **Exercise 1 (Vector Magnitude):** Given $\mathbf{v} = [3, -4, 12]^T$, calculate $\|\mathbf{v}\|$.  
   *Solution:* $\|\mathbf{v}\| = \sqrt{3^2 + (-4)^2 + 12^2} = \sqrt{9 + 16 + 144} = \sqrt{169} = \mathbf{13}$.
2. **Exercise 2 (Unit Normalization):** Compute unit vector $\hat{\mathbf{v}}$ for $\mathbf{v} = [0, 6, 8]^T$.  
   *Solution:* $\|\mathbf{v}\| = \sqrt{0 + 36 + 64} = 10 \implies \hat{\mathbf{v}} = [0, 0.6, 0.8]^T$.
3. **Exercise 3 (Vector Addition):** Robot moves by displacement $\mathbf{d}_1 = [2, 5]^T$, then $\mathbf{d}_2 = [-4, 3]^T$. Net displacement?  
   *Solution:* $\mathbf{d}_{\text{net}} = [2 + (-4), 5 + 3]^T = \mathbf{[-2, 8]^T}$.
4. **Exercise 4 (Distance Between Points):** Landmark $A = [1, 2, 3]^T$, Landmark $B = [4, 6, 3]^T$. Euclidean distance?  
   *Solution:* $d = \|\mathbf{b} - \mathbf{a}\| = \sqrt{(4-1)^2 + (6-2)^2 + (3-3)^2} = \sqrt{9 + 16 + 0} = \mathbf{5.0\text{ m}}$.
5. **Exercise 5 (Linear Velocity Integration):** Constant velocity $\mathbf{v} = [1.5, -0.5, 0.0]^T\text{ m/s}$ over $\Delta t = 4\text{ s}$ from initial position $\mathbf{p}_0 = [10, 20, 0]^T$. Final position $\mathbf{p}_1$?  
   *Solution:* $\mathbf{p}_1 = \mathbf{p}_0 + \mathbf{v} \Delta t = [10 + 1.5(4), 20 - 0.5(4), 0]^T = \mathbf{[16.0, 18.0, 0.0]^T}$.
6. **Exercise 6 (Relative Position Vector):** If base frame is at $\mathbf{p}_B = [5, 2]^T$ and obstacle is at $\mathbf{p}_O = [8, 6]^T$ in map frame, what is obstacle vector relative to robot $\mathbf{p}_{O/B}$ in map coordinates?  
   *Solution:* $\mathbf{p}_{O/B} = \mathbf{p}_O - \mathbf{p}_B = [8-5, 6-2]^T = \mathbf{[3, 4]^T}$ (Distance = 5 m).
7. **Exercise 7 (Scalar Multiplication):** Desired deceleration vector is opposite to heading vector $\mathbf{h} = [0.8, 0.6]^T$ with magnitude $a = 2.5\text{ m/s}^2$. Acceleration vector $\mathbf{a}$?  
   *Solution:* $\mathbf{a} = -a \cdot \mathbf{h} = -2.5 [0.8, 0.6]^T = \mathbf{[-2.0, -1.5]^T\text{ m/s}^2}$.
8. **Exercise 8 ($L_1$ vs $L_2$ vs $L_\infty$ Norm):** For error vector $\mathbf{e} = [-3, 4]^T$:  
   *Solution:* $\|\mathbf{e}\|_1 = |-3| + |4| = \mathbf{7}$, $\|\mathbf{e}\|_2 = \sqrt{9+16} = \mathbf{5}$, $\|\mathbf{e}\|_\infty = \max(|-3|, |4|) = \mathbf{4}$.
9. **Exercise 9 (Midpoint Calculation):** Midpoint between waypoint $\mathbf{w}_1 = [12, -4]^T$ and $\mathbf{w}_2 = [6, 8]^T$?  
   *Solution:* $\mathbf{w}_{\text{mid}} = \frac{1}{2}(\mathbf{w}_1 + \mathbf{w}_2) = \mathbf{[9.0, 2.0]^T}$.
10. **Exercise 10 (Vector Basis Linear Combination):** Express $\mathbf{p} = [7, 11]^T$ in terms of orthonormal basis $\mathbf{u}_1 = [1, 0]^T$ and $\mathbf{u}_2 = [0, 1]^T$.  
    *Solution:* $\mathbf{p} = 7\mathbf{u}_1 + 11\mathbf{u}_2$.

---

# 3. Dot Product

### Mathematical Definition & Geometric Interpretation 🔴 [MUST KNOW]
The dot product (scalar product / inner product) maps two vectors $\mathbf{a}, \mathbf{b} \in \mathbb{R}^n$ to a real scalar:

$$\mathbf{a} \cdot \mathbf{b} = \mathbf{a}^T \mathbf{b} = \sum_{i=1}^n a_i b_i = \|\mathbf{a}\| \|\mathbf{b}\| \cos(\theta)$$

Where $\theta$ is the angle between the two vectors ($0 \le \theta \le \pi$).

```
Geometric Projection:
           b
          /|
         / |
        /  |
       /θ  |
      +----+---------> a
        proj_a(b)
```

- **Angle Between Vectors:**
$$\cos(\theta) = \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{a}\| \|\mathbf{b}\|}$$
- **Orthogonality Test (Perpendicular Vectors):**
$$\mathbf{a} \perp \mathbf{b} \iff \mathbf{a} \cdot \mathbf{b} = 0 \quad (\text{if } \|\mathbf{a}\|, \|\mathbf{b}\| \ne 0)$$
- **Scalar Projection of $\mathbf{b}$ onto $\mathbf{a}$:**
$$\text{proj}_{\mathbf{a}}(\mathbf{b}) = \|\mathbf{b}\| \cos(\theta) = \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{a}\|}$$
- **Vector Projection of $\mathbf{b}$ onto $\mathbf{a}$:**
$$\mathbf{b}_{\parallel \mathbf{a}} = \left(\frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{a}\|^2}\right) \mathbf{a} = (\hat{\mathbf{a}}^T \mathbf{b}) \hat{\mathbf{a}}$$

---

### Robotics Applications of the Dot Product 🤖 [ROBOTICS CONNECTION]
1. **Heading Alignment & Error Computation:** Evaluating how closely the robot's forward axis $\hat{\mathbf{x}}_R$ aligns with the path tangent $\hat{\mathbf{t}}_{\text{path}}$: $\text{Alignment} = \hat{\mathbf{x}}_R \cdot \hat{\mathbf{t}}_{\text{path}}$. If equal to $1$, perfectly aligned; if $0$, perpendicular.
2. **Cross-Track Error (Point-to-Line Distance):** Projecting relative error vector onto the normal vector of the path segment.
3. **LiDAR & Camera Surface Normal Calculation:** Finding angle of incidence for ray tracing or planar ground segmentation ($\mathbf{n}_{\text{plane}} \cdot \mathbf{p}_{\text{lidar}} + d = 0$).
4. **Kinetic Energy & Work:** Mechanical power $P = \mathbf{F} \cdot \mathbf{v}$.

---

### Numerical Interview Problems on Dot Product 🔴 [MUST KNOW]

- **Problem 3.1 (Heading Error):** Robot current heading unit vector is $\mathbf{h} = [\frac{\sqrt{3}}{2}, \frac{1}{2}]^T$. The target waypoint direction unit vector is $\mathbf{w} = [0, 1]^T$. Find the angle $\theta$ between the current heading and target direction.  
  *Calculation:*
  $$\mathbf{h} \cdot \mathbf{w} = \left(\frac{\sqrt{3}}{2}\right)(0) + \left(\frac{1}{2}\right)(1) = 0.5$$
  $$\cos(\theta) = \frac{\mathbf{h} \cdot \mathbf{w}}{\|\mathbf{h}\| \|\mathbf{w}\|} = \frac{0.5}{1 \times 1} = 0.5 \implies \theta = \arccos(0.5) = \mathbf{60^\circ \quad \left(\frac{\pi}{3}\text{ rad}\right)}$$

- **Problem 3.2 (Decomposing Velocity into Along-Track & Cross-Track):** A robot moves with velocity $\mathbf{v} = [4.0, 3.0]^T\text{ m/s}$. The planned path heading is given by unit vector $\hat{\mathbf{u}} = [1.0, 0.0]^T$. Compute along-track speed $v_{\parallel}$ and cross-track speed $v_{\perp}$.  
  *Calculation:*
  $$v_{\parallel} = \mathbf{v} \cdot \hat{\mathbf{u}} = (4.0)(1.0) + (3.0)(0.0) = \mathbf{4.0\text{ m/s}}$$
  $$\mathbf{v}_{\parallel} = 4.0 [1, 0]^T = [4.0, 0.0]^T$$
  $$\mathbf{v}_{\perp} = \mathbf{v} - \mathbf{v}_{\parallel} = [4.0, 3.0]^T - [4.0, 0.0]^T = [0.0, 3.0]^T \implies v_{\perp} = \|\mathbf{v}_{\perp}\| = \mathbf{3.0\text{ m/s}}$$

---

# 4. Cross Product

### Mathematical Definition & Properties 🔴 [MUST KNOW]
The cross product (vector product) of two vectors in $\mathbb{R}^3$, denoted $\mathbf{a} \times \mathbf{b}$, produces a **vector perpendicular to both $\mathbf{a}$ and $\mathbf{b}$**, following the right-hand rule:

$$\mathbf{a} \times \mathbf{b} = \det \begin{bmatrix} \hat{\mathbf{i}} & \hat{\mathbf{j}} & \hat{\mathbf{k}} \\ a_x & a_y & a_z \\ b_x & b_y & b_z \end{bmatrix} = \begin{bmatrix} a_y b_z - a_z b_y \\ a_z b_x - a_x b_z \\ a_x b_y - a_y b_x \end{bmatrix}$$

$$\|\mathbf{a} \times \mathbf{b}\| = \|\mathbf{a}\| \|\mathbf{b}\| \sin(\theta)$$

```
Right-Hand Rule:
           a x b (Perpendicular to plane)
           ^
           |   b
           |  /
           | /
           +---------> a
```

### Essential Properties ⚠️ [INTERVIEW TRAP]
- **Anti-commutative:** $\mathbf{a} \times \mathbf{b} = -(\mathbf{b} \times \mathbf{a})$.
- **Parallel Vectors:** $\mathbf{a} \times \mathbf{a} = \mathbf{0}$. If $\mathbf{a} \parallel \mathbf{b}$, then $\mathbf{a} \times \mathbf{b} = \mathbf{0}$.
- **Skew-Symmetric Matrix Representation ($[\mathbf{a}]_\times$ or $\mathbf{a}^\wedge$):**
$$\mathbf{a} \times \mathbf{b} = [\mathbf{a}]_\times \mathbf{b} = \begin{bmatrix} 0 & -a_z & a_y \\ a_z & 0 & -a_x \\ -a_y & a_x & 0 \end{bmatrix} \begin{bmatrix} b_x \\ b_y \\ b_z \end{bmatrix}$$
*This skew-symmetric matrix $[\mathbf{a}]_\times$ is the foundational Lie algebra generator $\mathfrak{so}(3)$ for 3D rotations.*

---

### Robotics Applications of the Cross Product 🤖 [ROBOTICS CONNECTION]
1. **Rigid Body Angular Velocity to Linear Velocity:** Velocity of point $\mathbf{r}$ on a rotating body with angular velocity $\boldsymbol{\omega}$:
$$\mathbf{v} = \boldsymbol{\omega} \times \mathbf{r}$$
2. **Torque Generation:** Torque generated by force $\mathbf{F}$ applied at lever arm $\mathbf{r}$:
$$\boldsymbol{\tau} = \mathbf{r} \times \mathbf{F}$$
3. **Coordinate Frame Construction (Gram-Schmidt Orthonormalization):** Given primary axis $\hat{\mathbf{x}}$ and secondary reference vector $\mathbf{v}_{\text{ref}}$, construct third axis $\hat{\mathbf{z}} = \frac{\hat{\mathbf{x}} \times \mathbf{v}_{\text{ref}}}{\|\hat{\mathbf{x}} \times \mathbf{v}_{\text{ref}}\|}$, then $\hat{\mathbf{y}} = \hat{\mathbf{z}} \times \hat{\mathbf{x}}$.
4. **Epipolar Geometry in Computer Vision:** Essential Matrix $\mathbf{E} = [\mathbf{t}]_\times \mathbf{R}$.

---

### Numerical Interview Problems on Cross Product 🔴 [MUST KNOW]

- **Problem 4.1 (Linear Velocity from Angular Velocity):** An industrial AGV rotates in place with angular velocity $\boldsymbol{\omega} = [0, 0, 2.0]^T\text{ rad/s}$ (yawing about Z). A LiDAR sensor is mounted at offset $\mathbf{r} = [1.5, 0.5, 0.0]^T\text{ m}$ from the rotation center. Find the instantaneous linear velocity vector $\mathbf{v}$ of the LiDAR.  
  *Calculation:*
  $$\mathbf{v} = \boldsymbol{\omega} \times \mathbf{r} = \det \begin{bmatrix} \hat{\mathbf{i}} & \hat{\mathbf{j}} & \hat{\mathbf{k}} \\ 0 & 0 & 2.0 \\ 1.5 & 0.5 & 0.0 \end{bmatrix} = \begin{bmatrix} (0)(0) - (2.0)(0.5) \\ (2.0)(1.5) - (0)(0) \\ (0)(0.5) - (0)(1.5) \end{bmatrix} = \mathbf{\begin{bmatrix} -1.0 \\ 3.0 \\ 0.0 \end{bmatrix}\text{ m/s}}$$
  *Physical Interpretation:* The sensor moves backwards at $1.0\text{ m/s}$ along X and laterally at $3.0\text{ m/s}$ along Y.

---

# 5. Matrices

### Matrix Definition & Fundamental Operations 🔴 [MUST KNOW]
A matrix $\mathbf{A} \in \mathbb{R}^{m \times n}$ has $m$ rows and $n$ columns. In robotics, matrices represent **linear transformations, coordinate frames, state-space systems, noise covariances, and Jacobians**.

$$\mathbf{A} = \begin{bmatrix} a_{11} & a_{12} & \dots & a_{1n} \\ a_{21} & a_{22} & \dots & a_{2n} \\ \vdots & \vdots & \ddots & \vdots \\ a_{m1} & a_{m2} & \dots & a_{mn} \end{bmatrix}$$

- **Transpose ($\mathbf{A}^T$):** Swaps rows and columns ($[\mathbf{A}^T]_{ij} = [\mathbf{A}]_{ji}$). Properties:
$$(\mathbf{A} + \mathbf{B})^T = \mathbf{A}^T + \mathbf{B}^T, \qquad (\mathbf{A}\mathbf{B})^T = \mathbf{B}^T \mathbf{A}^T, \qquad (\mathbf{A}^{-1})^T = (\mathbf{A}^T)^{-1}$$
- **Symmetric Matrix:** $\mathbf{A} = \mathbf{A}^T$ (e.g., Covariance matrix $\boldsymbol{\Sigma}$, Hessian $\mathbf{H}$).
- **Skew-Symmetric Matrix:** $\mathbf{A} = -\mathbf{A}^T \implies a_{ii} = 0$ (e.g., Cross-product matrix $[\mathbf{v}]_\times$).
- **Trace ($\text{Tr}(\mathbf{A})$):** Sum of diagonal elements $\text{Tr}(\mathbf{A}) = \sum_{i=1}^n a_{ii}$. Properties: $\text{Tr}(\mathbf{A}\mathbf{B}) = \text{Tr}(\mathbf{B}\mathbf{A})$.

---

# 6. Matrix Multiplication

### Matrix Multiplication Mechanics & Dimensional Rules 🔴 [MUST KNOW]
For product $\mathbf{C} = \mathbf{A}\mathbf{B}$ to exist, the number of columns in $\mathbf{A} \in \mathbb{R}^{m \times k}$ must equal the number of rows in $\mathbf{B} \in \mathbb{R}^{k \times n}$. Result $\mathbf{C} \in \mathbb{R}^{m \times n}$:

$$c_{ij} = \sum_{p=1}^k a_{ip} b_{pj} = (\text{row } i \text{ of } \mathbf{A}) \cdot (\text{column } j \text{ of } \mathbf{B})$$

```
Dimensions:
    (m x k)  *  (k x n)  =  (m x n)
       ^           ^
       +---MATCH---+
```

### Critical Rules in Robotics Matrix Multiplication ⚠️ [INTERVIEW TRAP]
1. **Non-Commutative:** In general, $\mathbf{A}\mathbf{B} \ne \mathbf{B}\mathbf{A}$. Rotating by Roll then Pitch is NOT the same as Pitch then Roll.
2. **Associative:** $\mathbf{A}(\mathbf{B}\mathbf{C}) = (\mathbf{A}\mathbf{B})\mathbf{C}$.
3. **Transformation Stacking Order:** If applying transformation $\mathbf{T}_1$ followed by $\mathbf{T}_2$ in a fixed reference frame:
$$\mathbf{p}_{\text{final}} = \mathbf{T}_2 \mathbf{T}_1 \mathbf{p}_{\text{initial}}$$

---

### 10 Matrix Multiplication Numerical Practice Problems 🔴 [MUST KNOW]

- **Problem 6.1:** Multiply $\mathbf{A} = \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}$ and $\mathbf{B} = \begin{bmatrix} 5 & 6 \\ 7 & 8 \end{bmatrix}$.  
  *Solution:* $\mathbf{A}\mathbf{B} = \begin{bmatrix} 1(5)+2(7) & 1(6)+2(8) \\ 3(5)+4(7) & 3(6)+4(8) \end{bmatrix} = \mathbf{\begin{bmatrix} 19 & 22 \\ 43 & 50 \end{bmatrix}}$.
- **Problem 6.2:** Compute $\mathbf{B}\mathbf{A}$ for the matrices above to verify non-commutativity.  
  *Solution:* $\mathbf{B}\mathbf{A} = \begin{bmatrix} 5(1)+6(3) & 5(2)+6(4) \\ 7(1)+8(3) & 7(2)+8(4) \end{bmatrix} = \mathbf{\begin{bmatrix} 23 & 34 \\ 31 & 46 \end{bmatrix}} \ne \mathbf{A}\mathbf{B}$.
- **Problem 6.3:** 2D Rotation matrix $\mathbf{R} = \begin{bmatrix} 0 & -1 \\ 1 & 0 \end{bmatrix}$ ($90^\circ$ rotation) applied to vector $\mathbf{v} = [3, 4]^T$.  
  *Solution:* $\mathbf{R}\mathbf{v} = \begin{bmatrix} 0(3) - 1(4) \\ 1(3) + 0(4) \end{bmatrix} = \mathbf{\begin{bmatrix} -4 \\ 3 \end{bmatrix}}$.
- **Problem 6.4:** Matrix-Vector multiplication $\mathbf{H}\mathbf{x}$ where $\mathbf{H} = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \end{bmatrix}$, $\mathbf{x} = [x, y, \theta]^T$.  
  *Solution:* $\mathbf{H}\mathbf{x} = \mathbf{\begin{bmatrix} x \\ y \end{bmatrix}}$ (Standard GPS position observation model).
- **Problem 6.5:** Transpose Product $(\mathbf{A}\mathbf{B})^T$ for $\mathbf{A} = \begin{bmatrix} 2 & 0 \\ 1 & 3 \end{bmatrix}$, $\mathbf{B} = \begin{bmatrix} 1 & 1 \\ 0 & 2 \end{bmatrix}$.  
  *Solution:* $\mathbf{A}\mathbf{B} = \begin{bmatrix} 2 & 2 \\ 1 & 7 \end{bmatrix} \implies (\mathbf{A}\mathbf{B})^T = \mathbf{\begin{bmatrix} 2 & 1 \\ 2 & 7 \end{bmatrix}}$. Verify $\mathbf{B}^T \mathbf{A}^T = \begin{bmatrix} 1 & 0 \\ 1 & 2 \end{bmatrix} \begin{bmatrix} 2 & 1 \\ 0 & 3 \end{bmatrix} = \begin{bmatrix} 2 & 1 \\ 2 & 7 \end{bmatrix}$.
- **Problem 6.6:** Diagonal Scaling $\mathbf{D}\mathbf{A}$ where $\mathbf{D} = \text{diag}(2, 3)$, $\mathbf{A} = \begin{bmatrix} 4 & 5 \\ 6 & 7 \end{bmatrix}$.  
  *Solution:* $\mathbf{D}\mathbf{A} = \mathbf{\begin{bmatrix} 8 & 10 \\ 18 & 21 \end{bmatrix}}$ (Premultiplication scales rows).
- **Problem 6.7:** Diagonal Scaling $\mathbf{A}\mathbf{D}$ with same matrices.  
  *Solution:* $\mathbf{A}\mathbf{D} = \mathbf{\begin{bmatrix} 8 & 15 \\ 12 & 21 \end{bmatrix}}$ (Postmultiplication scales columns).
- **Problem 6.8:** Inner Product as Matrix Multiplication: $\mathbf{u}^T \mathbf{v}$ where $\mathbf{u} = [1, 2, 3]^T, \mathbf{v} = [4, 5, 6]^T$.  
  *Solution:* $[1, 2, 3] \begin{bmatrix} 4 \\ 5 \\ 6 \end{bmatrix} = 1(4)+2(5)+3(6) = 4+10+18 = \mathbf{32} \in \mathbb{R}^{1 \times 1}$.
- **Problem 6.9:** Outer Product $\mathbf{u}\mathbf{v}^T$ with same vectors.  
  *Solution:* $\begin{bmatrix} 1 \\ 2 \\ 3 \end{bmatrix} [4, 5, 6] = \mathbf{\begin{bmatrix} 4 & 5 & 6 \\ 8 & 10 & 12 \\ 12 & 15 & 18 \end{bmatrix}} \in \mathbb{R}^{3 \times 3}$ (Rank-1 matrix).
- **Problem 6.10:** Quadratic Form $\mathbf{x}^T \mathbf{P} \mathbf{x}$ for $\mathbf{x} = [1, 2]^T, \mathbf{P} = \begin{bmatrix} 2 & 0 \\ 0 & 3 \end{bmatrix}$.  
  *Solution:* $\mathbf{x}^T (\mathbf{P}\mathbf{x}) = [1, 2] \begin{bmatrix} 2 \\ 6 \end{bmatrix} = 1(2) + 2(6) = 2 + 12 = \mathbf{14}$.

---

# 7. Matrix Inverse

### Mathematical Definition & Invertibility 🔴 [MUST KNOW]
For a square matrix $\mathbf{A} \in \mathbb{R}^{n \times n}$, its inverse $\mathbf{A}^{-1}$ satisfies:

$$\mathbf{A} \mathbf{A}^{-1} = \mathbf{A}^{-1} \mathbf{A} = \mathbf{I}_n$$

- An inverse exists if and only if $\det(\mathbf{A}) \ne 0$ ($\mathbf{A}$ is **non-singular / full rank**).
- For a $2 \times 2$ matrix:
$$\mathbf{A} = \begin{bmatrix} a & b \\ c & d \end{bmatrix} \implies \mathbf{A}^{-1} = \frac{1}{ad - bc} \begin{bmatrix} d & -b \\ -c & a \end{bmatrix}$$
- **Inverse of Products:**
$$(\mathbf{A}\mathbf{B})^{-1} = \mathbf{B}^{-1} \mathbf{A}^{-1}$$

---

### Why Direct Matrix Inversion is an Anti-Pattern in Robotics Software ⚠️ [INTERVIEW TRAP]
In robotics algorithms (EKF updates, least-squares, bundle adjustment, MPC), we frequently encounter expressions like:
$$\mathbf{x} = \mathbf{A}^{-1} \mathbf{b}$$

**Interviewer Question:** *"Why do we never write `x = A.inverse() * b` in production C++ robotics code?"*  
**Strong Candidate Answer:**
1. **Numerical Instability:** Direct inversion computes intermediate round-off errors that amplify noise, especially if $\mathbf{A}$ is ill-conditioned ($\kappa(\mathbf{A}) \gg 1$).
2. **Computational Inefficiency:** Inverting an $n \times n$ matrix costs $\mathcal{O}(n^3)$ operations and destroys matrix sparsity.
3. **Proper Engineering Practice:** We solve the linear system $\mathbf{A}\mathbf{x} = \mathbf{b}$ directly using matrix decompositions:
   - If $\mathbf{A}$ is Symmetric Positive Definite (e.g., EKF innovation covariance, Normal Equation $\mathbf{A}^T\mathbf{A}$): Use **LLT / LDLT (Cholesky decomposition)** $\to \mathcal{O}(\frac{1}{3}n^3)$. In Eigen: `A.ldlt().solve(b)`.
   - If $\mathbf{A}$ is General Square: Use **Partial Pivoting LU** $\to$ `A.partialPivLu().solve(b)`.
   - If $\mathbf{A}$ is Overdetermined ($m > n$): Use **ColPivHouseholderQR** $\to$ `A.colPivHouseholderQr().solve(b)`.

---

# 8. Determinants

### Geometric & Physical Meaning 🔴 [MUST KNOW]
The determinant $\det(\mathbf{A})$ measures the **volume scaling factor** of the linear transformation described by $\mathbf{A}$.

```
Geometric Area Scaling in 2D:
       ^ Y                      ^ Y'
       |                        |         /  Transformed Area = |det(A)| * Original Area
       |   +---+ (Area = 1)     |        /
       |   |   |           ───► |       +---+
       |   +---+                |      /   /
       +-------> X              +----->+--+-----> X'
```

- In 2D: $\det(\mathbf{A})$ is the factor by which areas are scaled.
- In 3D: $\det(\mathbf{A})$ is the factor by which volumes are scaled.
- **Sign of Determinant:**
  - $\det(\mathbf{A}) > 0$: Orientation is preserved (Right-handed frame remains right-handed).
  - $\det(\mathbf{A}) < 0$: Orientation is flipped (Reflection / Mirroring).
  - $\det(\mathbf{A}) = 0$: Transformation collapses space into a lower dimension (Line or Point) $\implies$ Matrix is **singular** and cannot be inverted.

### Special Determinant Properties in Robotics
- For any valid pure 3D rotation matrix $\mathbf{R} \in SO(3)$: $\det(\mathbf{R}) = +1$ (Preserves distance and orientation without scaling).
- $\det(\mathbf{A}\mathbf{B}) = \det(\mathbf{A})\det(\mathbf{B})$.
- $\det(\mathbf{A}^{-1}) = \frac{1}{\det(\mathbf{A})}$.
- $\det(\mathbf{A}^T) = \det(\mathbf{A})$.

---

# 9. Eigenvalues and Eigenvectors

### Mathematical Definition & Intuition 🔴 [MUST KNOW]
For a square matrix $\mathbf{A} \in \mathbb{R}^{n \times n}$, a non-zero vector $\mathbf{v}$ is an **eigenvector** with corresponding **eigenvalue** $\lambda$ if multiplying by $\mathbf{A}$ only scales $\mathbf{v}$ without changing its direction:

$$\mathbf{A}\mathbf{v} = \lambda \mathbf{v} \iff (\mathbf{A} - \lambda \mathbf{I})\mathbf{v} = \mathbf{0}$$

$$\text{Characteristic Equation: } \det(\mathbf{A} - \lambda \mathbf{I}) = 0$$

```
Eigenvector Geometric Intuition:
       ^                      ^
       |    v (Eigenvector)   |      Av = λv (Scaled along SAME line)
       |   /                  |     /
       |  /              ───► |    /
       | /                    |   /
       +-------->             +-------->
```

### Robotics Applications of Eigenvalues & Eigenvectors 🤖 [ROBOTICS CONNECTION]
1. **Uncertainty Ellipsoids (Covariance Principal Axes):** For covariance $\boldsymbol{\Sigma}$, eigenvectors define the **directions of maximum/minimum uncertainty**, and $\sqrt{\lambda_i}$ defines the standard deviation ($\sigma_i$) along those axes.
2. **Dynamic System Stability:** In continuous state-space $\dot{\mathbf{x}} = \mathbf{A}\mathbf{x}$, the system is asymptotically stable if and only if $\text{Re}(\lambda_i) < 0$ for all eigenvalues of $\mathbf{A}$. In discrete systems $\mathbf{x}_{k+1} = \mathbf{A}\mathbf{x}_k$, stable iff $|\lambda_i| < 1$.
3. **Principal Component Analysis (PCA):** Ground plane extraction from 3D LiDAR point clouds: Smallest eigenvalue eigenvector corresponds to the **ground surface normal vector**.

---

### Step-by-Step Eigenvalue Calculation 🔴 [MUST KNOW]
- **Problem 9.1:** Compute eigenvalues and eigenvectors for $\mathbf{A} = \begin{bmatrix} 4 & 1 \\ 2 & 3 \end{bmatrix}$.  
  *Step 1: Characteristic Equation:*
  $$\det\begin{bmatrix} 4-\lambda & 1 \\ 2 & 3-\lambda \end{bmatrix} = (4-\lambda)(3-\lambda) - (1)(2) = \lambda^2 - 7\lambda + 12 - 2 = \lambda^2 - 7\lambda + 10 = 0$$
  $$(\lambda - 5)(\lambda - 2) = 0 \implies \mathbf{\lambda_1 = 5, \quad \lambda_2 = 2}$$
  *Step 2: Eigenvector for $\lambda_1 = 5$:*
  $$(\mathbf{A} - 5\mathbf{I})\mathbf{v}_1 = \begin{bmatrix} -1 & 1 \\ 2 & -2 \end{bmatrix} \begin{bmatrix} v_{1x} \\ v_{1y} \end{bmatrix} = \begin{bmatrix} 0 \\ 0 \end{bmatrix} \implies -v_{1x} + v_{1y} = 0 \implies \mathbf{v}_1 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$$
  *Step 3: Eigenvector for $\lambda_2 = 2$:*
  $$(\mathbf{A} - 2\mathbf{I})\mathbf{v}_2 = \begin{bmatrix} 2 & 1 \\ 2 & 1 \end{bmatrix} \begin{bmatrix} v_{2x} \\ v_{2y} \end{bmatrix} = \begin{bmatrix} 0 \\ 0 \end{bmatrix} \implies 2v_{2x} + v_{2y} = 0 \implies \mathbf{v}_2 = \begin{bmatrix} 1 \\ -2 \end{bmatrix}$$

---

# 10. Positive Definite Matrices

### Definition & Properties 🔴 [MUST KNOW]
A symmetric matrix $\mathbf{A} = \mathbf{A}^T \in \mathbb{R}^{n \times n}$ is **Symmetric Positive Definite (SPD)** if for every non-zero vector $\mathbf{x} \ne \mathbf{0}$:

$$\mathbf{x}^T \mathbf{A} \mathbf{x} > 0$$

- **Positive Semi-Definite (PSD):** $\mathbf{x}^T \mathbf{A} \mathbf{x} \ge 0$.
- **Key Conditions for SPD Matrix:**
  1. All eigenvalues are strictly positive: $\lambda_i > 0$.
  2. All leading principal minors are strictly positive (Sylvester's criterion).
  3. Cholesky factorization exists: $\mathbf{A} = \mathbf{L}\mathbf{L}^T$ where $\mathbf{L}$ is lower triangular with strictly positive diagonal entries.
  4. Strictly invertible with SPD inverse: $\mathbf{A}^{-1}$ is also SPD.

```
Quadratic Form Geometry x^T A x:
       ^ z = x^T A x
       |         /
       |   \    /   Strictly convex "Bowl" shape with unique global minimum at origin
       |    \__/
       +------------> x, y
```

### Why Covariance Matrices $\boldsymbol{\Sigma}$ Must Be SPD ⚠️ [INTERVIEW TRAP]
In Kalman filtering and state estimation, the covariance matrix $\mathbf{P}$ represents state uncertainty. If numerical roundoff causes an eigenvalue of $\mathbf{P}$ to become $\le 0$, it implies **zero or negative variance** along that state direction. This causes the Kalman Gain to compute NaN/Inf and the filter diverges immediately.

---

# 11. Coordinate Systems

### Standard Coordinate Conventions in Autonomous Systems 🔴 [MUST KNOW]

```
+------------------------+------------------------------------+---------------------------------------+
| Coordinate System      | Mathematical Form                  | Robotics / Sensor Application         |
+------------------------+------------------------------------+---------------------------------------+
| 3D Cartesian (x, y, z) | p = [x, y, z]^T                    | Global Map, TF2 base_link, Waypoints  |
| 2D Polar (r, θ)        | x = r cos(θ), y = r sin(θ)         | 2D Planar LiDAR Scanners (SICK/Hokuyo)|
| 3D Spherical (r, θ, φ) | x=r sin(φ)cos(θ), y=r sin(φ)sin(θ) | 3D Velodyne / Ouster LiDAR Range Data |
+------------------------+------------------------------------+---------------------------------------+
```

```
Cartesian ↔ Polar Conversions:
  x = r cos(θ)            r = √(x² + y²)
  y = r sin(θ)            θ = atan2(y, x)   (CRITICAL: Always use atan2, NEVER atan)
```

⚠️ **[INTERVIEW TRAP]:** Always explain why `atan2(y, x)` is mandatory in robotics software over `atan(y/x)`. `atan(y/x)` maps only to $(-\pi/2, \pi/2)$ and loses quadrant information (e.g., $[-1, -1]^T$ produces $+45^\circ$ instead of $-135^\circ$). `atan2(y, x)` evaluates signs of both arguments to output the full $[-\pi, \pi]$ range.

---

# 12. 2D Rotations

### 2D Rotation Matrix Derivation 🔴 [MUST KNOW]
Rotating a 2D vector counter-clockwise by angle $\theta$:

$$\mathbf{R}(\theta) = \begin{bmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) & \cos(\theta) \end{bmatrix}$$

```
Rotating Point p by θ:
       ^ Y
       |        p' = R(θ) p
       |       /
       |      /  θ
       |     +------- p = [x, y]^T
       +-----------------> X
```

### Algebraic Properties of $\mathbf{R}(\theta) \in SO(2)$
1. $\mathbf{R}^{-1}(\theta) = \mathbf{R}^T(\theta) = \mathbf{R}(-\theta)$.
2. $\mathbf{R}(\theta_1) \mathbf{R}(\theta_2) = \mathbf{R}(\theta_1 + \theta_2)$.
3. $\det(\mathbf{R}(\theta)) = \cos^2(\theta) - (-\sin^2(\theta)) = \cos^2(\theta) + \sin^2(\theta) = 1$.

- **Numerical Example:** Rotate vector $\mathbf{p} = [2, 0]^T$ by $\theta = 30^\circ$ ($\frac{\pi}{6}$ rad):
$$\mathbf{p}' = \begin{bmatrix} \cos(30^\circ) & -\sin(30^\circ) \\ \sin(30^\circ) & \cos(30^\circ) \end{bmatrix} \begin{bmatrix} 2 \\ 0 \end{bmatrix} = \begin{bmatrix} \frac{\sqrt{3}}{2} & -\frac{1}{2} \\ \frac{1}{2} & \frac{\sqrt{3}}{2} \end{bmatrix} \begin{bmatrix} 2 \\ 0 \end{bmatrix} = \mathbf{\begin{bmatrix} \sqrt{3} \\ 1 \end{bmatrix} \approx \begin{bmatrix} 1.732 \\ 1.000 \end{bmatrix}}$$

---

# 13. 3D Rotation Matrices

### Elementary Axis Rotations ($SO(3)$) 🔴 [MUST KNOW]
Rotations in 3D Euclidean space around the principal Cartesian axes:

$$\mathbf{R}_x(\phi) = \begin{bmatrix} 1 & 0 & 0 \\ 0 & \cos\phi & -\sin\phi \\ 0 & \sin\phi & \cos\phi \end{bmatrix} \quad (\text{Roll about X})$$

$$\mathbf{R}_y(\theta) = \begin{bmatrix} \cos\theta & 0 & \sin\theta \\ 0 & 1 & 0 \\ -\sin\theta & 0 & \cos\theta \end{bmatrix} \quad (\text{Pitch about Y - NOTE the sign pattern!})$$

$$\mathbf{R}_z(\psi) = \begin{bmatrix} \cos\psi & -\sin\psi & 0 \\ \sin\psi & \cos\psi & 0 \\ 0 & 0 & 1 \end{bmatrix} \quad (\text{Yaw about Z})$$

⚠️ **[INTERVIEW TRAP - Pitch Sign Pattern]:** In $\mathbf{R}_y(\theta)$, the $(1,3)$ element is $+\sin\theta$ and the $(3,1)$ element is $-\sin\theta$. This is because the right-hand cyclic order of axes is $Z \times X = Y$, so the cross terms invert sign relative to $X$ and $Z$.

---

### Composite Rotation (ZYX Yaw-Pitch-Roll Convention) 🔴 [MUST KNOW]
In robotics (ROS REP-103), the standard intrinsic rotation order is **Yaw ($\psi$) $\to$ Pitch ($\theta$) $\to$ Roll ($\phi$)**:

$$\mathbf{R} = \mathbf{R}_z(\psi) \mathbf{R}_y(\theta) \mathbf{R}_x(\phi)$$

Because matrix multiplication does not commute, $\mathbf{R}_z \mathbf{R}_y \mathbf{R}_x \ne \mathbf{R}_x \mathbf{R}_y \mathbf{R}_z$. Changing the sequence changes the final orientation.

---

# 14. Rotation Properties

### The Special Orthogonal Group $SO(3)$ Constraints 🔴 [MUST KNOW]
A matrix $\mathbf{R} \in \mathbb{R}^{3 \times 3}$ is a valid rotation matrix if and only if it belongs to the Special Orthogonal Group $SO(3)$:

$$SO(3) = \{ \mathbf{R} \in \mathbb{R}^{3 \times 3} \mid \mathbf{R}^T \mathbf{R} = \mathbf{I}, \quad \det(\mathbf{R}) = +1 \}$$

```
Geometric Column Interpretation:
  R = [ r_1 | r_2 | r_3 ]
  - r_1, r_2, r_3 are mutually orthogonal unit vectors:
    r_i · r_j = 0 (for i ≠ j),   ||r_i|| = 1
  - Forms a right-handed basis: r_3 = r_1 x r_2
```

### How to Check if a Matrix is a Valid Rotation Matrix in an Interview
1. Compute $\mathbf{R}^T \mathbf{R}$. Must equal $\mathbf{I}_3$.
2. Compute $\det(\mathbf{R})$. Must equal $+1.0$ (if $-1.0$, it is a reflection matrix).

---

# 15. Homogeneous Coordinates

### Why Robotics Uses Homogeneous Coordinates 🔴 [MUST KNOW]
In Cartesian space, a rotation is a linear matrix multiplication ($\mathbf{p}' = \mathbf{R}\mathbf{p}$), but a translation is a non-linear addition ($\mathbf{p}' = \mathbf{p} + \mathbf{t}$).  
To combine rotations and translations into a **single linear matrix multiplication**, we embed $\mathbb{R}^n$ into Projective Space $\mathbb{P}^n$ using **Homogeneous Coordinates**:

$$\text{Point in 3D: } \mathbf{p} = \begin{bmatrix} x \\ y \\ z \end{bmatrix} \in \mathbb{R}^3 \implies \tilde{\mathbf{p}} = \begin{bmatrix} x \\ y \\ z \\ 1 \end{bmatrix} \in \mathbb{P}^3$$

$$\text{Direction Vector in 3D: } \mathbf{v} = \begin{bmatrix} v_x \\ v_y \\ v_z \end{bmatrix} \in \mathbb{R}^3 \implies \tilde{\mathbf{v}} = \begin{bmatrix} v_x \\ v_y \\ v_z \\ 0 \end{bmatrix} \in \mathbb{P}^3$$

*Notice: Points have a scale factor of $1$ (affected by translation), while pure direction vectors have a scale factor of $0$ (invariant to translation).*

---

# 16. Rigid Body Transformations

### Special Euclidean Group $SE(3)$ & $4 \times 4$ Matrix Structure 🔴 [MUST KNOW]
A rigid body transformation combines 3D rotation $\mathbf{R} \in SO(3)$ and 3D translation $\mathbf{t} \in \mathbb{R}^3$:

$$\mathbf{T} = \begin{bmatrix} \mathbf{R} & \mathbf{t} \\ \mathbf{0}_{1 \times 3} & 1 \end{bmatrix} = \begin{bmatrix} r_{11} & r_{12} & r_{13} & t_x \\ r_{21} & r_{22} & r_{23} & t_y \\ r_{31} & r_{32} & r_{33} & t_z \\ 0 & 0 & 0 & 1 \end{bmatrix} \in SE(3)$$

$$\tilde{\mathbf{p}}' = \mathbf{T} \tilde{\mathbf{p}} \iff \begin{bmatrix} \mathbf{p}' \\ 1 \end{bmatrix} = \begin{bmatrix} \mathbf{R} & \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix} \begin{bmatrix} \mathbf{p} \\ 1 \end{bmatrix} = \begin{bmatrix} \mathbf{R}\mathbf{p} + \mathbf{t} \\ 1 \end{bmatrix}$$

- **Composition of Transformations:**
$$\mathbf{T}_{A \to C} = \mathbf{T}_{B \to C} \mathbf{T}_{A \to B} \quad \left(\text{or } \mathbf{T}_A^C = \mathbf{T}_B^C \mathbf{T}_A^B\right)$$

---

# 17. Transform Inverse

### Step-by-Step Derivation of $\mathbf{T}^{-1}$ 🔴 [MUST KNOW]
Let $\mathbf{T} = \begin{bmatrix} \mathbf{R} & \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix}$. We seek $\mathbf{T}^{-1} = \begin{bmatrix} \mathbf{A} & \mathbf{b} \\ \mathbf{0} & 1 \end{bmatrix}$ such that $\mathbf{T} \mathbf{T}^{-1} = \mathbf{I}$:

$$\begin{bmatrix} \mathbf{R} & \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix} \begin{bmatrix} \mathbf{A} & \mathbf{b} \\ \mathbf{0} & 1 \end{bmatrix} = \begin{bmatrix} \mathbf{R}\mathbf{A} & \mathbf{R}\mathbf{b} + \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix} = \begin{bmatrix} \mathbf{I} & \mathbf{0} \\ \mathbf{0} & 1 \end{bmatrix}$$

1. $\mathbf{R}\mathbf{A} = \mathbf{I} \implies \mathbf{A} = \mathbf{R}^{-1} = \mathbf{R}^T$ (since $\mathbf{R} \in SO(3)$).
2. $\mathbf{R}\mathbf{b} + \mathbf{t} = \mathbf{0} \implies \mathbf{R}\mathbf{b} = -\mathbf{t} \implies \mathbf{b} = -\mathbf{R}^T \mathbf{t}$.

$$\mathbf{T}^{-1} = \begin{bmatrix} \mathbf{R}^T & -\mathbf{R}^T \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix}$$

⚠️ **[INTERVIEW TRAP]:** Never write the inverse translation as $-\mathbf{t}$. It must be rotated back into the original frame: $-\mathbf{R}^T \mathbf{t}$.

---

# 18. Coordinate Frame Reasoning

### Frame Transformation Mathematics & ROS 2 TF2 🔴 [MUST KNOW]
In robotics, spatial reasoning errors account for over 50% of sensor fusion and navigation bugs.

```
Coordinate Frame Tree (REP-105 Standard):
  [map]
    │
    ▼ T_map_odom (Drift-corrected global localization)
  [odom]
    │
    ▼ T_odom_base (Continuous, smooth dead-reckoning from wheel/IMU)
  [base_link] (Robot center of rotation)
    ├──► T_base_lidar   [lidar_link]
    ├──► T_base_camera  [camera_link] ──► [camera_optical_frame]
    └──► T_base_imu     [imu_link]
```

### Solving Frame Transformations: Step-by-Step
**Interview Problem:** A camera is mounted on a robot base at $\mathbf{T}_{\text{base}}^{\text{cam}} = \begin{bmatrix} \mathbf{R}_{bc} & \mathbf{t}_{bc} \\ \mathbf{0} & 1 \end{bmatrix}$. The robot base is localized in the map frame at $\mathbf{T}_{\text{map}}^{\text{base}} = \begin{bmatrix} \mathbf{R}_{mb} & \mathbf{t}_{mb} \\ \mathbf{0} & 1 \end{bmatrix}$. The camera detects an obstacle point $\mathbf{p}_c = [x_c, y_c, z_c]^T$ in its optical coordinate frame. Where is the obstacle in the map frame $\mathbf{p}_m$?

$$\tilde{\mathbf{p}}_m = \mathbf{T}_{\text{map}}^{\text{base}} \mathbf{T}_{\text{base}}^{\text{cam}} \tilde{\mathbf{p}}_c$$
$$\mathbf{p}_m = \mathbf{R}_{mb} (\mathbf{R}_{bc} \mathbf{p}_c + \mathbf{t}_{bc}) + \mathbf{t}_{mb}$$

---

# 19. Quaternions

### Unit Quaternion Mathematics ($\mathbb{H}$) 🔴 [MUST KNOW]
A unit quaternion $\mathbf{q} \in \mathbb{H}$ represents a 3D rotation without singularities:

$$\mathbf{q} = w + x\mathbf{i} + y\mathbf{j} + z\mathbf{k} = [w, \mathbf{v}]^T = [w, x, y, z]^T, \quad \|\mathbf{q}\| = \sqrt{w^2 + x^2 + y^2 + z^2} = 1$$

- **Axis-Angle ($\theta$ about unit axis $\hat{\mathbf{u}} = [u_x, u_y, u_z]^T$) to Quaternion:**
$$w = \cos\left(\frac{\theta}{2}\right), \quad \mathbf{v} = \hat{\mathbf{u}} \sin\left(\frac{\theta}{2}\right) = \begin{bmatrix} u_x \sin(\theta/2) \\ u_y \sin(\theta/2) \\ u_z \sin(\theta/2) \end{bmatrix}$$
- **Hamilton Product (Quaternion Multiplication):**
$$\mathbf{q}_1 \otimes \mathbf{q}_2 = \begin{bmatrix} w_1 w_2 - \mathbf{v}_1 \cdot \mathbf{v}_2 \\ w_1 \mathbf{v}_2 + w_2 \mathbf{v}_1 + \mathbf{v}_1 \times \mathbf{v}_2 \end{bmatrix}$$
- **Conjugate & Inverse:**
$$\mathbf{q}^* = [w, -\mathbf{v}]^T, \qquad \mathbf{q}^{-1} = \frac{\mathbf{q}^*}{\|\mathbf{q}\|^2} = \mathbf{q}^* \quad (\text{for unit quaternions})$$
- **Rotating a 3D Vector $\mathbf{p}$:**
$$\tilde{\mathbf{p}}' = \mathbf{q} \otimes [0, \mathbf{p}]^T \otimes \mathbf{q}^*$$
- **Double Cover Property:** $\mathbf{q}$ and $-\mathbf{q}$ represent the **exact same physical rotation**.

---

# 20. Euler Angles

### Roll-Pitch-Yaw & Gimbal Lock 🔴 [MUST KNOW]
Euler angles represent orientation as three sequential rotations $(\phi, \theta, \psi)$.

```
+-------------------+---------------------+-------------------------+-------------------------------+
| Representation    | Memory / Storage    | Advantages              | Disadvantages / Failure Modes |
+-------------------+---------------------+-------------------------+-------------------------------+
| Rotation Matrix R | 9 floats (3x3)      | Direct linear mapping   | Redundant (6 constraints), drift|
| Euler Angles      | 3 floats (r, p, y)  | Human intuitive         | Gimbal lock singularity, order|
| Quaternion q      | 4 floats (w, x, y, z)| Compact, smooth SLERP   | Double cover (±q), normalization|
+-------------------+---------------------+-------------------------+-------------------------------+
```

### What is Gimbal Lock? ⚠️ [INTERVIEW TRAP]
**Gimbal Lock** occurs when the pitch angle reaches $\theta = \pm 90^\circ$ ($\pm \frac{\pi}{2}\text{ rad}$). In this configuration, the first axis (Roll) and third axis (Yaw) align onto the same physical axis, resulting in the **loss of one rotational degree of freedom**. Mathematically, the Jacobian mapping Euler angular rates to body angular velocity becomes singular ($\det = 0$).

---

# 21. Lie Groups — Interview Level

### Intuitive Lie Theory for Robotics ($SO(3), SE(3)$) 🟡 [GOOD TO KNOW]
Rotations and rigid transformations do not form a vector space (e.g., adding two rotation matrices $\mathbf{R}_1 + \mathbf{R}_2 \notin SO(3)$). They form a **smooth differentiable manifold (Lie Group)**.

```
Manifold vs Tangent Space:
            Lie Group Manifold SO(3) (Curved surface)
                  /----\
                 /  R   \
                +--------+
                     \
                      \ Exp Map (ω^)
                       \
                        v Tangent Space at Identity: Lie Algebra so(3) (Flat vector space R^3)
```

- **Lie Algebra $\mathfrak{so}(3)$:** Tangent space around identity, represented by $3 \times 1$ tangent vectors $\boldsymbol{\phi} = \theta \hat{\mathbf{u}} \in \mathbb{R}^3$ or skew-symmetric matrices $[\boldsymbol{\phi}]_\times$.
- **Exponential Map (Rodrigues' Formula):** Maps tangent vector $\boldsymbol{\phi} = \theta \hat{\mathbf{u}}$ to rotation matrix $\mathbf{R} \in SO(3)$:
$$\mathbf{R} = \exp([\boldsymbol{\phi}]_\times) = \mathbf{I} + \sin(\theta) [\hat{\mathbf{u}}]_\times + (1 - \cos(\theta)) [\hat{\mathbf{u}}]_\times^2$$
- **Logarithmic Map:** Maps rotation matrix $\mathbf{R}$ back to tangent vector $\boldsymbol{\phi} \in \mathbb{R}^3$:
$$\theta = \arccos\left(\frac{\text{Tr}(\mathbf{R}) - 1}{2}\right), \quad [\hat{\mathbf{u}}]_\times = \frac{\mathbf{R} - \mathbf{R}^T}{2\sin(\theta)}$$
- **Robotics Purpose:** Allows unconstrained gradient descent optimization on robot poses in SLAM (g2o, GTSAM) without violating orthogonality constraints.

---

# 22. Differential Calculus

### Kinematics & Rates of Change 🔴 [MUST KNOW]
In robotics, state derivatives describe vehicle dynamics and sensor motion:

$$\text{Position: } \mathbf{p}(t) \implies \text{Velocity: } \mathbf{v}(t) = \frac{d\mathbf{p}}{dt} = \dot{\mathbf{p}} \implies \text{Acceleration: } \mathbf{a}(t) = \frac{d\mathbf{v}}{dt} = \ddot{\mathbf{p}}$$

- **Time Derivative of a Rotating Vector:** For vector $\mathbf{r}$ expressed in a rotating frame with angular rate $\boldsymbol{\omega}$:
$$\left(\frac{d\mathbf{r}}{dt}\right)_{\text{world}} = \left(\frac{d\mathbf{r}}{dt}\right)_{\text{body}} + \boldsymbol{\omega} \times \mathbf{r}$$
- **Time Derivative of a Rotation Matrix:**
$$\dot{\mathbf{R}}(t) = \mathbf{R}(t) [\boldsymbol{\omega}_{\text{body}}(t)]_\times = [\boldsymbol{\omega}_{\text{world}}(t)]_\times \mathbf{R}(t)$$

---

# 23. Multivariable Calculus

### Gradients & Directional Derivatives 🔴 [MUST KNOW]
For a scalar cost function $f(\mathbf{x}): \mathbb{R}^n \to \mathbb{R}$ (e.g., trajectory optimization cost, obstacle potential field):

$$\nabla f(\mathbf{x}) = \begin{bmatrix} \frac{\partial f}{\partial x_1} \\ \frac{\partial f}{\partial x_2} \\ \vdots \\ \frac{\partial f}{\partial x_n} \end{bmatrix} \in \mathbb{R}^{n \times 1}$$

- **Geometric Meaning:** $\nabla f(\mathbf{x})$ points in the **direction of steepest ascent**.
- **Direction of Steepest Descent:** $-\nabla f(\mathbf{x})$ (used in gradient descent motion planning).
- **Directional Derivative along unit vector $\hat{\mathbf{v}}$:**
$$D_{\hat{\mathbf{v}}} f(\mathbf{x}) = \nabla f(\mathbf{x}) \cdot \hat{\mathbf{v}} = \nabla f(\mathbf{x})^T \hat{\mathbf{v}}$$

---

# 24. Jacobians

### Definition & First-Order Multivariable Linearization 🔴 [MUST KNOW]
For a vector-valued function $\mathbf{f}(\mathbf{x}): \mathbb{R}^n \to \mathbb{R}^m$, the **Jacobian matrix $\mathbf{J} \in \mathbb{R}^{m \times n}$** contains all first-order partial derivatives:

$$\mathbf{J} = \frac{\partial \mathbf{f}}{\partial \mathbf{x}} = \begin{bmatrix} \frac{\partial f_1}{\partial x_1} & \frac{\partial f_1}{\partial x_2} & \dots & \frac{\partial f_1}{\partial x_n} \\ \frac{\partial f_2}{\partial x_1} & \frac{\partial f_2}{\partial x_2} & \dots & \frac{\partial f_2}{\partial x_n} \\ \vdots & \vdots & \ddots & \vdots \\ \frac{\partial f_m}{\partial x_1} & \frac{\partial f_m}{\partial x_2} & \dots & \frac{\partial f_m}{\partial x_n} \end{bmatrix}$$

### First-Order Taylor Linearization
$$\mathbf{f}(\mathbf{x} + \Delta \mathbf{x}) \approx \mathbf{f}(\mathbf{x}) + \mathbf{J} \Delta \mathbf{x}$$

$$\text{Covariance Propagation: } \boldsymbol{\Sigma}_{\mathbf{f}} \approx \mathbf{J} \boldsymbol{\Sigma}_{\mathbf{x}} \mathbf{J}^T$$

---

# 25. Jacobian in Robotics

### Kinematic Jacobians & Singularities 🔴 [MUST KNOW]
In robot kinematics, the geometric Jacobian $\mathbf{J}(\mathbf{q})$ maps joint velocities $\dot{\mathbf{q}}$ to end-effector Cartesian velocities $\mathbf{v}_e$:

$$\mathbf{v}_e = \begin{bmatrix} \mathbf{v} \\ \boldsymbol{\omega} \end{bmatrix} = \mathbf{J}(\mathbf{q}) \dot{\mathbf{q}}$$

- **Inverse Kinematics Velocity:** $\dot{\mathbf{q}} = \mathbf{J}^{-1}(\mathbf{q}) \mathbf{v}_e$.
- **Kinematic Singularity:** Occurs when $\det(\mathbf{J}(\mathbf{q})) = 0$ (or $\text{rank}(\mathbf{J}) < m$). At a singularity:
  1. The robot loses the ability to move in one or more Cartesian directions.
  2. Inverse velocity $\mathbf{J}^{-1}$ approaches infinity, requiring infinite joint speeds.
- **Damped Least Squares (Pseudoinverse for Singularities):**
$$\mathbf{J}^\dagger = \mathbf{J}^T (\mathbf{J}\mathbf{J}^T + \lambda^2 \mathbf{I})^{-1}$$

---

# 26. Hessians

### Second-Order Curvature & Optimization 🔴 [MUST KNOW]
For scalar objective function $f(\mathbf{x}): \mathbb{R}^n \to \mathbb{R}$, the **Hessian matrix $\mathbf{H} \in \mathbb{R}^{n \times n}$** is the symmetric matrix of second partial derivatives:

$$\mathbf{H} = \nabla^2 f(\mathbf{x}) = \begin{bmatrix} \frac{\partial^2 f}{\partial x_1^2} & \frac{\partial^2 f}{\partial x_1 \partial x_2} & \dots & \frac{\partial^2 f}{\partial x_1 \partial x_n} \\ \frac{\partial^2 f}{\partial x_2 \partial x_1} & \frac{\partial^2 f}{\partial x_2^2} & \dots & \frac{\partial^2 f}{\partial x_2 \partial x_n} \\ \vdots & \vdots & \ddots & \vdots \\ \frac{\partial^2 f}{\partial x_n \partial x_1} & \frac{\partial^2 f}{\partial x_n \partial x_2} & \dots & \frac{\partial^2 f}{\partial x_n^2} \end{bmatrix}$$

- **Second-Order Taylor Series:**
$$f(\mathbf{x} + \Delta \mathbf{x}) \approx f(\mathbf{x}) + \nabla f(\mathbf{x})^T \Delta \mathbf{x} + \frac{1}{2} \Delta \mathbf{x}^T \mathbf{H} \Delta \mathbf{x}$$
- **Curvature Test:**
  - If $\mathbf{H}$ is **Positive Definite ($\mathbf{H} \succ 0$)**: Local Minimum (Strictly convex).
  - If $\mathbf{H}$ is **Negative Definite ($\mathbf{H} \prec 0$)**: Local Maximum.
  - If $\mathbf{H}$ has both positive and negative eigenvalues: **Saddle Point**.

---

# 27. Taylor Series

### Multi-Dimensional Linearization in State Estimation 🔴 [MUST KNOW]
Non-linear robot motion models $\mathbf{x}_{k} = \mathbf{f}(\mathbf{x}_{k-1}, \mathbf{u}_k)$ and measurement models $\mathbf{z}_k = \mathbf{h}(\mathbf{x}_k)$ are linearized in the **Extended Kalman Filter (EKF)** via 1st-order Taylor expansions around the current state estimate $\hat{\mathbf{x}}$:

$$\mathbf{f}(\mathbf{x}) \approx \mathbf{f}(\hat{\mathbf{x}}) + \left.\frac{\partial \mathbf{f}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}} (\mathbf{x} - \hat{\mathbf{x}})$$
$$\mathbf{h}(\mathbf{x}) \approx \mathbf{h}(\hat{\mathbf{x}}) + \left.\frac{\partial \mathbf{h}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}} (\mathbf{x} - \hat{\mathbf{x}})$$

Where $\mathbf{F} = \left.\frac{\partial \mathbf{f}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}}$ and $\mathbf{H} = \left.\frac{\partial \mathbf{h}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}}$ are the state transition and measurement Jacobians.

---

# 28. Probability Fundamentals

### Axioms & Probability in Mobile Robotics 🔴 [MUST KNOW]
In the real physical world, sensor readings are noisy and actuators suffer from slip and compliance. Probability models this fundamental uncertainty.

- **Axioms of Probability ($P(A)$):**
  1. $0 \le P(A) \le 1$.
  2. $P(\Omega) = 1$ (Total probability of sample space is 1).
  3. For mutually exclusive events: $P(A \cup B) = P(A) + P(B)$.
- **Joint Probability:** $P(A, B) = P(A \cap B) = P(A \mid B) P(B)$.
- **Conditional Probability:**
$$P(A \mid B) = \frac{P(A, B)}{P(B)} \quad (\text{if } P(B) > 0)$$
- **Law of Total Probability:**
$$P(A) = \sum_{i} P(A \mid B_i) P(B_i)$$

---

# 29. Bayes' Theorem

### The Engine of Robotic Localization & Perception 🔴 [MUST KNOW]
Bayes' Rule provides the mathematical mechanism to update our belief about the robot's latent state $\mathbf{x}$ upon observing noisy sensor data $\mathbf{z}$:

$$P(\mathbf{x} \mid \mathbf{z}) = \frac{P(\mathbf{z} \mid \mathbf{x}) P(\mathbf{x})}{P(\mathbf{z})} = \frac{P(\mathbf{z} \mid \mathbf{x}) P(\mathbf{x})}{\int P(\mathbf{z} \mid \mathbf{x}') P(\mathbf{x}') d\mathbf{x}'}$$

$$\text{Posterior} = \frac{\text{Likelihood} \times \text{Prior}}{\text{Evidence (Normalization Factor } \eta\text{)}}$$

- **Prior $P(\mathbf{x})$:** State belief before incorporating current sensor observation (from odometry motion prediction).
- **Likelihood $P(\mathbf{z} \mid \mathbf{x})$:** Probability of obtaining sensor reading $\mathbf{z}$ given the robot is at pose $\mathbf{x}$ (from sensor observation model).
- **Posterior $P(\mathbf{x} \mid \mathbf{z})$:** Updated state belief after fusing sensor reading.

---

# 30. Random Variables

### Expectation, Variance & Moments 🔴 [MUST KNOW]
- **Expected Value (Mean $\mu$):**
$$\mu = \mathbb{E}[X] = \int_{-\infty}^{\infty} x p(x) dx$$
- **Variance ($\sigma^2$ - Dispersion of sensor noise):**
$$\sigma^2 = \text{Var}(X) = \mathbb{E}[(X - \mu)^2] = \mathbb{E}[X^2] - (\mathbb{E}[X])^2 = \int_{-\infty}^{\infty} (x - \mu)^2 p(x) dx$$
- **Standard Deviation:** $\sigma = \sqrt{\text{Var}(X)}$ (units match the physical quantity).

---

# 31. Gaussian Distribution

### 1D Normal Distribution Equations 🔴 [MUST KNOW]
A univariate continuous random variable $X \sim \mathcal{N}(\mu, \sigma^2)$ is governed by the probability density function (PDF):

$$p(x) = \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left( -\frac{(x - \mu)^2}{2\sigma^2} \right)$$

```
1D Gaussian PDF:
             p(x)
              ^
             / \         Mean = μ
            / | \        Inflection point at μ ± σ
           /  |  \       68.3% within ±1σ
         _/   |   \_     95.4% within ±2σ
       ---+---+---+---> x
         μ-σ  μ  μ+σ
```

### Why Gaussians Dominate Robotics State Estimation 🔴 [MUST KNOW]
1. **Central Limit Theorem:** Sum of multiple independent noise sources converges to a Gaussian distribution.
2. **Computational Tractability:** Gaussians are closed under linear transformations and conditioning (multiplying two Gaussians yields another Gaussian analytically).
3. **Parametric Efficiency:** An $n$-dimensional Gaussian is completely parameterized by just its mean vector $\boldsymbol{\mu} \in \mathbb{R}^n$ and covariance matrix $\boldsymbol{\Sigma} \in \mathbb{R}^{n \times n}$.

---

# 32. Covariance

### Covariance Matrix & Uncertainty Ellipses 🔴 [MUST KNOW]
For a random vector $\mathbf{x} = [x_1, x_2, \dots, x_n]^T \in \mathbb{R}^n$, the **Covariance Matrix $\boldsymbol{\Sigma} \in \mathbb{R}^{n \times n}$** is:

$$\boldsymbol{\Sigma} = \text{Cov}(\mathbf{x}) = \mathbb{E}[(\mathbf{x} - \boldsymbol{\mu})(\mathbf{x} - \boldsymbol{\mu})^T] = \begin{bmatrix} \sigma_{x_1}^2 & \sigma_{x_1 x_2} & \dots & \sigma_{x_1 x_n} \\ \sigma_{x_2 x_1} & \sigma_{x_2}^2 & \dots & \sigma_{x_2 x_n} \\ \vdots & \vdots & \ddots & \vdots \\ \sigma_{x_n x_1} & \sigma_{x_n x_2} & \dots & \sigma_{x_n}^2 \end{bmatrix}$$

$$\text{Covariance between variables: } \sigma_{xy} = \mathbb{E}[(X - \mu_x)(Y - \mu_y)]$$

$$\text{Correlation Coefficient: } \rho_{xy} = \frac{\sigma_{xy}}{\sigma_x \sigma_y}, \quad -1 \le \rho_{xy} \le 1$$

```
2D Uncertainty Ellipse Geometry:
       ^ Y
       |           /--------\    Major axis = 2 k √λ_1  along eigenvector v_1
       |          /          \   Minor axis = 2 k √λ_2  along eigenvector v_2
       |         /     μ      \  Tilt angle θ = 0.5 atan2(2 σ_xy, σ_x² - σ_y²)
       |        \            /
       |         \----------/
       +-----------------------------> X
```

---

# 33. Multivariate Gaussian

### Mathematical Definition & Mahalanobis Distance 🔴 [MUST KNOW]
An $n$-dimensional random vector $\mathbf{x} \sim \mathcal{N}(\boldsymbol{\mu}, \boldsymbol{\Sigma})$ has PDF:

$$p(\mathbf{x}) = \frac{1}{\sqrt{(2\pi)^n \det(\boldsymbol{\Sigma})}} \exp\left( -\frac{1}{2} (\mathbf{x} - \boldsymbol{\mu})^T \boldsymbol{\Sigma}^{-1} (\mathbf{x} - \boldsymbol{\mu}) \right)$$

- **Mahalanobis Distance ($d_M$):** Measures statistical distance of point $\mathbf{x}$ from mean $\boldsymbol{\mu}$ scaled by uncertainty covariance:
$$d_M = \sqrt{(\mathbf{x} - \boldsymbol{\mu})^T \boldsymbol{\Sigma}^{-1} (\mathbf{x} - \boldsymbol{\mu})}$$
- **Robotics Use (Data Association / Gating):** In visual tracking and LiDAR SLAM, we discard outlier measurements if $d_M^2 > \chi_{n, \alpha}^2$ (Chi-squared distribution threshold).

---

# 34. Conditional Probability in Sensor Fusion

### Fusing Multiple Independent Sensor Observations 🔴 [MUST KNOW]
Suppose two independent sensors (e.g., Wheel Odometry $\hat{x}_1 \sim \mathcal{N}(\mu_1, \sigma_1^2)$ and LiDAR scan matcher $\hat{x}_2 \sim \mathcal{N}(\mu_2, \sigma_2^2)$) measure the 1D robot position $x$.  
Multiplying their Gaussian probability densities yields the optimal fused posterior $\mathcal{N}(\mu_{\text{fused}}, \sigma_{\text{fused}}^2)$:

$$\frac{1}{\sigma_{\text{fused}}^2} = \frac{1}{\sigma_1^2} + \frac{1}{\sigma_2^2} \implies \sigma_{\text{fused}}^2 = \frac{\sigma_1^2 \sigma_2^2}{\sigma_1^2 + \sigma_2^2}$$

$$\mu_{\text{fused}} = \sigma_{\text{fused}}^2 \left( \frac{\mu_1}{\sigma_1^2} + \frac{\mu_2}{\sigma_2^2} \right) = \mu_1 + \frac{\sigma_1^2}{\sigma_1^2 + \sigma_2^2} (\mu_2 - \mu_1)$$

*Notice: $\sigma_{\text{fused}}^2 < \min(\sigma_1^2, \sigma_2^2)$. Fusing two independent sensors ALWAYS results in uncertainty lower than either individual sensor!*

---

# 35. Bayes Filter

### Unified Recursive State Estimation Framework 🔴 [MUST KNOW]
All robotic filters (Kalman Filter, EKF, UKF, Particle Filter) are specific discrete implementations of the recursive **Bayes Filter**:

```
Recursive Loop:
  Bel(x_{k-1})  ──► [ 1. PREDICTION (Motion Model) ]   ──► Bel_bar(x_k)
                            │
                            ▼
                    [ 2. CORRECTION (Sensor Model) ]   ──► Bel(x_k)
```

1. **Prediction Step (Chapman-Kolmogorov Equation):**
$$\overline{\text{bel}}(\mathbf{x}_k) = P(\mathbf{x}_k \mid \mathbf{z}_{1:k-1}, \mathbf{u}_{1:k}) = \int P(\mathbf{x}_k \mid \mathbf{x}_{k-1}, \mathbf{u}_k) \text{bel}(\mathbf{x}_{k-1}) d\mathbf{x}_{k-1}$$
2. **Correction Step (Measurement Update via Bayes Rule):**
$$\text{bel}(\mathbf{x}_k) = P(\mathbf{x}_k \mid \mathbf{z}_{1:k}, \mathbf{u}_{1:k}) = \eta P(\mathbf{z}_k \mid \mathbf{x}_k) \overline{\text{bel}}(\mathbf{x}_k)$$

---

# 36. Kalman Filter Mathematics

### Complete Linear Kalman Filter (KF) Derivation 🔴 [MUST KNOW]

```
Linear State-Space System:
  State Equation:       x_k = F x_{k-1} + B u_k + w_k,    w_k ~ N(0, Q)
  Measurement Equation: z_k = H x_k + v_k,                v_k ~ N(0, R)
```

### The 5 Standard Kalman Filter Equations 🔴 [MUST MEMORIZE]

```
+---------------------------------------------------------------------------------------------------+
| 1. PREDICT STATE:       x̂_k|k-1 = F x̂_{k-1|k-1} + B u_k                                           |
| 2. PREDICT COVARIANCE:  P_k|k-1 = F P_{k-1|k-1} F^T + Q                                           |
| 3. INNOVATION RESIDUAL: y_k = z_k - H x̂_k|k-1                                                    |
| 4. KALMAN GAIN:         K_k = P_k|k-1 H^T (H P_k|k-1 H^T + R)^-1                                 |
| 5. UPDATE STATE:        x̂_k|k = x̂_k|k-1 + K_k y_k                                                |
| 6. UPDATE COVARIANCE:   P_k|k = (I - K_k H) P_k|k-1   [Joseph Form: (I-KH)P(I-KH)^T + KRK^T]       |
+---------------------------------------------------------------------------------------------------+
```

### Physical Intuition Behind Kalman Gain $\mathbf{K}$
- If Measurement Noise is huge ($\mathbf{R} \to \infty$): $\mathbf{K} \to \mathbf{0} \implies \hat{\mathbf{x}}_k = \hat{\mathbf{x}}_{k|k-1}$ (Trust motion model entirely).
- If Measurement is perfect ($\mathbf{R} \to \mathbf{0}$): $\mathbf{K} \to \mathbf{H}^{-1} \implies \hat{\mathbf{x}}_k = \mathbf{H}^{-1} \mathbf{z}_k$ (Trust sensor measurement entirely).

---

# 37. EKF Mathematics

### Extended Kalman Filter Non-Linear Formulation 🔴 [MUST KNOW]
When system dynamics $\mathbf{f}$ or measurement models $\mathbf{h}$ are non-linear:

$$\mathbf{x}_k = \mathbf{f}(\mathbf{x}_{k-1}, \mathbf{u}_k) + \mathbf{w}_k, \quad \mathbf{w}_k \sim \mathcal{N}(\mathbf{0}, \mathbf{Q})$$
$$\mathbf{z}_k = \mathbf{h}(\mathbf{x}_k) + \mathbf{v}_k, \quad \mathbf{v}_k \sim \mathcal{N}(\mathbf{0}, \mathbf{R})$$

### EKF Algorithm Steps:
1. **State Prediction:** $\hat{\mathbf{x}}_{k|k-1} = \mathbf{f}(\hat{\mathbf{x}}_{k-1|k-1}, \mathbf{u}_k)$.
2. **Covariance Prediction:** $\mathbf{P}_{k|k-1} = \mathbf{F}_k \mathbf{P}_{k-1|k-1} \mathbf{F}_k^T + \mathbf{Q}_k$, where $\mathbf{F}_k = \left.\frac{\partial \mathbf{f}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}_{k-1|k-1}}$.
3. **Innovation:** $\mathbf{y}_k = \mathbf{z}_k - \mathbf{h}(\hat{\mathbf{x}}_{k|k-1})$.
4. **Kalman Gain:** $\mathbf{K}_k = \mathbf{P}_{k|k-1} \mathbf{H}_k^T (\mathbf{H}_k \mathbf{P}_{k|k-1} \mathbf{H}_k^T + \mathbf{R}_k)^{-1}$, where $\mathbf{H}_k = \left.\frac{\partial \mathbf{h}}{\partial \mathbf{x}}\right|_{\hat{\mathbf{x}}_{k|k-1}}$.
5. **State Update:** $\hat{\mathbf{x}}_{k|k} = \hat{\mathbf{x}}_{k|k-1} + \mathbf{K}_k \mathbf{y}_k$.
6. **Covariance Update:** $\mathbf{P}_{k|k} = (\mathbf{I} - \mathbf{K}_k \mathbf{H}_k) \mathbf{P}_{k|k-1}$.

---

# 38. Particle Filter Mathematics

### Sequential Monte Carlo (SMC) & AMCL 🔴 [MUST KNOW]
Particle filters represent non-Gaussian arbitrary posterior distributions using a set of $M$ discrete weighted samples (particles) $\mathcal{S}_k = \{ (\mathbf{x}_k^{[m]}, w_k^{[m]}) \}_{m=1}^M$:

$$\text{bel}(\mathbf{x}_k) \approx \sum_{m=1}^M w_k^{[m]} \delta(\mathbf{x}_k - \mathbf{x}_k^{[m]})$$

1. **Prediction (Sampling from Proposal):** Sample particle $\mathbf{x}_k^{[m]} \sim P(\mathbf{x}_k \mid \mathbf{x}_{k-1}^{[m]}, \mathbf{u}_k)$.
2. **Measurement Weighting:** Assign importance weight $w_k^{[m]} = P(\mathbf{z}_k \mid \mathbf{x}_k^{[m]})$.
3. **Weight Normalization:** $\tilde{w}_k^{[m]} = \frac{w_k^{[m]}}{\sum_{j=1}^M w_k^{[j]}}$.
4. **Resampling (Low-Variance Resampling):** Draw $M$ new particles with probability proportional to normalized weights $\tilde{w}_k^{[m]}$ to eliminate low-likelihood hypotheses.

---

# 39. Least Squares

### The Normal Equation Derivation 🔴 [MUST KNOW]
Given an overdetermined linear system $\mathbf{A}\mathbf{x} = \mathbf{b}$ ($\mathbf{A} \in \mathbb{R}^{m \times n}, m > n$), find $\mathbf{x}^*$ minimizing residual sum of squares:

$$S(\mathbf{x}) = \|\mathbf{A}\mathbf{x} - \mathbf{b}\|^2 = (\mathbf{A}\mathbf{x} - \mathbf{b})^T (\mathbf{A}\mathbf{x} - \mathbf{b}) = \mathbf{x}^T \mathbf{A}^T \mathbf{A} \mathbf{x} - 2 \mathbf{b}^T \mathbf{A} \mathbf{x} + \mathbf{b}^T \mathbf{b}$$

Taking the gradient with respect to $\mathbf{x}$ and setting to $\mathbf{0}$:

$$\nabla_{\mathbf{x}} S(\mathbf{x}) = 2 \mathbf{A}^T \mathbf{A} \mathbf{x} - 2 \mathbf{A}^T \mathbf{b} = \mathbf{0} \implies \mathbf{A}^T \mathbf{A} \mathbf{x} = \mathbf{A}^T \mathbf{b}$$

$$\mathbf{x}^* = (\mathbf{A}^T \mathbf{A})^{-1} \mathbf{A}^T \mathbf{b} = \mathbf{A}^\dagger \mathbf{b} \quad (\mathbf{A}^\dagger = \text{Moore-Penrose Pseudoinverse})$$

---

# 40. Weighted Least Squares

### Incorporating Sensor Noise Covariance 🔴 [MUST KNOW]
When measurements have unequal variances $\boldsymbol{\Sigma}_{\mathbf{v}} = \mathbf{W}^{-1}$:

$$\min_{\mathbf{x}} (\mathbf{A}\mathbf{x} - \mathbf{b})^T \mathbf{W} (\mathbf{A}\mathbf{x} - \mathbf{b})$$

$$\mathbf{x}^* = (\mathbf{A}^T \mathbf{W} \mathbf{A})^{-1} \mathbf{A}^T \mathbf{W} \mathbf{b}$$

---

# 41. Nonlinear Least Squares

### General Formulation in SLAM & Bundle Adjustment 🔴 [MUST KNOW]
Minimize the sum of non-linear squared residuals $\mathbf{r}_i(\mathbf{x}) = \mathbf{z}_i - \mathbf{h}_i(\mathbf{x})$:

$$\min_{\mathbf{x}} F(\mathbf{x}) = \frac{1}{2} \sum_{i=1}^m \|\mathbf{r}_i(\mathbf{x})\|_{\boldsymbol{\Sigma}_i}^2 = \frac{1}{2} \mathbf{r}(\mathbf{x})^T \boldsymbol{\Sigma}^{-1} \mathbf{r}(\mathbf{x})$$

---

# 42. Gauss-Newton

### Iterative First-Order Residual Optimization 🔴 [MUST KNOW]
Linearize residual vector $\mathbf{r}(\mathbf{x} + \Delta \mathbf{x}) \approx \mathbf{r}(\mathbf{x}) + \mathbf{J} \Delta \mathbf{x}$, where $\mathbf{J} = \frac{\partial \mathbf{r}}{\partial \mathbf{x}}$:

$$\min_{\Delta \mathbf{x}} \frac{1}{2} \|\mathbf{r}(\mathbf{x}) + \mathbf{J} \Delta \mathbf{x}\|^2$$

$$\text{Normal Equation for Step } \Delta \mathbf{x}: \quad (\mathbf{J}^T \mathbf{J}) \Delta \mathbf{x} = -\mathbf{J}^T \mathbf{r}(\mathbf{x})$$

$$\mathbf{x}_{k+1} = \mathbf{x}_k + \Delta \mathbf{x}$$

---

# 43. Levenberg-Marquardt

### Damped Non-Linear Least Squares (Trust Region) 🔴 [MUST KNOW]
When $\mathbf{J}^T \mathbf{J}$ is nearly singular or initial guess is far from minimum, Gauss-Newton can diverge wildly.  
**Levenberg-Marquardt (LM)** introduces an adaptive damping parameter $\lambda$:

$$(\mathbf{J}^T \mathbf{J} + \lambda \mathbf{I}) \Delta \mathbf{x} = -\mathbf{J}^T \mathbf{r}(\mathbf{x}) \quad \left(\text{or } (\mathbf{J}^T \mathbf{J} + \lambda \text{diag}(\mathbf{J}^T \mathbf{J})) \Delta \mathbf{x} = -\mathbf{J}^T \mathbf{r}\right)$$

```
Behavior as λ Varies:
  - λ → 0:  Becomes pure GAUSS-NEWTON (Fast quadratic convergence near minimum).
  - λ → ∞:  Becomes pure GRADIENT DESCENT with tiny step size (Guaranteed descent far from minimum).
```

---

# 44. Gradient Descent

### First-Order Optimization Mechanics 🔴 [MUST KNOW]
Iteratively moves in the negative gradient direction:

$$\mathbf{x}_{k+1} = \mathbf{x}_k - \alpha \nabla f(\mathbf{x}_k)$$

Where $\alpha > 0$ is the learning rate / step size.
- **Convergence Condition:** If $f$ is $L$-Lipschitz smooth, convergence requires $\alpha < \frac{2}{L}$.

---

# 45. Convexity

### Convex Functions & Sets in Trajectory Planning 🔴 [MUST KNOW]
- **Convex Set $\mathcal{C}$:** For any $\mathbf{x}, \mathbf{y} \in \mathcal{C}$ and $\theta \in [0, 1]$, the line segment $\theta \mathbf{x} + (1-\theta)\mathbf{y} \in \mathcal{C}$.
- **Convex Function $f(\mathbf{x})$:**
$$f(\theta \mathbf{x} + (1-\theta)\mathbf{y}) \le \theta f(\mathbf{x}) + (1-\theta)f(\mathbf{y})$$
- **Core Property:** For a convex optimization problem, **every local minimum is guaranteed to be a global minimum**.

---

# 46. Constraints and Optimization

### Constrained Optimization & Feasible Sets 🔴 [MUST KNOW]
$$\min_{\mathbf{x}} f(\mathbf{x}) \quad \text{subject to } g_i(\mathbf{x}) \le 0 \ (i=1,\dots,m), \quad h_j(\mathbf{x}) = 0 \ (j=1,\dots,p)$$

- In robotics: $g_i(\mathbf{x})$ enforces velocity limits, acceleration limits, and obstacle avoidance clearances.

---

# 47. Lagrange Multipliers

### Equality Constrained Optimization 🔴 [MUST KNOW]
To minimize $f(\mathbf{x})$ subject to equality constraint $g(\mathbf{x}) = 0$, construct the Lagrangian:

$$\mathcal{L}(\mathbf{x}, \lambda) = f(\mathbf{x}) + \lambda g(\mathbf{x})$$

$$\text{Optimality Conditions: } \nabla_{\mathbf{x}} \mathcal{L} = \nabla f(\mathbf{x}) + \lambda \nabla g(\mathbf{x}) = \mathbf{0}, \qquad \nabla_\lambda \mathcal{L} = g(\mathbf{x}) = 0$$

---

# 48. Linear Programming / Quadratic Programming

### LP vs QP in Model Predictive Control (MPC) 🔴 [MUST KNOW]
- **Linear Program (LP):** Linear cost, linear constraints $\implies \min_{\mathbf{x}} \mathbf{c}^T \mathbf{x} \text{ s.t. } \mathbf{A}\mathbf{x} \le \mathbf{b}$.
- **Quadratic Program (QP):** Quadratic cost, linear constraints $\implies \min_{\mathbf{x}} \frac{1}{2} \mathbf{x}^T \mathbf{Q} \mathbf{x} + \mathbf{c}^T \mathbf{x} \text{ s.t. } \mathbf{A}\mathbf{x} \le \mathbf{b}$.
- In robotics MPC: Tracking error and actuator effort are quadratic ($(\mathbf{x}-\mathbf{x}_{\text{ref}})^T \mathbf{Q} (\mathbf{x}-\mathbf{x}_{\text{ref}}) + \mathbf{u}^T \mathbf{R} \mathbf{u}$), solvable in real-time ($< 10\text{ ms}$) via active-set or interior-point QP solvers (e.g., OSQP, qpOASES).

---

# 49. Numerical Stability

### Condition Number & Floating Point Precision 🔴 [MUST KNOW]
- **Condition Number $\kappa(\mathbf{A})$:** Measures sensitivity of linear system $\mathbf{A}\mathbf{x} = \mathbf{b}$ to input errors:
$$\kappa(\mathbf{A}) = \|\mathbf{A}\| \|\mathbf{A}^{-1}\| = \frac{\sigma_{\max}(\mathbf{A})}{\sigma_{\min}(\mathbf{A})}$$
- If $\kappa(\mathbf{A}) \approx 1$: Well-conditioned.
- If $\kappa(\mathbf{A}) \gg 10^7$ in 32-bit `float`: **Ill-conditioned matrix**. Inverting it loses all numerical precision.

---

# 50. Complexity and Numerical Cost

### Big-$\mathcal{O}$ Computation Costs in Real-Time Robotics 🔴 [MUST KNOW]

```
+---------------------------------------+----------------------------------+--------------------------------------+
| Operation                             | Mathematical Complexity          | Real-Time Practical Note             |
+---------------------------------------+----------------------------------+--------------------------------------+
| Matrix Addition (n x n)               | O(n^2)                           | Cheap, SIMD vectorized              |
| Matrix Multiplication (m x k * k x n) | O(m * k * n)                     | Dense O(n^3); use fixed-size Eigen   |
| Matrix Inverse / Linear Solve (n x n) | O(n^3)  [Cholesky: 1/3 n^3]      | Expensive for n > 100               |
| EKF State Prediction (n states)       | O(n^3) due to FPF^T              | Limit state vector size              |
| EKF-SLAM (N landmarks)                | O(N^2)                           | Fails for large maps (use Factor Graph)|
| Graph SLAM / Bundle Adjustment        | O(P^3 + L) via Schur Complement  | Solvable in real-time with sparsity  |
+---------------------------------------+----------------------------------+--------------------------------------+
```

---

# 51. Robotics Kinematics Mathematics

### Forward & Inverse Kinematics of a 2-Link Planar Arm 🔴 [MUST KNOW]

```
2-Link Planar Manipulator:
       ^ Y
       |              (x, y) End-Effector
       |              /
       |          l_2/
       |            / q_2 (Relative angle)
       |      o----+
       |     /
       | l_1/ q_1
       +---+-----------------> X
```

### Forward Kinematics Equations:
$$x = l_1 \cos(q_1) + l_2 \cos(q_1 + q_2)$$
$$y = l_1 \sin(q_1) + l_2 \sin(q_1 + q_2)$$

### Analytical Jacobian $\mathbf{J}(\mathbf{q}) \in \mathbb{R}^{2 \times 2}$:
$$\mathbf{J}(\mathbf{q}) = \begin{bmatrix} \frac{\partial x}{\partial q_1} & \frac{\partial x}{\partial q_2} \\ \frac{\partial y}{\partial q_1} & \frac{\partial y}{\partial q_2} \end{bmatrix} = \begin{bmatrix} -l_1\sin(q_1) - l_2\sin(q_1+q_2) & -l_2\sin(q_1+q_2) \\ l_1\cos(q_1) + l_2\cos(q_1+q_2) & l_2\cos(q_1+q_2) \end{bmatrix}$$

$$\det(\mathbf{J}(\mathbf{q})) = l_1 l_2 \sin(q_2)$$
*Singularity occurs when $\sin(q_2) = 0 \implies q_2 = 0^\circ \text{ or } 180^\circ$ (Arm is fully outstretched or folded back).*

---

# 52. Differential Drive Mathematics

### Forward & Inverse Kinematics of Differential Drive AMRs 🔴 [MUST KNOW]

```
Differential Drive Model:
               +-------+ (Wheel R, velocity v_R)
               |       |
       +-------+---x---+-------+  Track width = L, Wheel radius = r
       |           |           |
       |           + (ICC)     |
       |           |           |
       +-------+---x---+-------+
               |       |
               +-------+ (Wheel L, velocity v_L)
```

- **Forward Kinematics (Wheel Speeds $\omega_R, \omega_L$ to Body Velocities $v, \omega$):**
$$v = \frac{r}{2} (\omega_R + \omega_L), \qquad \omega = \frac{r}{L} (\omega_R - \omega_L)$$

- **Inverse Kinematics (Desired $v, \omega$ to Wheel Speeds $\omega_R, \omega_L$):**
$$\omega_R = \frac{v + \frac{L}{2}\omega}{r}, \qquad \omega_L = \frac{v - \frac{L}{2}\omega}{r}$$

- **Instantaneous Center of Curvature (ICC) Radius $R_{\text{ICC}}$:**
$$R_{\text{ICC}} = \frac{v}{\omega} = \frac{L}{2} \left( \frac{\omega_R + \omega_L}{\omega_R - \omega_L} \right)$$

---

# 53. Differential Drive Odometry

### Dead Reckoning Discrete Pose Integration 🔴 [MUST KNOW]
Given linear displacement $\Delta s = \frac{\Delta s_R + \Delta s_L}{2} = v \Delta t$ and angular displacement $\Delta \theta = \frac{\Delta s_R - \Delta s_L}{L} = \omega \Delta t$:

### 1. Midpoint (2nd-Order Runge-Kutta) Approximation:
$$x_{k+1} = x_k + \Delta s \cos\left(\theta_k + \frac{\Delta \theta}{2}\right)$$
$$y_{k+1} = y_k + \Delta s \sin\left(\theta_k + \frac{\Delta \theta}{2}\right)$$
$$\theta_{k+1} = \theta_k + \Delta \theta$$

### 2. Exact Arc Integration (when $\omega \ne 0$):
$$x_{k+1} = x_k + \frac{v}{\omega} \left( \sin(\theta_k + \omega \Delta t) - \sin(\theta_k) \right)$$
$$y_{k+1} = y_k - \frac{v}{\omega} \left( \cos(\theta_k + \omega \Delta t) - \cos(\theta_k) \right)$$
$$\theta_{k+1} = \theta_k + \omega \Delta t$$

---

# 54. Bicycle Model Mathematics

### Ackermann Kinematic Vehicle Model 🔴 [MUST KNOW]

```
Bicycle Kinematic Model:
                  Front Wheel (Steering angle δ)
                     /
                    /
                   +
                   |
                   | Wheelbase = L
                   |
                   +
                  Rear Wheel (Heading θ)
```

$$\dot{x} = v \cos(\theta), \qquad \dot{y} = v \sin(\theta), \qquad \dot{\theta} = \frac{v}{L} \tan(\delta)$$

- **Path Curvature $\kappa$:**
$$\kappa = \frac{1}{R} = \frac{\tan(\delta)}{L}$$

---

# 55. Control Mathematics Review

### State-Space Representation & Stability 🔴 [MUST KNOW]
$$\dot{\mathbf{x}} = \mathbf{A}\mathbf{x} + \mathbf{B}\mathbf{u}, \qquad \mathbf{y} = \mathbf{C}\mathbf{x} + \mathbf{D}\mathbf{u}$$

- **Controllability Matrix $\mathcal{C}$ (Full Row Rank Test):**
$$\mathcal{C} = \begin{bmatrix} \mathbf{B} & \mathbf{A}\mathbf{B} & \mathbf{A}^2\mathbf{B} & \dots & \mathbf{A}^{n-1}\mathbf{B} \end{bmatrix}, \quad \text{Rank}(\mathcal{C}) = n$$
- **Observability Matrix $\mathcal{O}$ (Full Column Rank Test):**
$$\mathcal{O} = \begin{bmatrix} \mathbf{C} \\ \mathbf{C}\mathbf{A} \\ \mathbf{C}\mathbf{A}^2 \\ \vdots \\ \mathbf{C}\mathbf{A}^{n-1} \end{bmatrix}, \quad \text{Rank}(\mathcal{O}) = n$$

---

# 56. Discrete-Time Robotics Mathematics

### Numerical Integration Schemes (Euler vs RK4) 🔴 [MUST KNOW]
To integrate non-linear continuous ODE $\dot{\mathbf{x}} = \mathbf{f}(\mathbf{x}, \mathbf{u})$ over time step $\Delta t$:

1. **Forward Euler (1st Order - Fast but unstable for large $\Delta t$):**
$$\mathbf{x}_{k+1} = \mathbf{x}_k + \Delta t \mathbf{f}(\mathbf{x}_k, \mathbf{u}_k)$$
2. **Classical Runge-Kutta 4th Order (RK4 - Highly accurate for IMU/physics integration):**
$$\mathbf{k}_1 = \mathbf{f}(\mathbf{x}_k, \mathbf{u}_k)$$
$$\mathbf{k}_2 = \mathbf{f}\left(\mathbf{x}_k + \frac{\Delta t}{2}\mathbf{k}_1, \mathbf{u}_k\right)$$
$$\mathbf{k}_3 = \mathbf{f}\left(\mathbf{x}_k + \frac{\Delta t}{2}\mathbf{k}_2, \mathbf{u}_k\right)$$
$$\mathbf{k}_4 = \mathbf{f}(\mathbf{x}_k + \Delta t \mathbf{k}_3, \mathbf{u}_k)$$
$$\mathbf{x}_{k+1} = \mathbf{x}_k + \frac{\Delta t}{6} (\mathbf{k}_1 + 2\mathbf{k}_2 + 2\mathbf{k}_3 + \mathbf{k}_4)$$

---

# 57. Computer Vision Mathematics Review

### Pinhole Projection, Stereo Depth & Epipolar Geometry 🔴 [MUST KNOW]
- **Pinhole Projection:**
$$u = f_x \frac{X_c}{Z_c} + c_x, \qquad v = f_y \frac{Y_c}{Z_c} + c_y$$
- **Stereo Depth from Disparity $d = u_L - u_R$:**
$$Z = \frac{f \cdot B}{d}, \qquad |\Delta Z| \approx \frac{Z^2}{f \cdot B} |\Delta d|$$
- **Epipolar Constraint:**
$$\mathbf{x}_2^T \mathbf{E} \mathbf{x}_1 = 0 \quad (\text{Normalized coordinates}), \qquad \mathbf{E} = [\mathbf{t}]_\times \mathbf{R}$$

---

# 58. SLAM Mathematics Review

### Factor Graph Optimization & Non-Linear Least Squares 🔴 [MUST KNOW]
In modern SLAM (e.g., GTSAM, Ceres, g2o), the full trajectory and landmark map are estimated jointly by minimizing all factor error residuals:

$$\mathbf{x}^* = \arg\min_{\mathbf{x}} \sum_{k} \|\mathbf{x}_k - \mathbf{f}(\mathbf{x}_{k-1}, \mathbf{u}_k)\|_{\mathbf{Q}_k}^2 + \sum_{i,j} \|\mathbf{z}_{ij} - \mathbf{h}(\mathbf{x}_i, \mathbf{l}_j)\|_{\mathbf{R}_{ij}}^2$$

$$\text{Sparse Normal Equation: } \mathbf{H} \Delta \mathbf{x} = -\mathbf{b}, \quad \mathbf{H} = \mathbf{J}^T \boldsymbol{\Sigma}^{-1} \mathbf{J}$$

---

# 59. Sensor Fusion Mathematics Review

### State & Measurement Models Across Sensor Modalities 🔴 [MUST KNOW]

```
+--------------------------+------------------------------+-------------------------------------------+
| Sensor Modality          | State Vector x               | Measurement Model z = h(x)                |
+--------------------------+------------------------------+-------------------------------------------+
| Wheel Encoders           | [x, y, θ, v, ω]^T            | z = [v, ω]^T  (Direct linear mapping)     |
| IMU Gyro + Accelerometer | [p, v, q, b_a, b_g]^T        | z_gyro = ω + b_g, z_acc = R^T(a - g) + b_a|
| 2D/3D LiDAR ICP          | [x, y, θ]^T                  | z_pose = x (Relative transformation SE(2))|
| Camera Landmark Observation| [x, y, z, roll, pitch, yaw]| z = [fx(X/Z)+cx, fy(Y/Z)+cy]^T            |
+--------------------------+------------------------------+-------------------------------------------+
```

---

# 60. Whiteboard Mathematics Problems

### 30 Step-by-Step Robotics Whiteboard Interview Problems 🔴 [MUST KNOW]

#### Problem 1: 2D Point Rotation
- **Question:** Rotate point $\mathbf{p} = [4, 2]^T$ counter-clockwise by $90^\circ$.
- **Solution:** $\mathbf{R}(90^\circ) = \begin{bmatrix} 0 & -1 \\ 1 & 0 \end{bmatrix}$. $\mathbf{p}' = \mathbf{R}\mathbf{p} = \begin{bmatrix} 0(4) - 1(2) \\ 1(4) + 0(2) \end{bmatrix} = \mathbf{\begin{bmatrix} -2 \\ 4 \end{bmatrix}}$.
- **Follow-up:** "What is the determinant of this matrix?" $\implies \det(\mathbf{R}) = 0(0) - (-1)(1) = +1$.

#### Problem 2: 2D Rigid Body Transformation
- **Question:** A robot base is at $[3, 5]^T$ in map frame with orientation $\theta = 0^\circ$. An obstacle is detected at $[2, 1]^T$ in robot base frame. Map coordinates?
- **Solution:** $\mathbf{T} = \begin{bmatrix} 1 & 0 & 3 \\ 0 & 1 & 5 \\ 0 & 0 & 1 \end{bmatrix}$. $\mathbf{p}_m = \mathbf{T} \begin{bmatrix} 2 \\ 1 \\ 1 \end{bmatrix} = \mathbf{\begin{bmatrix} 5 \\ 6 \\ 1 \end{bmatrix}} \implies (5, 6)\text{ m}$.

#### Problem 3: Homogeneous Transform Inverse
- **Question:** Invert $\mathbf{T} = \begin{bmatrix} 0 & -1 & 4 \\ 1 & 0 & 2 \\ 0 & 0 & 1 \end{bmatrix}$.
- **Solution:** $\mathbf{R}^T = \begin{bmatrix} 0 & 1 \\ -1 & 0 \end{bmatrix}$, $-\mathbf{R}^T \mathbf{t} = -\begin{bmatrix} 0 & 1 \\ -1 & 0 \end{bmatrix} \begin{bmatrix} 4 \\ 2 \end{bmatrix} = -\begin{bmatrix} 2 \\ -4 \end{bmatrix} = \begin{bmatrix} -2 \\ 4 \end{bmatrix}$.  
  $$\mathbf{T}^{-1} = \mathbf{\begin{bmatrix} 0 & 1 & -2 \\ -1 & 0 & 4 \\ 0 & 0 & 1 \end{bmatrix}}$$

#### Problem 4: Dot Product Projection
- **Question:** Project vector $\mathbf{v} = [3, 4]^T$ onto unit vector $\hat{\mathbf{u}} = [1, 0]^T$.
- **Solution:** $\text{proj} = (\mathbf{v} \cdot \hat{\mathbf{u}}) \hat{\mathbf{u}} = (3(1) + 4(0)) [1, 0]^T = \mathbf{[3, 0]^T}$.

#### Problem 5: Cross Product & Angular Velocity
- **Question:** $\boldsymbol{\omega} = [0, 0, 3]^T\text{ rad/s}$, $\mathbf{r} = [2, 0, 0]^T\text{ m}$. Compute linear velocity $\mathbf{v}$.
- **Solution:** $\mathbf{v} = \boldsymbol{\omega} \times \mathbf{r} = [0(0)-3(0), 3(2)-0(0), 0(0)-0(2)]^T = \mathbf{[0, 6, 0]^T\text{ m/s}}$.

#### Problem 6: Eigenvalues of Diagonal Matrix
- **Question:** Find eigenvalues of covariance $\boldsymbol{\Sigma} = \begin{bmatrix} 9 & 0 \\ 0 & 4 \end{bmatrix}$.
- **Solution:** $\det(\boldsymbol{\Sigma} - \lambda \mathbf{I}) = (9-\lambda)(4-\lambda) = 0 \implies \mathbf{\lambda_1 = 9, \lambda_2 = 4}$. Standard deviations: $\sigma_x = 3, \sigma_y = 2$.

#### Problem 7: 1D Sensor Fusion
- **Question:** Sensor 1 measures $x = 10\text{ m}, \sigma_1^2 = 4$. Sensor 2 measures $x = 12\text{ m}, \sigma_2^2 = 4$. Compute fused estimate.
- **Solution:** Equal variance $\implies \mu = \frac{10+12}{2} = \mathbf{11.0\text{ m}}$, $\sigma_{\text{fused}}^2 = \frac{4 \times 4}{4 + 4} = \mathbf{2.0}$.

#### Problem 8: 1D Kalman Filter Update
- **Question:** Prior $\hat{x} = 5.0, P = 6.0$. Measurement $z = 8.0, R = 2.0$. Measurement matrix $H = 1.0$. Compute new state and covariance.
- **Solution:** $K = \frac{P}{P+R} = \frac{6}{6+2} = \mathbf{0.75}$.  
  $\hat{x}_{\text{new}} = 5.0 + 0.75(8.0 - 5.0) = 5.0 + 0.75(3.0) = \mathbf{7.25}$.  
  $P_{\text{new}} = (1 - K)P = (1 - 0.75)(6.0) = \mathbf{1.50}$.

#### Problem 9: Differential Drive Kinematics
- **Question:** AMR has wheel radius $r = 0.1\text{ m}$, track width $L = 0.5\text{ m}$. Wheel speeds $\omega_R = 12\text{ rad/s}, \omega_L = 8\text{ rad/s}$. Find $v, \omega$.
- **Solution:** $v = \frac{0.1}{2}(12 + 8) = \mathbf{1.0\text{ m/s}}$. $\omega = \frac{0.1}{0.5}(12 - 8) = \frac{0.1}{0.5}(4) = \mathbf{0.8\text{ rad/s}}$.

#### Problem 10: Differential Drive In-Place Rotation
- **Question:** Desired $\omega = 1.0\text{ rad/s}, v = 0\text{ m/s}$. $r = 0.1\text{ m}, L = 0.6\text{ m}$. Wheel velocities?
- **Solution:** $\omega_R = \frac{0 + 0.3(1.0)}{0.1} = \mathbf{+3.0\text{ rad/s}}$, $\omega_L = \frac{0 - 0.3(1.0)}{0.1} = \mathbf{-3.0\text{ rad/s}}$.

#### Problem 11: Pinhole Projection
- **Question:** $f_x = 800, c_x = 320$. 3D point $X_c = 1.5\text{ m}, Z_c = 3.0\text{ m}$. Pixel $u$?
- **Solution:** $u = 800 \left(\frac{1.5}{3.0}\right) + 320 = 800(0.5) + 320 = \mathbf{720\text{ pixels}}$.

#### Problem 12: Stereo Depth
- **Question:** $f = 1000\text{ px}, B = 0.2\text{ m}$, disparity $d = 20\text{ px}$. Depth $Z$?
- **Solution:** $Z = \frac{1000 \times 0.2}{20} = \frac{200}{20} = \mathbf{10.0\text{ meters}}$.

#### Problem 13: Normal Equation Least Squares
- **Question:** Fit line $y = mx$ to points $(1, 2)$ and $(2, 5)$.
- **Solution:** $\mathbf{A} = \begin{bmatrix} 1 \\ 2 \end{bmatrix}, \mathbf{b} = \begin{bmatrix} 2 \\ 5 \end{bmatrix}$. $\mathbf{A}^T\mathbf{A} = 1^2 + 2^2 = 5$. $\mathbf{A}^T\mathbf{b} = 1(2) + 2(5) = 12$. $m = \frac{12}{5} = \mathbf{2.4}$.

#### Problem 14: Gradient Calculation
- **Question:** $f(x, y) = x^2 + 3xy + y^2$. Compute $\nabla f(1, 2)$.
- **Solution:** $\frac{\partial f}{\partial x} = 2x + 3y = 2(1)+3(2) = 8$. $\frac{\partial f}{\partial y} = 3x + 2y = 3(1)+2(2) = 7$. $\nabla f(1, 2) = \mathbf{[8, 7]^T}$.

#### Problem 15: Jacobian Matrix
- **Question:** $\mathbf{f}(x, y) = \begin{bmatrix} x^2 y \\ x + \sin(y) \end{bmatrix}$. Compute $\mathbf{J}(1, 0)$.
- **Solution:** $\mathbf{J} = \begin{bmatrix} 2xy & x^2 \\ 1 & \cos(y) \end{bmatrix} \implies \mathbf{J}(1, 0) = \mathbf{\begin{bmatrix} 0 & 1 \\ 1 & 1 \end{bmatrix}}$.

#### Problem 16: Quaternion to Axis-Angle
- **Question:** $\mathbf{q} = [\frac{\sqrt{3}}{2}, 0, 0, \frac{1}{2}]^T$. Find angle $\theta$ and rotation axis $\hat{\mathbf{u}}$.
- **Solution:** $w = \cos(\theta/2) = \frac{\sqrt{3}}{2} \implies \theta/2 = 30^\circ \implies \mathbf{\theta = 60^\circ \ (\frac{\pi}{3}\text{ rad})}$.  
  $\sin(\theta/2) = 0.5 \implies \hat{\mathbf{u}} = \frac{[0, 0, 0.5]^T}{0.5} = \mathbf{[0, 0, 1]^T}$ (Pure Z-axis rotation).

#### Problem 17: Ackermann Steering Curvature
- **Question:** Wheelbase $L = 2.0\text{ m}$, steering angle $\delta = 45^\circ$ ($\tan(45^\circ)=1$). Curvature $\kappa$ and turning radius $R$?
- **Solution:** $\kappa = \frac{\tan(45^\circ)}{2.0} = \mathbf{0.5\text{ m}^{-1}}$. $R = \frac{1}{\kappa} = \mathbf{2.0\text{ meters}}$.

#### Problem 18: Linear System Solution
- **Question:** Solve $\begin{bmatrix} 2 & 1 \\ 1 & 2 \end{bmatrix} \begin{bmatrix} x_1 \\ x_2 \end{bmatrix} = \begin{bmatrix} 4 \\ 5 \end{bmatrix}$.
- **Solution:** $2x_1 + x_2 = 4 \implies x_2 = 4 - 2x_1$. Sub into row 2: $x_1 + 2(4 - 2x_1) = 5 \implies -3x_1 + 8 = 5 \implies -3x_1 = -3 \implies \mathbf{x_1 = 1, x_2 = 2}$.

#### Problem 19: Mahalanobis Distance
- **Question:** State mean $\boldsymbol{\mu} = [0, 0]^T$, point $\mathbf{x} = [2, 0]^T$, covariance $\boldsymbol{\Sigma} = \begin{bmatrix} 4 & 0 \\ 0 & 1 \end{bmatrix}$. Compute $d_M$.
- **Solution:** $d_M = \sqrt{[2, 0] \begin{bmatrix} 0.25 & 0 \\ 0 & 1 \end{bmatrix} \begin{bmatrix} 2 \\ 0 \end{bmatrix}} = \sqrt{2(0.25)(2) + 0} = \sqrt{1.0} = \mathbf{1.0}$.

#### Problem 20: 2-Link Planar Forward Kinematics
- **Question:** $l_1 = 1.0\text{ m}, l_2 = 1.0\text{ m}, q_1 = 90^\circ, q_2 = -90^\circ$. Find end-effector $(x, y)$.
- **Solution:** $x = 1.0\cos(90^\circ) + 1.0\cos(0^\circ) = 0 + 1.0 = \mathbf{1.0\text{ m}}$.  
  $y = 1.0\sin(90^\circ) + 1.0\sin(0^\circ) = 1.0 + 0 = \mathbf{1.0\text{ m}}$.

#### Problem 21: Gradient Descent Step
- **Question:** $f(x) = x^2 - 4x + 7$, initial $x_0 = 0$, learning rate $\alpha = 0.1$. Find $x_1$.
- **Solution:** $f'(x) = 2x - 4 \implies f'(0) = -4$. $x_1 = 0 - 0.1(-4) = \mathbf{+0.4}$.

#### Problem 22: Euler Integration of Velocity
- **Question:** $x_0 = 10\text{ m}, v_0 = 2\text{ m/s}, a = 1\text{ m/s}^2, \Delta t = 1\text{ s}$. Compute $x_1, v_1$ using Forward Euler.
- **Solution:** $v_1 = v_0 + a \Delta t = 2 + 1(1) = \mathbf{3\text{ m/s}}$. $x_1 = x_0 + v_0 \Delta t = 10 + 2(1) = \mathbf{12\text{ m}}$.

#### Problem 23: Covariance Propagation
- **Question:** $y = 3x + 5$, where $x \sim \mathcal{N}(2, 4)$. What is the distribution of $y$?
- **Solution:** $\mu_y = 3(2) + 5 = 11$. $\sigma_y^2 = 3^2 \sigma_x^2 = 9(4) = 36$. $\mathbf{y \sim \mathcal{N}(11, 36)}$.

#### Problem 24: Matrix Determinant Invertibility Test
- **Question:** Is $\mathbf{A} = \begin{bmatrix} 2 & 4 \\ 3 & 6 \end{bmatrix}$ invertible?
- **Solution:** $\det(\mathbf{A}) = 2(6) - 4(3) = 12 - 12 = \mathbf{0}$. Matrix is singular $\implies$ **NOT invertible**.

#### Problem 25: Unit Vector Normalization
- **Question:** Find unit vector of $\mathbf{a} = [2, -2, 1]^T$.
- **Solution:** $\|\mathbf{a}\| = \sqrt{4 + 4 + 1} = \sqrt{9} = 3$. $\hat{\mathbf{a}} = \mathbf{[\frac{2}{3}, -\frac{2}{3}, \frac{1}{3}]^T}$.

#### Problem 26: Skew-Symmetric Cross Product Matrix
- **Question:** Write skew-symmetric matrix for $\mathbf{v} = [1, 2, 3]^T$.
- **Solution:** $[\mathbf{v}]_\times = \mathbf{\begin{bmatrix} 0 & -3 & 2 \\ 3 & 0 & -1 \\ -2 & 1 & 0 \end{bmatrix}}$.

#### Problem 27: Hessian Matrix Curvature
- **Question:** $f(x, y) = 2x^2 + 5y^2$. Compute Hessian $\mathbf{H}$ and check positive definiteness.
- **Solution:** $\mathbf{H} = \begin{bmatrix} 4 & 0 \\ 0 & 10 \end{bmatrix}$. Eigenvalues $\lambda_1 = 4 > 0, \lambda_2 = 10 > 0 \implies$ **Strictly Positive Definite (Local Minimum)**.

#### Problem 28: Rotation Matrix Transpose Property
- **Question:** Given $\mathbf{R} = \begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix}$, compute $\mathbf{R}\mathbf{R}^T$.
- **Solution:** $\begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \begin{bmatrix} \cos\theta & \sin\theta \\ -\sin\theta & \cos\theta \end{bmatrix} = \begin{bmatrix} \cos^2\theta+\sin^2\theta & \cos\theta\sin\theta-\sin\theta\cos\theta \\ \sin\theta\cos\theta-\cos\theta\sin\theta & \sin^2\theta+\cos^2\theta \end{bmatrix} = \mathbf{\begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix}}$.

#### Problem 29: Kinetic Energy of Mobile Robot
- **Question:** Robot of mass $m = 100\text{ kg}$, rotational inertia $I = 10\text{ kg}\cdot\text{m}^2$, moving at $v = 2\text{ m/s}, \omega = 1\text{ rad/s}$. Total kinetic energy $E$?
- **Solution:** $E = \frac{1}{2}mv^2 + \frac{1}{2}I\omega^2 = \frac{1}{2}(100)(4) + \frac{1}{2}(10)(1) = 200 + 5 = \mathbf{205\text{ Joules}}$.

#### Problem 30: Essential Matrix Constraint
- **Question:** Point $\mathbf{x}_1 = [0, 0, 1]^T$, translation $\mathbf{t} = [1, 0, 0]^T$, rotation $\mathbf{R} = \mathbf{I}$. Compute epipolar line $\mathbf{l}_2 = \mathbf{E}\mathbf{x}_1$.
- **Solution:** $\mathbf{E} = [\mathbf{t}]_\times \mathbf{R} = \begin{bmatrix} 0 & 0 & 0 \\ 0 & 0 & -1 \\ 0 & 1 & 0 \end{bmatrix}$. $\mathbf{l}_2 = \mathbf{E}\mathbf{x}_1 = \begin{bmatrix} 0 \\ -1 \\ 0 \end{bmatrix} \implies -y = 0 \implies \mathbf{y = 0}$ (Horizontal epipolar line).

---

# 61. Numerical Interview Problems

### 25 Tiered Interview Problems 🔴 [MUST KNOW]

#### Beginner Tier (Problems 1–7)
1. **Vector Subtraction:** $\mathbf{a} = [5, 2]^T, \mathbf{b} = [1, 4]^T$. $\mathbf{a} - \mathbf{b} = \mathbf{[4, -2]^T}$.
2. **Matrix Trace:** $\mathbf{A} = \begin{bmatrix} 5 & 2 & 1 \\ 0 & 3 & 4 \\ 1 & 1 & 7 \end{bmatrix}$. $\text{Tr}(\mathbf{A}) = 5 + 3 + 7 = \mathbf{15}$.
3. **Cartesian to Polar:** Point $(x, y) = (3, 3\sqrt{3})$. $r = \sqrt{9 + 27} = 6.0$, $\theta = \text{atan2}(3\sqrt{3}, 3) = \mathbf{60^\circ \ (\frac{\pi}{3}\text{ rad})}$.
4. **Probability Union:** Mutually exclusive sensor alarms $P(A) = 0.05, P(B) = 0.03$. $P(A \cup B) = 0.05 + 0.03 = \mathbf{0.08}$.
5. **Scalar Dot Product:** $\mathbf{u} = [2, -1, 3]^T, \mathbf{v} = [4, 2, -1]^T$. $\mathbf{u} \cdot \mathbf{v} = 8 - 2 - 3 = \mathbf{3}$.
6. **Matrix Transpose:** Transpose of $\begin{bmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \end{bmatrix} = \mathbf{\begin{bmatrix} 1 & 4 \\ 2 & 5 \\ 3 & 6 \end{bmatrix}}$.
7. **2D Rotation $180^\circ$:** $\mathbf{R}(180^\circ) = \mathbf{\begin{bmatrix} -1 & 0 \\ 0 & -1 \end{bmatrix}}$. Point $[3, 4]^T$ becomes $\mathbf{[-3, -4]^T}$.

#### Intermediate Tier (Problems 8–15)
8. **Transformation Chain:** $\mathbf{T}_1 = \begin{bmatrix} 1 & 0 & 2 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}, \mathbf{T}_2 = \begin{bmatrix} 0 & -1 & 0 \\ 1 & 0 & 3 \\ 0 & 0 & 1 \end{bmatrix}$.  
   $\mathbf{T}_1 \mathbf{T}_2 = \begin{bmatrix} 0 & -1 & 3 \\ 1 & 0 & 3 \\ 0 & 0 & 1 \end{bmatrix} \dots \mathbf{T}_2 \mathbf{T}_1 = \mathbf{\begin{bmatrix} 0 & -1 & 0 \\ 1 & 0 & 5 \\ 0 & 0 & 1 \end{bmatrix}}$.
9. **Covariance Matrix Calculation:** Samples: $(2, 4), (4, 6), (6, 8)$. Mean $\boldsymbol{\mu} = [4, 6]^T$. Deviations: $(-2, -2), (0, 0), (2, 2)$.  
   $\sigma_x^2 = \frac{4+0+4}{2} = 4, \sigma_y^2 = 4, \sigma_{xy} = \frac{4+0+4}{2} = 4 \implies \boldsymbol{\Sigma} = \mathbf{\begin{bmatrix} 4 & 4 \\ 4 & 4 \end{bmatrix}}$ (Perfect correlation $\rho = 1.0$).
10. **Differential Drive Turning Radius:** $L = 0.6\text{ m}, \omega_R = 10\text{ rad/s}, \omega_L = 6\text{ rad/s}, r = 0.1\text{ m}$.  
    $v = 0.05(16) = 0.8\text{ m/s}, \omega = \frac{0.1}{0.6}(4) = 0.667\text{ rad/s} \implies R_{\text{ICC}} = \frac{0.8}{0.667} = \mathbf{1.2\text{ meters}}$.
11. **Camera Principal Point Offset:** $f_x = 500, c_x = 320$. Point at $X_c = 0\text{ m}, Z_c = 5\text{ m}$. Pixel $u = 500(0) + 320 = \mathbf{320\text{ px}}$ (Projects exactly onto principal axis).
12. **Quaternion Normalization:** Unnormalized $\mathbf{q} = [1, 1, 1, 1]^T$. Norm = $\sqrt{1+1+1+1} = 2.0$. Normalized $\mathbf{q} = \mathbf{[0.5, 0.5, 0.5, 0.5]^T}$.
13. **Controllability Rank:** $\mathbf{A} = \begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix}, \mathbf{B} = \begin{bmatrix} 0 \\ 1 \end{bmatrix}$. $\mathbf{A}\mathbf{B} = \begin{bmatrix} 1 \\ 0 \end{bmatrix} \implies \mathcal{C} = \begin{bmatrix} 0 & 1 \\ 1 & 0 \end{bmatrix}$. $\det(\mathcal{C}) = -1 \ne 0 \implies$ **Controllable (Rank 2)**.
14. **Observability Rank:** $\mathbf{A} = \begin{bmatrix} 1 & 0 \\ 0 & 2 \end{bmatrix}, \mathbf{C} = \begin{bmatrix} 1 & 0 \end{bmatrix}$. $\mathbf{C}\mathbf{A} = \begin{bmatrix} 1 & 0 \end{bmatrix} \implies \mathcal{O} = \begin{bmatrix} 1 & 0 \\ 1 & 0 \end{bmatrix}$. $\det(\mathcal{O}) = 0 \implies$ **Unobservable (Rank 1)**.
15. **Discrete State Transition Matrix:** Continuous $\dot{x} = ax \implies$ Discrete $F = e^{a \Delta t} \approx 1 + a \Delta t$. For $a = -2, \Delta t = 0.1 \implies F = 1 - 0.2 = \mathbf{0.8}$.

#### Advanced Tier (Problems 16–22)
16. **2D EKF Jacobian:** Non-linear range sensor $h(x, y) = \sqrt{x^2 + y^2}$. $\mathbf{H} = \left[ \frac{x}{\sqrt{x^2+y^2}}, \frac{y}{\sqrt{x^2+y^2}} \right]$. At $(3, 4)$: $\mathbf{H} = \mathbf{[0.6, 0.8]}$.
17. **Quadratic Form Cost:** $\mathbf{x} = [1, -1]^T, \mathbf{Q} = \begin{bmatrix} 3 & 1 \\ 1 & 2 \end{bmatrix}$. $\mathbf{x}^T \mathbf{Q} \mathbf{x} = [1, -1] \begin{bmatrix} 2 \\ -1 \end{bmatrix} = 1(2) + (-1)(-1) = 2 + 1 = \mathbf{3}$.
18. **Stereo Error Sensitivity:** $f = 800\text{ px}, B = 0.25\text{ m} \implies fB = 200$. Target at $Z = 5\text{ m}$ with $\Delta d = 1\text{ px}$. $\Delta Z \approx \frac{5^2}{200}(1) = \frac{25}{200} = \mathbf{\pm 0.125\text{ m} \ (\pm 12.5\text{ cm})}$.
19. **Gauss-Newton Step:** Residual $r(x) = x^2 - 4$. At $x_0 = 3$: $r(3) = 5$. $J = \frac{dr}{dx} = 2x \implies J(3) = 6$.  
    $J^2 \Delta x = -J r \implies 36 \Delta x = -6(5) = -30 \implies \Delta x = -\frac{30}{36} = -0.833 \implies x_1 = 3 - 0.833 = \mathbf{2.167}$ (Converging rapidly to 2.0).
20. **Chi-Squared Gating:** $d_M^2 = 5.2$. For 2 DOF at $\alpha = 0.05$, critical value is $\chi_{2, 0.05}^2 = 5.99$. Since $5.2 < 5.99$, **ACCEPT measurement (Inlier)**.
21. **Cholesky Factorization:** $\mathbf{A} = \begin{bmatrix} 4 & 2 \\ 2 & 10 \end{bmatrix} = \begin{bmatrix} l_{11} & 0 \\ l_{21} & l_{22} \end{bmatrix} \begin{bmatrix} l_{11} & l_{21} \\ 0 & l_{22} \end{bmatrix}$.  
    $l_{11}^2 = 4 \implies l_{11} = 2$. $l_{21} l_{11} = 2 \implies l_{21} = 1$. $l_{21}^2 + l_{22}^2 = 10 \implies 1 + l_{22}^2 = 10 \implies l_{22} = 3$.  
    $\mathbf{L} = \mathbf{\begin{bmatrix} 2 & 0 \\ 1 & 3 \end{bmatrix}}$.
22. **Matrix Condition Number:** $\boldsymbol{\Sigma} = \begin{bmatrix} 100 & 0 \\ 0 & 0.01 \end{bmatrix}$. $\sigma_{\max} = 100, \sigma_{\min} = 0.01 \implies \kappa(\boldsymbol{\Sigma}) = \frac{100}{0.01} = \mathbf{10,000}$.

#### Expert Interview Challenges (Problems 23–25)
23. **Integrated Odometry Drift:** AMR drives at $v = 1\text{ m/s}$ with gyro yaw rate bias $b_g = 0.01\text{ rad/s}$. After $t = 10\text{ s}$, total angular error $\Delta \theta = 0.1\text{ rad} \approx 5.73^\circ$. Lateral position drift $y \approx \int_0^{10} v(b_g t) dt = 1(0.01)\frac{10^2}{2} = \mathbf{0.5\text{ meters}}$ (Drifts quadratically $O(t^2)$).
24. **Multi-Camera Baseline Extrinsics:** Camera 1 pose $\mathbf{T}_{b}^{c1} = \begin{bmatrix} \mathbf{I} & [0.2, 0.1, 0]^T \\ \mathbf{0} & 1 \end{bmatrix}$, Camera 2 pose $\mathbf{T}_{b}^{c2} = \begin{bmatrix} \mathbf{I} & [0.2, -0.1, 0]^T \\ \mathbf{0} & 1 \end{bmatrix}$. Relative baseline vector $\mathbf{t}_{12} = \mathbf{t}_{c2} - \mathbf{t}_{c1} = [0, -0.2, 0]^T \implies \text{Baseline } B = \mathbf{0.2\text{ m}}$ along lateral Y axis.
25. **Non-Linear Least Squares with Outlier Weighting:** Residual $r_1 = 0.1$ (weight $w_1 = 1.0$), Outlier residual $r_2 = 5.0$ (Huber weight $w_2 = 0.02$). Fused gradient contribution: $g_1 = 1.0(0.1) = 0.1$, $g_2 = 0.02(5.0) = 0.1$. The outlier's influence is attenuated by $98\%$.

---

# 62. C++ Mathematics Coding

### Production C++ with Eigen Library 🔴 [MUST KNOW]

```cpp
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

// 1. Homogeneous SE(3) Transformation Pipeline
class RobotKinematics {
public:
    static Eigen::Matrix4d createTransform(double x, double y, double z, double roll, double pitch, double yaw) {
        Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
        
        // ZYX Euler Angle to 3x3 Rotation Matrix
        Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
        Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitY());
        Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitZ());
        
        Eigen::Matrix3d R = (yawAngle * pitchAngle * rollAngle).toRotationMatrix();
        
        T.block<3, 3>(0, 0) = R;
        T.block<3, 1>(0, 3) = Eigen::Vector3d(x, y, z);
        return T;
    }
    
    // Fast Analytical SE(3) Inverse: T^-1 = [R^T, -R^T * t]
    static Eigen::Matrix4d invertTransform(const Eigen::Matrix4d& T) {
        Eigen::Matrix4d T_inv = Eigen::Matrix4d::Identity();
        Eigen::Matrix3d R_T = T.block<3, 3>(0, 0).transpose();
        Eigen::Vector3d t = T.block<3, 1>(0, 3);
        
        T_inv.block<3, 3>(0, 0) = R_T;
        T_inv.block<3, 1>(0, 3) = -R_T * t;
        return T_inv;
    }
};

// 2. Numerically Stable Linear Least Squares Solver (Ax = b)
Eigen::VectorXd solveLeastSquaresCholesky(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
    // Solve Normal Equation (A^T * A) x = A^T * b using Cholesky LDLT
    Eigen::MatrixXd AtA = A.transpose() * A;
    Eigen::VectorXd Atb = A.transpose() * b;
    return AtA.ldlt().solve(Atb);
}

// 3. Discrete 2D Kalman Filter Update Step
struct KalmanState2D {
    Eigen::Vector2d x; // State: [position, velocity]
    Eigen::Matrix2d P; // Covariance
};

KalmanState2D kalmanUpdate(const KalmanState2D& prior, double z_meas, double R_noise, double H_gain) {
    KalmanState2D post;
    Eigen::RowVector2d H(H_gain, 0.0);
    
    // Innovation
    double y = z_meas - H * prior.x;
    double S = H * prior.P * H.transpose() + R_noise;
    Eigen::Vector2d K = prior.P * H.transpose() / S;
    
    // Posterior Update
    post.x = prior.x + K * y;
    post.P = (Eigen::Matrix2d::Identity() - K * H) * prior.P;
    return post;
}
```

---

# 63. Python Mathematics Coding

### Vectorized NumPy & SciPy Robotics Mathematics 🔴 [MUST KNOW]

```python
import numpy as np
from scipy.spatial.transform import Rotation as R

# 1. 2D Odometry Arc Integration
def integrate_differential_drive(x, y, theta, v, omega, dt):
    """
    Exact Arc integration for differential drive mobile robot.
    """
    if abs(omega) < 1e-6: # Straight line motion
        x_next = x + v * np.cos(theta) * dt
        y_next = y + v * np.sin(theta) * dt
        theta_next = theta
    else: # Arc motion around ICC
        x_next = x + (v / omega) * (np.sin(theta + omega * dt) - np.sin(theta))
        y_next = y - (v / omega) * (np.cos(theta + omega * dt) - np.cos(theta))
        theta_next = theta + omega * dt
        
    # Normalize theta to [-pi, pi]
    theta_next = (theta_next + np.pi) % (2 * np.pi) - np.pi
    return x_next, y_next, theta_next

# 2. Pinhole Camera 3D-to-2D Projection
def project_points(points_3d, K, T_cam_world):
    """
    Project (N, 3) 3D points in world frame to 2D pixel coordinates.
    """
    N = points_3d.shape[0]
    points_hom = np.hstack((points_3d, np.ones((N, 1)))) # (N, 4)
    
    # Transform to Camera Frame
    points_cam = (T_cam_world @ points_hom.T).T[:, :3] # (N, 3)
    
    # Perspective Division
    Z = points_cam[:, 2:3]
    valid_mask = (Z > 0.1).flatten() # Remove points behind camera
    
    pixels = (K @ points_cam.T).T
    u = pixels[:, 0] / pixels[:, 2]
    v = pixels[:, 1] / pixels[:, 2]
    
    return np.column_stack((u, v)), valid_mask

# 3. Vectorized Mahalanobis Distance for Data Association
def mahalanobis_distance_batch(measurements, predicted_meas, S_cov):
    """
    Compute Mahalanobis distance for batch of sensor measurements.
    """
    diff = measurements - predicted_meas # (N, 2)
    S_inv = np.linalg.inv(S_cov)
    # Vectorized quadratic form: sum(diff * (S_inv @ diff.T).T, axis=1)
    d_M_sq = np.sum(diff @ S_inv * diff, axis=1)
    return np.sqrt(d_M_sq)
```

---

# 64. Debugging Mathematical Robotics Systems

### 20 Real-World Mathematical Failure Scenarios 🔴 [MUST KNOW]

1. **Covariance Matrix Loses Positive Definiteness:**  
   *Symptom:* Kalman filter crashes with `NaN` in state vector.  
   *Root Cause:* Subtraction in standard update $\mathbf{P} = (\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}$ accumulates asymmetry and negative eigenvalues.  
   *Fix:* Use **Joseph Form Covariance Update**: $\mathbf{P} = (\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}(\mathbf{I}-\mathbf{K}\mathbf{H})^T + \mathbf{K}\mathbf{R}\mathbf{K}^T$ and enforce symmetry: $\mathbf{P} = 0.5(\mathbf{P} + \mathbf{P}^T)$.
2. **Quaternion Drift Over Time:**  
   *Symptom:* Virtual robot flips or scales distortedly in RViz.  
   *Root Cause:* Discrete-time integration causes $\|\mathbf{q}\| \ne 1.0$.  
   *Fix:* Re-normalize quaternion at every step: $\mathbf{q} \leftarrow \frac{\mathbf{q}}{\|\mathbf{q}\|}$.
3. **Rotation Matrix Orthogonality Loss:**  
   *Symptom:* $\det(\mathbf{R}) \ne 1.0$, robot model stretches.  
   *Fix:* Project back to $SO(3)$ via SVD: $\mathbf{R} = \mathbf{U}\mathbf{V}^T$ (with $\det(\mathbf{U}\mathbf{V}^T)=+1$).
4. **Gimbal Lock at $90^\circ$ Pitch:**  
   *Symptom:* Euler angle yaw jumps by $180^\circ$ intermittently.  
   *Fix:* Transition entire internal kinematics pipeline to Quaternions or Rotation Matrices.
5. **Angle Discontinuity at $\pm \pi$:**  
   *Symptom:* Heading error jumps from $+179^\circ$ to $-179^\circ$, causing controller to spin $358^\circ$.  
   *Fix:* Angle wrap function: `err = atan2(sin(target - current), cos(target - current))`.
6. **Inverted Frame Transformation:**  
   *Symptom:* Moving robot forward causes map point to move forward instead of backward.  
   *Fix:* Verify whether transform is $\mathbf{T}_{\text{map}}^{\text{base}}$ or $\mathbf{T}_{\text{base}}^{\text{map}}$.
7. **Jacobian Dimension Mismatch:**  
   *Symptom:* Runtime crash during matrix multiplication $\mathbf{H}\mathbf{P}\mathbf{H}^T$.  
   *Fix:* Check that $\mathbf{H} \in \mathbb{R}^{m \times n}$, $\mathbf{P} \in \mathbb{R}^{n \times n} \implies \mathbf{H}\mathbf{P}\mathbf{H}^T \in \mathbb{R}^{m \times m}$.
8. **Ill-Conditioned Least Squares Solver:**  
   *Symptom:* Wild parameter oscillations in plane fitting.  
   *Fix:* Switch solver from `A.inverse()` to `A.colPivHouseholderQr().solve(b)`.
9. **Gauss-Newton Divergence:**  
   *Symptom:* Non-linear optimizer cost increases to infinity.  
   *Fix:* Add Levenberg-Marquardt damping: $(\mathbf{J}^T\mathbf{J} + \lambda \mathbf{I})\Delta \mathbf{x} = -\mathbf{J}^T\mathbf{r}$.
10. **IMU Integration Cubic Drift ($O(t^3)$):**  
    *Symptom:* Position estimate drifts into space after 10 seconds of no wheel motion.  
    *Fix:* Estimate accelerometer bias $\mathbf{b}_a$ and fuse with Zero Velocity Updates (ZUPT).
11. **Negative Determinant in Frame Construction:**  
    *Symptom:* Left-handed coordinate frame flips camera images.  
    *Fix:* Ensure third axis is computed via right-hand rule: $\hat{\mathbf{z}} = \hat{\mathbf{x}} \times \hat{\mathbf{y}}$.
12. **Wrong Trigonometric Units:**  
    *Symptom:* Robot rotates 57 times too fast.  
    *Fix:* Candidate passed degrees into `std::cos()` which expects radians.
13. **Stereo Depth Zero Disparity Crash:**  
    *Symptom:* Division by zero when calculating $Z = fB/d$ for distant points.  
    *Fix:* Clamp minimum disparity: `d = max(0.5, d)`.
14. **EKF Process Noise $\mathbf{Q}$ Underestimated:**  
    *Symptom:* Filter ignores new sensor measurements ("smug filter").  
    *Fix:* Increase diagonal elements of $\mathbf{Q}$ to model wheel slip.
15. **EKF Measurement Noise $\mathbf{R}$ Underestimated:**  
    *Symptom:* State estimate jitters aggressively with every noisy measurement.  
    *Fix:* Increase $\mathbf{R}$ to reflect true sensor noise variance.
16. **Coordinate Origin Inconsistency (Camera Optical vs Body Frame):**  
    *Symptom:* Camera projection appears flipped along vertical axis.  
    *Fix:* Optical frame uses $+Z$ Forward, $+X$ Right, $+Y$ Down. Body frame uses $+X$ Forward, $+Y$ Left, $+Z$ Up. Insert optical rotation transform $\mathbf{R}_{\text{body}}^{\text{optical}}$.
17. **Dynamic Matrix Allocation in Real-Time Control Loop:**  
    *Symptom:* 1 kHz control loop suffers periodic 5 ms jitter spikes.  
    *Fix:* Replace `Eigen::MatrixXd` with fixed-size `Eigen::Matrix<double, 6, 6>`.
18. **Un-synchronized Multi-Rate Sensor Integration:**  
    *Symptom:* EKF states jump backwards in time.  
    *Fix:* Buffer sensor messages and integrate in strict monotonic timestamp order.
19. **Euler Integration Instability at High Frequencies:**  
    *Symptom:* Dynamic simulation blows up when motor speed increases.  
    *Fix:* Switch integrator to Runge-Kutta 4 (RK4).
20. **Under-Constrained Factor Graph SLAM:**  
    *Symptom:* SLAM solver outputs singular matrix error on first step.  
    *Fix:* Add a **Prior Factor** with high confidence on the initial robot pose $\mathbf{x}_0$ to anchor the gauge freedom.

---

# 65. System Design Mathematics

### Mathematical Architecture of an Autonomous Tugger (ATI Sherpa) 🔴 [MUST KNOW]

```
+---------------------------------------------------------------------------------------------------+
|                        MATHEMATICAL STATE ESTIMATION & CONTROL PIPELINE                           |
+---------------------------------------------------------------------------------------------------+
|                                                                                                   |
|  STATE VECTOR x ∈ R^10: [ x, y, z, roll, pitch, yaw, v_x, v_y, ω_z, b_gyro ]^T                    |
|                                                                                                   |
|  1. 100 Hz IMU PREDICTION:                                                                        |
|     x_{k|k-1} = f_RK4( x_{k-1}, a_raw - b_a, ω_raw - b_g, Δt )                                    |
|     P_{k|k-1} = F P_{k-1} F^T + Q                                                                 |
|                                                                                                   |
|  2. 50 Hz WHEEL ENCODER UPDATE:                                                                   |
|     z_enc = [ v_x, ω_z ]^T,   y = z_enc - H_enc x,   K_enc = P H^T (H P H^T + R_enc)^-1           |
|                                                                                                   |
|  3. 10 Hz 3D LiDAR SCAN-TO-MAP ICP:                                                               |
|     T_lidar = argmin_T Σ || p_i - T q_i ||^2  (Levenberg-Marquardt on SE(3) Lie Manifold)         |
|     y_lidar = z_lidar - x,   K_lidar = P (P + R_lidar)^-1                                         |
|                                                                                                   |
|  4. 20 Hz PATH TRACKING (Model Predictive Control QP):                                            |
|     min_U  Σ (x_k - x_ref)^T Q (x_k - x_ref) + u_k^T R u_k                                        |
|     s.t.   v_min ≤ v ≤ v_max,   |δ| ≤ δ_max,   |a| ≤ a_max                                        |
+---------------------------------------------------------------------------------------------------+
```

---

# 66. 60 Interview Questions

### Categorized Core Interview Questions & Answers 🔴 [MUST KNOW]

#### Linear Algebra (Q1–Q6)
1. **Q:** What is the rank of a matrix?  
   **A:** The maximum number of linearly independent row or column vectors. Represents the dimension of the vector space spanned by the matrix.
2. **Q:** What does it mean if $\det(\mathbf{A}) = 0$?  
   **A:** The matrix is singular, has linearly dependent columns, compresses space to a lower dimension, and has NO inverse.
3. **Q:** Why are covariance matrices symmetric?  
   **A:** Because $\text{Cov}(X, Y) = \mathbb{E}[(X-\mu_x)(Y-\mu_y)] = \mathbb{E}[(Y-\mu_y)(X-\mu_x)] = \text{Cov}(Y, X)$.
4. **Q:** What is the difference between an inner and outer product?  
   **A:** Inner product $\mathbf{u}^T \mathbf{v}$ yields a scalar ($\mathbb{R}^1$); outer product $\mathbf{u}\mathbf{v}^T$ yields a rank-1 matrix ($\mathbb{R}^{n \times n}$).
5. **Q:** How do you find the inverse of an orthogonal matrix $\mathbf{Q}$?  
   **A:** Its inverse is simply its transpose: $\mathbf{Q}^{-1} = \mathbf{Q}^T$.
6. **Q:** What is an eigenvalue decomposition?  
   **A:** Factorizing $\mathbf{A} = \mathbf{V} \boldsymbol{\Lambda} \mathbf{V}^{-1}$, where $\mathbf{V}$ are eigenvectors and $\boldsymbol{\Lambda}$ is the diagonal matrix of eigenvalues.

#### Geometry & Transformations (Q7–Q14)
7. **Q:** What is the difference between $SO(3)$ and $SE(3)$?  
   **A:** $SO(3)$ is the group of 3D rotations (3 DOF, $3 \times 3$ matrices). $SE(3)$ is the group of rigid transformations combining 3D rotation and 3D translation (6 DOF, $4 \times 4$ matrices).
8. **Q:** Why do we use quaternions instead of Euler angles in state estimation?  
   **A:** Quaternions have no gimbal lock singularities, offer smooth spherical linear interpolation (SLERP), and are computationally efficient.
9. **Q:** What is the geometric interpretation of a Homography matrix?  
   **A:** A $3 \times 3$ projective mapping between two planar surfaces or between two camera views of a planar scene (8 DOF).
10. **Q:** How do you invert a $4 \times 4$ transformation matrix efficiently?  
    **A:** $\mathbf{T}^{-1} = \begin{bmatrix} \mathbf{R}^T & -\mathbf{R}^T\mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix}$. Never use generic Gaussian elimination.
11. **Q:** What is the Lie algebra of $SO(3)$?  
    **A:** The space of $3 \times 3$ skew-symmetric matrices $\mathfrak{so}(3)$, representing angular velocities / tangent vectors in $\mathbb{R}^3$.
12. **Q:** What is the Exponential Map?  
    **A:** Maps an element of the Lie algebra (tangent vector) to the Lie group (rotation matrix) via Rodrigues' formula.
13. **Q:** Why are homogeneous coordinates necessary for translation?  
    **A:** Translation is an affine operation ($\mathbf{x} + \mathbf{t}$). Adding a 4th dimension with scale $1$ makes translation a linear matrix multiplication.
14. **Q:** How many DOF does a 3D rigid body have?  
    **A:** 6 Degrees of Freedom: 3 translational $(x, y, z)$ and 3 rotational $(\text{roll, pitch, yaw})$.

#### Probability & Estimation (Q15–Q24)
15. **Q:** What is the difference between a Prior, Likelihood, and Posterior?  
    **A:** Prior is belief before data; Likelihood is probability of data given state; Posterior is updated belief after data.
16. **Q:** What are the core assumptions of the standard linear Kalman Filter?  
    **A:** Linear dynamics, linear measurement model, and zero-mean additive Gaussian white noise.
17. **Q:** How does an Extended Kalman Filter (EKF) handle non-linearities?  
    **A:** Linearizes non-linear functions using first-order Taylor series Jacobians around current state estimates.
18. **Q:** What is the Kalman Gain physically?  
    **A:** A weighting matrix that balances model uncertainty against sensor noise uncertainty to minimize posterior covariance.
19. **Q:** Why does EKF diverge if initial covariance is too small?  
    **A:** The filter becomes overconfident ("smug"), ignores new sensor measurements, and cannot correct linearization errors.
20. **Q:** What is the Mahalanobis distance?  
    **A:** Distance between points normalized by covariance: $d_M = \sqrt{(\mathbf{x}-\boldsymbol{\mu})^T \boldsymbol{\Sigma}^{-1} (\mathbf{x}-\boldsymbol{\mu})}$.
21. **Q:** What is particle deprivation in Particle Filters?  
    **A:** When particles cluster into a single mode and eliminate hypotheses in other areas, making recovery from localization failure impossible.
22. **Q:** What is the difference between EKF-SLAM and Graph-SLAM?  
    **A:** EKF-SLAM maintains only the current pose and marginalizes landmarks ($O(N^2)$); Graph-SLAM optimizes the entire historical trajectory using sparse non-linear least squares.
23. **Q:** What is the Joseph form of the covariance update?  
    **A:** $\mathbf{P} = (\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}(\mathbf{I}-\mathbf{K}\mathbf{H})^T + \mathbf{K}\mathbf{R}\mathbf{K}^T$. Guarantees positive semi-definiteness.
24. **Q:** Why is white noise a common assumption in robotics?  
    **A:** It means noise samples are uncorrelated in time ($\mathbb{E}[w_t w_\tau] = 0$ for $t \ne \tau$), making Markovian state transitions valid.

#### Optimization (Q25–Q32)
25. **Q:** What is the difference between Gauss-Newton and Newton's Method?  
    **A:** Newton's method computes full second-order Hessian $\mathbf{H} = \mathbf{J}^T\mathbf{J} + \sum r_i \nabla^2 r_i$; Gauss-Newton approximates $\mathbf{H} \approx \mathbf{J}^T\mathbf{J}$, avoiding costly 2nd derivatives.
26. **Q:** When does Gauss-Newton fail?  
    **A:** When $\mathbf{J}^T\mathbf{J}$ is singular (ill-conditioned) or residuals $r_i$ are large and non-linear.
27. **Q:** How does Levenberg-Marquardt solve Gauss-Newton instability?  
    **A:** Adds damping $\lambda \mathbf{I}$ to interpolate between Gauss-Newton and robust Gradient Descent.
28. **Q:** What is the Normal Equation in linear least squares?  
    **A:** $\mathbf{A}^T\mathbf{A}\mathbf{x} = \mathbf{A}^T\mathbf{b}$.
29. **Q:** What is a convex optimization problem?  
    **A:** Minimizing a convex objective function over a convex feasible set. All local minima are global minima.
30. **Q:** What are the Karush-Kuhn-Tucker (KKT) conditions?  
    **A:** First-order necessary conditions for non-linear constrained optimization (Stationarity, Primal feasibility, Dual feasibility, Complementary slackness).
31. **Q:** What is the condition number of a matrix?  
    **A:** $\kappa(\mathbf{A}) = \frac{\sigma_{\max}}{\sigma_{\min}}$. Measures sensitivity to numerical perturbations.
32. **Q:** Why is QR decomposition preferred over normal equations for least squares?  
    **A:** Forming $\mathbf{A}^T\mathbf{A}$ squares the condition number ($\kappa(\mathbf{A}^T\mathbf{A}) = \kappa(\mathbf{A})^2$), amplifying numerical precision loss.

#### Kinematics & Control (Q33–Q42)
33. **Q:** What is the non-holonomic constraint of a differential drive robot?  
    **A:** $\dot{y}\cos\theta - \dot{x}\sin\theta = 0$ (Cannot move instantaneously perpendicular to its wheels).
34. **Q:** What is the Instantaneous Center of Curvature (ICC)?  
    **A:** The point around which all wheels of a vehicle rotate on concentric circles during turning.
35. **Q:** How does a bicycle model differ from a differential drive model?  
    **A:** Bicycle model steers by rotating front wheel angle $\delta$; differential drive steers by speed difference between fixed wheels.
36. **Q:** What is a kinematic singularity?  
    **A:** Joint configuration where the manipulator Jacobian loses rank, losing motion along one or more Cartesian directions.
37. **Q:** What is the difference between Forward and Inverse Kinematics?  
    **A:** FK maps joint angles to end-effector Cartesian pose; IK maps desired Cartesian pose to required joint angles.
38. **Q:** How do you test if a linear state-space system is controllable?  
    **A:** Check if controllability matrix $\mathcal{C} = [\mathbf{B}, \mathbf{A}\mathbf{B}, \dots, \mathbf{A}^{n-1}\mathbf{B}]$ has full rank $n$.
39. **Q:** What does LQR optimize?  
    **A:** Linear Quadratic Regulator minimizes infinite-horizon quadratic cost $J = \int ( \mathbf{x}^T \mathbf{Q} \mathbf{x} + \mathbf{u}^T \mathbf{R} \mathbf{u} ) dt$.
40. **Q:** What is the difference between Pure Pursuit and Stanley control?  
    **A:** Pure Pursuit geometric curvature controller looks ahead to a point on the path; Stanley controller calculates cross-track error at the front axle and adds heading error.
41. **Q:** Why do we discretize continuous controllers?  
    **A:** Real microcontrollers and computers execute software at discrete clock intervals $\Delta t$.
42. **Q:** What is dead reckoning?  
    **A:** Estimating current position by integrating past velocity/encoder increments from a known starting point.

#### Computer Vision Geometry (Q43–Q50)
43. **Q:** What is the pinhole camera equation?  
    **A:** $u = f_x \frac{X}{Z} + c_x, \quad v = f_y \frac{Y}{Z} + c_y$.
44. **Q:** What does the intrinsic matrix $\mathbf{K}$ contain?  
    **A:** Focal lengths $(f_x, f_y)$ and principal point coordinates $(c_x, c_y)$.
45. **Q:** How is stereo disparity related to metric depth?  
    **A:** Inversely proportional: $Z = \frac{f \cdot B}{d}$.
46. **Q:** What is the Essential Matrix $\mathbf{E}$?  
    **A:** $\mathbf{E} = [\mathbf{t}]_\times \mathbf{R}$. Encodes epipolar geometry between two calibrated camera views (5 DOF).
47. **Q:** What is the Fundamental Matrix $\mathbf{F}$?  
    **A:** $\mathbf{F} = \mathbf{K}^{-T} \mathbf{E} \mathbf{K}^{-1}$. Relates corresponding pixels in uncalibrated images ($\mathbf{p}_2^T \mathbf{F} \mathbf{p}_1 = 0$).
48. **Q:** What is Perspective-n-Point (PnP)?  
    **A:** Estimating 6-DOF camera pose $[\mathbf{R} \mid \mathbf{t}]$ from $n \ge 3$ known 3D world points and their 2D pixel projections.
49. **Q:** What is Reprojection Error?  
    **A:** Geometric Euclidean distance between observed 2D image pixel and projected 3D landmark point.
50. **Q:** Why does monocular visual odometry suffer from scale ambiguity?  
    **A:** A small object moving close looks identical to a large object moving far away on a 2D projection plane.

#### Numerical Methods & Software (Q51–Q60)
51. **Q:** What is the difference between Euler integration and RK4?  
    **A:** Euler is 1st-order ($O(\Delta t)$ error); RK4 is 4th-order ($O(\Delta t^4)$ error) taking 4 slope samples per step.
52. **Q:** Why use fixed-size Eigen matrices (`Matrix3d`) instead of dynamic (`MatrixXd`)?  
    **A:** Fixed-size allocates on the stack without heap allocation, enabling compiler vectorization (AVX/SIMD) and zero-malloc real-time safety.
53. **Q:** What is the computational complexity of inverting an $n \times n$ matrix?  
    **A:** $\mathcal{O}(n^3)$.
54. **Q:** What is the Schur Complement in Bundle Adjustment?  
    **A:** A matrix trick that marginalizes 3D landmark points to solve camera poses first in a reduced camera-only system.
55. **Q:** What is the purpose of RANSAC?  
    **A:** Robust non-deterministic fitting that rejects large fractions of outlier measurements by random minimal subset consensus.
56. **Q:** What is the difference between single precision `float` and double precision `double`?  
    **A:** `float` is 32-bit (~7 decimal digits); `double` is 64-bit (~16 decimal digits). State estimation requires `double` to prevent covariance collapse.
57. **Q:** How do you test if a symmetric matrix is positive definite?  
    **A:** Check if Cholesky decomposition $\mathbf{A} = \mathbf{L}\mathbf{L}^T$ succeeds or verify all eigenvalues are $> 0$.
58. **Q:** What is aliasing in discrete-time signal processing?  
    **A:** High-frequency signals masquerading as low-frequency signals when sampling rate $f_s < 2 f_{\max}$ (violating Nyquist theorem).
59. **Q:** Why does IMU double integration cause quadratic position drift?  
    **A:** Constant bias $b_a$ integrated once gives linear velocity error $b_a t$; integrated twice gives quadratic position error $\frac{1}{2}b_a t^2$.
60. **Q:** What is the difference between loose and tight sensor fusion?  
    **A:** Loosely coupled fuses separate pose estimates; tightly coupled fuses raw sensor measurements (IMU deltas, LiDAR points, visual features) directly inside a single optimization filter.

---

# 67. High-Pressure Interview Chains

### 15 Deep-Dive Interviewer Chains 🔴 [MUST KNOW]

#### Chain 1: Covariance & Uncertainty
- **Interviewer:** Why do we use covariance matrices in robotics?  
  *Candidate:* To quantify both the marginal uncertainty of individual state variables and the cross-correlation between pairs of variables.
- **Interviewer:** What does a non-zero off-diagonal term $\sigma_{xy}$ mean physically?  
  *Candidate:* It means errors in $x$ and $y$ are correlated. For example, if a robot drives along a diagonal heading, position error along $x$ directly correlates with position error along $y$.
- **Interviewer:** How does that look geometrically?  
  *Candidate:* The 2D uncertainty ellipse rotates away from the Cartesian axes, tilting along the major eigenvector of the covariance matrix.
- **Interviewer:** What happens if the covariance matrix loses positive definiteness during execution?  
  *Candidate:* The Gaussian PDF exponents become positive, variance becomes negative, Kalman gains produce NaNs, and state estimation blows up.
- **Interviewer:** How do you fix that in production C++ code?  
  *Candidate:* Use the Joseph form covariance update $(\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}(\mathbf{I}-\mathbf{K}\mathbf{H})^T + \mathbf{K}\mathbf{R}\mathbf{K}^T$ and enforce numerical symmetry at every cycle.

#### Chain 2: Matrix Inversion & Solvers
- **Interviewer:** How do you solve $\mathbf{A}\mathbf{x} = \mathbf{b}$ in C++?  
  *Candidate:* In Eigen, I use matrix decomposition solvers like `A.ldlt().solve(b)` for SPD systems or `A.colPivHouseholderQr().solve(b)` for general least-squares.
- **Interviewer:** Why not `x = A.inverse() * b`?  
  *Candidate:* Direct inversion is computationally slower ($\mathcal{O}(n^3)$), destroys matrix sparsity, and amplifies numerical roundoff errors when condition number $\kappa(\mathbf{A})$ is large.
- **Interviewer:** What is the condition number mathematically?  
  *Candidate:* $\kappa(\mathbf{A}) = \frac{\sigma_{\max}(\mathbf{A})}{\sigma_{\min}(\mathbf{A})}$. It measures how much output error is magnified relative to input error.
- **Interviewer:** If $\kappa(\mathbf{A}) = 10^8$ in single precision `float`, what happens?  
  *Candidate:* Single-precision `float` has ~7 decimal digits of precision. A condition number of $10^8$ completely wipes out all significant digits, producing pure numerical garbage.

---

# 68. "Explain It in 30 Seconds"

### Concise Spoken Answers for Live Interviews 🔴 [MUST KNOW]

- **Rotation Matrix:** "A $3 \times 3$ orthogonal matrix with determinant $+1$ representing spatial orientation. Its columns are mutually orthogonal unit vectors defining the transformed coordinate axes."
- **Quaternion:** "A 4-dimensional unit vector representing 3D orientation without gimbal lock. It parameterizes rotation as an angle $\theta$ around a 3D unit axis $\hat{\mathbf{u}}$."
- **Jacobian:** "A matrix of first-order partial derivatives mapping differential changes or velocities in input space to output space. In robotics, it maps joint rates to Cartesian end-effector velocities."
- **Kalman Filter:** "An optimal recursive Bayes filter for linear Gaussian systems that updates state estimates by computing a weighted average between motion prediction and noisy sensor measurements."
- **Gauss-Newton:** "An iterative optimization algorithm for non-linear least squares that approximates the Hessian as $\mathbf{J}^T\mathbf{J}$, solving successive linear normal equations to find local minima."
- **Stereo Depth:** "Triangulating metric distance from two cameras by measuring horizontal pixel shift (disparity) between corresponding points: $Z = \frac{f \cdot B}{d}$."
- **SE(3):** "The Special Euclidean group of 6-DOF rigid body transformations combining a $3 \times 3$ rotation matrix and a $3 \times 1$ translation vector in a $4 \times 4$ homogeneous matrix."

---

# 69. Common Interview Traps

### Mistakes That Make Candidates Look Unprepared ⚠️ [INTERVIEW TRAP]

1. **Multiplying Transformations in Reverse Order:** Confusing local frame transformation (post-multiplication $\mathbf{T}_1 \mathbf{T}_2$) with global reference frame transformation (pre-multiplication $\mathbf{T}_2 \mathbf{T}_1$).
2. **Confusing Variance with Standard Deviation:** Writing $\sigma$ inside equations where variance $\sigma^2$ is required.
3. **Using `atan` instead of `atan2`:** Losing quadrant signs and failing for negative coordinates.
4. **Assuming Matrices Commute:** Claiming $\mathbf{R}_1 \mathbf{R}_2 = \mathbf{R}_2 \mathbf{R}_1$.
5. **Inverting Translation Directly:** Claiming $\mathbf{T}^{-1}$ has translation $-\mathbf{t}$ instead of $-\mathbf{R}^T \mathbf{t}$.
6. **Forgetting Radians in Trigonometry:** Passing angles in degrees to `sin()` and `cos()`.
7. **Confusing Process Noise $\mathbf{Q}$ with Measurement Noise $\mathbf{R}$:** $\mathbf{Q}$ models actuator/model uncertainty; $\mathbf{R}$ models sensor hardware noise.
8. **Saying "Just Invert the Matrix":** Demonstrates lack of numerical computing maturity.

---

# 70. Unit and Dimensional Analysis

### Dimensional Consistency Verification 🔴 [MUST KNOW]
Always verify units across every equation on the whiteboard:

$$\text{Position } \mathbf{p}: [\text{m}], \quad \text{Velocity } \mathbf{v}: [\text{m/s}], \quad \text{Angular Velocity } \boldsymbol{\omega}: [\text{rad/s}], \quad \text{Acceleration } \mathbf{a}: [\text{m/s}^2]$$
$$\text{Force } \mathbf{F}: [\text{N} = \text{kg}\cdot\text{m/s}^2], \quad \text{Torque } \boldsymbol{\tau}: [\text{N}\cdot\text{m} = \text{kg}\cdot\text{m}^2/\text{s}^2]$$
$$\text{Covariance } \boldsymbol{\Sigma}_{xx}: [\text{m}^2], \quad \boldsymbol{\Sigma}_{x\theta}: [\text{m}\cdot\text{rad}], \quad \text{Kalman Gain } \mathbf{K}: [\text{State Units} / \text{Measurement Units}]$$

---

# 71. Mental Math for Robotics Interviews

### 20 Quick Estimation Shortcuts 🔴 [MUST KNOW]
- $\pi \approx 3.14159, \quad \pi/2 \approx 1.57, \quad \pi/4 \approx 0.785, \quad \pi/6 \approx 0.523$.
- $1\text{ radian} \approx 57.3^\circ, \quad 0.1\text{ rad} \approx 5.7^\circ, \quad 0.01\text{ rad} \approx 0.57^\circ$.
- Small Angle Approximations for $|\theta| < 0.1\text{ rad} \ (5.7^\circ)$:
  $$\sin(\theta) \approx \theta, \quad \cos(\theta) \approx 1 - \frac{\theta^2}{2} \approx 1.0, \quad \tan(\theta) \approx \theta$$
- $\sqrt{2} \approx 1.414, \quad \sqrt{3} \approx 1.732, \quad \sqrt{5} \approx 2.236$.
- Gaussian Confidence: $1\sigma \approx 68\%, \quad 2\sigma \approx 95.4\%, \quad 3\sigma \approx 99.7\%$.

---

# 72. Integrated Autonomy Problems

### 10 Multi-Disciplinary Challenge Problems 🔴 [MUST KNOW]

#### Challenge 1: Dynamic Obstacle Interception Geometry
- **Problem:** An autonomous tugger is at origin $(0, 0)$ moving at $v_r = 2.0\text{ m/s}$ along $+X$. A forklift is detected at $(10, 10)\text{ m}$ moving at $v_f = 2.0\text{ m/s}$ along $-Y$. Will they collide?  
  *Calculation:*
  Robot position: $\mathbf{p}_r(t) = [2t, 0]^T$. Forklift position: $\mathbf{p}_f(t) = [10, 10 - 2t]^T$.  
  Set $\mathbf{p}_r(t) = \mathbf{p}_f(t) \implies 2t = 10 \implies t = 5\text{ s}$.  
  At $t = 5\text{ s}$, forklift Y position is $10 - 2(5) = 0\text{ m}$.  
  **Result: Collision occurs at $(10, 0)\text{ m}$ at exactly $t = 5.0\text{ seconds}$. Tugger must decelerate immediately.**

---

# 73. Final Mathematics Cheat Sheet

```
+---------------------------------------------------------------------------------------------------+
| 1. ROTATION:       R(θ) = [cos θ, -sin θ; sin θ, cos θ],    R^T R = I,   det(R) = +1              |
| 2. SE(3) TRANSFORM:T = [R, t; 0, 1],   T^-1 = [R^T, -R^T t; 0, 1]                                 |
| 3. QUATERNION:     q = [cos(θ/2), u sin(θ/2)]^T,   p' = q ⊗ [0, p] ⊗ q*                           |
| 4. PINHOLE:        u = fx(X/Z) + cx,   v = fy(Y/Z) + cy                                           |
| 5. STEREO DEPTH:   Z = (f * B) / d,    ΔZ ≈ (Z^2 / (f*B)) Δd                                      |
| 6. NORMAL EQ:      A^T A x = A^T b  ==>  x = (A^T A)^-1 A^T b                                     |
| 7. GAUSS-NEWTON:   (J^T J) Δx = -J^T r                                                            |
| 8. LEVENBERG-MARQ: (J^T J + λ I) Δx = -J^T r                                                      |
| 9. DIFF DRIVE:     v = (r/2)(ω_R + ω_L),   ω = (r/L)(ω_R - ω_L)                                   |
| 10. BICYCLE MODEL: κ = tan(δ) / L                                                                 |
| 11. KALMAN GAIN:   K = P H^T (H P H^T + R)^-1                                                     |
| 12. JOSEPH UPDATE: P = (I - KH) P (I - KH)^T + K R K^T                                            |
+---------------------------------------------------------------------------------------------------+
```

---

# 74. Formula Memorization List

### Core Equations to Write from Memory 🔴 [MUST MEMORIZE]
1. $\mathbf{T}^{-1} = \begin{bmatrix} \mathbf{R}^T & -\mathbf{R}^T\mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix}$
2. $\mathbf{A}^T\mathbf{A}\mathbf{x} = \mathbf{A}^T\mathbf{b}$
3. $\mathbf{K} = \mathbf{P}\mathbf{H}^T (\mathbf{H}\mathbf{P}\mathbf{H}^T + \mathbf{R})^{-1}$
4. $\mathbf{P}_{\text{new}} = (\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}$
5. $Z = \frac{f \cdot B}{d}$
6. $v = \frac{r}{2}(\omega_R + \omega_L), \quad \omega = \frac{r}{L}(\omega_R - \omega_L)$
7. $u = f_x \frac{X}{Z} + c_x, \quad v = f_y \frac{Y}{Z} + c_y$
8. $\kappa = \frac{\tan\delta}{L}$

---

# 75. 30-Minute Mathematics Revision Plan

```
+---------------+-----------------------------------------------------------------------------------+
| Time          | Focus Area & Critical Formulas                                                    |
+---------------+-----------------------------------------------------------------------------------+
| 00 - 05 min   | Linear Algebra: Dot, Cross, Skew-Symmetric [v]_x, Normal Eq A^T A x = A^T b       |
| 05 - 10 min   | Geometry: SE(3) Transform, Invert T = [R^T, -R^T t], Quaternions q = [cos, u sin]|
| 10 - 15 min   | Calculus & Jacobians: J = ∂f/∂x, Hessian H = ∇^2 f, Taylor Linearization          |
| 15 - 20 min   | Estimation: KF 5 Equations, Kalman Gain K, Joseph Covariance Update               |
| 20 - 25 min   | Optimization: Gauss-Newton (J^T J)Δx = -J^T r, Levenberg-Marquardt (+ λ I)        |
| 25 - 30 min   | Kinematics & Vision: Diff drive (v, ω), Pinhole Projection, Stereo Z = fB/d       |
+---------------+-----------------------------------------------------------------------------------+
```

---

# 76. Final Readiness Test

### Questions (Attempt before expanding solutions)

#### Conceptual & Mathematical (10 Questions)
1. Find the inverse of $\mathbf{T} = \begin{bmatrix} 1 & 0 & 0 & 3 \\ 0 & 0 & -1 & 4 \\ 0 & 1 & 0 & 2 \\ 0 & 0 & 0 & 1 \end{bmatrix}$.
2. A differential drive AMR has $r = 0.1\text{ m}, L = 0.5\text{ m}$. Wheel velocities are $\omega_R = 15\text{ rad/s}, \omega_L = 5\text{ rad/s}$. Compute $v$ and $\omega$.
3. Compute the Jacobian $\mathbf{J}$ for polar-to-Cartesian function $\mathbf{f}(r, \theta) = \begin{bmatrix} r\cos\theta \\ r\sin\theta \end{bmatrix}$.
4. A camera has $f_x = 1000, c_x = 640$. 3D landmark is at $X_c = 3.0\text{ m}, Z_c = 6.0\text{ m}$. Compute pixel $u$.
5. Stereo camera has $f = 800\text{ px}, B = 0.25\text{ m}$. Measured disparity is $d = 40\text{ px}$. Compute depth $Z$.
6. In 1D Kalman filtering, prior is $\hat{x} = 10, P = 8$. Sensor measurement is $z = 14, R = 2$. Compute Kalman gain $K$ and posterior $\hat{x}_{\text{post}}$.
7. Compute the cross product $\mathbf{a} \times \mathbf{b}$ for $\mathbf{a} = [1, 0, 0]^T, \mathbf{b} = [0, 2, 0]^T$.
8. Find eigenvalues of $\mathbf{A} = \begin{bmatrix} 6 & 0 \\ 0 & 2 \end{bmatrix}$.
9. What is the minimum number of 2D-2D point correspondences required to compute a Homography matrix?
10. Why is $\mathbf{P} = (\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}(\mathbf{I}-\mathbf{K}\mathbf{H})^T + \mathbf{K}\mathbf{R}\mathbf{K}^T$ preferred over $(\mathbf{I}-\mathbf{K}\mathbf{H})\mathbf{P}$?

---

<details>
<summary><b>🔍 Click to Expand Complete Test Solutions & Answer Key</b></summary>

### Answer Key & Solutions
1. $\mathbf{R} = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 0 & -1 \\ 0 & 1 & 0 \end{bmatrix} \implies \mathbf{R}^T = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 0 & 1 \\ 0 & -1 & 0 \end{bmatrix}$.  
   $-\mathbf{R}^T \mathbf{t} = -\begin{bmatrix} 1 & 0 & 0 \\ 0 & 0 & 1 \\ 0 & -1 & 0 \end{bmatrix} \begin{bmatrix} 3 \\ 4 \\ 2 \end{bmatrix} = -\begin{bmatrix} 3 \\ 2 \\ -4 \end{bmatrix} = \begin{bmatrix} -3 \\ -2 \\ 4 \end{bmatrix}$.  
   $$\mathbf{T}^{-1} = \mathbf{\begin{bmatrix} 1 & 0 & 0 & -3 \\ 0 & 0 & 1 & -2 \\ 0 & -1 & 0 & 4 \\ 0 & 0 & 0 & 1 \end{bmatrix}}$$
2. $v = \frac{0.1}{2}(15 + 5) = \mathbf{1.0\text{ m/s}}$. $\omega = \frac{0.1}{0.5}(15 - 5) = \frac{0.1}{0.5}(10) = \mathbf{2.0\text{ rad/s}}$.
3. $\mathbf{J} = \mathbf{\begin{bmatrix} \cos\theta & -r\sin\theta \\ \sin\theta & r\cos\theta \end{bmatrix}}$. ($\det(\mathbf{J}) = r$).
4. $u = 1000 \left(\frac{3.0}{6.0}\right) + 640 = 500 + 640 = \mathbf{1140\text{ pixels}}$.
5. $Z = \frac{800 \times 0.25}{40} = \frac{200}{40} = \mathbf{5.0\text{ meters}}$.
6. $K = \frac{8}{8 + 2} = \mathbf{0.80}$. $\hat{x}_{\text{post}} = 10 + 0.80(14 - 10) = 10 + 3.2 = \mathbf{13.2}$.
7. $\mathbf{a} \times \mathbf{b} = \mathbf{[0, 0, 2]^T}$.
8. $\mathbf{\lambda_1 = 6, \lambda_2 = 2}$.
9. **4 point pairs** (8 equations for 8 DOF).
10. **Guarantees numerical symmetry and positive semi-definiteness** even in the presence of finite precision floating-point roundoff errors.

</details>

---

### 📊 Scoring Rubric
- **90–100%**: *Exceptional Mastery* (Ready for senior autonomy whiteboard grilling).
- **75–89%**: *Interview Ready* (Solid foundation in transformations, kinematics, and estimation).
- **60–74%**: *Needs Targeted Review* (Review transformation inverses and Kalman gain math).
- **< 60%**: *Revisit Fundamentals* (Practice matrix multiplications and 2D rotations).
