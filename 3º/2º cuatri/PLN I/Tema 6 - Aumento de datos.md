## Objetivos

- Introducir el concepto de **Data Augmentation (DA)**.
- Conocer las principales **técnicas** de DA.
- Conocer las principales **librerías** que implementan las técnicas de DA.
- Conocer otras formas de aumento de datos **sin utilizar librerías** específicas.

---

## 1. Introducción

- **Data Augmentation (DA)** o Aumento de Datos son técnicas dirigidas a **crear nuevos datos**.
- Los nuevos datos se crean **a partir de los datos disponibles**.
- Es necesario aplicar algún tipo de **modificación sobre los datos originales** para poder generar los nuevos datos.
- El aumento de datos es un **proceso automático** que ayuda a reducir los costes de creación de nuevos datos.
- ⚠️ **Aumento de datos ≠ datos sintéticos.**

### ¿Cuándo utilizar DA?

- Para que los modelos **no sobreajusten**.
- Si el conjunto de entrenamiento inicial es **muy pequeño**, **no está balanceado** o **no tiene suficiente variación** en los datos.
- Para **mejorar la exactitud** del modelo.
- Para **reducir el coste operativo** del etiquetado.

### Limitaciones del DA

- Se **mantienen los sesgos** del conjunto de datos original.
- Hay que encontrar el **enfoque eficaz** para cada problema.
- **Garantizar la calidad** de los datos aumentados no es fácil.

---

## 2. Aumento de Datos en PLN

### 2.1 Categorización de métodos

Los métodos de aumento de datos en PLN se pueden categorizar en dos grandes grupos:

- **Easy Data Augmentation (EDA)**
    - Random Swapping
    - Synonym Replacement
    - Random Insertion/Deletion
- **Text Data Augmentation**
    - Generative Models
    - Backtranslation

### 2.2 Niveles de aplicación

El aumento de datos se puede aplicar en tres niveles:

- **Nivel de palabra:** transformación o sustitución de palabras individuales dentro del texto.
- **Nivel de frase:** se altera la estructura y composición de frases completas.
- **Nivel de documento:** se altera la estructura y composición de documentos completos.

---

### 2.3 Easy Data Augmentation (EDA)

EDA engloba técnicas de dos tipos:

- **Lexical-based** (basadas en léxico):
    
    - **Insertion** → Inserción de una palabra. Ej: `"I am dancing in the club."` → `"I am penguin dancing in the club."`
    - **Deletion** → Eliminación de una palabra. Ej: `"I am dancing in the club."` → `"I dancing in the club."`
    - **Synonym** → Sustitución por sinónimo. Ej: `"I am dancing in the club."` → `"I am waltzing in the club."`
- **Word-embedding-based** (basadas en embeddings de palabras):
    
    - **Inversion** → Inversión del orden. Ej: `"I am dancing in the club."` → `"In the club I am dancing."`
    - **Tense** → Cambio de tiempo verbal. Ej: `"I am dancing in the club."` → `"I am danced in the club."`

---

### 2.4 Generative Models

#### Data-to-text generation

Se parte de un **dato estructurado** y se genera texto a partir de él.

**Ejemplo:**

```
Input:  { "disease": "diabetes", "symptom": "fatigue", "severity": "high" }
Output: "The patient shows severe fatigue associated with diabetes."
```

Existen dos variantes:

- **Soft Data-to-text generation:** Generación **flexible**.
    
    ```
    Input:  { "topic": "climate change", "stance": "negative" }
    Output: "Climate change is having increasingly harmful effects on the planet."
    ```
    
- **Hard Data-to-text generation:** Generación **controlada y fiel a la entrada**.
    
    ```
    Input:  { "drug": "aspirin", "dose": "100 mg", "frequency": "daily" }
    Output: "Aspirin should be taken at a dose of 100 mg daily."
    ```
    

#### Text Summarization

Se genera un resumen más corto del texto original.

**Ejemplo:**

```
Original: "The study analyzes the long-term effects of diabetes on cardiovascular health,
           focusing on multiple risk factors..."
Resumen:  "The study examines how diabetes affects cardiovascular health over time."
```

#### Paraphrasing (Paráfrasis)

Se reformula el texto manteniendo el significado.

**Ejemplo:**

```
Original:   "The drug reduces blood pressure."
Paráfrasis: "This medication lowers blood pressure levels."
```

**Clasificación de la paráfrasis:**

- **Paráfrasis léxica** → Cambios locales (sustitución de palabras).
    
    ```
    "big problem" → "large issue"
    ```
    
- **Paráfrasis sintáctica** → Cambia la estructura gramatical.
    
    ```
    "The model was trained by researchers" → "Researchers trained the model"
    ```
    
- **Paráfrasis semántica profunda** → Reformulación más libre.
    
    ```
    "He failed the exam" → "He did not pass the test"
    ```
    

---

### 2.5 Back Translation (Traducción Automática Inversa)

Se traduce el texto a otro idioma y luego se vuelve a traducir al idioma original. El resultado es una variación del texto original.

**Ejemplo:**

