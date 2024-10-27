#### Introducción

Ciertos problemas requieren realizar una búsqueda exhaustiva por el espacio de posibles soluciones hasta que encontremos una solución o constatemos que no existe solución. 

Nuestro esquema **Vuelta Atrás** genera de forma **sistemática** posibles soluciones. Este espacio de soluciones se plantea en términos de un **grafo (o árbol) implícito**.

**Casos de uso**
- Necesito una solución -> Paramos en cuanto encontremos la primera solución factible.
- Necesito todas las soluciones -> El algoritmo recorre todo el espacio de soluciones.
- Necesito la MEJOR solución -> Recorremos todo el espacio de soluciones y devolvemos el mejor resultado de todos.

Conseguimos un árbol que representa todas las soluciones.

![[Árbol implícito Backtracking|600]]

Realizamos un recorrido en profundidad en un grafo dirigido implícito y sin ciclos conocido como *Árbol de Exploración*.
#### Estrategia general

A medida que progresamos en recorrido se construyen soluciones parciales (n-tupla) (ya que no hemos decidido qué hacer con lo generado).

Cuando llegamos a un nodo hoja y la solución no es completa, entonces el recorrido no es exitoso y hacemos backtracking:
- Eliminaremos el último elemento de la tupla.
- Intentamos construir añadiendo otro elemento diferente.

En el caso de que lleguemos a una hoja con solución completa, el recorrido ha sido exitoso.
- Si sólo buscamos una solución, el algoritmo se detiene. 
- En caso contrario, hacemos **backtracking**.

**n-tupla**
Es una solución factible si verifica las siguientes restricciones:
- **Explícitas**: indican los valores que puede tomar cada componente de una tupla solución (Soluciones factibles + no factibles).
- **Implícitas**: Las que tenemos que cumplir para que la solución sea factible.

**Espacio de soluciones**
Conjunto de tuplas que satisfacen las restricciones explícitas (factibles y no factibles).

**Árbol de exploración**
Forma de estructurar el espacio de soluciones factibles
	**Nodo del árbol**
	Tupla parcial (prometedora) o completa (sol. factible)

**Función de poda o Test de factibilidad**
Determinamos con esto si esta tupla parcial es o no prometedora. Se trata en [[Tema 5 - Ramificación y poda]].

##### ¿Cómo identificar si podemos usar bt?

**Principal**
Una solución, mejor solución o todas las soluciones es seguro que es backtracking. 

Si no, siempre que la solución se exprese como una n-tupla, tengamos que hallar un recorrido en profundidad sobre el árbol de exploración o cuando cada etapa representa un nivel en el árbol de busqueda.

Complejidad algorítmica de esto? -> O(n!)

>[!NOTE]
>Si el tamaño de la entrada en el apartado de límites es pequeño para N, puede ser backtracking, ya que si fuera mayor no daría abasto la memoria.

#### Esquema de la técnica

```python
procedimiento VueltaAtras(v[1..k])
si EsSolucion(v[1..k]) entonces
	escribir v {o almacenar v}
sino
para ei={e1,..,ej} hacer {ei: comp. disp.}
	v[k+1] ← ei
 si EsPrometedor(v[1..k+1]) entonces
	VueltaAtras(v[1..k+1])
 fsi
	fpara
fsi
fprocedimiento
```

- v[1..k] es una tupla (nodo).
- EsSolucion() es una función que indica si la tupla es solucion.
- {e1, .., ej} es un conjunto de posibles sucesores dada una tupla.
- EsPrometedor(v[1...k+1]) es una función que determina si una tupla se puede podar.
#### Ejemplos 

##### Mochila backtracking

```
funcion mochilaVA(i,r:entero):entero
 {i: construir usando los elementos i al n y cuyo
 peso no sobrepase r}
 b ← 0;
 para k ← i hasta n hacer
  si (w[k] ≤ r) entonces
	b ← max(b,v[k]+mochilaVA(k,r-w[k]));
  fsi
 fpara
 devolver b
ffun
```

>[!NOTE]
>Suponemos que w[k], v[k] y n se encuentran disponibles
>

En este código falta saber cómo voy a probar todos los nodos en un nivel concreto si no voy a deshacer un movimiento hecho previamente. En este caso si el movimiento no me lleva a una sol. factible, tendremos que deshacer el movimiento.
