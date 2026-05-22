**Tema 2: Procesamiento Básico, Análisis Léxico, Morfológico y Semántico**

Este tema asienta las bases del preprocesamiento y el análisis de textos utilizando herramientas clásicas.

**Librerías principales:** `nltk`, `spacy`, `re` (expresiones regulares).

**Funciones y Clases clave:**

- **Tokenización y Normalización (NLTK):** `PunktSentenceTokenizer` para dividir en oraciones; `word_tokenize` para dividir en palabras; `split` (método básico de Python).
- **Análisis Morfológico (NLTK):** `nltk.pos_tag` para obtener la categoría gramatical (PoS).
- **Procesamiento con SpaCy:** `spacy.load()` para cargar modelos (ej. `es_core_news_sm`). Al pasar un texto por `nlp(text)`, se genera un objeto `Doc`. De ahí extraes atributos como `token.text`, `token.pos_` (categoría gramatical), `token.lemma_` (lema) y `token.is_stop` (si es palabra vacía). `spacy.explain()` sirve para entender qué significa una etiqueta PoS concreta.
- **Búsqueda y Patrones:** `Matcher` y `PhraseMatcher` de SpaCy para buscar patrones complejos (ej. nombre + adjetivo). `re` para buscar fechas, teléfonos o acrónimos mediante expresiones regulares puras.
- **Análisis Sintáctico (Chunking):** `nltk.RegexpParser` para definir gramáticas y extraer sintagmas (chunks).
- **Análisis Semántico (WordNet en NLTK):** `wordnet.synsets` para obtener los sentidos de una palabra; `hypernyms()` e `hyponyms()` para relaciones de jerarquía; `path_similarity` o `wordnet_ic` para medir similitud semántica entre conceptos.
- **Desambiguación (WSD):** `nltk.wsd.lesk` para aplicar el algoritmo de Lesk y desambiguar el sentido de una palabra basándose en su contexto.
- **Análisis de Sentimientos:** Uso de lexicones predefinidos como `opinion_lexicon` (listas de palabras positivas/negativas) y `SentiWordNet` (puntuaciones entre -1 y 1).
- **Uso de Corpus y Clasificadores:** `nltk.corpus` (Gutenberg para frecuencias, Treebank para sintaxis, CESS-ESP para español). Entrenamiento de `NaiveBayesClassifier` y clasificadores de Máxima Entropía (`maxent`) para predecir polaridad de opiniones.

**Cosas a tener en cuenta:**

- Las **expresiones regulares (ER)** son rápidas, pero tienen limitaciones para tareas semánticas complejas y no reconocen sinónimos.
- El **Etiquetador PoS de NLTK** por defecto está entrenado para inglés; para español, debes entrenar un etiquetador propio usando un corpus anotado como CESS-ESP.
- La **desambiguación** mejora significativamente si filtras primero por la categoría gramatical (PoS) antes de consultar WordNet o aplicar algoritmos.

--------------------------------------------------------------------------------

**Tema 3: Representación de Textos, Modelos Latentes y Embeddings**

Este tema se enfoca en cómo convertir el texto en números (vectores) para que las máquinas puedan procesarlo.

**Librerías principales:** `sklearn`, `numpy`, `gensim`, `sense2vec`, `tensorflow_hub`, `transformers`, `sentence_transformers`.

**Funciones y Clases clave:**

- **Bolsa de Palabras (BoW):** `CountVectorizer` de scikit-learn para crear representaciones basadas en frecuencia de n-gramas (unigramas, bigramas, trigramas). También se usa la función de pesado TF-IDF.
- **Matrices y Similitud:** `cosine_similarity` de scikit-learn para medir cuán parecidos son dos vectores. Uso de `numpy` para crear matrices de coocurrencia y aplicar la función de pesado **PPMI**, que premia asociaciones específicas e informativas penalizando palabras muy frecuentes.
- **Modelos de Temas (Topic Modeling):** `LatentDirichletAllocation` (LDA) en scikit-learn para descubrir temas latentes en un conjunto de documentos.
- **Embeddings Estáticos:** `Word2Vec` (técnicas Skip-gram o CBOW), `FastText` (que maneja n-gramas de caracteres, solucionando problemas de palabras fuera de vocabulario) y GloVe. En Gensim se usa `.most_similar()` para relaciones analógicas (rey - hombre + mujer = reina).
- **Variantes de Embeddings:** `Sense2Vec` genera vectores distintos según la categoría gramatical de la palabra (evita problemas de polisemia). `Doc2Vec` genera un vector para un documento entero.
- **Embeddings Contextualizados:** A diferencia de los estáticos, cambian según el contexto de la frase. ELMo (`hub.load`) basado en biLSTM; BERT (basado en Transformers, se extrae de `last_hidden_state`); SBERT (redes siamesas optimizadas para comparar frases completas).

**Cosas a tener en cuenta:**

- Para representar una frase completa usando embeddings de palabras (como Word2Vec), se suele aplicar el **promedio (mean pooling)** o el **máximo (max pooling)** de los vectores de sus tokens.
- El **preprocesamiento** (eliminar stopwords, lematizar) impacta directamente en la calidad de la representación y en la precisión de clasificadores como `MultinomialNB`.

--------------------------------------------------------------------------------

**Tema 4: Redes Neuronales y Redes Recurrentes (RNN)**

Aplicación de Deep Learning para clasificación de textos.

**Librerías principales:** `tensorflow.keras`, `datasets` (Hugging Face), `matplotlib`.

**Funciones y Clases clave:**

