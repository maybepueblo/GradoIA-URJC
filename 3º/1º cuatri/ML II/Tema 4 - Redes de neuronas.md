>[!NOTE]
>Necesitamos la función de activación para otorgar flexibilidad a nuestro modelo. Si esta no existiese, tendríamos menos parámetros, siendo equiparable a un modelo lineal, que es peor que nuestra red de neuronas.

unidades ocultas
$h_1 = a[\theta_{10}+\theta_{11}x_1+\theta_{12}x_2]$  siendo $0_{10}$ el sesgo asociado
# Conceptos fundamentales y estructura
## Componentes del modelo
Una Red de Neuronas (RN) se compone de varias capas de unidades de procesamiento (neuronas):
- **Capas:** La red tiene una **capa de entrada** (se introduce la información), una o varias **capas ocultas** (realizan transformaciones complejas) y una **capa de salida** (produce el resultado final)
- **Conexiones y parámetros:** Las conexiones entre neuronas se definen por pesos ($\ohm$) y cada neurona tiene un sesgo ($\beta$) que se suma al cálculo lineal. El conjunto de pesos y sesgos son los parámetros del modelo que deben aprenderse.
- **Neurona o unidad oculta** - Realiza dos pasos:
	1. **Cálculo lineal (Pre-activación, $z$)**: Combina las entradas de la capa anterior, multiplicadas por los pesos y sumando el sesgo ($\ohm x + \beta$)
	2. **Función de activación ($a()$)** Aplica una función no lineal a la pre-activación para obtener la activación ($h=a(z)$)
## Tipos de redes y terminología
- **Red *Feedforward*** Aquella en la que no hay ciclos en el grafo de cómputo
- **Fully Connected Network:** Aquella donde todo elemento de una capa está conectado a todo elemento de la siguiente. 
- **Red Superficial (*Shallow*)**: Tiene una única capa oculta
- **Red Profunda (Deep)**: Más de una capa oculta
## Funciones de activación
La función de activación es esencialmente la que convierte el modelo en **no lineal**, permitiéndole aprender relaciones complejas.
- **Necesidad de No Linealidad:** Si la función de activación fuese lineal, el resultado final de toda la red sería simplemente otra función lineal de la entrada, por lo que el modelo resultante no sería mejor que un modelo lineal simple.
- **Ejemplos comunes**:
	- **ReLU (Rectified Linear Unit):** Tipo de activación común
	- **Sigmoide:** Se usa a menudo en la capa de salida para problemas de clasificación binaria (con una única salida) ya que permite obtener valores en el intervalo que representan la probabilidad a posteriori de la clase positiva.
# Capacidad del modelado
## Teorema de aproximación universal
Este teorema establece que, con un **número suficiente de unidades ocultas**, una RN puede describir **cualquier función continua** en un subconjunto compacto con precisión arbitraria.
- Aunque el teorema garantiza la existencia de una red capaz de representar la función deseada (a veces con un número exponencialmente grande de unidades ocultas), **no prueba si esa red puede encontrarse** mediante un algoritmo de aprendizaje.
## Partición del espacio (Regiones)
Las redes de neuronas dividen el espacio de características de entrada en diferentes regiones (politopos convexos)
- El número de regiones que una red puede crear depende del número de entradas ($D_i$) y del número de unidades ocultas ($D$)
- Si el número de entradas es igual al número de unidades ocultas ($D_i = D$), el número máximo de regiones es $2^D$
# Entrenamiento de redes de neuronas
El entrenamiento (encontrar los parámetros óptimos Φ) se realiza minimizando una función de coste (o pérdida media) sobre el conjunto de datos de entrenamiento
## Funciones de pérdida
La función de pérdida $L$ mide cuán malo es el modelo para un dato específico
- **Clasificación Binaria:** Se usa la función de pérdida **Entropía Cruzada Binaria** (*Binary Cross Entropy* o *binomial deviance*) cuando la salida del modelo es la probabilidad de la clase positiva (generalmente después de pasar por una sigmoide)
- **Clasificación multiclase:** Cuando la red tiene $K$ salidas (una por clase) se usa **SoftMax** para asegurar que las probabilidades suman 1, y luego la **Entropía Cruzada Multiclase**
- **Regresión**: Se usa de normal el **Error Cuadrático Medio (MSE)**
## Optimización (Descenso de Gradiente)
La minimización de la función de coste se realiza mediante algoritmos de Descenso de gradiente:
- **Descenso de Gradiente Estocástico (SGD)** En lugar de usar todos los datos de entrenamiento (*full batch*), el SGD usa una **muestra de datos** (*mini-batch*) para calcular una estimación del gradiente.
	- Para completar una **época** (pasar por todos los datos), se barajan aleatoriamente los datos y luego se toman los mini-batches secuencialmente
	- El SGD puede ayudar a escapar de **mínimos locales** al añadir ruido al proceso
- **Actualización de parámetros** En cada iteración, los parámetros se actualizan en dirección opuesta al gradiente, escalados por la tasa de aprendizaje ($\alpha$):$$Φ_{t+1}\leftarrowΦ_t-\alpha\frac{∂J(Φ)}{∂Φ}$$
## Backpropagation (Retropropagación del gradiente)
Para que el descenso de gradiente funcione en una RN (NN - Neural Network), se necesita calcular de forma eficiente el gradiente de la función de coste con respecto a todos los parámetros. Esto se logra mediante ***Backpropagation***.
- **Grafo de cómputo**: La RN se representa como un **grafo de cómputo**, donde cada operación (suma, multiplicación, activación) es un nodo
- **Regla de la cadena**: El cálculo de gradiente se basa en la **regla de la cadena** del cálculo, usada para calcular derivadas de funciones compuestas.
- **Dos fases de backpropagation**:
	1. **Paso hacia adelante (*Forward Pass*)**: Se ejecuta la red desde la entrada hasta la salida, calculando pre-activaciones y activaciones de cada nodo.
	2. **Paso hacia atrás (*Backward Pass*)**: Se inicializa la derivada en la capa de salida (con respecto a la pérdida) y se propaga hacia atrás, multiplicando los gradientes locales en cada nodo
- **Objetivo final**: El objetivo último es calcular las derivadas de la función de pérdida con respecto a los parámetros (pesos $\ohm$ y sesgos $\beta$) en cada capa, para poder actualizarlos en el paso del Descenso de Gradiente.