```
Inglés (original):  "I am dancing in the club."
          ↓
Alemán:             "Ich tanze im Club."
          ↓
Inglés (resultado): "I dance in the club."
```

---

## 3. Librerías para Aumento de Datos en PLN

Las principales librerías en Python para aumento de datos en PLN son:

- **NLP Aug**
- **TextAugment**
- **TextAttack**

---

### 3.1 NLP Aug

- Proporciona una implementación eficiente para aumento de datos para texto.
- Opera en **tres niveles:** carácter, palabra y oración.
- Para cada nivel ofrece: inserción aleatoria, eliminación aleatoria, alteración del orden y sustitución de sinónimos.
- Puede manejar como entrada **texto y audio**.

#### Reemplazo de caracteres

Además del reemplazo aleatorio, incluye:

- **Optical Character Recognition (OCR):** Simula errores basándose en caracteres con grafía similar.

```python
import nlpaug.augmenter.char as nac
import nlpaug.augmenter.word as naw
import nlpaug.augmenter.sentence as nas
import nlpaug.flow as nafc
from nlpaug.util import Action

text = 'The quick brown fox jumps over the lazy dog .'

aug = nac.OcrAug()
augmented_texts = aug.augment(text, n=3)
print("Original:")
print(text)
print("Augmented Texts:")
print(augmented_texts)
```

**Resultado:**

```
Original: The quick brown fox jumps over the lazy dog .
Augmented Texts: ['The quick bkown fox jumps ovek the lazy dog .', 
                  'The quick 6rown fox jumps ovek the lazy dog .', 
                  'The quick brown f0x jomps over the la2y dog .']
```

- **Keyboard Augmenter:** Genera nuevas instancias reemplazando caracteres por otros **próximos en el teclado**.

```python
aug = nac.KeyboardAug()
augmented_text = aug.augment(text)
print("Original:")
print(text)
print("Augmented Text:")
print(augmented_text)
```

**Resultado:**

```
Original: The quick brown fox jumps over the lazy dog .
Augmented Text: The quick brown Gox juJps ocer the lazy dog .
```

#### Reemplazo de palabras

- **Simulando errores ortográficos** (`SpellingAug`):

```python
aug = naw.SpellingAug()
augmented_texts = aug.augment(text, n=3)
print("Original:")
print(text)
print("Augmented Texts:")
print(augmented_texts)
```

**Resultado:**

```
Original: The quick brown fox jumps over the lazy dog .
Augmented Texts: ['Tha qchick brown fox jumps ower the lazy dog.', 
                  'Their quick borwn fox jumps over tge lazy dog.', 
                  'The qchick brown fox jum ps ower the lazy dod.']
```

- **Inserción o sustitución por similitud de embeddings** (`WordEmbsAug` con word2vec, GloVe o fasttext):

```python
# Inserción
aug = naw.WordEmbsAug(
    model_type='word2vec',
    model_path=model_dir+'GoogleNews-vectors-negative300.bin',
    action="insert")
augmented_text = aug.augment(text)
# Resultado: The quick brown fox jumps Alzeari over the lazy Superintendents dog

# Sustitución
aug = naw.WordEmbsAug(
    model_type='word2vec',
    model_path=model_dir+'GoogleNews-vectors-negative300.bin',
    action="substitute")
augmented_text = aug.augment(text)
# Resultado: The easy brown fox jumps around the lazy dog
```

- **Sustitución por sinónimos con WordNet** (`SynonymAug` con `lang='spa'` para español):

```python
text = 'Un rápido zorro marrón salta sobre el perro perezoso'
aug = naw.SynonymAug(aug_src='wordnet', lang='spa')
augmented_text = aug.augment(text)
print("Original:")
print(text)
print("Augmented Text:")
print(augmented_text)
```

**Resultado:**

```
Original: Un rápido zorro marrón salta sobre el perro perezoso
Augmented Text: Un rápido zorro marrón salta sobre el can perezoso
```

- **Contextual Word Embeddings** con BERT (`ContextualWordEmbsAug`):

```python
# Ejemplo multilingüe con BERT
aug = naw.ContextualWordEmbsAug(
    model_path='bert-base-multilingual-uncased', aug_p=0.1)
text = "Bonjour, J'aimerais une attestation de l'employeur certifiant que je suis en CDI."
augmented_text = aug.augment(text)
```

**Resultado:**

```
Original: Bonjour, J'aimerais une attestation de l'employeur certifiant que je suis en CDI.
Augmented Text: bonjour , j ' aimerais ! attestation de l ' employeur certifiant comment je suis en cdi .
```

#### Back Translation con NLP Aug

```python
import nlpaug.augmenter.word as naw

text = 'The quick brown fox jumped over the lazy dog'
back_translation_aug = naw.BackTranslationAug(
    from_model_name='facebook/wmt19-en-de',
    to_model_name='facebook/wmt19-de-en'
)
back_translation_aug.augment(text)
```

**Resultado:**

```
'The speedy brown fox jumped over the lazy dog'
```

---

### 3.2 TextAugment

- Librería para aumento de datos para texto.
- Se apoya en otras librerías como **NLTK** (stopwords, sinónimos de WordNet), **Gensim** y **TextBlob**.

