select CountryCode,ct.name,round(CAST(ct.Population AS float)/ CAST(cnt.Population AS float) * 100 , 5) AS Percentage
FROM city as ct,country as cnt
WHERE cnt.Capital = ct.ID
ORDER BY CountryCode DESC