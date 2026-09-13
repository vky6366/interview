# ☁️ AWS Interview Questions (Full Coverage + Security Focus)

## 🟡 1. AWS Fundamentals

**What is AWS and how does cloud computing work?**
AWS (Amazon Web Services) is a comprehensive, evolving cloud computing platform provided by Amazon that includes a mixture of infrastructure-as-a-service (IaaS), platform-as-a-service (PaaS) and packaged software-as-a-service (SaaS) offerings. Cloud computing works by renting compute power, storage, databases, and other IT resources over the internet with pay-as-you-go pricing, rather than buying, owning, and maintaining physical data centers and servers.

**What are the advantages of cloud over on-premise?**
* **Cost:** Variable expense instead of capital expense (CapEx vs OpEx). Pay only for what you consume.
* **Agility & Speed:** Rapidly provision resources in minutes.
* **Elasticity:** Scale up or down automatically based on demand (no more guessing capacity).
* **Global Reach:** Deploy globally in minutes across multiple regions.
* **Maintenance:** Focus on applications rather than managing physical hardware.

**Explain IaaS vs PaaS vs SaaS**
* **IaaS (Infrastructure as a Service):** Provides building blocks (compute, storage, network). You manage the OS, runtime, and app (e.g., EC2).
* **PaaS (Platform as a Service):** Removes the need for underlying infrastructure management. You just deploy your code/app (e.g., Elastic Beanstalk).
* **SaaS (Software as a Service):** A completed product run and managed by the service provider (e.g., Gmail, Dropbox).

**What is high availability in AWS?**
High Availability (HA) ensures that systems are dependable and operate continuously without failure for a long time. In AWS, this is typically achieved by deploying applications across multiple Availability Zones (AZs) using Load Balancers and Auto Scaling groups to handle single data center failures seamlessly.

**What is a region and availability zone (AZ)?**
* **Region:** A geographical area containing two or more Availability Zones (e.g., us-east-1, eu-west-1).
* **Availability Zone (AZ):** One or more discrete data centers with redundant power, networking, and connectivity within an AWS Region. AZs are isolated from failures in other AZs.

**Difference between region vs edge location**
Regions are clusters of data centers for computing and storage. Edge Locations are endpoints for AWS used for caching content (CloudFront) and DNS (Route 53) to reduce latency by delivering content closer to the end user.

**What is fault tolerance vs scalability?**
* **Fault Tolerance:** The ability of a system to remain fully operational even if one of its components fails (e.g., Multi-AZ RDS).
* **Scalability:** The ability of a system to easily handle increased workloads by adding resources (e.g., Auto Scaling adding EC2 instances).

---

## 🟢 2. EC2 (Compute)

**What is EC2? How does it work?**
Amazon Elastic Compute Cloud (EC2) provides resizable compute capacity in the cloud. It allows users to boot virtual machines (instances) with a variety of operating systems and configure them with CPU, memory, and networking capacity as needed.

**What are instance types (compute, memory, GPU)?**
AWS offers various instance families optimized for specific use cases:
* **Compute Optimized (C):** High-performance processors for batch processing, media transcoding, ML inference.
* **Memory Optimized (R, X):** Fast performance for workloads that process large data sets in memory (e.g., databases).
* **Accelerated Computing/GPU (P, G):** Hardware accelerators for graphics processing or data pattern matching (Deep Learning).
* **General Purpose (M, T):** Balanced compute, memory, and networking resources.

**What is AMI (Amazon Machine Image)?**
An AMI provides the information required to launch an instance. It includes the OS, application server, and applications. You can use AWS-provided AMIs, custom AMIs, or community AMIs.

**What is auto scaling group (ASG)?**
An ASG contains a collection of EC2 instances that are treated as a logical grouping for the purposes of automatic scaling and management. It ensures that you have the correct number of EC2 instances available to handle the load for your application.

**What is Elastic Load Balancer (ELB)?**
ELB automatically distributes incoming application traffic across multiple targets (e.g., EC2 instances, containers, IP addresses) in multiple Availability Zones.

**Difference between: ALB vs NLB vs CLB**
* **ALB (Application Load Balancer):** Layer 7 (HTTP/HTTPS). Routes traffic based on content (path, host, headers). Great for microservices.
* **NLB (Network Load Balancer):** Layer 4 (TCP/UDP/TLS). Ultra-high performance, ultra-low latency. Handles millions of requests per second. Static IPs.
* **CLB (Classic Load Balancer):** Legacy load balancer (Layer 4 & 7). Deprecated; use ALB/NLB instead.

