# Introducción
## ¿Qué es SQL?
***Structured Query Language***, es un lenguaje estándar para gestionar y manipular bases de datos relacionales. Surgió como evolución del lenguaje SEQUEL (IBM) para su prototipo System R en los 70. El primer producto comercial que implementó SQL fue Oracle, seguido por otros sistemas como INGRES, IBM, DB2, etc.

Es un lenguaje declarativo (damos lo que queremos, no cómo obtenerlo) que opera con conjuntos de registros en lugar de trabajar registro a registro. Proporciona capacidades para:
- **Definición** de estructuras de datos (tablas, vistas, índices)
- **Manipulación** de datos (consultas, inserciones, actualizaciones)
- **Control** de acceso y transacciones
- **Programación** mediante procedimientos almacenados
Ejemplo básico: `SELECT * FROM clientes;` recupera todos los datos de la tabla clientes.
## Estado actual y futuro de SQL

SQL ha evolucionado a través de múltiples estándares

| **Versión** | **Características principales**                                   |
| ----------- | ----------------------------------------------------------------- |
| SQL-86/87   | Primer estándar ANSI                                              |
| SQL-92      | Mejoró restricciones, añadió combinaciones externas, SQL dinámico |
| SQL:1999    | Introdujo triggers, características orientadas a objetos          |
| SQL:2003    | Soporte para XML, secuencias                                      |
| SQL:2011    | Bases de datos temporales                                         |
| SQL:2016    | Compatibilidad con JSON                                           |
El futuro de SQL sigue siendo brillante, con nuevas versiones incorporando:
- Mejor integración con datos semiestructurados (JSON, XML)
- Soporte para análisis avanzado (OLAP)
- Funciones de inteligencia artificial y aprendizaje automático
- Mejoras en manejo de datos temporales y espaciales
# Sintaxis básica de SQL-92
## Lenguaje de Manipulación de Datos (LMD)
El LMD permite consultar y modificar los datos almacenados en la base de datos. Consultas básicas permite, siendo la estructura fundamental la sentencia `SELECT`:

```sql
SELECT [ALL|DISTINCT] {lista-atributos | *}
FROM nombre_tabla [, nombre_tabla, …]
[WHERE condición]
[GROUP BY agrupación]
[HAVING condición_grupo]
[ORDER BY ordenación];
```

**Ejemplo**
1. Consulta simple:

```sql
SELECT * FROM alumno;
```
Devuelve todos los atributos de todos los alumnos

2. Proyección (selección de columnas):

```sql
SELECT nombre, ciudad FROM alumno;
```
Muestra solo nombre y ciudad de cada alumno

3. Eliminación de duplicados:

```sql
SELECT DISTINCT ciudad FROM alumno;
```
Muestra cada ciudad solo una vez, aunque haya varios alumnos de ella.

**Operadores y condiciones**
- **Comparación**: =, <>, <, >, <=, >=
- **Aritméticos**: +, -, $*$, /
- **Lógicos**: AND, OR, NOT
- **Especiales**:
	- `BETWEEN` para rangos
	- `LIKE` para patrones de texto (% cualquier cadena, _ un carácter)
	- `IN` para conjuntos de valores
	- `IS NULL` para valores nulos

**Ejemplo complejo:**
```sql
SELECT * FROM alumno
WHERE precio > 20000 AND (ciudad = 'MADRID' or ciudad = 'GETAFE')
```

**Funciones de agrupación**
Permiten realizar cálculos sobre conjuntos de datos

| **Función** | **Descripción**  | **Ejemplo**                      |
| ----------- | ---------------- | -------------------------------- |
| COUNT       | Cuenta registros | `SELECT COUNT(*) FROM alumno`    |
| MAX         | Valor máximo     | `SELECT MAX(precio) FROM alumno` |
| MIN         | Valor mínimo     | `SELECT MIN(precio) FROM alumno` |
| AVG         | Promedio         | `SELECT AVG(precio) FROM alumno` |
| SUM         | Suma             | `SELECT SUM(precio) FROM alumno` |
**Ejemplo con GROUP BY**
```sql
SELECT ciudad, AVG(precio)
FROM alumno
GROUP BY ciudad;
```
Calcula el precio promedio por ciudad

*Combinaciones de tablas*:
- **Producto cartesiano**: Combina cada fila de una tabla con todas las de otra
```sql
SELECT * FROM alumno CROSS JOIN grupo;
```
- **Combinación interna**: Solo filas que cumplen la condición de join
```sql
SELECT a.nombre, g.curso
FROM alumno a JOIN grupo g ON a.cod_grupo = g.cod_grupo;
```
- **Combinaciones externas:**
	- LEFT JOIN: Todas las filas de la tabla izquierda aunque no tengan coincidencia
	- RIGHT JOIN: Todas las filas de la tabla derecha
	- FULL JOIN: Todas las filas de ambas tablas

*Consultas anidadas*
Permiten usar resultados de una consulta dentro de otra:
```sql
SELECT * FROM alumno
WHERE cod_grupo IN (SELECT cod_grupo FROM grupo WHERE curso='1');
```