- **Arquitectura Básica Keras:** `Sequential` para apilar capas. `Embedding` transforma tokens en matrices de vectores densos. `Dense` es la capa de salida (usa activación `sigmoid` para clasificación binaria).
- **Entrenamiento:** Al compilar se define el `optimizer` (ej. adam), `loss` (función de pérdida) y `metrics` (ej. accuracy). El entrenamiento se hace con `model.fit()` especificando `epochs` (épocas) y `batch_size`. `EarlyStopping` detiene el entrenamiento si el error de validación no mejora.
- **Redes Recurrentes:** `SimpleRNN` para memoria secuencial básica; `LSTM` para memoria a largo y corto plazo; `Bidirectional` para procesar el texto en ambas direcciones. `Dropout` y `recurrent_dropout` son técnicas de regularización para evitar el sobreajuste apagando neuronas aleatoriamente.
- **Análisis Visual:** `matplotlib.pyplot` se utiliza para graficar las **curvas de aprendizaje** (Accuracy y Loss) y diagnosticar si hay _overfitting_ (sobreajuste) o si el modelo aprende correctamente.

**Cosas a tener en cuenta:**

- Se debe hacer un **análisis exploratorio** del número de palabras de los textos para fijar el tamaño máximo de secuencia (parámetro `max_length`) y rellenar con ceros (`padding`) o truncar según proceda.
- La capa de embeddings puede inicializarse con pesos aleatorios y entrenarse desde cero, o inicializarse cargando un modelo preentrenado como **Word2Vec** para mejorar el rendimiento inicial.

--------------------------------------------------------------------------------

**Tema 5: Transformers y Modelos de Lenguaje**

El estándar actual en el estado del arte del PLN.

**Librerías principales:** `tensorflow.keras`, `keras-nlp`, `transformers` (Hugging Face).

**Funciones y Clases clave:**

- **Construcción manual de Transformer (Keras):** Uso de capas como `MultiHeadAttention` (con `use_causal_mask=True` para decoders), `LayerNormalization`, y `PositionEmbedding` (para inyectar información de la posición de la palabra).
- **Modelos de Hugging Face:** `AutoTokenizer` carga el tokenizador adecuado. `AutoModelForSequenceClassification` adapta un modelo (ej. BERT) añadiendo una capa final para clasificación. `Trainer` y `TrainingArguments` simplificano el proceso de ajuste (fine-tuning) controlando hiperparámetros.
- **Tokenización:** `tokenizer.encode` (pasa a IDs numéricos) y `tokenizer.decode` (vuelve a texto). Estrategias en `tokenizer()` como `padding="max_length"` y `truncation=True`.

**Cosas a tener en cuenta:**

- **Entrenamiento Autoregresivo (Decoder):** Para que el modelo aprenda a predecir la siguiente palabra, las secuencias de entrada (X) son la frase sin el último token, y las etiquetas (Y) son la frase sin el primer token.
- **Tokenización Subword:** Algoritmos como WordPiece dividen palabras raras en subunidades (marcadas con `##`).
- **Tokens Especiales:** El tokenizador añade identificadores clave como `[CLS]` (resumen de la secuencia para clasificación), `[SEP]` (separador) y `[PAD]` (relleno).
- Es crucial utilizar **tokenizadores específicos de dominio** (ej. `PubMedBERT` para textos médicos) porque incluyen tecnicismos completos en su vocabulario, evitando que se fragmenten excesivamente.

--------------------------------------------------------------------------------

**Tema 6: Aumento de Datos (Data Augmentation)**

Estrategias para mejorar modelos cuando hay pocos datos o clases desbalanceadas.

**Cosas a tener en cuenta:**

- **Problema:** En tareas de clasificación (ej. opiniones con TF-IDF y SVM), un conjunto de datos desbalanceado hace que el modelo ignore la clase minoritaria.
- **Solución:** Se aplican técnicas de aumento de datos exclusivamente sobre los textos de la **clase minoritaria** del conjunto de entrenamiento. Esto genera nuevas instancias artificiales mejorando la robustez y los resultados finales.

--------------------------------------------------------------------------------

**Tema 7: Reconocimiento de Entidades Nombradas (NER)**

Extracción y clasificación de información específica en textos.

**Librerías principales:** `nltk`, `spacy`, `transformers`.

**Funciones y Clases clave:**

- **Detección:** `nltk.ne_chunk` agrupa secuencias de tokens en árboles para detectar entidades. En SpaCy, la tupla `doc.ents` devuelve directamente las entidades nombradas.
- **Modelos SpaCy:** Transición de arquitecturas CNN (`en_core_web_sm`) a arquitecturas basadas en Transformers como RoBERTa (`en_core_web_trf`). Modelos como `SciSpaCy` (`en_ner_jnlpba_md`) están especializados en categorías concretas (ej. FARMACIA, ENFERMEDAD).
- **Fine-tuning en SpaCy:** Para adaptar el NER a entidades nuevas:
    1. Transformar datos al formato `spacy.training.Example` usando los offsets (posición inicial y final de la entidad).
    2. Congelar tuberías que no se entrenan con `nlp.disable_pipes`.
    3. Añadir nuevas etiquetas con `ner.add_label('NUEVA_ENTIDAD')`.
    4. Actualizar los pesos con `nlp.update()` usando un optimizador (`nlp.create_optimizer()`).
- **Evaluación:** `nlp.evaluate(examples)` permite obtener automáticamente métricas de **Precision, Recall y F1-score** global y desglosado por tipo de entidad.

**Cosas a tener en cuenta:**

- Para evaluar la robustez de un modelo NER, es una buena práctica añadir **variaciones** al conjunto de prueba, como introducir errores ortográficos intencionados, para verificar si el modelo sigue reconociendo la entidad.
- En el fine-tuning de Transformers puros para NER, las etiquetas de entrenamiento suelen seguir el **formato BIO** (Begin, Inside, Outside), por ejemplo: `B-FARMACO`, `I-FARMACO`, `O`.