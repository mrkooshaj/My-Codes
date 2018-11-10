SELECT District
FROM (
  SELECT Code,SpeakingOfficial,District,Pop
  from (
    SELECT Code,ROUND(Population * Percntg / 100,0) AS SpeakingOfficial
    FROM (
      SELECT CountryCode,SUM(Percentage) AS Percntg
      FROM (
        SELECT *
        FROM countrylanguage
        WHERE IsOfficial = 'T')
      GROUP BY CountryCode),(
      SELECT Code,Population
      FROM country)
    WHERE Code = CountryCode),
    (SELECT District
       ,SUM(Population)
        AS Pop,CountryCode
     FROM (
       SELECT Name,District,Population,CountryCode
       FROM city
       ORDER BY District)
     GROUP BY District)
  WHERE Code = CountryCode and
        District in (
          SELECT District
          FROM city
          WHERE ID
                IN (
                  SELECT Capital FROM country)))
WHERE Pop > SpeakingOfficial
ORDER BY District