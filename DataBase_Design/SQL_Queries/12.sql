SELECT Name,Population,CountryCode
FROM city
WHERE CountryCode
      IN (
        SELECT CountryCode
        FROM city
        GROUP BY CountryCode
        HAVING Count(Name) < 3
)
GROUP BY CountryCode
HAVING MAX(Population)
ORDER BY Population DESC