## Machine Learning
El aprendizaje automático (para esta asignatura, ML) nos hace pensar a través de su significado: *Machine Learning*. Toca analizar la importancia de cada significado para construir lo que trata de expresar la asignatura.
- ***Machine***: Aparato con entradas y salidas esperadas además de modificables. Lo que nos permita darle una modificación para que dicha máquina tenga comportamientos diferentes se denomina **parámetros**. Este concepto es la base del ML. **Si una máquina no tiene parámetros, es imposible que aprenda**. En esta asignatura este término se acuña a la hora de usar para las funciones paramétricas. 
- ***Learning***: A la hora de aprender, decimos que es la capacidad de una máquina de tener el proceso del aprendizaje automatizado sin intervención humana. Con esto, tenemos que encontrar unos parámetros que simbolizan si nuestra máquina es capaz de aprender o no, unos ejemplos para determinar el objetivo del programa, la función que busca la misma (pérdida, objetivo, fitness...) además de un carácter de retroalimentación que permita la actualización de dichos parámetros que forman la máquina. Esto se hace para buscar una máquina que con este modelo y parámetros óptimos ha **aprendido** a generalizar los ejemplos dados.
Cualquier tarea de ML se formula como la búsqueda de los parámetros que **minimizan** el error entre lo obtenido y lo deseado. Asimismo hemos de resaltar la importancia de que cada tarea de ML pertenece a un cierto dominio. Dos tablas con datos iguales pero de distinto dominio se han de tratar y modelar diferente.
### Notación
- **Datos** -> Serán tabulados en este curso. Se han de representar en forma de tabla siendo cada fila un ejemplo. Así, los ejemplos son un array de valores (**atributos** o **features**)
-  **Modelos** -> Función paramétrica de los ejemplos
- **Optimizar** -> Minimizar función de perdida (*Loss*). Es buscar los parámetros que logren la menor pérdida posible. A veces se puede plantear la maximización de la probabilidad o de la ganancia de información. Sin embargo, esto es redundante porque maximizar f(x) es lo mismo que minimizar - f(x). 
## Tipos de aprendizaje
- **Supervisado**
	- Conjunto de ejemplos emparejados "x" uno a uno con valor "y" que recibe varios nombres, siendo los más habituales: "etiqueta", "clase", "valor objetivo", "target" o "ground truth". Queremos predecir  "y" a partir de los emparejamientos. Tenemos que estar para proporcionar etiquetas, esto es un proceso lento y costoso.
- **No supervisado**
	- Eliminando y entonces nos quedan solo ejemplos. El tipo de tareas que podemos hacer sin etiquetas es diferente y se agrupan todas aquí.
- **Por refuerzo**
	- Si eliminamos los ejemplos buscamos que la máquina adquiera la propia información de su entorno.
Consideramos en que en los dos últimos no hay intervención humana. Si uno ha dado los datos es solamente un intermediario. Ni siquiera importa si es humano el que haya programado los algoritmos de ML. Sólo el supervisado se considera que hay para dar los emparejamientos.

Hay problemas que no son tan fácil de clasificar:
- **Semi-supervisado** -> Familia de problemas donde existe un pequeño subconjunto de ejemplos que sí está etiquetado pero la gran mayoría no.
- **Auto-supervisado** -> Usamos los mismos ejemplos dados como etiquetas. Por ejemplo dada la primera mitad de X intenta predecir la segunda.
- **On-line** -> No todos los ejemplos están disponibles al mismo tiempo en una base de datos o memoria.

Por último, podemos clasificar el problema de ML según los tipos de datos usados:
- **Tabulados**: Dato básico y más común. Tablas con ejemplos descritos por arrays de atributos. 
- **Secuenciales**: Ejemplos ordenados (relación entre ellos)
	- Series temporales -> Tienen un índice denominado tiempo.
	- Series espacio-temporales -> Lo de arriba con dos o tres coordenadas que marcan la trayectoria seguida en ese tiempo.
	- Texto -> Los datos tienen un orden pero su naturaleza es diferente de una colección de números.
- **Estructurados**: Aquellos datos recogidos en formato establecido y conocido.
- **No estructurados**: Requieren métodos específicos.
- **Imágenes**: Matriz tridimensional con elemento conocido como *pixel*.
- **Texto**: Problema con idioma pero conjunto limitado (enorme) de elementos atómicos (palabras)
- **Audio**: Una o varias series temporales pero tratamiento o interpretación diferentes.
## Éxito
Para tenerlo, nos basamos en 3 leyes fundamentales:
1. **Buenos datos**
2. **Buenos modelos**
3. **Buenas prácticas**
### Buenos datos
Han de ser correctos, abundantes y representativos y mejor que mejor si están bien etiquetados. A veces tendrán errores y huecos, y si están bien etiquetados es normalmente porque no tenemos muchos datos. Otras veces tenemos muchos ejemplos de un tipo y muy pocos de otro. 
Tenemos técnicas para suplir la carencia de estos, pero para aplicarlas es imprescindible conocer y comprender los datos dados, así como el dominio y el problema o la tarea llevada a cabo. 
### Buenos modelos
El modelo generaliza datos y predice. Por datos muy buenos que tengamos, si pillamos un modelo de forma incorrecta, no lograremos buen resultado.
Las causas de un mal modelo se debe a una elección equívoca del número de parámetros o un mal ajuste de estos.
### Buenas prácticas
Es importante saber delimitar en qué momento o bajo qué circunstancias las predicciones o estimaciones dejan de ser aceptables. 
Recopilando lo dicho, para resolver problemas o tareas de ML necesitamos datos que alimentarán algoritmos cuyo objetivo es encontrar los parámetros óptimos del modelo. Esto requiere conocimiento y experiencia

