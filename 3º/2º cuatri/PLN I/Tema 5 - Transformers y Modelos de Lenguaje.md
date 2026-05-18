## Índice General
1. [[#Precedentes de representaciones textuales]]
2. [[#¿Qué son los Transformers?]]
3. [[#Arquitectura de los Transformers]]
    - [[#Previo: modelo Seq2Seq y mecanismo de atención]]
    - [[#Primer modelo Transformer (Attention is All You Need)]]
    - [[#El Codificador (Encoder)]]
    - [[#El Descodificador (Decoder)]]
4. [[#¿Cómo se trabaja con los Transformers?]]
    - [[#Pre-training]]
    - [[#Fine-tuning]]
5. [[#Modelos de Lenguaje (LMs)]]
    - [[#SLMs – Small Language Models]]
    - [[#LLMs – Large Language Models]]
    - [[#Aprendizaje en contexto (In-context learning)]]
6. [[#Tokenización en modelos Transformer]]
    - [[#Carga del tokenizador y salida de BERT]]
    - [[#WordPiece Tokenization]]
    - [[#Campo input_ids]]
    - [[#Campo token_type_ids]]
7. [[#Embeddings Contextuales con Transformers]]
    - [[#Embeddings con Encoders]]
    - [[#Embeddings con Bi-encoders (SBERT)]]
8. [[#Fine-tuning sobre BERT]]
9. [[#Retos en la integración de los modelos]]
10. [[#Limitaciones y desafíos de los Transformers en PLN]]

---
## Precedentes de representaciones textuales
Antes de los Transformers existían dos grandes aproximaciones para representar texto:
### Bolsa de palabras (Bag-of-Words)
- Generan **vectores dispersos** (_sparse vectors_).
- Representaciones basadas en frecuencia de términos.
- **Ignoran el contexto** y las relaciones semánticas entre términos.
- Ejemplos: Pesado Binario, TF-IDF, BM25.
### Embeddings estáticos
- Generan **vectores densos**.
- Representaciones **fijas por término**: no tienen en cuenta el contexto en el que se encuentran.
- Incorporan relaciones semánticas entre términos.
- Ejemplos: Word2Vec, GloVe, FastText.

---
## ¿Qué son los Transformers?
- Son una **arquitectura de red neuronal** utilizada para Procesamiento del Lenguaje Natural.
- Surgieron en **2017** con el paper de Google _"Attention is All You Need"_ (Vaswani et al.).
- **No requieren entrada secuencial**: son capaces de procesar palabras y oraciones completas **en paralelo**.
    - Lo logran capturando dependencias contextuales a largo plazo mediante **mecanismos de atención**.
- Aprenden el contexto de los datos secuenciales y son capaces de generar nuevos datos a partir de él.
- El **mecanismo de atención** es el componente clave.
- Sustituyen las capas recurrentes (RNN) por capas de atención.
    - Las capas de atención codifican cada palabra en función del **resto de la secuencia**, introduciendo el contexto en la representación matemática del texto.
- También incluyen **embeddings posicionales**, que permiten al algoritmo conocer la posición relativa de cada palabra.
- A los modelos basados en Transformer se les denomina también **Embeddings Contextuales**.
- Son la **arquitectura estándar** para construir modelos de lenguaje.
### Contexto histórico (evolución del PLN)
- Hace ~12-13 años: se usaba BoW como entrada de algoritmos de ML.
- Última década: explosión del Deep Learning → irrumpen los embeddings → el propio texto pasa a ser la entrada.
    - Las **RNN** se convirtieron en el estándar, pero tenían **memoria a corto plazo** (generaban texto repetitivo e incorrecto en secuencias largas).
- 2017: los Transformers resuelven estas limitaciones.

> _"Los transformers hicieron posible el aprendizaje autosupervisado y la IA alcanzó una velocidad asombrosa"_ — Jensen Huang, fundador y CEO de NVIDIA

**Aprendizaje automático autosupervisado:**
- El modelo se entrena utilizando señales intrínsecas presentes en los datos, sin etiquetas externas proporcionadas por humanos.
- Aprende de la propia entrada.

---

## Arquitectura de los Transformers

### Previo: modelo Seq2Seq y mecanismo de atención

#### Modelo Seq2Seq (Sequence-to-Sequence)
- Ha alcanzado mucho éxito en tareas como **traducción automática**.
- Es la base sobre la que evoluciona la arquitectura Transformer.
- Está compuesto por:
    - **Codificador (Encoder)**: recibe la secuencia de entrada y genera una representación intermedia.
    - **Descodificador (Decoder)**: recibe la salida del codificador y produce la secuencia de salida.
#### Limitaciones del modelo Seq2Seq
- La salida se basa en gran medida en el **estado oculto de la salida final** del codificador → dificulta el manejo de oraciones largas (la información de los primeros tokens puede perderse).
- **No permite paralelización**.
#### Solución: Mecanismo de atención
- Se añade un **mecanismo de atención** al modelo Seq2Seq.
- Permite generar cada token en la secuencia de salida en función de los **tokens más relevantes** en la oración para dicho token.
- El codificador genera un **vector de salida por cada token de entrada** (no solo uno al final).

**Ventajas del mecanismo de atención:**
- Ya no se pierde información en secuencias largas: ahora **todos los estados del codificador** se pasan al descodificador.
- El descodificador puede aprender qué partes de la entrada son más relevantes en cada paso.

**Limitaciones del mecanismo de atención:**
- Sigue siendo **procesamiento secuencial**: cada estado oculto depende del anterior. No se puede empezar el paso _t_ hasta terminar el _t-1_.
- Ineficiente en conjuntos de datos grandes.

---

### Primer modelo Transformer (Attention is All You Need)

> Vaswani, A. et al. (2017). _Attention is all you need_. Advances in neural information processing systems, 30. _"No recurrence. No convolutions. Just attention."_

La arquitectura se apoya en varios conceptos clave:

- **Positional encoding**: las palabras se numeran según su posición en la frase → el modelo puede conocer el orden de las palabras.
- **Self-attention**: cuando se procesa un token de la secuencia de entrada, el codificador identifica qué otros tokens de la secuencia son los más relevantes para dicho token.
- El mecanismo de **self-attention sí permite paralelización** (multi-head), a diferencia del mecanismo de atención anterior.

**Estructura general:**

- Se mantiene el modelo **encoder-decoder**.
- Tanto el codificador como el descodificador son **pilas con varias capas** (mismo número en cada uno):
    - En los codificadores: la entrada pasa al siguiente codificador.
    - En los descodificadores: recibe como entrada la del último codificador y la del descodificador anterior.

---

### El Codificador (Encoder)

Transforma los tokens de entrada en **representaciones contextualizadas** → capta el contexto de cada token con respecto a la secuencia.
#### Tarea 1: Conversión a vectores de embeddings
- Convierte cada token de la entrada en un **vector de embeddings** (de tamaño 512 en el modelo original).
#### Tarea 2: Codificación posicional (Positional Encoding)
- Se combinan **funciones seno y coseno** para crear vectores posicionales.
- Se producen codificaciones únicas para cada posición.
- El vector posicional se **suma** al vector de embedding de la palabra para crear el embedding con contexto posicional.
- Fórmulas:
    - `P(k, 2i) = sin(k / n^(2i/d))`
    - `P(k, 2i+1) = cos(k / n^(2i/d))`
    - Donde:
        - `k`: posición del objeto en la secuencia de entrada (`0 < k < L/2`)
        - `d`: dimensión del espacio de embedding de salida
        - `P(k,j)`: función posicional para mapear posición `k` al índice `(k,j)` de la matriz posicional
        - `n`: escalar definido por el usuario (los autores del paper lo fijaron a **10.000**)
        - `i`: usado para mapear índices de columna (`0 < i < d/2`), un valor de `i` mapea tanto a seno como a coseno
#### Tarea 3: Pila de capas del codificador
##### 3.1. Self-Attention (Multi-Head Attention)
- Se relaciona cada palabra de la entrada con otras palabras de la secuencia.
- Las puntuaciones de atención se calculan usando **tres representaciones alternativas** de los tokens de entrada. Cada embedding de la entrada se transforma en tres vectores:
    - **Query (Q)** – Consulta: define **qué busca** el token en otros tokens.
    - **Key (K)** – Clave: indica **cómo se define** cada token a sí mismo.
    - **Value (V)** – Valor: define **qué aporta** cada token a otros tokens.
- Si la similitud entre el vector de consulta y la clave es alta, al multiplicarse por el vector del valor quedará resaltado en la salida el score final → indica si las palabras están más o menos relacionadas.
- Fórmula: `Attention(Q, K, V) = softmax(QK^T / √d_k) · V`

**Ejemplo:** _"The girl dropped her book because she was tired."_ — se necesita saber a quién se refiere "she":

- La Query (Q) para "she" pregunta: _"¿A quién me refiero?"_
- El modelo compara esta consulta con las claves (K) de todas las demás palabras.
- La clave de "girl" coincide más que la de "book" → el valor (V) de "girl" contribuye más a cómo el modelo entiende "she".

**Proceso de cálculo de las puntuaciones:**

1. Se calculan las puntuaciones de atención (producto de Q y K).
2. Las puntuaciones se **reducen dividiéndolas por la raíz cuadrada de la dimensión** de los vectores de consulta y clave (`√d_k`).
3. Se aplica **softmax** → se obtienen valores entre 0 y 1. Enfatiza las puntuaciones más altas y disminuye las más bajas → ayuda al modelo a saber qué palabras deben recibir más atención.

**Multi-Head:**

- El mecanismo de autoatención ocurre **por separado en múltiples etapas o "cabezas"**, cada una de forma independiente.
- Al usar múltiples capas, se pueden detectar **asociaciones entre palabras y entre grupos de palabras a diferentes niveles**.
- Las salidas de estas capas se combinan en una red neuronal que **condensa toda la información en un único vector** para cada token de entrada.

**Ejemplo con 4 cabezas de atención** sobre _"The girl dropped her book because she was tired."_:

- Head 1: Tracks subject-verb connections (_"girl" → "dropped"_)
- Head 2: Resolves pronouns (_"she" → "girl"_)
- Head 3: Focuses on cause-and-effect (_"because" → "tired"_)
- Head 4: Identifies object ownership (_"her" → "book"_)
- Cada cabeza percibe algo diferente → al combinar sus percepciones, el modelo comprende la frase con mayor profundidad.

##### 3.2. Normalización y conexión residual

- Cada subcapa va seguida de una **capa de normalización**.
- La salida de cada subcapa se **añade a su entrada** (conexión residual) → ayuda a mitigar el problema del **descenso del gradiente**.
- Se toman los datos, se suman y se normalizan para que tengan la escala adecuada para la siguiente capa.
- Este proceso se **repite también después de la red neuronal Feed Forward**.
- Fórmula: `LayerNorm(entrada + salida_subcapa)`

##### 3.3. Red Neuronal Feed Forward

- Red neuronal con **dos capas lineales** y una activación **ReLU** entre ellas.
- Seguida de otra capa de normalización y conexión residual.

#### Tarea 4: Salida del codificador

- La salida es un **conjunto de vectores** que se utilizará como entrada:
    - Para otro codificador (puede haber varios en el Transformer).
    - Para los descodificadores (puede haber varios).

---

### El Descodificador (Decoder)
**Función principal:** Genera secuencias de texto, **palabra por palabra**.
#### Tareas del descodificador:
1. **Generar los embeddings** de la entrada que recibe.
2. **Añadir la información de la posición** (Positional Encoding, igual que en el encoder).
3. **Capas con tres componentes** (con capas de normalización entre ellos):
    - Mecanismo de autoatención enmascarada (_Masked Multi-Head Attention_)
    - Atención Multicabezal (_Multi-Head Attention_)
    - Red Neuronal _Feed-Forward_
4. **Clasificador lineal y Softmax**: permite generar una a una las palabras de la secuencia de salida.
#### Componente 3a: Masked Multi-Head Attention
- El descodificador solo tiene que prestar atención a la **palabra generada ahora y a las anteriores**, **pero NO a las futuras**.
- Ejemplo:
    - Secuencia original: _"I love Italian food"_
    - Secuencia traducida: _"Amo la comida italiana"_
    - Si nos ubicamos en la palabra "la", el descodificador solo tendrá acceso a la palabra "amo".
- **Enmascarar**: poner con valor 0 las palabras a las que no se debe prestar atención.
#### Componente 3b: Multi-Head Attention (encoder-decoder)
- Aquí **interaccionan los componentes del codificador con el descodificador**.
- En esta capa se enfoca la atención tanto en la secuencia original como en la salida.
- Las **Queries (Q)** provienen de la capa anterior del descodificador.
- Las **Keys (K) y Values (V)** provienen directamente de la salida final del codificador.
- De nuevo, se usan múltiples bloques atencionales de manera simultánea para codificar asociaciones a diferentes niveles.
#### Componente 3c: Red Neuronal Feed-Forward (FFN)
- Igual que en el codificador: procesa la información de manera independiente para cada posición.
#### Componente 4: Clasificador lineal y Softmax
- La **capa lineal** proyecta la salida del descodificador a un vector de tamaño del vocabulario (_N classes / vocabulary size_).
- **Softmax** convierte ese vector en probabilidades → la palabra con mayor probabilidad es el output final.

---
## ¿Cómo se trabaja con los Transformers?

De forma general, se trabaja en **dos fases**:
### Pre-training
- El modelo aprende cómo se estructura el lenguaje de forma general → consigue un **conocimiento genérico** del significado de las palabras.
- Necesita una **cantidad masiva de textos** (millones de palabras).
- Ejemplo: BERT fue preentrenado con:
    - La colección de libros en formato digital contenida en **BookCorpus**.
    - Todos los textos de la **Wikipedia en inglés**.
    - En total: más de **3.000 millones de palabras**.
- Estrategias de entrenamiento (ejemplos):
    - **Masked Language Model**: enmascaramiento de tokens.
    - **Next Sentence Prediction (NSP)**: el modelo identifica si dos oraciones aparecen juntas en un texto o no.
- Resultado: vectores + la arquitectura con los **pesos aprendidos** durante el entrenamiento.
### Fine-tuning
- El modelo preentrenado se **ajusta a una tarea concreta** de PLN.
- Ajustarlo significa **añadir nuevas capas** adecuadas para la tarea a realizar.
- Se necesita un **dataset anotado** propio de la tarea.
- El modelo preentrenado se entrenó sobre gran cantidad de textos → la tarea de fine-tuning necesita **menos ejemplos**, el dataset puede ser más pequeño.
- **Todo se entrena conjuntamente**: el modelo preentrenado y las nuevas capas, con el conjunto de datos de la tarea.
- Ejemplos de fine-tuning:
    - **Clasificación de textos** → capa de softmax sobre la salida del modelo para predecir la clase.
    - **NER (Named Entity Recognition)** → se añade un CRF para predecir la etiqueta de cada token.
    - **Detección de fake news** → dataset con noticias etiquetadas como ciertas o falsas.

**Esquema típico de fine-tuning para clasificación en 4 clases:**

```
Textos (noticias) + Labels (economía, política, deporte, cultura)
        ↓
Modelo pre-entrenado
        ↓
Capa densa (fully-connected)
        ↓
Softmax (4 clases)
```

**Esquema general de fine-tuning de LLMs:**

```
Large corpus of data → LLM
Task-specific dataset → Fine-tuning the model → Final Model (Ready for real-world applications)
```

---
## Modelos de Lenguaje (LMs)
- Los modelos del lenguaje son **redes neuronales artificiales de gran tamaño**, capaces de analizar ingentes volúmenes de texto escrito para aprender la estructura con la que se presentan las palabras de un determinado idioma.
- Tienen una **arquitectura basada en Transformers**.
- Diseñados para **comprender, generar y manipular texto** en lenguaje natural a gran escala → logran que una máquina dé respuestas como un humano.
- Se han convertido en **herramientas indispensables** para empresas, investigadores y organizaciones.
- Se dividen en **SLMs** (Small Language Models) y **LLMs** (Large Language Models).

---
### SLMs – Small Language Models
- Se construyen con **menos parámetros** y arquitecturas neuronales más sencillas que los LLMs → permite:
    - Entrenamiento más rápido.
    - Menor consumo de energía.
    - Despliegue en dispositivos con recursos limitados.
- **Tamaño**: los parámetros oscilan entre **pocos millones y pocos miles de millones**. Los LLMs manejan **cientos de miles de millones**.
- Algunos SLMs populares:
    - **DistilBERT**: versión más ligera del modelo fundacional BERT de Google.
    - **Llama**: línea de modelos de lenguaje de código abierto de Meta.
    - **GPT-4o mini**: variante más pequeña que GPT-4o con capacidades multimodales.
#### Beneficios de los SLMs:
- **Accesibilidad**: se pueden usar sin invertir en múltiples GPUs y otros recursos.
- **Eficiencia**: al necesitar menos recursos, el entrenamiento es más rápido.
- **Rendimiento efectivo**: pueden tener un rendimiento comparable o incluso mejor que sus equivalentes de modelos grandes.
- **Mayor control de privacidad y seguridad**: pueden implementarse en entornos locales o privados de cloud → se mitigan amenazas y se tiene mejor protección de datos.
- **Menor latencia**: menos parámetros → tiempos de procesamiento menores → el modelo responde más rápido.
- **Más sostenibles**: requieren menos recursos → consumen menos energía → se reduce su huella de carbono.
- **Reducción de costes**: los gastos de desarrollo, infraestructura, etc. son menores que en los LLMs.
#### Limitaciones de los SLMs:
- **Sesgo y alucinaciones** como los modelos más grandes.
- **Disminución del rendimiento** en tareas complejas.
- **Generalización más limitada**.

---
### LLMs – Large Language Models
- Entrenados con **enormes cantidades de datos**.
- **Miles de millones de parámetros** → capacidad de aprender de una amplia gama de fuentes de datos.
- Al aprender de cantidades ingentes de datos, presentan **mayor capacidad de generalización** → mejoran el rendimiento en tareas más complejas.
- Algunos LLMs populares: GPT-4, Llama, Falcon, PaLM, ...
#### Limitaciones de los LLMs:
- **Desajuste de dominios**.
- **Alucinaciones y prejuicios**.
- **Escalabilidad e impacto ambiental**.

---
### Aprendizaje en contexto (In-context learning)
- Capacidad de un LLM de **aprender y realizar tareas específicas** basándose únicamente en el texto de entrada proporcionado durante la inferencia.
- Los LLMs modernos, además de aprender durante el entrenamiento, pueden **razonar en tiempo real** usando el prompt.
- Es muy relevante el **prompt engineering**: las indicaciones en el prompt ayudan al modelo a entender mejor el contexto → genera resultados más precisos.
#### Casos concretos de In-context learning:
- **Zero-shot learning**: el modelo resuelve tareas sin ejemplos previos.
- **Few-shot learning**: el modelo resuelve tareas con muy pocos ejemplos proporcionados en el prompt.

---
## Tokenización en modelos Transformer
- La tokenización es **crucial** en los modelos Transformer.
- Se ocupa de **representar los datos en un formato** que entienda el modelo.
- Cada token se representa con un **número** (índice del token en el vocabulario del Transformer).
- Cada token se transforma a un **vector de números reales** (entrada al modelo).
- Si se va a utilizar un modelo preentrenado **hay que usar el tokenizador asociado al modelo**:
    - Hay que dividir el texto siguiendo las mismas reglas del preprocesamiento del preentrenamiento.
    - Se tienen que usar los mismos índices para representar los tokens.
### Carga del tokenizador y salida de BERT
- Se utiliza la clase **`AutoTokenizer`** (carga el tokenizador de cualquier Transformer).
- Ejemplo de carga del modelo _uncased_ de BERT (no distingue entre mayúsculas y minúsculas):

```python
from transformers import AutoTokenizer
tokenizer = AutoTokenizer.from_pretrained("bert-base-uncased")
```

- La salida del tokenizador de BERT contiene tres campos principales:
    - `input_ids`
    - `token_type_ids`
    - `attention_mask`

---
### WordPiece Tokenization
- BERT utiliza el algoritmo **WordPiece**.
- En el vocabulario, además de palabras completas, se incluye la **lista de morfemas con mayor probabilidad** en la colección de textos del preentrenamiento.
- Los morfemas que son parte interna de una palabra se marcan con `##` al inicio.
- **Ventaja del WordPiece**: se puede representar **cualquier texto**, incluso palabras desconocidas, descomponiéndolas en subpalabras conocidas.
- Ejemplo: _"Esto es supercalifristicoespialidoso"_
    - Tokenización simple: `['Esto', 'es', 'supercalifristicoespialidoso']`
    - WordPiece: `['Esto', 'es', 'super', 'cal', 'if', 'rag', 'ilis', 'tico', 'es', 'pia', 'lido', 'so']`
- WordPiece es utilizado por modelos como **BERT, DistilBERT**. Existen otros algoritmos similares; por ejemplo, **GPT utiliza una variación de WordPiece**.

**Ejemplo con BERT multilingüe:**

```python
from transformers import BertTokenizer
bert_tokenizer = BertTokenizer.from_pretrained("bert-base-multilingual-uncased")

sentence = 'Esto es supercalifristicoespialidoso'
encoding = bert_tokenizer(sentence)

# tokens resultantes:
# ['[CLS]', 'esto', 'es', 'super', '##cal', '##if', '##risti', '##coes', '##pia', '##lido', '##so', '[SEP]']
```

---

### Campo `input_ids`

- Contiene los **índices numéricos** de cada token en el vocabulario.
- Siempre incluye tokens especiales:
    - **101** → id de `[CLS]` (token de inicio/clasificación)
    - **102** → id de `[SEP]` (token separador/fin)

**Ejemplo:**

```python
encoded = tokenizer('Ven')
# input_ids:  [101, 22712, 102]
# token_type_ids: [0, 0, 0]
# attention_mask: [1, 1, 1]
# tokens: ['[CLS]', 'ven', '[SEP]']
```

---

### Campo `token_type_ids`

- BERT necesita este campo porque ha sido entrenado usando **dos estrategias**:
    
    1. **Enmascaramiento de tokens** (Masked Language Model).
    2. **Next Sentence Prediction (NSP)**: tiene que identificar si dos oraciones aparecen juntas en un texto o no.
- Cuando se pasan **dos oraciones**, `token_type_ids` indica a qué oración pertenece cada token:
    
    - Tokens de la **primera oración** → valor `0`
    - Tokens de la **segunda oración** → valor `1`

**Ejemplo con dos oraciones:**

```python
sentence1 = "Hoy es jueves, queda poco para que termine la semana."
sentence2 = "La asignatura que más me gusta del grado es PLN"
encoded = tokenizer(sentence1, sentence2)

# token_type_ids: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
# (los 1s corresponden a los tokens de la segunda oración)
```

---

## Embeddings Contextuales con Transformers

### Ventaja clave sobre representaciones previas

- Los **mecanismos de atención** permiten considerar el contexto en el que se encuentran las palabras.
- Obtienen **representaciones diferentes en función de las palabras que la rodean**.
- Es posible obtener embeddings contextuales considerando tanto la **semántica** como el **contexto** de las palabras.

---

### Embeddings con Encoders

- Los encoders aprenden **representaciones profundas** de una entrada de texto.
- Son **idóneos** para la obtención de embeddings contextuales.
- Una forma habitual de obtenerlos es hacer la **media de los embeddings de los tokens en la última capa oculta**.

---

### Embeddings con Bi-encoders (SBERT)

- **Sentence Transformers (SBERT)** → extiende el concepto de embedding a la **sentencia completa**.
- Paper: _"Sentence-BERT: Sentence Embeddings using Siamese BERT-Networks"_ (Reimers y Gurevych, 2019).
- Los embeddings se calculan de forma **independiente por cada frase**.
- Arquitectura: dos instancias de BERT procesan cada frase por separado → cada una aplica _pooling_ → se obtienen vectores `u` y `v` → se comparan mediante **similitud coseno** (`cosine-sim(u, v)` ∈ [-1, 1]).
- Se puede hacer **fine-tuning** para otras tareas.

---

## Fine-tuning sobre BERT

Pasos a dar para hacer fine-tuning sobre un modelo BERT:

1. **Cargar y preparar el dataset anotado** que se vaya a utilizar para ajustar el modelo preentrenado.
2. **Configurar parámetros**.

> Al hacer fine-tuning de un modelo preentrenado se ajusta a una tarea concreta.

---

## Retos en la integración de los modelos

- **Calidad y volumen de los datos.**
- **Personalización de los modelos.**
- **Complejidad de la integración.**
- **Sesgos en los resultados.**
- **Actualización constante.**
- **Considerar normativas.**
- **Limitaciones de rendimiento.**

---

## Limitaciones y desafíos de los Transformers en PLN

- **Requerimientos computacionales**: los modelos grandes requieren grandes capacidades de cómputo.
- **Sesgo y calidad de los datos de entrenamiento**: los sesgos presentes en los datos se transfieren al modelo.
- **Capacidad de generalización**: pueden fallar ante datos muy diferentes a los de entrenamiento.
- **Interpretabilidad y explicabilidad**: es difícil entender por qué el modelo toma determinadas decisiones.

---

## Características generales de los Modelos de Lenguaje

- Comprensión contextual.
- Capacidad multilingüe.
- Procesamiento en tiempo real.
- Aprendizaje por transferencia.
- Personalización.
- Mayor precisión y eficacia.
- Escalabilidad.
- Personalización basada en IA.

---