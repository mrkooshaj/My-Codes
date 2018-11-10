/*Query20*/SELECT
  round(GNP/Population * 1000000,3)
    AS GNPAvg
FROM country
WHERE Name = 'Iran' AND
      HeadOfState = 'Ali Mohammad Khatami'