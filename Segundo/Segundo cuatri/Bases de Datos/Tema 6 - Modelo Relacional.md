## Presentación
Se introduce el modelo relacional por Codd con los siguientes objetivos en mente:
- **Independencia física** -> Cambios físicos no afectan a programas
- **Independencia lógica** -> Añadir, eliminar o modificar elementos no repercute en los programas y/o usuarios que acceden a ellos.
- **Flexibilidad** -> Adaptar datos al usuario
- **Uniformidad** -> Las estructuras lógicas son tablas
- **Sencillez** -> Fácil de comprender y utilizar 
Lo dividimos en dos aspectos principales: *propiedades estáticas* (estructura y restricciones) y *propiedades dinámicas* (operaciones y transformaciones). Veamos un resumen sobre cada
## Propiedades estáticas
Definen la estructura y las reglas que garantizan la integridad de los datos.
### Elementos básicos
- **Relación**: Estructura básica representada como una tabla
- **Atributo**: Columna de una tabla que representa una propiedad (ej: "Nombre")
- **Dominio**: Conjunto de valores válidos para un atributo (ej: "Nacionalidades")
- **Tupla**: Fila de una tabla que representa una ocurrencia de datos
- **Grado**: Número de atributos de una relación
- **Cardinalidad**: Número de tuplas en una relación
***Ejemplo***
Tabla **AUTOR** con atributos *Nombre, Nacionalidad, Institución*
- Grado 3 (columnas)
- Cardinalidad 4 (filas)
### Claves
- **Candidata**: Atributo(s) que identifican tuplas de forma única y mínima
- **Primaria**: Candidata elegida para identificar tuplas (no admite nulos)
- **Alternativa**: Candidata no seleccionada como primaria
- **Ajena**: Atributo(s) que referencia(n) la clave primaria de otra tabla
***Ejemplo***
- En la tabla **LIBRO**, *código* es clave primaria
- En **EDITORIAL**, *nombre_e* es clave primaria y clave ajena en **LIBRO**
### Restricciones

**Inherentes**
- NO hay tuplas duplicadas
- Orden de tuplas y atributos no importa
- **Integridad de Entidad:** Claves primarias no pueden ser nulas
- **Integridad Referencial:** Claves ajenas deben coincidir con claves primarias referenciadas o ser nulas
***Ejemplo***
Si borramos una editorial en **EDITORIAL**, las tuplas en **LIBRO** con esa editorial pueden:
- Borrarse en cascada
- Poner *nombre_e* a NULL

**Semánticas**
- Clave primaria
- Unicidad -> No pueden repetirse los valores de un conjunto de atributos
- Obligatoriedad -> NOT NULL
- Integridad referencial
- **CHECK:** Valida valores pero sobre un único elemento, puede tener o no nombre
- **Disparadores (Triggers):** Acciones automáticas ante eventos
- **ASSERTION**: Identico a **CHECK** pero puede afectar a diferentes elementos
### Vistas
- **Tablas virtuales** basadas en consultas. No almacenan datos físicamente
## Propiedades dinámicas
Las propiedades dinámicas describen las operaciones para transformar los datos entre estados válidos
### Operadores primitivos
- **Unarios** (actúan sobre una relación)
	- **Selección (**`σ`**)** Filtra tuplas que cumplen una condición
		- ***Ejemplo*** -> `σ nacionalidad="Española"(AUTOR)` Tuplas de autores españoles.
	- **Proyección (**`π`**)** Extrae columnas específicas, eliminando duplicados
		- ***Ejemplo*** -> `π nacionalidad(AUTOR)` Lista de nacionalidades únicas
- **Binarios** (actúan sobre dos relaciones)
	- **Unión (**`∪`**)** Combina tuplas de dos relaciones compatibles
		- ***Ejemplo*** -> `AUTOR ∪ EDITOR` Todos los autores y editores
	- **Diferencia (**`-`**)** Tuplas en R1 que no están en R2
		- ***Ejemplo*** -> `AUTOR - EDITOR` Autores que no son editores
	- **Producto Cartesiano (**`×`**)** Combina cada tupla de R1 con todas las de R2
		- ***Ejemplo*** -> `LIBRO × EDITORIAL` Todas las combinaciones posibles
### Operadores Derivados
- **Combinación (θ)** Une tablas basándose en una condición
	- **Combinación Natural (`*`)** Une por atributos con el mismo nombre
	- ***Ejemplo*** -> `LIBROS * EDITORIAL` Libros con datos de su editorial. Esto equivale a: `σ LIBRO.nombre_e=EDITORIAL.nombre_e(LIBRO × EDITORIAL)`
- **Intersección (**`∩`**)** Tuplas comunes en R1 y R2
	- ***Ejemplo*** `AUTOR ∩ EDITOR` Personas que son autores y editores
- **División (**`÷`**)** Tuplas de R1 que están relacionadas con todas las de R1
	- **Ejemplo:** `AUTOR_EDITORIAL ÷ EDITORIAL` Autores que publican en todas las editoriales listadas
### Ejemplo de álgebra relacional
**Consulta** "Nombres de autores españoles y sus instituciones"
1. Selección: `σ nacionalidad="Española"(AUTOR)`
2. Proyección: `π Nombre, Institución(...)`
## Reglas de Codd (Resumidas)
Codd definió 13 reglas para que un SGBD sea relacional. Algunas son:
- **Regla 0**: Un SGBD relacional debe gestionar la base de datos exclusivamente mediante sus capacidades relacionales
- **Regla 1**: Toda información se representa en tablas.
- **Regla 2**: Acceso a datos mediante clave primaria.
- **Regla 3**: Soporte para valores nulos.
- **Regla 5**: Lenguaje completo (SQL).
- **Regla 6**: Actualización de vistas.
- **Regla 8-9**: Independencia física/lógica de los datos.
- **Regla 10**: Las reglas de integridad deben definirse en el sublenguaje relacional
- **Regla 11:** Independencia de la distribución
- **Regla 12:** No subversión, si el SGBD permite un lenguaje de bajo nivel, no debe eludir reglas de integridad