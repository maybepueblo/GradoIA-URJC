Los lengujaes regulares son en una gran mayoría de sus veces, simples, para ciertas aplicaciones. Por ello, es necesario estudiar lenguajes libres de contexto (sin estar atados a una circunstancia). Estos tienen aplicaciones en el desarrollo de compiladores y en la compartición de información.

Podemos dar significado a un programa mediante la estructura del árbol. Veamos un ejemplo:

![[Pasted image 20241021153906.png]]

Como vemos en la imagen, tenemos dos formas de interpretar el programa `1+2*3`. Esto significa que todo depende de la estructura de nuestro árbol.

#### Gramáticas libres de contexto

Vamos a definir formalmente una gramática libre de contexto (conocida como de tipo 2) como:
$$G=(V, \sum, Q_o, P)$$
donde:

- V es el conjunto de variables (símbolos no terminales).
- Sum es el alfabeto (símbolos terminales).
- Qo es el símbolo inicial.
- P es el conjunto de producciones.

Todas las producciones en P deben de ser de la forma A -> ω, donde `A ∈ V y ω ∈ (Σ ∪ V)*`

Un lenguaje libre de contexto es aquel generado por una gramática libre de contexto. 

#### Derivaciones 

Vamos a explicar las derivaciones, que es la secuencia de pasos que va desde el símbolo inicial hasta una palabra del lenguaje aplicando las producciones de la gramática.

Veamos dos tipos especiales de derivaciones:
- **Derivación más a la derecha** -> siempre sustituímos la variable más a la derecha en la configuración. 
- **Derivación más a la izquierda** -> siempre se sustituye la variable más a la izquierda. 

Para cualquier derivación, existe una derivación más a la izquierda y más a la derecha equivalente.

#### Árboles de derivación

Representación visual de las derivaciones, veamos una imagen:

![[Árboles de derivación|1000]]

- La raíz es el símbolo inicial.
- Los nodos internos son variables (símbolos no terminales).
- Las hojas son símbolos terminales o ε (palabra vacía).
- Cada nodo y sus hijos representan una producción de la gramática.

>[!WARNING] 
>Para cada palabra, el árbol de derivación es único.

#### Relación árbol deriv - lenguaje

Establecemos que una palabra está en el lenguaje generado por una gramática si y solo si existe un árbol derivado cuyas hojas, leídas de izquierda a derecha, producen dicha palabra.

#### Problema de la palabra 

Definimos el problema de la palabra como: dada una gramática G y una palabra ω, determinar si existe una derivación de ω utilizando G.

El problema de la palabra es resoluble para cualquier gramática libre de contexto.

##### Algoritmo para el problema de la palabra

**Algoritmo de fuerza bruta**
- Comenzamos con el símbolo inicial.
- Probamos todas las derivaciones más a la izquierda posibles.
- El criterio de parada es cuando la configuración es más larga que la palabra objetivo. 

**Consideraciones para el algoritmo de fuerza bruta**
- No puede haber ε-producciones (producciones que generan la palabra vacia).
- Existen algoritmos que sí pueden eliminar ε-producciones de una gramática.
- El algoritmo tiene complejidad exponencial en el tamaño de la palabra de entrada. 
- Más adelante se verá un algoritmo en tiempo lineal con preprocesado.
