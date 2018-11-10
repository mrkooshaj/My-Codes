SELECT
             ROUND(
                 (SELECT * FROM
                   (SELECT CAST
                   (SUM(Population) AS FLOAT)
                    FROM (
                      SELECT Code,Population,CountryCode,Language,isOfficial
           FROM countrylanguage,country
           where Code = CountryCode
                 AND Language = 'English'
                 AND IsOfficial = 'T')))
                 /
                 (SELECT * FROM
                   (SELECT (SUM(Population))
                    FROM (
                      SELECT Name,Population FROM country)))
                 * 100,5) AS Percentage