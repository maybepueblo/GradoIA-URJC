## El problema de la ambigüedad
Lo vemos como la capacidad de que algo se entienda de más de una forma. Hay tipos:
- Léxica -> Palabra tiene varios significados
- Sintáctica -> Frase se analiza de diversas formas
- Semántica -> Se puede no entender el significado de las palabras
- Anafórica -> Alusiones a elementos que vienen antes en un discurso, que solo se puede resolver con el contexto
- Pragmática -> El contexto da lugar a múltiples interpretaciones
## Niveles básicos de procesamiento
Existen diferentes niveles de análisis:
### Análisis fonológico
Se basa en entender la pronunciación. No ahondaremos en esta asignatura en este tipo de análisis.
### Análisis morfológico
Identificar los lexemas y morfemas de una palabra

Una palabra es una unidad lingüística compleja formada por unidades más pequeñas, que pueden ser de dos tipos:
- **Lexemas** -> Parte de la palabra que tiene significado por sí mismo.
- **Morfemas gramaticales** -> Elemento que modifica o completa el significado de un lexema. 
	- **Libres** -> Tienen significado por sí solos ("los", "para", etc.)
	- **Ligados** -> Pueden aparecer unidos a otros morfemas con los que forman palabras.
	- En el análisis morfológico obtenemos distintos rasgos morfológicos (categoría gramatical, género, número, persona, etc.)
### Análisis léxico
El léxico en una lengua es el conjunto de palabras de un idioma (colección de lexemas). Un analizador léxico se centra en analizar la estructura de las palabras.

También se asigna la posible parte del discurso (*PoS, Part of Speech*) a la palabra.
- Se pueden clasificar en clases/categorías (PoS) en base a su función dentro de las frases del lenguaje

**Tokenización**
- Consiste en dividir un texto en unidades mínimas significativas llamadas "tokens".
	- *Texto* -> "El PLN es imprescindible hoy."
	- *Tokens* -> ["El", "PLN", "es", "imprescindible", "hoy", "."]
#### Etiquetado de las partes del discurso (PoS tagging)
- Se dice que el etiquetado es el proceso de asignar etiquetas a cada token.
- Cada token es etiquetado con su categoría gramatical (sustantivo, verbo, adjetivo, etc.)
- *Texto* -> "El PLN es imprescindible hoy"
- *Tokens* -> [(El, determinante), (PLN, sustantivo), (es, verbo), (imprescindible, adjetivo), (hoy, adverbio)] 
- **Clases de palabras**:
	- **Cerradas**: número fijo de palabras (preposiciones, pronombres, etc.)
	- **Abiertas**: permiten añadir nuevas palabras (nombres, adjetivos, verbos, etc.)
	- Dentro de una clase pueden existir subclases
		- *E. j* -> Dentro de nombres existen los propios y los comunes (y dentro de comunes los contables e incontables)
		- *E. j 2* -> Dentro de los pronombres existen los personales, los posesivos, los interrogativos y los relativos.

Decimos entonces que existe un conjunto de etiquetas posibles (PoS tags) donde cada etiqueta codifica:
- Categoría léxica (clase de palabra)
- Información de los rasgos gramaticales (género, número, etc...)

