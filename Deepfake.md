# Deepfake Detection Interview Prep

## Resume Line 1: Developed EfficientNet-B4 & B5 ensemble achieving 99.8% AUC on FF++, Celeb-DF, DeeperForensics

This single sentence contains five major interview topics:
- Why Deepfake Detection?
- Why EfficientNet?
- Why B4 and B5?
- Why Ensemble?
- Why AUC?

### Step 1 — Explain the Problem

**Interviewer:**
Explain your project.

**A good answer:**
"The goal of the project was to detect manipulated face videos in real time. Given a video input, the system extracts frames, detects the face, preprocesses it, performs inference using an ensemble of EfficientNet models, aggregates predictions across frames, generates Grad-CAM explanations, and returns a final real/fake prediction through a FastAPI backend."

**Architecture:**
```text
Video
   │
Frame Extraction
   │
Face Detection
   │
Face Crop
   │
Resize + Normalize
   │
EfficientNet B4 + B5
   │
Frame Predictions
   │
Temporal Fusion
   │
Video Prediction
   │
GradCAM
   │
FastAPI Response
```

### Step 2 — Why EfficientNet?

This is almost guaranteed.

**Question:**
Why not ResNet? Why not MobileNet? Why EfficientNet?

**Answer:**
EfficientNet uses compound scaling.
Instead of only increasing depth, width, or resolution independently, EfficientNet scales all three together.

Result:
Higher accuracy -> Fewer parameters -> Lower computation -> Better inference speed

**Question:**
Why not Vision Transformer?

**Answer:**
At the time, ViTs generally require:
- significantly larger datasets
- more GPU memory
- longer training

EfficientNet provided an excellent accuracy-speed trade-off for this application.

### Step 3 — Why B4 and B5?

**Question:**
Why specifically B4 and B5?

**Good answer:**
- **B4**: Faster inference, Smaller, Good accuracy
- **B5**: Higher accuracy, More parameters, Better feature extraction

Combining them captures complementary representations while keeping inference practical.

**Question:**
Why not B7?

**Answer:**
Much larger, Higher latency, More memory. Marginal accuracy improvement compared to increased computational cost.

### Step 4 — Why Ensemble?

**Question:**
What is an ensemble?

**Answer:**
Instead of: `One Model -> Prediction`
You have:
```text
B4 -> Prediction
+
B5 -> Prediction
↓
Average / Weighted
↓
Final Prediction
```

**Why?**
Different models learn different feature representations.
One model might detect texture artifacts.
Another might detect compression inconsistencies.
Together -> More robust.

**Question:**
Why does ensemble improve performance?

**Answer:**
Because errors made by one model may not be made by the other. Averaging reduces variance.

**Question:**
Any disadvantages?

**Answer:**
Absolutely.
- Higher latency
- More memory
- Larger deployment size

Mentioning trade-offs is a sign of engineering maturity.

### Step 5 — Why These Datasets?

You used FF++, CelebDF, DeeperForensics. Know why each exists.

**FaceForensics++**
Contains: DeepFake, FaceSwap, Face2Face, NeuralTextures.
Large benchmark. Good diversity.

**CelebDF**
More realistic. Higher quality. Harder to detect. Closer to real-world scenarios.

**DeeperForensics**
Contains: Lighting, Blur, Compression, Pose variation, Weather effects, Motion.
Designed to improve robustness.

**Question:**
Why combine all three?

**Answer:**
Because training on one dataset often causes overfitting to that dataset's artifacts. Multiple datasets improve generalization.

### Step 6 — AUC

**Question:**
Why report AUC instead of Accuracy?

**Answer:**
This is extremely common.
Accuracy = Correct / Total. Can be misleading on imbalanced datasets.
AUC measures True Positive Rate vs False Positive Rate across all thresholds.
Better indicator of classifier quality.

**Question:**
Difference between Accuracy, Precision, Recall, F1, AUC?

Know all of them.

**Question:**
Why was AUC 99.8 but accuracy lower?

**Answer:**
Because AUC measures ranking ability. Accuracy depends on one threshold. Very common.

### Step 7 — Video Pipeline

Now the interviewer moves to deployment.

**Question:**
How does a video become a prediction?

**Pipeline:**
Video -> OpenCV -> Frames -> Face Detection -> Crop Face -> Resize -> Normalize -> Model -> Frame Score

**Question:**
Why not feed the whole video?