#### Ejemplo básico: sustitución con Word Embeddings

```python
from textaugment import Word2vec, Fasttext

t = Word2vec(model='path/to/gensim/model' or 'gensim model itself')
t.augment('The stories are good')
# The films are good

t = Fasttext(model='path/to/gensim/model' or 'gensim model itself')
t.augment('The stories are good')
# The films are good
```

#### Ejemplo avanzado: múltiples sustituciones con Word Embeddings

```python
# runs = 1        # Por defecto
# v = False       # verbose; si True, reemplaza todas las palabras
# p = 0.5         # probabilidad de éxito individual (0.1 < p < 1.0)

word = Word2vec(model='path/to/gensim/model' or 'gensim model itself', runs=5, v=False, p=0.5)
word.augment('The stories are good', top_n=10)
# The movies are excellent

fast = Fasttext(model='path/to/gensim/model' or 'gensim model itself', runs=5, v=False, p=0.5)
fast.augment('The stories are good', top_n=10)
# The movies are excellent
```

#### Ejemplo básico: aumento con WordNet

```python
import nltk
nltk.download('punkt')
nltk.download('wordnet')
from textaugment import Wordnet

t = Wordnet()
t.augment('In the afternoon, John is going to town')
# In the afternoon, John is walking to town
```

#### Ejemplo avanzado: aumento con WordNet (configuración)

```python
# v = True     # activar aumentación de verbos (por defecto True)
# n = False    # activar aumentación de sustantivos (por defecto False)
# runs = 1     # número de veces que se aumenta una frase (por defecto 1)
# p = 0.5      # probabilidad de éxito individual (0.1 < p < 1.0)

t = Wordnet(v=False, n=True, p=0.5)
t.augment('In the afternoon, John is going to town', top_n=10)
# In the afternoon, Joseph is going to town.
```

---

### 3.3 TextAttack

- Framework en Python con una parte específica para **aumento de datos de texto**.
- Usa la clase `textattack.Augmenter`, que combina una **transformación** y una lista de **restricciones**.

#### Recetas integradas de aumento de datos

|Receta|Descripción|
|---|---|
|`wordnet`|Reemplaza palabras por sinónimos de WordNet|
|`embedding`|Reemplaza palabras por vecinos en el espacio de embeddings (similitud coseno ≥ 0.8)|
|`charswap`|Sustituye, elimina, inserta e intercambia caracteres adyacentes|
|`eda`|Combinación de inserciones, sustituciones y eliminaciones de palabras|
|`checklist`|Contracción/extensión y sustitución de nombres, lugares y números|
|`clare`|Reemplaza, inserta y fusiona usando un modelo de lenguaje enmascarado pre-entrenado|
|`back_trans`|Enfoque de backtranslation|
|`back_transcription`|Enfoque de back transcription|

#### Ejemplo con WordNetAugmenter

```python
from textattack.augmentation import WordNetAugmenter

augmenter = WordNetAugmenter()

sentence = "The quick brown fox jumps over the lazy dog."
augmented_sentence = augmenter.augment(sentence)

print(f"Original Sentence: {sentence}")
print(f"Augmented Sentence: {augmented_sentence}")
```

**Resultado:**

```
Original Sentence: The quick brown fox jumps over the lazy dog.
Augmented Sentence: ['The quick brown fox jumps over the lazy click.']
```

---

## 4. Aumento de Datos sin Librerías

- También es posible hacer aumento de datos **sin el soporte de una librería** específica.
- Se pueden hacer **reemplazos, inserciones, sustituciones, back translation**, etc., utilizando recursos como:
    - Bases de datos léxicas (ej. **WordNet**)
    - Modelos de lenguaje para obtener traducciones
- Se pueden **duplicar textos completos o fragmentos** como una técnica básica de aumento de datos.

---

## 5. Resumen y Consideraciones Finales

- Las técnicas de DA hay que aplicarlas **antes del entrenamiento** y **solo sobre los datos de entrenamiento** (nunca sobre el conjunto de validación y test).
- Las técnicas de DA pueden provocar que el nuevo texto **contenga errores o no tenga coherencia** → no es una tarea sencilla.
- Es conveniente realizar un **estudio previo** para determinar:
    - Qué combinación de técnicas es la más adecuada para cada tarea.
    - Qué cantidad de datos se aumenta.
    - Si los resultados mejoran con el aumento.
- ⚠️ Puede que las técnicas de DA **no ayuden a mejorar los resultados**.

---

## Referencias

1. Segura Bedmar, I. _Transformers. Procesamiento del Lenguaje Natural con Aprendizaje Profundo._ Máster en Ciencia y Tecnología Informática. 2023.
2. Murel, J. y Kavlakoglu, E. _¿Qué es el aumento de datos?_ 2024.
3. Chen, J., Tam, D., Raffel, C., Bansal, M. y Yang, D. _An Empirical Survey of Data Augmentation for Limited Data Learning in NLP._ Transactions of the Association for Computational Linguistics 2023; 11, 191–211. doi: https://doi.org/10.1162/tacl_a_00542
4. Geeks for Geeks. _Text augmentation techniques in NLP._ 2025.