**What are spot instances vs reserved vs on-demand?**
* **On-Demand:** Pay by the second/hour with no long-term commitments.
* **Reserved:** 1 or 3-year commitment for a significant discount (up to 72%). Best for steady-state workloads.
* **Spot Instances:** Spare EC2 capacity at steep discounts (up to 90%). Can be interrupted with 2 minutes notice. Best for fault-tolerant, flexible workloads.

**What is user data script?**
A script executed on an EC2 instance during its initial boot process. It's typically used to automate boot tasks, such as installing software, updating the OS, or downloading configuration files.

---

## 🔵 3. Storage (S3, EBS, EFS)

### S3
**What is S3?**
Amazon Simple Storage Service (S3) is an object storage service offering industry-leading scalability, data availability, security, and performance. It stores data as objects within resources called "buckets."

**What are storage classes (Standard, IA, Glacier)?**
* **Standard:** General purpose, frequent access, low latency.
* **Standard-IA (Infrequent Access):** For data accessed less frequently, but requires rapid access when needed (lower storage cost, but retrieval fee).
* **Glacier:** Deep archive for long-term retention. Very low storage cost, but data takes minutes to hours to retrieve.

**What is versioning in S3?**
Keeps multiple variants of an object in the same bucket. Once enabled, it cannot be disabled (only suspended). It protects against accidental deletion and overwrites.

**What is lifecycle policy?**
Rules that automate moving S3 objects between storage classes (e.g., move to IA after 30 days, move to Glacier after 90 days) or expiring/deleting them based on age.

**What is pre-signed URL?**
A URL that grants temporary access (download or upload) to an S3 object without requiring the user to have AWS credentials. Useful for sharing private files temporarily.

**What is event notification in S3?**
S3 can trigger notifications (via SNS, SQS, or Lambda) when certain events happen in a bucket (e.g., an object is created, deleted, or restored).

### EBS / EFS
**Difference between EBS vs EFS vs S3**
* **EBS (Elastic Block Store):** Block storage attached to a *single* EC2 instance (like a hard drive). Must be in the same AZ as the instance.
* **EFS (Elastic File System):** File storage that can be mounted to *multiple* EC2 instances simultaneously across multiple AZs (NFS protocol).
* **S3:** Object storage accessible globally via API/HTTP. Not typically mounted as a filesystem.

**What is snapshot in EBS?**
A point-in-time backup of an EBS volume stored in S3. Incremental backups mean only the blocks that changed since the last snapshot are saved.

**What is IOPS?**
Input/Output Operations Per Second. A measure of storage performance. For workloads that require high, sustained performance (e.g., databases), Provisioned IOPS EBS volumes are used.

---

## 🔴 4. Networking (VERY IMPORTANT)

**What is a VPC?**
Virtual Private Cloud (VPC) is a logically isolated section of the AWS Cloud where you can launch AWS resources in a virtual network that you define.

**What are:**
* **Subnets (public vs private):** A segment of a VPC's IP address range. A *public subnet* has a route to an Internet Gateway (can access the internet). A *private subnet* does not.
* **Route tables:** A set of rules (routes) used to determine where network traffic from your subnet or gateway is directed.
* **Internet Gateway (IGW):** A horizontally scaled, redundant VPC component that allows communication between your VPC and the internet.
* **NAT Gateway:** Allows instances in a private subnet to connect to the internet (e.g., for updates) while preventing the internet from initiating connections to those instances.

**Difference: Security Group vs NACL**
* **Security Group (SG):** Acts at the instance level. *Stateful* (return traffic is automatically allowed). Defaults to deny all inbound, allow all outbound.
* **NACL (Network Access Control List):** Acts at the subnet level. *Stateless* (return traffic must be explicitly allowed). Can block specific IPs.

**What is CIDR block?**
Classless Inter-Domain Routing. A method for allocating IP addresses and IP routing. E.g., `10.0.0.0/16` defines the range of IP addresses available in a VPC.

**What is VPC peering?**
A networking connection between two VPCs that enables you to route traffic between them using private IPv4 or IPv6 addresses. Can be inter-region.

**What is PrivateLink?**
Provides private connectivity between VPCs, AWS services, and on-premises applications, securely on the Amazon network. Traffic does not traverse the public internet.

