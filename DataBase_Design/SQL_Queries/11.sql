/*Query11*/SELECT Name,Cnt
from
  (SELECT Name, COUNT(Language) AS Cnt
   FROM (
     SELECT Name,Language
     FROM country,countrylanguage
     WHERE country.Code = CountryCode)
   GROUP BY Name)
WHERE Name
      IN
      (SELECT country.Name
       FROM country,city
       WHERE CountryCode = Code
             AND city.Name = 'Victoria')
ORDER BY Cnt
  DESC