*Operaciones de conjuntos*
- UNION: Combina resultados eliminando duplicados
- INTERSECT: Solo filas presentes en ambos resultados
- EXCEPT: Filas del primer resultado no presentes en el segundo

**Ejemplo**
```sql
SELECT nombre FROM alumno
UNION
SELECT nemp FROM empleado;
```

*Actualizaciones de datos*
- **INSERT**: Añade nuevos registros
```sql
INSERT INTO alumno VALUES (9, 'Eva', 'Fuenlabrada', NULL, 60000);
```
- **UPDATE**: Modifica registros existentes
```sql
UPDATE alumno SET precio = precio + 1000 WHERE ciudad = 'Madrid';
```
- **DELETE**: Elimina registros
```sql
DELETE FROM alumno WHERE nombre = 'Juan';
```
## Lenguaje de Definición de Datos (LDD)
Nos permite definir y modificar la estructura de las bases de datos

*Creación de tablas*
Sintaxis básica:
```sql
CREATE TABLE nombre_tabla (
  columna1 tipo [restricciones],
  columna2 tipo [restricciones],
  ...
  [restricciones de tabla]
);
```

**Ejemplo completo**
```sql
CREATE TABLE grupo (
	cod_grupo CHAR(3) PRIMARY KEY,
	curso CHAR(1) NOT NULL CHECK (curso BETWEEN '1' AND '4'),
	turno CHAR(1) DEFAULT 'M' CHECK (turno IN ('M', 'T'))
);

CREATE TABLE alumno (
	num_mat CHAR(3) PRIMARY KEY,
	nombre VARCHAR(20) UNIQUE,
	ciudad VARCHAR(25) NOT NULL,
	cod_grupo CHAR(3),
	precio INTEGER,
	FOREIGN KEY (cod_grupo) REFERENCES grupo(cod_grupo)
		ON DELETE SET NULL
		ON UPDATE CASCADE
)
```

*Tipos de datos comunes*
- **Caracteres**: CHAR(n), VARCHAR(n)
- **Numéricos**: INTEGER, NUMERIC(p, s), FLOAT
- **Fecha/hora**: DATE, TIME, TIMESTAMP
- **Especiales**: BLOB (datos binarios), CLOB (texto largo)

*Restricciones de integridad*
- **PRIMARY KEY** Clave primaria (única y no nula)
- **FOREIGN KEY** Clave foránea (referencia a otra tabla)
- **UNIQUE** Valores únicos con posibilidad a NULL
- **NOT NULL** No permite valores nulos
- **CHECK** Condición que deben cumplir los valores
- **DEFAULT** Valor por defecto

**Opciones para claves foráneas**
- ON DELETE: Qué hacer al borrar el registro referenciado
	- CASCADE: Borrar los registros que lo referencian también
	- SET NULL: Poner a NULL las referencias
	- SET DEFAULT: Poner al valor por defecto
	- NO ACTION: No permitir el borrado (por defecto)
- ON UPDATE: Similar para actualizaciones

*Vistas*
Son consultas almacenadas que se comportan como tablas virtuales:
```sql
CREATE VIEW alumnos_madrid AS
SELECT * FROM alumno WHERE ciudad = 'Madrid';
```

*Índices*
Mejoran el rendimiento de las consultas:
```sql
CREATE INDEX idx_alumno_ciudad ON alumno(ciudad);
```

*Modificación de estructuras*
- Añadir columnas
```sql
ALTER TABLE alumno ADD COLUMN fecha_nac DATE;
```
- Eliminar tablas
```sql
DROP TABLE alumno CASCADE;
```
## Lenguaje de Control de Datos (LCD)
Gestiona el control de acceso y las transacciones

*Transacciones*
Una transacción es una secuencia de operaciones que se ejecutan como una unidad atómica (todo o nada). Deben cumplir las propiedades ACID:
- **Atomicidad** Se ejecuta completamente o no se ejecuta
- **Consistencia** Lleva la BD de un estado válido a otro
- **Aislamiento** Las transacciones no interfieren entre sí
- **Durabilidad** Los cambios persisten tras completarse

**Comandos**:
- `BEGIN TRANSACTION` Inicia una transacción
- `COMMIT` Confirma los cambios permanentemente
- `ROLLBACK` Deshace todos los cambios de la transacción

**Ejemplo**
```sql
BEGIN TRANSACTION;
	UPDATE cuentas SET saldo = saldo - 100 WHERE id = 1;
	UPDATE cuentas SET saldo = saldo + 100 WHERE id = 2;
COMMIT;
```

*Control de acceso:*
- `GRANT` Otorga privilegios a usuarios
- `REVOKE` Revoca privilegios

**Ejemplo**
```sql
GRANT SELECT, INSERT ON alumno TO usuario1;
REVOKE DELETE ON grupo FROM usuario2;
```

**Privilegios comunes:**
- **SELECT** Permite consultar datos
- **INSERT** Permite añadir datos
- **UPDATE** Permite modificar datos
- **DELETE** Permite eliminar datos
- **ALL** Todos los privilegios