SELECT DISTINCT
  Language
FROM countrylanguage
WHERE Language
      NOT IN
      (SELECT DistINCT
         Language
       FROM countrylanguage
       WHERE IsOfficial = 'T')
ORDER BY Language