SELECT
  Continent, TRUNCATE(10 * YearlyIncome * (POWER(1.1,LifeExpectancy) - 1),5) AS Income
FROM (
  SELECT Continent, s1/s2 AS YearlyIncome,s3/s2 as LifeExpectancy
  FROM (
    SELECT Continent,SUM(YearlyIncome * Population) AS s1, SUM(Population) AS s2, SUM(LifeExpectancy*Population) AS s3
    FROM (SELECT Name,Continent,(GNP/Population * 1000000) AS YearlyIncome,LifeExpectancy,Population
          from country)
    GROUP BY Continent)
  )
ORDER BY Income
  DESC