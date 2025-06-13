Hasta ahora hemos visto el [[Modelo E - R extendido]], veamos cómo se relaciona este con un modelo de datos relacional. 

**Modelo de datos**:
- E/R -> Conceptual
- Relacional -> Lógico

**Modelos de datos**:
- ***Estáticas*** -> Objetos, relacionan, representación. (E/R: entidades, interrelaciones, formas geométricas, etc.) - Es lo único que tiene un modelo conceptual, no como su contraparte lógica.
- ***Dinámicas*** -> Operativas como son consultar, insertar, modificar o borrar (estas son las 4 operativas básicas de una base de datos)
## Estructura del Modelo Relacional

| Nombre    | Nacionalidad | ... | Atributo N |         |
| --------- | ------------ | --- | ---------- | ------- |
| Rodríguez | Española     | ..  | XXXX       | Tupla1  |
| Sánchez   | Española     | ..  | XXXX       | Tupla2  |
| ...       | ...          | ..  | XXXX       | ....    |
| XXXX      | XXXX         | ..  | XXXX       | Tupla m |
Esto lo concebimos como una tabla de grado N (número de atributos) y cardinalidad m (número de filas)
### Elementos básicos
- **Relación** -> Representada mediante una tabla
- **Atributo** -> Representa mediante una columna (propiedades) 
- **Dominio** -> Conjunto válido de valores
- **Tupla** -> Ocurrencia de relación representada por filas
- **Grado** -> Número de atributos
- **Cardinalidad** -> Número de tuplas

Como características de una relación decimos:
- No puede haber tuplas duplicadas
- Orden de tuplas irrelevante
- Tabla plana, en cruce de un atributo y tupla sólo puede haber un valor
- Orden de atributos no significativo
### Clases de relación
- **Con nombre**: 
	- Persistentes
		- Base
		- Vistas
			- Individualizar el mostrado de información para poder dar al usuario una interfaz personalizada con unos datos que solo puede acceder alguien de su misma jerarquía (por ejemplo).
		- Vistas materializadas
	- Temporales
		- Autónomas
		- Vistas temporales
		- Vistas materializadas temporales
- **Sin nombre**: (siempre temporales)
	- Resultado final de consulta
	- Resultados intermedios de consulta
### Relación
- **Intensión**
	- Definir todos los atributos en un espacio finito siendo estos valores simplemente definidos
- **Extensión**
	- Dar todos los atributos en tuplas, siendo especificado el nombre de ese atributo y el valor del correspondiente dominio.
### Claves
- **Candidata
	- Conjunto no vacío de atributos que identifica sin error y de forma mínima cada tupla de una relación.
- **Primaria**
	- Elige usuario para identificar tuplas de relación. Se dice que es compuesta cuando está formada por más de un atributo.
		- *Regla de Integridad de Entidad* -> Ningún atributo que forme parte de esta clave puede tomar un valor nulo
- **Alternativa**
	- Clave candidata no elegida como primaria
- **Ajena**
	- Conjunto no vacío de atributos cuyos valores han de coincidir los valores de clave primaria. Han de estar esta y la primaria correspondiente definidas sobre el mismo dominio. Esta clave sirve para relacionar tablas. 
	- Lo que hace esta clave es relacionar tablas para indicar las relaciones que existen entre distintos tipos de datos