**What is DNS in AWS (Route 53)?**
Amazon Route 53 is a highly available and scalable cloud Domain Name System (DNS) web service. It translates domain names (www.example.com) into IP addresses and routes traffic globally.

---

## 🟣 5. IAM (CRITICAL FOR SECURITY)

**What is IAM?**
Identity and Access Management (IAM) enables you to manage access to AWS services and resources securely. You create users, groups, and roles, and attach policies to deny or allow access.

**Difference: User vs Role vs Policy**
* **User:** A person or application that interacts with AWS. Has long-term credentials (password, access keys).
* **Role:** An identity that you can create that has specific permissions, intended to be *assumed* temporarily by anyone/anything that needs it. Has short-term credentials.
* **Policy:** A JSON document that defines the permissions (Effect, Action, Resource, Condition). Attached to users, groups, or roles.

**What is least privilege principle?**
Granting users or systems only the minimum permissions necessary to perform their required tasks, and nothing more. This is a foundational security best practice.

**What is IAM role vs IAM user?**
A user represents a specific individual or application with permanent credentials. A role is meant to be assumed dynamically by AWS services (like EC2), federated users, or other AWS accounts, providing temporary, rotating credentials.

**What is STS (temporary credentials)?**
Security Token Service (STS) enables you to request temporary, limited-privilege credentials for AWS IAM users or for users that you authenticate (federated users).

**What is assume role?**
An API call (via STS) that returns a set of temporary security credentials that you can use to access AWS resources that you might not normally have access to.

