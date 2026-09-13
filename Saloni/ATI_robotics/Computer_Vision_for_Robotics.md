# Computer Vision for Robotics & Autonomous Systems: Master Technical Interview Guide
**Role Target:** Robotics Intern – Autonomy (ATI Robotics)  
**Focus Areas:** Pinhole Camera Geometry, Camera Calibration, Epipolar Geometry, Stereo Vision, Feature Detection & Matching (ORB/SIFT), Homography, Visual Odometry (VO), Visual SLAM (ORB-SLAM3/VIO), Deep Learning Perception (YOLO/Segmentation), Camera-LiDAR-IMU Sensor Fusion, ROS 2 Vision Pipelines  
**Level:** Comprehensive Foundational Theory to Mathematical, Algorithmic & Systems-Level Interview Mastery  

---

## 📌 Categorization Legend
- 🔴 **[MUST KNOW]**: Mandatory for passing the technical interview. High likelihood of mathematical derivations, projection matrix calculations, whiteboard sketches, or live coding.
- 🟡 **[GOOD TO KNOW]**: Demonstrates engineering depth, multi-view geometry rigor, and production deployment competence; distinguishes top candidates.
- 🔵 **[ADVANCED / OPTIONAL]**: Lie algebra ($\mathfrak{so}(3)/\mathfrak{se}(3)$) manifold optimization, direct sparse odometry (DSO), photometric bundle adjustment, and custom TensorRT CUDA plugins.
- ⚠️ **[INTERVIEW TRAP]**: Common misconceptions, mathematical gotchas, and edge cases frequently probed by interviewers.
- 🤖 **[ROBOTICS CONNECTION]**: Direct application to autonomous industrial tuggers (e.g., ATI Sherpa), warehouse AMRs, visual dockers, obstacle avoidance, and pallet detection.

---

