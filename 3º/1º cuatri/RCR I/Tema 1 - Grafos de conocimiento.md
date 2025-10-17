## Introducción a la Web Semántica
### ¿Qué es?
- Extensión de la web actual propuesta por Tim Berners-Lee
- Transforma la web de documentos en una web de datos con significado
- Diseñada para ser entendida tanto por humanos como por máquinas
### Problemas de la web actual
- Falta de estructura semántica
- Datos aislados y no conectados
- Dependencia excesiva de motores de búsqueda
- Dificultad para integrar datos de múltiples fuentes
- Los datos carecen de contexto y significado para las máquinas
### Comparación

| Web Actual                             | Web Semántica                                          |
| -------------------------------------- | ------------------------------------------------------ |
| Documentos enlazados por hipervínculos | Datos conectados con significado semántico             |
| Pensada para humanos                   | Pensada para humanos y máquinas                        |
| Sin contexto asociado                  | Datos con significado que las máquinas pueden entender |
| Dificultad para integrar datos         | Datos fácilmente compartibles y reutilizables          |
### Objetivos y características
- **Interoperabilidad de datos**: entre aplicaciones, sistemas y organizaciones
- **Ejemplos**: OBO, Linked Universities, GoodRelations Ontology
- **Tecnologías clave**
	- Lenguajes para representar conocimiento (RDF, RDFS, OWL)
	- Lenguaje de consulta (SPARQL)
	- Herramientas diversas
### Grafos de conocimiento
- Modelo flexible para organizar información
- Supera la rigidez del modelo relacional
- Fácil de extender y mejorar
- Usado por grandes compañías: Google Knowledge Graph, Microsoft Bing, Facebook, eBay, IBM Watson.
## Resource Description Framework (RDF)
### Conceptos fundamentales
- **Framework descriptor de recursos** web
- Recomendación del W3C
- Modelo de datos equivalente a una red semántica
- Organiza información en grafos de triples
### Estructura de Triple RDF
- **Sujeto**: Recurso (IRI) o blank node
- **Predicado**: Relación binaria (IRI)
- **Objeto**: IRI, literal o blank node
### Identificadores
- **IRIs** (International Resource Identifiers): Identifican recursos únicos
- Ejemplos:
	- `http://www.urjc.es/` 
	- `http://dbpedia.org/resource/King_Juan_Carlos_University`
### Formatos de serialización
- **Turtle:** Legible para humanos, usa prefijos
- **RDF/XML** Sintaxis XML
- **N-Triples, TriG, N-Quads, JSON-LD, RDFa**
### Características especiales
- **Blank Nodes** Nodos anónimos sin IRI
- **Literales** Valores con tipos de datos
	- Tipos XML Schema: `xsd:string`, `xsd:integer`, `xsd:date`
	- Etiquetas de idioma: `"Boston"@en`
### Ejemplo en Turtle

```turtle
@prefix ex: <http://www.example.org/>.
@prefix dc: <http://purl.org/dc/elements/1.1/>.

ex:index.html dc:creator ex:staffid/85740 ;
				dc:language = "en" .
```
## Consulta de información en la Web Semántica
### SPARQL
**Introducción**
- Lenguaje de consulta para RDF
- Recomendación del W3C
- Sintaxis estilo SQL

**Estructura básica de consulta**
```sparql
PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
PREFIX pre: <http://www.example.org/>

SELECT ?nom ?ape
WHERE {
    ?x rdf:type pre:Empleado.
    ?x pre:nombre ?nom.
    ?x pre:apellido ?ape.
}
```

#### Características del lenguaje

**Patrones básicos**
- SELECT - Devuelve tabla de resultados
- SELECT * - Selecciona todas las variables
- Sintaxis abreviada con ; para compartir sujeto

**Filtros**
```sparql
FILTER (?hab >= 200000)
FILTER (regex(?nom, "Alberto", "i"))
FILTER (?fecha > "1980-05-1"^^xsd:date)
```

**Patrones opcionales (OPTIONAL)**
- Permite información no presente

**Uniones (UNION)**
- Patrones alternativos

**Negación**
- `FILTER NOT EXISTS`
- `MINUS`

**Funciones de agregación**
- **COUNT, SUM, MIN, MAX, AVG, GROUP_CONCAT, SAMPLE**
- Uso con `GROUP BY` y `HAVING`

**Modificadores de resultados**
- **ORDER BY**: Ordenación
- **DISTINCT**: Elimina duplicados
- **LIMIT/OFFSET**: Paginación

**RDF Datasets**
- Grafo por defecto + grafos nombrados
- Consulta múltiples grafos

**Property paths**
- Consulta rutas complejas en el grafo
- **Operadores principales**
	- `/`: Secuencia (`property1/property2`)
	- `|`: Alternativa (`property1|property2`)
	- `*`: Cero o más repeticiones
	- `+`: Una o más repeticiones
	- `?`: Cero o una repetición

**Formas de consulta**
- **SELECT** Tabla de resultados
- **ASK** devuelve booleano (si existe solución)
- **DESCRIBE** Grado RDF con datos de objetos
- **CONSTRUCT** Genera nuevo grafo RDF

**Endpoints SPARQL**
- Servicios que aceptan consultas SPARQL vía HTTP
- Formatos de respuesta: XML, JSON, RDF, HTML, CSV, TSV
## RDF Schema (RDFS)
### Introducción
- Extensión de RDF para definir vocabularios
- Permite razonar sobre clases y no solo objetos individuales
- Recomendación del W3C
### Elementos principales

**Clases e Instancias**
- **rdfs:Class** - Define clases
- **rdf:type** - Relación de instanciación

```turtle
ex:Asignatura rdf:type rdfs:Class.
ex:IC rdf:type ex:Asignatura.
```

**Jerarquías de clases**
- **rdfs:subClassOf** - relación de subclase 

```turtle
ex:Catedratico rdfs:subClassOf ex:PersonalDocente.
```

**Propiedades**
- **rdf:Property** - Define propiedades
- **rdfs:domain** - Restricción de dominio
- **rdfs:range** - Restricción de rango

```turtle
ex:impartidaPor rdf:type rdf:Property;
               rdfs:domain ex:Asignatura;
               rdfs:range ex:PersonalDocente.
```

**Jerarquías de propiedades**
- **rdfs:subPropertyOf** - Relación de subpropiedad
### Propiedades Descriptivas
- **rdfs:comment** - Descripción legible para humanos
- **rdfs:label** - Etiqueta legible del recurso
- **rdfs:seeAlso** - Recurso con información adicional
### Limitaciones de RDFS
- Solo permite organización básica en jerarquías
- **Ámbito local** de las propiedades
- **No permite expresar**:
	- Clases disjuntas
	- Combinación booleana de clases
	- Restricciones de cardinalidad
	- Propiedades transitivas, simétricas, inversas