**Answer:**
Huge memory, Huge computation. CNNs work on images. Frames are much simpler.

**Question:**
Frame rate?

**Answer:**
Maybe 5 FPS, 10 FPS, or Every nth frame. Explain why.

### Step 8 — Face Detection

**Question:**
How did you detect faces?

**Possible answers:**
MTCNN, Dlib, MediaPipe, RetinaFace.
Know **Why**.

**Question:**
Why crop faces?

**Answer:**
Because:
- Background -> Adds noise.
- Face -> Contains manipulation artifacts.

### Step 9 — Preprocessing

**Question:**
What preprocessing?

**Typical:**
Resize, Normalize, Convert RGB, Tensor, Batch.

**Question:**
Image size?

**Answer:**
224×224 or 380×380 depending on EfficientNet version. Know yours.

---

## Resume Line 2: deployed real-time FastAPI + Android/web pipeline

**Question:**
Explain architecture.

**Answer:**
Android or Website -> Upload Video -> FastAPI -> Frame Extraction -> Inference -> GradCAM -> Prediction -> Return JSON

**Question:**
Why FastAPI?

**Answer:**
- Python
- Async
- Easy deployment
- Automatic docs

**Question:**
What response?

**Answer:**
```json
{
  "prediction": "Fake",
  "confidence": 98.6,
  "heatmap": "..."
}
```

**Question:**
How long did inference take?

**Answer:**
Know approximate latency.

---

## Resume Line 3: Grad-CAM explanations

This is extremely interview-worthy.

**Question:**
What is GradCAM?

**Answer:**
Instead of just outputting "Fake", it shows **WHY** the network predicted fake.
Heatmap on Face, Eyes, Cheeks, Jaw, Forehead Highlighted.

**Question:**
Why important?

**Answer:**
Explainability.
Without it: User -> "Why is this fake?"
With GradCAM: Model -> Shows manipulated regions.

**Question:**
How does GradCAM work?

**Answer:**
High level: Forward pass -> Gradient -> Feature maps -> Weighted average -> Heatmap.
No need to derive equations unless asked.

**Question:**
Limitations?

**Answer:**
Not perfect. Sometimes highlights unrelated regions. Resolution is coarse.

---

## Resume Line 4: Optimized frame sampling

**Question:**
Why?

**Answer:**
Videos have thousands of frames. Running inference on every frame -> Too slow.
Instead sample every 5th or 10th frame.

**Question:**
Tradeoff?

**Answer:**
Fewer frames -> Faster -> Possible accuracy loss.

---

## Resume Line 5: Fusion strategies

Huge interview topic.

**Question:**
What is fusion?

**Answer:**
Each frame produces a probability. Need one video prediction.
Example:
- Frame1: 98%
- Frame2: 95%
- Frame3: 12%
- Frame4: 97%
Average -> 95%

**Possible methods:**
Average, Weighted Average, Max, Voting, Attention.

**Question:**
Which worked best?

**Answer:**
Know yours.

---

## Resume Line 6: Model quantization

**Question:**
What is quantization?

**Answer:**
Converts FP32 -> INT8 or FP16.
Result: Smaller model -> Faster inference -> Lower RAM.

**Question:**
Disadvantage?

**Answer:**
Slight accuracy drop.

**Question:**
Why quantize?

**Answer:**
Deployment. Especially on Mobile, Edge, CPU.

---

## Resume Line 7: Accuracy–Latency Trade-off

This is one of the most important engineering discussions.

**Question:**
What does this mean?

**Answer:**
- Large model -> High accuracy -> High latency
- Small model -> Lower accuracy -> Fast

Engineering means choosing the right balance.

---

## Resume Line 8: Tech Stack

Know why each was used.

- **PyTorch**: Training.
- **OpenCV**: Video processing.
- **FastAPI**: Inference server.
- **Kotlin**: Android app.

---

## Architecture they may ask you to draw

```text
               Video Upload
                     │
                     ▼
            FastAPI Backend
                     │
         Frame Extraction (OpenCV)
                     │
             Face Detection
                     │
             Face Preprocessing
                     │
        ┌────────────┴────────────┐
        ▼                         ▼
  EfficientNet-B4          EfficientNet-B5
        │                         │
        └────────────┬────────────┘
                     ▼
             Fusion Strategy
                     ▼
           Video Prediction
                     ▼
          Grad-CAM Generation
                     ▼
           JSON Response/API
                     ▼
        Android App / Web Client
```