# Table of Contents
1. [Computer Vision in Robotics](#1-computer-vision-in-robotics)
2. [Image Fundamentals & Pixel Coordinate Systems](#2-image-fundamentals)
3. [Image Formation & Pinhole Camera Model](#3-image-formation)
4. [Camera Coordinate Frames & Spatial Transformations](#4-camera-coordinate-frames)
5. [Camera Calibration & Lens Distortion](#5-camera-calibration)
6. [OpenCV Fundamentals (C++ & Python)](#6-opencv-fundamentals)
7. [Classical Image Processing & Filtering](#7-image-processing)
8. [Feature Detection (Corners, Edges, Blobs)](#8-feature-detection)
9. [Feature Descriptors & Matching Metrics](#9-feature-descriptors)
10. [Feature Matching & Outlier Rejection](#10-feature-matching)
11. [Planar Homography & Perspective Warping](#11-homography)
12. [Epipolar Geometry & Two-View Geometry](#12-epipolar-geometry)
13. [Stereo Vision & Disparity-to-Depth Triangulation](#13-stereo-vision)
14. [Depth Cameras (RGB-D, ToF, Structured Light)](#14-depth-cameras)
15. [Optical Flow & Motion Estimation](#15-optical-flow)
16. [Object Detection & Bounding Box Regressors (YOLO)](#16-object-detection)
17. [Semantic & Instance Segmentation](#17-semantic-segmentation)
18. [Multi-Object Tracking (SORT / DeepSORT)](#18-object-tracking)
19. [Perspective-n-Point (PnP) Pose Estimation](#19-pose-estimation)
20. [PnP Mathematical Formulations](#20-perspective-n-point-mathematics)
21. [Visual Odometry (VO) Pipelines](#21-visual-odometry)
22. [Visual SLAM Systems](#22-visual-slam)
23. [Bundle Adjustment (BA) & Non-Linear Optimization](#23-bundle-adjustment)
24. [Camera + LiDAR Sensor Fusion](#24-lidar--camera-fusion)
25. [Visual-Inertial Odometry (VIO) & Camera-IMU Fusion](#25-camera--imu-fusion)
26. [Machine Learning for Robotics Vision](#26-machine-learning-for-robotics-vision)
27. [Convolutional Neural Network (CNN) Mathematics](#27-cnn-mathematics)
28. [Edge AI Model Deployment (TensorRT & ONNX)](#28-vision-model-deployment)
29. [Real-Time Computer Vision Systems](#29-real-time-computer-vision)
30. [End-to-End Perception Pipeline Architecture](#30-vision-pipeline-design)
31. [ROS 2 + OpenCV Integration (`cv_bridge`)](#31-ros2--opencv)
32. [C++ Computer Vision Coding Problems](#32-c-computer-vision-coding)
33. [Python Computer Vision Coding Problems](#33-python-computer-vision-coding)
34. [15+ Hand-Solvable Numerical Problems](#34-numerical-interview-problems)
35. [15 Whiteboard Problems & Visual Derivations](#35-whiteboard-problems)
36. [20 Real-World Robotics Vision Debugging Scenarios](#36-debugging-scenarios)
37. [Vision Failure Modes in Field Robotics](#37-computer-vision-failure-modes)
38. [Sensor Comparison: Vision vs. LiDAR vs. Radar](#38-vision-vs-lidar-vs-radar)
39. [Computer Vision Mathematics Cheat Sheet](#39-mathematics-cheat-sheet)
40. [Essential Equations Formula Sheet](#40-essential-equations)
41. [System Design: AMR Perception Subsystem](#41-system-design-interview)
42. [60+ Core Computer Vision Interview Questions](#42-high-pressure-interview-questions)
43. [15 High-Pressure Interviewer Follow-Up Chains](#43-high-pressure-follow-ups)
44. ["Explain It in 30 Seconds" (Elevator Pitches)](#44-explain-it-in-30-seconds)
45. [Mistakes That Make Candidates Look Weak](#45-common-interview-traps)
46. [ATI Robotics Specific Vision Questions](#46-ati-robotics-oriented-questions)
47. [Integrated Autonomy Multi-Module Problems](#47-integrated-autonomy-problems)
48. [45-Minute Mini Coding Interview Simulation](#48-practical-coding-interview)
49. [Quick Revision Cheat Sheet](#49-quick-revision-cheat-sheet)
50. [30-Minute Pre-Interview Revision Plan](#50-30-minute-final-revision)
51. [Mock Interview Readiness Test (with Complete Answer Key & Rubric)](#51-final-readiness-test)

---

# 1. Computer Vision in Robotics

### What is Computer Vision in Robotics? 🔴 [MUST KNOW]
In classical software, computer vision processes static digital imagery. In **autonomous robotics**, computer vision is the **active, real-time extraction of geometric, spatial, and semantic meaning** from dynamic optical data to enable state estimation, obstacle detection, scene understanding, and closed-loop motion control.

---

### The End-to-End Autonomy Perception Pipeline 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
|                         AUTONOMOUS VISION PIPELINE                                 |
+------------------------------------------------------------------------------------+
|                                                                                    |
|  1. HARDWARE SENSOR    [ CMOS Global Shutter RGB / Stereo / RGB-D Camera ]         |
|                             │ (Raw Bayer / YUV Pixel Stream @ 30 FPS)              |
|                             ▼                                                      |
|  2. ACQUISITION        [ V4L2 Driver / ROS 2 image_transport / cv_bridge ]        |
|                             │ (cv::Mat BGR / Grayscale Matrix + Stamped Time)      |
|                             ▼                                                      |
|  3. PREPROCESSING      [ Lens Undistortion (K, D) / Rectification / Bilateral Fltr]|
|                             │                                                      |
|                             ▼                                                      |
|  4. FEATURE EXTRACTION [ FAST / ORB Keypoints ]   OR   [ Deep Tensor (YOLOv8) ]    |
|                             │                                   │                  |
|                             ▼                                   ▼                  |
|  5. GEOMETRIC / SEMANTIC[ Epipolar Matching / PnP ]   [ 2D/3D Bounding Boxes / Mask|
|                             │                                   │                  |
|                             ▼                                   ▼                  |
|  6. 3D STATE ESTIMATE  [ Camera Ego-Motion ΔT ]        [ Object Distance & TrackID]|
|                             │                                   │                  |
|                             ▼                                   ▼                  |
|  7. AUTONOMY FUSION    [ EKF State Estimator / SLAM ] ─> [ Local Costmap Obstacles]|
|                             │                                   │                  |
|                             ▼                                   ▼                  |
|  8. PLANNING & CONTROL [ Trajectory Planner (TEB) ]  ──> [ Velocity Cmd /cmd_vel ] |
|                                                                                    |
+------------------------------------------------------------------------------------+
```

---

# 2. Image Fundamentals

### Pixels, Color Spaces & Memory Layouts 🔴 [MUST KNOW]
- **Image as a Discrete Function:** An image is a 2D matrix $I(u, v)$ mapping pixel coordinates $(u, v)$ to intensity or color tuples.
- **Coordinate Conventions:**
  - **Origin $(0, 0)$:** Top-Left corner of the image.
  - **Horizontal Axis ($u$ or $x$):** Columns ($0 \le u < \text{Width}$).
  - **Vertical Axis ($v$ or $y$):** Rows ($0 \le v < \text{Height}$).
  - **Array Indexing in C++/NumPy:** `image[row, col]` $\to$ `image[y, x]`.

```
(0,0) ────── u / Column / Width ──────►
  │
  │     Pixel P(u, v) = [B, G, R]
  │           • (x=u, y=v)
  v / Row / Height
  │
  ▼
```

- **Color Spaces:**
  - **BGR (OpenCV Default):** Blue-Green-Red 3-channel format ($8\text{-bit}$ per channel, range $[0, 255]$).
  - **Grayscale:** Single-channel luminance $Y = 0.299R + 0.587G + 0.114B$. Preferred for feature detection (FAST, ORB) to reduce compute by $3\times$.
  - **HSV (Hue, Saturation, Value):** Decouples chromatic color information (Hue) from lighting intensity (Value). **Mandatory for color thresholding under varying ambient light.**

---

# 3. Image Formation

### The Pinhole Camera Model 🔴 [MUST KNOW]
Projects a 3D point in the Camera Optical Frame $\mathbf{P}_c = [X_c, Y_c, Z_c]^T$ onto a 2D pixel coordinate $\mathbf{p} = [u, v]^T$ on the image plane located at focal length $f$.

```
         Y_camera
            ▲
            │       3D Point P(X, Y, Z)
            │           •
            │          /
            │         /
            │   Image Plane (Z = f)
            │      ┌─────┐
            │      │  • p(u, v)
            │      └─────┘
            └────────────► Z_camera (Optical Axis)
           /
          /
         ▼ X_camera
```

---

### Mathematical Derivation of Projection 🔴 [MUST KNOW]
Using similar triangles:

$$\frac{x_{\text{img}}}{f_x} = \frac{X_c}{Z_c} \implies x_{\text{img}} = f_x \frac{X_c}{Z_c}, \qquad \frac{y_{\text{img}}}{f_y} = \frac{Y_c}{Z_c} \implies y_{\text{img}} = f_y \frac{Y_c}{Z_c}$$

Shifting the origin from the optical center to the top-left pixel corner via the **Principal Point offset ($c_x, c_y$)**:

$$u = f_x \frac{X_c}{Z_c} + c_x, \qquad v = f_y \frac{Y_c}{Z_c} + c_y$$

---

### The Camera Intrinsic Matrix ($\mathbf{K}$) 🔴 [MUST KNOW]
In homogeneous matrix notation:

$$\begin{bmatrix} u \\ v \\ 1 \end{bmatrix} \sim \mathbf{K} \begin{bmatrix} X_c \\ Y_c \\ Z_c \end{bmatrix} \implies Z_c \begin{bmatrix} u \\ v \\ 1 \end{bmatrix} = \begin{bmatrix} f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} X_c \\ Y_c \\ Z_c \end{bmatrix}$$

- $f_x = \frac{F}{\text{pixel\_size}_x}, f_y = \frac{F}{\text{pixel\_size}_y}$: Focal length in pixel units.
- $c_x, c_y$: Coordinates of the principal point (intersection of optical axis with sensor, ideally $\approx (\frac{\text{Width}}{2}, \frac{\text{Height}}{2})$).

---

# 4. Camera Coordinate Frames

### ROS Standard Optical vs. Body Coordinate Conventions 🔴 [MUST KNOW]

```
+-----------------------------------+------------------------------------+
| Camera Optical Frame (OpenCV/ROS) | Robot Body Frame (base_link) (REP-105)|
+-----------------------------------+------------------------------------+
| +Z Axis: Points FORWARD (Out of lens)| +X Axis: Points FORWARD (Driving dir)|
| +X Axis: Points to the RIGHT      | +Y Axis: Points to the LEFT        |
| +Y Axis: Points DOWNWARD          | +Z Axis: Points UPWARD (Skyward)   |
+-----------------------------------+------------------------------------+
```

---

### World-to-Pixel Transformation Chain 🔴 [MUST KNOW]

$$\mathbf{p}_{\text{pixel}} = \mathbf{K} \cdot [\mathbf{R} \mid \mathbf{t}] \cdot \mathbf{P}_{\text{world}} = \mathbf{K} \cdot \mathbf{T}_{\text{world}}^{\text{camera}} \cdot \mathbf{P}_{\text{world}}$$

where $[\mathbf{R} \mid \mathbf{t}]$ is the **Extrinsic Calibration Matrix** ($3\times4$) representing the rotation $\mathbf{R} \in SO(3)$ and translation $\mathbf{t} \in \mathbb{R}^3$ of the world relative to the camera optical center.

---

# 5. Camera Calibration

### Lens Distortion Models (Brown-Conrady) 🔴 [MUST KNOW]
Real physical glass lenses introduce optical distortions:

```
    Pincushion Distortion (k1 > 0)          Barrel Distortion (k1 < 0)
              ┌───┐                                 .---.
             │     │                               (     )
              └───┘                                 '---'
```

1. **Radial Distortion (Curvature of glass lens):**
   $$x_{\text{dist}} = x (1 + k_1 r^2 + k_2 r^4 + k_3 r^6), \qquad y_{\text{dist}} = y (1 + k_1 r^2 + k_2 r^4 + k_3 r^6)$$
   where $r^2 = x^2 + y^2$.
2. **Tangential Distortion (Lens not perfectly parallel to CMOS sensor plane):**
   $$x_{\text{tan}} = 2 p_1 x y + p_2 (r^2 + 2x^2), \qquad y_{\text{tan}} = p_1 (r^2 + 2y^2) + 2 p_2 x y$$
- **Distortion Vector:** $\mathbf{D} = [k_1, k_2, p_1, p_2, k_3]$.

---

### Reprojection Error 🔴 [MUST KNOW]
The quality of a camera calibration is evaluated using the Mean Reprojection Error:

$$\text{Error} = \frac{1}{N \cdot M} \sum_{i=1}^N \sum_{j=1}^M \|\mathbf{p}_{ij} - \hat{\mathbf{p}}(\mathbf{K}, \mathbf{D}, \mathbf{R}_i, \mathbf{t}_i, \mathbf{P}_j)\|^2$$

A production-grade calibration should achieve a root-mean-square (RMS) reprojection error of **$< 0.5\text{ pixels}$**.

---

# 6. OpenCV Fundamentals

### Core C++ vs. Python Syntax Patterns 🔴 [MUST KNOW]

```cpp
// C++ (High Performance, Multi-Threaded Real-Time Node)
#include <opencv2/opencv.hpp>

cv::Mat image = cv::imread("frame.jpg", cv::IMREAD_COLOR);
cv::Mat gray, blurred, edges;

// 1. Color Conversion
cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

// 2. Gaussian Blur (5x5 kernel, sigma=1.5)
cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.5);

// 3. Canny Edge Detection (Thresholds: 50, 150)
cv::Canny(blurred, edges, 50, 150);
```

```python
# Python 3 (NumPy Vectorized Prototype)
import cv2
import numpy as np

image = cv2.imread("frame.jpg", cv2.IMREAD_COLOR)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
blurred = cv2.GaussianBlur(gray, (5, 5), 1.5)
edges = cv2.Canny(blurred, 50, 150)
```

---

# 7. Image Processing

### Spatial Filters & Edge Detectors 🔴 [MUST KNOW]
- **Gaussian Filter:** Low-pass filter for removing high-frequency white noise before edge detection:
  $$G(x, y) = \frac{1}{2\pi\sigma^2} \exp\left(-\frac{x^2 + y^2}{2\sigma^2}\right)$$
- **Sobel Operator:** Computes discrete spatial image gradients ($G_x, G_y$):
  $$\mathbf{S}_x = \begin{bmatrix} -1 & 0 & +1 \\ -2 & 0 & +2 \\ -1 & 0 & +1 \end{bmatrix}, \quad \mathbf{S}_y = \begin{bmatrix} -1 & -2 & -1 \\ 0 & 0 & 0 \\ +1 & +2 & +1 \end{bmatrix}$$
  $$\text{Magnitude } G = \sqrt{G_x^2 + G_y^2}, \qquad \text{Direction } \theta = \arctan2(G_y, G_x)$$
- **Canny Edge Detection Pipeline (4 Stages):**
  1. Gaussian Smoothing $\to$ 2. Sobel Gradient Calculation $\to$ 3. Non-Maximum Suppression (thins edges to 1-pixel width) $\to$ 4. Hysteresis Thresholding (low/high thresholding with edge tracking).

---

# 8. Feature Detection

### Classical Feature Detectors Comparison 🔴 [MUST KNOW]

```
+-------------------+----------------------+--------------------+--------------------+----------------------------------+
| Detector          | Key Mechanism        | Invariance Traits  | Compute Speed      | Robotics Use Case                |
+-------------------+----------------------+--------------------+--------------------+----------------------------------+
| Harris Corner     | Auto-correlation     | Rotation           | Fast (~5 ms)       | Simple visual odometry           |
| FAST              | Circle pixel test (9)| None (Scale/Rot No)| Blazing (< 1 ms)   | Real-time VO tracking front-end  |
| SIFT              | Difference of Gauss. | Rotation, Scale    | Heavy (~50 ms)     | High-accuracy mapping / Loop cl. |
| ORB (FAST+BRIEF)  | Oriented FAST        | Rotation, Scale    | Very Fast (~3 ms)  | Industry Standard for vSLAM (ORB3|
+-------------------+----------------------+--------------------+--------------------+----------------------------------+
```

---

# 9. Feature Descriptors

### Feature Descriptors: Floating Point vs. Binary 🔴 [MUST KNOW]
- **SIFT Descriptor:** 128-dimensional floating-point vector of localized gradient histograms. Distance measured via **Euclidean Distance ($L_2$ Norm)**. Expensive to compare ($O(128)$ float multiplications).
- **ORB Descriptor (BRIEF):** 256-bit binary string representing pairwise pixel intensity comparisons. Distance measured via **Hamming Distance** (number of differing bits):
  $$\text{HammingDist}(\mathbf{d}_1, \mathbf{d}_2) = \text{popcount}(\mathbf{d}_1 \oplus \mathbf{d}_2)$$
  Executed via a **single CPU instruction (`__builtin_popcount` / `POPCNT`) in $< 1\text{ nanosecond}$!**

---

# 10. Feature Matching

### Robust Matching with Lowe's Ratio Test & RANSAC 🔴 [MUST KNOW]

```python
import cv2

def match_features_orb(desc1, desc2, ratio_thresh=0.75):
    # Hamming distance brute-force matcher for binary descriptors
    bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=False)
    # k=2 returns the best 2 matches for each query descriptor
    raw_matches = bf.knnMatch(desc1, desc2, k=2)
    
    # Lowe's Ratio Test: Discards ambiguous matches (e.g. repeated patterns/textures)
    good_matches = []
    for m, n in raw_matches:
        if m.distance < ratio_thresh * n.distance:
            good_matches.append(m)
            
    return good_matches
```

---

# 11. Homography

### Planar Projective Transformations 🔴 [MUST KNOW]
A **Homography ($\mathbf{H} \in \mathbb{R}^{3\times3}$)** is an invertible transformation mapping points from one planar surface to another:

$$\mathbf{p}_2 \sim \mathbf{H} \mathbf{p}_1 \implies \begin{bmatrix} u_2 \\ v_2 \\ 1 \end{bmatrix} \sim \begin{bmatrix} h_{11} & h_{12} & h_{13} \\ h_{21} & h_{22} & h_{23} \\ h_{31} & h_{32} & h_{33} \end{bmatrix} \begin{bmatrix} u_1 \\ v_1 \\ 1 \end{bmatrix}$$

- **Degrees of Freedom:** 8 (since $\mathbf{H}$ is defined up to an arbitrary scale factor).
- **Minimum Correspondences Required:** 4 non-collinear point pairs ($2\text{ equations per point pair} \to 8\text{ independent equations}$).
- **Robotics Use Case:** **Inverse Perspective Mapping (IPM / Bird's-Eye View)**: Warping angled ground-plane camera footage into a metric top-down grid for local costmaps.

---

# 12. Epipolar Geometry

### Two-View Geometry & The Essential Matrix 🔴 [MUST KNOW]

```
Left Camera Optical Center (O_L)                  Right Camera Optical Center (O_R)
        •──────────────────── Baseline B ────────────────────•
       / \                                                  / \
      /   \                                                /   \
     /     \  Epipolar Line l_L               Epipolar Line /     \
    /       • p_L                                       p_R •      \
   /         \                                             /        \
  /           \                                           /          \
 /             ▼                                         ▼            \
•───────────────•───────────────────────────────────────•──────────────•
                3D World Landmark Point P
```

1. **Epipolar Constraint:**
   $$\mathbf{x}_R^T \mathbf{E} \, \mathbf{x}_L = 0 \quad (\text{Normalized Metric Coordinates})$$
   $$\mathbf{p}_R^T \mathbf{F} \, \mathbf{p}_L = 0 \quad (\text{Pixel Coordinates})$$
2. **Essential Matrix ($\mathbf{E}$):** Relates calibrated camera rays via relative rotation $\mathbf{R}$ and translation $\mathbf{t}$:
   $$\mathbf{E} = [\mathbf{t}]_\times \mathbf{R} = \mathbf{K}_R^T \mathbf{F} \mathbf{K}_L$$
   where $[\mathbf{t}]_\times$ is the skew-symmetric cross-product matrix of translation vector $\mathbf{t} = [t_x, t_y, t_z]^T$:
   $$[\mathbf{t}]_\times = \begin{bmatrix} 0 & -t_z & t_y \\ t_z & 0 & -t_x \\ -t_y & t_x & 0 \end{bmatrix}$$
3. **Fundamental Matrix ($\mathbf{F}$):** Operates on raw, uncalibrated pixel coordinates.

---

# 13. Stereo Vision

### Disparity-to-Depth Mathematical Derivation 🔴 [MUST KNOW]

```
Left Camera                           Right Camera
     │                                     │
     │◄──────────── Baseline B ───────────►│
     │                                     │
     ├─── u_L ───►•                   •◄───┼─ u_R
     │             \                 /     │
     │              \               /      │
     │               \             /       │
     ▼                \           /        ▼
                       ▼         ▼
                     3D Landmark Point P(X, Y, Z)
```

For two parallel, rectified cameras with focal length $f$ and baseline $B$:

$$\frac{x_L}{f} = \frac{X + \frac{B}{2}}{Z}, \qquad \frac{x_R}{f} = \frac{X - \frac{B}{2}}{Z}$$

Subtracting the two equations:

$$\frac{x_L - x_R}{f} = \frac{B}{Z} \implies \frac{d}{f} = \frac{B}{Z}$$

$$\mathbf{Z = \frac{f \cdot B}{d}}$$

where $d = x_L - x_R$ is the **Disparity** (pixel shift between left and right views).

---

### Depth Error Characteristics ($\Delta Z \propto Z^2$) 🔴 [MUST KNOW]
Differentiating the depth equation with respect to disparity $d$:

$$\frac{\partial Z}{\partial d} = -\frac{f B}{d^2} = -\frac{Z^2}{f B} \implies |\Delta Z| \approx \frac{Z^2}{f \cdot B} |\Delta d|$$

> ⚠️ **CRITICAL ROBOTICS INSIGHT**: **Stereo depth error grows quadratically with distance ($Z^2$).**  
> At $2\text{ meters}$, stereo depth error is $\approx 1\text{ cm}$. At $20\text{ meters}$, the error degrades to $\approx 1.0\text{ meter}$! To measure distant obstacles accurately, an AMR must increase baseline $B$ or switch to LiDAR.

---

# 14. Depth Cameras

```
+--------------------+-----------------------+--------------------+---------------------+------------------------------------+
| Sensor Type        | Principle             | Lighting Limits    | Typical Range       | Robotics Application               |
+--------------------+-----------------------+--------------------+---------------------+------------------------------------+
| Passive Stereo     | Triangulation (SGBM)  | Fails in darkness  | 0.5m – 20m          | Outdoor navigation, AGVs           |
| Structured Light   | Projected IR Pattern  | Fails in sunlight  | 0.2m – 3.5m         | Indoor manipulation, pick & place  |
| Time-of-Flight(ToF)| IR Phase Shift / ToF  | High power draw    | 0.5m – 6.0m         | Fast obstacle detection, pallet ID |
| 3D Solid-State LiD.| Laser Pulse ToF       | Sunlight invariant | 0.1m – 100m         | Primary safety & 3D mapping        |
+--------------------+-----------------------+--------------------+---------------------+------------------------------------+
```

---

# 15. Optical Flow

### The Optical Flow Brightness Constancy Constraint 🔴 [MUST KNOW]
Assumes pixel brightness of a moving surface remains constant over short time $\Delta t$:

$$I(x, y, t) = I(x + \Delta x, y + \Delta y, t + \Delta t)$$

First-order Taylor expansion yields the **Optical Flow Equation**:

$$\frac{\partial I}{\partial x} u + \frac{\partial I}{\partial y} v + \frac{\partial I}{\partial t} = 0 \implies I_x u + I_y v + I_t = 0$$

- **The Aperture Problem:** 1 equation with 2 unknowns ($u, v$). Only normal motion can be resolved from a single pixel.
- **Lucas-Kanade (LK) Method:** Solves the aperture problem by assuming all pixels in a small local $N \times N$ window share the same velocity vector $(u, v)$, solving via least squares:
  $$\begin{bmatrix} u \\ v \end{bmatrix} = \left(\mathbf{A}^T \mathbf{A}\right)^{-1} \mathbf{A}^T \mathbf{b}$$

---

# 16. Object Detection

### 2D Object Detection Architecture: YOLO 🔴 [MUST KNOW]
- **Single-Stage Detectors (YOLOv8 / SSD):** Treat object detection as a single end-to-end regression problem. Image is divided into a grid; each cell predicts bounding box coordinates $(x, y, w, h)$, objectness confidence, and class probabilities in a single forward pass. Runs in **real-time ($> 60\text{ FPS}$ on Jetson GPU)**.

---

### Evaluation Metrics: IoU, Precision, Recall, mAP 🔴 [MUST KNOW]
- **Intersection over Union (IoU):**
  $$\text{IoU} = \frac{\text{Area of Overlap}}{\text{Area of Union}} = \frac{\text{Area}(B_{\text{pred}} \cap B_{\text{gt}})}{\text{Area}(B_{\text{pred}} \cup B_{\text{gt}})}$$
- **Precision & Recall:**
  $$\text{Precision} = \frac{TP}{TP + FP} \quad (\text{When detector fires, is it correct?}), \qquad \text{Recall} = \frac{TP}{TP + FN} \quad (\text{Did it find all real obstacles?})$$
- **Robotics Rule:** Autonomous safety systems prioritize **high recall** (missing an obstacle causes a physical collision, whereas a false positive merely causes a temporary stop).

---

# 17. Semantic Segmentation

### Dense Pixel-Level Classification 🔴 [MUST KNOW]
- **Semantic Segmentation:** Assigns every individual pixel a class label (Road, Drivable Free Space, Pallet, Wall, Pedestrian) without distinguishing distinct object instances.
- **Robotics Use Case:** Generating real-time **traversability costmap layers** directly from camera footage.

---

# 18. Object Tracking

### SORT / DeepSORT Multi-Object Tracking Pipeline 🔴 [MUST KNOW]

```
Camera Frame ──> [ YOLO Detector ] ──> New Bounding Boxes
                                              │
                                              ▼
[ Kalman Filter State Estimator ] ──> Predicted Box Tracks ──┐
                                                             ├──> [ Hungarian Matcher (IoU / Cosine Distance) ]
                                                             │                  │
                                                             ▼                  ▼
                                                  Matched Tracks Updated   New Tracks Created / Dead Tracks Deleted
```

---

# 19. Pose Estimation

### Perspective-n-Point (PnP) 🔴 [MUST KNOW]
Given $N$ known 3D landmark coordinates in the object frame $\mathbf{P}_i = [X_i, Y_i, Z_i]^T$ and their corresponding 2D pixel observations $\mathbf{p}_i = [u_i, v_i]^T$, find the 6-DOF camera pose $(\mathbf{R}, \mathbf{t}) \in SE(3)$ that minimizes the **Non-Linear Reprojection Error**:

$$\arg\min_{\mathbf{R}, \mathbf{t}} \sum_{i=1}^N \left\| \mathbf{p}_i - \pi\left(\mathbf{K} (\mathbf{R}\mathbf{P}_i + \mathbf{t})\right) \right\|^2$$

- **Minimum Points:** $N = 3$ points with up to 4 ambiguous solutions (P3P); $N \ge 4$ points (EPnP) for a unique algebraic solution.
- **RANSAC-PnP (`cv::solvePnPRansac`):** Essential for rejecting spurious feature matches before computing final pose.

---

# 20. Perspective-n-Point Mathematics

### Rodrigues Rotation Representation 🔴 [MUST KNOW]
In PnP solvers, 3D rotation is parameterized compactly as a $3 \times 1$ axis-angle vector $\mathbf{r} = \theta \mathbf{u}$:

$$\mathbf{R} = \mathbf{I} + \sin\theta [\mathbf{u}]_\times + (1 - \cos\theta) [\mathbf{u}]_\times^2 \quad (\text{Rodrigues Formula})$$

---

# 21. Visual Odometry

### The Monocular vs. Stereo Visual Odometry Pipeline 🔴 [MUST KNOW]

```
+------------------------------------------------------------------------------------+
|                         VISUAL ODOMETRY PIPELINE                                   |
+------------------------------------------------------------------------------------+
|  Frame k-1, Frame k ──> [ FAST Feature Detector ] ──> [ ORB Descriptor Extraction ]|
|                                                               │                    |
|                                                               ▼                    |
|  [ Feature Matching / Optical Flow ] ──> [ RANSAC Epipolar Outlier Rejection ]     |
|                                                               │                    |
|                                                               ▼                    |
|  [ PnP / Essential Matrix SVD ] ──────> [ Relative Motion (R_{k-1, k}, t_{k-1, k})]|
|                                                               │                    |
|                                                               ▼                    |
|  [ Pose Accumulator ] ────────────────> Integrated Camera Trajectory T_world_cam   |
+------------------------------------------------------------------------------------+
```

- **Monocular Scale Ambiguity:** A single camera can only determine motion up to an unknown scale factor ($s \cdot \mathbf{t}$). Stereo VO and Visual-Inertial Odometry resolve metric scale explicitly.

---

# 22. Visual SLAM

### ORB-SLAM3 System Architecture 🔴 [MUST KNOW]

```
                               +-----------------------------+
                               |     ORB-SLAM3 ARCHITECTURE  |
                               +-----------------------------+
                                              │
             ┌────────────────────────────────┼──────────────────────────────┐
             │                                │                              │
             ▼                                ▼                              ▼
+-------------------------+      +-------------------------+    +-------------------------+
|   TRACKING THREAD       |      |  LOCAL MAPPING THREAD   |    |  LOOP CLOSING THREAD    |
|   (Real-Time @ 30 Hz)   |      |  (Background @ 5-10 Hz) |    |  (Async @ 1 Hz)         |
| ├── FAST Feature Detect |      | ├── Triangulate Points  |    | ├── DBoW2 Place Recogn. |
| ├── Frame-to-Frame Pose | ───> | ├── Keyframe Insertion  |───>| ├── 7-DOF Sim(3) Align  |
| └── Motion Model VO     |      | └── Local Bundle Adjust |    | └── Essential Graph Opt |
+-------------------------+      +-------------------------+    +-------------------------+
```

---

# 23. Bundle Adjustment

### Non-Linear Joint Graph Optimization 🔴 [MUST KNOW]
Bundle Adjustment (BA) refines camera poses $\mathbf{C}_i = (\mathbf{R}_i, \mathbf{t}_i)$ and 3D world landmark positions $\mathbf{X}_j$:

$$\min_{\mathbf{C}_i, \mathbf{X}_j} \sum_{i=1}^M \sum_{j=1}^N \rho\left( \|\mathbf{u}_{ij} - \pi(\mathbf{K}(\mathbf{R}_i \mathbf{X}_j + \mathbf{t}_i))\|^2 \right)$$

where $\rho(\cdot)$ is a robust Huber/Cauchy loss function to downweight outlier residuals.

---

# 24. LiDAR + Camera Fusion

### 3D LiDAR Point Cloud Projection onto 2D Image 🔴 [MUST KNOW]
To project a 3D LiDAR point $\mathbf{P}_{\text{lidar}} = [X_l, Y_l, Z_l]^T$ onto a camera pixel $(u, v)$:

$$\begin{bmatrix} u \\ v \\ 1 \end{bmatrix} \sim \mathbf{K} \cdot \mathbf{T}_{\text{lidar}}^{\text{cam}} \begin{bmatrix} X_l \\ Y_l \\ Z_l \\ 1 \end{bmatrix} = \mathbf{K} \cdot \begin{bmatrix} \mathbf{R} & \mathbf{t} \\ \mathbf{0} & 1 \end{bmatrix} \begin{bmatrix} X_l \\ Y_l \\ Z_l \\ 1 \end{bmatrix}$$

- **Condition:** $Z_{\text{cam}} > 0$ (Point is in front of the camera optical lens).

---

# 25. Camera + IMU Fusion

### Visual-Inertial Odometry (VIO) Synergy 🔴 [MUST KNOW]
- **Camera:** Provides rich spatial landmarks and zero-drift orientation when static; fails during rapid motion / motion blur.
- **IMU:** Operates at $200-1000\text{ Hz}$, handles aggressive turns, makes gravity vector and metric scale directly observable; drifts rapidly over time.
- **Tightly-Coupled VIO (VINS-Mono):** Minimizes joint visual reprojection errors and IMU preintegration residuals simultaneously inside a sliding-window factor graph.

---

# 26. Machine Learning for Robotics Vision

### Convolutional Layer Mechanics 🔴 [MUST KNOW]
A 2D convolution applies a parameterized filter kernel $\mathbf{W}$ of size $K \times K$ across an input feature map $\mathbf{X}$:

$$Y(i, j) = \sum_{m=-k}^k \sum_{n=-k}^k X(i+m, j+n) \cdot W(m, n) + b$$

---

# 27. CNN Mathematics

### Output Dimension Formula 🔴 [MUST KNOW]

$$\mathbf{O = \left\lfloor \frac{W - K + 2P}{S} \right\rfloor + 1}$$

where:
- $W$: Input width/height.
- $K$: Kernel size.
- $P$: Padding size.
- $S$: Stride step size.

---

# 28. Edge AI Model Deployment

### Model Optimization for Embedded Hardware (NVIDIA Jetson) 🔴 [MUST KNOW]
1. **ONNX (Open Neural Network Exchange):** Standard open format representing trained neural networks independently of framework (PyTorch $\to$ ONNX).
2. **TensorRT Engine Compilation:** Parses ONNX graph, performs layer fusion (Conv + BatchNorm + ReLU merged into single CUDA kernel), and optimizes GPU memory allocations.
3. **Quantization:**
   - **FP32 $\to$ FP16:** Reduces memory by $2\times$, delivers $2-3\times$ speedup with zero perceptible accuracy loss.
   - **INT8 Quantization:** Maps 32-bit floats to 8-bit integers via calibration histograms, delivering $4\times$ throughput speedup for edge real-time inference.

---

# 29. Real-Time Computer Vision

### Threading & Buffer Overflow Mitigation 🔴 [MUST KNOW]
If camera driver captures at $30\text{ FPS}$ ($33.3\text{ ms}$ interval) but neural network inference takes $50\text{ ms}$:
- A sequential single-threaded node will accumulate an ever-growing memory queue, causing **multi-second latency lag**.
- **Fix:** Decouple capture and inference into separate threads with a **queue depth of 1 (Drop old frames)**:
  ```cpp
  // Always grab only the latest available frame, dropping stale intermediate frames
  ```

---

# 30. Vision Pipeline Design

### Complete Autonomous AMR Perception Stack 🔴 [MUST KNOW]

```
[ Camera Hardware ] ──> /camera/image_raw (sensor_msgs/Image)
                              │
                              ▼
                   [ image_proc / cv_bridge ] (Undistortion via K, D)
                              │
                              ▼
           ┌──────────────────┴──────────────────┐
           │                                     │
           ▼                                     ▼
[ YOLOv8 TensorRT Node ]              [ ORB Visual Odometry Node ]
 ├── Pallet & Forklift BBoxes          ├── 6-DOF Motion Delta (v, ω)
 └── Depth Cloud Fusion                └── Transmit to EKF (/odom)
           │
           ▼
[ 3D Bounding Box Projection ] ──> [ Nav2 Local Costmap Layer ] ──> [ Path Planner ]
```

---

# 31. ROS 2 + OpenCV

### C++ ROS 2 Image Processing Node (`cv_bridge`) 🔴 [MUST KNOW]

```cpp
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>

class ImageProcessorNode : public rclcpp::Node {
public:
    ImageProcessorNode() : Node("image_processor_node") {
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/image_raw", 10,
            std::bind(&ImageProcessorNode::imageCallback, this, std::placeholders::_1)
        );
        pub_ = this->create_publisher<sensor_msgs::msg::Image>("/camera/processed", 10);
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            // Convert ROS image to OpenCV Mat
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        // Processing: Convert to grayscale and detect edges
        cv::Mat gray, edges;
        cv::cvtColor(cv_ptr->image, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, edges, 50, 150);

        // Convert back to ROS message and publish
        auto out_msg = cv_bridge::CvImage(msg->header, "mono8", edges).toImageMsg();
        pub_->publish(*out_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
};
```

---

# 32. C++ Computer Vision Coding

#### Problem 32.1: Robust Visual Landmark Pose Estimation (PnP + RANSAC) 🔴 [MUST KNOW]

```cpp
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

struct EstimatedPose {
    cv::Mat R;
    cv::Mat t;
    bool success;
};

EstimatedPose estimateDockingMarkerPose(
    const std::vector<cv::Point3f>& object_points_3d,
    const std::vector<cv::Point2f>& image_points_2d,
    const cv::Mat& camera_matrix_K,
    const cv::Mat& dist_coeffs_D) 
{
    EstimatedPose result;
    result.success = false;

    if (object_points_3d.size() < 4 || object_points_3d.size() != image_points_2d.size()) {
        return result;
    }

    cv::Mat rvec, tvec;
    std::vector<int> inliers;

    // Solve PnP using RANSAC to reject false image detections
    bool solved = cv::solvePnPRansac(
        object_points_3d, image_points_2d,
        camera_matrix_K, dist_coeffs_D,
        rvec, tvec, false, 100, 8.0F, 0.99, inliers, cv::SOLVEPNP_EPNP
    );

    if (solved && inliers.size() >= 4) {
        // Convert rotation vector to 3x3 rotation matrix using Rodrigues formula
        cv::Rodrigues(rvec, result.R);
        result.t = tvec;
        result.success = true;
    }

    return result;
}
```

---

# 33. Python Computer Vision Coding

#### Problem 33.1: Inverse Perspective Mapping (IPM / Top-Down Bird's-Eye View) 🔴 [MUST KNOW]

```python
import cv2
import numpy as np

def compute_birds_eye_view(image_bgr: np.ndarray) -> np.ndarray:
    """Warps an angled front-camera view into a metric top-down costmap grid."""
    h, w = image_bgr.shape[:2]

    # Source: 4 trapezoidal coordinates on ground plane in front of robot
    src_pts = np.float32([
        [w * 0.25, h * 0.70],  # Top-left
        [w * 0.75, h * 0.70],  # Top-right
        [w * 0.90, h * 0.95],  # Bottom-right
        [w * 0.10, h * 0.95]   # Bottom-left
    ])

    # Destination: 4 rectangular coordinates in top-down metric plane
    dst_pts = np.float32([
        [w * 0.20, 0],
        [w * 0.80, 0],
        [w * 0.80, h],
        [w * 0.20, h]
    ])

    # Compute 3x3 Homography Matrix
    H = cv2.getPerspectiveTransform(src_pts, dst_pts)
    
    # Warp perspective
    top_down_view = cv2.warpPerspective(image_bgr, H, (w, h), flags=cv2.INTER_LINEAR)
    return top_down_view
```

---

# 34. Numerical Interview Problems

#### Problem 34.1: Pinhole Camera Projection
A camera has focal lengths $f_x = 800, f_y = 800$ pixels, and principal point at $c_x = 320, c_y = 240$. A target obstacle is located at 3D camera coordinates $\mathbf{P}_c = [1.5, -0.5, 3.0]^T$ meters.
1. Compute the normalized coordinates $(x_n, y_n)$.
2. Compute the 2D pixel coordinates $(u, v)$.

#### Problem 34.2: Stereo Depth & Disparity Calculation
A stereo camera has baseline $B = 0.2\text{ m}$ and focal length $f = 500\text{ pixels}$. An obstacle produces a disparity of $d = 25\text{ pixels}$.
1. Calculate the distance $Z$ to the obstacle.
2. If disparity estimation has an uncertainty of $\Delta d = \pm 1\text{ pixel}$, calculate the depth uncertainty $\Delta Z$.

*(Solutions in Section 51)*

---

# 35. Whiteboard Problems

### 1. "Derive the Stereo Depth formula from scratch on the whiteboard." 🔴
- **Draw:** Two pinhole optical centers separated by baseline $B$, projecting rays to point $P(X, Y, Z)$ on left and right image planes at focal length $f$.
- **Write:** $\frac{x_L}{f} = \frac{X + B/2}{Z}$ and $\frac{x_R}{f} = \frac{X - B/2}{Z}$. Subtract: $x_L - x_R = \frac{f B}{Z} \implies Z = \frac{f B}{d}$.

---

# 36. Debugging Scenarios

### 20 Real-World Robotics Vision Scenarios & Solutions 🔴 [MUST KNOW]

```
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| Failure Scenario                                  | Root Cause Diagnosis                              | Engineering Fix                                   |
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| 1. Vision node output delayed by 1.5 seconds      | ROS 2 subscription queue accumulating old frames  | Set subscription queue depth to 1                 |
| 2. PnP pose jumps wildly when robot turns         | Outlier feature matches passing into solvePnP     | Switch to cv::solvePnPRansac with strict threshold|
| 3. Stereo depth map has massive black holes/noise | Low-texture flat painted walls                    | Switch to Active Stereo (IR projector) or LiDAR   |
| 4. Point cloud projected onto image is shifted 10cm| Extrinsic calibration T_lidar_cam translation err | Re-calibrate extrinsics using calibration target  |
| 5. Camera image completely washed out / white     | Auto-exposure latency when exiting dark warehouse | Lock auto-exposure or use High Dynamic Range (HDR)|
| 6. Visual Odometry fails completely on highway    | Feature matching on moving cars instead of ground | Mask out dynamic YOLO object bounding boxes       |
| 7. Features vanish during fast robot rotations    | Rolling shutter distortion and motion blur        | Switch to Global Shutter camera + hardware trigger|
| 8. Top-down IPM road warp bends into curve        | Pitch/Roll angle estimation error in Homography   | Stabilize homography using real-time IMU pitch    |
| 9. Jetson GPU throttles and drops FPS             | High inference batching; FP32 model bloat         | Quantize ONNX model to INT8 using TensorRT        |
| 10. Tag detection fails at 45° viewing angle      | Severe perspective distortion on AprilTag         | Use adaptive thresholding and corner sub-pixel opt|
+---------------------------------------------------+---------------------------------------------------+---------------------------------------------------+
```

---

# 37. Computer Vision Failure Modes

```
+-----------------------+---------------------------------------------+-----------------------------------------------+
| Optical Failure Mode  | Physical Mechanism                          | Mitigation Strategy                           |
+-----------------------+---------------------------------------------+-----------------------------------------------+
| Motion Blur           | Long exposure time during fast turn         | Global shutter + High shutter speed (< 2ms)   |
| Rolling Shutter Skew  | Sensor rows exposed at sequential times     | Hardware global shutter CMOS sensor           |
| Low Texture / Plain   | Homogeneous white walls have zero gradients | Active IR dot projection / LiDAR sensor fusion|
| Direct Sun Flare      | Saturated CMOS pixels (Zero contrast)       | Polarizing physical lens filters / Dual cams  |
+-----------------------+---------------------------------------------+-----------------------------------------------+
```

---

# 38. Vision vs. LiDAR vs. Radar

```
+--------------------+-----------------------+-----------------------+-----------------------+-------------------------+
| Feature            | Monocular / Stereo Cam| 3D Mechanical LiDAR   | Solid-State LiDAR     | 4D Imaging Radar        |
+--------------------+-----------------------+-----------------------+-----------------------+-------------------------+
| Spatial Resolution | Ultra-High (Megapixels| High (Points in space)| High (Voxel grid)     | Low to Medium           |
| Direct Metric Depth| No (Mono) / Yes(Stereo| YES (Millimeter level)| YES (Millimeter level)| YES (Direct Doppler vel)|
| Weather Resistance | Poor (Fog/Rain/Dust)  | Medium (Degrades rain)| Medium                | EXCELLENT (Penetrates)  |
| Lighting Dependency| High (Fails darkness) | Zero (Active Laser)   | Zero (Active Laser)   | Zero (Radio frequency)  |
| Hardware Cost      | Very Low ($50 - $300) | High ($2k - $10k)     | Medium ($500 - $1.5k) | Low to Medium ($200-$1k)|
+--------------------+-----------------------+-----------------------+-----------------------+-------------------------+
```

---

# 39. Mathematics Cheat Sheet

- **Projection Equation:** $Z_c \mathbf{p}_{\text{pixel}} = \mathbf{K} \cdot \mathbf{P}_c$.
- **Stereo Depth:** $Z = \frac{f \cdot B}{d}$.
- **Epipolar Constraint:** $\mathbf{x}_2^T \mathbf{E} \mathbf{x}_1 = 0 \quad (\text{where } \mathbf{E} = [\mathbf{t}]_\times \mathbf{R})$.
- **Homography:** $\mathbf{p}_2 \sim \mathbf{H} \mathbf{p}_1$.

---

# 40. Essential Equations

```
+-----------------------+---------------------------------------------------+---------------------------------------------+
| Concept               | Governing Equation                                | Physical Robotics Meaning                   |
+-----------------------+---------------------------------------------------+---------------------------------------------+
| Pinhole Projection    | u = fx (X/Z) + cx,  v = fy (Y/Z) + cy             | 3D camera point mapped to 2D image pixel    |
| Stereo Triangulation  | Z = (f * B) / d                                   | Disparity d yields metric distance Z        |
| Stereo Depth Error    | |ΔZ| ≈ (Z^2 / (f * B)) * |Δd|                     | Depth uncertainty grows quadratically       |
| Essential Matrix      | E = [t]_x R                                       | Encodes relative pose between two views     |
| CNN Output Dimension  | O = floor((W - K + 2P) / S) + 1                   | Calculates feature map dimensions           |
+-----------------------+---------------------------------------------------+---------------------------------------------+
```

---

# 41. System Design Interview

### Autonomous Pallet-Docking Perception System 🔴 [MUST KNOW]
> **Prompt:** *"Design the computer vision perception subsystem for an autonomous mobile tugger to detect, align with, and dock under a warehouse pallet in variable indoor lighting."*

```
+------------------------------------------------------------------------------------+
|                         PALLET DOCKING PERCEPTION ARCHITECTURE                     |
+------------------------------------------------------------------------------------+
|                                                                                    |
|  [ SENSORS ]                                                                       |
|  ├── Front Low-Mount RGB-D Camera (Active IR Projector @ 30 FPS)                   |
|  └── High-Mount AprilTag Fiducial Camera (Global Shutter Monocular)                |
|                                                                                    |
|  [ STAGE 1: COARSE DETECTION (Range > 2.0m) ]                                      |
|  └── AprilTag / YOLOv8 Detector -> Identifies approximate pallet pocket 3D pose    |
|                                                                                    |
|  [ STAGE 2: FINE REGISTRATION (Range 0.3m - 2.0m) ]                                |
|  ├── RGB-D Point Cloud Filter -> Extracts pallet pocket crossbar planes            |
|  └── RANSAC Plane & Cylinder Fitting -> Computes exact 6-DOF docking frame pose    |
|                                                                                    |
|  [ STAGE 3: CLOSED-LOOP CONTROL ]                                                  |
|  └── Visual Servoing Controller -> Computes pure pursuit yaw/lateral corrections   |
+------------------------------------------------------------------------------------+
```

---

# 42. 60+ Core Computer Vision Interview Questions

1. **Q:** What is the difference between camera intrinsics and extrinsics?  
   - **Answer:** Intrinsics ($\mathbf{K}, \mathbf{D}$) represent internal optical geometry (focal lengths, optical center, lens distortion). Extrinsics ($[\mathbf{R} \mid \mathbf{t}]$) define the 6-DOF spatial pose of the camera optical frame relative to the robot body or world.
2. **Q:** Why does monocular visual odometry suffer from scale ambiguity?  
   - **Answer:** A single 2D image plane records angular bearings, not distance. A small object moving close produces identical pixel rays to a large object moving far away at high speed.
3. **Q:** What is the difference between the Essential Matrix and Fundamental Matrix?  
   - **Answer:** The Essential Matrix ($\mathbf{E}$) operates on calibrated normalized metric coordinates ($[\mathbf{t}]_\times \mathbf{R}$); the Fundamental Matrix ($\mathbf{F} = \mathbf{K}_R^{-T} \mathbf{E} \mathbf{K}_L^{-1}$) operates on raw uncalibrated pixel coordinates.
4. **Q:** Why is ORB preferred over SIFT in real-time robotics?  
   - **Answer:** ORB uses binary BRIEF descriptors that compare via single-instruction CPU Hamming distance ($< 1\text{ ms}$), whereas SIFT uses 128-dimensional floating-point Euclidean vectors ($> 50\text{ ms}$).
5. **Q:** What causes the Aperture Problem in optical flow?  
   - **Answer:** Observing motion through a small local window only allows measuring motion perpendicular to edges, leaving parallel motion ambiguous.

---

# 43. High-Pressure Follow-Up Chains

### Dialogue Chain 1: Camera Calibration & Epipolar Geometry
- **Interviewer:** *"Why is camera calibration mandatory before running stereo vision?"*  
  **Candidate:** *"To correct lens distortion ($\mathbf{D}$) and determine focal lengths and principal points ($\mathbf{K}$) needed to rectify images."*
- **Interviewer:** *"What is stereo rectification?"*  
  **Candidate:** *"Warping left and right images onto a common plane so epipolar lines become perfectly horizontal and collinear."*
- **Interviewer:** *"Why does that matter computationally?"*  
  **Candidate:** *"It reduces 2D stereo correspondence search across the entire image down to a fast 1D horizontal line search ($O(W \cdot H) \to O(W)$)."*

---

# 44. "Explain It in 30 Seconds"

- **Pinhole Camera:** *"A geometric model that maps 3D world coordinates onto a 2D image plane using perspective projection through an optical center located at focal length $f$."*
- **Stereo Vision:** *"Using two calibrated cameras separated by baseline $B$ to calculate depth $Z = \frac{f B}{d}$ from horizontal disparity $d$ via triangulation."*
- **Homography:** *"A $3\times3$ projective transformation matrix relating two 2D images of a flat planar surface in space."*

---

# 45. Common Interview Mistakes

- ⚠️ **Mistake 1:** Confusing normalized camera coordinates ($x_n = X/Z$) with pixel coordinates ($u = f_x x_n + c_x$).
- ⚠️ **Mistake 2:** Forgetting that stereo depth error degrades quadratically ($\Delta Z \propto Z^2$).
- ⚠️ **Mistake 3:** Assuming deep learning models should process raw $4\text{K}$ images in real-time control loops (destroys FPS).

---

# 46. ATI Robotics Specific Vision Questions

- **Q: How would you detect a pallet pocket in a low-contrast warehouse?**  
  *Answer: Combine an active IR structured-light depth camera (invariant to ambient shadow) with a YOLOv8 object detector to segment the pocket rectangular openings, followed by RANSAC plane fitting on the point cloud to compute the 6-DOF docking pose.*

---

# 47. Integrated Autonomy Problems

### Multi-Sensor Localization Architecture 🔴 [MUST KNOW]
- Combine wheel encoders ($100\text{ Hz}$) + IMU ($200\text{ Hz}$) in an EKF for high-rate continuous odometry, and use Visual Odometry / AprilTags ($20\text{ Hz}$) to correct accumulated wheel slip and heading drift.

---

# 48. Practical Coding Interview

```python
# 45-Minute Coding Problem: 2D IoU Calculation
def compute_iou(boxA, boxB):
    # box = [x1, y1, x2, y2]
    xA = max(boxA[0], boxB[0])
    yA = max(boxA[1], boxB[1])
    xB = min(boxA[2], boxB[2])
    yB = min(boxA[3], boxB[3])

    interArea = max(0, xB - xA) * max(0, yB - yA)
    boxAArea = (boxA[2] - boxA[0]) * (boxA[3] - boxA[1])
    boxBArea = (boxB[2] - boxB[0]) * (boxB[3] - boxB[1])

    iou = interArea / float(boxAArea + boxBArea - interArea) if (boxAArea + boxBArea - interArea) > 0 else 0.0
    return iou
```

---

# 49. Quick Revision Cheat Sheet

```
+---------------------+---------------------------------------+---------------------------------------------+
| Concept             | Core Formula                          | Robotics Significance                       |
+---------------------+---------------------------------------+---------------------------------------------+
| Projection          | u = fx(X/Z) + cx,  v = fy(Y/Z) + cy   | Projects 3D space to 2D pixels              |
| Stereo Depth        | Z = (f * B) / d                       | Metric distance from disparity              |
| Homography          | p2 ~ H p1                             | Planar perspective warping & IPM            |
| Essential Matrix    | E = [t]_x R                           | 5-DOF relative pose between calibrated views|
| CNN Output Size     | O = floor((W - K + 2P)/S) + 1         | Dimension scaling in neural nets            |
+---------------------+---------------------------------------+---------------------------------------------+
```

---

# 50. 30-Minute Final Revision Plan

1. **Pinhole Projection:** $u = f_x \frac{X}{Z} + c_x, \quad v = f_y \frac{Y}{Z} + c_y$.
2. **Stereo Depth:** $Z = \frac{f B}{d}$, error grows as $\Delta Z \propto Z^2$.
3. **Epipolar Geometry:** $\mathbf{x}_2^T \mathbf{E} \mathbf{x}_1 = 0$, where $\mathbf{E} = [\mathbf{t}]_\times \mathbf{R}$.
4. **Homography:** 8 DOF, minimum 4 point correspondences.
5. **Real-Time Rule:** Queue depth $= 1$ to drop stale camera frames.

---

# 51. Final Readiness Test

### Questions (Attempt before viewing solutions)

#### Conceptual & Mathematical (10 Questions)
1. A camera has $f_x = 1000, c_x = 640$. A 3D landmark is at $X_c = 2.0\text{ m}, Z_c = 4.0\text{ m}$. What is pixel $u$?
2. In stereo vision, if baseline $B = 0.1\text{ m}, f = 1000\text{ pixels}, d = 20\text{ pixels}$, compute depth $Z$.
3. What is the minimum number of point correspondences required to compute a Homography matrix?
4. What is the rank of the Essential Matrix $\mathbf{E}$?
5. A CNN layer has input width $W = 224$, kernel $K = 7$, padding $P = 3$, stride $S = 2$. What is the output width $O$?
6. Why does ORB feature matching run faster than SIFT?
7. What coordinate frame convention does OpenCV use for its optical axis?
8. Explain the difference between Precision and Recall in obstacle detection.
9. How does RANSAC prevent false feature matches from ruining PnP pose estimation?
10. In ROS 2, what node package converts `sensor_msgs/Image` to `cv::Mat`?

---

<details>
<summary><b>🔍 Click to Expand Complete Test Solutions & Math Answers</b></summary>

### Solutions
1. $u = f_x \frac{X_c}{Z_c} + c_x = 1000 \left(\frac{2.0}{4.0}\right) + 640 = 500 + 640 = \mathbf{1140\text{ pixels}}$.
2. $Z = \frac{f \cdot B}{d} = \frac{1000 \times 0.1}{20} = \frac{100}{20} = \mathbf{5.0\text{ meters}}$.
3. **4 point pairs** (8 independent equations for 8 degrees of freedom).
4. **Rank 2** (Singular matrix, two identical non-zero singular values $\sigma_1 = \sigma_2 \ne 0, \sigma_3 = 0$).
5. $O = \lfloor \frac{224 - 7 + 2(3)}{2} \rfloor + 1 = \lfloor \frac{224 - 7 + 6}{2} \rfloor + 1 = \lfloor \frac{223}{2} \rfloor + 1 = 111 + 1 = \mathbf{112}$.
6. **Binary Hamming Distance:** ORB uses binary strings compared via single CPU popcount instructions, while SIFT uses 128-float Euclidean distances.
7. **+Z Forward (along optical axis), +X Right, +Y Down.**
8. **Precision:** Fraction of detected obstacles that are real. **Recall:** Fraction of all real obstacles detected.
9. **RANSAC Consensus:** Randomly samples minimal subset (4 points), models pose, counts inliers within pixel threshold, and eliminates outliers.
10. **`cv_bridge`**.

#### Solutions to Mathematical Problems (from Section 34):
- **Problem 34.1:**  
  1. $x_n = \frac{X}{Z} = \frac{1.5}{3.0} = 0.5, \quad y_n = \frac{Y}{Z} = \frac{-0.5}{3.0} = -0.1667$.  
  2. $u = 800(0.5) + 320 = 400 + 320 = \mathbf{720\text{ pixels}}$.  
     $v = 800(-0.1667) + 240 = -133.33 + 240 = \mathbf{106.67\text{ pixels}}$.
- **Problem 34.2:**  
  1. $Z = \frac{f \cdot B}{d} = \frac{500 \times 0.2}{25} = \frac{100}{25} = \mathbf{4.0\text{ meters}}$.  
  2. $|\Delta Z| \approx \frac{Z^2}{f \cdot B} |\Delta d| = \frac{4.0^2}{500 \times 0.2} (1) = \frac{16.0}{100} = \mathbf{\pm 0.16\text{ meters} \ (\pm 16\text{ cm})}$.

</details>

---

### 📊 Scoring Rubric
- **90–100%**: *Mastery Level* (Ready for senior autonomy perception grilling).
- **75–89%**: *Interview Ready* (Strong performance across core geometry, calibration, and algorithms).
- **60–74%**: *Needs Targeted Revision* (Review epipolar geometry and stereo depth math).
- **< 60%**: *Revisit Fundamentals* (Practice pinhole camera derivations and OpenCV matrix layouts).
