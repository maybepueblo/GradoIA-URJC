**Soft Computing**
Conjunto de técnicas empleadas para ofrecer solución a tareas computacionales costosas, siendo las soluciones dadas como aproximadas de forma habitual. Exploramos con esto la tolerancia de la precisión.
## Redes de neuronas
**Definición** -> Paradigma de aprendizaje inspirado en el sistema nervioso. En este existen las llamadas neuronas que están interconectadas entre sí. 

Buscamos producir una respuesta de salida dados una serie de estímulos de entrada. Lo aplicamos en **problemas de clasificación** y **reconocimiento de patrones**, entre otros.

*Ejemplos*
Entrada/Salida, Capas, Funciones de propagación
## Máquinas vectores soporte (MVS)
**Definición** -> Conjunto de algoritmos de aprendizaje supervisado. Lo aplicamos en la resolución de problemas de clasificación. 

Necesitamos conjuntos de datos de entrenamiento que permitan etiquetar una serie de clases de modo que, cuando venga un individuo nuevo, pueda determinar a qué clase pertenece.

De normal hacemos la separación de clases con rectas, planos o hiperplanos (sencillo). En ocasiones, tenemos que usar representaciones más complejas, aquí empleamos una función kernel que permite hacerlo.
## Lógica borrosa
**Definición** -> Forma de pensar donde los mismos conceptos son percibidos de manera distinta por diferentes individuos. 

Así, definimos una serie de conjuntos difusos que se solapan entre sí. Tenemos entonces que un valor determinado pertenece en cierto grado a un conjunto y en cierto grado a otro. 

Esto lo hacemos a traves de una **función de pertenencia**, que asigna un grado de membresía entre 0 y 1. Además tenemos una serie de reglas difusas del tipo *"Si... entonces..."* que asignan acciones a una situación determinada mediante inferencia.
## Computación evolutiva
Campo dentro de la IA que incluye la optimización combinatoria y la optimización continua. Engloba el conjunto de técnicas conocidas como metaheurísticas. 

Son un subconjunto que incluye aquellas técnicas con inspiración biológica. 
# Algoritmos heurísticos/metaheurísticos

## Heurísticas
Procedimientos simples a menudos basados en el sentido común que se supone que obtendrán una buena solución (no tiene por qué ser óptima) a problemas difíciles de un modo sencillo y rápido.

Siendo entonces estos algoritmos métodos para problemas donde la rapidez del proceso es tan importante como la calidad de la solución obtenida. 

**¿Útiles?**
No se dispone de un algoritmo exacto para muchos problemas, y en caso de haberlo, la cardinalidad del espacio de búsqueda lo hace muy ineficiente de usar. 

Necesitamos soluciones aproximadas que garantizan un óptimo a un problema. El método heurístico proporciona una buena solución inicial de partida (BB) y además participa en paso intermedio del procedimiento.

Por eso los usamos, para dar buenas soluciones en poco tiempo.

**Limitaciones**
- Dependen de la estructura del problema
- No pueden escapar de óptimos locales, véase [[Tema 1 - Introducción a la optimización]]
- No hay mecanismos para seguir buscando un óptimo global al llegar al local.

### Tipos de algoritmos heurísticos
- Constructivos: construyen una solución factible a un problema dado siguiendo una estrategia predefinida.
	- Aleatorizado
	- Voraz
	- Descomposición
	- Reducción
	- Manipulación del modelo
- De búsqueda: partimos de una solución factible ya construida para tratar de encontrar una solución mejor
	- Aleatorizada
	- First improvement
	- Best improvement

### Medidas de calidad
Un heurístico/metaheurístico debe de tener las siguientes propiedades:
- Eficiente
- Bueno
- Robusto

Entonces, medimos para cada uno de los ejemplos, la desviación porcentual de la solución heurística frente a una referencia, calculando posteriormente el promedio de dichas desviaciones.

**Posibles referencias**
- Comparar con sol. óptima
- Comparar con cota
- Comparar con método exacto truncado
- Comparar con otros heurísticos
- Análisis peor caso
## Metaheurísticos
Buscan obtener mejores resultados que los alcanzados por los heurísticos tradicionales. Se sitúan conceptualmente por encima de los heurísticos, guiando su comportamiento.

### Intensificación y diversificación
Son la base para que una metaheurística funcione. En general son conceptos contrapuestos por lo que es necesario encontrar un balance entre ellos.

Definimos:
- **Intensificación**: definimos un proceso de búsqueda muy exhaustivo para explorar una vecindad muy limitada, buscando su óptimo local.
- **Diversificación:** definimos un proceso que permite visitar vecindades lejanas sin explorarlas en profundidad
### Estrategias para escapar de óptimos locales
- Búsqueda multi-arranque
- Búsqueda aleatorizada
- Búsqueda determinista

# Taxonomía
![[Pasted image 20260528132607.png]]

















