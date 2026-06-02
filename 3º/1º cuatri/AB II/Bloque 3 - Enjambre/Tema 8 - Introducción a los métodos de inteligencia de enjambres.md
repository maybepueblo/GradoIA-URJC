# Introducción a los algoritmos bioinspirados
Son algoritmos inspirados por la naturaleza que usamos para resolver problemas como:
- **Evolución** -> adaptación al entorno
- **Comportamiento de especies** -> supervivencia
- **Genética** -> transmitir características relevantes
También se inspiran en fenómenos físicos como el enfriamiento simulado.
## Categorías de algoritmos
- **Inteligencia de enjambres**:
	- Optimización por enjambre de partículas (PSO), véase [[Tema 9 - Optimización por enjambre de partículas]]
	- Optimización por colonia de hormigas (ACO), véase [[Tema 10 - Optimización por colonia de hormigas]]
- **Algoritmos evolutivos**, véase [[Tema 11 - Introducción a los algoritmos evolutivos]]
	- Algoritmos genéticos (GA), véase [[Tema 12 - Algoritmos genéticos y meméticos]]
	- Estrategias evolutivas (ES)
	- Evolución diferencial (DE)
	- Programación evolutiva (EP)
	- Programación genética (GP), véase [[Tema 13 - Programación genética]]
- **Algoritmos basados en fenómenos físicos**
	- Enfriamiento simulado (SA), véase [[Tema 5 - Simulated Annealing]]
## Características principales
- **Población de soluciones**: No como los trayectoriales, suelen trabajar con una población de soluciones, no una solo. Esto nos da amplitud al explorar el espacio de soluciones y nos ayuda a escapar de mínimos locales.
- **Aleatoriedad y estocasticidad**: Incorporan elementos aleatorios en sus procesos, como la selección de soluciones, mutaciones o movimientos en el espacio de soluciones. Esto nos hace explorar mejor el espacio de búsqueda y a evitar quedarnos atrapados en soluciones subóptimas
- **Iteratividad y generación de nuevas soluciones**: Funcionan de forma iterativa generando nuevas soluciones a partir de la población actual mediante operadores como recombinar, mutar o moverse basado en reglas (actualizar velocidades en caso de enjambres)
- **Adaptación y aprendizaje**: Simulan estos presentes en lo biológico. E.j -> la selección natural, las mejores soluciones (aptas) tienen mayor probabilidad de sobrevivir y propagarse.
- **Paralelismo intrínseco**: Por su naturaleza de poblaciones son muy paralelizables. Podemos evaluar y modificar varias soluciones en paralelo (eficiente)
- **Robustez y flexibilidad**: Son generalmente robustos y pueden adaptarse a diferentes tipos de problemas (optimización combinatoria, continua o multiobjetivo).
- **Exploración y explotación del espacio de búsqueda**: Equilibramos estas a través de viersos mecanismos como la mutación en GA o el ajuste de parámetros en PSO.
- **Uso de heurísticas**: Muchos algoritmos bioinspirados dependen de heurísticas simples que guían la generación y selección de nuevas soluciones. Esto los hace fáciles de implementar y ajustar a diversos problemas.
- **No requieren gradientes:** Ventajoso para problemas no diferenciables o con múltiples óptimos locales.
- **Son explicables**: Siguen reglas sencillas y fáciles de explicar.
# Introducción a la Inteligencia de Enjambres
A partir de lo observado en la naturaleza y primeramente en 1989, se han propuesto muchos algoritmos basado en este comportamiento de enjambre.

Los más relevantes:
- PSO - Enjambre de partículas
- ACO - Colonia de hormigas
- ABC - Colonia de abejas
## Características principales
Son algoritmos poblacionales **autoorganizados**, es decir, cada individuo de la población tiene un **comportamiento individual** simple que viene condicionado por el entorno.

Algunos algoritmos definen **comportamientos especializados** por individuo, esto les denomina **agentes**.

Dicha autoorganización requiere **interacción entre individuos**:
- Directa como los bancos de peces
- Indirecta a través del entorno (estigmergia)
	- Reduce comunicación entre agentes
	- Evita un gestor central

Presentamos **dos modos de interactuar**:
- Retroalimentación positiva -> amplificación que promueve cambios en el sistema
- Retroalimentación negativa -> previene cambios en el sistema permitiendo una vuelta a la estabilidad.

Las decisiones individuales deben de tener una componente aleatoria que permita ampliar la capacidad de explorar.
