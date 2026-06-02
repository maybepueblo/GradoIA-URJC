# Introducción
Se basan en la idea de la **supervivencia de los mejor adaptados** (selección natural).

Manejan un **conjunto de individuos** (población) que compiten por los recursos limitados de un entorno concreto. Estos individuos se **reproducen** (combinan) y generan **descendientes**. Cada gen mejora la anterior.
## Características principales
- Algoritmos estocásticos basados en **población**.
- Los **operadores de variación** (recombinar y mutar) crean la diversidad necesaria e introducen novedad.
- La **selección** reduce la diversidad y actúa como una fuerza que favorece la calidad.
- Se introduce el concepto de **fitness** como el nivel de adaptación al entorno, correspondido a la calidad de la solución.
## Esquema general

![[Pasted image 20260602234117.png]]
# AEs
## Pseudocódigo
*Parámetros de entrada*: tamaño de población, condición de terminación, parámetros 

```
INICIALIZA población con sols aleatorias
EVALUA individuos de la población
REPETIR HASTA (condicion de fin) {
	1. SELECCIÓN de progenitores
	2. RECOMBINACIÓN de progenitores
	3. MUTACIÓN de descendientes
	4. EVALUACIÓN de descendientes
	5. REEMPLAZO de individuos para formar nueva población
}
DEVUELVE mejor individuo
```
## Tipos
**Según cómo representamos los individuos**:
- Cadenas binarias o de enteros
	- AGs, véase [[Tema 12 - Algoritmos genéticos y meméticos]]
- Vectores de números reales
	- Strats evolutivas
	- Evolución diferencial
- Máquinas de estados finitas
	- Programación evolutiva
- Árboles
	- Programación genética, véase [[Tema 13 - Programación genética]]

Diferencias muy irrelevantes:
- Escogemos primero **representación** para el problema
- Luego **operadores** adecuados para variar las soluciones
- Tercero el algoritmo.
Los operadores de selección usan el *fitness* por lo que son independientes de la representación.
## Representar soluciones
Las soluciones candidatas (**individuos**) existen en el **espacio de fenotipos**.
- Esto es, el conjunto de características observables del individuo.
Codificamos a los individuos en **cromosomas**, que existen en el **espacio de genotipos**:
- Codificación: fenotipo -> genotipo (mapeo no necesariamente uno a uno)
- Decodificación: genotipo -> fenotipo (debe ser mapeo uno a uno)
Los cromosomas contienen **genes** que normalmente ubicamos en posiciones fijas llamadas **loci** (locus en singular) y tienen un valor conocido como **alelo**.

> Para poder encontrar el óptimo global, toda solución factible debe poder ser representada en el espacio de genotipos.
## Función de evaluación - ***Fitness function***
Representa los requisitos a los que se debe adaptar la población, también la llamamos **función objetivo** o **función de calidad**.

Asigna un valor de fitness a cada fenotipo (número real) y cuanto más discriminatorio sea (mayor número de valores diferentes produzca para los distintos fenotipos), mejor.
- Así la selección y el reemplazo se ejecutan con criterio
- Evitamos "flat landscape", que se concentre todo en valores específicos.

Funciones capaces de tener topologías muy complicadas.
- Las usamos como test para nuevos algoritmos.
## Población
El conjunto de representaciones de posibles sols.
- Multiconjunto de genotipos

Tiene un tamaño fijo de normal, se puede definir con una estructura espacial de rejilla en otros casos sofisticados.

Nuestros operadores de selección tienen que tener en cuenta toda la población, las chances de reproducir son relativas a la generación actual.

**Diversidad** -> número de valores diferentes de *fitness* / fenotipos / genotipos presentes.
- Puede ser diferente en cada uno de estos aspectos.
## Elegir progenitores
Asignamos probabilidad según nuestro fitness para los individuos que serán los padres.

