# 04. High-Frequency SQL Interview Problems & Patterns

> **Infosys SP L3 Must-Solve Problems:** These exact problem patterns account for over 90% of SQL coding questions in technical rounds.

---

## 1. Second Highest & Nth Highest Salary

### Problem: Find the 2nd Highest Salary in `Employee` table (Handle ties and return `NULL` if no 2nd exists).

#### Method 1: Subquery with `MAX()` (Standard across all SQL dialects)
```sql
SELECT MAX(salary) AS SecondHighestSalary
FROM Employee
WHERE salary < (SELECT MAX(salary) FROM Employee);
```

#### Method 2: Generic Nth Highest using Window Function (`DENSE_RANK()`)
```sql
WITH RankedSalaries AS (
    SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) AS rnk
    FROM Employee
)
SELECT salary AS NthHighestSalary
FROM RankedSalaries
WHERE rnk = 2 -- Change to N for Nth highest
LIMIT 1;
```

#### Method 3: `LIMIT` / `OFFSET` (MySQL / PostgreSQL)
```sql
SELECT DISTINCT salary AS SecondHighestSalary
FROM Employee
ORDER BY salary DESC
LIMIT 1 OFFSET 1; -- (For Nth: OFFSET N-1)
```

---

## 2. Highest Salary per Department & Top N per Department

### Problem: Find employees who have the highest salary in each department.

#### Method 1: Using Window Function with CTE (Most Optimal & Standard)
```sql
WITH RankedEmployees AS (
    SELECT 
        d.dept_name,
        e.name AS employee_name,
        e.salary,
        DENSE_RANK() OVER (PARTITION BY e.dept_id ORDER BY e.salary DESC) AS rnk
    FROM Employees e
    JOIN Departments d ON e.dept_id = d.dept_id
)
SELECT dept_name, employee_name, salary
FROM RankedEmployees
WHERE rnk = 1; -- For Top N per dept: WHERE rnk <= N
```

#### Method 2: Using Correlated Subquery
```sql
SELECT d.dept_name, e.name, e.salary
FROM Employees e
JOIN Departments d ON e.dept_id = d.dept_id
WHERE (e.dept_id, e.salary) IN (
    SELECT dept_id, MAX(salary)
    FROM Employees
    GROUP BY dept_id
);
```

---

## 3. Employees Earning More than Department Average

```sql
SELECT e.name, e.salary, e.dept_id, dept_avg.avg_salary
FROM Employees e
JOIN (
    SELECT dept_id, AVG(salary) AS avg_salary
    FROM Employees
    GROUP BY dept_id
) dept_avg ON e.dept_id = dept_avg.dept_id
WHERE e.salary > dept_avg.avg_salary;
```

---

## 4. Find and Delete Duplicate Records

```
Sample Table: Person (id, email)
Rows: (1, 'a@b.com'), (2, 'a@b.com'), (3, 'c@d.com')
```

### 1. Find Duplicate Emails
```sql
SELECT email, COUNT(*) AS duplicate_count
FROM Person
GROUP BY email
HAVING COUNT(*) > 1;
```

### 2. Delete Duplicates (Keep only the smallest `id` for each duplicate email)

#### Approach A: Using Self-Join (`DELETE` with Join)
```sql
DELETE p1
FROM Person p1
JOIN Person p2 ON p1.email = p2.email AND p1.id > p2.id;
```

#### Approach B: Using Window Function CTE
```sql
WITH Duplicates AS (
    SELECT id, ROW_NUMBER() OVER (PARTITION BY email ORDER BY id ASC) AS row_num
    FROM Person
)
DELETE FROM Person 
WHERE id IN (SELECT id FROM Duplicates WHERE row_num > 1);
```

---

## 5. Unassigned Records (Anti-Joins)

### Problem: Find Departments with 0 employees, and Employees with no department.

```sql
-- Departments with NO employees
SELECT d.dept_id, d.dept_name
FROM Departments d
LEFT JOIN Employees e ON d.dept_id = e.dept_id
WHERE e.emp_id IS NULL;

-- Employees with NO assigned department
SELECT e.emp_id, e.name
FROM Employees e
LEFT JOIN Departments d ON e.dept_id = d.dept_id
WHERE d.dept_id IS NULL;
```

---

## 6. Latest / Most Recent Record per User

### Problem: Find each customer's most recent order.

```sql
WITH RankedOrders AS (
    SELECT 
        order_id, 
        customer_id, 
        order_date, 
        total_amount,
        ROW_NUMBER() OVER (PARTITION BY customer_id ORDER BY order_date DESC, order_id DESC) AS rn
    FROM Orders
)
SELECT order_id, customer_id, order_date, total_amount
FROM RankedOrders
WHERE rn = 1;
```

---

## 7. Consecutive Records (e.g., 3+ Consecutive Logins / Numbers)

### Problem: Find all numbers that appear at least three times consecutively in `Logs(id, num)`.

#### Method 1: Using `LEAD()` and `LAG()`
```sql
WITH NumberHistory AS (
    SELECT 
        num,
        LAG(num, 1) OVER (ORDER BY id) AS prev_num,
        LEAD(num, 1) OVER (ORDER BY id) AS next_num
    FROM Logs
)
SELECT DISTINCT num AS ConsecutiveNums
FROM NumberHistory
WHERE num = prev_num AND num = next_num;
```

#### Method 2: Island and Gaps Technique (`ROW_NUMBER()` Difference)
```sql
WITH NumberGroups AS (
    SELECT 
        num,
        (id - ROW_NUMBER() OVER (PARTITION BY num ORDER BY id)) AS grp
    FROM Logs
)
SELECT num
FROM NumberGroups
GROUP BY num, grp
HAVING COUNT(*) >= 3;
```

---

## 8. Employees with Same Salary (Pairs)

```sql
SELECT e1.name AS Employee_1, e2.name AS Employee_2, e1.salary
FROM Employees e1
JOIN Employees e2 ON e1.salary = e2.salary AND e1.emp_id < e2.emp_id;
```
