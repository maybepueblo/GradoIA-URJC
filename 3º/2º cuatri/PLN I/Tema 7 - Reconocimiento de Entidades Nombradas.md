## Índice

1. [[#Introducción]]
2. [[#¿Qué es NER?]]
3. [[#Principales enfoques para NER]]
4. [[#Dificultades en NER]]
5. [[#Bibliografía]]

---

## Introducción

### Contexto: Recuperación de Información (IR)

- **Recuperación de Información (IR, _Information Retrieval_):** proceso de buscar y extraer datos relevantes de grandes volúmenes de información en respuesta a una consulta o necesidad específica.
    - Ejemplo clásico: motor de búsqueda (Query → Documentos relevantes).

### Contexto: Extracción de Información (IE)

- **Extracción de Información (IE, _Information Extraction_):** proceso de extraer información **estructurada** relevante de datos **no estructurados**.
- Flujo general:
    
    ```
    Colecciones de documentos     ↓Recuperación de Información     ↓Extracción de Información (entidades, relaciones, eventos)     ↓Bases de datos, ontologías, etc.
    ```
    

### Tareas dentro de la Extracción de Información

1. **(1) Reconocimiento de Entidades Nombradas** → identificar y clasificar entidades en el texto (personas, lugares, organizaciones, etc.).
2. **(2) Resolución de correferencia** → identificar todas las expresiones en un texto que se refieren a la misma entidad.
    - Ejemplo: _"I loved the cheesecake because **it** reminded **me** of the recipe **my mother** used to make." **James** said._  
        Se resuelve sustituyendo cada pronombre por su referente real.
3. **(3) Extracción de relaciones** → identificar relaciones semánticas entre entidades.
    - Ejemplo: _"**Steve Jobs** was born in **San Francisco** on **24th Feb, 1955**"_  
        → Relaciones: `Person –[Born in]→ Place` y `Person –[Born on]→ Date`.

---

## ¿Qué es NER?

### Entidad Nombrada (EN / NE, _Named Entity_)

- **Definición:** unidad de información fundamental que se refiere a **nombres propios** que pueden clasificarse en varias categorías.
- Una EN se refiere a un **"objeto real"** que tiene asignado un determinado nombre (por ejemplo, una persona, un país, el título de un libro, etc.).

### Categorías genéricas más aceptadas

|Categoría|Ejemplos|
|---|---|
|**Personas**|Paul Newman, Paul, Presidente Barack Obama, …|
|**Lugares**|Madrid, Embalse de Buendía, Estados Unidos, Calle Mayor, …|
|**Organizaciones**|Ministerio de Industria, Apple, Ayuntamiento de Madrid, Universidad Rey Juan Carlos, …|

- Se pueden añadir otras categorías como:
    - **Expresiones temporales** (fecha, hora)
    - **Cantidades numéricas** (porcentajes)

### Categorías específicas según dominio

Dependiendo del dominio de aplicación pueden aparecer categorías más específicas. Ejemplos:

- **Dominio biomédico:** RAREDISEASE, SYMPTOM, SIGN, DISEASE, PROC (procedimiento), CHEM (química), ANAT (anatomía), DISO (trastorno)…
- **Dominio legal:** LEGAL (normas jurídicas), TIME (expresiones temporales), LOC (lugares)…

### ¿Por qué es importante NER?

- Es **crucial** para la extracción de relaciones.
- Es una tarea **necesaria o imprescindible** para otras muchas tareas de PLN:
    - Recuperación de información
    - Búsqueda de respuestas (_Question Answering_)
    - etc.
- Los sistemas NER suelen formar parte del **pipeline de análisis lingüístico**.

---

## Principales enfoques para NER

Los principales enfoques aplicados a NER son:

1. **Enfoques basados en diccionarios y reglas** (listas de nombres, organizaciones, expresiones regulares).
2. **Enfoques basados en aprendizaje automático:**
    - Algoritmos clásicos (e.g., CRF)
    - Aprendizaje profundo (_Deep Learning_)

---

### Enfoque 1 – Diccionarios y Reglas

- Los **diccionarios** proporcionan listas de entidades ya conocidas.
- Las **reglas** son patrones para reconocer EN no presentes en los diccionarios. Ejemplos:

|Patrón|Categoría|Ejemplo|
|---|---|---|
|`"Organización de " + …`|ORG|"Organización de Naciones Unidas"|
|`"Calle " + …`|LOC|"Calle Mayor"|
|`"Universidad de " + lugar`|ORG|"Universidad de Oviedo"|
|`[Mr.\|Mrs.\|Dr.] + Xxxx`|PER|"Mr. Smith"|

> **Características de rendimiento:** los sistemas basados en este enfoque suelen tener una **precisión alta**, pero un **recall bajo**.

---

### Enfoque 2 – Aprendizaje Automático

#### Planteamiento general

- La tarea se plantea como una tarea de **clasificación de tokens (_sequence labeling_)**.
- El texto se tokeniza y cada token se clasifica de acuerdo a una etiqueta.
- El conjunto de etiquetas más utilizado es el **estándar IOB (_Inside-Outside-Beginning_)**.

#### Esquema de anotación IOB

|Prefijo|Significado|
|---|---|
|**B-**|El token es el **inicio** (_Beginning_) de una entidad|
|**I-**|El token está **dentro** (_Inside_) de una entidad|
|**O**|El token **no pertenece** (_Outside_) a ninguna entidad|

- El conjunto completo de etiquetas es: **O, B-X, I-X**, donde X es un tipo de entidad (LOC, ORG, PER, etc.).

##### Ejemplo de anotación IOB

|Token|Etiqueta|Tipo de Entidad|
|---|---|---|
|Yolanda|B|PER|
|Díaz|I|PER|
|visitó|O|–|
|hoy|O|–|
|la|O|–|
|Comisión|B|ORG|
|Europea|I|ORG|
|.|O|–|

También existe el **esquema BILUO** (utilizado por spaCy):

|Prefijo|Significado|
|---|---|
|**B**|_Beginning_ – inicio de una entidad multi-token|
|**I**|_Inside_ – interior de una entidad multi-token|
|**L**|_Last_ – último token de una entidad multi-token|
|**U**|_Unit_ – entidad de un único token|
|**O**|_Outside_ – no pertenece a ninguna entidad|

#### Con ambos enfoques (clásico y profundo)

Se necesita un **dataset de entrenamiento** con los tokens anotados siguiendo el esquema de anotación IOB.

---

### Enfoque 2a – Algoritmos Clásicos (Machine Learning)

- Hay que definir un **conjunto de características (_features_)** para representar cada token.

#### Características más habituales para NER

- **Token y lema:** e.g., "Madrid" como token y "Madrid" como lema.
- **PoS tag:** e.g., NNP (nombre propio).
- **Patrón ortográfico** de una palabra: e.g., "Madrid" → `Xxxxxx`.
- **Afijos:** prefijos y sufijos.
- **Pertenencia a diccionario o base de datos** → valor booleano.
- **Información de contexto:** para representar un token, el conjunto de características se extiende también a los tokens del contexto (tokens vecinos).
    - Las características también se obtienen para los tokens que **rodean** al token que se está representando.
    - Ejemplo: _"La ciudad Madrid es grande"_
        - Si se representa el token **"Madrid"** y se tiene una **ventana de contexto de tamaño 2**:
            - Se añaden también las características de los **2 tokens anteriores** ("La", "ciudad") y los **2 siguientes** ("es", "grande").

---

### Enfoque 2b – Aprendizaje Profundo (_Deep Learning_)

- **No es necesario** definir manualmente un conjunto de características para cada token.
- Simplemente se tokeniza el texto y la **red profunda aprende durante el entrenamiento** las características (vectores) más adecuadas para cada token.
- Se combinan diferentes capas para resolver la tarea de clasificación de tokens.

#### Arquitecturas destacadas

**Arquitectura BiLSTM + CRF:**

```
Tokens de entrada:   Rafa    Nadal    ganó    Wimbledon
                      ↓        ↓       ↓         ↓
               Embeddings (e₁, e₂, e₃, e₄)
                      ↓        ↓       ↓         ↓
               BiLSTM (bidireccional: → y ←)
               Estados ocultos (h₁, h₂, h₃, h₄)
                      ↓        ↓       ↓         ↓
               Conditional Random Field (CRF)
                      ↓        ↓       ↓         ↓
Etiquetas:         B-PER    I-PER      O       B-LOC
```

**Arquitectura BERT + CRF:**

```
Tokens de entrada:   Rafa    Nadal    ganó    Wimbledon
                      ↓        ↓       ↓         ↓
                           BERT
                      ↓        ↓       ↓         ↓
               Conditional Random Field (CRF)
                      ↓        ↓       ↓         ↓
Etiquetas:         B-PER    I-PER      O       B-LOC
```

Ambas arquitecturas han dado **buenos resultados** para NER.

---

## Dificultades en NER

Aspectos que pueden dificultar el reconocimiento de Entidades Nombradas:

|Dificultad|Descripción|Ejemplo|
|---|---|---|
|**Abreviaturas**|No siempre se reconocen como la entidad completa|"N.Y." ↔ "Nueva York"|
|**Distintas menciones**|Una misma entidad puede aparecer con diferentes formas|"Madrid" / "Capital de España"; "Barack Obama" / "presidente Obama" / "Mr. Obama"|
|**Múltiples clasificaciones**|Una misma mención puede pertenecer a diferentes categorías|"Toledo" → LOC (ciudad) o PERSON (apellido: "Goya Toledo")|
|**Errores ortográficos**|Pueden provocar la omisión de entidades|Faltas de escritura en nombres propios|
|**Anidamiento de Entidades**|Una entidad puede contener a otra dentro|"Madrid Fashion Week"|

### Dificultades adicionales en dominios especializados

En algunos dominios la tarea se complica aún más. Por ejemplo, en el **dominio médico** se pueden encontrar entidades representadas por **frases completas** (no solo palabras individuales):

- Ejemplos de entidades multi-token en textos clínicos:
    - _"Estudio de Fase 3 Aleatorizado para Evaluar la Seguridad…"_ → PROC
    - _"infección grave por el COVID-19"_ → DISO
    - _"Infección por el SARS-CoV-2 confirmada mediante PCR"_ → DISO + PROC
    - _"temperatura ≥ 36,6 °C en la axila"_ → ANAT

---

## Bibliografía

1. **Segura Bedmar, I.** Desarrollo de aplicaciones PLN basadas en aprendizaje profundo. Reconocimiento de entidades (Named Entity Recognition). _Procesamiento del Lenguaje Natural con Aprendizaje Profundo. Máster en Ciencia y Tecnología Informática._ 2023.
2. **Cook, M.** Coreference Resolution.
3. **Geeks for Geeks.** Relationship Extraction in NLP. 2025.
4. **Campillos-Llanos, L., Valverde-Mateos, A., Capllonch-Carrión, A. y Moreno-Sandoval, A.** A clinical trials corpus annotated with UMLS entities to enhance the access to evidence-based medicine. _BMC Medical Informatics and Decision Making_, 21, 69 (2021). https://doi.org/10.1186/s12911-021-01395-z
5. **Saamy, D.** Reconocimiento y clasificación de entidades nombradas en textos legales en español. _Procesamiento del Lenguaje Natural_, Revista nº 67, septiembre de 2021, pp. 103-114.