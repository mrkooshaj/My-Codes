/*Query7*/SELECT District
FROM
  (SELECT District, MAX(Population)
   FROM
     (SELECT distinct
        District,SUM(Population) AS Population
      FROM city as c1
      WHERE NOT EXISTS(
          SELECT Name
          FROM city as c2
          WHERE ID IN
                (SELECT Capital
                 FROM country)
                AND
                c2.District = c1.District)
      group by District))