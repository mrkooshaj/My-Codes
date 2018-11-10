SELECT
  Language,Population
FROM (
  SELECT Language,SUM(Speakers)
    AS Population
  FROM (
    SELECT CountryCode,Language,round(Population * Percentage / 100,0) AS Speakers
    from
      (SELECT CountryCode,Language,Percentage,Population
       FROM countrylanguage,country
       WHERE CountryCode = Code))
       GROUP BY Language
  ORDER BY Population
    DESC limit 5)
UNION
SELECT Language,Population
FROM (
  SELECT Language,SUM(Speakers) AS Population
  FROM (
    SELECT CountryCode,Language,round(Population * Percentage / 100,0)
      AS Speakers from
      (SELECT CountryCode,Language,Percentage,Population
       FROM countrylanguage,country
       WHERE CountryCode = Code))
  GROUP BY Language
  ORDER BY Population
    ASC limit 5)
ORDER BY Population
  DESC