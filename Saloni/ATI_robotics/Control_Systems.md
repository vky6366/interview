# Control Systems for Robotics & Autonomous Systems: Master Technical Interview Guide
**Role Target:** Robotics Intern – Autonomy (ATI Robotics)  
**Focus Areas:** Classical Control (PID), State-Space, LQR, MPC, Motor Control, Path Tracking, Real-Time Discretization  
**Level:** Comprehensive Engineering Foundations to Mathematical Interview Mastery  

---

## 📌 Categorization Legend
- 🔴 **[MUST KNOW]**: Mandatory for passing the technical interview. High likelihood of mathematical derivations, live coding, or direct conceptual grilling.
- 🟡 **[GOOD TO KNOW]**: Demonstrates strong systems and control engineering depth; distinguishes top candidates.
- 🔵 **[ADVANCED / OPTIONAL]**: Advanced optimization mechanics, non-linear control, and specialized theoretical proofs.
- ⚠️ **[INTERVIEW TRAP]**: Common misconceptions, edge cases, and pitfalls tested in technical interviews.
- 🤖 **[ROBOTICS CONNECTION]**: Direct application to mobile robots, autonomous tuggers (e.g. ATI Sherpa), drivetrains, and manipulators.

---

# Table of Contents
1. [Control System Fundamentals](#1-control-system-fundamentals)
2. [Why Control is Critical in Autonomous Robotics](#2-why-control-is-important-in-robotics)
3. [Mathematical Foundations for Control](#3-mathematical-foundations)
4. [Differential Equations in Robotics](#4-differential-equations-in-robotics)
5. [Transfer Functions & The s-Domain](#5-transfer-functions)
6. [Block Diagrams & Feedback Derivations](#6-block-diagrams)
7. [System Stability & Pole Placement](#7-stability--extremely-important)
8. [Time-Domain Response & Dynamic Characteristics](#8-time-domain-response)
9. [PID Control (First Principles & Discrete Implementation)](#9-pid-control--highest-priority)
10. [PID Hand-Calculation Problems](#10-pid-numerical-problems)
11. [Systematic Effects of PID Gains](#11-effect-of-pid-gains)
12. [Integral Windup & Anti-Windup Strategies](#12-integral-windup)
13. [Derivative Kick, Sensor Noise & Practical Filtering](#13-derivative-kick-and-sensor-noise)
14. [PID Tuning Methodologies in Practice](#14-pid-tuning)
15. [Cascade Control Architecture in Robotics](#15-cascade-control)
16. [Feedforward + Feedback Control](#16-feedforward--feedback)
17. [State-Space Representation](#17-state-space-representation)
18. [Controllability and Observability](#18-controllability-and-observability)
19. [Discrete-Time Control & Sampling Dynamics](#19-discrete-time-control)
20. [Digital Control Issues & Real-Time Constraints](#20-digital-control-issues)
21. [Electric Motor Control (BLDC / DC / FOC)](#21-motor-control)
22. [Robot Kinematics vs. Dynamics vs. Control](#22-robot-kinematics--control-connection)
23. [Mobile Robot Kinematic Control (Differential Drive)](#23-mobile-robot-control)
24. [Path Tracking Controllers (Pure Pursuit & Stanley)](#24-path-tracking-controllers)
25. [Linear Quadratic Regulator (LQR)](#25-lqr--high-priority)
26. [LQR Numerical & Conceptual Problems](#26-lqr-numerical--conceptual-problems)
27. [Model Predictive Control (MPC)](#27-mpc--high-priority)
28. [Optimal Control Formulations](#28-optimal-control)
29. [Learning-Based & Adaptive Control](#29-learning-based-control)
30. [System Robustness & Disturbance Rejection](#30-robustness)
31. [Full Autonomy Control Architecture Design Problem](#31-control-system-design-problem)
32. [Practical Control System Debugging Scenarios](#32-debugging-control-systems)
33. [40+ Core Control Systems Interview Questions](#33-control-interview-questions)
34. [20+ Hand-Solvable Mathematical Interview Problems](#34-mathematical-interview-problems)
35. [Python & C++ Control Implementation Exercises](#35-coding-problems)
36. [Control Systems Master Cheat Sheet](#36-control-system-cheat-sheet)
37. [30-Minute Pre-Interview Revision Sheet](#37-30-minute-pre-interview-revision)
38. [Mock Interview Readiness Test (with Complete Solutions)](#38-interview-readiness-test)

---

# 1. Control System Fundamentals

### What is a Control System? 🔴 [MUST KNOW]
A control system is an interconnection of physical components configured to command, direct, or regulate the behavior of a device or physical process (the **Plant**) to achieve a desired output value (the **Setpoint** or **Reference**).

---

### Core Anatomy of a Feedback Control System 🔴 [MUST KNOW]

```
                       Disturbance d(t) (Wind, Friction, Payload change)
                                        │
                                        ▼
Reference r(t)      Error e(t)    Control u(t)    Actuator   Actual Output y(t)
 (Desired) ────(+)───> [Controller] ───> [Actuator] ───(+)───> [ Plant ] ───┬───>
                ▲ -                                                        │
                │                                                          │
                └────────────────── [ Sensor ] <───────────────────────────┘
                               Feedback Measurement ym(t)
```

1. **Reference / Setpoint ($r(t)$):** The desired target state (e.g., target vehicle speed of $1.5\text{ m/s}$, or desired yaw angle of $0.0\text{ rad}$).
2. **Error ($e(t) = r(t) - y_m(t)$):** The instantaneous discrepancy between the desired reference and the measured output.
3. **Controller:** The computational algorithm that processes the error signal to calculate an appropriate control effort (e.g., PID, LQR, MPC).
4. **Actuator:** The physical hardware transducer that converts the controller's low-power electrical command into physical action (e.g., H-bridge motor driver, hydraulic valve, steering servo).
5. **Plant:** The physical system or physical body being controlled (e.g., robot chassis, DC motor rotor, drone frame).
6. **Disturbance ($d(t)$):** Unmodeled external forces acting on the plant (e.g., slope inclination, carpet friction, payload added to tugger).
7. **Sensor:** The measurement transducer that reads the physical output state (e.g., optical wheel encoder, IMU gyroscope, Hall effect sensor).
8. **Feedback ($y_m(t)$):** The measured output signal transmitted back to the summing junction to close the loop.

---

### Open-Loop vs. Closed-Loop Control 🔴 [MUST KNOW]

```
+-----------------------------------+------------------------------------+
| Dimension                         | Open-Loop Control                  | Closed-Loop (Feedback) Control    |
+-----------------------------------+------------------------------------+
| Feedback                          | None (Blind execution)             | Continuous sensor feedback         |
| Disturbance Rejection             | Zero (Cannot compensate for load)  | High (Actively drives error to 0)  |
| Model Sensitivity                 | Extremely sensitive to model error | Robust to moderate model variations|
| Stability Hazard                  | Rarely goes unstable on its own    | Can cause oscillation / instability|
| Cost & Complexity                 | Simple, cheap, no sensors needed   | Requires sensors, compute, tuning  |
| Robotics Example                  | Stepper motor open-stepping        | Closed-loop BLDC wheel velocity PID|
+-----------------------------------+------------------------------------+
```

---

### Real-World Robotics Examples 🔴 [MUST KNOW]
- **Motor Speed Control:** Setpoint = $200\text{ RPM}$; Sensor = Optical Encoder; Actuator = PWM H-Bridge; Disturbance = Tugger towing a heavy trailer.
- **Robot Heading Control:** Setpoint = $90^\circ\text{ Yaw}$; Sensor = IMU Gyroscope; Actuator = Differential wheel velocity $(\Delta v)$; Disturbance = Uneven floor wheel slip.
- **Drone Altitude Control:** Setpoint = $5.0\text{ m}$; Sensor = Barometer / LiDAR Altimeter; Actuator = Quadcopter rotor thrust; Disturbance = Wind gust downwash.

---

# 2. Why Control is Important in Robotics

### Planning vs. Control: The Division of Responsibility 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
|  AUTONOMY STACK                                                                    |
+------------------------------------------------------------------------------------+
|  Global Path Planner (A*, Dijkstra)       ──> "What geometric route to take?"      |
|  Local Trajectory Planner (TEB, DWA)      ──> "What feasible speeds (v, w) now?"   |
|  Control System (PID, Pure Pursuit, MPC)  ──> "How to physically force the motors  |
|                                                to track those speeds accurately?"  |
+------------------------------------------------------------------------------------+
```

Robots operate in non-ideal, stochastic physical environments where:
1. **Actuators Suffer Lag & Backlash:** Commanded voltage does not instantly produce commanded speed due to rotor inertia and gearbox friction.
2. **Contact Dynamics Vary:** Wheel friction coefficients change unpredictably across concrete, epoxy, and wet metal.
3. **Payload Shifts:** An autonomous tugger may pull an empty 50 kg cart or a loaded 1000 kg cart, altering system inertia by an order of magnitude.
4. **Safety & Stability:** Without feedback control, small deviations accumulate monotonically, causing the robot to drift off course and collide.

---

# 3. Mathematical Foundations

### 1. Derivatives and Integrals in Physical Systems 🔴 [MUST KNOW]
- **Position $\to$ Velocity $\to$ Acceleration:**
  $$v(t) = \dot{x}(t) = \frac{dx(t)}{dt}, \quad a(t) = \ddot{x}(t) = \frac{dv(t)}{dt} = \frac{d^2 x(t)}{dt^2}$$
- **Integration as Physical Accumulation:**
  $$x(t) = x(0) + \int_0^t v(\tau)\,d\tau$$
  In control, integration accumulates steady-state error over time to generate sufficient control effort to eliminate residual offsets.

---

### 2. Linear Ordinary Differential Equations (ODEs) 🔴 [MUST KNOW]
Physical robot dynamics are modeled via differential equations relating inputs (forces, torques, voltages) to output states (positions, velocities, currents).

---

# 4. Differential Equations in Robotics

### First-Order Dynamic System (e.g., DC Motor Velocity) 🔴 [MUST KNOW]
Newton's rotational law for a motor shaft with inertia $J$, viscous damping $b$, and applied motor torque $\tau(t) = K_t i(t)$:

$$J \frac{d\omega(t)}{dt} + b \omega(t) = \tau(t)$$

Dividing by $b$ yields the standard first-order time-constant form:

$$\tau_m \dot{\omega}(t) + \omega(t) = K \cdot u(t)$$

where $\tau_m = \frac{J}{b}$ is the **mechanical time constant** (time required to reach $63.2\%$ of steady-state speed) and $K = \frac{1}{b}$ is the steady-state gain.

---

### Second-Order Dynamic System (e.g., Mass-Spring-Damper Chassis) 🔴 [MUST KNOW]
Newton's translational law for a mass $m$ attached to a suspension damper $c$ and spring $k$:

$$m \ddot{x}(t) + c \dot{x}(t) + k x(t) = F(t)$$

Dividing by $m$:

$$\ddot{x}(t) + 2\zeta\omega_n \dot{x}(t) + \omega_n^2 x(t) = \frac{1}{m} F(t)$$

where:
- $\omega_n = \sqrt{\frac{k}{m}}$ is the **Natural Frequency** (speed of system oscillation).
- $\zeta = \frac{c}{2\sqrt{m k}}$ is the **Damping Ratio** (governs overshoot and oscillation).

---

# 5. Transfer Functions

### The Laplace Transform Intuition 🔴 [MUST KNOW]
The Laplace Transform converts linear differential equations from the complex time domain $t$ into algebraic equations in the complex frequency domain $s = \sigma + j\omega$.
- **Derivative Property:** $\mathcal{L}\left\{\frac{dx(t)}{dt}\right\} = s X(s) - x(0)$ (Assuming zero initial conditions: $\frac{d}{dt} \to s$).
- **Integral Property:** $\mathcal{L}\left\{\int x(t)\,dt\right\} = \frac{X(s)}{s}$.

---

### Definition of a Transfer Function 🔴 [MUST KNOW]
The Transfer Function $G(s)$ of a linear time-invariant (LTI) system is the ratio of the Laplace transform of the output $Y(s)$ to the Laplace transform of the input $U(s)$, assuming **zero initial conditions**:

$$G(s) = \frac{Y(s)}{U(s)} = \frac{N(s)}{D(s)} = \frac{b_m s^m + \dots + b_1 s + b_0}{a_n s^n + \dots + a_1 s + a_0}$$

---

### Physical Meaning of Poles and Zeros 🔴 [MUST KNOW]
- **Poles:** The roots of the denominator polynomial $D(s) = 0$.
  - **Poles dictate system stability, speed of response, and natural oscillation frequencies.**
- **Zeros:** The roots of the numerator polynomial $N(s) = 0$.
  - **Zeros dictate the relative amplitudes of response modes and can cause overshoot or non-minimum phase undershoot.**

🤖 **ROBOTICS CONNECTION**: In a DC motor velocity model $G(s) = \frac{\Omega(s)}{V(s)} = \frac{K}{\tau_m s + 1}$, the single pole is at $s = -\frac{1}{\tau_m}$. A smaller time constant $\tau_m$ pushes the pole farther left along the negative real axis, resulting in a faster motor response.

---

# 6. Block Diagrams

### Block Diagram Algebra Rules 🔴 [MUST KNOW]

```
1. Series (Cascade):      ──[ G1(s) ]──>[ G2(s) ]──>        Equivalent: G_eq = G1(s) * G2(s)

2. Parallel:              ──┬──>[ G1(s) ]──>(+)──>          Equivalent: G_eq = G1(s) + G2(s)
                            └──>[ G2(s) ]───┘

3. Negative Feedback:     R(s) ──(+)──>[ G(s) ]──┬──> Y(s)  Equivalent: T(s) = G(s) / (1 + G(s)H(s))
                                  ▲ -            │
                                  └───[ H(s) ]───┘
```

---

### Derivation of the Closed-Loop Transfer Function 🔴 [MUST KNOW]
Let $R(s)$ be the input, $Y(s)$ be the output, $E(s)$ be the error, $G(s)$ be the forward plant, and $H(s)$ be the feedback sensor:

$$1. \quad E(s) = R(s) - H(s) Y(s)$$
$$2. \quad Y(s) = G(s) E(s)$$

Substitute (1) into (2):

$$Y(s) = G(s) \Big( R(s) - H(s) Y(s) \Big) = G(s) R(s) - G(s) H(s) Y(s)$$

Group $Y(s)$ terms on the left side:

$$Y(s) \Big( 1 + G(s) H(s) \Big) = G(s) R(s)$$

Divide to obtain the **Closed-Loop Transfer Function $T(s)$**:

$$T(s) = \frac{Y(s)}{R(s)} = \frac{G(s)}{1 + G(s) H(s)}$$

When unity feedback is used ($H(s) = 1$):

$$T(s) = \frac{G(s)}{1 + G(s)}$$

---

# 7. Stability — EXTREMELY IMPORTANT

### Bounded-Input Bounded-Output (BIBO) Stability 🔴 [MUST KNOW]
A system is **BIBO Stable** if every bounded input ($|u(t)| \le M_u < \infty$) produces a bounded output ($|y(t)| \le M_y < \infty$).

---

### Continuous-Time Stability via the Complex $s$-Plane 🔴 [MUST KNOW]

```
                   Imaginary Axis (jω)
                          │
    UNSTABLE REGION       │       UNSTABLE REGION
    (Left Half-Plane)     │       (Right Half-Plane)
                          │
         Re(s) < 0        │          Re(s) > 0
                          │
            X (Pole 1)    │              X (Unstable Pole)
                          │
  ────────────────────────┼──────────────────────── Real Axis (σ)
                          │
            X (Pole 2)    │
                          │
    STABLE REGION         │       MARGINALLY STABLE:
    All poles Re(s) < 0   │       Non-repeated poles on jω axis
```

- **Stable:** **ALL** closed-loop poles lie strictly in the **Open Left-Half Plane (LHP)** ($\text{Re}(p_i) < 0$). Impulse response decays exponentially to 0.
- **Unstable:** If **ANY** pole lies in the **Right-Half Plane (RHP)** ($\text{Re}(p_i) > 0$) or if multiple repeated poles lie on the imaginary axis. Impulse response explodes to $\pm \infty$.
- **Marginally Stable:** One or more non-repeated, simple poles lie exactly on the imaginary axis ($\text{Re}(p_i) = 0$) with all other poles in the LHP. System sustains constant-amplitude oscillations without decaying or growing.

---

### Discrete-Time Stability ($z$-Domain) 🔴 [MUST KNOW]
In digital discrete-time control ($z = e^{s T_s}$), the continuous-time LHP maps inside the **Unit Circle**:
- **Stable:** All poles lie strictly **inside the unit circle** ($|z_i| < 1$).
- **Unstable:** Any pole lies **outside the unit circle** ($|z_i| > 1$).
- **Marginally Stable:** Non-repeated poles on the unit circle circumference ($|z_i| = 1$).

---

# 8. Time-Domain Response

### Standard Second-Order Step Response Specifications 🔴 [MUST KNOW]

```
Output y(t)
    ▲
    │                      Peak Value y_max (Overheat/Overshoot)
    │                      ┌────────┐
1.0 ┼ - - - - - - - - - - ┌┘ - - - - └───┬─────────────────── Steady-State Value y_ss = 1.0
    │                    ┌┘              └──┬─────────────── ±2% Settling Band
    │                   ┌┘                  └───────────────
    │                  ┌┘
    │                 ┌┘
    │               ┌─┘
    │             ┌─┘
    │          ┌──┘
0.0 ┼──────────┴──────────┬──────────────┬──────────────┬────► Time t
    0                     tr             tp             ts
                       Rise Time      Peak Time     Settling Time
```

---

### The Governing Equations for Second-Order Systems 🔴 [MUST KNOW]

$$T(s) = \frac{\omega_n^2}{s^2 + 2\zeta\omega_n s + \omega_n^2}$$

1. **Damping Ratio ($\zeta$):**
   - $\zeta > 1$: **Overdamped** (Slow, sluggish response; two distinct real negative poles; zero overshoot).
   - $\zeta = 1$: **Critically Damped** (Fastest possible response without overshoot; two identical real negative poles).
   - $0 < \zeta < 1$: **Underdamped** (Fast rise time; oscillatory overshoot; complex conjugate poles $s = -\zeta\omega_n \pm j\omega_n\sqrt{1-\zeta^2}$).
   - $\zeta = 0$: **Undamped** (Sustained continuous oscillation at natural frequency $\omega_n$; poles on imaginary axis $s = \pm j\omega_n$).
   - $\zeta < 0$: **Unstable** (Exploding oscillations; poles in RHP).

2. **Percentage Overshoot ($\%OS$):**
   $$\%OS = e^{-\left(\frac{\zeta \pi}{\sqrt{1 - \zeta^2}}\right)} \times 100\%$$
   *(Depends ONLY on damping ratio $\zeta$, completely independent of $\omega_n$)*

3. **Peak Time ($t_p$):**
   $$t_p = \frac{\pi}{\omega_d} = \frac{\pi}{\omega_n \sqrt{1 - \zeta^2}}$$

4. **Settling Time ($t_s$ for $\pm 2\%$ tolerance band):**
   $$t_s \approx \frac{4}{\zeta \omega_n}$$

5. **Rise Time ($t_r$ from $10\%$ to $90\%$):**
   $$t_r \approx \frac{1.8}{\omega_n}$$

---

# 9. PID Control — HIGHEST PRIORITY

```
               ┌──────────────────────┐
               │ Proportional Gain Kp │
            ┌─>│      u_P = Kp * e    ├─┐
            │  └──────────────────────┘ │
            │                           │
            │  ┌──────────────────────┐ │
Error e(t)  │  │   Integral Gain Ki   │ │   Summing Junction
 ───────────┼─>│ u_I = Ki * ∫ e(τ)dτ  ├─┼────────(+)────────> Control Command u(t)
            │  └──────────────────────┘ │         ▲
            │                           │         │
            │  ┌──────────────────────┐ │         │
            │  │  Derivative Gain Kd  │ │         │
            └─>│ u_D = Kd * (de / dt) ├─┘         │
               └──────────────────────┘           │
               Feedforward Term u_FF (Optional) ──┘
```

### Continuous-Time PID Formulation 🔴 [MUST KNOW]

$$u(t) = K_p \, e(t) + K_i \int_0^t e(\tau)\,d\tau + K_d \, \frac{de(t)}{dt}$$

- **Proportional Term ($u_P(t) = K_p e(t)$):** Action based on the **PRESENT** error. Generates a restoring force proportional to the instantaneous deviation. Cannot eliminate steady-state error on its own in type-0 systems.
- **Integral Term ($u_I(t) = K_i \int e(\tau)d\tau$):** Action based on the **PAST** accumulated error. Continues to build up control effort as long as any residual error exists, guaranteeing **zero steady-state error**.
- **Derivative Term ($u_D(t) = K_d \dot{e}(t)$):** Action based on the **FUTURE** anticipated error trend. Acts as virtual electronic damping/friction, predicting overshoot and braking the system to improve stability.

---

### Discrete-Time PID Implementation Derivation 🔴 [MUST KNOW]
In digital microcontrollers and ROS nodes running at discrete sample period $\Delta t$:
1. Current error at sample step $k$:
   $$e[k] = r[k] - y[k]$$
2. Numerical integration via Euler forward/backward sum:
   $$\text{integral}[k] = \text{integral}[k-1] + e[k] \cdot \Delta t$$
3. Numerical backward finite difference derivative:
   $$\text{derivative}[k] = \frac{e[k] - e[k-1]}{\Delta t}$$
4. Discrete total control output:
   $$u[k] = K_p \, e[k] + K_i \, \text{integral}[k] + K_d \, \left( \frac{e[k] - e[k-1]}{\Delta t} \right)$$

---

# 10. PID Numerical Problems

### Problem Set for Hand Calculation Practice 🔴 [MUST KNOW]

#### Problem 10.1: Discrete PID Hand Step Calculation
A robot joint position controller has gains:
$$K_p = 4.0, \quad K_i = 2.0, \quad K_d = 0.5$$
The control loop executes at $\Delta t = 0.1\text{ s}$.
The accumulated integral up to the previous step is $\text{integral}[k-1] = 1.5\text{ rad}\cdot\text{s}$.
The previous error was $e[k-1] = 0.8\text{ rad}$.
At current step $k$, the target position is $r[k] = 2.0\text{ rad}$ and actual position is $y[k] = 1.6\text{ rad}$.

**Tasks:**
1. Calculate current error $e[k]$.
2. Calculate current accumulated integral $\text{integral}[k]$.
3. Calculate derivative term $\text{derivative}[k]$.
4. Calculate $u_P$, $u_I$, $u_D$, and total unconstrained output $u[k]$.
5. If the motor driver saturates at $u_{\max} = 5.0\text{ V}$, what is the final applied voltage?

*(Solutions provided in Section 34)*

---

# 11. Effect of PID Gains

### Systematic Impact of Parameter Variations 🔴 [MUST KNOW]

```
+----------------+---------------+---------------+---------------+--------------------+------------------+
| Parameter Inc. | Rise Time     | Overshoot     | Settling Time | Steady-State Error | Stability        |
+----------------+---------------+---------------+---------------+--------------------+------------------+
| Increasing Kp  | Decreases (↓) | Increases (↑) | Small change  | Decreases (↓)      | Degrades (↓)     |
| Increasing Ki  | Decreases (↓) | Increases (↑) | Increases (↑) | Eliminates (→ 0)   | Degrades (↓)     |
| Increasing Kd  | Minor change  | Decreases (↓) | Decreases (↓) | No direct effect   | Improves (↑)*    |
+----------------+---------------+---------------+---------------+--------------------+------------------+
```
*\*Note: Excessive $K_d$ amplifies high-frequency sensor noise, which destabilizes physical actuators.*

> ⚠️ **INTERVIEW TRAP**: Never state that increasing $K_p$ eliminates steady-state error. Proportional gain *reduces* steady-state error by increasing system stiffness, but it requires non-zero error to produce non-zero output. Only **Integral action ($K_i$)** can drive steady-state error strictly to zero.

---

# 12. Integral Windup

### The Cause of Integral Windup 🔴 [MUST KNOW]
When a physical actuator hits its hard saturation limit (e.g., motor driver hits $100\%$ PWM duty cycle or maximum battery voltage $24\text{ V}$), the control loop can no longer accelerate the system any faster. However, if an error persists, the integral term $\int e(t)dt$ **continues to integrate and grow to enormous values**.
- When the robot finally reaches the setpoint, the massive accumulated integral forces the motor to stay saturated at full power in the same direction.
- This causes **violent, prolonged overshoot** while the system slowly integrates reverse error to "unwind" the integral accumulator.

---

### Anti-Windup Countermeasures 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
| Anti-Windup Method       | Mechanism                                               |
+--------------------------+---------------------------------------------------------+
| 1. Integrator Clamping   | Hard-clamp the integral accumulator:                    |
|    (Saturation Limits)   | integral = clamp(integral, -I_max, I_max)               |
+--------------------------+---------------------------------------------------------+
| 2. Conditional           | Freeze integration whenever actuator is saturated AND   |
|    Integration (Clamping)| sign(error) == sign(control_output).                    |
+--------------------------+---------------------------------------------------------+
| 3. Back-Calculation      | Feed the difference (u_actual - u_unclamped) back into   |
|    Tracking Anti-Windup  | the integrator with a tracking gain Kt to bleed off sum.|
+--------------------------+---------------------------------------------------------+
```

```cpp
// C++ Anti-Windup Conditional Clamping Code Pattern:
double u_unconstrained = u_p + (integral + error * dt) * ki + u_d;
if (u_unconstrained > u_max) {
    u_actual = u_max;
    if (error < 0) integral += error * dt; // Only integrate if error unwinds
} else if (u_unconstrained < u_min) {
    u_actual = u_min;
    if (error > 0) integral += error * dt;
} else {
    integral += error * dt;
    u_actual = u_unconstrained;
}
```

---

# 13. Derivative Kick and Sensor Noise

### 1. Derivative Kick 🔴 [MUST KNOW]
When a user or path planner suddenly commands a step change in setpoint $r(t)$, the derivative of error $\frac{d e(t)}{dt} = \frac{d(r - y)}{dt} = \frac{dr}{dt} - \frac{dy}{dt}$ approaches **infinity** ($\infty$) at that instant. This produces an instantaneous, massive voltage spike ("kick") that can damage gearboxes or trip motor driver overcurrent faults.
- **Solution — Derivative on Measurement:** Compute the derivative of the measured output variable $- \frac{dy}{dt}$ instead of the error:
  $$u(t) = K_p \, e(t) + K_i \int e(\tau)d\tau - K_d \, \frac{dy(t)}{dt}$$

---

### 2. Sensor Noise Amplification & First-Order Low-Pass Filter 🔴 [MUST KNOW]
High-frequency sensor quantization noise $n(t)$ from optical encoders or IMUs has large derivatives ($\frac{dn}{dt} \gg 0$). Pure derivative control amplifies this noise, causing motor chatter and heating.
- **Solution — Filtered Derivative:** Pass the derivative term through a first-order low-pass filter with cutoff pole $N$ (typically $N \in [8, 20]$):
  $$D(s) = \frac{K_d s}{\frac{s}{N} + 1}$$

---

# 14. PID Tuning

### Practical Manual Heuristic Tuning Procedure 🔴 [MUST KNOW]
If an interviewer asks: *"How would you tune a PID controller on a physical robot motor?"* provide this structured, safety-first methodology:

1. **Step 1: Set All Gains to Zero:** $K_p = 0, K_i = 0, K_d = 0$.
2. **Step 2: Increase $K_p$ (Proportional):** Gradually increase $K_p$ until the system responds with brisk motion and begins to exhibit sustained oscillation around the setpoint.
3. **Step 3: Increase $K_d$ (Derivative):** Gradually increase $K_d$ to add damping, suppress oscillations, and eliminate overshoot.
4. **Step 4: Increase $K_i$ (Integral):** Increase $K_i$ slowly to eliminate residual steady-state error and overcome static friction / gravity offsets.
5. **Step 5: Apply Anti-Windup & Low-Pass Filter:** Add integral saturation clamps and a low-pass filter to the derivative channel to suppress encoder chatter.

---

# 15. Cascade Control

### Multi-Loop Control Architecture 🔴 [MUST KNOW]
In industrial robotics, motor control is organized into **nested cascade loops**:

```
Position Target     +───────────────+     Velocity Cmd     +──────────────+     Current Cmd     +──────────────+
 (Trajectory)  ───> │ Position Loop │ ──> (Limit Clamped) ─> │ Velocity Loop│ ──> (Limit Clamped)─> │ Current Loop │ ──> Inverter PWM ──> Motor
                    │ (PID @ 50 Hz) │                      │ (PID @ 200 Hz│                     │ (PI @ 10 kHz)│
                    +───────┬───────+                      +──────┬───────+                     +──────┬───────+
                            │                                     │                                    │
                            ▲                                     ▲                                    ▲
                            │ Position Feedback                   │ Velocity Feedback                  │ Phase Current
                     [ Optical Encoder ]                   [ Encoder Ticks / dt ]               [ Current Shunt Sensor ]
```

> 💡 **CRITICAL RULE OF CASCADE CONTROL**: **Inner loops MUST operate significantly faster than outer loops.**  
> - Current/Torque Loop (Innermost): $10\text{ kHz}$ (Sub-millisecond electrical dynamics $L/R$).
> - Velocity Loop (Middle): $200\text{ Hz} - 500\text{ Hz}$ (Mechanical inertia dynamics $J/b$).
> - Position / Trajectory Loop (Outermost): $20\text{ Hz} - 50\text{ Hz}$ (Kinematic navigation dynamics).

---

# 16. Feedforward + Feedback

### Predictive Feedforward + Corrective Feedback 🔴 [MUST KNOW]

$$u_{\text{total}}(t) = u_{\text{feedforward}}(t) + u_{\text{feedback}}(t)$$

```
Desired Acceleration a_des ───> [ Inverse Dynamics / Model ] ───> u_FF
                                                                   │
Desired Position p_des ──────(+)───> [ PID Feedback ] ───────────(+)───> Motor Torque Cmd
                              ▲ -                                  │
Actual Position p_act ────────┴────────────────────────────────────┘
```

- **Feedforward ($u_{\text{FF}}$):** Computes the nominal control effort required based on the **known mathematical model of the plant** (e.g., $u_{\text{FF}} = m \cdot a_{\text{des}} + v_{\text{des}} \cdot b + \tau_{\text{gravity}}$). It acts immediately with **zero phase lag**.
- **Feedback ($u_{\text{FB}}$):** Reacts only to unmodeled disturbances, parameter errors, and sensor noise to zero out residual tracking error.

---

# 17. State-Space Representation

### Modern State-Space Matrix Form 🔴 [MUST KNOW]

$$\dot{\mathbf{x}}(t) = \mathbf{A}\mathbf{x}(t) + \mathbf{B}\mathbf{u}(t) \quad \text{(State Equation)}$$
$$\mathbf{y}(t) = \mathbf{C}\mathbf{x}(t) + \mathbf{D}\mathbf{u}(t) \quad \text{(Output Equation)}$$

where:
- $\mathbf{x}(t) \in \mathbb{R}^n$: **State Vector** (Minimum set of internal variables that completely describe the system's dynamic state at time $t$).
- $\mathbf{u}(t) \in \mathbb{R}^m$: **Control Input Vector** (Actuator commands: voltages, forces, torques).
- $\mathbf{y}(t) \in \mathbb{R}^p$: **Output Vector** (Sensor measurements).
- $\mathbf{A} \in \mathbb{R}^{n \times n}$: **System Matrix** (Internal system dynamics).
- $\mathbf{B} \in \mathbb{R}^{n \times m}$: **Input Matrix** (How actuators influence states).
- $\mathbf{C} \in \mathbb{R}^{p \times n}$: **Output Matrix** (How states map to sensor readings).
- $\mathbf{D} \in \mathbb{R}^{p \times m}$: **Feedthrough / Direct Transmission Matrix** (Usually $\mathbf{0}$ in physical mechanical systems).

---

### Step-by-Step Robotics Derivation: 1D Mobile Robot with Friction 🔴 [MUST KNOW]
A mobile robot of mass $m$ has position $p(t)$, velocity $v(t)$, viscous drag friction $b$, and applied motor force $F(t)$:

$$\dot{p}(t) = v(t)$$
$$m \dot{v}(t) + b v(t) = F(t) \implies \dot{v}(t) = -\frac{b}{m} v(t) + \frac{1}{m} F(t)$$

1. Define State Vector $\mathbf{x} = \begin{bmatrix} p \\ v \end{bmatrix}$ and Input $u = F$.
2. Write in matrix form:
   $$\begin{bmatrix} \dot{p} \\ \dot{v} \end{bmatrix} = \begin{bmatrix} 0 & 1 \\ 0 & -\frac{b}{m} \end{bmatrix} \begin{bmatrix} p \\ v \end{bmatrix} + \begin{bmatrix} 0 \\ \frac{1}{m} \end{bmatrix} u$$
3. If our sensor measures only position $y = p$:
   $$y = \begin{bmatrix} 1 & 0 \end{bmatrix} \begin{bmatrix} p \\ v \end{bmatrix} + [0] u$$

$$\mathbf{A} = \begin{bmatrix} 0 & 1 \\ 0 & -\frac{b}{m} \end{bmatrix}, \quad \mathbf{B} = \begin{bmatrix} 0 \\ \frac{1}{m} \end{bmatrix}, \quad \mathbf{C} = \begin{bmatrix} 1 & 0 \end{bmatrix}, \quad \mathbf{D} = [0]$$

---

# 18. Controllability and Observability

### 1. Controllability 🔴 [MUST KNOW]
- **Intuition:** A system is controllable if an input $\mathbf{u}(t)$ can steer any initial state $\mathbf{x}(0)$ to any target state $\mathbf{x}(t_f)$ in a finite time $t_f$.
- **Controllability Matrix ($\mathcal{C}$):**
  $$\mathcal{C} = \begin{bmatrix} \mathbf{B} & \mathbf{A}\mathbf{B} & \mathbf{A}^2\mathbf{B} & \dots & \mathbf{A}^{n-1}\mathbf{B} \end{bmatrix}$$
- **Condition:** The system is **Controllable** if and only if $\text{rank}(\mathcal{C}) = n$ (Full Row Rank / $\det(\mathcal{C}) \ne 0$ for square matrices).

---

### 2. Observability 🔴 [MUST KNOW]
- **Intuition:** A system is observable if the initial state $\mathbf{x}(0)$ can be uniquely reconstructed from observing the output history $\mathbf{y}(t)$ and input $\mathbf{u}(t)$ over a finite time interval.
- **Observability Matrix ($\mathcal{O}$):**
  $$\mathcal{O} = \begin{bmatrix} \mathbf{C} \\ \mathbf{C}\mathbf{A} \\ \mathbf{C}\mathbf{A}^2 \\ \vdots \\ \mathbf{C}\mathbf{A}^{n-1} \end{bmatrix}$$
- **Condition:** The system is **Observable** if and only if $\text{rank}(\mathcal{O}) = n$ (Full Column Rank).

---

# 19. Discrete-Time Control

### Discretization & Sampling Frequencies in Robotics 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
| Loop Hierarchy                | Execution Rate | Primary Task                      |
+------------------------------------------------------------------------------------+
| Motor Current / PWM (FOC)     | 10 kHz         | Sub-millisecond current regulation|
| Wheel Velocity PID Loop       | 500 Hz – 1 kHz | Encoder tick processing & torque  |
| State Estimation (EKF / IMU)  | 100 Hz – 200 Hz| IMU fusion & odometry propagation |
| Local Trajectory Tracking     | 20 Hz – 50 Hz  | Pure pursuit, DWA, local avoidance|
| Global Path Planning (A*)     | 1 Hz – 5 Hz    | Long-horizon graph search         |
+------------------------------------------------------------------------------------+
```

---

# 20. Digital Control Issues

### Practical Real-Time Degradation Factors 🔴 [MUST KNOW]
1. **Sampling Delay & Zero-Order Hold (ZOH):** Digital-to-analog converters hold their command constant between sample ticks, introducing an effective time delay of $\frac{T_s}{2}$, which erodes control phase margin.
2. **Computational Latency:** Complex algorithms (e.g. MPC quadratic program solvers) take non-zero time $\tau_{\text{calc}}$ to compute. If $\tau_{\text{calc}} \approx T_s$, the commanded action applies to an already outdated state.
3. **Sensor Latency:** Camera image processing pipelines or LiDAR point-cloud clustering introduce $30\text{ ms} - 100\text{ ms}$ delays.
4. **Aliasing:** Sampling a signal containing frequencies above the **Nyquist frequency** ($f_{\text{Nyquist}} = \frac{f_s}{2}$) causes high-frequency mechanical vibration to masquerade as low-frequency oscillations. Must use an analog anti-aliasing RC filter before ADC!

---

# 21. Motor Control

### Electric Motor Drive Architecture 🔴 [MUST KNOW]

```
Voltage Command u(t)      Duty Cycle D          High-Power PWM      Electromagnetic Torque
 (from Velocity PID) ───> [ PWM Timer ] ────> [ H-Bridge Driver ] ───────> [ DC Motor ] ───> Wheel Shaft
                             (e.g., 20 kHz)       (MOSFETs / IGBTs)
```

1. **Pulse-Width Modulation (PWM):** Fast digital switching ($10\text{ kHz} - 40\text{ kHz}$) where the average DC voltage applied across the motor windings is proportional to the **Duty Cycle ($D = \frac{T_{\text{on}}}{T_{\text{period}}}$)**:
   $$V_{\text{avg}} = D \cdot V_{\text{battery}}$$
2. **Optical Incremental Encoder:** Measures wheel revolutions via two out-of-phase optical channels (Channel A and Channel B in **quadrature**), providing direction of rotation and velocity calculation:
   $$\omega = \frac{\Delta \text{ticks}}{\text{TicksPerRev} \cdot \Delta t} \times 2\pi \quad (\text{rad/s})$$

---

# 22. Robot Kinematics + Control Connection

### Kinematics vs. Dynamics vs. Control 🔴 [MUST KNOW]
- **Forward Kinematics (FK):** Maps joint angles $\mathbf{q}$ to end-effector Cartesian pose $\mathbf{x}_e$: $\mathbf{x}_e = f(\mathbf{q})$.
- **Inverse Kinematics (IK):** Computes required joint angles to achieve a desired Cartesian pose: $\mathbf{q} = f^{-1}(\mathbf{x}_e)$.
- **Dynamics:** Formulates the underlying forces and torques that generate acceleration ($\mathbf{M}(\mathbf{q})\ddot{\mathbf{q}} + \mathbf{C}(\mathbf{q}, \dot{\mathbf{q}})\dot{\mathbf{q}} + \mathbf{g}(\mathbf{q}) = \boldsymbol{\tau}$).
- **Control:** Generates the actual instantaneous actuator torque commands $\boldsymbol{\tau}(t)$ to track desired joint trajectories $\mathbf{q}_{\text{des}}(t)$ in the presence of friction and payload disturbances.

---

# 23. Mobile Robot Control

### Differential Drive Kinematics (Unicycle Model) 🔴 [MUST KNOW]

```
               ▲ Y (World)
               │          Robot Heading θ
               │             /  v (Linear Velocity)
               │            /
               │           ┌──────────┐
   Left Wheel  │           │   [X]    │  Right Wheel
   Speed v_L   │   =====[  │          │  ]===== Speed v_R
               │           └──────────┘
               │               ◄──L──► (Track Width)
               │
               └────────────────────────► X (World)
```

1. **Forward Kinematics (Wheel Speeds $\to$ Body Twist):**
   $$v = \frac{v_R + v_L}{2} \quad (\text{Linear Velocity, m/s})$$
   $$\omega = \frac{v_R - v_L}{L} \quad (\text{Angular Velocity, rad/s})$$
   where $L$ is the track width (wheel-to-wheel baseline distance).

2. **Inverse Kinematics (Body Twist $\to$ Individual Wheel Commands):**
   $$v_R = v + \frac{\omega \cdot L}{2}$$
   $$v_L = v - \frac{\omega \cdot L}{2}$$

3. **Unicycle Kinematic State Evolution in World Frame:**
   $$\dot{x} = v \cos(\theta), \quad \dot{y} = v \sin(\theta), \quad \dot{\theta} = \omega$$

---

# 24. Path Tracking Controllers

```
+----------------------------------------------------------------------------------------------------+
| Controller      | Primary Error Metric         | Strengths                      | Weaknesses       |
+-----------------+------------------------------+--------------------------------+------------------+
| Pure Pursuit    | Lookahead lateral offset y_l | Extremely stable, simple math  | Cuts corners     |
| Stanley Control | Cross-track error e & yaw ψ  | Proven on autonomous cars (DARPA)| Sensitive to noise|
| PID Cross-Track | Lateral distance e           | Intuitive                      | Lacks predictive |
|                 |                              |                                | geometric model  |
+----------------------------------------------------------------------------------------------------+
```

---

### 1. Pure Pursuit Controller 🔴 [MUST KNOW]
Geometrically fits a circular arc from the vehicle's rear axle to a lookahead point $(x_L, y_L)$ on the reference path at distance $L_d$:

$$\kappa = \frac{2 y_{\text{local}}}{L_d^2} \quad \implies \quad \delta = \arctan(\kappa \cdot W) = \arctan\left(\frac{2 W \sin(\alpha)}{L_d}\right)$$

where $W$ is wheelbase, $L_d$ is lookahead distance, and $\alpha$ is angle between vehicle heading and target lookahead point.
- **Lookahead Tradeoff:** Small $L_d \to$ aggressive, oscilliatory path tracking. Large $L_d \to$ smooth tracking, but cuts sharp corners.

---

### 2. Stanley Controller 🔴 [MUST KNOW]
Computes steering angle $\delta(t)$ referenced to the **front axle** using heading error $\theta_e = \theta_{\text{path}} - \theta_{\text{robot}}$ and cross-track distance $e(t)$:

$$\delta(t) = \theta_e + \arctan\left(\frac{k \cdot e(t)}{v(t) + \epsilon}\right)$$

where $k$ is cross-track gain, $v(t)$ is forward velocity, and $\epsilon$ prevents division by zero at rest.

---

# 25. LQR — HIGH PRIORITY

### Why PID is Insufficient for Coupled Multi-Input Multi-Output (MIMO) Systems 🔴 [MUST KNOW]
PID controls single inputs based on single outputs (SISO). For coupled systems (e.g. an inverted pendulum cart, quadcopter attitude, or full robot chassis tracking $[x, y, \theta]$ simultaneously), tuning separate PID loops leads to fighting between actuators. LQR provides a mathematically optimal, globally stable multi-state feedback gain matrix $\mathbf{K}$.

---

### LQR Cost Function Formulation 🔴 [MUST KNOW]
For a linear state-space system $\dot{\mathbf{x}} = \mathbf{A}\mathbf{x} + \mathbf{B}\mathbf{u}$, find the control law $\mathbf{u}(t) = -\mathbf{K}\mathbf{x}(t)$ that minimizes the infinite-horizon quadratic performance index:

$$J = \int_0^\infty \Big( \mathbf{x}(t)^T \mathbf{Q} \mathbf{x}(t) + \mathbf{u}(t)^T \mathbf{R} \mathbf{u}(t) \Big) \, dt$$

where:
- $\mathbf{Q} \succeq 0$ (Positive Semi-Definite State Weighting Matrix): Penalizes state tracking deviations.
- $\mathbf{R} \succ 0$ (Positive Definite Control Weighting Matrix): Penalizes actuator energy and effort.

---

### The Continuous Algebraic Riccati Equation (CARE) 🔴 [MUST KNOW]
The optimal gain matrix is computed as:

$$\mathbf{K} = \mathbf{R}^{-1} \mathbf{B}^T \mathbf{P}$$

where $\mathbf{P}$ is the unique positive-definite solution to the Algebraic Riccati Equation:

$$\mathbf{A}^T \mathbf{P} + \mathbf{P} \mathbf{A} - \mathbf{P} \mathbf{B} \mathbf{R}^{-1} \mathbf{B}^T \mathbf{P} + \mathbf{Q} = \mathbf{0}$$

---

### The $\mathbf{Q}$ vs. $\mathbf{R}$ Engineering Tradeoff 🔴 [MUST KNOW]
- **Increasing $\mathbf{Q}$ relative to $\mathbf{R}$:** State error is heavily penalized. Controller acts aggressively with fast response, placing closed-loop poles far into the LHP at the expense of high actuator effort and saturation risk.
- **Increasing $\mathbf{R}$ relative to $\mathbf{Q}$:** Actuator effort is heavily penalized. Controller acts gently with slow, smooth response, conserving battery and avoiding motor saturation.

---

# 26. LQR Numerical & Conceptual Problems

#### Problem 26.1: Direct LQR State Feedback Output Calculation
An autonomous tugger lateral controller uses state vector $\mathbf{x} = \begin{bmatrix} e \\ \dot{e} \end{bmatrix}$ (lateral position error $e$ and lateral velocity error $\dot{e}$).
LQR optimization produced the gain matrix:
$$\mathbf{K} = \begin{bmatrix} 3.5 & 1.2 \end{bmatrix}$$
At the current instant, the vehicle is off-course by $e = -0.4\text{ m}$ and moving toward the center at $\dot{e} = 0.2\text{ m/s}$.

**Tasks:**
1. State the optimal control law formula.
2. Compute the scalar steering command $u$.
3. Explain why the control law contains a negative sign.

*(Solution in Section 34)*

---

# 27. MPC — HIGH PRIORITY

### The Model Predictive Control (MPC) Philosophy 🔴 [MUST KNOW]

```
Current Time t = k
       │
       ▼
1. Measure current state x[k]
       │
       ▼
2. Over Prediction Horizon N (e.g., next 2.0s):
   Solve a constrained numerical optimization problem (Quadratic Program):
   Find optimal control sequence: U* = { u[k], u[k+1], ..., u[k+N-1] }
   Subject to:
     - Robot Dynamics: x[t+1] = f(x[t], u[t])
     - Actuator Limits: u_min <= u[t] <= u_max  (Motor limits)
     - State Bounds: y_min <= y[t] <= y_max      (Lane boundaries / obstacle clearance)
       │
       ▼
3. Receding Horizon Step:
   Apply ONLY the first control action u*[k] to the physical robot motors.
       │
       ▼
4. Advance clock k -> k+1, discard remaining sequence, measure new state x[k+1], and REPEAT.
```

---

### Master Comparison: PID vs. LQR vs. MPC 🔴 [MUST KNOW]

```
+-------------------+----------------------+-----------------------+----------------------------------+
| Feature           | PID                  | LQR                   | MPC                              |
+-------------------+----------------------+-----------------------+----------------------------------+
| Model Required    | Model-free (heuristic| Linear State-Space    | Linear or Non-linear Model       |
| Hard Constraints  | Heuristic clamping   | Cannot handle bounds  | Explicitly handles state & input |
|                   | (Anti-windup)        |                       | constraints in optimization      |
| Computation Load  | Tiny (< microsecond) | Low (u = -Kx matrix)  | Heavy (Solves QP/NLP at 20-50Hz) |
| Multi-Variable    | Poor (SISO only)     | Excellent (MIMO)      | Excellent (MIMO)                 |
| Predictive Horizon| None (Reactive)      | Infinite (Analytical) | Finite Prediction Horizon N      |
+-------------------+----------------------+-----------------------+----------------------------------+
```

---

# 28. Optimal Control

### What is Optimal Control? 🔴 [MUST KNOW]
Optimal control mathematically determines control inputs over time that minimize a specified scalar performance index (Cost Function $J$) while satisfying physical dynamic constraints.
- **Minimum Time Control (Bang-Bang):** Drives state to goal in minimum time by operating actuators at maximum positive or negative saturation limits.
- **Minimum Energy Control:** Minimizes $\int u(t)^2 dt$ to maximize battery life on mobile AGVs.
- **Minimum Jerk Control:** Minimizes $\int \left(\frac{d^3 x}{dt^3}\right)^2 dt$ to ensure smooth motions that protect delicate cargo.

---

# 29. Learning-Based Control

### Model-Based vs. Model-Free Reinforcement Learning (RL) 🟡 [GOOD TO KNOW]

```
+------------------------------------------------------------------------------------+
| Classical Control (MPC / PID)        | Reinforcement Learning (PPO / SAC)          |
+--------------------------------------+---------------------------------------------+
| Requires explicit physics equations  | Learns mapping through trial-and-error      |
| Deterministic, provable stability    | No formal stability or safety guarantees    |
| Breaks when unmodeled physics occur  | Can discover complex non-linear dynamics    |
+--------------------------------------+---------------------------------------------+
```
🤖 **ROBOTICS HYBRID BEST PRACTICE**: In industrial autonomy, pure neural-network control directly driving motors is considered a safety hazard. Instead, **RL policies output high-level setpoints**, while a classical, deterministic **PID/MPC controller enforces low-level physical safety barriers**.

---

# 30. Robustness

### Disturbances and Parameter Variations in Robotics 🔴 [MUST KNOW]
- **Parametric Uncertainty:** Payload variation changing robot total mass $m$ by $200\%$, wheel diameter wear over years, motor coil resistance changes with heat.
- **Unmodeled Dynamics:** Tire lateral slip, gearbox backlash, fluid slosh in liquid transport AGVs.
- **Disturbance Rejection:** The capacity of a controller to maintain zero tracking error despite continuous external forces (e.g., navigating up a $10^\circ$ warehouse loading ramp).

---

# 31. Control System Design Problem

### Realistic Interview Design Scenario 🔴 [MUST KNOW]
> **Prompt:** *"Design the complete velocity and trajectory tracking control architecture for an autonomous industrial electric tugger carrying variable payloads up to 1000 kg."*

#### Model Architectural Solution:
1. **Sensors & State Estimation (100 Hz):** Dual quadrature wheel encoders + 6-DOF IMU fused via an Extended Kalman Filter (EKF) to produce filtered pose $(x, y, \theta)$ and body twist $(v, \omega)$.
2. **Trajectory Interpolator (20 Hz):** Receives global path waypoints and interpolates continuous target state $[x_{\text{ref}}(t), y_{\text{ref}}(t), \theta_{\text{ref}}(t), v_{\text{ref}}(t)]$.
3. **Kinematic Path Tracking Controller:** Pure Pursuit or Stanley Controller computes target linear speed $v_{\text{cmd}}$ and yaw rate $\omega_{\text{cmd}}$.
4. **Inverse Kinematics Block:** Converts $(v_{\text{cmd}}, \omega_{\text{cmd}})$ into individual wheel setpoints: $\omega_L^*, \omega_R^*$.
5. **Feedforward Dynamics Block:** Evaluates nominal torque $\tau_{\text{FF}} = J_{\text{nominal}} \dot{\omega}^* + b \omega^*$ to compensate for inertia and friction.
6. **Inner Cascade Velocity PID Loops (500 Hz):** Dedicated PID loops per wheel with conditional integrator anti-windup and derivative measurement filtering.
7. **Current / Torque PI Loop (10 kHz):** Directly controls H-bridge PWM to regulate motor phase current.
8. **Safety & Supervisory Layer:** Emergency E-stop monitoring, tilt limits, and watchdog timers to zero out PWM if communication drops.

---

# 32. Debugging Control Systems

### 6 Real-World Failure Scenarios & Diagnostic Solutions 🔴 [MUST KNOW]

#### Scenario 1: Robot Oscillates Violently Around Target Pose
- **Probable Causes:** Proportional gain $K_p$ too high; Derivative gain $K_d$ too low (insufficient damping); Sensor feedback delay too long; Excessive loop execution jitter.
- **Fix:** Decrease $K_p$ by $30-50\%$; increase $K_d$; verify sensor timestamps and eliminate thread latency.

#### Scenario 2: Robot Tracks Path Well at Low Speed but Spins Out / Destabilizes at High Speed
- **Probable Causes:** Fixed lookahead distance in Pure Pursuit (too short for high speed); Tire cornering stiffness saturation (non-linear tire slip); Actuator bandwidth saturation.
- **Fix:** Implement **velocity-scaled lookahead distance** ($L_d = k_v \cdot v + L_{d,0}$); implement dynamic bicycle model MPC.

#### Scenario 3: Large Steady-State Error on Incline / Slopes
- **Probable Causes:** Zero integral gain ($K_i = 0$); Gravity load cannot be overcome by proportional term alone without steady error.
- **Fix:** Introduce small $K_i$ with anti-windup; add feedforward gravity compensation term ($u_{\text{FF}} = m g \sin(\theta_{\text{pitch}})$).

#### Scenario 4: Controller Works in Simulation but Shakes / Chatters on Physical Hardware
- **Probable Causes:** High-frequency encoder quantization noise amplified by unfiltered derivative term; Unmodeled gearbox backlash.
- **Fix:** Filter the derivative channel with a first-order low-pass filter; implement derivative on measurement; add deadband.

#### Scenario 5: Massive Overshoot After Overcoming Obstacle or Saturated Acceleration
- **Probable Causes:** Integral windup during the saturated period.
- **Fix:** Implement conditional integration anti-windup clamping.

#### Scenario 6: Motor Commands Frequently Saturate at 100% PWM
- **Probable Causes:** Reference trajectory requests accelerations beyond motor torque limits; $K_p$ gain unrealistically aggressive.
- **Fix:** Pass reference trajectory through a trapezoidal velocity rate limiter; tune down $K_p$.

---

# 33. Control Interview Questions

### 40+ Categorized Technical Interview Questions 🔴 [MUST KNOW]

#### Fundamentals & Stability
1. **Q:** What is the difference between open-loop and closed-loop control?  
   - **Answer:** Open-loop acts purely on reference commands without measurement; closed-loop uses sensor feedback to compute error and reject disturbances.
2. **Q:** What determines the stability of a continuous-time LTI system?  
   - **Answer:** The locations of the roots of the characteristic equation (closed-loop poles). All poles must have strictly negative real parts ($\text{Re}(p) < 0$, Left Half-Plane).
3. **Q:** What happens if a pole lies exactly on the imaginary axis?  
   - **Answer:** The system is marginally stable, producing undamped sustained oscillations. If the pole is repeated, the system is unstable (output grows as $t \cdot \sin(\omega t)$).
4. **Q:** What is phase margin and gain margin?  
   - **Answer:** Gain Margin is the factor by which open-loop gain can increase before instability. Phase Margin is the additional phase lag at gain-crossover frequency required to induce instability.
5. **Q:** What is the physical meaning of a transfer function zero?  
   - **Answer:** Frequencies $s$ where the transmission of input to output is completely blocked ($Y(s) = 0$). Right-Half Plane zeros produce non-minimum phase undershoot.

#### PID Control
6. **Q:** Why does pure Proportional control produce steady-state error in a type-0 system?  
   - **Answer:** To generate non-zero steady-state control effort to counter friction/load, a non-zero error $e_{ss} = \frac{u_{ss}}{K_p}$ must physically exist.
7. **Q:** Explain Integral Windup and how to prevent it.  
   - **Answer:** Excessive error accumulation in the integrator during actuator saturation. Prevented via conditional integration or back-calculation.
8. **Q:** What is Derivative Kick?  
   - **Answer:** A spike in control effort caused by differentiating a step change in setpoint. Solved by taking derivative of measurement: $-K_d \frac{dy}{dt}$.
9. **Q:** Why do we filter the derivative term in PID?  
   - **Answer:** Unfiltered differentiation acts as a high-pass filter, severely amplifying high-frequency sensor noise ($j\omega K_d$).
10. **Q:** What is the effect of increasing $K_i$ too much?  
    - **Answer:** Introduces phase lag, increases overshoot, causes prolonged settling time, and pushes closed-loop poles toward the RHP.

#### State-Space & Modern Control
11. **Q:** What is state-space representation?  
    - **Answer:** A time-domain matrix model $\dot{\mathbf{x}} = \mathbf{A}\mathbf{x} + \mathbf{B}\mathbf{u}$ using a minimal vector of internal energy state variables.
12. **Q:** Define Controllability.  
    - **Answer:** The ability to steer any initial state to any arbitrary final state in finite time using the control inputs.
13. **Q:** How do you test for Controllability mathematically?  
    - **Answer:** Check if the controllability matrix $\mathcal{C} = [\mathbf{B} \quad \mathbf{AB} \quad \dots \quad \mathbf{A}^{n-1}\mathbf{B}]$ has full rank $n$.
14. **Q:** Define Observability.  
    - **Answer:** The ability to uniquely determine the initial internal states from observing the input and output over a finite time window.
15. **Q:** What is the difference between an unobservable state and an uncontrollable state?  
    - **Answer:** An uncontrollable state cannot be influenced by actuator inputs. An unobservable state cannot be seen or deduced from sensor measurements.

#### LQR & Optimal Control
16. **Q:** What is LQR and what does it optimize?  
    - **Answer:** Linear Quadratic Regulator; optimizes a quadratic cost function trading off state tracking error ($\mathbf{Q}$) and actuator effort ($\mathbf{R}$).
17. **Q:** What happens to LQR gains when $\mathbf{R} \to \infty$?  
    - **Answer:** Control effort is infinitely penalized; gains $\mathbf{K} \to \mathbf{0}$, meaning the controller exerts minimal to zero effort.
18. **Q:** What happens to LQR gains when $\mathbf{Q} \to \infty$?  
    - **Answer:** State error is infinitely penalized; gains $\mathbf{K} \to \infty$, placing poles far into the LHP and driving errors to zero instantly (at risk of actuator saturation).
19. **Q:** Can LQR handle hard actuator constraints directly?  
    - **Answer:** No, standard LQR is an unconstrained analytical optimization. Constraints must be handled via heuristic clipping or MPC.

#### Model Predictive Control (MPC)
20. **Q:** Explain the receding horizon principle in MPC.  
    - **Answer:** At each step, optimize control inputs over a finite future horizon $N$, execute only the first action $u_0$, advance time, and re-solve.
21. **Q:** Why is MPC computationally demanding?  
    - **Answer:** It solves a constrained numerical optimization problem (Quadratic Program or Non-linear Program) online at every single time step.
22. **Q:** What happens if the prediction horizon $N$ in MPC is too short?  
    - **Answer:** The controller acts myopic (short-sighted), potentially steering the vehicle into kinematic traps or dead-ends.
23. **Q:** How does MPC handle hard constraints?  
    - **Answer:** Incorporates inequalities directly into the solver: $\mathbf{u}_{\min} \le \mathbf{u}_k \le \mathbf{u}_{\max}$ and $\mathbf{x}_{\min} \le \mathbf{x}_k \le \mathbf{x}_{\max}$.

#### Mobile Robot Path Tracking
24. **Q:** How does Pure Pursuit calculate steering angle?  
    - **Answer:** Fits a circular arc to a lookahead point at distance $L_d$ on the reference path: $\kappa = \frac{2 y_{\text{local}}}{L_d^2}$.
25. **Q:** What is the effect of a small lookahead distance in Pure Pursuit?  
    - **Answer:** Tight path tracking at low speeds, but causes aggressive, oscillatory snake-like behavior at high speeds.
26. **Q:** What is the Stanley controller?  
    - **Answer:** A front-axle path tracker that combines heading error and non-linear cross-track error: $\delta = \theta_e + \arctan\left(\frac{k e}{v}\right)$.
27. **Q:** Why is cross-track error alone insufficient for steering control?  
    - **Answer:** Without heading error, the robot will overshoot and oscillate across the path like an undamped pendulum.

#### Discrete & Motor Control
28. **Q:** What is the Nyquist-Shannon sampling theorem?  
    - **Answer:** The sampling frequency $f_s$ must be at least twice the highest frequency component present in the physical signal ($f_s > 2 f_{\max}$).
29. **Q:** Why must cascade control inner loops run faster than outer loops?  
    - **Answer:** To prevent phase lag and ensure the inner loop reaches steady state before the outer loop makes its next correction.
30. **Q:** What is Field Oriented Control (FOC)?  
    - **Answer:** A vector control method for BLDC/PMSM motors that decouples stator currents into torque-producing ($I_q$) and flux-producing ($I_d$) components.

---

# 34. Mathematical Interview Problems

### Hand-Solvable Problem Set 🔴 [MUST KNOW]

#### Problem 34.1: Closed-Loop Pole Stability Determination
Given the open-loop plant $G(s) = \frac{10}{s(s + 4)}$ with unity feedback $H(s) = 1$:
1. Determine the closed-loop transfer function $T(s)$.
2. Calculate the natural frequency $\omega_n$ and damping ratio $\zeta$.
3. Determine if the closed-loop system is stable, and classify its damping regime.

#### Problem 34.2: Second-Order Settling Time and Peak Calculation
A robot arm joint has closed-loop transfer function:
$$T(s) = \frac{100}{s^2 + 12 s + 100}$$
1. Find $\omega_n$ and $\zeta$.
2. Calculate the $2\%$ settling time $t_s$.
3. Calculate the percentage overshoot $\%OS$.

#### Problem 34.3: Controllability Matrix Verification
A system has matrices:
$$\mathbf{A} = \begin{bmatrix} 0 & 1 \\ -2 & -3 \end{bmatrix}, \quad \mathbf{B} = \begin{bmatrix} 0 \\ 1 \end{bmatrix}$$
1. Construct the controllability matrix $\mathcal{C}$.
2. Determine if the system is controllable.

#### Problem 34.4: LQR Control Input Evaluation
Given state $\mathbf{x} = \begin{bmatrix} 0.5 \\ -0.2 \end{bmatrix}$ and precomputed LQR gain $\mathbf{K} = \begin{bmatrix} 4.0 & 2.5 \end{bmatrix}$, compute scalar control input $u$.

---

### Complete Mathematical Solutions

#### Solution 34.1:
1. $T(s) = \frac{G(s)}{1 + G(s)} = \frac{\frac{10}{s(s+4)}}{1 + \frac{10}{s(s+4)}} = \frac{10}{s^2 + 4s + 10}$.
2. Compare with standard form $s^2 + 2\zeta\omega_n s + \omega_n^2$:
   - $\omega_n^2 = 10 \implies \omega_n = \sqrt{10} \approx 3.162\text{ rad/s}$.
   - $2\zeta\omega_n = 4 \implies \zeta = \frac{4}{2\sqrt{10}} = \frac{2}{\sqrt{10}} \approx 0.632$.
3. **Stability:** Poles are roots of $s^2 + 4s + 10 = 0 \implies s = -2 \pm j\sqrt{6}$. Real parts are negative ($-2 < 0$), so the system is **Stable**. Because $0 < \zeta < 1$, it is **Underdamped**.

#### Solution 34.2:
1. $\omega_n^2 = 100 \implies \omega_n = 10\text{ rad/s}$.
   $2\zeta\omega_n = 12 \implies \zeta = \frac{12}{20} = 0.6$.
2. $t_s \approx \frac{4}{\zeta \omega_n} = \frac{4}{0.6 \times 10} = \frac{4}{6} \approx 0.67\text{ seconds}$.
3. $\%OS = e^{-\left(\frac{0.6 \pi}{\sqrt{1 - 0.36}}\right)} \times 100\% = e^{-\left(\frac{1.8849}{0.8}\right)} \times 100\% = e^{-2.356} \times 100\% \approx 9.48\%$.

#### Solution 34.3:
1. $\mathbf{A}\mathbf{B} = \begin{bmatrix} 0 & 1 \\ -2 & -3 \end{bmatrix} \begin{bmatrix} 0 \\ 1 \end{bmatrix} = \begin{bmatrix} 1 \\ -3 \end{bmatrix}$.
   $\mathcal{C} = \begin{bmatrix} \mathbf{B} & \mathbf{A}\mathbf{B} \end{bmatrix} = \begin{bmatrix} 0 & 1 \\ 1 & -3 \end{bmatrix}$.
2. $\det(\mathcal{C}) = (0 \times -3) - (1 \times 1) = -1 \ne 0$. Rank is 2 (Full Rank).  
   **Conclusion:** The system is **Controllable**.

#### Solution 34.4:
1. $u = -\mathbf{K}\mathbf{x} = -\begin{bmatrix} 4.0 & 2.5 \end{bmatrix} \begin{bmatrix} 0.5 \\ -0.2 \end{bmatrix} = -(4.0 \times 0.5 + 2.5 \times -0.2) = -(2.0 - 0.5) = -1.5$.

#### Solution to Problem 10.1 (from Section 10):
1. $e[k] = r[k] - y[k] = 2.0 - 1.6 = 0.4\text{ rad}$.
2. $\text{integral}[k] = \text{integral}[k-1] + e[k]\Delta t = 1.5 + (0.4 \times 0.1) = 1.54\text{ rad}\cdot\text{s}$.
3. $\text{derivative}[k] = \frac{e[k] - e[k-1]}{\Delta t} = \frac{0.4 - 0.8}{0.1} = \frac{-0.4}{0.1} = -4.0\text{ rad/s}$.
4. $u_P = K_p e[k] = 4.0 \times 0.4 = 1.6\text{ V}$.  
   $u_I = K_i \text{integral}[k] = 2.0 \times 1.54 = 3.08\text{ V}$.  
   $u_D = K_d \text{derivative}[k] = 0.5 \times -4.0 = -2.0\text{ V}$.  
   $u[k] = 1.6 + 3.08 - 2.0 = 2.68\text{ V}$.
5. $u[k] = 2.68\text{ V} \le 5.0\text{ V}$, so no saturation occurs. Output is **$2.68\text{ V}$**.

---

# 35. Coding Problems

### 1. Robust C++ PID Controller Class with Anti-Windup & Low-Pass Filter 🔴 [MUST KNOW]

```cpp
#include <iostream>
#include <algorithm>

class RobustPID {
private:
    double kp_, ki_, kd_;
    double out_min_, out_max_;
    double tau_filter_; // Low-pass filter time constant for derivative

    double prev_error_{0.0};
    double prev_measurement_{0.0};
    double integral_{0.0};
    double filtered_derivative_{0.0};

public:
    RobustPID(double kp, double ki, double kd, double out_min, double out_max, double tau = 0.02)
        : kp_(kp), ki_(ki), kd_(kd), out_min_(out_min), out_max_(out_max), tau_filter_(tau) {}

    double update(double setpoint, double measurement, double dt) {
        if (dt <= 0.0) return 0.0;

        double error = setpoint - measurement;

        // 1. Proportional Term
        double p_term = kp_ * error;

        // 2. Derivative on Measurement with First-Order Low-Pass Filter
        // d(measurement)/dt instead of d(error)/dt prevents derivative kick
        double raw_derivative = -(measurement - prev_measurement_) / dt;
        double alpha = dt / (tau_filter_ + dt);
        filtered_derivative_ = alpha * raw_derivative + (1.0 - alpha) * filtered_derivative_;
        double d_term = kd_ * filtered_derivative_;

        // 3. Unconstrained Output Calculation
        double u_unconstrained = p_term + (integral_ + error * dt) * ki_ + d_term;

        // 4. Actuator Output Clamping & Conditional Anti-Windup
        double u_clamped = std::clamp(u_unconstrained, out_min_, out_max_);

        if (u_unconstrained == u_clamped) {
            integral_ += error * dt; // Only integrate if NOT saturated
        } else if ((error > 0 && u_unconstrained < out_min_) || (error < 0 && u_unconstrained > out_max_)) {
            integral_ += error * dt; // Integrate if error works to unwind saturation
        }

        double total_output = p_term + (ki_ * integral_) + d_term;
        total_output = std::clamp(total_output, out_min_, out_max_);

        prev_error_ = error;
        prev_measurement_ = measurement;
        return total_output;
    }

    void reset() {
        prev_error_ = 0.0;
        prev_measurement_ = 0.0;
        integral_ = 0.0;
        filtered_derivative_ = 0.0;
    }
};
```

---

### 2. Python Pure Pursuit Trajectory Tracking Implementation 🔴 [MUST KNOW]

```python
import math
import numpy as np
from typing import List, Tuple

class PurePursuitTracker:
    def __init__(self, wheelbase: float = 0.65, lookahead_gain: float = 0.5, min_lookahead: float = 0.5):
        self.L = wheelbase
        self.k_v = lookahead_gain
        self.L_min = min_lookahead

    def get_steering_command(self, 
                             robot_pose: Tuple[float, float, float], # (x, y, yaw)
                             current_v: float, 
                             path: List[Tuple[float, float]]) -> Tuple[float, float]:
        rx, ry, ryaw = robot_pose
        
        # 1. Dynamic Lookahead Distance
        L_d = max(self.L_min, self.k_v * current_v)
        
        # 2. Find nearest waypoint that is at least L_d away
        target_pt = None
        for px, py in path:
            dist = math.hypot(px - rx, py - ry)
            if dist >= L_d:
                target_pt = (px, py)
                break
                
        if target_pt is None:
            target_pt = path[-1] # Target goal if near end
            
        # 3. Transform target into Robot Local Frame
        dx = target_pt[0] - rx
        dy = target_pt[1] - ry
        
        # Local Y offset (lateral error)
        local_y = -math.sin(ryaw) * dx + math.cos(ryaw) * dy
        actual_dist = math.hypot(dx, dy)
        
        if actual_dist < 1e-3:
            return 0.0, 0.0
            
        # 4. Pure Pursuit Curvature Formula: kappa = 2 * y_local / (L_d^2)
        curvature = (2.0 * local_y) / (actual_dist ** 2)
        steering_angle = math.atan(curvature * self.L)
        
        return current_v, steering_angle
```

---

# 36. Control System Cheat Sheet

```
+-----------------------------------+---------------------------------------------------+---------------------------------------------+
| Concept                           | Formula / Governing Equation                      | Physical / Robotics Meaning                 |
+-----------------------------------+---------------------------------------------------+---------------------------------------------+
| PID Control                       | u(t) = Kp e + Ki ∫e dt + Kd de/dt                 | P=Present error, I=Past offset, D=Future lag|
| Closed-Loop Transfer Function     | T(s) = G(s) / (1 + G(s)H(s))                      | System transfer ratio under feedback        |
| Second-Order Denominator          | s^2 + 2ζω_n s + ω_n^2                             | Defines damping (ζ) and response speed (ω_n)|
| Settling Time (±2%)               | t_s ≈ 4 / (ζ ω_n)                                 | Time to remain within 2% of setpoint        |
| Percentage Overshoot (%OS)        | %OS = exp(-ζπ / sqrt(1-ζ^2)) * 100                | Peak height over setpoint due to momentum   |
| State-Space Model                 | x_dot = A x + B u,  y = C x + D u                 | Time-domain dynamic vector equations        |
| Controllability Matrix            | C = [ B  AB  A^2 B ... A^(n-1)B ]                 | Rank n ensures states are reachable         |
| LQR Cost Function                 | J = ∫ (x^T Q x + u^T R u) dt                      | Quadratic trade-off of state error vs energy|
| Pure Pursuit Steering             | δ = arctan( 2 L sin(α) / L_d )                    | Circular arc geometry to lookahead point    |
| Differential Drive Twist          | v = (v_R + v_L)/2,  ω = (v_R - v_L)/L             | Body velocity from wheel velocities         |
+-----------------------------------+---------------------------------------------------+---------------------------------------------+
```

---

# 37. 30-Minute Pre-Interview Revision

1. **Stability:** Continuous LTI is stable iff **all poles have $\text{Re}(s) < 0$ (Left-Half Plane)**. Discrete LTI is stable iff **all poles $|z| < 1$ (inside unit circle)**.
2. **PID Roles:** $K_p$ speeds response but leaves steady-state error; $K_i$ eliminates steady-state error but risks windup and overshoot; $K_d$ adds damping and arrests overshoot but amplifies sensor noise.
3. **Anti-Windup:** Must be used on all physical systems to prevent integrator explosion during actuator saturation.
4. **Cascade Rule:** Inner loops (Current @ 10 kHz) must be faster than middle loops (Velocity @ 500 Hz), which must be faster than outer loops (Position @ 50 Hz).
5. **LQR vs MPC:** LQR gives optimal linear state feedback analytically ($u = -\mathbf{K}\mathbf{x}$), but cannot enforce inequality constraints. MPC solves numerical optimization online, strictly enforcing actuator limits ($\mathbf{u}_{\min} \le \mathbf{u} \le \mathbf{u}_{\max}$) and state bounds over a receding prediction horizon $N$.
6. **Pure Pursuit:** Curvature $\kappa = \frac{2 y_{\text{local}}}{L_d^2}$. Large lookahead $L_d$ stabilizes tracking at high speed but cuts corners. Small $L_d$ tracks aggressively but oscillates.

---

# 38. Mock Interview Readiness Test

Attempt all questions before reviewing the solutions in the collapsed section below.

### Conceptual Questions (10 Questions)
1. Why does pure proportional control fail to bring a drone to a stationary hover without steady-state altitude error?
2. What is the fundamental difference between an underdamped ($\zeta < 1$) and an overdamped ($\zeta > 1$) system in terms of pole locations?
3. Explain why increasing derivative gain $K_d$ can cause high-frequency motor chattering.
4. What is the difference between feedforward control and feedback control in terms of phase lag and disturbance rejection?
5. Why are the inner loops of a cascade controller tuned before the outer loops?
6. What mathematical condition must the matrix $\mathbf{R}$ satisfy in an LQR formulation?
7. How does Model Predictive Control handle state constraints that LQR cannot?
8. In differential drive kinematics, why can a robot not translate instantaneously in the lateral direction (along its wheel axle)?
9. What is the difference between derivative on error versus derivative on measurement?
10. What is aliasing in digital control and how is it prevented in hardware?

---

### Mathematical Problems (10 Problems)
11. Given the open-loop plant $G(s) = \frac{4}{s + 2}$ with unity feedback, compute the closed-loop pole and determine the time constant $\tau$.
12. A system has closed-loop transfer function $T(s) = \frac{25}{s^2 + 8s + 25}$. Compute $\omega_n$, $\zeta$, and the peak time $t_p$.
13. A PID controller has $K_p = 2, K_i = 1, K_d = 0.5, \Delta t = 0.2\text{ s}$. Given $e[k] = 1.0, e[k-1] = 0.5$, and $\text{integral}[k-1] = 2.0$, compute the unconstrained output $u[k]$.
14. Check the controllability of: $\mathbf{A} = \begin{bmatrix} 1 & 0 \\ 0 & 2 \end{bmatrix}, \mathbf{B} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$.
15. For differential drive wheelbase $L = 0.5\text{ m}$, calculate the required left and right wheel velocities to achieve $v = 1.0\text{ m/s}$ and $\omega = 2.0\text{ rad/s}$.
16. Given state-space matrix $\mathbf{A} = \begin{bmatrix} 0 & 1 \\ -6 & -5 \end{bmatrix}$, find the open-loop system poles.
17. In a Pure Pursuit tracker with wheelbase $L = 1.0\text{ m}$ and lookahead distance $L_d = 2.0\text{ m}$, the lookahead point is at local coordinate $(x_l = 1.732, y_l = 1.0)$. Compute the steering angle $\delta$.
18. Given LQR state $\mathbf{x} = \begin{bmatrix} 1 \\ 2 \end{bmatrix}$ and gain $\mathbf{K} = \begin{bmatrix} 2 & 3 \end{bmatrix}$, compute control $u$.
19. Compute the percentage overshoot $\%OS$ of a second-order system with $\zeta = \frac{1}{\sqrt{2}} \approx 0.707$.
20. A discrete-time system has pole $z = 1.05$. Is it stable?

---

<details>
<summary><b>🔍 Click to Expand Complete Mock Test Solutions</b></summary>

### Conceptual Answers
1. **Need for Non-Zero Lift:** To hover against gravity, the rotors must produce thrust equal to $m g$. Under pure P-control, $u = K_p e$. If error were zero, thrust would be zero and the drone would fall. Thus, a persistent steady-state error $e_{ss} = \frac{m g}{K_p}$ is required to generate the hover thrust.
2. **Pole Locations:** Underdamped systems have complex conjugate poles with non-zero imaginary parts ($s = -\sigma \pm j\omega_d$). Overdamped systems have two distinct, purely real negative poles on the real axis ($s = -\sigma_1, -\sigma_2$).
3. **Noise Amplification:** Differentiation multiplies signals by frequency ($j\omega$). High-frequency electrical or quantization noise in sensor streams has huge derivatives, causing large, rapid fluctuations in $u_D$ that chatter the motor coils.
4. **Phase Lag & Disturbance:** Feedforward acts proactively based on setpoint/model with zero phase lag, but cannot reject unmodeled disturbances. Feedback acts reactively on error with inherent phase lag, but eliminates steady-state disturbances.
5. **Inner Loop Convergence:** The outer loop assumes that when it commands a setpoint (e.g. target velocity), the inner loop achieves that setpoint almost instantaneously. If the inner loop is not tuned and stabilized first, the entire cascade goes unstable.
6. **Positive Definiteness:** $\mathbf{R}$ must be strictly **Positive Definite** ($\mathbf{R} \succ 0$, all eigenvalues $> 0$) to ensure that any non-zero control input incurs a strictly positive penalty and guarantees that $\mathbf{R}^{-1}$ exists.
7. **Constrained Quadratic Programming:** MPC casts control as an online optimization with explicit mathematical inequality constraints ($\mathbf{A}_{\text{ineq}}\mathbf{u} \le \mathbf{b}_{\text{ineq}}$), whereas LQR assumes unconstrained state space.
8. **Non-Holonomic Constraint:** The wheels roll without slipping along the forward heading direction but cannot slide sideways ($\dot{y}_{\text{local}} = 0$).
9. **Eliminating Derivative Kick:** Derivative on error differentiates $(r - y)$, producing an infinite spike during step changes in setpoint $r$. Derivative on measurement differentiates $-y$, keeping the derivative signal smooth.
10. **Hardware Anti-Aliasing:** High-frequency noise folding down into the control bandwidth. Prevented via an analog low-pass RC filter before the Analog-to-Digital Converter (ADC).

---

### Mathematical Solutions
11. $T(s) = \frac{4/(s+2)}{1 + 4/(s+2)} = \frac{4}{s + 6}$. Closed-loop pole at $s = -6$. Time constant $\tau = \frac{1}{6} \approx 0.167\text{ s}$.
12. $\omega_n^2 = 25 \implies \omega_n = 5\text{ rad/s}$. $2\zeta\omega_n = 8 \implies \zeta = \frac{8}{10} = 0.8$.  
    $\omega_d = \omega_n \sqrt{1 - \zeta^2} = 5 \sqrt{1 - 0.64} = 5(0.6) = 3.0\text{ rad/s}$.  
    $t_p = \frac{\pi}{\omega_d} = \frac{\pi}{3} \approx 1.047\text{ s}$.
13. $e[k] = 1.0$. $\text{integral}[k] = 2.0 + (1.0 \times 0.2) = 2.2$. $\text{derivative}[k] = \frac{1.0 - 0.5}{0.2} = 2.5$.  
    $u[k] = (2 \times 1.0) + (1 \times 2.2) + (0.5 \times 2.5) = 2.0 + 2.2 + 1.25 = \mathbf{5.45}$.
14. $\mathbf{B} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}, \mathbf{AB} = \begin{bmatrix} 1 & 0 \\ 0 & 2 \end{bmatrix} \begin{bmatrix} 1 \\ 0 \end{bmatrix} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$.  
    $\mathcal{C} = \begin{bmatrix} 1 & 1 \\ 0 & 0 \end{bmatrix}$. $\det(\mathcal{C}) = 0$. Rank is 1 ($< 2$). **Uncontrollable** (State 2 cannot be influenced).
15. $v_R = v + \frac{\omega L}{2} = 1.0 + \frac{2.0 \times 0.5}{2} = 1.0 + 0.5 = \mathbf{1.5\text{ m/s}}$.  
    $v_L = v - \frac{\omega L}{2} = 1.0 - 0.5 = \mathbf{0.5\text{ m/s}}$.
16. $\det(s\mathbf{I} - \mathbf{A}) = \det\begin{bmatrix} s & -1 \\ 6 & s + 5 \end{bmatrix} = s(s + 5) + 6 = s^2 + 5s + 6 = (s + 2)(s + 3) = 0$.  
    Poles are at $s = -2$ and $s = -3$.
17. $\kappa = \frac{2 y_l}{L_d^2} = \frac{2(1.0)}{2.0^2} = \frac{2.0}{4.0} = 0.5\text{ m}^{-1}$.  
    $\delta = \arctan(\kappa L) = \arctan(0.5 \times 1.0) = \arctan(0.5) \approx \mathbf{0.4636\text{ rad} \approx 26.57^\circ}$.
18. $u = -\mathbf{K}\mathbf{x} = -\begin{bmatrix} 2 & 3 \end{bmatrix} \begin{bmatrix} 1 \\ 2 \end{bmatrix} = -(2 \times 1 + 3 \times 2) = -(2 + 6) = \mathbf{-8}$.
19. $\zeta = \frac{1}{\sqrt{2}} \implies \sqrt{1 - \zeta^2} = \frac{1}{\sqrt{2}}$.  
    $\%OS = e^{-\frac{\pi (1/\sqrt{2})}{1/\sqrt{2}}} \times 100\% = e^{-\pi} \times 100\% \approx e^{-3.14159} \times 100\% \approx \mathbf{4.32\%}$.
20. **Unstable.** In discrete-time systems, stability requires all poles strictly inside the unit circle ($|z| < 1$). Here $|1.05| > 1$, so impulse response explodes.

</details>
