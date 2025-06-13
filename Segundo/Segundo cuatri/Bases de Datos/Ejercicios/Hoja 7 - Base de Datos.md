
```mysql
#### CONSULTAS ####

# Ejercicio 1
SELECT Language, SUM(country.Population * countrylanguage.Percentage / 100) AS TotalSpeakers
FROM countrylanguage
JOIN country ON country.Code = countrylanguage.CountryCode
WHERE IsOfficial = 'T'
GROUP BY Language;

# Ejercicio 2
SELECT city.Name
FROM city
JOIN country ON city.CountryCode = country.Code
WHERE country.LifeExpectancy < 50
ORDER BY city.Name;

# Ejercicio 3
SELECT DISTINCT country.Name
FROM country
JOIN city ON country.Code = city.CountryCode
WHERE city.Name LIKE 'A%';

# Ejercicio 4
SELECT DISTINCT country.Continent
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
WHERE countrylanguage.Language = 'German';

# Ejercicio 5
(SELECT DISTINCT Continent FROM country)
EXCEPT
(SELECT DISTINCT Continent FROM country JOIN countrylanguage ON country.Code = countrylanguage.CountryCode WHERE Language = 'Chinese');

# Ejercicio 6
SELECT Name AS cOUNTRY, countrylanguage.Language, countrylanguage.IsOfficial
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
ORDER BY country.Name;

# Ejercicio 7
SELECT country.Name
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
WHERE country.Continent = 'Europe'
GROUP BY country.Code
HAVING COUNT(*) = 1 AND MAX(IsOfficial) = 'T';

# Ejercicio 8
SELECT Name,
       'Inglés' AS Inglés,
        NULL AS Francés
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
WHERE Language = 'English'

UNION

SELECT Name,
       NULL AS Inglés,
       'Francés' as Francés
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
WHERE Language = 'French';

# Ejercicio 9
SELECT city.Name AS City, country.Name AS Country
FROM city
JOIN country ON city.CountryCode = country.Code
WHERE country.Continent IN ('North America', 'South America');

# Ejercicio 10
SELECT country.Name AS Country, city.Name AS Capital, country.Continent
FROM country
JOIN city ON country.Capital = city.ID
ORDER BY country.Continent;

# Ejercicio 11
SELECT country.Name AS Country, city.Name AS Capital, countrylanguage.Language
FROM country
JOIN city ON country.Capital = city.ID
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
WHERE countrylanguage.IsOfficial = 'T'
ORDER BY country.Name;

# Ejercicio 12
SELECT c1.Name AS Country1, c2.Name AS Country2, cl1.Language
FROM country c1
JOIN countrylanguage cl1 ON c1.Code = cl1.CountryCode
JOIN countrylanguage cl2 ON cl1.Language = cl2.Language AND cl1.IsOfficial = 'T'
JOIN country c2 ON cl2.CountryCode = c2.Code
WHERE c1.Continent = 'Europe' AND c2.Continent = 'Europe' AND c1.Code < c2.Code;

#### INSERT / UPDATE / DELETE ####

# Ejercicio 1
INSERT INTO city (Name, CountryCode, District, Population)
VALUES ('Nueva Ciudad', 'ESP', 'Madrid', 1000000)
## Si es posible, si CountryCode existe en country y los campos son válidos

# Ejercicio 2
INSERT INTO country
VALUES ('XYZ', 'Zetania', 'Europe', 'Western Europe', 12345.6, 1999, 500000
       , 75.7, 12345.6, NULL, 'Zetania', 'Republic', 'John Doe', NULL, 'ZY');

# Ejercicio 3
INSERT INTO city (Name, CountryCode, District, Population)
VALUES ('Zetópolis', 'XYZ', 'Central', 25000),
       ('Nova Zetania', 'XYZ', 'North', 15000);

# Ejercicio 4
INSERT INTO countrylanguage 
VALUES ('XYZ', 'Zetanian', 'T', 100.0)

# Ejercicio 5
UPDATE country
SET Continent = 'Europa'
WHERE Continent = 'Europe';

# Ejercicio 6
UPDATE country
SET GNP = GNP * 1.05
WHERE GNP < 500 AND GNP > 0;

# Ejercicio 7
DELETE FROM countrylanguage WHERE CountryCode = 'XYZ';
DELETE FROM city WHERE CountryCode = 'XYZ';
DELETE FROM country WHERE Code = 'XYZ';
# Se necesitan 3 comandos por la dependencia entre tablas (idiomas, ciudades, países)
```