## Introducción a la Web Semántica
Hablamos de web semántica cuando nos referimos a intentar hacer explicable la información para que las propias máquinas (web, algoritmos, etc.) la comprendan.
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

| Característica    | Web Actual                                                     | Web Semántica                                                                     |
| ----------------- | -------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| **Unidad Básica** | Documentos enlazados por hipervínculos                         | Datos conectados con significado semántico                                        |
| **Destinatario**  | Los humanos (lectura visual)                                   | Los humanos y máquinas                                                            |
| **Contexto**      | No tienen significado los datos pal ordenador (son solo texto) | Datos con significado explícito y estructurado                                    |
| **Integración**   | Difícil. Los datos están aislados en "silos"                   | Fácil. Se comparten y reutilizan los datos entre aplicaciones (interoperabilidad) |
### Objetivos y características
- **Interoperabilidad de datos**: que diferentes aplicaciones, sistemas y organizaciones puedan intercambiar datos y "entenderse" automáticamente.
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
### Architecture Stack
Para que todo esto funcione, necesitamos varias capas de tecnología:
- **Identificadores (URI/IRI) + UNICODE:** Dar nombres únicos a las cosas y usar cualquier idioma
- **Sintaxis (XML/Turtle):** Cómo escribimos los datos
- **Intercambio de datos (RDF):** El modelo básico de datos (el grafo)
- **Taxonomías (RDFS):** Vocabulario básico (qué es una clase, qué es una propiedad, etc...)
- **Ontologías (OWL):** Lógica compleja (restricciones, equivalencias...)
- **Consultas (SPARQL):** Lenguaje para hacer preguntas al grafo.
## Resource Description Framework (RDF)
### Conceptos fundamentales
- **Framework descriptor de recursos** web
- Recomendación del W3C
- Modelo de datos equivalente a una red semántica
- Organiza información en grafos de triples
### Estructura de Triple RDF (Grafo de triples)
En vez de tablas, usamos un grafo que se forma conectando nodos con flechas. La unidad mínima es el Triple (o Sentencia), que funciona igual que una frase simple en lengua: **Sujeto + Predicado + Objeto**
- **Sujeto**: Recurso (IRI) o blank node - De quién hablamos
- **Predicado**: Recurso IRI - La relación
- **Objeto**: IRI, literal o blank node - El valor
- ***Ejemplos***
	- Sujeto: `http://www.urjc.es/`
	- Predicado: `está_en`
	- Objeto: `Madrid`
### Elementos de RDF
1. **IRIs** (Identificadores): Son como DNIs únicos para cosas en la web. Suelen parecerse a URLs
2. **Literales** Valores concretos (datos puros). Pueden tener:
	- **Tipo de dato**: `xsd:integer`, `xsd:date`. Ej: `"1999-08-16"^^xsd:date`.
	- **Idioma**: `"Boston"@en` o `"Madrid"@es`
3. **Blank Nodes (Nodos anónimos)**: Son nodos que existen pero no tienen un identificador global (IRI). Se usan cuando quieres decir "hay algo que cumple esto, pero no necesito dearle un nombre oficial". Se representan a veces como `[]` o `_:b1`.
### Formatos de serialización (Cómo escribirlo)
Un grafo es abstracto, pero para guardarlo en un archivo necesitamos escribirlo. Usamos los siguientes formatos:
- **Turtle:** Legible para humanos, usa prefijos
- **RDF/XML** Muy verboso, difícil para humanos, pero bueno para máquinas antiguas
- **N-Triples**: Muy simple, una línea por triple, sin prefijos (archivos muy grandes)
- **JSON-LD** Formato JSON para desarrolladores web
### Ejemplo en Turtle (Explicado)

```turtle
# Prefijos para no escribir las URLs enteras todo el rato
@prefix ex: <http://www.example.org/>.
@prefix dc: <http://purl.org/dc/elements/1.1/>.
@prefix xsd: <http://www.w3.org/2001/XMLSchema#>.

# El sujeto "index.html" tiene un creador (staffid/85740)
# El punto y coma (;) significa "y también sobre el MISMO sujeto..."
ex:index.html dc:creator ex:staffid/85740 ;
				# Tiene fecha de creación
				ex:creation_date "1999-08-16"^^xsd:date ;
				# Y está en inglés
				dc:language = "en".
```
## Consulta de información en la Web Semántica
### SPARQL
**Introducción**
Es el SQL de los grafos. Sirve para buscar patrones dentro del grafo RDF.

**Estructura básica de consulta**
Busca **patrones** que encajen en el grafo. Si el grafo tiene `A -> flecha -> B`, tú buscas `?x -> flecha -> ?y` y él te devuelve qué son `x` e `y`.

```sparql
PREFIX pre: <http://www.example.org/>

SELECT ?nombre ?apellido # Columnas que quiero ver
WHERE {
	# Aquí defino el "molde" o patrón que busco
    ?x rdf:type pre:Empleado.  # Que sea un empleado
    ?x pre:nombre ?nombre.        # Que tenga nombre (y lo                                          guardas en la variable)
    ?x pre:apellido ?apellido.      # Que tenga apellido
}
```
### Herramientas potentes de SPARQL
1. **FILTER** (Filtros)
	Para poner condiciones lógicas (mayor que, contiene texto, fechas...)
	- `FILTER (?edad > 18)`
	- `FILTER (regex(?nombre, "^Al", "i"))` - Nombres que empiecen por "Al" (insensible a mayúsculas)0
