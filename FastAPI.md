# FastAPI Interview Guide

FastAPI is a modern, fast (high-performance), web framework for building APIs with Python based on standard Python type hints. This guide covers the essential concepts you need for an interview.

---

## 1. Introduction

### Why FastAPI?
FastAPI has become the go-to framework for building AI and machine learning backends, largely replacing Flask and Django for API-centric applications. Key reasons include:
*   **Performance:** It is extremely fast, on par with NodeJS and Go, thanks to Starlette (for web routing) and Pydantic (for data validation).
*   **Ease of Use & Speed to Code:** It significantly increases development speed and reduces bugs by relying heavily on standard Python type hints.
*   **Automatic Documentation:** It automatically generates interactive API documentation (Swagger UI and ReDoc) out of the box based on the OpenAPI standard.
*   **Built-in Validation:** Input data is automatically validated against your Pydantic schemas, and it returns helpful JSON error responses if the validation fails.
*   **Asynchronous Support:** It was built from the ground up to support asynchronous programming (`async/await`), which is crucial for high-concurrency applications.

---

## 2. HTTP Methods (CRUD Operations)

APIs communicate over HTTP using different methods. FastAPI makes it very intuitive to map these methods to Python functions.

*   **GET:** Retrieve data. Used for fetching information without modifying anything on the server (e.g., getting a list of users or a specific article).
    *   *FastAPI Decorator:* `@app.get("/items/{item_id}")`
*   **POST:** Create new data. Used when submitting a payload (usually JSON) to the server to create a new resource (e.g., creating a new user account).
    *   *FastAPI Decorator:* `@app.post("/items/")`
*   **PUT:** Update existing data. Used to completely replace an existing resource with a new payload (e.g., updating a user's entire profile).
    *   *FastAPI Decorator:* `@app.put("/items/{item_id}")`
*   **DELETE:** Remove data. Used to delete a specified resource.
    *   *FastAPI Decorator:* `@app.delete("/items/{item_id}")`

*(Note: There is also **PATCH**, which is used for partial updates, changing only specific fields of a resource rather than replacing it entirely).*

---

## 3. Core Technologies

### Pydantic
Pydantic is a data validation and settings management library built heavily on Python type hints. It is the powerhouse behind FastAPI's data handling.
*   **What it does:** You define schemas (models) by creating classes that inherit from `pydantic.BaseModel`. You use type hints (like `str`, `int`, `List[str]`) to define the expected structure of the incoming JSON.
*   **Why it's crucial:** When a request comes in, Pydantic automatically parses the raw JSON, validates that the data types are correct (and attempts to coerce them if possible, e.g., turning the string `"123"` into the integer `123`), and throws a clean HTTP 422 error if the data is invalid. It guarantees that the data reaching your core logic is exactly the shape you expect.

### Async (Asynchronous Programming)
FastAPI natively supports the `async/await` syntax in Python, which is vital for building performant web applications.
*   **The Problem:** In a synchronous framework (like standard Flask), if a request has to wait for a database query or an external API call (I/O operations), the entire worker process is blocked. It can't handle any other requests during that time.
*   **The Solution (Async):** With `async def`, when your code hits an `await` statement (e.g., `await database.fetch(...)`), it releases control back to the event loop. The event loop can then pick up and process other incoming HTTP requests while waiting for that database query to finish in the background. This allows a single server to handle thousands of concurrent connections efficiently.

---

## 4. Advanced Concepts (Bonus Points)

### Dependency Injection
FastAPI has a very powerful and intuitive built-in Dependency Injection system.
*   **What is it?** A way for a function to declare things it needs (dependencies) to work, and the framework provides them automatically.
*   **Use cases:** It's heavily used for sharing logic (like database connections), enforcing security/authentication (e.g., "this endpoint depends on a valid JWT token"), and minimizing code repetition.
*   *Implementation:* You use the `Depends()` class. E.g., `def read_items(db: Session = Depends(get_db)):`

### OpenAPI and Swagger UI
Because FastAPI forces you to use type hints and Pydantic models, it inherently knows exactly what your API looks like—what endpoints exist, what data they expect, and what they return.
*   It automatically generates an OpenAPI schema (formerly Swagger).
*   By default, if you run a FastAPI app and go to `/docs` in your browser, you get a fully interactive Swagger UI where you can test your API endpoints directly from the browser without needing Postman.
