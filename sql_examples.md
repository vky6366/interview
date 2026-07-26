# SQL Basics and Examples

This guide covers the fundamental SQL concepts frequently asked in interviews, along with query examples and explanations.

## 1. SELECT
The `SELECT` statement is used to retrieve data from a database.

```sql
-- Retrieve all columns from the employees table
SELECT * FROM employees;

-- Retrieve specific columns (name and salary)
SELECT name, salary FROM employees;
```

## 2. WHERE
The `WHERE` clause is used to filter records, extracting only those that fulfill a specified condition.

```sql
-- Find employees who earn more than 50,000
SELECT * FROM employees WHERE salary > 50000;
```

**Common Operators used with WHERE:**
*   `=` : Equal
*   `!=` or `<>` : Not equal
*   `>` : Greater than
*   `<` : Less than
*   `>=` : Greater than or equal to
*   `<=` : Less than or equal to
*   `AND` : True if all conditions separated by AND are true
*   `OR` : True if any of the conditions separated by OR is true
*   `NOT` : Displays a record if the condition(s) is NOT TRUE
*   `IN` : Specify multiple possible values for a column
*   `BETWEEN` : Select values within a given range
*   `LIKE` : Search for a specified pattern in a column

## 3. ORDER BY
The `ORDER BY` keyword is used to sort the result-set in ascending or descending order.

```sql
-- Sort employees by salary in descending order (highest to lowest)
SELECT * FROM employees ORDER BY salary DESC;
```

## 4. LIMIT
The `LIMIT` clause is used to specify the maximum number of records to return. It is very useful for testing queries on large tables.

```sql
-- Retrieve only the first 5 records
SELECT * FROM employees LIMIT 5;
```

## 5. Aggregate Functions
Aggregate functions perform a calculation on a set of values and return a single value.

*   `COUNT()`: Returns the number of rows.
*   `SUM()`: Returns the total sum of a numeric column.
*   `AVG()`: Returns the average value of a numeric column.
*   `MAX()`: Returns the largest value.
*   `MIN()`: Returns the smallest value.

```sql
-- Calculate the average salary of all employees
SELECT AVG(salary) FROM employees;
```

## 6. GROUP BY
The `GROUP BY` statement groups rows that have the same values into summary rows. It is often used with aggregate functions.

```sql
-- Count the number of employees in each department
SELECT department, COUNT(*) 
FROM employees 
GROUP BY department;
```
*Explanation:* This query groups the table by the unique values in the `department` column, and then calculates the count of rows for each department.

## 7. HAVING
The `HAVING` clause was added to SQL because the `WHERE` keyword cannot be used with aggregate functions.

```sql
-- Find departments that have more than 5 employees
SELECT department, COUNT(*) 
FROM employees 
GROUP BY department
HAVING COUNT(*) > 5;
```
**Important Difference (Often Asked in Interviews):**
*   `WHERE` filters rows **before** the grouping occurs.
*   `HAVING` filters groups **after** the grouping occurs.

## 8. JOINS ⭐⭐⭐⭐⭐
Joins are used to combine rows from two or more tables, based on a related column between them. This is arguably the most important SQL topic.

**Example Tables:**
*   **Employee**: `id`, `name`, `dept_id`
*   **Department**: `id`, `dept`

### INNER JOIN
Returns records that have matching values in both tables.

```sql
-- Get employee names and their respective department names
SELECT e.name, d.dept 
FROM Employee e 
INNER JOIN Department d 
ON e.dept_id = d.id;
```

### LEFT JOIN
Returns all records from the left table, and the matched records from the right table. If there is no match, the right side will contain NULL.

```sql
-- Get all employees and their departments. 
-- If an employee has no department (or a missing dept_id), department will be NULL.
SELECT e.name, d.dept 
FROM Employee e 
LEFT JOIN Department d 
ON e.dept_id = d.id;
```

### RIGHT JOIN
Opposite of LEFT JOIN. Returns all records from the right table, and the matched records from the left table.

### FULL OUTER JOIN
Returns all records when there is a match in either left or right table. (Note: Not all databases support this directly, e.g., MySQL requires combining LEFT and RIGHT JOINs with UNION).

## 9. DISTINCT
The `SELECT DISTINCT` statement is used to return only distinct (different) values.

```sql
-- Find all unique cities where customers are located
SELECT DISTINCT city FROM customers;
```

## 10. Interview Theory: DELETE vs. TRUNCATE vs. DROP

Understanding the differences between these three commands is a very common interview question.

| Feature | `DELETE` | `TRUNCATE` | `DROP` |
| :--- | :--- | :--- | :--- |
| **Action** | Deletes specific rows from a table | Deletes all rows from a table | Deletes the entire table structure and data |
| **Conditioning** | Can use a `WHERE` clause to filter | No `WHERE` clause allowed | No `WHERE` clause allowed |
| **Rollback** | Rollback is possible (if within a transaction) | Usually limited or not possible | No rollback possible |
| **Performance**| Slower (logs individual row deletions) | Faster (deallocates data pages) | Fastest (removes metadata) |
