# SQL Interview Preparation Guide

## 1. Basics & Fundamentals
- **SELECT / FROM**: Core clauses to retrieve data.
- **WHERE**: Filters rows before any grouping.
- **ORDER BY**: Sorts the output (ASC/DESC).
- **LIMIT / OFFSET**: Controls the number of rows returned and pagination.

## 2. Joins
- **INNER JOIN**: Returns only the rows where there is a match in both tables.
- **LEFT JOIN**: Returns all rows from the left table, and the matched rows from the right table (NULL if no match).
- **RIGHT JOIN**: Returns all rows from the right table, and the matched rows from the left table.
- **FULL OUTER JOIN**: Returns all rows from both tables, matching where possible, filling in with NULLs where there's no match.
- **CROSS JOIN**: Produces the Cartesian product of two tables (every row combined with every row).
- **SELF JOIN**: A regular join, but the table is joined with itself.

## 3. Aggregation & Grouping
- **GROUP BY**: Groups rows that have the same values into summary rows.
- **HAVING**: Filters grouped data (used instead of WHERE when filtering based on aggregate functions like COUNT, SUM, etc.).
- **Aggregate Functions**: `COUNT()`, `SUM()`, `AVG()`, `MIN()`, `MAX()`.

## 4. Window Functions
Window functions perform calculations across a set of table rows that are somehow related to the current row, without grouping them into a single output row.
- **ROW_NUMBER()**: Assigns a unique sequential integer to rows within a partition.
- **RANK()**: Similar to ROW_NUMBER but assigns the same rank to ties (skips numbers, e.g., 1, 2, 2, 4).
- **DENSE_RANK()**: Same as RANK but does not skip numbers (e.g., 1, 2, 2, 3).
- **LEAD()**: Accesses data from a subsequent row in the same result set.
- **LAG()**: Accesses data from a previous row in the same result set.
- **Syntax Example**: `RANK() OVER (PARTITION BY department_id ORDER BY salary DESC)`

## 5. Subqueries and CTEs
- **Subqueries**: A query nested inside another query (e.g., in SELECT, FROM, or WHERE clauses).
- **CTEs (Common Table Expressions)**: Defined using the `WITH` clause. They make complex queries much more readable and can be recursive.
  ```sql
  WITH DepartmentSales AS (
      SELECT dept_id, SUM(sales) as total_sales FROM sales GROUP BY dept_id
  )
  SELECT * FROM DepartmentSales WHERE total_sales > 10000;
  ```

## 6. Set Operations
Used to combine the result sets of two or more queries.
- **UNION**: Combines result sets and removes duplicates.
- **UNION ALL**: Combines result sets including duplicates (faster than UNION).
- **INTERSECT**: Returns only the rows that appear in both result sets.
- **EXCEPT / MINUS**: Returns rows from the first query that are not in the second query.

## 7. Useful Functions
- **COALESCE()**: Returns the first non-null value in a list (e.g., `COALESCE(phone, email, 'No Contact')`).
- **CAST() / CONVERT()**: Changes the data type of a value.
- **String Functions**: `CONCAT()`, `SUBSTRING()`, `LENGTH()`, `UPPER()`, `LOWER()`, `TRIM()`.
- **Date Functions**: `DATE_ADD()`, `DATEDIFF()`, `EXTRACT()`, `DATE_TRUNC()`.

## 8. Database Concepts & Optimization
- **Primary Key vs. Foreign Key**: 
  - Primary Key uniquely identifies a record.
  - Foreign Key creates a relationship between two tables.
- **Indexes**: Used to speed up data retrieval. 
  - B-Tree Index (most common)
  - Hash Index
  - Clustered vs. Non-Clustered Indexes (Clustered dictates the physical storage order).
- **ACID Properties (Transactions)**:
  - **Atomicity**: All or nothing.
  - **Consistency**: Leaves the DB in a valid state.
  - **Isolation**: Concurrent execution of transactions leaves the DB in the same state as if they were executed sequentially.
  - **Durability**: Once a transaction has been committed, it will remain committed even in the case of a system failure.
- **Normalization**:
  - **1NF**: Atomic values, no repeating groups.
  - **2NF**: 1NF + all non-key attributes are fully dependent on the primary key.
  - **3NF**: 2NF + no transitive dependencies (non-key attributes shouldn't depend on other non-key attributes).

## 9. Common Interview Problems
1. **Find the 2nd highest salary**:
   ```sql
   SELECT MAX(salary) FROM employee WHERE salary < (SELECT MAX(salary) FROM employee);
   ```
   Or using DENSE_RANK():
   ```sql
   WITH RankedSalaries AS (
       SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) as rnk FROM employee
   )
   SELECT salary FROM RankedSalaries WHERE rnk = 2 LIMIT 1;
   ```
2. **Find duplicate records**:
   ```sql
   SELECT email, COUNT(*) FROM users GROUP BY email HAVING COUNT(*) > 1;
   ```
3. **Cumulative sum**:
   ```sql
   SELECT date, amount, SUM(amount) OVER (ORDER BY date) as cumulative_sum FROM sales;
   ```
