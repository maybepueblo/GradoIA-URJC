tokenización: dividir el texto en partes más pequeños
## ¿Qué es el Procesamiento del Lenguaje Natural (PLN)?
- Es una rama de la Inteligencia Artificial que ayuda a los ordenadores a comprender, interpretar, manipular y generar el lenguaje humano.
- Es un campo interdisciplinar, que combina informática y lingüística que usa el aprendizaje automático para alcanzar un objetivo.
## Importancia del PLN
- Los datos son esenciales para tomar decisiones
- Los datos crecen de forma exponencial en el mundo
- 80% de datos están no estructurados, siendo estos texto.
	- Datos estructurados: formato predefinido y que siguen una estructura clara.
	- Datos no estructurados: no tienen una estructura predefinida y que, por tanto, no se pueden organizar fácilmente en tablas o en bases de datos relacionales.

Por ende, hay una cantidad ingente de información que tenemos que gestionar para generar conocimiento.
- Sin embargo, el lenguaje natural es extremadamente complejo
- El PLN es importante porque ayuda a entender datos no estructurados y a reducir la ambigüedad del lenguaje natural.
## Aplicaciones del PLN
Tareas que tengan que ver con el lenguaje:
- Extraer información
- Sistema de recomendación
- Fake news
- Idioma
- Traducción
- Spam
## ¿Cómo funciona el PLN?
Lo dividimos en dos aspectos esenciales:
- Lingüística
- Ciencia de datos

Convierten el texto en algo entendible por la máquina, creando representaciones vectoriales. Para ello hay que preprocesar el texto haciendo por ejemplo:
- Segmentación
- Tokenización
- Eliminación de stop words
- Stemming
- Lematización
- ...
## Evaluación
- **Matriz de confusión**
	- Predicciones de uno de cuatro resultados, basado en cómo coincide respecto al valor real:
		- **Verdadero Positivo**
		- **Verdadero Negativo**
		- **Falso positivo**
		- **Falso negativo**
- **Precisión**
	- Proporción de casos positivos predichos correctamente respecto al número total de casos positivos predichos.$$precision=\frac{TP}{TP+FP}$$
- **Recall (Exhaustividad)**
	- Proporción de casos positivos identificados correctamente en relación al total de casos positivos reales. $$recall=\frac{TP}{TP+FN}$$
- **F1 (valor F, medida F)**
	- Medida armónica entre precisión y recall$$F1=2*\frac{precision*recall}{precision+recall}$$ $$F_\beta=(1+\beta²)*\frac{precision*recall}{(\beta²*precision)+recall}$$
	- Donde si $\beta = 1$, es el mismo peso a precisión y recall combinados, si es 0.5, se prioriza precisión y en 2, se prioriza el recall.
- **Accuracy (Exactitud)**
	- Porcentaje de casos en los que el algoritmo acierta en ambas clases, es decir, acierta en los TP, pero también en los TN.$$accuracy=\frac{TP+TN}{TP+TN+FP+FN}$$
## Librerías para PLN
- Usamos Python
	- [NLTK](https://www.nltk.org/)
	- [spaCy](https://spacy.io/)
	- [Gensim](https://spacy.io/)
	- [TextBlob](https://textblob.readthedocs.io/en/dev/)
	- [Stanza](https://stanfordnlp.github.io/stanza/)
- Librerías para ML
- Librerías de DL
- Hugging Face