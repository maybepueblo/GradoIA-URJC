## 1. Introducción: ¿Por qué necesitamos OWL?

Hasta ahora teníamos **RDF** y **RDFS** ([[Tema 1 - Grafos de conocimiento]]). Con ellos podíamos crear jerarquías básicas ("El coche es un vehículo"). Pero RDFS se queda corto muy rápido.

**Limitaciones de RDFS (El problema)**

En RDFS **NO** puedes decir cosas como:

1. **Negación:** "Un pingüino **NO** puede volar".
2. **Cardinalidad:** "Una persona tiene **exactamente** 2 padres biológicos".
3. **Disyunción:** "Si eres Profesor, **no** puedes ser una Publicación" (o eres una cosa o la otra).
4. **Igualdad:** "La palabra 'Coche' y la palabra 'Auto' se refieren al mismo concepto".

Para solucionar esto nace **OWL** (Web Ontology Language).

- Es un estándar del W3C.
- Es la versión "web" de la **Lógica de Descripciones** ([[Tema 4 - Lógica de descripciones]]). Si RDFS es el vocabulario de un niño, OWL es el de un catedrático.

---
## 2. La "Tarta" de la Web Semántica (¿Dónde estamos?) 

Es importante situarse. OWL no funciona solo, se apoya en los anteriores:

1. **RDF:** Sirve para intercambiar datos (Grafos).
2. **RDFS:** Sirve para definir taxonomías (Jerarquías simples).
3. **OWL:** Sirve para **Ontologías** (Lógica compleja y reglas).
4. **RIF/SWRL:** (Nivel superior) Reglas aún más complejas ("Si A, entonces B").

---
## 3. Vocabulario Especial de OWL

OWL añade palabras clave nuevas para expresar lo que RDFS no podía. Aquí están las más importantes explicadas:
### A. Identidad (¿Eres tú o soy yo?) 

En la web, diferentes personas pueden llamar a la misma cosa con nombres distintos. OWL nos permite unificarlos.

- **`owl:sameAs` (Es lo mismo que):**
    - Sirve para decir que dos URIs distintas son **el mismo individuo**.
    - _Ejemplo:_ `ex:Spain owl:sameAs <http://sws.geonames.org/2510769/>`. (Mi "Spain" y la de Geonames son el mismo país).

- **`owl:differentFrom` (Es distinto de):**
    - Sirve para aclarar que dos cosas son diferentes (aunque parezcan iguales).
    - _Ejemplo:_ `Juan owl:differentFrom Pedro`.

- **`owl:AllDifferent`:**
    - Para no ir uno por uno, creas una lista y dices "Todos estos son diferentes entre sí" (Rojo, Verde, Azul...).
### B. Relaciones entre Clases (Lógica de Conjuntos) 

OWL nos deja operar con conjuntos como vimos en el Tema 4.

- **`owl:disjointWith` (Disjunto con):**
    - Dos clases no pueden tocarse. Si algo es de una, imposible que sea de la otra.
    - _Ejemplo:_ `Profesor owl:disjointWith Publicacion`.
    - _Inferencia:_ Si la máquina sabe que "Libro1" es una `Publicacion`, y le dices que también es `Profesor`, dará **Error de Inconsistencia**.

- **`owl:equivalentClass` (Clase Equivalente):**
    - Dos clases son sinónimos perfectos.
    - _Ejemplo:_ `Persona owl:equivalentClass Humano`.
    - _Inferencia:_ Si Juan es `Humano`, la máquina aprende sola que Juan es `Persona`.

- **Operadores Lógicos:**
    - `owl:unionOf` ($\sqcup$): Unión. (Padre O Madre).
    - `owl:intersectionOf` ($\sqcap$): Intersección. (Mujer Y ConHijos).
    - `owl:complementOf` ($\neg$): Negación. (No es Coche).
### C. Propiedades Avanzadas (La magia de las flechas)

Esto no sale explícito en el recorte del PDF, pero es **fundamental** en OWL y seguro que te cae:

1. **`owl:inverseOf`:** Si A _tieneHijo_ B, entonces B _tienePadre_ A.
2. **`owl:TransitiveProperty`:** Si A es mayor que B, y B es mayor que C -> A es mayor que C.
3. **`owl:SymmetricProperty`:** Si Juan _estáCasado_ con María -> María _estáCasada_ con Juan.
4. **`owl:FunctionalProperty`:** Solo puede haber **uno**. (Ej: `tieneMadreBiologica`. No puedes tener dos).

---
## 4. Anotaciones (Metadatos para humanos) 

Aunque OWL es para máquinas, necesitamos etiquetas para nosotros. Hereda las de RDFS y añade algunas:

- **`rdfs:label`:** El nombre legible ("Coche").
- **`rdfs:comment`:** Una descripción larga ("Vehículo de 4 ruedas...").
- **`owl:deprecated`:** Etiqueta muy útil para avisar: "Oye, esta clase es antigua, no la uses más" (`"true"`).

---
## 5. Inferencia en OWL (Ejemplos Reales)

¿Para qué sirve todo esto? Para que la máquina "piense" (razone) y descubra datos que tú no has escrito.

**Caso 1: Herencia e Instanciación**
- _Hechos:_
    1. `"LibroSemantica"` es un `Libro`.
    2. `Libro` es subclase de `Publicación`.
- Inferencia:
    La máquina deduce sola que "LibroSemantica" es una Publicación.

**Caso 2: Equivalencia**
- _Hechos:_
    1. `Hombre` es subclase de `Persona`.
    2. `Persona` es equivalente a `Humano`.
- Inferencia:
    La máquina deduce que Hombre es subclase de Humano.

**Caso 3: Detectar Errores (Consistencia)**
- _Hechos:_
    1. `Profesor` y `Publicación` son DISJUNTOS (`disjointWith`).
    2. Dices que `Juan` es `Profesor` y también `Publicación`.
- Resultado:
    La máquina explota (bueno, da un error lógico). Esto es vital para validar datos.