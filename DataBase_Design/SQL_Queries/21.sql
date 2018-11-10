SELECT
             SOUNDEX(Name) AS Sdx,Name
           FROM country
           ORDER BY Sdx ASC,
             Name DESC
