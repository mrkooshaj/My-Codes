SELECT Language
FROM country,countrylanguage
WHERE Code = CountryCode
GROUP BY Language
HAVING MAX(IsOfficial) = 'F'
ORDER BY Language