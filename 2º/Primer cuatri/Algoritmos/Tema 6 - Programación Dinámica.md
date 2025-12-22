#### Introducción

En [[Divide y Vencerás]] vimos lo siguiente:
- dividir un problema en subproblemas
- resolverlos
- combinar las soluciones para resolver el problema original

En ocasiones, la división produce subproblemas solapados, que comportan cálculos repetidos. Si no tuvisiemos cuidado, desarrollaríamos algoritmos poco eficientes.

Por eso estudiamos la **Programación Dinámica**, que trata de resolver cada subejemplar una sola vez, almacenando la solución para usarla tantas veces como sea necesario.

Así, como diferencias tenemos lo siguiente:
- DyV es un método de refinamiento sucesivo, atacando el problema completo mientras se divide el problema en subproblemas más sencillos.
- Mientras que en la programación dinámica, hablamos de un método ascendente: empezando por resolver casos simples, combinando las soluciones para obtener respuesta a casos más complejos.

--- 

**Principio de optimalidad** --> "En una sucesión óptima de decisiones u opciones, cualquier subsecuencia debe también ser óptima"
- Este principio no es siempre aplicable:
	- ej: utilización óptima de un conjunto de recursos limitados
	- En este problema, la combinación de soluciones óptimas de dos o más subcasos no ha de ser factible porque sí. 

Los problemas para los que son aplicables son candidatos a ser resueltos con programación dinámica.




