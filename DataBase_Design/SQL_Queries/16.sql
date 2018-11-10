SELECT DISTINCT 
  Language 
FROM countrylanguage as cl 
where NOT EXISTS
(SELECT CountryCode 
 FROM countrylanguage 
 WHERE IsOfficial = 'T' 
       AND Language = cl.Language) 
ORDER BY Language