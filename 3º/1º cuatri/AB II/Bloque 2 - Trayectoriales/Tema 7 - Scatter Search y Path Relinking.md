A partir de ahora serán SS y PR para amenizar la lectura.
# Introducción
Son algoritmos de optimización que datan del 1977. Algunas de las ideas subyacentes estaban presentes a inicios de los 70:
- Combinar reglas de decisión
- Problemas de satisfacción de restricciones (método de restricciones subrogadas)
## Características
- Están basados en usar **poblaciones**
- **Combina soluciones** almacenadas en un conjunto de referencia denominado RefSet.
- A diferencia de los genéticos, SS y PR usan **estrategias sistemáticas**, no aleatorias.
- Usan **conjuntos de soluciones pequeñas** (unas 10, no como las 100 típicas en genéticos)
# Scatter Search
Opera sobre las soluciones del conjunto de referencia combinándolas para crear nuevas soluciones. Así, serán mejores que la original.

Para esto, se basa en el principio siguiente:
- *la información sobre la calidad o el atractivo de un conjunto de reglas, restricciones o soluciones puede ser usado mediante combinación de estas en lugar de aisladamente*

Adicionalmente suele integrar la combinación de soluciones con la búsqueda local u otras metaheurísticas sofisticadas.

Originalmente se establecieron los siguientes **principios relacionados con la combinación de soluciones**:
- SS busca combinar dos o más soluciones de un RefSet, lo que genera centroides.
- Generar soluciones en la línea de unión de dos soluciones es una simplificación del método.
- Al combinar, usamos pesos adecuados
- Hay que realizar combinaciones "convexas" y "no convexas" de las soluciones.

De esto destacamos las siguientes aportaciones:
- Combinación ponderada de soluciones
- Mecanismos de combinación por votos: una solución vota para que sus características aparezcan en la solución que se genera.
## Esquema algorítmico
SS se compone por una gran variedad de métodos. Vamos a verlos.
### Diversification Generation Method
- Genera soluciones diversas
- Encargado de generar un conjunto P de soluciones (tamaño 1000 tipicamente)
- De este P sacaremos 10 sols que serán parte del RefSet
### Improvement Method
- Mejora
- Suele ser una búsqueda local pero puede ser más sofisticado
- Tienen que ser factibles las soluciones que genere
### Reference Set Update Method
- Crea y actualiza el RefSet
- **Creación** -> a partir de P genera el RefSet de tamaño b eligiendo:
	- las b/2 mejores soluciones
	- las b/2 soluciones más diversas: extraemos de P con el criterio de maximizar la mínima distancia con las ya incluidas en b. Es necesaria una función distancia.
- **Actualización** -> las soluciones generadas pueden ser mejores que las del RefSet. Puede interesarnos meterlas aquí reemplazando las de menor calidad. También se admiten criterios de diversidad. 
### Subset Generation Method
- Generación de subconjuntos de soluciones que serán combinadas.
- Suelen ser parejas
- Usualmente se consideran todas las parejas posibles en el RefSet
### Solution Combination Method
- Combina las soluciones.
- Lo aplicamos a todos los subconjuntos dados por el método anterior
- Las buenas actualizaciones construidas podemos meterlas inmediatamente en el RefSet (update dinámico) o almacenarlas temporalmente hasta tener todas las combinaciones completas (update estático)
### Visualización

![[Pasted image 20260531222245.png]]
## Pseudocódigo
1. P←ø. Generar x con el método de generacion de soluciones. Aplicar a x el método de mejora. Si x ∈ P, rechazar x. Si no, añadir x a P. Repetir hasta completar P.
2. Construir RefSet con las b/2 mejores soluciones de P y las b/2 más diversas
3. Evaluar las soluciones en RefSet y ordenarlas de mayor a menor calidad
4. NuevaSolucion ← TRUE
   WHILE (NuevaSolucion) DO
5. NuevaSolucion ← FALSE
6. Generar subconjuntos en RefSet con, al menos, una solución nueva
   WHILE (Queden subconjuntos sin examinar) DO
7. Seleccionar un subconjunto y marcarlo como examinado
8. Aplicar el método de combinación a las soluciones del conjunto
9. Aplicar el método de mejora a la solución generada x.
   IF f(x)<f(xb) THEN
10. xb ← x. Reordenar RefSet.
11. NuevaSolucion ← TRUE
## Strats avanzadas y decisiones de diseño
- **No sabemos el tamaño óptimo del Refset** ¿tamaño variable?
- **Aplicar el método de mejora sólo a algunas de las soluciones generadas**: Esto evita la convergencia prematura
- Estudiar el % de tiempo empleado en construir sols y mejorarlas: compromiso **diversificación-intensificación**
- **Uso de memoria** de frecuencia para desarrollar diversificación eficiente, véase [[Tema 4 - Tabu Search]]
- **Actualizar por calidad** que por diversidad
- **¿Update estático o dinámico?**
- Combinar dos buenas sols suele producir una buena solución
- Estudiar otros % de **sols de calidad y diversas**
- La mayoría de buenas sols vienen de combinar buenas sols
- Considerar el uso de **varios métodos de combinación**