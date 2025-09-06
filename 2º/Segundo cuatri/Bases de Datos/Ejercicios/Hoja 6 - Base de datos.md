
```mysql
# Ejercicio 1
SELECT Name, Population FROM country;

# Ejercicio 2
SELECT city.CountryCode, AVG(city.Population) AvgPopulation
FROM city
GROUP BY CountryCode;

# Ejercicio 3
SELECT Continent, Sum(Population) / Sum(country.SurfaceArea) AS Density
FROM country
GROUP BY Continent
ORDER BY Density DESC;

# Ejercicio 4
SELECT Region
FROM country
GROUP BY Region
HAVING COUNT(*) > 10;

# Ejercicio 5
SELECT DISTINCT country.Name
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode

# Ejercicio 6
SELECT Name
FROM country
WHERE Code NOT IN (SELECT CountryCode
                   FROM countrylanguage
                   WHERE Language = 'Spanish');

# Ejercicio 7
SELECT c.Name AS Country, ci.Name AS City, ci.Population
FROM country c
JOIN city ci ON c.Code = ci.CountryCode
WHERE ci.Population = (
        SELECT MAX(c2.Population)
        FROM city c2
        WHERE c2.CountryCode = c.Code
    );

# Ejercicio 8
SELECT DISTINCT country.GovernmentForm
FROM country;

# Ejercicio 9
SELECT Name, Continent
FROM country
WHERE GovernmentForm LIKE '%Monarchy%'
ORDER BY Continent, Name;

# Ejercicio 10
SELECT Name
FROM country
WHERE LifeExpectancy IS NULL;

# Ejercicio 11
SELECT DISTINCT country.Continent
FROM country
WHERE HeadOfState IS NULL;

# Ejercicio 12
SELECT country.GovernmentForm
FROM country
WHERE Name = 'Swaziland';

# Ejercicio 13
SELECT Name
FROM country
WHERE Name <> country.LocalName;

# Ejercicio 14
SELECT Name,
       CASE
           WHEN country.IndepYear IS NULL THEN 'n.a.'
           WHEN country.IndepYear < 0 THEN 'a.c.'
           ELSE CAST(IndepYear AS CHAR)
       END AS Independencia
FROM country

# Ejercicio 15
SELECT District, SUM(city.Population) AS TotalPopulation
FROM city
GROUP BY District
ORDER BY TotalPopulation DESC
LIMIT 10;

# Ejercicio 16
SELECT District, COUNT(*) AS CityCount
FROM city
WHERE CountryCode = 'USA'
GROUP BY District

# Ejercicio 17
SELECT countrylanguage.Language
FROM countrylanguage
WHERE IsOfficial = 'T'
GROUP BY Language
HAVING COUNT(DISTINCT CountryCode) > 10;

# Ejercicio 18
SELECT Name, Continent, GNP, (GNP / Population) AS GNP_per_capita
FROM country
WHERE Population > 50000000
ORDER BY GNP_per_capita DESC;

# Ejercicio 19
SELECT Name, Continent, country.LifeExpectancy
FROM country
WHERE LifeExpectancy > 80;

# Ejercicio 20
SELECT Continent
FROM country
WHERE Population > 50000000 AND (GNP / Population) > 0.001
GROUP BY Continent
ORDER BY COUNT(*) DESC
LIMIT 1;
```