No existe un conjunto de etiquetas único. La información codificada depende del lenguaje y del tipo de aplicación. Así tenemos fuentes de referencia como:
- [Universal POS tags](https://universaldependencies.org/u/pos/index.html)
- [Penn Treebank Project](https://www.ling.upenn.edu/courses/Fall_2003/ling001/pe)
- [EAGLES Tags](https://www.ilc.cnr.it/EAGLES96/home.html)

**El problema del PoS tagging**
Una misma palabra puede tener varios tags candidatos (**ambigüedad**)
- ¿Cómo resolverla? Desambigüación morfosintáctica
	- El contexto nos brinda información de la categoría concreta de esa palabra en ese momento.
	- [FreeLing](https://nlp.lsi.upc.edu/freeling/demo/demo.php) como herramienta online que nos permite visualizar la desambigüación

#### Stemming y Lematización
Son técnicas fundamentales del PLN. Las usamos para reducir las palabras a su forma raíz, siendo esenciales para normalizar el texto. Es reducir variabilidad en palabras para que los vectores no sean tan grandes, en esto consiste el stemming y la lematización.

| Palabra                                         | Stemming | Lematización |
| ----------------------------------------------- | -------- | ------------ |
| canto, cantas, canta, cantamos, cantais, cantan | cant     | cantar       |
- **Stemming**
	- Reduce la palabra a su raíz (*stem*)
	- Corta los sufijos de las palabras para reducirlas a su raíz morfológica.
	- Ayuda a homogeneizar las diferentes variaciones de una palabra.
	- OJO, la raíz que se obtiene no siempre tiene significado:
		- "corriendo", "corre", "corrí" -> "corr" (stem)
	- Algoritmos más usados:
		- Porter
		- Snowball

- **Lematización**
	- Segmentación de una palabra para separar la raíz (lexema) de los morfemas de flexión
	- Se obtiene el lema o forma canónica de las palabras
	- Lema: forma de citación de una palabra, la forma que tienen las palabras cuando se buscan en el diccionario.
	- Ejemplos
		- Corriendo, corre, corrí -> correr (lema)
	- Considera el contexto y reglas gramaticales para obtener la forma canónica
	- Usa un diccionario para lematizar.

**Lematización vs Stemming**
Es más agresivo y rápido el stemming pero puede dar raíces no existentes, lo que añade ruido. La lematización puede necesitar recursos con lo cual se vuelve un proceso más fino y lento pero más precisa y dando mejor compresión del texto.

Por ende, depende del problema podemos tirar por una u otra, o a veces las dos
### Análisis sintáctico
Estudia cómo las palabras se relacionan y combinan entre sí para formar unidades superiores, es decir, se estudia la estructura de una frase agrupando las palabras según su funcionalidad, estudiando entonces cómo se combinan las palabras en sintagmas y frases.

Tenemos distintas formas de agrupación:
- Sintagmas nominales: un nombre con o sin determinante.
- Sintagmas preposicionales: una preposición junto con un sintagma nominal
- Sintagmas verbales: un verbo que indica una acción, junto con otros sintagmas nominales o preposicionales.
- ...

Valor de la sintaxis:
- *Palabras sueltas:* Rugió mundo el fue volcán y el evacuado
- *Orden de sintagmas* -> El volcán rugió y todo el mundo fue evacuado

**¿Necesidad?**
 Es necesario para establecer el sentido de una oración. Pues hay que conocer el sentido de cada palabra y además, la relación jerárquica (sintáctica) entre las palabras que forman dicha oración.

Se forma pues una estructura en árbol de palabras y relaciones, un árbol sintáctico que representa la estructura de constituyentes de una frase.

Para analizar dicha estructura de una frase usamos una gramática.

**Parser** -> Herramienta que realiza el análisis sintáctico automático. Necesita una gramática del lenguaje y la información morfológica de las palabras.

Decimos que los algoritmos que llevan a cabo un análisis sintáctico global o análisis sintáctico completo (*full parsing*) brindan la estructura de una oración cuando ésta pertenece al lenguaje definido por una gramática.
- Problema: necesidad de una gramática que cubra de forma amplia, pues hemos de recoger todas las estructuras del lenguaje. Esto es muy costoso de definir.

Así, decimos que la salida de una analizador global es un árbol completo de análisis. 

**Ambigüedad sintáctica** -> Una oración puede tener varios análisis sintácticos
- A mayor cobertura de la gramática, mayor es la ambigüedad producida.

**Gramáticas**
Sea una gramática G que define el lenguaje $G=\{N, \sum, P, S\}$ donde:
- $N \equiv$ conjunto de símbolos no terminales
- $\sum \equiv$ conjunto de símbolos terminales
- $P \equiv$ conjunto de reglas
- $S \equiv$ símbolo raíz

Ej gramática sencilla oraciones SUJ-V-OBJ
$$
S \rightarrow NP \hspace{0.5cm} VP
$$$$
NP \rightarrow det \hspace{0.5cm} nombre
$$$$
VP \rightarrow verbo \hspace{0.5cm} NP
$$
- *Treebank*: Cada palabra aparece acompañada de su etiqueta y cada frase es analizada sintácticamente al completo. 

**Problemas del análisis sintáctico completo (*full parsing*)**
- Requiere conocimiento/recursos lingüísticos complejos (gramáticas, treebanks, etc.)
- Escasa cobertura de gramáticas
- Escasa robustez
- Alto coste

Entonces, ¿necesitamos siempre la estructura completa al hacer análisis sintáctico?

- Análisis sintáctico superficial (shallow parsing, chunking)
	- Representación "superficial" de la estructura sintáctica del texto
	- Menores requirimientos
	- Mayor robustez 
	- Bajo coste
#### Análisis sintáctico superficial (shallow parsing)
Los chunks son regiones no solapadas en el texto:
	[I] saw [a tall man] in [the park]

Estos no son estructuras recursivas (un chunk no contiene otros chunks)
- Simplificamos el proceso de detección
- La recursividad significa que un componente puede estar formado por componentes de su misma categoría.
	- *Ej* -> SN = Nombre + Preposición + Nombre ("Coche de caballos")
- Los chunks no son exhaustivos
	- No todas las palabras de una frase tienen que estar incluidas en chunks.

**Chunking** -> Localizar el segmento/grupo de palabras e identificar su clase.
- Gramática
	- Reglas para guiar cómo debemos identificar los chunks en las frases
	- Las reglas usan patrones de etiquetas PoS, similares a como son los patrones en expresiones regulares.
	- *Ejemplo* -> Identificar un sintagma que puede tener o no un determinante, tener uno o varios adjetivos y un nombre.
		- $<DD>?<JJ>*<NN>$

Veamos un ejemplo en código

```python
text = "Rwanda is set to become the first African nation to host the event from 21-28 September"
tokens = nltk.word_tokenize(text)
print(tokens)
tag = nltk.pos_tag(tokens)
print(tag)
gram = ("NP: {<DT>?<JJ>*<NN>}")
cp = nltk.RegexpParser(gram)
result = cp.parse(tag)
print(result)
```

Esto debería dar el siguiente output:
![[Pasted image 20260518111112.png]]

Tenemos para el shallow parsing dos enfoques posibles:
- Etiquetando palabras (IOB Tagging)
	- Etiquetamos palabras por medio de tags
	- *Chunk tags* indica el comienzo del chunk, las palabras que contiene y el tipo de chunk
		- B -> palabra inicial del chunk
		- I -> interior del chunk
		- O -> fuera del chunk
- Etiquetando separaciones entre palabras (parentización)
	- Etiquetamos separación entre palabras
	- Tags indican límites y tipo de chunk

**Entidades nombradas**
- La técnica de chunking la usamos también para identificar Entidades Nombradas.
	- Entidad Nombrada (*Named Entity*) -> Unidad de información fundamental que se refiere a nombres propios que pueden ser clasificados en unas determinadas categorías (Personas, Localizaciones, Organizaciones, etc...)

En código:
```python
import nltk

nltk.download('maxent_ne_chunker')

text = "Santorini earthquakes: What is causing 'unusual' seismic activity and what is the advice for tourists visiting Greece?"

tokens = nltk.word_tokenize(text)
tags = nltk.pos_tag(text)
ner_tags = nltk.ne_chunk(tags)

print(ner_tags)
```

Output esperado:
![[Pasted image 20260518111654.png]]

##### Chink
El **chink** es lo opuesto al *chunk*. Es toda aquella secuencia de tokens no incluida en un chunk. 
- Para indicar el chink ponemos los tags fuera de las llaves

Ejemplo de chink
![[Pasted image 20260518111803.png]]
### Análisis semántico
Estudiamos el significado de la frase completa a partir del significado de las palabras y la estructura sintáctica.
- Extrae el sentido global a partir de sentidos individuales y de relaciones. 
- Es el aspecto lingüístico más difícil de procesar.
	- NO hay teoría general del significado que podamos implementar
- El significado de la oración está compuesto por el significado de las unidades que componen la oración.
	- Principio de composicionalidad.
		- El significado de una expresión compleja es una función del significado de cada una de las unidades simples que la componen y las reglas sintácticas mediante las cuales se combinan (de las relaciones sintácticas que se establecen entre ellas)

**Problema esencial**: ambigüedad en el significado de las palabras. En contextos determinados esta se reduce.

**Fenómenos**
- *Homonimia:* Relación que se establece entre dos o más palabras que se escriben o pronuncian igual pero tienen distintos significados
	- bota (zapato) - bota (recipiente)
- *Polisemia*: Palabras con más de un significado
	- Tienda (carpa) - tienda (comercio)
	- Banco (entidad financiera) - banco (asiento)

**Desambigüación**
- Word Sense Disambiguation (WSD)
	- Proceso de seleccionar de un diccionario el significado correcto de una palabra en un contexto concreto.
	- Tarea adicional del PLN
	- Los sistemas de WSD están formados por dos componentes fundamentales: un diccionario y un algoritmo de desambiguación.
- La desambiguación del sentido de una palabra, salvo en casos extremos, no suele ser un problema para los humanos 
	- Las máquinas sí necesitan ayuda para desambiguar, incluso en casos muy sencillos.
#### WordNet
Red de sentidos para evitar desambiguación donde cada nodo representa un sentido y cada sentido se representa mediante el conjunto de palabras sinónimas en un idioma, denominado *synset* (set of synonyms)
- Cada *synset* tiene asociado más información léxica (ID único del sentido, ejemplos de uso, etc...)
- Las palabras sinónimas del *synset* son intercambiables en un contexto dado.

**Entrada en Wordnet**
- Conjunto de sinónimos (synset)
- Definición (glosa)
- Ejemplo: car
- Tenemos entrada para nombres, verbos, adjetivos y adverbios

**Synsets y lemas**
- NO podemos confundirlos
	- Un synset está asociado a un significado y se puede representar con distintos lemas (dog, can, perro...)
	- Un lema es una palabra en lenguaje natural -> puede tener varios significados.

![[Pasted image 20260518114133.png]]

Entonces, para un determinado sentido se pueden obtener los lemas que lo representan:

![[Pasted image 20260518114203.png|500]]

Y para un determinado lema, todos sus posibles sentidos:

![[Pasted image 20260518114231.png|500]]

**Red de sentido**
Lo que le da forma decimos que son las relaciones conceptuales-semánticas y léxicas entre sentidos.
- Relaciones semánticas a nivel de synset (no de palabra):
	- Sinonimia -> relación semántica de identidad o semejanza de significados
	- Antonimia -> relación semántica de contraste entre dos unidades léxicas en un contexto determinado
	- Hiperonimia/hiponimia -> "ES_UN"
		- Cereales (hiperónimo) -> arroz, avena, cebada... (hipónimos)
	- Troponimia: "hiponimia verbal" (verbo como caso particular de otro)
		- "caminar" - "pasear" (pasear como forma de caminar)
	- Entailment: relación de implicación-causa. "roncar"-"dormir"
	- Meronimia/holonimia: "PARTE_DE"
		- coche (holónimo) - motor, ruedas, carrocería (merónimos)

>[!NOTE]
>Wordnet era y es aún el estándar de facto para representar significado en las palabras de un corpus
### Análisis pragmático
Estudio del lenguaje en uso, es decir, vincula a contexto y a situación comunicativa concreta. 

**Problema** -> Presencia adverbios o pronombres cuyo significado no está explícito en una frase, sino que depende del contexto. Se extrae su significado a partir de:
- Descripciones de la situación actual (quién habla, cuándo habla, dónde está)
- Frases analizadas previamente.

**Elementos que influyen en el significado de una comunicación**
- Contexto
- Intención del hablante
- Inferencias
- Presuposiciones
- Actos de habla
## Expresiones regulares
Notación estándar para caracterizar una secuencia de caracteres (letras, números, espacios, tabuladores y signos de puntuación)
- Esta forma un patrón que ayuda a encontrar las coincidencias en los textos.
- Permiten buscar, validar y manipular texto de forma eficiente.
- Se les denomina regex o regexp

Frecuentes usarlas en PLN, pues juegan un papel fundamental porque permiten buscar texto de forma eficiente.
- Diferentes análisis del lenguaje
- Recuperar información
- Detectar Entidades Nombradas
- Extraer información
- Etc..
### Tipos de expresiones regulares
- **Coincidencia literal**
	- ER más simple, una secuencia de caracteres tiene que coincidir exactamente con la cadena de texto.
		- Ejemplo "mundo" tendrá que coincidir con "mundo"
	- ER case-sensitive, se distingue entre mayus y minus
- **Clausura de Kleene**
	- Operador `*`: cero o más ocurrencias de la ER inmediatamente anterior
		- ba* -> b, ba, baa, baaaaaa, ....
	- Operador `+`: una o más ocurrencias de la ER inmediatamente anterior.
		- ba+ -> ba, baa, baaa, ...
- **Grupos y alternativas**
	- Símbolo `|` para representar alternativa
		- a | b -> a o b
	- Paréntesis para agrupar partes de expresión regular
		- (ba)+ -> ba, baba, babababa, ...
		- (b | a)+ -> b, a, bb, ba, aa, ab, ...
- **Cuantificadores**: Definen cuántas veces debe aparecer un carácter o grupo en la cadena. Algunos ejemplos son:
	- {n, m} -> de n a m repeticiones de la ER que lo precede
	- {n} -> exactamente n repeticiones
	- {n, } -> repite al menos n veces o más
- **Caracteres especiales**: Metacaracteres con significados especiales en expresiones regulares. 
	- . (punto) -> Este símbolo coincide con cualquier carácter excepto el salto de línea
		- beg.n -> begin, begun, begxn, ...
		- a.`*`b -> cualquier cadena que empiece con a y termine con b
	- ? -> coincide con cero o una repetición de lo anterior.
	- [] -> agrupa caracteres en grupos o clases
		- [a - z] -> especifica el rango de caracteres que va de la a la z
	- \ -> escapa un carácter especial para tratarlo como literal
	- $ -> final de la cadena
	- ^ -> coincide sólo al principio de la cadena
		- si lo usamos con corchetes sirve para indicar que algo no esté presente.
		- ![[Pasted image 20260518120210.png]]
	- Más caracteres especiales
		- ![[Pasted image 20260518120233.png]]
		- [Y muchos más](https://docs.python.org/3/library/re.html#re-syntax)

**Precedencia de operadores**
Aquí los tenemos ordenados de mayor a menor preferencia

![[Pasted image 20260518120326.png|500]]

### Expresiones regulares en Python
El módulo `re` en Python es el que da soporte para expresiones regulares. Algunos métodos que tiene:

![[Pasted image 20260518120422.png]]

Ejemplos:
- Dado un texto obtener sólo los números que aparezcan en él:![[Pasted image 20260518120446.png]]
- Dado un texto extraer las direcciones email que aparezcan en él:![[Pasted image 20260518120508.png]]
## Recursos lingüísticos
Nos referimos con este término a un conjunto de datos en formato legible por la máquina. Hay diferentes tipos:
- Lexicones
- Corpus
- Ontologías
- Bases de datos léxicas
- Diccionarios
- Etc...
### Lexicón
Diferentes definiciones para este término:
- En sentido general es el conjunto de lexemas (palabras y expresiones idiomáticas o frases hechas) de una lengua, que aparecen listados y definidos en un diccionario.
- En gramática generativa es un componente que contiene un listado de los elementos léxicos de una lengua e información sobre sus propiedades estructurales, esto es, especificaciones sintácticas, semánticas y fonológicas
- Es el sistema mental que contiene toda la información que posee un hablante sobre el vocabulario de su lengua. Dicha info abarca desde el conjunto de elementos léxicos del hablante a datos sobre cómo se pronuncia una palabra, los patrones gramaticales de uso y su(s) significado(s)
#### Tipos de lexicones
**Lexicones para análisis de sentimientos**
- Profesor Bing Liu. Recopilación de palabras con valor positivo o negativo. Todo en inglés -> [Enlace](http://www.cs.uic.edu/~liub/FBS/opinion-lexicon-English.rar)
- [SentiWordNet](https://github.com/aesuli/SentiWordNet), usa synsets (grupos de sinónimos de WordNet). Cada synset tiene anotaciones, para identificar el grado de valor positivo, negativo o bien de objetividad que contiene cada palabra.
	- Ejemplo de uso:  ![[Pasted image 20260518122108.png]]
- [AFINN lexicón](http://corpustext.com/reference/sentiment_afinn.html), lista de términos en inglés con rango de valores entre -5 (negativo) y 5 (positivo)
**Lexicón de emoticonos** se suelen usar en aplicaciones que tratan de detectar emociones -> [EmoLex](https://saifmohammad.com/WebPages/NRC-Emotion-Lexicon.htm)
#### Retos de estos sistemas
- Lagunas léxicas. Palabra o frase no incluida en el lexicón.
- Polisemia y simetría de las palabras
- Dominio específico.
### Corpus
**Definiciónes**
- ![[Pasted image 20260518122341.png]]
- ![[Pasted image 20260518122347.png]]

**¿Qué es un corpus?**
- Conjunto de datos y descripciones del lenguaje natural en formato electrónico. Un corpus puede ser escrito u oral. En referencia a los corpus escritos se puede hablar de corpus lingüísticos como un conjunto de textos preparados y adaptados para la investigación lingüística (no cualquier colección de textos constituye un corpus lingüístico)
- Una colección de textos se considera un corpus cuando es lo suficientemente representativa de la variedad del lenguaje u objeto lingüístico que se quiere estudiar, abarcable para que la investigación pueda llevarse a cabo y además está almacenada en un soporte procesable por un ordenador.
- Corpora en plural
#### Tipos de corpus
Según el origen o naturaleza de los datos:
- Corpus oral
- Corpus textual
- Corpus multimodal
Según la codificación y anotación:
- Corpus simple -> Donde no hay codificación y anotación en los textos que lo compone.
- Corpus codificado o anotado -> Pueden contener los textos anotaciones correspondientes a diferentes análisis del lenguaje.
	- Ejemplo 1: Anotadas enfermedades en textos de notas clínicas
	- ![[Pasted image 20260518122759.png]]
	- Ejemplo 2 : Titulares de noticias anotados con polaridad de sentimiento para tres entidades específicas
	- ![[Pasted image 20260518122826.png]]
Según la lengua:
- Corpus monolingüe -> Todos los textos en una sola lengua
- Corpus bilingüe -> Todos textos en dos lenguas diferentes
- Corpus multilingüe -> Textos del corpus escritos en más de dos lenguas
Para corpus escritos en más de una lengua:
- Corpus paralelo -> Contiene misma colección de textos en más de una lengua, de manera que si es bilingüe los textos de una lengua son una traducción exacta de los textos de la obra.
	- Ejemplo de tres lenguas adicionales
	- ![[Pasted image 20260518123105.png]]
- Corpus comparable -> Los textos de una lengua no son traducciones exactas de los textos del resto de lenguas. Simplemente un corpus comparable se compone de textos en diferentes lenguas con temática similar.
Según la especificidad de los textos:
- Corpus general
- Corpus especializado.
Otras clasificaciones:
- Según cantidad de textos (grande, referencia, pequeño...)
- Según accesibilidad (público, privado, de acceso restringido...)

**¿Qué tener en cuenta a la hora de diseñar un corpus?**
- Representatividad (muestra representativa)
- Aspectos legales y licencias
- Plataformas para anotar.
#### Anotación de corpus
- Anotación lingüística
	- Se realizan marcas o anotaciones sobre textos para describir, analizar o relacionar aspectos concretos.
	- Pueden ser a nivel de palabra, sintagma, frase, texto completo...
	- En la descripción de un corpus anotado se puede encontrar info de la anotación
		- Guía de anotación
		- Información de cuántos anotadores, métricas del grado de acuerdo entre ellos...
#### Ejemplos de algunos corpus
- Brown corpus
	- Primer corpus general disponible en formato electrónico 
	- Millón de palabras y recopilado en universidad de brown en años 1963-64
	- Textos de diferentes géneros (periódicos, académicos, ficción, etc...)
	- Incluido en NLTK (https://www.nltk.org/nltk_data/)
- Reuters corpus
	- Gran colección de historias publicadas por la agencia Reuters para fines de investigación y desarrollo.
- Spanish Billion Word Corpus and Embeddings
	- Corpus no anotado en español con casi 1500 millones de palabras, compilado a partir de diferentes corpus y recursos de la web.
#### Corpus en NLTK

![[Pasted image 20260518123707.png]]
