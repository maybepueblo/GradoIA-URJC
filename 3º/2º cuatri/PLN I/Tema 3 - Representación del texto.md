### 1. Conceptos Preliminares
- Para procesar textos de forma automática, es necesario aplicar técnicas de preprocesamiento (como la tokenización, lematización o eliminación de palabras vacías) para **extraer los rasgos o características del contenido**.
- Las representaciones textuales se dividen en dos naturalezas: simbólicas (reglas, diccionarios) y vectoriales (numéricas).
- Las representaciones vectoriales transforman cada objeto a representar en un vector numérico multidimensional.
	- **Dispersas:** Basadas en **bolsas de palabras** (TF-IDF) y **coocurrencias**
	- **Densas**:  **Modelos latentes** (LSA/LDA), embeddings estáticos (word2vec) y **embeddings contextuales** (BERT)
	- Matemáticamente decimos que una representación vectoral viene dada por una cuádrupla $<X, Z, Φ, \mu>$ donde:
		- $X$->Conjunto que define el universo de objetos a representar (tokens, frases, documentos, etc.)
		- $Z$->Espacio vectorial que define la dimensión y estructura de las representaciones (disperso o denso)
		- $Φ$->Establece transformación de cada objeto X al espacio vectorial Z (funciones de pesado, modelos de embeddings, etc...)
		- $\mu$->Establece proximidad entre objetos (similitud o distancia)
		- El objeto que representemos se transforma en un vector ℝᵈ, cuya transformación depende del contexto elegido.
			- d puede ser el tamaño del vocabulario (dispersas) o del embedding (densas)
			- los valores del vector se basan en conteos o pesos (BoW, TF-IDF), factores latentes o distribuciones (LSA, LDA) y modelos de embeddings (estáticos o contextuales)
- Para medir la proximidad o similitud entre estos vectores se utilizan métricas matemáticas como:
	- **distancia euclídea** -> sensible a escala
		- $d(x, y)=\sqrt{\sum_{i=1}^n (x_i-y_i)^2}$ 
	- **la similitud coseno** -> compara ángulo entre vectores (muy usada)
		- puede ser su valor:
			- 1 para vectores en misma dirección
			- 0 para vectores ortogonales (perpendicular)
			- -1 para vectores que apuntan en direcciones opuestas
		- ![[Pasted image 20260518170756.png]]
	- **Jaccard.** -> adecuada pa repre binaria o por conjuntos
		- $J(A, B)=\frac{|A\cap B|}{|A\cup B|}$ 
### 2. Bolsa de Palabras (Representaciones Dispersas)
- En el modelo de "Bolsa de Palabras" (Bag of Words), los documentos se representan como vectores dentro de una matriz documento-término, formando un espacio de alta dimensión y muy disperso (lleno de ceros).    
- Este enfoque asume erróneamente que las palabras son independientes entre sí y no tiene en cuenta el orden en el que aparecen, reduciendo la semántica a una simple suma de términos.
- Para calcular los valores de los vectores se usan **funciones locales** (que evalúan el peso de un rasgo solo dentro del propio documento, como la función binaria o la frecuencia del término - TF) y **funciones globales** (que también usan información de toda la colección, como la Frecuencia inversa del documento - IDF o TF-IDF).
#### Bag of Words Binaria en Python
![[Pasted image 20260518171029.png]]
- Ventajas
	- Se entiende
	- Fácil de implementar
- Inconvenientes
	- No hay chance de relacionar palabras con otras
	- Se generan matrices muy grandes y dispersas
#### Bag of Words Frecuencia en Python
![[Pasted image 20260518171136.png]]
- Ventajas
	- Se entiende y fácil de implementar
	- Captura algo de similitud semántica entre docs
- Inconvenientes
	- No hay chance de relacionar unas palabras con otras
	- Matrices grandes y dispersas
#### Bag of Words TF-IDF
![[Pasted image 20260518171441.png]]
### 3. Matrices de Coocurrencia (Semántica Distribucional)
- Para solucionar la falta de relación semántica de la Bolsa de Palabras, surge la hipótesis distribucional, que establece que las palabras que ocurren en contextos similares tienden a tener significados similares.
- Se utilizan matrices término-contexto, donde se evalúa qué palabras aparecen juntas definiendo una "ventana" de palabras vecinas.
- La función de pesado más recomendada para estas matrices es la PPMI (Información Mutua Puntual Positiva), ya que funciona mejor que el TF-IDF para modelar las dimensiones entre palabras.

El PPMI se ve tal que:
![[Pasted image 20260518172002.png]]
Siendo w filas (palabras) y c columnas (contextos) donde $f_{i,j}$ es el número de veces que la palabra $w_i$ aparece en contexto $c_j$.

Con matrices de coocurrencia podemos:
- Encontrar X palabras más similares a una palabra objetivo
- Similitud entre dos documents por medio de su centroide (vector calculado a partir de los vectores de palabras)
### 4. Modelos Latentes (Topic Modelling)
- Estos modelos logran transformar las representaciones dispersas y enormes en espacios vectoriales más **densos y de menor dimensión**, agrupando los textos en "temas/topics" o conceptos latentes.
- **LDA (Latent Dirichlet Allocation):** Es un modelo probabilístico que asume que los documentos son una mezcla de varios temas, y cada tema es una distribución de probabilidad sobre distintas palabras.
- **LSA (Latent Semantic Analysis):** Es un modelo algebraico que utiliza la descomposición en valores singulares (SVD) para proyectar documentos y palabras en un espacio semántico.
	- SVD descompone la matriz término-documento en el producto de tres matrices que revelan la estructura del texto 
	- $X=U\sum V^T$
		- Matriz U -> relaciona cada término con temas latentes
		- Matriz Σ -> indica importancia de cada tema latente. Solemos pillar valores más altos
		- Matriz V^T -> relaciona cada doc con los temas latentes
### 5. Embeddings (Representaciones Densas y Distribuidas)
- Los embeddings representan palabras o frases/documentos como puntos en un espacio semántico multidimensional, y tienen la gran ventaja de que pueden ser aprendidos automáticamente por las máquinas leyendo grandes corpus de texto sin etiquetar.
- Se les llama también **representaciones distribuidas**
- Entonces los vectores para representar palabras se llaman **embeddings** porque la palabra está embebida en un espacio vectorial en particular

Para modelar embeddings usamos herramientas como:
- TensorFlow
- PyTorch
- Gensim
- Hugging Face Transformers

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