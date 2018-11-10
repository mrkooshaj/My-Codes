SELECT Name
FROM country
WHERE Code
      IN (
        SELECT DISTINCT
          Code
        from country
        except
        SELECT DISTINCT
          CountryCode
        FROM countrylanguage
        WHERE IsOfficial = 'T')
ORDER BY Name