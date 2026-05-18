### 1. Conceptos Preliminares
- Para procesar textos de forma automática, es necesario aplicar técnicas de preprocesamiento (como la tokenización, lematización o eliminación de palabras vacías) para **extraer los rasgos o características del contenido**.
- Las representaciones textuales se dividen en dos naturalezas: simbólicas (reglas, diccionarios) y vectoriales (numéricas).
- Las representaciones vectoriales transforman cada objeto a representar en un vector numérico multidimensional.
	- **Dispersas:** Basadas en **bolsas de palabras** (TF-IDF) y **coocurrencias**
	- **Densas**:  **Modelos latentes** (LSA/LDA), embeddings estáticos (word2vec) y **embeddings contextuales** (BERT)
- Para medir la proximidad o similitud entre estos vectores se utilizan métricas matemáticas como la **distancia euclídea, la similitud coseno o la de Jaccard.**
### 2. Bolsa de Palabras (Representaciones Dispersas)
- En el modelo de "Bolsa de Palabras" (Bag of Words), los documentos se representan como vectores dentro de una matriz documento-término, formando un espacio de alta dimensión y muy disperso (lleno de ceros).    
- Este enfoque asume erróneamente que las palabras son independientes entre sí y no tiene en cuenta el orden en el que aparecen, reduciendo la semántica a una simple suma de términos.
- Para calcular los valores de los vectores se usan **funciones locales** (que evalúan el peso de un rasgo solo dentro del propio documento, como la función binaria o la frecuencia del término - TF) y **funciones globales** (que también usan información de toda la colección, como la Frecuencia inversa del documento - IDF o TF-IDF).
### 3. Matrices de Coocurrencia (Semántica Distribucional)
- Para solucionar la falta de relación semántica de la Bolsa de Palabras, surge la hipótesis distribucional, que establece que las palabras que ocurren en contextos similares tienden a tener significados similares.
- Se utilizan matrices término-contexto, donde se evalúa qué palabras aparecen juntas definiendo una "ventana" de palabras vecinas.
- La función de pesado más recomendada para estas matrices es la PPMI (Información Mutua Puntual Positiva), ya que funciona mejor que el TF-IDF para modelar las dimensiones entre palabras.
### 4. Modelos Latentes (Topic Modelling)
- Estos modelos logran transformar las representaciones dispersas y enormes en espacios vectoriales más densos y de menor dimensión, agrupando los textos en "temas" o conceptos latentes.
- **LDA (Latent Dirichlet Allocation):** Es un modelo probabilístico que asume que los documentos son una mezcla de varios temas, y cada tema es una distribución de probabilidad sobre distintas palabras.
- **LSA (Latent Semantic Analysis):** Es un modelo algebraico que utiliza la descomposición en valores singulares (SVD) para proyectar documentos y palabras en un espacio semántico.
### 5. Embeddings (Representaciones Densas y Distribuidas)
- Los embeddings representan palabras o documentos como puntos en un espacio semántico multidimensional, y tienen la gran ventaja de que pueden ser aprendidos automáticamente por las máquinas leyendo grandes corpus de texto sin etiquetar.
**Embeddings Estáticos**
- Cada palabra tiene asignado un único vector que no cambia, sin importar el contexto en el que se use.
- **Word2Vec:** Utiliza redes neuronales para aprender representaciones prediciendo contextos. Su arquitectura **CBOW** intenta predecir una palabra central basándose en sus vecinas, mientras que **Skip-Gram** hace lo contrario: predice el contexto a partir de la palabra central.
- **GloVe:** Captura relaciones utilizando una matriz de coocurrencia global de todo el corpus.
- **FastText:** Mejora a Word2Vec entrenando vectores para subpalabras (n-gramas), lo que le permite entender variaciones morfológicas y palabras raras que no estaban en su vocabulario original.
- **Sense2Vec:** Extensión que usa etiquetas de la categoría gramatical para diferenciar palabras polisémicas (ej. "banco" de sentarse vs. "banco" de dinero).
- **Doc2Vec:** Una variación de Word2Vec diseñada para generar embeddings de párrafos o documentos enteros.
**Embeddings Contextuales**
- El vector de una palabra es dinámico y depende de las otras palabras presentes en la oración (el contexto).
- **ELMo:** Emplea redes neuronales recurrentes bidireccionales (LSTM). Lee el texto de izquierda a derecha y de derecha a izquierda para entender el uso de la palabra en esa oración específica.
- **BERT:** Basado en la arquitectura _Transformers_, es profundamente bidireccional. Entrena enmascarando ciertas palabras del texto e intentando predecirlas usando toda la información tanto previa como posterior al mismo tiempo.