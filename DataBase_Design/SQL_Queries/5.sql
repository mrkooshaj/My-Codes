SELECT Name
FROM city
WHERE
  NOT EXISTS(
      SELECT Capital
      FROM country
      WHERE country.Capital = city.ID)
ORDER BY city.Population
  DESC
LIMIT 1