SELECT Continent,Language,Population 
FROM (SELECT Continent,Language,ROUND(SUM(pp),0) 
  AS Population FROM  
  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM 
    (SELECT CountryCode,Language,Percentage,Population,Continent 
     FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) 
  WHERE Continent = 'Asia') 
GROUP BY Language 
      ORDER BY Population DESC LIMIT 1)

UNION

SELECT Continent,Language,Population 
FROM (SELECT Continent,Language,ROUND(SUM(pp),0) 
  AS Population FROM  
  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM 
    (SELECT CountryCode,Language,Percentage,Population,Continent 
     FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) 
  WHERE Continent = 'Africa') 
GROUP BY Language 
      ORDER BY Population DESC LIMIT 1)

UNION 

SELECT Continent,Language,Population FROM (SELECT Continent,Language,ROUND(SUM(pp),0) AS Population FROM  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM (SELECT CountryCode,Language,Percentage,Population,Continent FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) WHERE Continent = 'Europe') GROUP BY Language ORDER BY Population DESC LIMIT 1)

UNION

SELECT Continent,Language,Population FROM (SELECT Continent,Language,ROUND(SUM(pp),0) AS Population FROM  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM (SELECT CountryCode,Language,Percentage,Population,Continent FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) WHERE Continent = 'North America') GROUP BY Language ORDER BY Population DESC LIMIT 1)

UNION

SELECT Continent,Language,Population FROM (SELECT Continent,Language,ROUND(SUM(pp),0) AS Population FROM  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM (SELECT CountryCode,Language,Percentage,Population,Continent FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) WHERE Continent = 'Oceania') GROUP BY Language ORDER BY Population DESC LIMIT 1)

UNION 

SELECT Continent,Language,Population FROM (SELECT Continent,Language,ROUND(SUM(pp),0) AS Population FROM  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM (SELECT CountryCode,Language,Percentage,Population,Continent FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) WHERE Continent = 'South America') GROUP BY Language ORDER BY Population DESC LIMIT 1)

UNION

SELECT Continent,Language,Population FROM (SELECT Continent,Language,ROUND(SUM(pp),0) AS Population FROM  (SELECT Language,Percentage*Population / 100 as pp, Continent FROM (SELECT CountryCode,Language,Percentage,Population,Continent FROM countrylanguage,country WHERE IsOfficial = 'F' AND CountryCode = Code) WHERE Continent = 'Antarctica') GROUP BY Language ORDER BY Population DESC LIMIT 1)

ORDER BY Population DESC