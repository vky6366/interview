# Deployment & Production Interview Guide

Taking machine learning and AI applications from a local Jupyter notebook to a scalable production environment is a highly valued skill. This guide covers the essential deployment and cloud infrastructure concepts.

---

## 1. Docker

Docker is the industry standard for packaging and deploying applications.

### The "It works on my machine" Problem
Before Docker, developers struggled because code that worked on their laptop might crash on the production server due to different OS versions, missing libraries, or conflicting Python environments. Docker solves this by packaging the application and *all* its dependencies into a standardized unit.

### Core Docker Concepts
*   **Images:** A read-only template containing your application code, runtime (e.g., Python), libraries, environment variables, and configuration files. It's the blueprint.
*   **Containers:** A running instance of an Image. It is a lightweight, standalone, and executable package of software that runs isolated from the host operating system and other containers. You can run multiple identical containers from a single image.
*   **Port Mapping:** Containers run in isolated networks. Port mapping binds a port on the host machine to a port inside the container so outside traffic can reach your app.
    *   *Example:* `-p 8000:80`. Traffic hitting port 8000 on your server is forwarded to port 80 inside the container (where your FastAPI app is listening).
*   **Volumes:** By default, if a container is deleted, any data generated inside it is lost (ephemeral storage). Volumes are used to persist data (like a database file or uploaded images) independently of the container's lifecycle. You mount a folder on the host machine to a folder inside the container.

---

## 2. Amazon Web Services (AWS)

AWS is the most widely used cloud provider. You don't need to know every service, but you must know the core computing, storage, and security primitives.

### EC2 (Elastic Compute Cloud)
*   **What it is:** Virtual servers in the cloud (Virtual Machines). You rent raw computing power (CPU, RAM, GPU) and an Operating System (usually Linux).
*   **Use case:** Hosting web servers, running heavy machine learning training jobs, or hosting a database yourself. It gives you complete control (root access), but you are responsible for maintaining the OS, patching, and scaling.

### ECS (Elastic Container Service)
*   **What it is:** A fully managed container orchestration service. Instead of manually SSH-ing into EC2 instances to run `docker run`, you tell ECS: "Here is my Docker image, I want 5 containers running at all times, and scale up if CPU goes over 70%."
*   **Use case:** Deploying scalable, containerized microservices (like your AI backend) without having to manually manage the underlying EC2 servers (especially when using AWS Fargate, a serverless compute engine for containers).

### S3 (Simple Storage Service)
*   **What it is:** Object storage built to store and retrieve any amount of data from anywhere. It does not have a traditional file system structure; data is stored as "objects" (files) inside "buckets."
*   **Use case:** Storing static assets (images, videos), datasets for machine learning, model weights (`.pt` or `.bin` files), and backups. It is infinitely scalable and highly durable.

### IAM (Identity and Access Management)
*   **What it is:** The security backbone of AWS. It allows you to manage access to AWS services and resources securely.
*   **Concept:** You create *Users* (people) and *Roles* (permissions assumed by services, like an EC2 instance). You attach *Policies* (JSON documents) to them that explicitly state what they are allowed to do (e.g., "This EC2 instance is only allowed to Read from this specific S3 bucket").
*   **Rule of Thumb:** Always follow the Principle of Least Privilege (give only the permissions strictly required to perform a task).

---

## 3. Advanced Production Concepts (Bonus Points)

Mentioning these shows you understand modern DevOps workflows.

### CI/CD (Continuous Integration / Continuous Deployment)
*   **What it is:** Automating the process of testing and deploying code.
*   **Workflow:** When you push code to GitHub, a CI/CD pipeline (like GitHub Actions) automatically triggers. It runs your unit tests (Integration). If they pass, it builds a new Docker Image, pushes it to a registry, and tells your production server (like ECS) to pull the new image and restart (Deployment).

### Load Balancing
*   **What it is:** As your traffic grows, one server (or container) isn't enough. You run multiple copies of your application. A Load Balancer (like AWS ALB) sits in front of them, receives incoming traffic, and evenly distributes it across all healthy instances. This ensures no single server is overwhelmed and provides high availability.

### Kubernetes (K8s)
*   While ECS is AWS-specific, Kubernetes is the open-source industry standard for container orchestration. It automates deploying, scaling, and managing containerized applications across clusters of machines. It is highly complex but incredibly powerful for massive-scale architectures.
