SELECT Name,Population,SurfaceArea AS Area
FROM country
WHERE Continent In
      (SELECT Continent FROM country WHERE Name = 'Iran')
      AND Population >
          (SELECT Population FROM country WHERE Name = 'Iran')
AND SurfaceArea >
    (SELECT SurfaceArea FROM country WHERE Name = 'Iran')
ORDER BY Population DESC