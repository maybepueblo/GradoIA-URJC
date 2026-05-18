### 1. Conceptos Preliminares: Bases Biológicas y Artificiales
Las Redes Neuronales Artificiales (ANN) son modelos computacionales diseñados para encontrar patrones y modelar relaciones complejas entre entradas y salidas, inspirándose directamente en la estructura neuronal del córtex del cerebro humano.

Existe un paralelismo claro entre una neurona biológica y una unidad artificial:
- **Dendritas:** En biología reciben señales químicas. En la red artificial, se corresponden con las señales de entrada ($x_n$).
- **Soma (Cuerpo neuronal):** Biológicamente integra los impulsos. En la red, se encarga de la ponderación (multiplicando por los pesos sinápticos $W_n$) y la suma de los valores.
- **Umbral de activación:** Es el límite biológico para disparar un impulso , que en el modelo computacional se representa mediante la **función de activación**.
- **Axón:** Es la salida biológica hacia otras neuronas , equivalente a la salida matemática $y$ de la red.
### 2. Arquitecturas y Tipos de Aprendizaje
Las redes se pueden clasificar según su arquitectura y cómo transmiten la información:
- **Redes Prealimentadas (Feedforward):** La información fluye en una única dirección (de entrada a salida) sin formar bucles ni ciclos. Un ejemplo clásico es el Perceptrón de Múltiples Capas (MLP).
- **Redes de Retropropagación (Backpropagation):** Diseñadas para entrenar redes multicapa. Calculan el error en la salida y lo propagan hacia atrás para actualizar los pesos de las conexiones eficientemente mediante la técnica de descenso por gradiente.
    - _Desventajas:_ Dependen mucho de cómo se inicialicen y sufren del "desvanecimiento del gradiente", donde la señal de error se vuelve tan pequeña en redes profundas que los pesos dejan de actualizarse y el entrenamiento se detiene.
