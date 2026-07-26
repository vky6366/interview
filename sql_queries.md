# Common SQL Interview Queries

Here is a collection of the most commonly asked SQL queries in technical interviews, covering various concepts such as joins, grouping, subqueries, and window functions.

## 1. Find the Second Highest Salary
**Scenario:** Given an `Employee` table with columns `Id` and `Salary`, find the second highest salary.

```sql
-- Using subquery
SELECT MAX(Salary) AS SecondHighestSalary
FROM Employee
WHERE Salary < (SELECT MAX(Salary) FROM Employee);

-- Using OFFSET (MySQL/PostgreSQL)
SELECT (
    SELECT DISTINCT Salary 
    FROM Employee 
    ORDER BY Salary DESC 
    LIMIT 1 OFFSET 1
) AS SecondHighestSalary;
```

## 2. Find the Nth Highest Salary
**Scenario:** Find the Nth highest salary from the `Employee` table.

```sql
-- Using DENSE_RANK() window function
WITH RankedSalaries AS (
    SELECT Salary, DENSE_RANK() OVER (ORDER BY Salary DESC) AS Rank
    FROM Employee
)
SELECT DISTINCT Salary 
FROM RankedSalaries 
WHERE Rank = N; -- Replace N with the desired number
```

## 3. Department Highest Salary
**Scenario:** Find employees who have the highest salary in each of the departments.
**Tables:** `Employee` (Id, Name, Salary, DepartmentId), `Department` (Id, Name)

```sql
SELECT d.Name AS Department, e.Name AS Employee, e.Salary
FROM Employee e
JOIN Department d ON e.DepartmentId = d.Id
WHERE (e.DepartmentId, e.Salary) IN (
    SELECT DepartmentId, MAX(Salary)
    FROM Employee
    GROUP BY DepartmentId
);
```

## 4. Find Duplicate Emails
**Scenario:** Write a query to find all duplicate emails in a table named `Person`.

```sql
SELECT Email
FROM Person
GROUP BY Email
HAVING COUNT(Email) > 1;
```

## 5. Employees Earning More Than Their Managers
**Scenario:** Find employees who earn more than their managers. `Employee` table has `Id`, `Name`, `Salary`, and `ManagerId`.

```sql
SELECT e1.Name AS Employee
FROM Employee e1
JOIN Employee e2 ON e1.ManagerId = e2.Id
WHERE e1.Salary > e2.Salary;
```

## 6. Customers Who Never Order
**Scenario:** Find all customers who never ordered anything.
**Tables:** `Customers` (Id, Name), `Orders` (Id, CustomerId)

```sql
-- Using LEFT JOIN
SELECT c.Name AS Customers
FROM Customers c
LEFT JOIN Orders o ON c.Id = o.CustomerId
WHERE o.Id IS NULL;

-- Using NOT IN
SELECT Name AS Customers
FROM Customers
WHERE Id NOT IN (SELECT CustomerId FROM Orders);
```

## 7. Find Consecutive Numbers
**Scenario:** Find all numbers that appear at least three times consecutively in a `Logs` table (Id, Num).

```sql
-- Using window functions LEAD
WITH NumberGroups AS (
    SELECT Num,
           LEAD(Num, 1) OVER (ORDER BY Id) AS Next1,
           LEAD(Num, 2) OVER (ORDER BY Id) AS Next2
    FROM Logs
)
SELECT DISTINCT Num AS ConsecutiveNums
FROM NumberGroups
WHERE Num = Next1 AND Num = Next2;
```

## 8. Get the Top 3 Salaries per Department
**Scenario:** Find employees who earn the top three salaries in each department.

```sql
WITH RankedEmployees AS (
    SELECT e.Name AS Employee, e.Salary, d.Name AS Department,
           DENSE_RANK() OVER (PARTITION BY e.DepartmentId ORDER BY e.Salary DESC) AS Rank
    FROM Employee e
    JOIN Department d ON e.DepartmentId = d.Id
)
SELECT Department, Employee, Salary
FROM RankedEmployees
WHERE Rank <= 3;
```

## 9. Delete Duplicate Emails
**Scenario:** Write a SQL query to delete all duplicate email entries in a table named `Person`, keeping only unique emails based on its smallest Id.

```sql
DELETE p1
FROM Person p1, Person p2
WHERE p1.Email = p2.Email AND p1.Id > p2.Id;
```

## 10. Rising Temperature
**Scenario:** Find all dates' `Id` with higher temperatures compared to its previous dates (yesterday). `Weather` table has `Id`, `RecordDate`, `Temperature`.

```sql
-- Using self-join and DATEDIFF
SELECT w1.Id
FROM Weather w1
JOIN Weather w2 ON DATEDIFF(w1.RecordDate, w2.RecordDate) = 1
WHERE w1.Temperature > w2.Temperature;
```