La selección es típicamente probabilista:
- Solución de alta calidad -> Más chance de ser progenitor
- No siempre está garantizado
- Incluso el peor individuo puede tener probabilidad mayor que cero.
**Esta naturaleza estocástica nos ayuda a escapar de óptimos locales**
## Operadores de variación
Generan nuevas soluciones candidatas.

Los clasificamos según el número de soluciones que involucran (**aridad**):
- Aridad 1: Operadores de **mutación**
- Aridad >1: operadores de **recombinación**
- Aridad =2: se les llama **cruce** (crossover)
### Mutación
- Actua sobre un genotipo
- Esencial tener factor aleatorio. Esto lo hace distinto de los heurísticos unarios.
- Garantiza conectividad en el espacio de búsqueda, demuestra convergencia.
### Recombinación
- Mezclamos info de los progenitores en sus descendientes (*offspring*)
- Elegir qué info mezclar puede ser estocástica.
- La mayoría de los descendientes pueden ser peores o iguales que sus padres.
- Esperamos que alguno sea mejor al combinar elementos de genotipos que codifican buenas soluciones.
### Reemplazo
- **Selección de supervivientes** para la siguiente generación.
- Se suele manejar un tamaño fijo, con lo que hay que elegir cómo escoger la siguiente generación.
- El reemplazo se decide habitualmente de forma determinista:
	- En función del fitness: e.j ranking de progenitores + descendientes
	- Basado en "edad": tantos descendientes como progenitores y seleccionado a todos los descendientes
	- Se pueden combinar técnicas
- El **elitismo** es mantener en la población al mejor individuo o a varios de los mejores.
## Inicialización / Terminación
Se suele hacer de forma aleatoria la **inicialización**:
- Garantizar una distribución y mezcla uniforme de los posibles valores de alelos.
- Podemos incluir soluciones existentes o usar heurísticas específicas.
Luego comprobamos la **condición de terminación** en cada generación:
- Alcanzar cierto fitness (conocido/esperado)
- Alcanzar número máximo permitido de generaciones
- Alcanzar un nivel mínimo de diversidad
- Alcanzar un número específico de generaciones sin mejorar fitness
# Consideraciones en AEs
En la optimización de un fitness landscape (relación entre genotipos y su exito al reproducirse) esperamos el siguiente comportamiento por fases:
- Fase inicial: distribución cuasi-aleatoria de la población
- Fase intermedia: se organiza alrededor/sobre las colinas
- Fase final: se concentran en las colinas más altas

Luego en la función de fitness es típico que se muestre el llamado "anytime behavior":
- Esto es, en cualquier momento que pares el algoritmo, tienes una solución válida.
	- Más tiempo corriendo -> Mejor solución

Sabiendo esto... ¿son beneficiosas las **ejecuciones largas**? Depende de cuánto necesitemos esa última mejora. Puede ser mejor hacer ejecuciones más cortas (cada vez nos toma más notar una mejoría significativa). 

Sin embargo SÍ es importante y merece la pena implementar **inicializaciones inteligentes** cuando existan buenas soluciones/métodos pero esto nos puede perjudicar la diversidad
# Contexto de EAs
Para la mayoría de problemas una herramienta específica puede:
- tener un mejor rendimiento que un algoritmo de búsqueda genérico en la mayoría de casos,
- una utilidad limitada,
- no tener un buen rendimiento en todos los casos

Buscamos entonces dar herramientas robustas que den:
- un rendimiento uniformemente bueno en una variedad de problemas e instancias.

Así, visualizamos lo siguiente:

![[Pasted image 20260603002406.png]]

Los métodos de los evolutivos son en promedios mejores que las búsquedas convencionales aleatorias y no muy lejanas a lo específico. Por ello son correctos en su uso.
# EAs y conocimiento del dominio
Había una tendencia de afinar con conocimiento específico del problema al EA. Esto nos daba una "deformación" de la curva recién vista:
- mejor en problema específico
- peor en problemas distintos del específico
- cantidad de conocimiento añadido variable
El buscar un algoritmo para todo uso puede que no de frutos.

![[Pasted image 20260603002635.png]]