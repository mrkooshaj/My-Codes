SELECT Name AS Country_Name,City_Name,pp AS Population FROM (SELECT CountryCode,Name AS City_Name,Population AS pp FROM (SELECT CountryCode,Name,MAX(Population) AS Population FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode)

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode) GROUP BY CountryCode)

EXCEPT /*!*/

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode)

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode) GROUP BY CountryCode) GROUP BY CountryCode)

EXCEPT /*!*/

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode)

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode) GROUP BY CountryCode)

EXCEPT /*!*/

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode)

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM (SELECT CountryCode,Name,Population FROM city

EXCEPT

SELECT CountryCode,Name,MAX(Population) FROM city GROUP BY CountryCode) GROUP BY CountryCode) GROUP BY CountryCode) GROUP BY CountryCode) GROUP BY CountryCode) WHERE CountryCode IN (SELECT DISTINCT CountryCode FROM countrylanguage WHERE Language = 'English')

),country WHERE country.Code = CountryCode ORDER BY Population DESC 