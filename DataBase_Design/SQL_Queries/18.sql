SELECT Region
  , ROUND(Pop/Surface,3) AS Density
FROM (SELECT Region,SUM(SurfaceArea) AS Surface ,
        SUM(Population) AS Pop
      FROM (
        SELECT Code,Region,Population,SurfaceArea FROM country)
      GROUP BY Region)
ORDER BY Density
  DESC