**Métodos de aprendizaje utilizados durante el entrenamiento:**
- **Supervisado:** Se proporcionan los datos de entrada junto con las salidas esperadas para que la red ajuste sus cálculos.
- **No supervisado:** La red no conoce las respuestas correctas; debe encontrar patrones basándose únicamente en las observaciones de entrada.
- **Reforzado:** La red se evalúa a sí misma, reforzando positivamente las salidas correctas y descartando las erróneas.
- **Híbrido:** Una combinación de los métodos anteriores.
### 3. Redes Neuronales Convolucionales (CNN)
Aunque se crearon inicialmente para clasificar imágenes basándose en que pequeños filtros pueden identificar partes representativas de un todo, también son aplicables al texto. Su entrada matemática es siempre una matriz y funcionan mediante ciclos de capas:
- **Capas de Convolución:** Utilizan "filtros" inicializados aleatoriamente que se desplazan por la matriz de entrada para extraer características relevantes. En cada movimiento, multiplican sus valores con los de la entrada para generar una nueva matriz llamada mapa de características (_feature map_).
- **Función de Activación ReLU:** Se aplica tras la convolución para aportar no linealidad. Su fórmula es $ReLU(x) = max(0, x)$, lo que significa que elimina los valores negativos (convirtiéndolos en 0) y mantiene los positivos intactos para conservar solo las características relevantes.
- **Capas de Pooling (Agrupación):** Reducen el tamaño del mapa de características sin perder la información esencial del objeto representado. Puede ser **Max-pooling** (selecciona el valor máximo) o **Average-pooling** (calcula la media).
- **Capas Densas (Fully Connected):** Se ubican al final de la arquitectura. Cada nodo se conecta a todos los de la capa anterior. A diferencia de las capas previas que usan ReLU, estas utilizan la función de activación **Softmax** para clasificar y generar probabilidades finales.
### 4. Redes CNN aplicadas al Procesamiento del Lenguaje Natural (PLN)
Para usar una CNN en texto, el proceso requiere adaptar la información a un formato matricial:
- **Preparación (Tokenización y Embeddings):** Se tokeniza el texto para crear un vocabulario. Cada token recibe un índice numérico y se representa mediante un vector de números reales de una dimensión fija (utilizando modelos de Word Embeddings o inicialización aleatoria).
- **Ajuste de tamaño:** Como la red necesita un tamaño de entrada fijo, se determina una longitud estándar ideal para el corpus. Si el texto es más corto, se aplica **Padding** (añadiendo tokens vacíos `<pad>` con índice 0 al principio o final). Si es más largo, se aplica **Truncation** (recortando tokens sobrantes).
- **Filtros en PLN:** Dado que el texto tiene una sola dimensión (la secuencia de tokens), los filtros actúan como "ventanas" de palabras. Un filtro que abarque $N$ palabras tendrá una dimensión matricial de $N \times dim$ (siendo $dim$ la dimensión del embedding).
### 5. Redes Neuronales Recurrentes (RNN)
Las RNN están específicamente diseñadas para datos secuenciales (texto, audio o series temporales) porque tienen "memoria".
- **Funcionamiento:** En lugar de procesar los datos de forma aislada, contienen conexiones recurrentes (bucles de retroalimentación) donde la salida de una neurona vuelve a entrar en ella misma en el siguiente paso.
- **Estados Ocultos (_Hidden States_):** Actúan como la memoria de la red. Al procesar una secuencia, el estado oculto actual se calcula usando la entrada del momento presente y el estado oculto del paso anterior.
- **Entrenamiento en NLP:** En PLN, la red recibe una secuencia de embeddings (matriz de dimensión $|V| \times d$). Utiliza la técnica de Retropropagación a Través del Tiempo (BPTT) para actualizar los pesos retrocediendo en la secuencia. Finalmente, suele aplicar la función Softmax en la salida para calcular probabilidades (ej. predecir la siguiente palabra).
- **Limitaciones críticas:** Al intentar procesar secuencias largas, la red "olvida" las primeras palabras. Además, son extremadamente vulnerables al **desvanecimiento del gradiente** (los parámetros dejan de actualizarse) y a la **explosión del gradiente** (crecen sin control haciendo inestable el aprendizaje).
### 6. Redes de Memoria a Corto y Largo Plazo (LSTM) y Bi-LSTM
Para solucionar los olvidos y mitigar el desvanecimiento del gradiente de las RNN estándar, se crearon las LSTM. Estas redes integran "celdas de memoria" complejas que priorizan qué información retener a largo plazo ($C_t$) y qué información mantener a corto plazo ($h_t$) a través de un sistema de "puertas" (_gates_):
1. **Puerta de entrada (_Input gate_):** Decide qué información nueva (de la entrada actual y el estado previo) es importante y debe añadirse a la memoria.
2. **Puerta de olvido (_Forget gate_):** Analiza los datos actuales y pasados para decidir qué información almacenada ya está obsoleta y debe ser eliminada.
3. **Puerta candidata (_Candidate gate_ / _State cell_):** Tras evaluar las dos puertas anteriores, calcula y guarda el estado actual combinado de la celda de memoria ($C_t$).
4. **Puerta de salida (_Output gate_):** Determina qué información de la celda de memoria actualizada debe salir en este momento a corto plazo ($h_t$).
**Ventajas y Desventajas de las LSTM:**
- Minimizan radicalmente el problema del descenso del gradiente, permitiendo un aprendizaje estable a lo largo del tiempo.
- Sin embargo, son computacionalmente costosas, difíciles de entrenar por su cantidad de hiperparámetros, requieren bases de datos inmensas y tienden al sobreentrenamiento si los datos no son variados.
**Redes Bi-LSTM (Bidireccionales):**
- Mientras las RNN o LSTM normales leen un texto secuencialmente (de izquierda a derecha), las Bi-LSTM añaden una capa adicional para leer también de derecha a izquierda simultáneamente (desde la última palabra hacia la primera).
- _El coste:_ Consumen mucha más memoria, requieren el doble de recursos y no sirven para procesar datos en directo (_streaming_), ya que necesitan tener la frase completa antes de empezar a evaluarla.