2. **OPTIONAL** (Información opcional)
	Fundamental. En bases de datos normales, si pides nombre y teléfono, y alguien no tiene teléfono, esa fila desaparece. En `SPARQL` si lo usas, te devuelve el nombre y deja el teléfono en blanco si no existe.
	- _Símil:_ "Tráeme a todos los empleados y, si tienen coche, dime la matrícula. Si no tienen, tráeme al empleado igual".
3. **UNION** (Alternativas)
	 Para buscar patrones alternativos. "Quiero personas que sean Autores O Cantantes"
4. **Negación** (FILTER NOT EXISTS vs MINUS)
	Sirve para pedir cosas que **NO** cumplan una condición
	- `FILTER NOT EXISTS { ?x pre:tieneJefe ?y }`. Dame los que no tengan jefe
5. **Property Paths** (Rutas de propiedades)
	Permite buscar caminos largos sin escribir cada paso. Muy potente en jerarquías:
	- `/` (Secuencia): `?x :padre/:padre ?y` (el padre del padre de y = abuelo)
	- `|` (Alternativa): `?x :esCreador|:esAutor ?y` (Creador o Autor de y)
	- `*` (Cero o más): `?x :conoce* ?y` (Conoce a alguien, que conoce a alguien... hasta el infinito, o a sí mismo)
	- `+` (Uno o más): Igual que el anterior pero tiene que haber al menos un paso (no vale él mismo, o lo que es igual, no conocer a nadie)
6. **Tipos de consulta** (No solo SELECT)
	- **SELECT:** Devuelve una tabla con valores
	- **ASK**: Devuelve `TRUE` o `FALSE` (¿Existe algún pokémon tipo fuego? -> Sí)
	- **CONSTRUCT**: No devuelve una tabla, sino que **crea un nuevo grafo RDF** con los resultados. Útil para transformar datos.
	- **DESCRIBE:** Devuelve toda la información disponible sobre un recurso.
## RDF Schema (RDFS) - Dando significado básico
RDF por sí solo son flechas y nodos sin reglas. RDFS es un vocabulario para crear **jerarquías** y reglas básicas. Convierte el grafo en algo con más lógica.
### Conceptos principales
**Clases e Instancias** -> Definen qué tipo de cosas existen
- **rdfs:Class** - Define una categoría (ej: `Profesor`)
- **rdf:type** - Dice que algo pertenece a esa categoría (ej `Juan rdf:type Profesor`)

```turtle
# Me dice que asignatura pertenece a la categoría clase
ex:Asignatura rdf:type rdfs:Class.
# Me dice que IS es una asignatura
ex:IS rdf:type ex:Asignatura.
```

**Jerarquías de clases**
- **rdfs:subClassOf** - Si `Catedrático` es subclase de `Profesor`, entonces todo Catedrático es automáticamente un profesor. Esto permite a la máquina inferir información que no estaba escrita explícitamente.

```turtle
ex:Catedratico rdfs:subClassOf ex:Profesor.
```

**Dominio y rango**
Sirve para definir que tipos de cosas pueden estar al principio o al final de una flecha (propiedad)
- **rdf:Property** - Define las flechas
	Hay que avisar al ordenador de que una palabra va a funcionar como flecha (una relación)
	- **Concepto**: Creando la palabra `tieneDueño`, para nosotros es obvio que hablamos de un Perro y una Persona. Pero para el ordenador es sólo un código más, igual que `Juan` o `Madrid`
	- **La solución**: Es la etiqueta que le ponemos a `tieneDueño` para decirle al sistema que es una flecha que conecta objetos.
- **rdfs:domain** - Es quien "dispara" la flecha.
	- Ejemplo: Propiedad `imparteAsignatura` de dominio `Profesor`
	- *Inferencia*: Si el grafo dice `Ana imparteAsignatura Matemáticas`, la máquina deduce automáticamente que **Ana es un Profesor**, aunque nadie lo haya dicho explícitamente
- **rdfs:range** - Es quien "recibe" la flecha
	- Ejemplo: Propiedad `imparteAsignatura` de rango `Asignatura`
	- *Inferencia*: Del ejemplo anterior, la máquina deduce que **Matemáticas es una Asignatura**

>[!NOTE] RDFs no valida como una base de datos SQL
Ejemplo del pez Wanda: Si definimos ue la propiedad `posee` tiene Rango `persona` y decimos que `Wendy posee a Wanda` y resulta que Wanda es un `Pez`... RDFS no da error. RDFS deduce que como es poseída, `Wanda` debe ser una `Persona`. Así que concluye que Wanda es un Pez y a la vez una Persona. RDFS no prohíbe, deduce.

```turtle
ex:impartidaPor rdf:type rdf:Property;
               rdfs:domain ex:Asignatura;
               rdfs:range ex:Profesor.
```

**Jerarquías de propiedades**
- **rdfs:subPropertyOf** - Relación de subpropiedad
### Propiedades Descriptivas
- **rdfs:comment** - Descripción larga (`"Vehículo de cuatro ruedas...`)
- **rdfs:label** - Nombre legible (`"Coche"` vs `ex:Vehicle`)
- **rdfs:seeAlso** - Enlace a más info.
### Limitaciones de RDFS (Porqué necesitamos OWL)
RDFS se queda corto para cosas complejas:
1. No puede decir que dos clases son **disjuntas** (algo no puede ser Hombre y Mujer a la vez)
2. No tiene negación (no puede decir "NO es un coche")
3. No puede contar (cardinalidad): No puede decir "Un coche tiene exactamente 4 ruedas"
4. No define propiedades avanzadas (Transitiva, Simétrica, Inversa)

Esto lo veremos en el [[Tema 5 - OWL]]