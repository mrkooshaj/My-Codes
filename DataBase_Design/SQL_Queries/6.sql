SELECT District
FROM
  (SELECT
     District,SUM(Population)
      AS Population
   FROM city
   group by District
   HAVING Population >
          (SELECT Population
           FROM country
           ORDER BY Population
           LIMIT 1
           OFFSET 14)
   ORDER BY District)
