SELECT Name
FROM country
WHERE GovernmentForm LIKE ('%Republic%')
      AND
      NOT EXISTS(
          SELECT Language
          FROM countrylanguage
          WHERE IsOfficial = 'T'
                AND Percentage > 20
                AND CountryCode = country.Code) EXCEPT
          SELECT Name
            FROM country
              WHERE GovernmentForm
                    LIKE ('%Republic%')
      AND
      NOT EXISTS(
          SELECT Language
          FROM countrylanguage
          WHERE IsOfficial = 'T'
                AND CountryCode = country.Code)