**What is policy JSON structure?**
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": "s3:ListBucket",
      "Resource": "arn:aws:s3:::example_bucket"
    }
  ]
}
```

**What is resource-based vs identity-based policy?**
* **Identity-based:** Attached to an IAM user, group, or role (e.g., "User X can access S3").
* **Resource-based:** Attached directly to an AWS resource (e.g., an S3 bucket policy stating "Anyone from Account Y can read this bucket").

---

## 🔐 6. AWS Security (VERY IMPORTANT 🔥)

### Core Security
**What is Shared Responsibility Model?**
Security *of* the Cloud vs Security *in* the Cloud.
* **AWS is responsible for:** Protecting the infrastructure (hardware, software, networking, facilities) that runs all AWS services.
* **Customer is responsible for:** Securing their data, managing OS, network configuration, firewall rules, IAM, and encryption.

**What are AWS security best practices?**
Enable MFA for root and IAM users, apply least privilege, use IAM Roles instead of long-term keys for apps, enable CloudTrail for auditing, encrypt data at rest and in transit, regularly rotate keys, and use VPCs for network isolation.

### Encryption
**Encryption at rest vs in transit**
* **At rest:** Encrypting data while it is stored on disk (e.g., S3 server-side encryption, EBS encryption).
* **In transit:** Encrypting data as it travels across the network (e.g., TLS/HTTPS).

**What is KMS (Key Management Service)?**
A managed service that makes it easy to create and control the cryptographic keys used to encrypt your data. It integrates natively with most AWS services.

**What is CMK (Customer Managed Key)?**
Keys created and managed by the AWS customer in KMS, allowing full control over key rotation, policies, and deletion, as opposed to AWS Managed Keys.

**What is envelope encryption?**
The practice of encrypting plaintext data with a data key, and then encrypting the data key under another key (the master key or KMS key). This is how KMS operates efficiently.

### Monitoring & Detection
**What is CloudTrail?**
A service that logs all API calls made within your AWS account. Critical for auditing, compliance, and answering "who did what, when, and from where?"

**What is CloudWatch?**
A monitoring and management service that collects performance and operational data in the form of logs, metrics, and events. Used for setting alarms and triggering Auto Scaling.

**What is AWS Config?**
Continuously monitors and records AWS resource configurations and allows you to automate the evaluation of recorded configurations against desired guidelines (compliance).

**What is GuardDuty?**
An intelligent threat detection service that continuously monitors for malicious activity and unauthorized behavior to protect your AWS accounts and workloads (uses ML).

**What is Security Hub?**
A comprehensive view of your high-priority security alerts and compliance status across AWS accounts. It aggregates findings from GuardDuty, Macie, Inspector, etc.

### Threat Protection
**What is AWS WAF?**
Web Application Firewall that helps protect web applications or APIs against common web exploits (e.g., SQL injection, Cross-Site Scripting) that may affect availability or compromise security.

**What is Shield (DDoS protection)?**
A managed Distributed Denial of Service (DDoS) protection service. Standard is free and enabled for all AWS customers. Advanced provides enhanced protections and 24x7 access to DDoS experts.

### Identity Security
**MFA in AWS**
Multi-Factor Authentication adds an extra layer of security on top of usernames and passwords. Highly recommended for all users, especially the root account.

**What is SSO?**
AWS IAM Identity Center (formerly AWS SSO) centrally manages SSO access to multiple AWS accounts and business applications using a single set of credentials (often integrating with Active Directory/Okta).

### Secrets
**Secrets Manager vs Parameter Store**
* **Secrets Manager:** Purpose-built for secrets. Can automatically rotate database credentials natively. Costs more.
* **Parameter Store (SSM):** Used for configuration data AND secure strings (secrets). No native automatic rotation. Mostly free (standard parameters).

---

## 🟠 7. DevOps & CI/CD

**What is CodePipeline?**
A fully managed continuous delivery service that helps you automate your release pipelines for fast and reliable application and infrastructure updates.

**What is CodeBuild / CodeDeploy?**
* **CodeBuild:** Compiles source code, runs tests, and produces software packages that are ready to deploy.
* **CodeDeploy:** Automates code deployments to any instance, including EC2, Fargate, Lambda, and on-premises servers.

**What is Infrastructure as Code (IaC)?**
The process of managing and provisioning computer data centers through machine-readable definition files, rather than physical hardware configuration or interactive configuration tools.

**CloudFormation vs Terraform**
* **CloudFormation:** AWS-native IaC tool. Uses JSON/YAML. State is managed by AWS automatically.
* **Terraform:** Open-source IaC tool by HashiCorp. Cloud-agnostic (supports AWS, Azure, GCP). Uses HCL. State is managed via a state file.

**What is blue-green deployment?**
A deployment strategy where you create two separate, but identical environments (Blue and Green). One runs the current application version, while the other runs the new version. Traffic is seamlessly routed to the new version once verified.

---

## 🟤 8. Containers & Serverless

### Containers
**What is ECS vs EKS?**
* **ECS (Elastic Container Service):** AWS's native container orchestration service. Simpler to use, deeply integrated with AWS.
* **EKS (Elastic Kubernetes Service):** Managed Kubernetes service on AWS. Better for multi-cloud strategies or if you already have Kubernetes expertise.

**What is Fargate?**
A serverless compute engine for containers that works with both ECS and EKS. Fargate removes the need to provision and manage servers (EC2 instances) to run containers.

### Serverless
**What is Lambda?**
A serverless compute service that lets you run code without provisioning or managing servers. You pay only for the compute time you consume (per millisecond).

**What are Lambda limits?**
* Maximum execution time: 15 minutes.
* Memory limit: 128 MB to 10 GB.
* Deployment package size: 50 MB (zipped), 250 MB (unzipped).

**What is API Gateway?**
A fully managed service that makes it easy for developers to create, publish, maintain, monitor, and secure APIs at any scale (acts as a "front door" for applications to access data/business logic, often Lambda).

**What is event-driven architecture?**
An architecture paradigm promoting the production, detection, consumption of, and reaction to events. In AWS, this means services communicating via events (e.g., S3 triggering a Lambda, EventBridge).

---

## ⚫ 9. Databases

**Difference: RDS vs DynamoDB**
* **RDS (Relational Database Service):** SQL (relational) database. Fixed schema. Scales vertically. Complex queries/joins. (MySQL, PostgreSQL, Oracle).
* **DynamoDB:** NoSQL database (Key-Value/Document). Schema-less. Scales horizontally automatically. Single-digit millisecond latency at any scale.

**What is Aurora?**
A MySQL and PostgreSQL-compatible relational database built for the cloud by AWS. Up to 5x faster than standard MySQL. Data is replicated 6 ways across 3 AZs for extreme durability.

**What is read replica?**
A read-only copy of a primary database instance. Used to scale out read-heavy workloads (offloading read queries from the primary database).

**What is Multi-AZ deployment?**
AWS automatically provisions and maintains a synchronous standby replica in a different AZ. Used strictly for high availability and disaster recovery (failover), NOT for scaling read capacity.

**What is NoSQL vs SQL?**
* **SQL:** Relational, table-based, strict schema, scales vertically (CPU/RAM). Uses ACID properties.
* **NoSQL:** Non-relational, document/key-value based, dynamic schema, scales horizontally (adding more servers).

---

## ⚪ 10. AI + AWS (IMPORTANT FOR YOU)

**What AWS services support AI?**
* ML Infrastructure (GPU instances, Inferentia).
* Core ML Services (SageMaker).
* Applied AI Services (Rekognition, Polly, Lex, Comprehend, Translate).
* Generative AI (Amazon Bedrock, Amazon Q).

**SageMaker**
A fully managed service that provides every developer and data scientist with the ability to build, train, and deploy machine learning models quickly.

**Bedrock**
A fully managed service offering a choice of high-performing Foundation Models (FMs) from leading AI companies (Anthropic, Meta, AI21) via a single API, along with a broad set of capabilities to build Generative AI applications.

**How to secure ML pipelines?**
Use VPC endpoints (PrivateLink) for SageMaker, encrypt training data in S3 (KMS), encrypt model artifacts, use IAM roles for execution, isolate training and inference environments, and enable CloudTrail.

**What are risks in AI systems on cloud?**
Data poisoning, model inversion, prompt injection (for LLMs), sensitive data leakage via training data, unauthorized model access, and API abuse.

**How to secure:**
* **APIs:** Use API Gateway, require authentication (Cognito/IAM), implement rate limiting/throttling, and deploy AWS WAF.
* **Data pipelines:** Encrypt data at rest/transit, use private VPCs, enforce IAM least privilege, restrict S3 bucket access.
* **Model endpoints:** Deploy behind API Gateway/ALB, use VPC Endpoints, implement IAM authorization, monitor endpoint access via CloudTrail/CloudWatch.

---

## 🔥 11. Scenario-Based Questions (MOST IMPORTANT)

### 🔹 Scenario 1: Your EC2 is publicly exposed and hacked — what will you do?
* **Containment:** Immediately restrict the Security Group to deny all inbound traffic or isolate the instance into a restrictive quarantine SG. Do not terminate it yet (need evidence).
* **Investigation:** Check AWS CloudTrail logs to see how it was compromised. Check CloudWatch logs. Take an EBS snapshot for forensic analysis.
* **Remediation:** Rotate any exposed IAM access keys or credentials that might have been on the instance.
* **Eradication:** Once forensics are complete, terminate the compromised instance.
* **Prevention:** Patch vulnerabilities in the AMI, refine Security Groups (remove 0.0.0.0/0), use AWS Systems Manager instead of SSH for access.

### 🔹 Scenario 2: How do you secure an S3 bucket?
* **Block Public Access:** Enable "Block Public Access" at the account or bucket level.
* **Use IAM Policies:** Restrict access using strict Identity-based and Resource-based policies (Bucket Policies).
* **Enable Encryption:** Turn on default server-side encryption (SSE-KMS or SSE-S3).
* **Enable Logging/Versioning:** Turn on S3 Server Access Logging or CloudTrail Data Events. Enable versioning to recover from accidental deletions or ransomware.
* **MFA Delete:** Require MFA to delete object versions.

### 🔹 Scenario 3: How to secure a web app on AWS?
* **WAF:** Deploy AWS WAF on an Application Load Balancer or CloudFront to block SQLi, XSS, and bad bots.
* **Load Balancer (ALB):** Place the ALB in a public subnet to handle incoming traffic, terminating SSL/TLS here.
* **Private Backend:** Place EC2 instances or ECS containers in private subnets so they cannot be accessed directly from the internet.
* **IAM Roles:** Attach IAM Roles to the EC2/ECS tasks instead of hardcoding credentials in the app.
* **HTTPS/TLS:** Use AWS Certificate Manager (ACM) to provision SSL certificates and enforce HTTPS everywhere.

### 🔹 Scenario 4: How to design secure architecture?
* **Least Privilege:** Apply strict IAM policies and roles across all services and users.
* **Network Isolation:** Use VPCs, public/private subnets, Security Groups, NACLs, and VPC Endpoints to restrict network paths.
* **Monitoring & Auditing:** Enable CloudTrail, CloudWatch, GuardDuty, and AWS Config. Send alerts to a SIEM or SNS.
* **Encryption Everywhere:** Encrypt data at rest using KMS and in transit using TLS.
* **Incident Response Plan:** Automate responses to security events (e.g., Lambda isolating a compromised instance detected by GuardDuty).
